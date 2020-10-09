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
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 272 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 272 "dhcp4_parser.yy"
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
#line 281 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 282 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 283 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 284 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 285 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 774 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 286 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 287 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 786 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 288 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 792 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 289 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 798 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 290 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 804 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 291 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 810 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 292 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 816 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 293 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 822 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 301 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 302 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 303 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 304 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 305 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 306 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 307 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 310 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 873 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 315 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 320 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 894 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 326 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 333 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 338 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 346 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 930 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 349 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 938 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 357 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 361 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 368 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 964 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 370 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 973 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 379 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 383 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 991 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 394 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1002 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 403 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 408 "dhcp4_parser.yy"
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
#line 418 "dhcp4_parser.yy"
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
#line 427 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 435 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1061 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 439 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1070 "dhcp4_parser.cc"
    break;

  case 120: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 508 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1080 "dhcp4_parser.cc"
    break;

  case 121: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 514 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 122: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 520 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1100 "dhcp4_parser.cc"
    break;

  case 123: // renew_timer: "renew-timer" ":" "integer"
#line 526 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 124: // rebind_timer: "rebind-timer" ":" "integer"
#line 532 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 125: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 538 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 126: // t1_percent: "t1-percent" ":" "floating point"
#line 544 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 127: // t2_percent: "t2-percent" ":" "floating point"
#line 550 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1150 "dhcp4_parser.cc"
    break;

  case 128: // cache_threshold: "cache-threshold" ":" "floating point"
#line 556 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1160 "dhcp4_parser.cc"
    break;

  case 129: // cache_max_age: "cache-max-age" ":" "integer"
#line 562 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1170 "dhcp4_parser.cc"
    break;

  case 130: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 568 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 131: // $@20: %empty
#line 574 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 132: // server_tag: "server-tag" $@20 ":" "constant string"
#line 577 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1199 "dhcp4_parser.cc"
    break;

  case 133: // echo_client_id: "echo-client-id" ":" "boolean"
#line 583 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1209 "dhcp4_parser.cc"
    break;

  case 134: // match_client_id: "match-client-id" ":" "boolean"
#line 589 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1219 "dhcp4_parser.cc"
    break;

  case 135: // authoritative: "authoritative" ":" "boolean"
#line 595 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 136: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 601 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1239 "dhcp4_parser.cc"
    break;

  case 137: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 607 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 138: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 613 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1259 "dhcp4_parser.cc"
    break;

  case 139: // $@21: %empty
#line 619 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 140: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 622 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 141: // ddns_replace_client_name_value: "when-present"
#line 628 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1285 "dhcp4_parser.cc"
    break;

  case 142: // ddns_replace_client_name_value: "never"
#line 631 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1293 "dhcp4_parser.cc"
    break;

  case 143: // ddns_replace_client_name_value: "always"
#line 634 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1301 "dhcp4_parser.cc"
    break;

  case 144: // ddns_replace_client_name_value: "when-not-present"
#line 637 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1309 "dhcp4_parser.cc"
    break;

  case 145: // ddns_replace_client_name_value: "boolean"
#line 640 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1318 "dhcp4_parser.cc"
    break;

  case 146: // $@22: %empty
#line 646 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "dhcp4_parser.cc"
    break;

  case 147: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 649 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1337 "dhcp4_parser.cc"
    break;

  case 148: // $@23: %empty
#line 655 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 149: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 658 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 150: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 664 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 151: // $@24: %empty
#line 670 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1375 "dhcp4_parser.cc"
    break;

  case 152: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 673 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 153: // $@25: %empty
#line 679 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 154: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 682 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1404 "dhcp4_parser.cc"
    break;

  case 155: // store_extended_info: "store-extended-info" ":" "boolean"
#line 688 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1414 "dhcp4_parser.cc"
    break;

  case 156: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 694 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1424 "dhcp4_parser.cc"
    break;

  case 157: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 700 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 158: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 706 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 159: // $@26: %empty
#line 712 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 160: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 718 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1466 "dhcp4_parser.cc"
    break;

  case 170: // $@27: %empty
#line 737 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1476 "dhcp4_parser.cc"
    break;

  case 171: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 741 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 172: // $@28: %empty
#line 746 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1497 "dhcp4_parser.cc"
    break;

  case 173: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 752 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1506 "dhcp4_parser.cc"
    break;

  case 174: // $@29: %empty
#line 757 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 175: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 760 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 176: // socket_type: "raw"
#line 765 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1530 "dhcp4_parser.cc"
    break;

  case 177: // socket_type: "udp"
#line 766 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1536 "dhcp4_parser.cc"
    break;

  case 178: // $@30: %empty
#line 769 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 179: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 772 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 180: // outbound_interface_value: "same-as-inbound"
#line 777 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1562 "dhcp4_parser.cc"
    break;

  case 181: // outbound_interface_value: "use-routing"
#line 779 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1570 "dhcp4_parser.cc"
    break;

  case 182: // re_detect: "re-detect" ":" "boolean"
#line 783 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1580 "dhcp4_parser.cc"
    break;

  case 183: // $@31: %empty
#line 790 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1592 "dhcp4_parser.cc"
    break;

  case 184: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 796 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 185: // $@32: %empty
#line 803 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 186: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 809 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 190: // $@33: %empty
#line 819 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 191: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 822 "dhcp4_parser.yy"
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
#line 1653 "dhcp4_parser.cc"
    break;

  case 192: // $@34: %empty
#line 838 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 193: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 844 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 194: // $@35: %empty
#line 851 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1688 "dhcp4_parser.cc"
    break;

  case 195: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 857 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1697 "dhcp4_parser.cc"
    break;

  case 200: // $@36: %empty
#line 870 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1707 "dhcp4_parser.cc"
    break;

  case 201: // database: "{" $@36 database_map_params "}"
#line 874 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 225: // $@37: %empty
#line 907 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1726 "dhcp4_parser.cc"
    break;

  case 226: // database_type: "type" $@37 ":" db_type
#line 910 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1735 "dhcp4_parser.cc"
    break;

  case 227: // db_type: "memfile"
#line 915 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1741 "dhcp4_parser.cc"
    break;

  case 228: // db_type: "mysql"
#line 916 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1747 "dhcp4_parser.cc"
    break;

  case 229: // db_type: "postgresql"
#line 917 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1753 "dhcp4_parser.cc"
    break;

  case 230: // db_type: "cql"
#line 918 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1759 "dhcp4_parser.cc"
    break;

  case 231: // $@38: %empty
#line 921 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1768 "dhcp4_parser.cc"
    break;

  case 232: // user: "user" $@38 ":" "constant string"
#line 924 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1778 "dhcp4_parser.cc"
    break;

  case 233: // $@39: %empty
#line 930 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1787 "dhcp4_parser.cc"
    break;

  case 234: // password: "password" $@39 ":" "constant string"
#line 933 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1797 "dhcp4_parser.cc"
    break;

  case 235: // $@40: %empty
#line 939 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1806 "dhcp4_parser.cc"
    break;

  case 236: // host: "host" $@40 ":" "constant string"
#line 942 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1816 "dhcp4_parser.cc"
    break;

  case 237: // port: "port" ":" "integer"
#line 948 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1826 "dhcp4_parser.cc"
    break;

  case 238: // $@41: %empty
#line 954 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1835 "dhcp4_parser.cc"
    break;

  case 239: // name: "name" $@41 ":" "constant string"
#line 957 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1845 "dhcp4_parser.cc"
    break;

  case 240: // persist: "persist" ":" "boolean"
#line 963 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1855 "dhcp4_parser.cc"
    break;

  case 241: // lfc_interval: "lfc-interval" ":" "integer"
#line 969 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1865 "dhcp4_parser.cc"
    break;

  case 242: // readonly: "readonly" ":" "boolean"
#line 975 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1875 "dhcp4_parser.cc"
    break;

  case 243: // connect_timeout: "connect-timeout" ":" "integer"
#line 981 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1885 "dhcp4_parser.cc"
    break;

  case 244: // request_timeout: "request-timeout" ":" "integer"
#line 987 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1895 "dhcp4_parser.cc"
    break;

  case 245: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 993 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1905 "dhcp4_parser.cc"
    break;

  case 246: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 999 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1915 "dhcp4_parser.cc"
    break;

  case 247: // $@42: %empty
#line 1005 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1924 "dhcp4_parser.cc"
    break;

  case 248: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1008 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1934 "dhcp4_parser.cc"
    break;

  case 249: // $@43: %empty
#line 1014 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1943 "dhcp4_parser.cc"
    break;

  case 250: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1017 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 251: // $@44: %empty
#line 1023 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 252: // consistency: "consistency" $@44 ":" "constant string"
#line 1026 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 253: // $@45: %empty
#line 1032 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 254: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1035 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 255: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1041 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 256: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1047 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 257: // max_row_errors: "max-row-errors" ":" "integer"
#line 1053 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2021 "dhcp4_parser.cc"
    break;

  case 258: // $@46: %empty
#line 1060 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2033 "dhcp4_parser.cc"
    break;

  case 259: // host_reservation_identifiers: "host-reservation-identifiers" $@46 ":" "[" host_reservation_identifiers_list "]"
#line 1066 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2042 "dhcp4_parser.cc"
    break;

  case 267: // duid_id: "duid"
#line 1082 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2051 "dhcp4_parser.cc"
    break;

  case 268: // hw_address_id: "hw-address"
#line 1087 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2060 "dhcp4_parser.cc"
    break;

  case 269: // circuit_id: "circuit-id"
#line 1092 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 270: // client_id: "client-id"
#line 1097 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2078 "dhcp4_parser.cc"
    break;

  case 271: // flex_id: "flex-id"
#line 1102 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2087 "dhcp4_parser.cc"
    break;

  case 272: // $@47: %empty
#line 1109 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 273: // dhcp_multi_threading: "multi-threading" $@47 ":" "{" multi_threading_params "}"
#line 1115 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 282: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1134 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2120 "dhcp4_parser.cc"
    break;

  case 283: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1140 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2130 "dhcp4_parser.cc"
    break;

  case 284: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1146 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2140 "dhcp4_parser.cc"
    break;

  case 285: // $@48: %empty
#line 1152 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 286: // hooks_libraries: "hooks-libraries" $@48 ":" "[" hooks_libraries_list "]"
#line 1158 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2161 "dhcp4_parser.cc"
    break;

  case 291: // $@49: %empty
#line 1171 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc"
    break;

  case 292: // hooks_library: "{" $@49 hooks_params "}"
#line 1175 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2181 "dhcp4_parser.cc"
    break;

  case 293: // $@50: %empty
#line 1181 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2191 "dhcp4_parser.cc"
    break;

  case 294: // sub_hooks_library: "{" $@50 hooks_params "}"
#line 1185 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2201 "dhcp4_parser.cc"
    break;

  case 300: // $@51: %empty
#line 1200 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2210 "dhcp4_parser.cc"
    break;

  case 301: // library: "library" $@51 ":" "constant string"
#line 1203 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2220 "dhcp4_parser.cc"
    break;

  case 302: // $@52: %empty
#line 1209 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2229 "dhcp4_parser.cc"
    break;

  case 303: // parameters: "parameters" $@52 ":" map_value
#line 1212 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2238 "dhcp4_parser.cc"
    break;

  case 304: // $@53: %empty
#line 1218 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2250 "dhcp4_parser.cc"
    break;

  case 305: // expired_leases_processing: "expired-leases-processing" $@53 ":" "{" expired_leases_params "}"
#line 1224 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 314: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1242 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2270 "dhcp4_parser.cc"
    break;

  case 315: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1248 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2280 "dhcp4_parser.cc"
    break;

  case 316: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1254 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2290 "dhcp4_parser.cc"
    break;

  case 317: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1260 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 318: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1266 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 319: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1272 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2320 "dhcp4_parser.cc"
    break;

  case 320: // $@54: %empty
#line 1281 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2332 "dhcp4_parser.cc"
    break;

  case 321: // subnet4_list: "subnet4" $@54 ":" "[" subnet4_list_content "]"
#line 1287 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2341 "dhcp4_parser.cc"
    break;

  case 326: // $@55: %empty
#line 1307 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 327: // subnet4: "{" $@55 subnet4_params "}"
#line 1311 "dhcp4_parser.yy"
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
#line 2377 "dhcp4_parser.cc"
    break;

  case 328: // $@56: %empty
#line 1333 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2387 "dhcp4_parser.cc"
    break;

  case 329: // sub_subnet4: "{" $@56 subnet4_params "}"
#line 1337 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2397 "dhcp4_parser.cc"
    break;

  case 373: // $@57: %empty
#line 1392 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 374: // subnet: "subnet" $@57 ":" "constant string"
#line 1395 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc"
    break;

  case 375: // $@58: %empty
#line 1401 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 376: // subnet_4o6_interface: "4o6-interface" $@58 ":" "constant string"
#line 1404 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 377: // $@59: %empty
#line 1410 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2444 "dhcp4_parser.cc"
    break;

  case 378: // subnet_4o6_interface_id: "4o6-interface-id" $@59 ":" "constant string"
#line 1413 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 379: // $@60: %empty
#line 1419 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 380: // subnet_4o6_subnet: "4o6-subnet" $@60 ":" "constant string"
#line 1422 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 381: // $@61: %empty
#line 1428 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 382: // interface: "interface" $@61 ":" "constant string"
#line 1431 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 383: // $@62: %empty
#line 1437 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 384: // client_class: "client-class" $@62 ":" "constant string"
#line 1440 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 385: // $@63: %empty
#line 1446 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2523 "dhcp4_parser.cc"
    break;

  case 386: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1452 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp4_parser.cc"
    break;

  case 387: // $@64: %empty
#line 1457 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2541 "dhcp4_parser.cc"
    break;

  case 388: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1460 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 389: // hr_mode: "disabled"
#line 1465 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2556 "dhcp4_parser.cc"
    break;

  case 390: // hr_mode: "out-of-pool"
#line 1466 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2562 "dhcp4_parser.cc"
    break;

  case 391: // hr_mode: "global"
#line 1467 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2568 "dhcp4_parser.cc"
    break;

  case 392: // hr_mode: "all"
#line 1468 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2574 "dhcp4_parser.cc"
    break;

  case 393: // id: "id" ":" "integer"
#line 1471 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2584 "dhcp4_parser.cc"
    break;

  case 394: // $@65: %empty
#line 1479 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2596 "dhcp4_parser.cc"
    break;

  case 395: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1485 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 400: // $@66: %empty
#line 1500 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2615 "dhcp4_parser.cc"
    break;

  case 401: // shared_network: "{" $@66 shared_network_params "}"
#line 1504 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2623 "dhcp4_parser.cc"
    break;

  case 440: // $@67: %empty
#line 1554 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2635 "dhcp4_parser.cc"
    break;

  case 441: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1560 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2644 "dhcp4_parser.cc"
    break;

  case 442: // $@68: %empty
#line 1568 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 443: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1571 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2661 "dhcp4_parser.cc"
    break;

  case 448: // $@69: %empty
#line 1587 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2671 "dhcp4_parser.cc"
    break;

  case 449: // option_def_entry: "{" $@69 option_def_params "}"
#line 1591 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 450: // $@70: %empty
#line 1602 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 451: // sub_option_def: "{" $@70 option_def_params "}"
#line 1606 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2705 "dhcp4_parser.cc"
    break;

  case 467: // code: "code" ":" "integer"
#line 1638 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2715 "dhcp4_parser.cc"
    break;

  case 469: // $@71: %empty
#line 1646 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2724 "dhcp4_parser.cc"
    break;

  case 470: // option_def_type: "type" $@71 ":" "constant string"
#line 1649 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2734 "dhcp4_parser.cc"
    break;

  case 471: // $@72: %empty
#line 1655 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2743 "dhcp4_parser.cc"
    break;

  case 472: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1658 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2753 "dhcp4_parser.cc"
    break;

  case 473: // $@73: %empty
#line 1664 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 474: // space: "space" $@73 ":" "constant string"
#line 1667 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 476: // $@74: %empty
#line 1675 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 477: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1678 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2791 "dhcp4_parser.cc"
    break;

  case 478: // option_def_array: "array" ":" "boolean"
#line 1684 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 479: // $@75: %empty
#line 1694 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2813 "dhcp4_parser.cc"
    break;

  case 480: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1700 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2822 "dhcp4_parser.cc"
    break;

  case 485: // $@76: %empty
#line 1719 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2832 "dhcp4_parser.cc"
    break;

  case 486: // option_data_entry: "{" $@76 option_data_params "}"
#line 1723 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2841 "dhcp4_parser.cc"
    break;

  case 487: // $@77: %empty
#line 1731 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2851 "dhcp4_parser.cc"
    break;

  case 488: // sub_option_data: "{" $@77 option_data_params "}"
#line 1735 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2860 "dhcp4_parser.cc"
    break;

  case 503: // $@78: %empty
#line 1768 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 504: // option_data_data: "data" $@78 ":" "constant string"
#line 1771 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc"
    break;

  case 507: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1781 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2889 "dhcp4_parser.cc"
    break;

  case 508: // option_data_always_send: "always-send" ":" "boolean"
#line 1787 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 509: // $@79: %empty
#line 1796 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2911 "dhcp4_parser.cc"
    break;

  case 510: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1802 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 515: // $@80: %empty
#line 1817 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2930 "dhcp4_parser.cc"
    break;

  case 516: // pool_list_entry: "{" $@80 pool_params "}"
#line 1821 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2940 "dhcp4_parser.cc"
    break;

  case 517: // $@81: %empty
#line 1827 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2950 "dhcp4_parser.cc"
    break;

  case 518: // sub_pool4: "{" $@81 pool_params "}"
#line 1831 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 528: // $@82: %empty
#line 1850 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2969 "dhcp4_parser.cc"
    break;

  case 529: // pool_entry: "pool" $@82 ":" "constant string"
#line 1853 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2979 "dhcp4_parser.cc"
    break;

  case 530: // $@83: %empty
#line 1859 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2987 "dhcp4_parser.cc"
    break;

  case 531: // user_context: "user-context" $@83 ":" map_value
#line 1861 "dhcp4_parser.yy"
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
#line 3014 "dhcp4_parser.cc"
    break;

  case 532: // $@84: %empty
#line 1884 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3022 "dhcp4_parser.cc"
    break;

  case 533: // comment: "comment" $@84 ":" "constant string"
#line 1886 "dhcp4_parser.yy"
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
#line 3051 "dhcp4_parser.cc"
    break;

  case 534: // $@85: %empty
#line 1914 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 535: // reservations: "reservations" $@85 ":" "[" reservations_list "]"
#line 1920 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 540: // $@86: %empty
#line 1933 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 541: // reservation: "{" $@86 reservation_params "}"
#line 1937 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 542: // $@87: %empty
#line 1942 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 543: // sub_reservation: "{" $@87 reservation_params "}"
#line 1946 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 563: // $@88: %empty
#line 1977 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3119 "dhcp4_parser.cc"
    break;

  case 564: // next_server: "next-server" $@88 ":" "constant string"
#line 1980 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3129 "dhcp4_parser.cc"
    break;

  case 565: // $@89: %empty
#line 1986 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp4_parser.cc"
    break;

  case 566: // server_hostname: "server-hostname" $@89 ":" "constant string"
#line 1989 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc"
    break;

  case 567: // $@90: %empty
#line 1995 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp4_parser.cc"
    break;

  case 568: // boot_file_name: "boot-file-name" $@90 ":" "constant string"
#line 1998 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 569: // $@91: %empty
#line 2004 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3176 "dhcp4_parser.cc"
    break;

  case 570: // ip_address: "ip-address" $@91 ":" "constant string"
#line 2007 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 571: // $@92: %empty
#line 2013 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3198 "dhcp4_parser.cc"
    break;

  case 572: // ip_addresses: "ip-addresses" $@92 ":" list_strings
#line 2019 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 573: // $@93: %empty
#line 2024 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 574: // duid: "duid" $@93 ":" "constant string"
#line 2027 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 575: // $@94: %empty
#line 2033 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 576: // hw_address: "hw-address" $@94 ":" "constant string"
#line 2036 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3245 "dhcp4_parser.cc"
    break;

  case 577: // $@95: %empty
#line 2042 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 578: // client_id_value: "client-id" $@95 ":" "constant string"
#line 2045 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3264 "dhcp4_parser.cc"
    break;

  case 579: // $@96: %empty
#line 2051 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 580: // circuit_id_value: "circuit-id" $@96 ":" "constant string"
#line 2054 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 581: // $@97: %empty
#line 2060 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3292 "dhcp4_parser.cc"
    break;

  case 582: // flex_id_value: "flex-id" $@97 ":" "constant string"
#line 2063 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3302 "dhcp4_parser.cc"
    break;

  case 583: // $@98: %empty
#line 2069 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3311 "dhcp4_parser.cc"
    break;

  case 584: // hostname: "hostname" $@98 ":" "constant string"
#line 2072 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3321 "dhcp4_parser.cc"
    break;

  case 585: // $@99: %empty
#line 2078 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3333 "dhcp4_parser.cc"
    break;

  case 586: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2084 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 587: // $@100: %empty
#line 2092 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3354 "dhcp4_parser.cc"
    break;

  case 588: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2098 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 591: // $@101: %empty
#line 2110 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3375 "dhcp4_parser.cc"
    break;

  case 592: // client_classes: "client-classes" $@101 ":" "[" client_classes_list "]"
#line 2116 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3384 "dhcp4_parser.cc"
    break;

  case 595: // $@102: %empty
#line 2125 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3394 "dhcp4_parser.cc"
    break;

  case 596: // client_class_entry: "{" $@102 client_class_params "}"
#line 2129 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3404 "dhcp4_parser.cc"
    break;

  case 613: // $@103: %empty
#line 2158 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3413 "dhcp4_parser.cc"
    break;

  case 614: // client_class_test: "test" $@103 ":" "constant string"
#line 2161 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3423 "dhcp4_parser.cc"
    break;

  case 615: // only_if_required: "only-if-required" ":" "boolean"
#line 2167 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3433 "dhcp4_parser.cc"
    break;

  case 616: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2175 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3443 "dhcp4_parser.cc"
    break;

  case 617: // $@104: %empty
#line 2183 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3455 "dhcp4_parser.cc"
    break;

  case 618: // control_socket: "control-socket" $@104 ":" "{" control_socket_params "}"
#line 2189 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3464 "dhcp4_parser.cc"
    break;

  case 626: // $@105: %empty
#line 2205 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 627: // control_socket_type: "socket-type" $@105 ":" "constant string"
#line 2208 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3483 "dhcp4_parser.cc"
    break;

  case 628: // $@106: %empty
#line 2214 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3492 "dhcp4_parser.cc"
    break;

  case 629: // control_socket_name: "socket-name" $@106 ":" "constant string"
#line 2217 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3502 "dhcp4_parser.cc"
    break;

  case 630: // $@107: %empty
#line 2226 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3514 "dhcp4_parser.cc"
    break;

  case 631: // dhcp_queue_control: "dhcp-queue-control" $@107 ":" "{" queue_control_params "}"
#line 2232 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 640: // enable_queue: "enable-queue" ":" "boolean"
#line 2251 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 641: // $@108: %empty
#line 2257 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 642: // queue_type: "queue-type" $@108 ":" "constant string"
#line 2260 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 643: // capacity: "capacity" ":" "integer"
#line 2266 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 644: // $@109: %empty
#line 2272 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 645: // arbitrary_map_entry: "constant string" $@109 ":" value
#line 2275 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 646: // $@110: %empty
#line 2282 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 647: // dhcp_ddns: "dhcp-ddns" $@110 ":" "{" dhcp_ddns_params "}"
#line 2288 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3605 "dhcp4_parser.cc"
    break;

  case 648: // $@111: %empty
#line 2295 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3615 "dhcp4_parser.cc"
    break;

  case 649: // sub_dhcp_ddns: "{" $@111 dhcp_ddns_params "}"
#line 2299 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3625 "dhcp4_parser.cc"
    break;

  case 670: // enable_updates: "enable-updates" ":" "boolean"
#line 2329 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 671: // $@112: %empty
#line 2335 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3644 "dhcp4_parser.cc"
    break;

  case 672: // server_ip: "server-ip" $@112 ":" "constant string"
#line 2338 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3654 "dhcp4_parser.cc"
    break;

  case 673: // server_port: "server-port" ":" "integer"
#line 2344 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 674: // $@113: %empty
#line 2350 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3673 "dhcp4_parser.cc"
    break;

  case 675: // sender_ip: "sender-ip" $@113 ":" "constant string"
#line 2353 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 676: // sender_port: "sender-port" ":" "integer"
#line 2359 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3693 "dhcp4_parser.cc"
    break;

  case 677: // max_queue_size: "max-queue-size" ":" "integer"
#line 2365 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3703 "dhcp4_parser.cc"
    break;

  case 678: // $@114: %empty
#line 2371 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 679: // ncr_protocol: "ncr-protocol" $@114 ":" ncr_protocol_value
#line 2374 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3721 "dhcp4_parser.cc"
    break;

  case 680: // ncr_protocol_value: "udp"
#line 2380 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3727 "dhcp4_parser.cc"
    break;

  case 681: // ncr_protocol_value: "tcp"
#line 2381 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3733 "dhcp4_parser.cc"
    break;

  case 682: // $@115: %empty
#line 2384 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 683: // ncr_format: "ncr-format" $@115 ":" "JSON"
#line 2387 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3752 "dhcp4_parser.cc"
    break;

  case 684: // $@116: %empty
#line 2394 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 685: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2397 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3771 "dhcp4_parser.cc"
    break;

  case 686: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2404 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3781 "dhcp4_parser.cc"
    break;

  case 687: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2411 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3791 "dhcp4_parser.cc"
    break;

  case 688: // $@117: %empty
#line 2418 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3800 "dhcp4_parser.cc"
    break;

  case 689: // dep_replace_client_name: "replace-client-name" $@117 ":" ddns_replace_client_name_value
#line 2421 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3809 "dhcp4_parser.cc"
    break;

  case 690: // $@118: %empty
#line 2427 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 691: // dep_generated_prefix: "generated-prefix" $@118 ":" "constant string"
#line 2430 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3828 "dhcp4_parser.cc"
    break;

  case 692: // $@119: %empty
#line 2437 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3837 "dhcp4_parser.cc"
    break;

  case 693: // dep_hostname_char_set: "hostname-char-set" $@119 ":" "constant string"
#line 2440 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3847 "dhcp4_parser.cc"
    break;

  case 694: // $@120: %empty
#line 2447 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3856 "dhcp4_parser.cc"
    break;

  case 695: // dep_hostname_char_replacement: "hostname-char-replacement" $@120 ":" "constant string"
#line 2450 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3866 "dhcp4_parser.cc"
    break;

  case 696: // $@121: %empty
#line 2459 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3878 "dhcp4_parser.cc"
    break;

  case 697: // config_control: "config-control" $@121 ":" "{" config_control_params "}"
#line 2465 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3888 "dhcp4_parser.cc"
    break;

  case 698: // $@122: %empty
#line 2471 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3898 "dhcp4_parser.cc"
    break;

  case 699: // sub_config_control: "{" $@122 config_control_params "}"
#line 2475 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3907 "dhcp4_parser.cc"
    break;

  case 704: // $@123: %empty
#line 2490 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3919 "dhcp4_parser.cc"
    break;

  case 705: // config_databases: "config-databases" $@123 ":" "[" database_list "]"
#line 2496 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 706: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2501 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3938 "dhcp4_parser.cc"
    break;

  case 707: // $@124: %empty
#line 2509 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3950 "dhcp4_parser.cc"
    break;

  case 708: // loggers: "loggers" $@124 ":" "[" loggers_entries "]"
#line 2515 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3959 "dhcp4_parser.cc"
    break;

  case 711: // $@125: %empty
#line 2527 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3969 "dhcp4_parser.cc"
    break;

  case 712: // logger_entry: "{" $@125 logger_params "}"
#line 2531 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 722: // debuglevel: "debuglevel" ":" "integer"
#line 2548 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3987 "dhcp4_parser.cc"
    break;

  case 723: // $@126: %empty
#line 2554 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3996 "dhcp4_parser.cc"
    break;

  case 724: // severity: "severity" $@126 ":" "constant string"
#line 2557 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4006 "dhcp4_parser.cc"
    break;

  case 725: // $@127: %empty
#line 2563 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4018 "dhcp4_parser.cc"
    break;

  case 726: // output_options_list: "output_options" $@127 ":" "[" output_options_list_content "]"
#line 2569 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4027 "dhcp4_parser.cc"
    break;

  case 729: // $@128: %empty
#line 2578 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4037 "dhcp4_parser.cc"
    break;

  case 730: // output_entry: "{" $@128 output_params_list "}"
#line 2582 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4045 "dhcp4_parser.cc"
    break;

  case 738: // $@129: %empty
#line 2597 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4054 "dhcp4_parser.cc"
    break;

  case 739: // output: "output" $@129 ":" "constant string"
#line 2600 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4064 "dhcp4_parser.cc"
    break;

  case 740: // flush: "flush" ":" "boolean"
#line 2606 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4074 "dhcp4_parser.cc"
    break;

  case 741: // maxsize: "maxsize" ":" "integer"
#line 2612 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4084 "dhcp4_parser.cc"
    break;

  case 742: // maxver: "maxver" ":" "integer"
#line 2618 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4094 "dhcp4_parser.cc"
    break;

  case 743: // $@130: %empty
#line 2624 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4103 "dhcp4_parser.cc"
    break;

  case 744: // pattern: "pattern" $@130 ":" "constant string"
#line 2627 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4113 "dhcp4_parser.cc"
    break;


#line 4117 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -910;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     529,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,    33,    41,    36,    49,    54,    59,
      66,    82,    86,   121,   131,   133,   145,   215,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,    41,  -143,   101,   104,    88,   224,
     -45,   231,    67,    56,   177,   -94,   403,    42,  -910,   178,
     204,   239,   211,   244,  -910,   247,  -910,  -910,  -910,   254,
     273,   276,  -910,  -910,  -910,  -910,  -910,  -910,   289,   299,
     316,   330,   336,   347,   349,   364,   366,   376,   377,  -910,
     396,   397,   399,   400,   401,  -910,  -910,  -910,   404,   408,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,   409,  -910,  -910,  -910,  -910,  -910,  -910,   411,
    -910,   412,  -910,    69,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,   413,  -910,    78,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,   415,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,    84,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,    94,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,   323,   390,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,   387,  -910,  -910,   419,  -910,  -910,  -910,   420,
    -910,  -910,   423,   434,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,   436,   438,  -910,
    -910,  -910,  -910,   435,   441,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,   118,  -910,  -910,
    -910,   443,  -910,  -910,   449,  -910,   450,   452,  -910,  -910,
     453,   454,  -910,  -910,  -910,  -910,  -910,  -910,  -910,   143,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,   455,   188,  -910,
    -910,  -910,  -910,    41,    41,  -910,   217,   457,  -910,   459,
     460,   463,   275,   277,   282,   465,   473,   475,   477,   478,
     479,   294,   297,   298,   302,   305,   304,   312,   314,   315,
     317,   318,   486,   321,   328,   322,   329,   334,   510,   544,
     558,   370,   371,   561,   562,   563,   566,   567,   568,   569,
     570,   571,   573,   574,   575,   393,   576,   577,   578,   582,
     583,   584,   398,   586,  -910,   104,  -910,   588,   590,   591,
     405,    88,  -910,   592,   595,   596,   598,   599,   600,   414,
     602,   603,   604,   224,  -910,   605,   -45,  -910,   606,   612,
     613,   614,   617,   619,   620,   621,  -910,   231,  -910,   622,
     623,   437,   625,   626,   627,   439,  -910,    56,   629,   446,
     447,  -910,   177,   630,   648,   -50,  -910,   461,   649,   651,
     474,   662,   476,   480,   664,   668,   481,   487,   669,   675,
     680,   682,   403,  -910,   684,   498,    42,  -910,  -910,  -910,
     686,   685,   688,   689,   691,  -910,  -910,  -910,   501,   503,
     509,   693,   694,   697,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,   513,  -910,  -910,  -910,  -910,
    -910,    -4,   514,   530,  -910,  -910,   714,   716,   717,   718,
     719,   534,   208,   720,   722,   723,   724,   725,  -910,   726,
     727,   728,   729,   540,   541,  -910,   732,  -910,   733,   192,
     205,  -910,  -910,   549,   550,   551,   737,   553,   554,  -910,
     733,   555,   739,  -910,   557,  -910,   733,   559,   564,   565,
     572,   579,   580,   581,  -910,   587,   589,  -910,   593,   594,
     597,  -910,  -910,   601,  -910,  -910,  -910,   607,   719,  -910,
    -910,   608,   609,  -910,   610,  -910,  -910,    31,   429,  -910,
    -910,    -4,   611,   615,   616,  -910,   743,  -910,  -910,    41,
     104,    42,    88,   734,  -910,  -910,  -910,   491,   491,   745,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,   746,
     749,   750,   752,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,   260,   753,   754,   756,   230,    58,   117,   212,   403,
    -910,  -910,   757,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,   758,  -910,  -910,  -910,  -910,   107,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,   745,  -910,
     189,   196,   197,  -910,   200,  -910,  -910,  -910,  -910,  -910,
    -910,   762,   763,   764,   768,   769,  -910,  -910,  -910,  -910,
     770,   772,   774,   776,   777,   778,  -910,   210,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,   213,
    -910,   779,   783,  -910,  -910,   782,   786,  -910,  -910,   784,
     789,  -910,  -910,   787,   791,  -910,  -910,   790,   792,  -910,
    -910,  -910,  -910,  -910,  -910,    34,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,   102,  -910,  -910,   796,   800,  -910,  -910,
     798,   804,  -910,   805,   806,   807,   808,   809,   810,   232,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,   811,   812,   813,
    -910,   233,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,   236,  -910,  -910,  -910,   814,  -910,   815,
    -910,  -910,  -910,   265,  -910,  -910,  -910,  -910,  -910,   324,
    -910,   119,  -910,   618,  -910,   816,   817,  -910,  -910,  -910,
    -910,   818,   819,  -910,  -910,  -910,   820,   734,  -910,   823,
     824,   825,   826,   632,   628,   640,   639,   642,   830,   831,
     832,   833,   647,   650,   652,   653,   646,   654,   491,  -910,
    -910,   491,  -910,   745,   224,  -910,   746,    56,  -910,   749,
     177,  -910,   750,   585,  -910,   752,   260,  -910,   288,   753,
    -910,   231,  -910,   754,   -94,  -910,   756,   655,   656,   657,
     658,   659,   660,   230,  -910,   661,   665,   667,    58,  -910,
     836,   838,   117,  -910,   666,   848,   670,   849,   212,  -910,
    -910,   194,   757,  -910,  -910,   856,   852,   -45,  -910,   758,
     861,  -910,  -910,   690,  -910,   391,   695,   707,   711,  -910,
    -910,  -910,  -910,  -910,   712,   731,   738,   747,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,   327,  -910,   335,  -910,   864,
    -910,   873,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,   361,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,   910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,   907,   915,  -910,  -910,  -910,  -910,
    -910,   921,  -910,   375,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,   795,   797,  -910,  -910,
     799,  -910,    41,  -910,  -910,   932,  -910,  -910,  -910,  -910,
    -910,   379,  -910,  -910,  -910,  -910,  -910,  -910,   801,   388,
    -910,   733,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,   585,
    -910,   935,   802,  -910,   288,  -910,  -910,  -910,  -910,  -910,
    -910,   978,   803,   986,   194,  -910,  -910,  -910,  -910,  -910,
     821,  -910,  -910,   987,  -910,   822,  -910,  -910,   989,  -910,
    -910,   136,  -910,   -91,   989,  -910,  -910,   993,   994,   995,
    -910,   389,  -910,  -910,  -910,  -910,  -910,  -910,  -910,   996,
     827,   828,   834,   997,   -91,  -910,   837,  -910,  -910,  -910,
     839,  -910,  -910,  -910
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   170,     9,   328,    11,   517,    13,
     542,    15,   442,    17,   450,    19,   487,    21,   293,    23,
     648,    25,   698,    27,    45,    39,     0,     0,     0,     0,
       0,   544,     0,   452,   489,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   696,   159,   185,     0,
       0,     0,   563,   565,   567,   183,   192,   194,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
       0,     0,     0,     0,     0,   139,   146,   148,     0,     0,
     320,   440,   479,   394,   530,   532,   387,   258,   591,   534,
     285,   304,     0,   272,   617,   630,   646,   151,   153,     0,
     707,     0,   119,     0,    62,    64,    65,    66,    67,    68,
      99,   100,   101,   102,   103,    69,    97,    86,    87,    88,
     107,   108,   109,   110,   111,   112,   113,   105,   106,   114,
     115,   116,   118,    72,    73,    94,    74,    75,    76,   117,
      80,    81,    70,    98,    71,    78,    79,    92,    93,    95,
      89,    90,    91,    77,    82,    83,    84,    85,    96,   104,
     172,   174,   178,     0,   169,     0,   161,   163,   164,   165,
     166,   167,   168,   375,   377,   379,   509,   373,   381,     0,
     385,   383,   587,   372,   332,   333,   334,   335,   336,   357,
     358,   359,   360,   361,   347,   348,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,     0,   330,   339,   352,
     353,   354,   340,   342,   343,   345,   341,   337,   338,   355,
     356,   344,   349,   350,   351,   346,   528,   527,   523,   524,
     522,     0,   519,   521,   525,   526,   585,   573,   575,   579,
     577,   583,   581,   569,   562,   556,   560,   561,     0,   545,
     546,   557,   558,   559,   553,   548,   554,   550,   551,   552,
     555,   549,     0,   469,   238,     0,   473,   471,   476,     0,
     465,   466,     0,   453,   454,   456,   468,   457,   458,   459,
     475,   460,   461,   462,   463,   464,   503,     0,     0,   501,
     502,   505,   506,     0,   490,   491,   493,   494,   495,   496,
     497,   498,   499,   500,   300,   302,   297,     0,   295,   298,
     299,     0,   684,   671,     0,   674,     0,     0,   678,   682,
       0,     0,   688,   690,   692,   694,   669,   667,   668,     0,
     650,   652,   653,   654,   655,   656,   657,   658,   659,   664,
     660,   661,   662,   663,   665,   666,   704,     0,     0,   700,
     702,   703,    44,     0,     0,    37,     0,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,     0,    61,     0,     0,     0,
       0,     0,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   329,     0,     0,   518,     0,     0,
       0,     0,     0,     0,     0,     0,   543,     0,   443,     0,
       0,     0,     0,     0,     0,     0,   451,     0,     0,     0,
       0,   488,     0,     0,     0,     0,   294,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   649,     0,     0,     0,   699,    48,    41,
       0,     0,     0,     0,     0,   133,   134,   135,     0,     0,
       0,     0,     0,     0,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     0,   156,   157,   136,   137,
     138,     0,     0,     0,   150,   155,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   616,     0,
       0,     0,     0,     0,     0,   158,     0,    63,     0,     0,
       0,   182,   162,     0,     0,     0,     0,     0,     0,   393,
       0,     0,     0,   331,     0,   520,     0,     0,     0,     0,
       0,     0,     0,     0,   547,     0,     0,   467,     0,     0,
       0,   478,   455,     0,   507,   508,   492,     0,     0,   296,
     670,     0,     0,   673,     0,   676,   677,     0,     0,   686,
     687,     0,     0,     0,     0,   651,     0,   706,   701,     0,
       0,     0,     0,     0,   564,   566,   568,     0,     0,   196,
     132,   141,   142,   143,   144,   145,   140,   147,   149,   322,
     444,   481,   396,    38,   531,   533,   389,   390,   391,   392,
     388,     0,     0,   536,   287,     0,     0,     0,     0,     0,
     152,   154,     0,    49,   173,   176,   177,   175,   180,   181,
     179,   376,   378,   380,   511,   374,   382,   386,   384,     0,
     529,   586,   574,   576,   580,   578,   584,   582,   570,   470,
     239,   474,   472,   477,   504,   301,   303,   685,   672,   675,
     680,   681,   679,   683,   689,   691,   693,   695,   196,    42,
       0,     0,     0,   190,     0,   187,   189,   225,   231,   233,
     235,     0,     0,     0,     0,     0,   247,   249,   251,   253,
       0,     0,     0,     0,     0,     0,   224,     0,   202,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   217,
     218,   219,   214,   220,   221,   222,   215,   216,   223,     0,
     200,     0,   197,   198,   326,     0,   323,   324,   448,     0,
     445,   446,   485,     0,   482,   483,   400,     0,   397,   398,
     267,   268,   269,   270,   271,     0,   260,   262,   263,   264,
     265,   266,   595,     0,   593,   540,     0,   537,   538,   291,
       0,   288,   289,     0,     0,     0,     0,     0,     0,     0,
     306,   308,   309,   310,   311,   312,   313,     0,     0,     0,
     281,     0,   274,   276,   277,   278,   279,   280,   626,   628,
     625,   623,   624,     0,   619,   621,   622,     0,   641,     0,
     644,   637,   638,     0,   632,   634,   635,   636,   639,     0,
     711,     0,   709,    51,   515,     0,   512,   513,   571,   589,
     590,     0,     0,    59,   697,   160,     0,     0,   186,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   184,
     193,     0,   195,     0,     0,   321,     0,   452,   441,     0,
     489,   480,     0,     0,   395,     0,     0,   259,   597,     0,
     592,   544,   535,     0,     0,   286,     0,     0,     0,     0,
       0,     0,     0,     0,   305,     0,     0,     0,     0,   273,
       0,     0,     0,   618,     0,     0,     0,     0,     0,   631,
     647,     0,     0,   708,    53,     0,    52,     0,   510,     0,
       0,   588,   705,     0,   188,     0,     0,     0,     0,   237,
     240,   241,   242,   243,     0,     0,     0,     0,   255,   256,
     244,   245,   246,   257,   203,     0,   199,     0,   325,     0,
     447,     0,   484,   439,   419,   420,   421,   407,   408,   424,
     425,   426,   427,   428,   410,   411,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   404,   405,   406,   417,
     418,   416,     0,   402,   409,   422,   423,   412,   413,   414,
     415,   399,   261,   613,     0,   611,   612,   604,   605,   609,
     610,   606,   607,   608,     0,   598,   599,   601,   602,   603,
     594,     0,   539,     0,   290,   314,   315,   316,   317,   318,
     319,   307,   282,   283,   284,   275,     0,     0,   620,   640,
       0,   643,     0,   633,   725,     0,   723,   721,   715,   719,
     720,     0,   713,   717,   718,   716,   710,    50,     0,     0,
     514,     0,   191,   227,   228,   229,   230,   226,   232,   234,
     236,   248,   250,   252,   254,   201,   327,   449,   486,     0,
     401,     0,     0,   596,     0,   541,   292,   627,   629,   642,
     645,     0,     0,     0,     0,   712,    54,   516,   572,   403,
       0,   615,   600,     0,   722,     0,   714,   614,     0,   724,
     729,     0,   727,     0,     0,   726,   738,     0,     0,     0,
     743,     0,   731,   733,   734,   735,   736,   737,   728,     0,
       0,     0,     0,     0,     0,   730,     0,   740,   741,   742,
       0,   732,   739,   744
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,   -52,  -910,  -528,  -910,   365,
    -910,  -910,  -910,  -910,  -910,  -910,  -585,  -910,  -910,  -910,
     -67,  -910,  -910,  -910,  -910,  -910,  -910,   352,   548,   -40,
     -28,   -24,    -1,     1,    11,    19,    22,    25,    26,  -910,
    -910,  -910,  -910,    29,    30,    32,    37,    40,    43,  -910,
     363,    44,  -910,    45,  -910,    47,    48,  -910,    50,  -910,
      51,  -910,  -910,  -910,  -910,  -910,   353,   545,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,   110,  -910,  -910,  -910,  -910,  -910,
    -910,   270,  -910,    87,  -910,  -645,    91,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,   -63,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
      77,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,    57,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,    68,  -910,  -910,
    -910,    72,   512,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
      65,  -910,  -910,  -910,  -910,  -910,  -910,  -909,  -910,  -910,
    -910,    95,  -910,  -910,  -910,    98,   560,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -906,  -910,   -65,  -910,    53,
    -910,    55,  -910,  -910,  -910,  -910,  -910,  -910,  -910,    89,
    -910,  -910,  -106,   -46,  -910,  -910,  -910,  -910,  -910,    97,
    -910,  -910,  -910,   105,  -910,   531,  -910,   -42,  -910,  -910,
    -910,  -910,  -910,   -36,  -910,  -910,  -910,  -910,  -910,   -35,
    -910,  -910,  -910,    99,  -910,  -910,  -910,   106,  -910,   532,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,    60,  -910,  -910,  -910,    61,   624,  -910,  -910,   -51,
    -910,   -11,  -910,   -25,  -910,  -910,  -910,    92,  -910,  -910,
    -910,    96,  -910,   556,   -55,  -910,     0,  -910,     7,  -910,
     332,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -905,  -910,
    -910,  -910,  -910,  -910,   103,  -910,  -910,  -910,   -90,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,    83,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,    79,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,   357,   526,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,  -910,
    -910,  -910,  -910,  -910,  -910,  -910,  -910,   402,   523,  -910,
    -910,  -910,  -910,  -910,  -910,    80,  -910,  -910,   -93,  -910,
    -910,  -910,  -910,  -910,  -910,  -114,  -910,  -910,  -130,  -910,
    -910,  -910,  -910,  -910,  -910,  -910
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   674,
      82,    83,    39,    64,    79,    80,   694,   883,   975,   976,
     766,    41,    66,    85,   397,    43,    67,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   422,   157,   158,   159,   160,   161,   162,   163,   428,
     666,   164,   429,   165,   430,   166,   167,   450,   168,   451,
     169,   170,   171,   172,   173,   400,   205,   206,    45,    68,
     207,   457,   208,   458,   697,   209,   459,   700,   210,   174,
     408,   175,   401,   744,   745,   746,   896,   176,   409,   177,
     410,   791,   792,   793,   921,   767,   768,   769,   899,  1117,
     770,   900,   771,   901,   772,   902,   773,   774,   490,   775,
     776,   777,   778,   779,   780,   781,   782,   908,   783,   909,
     784,   910,   785,   911,   786,   787,   788,   178,   440,   815,
     816,   817,   818,   819,   820,   821,   179,   446,   851,   852,
     853,   854,   855,   180,   443,   830,   831,   832,   944,    59,
      75,   347,   348,   349,   503,   350,   504,   181,   444,   839,
     840,   841,   842,   843,   844,   845,   846,   182,   433,   795,
     796,   797,   924,    47,    69,   246,   247,   248,   467,   249,
     463,   250,   464,   251,   465,   252,   468,   253,   471,   254,
     470,   183,   439,   680,   256,   184,   436,   807,   808,   809,
     933,  1042,  1043,   185,   434,    53,    72,   799,   800,   801,
     927,    55,    73,   312,   313,   314,   315,   316,   317,   318,
     489,   319,   493,   320,   492,   321,   322,   494,   323,   186,
     435,   803,   804,   805,   930,    57,    74,   333,   334,   335,
     336,   337,   498,   338,   339,   340,   341,   258,   466,   885,
     886,   887,   977,    49,    70,   271,   272,   273,   475,   187,
     437,   188,   438,   189,   442,   826,   827,   828,   941,    51,
      71,   288,   289,   290,   190,   405,   191,   406,   192,   407,
     294,   485,   890,   980,   295,   479,   296,   480,   297,   482,
     298,   481,   299,   484,   300,   483,   301,   478,   265,   472,
     891,   193,   441,   823,   824,   938,  1064,  1065,  1066,  1067,
    1068,  1131,  1069,   194,   195,   447,   863,   864,   865,   960,
     866,   961,   196,   448,   873,   874,   875,   876,   965,   877,
     878,   967,   197,   449,    61,    76,   369,   370,   371,   372,
     509,   373,   374,   511,   375,   376,   377,   514,   732,   378,
     515,   379,   508,   380,   381,   382,   518,   383,   519,   384,
     520,   385,   521,   198,   399,    63,    77,   388,   389,   390,
     524,   391,   199,   453,   881,   882,   971,  1101,  1102,  1103,
    1104,  1143,  1105,  1141,  1161,  1162,  1163,  1171,  1172,  1173,
    1179,  1174,  1175,  1176,  1177,  1183
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     142,   204,   223,   267,   284,   268,   310,   329,   346,   366,
     311,   330,    78,   789,   262,   707,   291,   211,   259,   274,
     286,   711,   324,   342,  1037,   367,   302,  1038,  1050,   224,
     344,   345,   331,    28,   257,   270,   285,   936,   332,   122,
     937,   225,   673,    40,   261,   226,    29,    81,    30,   730,
      31,   266,   124,   125,   386,   387,    42,   212,   260,   275,
     287,    44,   325,   343,   220,   368,    46,   221,   227,   263,
     228,   292,   455,    48,   344,   345,   264,   456,   293,  1166,
     229,   461,  1167,  1168,  1169,  1170,   462,   473,   230,    50,
     303,   231,   474,    52,   232,   233,   141,   476,   234,   235,
     673,   236,   477,   200,   201,   939,   237,   202,   940,   238,
     203,    84,   239,   240,   241,    86,   242,   243,    87,   244,
     245,   505,   972,   269,   255,   973,   506,    88,    54,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    56,  1164,
      58,   304,  1165,   305,   306,   141,   522,   307,   308,   309,
     121,   523,    60,   124,   125,   124,   125,   661,   662,   663,
     664,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   392,   124,   125,   121,   122,   665,
     731,   526,   455,   847,   848,   849,   527,   893,   123,   526,
     461,   124,   125,   897,   894,   895,   126,   393,   898,   695,
     696,   127,   128,   918,   124,   125,   918,   129,   919,   395,
    1037,   920,    62,  1038,  1050,   698,   699,   130,   283,   888,
     131,    32,    33,    34,    35,   953,   958,   132,   133,   962,
     954,   959,   134,   394,   963,   135,   141,   396,   141,   136,
      90,    91,    92,    93,    94,   398,   858,   859,   402,    92,
      93,    94,   304,   326,   305,   306,   327,   328,   968,   137,
     138,   139,   140,   969,   124,   125,  1005,   403,   141,   304,
     404,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   124,   125,   411,   141,   112,   113,   114,   115,   116,
     117,   118,   119,   412,   213,   214,   215,   141,   122,   124,
     125,   676,   677,   678,   679,   122,    92,    93,    94,   216,
     413,   124,   125,   217,   218,   219,   126,   522,   124,   125,
     918,   486,   970,   220,   414,  1125,   221,   129,   473,   276,
     415,   528,   529,  1126,   222,   277,   278,   279,   280,   281,
     282,   416,   283,   417,   867,   868,   869,   833,   834,   835,
     836,   837,   838,  1094,  1129,  1095,  1096,   141,   418,  1130,
     419,   121,   122,   304,   810,   811,   812,   813,   505,   814,
     420,   421,  1144,  1136,   141,   124,   125,  1145,   142,   137,
     138,   476,  1184,   487,   204,   488,  1147,  1185,  1053,  1054,
     423,   424,   870,   425,   426,   427,   223,   530,   431,   267,
     211,   268,   432,   445,   141,   452,   454,   460,   262,   469,
     284,   141,   259,   491,   495,   274,  1113,  1114,  1115,  1116,
     310,   496,   291,   224,   311,   329,   286,   497,   257,   330,
     499,   270,   500,   501,   502,   225,   324,   507,   261,   226,
     212,   342,   285,   510,   512,   366,   513,   516,   517,   525,
     331,   531,   260,   532,   533,   275,   332,   534,   535,   538,
     536,   367,   227,   263,   228,   537,   287,   539,   141,   540,
     264,   541,   542,   543,   229,   544,   325,   292,   545,   546,
     555,   343,   230,   547,   293,   231,   548,   549,   232,   233,
     124,   125,   234,   235,   550,   236,   551,   552,   553,   554,
     237,   368,   556,   238,   561,   558,   239,   240,   241,   557,
     242,   243,   559,   244,   245,   747,  1148,   560,   255,   269,
     748,   749,   750,   751,   752,   753,   754,   755,   756,   757,
     758,   759,   760,   761,   762,   763,   764,   765,   562,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   563,   564,   565,   566,   567,   568,   364,   365,
     569,   570,   571,   572,   573,   574,   304,   575,   576,   577,
     579,   580,   581,   142,   578,   204,   582,   583,   584,   733,
     586,   585,   588,   141,   589,   590,   593,   739,   591,   594,
     595,   211,   596,   597,   598,   599,   600,   601,   602,   604,
     606,    90,    91,    92,    93,    94,   607,   608,   609,   850,
     860,   610,   366,   611,   612,   613,   615,   616,   617,   618,
     619,   620,   621,   623,   627,   856,   861,   871,   367,   624,
     625,   212,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   628,   631,   630,   632,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   633,   634,   635,   637,   122,
     304,   636,   638,   641,   639,   857,   862,   872,   368,   642,
     640,   141,   124,   125,   643,   218,   644,   126,   646,   647,
     649,   654,   650,   655,   220,   651,   652,   221,   653,   656,
     657,   658,   659,   660,   667,   222,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   669,
     668,   670,   671,   672,   675,   681,    30,   682,   683,   684,
     690,   691,   685,   686,   687,   688,   689,   692,   693,   701,
     702,   703,   704,   705,   706,   708,   709,   710,   738,   712,
     137,   138,   790,   794,   713,   714,   798,   802,   743,   806,
     822,   825,   715,   829,   880,   884,   903,   904,   905,   716,
     717,   718,   906,   907,   912,   141,   913,   719,   914,   720,
     915,   916,   917,   721,   722,   922,   923,   723,   925,   926,
     928,   724,   929,   931,   932,   935,   934,   725,   727,   728,
     729,   735,   942,   943,   945,   736,   737,   946,   974,   947,
     948,   949,   950,   951,   952,   955,   956,   957,   964,   966,
     979,   990,   978,   989,   983,   982,   981,   985,   986,   987,
     988,   991,   992,   993,   994,   995,   996,   997,   998,  1002,
    1086,   999,  1087,  1000,  1001,  1003,  1075,  1076,  1077,  1078,
    1079,  1080,  1090,  1092,  1082,  1108,  1083,   223,  1084,  1089,
     310,  1091,  1107,   329,   311,  1111,  1013,   330,  1039,   262,
    1036,  1055,  1127,   259,   284,  1056,   324,   346,  1047,   342,
    1112,  1128,  1045,  1061,   224,  1118,   291,  1059,   331,   257,
     286,   850,  1057,  1014,   332,   860,   225,  1119,  1044,   261,
     226,  1120,  1121,  1058,  1097,  1015,   285,   856,  1098,  1016,
     267,   861,   268,   260,  1132,  1133,   325,   871,  1134,   343,
    1099,  1122,  1046,   227,   263,   228,   274,  1060,  1123,  1135,
     287,   264,  1017,  1048,  1018,   229,  1142,  1124,  1062,  1150,
    1049,   292,   270,   230,  1019,  1063,   231,   857,   293,   232,
     233,   862,  1020,   234,   235,  1021,   236,   872,  1022,  1023,
    1100,   237,  1024,  1025,   238,  1026,   275,   239,   240,   241,
    1027,   242,   243,  1028,   244,   245,  1029,  1030,  1031,   255,
    1032,  1033,  1153,  1034,  1035,  1137,  1040,  1138,  1041,  1139,
    1155,  1146,  1158,   726,  1154,  1151,  1160,  1180,  1181,  1182,
    1186,  1190,   740,   587,   734,   742,   592,   984,   892,  1004,
    1006,  1157,  1159,  1052,  1074,  1085,  1073,   629,  1081,  1188,
    1187,  1008,  1007,  1149,  1051,  1189,  1010,  1192,   622,  1193,
     269,  1012,  1009,   603,   626,  1072,  1011,  1071,  1109,  1110,
    1140,   889,  1070,   614,  1152,  1088,   879,  1093,   645,   648,
    1178,  1156,  1106,   741,  1191,     0,     0,     0,     0,     0,
       0,     0,  1013,     0,  1039,     0,  1036,  1055,     0,     0,
       0,  1056,     0,     0,  1047,     0,     0,  1097,  1045,  1061,
       0,  1098,     0,  1059,     0,     0,     0,     0,  1057,  1014,
       0,     0,     0,  1099,  1044,     0,     0,     0,     0,  1058,
     605,  1015,     0,     0,     0,  1016,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1046,     0,
       0,     0,     0,  1060,     0,     0,     0,     0,  1017,  1048,
    1018,     0,     0,  1100,  1062,     0,  1049,     0,     0,     0,
    1019,  1063,     0,     0,     0,     0,     0,     0,  1020,     0,
       0,  1021,     0,     0,  1022,  1023,     0,     0,  1024,  1025,
       0,  1026,     0,     0,     0,     0,  1027,     0,     0,  1028,
       0,     0,  1029,  1030,  1031,     0,  1032,  1033,     0,  1034,
    1035,     0,  1040,     0,  1041
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   658,    69,   600,    71,    68,    69,    70,
      71,   606,    73,    74,   933,    76,    72,   933,   933,    69,
     124,   125,    74,     0,    69,    70,    71,     3,    74,    84,
       6,    69,   570,     7,    69,    69,     5,   190,     7,    18,
       9,    96,    97,    98,    12,    13,     7,    68,    69,    70,
      71,     7,    73,    74,   109,    76,     7,   112,    69,    69,
      69,    71,     3,     7,   124,   125,    69,     8,    71,   170,
      69,     3,   173,   174,   175,   176,     8,     3,    69,     7,
      34,    69,     8,     7,    69,    69,   190,     3,    69,    69,
     628,    69,     8,    15,    16,     3,    69,    19,     6,    69,
      22,    10,    69,    69,    69,    11,    69,    69,    14,    69,
      69,     3,     3,    70,    69,     6,     8,    23,     7,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     7,     3,
       7,    85,     6,    87,    88,   190,     3,    91,    92,    93,
      83,     8,     7,    97,    98,    97,    98,   161,   162,   163,
     164,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,     6,    97,    98,    83,    84,   193,
     159,     3,     3,   135,   136,   137,     8,     8,    94,     3,
       3,    97,    98,     3,     8,     8,   102,     3,     8,    17,
      18,   107,   108,     3,    97,    98,     3,   113,     8,     8,
    1129,     8,     7,  1129,  1129,    20,    21,   123,   121,   122,
     126,   190,   191,   192,   193,     3,     3,   133,   134,     3,
       8,     8,   138,     4,     8,   141,   190,     3,   190,   145,
      26,    27,    28,    29,    30,     8,   139,   140,     4,    28,
      29,    30,    85,    86,    87,    88,    89,    90,     3,   165,
     166,   167,   168,     8,    97,    98,   921,     4,   190,    85,
       4,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    97,    98,     4,   190,    71,    72,    73,    74,    75,
      76,    77,    78,     4,    80,    81,    82,   190,    84,    97,
      98,   103,   104,   105,   106,    84,    28,    29,    30,    95,
       4,    97,    98,    99,   100,   101,   102,     3,    97,    98,
       3,     8,     8,   109,     4,     8,   112,   113,     3,   108,
       4,   393,   394,     8,   120,   114,   115,   116,   117,   118,
     119,     4,   121,     4,   142,   143,   144,   127,   128,   129,
     130,   131,   132,   169,     3,   171,   172,   190,     4,     8,
       4,    83,    84,    85,   114,   115,   116,   117,     3,   119,
       4,     4,     3,     8,   190,    97,    98,     8,   455,   165,
     166,     3,     3,     3,   461,     8,     8,     8,   110,   111,
       4,     4,   190,     4,     4,     4,   473,   190,     4,   476,
     461,   476,     4,     4,   190,     4,     4,     4,   473,     4,
     487,   190,   473,     4,     4,   476,    35,    36,    37,    38,
     497,     8,   487,   473,   497,   502,   487,     3,   473,   502,
       4,   476,     4,     8,     3,   473,   497,     4,   473,   473,
     461,   502,   487,     4,     4,   522,     4,     4,     4,     4,
     502,     4,   473,     4,     4,   476,   502,     4,   193,     4,
     193,   522,   473,   473,   473,   193,   487,     4,   190,     4,
     473,     4,     4,     4,   473,   191,   497,   487,   191,   191,
       4,   502,   473,   191,   487,   473,   191,   193,   473,   473,
      97,    98,   473,   473,   192,   473,   192,   192,   191,   191,
     473,   522,   191,   473,     4,   193,   473,   473,   473,   191,
     473,   473,   193,   473,   473,    34,  1111,   193,   473,   476,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,     4,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,     4,   193,   193,     4,     4,     4,   165,   166,
       4,     4,     4,     4,     4,     4,    85,     4,     4,     4,
       4,     4,     4,   650,   191,   652,     4,     4,     4,   160,
       4,   193,     4,   190,     4,     4,     4,   649,   193,     4,
       4,   652,     4,     4,     4,   191,     4,     4,     4,     4,
       4,    26,    27,    28,    29,    30,     4,     4,     4,   686,
     687,     4,   689,     4,     4,     4,     4,     4,   191,     4,
       4,     4,   193,     4,     4,   686,   687,   688,   689,   193,
     193,   652,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     4,     4,   193,     4,    71,    72,    73,    74,
      75,    76,    77,    78,    79,   191,     4,   191,     4,    84,
      85,   191,     4,     4,   193,   686,   687,   688,   689,     4,
     193,   190,    97,    98,     4,   100,     4,   102,     4,   191,
       4,   190,     7,   190,   109,     7,     7,   112,     7,   190,
       7,     7,     5,   190,   190,   120,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     5,
     190,     5,     5,     5,   190,     5,     7,     5,     5,     5,
     190,   190,     7,     7,     7,     7,     7,     5,     5,   190,
     190,   190,     5,   190,   190,   190,     7,   190,     5,   190,
     165,   166,     7,     7,   190,   190,     7,     7,    24,     7,
       7,     7,   190,     7,     7,     7,     4,     4,     4,   190,
     190,   190,     4,     4,     4,   190,     4,   190,     4,   190,
       4,     4,     4,   190,   190,     6,     3,   190,     6,     3,
       6,   190,     3,     6,     3,     3,     6,   190,   190,   190,
     190,   190,     6,     3,     6,   190,   190,     3,   190,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   193,     6,   191,     4,     6,     8,     4,     4,     4,
       4,   191,   193,   191,     4,     4,     4,     4,   191,   193,
       4,   191,     4,   191,   191,   191,   191,   191,   191,   191,
     191,   191,     4,     4,   193,     3,   191,   924,   191,   193,
     927,   191,     6,   930,   927,     4,   933,   930,   933,   924,
     933,   938,     8,   924,   941,   938,   927,   944,   933,   930,
     190,     8,   933,   938,   924,   190,   941,   938,   930,   924,
     941,   958,   938,   933,   930,   962,   924,   190,   933,   924,
     924,   190,   190,   938,   971,   933,   941,   958,   971,   933,
     977,   962,   977,   924,     4,     8,   927,   968,     3,   930,
     971,   190,   933,   924,   924,   924,   977,   938,   190,     8,
     941,   924,   933,   933,   933,   924,     4,   190,   938,     4,
     933,   941,   977,   924,   933,   938,   924,   958,   941,   924,
     924,   962,   933,   924,   924,   933,   924,   968,   933,   933,
     971,   924,   933,   933,   924,   933,   977,   924,   924,   924,
     933,   924,   924,   933,   924,   924,   933,   933,   933,   924,
     933,   933,     4,   933,   933,   190,   933,   190,   933,   190,
       4,   190,     5,   628,   191,   193,     7,     4,     4,     4,
       4,     4,   650,   455,   641,   652,   461,   897,   738,   918,
     923,   190,   190,   936,   946,   958,   944,   505,   953,   191,
     193,   926,   924,  1129,   935,   191,   929,   190,   497,   190,
     977,   932,   927,   473,   502,   943,   930,   941,   977,   979,
    1092,   709,   939,   487,  1134,   962,   689,   968,   522,   526,
    1164,  1144,   972,   651,  1184,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1129,    -1,  1129,    -1,  1129,  1134,    -1,    -1,
      -1,  1134,    -1,    -1,  1129,    -1,    -1,  1144,  1129,  1134,
      -1,  1144,    -1,  1134,    -1,    -1,    -1,    -1,  1134,  1129,
      -1,    -1,    -1,  1144,  1129,    -1,    -1,    -1,    -1,  1134,
     476,  1129,    -1,    -1,    -1,  1129,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1129,    -1,
      -1,    -1,    -1,  1134,    -1,    -1,    -1,    -1,  1129,  1129,
    1129,    -1,    -1,  1144,  1134,    -1,  1129,    -1,    -1,    -1,
    1129,  1134,    -1,    -1,    -1,    -1,    -1,    -1,  1129,    -1,
      -1,  1129,    -1,    -1,  1129,  1129,    -1,    -1,  1129,  1129,
      -1,  1129,    -1,    -1,    -1,    -1,  1129,    -1,    -1,  1129,
      -1,    -1,  1129,  1129,  1129,    -1,  1129,  1129,    -1,  1129,
    1129,    -1,  1129,    -1,  1129
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,     0,     5,
       7,     9,   190,   191,   192,   193,   209,   210,   211,   216,
       7,   225,     7,   229,     7,   272,     7,   377,     7,   457,
       7,   473,     7,   409,     7,   415,     7,   439,     7,   353,
       7,   538,     7,   569,   217,   212,   226,   230,   273,   378,
     458,   474,   410,   416,   440,   354,   539,   570,   209,   218,
     219,   190,   214,   215,    10,   227,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    83,    84,    94,    97,    98,   102,   107,   108,   113,
     123,   126,   133,   134,   138,   141,   145,   165,   166,   167,
     168,   190,   224,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   246,   247,   248,
     249,   250,   251,   252,   255,   257,   259,   260,   262,   264,
     265,   266,   267,   268,   283,   285,   291,   293,   331,   340,
     347,   361,   371,   395,   399,   407,   433,   463,   465,   467,
     478,   480,   482,   505,   517,   518,   526,   536,   567,   576,
      15,    16,    19,    22,   224,   270,   271,   274,   276,   279,
     282,   463,   465,    80,    81,    82,    95,    99,   100,   101,
     109,   112,   120,   224,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   247,   248,   249,   250,   251,   252,
     255,   257,   259,   260,   262,   264,   379,   380,   381,   383,
     385,   387,   389,   391,   393,   395,   398,   433,   451,   463,
     465,   467,   478,   480,   482,   502,    96,   224,   391,   393,
     433,   459,   460,   461,   463,   465,   108,   114,   115,   116,
     117,   118,   119,   121,   224,   433,   463,   465,   475,   476,
     477,   478,   480,   482,   484,   488,   490,   492,   494,   496,
     498,   500,   407,    34,    85,    87,    88,    91,    92,    93,
     224,   311,   417,   418,   419,   420,   421,   422,   423,   425,
     427,   429,   430,   432,   463,   465,    86,    89,    90,   224,
     311,   421,   427,   441,   442,   443,   444,   445,   447,   448,
     449,   450,   463,   465,   124,   125,   224,   355,   356,   357,
     359,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   165,   166,   224,   463,   465,   540,
     541,   542,   543,   545,   546,   548,   549,   550,   553,   555,
     557,   558,   559,   561,   563,   565,    12,    13,   571,   572,
     573,   575,     6,     3,     4,     8,     3,   228,     8,   568,
     269,   286,     4,     4,     4,   479,   481,   483,   284,   292,
     294,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   245,     4,     4,     4,     4,     4,   253,   256,
     258,     4,     4,   372,   408,   434,   400,   464,   466,   396,
     332,   506,   468,   348,   362,     4,   341,   519,   527,   537,
     261,   263,     4,   577,     4,     3,     8,   275,   277,   280,
       4,     3,     8,   384,   386,   388,   452,   382,   390,     4,
     394,   392,   503,     3,     8,   462,     3,     8,   501,   489,
     491,   495,   493,   499,   497,   485,     8,     3,     8,   424,
     312,     4,   428,   426,   431,     4,     8,     3,   446,     4,
       4,     8,     3,   358,   360,     3,     8,     4,   556,   544,
       4,   547,     4,     4,   551,   554,     4,     4,   560,   562,
     564,   566,     3,     8,   574,     4,     3,     8,   209,   209,
     190,     4,     4,     4,     4,   193,   193,   193,     4,     4,
       4,     4,     4,     4,   191,   191,   191,   191,   191,   193,
     192,   192,   192,   191,   191,     4,   191,   191,   193,   193,
     193,     4,     4,     4,   193,   193,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   191,     4,
       4,     4,     4,     4,     4,   193,     4,   232,     4,     4,
       4,   193,   271,     4,     4,     4,     4,     4,     4,   191,
       4,     4,     4,   380,     4,   460,     4,     4,     4,     4,
       4,     4,     4,     4,   477,     4,     4,   191,     4,     4,
       4,   193,   419,     4,   193,   193,   443,     4,     4,   356,
     193,     4,     4,   191,     4,   191,   191,     4,     4,   193,
     193,     4,     4,     4,     4,   541,     4,   191,   572,     4,
       7,     7,     7,     7,   190,   190,   190,     7,     7,     5,
     190,   161,   162,   163,   164,   193,   254,   190,   190,     5,
       5,     5,     5,   211,   213,   190,   103,   104,   105,   106,
     397,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     190,   190,     5,     5,   220,    17,    18,   278,    20,    21,
     281,   190,   190,   190,     5,   190,   190,   220,   190,     7,
     190,   220,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   213,   190,   190,   190,
      18,   159,   552,   160,   254,   190,   190,   190,     5,   209,
     231,   571,   270,    24,   287,   288,   289,    34,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,   224,   299,   300,   301,
     304,   306,   308,   310,   311,   313,   314,   315,   316,   317,
     318,   319,   320,   322,   324,   326,   328,   329,   330,   299,
       7,   295,   296,   297,     7,   373,   374,   375,     7,   411,
     412,   413,     7,   435,   436,   437,     7,   401,   402,   403,
     114,   115,   116,   117,   119,   333,   334,   335,   336,   337,
     338,   339,     7,   507,   508,     7,   469,   470,   471,     7,
     349,   350,   351,   127,   128,   129,   130,   131,   132,   363,
     364,   365,   366,   367,   368,   369,   370,   135,   136,   137,
     224,   342,   343,   344,   345,   346,   463,   465,   139,   140,
     224,   463,   465,   520,   521,   522,   524,   142,   143,   144,
     190,   463,   465,   528,   529,   530,   531,   533,   534,   540,
       7,   578,   579,   221,     7,   453,   454,   455,   122,   484,
     486,   504,   295,     8,     8,     8,   290,     3,     8,   302,
     305,   307,   309,     4,     4,     4,     4,     4,   321,   323,
     325,   327,     4,     4,     4,     4,     4,     4,     3,     8,
       8,   298,     6,     3,   376,     6,     3,   414,     6,     3,
     438,     6,     3,   404,     6,     3,     3,     6,   509,     3,
       6,   472,     6,     3,   352,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     523,   525,     3,     8,     4,   532,     4,   535,     3,     8,
       8,   580,     3,     6,   190,   222,   223,   456,     6,     3,
     487,     8,     6,     4,   288,     4,     4,     4,     4,   191,
     193,   191,   193,   191,     4,     4,     4,     4,   191,   191,
     191,   191,   193,   191,   300,   299,   297,   379,   375,   417,
     413,   441,   437,   224,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   247,   248,   249,   250,   251,   252,
     255,   257,   259,   260,   262,   264,   311,   371,   389,   391,
     393,   395,   405,   406,   433,   463,   465,   478,   480,   482,
     502,   403,   334,   110,   111,   224,   311,   407,   433,   463,
     465,   478,   480,   482,   510,   511,   512,   513,   514,   516,
     508,   475,   471,   355,   351,   191,   191,   191,   191,   191,
     191,   364,   193,   191,   191,   343,     4,     4,   521,   193,
       4,   191,     4,   529,   169,   171,   172,   224,   311,   463,
     465,   581,   582,   583,   584,   586,   579,     6,     3,   459,
     455,     4,   190,    35,    36,    37,    38,   303,   190,   190,
     190,   190,   190,   190,   190,     8,     8,     8,     8,     3,
       8,   515,     4,     8,     3,     8,     8,   190,   190,   190,
     209,   587,     4,   585,     3,     8,   190,     8,   220,   406,
       4,   193,   512,     4,   191,     4,   582,   190,     5,   190,
       7,   588,   589,   590,     3,     6,   170,   173,   174,   175,
     176,   591,   592,   593,   595,   596,   597,   598,   589,   594,
       4,     4,     4,   599,     3,     8,     4,   193,   191,   191,
       4,   592,   190,   190
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   194,   196,   195,   197,   195,   198,   195,   199,   195,
     200,   195,   201,   195,   202,   195,   203,   195,   204,   195,
     205,   195,   206,   195,   207,   195,   208,   195,   209,   209,
     209,   209,   209,   209,   209,   210,   212,   211,   213,   214,
     214,   215,   215,   217,   216,   218,   218,   219,   219,   221,
     220,   222,   222,   223,   223,   224,   226,   225,   228,   227,
     230,   229,   231,   231,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   245,   244,   246,   247,   248,   249,   250,   251,   253,
     252,   254,   254,   254,   254,   254,   256,   255,   258,   257,
     259,   261,   260,   263,   262,   264,   265,   266,   267,   269,
     268,   270,   270,   271,   271,   271,   271,   271,   271,   271,
     273,   272,   275,   274,   277,   276,   278,   278,   280,   279,
     281,   281,   282,   284,   283,   286,   285,   287,   287,   288,
     290,   289,   292,   291,   294,   293,   295,   295,   296,   296,
     298,   297,   299,   299,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   302,   301,   303,   303,   303,
     303,   305,   304,   307,   306,   309,   308,   310,   312,   311,
     313,   314,   315,   316,   317,   318,   319,   321,   320,   323,
     322,   325,   324,   327,   326,   328,   329,   330,   332,   331,
     333,   333,   334,   334,   334,   334,   334,   335,   336,   337,
     338,   339,   341,   340,   342,   342,   343,   343,   343,   343,
     343,   343,   344,   345,   346,   348,   347,   349,   349,   350,
     350,   352,   351,   354,   353,   355,   355,   355,   356,   356,
     358,   357,   360,   359,   362,   361,   363,   363,   364,   364,
     364,   364,   364,   364,   365,   366,   367,   368,   369,   370,
     372,   371,   373,   373,   374,   374,   376,   375,   378,   377,
     379,   379,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   382,   381,   384,   383,   386,   385,   388,
     387,   390,   389,   392,   391,   394,   393,   396,   395,   397,
     397,   397,   397,   398,   400,   399,   401,   401,   402,   402,
     404,   403,   405,   405,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     408,   407,   410,   409,   411,   411,   412,   412,   414,   413,
     416,   415,   417,   417,   418,   418,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   420,   421,   422,   424,
     423,   426,   425,   428,   427,   429,   431,   430,   432,   434,
     433,   435,   435,   436,   436,   438,   437,   440,   439,   441,
     441,   442,   442,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   444,   446,   445,   447,   448,   449,   450,   452,
     451,   453,   453,   454,   454,   456,   455,   458,   457,   459,
     459,   460,   460,   460,   460,   460,   460,   460,   462,   461,
     464,   463,   466,   465,   468,   467,   469,   469,   470,   470,
     472,   471,   474,   473,   475,   475,   476,   476,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   479,   478,   481,   480,   483,   482,   485,
     484,   487,   486,   489,   488,   491,   490,   493,   492,   495,
     494,   497,   496,   499,   498,   501,   500,   503,   502,   504,
     504,   506,   505,   507,   507,   509,   508,   510,   510,   511,
     511,   512,   512,   512,   512,   512,   512,   512,   512,   512,
     512,   512,   513,   515,   514,   516,   517,   519,   518,   520,
     520,   521,   521,   521,   521,   521,   523,   522,   525,   524,
     527,   526,   528,   528,   529,   529,   529,   529,   529,   529,
     530,   532,   531,   533,   535,   534,   537,   536,   539,   538,
     540,   540,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     542,   544,   543,   545,   547,   546,   548,   549,   551,   550,
     552,   552,   554,   553,   556,   555,   557,   558,   560,   559,
     562,   561,   564,   563,   566,   565,   568,   567,   570,   569,
     571,   571,   572,   572,   574,   573,   575,   577,   576,   578,
     578,   580,   579,   581,   581,   582,   582,   582,   582,   582,
     582,   582,   583,   585,   584,   587,   586,   588,   588,   590,
     589,   591,   591,   592,   592,   592,   592,   592,   594,   593,
     595,   596,   597,   599,   598
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
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     0,     4,     0,     4,     3,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     1,     1,     0,     4,
       1,     1,     3,     0,     6,     0,     6,     1,     3,     1,
       0,     4,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     1,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       1,     0,     6,     1,     3,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     6,     3,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4
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
  "hostname_char_set", "$@24", "hostname_char_replacement", "$@25",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "ip_reservations_unique",
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
       0,   281,   281,   281,   282,   282,   283,   283,   284,   284,
     285,   285,   286,   286,   287,   287,   288,   288,   289,   289,
     290,   290,   291,   291,   292,   292,   293,   293,   301,   302,
     303,   304,   305,   306,   307,   310,   315,   315,   326,   329,
     330,   333,   338,   346,   346,   353,   354,   357,   361,   368,
     368,   375,   376,   379,   383,   394,   403,   403,   418,   418,
     435,   435,   444,   445,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     508,   514,   520,   526,   532,   538,   544,   550,   556,   562,
     568,   574,   574,   583,   589,   595,   601,   607,   613,   619,
     619,   628,   631,   634,   637,   640,   646,   646,   655,   655,
     664,   670,   670,   679,   679,   688,   694,   700,   706,   712,
     712,   724,   725,   728,   729,   730,   731,   732,   733,   734,
     737,   737,   746,   746,   757,   757,   765,   766,   769,   769,
     777,   779,   783,   790,   790,   803,   803,   814,   815,   817,
     819,   819,   838,   838,   851,   851,   862,   863,   866,   867,
     870,   870,   880,   881,   884,   885,   886,   887,   888,   889,
     890,   891,   892,   893,   894,   895,   896,   897,   898,   899,
     900,   901,   902,   903,   904,   907,   907,   915,   916,   917,
     918,   921,   921,   930,   930,   939,   939,   948,   954,   954,
     963,   969,   975,   981,   987,   993,   999,  1005,  1005,  1014,
    1014,  1023,  1023,  1032,  1032,  1041,  1047,  1053,  1060,  1060,
    1071,  1072,  1075,  1076,  1077,  1078,  1079,  1082,  1087,  1092,
    1097,  1102,  1109,  1109,  1122,  1123,  1126,  1127,  1128,  1129,
    1130,  1131,  1134,  1140,  1146,  1152,  1152,  1163,  1164,  1167,
    1168,  1171,  1171,  1181,  1181,  1191,  1192,  1193,  1196,  1197,
    1200,  1200,  1209,  1209,  1218,  1218,  1230,  1231,  1234,  1235,
    1236,  1237,  1238,  1239,  1242,  1248,  1254,  1260,  1266,  1272,
    1281,  1281,  1295,  1296,  1299,  1300,  1307,  1307,  1333,  1333,
    1344,  1345,  1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,  1361,  1362,  1363,  1364,  1365,  1366,
    1367,  1368,  1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,
    1377,  1378,  1379,  1380,  1381,  1382,  1383,  1384,  1385,  1386,
    1387,  1388,  1389,  1392,  1392,  1401,  1401,  1410,  1410,  1419,
    1419,  1428,  1428,  1437,  1437,  1446,  1446,  1457,  1457,  1465,
    1466,  1467,  1468,  1471,  1479,  1479,  1491,  1492,  1496,  1497,
    1500,  1500,  1508,  1509,  1512,  1513,  1514,  1515,  1516,  1517,
    1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,
    1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,
    1538,  1539,  1540,  1541,  1542,  1543,  1544,  1545,  1546,  1547,
    1554,  1554,  1568,  1568,  1577,  1578,  1581,  1582,  1587,  1587,
    1602,  1602,  1616,  1617,  1620,  1621,  1624,  1625,  1626,  1627,
    1628,  1629,  1630,  1631,  1632,  1633,  1636,  1638,  1644,  1646,
    1646,  1655,  1655,  1664,  1664,  1673,  1675,  1675,  1684,  1694,
    1694,  1707,  1708,  1713,  1714,  1719,  1719,  1731,  1731,  1743,
    1744,  1749,  1750,  1755,  1756,  1757,  1758,  1759,  1760,  1761,
    1762,  1763,  1766,  1768,  1768,  1777,  1779,  1781,  1787,  1796,
    1796,  1809,  1810,  1813,  1814,  1817,  1817,  1827,  1827,  1837,
    1838,  1841,  1842,  1843,  1844,  1845,  1846,  1847,  1850,  1850,
    1859,  1859,  1884,  1884,  1914,  1914,  1925,  1926,  1929,  1930,
    1933,  1933,  1942,  1942,  1951,  1952,  1955,  1956,  1960,  1961,
    1962,  1963,  1964,  1965,  1966,  1967,  1968,  1969,  1970,  1971,
    1972,  1973,  1974,  1977,  1977,  1986,  1986,  1995,  1995,  2004,
    2004,  2013,  2013,  2024,  2024,  2033,  2033,  2042,  2042,  2051,
    2051,  2060,  2060,  2069,  2069,  2078,  2078,  2092,  2092,  2103,
    2104,  2110,  2110,  2121,  2122,  2125,  2125,  2135,  2136,  2139,
    2140,  2143,  2144,  2145,  2146,  2147,  2148,  2149,  2150,  2151,
    2152,  2153,  2156,  2158,  2158,  2167,  2175,  2183,  2183,  2194,
    2195,  2198,  2199,  2200,  2201,  2202,  2205,  2205,  2214,  2214,
    2226,  2226,  2239,  2240,  2243,  2244,  2245,  2246,  2247,  2248,
    2251,  2257,  2257,  2266,  2272,  2272,  2282,  2282,  2295,  2295,
    2305,  2306,  2309,  2310,  2311,  2312,  2313,  2314,  2315,  2316,
    2317,  2318,  2319,  2320,  2321,  2322,  2323,  2324,  2325,  2326,
    2329,  2335,  2335,  2344,  2350,  2350,  2359,  2365,  2371,  2371,
    2380,  2381,  2384,  2384,  2394,  2394,  2404,  2411,  2418,  2418,
    2427,  2427,  2437,  2437,  2447,  2447,  2459,  2459,  2471,  2471,
    2481,  2482,  2486,  2487,  2490,  2490,  2501,  2509,  2509,  2522,
    2523,  2527,  2527,  2535,  2536,  2539,  2540,  2541,  2542,  2543,
    2544,  2545,  2548,  2554,  2554,  2563,  2563,  2574,  2575,  2578,
    2578,  2586,  2587,  2590,  2591,  2592,  2593,  2594,  2597,  2597,
    2606,  2612,  2618,  2624,  2624
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
#line 5628 "dhcp4_parser.cc"

#line 2633 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
