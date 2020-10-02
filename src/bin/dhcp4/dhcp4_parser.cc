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
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 336 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 344 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 930 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 347 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 938 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 355 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 359 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 366 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 964 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 368 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 973 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 377 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 381 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 991 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 392 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1002 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 401 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 406 "dhcp4_parser.yy"
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
#line 416 "dhcp4_parser.yy"
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
#line 425 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 433 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1061 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 437 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1070 "dhcp4_parser.cc"
    break;

  case 118: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 504 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1080 "dhcp4_parser.cc"
    break;

  case 119: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 510 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 120: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 516 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1100 "dhcp4_parser.cc"
    break;

  case 121: // renew_timer: "renew-timer" ":" "integer"
#line 522 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 122: // rebind_timer: "rebind-timer" ":" "integer"
#line 528 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 123: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 534 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 124: // t1_percent: "t1-percent" ":" "floating point"
#line 540 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 125: // t2_percent: "t2-percent" ":" "floating point"
#line 546 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1150 "dhcp4_parser.cc"
    break;

  case 126: // cache_threshold: "cache-threshold" ":" "floating point"
#line 552 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1160 "dhcp4_parser.cc"
    break;

  case 127: // cache_max_age: "cache-max-age" ":" "integer"
#line 558 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1170 "dhcp4_parser.cc"
    break;

  case 128: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 564 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 129: // $@20: %empty
#line 570 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 130: // server_tag: "server-tag" $@20 ":" "constant string"
#line 573 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1199 "dhcp4_parser.cc"
    break;

  case 131: // echo_client_id: "echo-client-id" ":" "boolean"
#line 579 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1209 "dhcp4_parser.cc"
    break;

  case 132: // match_client_id: "match-client-id" ":" "boolean"
#line 585 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1219 "dhcp4_parser.cc"
    break;

  case 133: // authoritative: "authoritative" ":" "boolean"
#line 591 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 134: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 597 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1239 "dhcp4_parser.cc"
    break;

  case 135: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 603 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 136: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 609 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1259 "dhcp4_parser.cc"
    break;

  case 137: // $@21: %empty
#line 615 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 138: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 618 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 139: // ddns_replace_client_name_value: "when-present"
#line 624 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1285 "dhcp4_parser.cc"
    break;

  case 140: // ddns_replace_client_name_value: "never"
#line 627 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1293 "dhcp4_parser.cc"
    break;

  case 141: // ddns_replace_client_name_value: "always"
#line 630 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1301 "dhcp4_parser.cc"
    break;

  case 142: // ddns_replace_client_name_value: "when-not-present"
#line 633 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1309 "dhcp4_parser.cc"
    break;

  case 143: // ddns_replace_client_name_value: "boolean"
#line 636 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1318 "dhcp4_parser.cc"
    break;

  case 144: // $@22: %empty
#line 642 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "dhcp4_parser.cc"
    break;

  case 145: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 645 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1337 "dhcp4_parser.cc"
    break;

  case 146: // $@23: %empty
#line 651 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 147: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 654 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 148: // $@24: %empty
#line 660 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1365 "dhcp4_parser.cc"
    break;

  case 149: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 663 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1375 "dhcp4_parser.cc"
    break;

  case 150: // $@25: %empty
#line 669 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1384 "dhcp4_parser.cc"
    break;

  case 151: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 672 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 152: // store_extended_info: "store-extended-info" ":" "boolean"
#line 678 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1404 "dhcp4_parser.cc"
    break;

  case 153: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 684 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1414 "dhcp4_parser.cc"
    break;

  case 154: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 690 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1424 "dhcp4_parser.cc"
    break;

  case 155: // $@26: %empty
#line 696 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 156: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 702 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 166: // $@27: %empty
#line 721 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 167: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 725 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 168: // $@28: %empty
#line 730 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1477 "dhcp4_parser.cc"
    break;

  case 169: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 736 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1486 "dhcp4_parser.cc"
    break;

  case 170: // $@29: %empty
#line 741 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 171: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 744 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 172: // socket_type: "raw"
#line 749 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1510 "dhcp4_parser.cc"
    break;

  case 173: // socket_type: "udp"
#line 750 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1516 "dhcp4_parser.cc"
    break;

  case 174: // $@30: %empty
#line 753 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 175: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 756 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 176: // outbound_interface_value: "same-as-inbound"
#line 761 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1542 "dhcp4_parser.cc"
    break;

  case 177: // outbound_interface_value: "use-routing"
#line 763 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1550 "dhcp4_parser.cc"
    break;

  case 178: // re_detect: "re-detect" ":" "boolean"
#line 767 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1560 "dhcp4_parser.cc"
    break;

  case 179: // $@31: %empty
#line 774 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1572 "dhcp4_parser.cc"
    break;

  case 180: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 780 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 181: // $@32: %empty
#line 787 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1595 "dhcp4_parser.cc"
    break;

  case 182: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 793 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 186: // $@33: %empty
#line 803 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1613 "dhcp4_parser.cc"
    break;

  case 187: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 806 "dhcp4_parser.yy"
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
#line 1633 "dhcp4_parser.cc"
    break;

  case 188: // $@34: %empty
#line 822 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 189: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 828 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1656 "dhcp4_parser.cc"
    break;

  case 190: // $@35: %empty
#line 835 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1668 "dhcp4_parser.cc"
    break;

  case 191: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 841 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1677 "dhcp4_parser.cc"
    break;

  case 196: // $@36: %empty
#line 854 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1687 "dhcp4_parser.cc"
    break;

  case 197: // database: "{" $@36 database_map_params "}"
#line 858 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1697 "dhcp4_parser.cc"
    break;

  case 221: // $@37: %empty
#line 891 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1706 "dhcp4_parser.cc"
    break;

  case 222: // database_type: "type" $@37 ":" db_type
#line 894 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1715 "dhcp4_parser.cc"
    break;

  case 223: // db_type: "memfile"
#line 899 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1721 "dhcp4_parser.cc"
    break;

  case 224: // db_type: "mysql"
#line 900 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1727 "dhcp4_parser.cc"
    break;

  case 225: // db_type: "postgresql"
#line 901 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1733 "dhcp4_parser.cc"
    break;

  case 226: // db_type: "cql"
#line 902 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1739 "dhcp4_parser.cc"
    break;

  case 227: // $@38: %empty
#line 905 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1748 "dhcp4_parser.cc"
    break;

  case 228: // user: "user" $@38 ":" "constant string"
#line 908 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1758 "dhcp4_parser.cc"
    break;

  case 229: // $@39: %empty
#line 914 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1767 "dhcp4_parser.cc"
    break;

  case 230: // password: "password" $@39 ":" "constant string"
#line 917 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1777 "dhcp4_parser.cc"
    break;

  case 231: // $@40: %empty
#line 923 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1786 "dhcp4_parser.cc"
    break;

  case 232: // host: "host" $@40 ":" "constant string"
#line 926 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1796 "dhcp4_parser.cc"
    break;

  case 233: // port: "port" ":" "integer"
#line 932 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1806 "dhcp4_parser.cc"
    break;

  case 234: // $@41: %empty
#line 938 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1815 "dhcp4_parser.cc"
    break;

  case 235: // name: "name" $@41 ":" "constant string"
#line 941 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1825 "dhcp4_parser.cc"
    break;

  case 236: // persist: "persist" ":" "boolean"
#line 947 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1835 "dhcp4_parser.cc"
    break;

  case 237: // lfc_interval: "lfc-interval" ":" "integer"
#line 953 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1845 "dhcp4_parser.cc"
    break;

  case 238: // readonly: "readonly" ":" "boolean"
#line 959 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1855 "dhcp4_parser.cc"
    break;

  case 239: // connect_timeout: "connect-timeout" ":" "integer"
#line 965 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1865 "dhcp4_parser.cc"
    break;

  case 240: // request_timeout: "request-timeout" ":" "integer"
#line 971 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1875 "dhcp4_parser.cc"
    break;

  case 241: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 977 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1885 "dhcp4_parser.cc"
    break;

  case 242: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 983 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1895 "dhcp4_parser.cc"
    break;

  case 243: // $@42: %empty
#line 989 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1904 "dhcp4_parser.cc"
    break;

  case 244: // contact_points: "contact-points" $@42 ":" "constant string"
#line 992 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1914 "dhcp4_parser.cc"
    break;

  case 245: // $@43: %empty
#line 998 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc"
    break;

  case 246: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1001 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc"
    break;

  case 247: // $@44: %empty
#line 1007 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1942 "dhcp4_parser.cc"
    break;

  case 248: // consistency: "consistency" $@44 ":" "constant string"
#line 1010 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1952 "dhcp4_parser.cc"
    break;

  case 249: // $@45: %empty
#line 1016 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1961 "dhcp4_parser.cc"
    break;

  case 250: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1019 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 251: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1025 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 252: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1031 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 253: // max_row_errors: "max-row-errors" ":" "integer"
#line 1037 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 254: // $@46: %empty
#line 1044 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2013 "dhcp4_parser.cc"
    break;

  case 255: // host_reservation_identifiers: "host-reservation-identifiers" $@46 ":" "[" host_reservation_identifiers_list "]"
#line 1050 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 263: // duid_id: "duid"
#line 1066 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2031 "dhcp4_parser.cc"
    break;

  case 264: // hw_address_id: "hw-address"
#line 1071 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2040 "dhcp4_parser.cc"
    break;

  case 265: // circuit_id: "circuit-id"
#line 1076 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2049 "dhcp4_parser.cc"
    break;

  case 266: // client_id: "client-id"
#line 1081 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2058 "dhcp4_parser.cc"
    break;

  case 267: // flex_id: "flex-id"
#line 1086 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2067 "dhcp4_parser.cc"
    break;

  case 268: // $@47: %empty
#line 1093 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 269: // dhcp_multi_threading: "multi-threading" $@47 ":" "{" multi_threading_params "}"
#line 1099 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2090 "dhcp4_parser.cc"
    break;

  case 278: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1118 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 279: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1124 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 280: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1130 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2120 "dhcp4_parser.cc"
    break;

  case 281: // $@48: %empty
#line 1136 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2132 "dhcp4_parser.cc"
    break;

  case 282: // hooks_libraries: "hooks-libraries" $@48 ":" "[" hooks_libraries_list "]"
#line 1142 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2141 "dhcp4_parser.cc"
    break;

  case 287: // $@49: %empty
#line 1155 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2151 "dhcp4_parser.cc"
    break;

  case 288: // hooks_library: "{" $@49 hooks_params "}"
#line 1159 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2161 "dhcp4_parser.cc"
    break;

  case 289: // $@50: %empty
#line 1165 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc"
    break;

  case 290: // sub_hooks_library: "{" $@50 hooks_params "}"
#line 1169 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2181 "dhcp4_parser.cc"
    break;

  case 296: // $@51: %empty
#line 1184 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2190 "dhcp4_parser.cc"
    break;

  case 297: // library: "library" $@51 ":" "constant string"
#line 1187 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2200 "dhcp4_parser.cc"
    break;

  case 298: // $@52: %empty
#line 1193 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 299: // parameters: "parameters" $@52 ":" map_value
#line 1196 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2218 "dhcp4_parser.cc"
    break;

  case 300: // $@53: %empty
#line 1202 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 301: // expired_leases_processing: "expired-leases-processing" $@53 ":" "{" expired_leases_params "}"
#line 1208 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc"
    break;

  case 310: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1226 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2250 "dhcp4_parser.cc"
    break;

  case 311: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1232 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 312: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1238 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2270 "dhcp4_parser.cc"
    break;

  case 313: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1244 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2280 "dhcp4_parser.cc"
    break;

  case 314: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1250 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2290 "dhcp4_parser.cc"
    break;

  case 315: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1256 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 316: // $@54: %empty
#line 1265 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2312 "dhcp4_parser.cc"
    break;

  case 317: // subnet4_list: "subnet4" $@54 ":" "[" subnet4_list_content "]"
#line 1271 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2321 "dhcp4_parser.cc"
    break;

  case 322: // $@55: %empty
#line 1291 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2331 "dhcp4_parser.cc"
    break;

  case 323: // subnet4: "{" $@55 subnet4_params "}"
#line 1295 "dhcp4_parser.yy"
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
#line 2357 "dhcp4_parser.cc"
    break;

  case 324: // $@56: %empty
#line 1317 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2367 "dhcp4_parser.cc"
    break;

  case 325: // sub_subnet4: "{" $@56 subnet4_params "}"
#line 1321 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2377 "dhcp4_parser.cc"
    break;

  case 368: // $@57: %empty
#line 1375 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 369: // subnet: "subnet" $@57 ":" "constant string"
#line 1378 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2396 "dhcp4_parser.cc"
    break;

  case 370: // $@58: %empty
#line 1384 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2405 "dhcp4_parser.cc"
    break;

  case 371: // subnet_4o6_interface: "4o6-interface" $@58 ":" "constant string"
#line 1387 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2415 "dhcp4_parser.cc"
    break;

  case 372: // $@59: %empty
#line 1393 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2424 "dhcp4_parser.cc"
    break;

  case 373: // subnet_4o6_interface_id: "4o6-interface-id" $@59 ":" "constant string"
#line 1396 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2434 "dhcp4_parser.cc"
    break;

  case 374: // $@60: %empty
#line 1402 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp4_parser.cc"
    break;

  case 375: // subnet_4o6_subnet: "4o6-subnet" $@60 ":" "constant string"
#line 1405 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc"
    break;

  case 376: // $@61: %empty
#line 1411 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2462 "dhcp4_parser.cc"
    break;

  case 377: // interface: "interface" $@61 ":" "constant string"
#line 1414 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2472 "dhcp4_parser.cc"
    break;

  case 378: // $@62: %empty
#line 1420 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2481 "dhcp4_parser.cc"
    break;

  case 379: // client_class: "client-class" $@62 ":" "constant string"
#line 1423 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 380: // $@63: %empty
#line 1429 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp4_parser.cc"
    break;

  case 381: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1435 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2512 "dhcp4_parser.cc"
    break;

  case 382: // $@64: %empty
#line 1440 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 383: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1443 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 384: // hr_mode: "disabled"
#line 1448 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2536 "dhcp4_parser.cc"
    break;

  case 385: // hr_mode: "out-of-pool"
#line 1449 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2542 "dhcp4_parser.cc"
    break;

  case 386: // hr_mode: "global"
#line 1450 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2548 "dhcp4_parser.cc"
    break;

  case 387: // hr_mode: "all"
#line 1451 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2554 "dhcp4_parser.cc"
    break;

  case 388: // id: "id" ":" "integer"
#line 1454 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2564 "dhcp4_parser.cc"
    break;

  case 389: // $@65: %empty
#line 1462 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2576 "dhcp4_parser.cc"
    break;

  case 390: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1468 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2585 "dhcp4_parser.cc"
    break;

  case 395: // $@66: %empty
#line 1483 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 396: // shared_network: "{" $@66 shared_network_params "}"
#line 1487 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2603 "dhcp4_parser.cc"
    break;

  case 434: // $@67: %empty
#line 1536 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2615 "dhcp4_parser.cc"
    break;

  case 435: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1542 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2624 "dhcp4_parser.cc"
    break;

  case 436: // $@68: %empty
#line 1550 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2633 "dhcp4_parser.cc"
    break;

  case 437: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1553 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2641 "dhcp4_parser.cc"
    break;

  case 442: // $@69: %empty
#line 1569 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2651 "dhcp4_parser.cc"
    break;

  case 443: // option_def_entry: "{" $@69 option_def_params "}"
#line 1573 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2663 "dhcp4_parser.cc"
    break;

  case 444: // $@70: %empty
#line 1584 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 445: // sub_option_def: "{" $@70 option_def_params "}"
#line 1588 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2685 "dhcp4_parser.cc"
    break;

  case 461: // code: "code" ":" "integer"
#line 1620 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 463: // $@71: %empty
#line 1628 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp4_parser.cc"
    break;

  case 464: // option_def_type: "type" $@71 ":" "constant string"
#line 1631 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc"
    break;

  case 465: // $@72: %empty
#line 1637 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp4_parser.cc"
    break;

  case 466: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1640 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2733 "dhcp4_parser.cc"
    break;

  case 467: // $@73: %empty
#line 1646 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2742 "dhcp4_parser.cc"
    break;

  case 468: // space: "space" $@73 ":" "constant string"
#line 1649 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 470: // $@74: %empty
#line 1657 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2761 "dhcp4_parser.cc"
    break;

  case 471: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1660 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 472: // option_def_array: "array" ":" "boolean"
#line 1666 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 473: // $@75: %empty
#line 1676 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2793 "dhcp4_parser.cc"
    break;

  case 474: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1682 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 479: // $@76: %empty
#line 1701 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 480: // option_data_entry: "{" $@76 option_data_params "}"
#line 1705 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 481: // $@77: %empty
#line 1713 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 482: // sub_option_data: "{" $@77 option_data_params "}"
#line 1717 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2840 "dhcp4_parser.cc"
    break;

  case 497: // $@78: %empty
#line 1750 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp4_parser.cc"
    break;

  case 498: // option_data_data: "data" $@78 ":" "constant string"
#line 1753 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 501: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1763 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 502: // option_data_always_send: "always-send" ":" "boolean"
#line 1769 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2879 "dhcp4_parser.cc"
    break;

  case 503: // $@79: %empty
#line 1778 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 504: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1784 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 509: // $@80: %empty
#line 1799 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2910 "dhcp4_parser.cc"
    break;

  case 510: // pool_list_entry: "{" $@80 pool_params "}"
#line 1803 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 511: // $@81: %empty
#line 1809 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2930 "dhcp4_parser.cc"
    break;

  case 512: // sub_pool4: "{" $@81 pool_params "}"
#line 1813 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2940 "dhcp4_parser.cc"
    break;

  case 522: // $@82: %empty
#line 1832 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2949 "dhcp4_parser.cc"
    break;

  case 523: // pool_entry: "pool" $@82 ":" "constant string"
#line 1835 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2959 "dhcp4_parser.cc"
    break;

  case 524: // $@83: %empty
#line 1841 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 525: // user_context: "user-context" $@83 ":" map_value
#line 1843 "dhcp4_parser.yy"
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
#line 2994 "dhcp4_parser.cc"
    break;

  case 526: // $@84: %empty
#line 1866 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp4_parser.cc"
    break;

  case 527: // comment: "comment" $@84 ":" "constant string"
#line 1868 "dhcp4_parser.yy"
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
#line 3031 "dhcp4_parser.cc"
    break;

  case 528: // $@85: %empty
#line 1896 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 529: // reservations: "reservations" $@85 ":" "[" reservations_list "]"
#line 1902 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 534: // $@86: %empty
#line 1915 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 535: // reservation: "{" $@86 reservation_params "}"
#line 1919 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 536: // $@87: %empty
#line 1924 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 537: // sub_reservation: "{" $@87 reservation_params "}"
#line 1928 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 557: // $@88: %empty
#line 1959 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3099 "dhcp4_parser.cc"
    break;

  case 558: // next_server: "next-server" $@88 ":" "constant string"
#line 1962 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3109 "dhcp4_parser.cc"
    break;

  case 559: // $@89: %empty
#line 1968 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3118 "dhcp4_parser.cc"
    break;

  case 560: // server_hostname: "server-hostname" $@89 ":" "constant string"
#line 1971 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3128 "dhcp4_parser.cc"
    break;

  case 561: // $@90: %empty
#line 1977 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3137 "dhcp4_parser.cc"
    break;

  case 562: // boot_file_name: "boot-file-name" $@90 ":" "constant string"
#line 1980 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3147 "dhcp4_parser.cc"
    break;

  case 563: // $@91: %empty
#line 1986 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3156 "dhcp4_parser.cc"
    break;

  case 564: // ip_address: "ip-address" $@91 ":" "constant string"
#line 1989 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3166 "dhcp4_parser.cc"
    break;

  case 565: // $@92: %empty
#line 1995 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 566: // ip_addresses: "ip-addresses" $@92 ":" list_strings
#line 2001 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 567: // $@93: %empty
#line 2006 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3196 "dhcp4_parser.cc"
    break;

  case 568: // duid: "duid" $@93 ":" "constant string"
#line 2009 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 569: // $@94: %empty
#line 2015 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3215 "dhcp4_parser.cc"
    break;

  case 570: // hw_address: "hw-address" $@94 ":" "constant string"
#line 2018 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 571: // $@95: %empty
#line 2024 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3234 "dhcp4_parser.cc"
    break;

  case 572: // client_id_value: "client-id" $@95 ":" "constant string"
#line 2027 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 573: // $@96: %empty
#line 2033 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 574: // circuit_id_value: "circuit-id" $@96 ":" "constant string"
#line 2036 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 575: // $@97: %empty
#line 2042 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3272 "dhcp4_parser.cc"
    break;

  case 576: // flex_id_value: "flex-id" $@97 ":" "constant string"
#line 2045 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3282 "dhcp4_parser.cc"
    break;

  case 577: // $@98: %empty
#line 2051 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3291 "dhcp4_parser.cc"
    break;

  case 578: // hostname: "hostname" $@98 ":" "constant string"
#line 2054 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3301 "dhcp4_parser.cc"
    break;

  case 579: // $@99: %empty
#line 2060 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3313 "dhcp4_parser.cc"
    break;

  case 580: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2066 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 581: // $@100: %empty
#line 2074 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3334 "dhcp4_parser.cc"
    break;

  case 582: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2080 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3343 "dhcp4_parser.cc"
    break;

  case 585: // $@101: %empty
#line 2092 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3355 "dhcp4_parser.cc"
    break;

  case 586: // client_classes: "client-classes" $@101 ":" "[" client_classes_list "]"
#line 2098 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3364 "dhcp4_parser.cc"
    break;

  case 589: // $@102: %empty
#line 2107 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3374 "dhcp4_parser.cc"
    break;

  case 590: // client_class_entry: "{" $@102 client_class_params "}"
#line 2111 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3384 "dhcp4_parser.cc"
    break;

  case 607: // $@103: %empty
#line 2140 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp4_parser.cc"
    break;

  case 608: // client_class_test: "test" $@103 ":" "constant string"
#line 2143 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 609: // only_if_required: "only-if-required" ":" "boolean"
#line 2149 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3413 "dhcp4_parser.cc"
    break;

  case 610: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2157 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3423 "dhcp4_parser.cc"
    break;

  case 611: // $@104: %empty
#line 2165 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3435 "dhcp4_parser.cc"
    break;

  case 612: // control_socket: "control-socket" $@104 ":" "{" control_socket_params "}"
#line 2171 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3444 "dhcp4_parser.cc"
    break;

  case 620: // $@105: %empty
#line 2187 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 621: // control_socket_type: "socket-type" $@105 ":" "constant string"
#line 2190 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 622: // $@106: %empty
#line 2196 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 623: // control_socket_name: "socket-name" $@106 ":" "constant string"
#line 2199 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3482 "dhcp4_parser.cc"
    break;

  case 624: // $@107: %empty
#line 2208 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3494 "dhcp4_parser.cc"
    break;

  case 625: // dhcp_queue_control: "dhcp-queue-control" $@107 ":" "{" queue_control_params "}"
#line 2214 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3505 "dhcp4_parser.cc"
    break;

  case 634: // enable_queue: "enable-queue" ":" "boolean"
#line 2233 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 635: // $@108: %empty
#line 2239 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3524 "dhcp4_parser.cc"
    break;

  case 636: // queue_type: "queue-type" $@108 ":" "constant string"
#line 2242 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 637: // capacity: "capacity" ":" "integer"
#line 2248 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 638: // $@109: %empty
#line 2254 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3553 "dhcp4_parser.cc"
    break;

  case 639: // arbitrary_map_entry: "constant string" $@109 ":" value
#line 2257 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3562 "dhcp4_parser.cc"
    break;

  case 640: // $@110: %empty
#line 2264 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 641: // dhcp_ddns: "dhcp-ddns" $@110 ":" "{" dhcp_ddns_params "}"
#line 2270 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3585 "dhcp4_parser.cc"
    break;

  case 642: // $@111: %empty
#line 2277 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3595 "dhcp4_parser.cc"
    break;

  case 643: // sub_dhcp_ddns: "{" $@111 dhcp_ddns_params "}"
#line 2281 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3605 "dhcp4_parser.cc"
    break;

  case 664: // enable_updates: "enable-updates" ":" "boolean"
#line 2311 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3615 "dhcp4_parser.cc"
    break;

  case 665: // $@112: %empty
#line 2317 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3624 "dhcp4_parser.cc"
    break;

  case 666: // server_ip: "server-ip" $@112 ":" "constant string"
#line 2320 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3634 "dhcp4_parser.cc"
    break;

  case 667: // server_port: "server-port" ":" "integer"
#line 2326 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3644 "dhcp4_parser.cc"
    break;

  case 668: // $@113: %empty
#line 2332 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 669: // sender_ip: "sender-ip" $@113 ":" "constant string"
#line 2335 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3663 "dhcp4_parser.cc"
    break;

  case 670: // sender_port: "sender-port" ":" "integer"
#line 2341 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3673 "dhcp4_parser.cc"
    break;

  case 671: // max_queue_size: "max-queue-size" ":" "integer"
#line 2347 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 672: // $@114: %empty
#line 2353 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3692 "dhcp4_parser.cc"
    break;

  case 673: // ncr_protocol: "ncr-protocol" $@114 ":" ncr_protocol_value
#line 2356 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3701 "dhcp4_parser.cc"
    break;

  case 674: // ncr_protocol_value: "udp"
#line 2362 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3707 "dhcp4_parser.cc"
    break;

  case 675: // ncr_protocol_value: "tcp"
#line 2363 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3713 "dhcp4_parser.cc"
    break;

  case 676: // $@115: %empty
#line 2366 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 677: // ncr_format: "ncr-format" $@115 ":" "JSON"
#line 2369 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 678: // $@116: %empty
#line 2376 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 679: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2379 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 680: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2386 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 681: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2393 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3771 "dhcp4_parser.cc"
    break;

  case 682: // $@117: %empty
#line 2400 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 683: // dep_replace_client_name: "replace-client-name" $@117 ":" ddns_replace_client_name_value
#line 2403 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3789 "dhcp4_parser.cc"
    break;

  case 684: // $@118: %empty
#line 2409 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3798 "dhcp4_parser.cc"
    break;

  case 685: // dep_generated_prefix: "generated-prefix" $@118 ":" "constant string"
#line 2412 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 686: // $@119: %empty
#line 2419 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3817 "dhcp4_parser.cc"
    break;

  case 687: // dep_hostname_char_set: "hostname-char-set" $@119 ":" "constant string"
#line 2422 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3827 "dhcp4_parser.cc"
    break;

  case 688: // $@120: %empty
#line 2429 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3836 "dhcp4_parser.cc"
    break;

  case 689: // dep_hostname_char_replacement: "hostname-char-replacement" $@120 ":" "constant string"
#line 2432 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3846 "dhcp4_parser.cc"
    break;

  case 690: // $@121: %empty
#line 2441 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 691: // config_control: "config-control" $@121 ":" "{" config_control_params "}"
#line 2447 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 692: // $@122: %empty
#line 2453 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3878 "dhcp4_parser.cc"
    break;

  case 693: // sub_config_control: "{" $@122 config_control_params "}"
#line 2457 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3887 "dhcp4_parser.cc"
    break;

  case 698: // $@123: %empty
#line 2472 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3899 "dhcp4_parser.cc"
    break;

  case 699: // config_databases: "config-databases" $@123 ":" "[" database_list "]"
#line 2478 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3908 "dhcp4_parser.cc"
    break;

  case 700: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2483 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 701: // $@124: %empty
#line 2491 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3930 "dhcp4_parser.cc"
    break;

  case 702: // loggers: "loggers" $@124 ":" "[" loggers_entries "]"
#line 2497 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3939 "dhcp4_parser.cc"
    break;

  case 705: // $@125: %empty
#line 2509 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3949 "dhcp4_parser.cc"
    break;

  case 706: // logger_entry: "{" $@125 logger_params "}"
#line 2513 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3957 "dhcp4_parser.cc"
    break;

  case 716: // debuglevel: "debuglevel" ":" "integer"
#line 2530 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 717: // $@126: %empty
#line 2536 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3976 "dhcp4_parser.cc"
    break;

  case 718: // severity: "severity" $@126 ":" "constant string"
#line 2539 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3986 "dhcp4_parser.cc"
    break;

  case 719: // $@127: %empty
#line 2545 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3998 "dhcp4_parser.cc"
    break;

  case 720: // output_options_list: "output_options" $@127 ":" "[" output_options_list_content "]"
#line 2551 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4007 "dhcp4_parser.cc"
    break;

  case 723: // $@128: %empty
#line 2560 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4017 "dhcp4_parser.cc"
    break;

  case 724: // output_entry: "{" $@128 output_params_list "}"
#line 2564 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4025 "dhcp4_parser.cc"
    break;

  case 732: // $@129: %empty
#line 2579 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4034 "dhcp4_parser.cc"
    break;

  case 733: // output: "output" $@129 ":" "constant string"
#line 2582 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4044 "dhcp4_parser.cc"
    break;

  case 734: // flush: "flush" ":" "boolean"
#line 2588 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4054 "dhcp4_parser.cc"
    break;

  case 735: // maxsize: "maxsize" ":" "integer"
#line 2594 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4064 "dhcp4_parser.cc"
    break;

  case 736: // maxver: "maxver" ":" "integer"
#line 2600 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4074 "dhcp4_parser.cc"
    break;

  case 737: // $@130: %empty
#line 2606 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4083 "dhcp4_parser.cc"
    break;

  case 738: // pattern: "pattern" $@130 ":" "constant string"
#line 2609 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4093 "dhcp4_parser.cc"
    break;


#line 4097 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -901;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     548,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,    31,    41,    59,    72,    74,   151,
     161,   162,   188,   194,   207,   227,   234,   243,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,    41,  -151,   206,   114,    67,   233,
     192,   242,   -31,    69,   280,   -84,   557,    95,  -901,   246,
     253,   270,   241,   281,  -901,   275,  -901,  -901,  -901,   297,
     307,   324,  -901,  -901,  -901,  -901,  -901,  -901,   331,   336,
     338,   339,   342,   343,   344,   346,   349,   350,   357,  -901,
     359,   370,   371,   374,   375,  -901,  -901,  -901,   382,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,   384,  -901,  -901,  -901,  -901,  -901,  -901,  -901,   385,
    -901,    53,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,   388,
    -901,    84,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,   389,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,    94,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,    97,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,   277,   348,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,   386,  -901,  -901,
     391,  -901,  -901,  -901,   392,  -901,  -901,   393,   397,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,   401,   402,  -901,  -901,  -901,  -901,   399,   405,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,   118,  -901,  -901,  -901,   406,  -901,  -901,   408,
    -901,   410,   412,  -901,  -901,   413,   415,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,   121,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,   416,   124,  -901,  -901,  -901,  -901,    41,    41,
    -901,  -141,   418,  -901,   420,   429,   436,   218,   255,   256,
     445,   447,   448,   450,   452,   453,   261,   271,   272,   273,
     282,   279,   288,   291,   293,   283,   300,   459,   301,   304,
     295,   303,   306,   495,   496,   497,   311,   501,   503,   504,
     508,   511,   514,   515,   516,   518,   519,   520,   522,   351,
     523,   527,   533,   534,   535,   537,   540,  -901,   114,  -901,
     541,   542,   543,   358,    67,  -901,   544,   546,   547,   549,
     550,   553,   363,   554,   555,   556,   233,  -901,   558,   192,
    -901,   569,   571,   581,   582,   583,   587,   589,   590,  -901,
     242,  -901,   591,   592,   372,   593,   594,   595,   409,  -901,
      69,   597,   417,   421,  -901,   280,   600,   602,    80,  -901,
     424,   605,   612,   430,   614,   431,   432,   618,   619,   433,
     440,   629,   651,   652,   653,   557,  -901,   654,   470,    95,
    -901,  -901,  -901,   656,   655,   657,   658,   665,  -901,  -901,
    -901,   473,   475,   485,   667,   668,   671,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,   489,  -901,
    -901,  -901,  -901,  -901,    82,   490,   491,  -901,   676,   677,
     678,   679,   680,   498,   268,   683,   684,   685,   686,   688,
    -901,   689,   690,   691,   692,   505,   512,   687,  -901,   696,
     113,   204,  -901,  -901,   528,   529,   530,   710,   531,   532,
    -901,   696,   551,   729,  -901,   552,  -901,   696,   559,   560,
     561,   562,   563,   564,   565,  -901,   566,   567,  -901,   568,
     570,   572,  -901,  -901,   573,  -901,  -901,  -901,   574,   680,
    -901,  -901,   575,   576,  -901,   577,  -901,  -901,    12,   526,
    -901,  -901,    82,   578,   579,   580,  -901,   732,  -901,  -901,
      41,   114,    95,    67,   714,  -901,  -901,  -901,   596,   596,
     734,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
     735,   736,   737,   739,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,   -41,   750,   752,   762,   138,    14,   -54,   294,
     557,  -901,  -901,   763,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,   764,  -901,  -901,  -901,  -901,
     117,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,   734,
    -901,   130,   149,   159,  -901,   190,  -901,  -901,  -901,  -901,
    -901,  -901,   768,   769,   770,   771,   772,  -901,  -901,  -901,
    -901,   773,   774,   775,   776,   777,   778,  -901,   191,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
     197,  -901,   779,   780,  -901,  -901,   781,   783,  -901,  -901,
     782,   786,  -901,  -901,   784,   788,  -901,  -901,   787,   789,
    -901,  -901,  -901,  -901,  -901,  -901,    61,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,    90,  -901,  -901,   790,   791,  -901,
    -901,   792,   794,  -901,   795,   796,   797,   798,   799,   800,
     209,  -901,  -901,  -901,  -901,  -901,  -901,  -901,   801,   802,
     803,  -901,   210,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,   225,  -901,  -901,  -901,   804,  -901,
     805,  -901,  -901,  -901,   232,  -901,  -901,  -901,  -901,  -901,
     245,  -901,   112,  -901,   607,  -901,   806,   807,  -901,  -901,
    -901,  -901,   808,   809,  -901,  -901,  -901,   810,   714,  -901,
     813,   814,   815,   816,   622,   630,   624,   631,   634,   820,
     821,   822,   823,   639,   640,   641,   642,   643,   644,   596,
    -901,  -901,   596,  -901,   734,   233,  -901,   735,    69,  -901,
     736,   280,  -901,   737,   506,  -901,   739,   -41,  -901,   446,
     750,  -901,   242,  -901,   752,   -84,  -901,   762,   646,   647,
     648,   649,   650,   660,   138,  -901,   659,   663,   664,    14,
    -901,   828,   836,   -54,  -901,   672,   837,   682,   838,   294,
    -901,  -901,    39,   763,  -901,  -901,   839,   840,   192,  -901,
     764,   842,  -901,  -901,   700,  -901,   347,   704,   705,   717,
    -901,  -901,  -901,  -901,  -901,   718,   721,   724,   731,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,   274,  -901,   278,  -901,
     848,  -901,   864,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,   312,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,   843,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,   868,   841,  -901,  -901,  -901,  -901,
    -901,   912,  -901,   314,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,   740,   742,  -901,  -901,
     785,  -901,    41,  -901,  -901,   923,  -901,  -901,  -901,  -901,
    -901,   315,  -901,  -901,  -901,  -901,  -901,  -901,   793,   316,
    -901,   696,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,   506,
    -901,   966,   811,  -901,   446,  -901,  -901,  -901,  -901,  -901,
    -901,   973,   812,   974,    39,  -901,  -901,  -901,  -901,  -901,
     817,  -901,  -901,   975,  -901,   818,  -901,  -901,   972,  -901,
    -901,   148,  -901,  -119,   972,  -901,  -901,   978,   979,   980,
    -901,   318,  -901,  -901,  -901,  -901,  -901,  -901,  -901,   981,
     819,   824,   825,   982,  -119,  -901,   827,  -901,  -901,  -901,
     829,  -901,  -901,  -901
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   166,     9,   324,    11,   511,    13,
     536,    15,   436,    17,   444,    19,   481,    21,   289,    23,
     642,    25,   692,    27,    45,    39,     0,     0,     0,     0,
       0,   538,     0,   446,   483,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   690,   155,   181,     0,
       0,     0,   557,   559,   561,   179,   188,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
       0,     0,     0,     0,     0,   137,   144,   146,     0,   316,
     434,   473,   389,   524,   526,   382,   254,   585,   528,   281,
     300,     0,   268,   611,   624,   640,   148,   150,   701,     0,
     117,     0,    62,    64,    65,    66,    67,    68,    99,   100,
     101,   102,   103,    69,    97,    86,    87,    88,   107,   108,
     109,   110,   111,   112,   105,   106,   113,   114,   115,    72,
      73,    94,    74,    75,    76,   116,    80,    81,    70,    98,
      71,    78,    79,    92,    93,    95,    89,    90,    91,    77,
      82,    83,    84,    85,    96,   104,   168,   170,   174,     0,
     165,     0,   157,   159,   160,   161,   162,   163,   164,   370,
     372,   374,   503,   368,   376,     0,   380,   378,   581,   367,
     328,   329,   330,   331,   332,   353,   354,   355,   356,   357,
     343,   344,   358,   359,   360,   361,   362,   363,   364,   365,
     366,     0,   326,   335,   348,   349,   350,   336,   338,   339,
     341,   337,   333,   334,   351,   352,   340,   345,   346,   347,
     342,   522,   521,   517,   518,   516,     0,   513,   515,   519,
     520,   579,   567,   569,   573,   571,   577,   575,   563,   556,
     550,   554,   555,     0,   539,   540,   551,   552,   553,   547,
     542,   548,   544,   545,   546,   549,   543,     0,   463,   234,
       0,   467,   465,   470,     0,   459,   460,     0,   447,   448,
     450,   462,   451,   452,   453,   469,   454,   455,   456,   457,
     458,   497,     0,     0,   495,   496,   499,   500,     0,   484,
     485,   487,   488,   489,   490,   491,   492,   493,   494,   296,
     298,   293,     0,   291,   294,   295,     0,   678,   665,     0,
     668,     0,     0,   672,   676,     0,     0,   682,   684,   686,
     688,   663,   661,   662,     0,   644,   646,   647,   648,   649,
     650,   651,   652,   653,   658,   654,   655,   656,   657,   659,
     660,   698,     0,     0,   694,   696,   697,    44,     0,     0,
      37,     0,     0,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    55,     0,    61,
       0,     0,     0,     0,     0,   167,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   325,     0,     0,
     512,     0,     0,     0,     0,     0,     0,     0,     0,   537,
       0,   437,     0,     0,     0,     0,     0,     0,     0,   445,
       0,     0,     0,     0,   482,     0,     0,     0,     0,   290,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   643,     0,     0,     0,
     693,    48,    41,     0,     0,     0,     0,     0,   131,   132,
     133,     0,     0,     0,     0,     0,     0,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,     0,   153,
     154,   134,   135,   136,     0,     0,     0,   152,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     610,     0,     0,     0,     0,     0,     0,     0,    63,     0,
       0,     0,   178,   158,     0,     0,     0,     0,     0,     0,
     388,     0,     0,     0,   327,     0,   514,     0,     0,     0,
       0,     0,     0,     0,     0,   541,     0,     0,   461,     0,
       0,     0,   472,   449,     0,   501,   502,   486,     0,     0,
     292,   664,     0,     0,   667,     0,   670,   671,     0,     0,
     680,   681,     0,     0,     0,     0,   645,     0,   700,   695,
       0,     0,     0,     0,     0,   558,   560,   562,     0,     0,
     192,   130,   139,   140,   141,   142,   143,   138,   145,   147,
     318,   438,   475,   391,    38,   525,   527,   384,   385,   386,
     387,   383,     0,     0,   530,   283,     0,     0,     0,     0,
       0,   149,   151,     0,    49,   169,   172,   173,   171,   176,
     177,   175,   371,   373,   375,   505,   369,   377,   381,   379,
       0,   523,   580,   568,   570,   574,   572,   578,   576,   564,
     464,   235,   468,   466,   471,   498,   297,   299,   679,   666,
     669,   674,   675,   673,   677,   683,   685,   687,   689,   192,
      42,     0,     0,     0,   186,     0,   183,   185,   221,   227,
     229,   231,     0,     0,     0,     0,     0,   243,   245,   247,
     249,     0,     0,     0,     0,     0,     0,   220,     0,   198,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     213,   214,   215,   210,   216,   217,   218,   211,   212,   219,
       0,   196,     0,   193,   194,   322,     0,   319,   320,   442,
       0,   439,   440,   479,     0,   476,   477,   395,     0,   392,
     393,   263,   264,   265,   266,   267,     0,   256,   258,   259,
     260,   261,   262,   589,     0,   587,   534,     0,   531,   532,
     287,     0,   284,   285,     0,     0,     0,     0,     0,     0,
       0,   302,   304,   305,   306,   307,   308,   309,     0,     0,
       0,   277,     0,   270,   272,   273,   274,   275,   276,   620,
     622,   619,   617,   618,     0,   613,   615,   616,     0,   635,
       0,   638,   631,   632,     0,   626,   628,   629,   630,   633,
       0,   705,     0,   703,    51,   509,     0,   506,   507,   565,
     583,   584,     0,     0,    59,   691,   156,     0,     0,   182,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   189,     0,   191,     0,     0,   317,     0,   446,   435,
       0,   483,   474,     0,     0,   390,     0,     0,   255,   591,
       0,   586,   538,   529,     0,     0,   282,     0,     0,     0,
       0,     0,     0,     0,     0,   301,     0,     0,     0,     0,
     269,     0,     0,     0,   612,     0,     0,     0,     0,     0,
     625,   641,     0,     0,   702,    53,     0,    52,     0,   504,
       0,     0,   582,   699,     0,   184,     0,     0,     0,     0,
     233,   236,   237,   238,   239,     0,     0,     0,     0,   251,
     252,   240,   241,   242,   253,   199,     0,   195,     0,   321,
       0,   441,     0,   478,   433,   414,   415,   416,   402,   403,
     419,   420,   421,   422,   423,   405,   406,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   399,   400,   401,   412,
     413,   411,     0,   397,   404,   417,   418,   407,   408,   409,
     410,   394,   257,   607,     0,   605,   606,   598,   599,   603,
     604,   600,   601,   602,     0,   592,   593,   595,   596,   597,
     588,     0,   533,     0,   286,   310,   311,   312,   313,   314,
     315,   303,   278,   279,   280,   271,     0,     0,   614,   634,
       0,   637,     0,   627,   719,     0,   717,   715,   709,   713,
     714,     0,   707,   711,   712,   710,   704,    50,     0,     0,
     508,     0,   187,   223,   224,   225,   226,   222,   228,   230,
     232,   244,   246,   248,   250,   197,   323,   443,   480,     0,
     396,     0,     0,   590,     0,   535,   288,   621,   623,   636,
     639,     0,     0,     0,     0,   706,    54,   510,   566,   398,
       0,   609,   594,     0,   716,     0,   708,   608,     0,   718,
     723,     0,   721,     0,     0,   720,   732,     0,     0,     0,
     737,     0,   725,   727,   728,   729,   730,   731,   722,     0,
       0,     0,     0,     0,     0,   724,     0,   734,   735,   736,
       0,   726,   733,   738
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,   -52,  -901,  -529,  -901,   368,
    -901,  -901,  -901,  -901,  -901,  -901,  -576,  -901,  -901,  -901,
     -67,  -901,  -901,  -901,  -901,  -901,  -901,   352,   584,   -40,
     -28,   -24,    -1,     1,    11,    19,    22,    25,    26,  -901,
    -901,  -901,  -901,    29,    30,    32,    37,    40,    43,  -901,
     356,    44,  -901,    45,  -901,    47,  -901,    48,  -901,    50,
    -901,  -901,  -901,  -901,   353,   536,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,   101,  -901,  -901,  -901,  -901,  -901,  -901,   262,
    -901,    78,  -901,  -636,    85,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,   -63,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,    68,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,    49,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,    60,  -901,  -901,  -901,    64,
     502,  -901,  -901,  -901,  -901,  -901,  -901,  -901,    63,  -901,
    -901,  -901,  -901,  -901,  -901,  -900,  -901,  -901,  -901,    86,
    -901,  -901,  -901,    89,   545,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -897,  -901,   -65,  -901,    52,  -901,    51,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,    83,  -901,  -901,
    -111,   -46,  -901,  -901,  -901,  -901,  -901,    92,  -901,  -901,
    -901,    98,  -901,   538,  -901,   -42,  -901,  -901,  -901,  -901,
    -901,   -36,  -901,  -901,  -901,  -901,  -901,   -35,  -901,  -901,
    -901,    96,  -901,  -901,  -901,   100,  -901,   539,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,    54,
    -901,  -901,  -901,    55,   586,  -901,  -901,   -51,  -901,   -11,
    -901,   -25,  -901,  -901,  -901,    88,  -901,  -901,  -901,    93,
    -901,   585,   -55,  -901,     0,  -901,     7,  -901,   326,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -896,  -901,  -901,  -901,
    -901,  -901,    99,  -901,  -901,  -901,  -106,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,    87,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,    76,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,   361,   521,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,   395,   524,  -901,  -901,  -901,
    -901,  -901,  -901,    70,  -901,  -901,  -107,  -901,  -901,  -901,
    -901,  -901,  -901,  -123,  -901,  -901,  -136,  -901,  -901,  -901,
    -901,  -901,  -901,  -901
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   665,
      82,    83,    39,    64,    79,    80,   685,   874,   966,   967,
     757,    41,    66,    85,   392,    43,    67,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   417,   155,   156,   157,   158,   159,   160,   161,   423,
     657,   162,   424,   163,   425,   164,   444,   165,   445,   166,
     167,   168,   169,   395,   201,   202,    45,    68,   203,   450,
     204,   451,   688,   205,   452,   691,   206,   170,   403,   171,
     396,   735,   736,   737,   887,   172,   404,   173,   405,   782,
     783,   784,   912,   758,   759,   760,   890,  1107,   761,   891,
     762,   892,   763,   893,   764,   765,   483,   766,   767,   768,
     769,   770,   771,   772,   773,   899,   774,   900,   775,   901,
     776,   902,   777,   778,   779,   174,   434,   806,   807,   808,
     809,   810,   811,   812,   175,   440,   842,   843,   844,   845,
     846,   176,   437,   821,   822,   823,   935,    59,    75,   342,
     343,   344,   496,   345,   497,   177,   438,   830,   831,   832,
     833,   834,   835,   836,   837,   178,   427,   786,   787,   788,
     915,    47,    69,   241,   242,   243,   460,   244,   456,   245,
     457,   246,   458,   247,   461,   248,   464,   249,   463,   179,
     433,   671,   251,   180,   430,   798,   799,   800,   924,  1032,
    1033,   181,   428,    53,    72,   790,   791,   792,   918,    55,
      73,   307,   308,   309,   310,   311,   312,   313,   482,   314,
     486,   315,   485,   316,   317,   487,   318,   182,   429,   794,
     795,   796,   921,    57,    74,   328,   329,   330,   331,   332,
     491,   333,   334,   335,   336,   253,   459,   876,   877,   878,
     968,    49,    70,   266,   267,   268,   468,   183,   431,   184,
     432,   185,   436,   817,   818,   819,   932,    51,    71,   283,
     284,   285,   186,   400,   187,   401,   188,   402,   289,   478,
     881,   971,   290,   472,   291,   473,   292,   475,   293,   474,
     294,   477,   295,   476,   296,   471,   260,   465,   882,   189,
     435,   814,   815,   929,  1054,  1055,  1056,  1057,  1058,  1121,
    1059,   190,   191,   441,   854,   855,   856,   951,   857,   952,
     192,   442,   864,   865,   866,   867,   956,   868,   869,   958,
     193,   443,    61,    76,   364,   365,   366,   367,   502,   368,
     369,   504,   370,   371,   372,   507,   723,   373,   508,   374,
     501,   375,   376,   377,   511,   378,   512,   379,   513,   380,
     514,   194,   394,    63,    77,   383,   384,   385,   517,   386,
     195,   446,   872,   873,   962,  1091,  1092,  1093,  1094,  1133,
    1095,  1131,  1151,  1152,  1153,  1161,  1162,  1163,  1169,  1164,
    1165,  1166,  1167,  1173
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     140,   200,   219,   262,   279,   263,   305,   324,   341,   361,
     306,   325,    78,   780,   257,   698,   286,   207,   254,   269,
     281,   702,   319,   337,  1027,   362,   297,  1028,  1040,   220,
     721,    28,   326,   664,   252,   265,   280,    81,   327,   339,
     340,   221,   123,   124,   256,   222,    29,   523,    30,  1156,
      31,   120,  1157,  1158,  1159,  1160,   448,   208,   255,   270,
     282,   449,   320,   338,   927,   363,    40,   928,   223,   258,
     224,   287,   801,   802,   803,   804,   259,   805,   288,    42,
     225,    44,   196,   197,   849,   850,   198,   454,   226,   199,
     664,   227,   455,   930,   228,   229,   931,   466,   230,   231,
     469,   232,   467,   298,   139,   470,   233,   381,   382,   234,
     123,   124,   235,   236,   237,   963,   238,   239,   964,   240,
     250,   498,   264,   299,   515,    86,   499,   519,    87,   516,
     686,   687,   520,   448,   139,   123,   124,    88,   884,    89,
      90,    91,    92,    93,    94,    95,    96,    97,   838,   839,
     840,  1154,   519,   299,  1155,   300,   301,   885,    46,   302,
     303,   304,   454,   123,   124,   123,   124,   886,    48,    50,
     722,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   888,   909,    52,   120,   121,   889,   910,
     909,    54,   139,   339,   340,   911,  1084,   122,  1085,  1086,
     123,   124,   944,   949,    56,   125,    84,   945,   950,  1027,
     126,   127,  1028,  1040,   689,   690,   128,   139,   953,    32,
      33,    34,    35,   954,    58,   959,   129,   278,   879,   130,
     960,    60,   652,   653,   654,   655,   131,   132,   515,   390,
      62,   133,   387,   961,   134,   139,   388,   139,   135,    90,
      91,    92,    93,    94,   824,   825,   826,   827,   828,   829,
      92,    93,    94,   656,   389,   121,   996,   909,   136,   137,
     138,   466,  1115,   393,   391,   479,  1116,   261,   123,   124,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     216,   397,   139,   217,   112,   113,   114,   115,   116,   117,
     118,   398,   209,   210,   211,  1119,   121,   498,  1134,   469,
    1120,  1174,  1126,  1135,  1137,   121,  1175,   212,   399,   123,
     124,   213,   214,   215,   125,   406,   521,   522,   123,   124,
     407,   216,   408,   409,   217,   128,   410,   411,   412,   271,
     413,   480,   218,   414,   415,   272,   273,   274,   275,   276,
     277,   416,   278,   418,   299,   321,   300,   301,   322,   323,
     667,   668,   669,   670,   419,   420,   123,   124,   421,   422,
     139,   140,  1103,  1104,  1105,  1106,   426,   200,   439,   447,
     123,   124,   453,   462,   481,   484,   488,   136,   137,   219,
     490,   489,   262,   207,   263,   492,   493,   494,   495,   528,
     500,   257,   503,   279,   505,   254,   506,   509,   269,   510,
     518,   139,   524,   305,   525,   286,   220,   306,   324,   281,
     139,   252,   325,   526,   265,   858,   859,   860,   221,   319,
     527,   256,   222,   208,   337,   280,   529,   530,   361,   531,
     537,   532,   533,   326,   534,   255,   535,   536,   270,   327,
     538,   539,   540,   548,   362,   223,   258,   224,   139,   282,
     542,   541,   546,   259,    92,    93,    94,   225,   543,   320,
     287,   544,   861,   545,   338,   226,   551,   288,   227,   547,
     549,   228,   229,   550,   552,   230,   231,   553,   232,   554,
     555,   556,   557,   233,   363,   558,   234,   559,   560,   235,
     236,   237,   561,   238,   239,   562,   240,   250,   563,   564,
     565,   264,   566,   567,   568,  1138,   569,   571,   120,   121,
     299,   572,    90,    91,    92,    93,    94,   573,   574,   575,
     570,   576,   123,   124,   577,   579,   580,   581,   584,   582,
     585,   586,   590,   587,   588,  1043,  1044,   589,   591,   592,
     593,   608,   595,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   597,   140,   598,   200,   112,   113,   114,
     115,   116,   117,   118,   119,   599,   600,   601,   730,   121,
     299,   602,   207,   603,   604,   606,   607,   609,   610,   611,
     612,   614,   123,   124,   618,   214,   619,   125,   615,   622,
     841,   851,   616,   361,   216,   621,   623,   217,   625,   624,
     626,   627,   628,   629,   630,   218,   847,   852,   862,   362,
     738,   631,   208,   632,   139,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   750,   751,   752,   753,
     754,   755,   756,   123,   124,   633,   634,   635,   637,   638,
     640,   645,   641,   646,   642,   643,   848,   853,   863,   363,
     136,   137,   644,   647,   648,   649,   650,   651,   658,   659,
     299,   660,   661,   662,   663,   724,   666,    30,   672,   673,
     674,   675,   683,   681,   139,   676,   677,   678,   679,   680,
     682,   684,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   695,   692,   693,   694,   696,
     697,   359,   360,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   700,   729,   734,   699,
     701,   781,   785,   789,   793,   139,   797,   703,   704,   705,
     706,   707,   708,   709,   710,   711,   712,   813,   713,   816,
     714,   715,   716,   718,   719,   720,   726,   727,   728,   820,
     871,   875,   894,   895,   896,   897,   898,   903,   904,   905,
     906,   907,   908,   914,   139,   913,   917,   916,   919,   920,
     922,   923,   926,   925,   934,   965,   933,   937,   936,   938,
     939,   940,   941,   942,   943,   946,   947,   948,   955,   957,
     970,   980,   969,   982,   974,   973,   972,   976,   977,   978,
     979,   981,   983,   984,   985,   986,   987,   988,   989,   990,
     991,   992,  1076,   994,   993,  1065,  1066,  1067,  1068,  1069,
    1077,  1080,  1082,  1098,  1124,  1097,  1101,  1122,   219,  1070,
    1072,   305,  1073,  1074,   324,   306,  1117,  1004,   325,  1029,
     257,  1026,  1045,  1079,   254,   279,  1046,   319,   341,  1037,
     337,  1081,  1118,  1035,  1051,   220,  1123,   286,  1049,   326,
     252,   281,   841,  1047,  1005,   327,   851,   221,  1102,  1034,
     256,   222,  1108,  1109,  1048,  1087,  1006,   280,   847,  1088,
    1007,   262,   852,   263,   255,  1110,  1111,   320,   862,  1112,
     338,  1089,  1113,  1036,   223,   258,   224,   269,  1050,  1114,
    1125,   282,   259,  1008,  1038,  1009,   225,  1132,  1127,  1052,
    1128,  1039,   287,   265,   226,  1010,  1053,   227,   848,   288,
     228,   229,   853,  1011,   230,   231,  1012,   232,   863,  1013,
    1014,  1090,   233,  1015,  1016,   234,  1017,   270,   235,   236,
     237,  1018,   238,   239,  1019,   240,   250,  1020,  1021,  1022,
    1140,  1023,  1024,  1129,  1025,  1031,  1030,  1143,  1145,  1150,
    1148,  1136,  1170,  1171,  1172,  1176,  1180,   717,   725,   975,
     583,   883,   997,   731,   995,  1042,   733,  1064,  1075,  1063,
     620,  1144,  1141,   999,   998,  1147,  1149,  1071,  1139,  1041,
    1177,   594,  1001,  1178,  1179,  1182,  1000,  1183,  1142,  1003,
     264,  1002,  1062,  1099,  1100,  1061,   880,  1146,   613,  1060,
    1130,  1168,   578,  1096,   617,  1083,   636,   732,  1181,     0,
    1078,   870,     0,   639,     0,     0,     0,     0,     0,     0,
       0,     0,  1004,     0,  1029,   596,  1026,  1045,     0,     0,
       0,  1046,     0,     0,  1037,   605,     0,  1087,  1035,  1051,
       0,  1088,     0,  1049,     0,     0,     0,     0,  1047,  1005,
       0,     0,     0,  1089,  1034,     0,     0,     0,     0,  1048,
       0,  1006,     0,     0,     0,  1007,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1036,     0,
       0,     0,     0,  1050,     0,     0,     0,     0,  1008,  1038,
    1009,     0,     0,  1090,  1052,     0,  1039,     0,     0,     0,
    1010,  1053,     0,     0,     0,     0,     0,     0,  1011,     0,
       0,  1012,     0,     0,  1013,  1014,     0,     0,  1015,  1016,
       0,  1017,     0,     0,     0,     0,  1018,     0,     0,  1019,
       0,     0,  1020,  1021,  1022,     0,  1023,  1024,     0,  1025,
    1031,  1030
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   649,    69,   591,    71,    68,    69,    70,
      71,   597,    73,    74,   924,    76,    72,   924,   924,    69,
      18,     0,    74,   562,    69,    70,    71,   188,    74,   123,
     124,    69,    96,    97,    69,    69,     5,   188,     7,   168,
       9,    82,   171,   172,   173,   174,     3,    68,    69,    70,
      71,     8,    73,    74,     3,    76,     7,     6,    69,    69,
      69,    71,   113,   114,   115,   116,    69,   118,    71,     7,
      69,     7,    15,    16,   138,   139,    19,     3,    69,    22,
     619,    69,     8,     3,    69,    69,     6,     3,    69,    69,
       3,    69,     8,    34,   188,     8,    69,    12,    13,    69,
      96,    97,    69,    69,    69,     3,    69,    69,     6,    69,
      69,     3,    70,    84,     3,    11,     8,     3,    14,     8,
      17,    18,     8,     3,   188,    96,    97,    23,     8,    25,
      26,    27,    28,    29,    30,    31,    32,    33,   134,   135,
     136,     3,     3,    84,     6,    86,    87,     8,     7,    90,
      91,    92,     3,    96,    97,    96,    97,     8,     7,     7,
     158,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     3,     3,     7,    82,    83,     8,     8,
       3,     7,   188,   123,   124,     8,   167,    93,   169,   170,
      96,    97,     3,     3,     7,   101,    10,     8,     8,  1119,
     106,   107,  1119,  1119,    20,    21,   112,   188,     3,   188,
     189,   190,   191,     8,     7,     3,   122,   120,   121,   125,
       8,     7,   160,   161,   162,   163,   132,   133,     3,     8,
       7,   137,     6,     8,   140,   188,     3,   188,   144,    26,
      27,    28,    29,    30,   126,   127,   128,   129,   130,   131,
      28,    29,    30,   191,     4,    83,   912,     3,   164,   165,
     166,     3,     8,     8,     3,     8,     8,    95,    96,    97,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
     108,     4,   188,   111,    71,    72,    73,    74,    75,    76,
      77,     4,    79,    80,    81,     3,    83,     3,     3,     3,
       8,     3,     8,     8,     8,    83,     8,    94,     4,    96,
      97,    98,    99,   100,   101,     4,   388,   389,    96,    97,
       4,   108,     4,     4,   111,   112,     4,     4,     4,   107,
       4,     3,   119,     4,     4,   113,   114,   115,   116,   117,
     118,     4,   120,     4,    84,    85,    86,    87,    88,    89,
     102,   103,   104,   105,     4,     4,    96,    97,     4,     4,
     188,   448,    35,    36,    37,    38,     4,   454,     4,     4,
      96,    97,     4,     4,     8,     4,     4,   164,   165,   466,
       3,     8,   469,   454,   469,     4,     4,     8,     3,   191,
       4,   466,     4,   480,     4,   466,     4,     4,   469,     4,
       4,   188,     4,   490,     4,   480,   466,   490,   495,   480,
     188,   466,   495,     4,   469,   141,   142,   143,   466,   490,
       4,   466,   466,   454,   495,   480,   191,   191,   515,     4,
     189,     4,     4,   495,     4,   466,     4,     4,   469,   495,
     189,   189,   189,     4,   515,   466,   466,   466,   188,   480,
     191,   189,   189,   466,    28,    29,    30,   466,   190,   490,
     480,   190,   188,   190,   495,   466,   191,   480,   466,   189,
     189,   466,   466,   189,   191,   466,   466,   191,   466,     4,
       4,     4,   191,   466,   515,     4,   466,     4,     4,   466,
     466,   466,     4,   466,   466,     4,   466,   466,     4,     4,
       4,   469,     4,     4,     4,  1101,     4,     4,    82,    83,
      84,     4,    26,    27,    28,    29,    30,     4,     4,     4,
     189,     4,    96,    97,     4,     4,     4,     4,     4,   191,
       4,     4,   189,     4,     4,   109,   110,     4,     4,     4,
       4,   189,     4,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     4,   641,     4,   643,    71,    72,    73,
      74,    75,    76,    77,    78,     4,     4,     4,   640,    83,
      84,     4,   643,     4,     4,     4,     4,     4,     4,     4,
     191,     4,    96,    97,     4,    99,     4,   101,   191,     4,
     677,   678,   191,   680,   108,   191,     4,   111,     4,   189,
     189,   189,     4,     4,   191,   119,   677,   678,   679,   680,
      34,   191,   643,     4,   188,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    96,    97,     4,     4,     4,     4,   189,
       4,   188,     7,   188,     7,     7,   677,   678,   679,   680,
     164,   165,     7,   188,     7,     7,     5,   188,   188,   188,
      84,     5,     5,     5,     5,   159,   188,     7,     5,     5,
       5,     5,     5,   188,   188,     7,     7,     7,     7,     7,
     188,     5,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,     5,   188,   188,   188,   188,
     188,   164,   165,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,     7,     5,    24,   188,
     188,     7,     7,     7,     7,   188,     7,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,     7,   188,     7,
     188,   188,   188,   188,   188,   188,   188,   188,   188,     7,
       7,     7,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   188,     6,     3,     6,     6,     3,
       6,     3,     3,     6,     3,   188,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   189,     6,   189,     4,     6,     8,     4,     4,     4,
       4,   191,   191,   189,     4,     4,     4,     4,   189,   189,
     189,   189,     4,   189,   191,   189,   189,   189,   189,   189,
       4,     4,     4,     3,     3,     6,     4,     4,   915,   189,
     191,   918,   189,   189,   921,   918,     8,   924,   921,   924,
     915,   924,   929,   191,   915,   932,   929,   918,   935,   924,
     921,   189,     8,   924,   929,   915,     8,   932,   929,   921,
     915,   932,   949,   929,   924,   921,   953,   915,   188,   924,
     915,   915,   188,   188,   929,   962,   924,   932,   949,   962,
     924,   968,   953,   968,   915,   188,   188,   918,   959,   188,
     921,   962,   188,   924,   915,   915,   915,   968,   929,   188,
       8,   932,   915,   924,   924,   924,   915,     4,   188,   929,
     188,   924,   932,   968,   915,   924,   929,   915,   949,   932,
     915,   915,   953,   924,   915,   915,   924,   915,   959,   924,
     924,   962,   915,   924,   924,   915,   924,   968,   915,   915,
     915,   924,   915,   915,   924,   915,   915,   924,   924,   924,
       4,   924,   924,   188,   924,   924,   924,     4,     4,     7,
       5,   188,     4,     4,     4,     4,     4,   619,   632,   888,
     454,   729,   914,   641,   909,   927,   643,   937,   949,   935,
     498,   189,   191,   917,   915,   188,   188,   944,  1119,   926,
     191,   466,   920,   189,   189,   188,   918,   188,  1124,   923,
     968,   921,   934,   968,   970,   932,   700,  1134,   490,   930,
    1082,  1154,   448,   963,   495,   959,   515,   642,  1174,    -1,
     953,   680,    -1,   519,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1119,    -1,  1119,   469,  1119,  1124,    -1,    -1,
      -1,  1124,    -1,    -1,  1119,   480,    -1,  1134,  1119,  1124,
      -1,  1134,    -1,  1124,    -1,    -1,    -1,    -1,  1124,  1119,
      -1,    -1,    -1,  1134,  1119,    -1,    -1,    -1,    -1,  1124,
      -1,  1119,    -1,    -1,    -1,  1119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1119,    -1,
      -1,    -1,    -1,  1124,    -1,    -1,    -1,    -1,  1119,  1119,
    1119,    -1,    -1,  1134,  1124,    -1,  1119,    -1,    -1,    -1,
    1119,  1124,    -1,    -1,    -1,    -1,    -1,    -1,  1119,    -1,
      -1,  1119,    -1,    -1,  1119,  1119,    -1,    -1,  1119,  1119,
      -1,  1119,    -1,    -1,    -1,    -1,  1119,    -1,    -1,  1119,
      -1,    -1,  1119,  1119,  1119,    -1,  1119,  1119,    -1,  1119,
    1119,  1119
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,     0,     5,
       7,     9,   188,   189,   190,   191,   207,   208,   209,   214,
       7,   223,     7,   227,     7,   268,     7,   373,     7,   453,
       7,   469,     7,   405,     7,   411,     7,   435,     7,   349,
       7,   534,     7,   565,   215,   210,   224,   228,   269,   374,
     454,   470,   406,   412,   436,   350,   535,   566,   207,   216,
     217,   188,   212,   213,    10,   225,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      82,    83,    93,    96,    97,   101,   106,   107,   112,   122,
     125,   132,   133,   137,   140,   144,   164,   165,   166,   188,
     222,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   244,   245,   246,   247,   248,
     249,   250,   253,   255,   257,   259,   261,   262,   263,   264,
     279,   281,   287,   289,   327,   336,   343,   357,   367,   391,
     395,   403,   429,   459,   461,   463,   474,   476,   478,   501,
     513,   514,   522,   532,   563,   572,    15,    16,    19,    22,
     222,   266,   267,   270,   272,   275,   278,   459,   461,    79,
      80,    81,    94,    98,    99,   100,   108,   111,   119,   222,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     245,   246,   247,   248,   249,   250,   253,   255,   257,   259,
     261,   375,   376,   377,   379,   381,   383,   385,   387,   389,
     391,   394,   429,   447,   459,   461,   463,   474,   476,   478,
     498,    95,   222,   387,   389,   429,   455,   456,   457,   459,
     461,   107,   113,   114,   115,   116,   117,   118,   120,   222,
     429,   459,   461,   471,   472,   473,   474,   476,   478,   480,
     484,   486,   488,   490,   492,   494,   496,   403,    34,    84,
      86,    87,    90,    91,    92,   222,   307,   413,   414,   415,
     416,   417,   418,   419,   421,   423,   425,   426,   428,   459,
     461,    85,    88,    89,   222,   307,   417,   423,   437,   438,
     439,   440,   441,   443,   444,   445,   446,   459,   461,   123,
     124,   222,   351,   352,   353,   355,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   164,
     165,   222,   459,   461,   536,   537,   538,   539,   541,   542,
     544,   545,   546,   549,   551,   553,   554,   555,   557,   559,
     561,    12,    13,   567,   568,   569,   571,     6,     3,     4,
       8,     3,   226,     8,   564,   265,   282,     4,     4,     4,
     475,   477,   479,   280,   288,   290,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   243,     4,     4,
       4,     4,     4,   251,   254,   256,     4,   368,   404,   430,
     396,   460,   462,   392,   328,   502,   464,   344,   358,     4,
     337,   515,   523,   533,   258,   260,   573,     4,     3,     8,
     271,   273,   276,     4,     3,     8,   380,   382,   384,   448,
     378,   386,     4,   390,   388,   499,     3,     8,   458,     3,
       8,   497,   485,   487,   491,   489,   495,   493,   481,     8,
       3,     8,   420,   308,     4,   424,   422,   427,     4,     8,
       3,   442,     4,     4,     8,     3,   354,   356,     3,     8,
       4,   552,   540,     4,   543,     4,     4,   547,   550,     4,
       4,   556,   558,   560,   562,     3,     8,   570,     4,     3,
       8,   207,   207,   188,     4,     4,     4,     4,   191,   191,
     191,     4,     4,     4,     4,     4,     4,   189,   189,   189,
     189,   189,   191,   190,   190,   190,   189,   189,     4,   189,
     189,   191,   191,   191,     4,     4,     4,   191,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     189,     4,     4,     4,     4,     4,     4,     4,   230,     4,
       4,     4,   191,   267,     4,     4,     4,     4,     4,     4,
     189,     4,     4,     4,   376,     4,   456,     4,     4,     4,
       4,     4,     4,     4,     4,   473,     4,     4,   189,     4,
       4,     4,   191,   415,     4,   191,   191,   439,     4,     4,
     352,   191,     4,     4,   189,     4,   189,   189,     4,     4,
     191,   191,     4,     4,     4,     4,   537,     4,   189,   568,
       4,     7,     7,     7,     7,   188,   188,   188,     7,     7,
       5,   188,   160,   161,   162,   163,   191,   252,   188,   188,
       5,     5,     5,     5,   209,   211,   188,   102,   103,   104,
     105,   393,     5,     5,     5,     5,     7,     7,     7,     7,
       7,   188,   188,     5,     5,   218,    17,    18,   274,    20,
      21,   277,   188,   188,   188,     5,   188,   188,   218,   188,
       7,   188,   218,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   211,   188,   188,
     188,    18,   158,   548,   159,   252,   188,   188,   188,     5,
     207,   229,   567,   266,    24,   283,   284,   285,    34,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,   222,   295,   296,
     297,   300,   302,   304,   306,   307,   309,   310,   311,   312,
     313,   314,   315,   316,   318,   320,   322,   324,   325,   326,
     295,     7,   291,   292,   293,     7,   369,   370,   371,     7,
     407,   408,   409,     7,   431,   432,   433,     7,   397,   398,
     399,   113,   114,   115,   116,   118,   329,   330,   331,   332,
     333,   334,   335,     7,   503,   504,     7,   465,   466,   467,
       7,   345,   346,   347,   126,   127,   128,   129,   130,   131,
     359,   360,   361,   362,   363,   364,   365,   366,   134,   135,
     136,   222,   338,   339,   340,   341,   342,   459,   461,   138,
     139,   222,   459,   461,   516,   517,   518,   520,   141,   142,
     143,   188,   459,   461,   524,   525,   526,   527,   529,   530,
     536,     7,   574,   575,   219,     7,   449,   450,   451,   121,
     480,   482,   500,   291,     8,     8,     8,   286,     3,     8,
     298,   301,   303,   305,     4,     4,     4,     4,     4,   317,
     319,   321,   323,     4,     4,     4,     4,     4,     4,     3,
       8,     8,   294,     6,     3,   372,     6,     3,   410,     6,
       3,   434,     6,     3,   400,     6,     3,     3,     6,   505,
       3,     6,   468,     6,     3,   348,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   519,   521,     3,     8,     4,   528,     4,   531,     3,
       8,     8,   576,     3,     6,   188,   220,   221,   452,     6,
       3,   483,     8,     6,     4,   284,     4,     4,     4,     4,
     189,   191,   189,   191,   189,     4,     4,     4,     4,   189,
     189,   189,   189,   191,   189,   296,   295,   293,   375,   371,
     413,   409,   437,   433,   222,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   245,   246,   247,   248,   249,
     250,   253,   255,   257,   259,   261,   307,   367,   385,   387,
     389,   391,   401,   402,   429,   459,   461,   474,   476,   478,
     498,   399,   330,   109,   110,   222,   307,   403,   429,   459,
     461,   474,   476,   478,   506,   507,   508,   509,   510,   512,
     504,   471,   467,   351,   347,   189,   189,   189,   189,   189,
     189,   360,   191,   189,   189,   339,     4,     4,   517,   191,
       4,   189,     4,   525,   167,   169,   170,   222,   307,   459,
     461,   577,   578,   579,   580,   582,   575,     6,     3,   455,
     451,     4,   188,    35,    36,    37,    38,   299,   188,   188,
     188,   188,   188,   188,   188,     8,     8,     8,     8,     3,
       8,   511,     4,     8,     3,     8,     8,   188,   188,   188,
     207,   583,     4,   581,     3,     8,   188,     8,   218,   402,
       4,   191,   508,     4,   189,     4,   578,   188,     5,   188,
       7,   584,   585,   586,     3,     6,   168,   171,   172,   173,
     174,   587,   588,   589,   591,   592,   593,   594,   585,   590,
       4,     4,     4,   595,     3,     8,     4,   191,   189,   189,
       4,   588,   188,   188
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   192,   194,   193,   195,   193,   196,   193,   197,   193,
     198,   193,   199,   193,   200,   193,   201,   193,   202,   193,
     203,   193,   204,   193,   205,   193,   206,   193,   207,   207,
     207,   207,   207,   207,   207,   208,   210,   209,   211,   212,
     212,   213,   213,   215,   214,   216,   216,   217,   217,   219,
     218,   220,   220,   221,   221,   222,   224,   223,   226,   225,
     228,   227,   229,   229,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   243,
     242,   244,   245,   246,   247,   248,   249,   251,   250,   252,
     252,   252,   252,   252,   254,   253,   256,   255,   258,   257,
     260,   259,   261,   262,   263,   265,   264,   266,   266,   267,
     267,   267,   267,   267,   267,   267,   269,   268,   271,   270,
     273,   272,   274,   274,   276,   275,   277,   277,   278,   280,
     279,   282,   281,   283,   283,   284,   286,   285,   288,   287,
     290,   289,   291,   291,   292,   292,   294,   293,   295,   295,
     296,   296,   296,   296,   296,   296,   296,   296,   296,   296,
     296,   296,   296,   296,   296,   296,   296,   296,   296,   296,
     296,   298,   297,   299,   299,   299,   299,   301,   300,   303,
     302,   305,   304,   306,   308,   307,   309,   310,   311,   312,
     313,   314,   315,   317,   316,   319,   318,   321,   320,   323,
     322,   324,   325,   326,   328,   327,   329,   329,   330,   330,
     330,   330,   330,   331,   332,   333,   334,   335,   337,   336,
     338,   338,   339,   339,   339,   339,   339,   339,   340,   341,
     342,   344,   343,   345,   345,   346,   346,   348,   347,   350,
     349,   351,   351,   351,   352,   352,   354,   353,   356,   355,
     358,   357,   359,   359,   360,   360,   360,   360,   360,   360,
     361,   362,   363,   364,   365,   366,   368,   367,   369,   369,
     370,   370,   372,   371,   374,   373,   375,   375,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   378,   377,
     380,   379,   382,   381,   384,   383,   386,   385,   388,   387,
     390,   389,   392,   391,   393,   393,   393,   393,   394,   396,
     395,   397,   397,   398,   398,   400,   399,   401,   401,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   404,   403,   406,   405,   407,   407,
     408,   408,   410,   409,   412,   411,   413,   413,   414,   414,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     416,   417,   418,   420,   419,   422,   421,   424,   423,   425,
     427,   426,   428,   430,   429,   431,   431,   432,   432,   434,
     433,   436,   435,   437,   437,   438,   438,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   440,   442,   441,   443,
     444,   445,   446,   448,   447,   449,   449,   450,   450,   452,
     451,   454,   453,   455,   455,   456,   456,   456,   456,   456,
     456,   456,   458,   457,   460,   459,   462,   461,   464,   463,
     465,   465,   466,   466,   468,   467,   470,   469,   471,   471,
     472,   472,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   473,   473,   475,   474,   477,
     476,   479,   478,   481,   480,   483,   482,   485,   484,   487,
     486,   489,   488,   491,   490,   493,   492,   495,   494,   497,
     496,   499,   498,   500,   500,   502,   501,   503,   503,   505,
     504,   506,   506,   507,   507,   508,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   509,   511,   510,   512,
     513,   515,   514,   516,   516,   517,   517,   517,   517,   517,
     519,   518,   521,   520,   523,   522,   524,   524,   525,   525,
     525,   525,   525,   525,   526,   528,   527,   529,   531,   530,
     533,   532,   535,   534,   536,   536,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   538,   540,   539,   541,   543,   542,
     544,   545,   547,   546,   548,   548,   550,   549,   552,   551,
     553,   554,   556,   555,   558,   557,   560,   559,   562,   561,
     564,   563,   566,   565,   567,   567,   568,   568,   570,   569,
     571,   573,   572,   574,   574,   576,   575,   577,   577,   578,
     578,   578,   578,   578,   578,   578,   579,   581,   580,   583,
     582,   584,   584,   586,   585,   587,   587,   588,   588,   588,
     588,   588,   590,   589,   591,   592,   593,   595,   594
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     0,     4,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     6,
       3,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     0,     4
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
  "global_object", "$@18", "sub_dhcp4", "$@19", "global_params",
  "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "echo_client_id", "match_client_id", "authoritative",
  "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@21",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@22",
  "ddns_qualifying_suffix", "$@23", "hostname_char_set", "$@24",
  "hostname_char_replacement", "$@25", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
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
     328,   331,   336,   344,   344,   351,   352,   355,   359,   366,
     366,   373,   374,   377,   381,   392,   401,   401,   416,   416,
     433,   433,   442,   443,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,   489,   490,   491,   492,   493,
     494,   495,   496,   497,   498,   499,   500,   501,   504,   510,
     516,   522,   528,   534,   540,   546,   552,   558,   564,   570,
     570,   579,   585,   591,   597,   603,   609,   615,   615,   624,
     627,   630,   633,   636,   642,   642,   651,   651,   660,   660,
     669,   669,   678,   684,   690,   696,   696,   708,   709,   712,
     713,   714,   715,   716,   717,   718,   721,   721,   730,   730,
     741,   741,   749,   750,   753,   753,   761,   763,   767,   774,
     774,   787,   787,   798,   799,   801,   803,   803,   822,   822,
     835,   835,   846,   847,   850,   851,   854,   854,   864,   865,
     868,   869,   870,   871,   872,   873,   874,   875,   876,   877,
     878,   879,   880,   881,   882,   883,   884,   885,   886,   887,
     888,   891,   891,   899,   900,   901,   902,   905,   905,   914,
     914,   923,   923,   932,   938,   938,   947,   953,   959,   965,
     971,   977,   983,   989,   989,   998,   998,  1007,  1007,  1016,
    1016,  1025,  1031,  1037,  1044,  1044,  1055,  1056,  1059,  1060,
    1061,  1062,  1063,  1066,  1071,  1076,  1081,  1086,  1093,  1093,
    1106,  1107,  1110,  1111,  1112,  1113,  1114,  1115,  1118,  1124,
    1130,  1136,  1136,  1147,  1148,  1151,  1152,  1155,  1155,  1165,
    1165,  1175,  1176,  1177,  1180,  1181,  1184,  1184,  1193,  1193,
    1202,  1202,  1214,  1215,  1218,  1219,  1220,  1221,  1222,  1223,
    1226,  1232,  1238,  1244,  1250,  1256,  1265,  1265,  1279,  1280,
    1283,  1284,  1291,  1291,  1317,  1317,  1328,  1329,  1333,  1334,
    1335,  1336,  1337,  1338,  1339,  1340,  1341,  1342,  1343,  1344,
    1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,
    1355,  1356,  1357,  1358,  1359,  1360,  1361,  1362,  1363,  1364,
    1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1375,  1375,
    1384,  1384,  1393,  1393,  1402,  1402,  1411,  1411,  1420,  1420,
    1429,  1429,  1440,  1440,  1448,  1449,  1450,  1451,  1454,  1462,
    1462,  1474,  1475,  1479,  1480,  1483,  1483,  1491,  1492,  1495,
    1496,  1497,  1498,  1499,  1500,  1501,  1502,  1503,  1504,  1505,
    1506,  1507,  1508,  1509,  1510,  1511,  1512,  1513,  1514,  1515,
    1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,
    1526,  1527,  1528,  1529,  1536,  1536,  1550,  1550,  1559,  1560,
    1563,  1564,  1569,  1569,  1584,  1584,  1598,  1599,  1602,  1603,
    1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,  1615,
    1618,  1620,  1626,  1628,  1628,  1637,  1637,  1646,  1646,  1655,
    1657,  1657,  1666,  1676,  1676,  1689,  1690,  1695,  1696,  1701,
    1701,  1713,  1713,  1725,  1726,  1731,  1732,  1737,  1738,  1739,
    1740,  1741,  1742,  1743,  1744,  1745,  1748,  1750,  1750,  1759,
    1761,  1763,  1769,  1778,  1778,  1791,  1792,  1795,  1796,  1799,
    1799,  1809,  1809,  1819,  1820,  1823,  1824,  1825,  1826,  1827,
    1828,  1829,  1832,  1832,  1841,  1841,  1866,  1866,  1896,  1896,
    1907,  1908,  1911,  1912,  1915,  1915,  1924,  1924,  1933,  1934,
    1937,  1938,  1942,  1943,  1944,  1945,  1946,  1947,  1948,  1949,
    1950,  1951,  1952,  1953,  1954,  1955,  1956,  1959,  1959,  1968,
    1968,  1977,  1977,  1986,  1986,  1995,  1995,  2006,  2006,  2015,
    2015,  2024,  2024,  2033,  2033,  2042,  2042,  2051,  2051,  2060,
    2060,  2074,  2074,  2085,  2086,  2092,  2092,  2103,  2104,  2107,
    2107,  2117,  2118,  2121,  2122,  2125,  2126,  2127,  2128,  2129,
    2130,  2131,  2132,  2133,  2134,  2135,  2138,  2140,  2140,  2149,
    2157,  2165,  2165,  2176,  2177,  2180,  2181,  2182,  2183,  2184,
    2187,  2187,  2196,  2196,  2208,  2208,  2221,  2222,  2225,  2226,
    2227,  2228,  2229,  2230,  2233,  2239,  2239,  2248,  2254,  2254,
    2264,  2264,  2277,  2277,  2287,  2288,  2291,  2292,  2293,  2294,
    2295,  2296,  2297,  2298,  2299,  2300,  2301,  2302,  2303,  2304,
    2305,  2306,  2307,  2308,  2311,  2317,  2317,  2326,  2332,  2332,
    2341,  2347,  2353,  2353,  2362,  2363,  2366,  2366,  2376,  2376,
    2386,  2393,  2400,  2400,  2409,  2409,  2419,  2419,  2429,  2429,
    2441,  2441,  2453,  2453,  2463,  2464,  2468,  2469,  2472,  2472,
    2483,  2491,  2491,  2504,  2505,  2509,  2509,  2517,  2518,  2521,
    2522,  2523,  2524,  2525,  2526,  2527,  2530,  2536,  2536,  2545,
    2545,  2556,  2557,  2560,  2560,  2568,  2569,  2572,  2573,  2574,
    2575,  2576,  2579,  2579,  2588,  2594,  2600,  2606,  2606
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
#line 5598 "dhcp4_parser.cc"

#line 2615 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
