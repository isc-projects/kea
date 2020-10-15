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
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 275 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 275 "dhcp4_parser.yy"
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
#line 284 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 285 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 286 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 287 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 288 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 774 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 289 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 290 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 786 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 291 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 792 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 292 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 798 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 293 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 804 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 294 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 810 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 295 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 816 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 296 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 822 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 304 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 305 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 306 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 307 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 308 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 309 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 310 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 313 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 873 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 318 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 323 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 894 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 329 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 336 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 341 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 349 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 930 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 352 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 938 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 360 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 364 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 371 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 964 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 373 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 973 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 382 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 386 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 991 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 397 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1002 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 406 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 411 "dhcp4_parser.yy"
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
#line 421 "dhcp4_parser.yy"
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
#line 430 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 438 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1061 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 442 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1070 "dhcp4_parser.cc"
    break;

  case 123: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 514 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1080 "dhcp4_parser.cc"
    break;

  case 124: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 520 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 125: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 526 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1100 "dhcp4_parser.cc"
    break;

  case 126: // renew_timer: "renew-timer" ":" "integer"
#line 532 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 127: // rebind_timer: "rebind-timer" ":" "integer"
#line 538 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 128: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 544 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 129: // t1_percent: "t1-percent" ":" "floating point"
#line 550 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 130: // t2_percent: "t2-percent" ":" "floating point"
#line 556 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1150 "dhcp4_parser.cc"
    break;

  case 131: // cache_threshold: "cache-threshold" ":" "floating point"
#line 562 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1160 "dhcp4_parser.cc"
    break;

  case 132: // cache_max_age: "cache-max-age" ":" "integer"
#line 568 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1170 "dhcp4_parser.cc"
    break;

  case 133: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 574 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 134: // $@20: %empty
#line 580 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 135: // server_tag: "server-tag" $@20 ":" "constant string"
#line 583 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1199 "dhcp4_parser.cc"
    break;

  case 136: // echo_client_id: "echo-client-id" ":" "boolean"
#line 589 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1209 "dhcp4_parser.cc"
    break;

  case 137: // match_client_id: "match-client-id" ":" "boolean"
#line 595 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1219 "dhcp4_parser.cc"
    break;

  case 138: // authoritative: "authoritative" ":" "boolean"
#line 601 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 139: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 607 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1239 "dhcp4_parser.cc"
    break;

  case 140: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 613 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 141: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 619 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1259 "dhcp4_parser.cc"
    break;

  case 142: // $@21: %empty
#line 625 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 143: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 628 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 144: // ddns_replace_client_name_value: "when-present"
#line 634 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1285 "dhcp4_parser.cc"
    break;

  case 145: // ddns_replace_client_name_value: "never"
#line 637 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1293 "dhcp4_parser.cc"
    break;

  case 146: // ddns_replace_client_name_value: "always"
#line 640 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1301 "dhcp4_parser.cc"
    break;

  case 147: // ddns_replace_client_name_value: "when-not-present"
#line 643 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1309 "dhcp4_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "boolean"
#line 646 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1318 "dhcp4_parser.cc"
    break;

  case 149: // $@22: %empty
#line 652 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "dhcp4_parser.cc"
    break;

  case 150: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 655 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1337 "dhcp4_parser.cc"
    break;

  case 151: // $@23: %empty
#line 661 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 152: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 664 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 153: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 670 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 154: // $@24: %empty
#line 676 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1375 "dhcp4_parser.cc"
    break;

  case 155: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 679 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 156: // $@25: %empty
#line 685 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 157: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 688 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1404 "dhcp4_parser.cc"
    break;

  case 158: // store_extended_info: "store-extended-info" ":" "boolean"
#line 694 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1414 "dhcp4_parser.cc"
    break;

  case 159: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 700 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1424 "dhcp4_parser.cc"
    break;

  case 160: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 706 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 161: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 712 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 162: // $@26: %empty
#line 718 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 163: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 724 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1466 "dhcp4_parser.cc"
    break;

  case 173: // $@27: %empty
#line 743 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1476 "dhcp4_parser.cc"
    break;

  case 174: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 747 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 175: // $@28: %empty
#line 752 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1497 "dhcp4_parser.cc"
    break;

  case 176: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 758 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1506 "dhcp4_parser.cc"
    break;

  case 177: // $@29: %empty
#line 763 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 178: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 766 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 179: // socket_type: "raw"
#line 771 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1530 "dhcp4_parser.cc"
    break;

  case 180: // socket_type: "udp"
#line 772 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1536 "dhcp4_parser.cc"
    break;

  case 181: // $@30: %empty
#line 775 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 182: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 778 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 183: // outbound_interface_value: "same-as-inbound"
#line 783 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1562 "dhcp4_parser.cc"
    break;

  case 184: // outbound_interface_value: "use-routing"
#line 785 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1570 "dhcp4_parser.cc"
    break;

  case 185: // re_detect: "re-detect" ":" "boolean"
#line 789 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1580 "dhcp4_parser.cc"
    break;

  case 186: // $@31: %empty
#line 796 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1592 "dhcp4_parser.cc"
    break;

  case 187: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 802 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 188: // $@32: %empty
#line 809 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 189: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 815 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 193: // $@33: %empty
#line 825 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 194: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 828 "dhcp4_parser.yy"
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

  case 195: // $@34: %empty
#line 844 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 196: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 850 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 197: // $@35: %empty
#line 857 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1688 "dhcp4_parser.cc"
    break;

  case 198: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 863 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1697 "dhcp4_parser.cc"
    break;

  case 203: // $@36: %empty
#line 876 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1707 "dhcp4_parser.cc"
    break;

  case 204: // database: "{" $@36 database_map_params "}"
#line 880 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 228: // $@37: %empty
#line 913 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1726 "dhcp4_parser.cc"
    break;

  case 229: // database_type: "type" $@37 ":" db_type
#line 916 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1735 "dhcp4_parser.cc"
    break;

  case 230: // db_type: "memfile"
#line 921 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1741 "dhcp4_parser.cc"
    break;

  case 231: // db_type: "mysql"
#line 922 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1747 "dhcp4_parser.cc"
    break;

  case 232: // db_type: "postgresql"
#line 923 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1753 "dhcp4_parser.cc"
    break;

  case 233: // db_type: "cql"
#line 924 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1759 "dhcp4_parser.cc"
    break;

  case 234: // $@38: %empty
#line 927 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1768 "dhcp4_parser.cc"
    break;

  case 235: // user: "user" $@38 ":" "constant string"
#line 930 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1778 "dhcp4_parser.cc"
    break;

  case 236: // $@39: %empty
#line 936 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1787 "dhcp4_parser.cc"
    break;

  case 237: // password: "password" $@39 ":" "constant string"
#line 939 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1797 "dhcp4_parser.cc"
    break;

  case 238: // $@40: %empty
#line 945 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1806 "dhcp4_parser.cc"
    break;

  case 239: // host: "host" $@40 ":" "constant string"
#line 948 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1816 "dhcp4_parser.cc"
    break;

  case 240: // port: "port" ":" "integer"
#line 954 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1826 "dhcp4_parser.cc"
    break;

  case 241: // $@41: %empty
#line 960 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1835 "dhcp4_parser.cc"
    break;

  case 242: // name: "name" $@41 ":" "constant string"
#line 963 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1845 "dhcp4_parser.cc"
    break;

  case 243: // persist: "persist" ":" "boolean"
#line 969 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1855 "dhcp4_parser.cc"
    break;

  case 244: // lfc_interval: "lfc-interval" ":" "integer"
#line 975 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1865 "dhcp4_parser.cc"
    break;

  case 245: // readonly: "readonly" ":" "boolean"
#line 981 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1875 "dhcp4_parser.cc"
    break;

  case 246: // connect_timeout: "connect-timeout" ":" "integer"
#line 987 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1885 "dhcp4_parser.cc"
    break;

  case 247: // request_timeout: "request-timeout" ":" "integer"
#line 993 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1895 "dhcp4_parser.cc"
    break;

  case 248: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 999 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1905 "dhcp4_parser.cc"
    break;

  case 249: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1005 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1915 "dhcp4_parser.cc"
    break;

  case 250: // $@42: %empty
#line 1011 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1924 "dhcp4_parser.cc"
    break;

  case 251: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1014 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1934 "dhcp4_parser.cc"
    break;

  case 252: // $@43: %empty
#line 1020 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1943 "dhcp4_parser.cc"
    break;

  case 253: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1023 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 254: // $@44: %empty
#line 1029 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 255: // consistency: "consistency" $@44 ":" "constant string"
#line 1032 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 256: // $@45: %empty
#line 1038 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 257: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1041 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 258: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1047 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 259: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1053 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 260: // max_row_errors: "max-row-errors" ":" "integer"
#line 1059 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2021 "dhcp4_parser.cc"
    break;

  case 261: // $@46: %empty
#line 1066 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2033 "dhcp4_parser.cc"
    break;

  case 262: // host_reservation_identifiers: "host-reservation-identifiers" $@46 ":" "[" host_reservation_identifiers_list "]"
#line 1072 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2042 "dhcp4_parser.cc"
    break;

  case 270: // duid_id: "duid"
#line 1088 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2051 "dhcp4_parser.cc"
    break;

  case 271: // hw_address_id: "hw-address"
#line 1093 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2060 "dhcp4_parser.cc"
    break;

  case 272: // circuit_id: "circuit-id"
#line 1098 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 273: // client_id: "client-id"
#line 1103 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2078 "dhcp4_parser.cc"
    break;

  case 274: // flex_id: "flex-id"
#line 1108 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2087 "dhcp4_parser.cc"
    break;

  case 275: // $@47: %empty
#line 1115 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 276: // dhcp_multi_threading: "multi-threading" $@47 ":" "{" multi_threading_params "}"
#line 1121 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 285: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1140 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2120 "dhcp4_parser.cc"
    break;

  case 286: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1146 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2130 "dhcp4_parser.cc"
    break;

  case 287: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1152 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2140 "dhcp4_parser.cc"
    break;

  case 288: // $@48: %empty
#line 1158 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 289: // hooks_libraries: "hooks-libraries" $@48 ":" "[" hooks_libraries_list "]"
#line 1164 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2161 "dhcp4_parser.cc"
    break;

  case 294: // $@49: %empty
#line 1177 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc"
    break;

  case 295: // hooks_library: "{" $@49 hooks_params "}"
#line 1181 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2181 "dhcp4_parser.cc"
    break;

  case 296: // $@50: %empty
#line 1187 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2191 "dhcp4_parser.cc"
    break;

  case 297: // sub_hooks_library: "{" $@50 hooks_params "}"
#line 1191 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2201 "dhcp4_parser.cc"
    break;

  case 303: // $@51: %empty
#line 1206 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2210 "dhcp4_parser.cc"
    break;

  case 304: // library: "library" $@51 ":" "constant string"
#line 1209 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2220 "dhcp4_parser.cc"
    break;

  case 305: // $@52: %empty
#line 1215 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2229 "dhcp4_parser.cc"
    break;

  case 306: // parameters: "parameters" $@52 ":" map_value
#line 1218 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2238 "dhcp4_parser.cc"
    break;

  case 307: // $@53: %empty
#line 1224 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2250 "dhcp4_parser.cc"
    break;

  case 308: // expired_leases_processing: "expired-leases-processing" $@53 ":" "{" expired_leases_params "}"
#line 1230 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 317: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1248 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2270 "dhcp4_parser.cc"
    break;

  case 318: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1254 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2280 "dhcp4_parser.cc"
    break;

  case 319: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1260 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2290 "dhcp4_parser.cc"
    break;

  case 320: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1266 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 321: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1272 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 322: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1278 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2320 "dhcp4_parser.cc"
    break;

  case 323: // $@54: %empty
#line 1287 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2332 "dhcp4_parser.cc"
    break;

  case 324: // subnet4_list: "subnet4" $@54 ":" "[" subnet4_list_content "]"
#line 1293 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2341 "dhcp4_parser.cc"
    break;

  case 329: // $@55: %empty
#line 1313 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 330: // subnet4: "{" $@55 subnet4_params "}"
#line 1317 "dhcp4_parser.yy"
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

  case 331: // $@56: %empty
#line 1339 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2387 "dhcp4_parser.cc"
    break;

  case 332: // sub_subnet4: "{" $@56 subnet4_params "}"
#line 1343 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2397 "dhcp4_parser.cc"
    break;

  case 379: // $@57: %empty
#line 1401 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 380: // subnet: "subnet" $@57 ":" "constant string"
#line 1404 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc"
    break;

  case 381: // $@58: %empty
#line 1410 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 382: // subnet_4o6_interface: "4o6-interface" $@58 ":" "constant string"
#line 1413 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 383: // $@59: %empty
#line 1419 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2444 "dhcp4_parser.cc"
    break;

  case 384: // subnet_4o6_interface_id: "4o6-interface-id" $@59 ":" "constant string"
#line 1422 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 385: // $@60: %empty
#line 1428 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 386: // subnet_4o6_subnet: "4o6-subnet" $@60 ":" "constant string"
#line 1431 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 387: // $@61: %empty
#line 1437 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 388: // interface: "interface" $@61 ":" "constant string"
#line 1440 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 389: // $@62: %empty
#line 1446 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 390: // client_class: "client-class" $@62 ":" "constant string"
#line 1449 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 391: // $@63: %empty
#line 1455 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2523 "dhcp4_parser.cc"
    break;

  case 392: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1461 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp4_parser.cc"
    break;

  case 393: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1466 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2542 "dhcp4_parser.cc"
    break;

  case 394: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1472 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2552 "dhcp4_parser.cc"
    break;

  case 395: // reservations_global: "reservations-global" ":" "boolean"
#line 1478 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2562 "dhcp4_parser.cc"
    break;

  case 396: // $@64: %empty
#line 1484 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2571 "dhcp4_parser.cc"
    break;

  case 397: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1487 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 398: // hr_mode: "disabled"
#line 1492 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2586 "dhcp4_parser.cc"
    break;

  case 399: // hr_mode: "out-of-pool"
#line 1493 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2592 "dhcp4_parser.cc"
    break;

  case 400: // hr_mode: "global"
#line 1494 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2598 "dhcp4_parser.cc"
    break;

  case 401: // hr_mode: "all"
#line 1495 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2604 "dhcp4_parser.cc"
    break;

  case 402: // id: "id" ":" "integer"
#line 1498 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2614 "dhcp4_parser.cc"
    break;

  case 403: // $@65: %empty
#line 1506 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 404: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1512 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2635 "dhcp4_parser.cc"
    break;

  case 409: // $@66: %empty
#line 1527 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2645 "dhcp4_parser.cc"
    break;

  case 410: // shared_network: "{" $@66 shared_network_params "}"
#line 1531 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 452: // $@67: %empty
#line 1584 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2665 "dhcp4_parser.cc"
    break;

  case 453: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1590 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2674 "dhcp4_parser.cc"
    break;

  case 454: // $@68: %empty
#line 1598 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 455: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1601 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2691 "dhcp4_parser.cc"
    break;

  case 460: // $@69: %empty
#line 1617 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2701 "dhcp4_parser.cc"
    break;

  case 461: // option_def_entry: "{" $@69 option_def_params "}"
#line 1621 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2713 "dhcp4_parser.cc"
    break;

  case 462: // $@70: %empty
#line 1632 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2723 "dhcp4_parser.cc"
    break;

  case 463: // sub_option_def: "{" $@70 option_def_params "}"
#line 1636 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2735 "dhcp4_parser.cc"
    break;

  case 479: // code: "code" ":" "integer"
#line 1668 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2745 "dhcp4_parser.cc"
    break;

  case 481: // $@71: %empty
#line 1676 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2754 "dhcp4_parser.cc"
    break;

  case 482: // option_def_type: "type" $@71 ":" "constant string"
#line 1679 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2764 "dhcp4_parser.cc"
    break;

  case 483: // $@72: %empty
#line 1685 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2773 "dhcp4_parser.cc"
    break;

  case 484: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1688 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2783 "dhcp4_parser.cc"
    break;

  case 485: // $@73: %empty
#line 1694 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 486: // space: "space" $@73 ":" "constant string"
#line 1697 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 488: // $@74: %empty
#line 1705 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp4_parser.cc"
    break;

  case 489: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1708 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 490: // option_def_array: "array" ":" "boolean"
#line 1714 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 491: // $@75: %empty
#line 1724 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2843 "dhcp4_parser.cc"
    break;

  case 492: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1730 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 497: // $@76: %empty
#line 1749 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2862 "dhcp4_parser.cc"
    break;

  case 498: // option_data_entry: "{" $@76 option_data_params "}"
#line 1753 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 499: // $@77: %empty
#line 1761 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2881 "dhcp4_parser.cc"
    break;

  case 500: // sub_option_data: "{" $@77 option_data_params "}"
#line 1765 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 515: // $@78: %empty
#line 1798 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 516: // option_data_data: "data" $@78 ":" "constant string"
#line 1801 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 519: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1811 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2919 "dhcp4_parser.cc"
    break;

  case 520: // option_data_always_send: "always-send" ":" "boolean"
#line 1817 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2929 "dhcp4_parser.cc"
    break;

  case 521: // $@79: %empty
#line 1826 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2941 "dhcp4_parser.cc"
    break;

  case 522: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1832 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2950 "dhcp4_parser.cc"
    break;

  case 527: // $@80: %empty
#line 1847 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 528: // pool_list_entry: "{" $@80 pool_params "}"
#line 1851 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 529: // $@81: %empty
#line 1857 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 530: // sub_pool4: "{" $@81 pool_params "}"
#line 1861 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 540: // $@82: %empty
#line 1880 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 541: // pool_entry: "pool" $@82 ":" "constant string"
#line 1883 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3009 "dhcp4_parser.cc"
    break;

  case 542: // $@83: %empty
#line 1889 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp4_parser.cc"
    break;

  case 543: // user_context: "user-context" $@83 ":" map_value
#line 1891 "dhcp4_parser.yy"
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
#line 3044 "dhcp4_parser.cc"
    break;

  case 544: // $@84: %empty
#line 1914 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 545: // comment: "comment" $@84 ":" "constant string"
#line 1916 "dhcp4_parser.yy"
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
#line 3081 "dhcp4_parser.cc"
    break;

  case 546: // $@85: %empty
#line 1944 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3093 "dhcp4_parser.cc"
    break;

  case 547: // reservations: "reservations" $@85 ":" "[" reservations_list "]"
#line 1950 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3102 "dhcp4_parser.cc"
    break;

  case 552: // $@86: %empty
#line 1963 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3112 "dhcp4_parser.cc"
    break;

  case 553: // reservation: "{" $@86 reservation_params "}"
#line 1967 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 554: // $@87: %empty
#line 1972 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3131 "dhcp4_parser.cc"
    break;

  case 555: // sub_reservation: "{" $@87 reservation_params "}"
#line 1976 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3140 "dhcp4_parser.cc"
    break;

  case 575: // $@88: %empty
#line 2007 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 576: // next_server: "next-server" $@88 ":" "constant string"
#line 2010 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 577: // $@89: %empty
#line 2016 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3168 "dhcp4_parser.cc"
    break;

  case 578: // server_hostname: "server-hostname" $@89 ":" "constant string"
#line 2019 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 579: // $@90: %empty
#line 2025 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 580: // boot_file_name: "boot-file-name" $@90 ":" "constant string"
#line 2028 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 581: // $@91: %empty
#line 2034 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 582: // ip_address: "ip-address" $@91 ":" "constant string"
#line 2037 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 583: // $@92: %empty
#line 2043 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3228 "dhcp4_parser.cc"
    break;

  case 584: // ip_addresses: "ip-addresses" $@92 ":" list_strings
#line 2049 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3237 "dhcp4_parser.cc"
    break;

  case 585: // $@93: %empty
#line 2054 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3246 "dhcp4_parser.cc"
    break;

  case 586: // duid: "duid" $@93 ":" "constant string"
#line 2057 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3256 "dhcp4_parser.cc"
    break;

  case 587: // $@94: %empty
#line 2063 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3265 "dhcp4_parser.cc"
    break;

  case 588: // hw_address: "hw-address" $@94 ":" "constant string"
#line 2066 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3275 "dhcp4_parser.cc"
    break;

  case 589: // $@95: %empty
#line 2072 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 590: // client_id_value: "client-id" $@95 ":" "constant string"
#line 2075 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 591: // $@96: %empty
#line 2081 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 592: // circuit_id_value: "circuit-id" $@96 ":" "constant string"
#line 2084 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3313 "dhcp4_parser.cc"
    break;

  case 593: // $@97: %empty
#line 2090 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 594: // flex_id_value: "flex-id" $@97 ":" "constant string"
#line 2093 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 595: // $@98: %empty
#line 2099 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 596: // hostname: "hostname" $@98 ":" "constant string"
#line 2102 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 597: // $@99: %empty
#line 2108 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 598: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2114 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3372 "dhcp4_parser.cc"
    break;

  case 599: // $@100: %empty
#line 2122 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3384 "dhcp4_parser.cc"
    break;

  case 600: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2128 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3393 "dhcp4_parser.cc"
    break;

  case 603: // $@101: %empty
#line 2140 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3405 "dhcp4_parser.cc"
    break;

  case 604: // client_classes: "client-classes" $@101 ":" "[" client_classes_list "]"
#line 2146 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3414 "dhcp4_parser.cc"
    break;

  case 607: // $@102: %empty
#line 2155 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3424 "dhcp4_parser.cc"
    break;

  case 608: // client_class_entry: "{" $@102 client_class_params "}"
#line 2159 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3434 "dhcp4_parser.cc"
    break;

  case 625: // $@103: %empty
#line 2188 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3443 "dhcp4_parser.cc"
    break;

  case 626: // client_class_test: "test" $@103 ":" "constant string"
#line 2191 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 627: // only_if_required: "only-if-required" ":" "boolean"
#line 2197 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 628: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2205 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 629: // $@104: %empty
#line 2213 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 630: // control_socket: "control-socket" $@104 ":" "{" control_socket_params "}"
#line 2219 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3494 "dhcp4_parser.cc"
    break;

  case 638: // $@105: %empty
#line 2235 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3503 "dhcp4_parser.cc"
    break;

  case 639: // control_socket_type: "socket-type" $@105 ":" "constant string"
#line 2238 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3513 "dhcp4_parser.cc"
    break;

  case 640: // $@106: %empty
#line 2244 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3522 "dhcp4_parser.cc"
    break;

  case 641: // control_socket_name: "socket-name" $@106 ":" "constant string"
#line 2247 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3532 "dhcp4_parser.cc"
    break;

  case 642: // $@107: %empty
#line 2256 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 643: // dhcp_queue_control: "dhcp-queue-control" $@107 ":" "{" queue_control_params "}"
#line 2262 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3555 "dhcp4_parser.cc"
    break;

  case 652: // enable_queue: "enable-queue" ":" "boolean"
#line 2281 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 653: // $@108: %empty
#line 2287 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 654: // queue_type: "queue-type" $@108 ":" "constant string"
#line 2290 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3584 "dhcp4_parser.cc"
    break;

  case 655: // capacity: "capacity" ":" "integer"
#line 2296 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 656: // $@109: %empty
#line 2302 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 657: // arbitrary_map_entry: "constant string" $@109 ":" value
#line 2305 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 658: // $@110: %empty
#line 2312 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3624 "dhcp4_parser.cc"
    break;

  case 659: // dhcp_ddns: "dhcp-ddns" $@110 ":" "{" dhcp_ddns_params "}"
#line 2318 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 660: // $@111: %empty
#line 2325 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 661: // sub_dhcp_ddns: "{" $@111 dhcp_ddns_params "}"
#line 2329 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3655 "dhcp4_parser.cc"
    break;

  case 682: // enable_updates: "enable-updates" ":" "boolean"
#line 2359 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3665 "dhcp4_parser.cc"
    break;

  case 683: // $@112: %empty
#line 2365 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3674 "dhcp4_parser.cc"
    break;

  case 684: // server_ip: "server-ip" $@112 ":" "constant string"
#line 2368 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3684 "dhcp4_parser.cc"
    break;

  case 685: // server_port: "server-port" ":" "integer"
#line 2374 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3694 "dhcp4_parser.cc"
    break;

  case 686: // $@113: %empty
#line 2380 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3703 "dhcp4_parser.cc"
    break;

  case 687: // sender_ip: "sender-ip" $@113 ":" "constant string"
#line 2383 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3713 "dhcp4_parser.cc"
    break;

  case 688: // sender_port: "sender-port" ":" "integer"
#line 2389 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3723 "dhcp4_parser.cc"
    break;

  case 689: // max_queue_size: "max-queue-size" ":" "integer"
#line 2395 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 690: // $@114: %empty
#line 2401 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 691: // ncr_protocol: "ncr-protocol" $@114 ":" ncr_protocol_value
#line 2404 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 692: // ncr_protocol_value: "udp"
#line 2410 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3757 "dhcp4_parser.cc"
    break;

  case 693: // ncr_protocol_value: "tcp"
#line 2411 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3763 "dhcp4_parser.cc"
    break;

  case 694: // $@115: %empty
#line 2414 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3772 "dhcp4_parser.cc"
    break;

  case 695: // ncr_format: "ncr-format" $@115 ":" "JSON"
#line 2417 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3782 "dhcp4_parser.cc"
    break;

  case 696: // $@116: %empty
#line 2424 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3791 "dhcp4_parser.cc"
    break;

  case 697: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2427 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3801 "dhcp4_parser.cc"
    break;

  case 698: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2434 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3811 "dhcp4_parser.cc"
    break;

  case 699: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2441 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3821 "dhcp4_parser.cc"
    break;

  case 700: // $@117: %empty
#line 2448 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 701: // dep_replace_client_name: "replace-client-name" $@117 ":" ddns_replace_client_name_value
#line 2451 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3839 "dhcp4_parser.cc"
    break;

  case 702: // $@118: %empty
#line 2457 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3848 "dhcp4_parser.cc"
    break;

  case 703: // dep_generated_prefix: "generated-prefix" $@118 ":" "constant string"
#line 2460 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 704: // $@119: %empty
#line 2467 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3867 "dhcp4_parser.cc"
    break;

  case 705: // dep_hostname_char_set: "hostname-char-set" $@119 ":" "constant string"
#line 2470 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3877 "dhcp4_parser.cc"
    break;

  case 706: // $@120: %empty
#line 2477 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3886 "dhcp4_parser.cc"
    break;

  case 707: // dep_hostname_char_replacement: "hostname-char-replacement" $@120 ":" "constant string"
#line 2480 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3896 "dhcp4_parser.cc"
    break;

  case 708: // $@121: %empty
#line 2489 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3908 "dhcp4_parser.cc"
    break;

  case 709: // config_control: "config-control" $@121 ":" "{" config_control_params "}"
#line 2495 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 710: // $@122: %empty
#line 2501 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 711: // sub_config_control: "{" $@122 config_control_params "}"
#line 2505 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3937 "dhcp4_parser.cc"
    break;

  case 716: // $@123: %empty
#line 2520 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3949 "dhcp4_parser.cc"
    break;

  case 717: // config_databases: "config-databases" $@123 ":" "[" database_list "]"
#line 2526 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3958 "dhcp4_parser.cc"
    break;

  case 718: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2531 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3968 "dhcp4_parser.cc"
    break;

  case 719: // $@124: %empty
#line 2539 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3980 "dhcp4_parser.cc"
    break;

  case 720: // loggers: "loggers" $@124 ":" "[" loggers_entries "]"
#line 2545 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 723: // $@125: %empty
#line 2557 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3999 "dhcp4_parser.cc"
    break;

  case 724: // logger_entry: "{" $@125 logger_params "}"
#line 2561 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4007 "dhcp4_parser.cc"
    break;

  case 734: // debuglevel: "debuglevel" ":" "integer"
#line 2578 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4017 "dhcp4_parser.cc"
    break;

  case 735: // $@126: %empty
#line 2584 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4026 "dhcp4_parser.cc"
    break;

  case 736: // severity: "severity" $@126 ":" "constant string"
#line 2587 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4036 "dhcp4_parser.cc"
    break;

  case 737: // $@127: %empty
#line 2593 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4048 "dhcp4_parser.cc"
    break;

  case 738: // output_options_list: "output_options" $@127 ":" "[" output_options_list_content "]"
#line 2599 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4057 "dhcp4_parser.cc"
    break;

  case 741: // $@128: %empty
#line 2608 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4067 "dhcp4_parser.cc"
    break;

  case 742: // output_entry: "{" $@128 output_params_list "}"
#line 2612 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4075 "dhcp4_parser.cc"
    break;

  case 750: // $@129: %empty
#line 2627 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4084 "dhcp4_parser.cc"
    break;

  case 751: // output: "output" $@129 ":" "constant string"
#line 2630 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4094 "dhcp4_parser.cc"
    break;

  case 752: // flush: "flush" ":" "boolean"
#line 2636 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4104 "dhcp4_parser.cc"
    break;

  case 753: // maxsize: "maxsize" ":" "integer"
#line 2642 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 754: // maxver: "maxver" ":" "integer"
#line 2648 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 755: // $@130: %empty
#line 2654 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4133 "dhcp4_parser.cc"
    break;

  case 756: // pattern: "pattern" $@130 ":" "constant string"
#line 2657 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4143 "dhcp4_parser.cc"
    break;


#line 4147 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -934;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     544,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,    28,    41,    57,    74,    80,   100,
     104,   125,   129,   152,   187,   189,   200,   206,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,    41,  -160,    27,   114,    67,   240,
       6,   250,    -4,    63,   300,   -85,   422,    54,  -934,   215,
     163,   225,    39,   228,  -934,   231,  -934,  -934,  -934,   238,
     241,   257,  -934,  -934,  -934,  -934,  -934,  -934,   259,   267,
     304,   319,   342,   349,   358,   360,   362,   373,   379,  -934,
     389,   397,   398,   399,   403,  -934,  -934,  -934,   412,   413,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,   415,   416,   420,
    -934,  -934,  -934,  -934,  -934,   421,  -934,  -934,  -934,  -934,
    -934,  -934,   423,  -934,   424,  -934,    53,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,   425,
    -934,    97,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,   427,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,   107,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
     126,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,   384,   432,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,   418,  -934,  -934,   434,  -934,  -934,  -934,   435,  -934,
    -934,   428,   437,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,   445,   448,  -934,  -934,
    -934,  -934,   433,   451,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,   130,  -934,  -934,  -934,
     452,  -934,  -934,   455,  -934,   461,   462,  -934,  -934,   464,
     465,  -934,  -934,  -934,  -934,  -934,  -934,  -934,   150,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,   466,   159,  -934,  -934,
    -934,  -934,    41,    41,  -934,   262,   467,  -934,   469,   471,
     472,   283,   284,   285,   478,   483,   485,   487,   490,   491,
     303,   306,   307,   308,   311,   313,   317,   318,   321,   314,
     324,   517,   330,   332,   331,   335,   338,   533,   535,   537,
     353,   354,   538,   541,   547,   548,   580,   581,   582,   391,
     392,   393,   588,   589,   590,   591,   592,   407,   593,   598,
     599,   601,   602,   603,   408,   604,  -934,   114,  -934,   605,
     606,   607,   417,    67,  -934,   610,   613,   614,   615,   616,
     617,   429,   618,   620,   621,   240,  -934,   627,     6,  -934,
     628,   629,   632,   634,   635,   636,   637,   638,  -934,   250,
    -934,   639,   640,   453,   641,   642,   644,   458,  -934,    63,
     645,   459,   473,  -934,   300,   663,   664,    -5,  -934,   474,
     676,   677,   488,   679,   492,   493,   684,   685,   498,   499,
     692,   695,   697,   702,   422,  -934,   704,   515,    54,  -934,
    -934,  -934,   706,   707,   709,   710,   711,  -934,  -934,  -934,
     518,   520,   526,   713,   714,   717,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,   545,  -934,  -934,
    -934,  -934,  -934,   123,   546,   549,  -934,  -934,   732,   735,
     736,   738,   737,   552,   186,  -934,  -934,  -934,   741,   742,
     743,   744,   745,  -934,   746,   747,   748,   749,   557,   558,
    -934,   752,  -934,   753,   312,   355,  -934,  -934,   566,   567,
     568,   757,   570,   571,  -934,   753,   572,   759,  -934,   574,
    -934,   753,   577,   578,   579,   583,   584,   585,   586,  -934,
     587,   594,  -934,   595,   596,   597,  -934,  -934,   608,  -934,
    -934,  -934,   609,   737,  -934,  -934,   611,   612,  -934,   619,
    -934,  -934,    33,   622,  -934,  -934,   123,   623,   624,   625,
    -934,   768,  -934,  -934,    41,   114,    54,    67,   750,  -934,
    -934,  -934,   514,   514,   774,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,   775,   776,   777,   779,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,   -45,   784,   785,   787,
      70,   135,   -58,   212,   422,  -934,  -934,   788,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,   789,
    -934,  -934,  -934,  -934,   208,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,   774,  -934,   160,   207,   219,  -934,   220,
    -934,  -934,  -934,  -934,  -934,  -934,   771,   793,   794,   795,
     796,  -934,  -934,  -934,  -934,   799,   802,   803,   804,   805,
     806,  -934,   245,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,   246,  -934,   807,   808,  -934,  -934,
     809,   811,  -934,  -934,   813,   817,  -934,  -934,   815,   819,
    -934,  -934,   818,   820,  -934,  -934,  -934,  -934,  -934,  -934,
      90,  -934,  -934,  -934,  -934,  -934,  -934,  -934,   146,  -934,
    -934,   821,   822,  -934,  -934,   823,   825,  -934,   826,   827,
     828,   829,   830,   831,   249,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,   832,   833,   834,  -934,   256,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,   269,  -934,
    -934,  -934,   835,  -934,   836,  -934,  -934,  -934,   278,  -934,
    -934,  -934,  -934,  -934,   288,  -934,   203,  -934,   633,  -934,
     837,   838,  -934,  -934,  -934,  -934,   839,   840,  -934,  -934,
    -934,   841,   750,  -934,   844,   845,   846,   847,   648,   656,
     650,   657,   660,   851,   852,   853,   854,   665,   666,   667,
     668,   669,   670,   514,  -934,  -934,   514,  -934,   774,   240,
    -934,   775,    63,  -934,   776,   300,  -934,   777,   600,  -934,
     779,   -45,  -934,   297,   784,  -934,   250,  -934,   785,   -85,
    -934,   787,   672,   673,   674,   675,   680,   682,    70,  -934,
     681,   686,   693,   135,  -934,   859,   866,   -58,  -934,   699,
     867,   718,   869,   212,  -934,  -934,    72,   788,  -934,  -934,
     890,   897,     6,  -934,   789,   912,  -934,  -934,   724,  -934,
     377,   740,   751,   758,  -934,  -934,  -934,  -934,  -934,   761,
     812,   814,   824,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
     328,  -934,   346,  -934,   921,  -934,   922,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
     357,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,   932,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,   935,   949,  -934,  -934,  -934,  -934,  -934,   994,
    -934,   370,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,   842,   843,  -934,  -934,   848,  -934,
      41,  -934,  -934,  1004,  -934,  -934,  -934,  -934,  -934,   376,
    -934,  -934,  -934,  -934,  -934,  -934,   849,   388,  -934,   753,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,   600,  -934,  1007,
     816,  -934,   297,  -934,  -934,  -934,  -934,  -934,  -934,  1009,
     850,  1010,    72,  -934,  -934,  -934,  -934,  -934,   856,  -934,
    -934,  1011,  -934,   857,  -934,  -934,  1008,  -934,  -934,   235,
    -934,  -124,  1008,  -934,  -934,  1014,  1015,  1016,  -934,   396,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  1017,   855,   858,
     860,  1018,  -124,  -934,   862,  -934,  -934,  -934,   863,  -934,
    -934,  -934
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   173,     9,   331,    11,   529,    13,
     554,    15,   454,    17,   462,    19,   499,    21,   296,    23,
     660,    25,   710,    27,    45,    39,     0,     0,     0,     0,
       0,   556,     0,   464,   501,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   708,   162,   188,     0,
       0,     0,   575,   577,   579,   186,   195,   197,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   134,
       0,     0,     0,     0,     0,   142,   149,   151,     0,     0,
     323,   452,   491,   403,   542,   544,   396,     0,     0,     0,
     261,   603,   546,   288,   307,     0,   275,   629,   642,   658,
     154,   156,     0,   719,     0,   122,     0,    62,    64,    65,
      66,    67,    68,   102,   103,   104,   105,   106,    69,    97,
      86,    87,    88,   110,   111,   112,   113,   114,   115,   116,
     108,   109,   117,   118,   119,   121,    72,    73,    94,    74,
      75,    76,   120,    80,    81,    70,    99,   100,   101,    98,
      71,    78,    79,    92,    93,    95,    89,    90,    91,    77,
      82,    83,    84,    85,    96,   107,   175,   177,   181,     0,
     172,     0,   164,   166,   167,   168,   169,   170,   171,   381,
     383,   385,   521,   379,   387,     0,   391,   389,   599,   378,
     335,   336,   337,   338,   339,   363,   364,   365,   366,   367,
     353,   354,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,     0,   333,   342,   358,   359,   360,   343,   345,
     346,   349,   350,   351,   348,   344,   340,   341,   361,   362,
     347,   355,   356,   357,   352,   540,   539,   535,   536,   534,
       0,   531,   533,   537,   538,   597,   585,   587,   591,   589,
     595,   593,   581,   574,   568,   572,   573,     0,   557,   558,
     569,   570,   571,   565,   560,   566,   562,   563,   564,   567,
     561,     0,   481,   241,     0,   485,   483,   488,     0,   477,
     478,     0,   465,   466,   468,   480,   469,   470,   471,   487,
     472,   473,   474,   475,   476,   515,     0,     0,   513,   514,
     517,   518,     0,   502,   503,   505,   506,   507,   508,   509,
     510,   511,   512,   303,   305,   300,     0,   298,   301,   302,
       0,   696,   683,     0,   686,     0,     0,   690,   694,     0,
       0,   700,   702,   704,   706,   681,   679,   680,     0,   662,
     664,   665,   666,   667,   668,   669,   670,   671,   676,   672,
     673,   674,   675,   677,   678,   716,     0,     0,   712,   714,
     715,    44,     0,     0,    37,     0,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    55,     0,    61,     0,
       0,     0,     0,     0,   174,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   332,     0,     0,   530,
       0,     0,     0,     0,     0,     0,     0,     0,   555,     0,
     455,     0,     0,     0,     0,     0,     0,     0,   463,     0,
       0,     0,     0,   500,     0,     0,     0,     0,   297,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   661,     0,     0,     0,   711,
      48,    41,     0,     0,     0,     0,     0,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,     0,   159,   160,
     139,   140,   141,     0,     0,     0,   153,   158,     0,     0,
       0,     0,     0,     0,     0,   393,   394,   395,     0,     0,
       0,     0,     0,   628,     0,     0,     0,     0,     0,     0,
     161,     0,    63,     0,     0,     0,   185,   165,     0,     0,
       0,     0,     0,     0,   402,     0,     0,     0,   334,     0,
     532,     0,     0,     0,     0,     0,     0,     0,     0,   559,
       0,     0,   479,     0,     0,     0,   490,   467,     0,   519,
     520,   504,     0,     0,   299,   682,     0,     0,   685,     0,
     688,   689,     0,     0,   698,   699,     0,     0,     0,     0,
     663,     0,   718,   713,     0,     0,     0,     0,     0,   576,
     578,   580,     0,     0,   199,   135,   144,   145,   146,   147,
     148,   143,   150,   152,   325,   456,   493,   405,    38,   543,
     545,   398,   399,   400,   401,   397,     0,     0,   548,   290,
       0,     0,     0,     0,     0,   155,   157,     0,    49,   176,
     179,   180,   178,   183,   184,   182,   382,   384,   386,   523,
     380,   388,   392,   390,     0,   541,   598,   586,   588,   592,
     590,   596,   594,   582,   482,   242,   486,   484,   489,   516,
     304,   306,   697,   684,   687,   692,   693,   691,   695,   701,
     703,   705,   707,   199,    42,     0,     0,     0,   193,     0,
     190,   192,   228,   234,   236,   238,     0,     0,     0,     0,
       0,   250,   252,   254,   256,     0,     0,     0,     0,     0,
       0,   227,     0,   205,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   220,   221,   222,   217,   223,   224,
     225,   218,   219,   226,     0,   203,     0,   200,   201,   329,
       0,   326,   327,   460,     0,   457,   458,   497,     0,   494,
     495,   409,     0,   406,   407,   270,   271,   272,   273,   274,
       0,   263,   265,   266,   267,   268,   269,   607,     0,   605,
     552,     0,   549,   550,   294,     0,   291,   292,     0,     0,
       0,     0,     0,     0,     0,   309,   311,   312,   313,   314,
     315,   316,     0,     0,     0,   284,     0,   277,   279,   280,
     281,   282,   283,   638,   640,   637,   635,   636,     0,   631,
     633,   634,     0,   653,     0,   656,   649,   650,     0,   644,
     646,   647,   648,   651,     0,   723,     0,   721,    51,   527,
       0,   524,   525,   583,   601,   602,     0,     0,    59,   709,
     163,     0,     0,   189,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   187,   196,     0,   198,     0,     0,
     324,     0,   464,   453,     0,   501,   492,     0,     0,   404,
       0,     0,   262,   609,     0,   604,   556,   547,     0,     0,
     289,     0,     0,     0,     0,     0,     0,     0,     0,   308,
       0,     0,     0,     0,   276,     0,     0,     0,   630,     0,
       0,     0,     0,     0,   643,   659,     0,     0,   720,    53,
       0,    52,     0,   522,     0,     0,   600,   717,     0,   191,
       0,     0,     0,     0,   240,   243,   244,   245,   246,     0,
       0,     0,     0,   258,   259,   247,   248,   249,   260,   206,
       0,   202,     0,   328,     0,   459,     0,   496,   451,   431,
     432,   433,   416,   417,   436,   437,   438,   439,   440,   419,
     420,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   413,   414,   415,   429,   430,   426,   427,   428,   425,
       0,   411,   418,   434,   435,   421,   422,   423,   424,   408,
     264,   625,     0,   623,   624,   616,   617,   621,   622,   618,
     619,   620,     0,   610,   611,   613,   614,   615,   606,     0,
     551,     0,   293,   317,   318,   319,   320,   321,   322,   310,
     285,   286,   287,   278,     0,     0,   632,   652,     0,   655,
       0,   645,   737,     0,   735,   733,   727,   731,   732,     0,
     725,   729,   730,   728,   722,    50,     0,     0,   526,     0,
     194,   230,   231,   232,   233,   229,   235,   237,   239,   251,
     253,   255,   257,   204,   330,   461,   498,     0,   410,     0,
       0,   608,     0,   553,   295,   639,   641,   654,   657,     0,
       0,     0,     0,   724,    54,   528,   584,   412,     0,   627,
     612,     0,   734,     0,   726,   626,     0,   736,   741,     0,
     739,     0,     0,   738,   750,     0,     0,     0,   755,     0,
     743,   745,   746,   747,   748,   749,   740,     0,     0,     0,
       0,     0,     0,   742,     0,   752,   753,   754,     0,   744,
     751,   756
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,   -52,  -934,  -551,  -934,   380,
    -934,  -934,  -934,  -934,  -934,  -934,  -591,  -934,  -934,  -934,
     -67,  -934,  -934,  -934,  -934,  -934,  -934,   359,   559,   -40,
     -28,   -24,    -1,     1,    11,    19,    22,    25,    26,  -934,
    -934,  -934,  -934,    29,    30,    32,    37,    40,    43,  -934,
     369,    44,  -934,    45,  -934,    47,    48,  -934,    50,  -934,
      51,  -934,  -934,  -934,  -934,  -934,   361,   554,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,   117,  -934,  -934,  -934,  -934,  -934,
    -934,   277,  -934,    93,  -934,  -660,    99,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,   -63,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
      82,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,    64,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,    73,  -934,  -934,
    -934,    79,   522,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
      75,  -934,  -934,  -934,  -934,  -934,  -934,  -933,  -934,  -934,
    -934,   105,  -934,  -934,  -934,   101,   560,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -927,  -934,   -65,  -934,    56,
    -934,    55,    58,    61,    62,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,   103,  -934,  -934,  -100,   -46,  -934,  -934,  -934,
    -934,  -934,   113,  -934,  -934,  -934,   118,  -934,   550,  -934,
     -42,  -934,  -934,  -934,  -934,  -934,   -36,  -934,  -934,  -934,
    -934,  -934,   -35,  -934,  -934,  -934,   115,  -934,  -934,  -934,
     116,  -934,   551,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,    69,  -934,  -934,  -934,    76,   576,
    -934,  -934,   -51,  -934,   -11,  -934,   -25,  -934,  -934,  -934,
     108,  -934,  -934,  -934,   111,  -934,   573,   -55,  -934,     0,
    -934,     7,  -934,   345,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -921,  -934,  -934,  -934,  -934,  -934,   119,  -934,  -934,
    -934,   -82,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
      94,  -934,  -934,  -934,  -934,  -934,  -934,  -934,    91,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,   371,
     542,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
    -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,  -934,
     411,   540,  -934,  -934,  -934,  -934,  -934,  -934,    92,  -934,
    -934,   -81,  -934,  -934,  -934,  -934,  -934,  -934,   -99,  -934,
    -934,  -116,  -934,  -934,  -934,  -934,  -934,  -934,  -934
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   689,
      82,    83,    39,    64,    79,    80,   709,   898,   990,   991,
     781,    41,    66,    85,   406,    43,    67,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   431,   160,   161,   162,   163,   164,   165,   166,   437,
     681,   167,   438,   168,   439,   169,   170,   462,   171,   463,
     172,   173,   174,   175,   176,   409,   211,   212,    45,    68,
     213,   469,   214,   470,   712,   215,   471,   715,   216,   177,
     417,   178,   410,   759,   760,   761,   911,   179,   418,   180,
     419,   806,   807,   808,   936,   782,   783,   784,   914,  1135,
     785,   915,   786,   916,   787,   917,   788,   789,   502,   790,
     791,   792,   793,   794,   795,   796,   797,   923,   798,   924,
     799,   925,   800,   926,   801,   802,   803,   181,   452,   830,
     831,   832,   833,   834,   835,   836,   182,   458,   866,   867,
     868,   869,   870,   183,   455,   845,   846,   847,   959,    59,
      75,   356,   357,   358,   515,   359,   516,   184,   456,   854,
     855,   856,   857,   858,   859,   860,   861,   185,   442,   810,
     811,   812,   939,    47,    69,   252,   253,   254,   479,   255,
     475,   256,   476,   257,   477,   258,   480,   259,   483,   260,
     482,   186,   187,   188,   189,   448,   695,   265,   190,   445,
     822,   823,   824,   948,  1060,  1061,   191,   443,    53,    72,
     814,   815,   816,   942,    55,    73,   321,   322,   323,   324,
     325,   326,   327,   501,   328,   505,   329,   504,   330,   331,
     506,   332,   192,   444,   818,   819,   820,   945,    57,    74,
     342,   343,   344,   345,   346,   510,   347,   348,   349,   350,
     267,   478,   900,   901,   902,   992,    49,    70,   280,   281,
     282,   487,   193,   446,   194,   447,   195,   454,   841,   842,
     843,   956,    51,    71,   297,   298,   299,   196,   414,   197,
     415,   198,   416,   303,   497,   905,   995,   304,   491,   305,
     492,   306,   494,   307,   493,   308,   496,   309,   495,   310,
     490,   274,   484,   906,   199,   453,   838,   839,   953,  1082,
    1083,  1084,  1085,  1086,  1149,  1087,   200,   201,   459,   878,
     879,   880,   975,   881,   976,   202,   460,   888,   889,   890,
     891,   980,   892,   893,   982,   203,   461,    61,    76,   378,
     379,   380,   381,   521,   382,   383,   523,   384,   385,   386,
     526,   747,   387,   527,   388,   520,   389,   390,   391,   530,
     392,   531,   393,   532,   394,   533,   204,   408,    63,    77,
     397,   398,   399,   536,   400,   205,   465,   896,   897,   986,
    1119,  1120,  1121,  1122,  1161,  1123,  1159,  1179,  1180,  1181,
    1189,  1190,  1191,  1197,  1192,  1193,  1194,  1195,  1201
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     145,   210,   229,   276,   293,   277,   319,   338,   355,   375,
     320,   339,    78,   804,   271,  1052,   300,   217,   268,   283,
     295,  1053,   333,   351,   722,   376,   311,  1068,    28,   230,
     726,   688,   340,    81,   266,   279,   294,    84,   341,   124,
     125,   231,   353,   354,   270,   232,    29,   404,    30,  1184,
      31,   745,  1185,  1186,  1187,  1188,   467,   218,   269,   284,
     296,   468,   334,   352,    40,   377,   395,   396,   233,   272,
     234,   301,   825,   826,   827,   828,   273,   829,   302,   121,
     235,    42,   206,   207,   873,   874,   208,    44,   236,   209,
     122,   237,   688,   951,   238,   239,   952,   312,   240,   241,
     473,   242,   275,   124,   125,   474,   243,    46,   144,   244,
     485,    48,   245,   246,   247,   486,   248,   249,   226,   250,
     251,   227,   353,   354,   261,    86,   278,   262,    87,   488,
     263,   264,    50,   517,   489,   144,    52,    88,   518,    89,
      90,    91,    92,    93,    94,    95,    96,    97,   313,   954,
     314,   315,   955,   534,   316,   317,   318,   313,   535,    54,
     124,   125,   538,   467,   124,   125,   402,   539,   908,   124,
     125,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    56,   746,    58,   121,   122,   144,
     848,   849,   850,   851,   852,   853,   987,    60,   123,   988,
     538,   124,   125,    62,  1052,   909,   126,   127,   128,   129,
    1053,   401,   473,   912,   130,   131,  1068,   910,   913,   403,
     132,   405,   124,   125,    32,    33,    34,    35,  1182,   407,
     133,  1183,   411,   134,  1112,   412,  1113,  1114,   933,   933,
     135,   136,   968,   934,   935,   137,   144,   969,   138,   973,
     144,   413,   139,   420,   974,   144,    90,    91,    92,    93,
      94,   421,   977,   862,   863,   864,  1020,   978,    92,    93,
      94,   983,   140,   141,   142,   143,   984,   676,   677,   678,
     679,   534,   691,   692,   693,   694,   985,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   144,   422,   124,
     125,   112,   113,   114,   115,   116,   117,   118,   119,   680,
     219,   220,   221,   423,   122,    92,    93,    94,   144,   710,
     711,   933,   292,   903,   122,   222,  1143,   124,   125,   223,
     224,   225,   126,   127,   128,   129,   424,   124,   125,   485,
     540,   541,   226,   425,  1144,   227,   132,   882,   883,   884,
    1147,   285,   426,   228,   427,  1148,   428,   286,   287,   288,
     289,   290,   291,   517,   292,   713,   714,   429,  1154,  1162,
     121,   122,   313,   430,  1163,   313,   335,   314,   315,   336,
     337,   488,   498,   432,   124,   125,  1165,   124,   125,  1202,
     145,   433,   434,   435,  1203,   885,   210,   436,   140,   141,
    1071,  1072,  1131,  1132,  1133,  1134,   440,   441,   229,   449,
     450,   276,   217,   277,   451,   457,   500,   464,   466,   472,
     271,   481,   293,   144,   268,   499,   508,   283,   503,   507,
     509,   513,   319,   144,   300,   230,   320,   338,   295,   511,
     266,   339,   512,   279,   514,   542,   519,   231,   333,   522,
     270,   232,   218,   351,   294,   524,   525,   375,   528,   529,
     537,   543,   340,   544,   269,   545,   546,   284,   341,   547,
     548,   549,   550,   376,   233,   272,   234,   551,   296,   552,
     144,   553,   273,   144,   554,   555,   235,   556,   334,   301,
     557,   558,   559,   352,   236,   560,   302,   237,   565,   561,
     238,   239,   562,   563,   240,   241,   564,   242,   566,   124,
     125,   567,   243,   377,   568,   244,   569,   570,   245,   246,
     247,   571,   248,   249,   572,   250,   251,   573,  1166,   574,
     261,   575,   578,   262,   278,   579,   263,   264,   762,   576,
     577,   580,   581,   763,   764,   765,   766,   767,   768,   769,
     770,   771,   772,   773,   774,   775,   776,   777,   778,   779,
     780,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   582,   583,   584,   585,   586,   587,
     373,   374,   588,   589,   590,   591,   592,   594,   145,   313,
     210,   593,   595,   596,   600,   597,   598,   599,   601,   603,
     604,   605,   754,   606,   608,   144,   217,   609,   610,   611,
     612,   613,   615,   614,   616,   617,    90,    91,    92,    93,
      94,   619,   621,   622,   865,   875,   623,   375,   624,   625,
     626,   627,   628,   630,   631,   633,   634,   632,   635,   638,
     871,   876,   886,   376,   636,   639,   218,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   642,   643,   640,
     645,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     646,   647,   648,   649,   122,   313,   650,   651,   652,   653,
     872,   877,   887,   377,   654,   655,   656,   124,   125,   657,
     224,   658,   126,   127,   128,   129,   659,   144,   661,   662,
     664,   669,   226,   670,   665,   227,   666,   667,   668,   671,
     672,   673,   674,   228,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   684,   675,   682,
     685,   686,   683,   687,    30,   690,   696,   697,   698,   699,
     705,   706,   700,   701,   702,   703,   704,   707,   708,   716,
     717,   718,   719,   720,   721,   723,   724,   725,   140,   141,
     727,   728,   729,   753,   758,   918,   730,   731,   732,   733,
     734,   805,   809,   813,   817,   748,   821,   735,   736,   737,
     738,   837,   840,   144,   844,   895,   899,   919,   920,   921,
     922,   739,   740,   927,   742,   743,   928,   929,   930,   931,
     932,   938,   744,   937,   941,   940,   750,   751,   752,   943,
     944,   946,   947,   950,   949,   958,   989,   957,   961,   960,
     962,   963,   964,   965,   966,   967,   970,   971,   972,   979,
     981,   994,  1004,   993,  1006,   998,   997,   996,  1000,  1001,
    1002,  1003,  1005,  1007,  1008,  1009,  1010,  1011,  1012,  1013,
    1014,  1015,  1016,  1104,  1018,  1017,  1093,  1094,  1095,  1096,
    1105,  1108,   229,  1110,  1097,   319,  1098,  1100,   338,   320,
    1101,  1028,   339,  1054,   271,  1051,  1073,  1102,   268,   293,
    1074,   333,   355,  1065,   351,  1107,  1125,  1063,  1079,   230,
    1126,   300,  1077,   340,   266,   295,   865,  1075,  1029,   341,
     875,   231,  1109,  1062,   270,   232,  1129,  1130,  1076,  1115,
    1030,   294,   871,  1116,  1031,   276,   876,   277,   269,  1145,
    1146,   334,   886,  1136,   352,  1117,  1150,  1064,   233,   272,
     234,   283,  1078,  1151,  1137,   296,   273,  1032,  1066,  1033,
     235,  1138,  1152,  1080,  1139,  1067,   301,   279,   236,  1034,
    1081,   237,   872,   302,   238,   239,   877,  1035,   240,   241,
    1036,   242,   887,  1037,  1038,  1118,   243,  1039,  1040,   244,
    1041,   284,   245,   246,   247,  1042,   248,   249,  1043,   250,
     251,  1044,  1045,  1046,   261,  1047,  1048,   262,  1049,  1050,
     263,   264,  1153,  1056,  1055,  1140,  1057,  1141,  1160,  1058,
    1059,  1168,  1169,  1171,  1173,  1178,  1176,  1142,  1198,  1199,
    1200,  1204,  1208,   741,   755,   749,   602,   607,   757,   999,
     907,  1021,  1019,  1070,  1092,  1155,  1156,  1103,  1091,   644,
    1022,  1157,  1164,  1099,  1172,   618,  1023,  1167,   278,  1175,
    1177,  1205,  1206,  1069,  1207,  1210,  1211,  1025,  1158,   637,
    1024,  1026,  1027,  1128,   620,   641,  1090,  1089,  1127,   904,
    1170,  1106,   629,  1088,  1111,   894,   660,   756,   663,  1124,
    1028,  1174,  1054,  1196,  1051,  1073,  1209,     0,     0,  1074,
       0,     0,  1065,     0,     0,  1115,  1063,  1079,     0,  1116,
       0,  1077,     0,     0,     0,     0,  1075,  1029,     0,     0,
       0,  1117,  1062,     0,     0,     0,     0,  1076,     0,  1030,
       0,     0,     0,  1031,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1064,     0,     0,     0,
       0,  1078,     0,     0,     0,     0,  1032,  1066,  1033,     0,
       0,  1118,  1080,     0,  1067,     0,     0,     0,  1034,  1081,
       0,     0,     0,     0,     0,     0,  1035,     0,     0,  1036,
       0,     0,  1037,  1038,     0,     0,  1039,  1040,     0,  1041,
       0,     0,     0,     0,  1042,     0,     0,  1043,     0,     0,
    1044,  1045,  1046,     0,  1047,  1048,     0,  1049,  1050,     0,
       0,     0,  1056,  1055,     0,  1057,     0,     0,  1058,  1059
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   673,    69,   948,    71,    68,    69,    70,
      71,   948,    73,    74,   615,    76,    72,   948,     0,    69,
     621,   582,    74,   193,    69,    70,    71,    10,    74,    97,
      98,    69,   127,   128,    69,    69,     5,     8,     7,   173,
       9,    18,   176,   177,   178,   179,     3,    68,    69,    70,
      71,     8,    73,    74,     7,    76,    12,    13,    69,    69,
      69,    71,   117,   118,   119,   120,    69,   122,    71,    83,
      69,     7,    15,    16,   142,   143,    19,     7,    69,    22,
      84,    69,   643,     3,    69,    69,     6,    34,    69,    69,
       3,    69,    96,    97,    98,     8,    69,     7,   193,    69,
       3,     7,    69,    69,    69,     8,    69,    69,   112,    69,
      69,   115,   127,   128,    69,    11,    70,    69,    14,     3,
      69,    69,     7,     3,     8,   193,     7,    23,     8,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    85,     3,
      87,    88,     6,     3,    91,    92,    93,    85,     8,     7,
      97,    98,     3,     3,    97,    98,     3,     8,     8,    97,
      98,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,     7,   162,     7,    83,    84,   193,
     130,   131,   132,   133,   134,   135,     3,     7,    94,     6,
       3,    97,    98,     7,  1147,     8,   102,   103,   104,   105,
    1147,     6,     3,     3,   110,   111,  1147,     8,     8,     4,
     116,     3,    97,    98,   193,   194,   195,   196,     3,     8,
     126,     6,     4,   129,   172,     4,   174,   175,     3,     3,
     136,   137,     3,     8,     8,   141,   193,     8,   144,     3,
     193,     4,   148,     4,     8,   193,    26,    27,    28,    29,
      30,     4,     3,   138,   139,   140,   936,     8,    28,    29,
      30,     3,   168,   169,   170,   171,     8,   164,   165,   166,
     167,     3,   106,   107,   108,   109,     8,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,   193,     4,    97,
      98,    71,    72,    73,    74,    75,    76,    77,    78,   196,
      80,    81,    82,     4,    84,    28,    29,    30,   193,    17,
      18,     3,   124,   125,    84,    95,     8,    97,    98,    99,
     100,   101,   102,   103,   104,   105,     4,    97,    98,     3,
     402,   403,   112,     4,     8,   115,   116,   145,   146,   147,
       3,   111,     4,   123,     4,     8,     4,   117,   118,   119,
     120,   121,   122,     3,   124,    20,    21,     4,     8,     3,
      83,    84,    85,     4,     8,    85,    86,    87,    88,    89,
      90,     3,     8,     4,    97,    98,     8,    97,    98,     3,
     467,     4,     4,     4,     8,   193,   473,     4,   168,   169,
     113,   114,    35,    36,    37,    38,     4,     4,   485,     4,
       4,   488,   473,   488,     4,     4,     8,     4,     4,     4,
     485,     4,   499,   193,   485,     3,     8,   488,     4,     4,
       3,     8,   509,   193,   499,   485,   509,   514,   499,     4,
     485,   514,     4,   488,     3,   193,     4,   485,   509,     4,
     485,   485,   473,   514,   499,     4,     4,   534,     4,     4,
       4,     4,   514,     4,   485,     4,     4,   488,   514,   196,
     196,   196,     4,   534,   485,   485,   485,     4,   499,     4,
     193,     4,   485,   193,     4,     4,   485,   194,   509,   499,
     194,   194,   194,   514,   485,   194,   499,   485,   194,   196,
     485,   485,   195,   195,   485,   485,   195,   485,   194,    97,
      98,     4,   485,   534,   194,   485,   194,   196,   485,   485,
     485,   196,   485,   485,   196,   485,   485,     4,  1129,     4,
     485,     4,     4,   485,   488,     4,   485,   485,    34,   196,
     196,     4,     4,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,     4,     4,     4,   196,   196,   196,
     168,   169,     4,     4,     4,     4,     4,     4,   665,    85,
     667,   194,     4,     4,   196,     4,     4,     4,     4,     4,
       4,     4,   664,   196,     4,   193,   667,     4,     4,     4,
       4,     4,     4,   194,     4,     4,    26,    27,    28,    29,
      30,     4,     4,     4,   701,   702,     4,   704,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   194,     4,     4,
     701,   702,   703,   704,   196,   196,   667,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,     4,     4,   196,
     196,    71,    72,    73,    74,    75,    76,    77,    78,    79,
       4,     4,   194,     4,    84,    85,   194,   194,     4,     4,
     701,   702,   703,   704,   196,   196,     4,    97,    98,     4,
     100,     4,   102,   103,   104,   105,     4,   193,     4,   194,
       4,   193,   112,   193,     7,   115,     7,     7,     7,   193,
       7,     7,     5,   123,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     5,   193,   193,
       5,     5,   193,     5,     7,   193,     5,     5,     5,     5,
     193,   193,     7,     7,     7,     7,     7,     5,     5,   193,
     193,   193,     5,   193,   193,   193,     7,   193,   168,   169,
     193,   193,   193,     5,    24,     4,   193,   193,   193,   193,
     193,     7,     7,     7,     7,   163,     7,   193,   193,   193,
     193,     7,     7,   193,     7,     7,     7,     4,     4,     4,
       4,   193,   193,     4,   193,   193,     4,     4,     4,     4,
       4,     3,   193,     6,     3,     6,   193,   193,   193,     6,
       3,     6,     3,     3,     6,     3,   193,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   194,     6,   194,     4,     6,     8,     4,     4,
       4,     4,   196,   196,   194,     4,     4,     4,     4,   194,
     194,   194,   194,     4,   194,   196,   194,   194,   194,   194,
       4,     4,   939,     4,   194,   942,   194,   196,   945,   942,
     194,   948,   945,   948,   939,   948,   953,   194,   939,   956,
     953,   942,   959,   948,   945,   196,     6,   948,   953,   939,
       3,   956,   953,   945,   939,   956,   973,   953,   948,   945,
     977,   939,   194,   948,   939,   939,     4,   193,   953,   986,
     948,   956,   973,   986,   948,   992,   977,   992,   939,     8,
       8,   942,   983,   193,   945,   986,     4,   948,   939,   939,
     939,   992,   953,     8,   193,   956,   939,   948,   948,   948,
     939,   193,     3,   953,   193,   948,   956,   992,   939,   948,
     953,   939,   973,   956,   939,   939,   977,   948,   939,   939,
     948,   939,   983,   948,   948,   986,   939,   948,   948,   939,
     948,   992,   939,   939,   939,   948,   939,   939,   948,   939,
     939,   948,   948,   948,   939,   948,   948,   939,   948,   948,
     939,   939,     8,   948,   948,   193,   948,   193,     4,   948,
     948,     4,   196,     4,     4,     7,     5,   193,     4,     4,
       4,     4,     4,   643,   665,   656,   467,   473,   667,   912,
     753,   938,   933,   951,   961,   193,   193,   973,   959,   517,
     939,   193,   193,   968,   194,   485,   941,  1147,   992,   193,
     193,   196,   194,   950,   194,   193,   193,   944,  1110,   509,
     942,   945,   947,   994,   488,   514,   958,   956,   992,   724,
    1152,   977,   499,   954,   983,   704,   534,   666,   538,   987,
    1147,  1162,  1147,  1182,  1147,  1152,  1202,    -1,    -1,  1152,
      -1,    -1,  1147,    -1,    -1,  1162,  1147,  1152,    -1,  1162,
      -1,  1152,    -1,    -1,    -1,    -1,  1152,  1147,    -1,    -1,
      -1,  1162,  1147,    -1,    -1,    -1,    -1,  1152,    -1,  1147,
      -1,    -1,    -1,  1147,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1147,    -1,    -1,    -1,
      -1,  1152,    -1,    -1,    -1,    -1,  1147,  1147,  1147,    -1,
      -1,  1162,  1152,    -1,  1147,    -1,    -1,    -1,  1147,  1152,
      -1,    -1,    -1,    -1,    -1,    -1,  1147,    -1,    -1,  1147,
      -1,    -1,  1147,  1147,    -1,    -1,  1147,  1147,    -1,  1147,
      -1,    -1,    -1,    -1,  1147,    -1,    -1,  1147,    -1,    -1,
    1147,  1147,  1147,    -1,  1147,  1147,    -1,  1147,  1147,    -1,
      -1,    -1,  1147,  1147,    -1,  1147,    -1,    -1,  1147,  1147
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,     0,     5,
       7,     9,   193,   194,   195,   196,   212,   213,   214,   219,
       7,   228,     7,   232,     7,   275,     7,   380,     7,   463,
       7,   479,     7,   415,     7,   421,     7,   445,     7,   356,
       7,   544,     7,   575,   220,   215,   229,   233,   276,   381,
     464,   480,   416,   422,   446,   357,   545,   576,   212,   221,
     222,   193,   217,   218,    10,   230,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    83,    84,    94,    97,    98,   102,   103,   104,   105,
     110,   111,   116,   126,   129,   136,   137,   141,   144,   148,
     168,   169,   170,   171,   193,   227,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     249,   250,   251,   252,   253,   254,   255,   258,   260,   262,
     263,   265,   267,   268,   269,   270,   271,   286,   288,   294,
     296,   334,   343,   350,   364,   374,   398,   399,   400,   401,
     405,   413,   439,   469,   471,   473,   484,   486,   488,   511,
     523,   524,   532,   542,   573,   582,    15,    16,    19,    22,
     227,   273,   274,   277,   279,   282,   285,   469,   471,    80,
      81,    82,    95,    99,   100,   101,   112,   115,   123,   227,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     250,   251,   252,   253,   254,   255,   258,   260,   262,   263,
     265,   267,   382,   383,   384,   386,   388,   390,   392,   394,
     396,   398,   399,   400,   401,   404,   439,   457,   469,   471,
     473,   484,   486,   488,   508,    96,   227,   394,   396,   439,
     465,   466,   467,   469,   471,   111,   117,   118,   119,   120,
     121,   122,   124,   227,   439,   469,   471,   481,   482,   483,
     484,   486,   488,   490,   494,   496,   498,   500,   502,   504,
     506,   413,    34,    85,    87,    88,    91,    92,    93,   227,
     314,   423,   424,   425,   426,   427,   428,   429,   431,   433,
     435,   436,   438,   469,   471,    86,    89,    90,   227,   314,
     427,   433,   447,   448,   449,   450,   451,   453,   454,   455,
     456,   469,   471,   127,   128,   227,   358,   359,   360,   362,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   168,   169,   227,   469,   471,   546,   547,
     548,   549,   551,   552,   554,   555,   556,   559,   561,   563,
     564,   565,   567,   569,   571,    12,    13,   577,   578,   579,
     581,     6,     3,     4,     8,     3,   231,     8,   574,   272,
     289,     4,     4,     4,   485,   487,   489,   287,   295,   297,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   248,     4,     4,     4,     4,     4,   256,   259,   261,
       4,     4,   375,   414,   440,   406,   470,   472,   402,     4,
       4,     4,   335,   512,   474,   351,   365,     4,   344,   525,
     533,   543,   264,   266,     4,   583,     4,     3,     8,   278,
     280,   283,     4,     3,     8,   387,   389,   391,   458,   385,
     393,     4,   397,   395,   509,     3,     8,   468,     3,     8,
     507,   495,   497,   501,   499,   505,   503,   491,     8,     3,
       8,   430,   315,     4,   434,   432,   437,     4,     8,     3,
     452,     4,     4,     8,     3,   361,   363,     3,     8,     4,
     562,   550,     4,   553,     4,     4,   557,   560,     4,     4,
     566,   568,   570,   572,     3,     8,   580,     4,     3,     8,
     212,   212,   193,     4,     4,     4,     4,   196,   196,   196,
       4,     4,     4,     4,     4,     4,   194,   194,   194,   194,
     194,   196,   195,   195,   195,   194,   194,     4,   194,   194,
     196,   196,   196,     4,     4,     4,   196,   196,     4,     4,
       4,     4,     4,     4,     4,   196,   196,   196,     4,     4,
       4,     4,     4,   194,     4,     4,     4,     4,     4,     4,
     196,     4,   235,     4,     4,     4,   196,   274,     4,     4,
       4,     4,     4,     4,   194,     4,     4,     4,   383,     4,
     466,     4,     4,     4,     4,     4,     4,     4,     4,   483,
       4,     4,   194,     4,     4,     4,   196,   425,     4,   196,
     196,   449,     4,     4,   359,   196,     4,     4,   194,     4,
     194,   194,     4,     4,   196,   196,     4,     4,     4,     4,
     547,     4,   194,   578,     4,     7,     7,     7,     7,   193,
     193,   193,     7,     7,     5,   193,   164,   165,   166,   167,
     196,   257,   193,   193,     5,     5,     5,     5,   214,   216,
     193,   106,   107,   108,   109,   403,     5,     5,     5,     5,
       7,     7,     7,     7,     7,   193,   193,     5,     5,   223,
      17,    18,   281,    20,    21,   284,   193,   193,   193,     5,
     193,   193,   223,   193,     7,   193,   223,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   216,   193,   193,   193,    18,   162,   558,   163,   257,
     193,   193,   193,     5,   212,   234,   577,   273,    24,   290,
     291,   292,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   227,   302,   303,   304,   307,   309,   311,   313,   314,
     316,   317,   318,   319,   320,   321,   322,   323,   325,   327,
     329,   331,   332,   333,   302,     7,   298,   299,   300,     7,
     376,   377,   378,     7,   417,   418,   419,     7,   441,   442,
     443,     7,   407,   408,   409,   117,   118,   119,   120,   122,
     336,   337,   338,   339,   340,   341,   342,     7,   513,   514,
       7,   475,   476,   477,     7,   352,   353,   354,   130,   131,
     132,   133,   134,   135,   366,   367,   368,   369,   370,   371,
     372,   373,   138,   139,   140,   227,   345,   346,   347,   348,
     349,   469,   471,   142,   143,   227,   469,   471,   526,   527,
     528,   530,   145,   146,   147,   193,   469,   471,   534,   535,
     536,   537,   539,   540,   546,     7,   584,   585,   224,     7,
     459,   460,   461,   125,   490,   492,   510,   298,     8,     8,
       8,   293,     3,     8,   305,   308,   310,   312,     4,     4,
       4,     4,     4,   324,   326,   328,   330,     4,     4,     4,
       4,     4,     4,     3,     8,     8,   301,     6,     3,   379,
       6,     3,   420,     6,     3,   444,     6,     3,   410,     6,
       3,     3,     6,   515,     3,     6,   478,     6,     3,   355,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   529,   531,     3,     8,     4,
     538,     4,   541,     3,     8,     8,   586,     3,     6,   193,
     225,   226,   462,     6,     3,   493,     8,     6,     4,   291,
       4,     4,     4,     4,   194,   196,   194,   196,   194,     4,
       4,     4,     4,   194,   194,   194,   194,   196,   194,   303,
     302,   300,   382,   378,   423,   419,   447,   443,   227,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   250,
     251,   252,   253,   254,   255,   258,   260,   262,   263,   265,
     267,   314,   374,   392,   394,   396,   398,   399,   400,   401,
     411,   412,   439,   469,   471,   484,   486,   488,   508,   409,
     337,   113,   114,   227,   314,   413,   439,   469,   471,   484,
     486,   488,   516,   517,   518,   519,   520,   522,   514,   481,
     477,   358,   354,   194,   194,   194,   194,   194,   194,   367,
     196,   194,   194,   346,     4,     4,   527,   196,     4,   194,
       4,   535,   172,   174,   175,   227,   314,   469,   471,   587,
     588,   589,   590,   592,   585,     6,     3,   465,   461,     4,
     193,    35,    36,    37,    38,   306,   193,   193,   193,   193,
     193,   193,   193,     8,     8,     8,     8,     3,     8,   521,
       4,     8,     3,     8,     8,   193,   193,   193,   212,   593,
       4,   591,     3,     8,   193,     8,   223,   412,     4,   196,
     518,     4,   194,     4,   588,   193,     5,   193,     7,   594,
     595,   596,     3,     6,   173,   176,   177,   178,   179,   597,
     598,   599,   601,   602,   603,   604,   595,   600,     4,     4,
       4,   605,     3,     8,     4,   196,   194,   194,     4,   598,
     193,   193
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   197,   199,   198,   200,   198,   201,   198,   202,   198,
     203,   198,   204,   198,   205,   198,   206,   198,   207,   198,
     208,   198,   209,   198,   210,   198,   211,   198,   212,   212,
     212,   212,   212,   212,   212,   213,   215,   214,   216,   217,
     217,   218,   218,   220,   219,   221,   221,   222,   222,   224,
     223,   225,   225,   226,   226,   227,   229,   228,   231,   230,
     233,   232,   234,   234,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   248,   247,   249,   250,   251,   252,
     253,   254,   256,   255,   257,   257,   257,   257,   257,   259,
     258,   261,   260,   262,   264,   263,   266,   265,   267,   268,
     269,   270,   272,   271,   273,   273,   274,   274,   274,   274,
     274,   274,   274,   276,   275,   278,   277,   280,   279,   281,
     281,   283,   282,   284,   284,   285,   287,   286,   289,   288,
     290,   290,   291,   293,   292,   295,   294,   297,   296,   298,
     298,   299,   299,   301,   300,   302,   302,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   305,   304,
     306,   306,   306,   306,   308,   307,   310,   309,   312,   311,
     313,   315,   314,   316,   317,   318,   319,   320,   321,   322,
     324,   323,   326,   325,   328,   327,   330,   329,   331,   332,
     333,   335,   334,   336,   336,   337,   337,   337,   337,   337,
     338,   339,   340,   341,   342,   344,   343,   345,   345,   346,
     346,   346,   346,   346,   346,   347,   348,   349,   351,   350,
     352,   352,   353,   353,   355,   354,   357,   356,   358,   358,
     358,   359,   359,   361,   360,   363,   362,   365,   364,   366,
     366,   367,   367,   367,   367,   367,   367,   368,   369,   370,
     371,   372,   373,   375,   374,   376,   376,   377,   377,   379,
     378,   381,   380,   382,   382,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   385,
     384,   387,   386,   389,   388,   391,   390,   393,   392,   395,
     394,   397,   396,   398,   399,   400,   402,   401,   403,   403,
     403,   403,   404,   406,   405,   407,   407,   408,   408,   410,
     409,   411,   411,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   414,   413,   416,   415,   417,   417,   418,   418,
     420,   419,   422,   421,   423,   423,   424,   424,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   426,   427,
     428,   430,   429,   432,   431,   434,   433,   435,   437,   436,
     438,   440,   439,   441,   441,   442,   442,   444,   443,   446,
     445,   447,   447,   448,   448,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   450,   452,   451,   453,   454,   455,
     456,   458,   457,   459,   459,   460,   460,   462,   461,   464,
     463,   465,   465,   466,   466,   466,   466,   466,   466,   466,
     468,   467,   470,   469,   472,   471,   474,   473,   475,   475,
     476,   476,   478,   477,   480,   479,   481,   481,   482,   482,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   485,   484,   487,   486,   489,
     488,   491,   490,   493,   492,   495,   494,   497,   496,   499,
     498,   501,   500,   503,   502,   505,   504,   507,   506,   509,
     508,   510,   510,   512,   511,   513,   513,   515,   514,   516,
     516,   517,   517,   518,   518,   518,   518,   518,   518,   518,
     518,   518,   518,   518,   519,   521,   520,   522,   523,   525,
     524,   526,   526,   527,   527,   527,   527,   527,   529,   528,
     531,   530,   533,   532,   534,   534,   535,   535,   535,   535,
     535,   535,   536,   538,   537,   539,   541,   540,   543,   542,
     545,   544,   546,   546,   547,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   547,   548,   550,   549,   551,   553,   552,   554,   555,
     557,   556,   558,   558,   560,   559,   562,   561,   563,   564,
     566,   565,   568,   567,   570,   569,   572,   571,   574,   573,
     576,   575,   577,   577,   578,   578,   580,   579,   581,   583,
     582,   584,   584,   586,   585,   587,   587,   588,   588,   588,
     588,   588,   588,   588,   589,   591,   590,   593,   592,   594,
     594,   596,   595,   597,   597,   598,   598,   598,   598,   598,
     600,   599,   601,   602,   603,   605,   604
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
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     3,     0,     4,     0,     4,     3,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     1,
       1,     0,     4,     1,     1,     3,     0,     6,     0,     6,
       1,     3,     1,     0,     4,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     0,     4,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     6,     3,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
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
  "\"interface\"", "\"id\"", "\"reservation-mode\"",
  "\"reservations-out-of-pool\"", "\"reservations-in-subnet\"",
  "\"reservations-global\"", "\"disabled\"", "\"out-of-pool\"",
  "\"global\"", "\"all\"", "\"host-reservation-identifiers\"",
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
  "$@62", "require_client_classes", "$@63", "reservations_out_of_pool",
  "reservations_in_subnet", "reservations_global", "reservation_mode",
  "$@64", "hr_mode", "id", "shared_networks", "$@65",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@66", "shared_network_params", "shared_network_param",
  "option_def_list", "$@67", "sub_option_def_list", "$@68",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@69", "sub_option_def", "$@70",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@71",
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
       0,   284,   284,   284,   285,   285,   286,   286,   287,   287,
     288,   288,   289,   289,   290,   290,   291,   291,   292,   292,
     293,   293,   294,   294,   295,   295,   296,   296,   304,   305,
     306,   307,   308,   309,   310,   313,   318,   318,   329,   332,
     333,   336,   341,   349,   349,   356,   357,   360,   364,   371,
     371,   378,   379,   382,   386,   397,   406,   406,   421,   421,
     438,   438,   447,   448,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   514,   520,   526,   532,   538,   544,   550,
     556,   562,   568,   574,   580,   580,   589,   595,   601,   607,
     613,   619,   625,   625,   634,   637,   640,   643,   646,   652,
     652,   661,   661,   670,   676,   676,   685,   685,   694,   700,
     706,   712,   718,   718,   730,   731,   734,   735,   736,   737,
     738,   739,   740,   743,   743,   752,   752,   763,   763,   771,
     772,   775,   775,   783,   785,   789,   796,   796,   809,   809,
     820,   821,   823,   825,   825,   844,   844,   857,   857,   868,
     869,   872,   873,   876,   876,   886,   887,   890,   891,   892,
     893,   894,   895,   896,   897,   898,   899,   900,   901,   902,
     903,   904,   905,   906,   907,   908,   909,   910,   913,   913,
     921,   922,   923,   924,   927,   927,   936,   936,   945,   945,
     954,   960,   960,   969,   975,   981,   987,   993,   999,  1005,
    1011,  1011,  1020,  1020,  1029,  1029,  1038,  1038,  1047,  1053,
    1059,  1066,  1066,  1077,  1078,  1081,  1082,  1083,  1084,  1085,
    1088,  1093,  1098,  1103,  1108,  1115,  1115,  1128,  1129,  1132,
    1133,  1134,  1135,  1136,  1137,  1140,  1146,  1152,  1158,  1158,
    1169,  1170,  1173,  1174,  1177,  1177,  1187,  1187,  1197,  1198,
    1199,  1202,  1203,  1206,  1206,  1215,  1215,  1224,  1224,  1236,
    1237,  1240,  1241,  1242,  1243,  1244,  1245,  1248,  1254,  1260,
    1266,  1272,  1278,  1287,  1287,  1301,  1302,  1305,  1306,  1313,
    1313,  1339,  1339,  1350,  1351,  1355,  1356,  1357,  1358,  1359,
    1360,  1361,  1362,  1363,  1364,  1365,  1366,  1367,  1368,  1369,
    1370,  1371,  1372,  1373,  1374,  1375,  1376,  1377,  1378,  1379,
    1380,  1381,  1382,  1383,  1384,  1385,  1386,  1387,  1388,  1389,
    1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,  1401,
    1401,  1410,  1410,  1419,  1419,  1428,  1428,  1437,  1437,  1446,
    1446,  1455,  1455,  1466,  1472,  1478,  1484,  1484,  1492,  1493,
    1494,  1495,  1498,  1506,  1506,  1518,  1519,  1523,  1524,  1527,
    1527,  1535,  1536,  1539,  1540,  1541,  1542,  1543,  1544,  1545,
    1546,  1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,
    1556,  1557,  1558,  1559,  1560,  1561,  1562,  1563,  1564,  1565,
    1566,  1567,  1568,  1569,  1570,  1571,  1572,  1573,  1574,  1575,
    1576,  1577,  1584,  1584,  1598,  1598,  1607,  1608,  1611,  1612,
    1617,  1617,  1632,  1632,  1646,  1647,  1650,  1651,  1654,  1655,
    1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,  1666,  1668,
    1674,  1676,  1676,  1685,  1685,  1694,  1694,  1703,  1705,  1705,
    1714,  1724,  1724,  1737,  1738,  1743,  1744,  1749,  1749,  1761,
    1761,  1773,  1774,  1779,  1780,  1785,  1786,  1787,  1788,  1789,
    1790,  1791,  1792,  1793,  1796,  1798,  1798,  1807,  1809,  1811,
    1817,  1826,  1826,  1839,  1840,  1843,  1844,  1847,  1847,  1857,
    1857,  1867,  1868,  1871,  1872,  1873,  1874,  1875,  1876,  1877,
    1880,  1880,  1889,  1889,  1914,  1914,  1944,  1944,  1955,  1956,
    1959,  1960,  1963,  1963,  1972,  1972,  1981,  1982,  1985,  1986,
    1990,  1991,  1992,  1993,  1994,  1995,  1996,  1997,  1998,  1999,
    2000,  2001,  2002,  2003,  2004,  2007,  2007,  2016,  2016,  2025,
    2025,  2034,  2034,  2043,  2043,  2054,  2054,  2063,  2063,  2072,
    2072,  2081,  2081,  2090,  2090,  2099,  2099,  2108,  2108,  2122,
    2122,  2133,  2134,  2140,  2140,  2151,  2152,  2155,  2155,  2165,
    2166,  2169,  2170,  2173,  2174,  2175,  2176,  2177,  2178,  2179,
    2180,  2181,  2182,  2183,  2186,  2188,  2188,  2197,  2205,  2213,
    2213,  2224,  2225,  2228,  2229,  2230,  2231,  2232,  2235,  2235,
    2244,  2244,  2256,  2256,  2269,  2270,  2273,  2274,  2275,  2276,
    2277,  2278,  2281,  2287,  2287,  2296,  2302,  2302,  2312,  2312,
    2325,  2325,  2335,  2336,  2339,  2340,  2341,  2342,  2343,  2344,
    2345,  2346,  2347,  2348,  2349,  2350,  2351,  2352,  2353,  2354,
    2355,  2356,  2359,  2365,  2365,  2374,  2380,  2380,  2389,  2395,
    2401,  2401,  2410,  2411,  2414,  2414,  2424,  2424,  2434,  2441,
    2448,  2448,  2457,  2457,  2467,  2467,  2477,  2477,  2489,  2489,
    2501,  2501,  2511,  2512,  2516,  2517,  2520,  2520,  2531,  2539,
    2539,  2552,  2553,  2557,  2557,  2565,  2566,  2569,  2570,  2571,
    2572,  2573,  2574,  2575,  2578,  2584,  2584,  2593,  2593,  2604,
    2605,  2608,  2608,  2616,  2617,  2620,  2621,  2622,  2623,  2624,
    2627,  2627,  2636,  2642,  2648,  2654,  2654
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
#line 5674 "dhcp4_parser.cc"

#line 2663 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
