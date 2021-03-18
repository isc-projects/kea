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
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 276 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 276 "dhcp4_parser.yy"
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
#line 285 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 286 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 287 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 288 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 289 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 774 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 290 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 291 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 786 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 292 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 792 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 293 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 798 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 294 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 804 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 295 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 810 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 296 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 816 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 297 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 822 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 305 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 306 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 307 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 308 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 309 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 310 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 311 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 314 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 873 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 319 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 324 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 894 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 330 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 337 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 342 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 350 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 930 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 353 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 938 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 361 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 365 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 372 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 964 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 374 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 973 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 383 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 387 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 991 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 398 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1002 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 407 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 412 "dhcp4_parser.yy"
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
#line 1041 "dhcp4_parser.cc"
    break;

  case 59: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 431 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 439 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1061 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 443 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1070 "dhcp4_parser.cc"
    break;

  case 124: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 516 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1080 "dhcp4_parser.cc"
    break;

  case 125: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 522 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 126: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 528 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1100 "dhcp4_parser.cc"
    break;

  case 127: // renew_timer: "renew-timer" ":" "integer"
#line 534 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 128: // rebind_timer: "rebind-timer" ":" "integer"
#line 540 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 129: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 546 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 130: // t1_percent: "t1-percent" ":" "floating point"
#line 552 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 131: // t2_percent: "t2-percent" ":" "floating point"
#line 558 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1150 "dhcp4_parser.cc"
    break;

  case 132: // cache_threshold: "cache-threshold" ":" "floating point"
#line 564 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1160 "dhcp4_parser.cc"
    break;

  case 133: // cache_max_age: "cache-max-age" ":" "integer"
#line 570 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1170 "dhcp4_parser.cc"
    break;

  case 134: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 576 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 135: // $@20: %empty
#line 582 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 136: // server_tag: "server-tag" $@20 ":" "constant string"
#line 585 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1199 "dhcp4_parser.cc"
    break;

  case 137: // echo_client_id: "echo-client-id" ":" "boolean"
#line 591 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1209 "dhcp4_parser.cc"
    break;

  case 138: // match_client_id: "match-client-id" ":" "boolean"
#line 597 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1219 "dhcp4_parser.cc"
    break;

  case 139: // authoritative: "authoritative" ":" "boolean"
#line 603 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 140: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 609 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1239 "dhcp4_parser.cc"
    break;

  case 141: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 615 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 142: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 621 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1259 "dhcp4_parser.cc"
    break;

  case 143: // $@21: %empty
#line 627 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 144: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 630 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 145: // ddns_replace_client_name_value: "when-present"
#line 636 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1285 "dhcp4_parser.cc"
    break;

  case 146: // ddns_replace_client_name_value: "never"
#line 639 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1293 "dhcp4_parser.cc"
    break;

  case 147: // ddns_replace_client_name_value: "always"
#line 642 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1301 "dhcp4_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "when-not-present"
#line 645 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1309 "dhcp4_parser.cc"
    break;

  case 149: // ddns_replace_client_name_value: "boolean"
#line 648 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1318 "dhcp4_parser.cc"
    break;

  case 150: // $@22: %empty
#line 654 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "dhcp4_parser.cc"
    break;

  case 151: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 657 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1337 "dhcp4_parser.cc"
    break;

  case 152: // $@23: %empty
#line 663 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 153: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 666 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 154: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 672 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 155: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 678 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1376 "dhcp4_parser.cc"
    break;

  case 156: // $@24: %empty
#line 684 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 157: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 687 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1395 "dhcp4_parser.cc"
    break;

  case 158: // $@25: %empty
#line 693 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1404 "dhcp4_parser.cc"
    break;

  case 159: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 696 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1414 "dhcp4_parser.cc"
    break;

  case 160: // store_extended_info: "store-extended-info" ":" "boolean"
#line 702 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1424 "dhcp4_parser.cc"
    break;

  case 161: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 708 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 162: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 714 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 163: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 720 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1454 "dhcp4_parser.cc"
    break;

  case 164: // $@26: %empty
#line 726 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1466 "dhcp4_parser.cc"
    break;

  case 165: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 732 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1476 "dhcp4_parser.cc"
    break;

  case 175: // $@27: %empty
#line 751 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1486 "dhcp4_parser.cc"
    break;

  case 176: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 755 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 177: // $@28: %empty
#line 760 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1507 "dhcp4_parser.cc"
    break;

  case 178: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 766 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1516 "dhcp4_parser.cc"
    break;

  case 179: // $@29: %empty
#line 771 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 180: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 774 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 181: // socket_type: "raw"
#line 779 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1540 "dhcp4_parser.cc"
    break;

  case 182: // socket_type: "udp"
#line 780 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1546 "dhcp4_parser.cc"
    break;

  case 183: // $@30: %empty
#line 783 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 184: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 786 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 185: // outbound_interface_value: "same-as-inbound"
#line 791 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1572 "dhcp4_parser.cc"
    break;

  case 186: // outbound_interface_value: "use-routing"
#line 793 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1580 "dhcp4_parser.cc"
    break;

  case 187: // re_detect: "re-detect" ":" "boolean"
#line 797 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1590 "dhcp4_parser.cc"
    break;

  case 188: // $@31: %empty
#line 804 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1602 "dhcp4_parser.cc"
    break;

  case 189: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 810 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1613 "dhcp4_parser.cc"
    break;

  case 190: // $@32: %empty
#line 817 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 191: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 823 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 195: // $@33: %empty
#line 833 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1643 "dhcp4_parser.cc"
    break;

  case 196: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 836 "dhcp4_parser.yy"
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
#line 1663 "dhcp4_parser.cc"
    break;

  case 197: // $@34: %empty
#line 852 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1675 "dhcp4_parser.cc"
    break;

  case 198: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 858 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1686 "dhcp4_parser.cc"
    break;

  case 199: // $@35: %empty
#line 865 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1698 "dhcp4_parser.cc"
    break;

  case 200: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 871 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1707 "dhcp4_parser.cc"
    break;

  case 205: // $@36: %empty
#line 884 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 206: // database: "{" $@36 database_map_params "}"
#line 888 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1727 "dhcp4_parser.cc"
    break;

  case 230: // $@37: %empty
#line 921 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1736 "dhcp4_parser.cc"
    break;

  case 231: // database_type: "type" $@37 ":" db_type
#line 924 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1745 "dhcp4_parser.cc"
    break;

  case 232: // db_type: "memfile"
#line 929 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1751 "dhcp4_parser.cc"
    break;

  case 233: // db_type: "mysql"
#line 930 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1757 "dhcp4_parser.cc"
    break;

  case 234: // db_type: "postgresql"
#line 931 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1763 "dhcp4_parser.cc"
    break;

  case 235: // db_type: "cql"
#line 932 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1769 "dhcp4_parser.cc"
    break;

  case 236: // $@38: %empty
#line 935 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1778 "dhcp4_parser.cc"
    break;

  case 237: // user: "user" $@38 ":" "constant string"
#line 938 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1788 "dhcp4_parser.cc"
    break;

  case 238: // $@39: %empty
#line 944 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1797 "dhcp4_parser.cc"
    break;

  case 239: // password: "password" $@39 ":" "constant string"
#line 947 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1807 "dhcp4_parser.cc"
    break;

  case 240: // $@40: %empty
#line 953 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1816 "dhcp4_parser.cc"
    break;

  case 241: // host: "host" $@40 ":" "constant string"
#line 956 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1826 "dhcp4_parser.cc"
    break;

  case 242: // port: "port" ":" "integer"
#line 962 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1836 "dhcp4_parser.cc"
    break;

  case 243: // $@41: %empty
#line 968 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp4_parser.cc"
    break;

  case 244: // name: "name" $@41 ":" "constant string"
#line 971 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1855 "dhcp4_parser.cc"
    break;

  case 245: // persist: "persist" ":" "boolean"
#line 977 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1865 "dhcp4_parser.cc"
    break;

  case 246: // lfc_interval: "lfc-interval" ":" "integer"
#line 983 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1875 "dhcp4_parser.cc"
    break;

  case 247: // readonly: "readonly" ":" "boolean"
#line 989 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1885 "dhcp4_parser.cc"
    break;

  case 248: // connect_timeout: "connect-timeout" ":" "integer"
#line 995 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1895 "dhcp4_parser.cc"
    break;

  case 249: // request_timeout: "request-timeout" ":" "integer"
#line 1001 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1905 "dhcp4_parser.cc"
    break;

  case 250: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1007 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1915 "dhcp4_parser.cc"
    break;

  case 251: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1013 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1925 "dhcp4_parser.cc"
    break;

  case 252: // $@42: %empty
#line 1019 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1934 "dhcp4_parser.cc"
    break;

  case 253: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1022 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1944 "dhcp4_parser.cc"
    break;

  case 254: // $@43: %empty
#line 1028 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 255: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1031 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc"
    break;

  case 256: // $@44: %empty
#line 1037 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 257: // consistency: "consistency" $@44 ":" "constant string"
#line 1040 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 258: // $@45: %empty
#line 1046 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 259: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1049 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 260: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1055 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 261: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1061 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2021 "dhcp4_parser.cc"
    break;

  case 262: // max_row_errors: "max-row-errors" ":" "integer"
#line 1067 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2031 "dhcp4_parser.cc"
    break;

  case 263: // $@46: %empty
#line 1074 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2043 "dhcp4_parser.cc"
    break;

  case 264: // host_reservation_identifiers: "host-reservation-identifiers" $@46 ":" "[" host_reservation_identifiers_list "]"
#line 1080 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2052 "dhcp4_parser.cc"
    break;

  case 272: // duid_id: "duid"
#line 1096 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2061 "dhcp4_parser.cc"
    break;

  case 273: // hw_address_id: "hw-address"
#line 1101 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2070 "dhcp4_parser.cc"
    break;

  case 274: // circuit_id: "circuit-id"
#line 1106 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 275: // client_id: "client-id"
#line 1111 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2088 "dhcp4_parser.cc"
    break;

  case 276: // flex_id: "flex-id"
#line 1116 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2097 "dhcp4_parser.cc"
    break;

  case 277: // $@47: %empty
#line 1123 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 278: // dhcp_multi_threading: "multi-threading" $@47 ":" "{" multi_threading_params "}"
#line 1129 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2120 "dhcp4_parser.cc"
    break;

  case 287: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1148 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2130 "dhcp4_parser.cc"
    break;

  case 288: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1154 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2140 "dhcp4_parser.cc"
    break;

  case 289: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1160 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2150 "dhcp4_parser.cc"
    break;

  case 290: // $@48: %empty
#line 1166 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2162 "dhcp4_parser.cc"
    break;

  case 291: // hooks_libraries: "hooks-libraries" $@48 ":" "[" hooks_libraries_list "]"
#line 1172 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2171 "dhcp4_parser.cc"
    break;

  case 296: // $@49: %empty
#line 1185 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2181 "dhcp4_parser.cc"
    break;

  case 297: // hooks_library: "{" $@49 hooks_params "}"
#line 1189 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2191 "dhcp4_parser.cc"
    break;

  case 298: // $@50: %empty
#line 1195 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2201 "dhcp4_parser.cc"
    break;

  case 299: // sub_hooks_library: "{" $@50 hooks_params "}"
#line 1199 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2211 "dhcp4_parser.cc"
    break;

  case 305: // $@51: %empty
#line 1214 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp4_parser.cc"
    break;

  case 306: // library: "library" $@51 ":" "constant string"
#line 1217 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 307: // $@52: %empty
#line 1223 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc"
    break;

  case 308: // parameters: "parameters" $@52 ":" map_value
#line 1226 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2248 "dhcp4_parser.cc"
    break;

  case 309: // $@53: %empty
#line 1232 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 310: // expired_leases_processing: "expired-leases-processing" $@53 ":" "{" expired_leases_params "}"
#line 1238 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2270 "dhcp4_parser.cc"
    break;

  case 319: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1256 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2280 "dhcp4_parser.cc"
    break;

  case 320: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1262 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2290 "dhcp4_parser.cc"
    break;

  case 321: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1268 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 322: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1274 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 323: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1280 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2320 "dhcp4_parser.cc"
    break;

  case 324: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1286 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2330 "dhcp4_parser.cc"
    break;

  case 325: // $@54: %empty
#line 1295 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2342 "dhcp4_parser.cc"
    break;

  case 326: // subnet4_list: "subnet4" $@54 ":" "[" subnet4_list_content "]"
#line 1301 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 331: // $@55: %empty
#line 1321 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2361 "dhcp4_parser.cc"
    break;

  case 332: // subnet4: "{" $@55 subnet4_params "}"
#line 1325 "dhcp4_parser.yy"
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
#line 2387 "dhcp4_parser.cc"
    break;

  case 333: // $@56: %empty
#line 1347 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2397 "dhcp4_parser.cc"
    break;

  case 334: // sub_subnet4: "{" $@56 subnet4_params "}"
#line 1351 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 382: // $@57: %empty
#line 1410 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2416 "dhcp4_parser.cc"
    break;

  case 383: // subnet: "subnet" $@57 ":" "constant string"
#line 1413 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc"
    break;

  case 384: // $@58: %empty
#line 1419 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 385: // subnet_4o6_interface: "4o6-interface" $@58 ":" "constant string"
#line 1422 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 386: // $@59: %empty
#line 1428 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 387: // subnet_4o6_interface_id: "4o6-interface-id" $@59 ":" "constant string"
#line 1431 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 388: // $@60: %empty
#line 1437 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 389: // subnet_4o6_subnet: "4o6-subnet" $@60 ":" "constant string"
#line 1440 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 390: // $@61: %empty
#line 1446 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 391: // interface: "interface" $@61 ":" "constant string"
#line 1449 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2502 "dhcp4_parser.cc"
    break;

  case 392: // $@62: %empty
#line 1455 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 393: // client_class: "client-class" $@62 ":" "constant string"
#line 1458 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 394: // $@63: %empty
#line 1464 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2533 "dhcp4_parser.cc"
    break;

  case 395: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1470 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2542 "dhcp4_parser.cc"
    break;

  case 396: // reservations_global: "reservations-global" ":" "boolean"
#line 1475 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2552 "dhcp4_parser.cc"
    break;

  case 397: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1481 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2562 "dhcp4_parser.cc"
    break;

  case 398: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1487 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2572 "dhcp4_parser.cc"
    break;

  case 399: // $@64: %empty
#line 1493 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2581 "dhcp4_parser.cc"
    break;

  case 400: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1496 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 401: // hr_mode: "disabled"
#line 1501 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2596 "dhcp4_parser.cc"
    break;

  case 402: // hr_mode: "out-of-pool"
#line 1502 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2602 "dhcp4_parser.cc"
    break;

  case 403: // hr_mode: "global"
#line 1503 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2608 "dhcp4_parser.cc"
    break;

  case 404: // hr_mode: "all"
#line 1504 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2614 "dhcp4_parser.cc"
    break;

  case 405: // id: "id" ":" "integer"
#line 1507 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2624 "dhcp4_parser.cc"
    break;

  case 406: // $@65: %empty
#line 1515 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2636 "dhcp4_parser.cc"
    break;

  case 407: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1521 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2645 "dhcp4_parser.cc"
    break;

  case 412: // $@66: %empty
#line 1536 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2655 "dhcp4_parser.cc"
    break;

  case 413: // shared_network: "{" $@66 shared_network_params "}"
#line 1540 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2663 "dhcp4_parser.cc"
    break;

  case 456: // $@67: %empty
#line 1594 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 457: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1600 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2684 "dhcp4_parser.cc"
    break;

  case 458: // $@68: %empty
#line 1608 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 459: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1611 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2701 "dhcp4_parser.cc"
    break;

  case 464: // $@69: %empty
#line 1627 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2711 "dhcp4_parser.cc"
    break;

  case 465: // option_def_entry: "{" $@69 option_def_params "}"
#line 1631 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2723 "dhcp4_parser.cc"
    break;

  case 466: // $@70: %empty
#line 1642 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2733 "dhcp4_parser.cc"
    break;

  case 467: // sub_option_def: "{" $@70 option_def_params "}"
#line 1646 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2745 "dhcp4_parser.cc"
    break;

  case 483: // code: "code" ":" "integer"
#line 1678 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2755 "dhcp4_parser.cc"
    break;

  case 485: // $@71: %empty
#line 1686 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2764 "dhcp4_parser.cc"
    break;

  case 486: // option_def_type: "type" $@71 ":" "constant string"
#line 1689 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2774 "dhcp4_parser.cc"
    break;

  case 487: // $@72: %empty
#line 1695 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2783 "dhcp4_parser.cc"
    break;

  case 488: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1698 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2793 "dhcp4_parser.cc"
    break;

  case 489: // $@73: %empty
#line 1704 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 490: // space: "space" $@73 ":" "constant string"
#line 1707 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 492: // $@74: %empty
#line 1715 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 493: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1718 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 494: // option_def_array: "array" ":" "boolean"
#line 1724 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2841 "dhcp4_parser.cc"
    break;

  case 495: // $@75: %empty
#line 1734 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2853 "dhcp4_parser.cc"
    break;

  case 496: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1740 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2862 "dhcp4_parser.cc"
    break;

  case 501: // $@76: %empty
#line 1759 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2872 "dhcp4_parser.cc"
    break;

  case 502: // option_data_entry: "{" $@76 option_data_params "}"
#line 1763 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2881 "dhcp4_parser.cc"
    break;

  case 503: // $@77: %empty
#line 1771 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 504: // sub_option_data: "{" $@77 option_data_params "}"
#line 1775 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 519: // $@78: %empty
#line 1808 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 520: // option_data_data: "data" $@78 ":" "constant string"
#line 1811 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2919 "dhcp4_parser.cc"
    break;

  case 523: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1821 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2929 "dhcp4_parser.cc"
    break;

  case 524: // option_data_always_send: "always-send" ":" "boolean"
#line 1827 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2939 "dhcp4_parser.cc"
    break;

  case 525: // $@79: %empty
#line 1836 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 526: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1842 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 531: // $@80: %empty
#line 1857 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 532: // pool_list_entry: "{" $@80 pool_params "}"
#line 1861 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 533: // $@81: %empty
#line 1867 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 534: // sub_pool4: "{" $@81 pool_params "}"
#line 1871 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3000 "dhcp4_parser.cc"
    break;

  case 544: // $@82: %empty
#line 1890 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3009 "dhcp4_parser.cc"
    break;

  case 545: // pool_entry: "pool" $@82 ":" "constant string"
#line 1893 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3019 "dhcp4_parser.cc"
    break;

  case 546: // $@83: %empty
#line 1899 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3027 "dhcp4_parser.cc"
    break;

  case 547: // user_context: "user-context" $@83 ":" map_value
#line 1901 "dhcp4_parser.yy"
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
#line 3054 "dhcp4_parser.cc"
    break;

  case 548: // $@84: %empty
#line 1924 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 549: // comment: "comment" $@84 ":" "constant string"
#line 1926 "dhcp4_parser.yy"
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
#line 3091 "dhcp4_parser.cc"
    break;

  case 550: // $@85: %empty
#line 1954 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3103 "dhcp4_parser.cc"
    break;

  case 551: // reservations: "reservations" $@85 ":" "[" reservations_list "]"
#line 1960 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3112 "dhcp4_parser.cc"
    break;

  case 556: // $@86: %empty
#line 1973 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3122 "dhcp4_parser.cc"
    break;

  case 557: // reservation: "{" $@86 reservation_params "}"
#line 1977 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3131 "dhcp4_parser.cc"
    break;

  case 558: // $@87: %empty
#line 1982 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3141 "dhcp4_parser.cc"
    break;

  case 559: // sub_reservation: "{" $@87 reservation_params "}"
#line 1986 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3150 "dhcp4_parser.cc"
    break;

  case 579: // $@88: %empty
#line 2017 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 580: // next_server: "next-server" $@88 ":" "constant string"
#line 2020 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 581: // $@89: %empty
#line 2026 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 582: // server_hostname: "server-hostname" $@89 ":" "constant string"
#line 2029 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 583: // $@90: %empty
#line 2035 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 584: // boot_file_name: "boot-file-name" $@90 ":" "constant string"
#line 2038 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 585: // $@91: %empty
#line 2044 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 586: // ip_address: "ip-address" $@91 ":" "constant string"
#line 2047 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 587: // $@92: %empty
#line 2053 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3238 "dhcp4_parser.cc"
    break;

  case 588: // ip_addresses: "ip-addresses" $@92 ":" list_strings
#line 2059 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3247 "dhcp4_parser.cc"
    break;

  case 589: // $@93: %empty
#line 2064 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3256 "dhcp4_parser.cc"
    break;

  case 590: // duid: "duid" $@93 ":" "constant string"
#line 2067 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3266 "dhcp4_parser.cc"
    break;

  case 591: // $@94: %empty
#line 2073 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp4_parser.cc"
    break;

  case 592: // hw_address: "hw-address" $@94 ":" "constant string"
#line 2076 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3285 "dhcp4_parser.cc"
    break;

  case 593: // $@95: %empty
#line 2082 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 594: // client_id_value: "client-id" $@95 ":" "constant string"
#line 2085 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3304 "dhcp4_parser.cc"
    break;

  case 595: // $@96: %empty
#line 2091 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3313 "dhcp4_parser.cc"
    break;

  case 596: // circuit_id_value: "circuit-id" $@96 ":" "constant string"
#line 2094 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3323 "dhcp4_parser.cc"
    break;

  case 597: // $@97: %empty
#line 2100 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 598: // flex_id_value: "flex-id" $@97 ":" "constant string"
#line 2103 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 599: // $@98: %empty
#line 2109 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 600: // hostname: "hostname" $@98 ":" "constant string"
#line 2112 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3361 "dhcp4_parser.cc"
    break;

  case 601: // $@99: %empty
#line 2118 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3373 "dhcp4_parser.cc"
    break;

  case 602: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2124 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3382 "dhcp4_parser.cc"
    break;

  case 603: // $@100: %empty
#line 2132 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3394 "dhcp4_parser.cc"
    break;

  case 604: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2138 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 607: // $@101: %empty
#line 2150 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3415 "dhcp4_parser.cc"
    break;

  case 608: // client_classes: "client-classes" $@101 ":" "[" client_classes_list "]"
#line 2156 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3424 "dhcp4_parser.cc"
    break;

  case 611: // $@102: %empty
#line 2165 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3434 "dhcp4_parser.cc"
    break;

  case 612: // client_class_entry: "{" $@102 client_class_params "}"
#line 2169 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3444 "dhcp4_parser.cc"
    break;

  case 632: // $@103: %empty
#line 2201 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 633: // client_class_test: "test" $@103 ":" "constant string"
#line 2204 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 634: // only_if_required: "only-if-required" ":" "boolean"
#line 2210 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 635: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2218 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3483 "dhcp4_parser.cc"
    break;

  case 636: // $@104: %empty
#line 2226 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 637: // control_socket: "control-socket" $@104 ":" "{" control_socket_params "}"
#line 2232 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3504 "dhcp4_parser.cc"
    break;

  case 645: // $@105: %empty
#line 2248 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3513 "dhcp4_parser.cc"
    break;

  case 646: // control_socket_type: "socket-type" $@105 ":" "constant string"
#line 2251 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3523 "dhcp4_parser.cc"
    break;

  case 647: // $@106: %empty
#line 2257 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3532 "dhcp4_parser.cc"
    break;

  case 648: // control_socket_name: "socket-name" $@106 ":" "constant string"
#line 2260 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 649: // $@107: %empty
#line 2269 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 650: // dhcp_queue_control: "dhcp-queue-control" $@107 ":" "{" queue_control_params "}"
#line 2275 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 659: // enable_queue: "enable-queue" ":" "boolean"
#line 2294 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3575 "dhcp4_parser.cc"
    break;

  case 660: // $@108: %empty
#line 2300 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3584 "dhcp4_parser.cc"
    break;

  case 661: // queue_type: "queue-type" $@108 ":" "constant string"
#line 2303 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 662: // capacity: "capacity" ":" "integer"
#line 2309 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3604 "dhcp4_parser.cc"
    break;

  case 663: // $@109: %empty
#line 2315 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3613 "dhcp4_parser.cc"
    break;

  case 664: // arbitrary_map_entry: "constant string" $@109 ":" value
#line 2318 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 665: // $@110: %empty
#line 2325 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3634 "dhcp4_parser.cc"
    break;

  case 666: // dhcp_ddns: "dhcp-ddns" $@110 ":" "{" dhcp_ddns_params "}"
#line 2331 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 667: // $@111: %empty
#line 2338 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3655 "dhcp4_parser.cc"
    break;

  case 668: // sub_dhcp_ddns: "{" $@111 dhcp_ddns_params "}"
#line 2342 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3665 "dhcp4_parser.cc"
    break;

  case 689: // enable_updates: "enable-updates" ":" "boolean"
#line 2372 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3675 "dhcp4_parser.cc"
    break;

  case 690: // $@112: %empty
#line 2378 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3684 "dhcp4_parser.cc"
    break;

  case 691: // server_ip: "server-ip" $@112 ":" "constant string"
#line 2381 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3694 "dhcp4_parser.cc"
    break;

  case 692: // server_port: "server-port" ":" "integer"
#line 2387 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3704 "dhcp4_parser.cc"
    break;

  case 693: // $@113: %empty
#line 2393 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3713 "dhcp4_parser.cc"
    break;

  case 694: // sender_ip: "sender-ip" $@113 ":" "constant string"
#line 2396 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3723 "dhcp4_parser.cc"
    break;

  case 695: // sender_port: "sender-port" ":" "integer"
#line 2402 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 696: // max_queue_size: "max-queue-size" ":" "integer"
#line 2408 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3743 "dhcp4_parser.cc"
    break;

  case 697: // $@114: %empty
#line 2414 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3752 "dhcp4_parser.cc"
    break;

  case 698: // ncr_protocol: "ncr-protocol" $@114 ":" ncr_protocol_value
#line 2417 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 699: // ncr_protocol_value: "udp"
#line 2423 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3767 "dhcp4_parser.cc"
    break;

  case 700: // ncr_protocol_value: "tcp"
#line 2424 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3773 "dhcp4_parser.cc"
    break;

  case 701: // $@115: %empty
#line 2427 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3782 "dhcp4_parser.cc"
    break;

  case 702: // ncr_format: "ncr-format" $@115 ":" "JSON"
#line 2430 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3792 "dhcp4_parser.cc"
    break;

  case 703: // $@116: %empty
#line 2437 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3801 "dhcp4_parser.cc"
    break;

  case 704: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2440 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3811 "dhcp4_parser.cc"
    break;

  case 705: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2447 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3821 "dhcp4_parser.cc"
    break;

  case 706: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2454 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3831 "dhcp4_parser.cc"
    break;

  case 707: // $@117: %empty
#line 2461 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3840 "dhcp4_parser.cc"
    break;

  case 708: // dep_replace_client_name: "replace-client-name" $@117 ":" ddns_replace_client_name_value
#line 2464 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3849 "dhcp4_parser.cc"
    break;

  case 709: // $@118: %empty
#line 2470 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 710: // dep_generated_prefix: "generated-prefix" $@118 ":" "constant string"
#line 2473 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 711: // $@119: %empty
#line 2480 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3877 "dhcp4_parser.cc"
    break;

  case 712: // dep_hostname_char_set: "hostname-char-set" $@119 ":" "constant string"
#line 2483 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3887 "dhcp4_parser.cc"
    break;

  case 713: // $@120: %empty
#line 2490 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3896 "dhcp4_parser.cc"
    break;

  case 714: // dep_hostname_char_replacement: "hostname-char-replacement" $@120 ":" "constant string"
#line 2493 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3906 "dhcp4_parser.cc"
    break;

  case 715: // $@121: %empty
#line 2502 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 716: // config_control: "config-control" $@121 ":" "{" config_control_params "}"
#line 2508 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 717: // $@122: %empty
#line 2514 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3938 "dhcp4_parser.cc"
    break;

  case 718: // sub_config_control: "{" $@122 config_control_params "}"
#line 2518 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3947 "dhcp4_parser.cc"
    break;

  case 723: // $@123: %empty
#line 2533 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3959 "dhcp4_parser.cc"
    break;

  case 724: // config_databases: "config-databases" $@123 ":" "[" database_list "]"
#line 2539 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3968 "dhcp4_parser.cc"
    break;

  case 725: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2544 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3978 "dhcp4_parser.cc"
    break;

  case 726: // $@124: %empty
#line 2552 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3990 "dhcp4_parser.cc"
    break;

  case 727: // loggers: "loggers" $@124 ":" "[" loggers_entries "]"
#line 2558 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3999 "dhcp4_parser.cc"
    break;

  case 730: // $@125: %empty
#line 2570 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4009 "dhcp4_parser.cc"
    break;

  case 731: // logger_entry: "{" $@125 logger_params "}"
#line 2574 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4017 "dhcp4_parser.cc"
    break;

  case 741: // debuglevel: "debuglevel" ":" "integer"
#line 2591 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4027 "dhcp4_parser.cc"
    break;

  case 742: // $@126: %empty
#line 2597 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4036 "dhcp4_parser.cc"
    break;

  case 743: // severity: "severity" $@126 ":" "constant string"
#line 2600 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4046 "dhcp4_parser.cc"
    break;

  case 744: // $@127: %empty
#line 2606 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4058 "dhcp4_parser.cc"
    break;

  case 745: // output_options_list: "output_options" $@127 ":" "[" output_options_list_content "]"
#line 2612 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4067 "dhcp4_parser.cc"
    break;

  case 748: // $@128: %empty
#line 2621 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4077 "dhcp4_parser.cc"
    break;

  case 749: // output_entry: "{" $@128 output_params_list "}"
#line 2625 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4085 "dhcp4_parser.cc"
    break;

  case 757: // $@129: %empty
#line 2640 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4094 "dhcp4_parser.cc"
    break;

  case 758: // output: "output" $@129 ":" "constant string"
#line 2643 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4104 "dhcp4_parser.cc"
    break;

  case 759: // flush: "flush" ":" "boolean"
#line 2649 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 760: // maxsize: "maxsize" ":" "integer"
#line 2655 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 761: // maxver: "maxver" ":" "integer"
#line 2661 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4134 "dhcp4_parser.cc"
    break;

  case 762: // $@130: %empty
#line 2667 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4143 "dhcp4_parser.cc"
    break;

  case 763: // pattern: "pattern" $@130 ":" "constant string"
#line 2670 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4153 "dhcp4_parser.cc"
    break;


#line 4157 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -939;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     398,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,    31,    41,    33,    57,    68,   104,
     126,   154,   157,   161,   174,   184,   194,   198,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,    41,  -161,    27,   220,    67,   605,
      61,    64,   -37,   114,   176,   -86,   226,    54,  -939,    98,
      70,   212,    53,   216,  -939,   215,  -939,  -939,  -939,   221,
     228,   250,  -939,  -939,  -939,  -939,  -939,  -939,   267,   268,
     269,   297,   307,   316,   344,   348,   359,   362,   363,  -939,
     364,   371,   389,   390,   393,  -939,  -939,  -939,   394,   395,
     396,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   397,   399,
     401,  -939,  -939,  -939,  -939,  -939,   402,  -939,  -939,  -939,
    -939,  -939,  -939,   403,  -939,   404,  -939,    69,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   405,  -939,    71,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,   407,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,    97,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,    99,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
     295,   310,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,   337,  -939,  -939,   408,  -939,  -939,
    -939,   409,  -939,  -939,   410,   412,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   413,
     415,  -939,  -939,  -939,  -939,   416,   418,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   115,
    -939,  -939,  -939,   419,  -939,  -939,   424,  -939,   425,   426,
    -939,  -939,   427,   428,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   127,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   429,
     142,  -939,  -939,  -939,  -939,    41,    41,  -939,    35,   431,
    -939,   433,   435,   436,   205,   219,   245,   439,   440,   441,
     443,   449,   452,   263,   264,   265,   274,   275,   266,   276,
     277,   278,   280,   282,   475,   285,   288,   287,   289,   294,
     481,   489,   490,   298,   300,   301,   495,   497,   500,   501,
     502,   505,   508,   317,   320,   323,   509,   512,   518,   520,
     521,   333,   526,   527,   528,   531,   534,   539,   349,   541,
    -939,   220,  -939,   544,   545,   546,   358,    67,  -939,   549,
     553,   555,   556,   588,   589,   400,   590,   592,   593,   605,
    -939,   594,    61,  -939,   595,   596,   597,   598,   600,   602,
     603,   606,  -939,    64,  -939,   607,   608,   414,   609,   610,
     611,   421,  -939,   114,   612,   422,   423,  -939,   176,   618,
     619,    15,  -939,   430,   620,   621,   434,   622,   442,   446,
     624,   626,   447,   448,   632,   634,   639,   642,   226,  -939,
     643,   453,    54,  -939,  -939,  -939,   645,   644,   646,   647,
     652,  -939,  -939,  -939,   456,   458,   466,   665,   666,   669,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   491,  -939,  -939,  -939,  -939,  -939,  -112,   498,   499,
    -939,  -939,  -939,   670,   684,   686,   689,   692,   506,   229,
    -939,  -939,  -939,   697,   704,   705,   707,   710,  -939,   712,
     713,   716,   717,   517,   532,  -939,   720,  -939,   722,   135,
     158,  -939,  -939,   536,   537,   543,   723,   547,   548,  -939,
     722,   550,   731,  -939,   551,  -939,   722,   552,   554,   557,
     558,   559,   560,   561,  -939,   562,   563,  -939,   564,   565,
     566,  -939,  -939,   567,  -939,  -939,  -939,   568,   692,  -939,
    -939,   579,   582,  -939,   599,  -939,  -939,    10,   575,  -939,
    -939,  -112,   601,   604,   614,  -939,   735,  -939,  -939,    41,
     220,    54,    67,   719,  -939,  -939,  -939,   522,   522,   740,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   742,
     743,   780,   781,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   121,   782,   783,   787,   207,    -2,   116,   122,   226,
    -939,  -939,   789,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,   790,  -939,  -939,  -939,  -939,   131,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   740,  -939,
     164,   172,   185,  -939,   187,  -939,  -939,  -939,  -939,  -939,
    -939,   796,   797,   798,   799,   802,  -939,  -939,  -939,  -939,
     806,   807,   808,   809,   813,   814,  -939,   191,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   201,
    -939,   815,   817,  -939,  -939,   818,   820,  -939,  -939,   819,
     823,  -939,  -939,   821,   825,  -939,  -939,   826,   828,  -939,
    -939,  -939,  -939,  -939,  -939,    78,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,    84,  -939,  -939,   827,   831,  -939,  -939,
     829,   833,  -939,   834,   835,   836,   837,   838,   839,   214,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,   840,   841,   842,
    -939,   225,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,   299,  -939,  -939,  -939,   843,  -939,   844,
    -939,  -939,  -939,   306,  -939,  -939,  -939,  -939,  -939,   309,
    -939,   109,  -939,   635,  -939,   845,   846,  -939,  -939,  -939,
    -939,   847,   848,  -939,  -939,  -939,   849,   719,  -939,   852,
     853,   854,   855,   655,   640,   657,   663,   667,   857,   859,
     860,   861,   671,   672,   673,   674,   675,   676,   522,  -939,
    -939,   522,  -939,   740,   605,  -939,   742,   114,  -939,   743,
     176,  -939,   780,   706,  -939,   781,   121,  -939,   112,   782,
    -939,    64,  -939,   783,   -86,  -939,   787,   678,   679,   683,
     687,   690,   726,   207,  -939,   682,   727,   746,    -2,  -939,
     866,   877,   116,  -939,   695,   897,   753,   901,   122,  -939,
    -939,   -47,   789,  -939,  -939,   911,   932,    61,  -939,   790,
     934,  -939,  -939,   755,  -939,   336,   762,   763,   816,  -939,
    -939,  -939,  -939,  -939,   830,   832,   850,   851,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,   318,  -939,   319,  -939,  1004,
    -939,  1005,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,   341,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  1010,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  1009,  1017,  -939,  -939,  -939,  -939,  -939,  1013,  -939,
     343,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,   856,   858,  -939,  -939,   862,  -939,    41,
    -939,  -939,  1018,  -939,  -939,  -939,  -939,  -939,   352,  -939,
    -939,  -939,  -939,  -939,  -939,   863,   353,  -939,   722,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,   706,  -939,  1019,   864,
    -939,   112,  -939,  -939,  -939,  -939,  -939,  -939,  1021,   865,
    1023,   -47,  -939,  -939,  -939,  -939,  -939,   868,  -939,  -939,
    1024,  -939,   870,  -939,  -939,  1025,  -939,  -939,   119,  -939,
     -23,  1025,  -939,  -939,  1026,  1027,  1029,  -939,   356,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  1030,   869,   873,   874,
    1031,   -23,  -939,   871,  -939,  -939,  -939,   876,  -939,  -939,
    -939
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   175,     9,   333,    11,   533,    13,
     558,    15,   458,    17,   466,    19,   503,    21,   298,    23,
     667,    25,   717,    27,    45,    39,     0,     0,     0,     0,
       0,   560,     0,   468,   505,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   715,   164,   190,     0,
       0,     0,   579,   581,   583,   188,   197,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
       0,     0,     0,     0,     0,   143,   150,   152,     0,     0,
       0,   325,   456,   495,   406,   546,   548,   399,     0,     0,
       0,   263,   607,   550,   290,   309,     0,   277,   636,   649,
     665,   156,   158,     0,   726,     0,   123,     0,    62,    64,
      65,    66,    67,    68,   102,   103,   104,   105,   106,    69,
      97,    86,    87,    88,   110,   111,   112,   113,   114,   115,
     116,   117,   108,   109,   118,   119,   120,   122,    72,    73,
      94,    74,    75,    76,   121,    80,    81,    70,    99,   100,
     101,    98,    71,    78,    79,    92,    93,    95,    89,    90,
      91,    77,    82,    83,    84,    85,    96,   107,   177,   179,
     183,     0,   174,     0,   166,   168,   169,   170,   171,   172,
     173,   384,   386,   388,   525,   382,   390,     0,   394,   392,
     603,   381,   337,   338,   339,   340,   341,   365,   366,   367,
     368,   369,   355,   356,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,     0,   335,   344,   360,   361,
     362,   345,   347,   348,   351,   352,   353,   350,   346,   342,
     343,   363,   364,   349,   357,   358,   359,   354,   544,   543,
     539,   540,   538,     0,   535,   537,   541,   542,   601,   589,
     591,   595,   593,   599,   597,   585,   578,   572,   576,   577,
       0,   561,   562,   573,   574,   575,   569,   564,   570,   566,
     567,   568,   571,   565,     0,   485,   243,     0,   489,   487,
     492,     0,   481,   482,     0,   469,   470,   472,   484,   473,
     474,   475,   491,   476,   477,   478,   479,   480,   519,     0,
       0,   517,   518,   521,   522,     0,   506,   507,   509,   510,
     511,   512,   513,   514,   515,   516,   305,   307,   302,     0,
     300,   303,   304,     0,   703,   690,     0,   693,     0,     0,
     697,   701,     0,     0,   707,   709,   711,   713,   688,   686,
     687,     0,   669,   671,   672,   673,   674,   675,   676,   677,
     678,   683,   679,   680,   681,   682,   684,   685,   723,     0,
       0,   719,   721,   722,    44,     0,     0,    37,     0,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,     0,    61,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     334,     0,     0,   534,     0,     0,     0,     0,     0,     0,
       0,     0,   559,     0,   459,     0,     0,     0,     0,     0,
       0,     0,   467,     0,     0,     0,     0,   504,     0,     0,
       0,     0,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   668,
       0,     0,     0,   718,    48,    41,     0,     0,     0,     0,
       0,   137,   138,   139,     0,     0,     0,     0,     0,     0,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,     0,   161,   162,   140,   141,   142,     0,     0,     0,
     154,   155,   160,     0,     0,     0,     0,     0,     0,     0,
     396,   397,   398,     0,     0,     0,     0,     0,   635,     0,
       0,     0,     0,     0,     0,   163,     0,    63,     0,     0,
       0,   187,   167,     0,     0,     0,     0,     0,     0,   405,
       0,     0,     0,   336,     0,   536,     0,     0,     0,     0,
       0,     0,     0,     0,   563,     0,     0,   483,     0,     0,
       0,   494,   471,     0,   523,   524,   508,     0,     0,   301,
     689,     0,     0,   692,     0,   695,   696,     0,     0,   705,
     706,     0,     0,     0,     0,   670,     0,   725,   720,     0,
       0,     0,     0,     0,   580,   582,   584,     0,     0,   201,
     136,   145,   146,   147,   148,   149,   144,   151,   153,   327,
     460,   497,   408,    38,   547,   549,   401,   402,   403,   404,
     400,     0,     0,   552,   292,     0,     0,     0,     0,     0,
     157,   159,     0,    49,   178,   181,   182,   180,   185,   186,
     184,   385,   387,   389,   527,   383,   391,   395,   393,     0,
     545,   602,   590,   592,   596,   594,   600,   598,   586,   486,
     244,   490,   488,   493,   520,   306,   308,   704,   691,   694,
     699,   700,   698,   702,   708,   710,   712,   714,   201,    42,
       0,     0,     0,   195,     0,   192,   194,   230,   236,   238,
     240,     0,     0,     0,     0,     0,   252,   254,   256,   258,
       0,     0,     0,     0,     0,     0,   229,     0,   207,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   222,
     223,   224,   219,   225,   226,   227,   220,   221,   228,     0,
     205,     0,   202,   203,   331,     0,   328,   329,   464,     0,
     461,   462,   501,     0,   498,   499,   412,     0,   409,   410,
     272,   273,   274,   275,   276,     0,   265,   267,   268,   269,
     270,   271,   611,     0,   609,   556,     0,   553,   554,   296,
       0,   293,   294,     0,     0,     0,     0,     0,     0,     0,
     311,   313,   314,   315,   316,   317,   318,     0,     0,     0,
     286,     0,   279,   281,   282,   283,   284,   285,   645,   647,
     644,   642,   643,     0,   638,   640,   641,     0,   660,     0,
     663,   656,   657,     0,   651,   653,   654,   655,   658,     0,
     730,     0,   728,    51,   531,     0,   528,   529,   587,   605,
     606,     0,     0,    59,   716,   165,     0,     0,   191,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   189,
     198,     0,   200,     0,     0,   326,     0,   468,   457,     0,
     505,   496,     0,     0,   407,     0,     0,   264,   613,     0,
     608,   560,   551,     0,     0,   291,     0,     0,     0,     0,
       0,     0,     0,     0,   310,     0,     0,     0,     0,   278,
       0,     0,     0,   637,     0,     0,     0,     0,     0,   650,
     666,     0,     0,   727,    53,     0,    52,     0,   526,     0,
       0,   604,   724,     0,   193,     0,     0,     0,     0,   242,
     245,   246,   247,   248,     0,     0,     0,     0,   260,   261,
     249,   250,   251,   262,   208,     0,   204,     0,   330,     0,
     463,     0,   500,   455,   434,   435,   436,   419,   420,   439,
     440,   441,   442,   443,   422,   423,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   416,   417,   418,
     432,   433,   429,   430,   431,   428,     0,   414,   421,   437,
     438,   424,   425,   426,   427,   411,   266,   632,     0,   627,
     628,   629,   630,   631,   620,   621,   625,   626,   622,   623,
     624,     0,   614,   615,   617,   618,   619,   610,     0,   555,
       0,   295,   319,   320,   321,   322,   323,   324,   312,   287,
     288,   289,   280,     0,     0,   639,   659,     0,   662,     0,
     652,   744,     0,   742,   740,   734,   738,   739,     0,   732,
     736,   737,   735,   729,    50,     0,     0,   530,     0,   196,
     232,   233,   234,   235,   231,   237,   239,   241,   253,   255,
     257,   259,   206,   332,   465,   502,     0,   413,     0,     0,
     612,     0,   557,   297,   646,   648,   661,   664,     0,     0,
       0,     0,   731,    54,   532,   588,   415,     0,   634,   616,
       0,   741,     0,   733,   633,     0,   743,   748,     0,   746,
       0,     0,   745,   757,     0,     0,     0,   762,     0,   750,
     752,   753,   754,   755,   756,   747,     0,     0,     0,     0,
       0,     0,   749,     0,   759,   760,   761,     0,   751,   758,
     763
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,   -52,  -939,  -538,  -939,   380,
    -939,  -939,  -939,  -939,  -939,  -939,  -596,  -939,  -939,  -939,
     -67,  -939,  -939,  -939,  -939,  -939,  -939,   366,   569,   -24,
       1,    11,   -40,   -28,    -1,    19,    22,    26,    29,  -939,
    -939,  -939,  -939,    30,    32,    34,    37,    40,    44,  -939,
     376,    45,  -939,    47,  -939,    48,    50,    51,  -939,    52,
    -939,    55,  -939,  -939,  -939,  -939,  -939,   367,   570,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,   124,  -939,  -939,  -939,  -939,
    -939,  -939,   284,  -939,    95,  -939,  -665,   105,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   -63,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,    90,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
      73,  -939,  -939,  -939,  -939,  -939,  -939,  -939,    82,  -939,
    -939,  -939,    85,   533,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,    80,  -939,  -939,  -939,  -939,  -939,  -939,  -938,  -939,
    -939,  -939,   113,  -939,  -939,  -939,   111,   583,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -932,  -939,   -65,  -939,
      66,  -939,    58,    62,    63,    65,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,   103,  -939,  -939,   -85,   -46,  -939,  -939,
    -939,  -939,  -939,   125,  -939,  -939,  -939,   128,  -939,   571,
    -939,   -42,  -939,  -939,  -939,  -939,  -939,   -36,  -939,  -939,
    -939,  -939,  -939,   -35,  -939,  -939,  -939,   129,  -939,  -939,
    -939,   123,  -939,   572,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,    77,  -939,  -939,  -939,    81,
     585,  -939,  -939,   -51,  -939,   -11,  -939,   -25,  -939,  -939,
    -939,   117,  -939,  -939,  -939,   118,  -939,   580,   -55,  -939,
       0,  -939,     7,  -939,   357,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -926,  -939,  -939,  -939,  -939,  -939,   133,  -939,
    -939,  -939,   -79,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   106,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   107,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
     378,   573,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   432,   576,  -939,  -939,  -939,  -939,  -939,  -939,    93,
    -939,  -939,   -75,  -939,  -939,  -939,  -939,  -939,  -939,   -94,
    -939,  -939,  -111,  -939,  -939,  -939,  -939,  -939,  -939,  -939
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   694,
      82,    83,    39,    64,    79,    80,   714,   903,   995,   996,
     786,    41,    66,    85,   409,    43,    67,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   434,   161,   162,   163,   164,   165,   166,   167,   440,
     686,   168,   441,   169,   442,   170,   171,   172,   466,   173,
     467,   174,   175,   176,   177,   178,   412,   213,   214,    45,
      68,   215,   473,   216,   474,   717,   217,   475,   720,   218,
     179,   420,   180,   413,   764,   765,   766,   916,   181,   421,
     182,   422,   811,   812,   813,   941,   787,   788,   789,   919,
    1144,   790,   920,   791,   921,   792,   922,   793,   794,   506,
     795,   796,   797,   798,   799,   800,   801,   802,   928,   803,
     929,   804,   930,   805,   931,   806,   807,   808,   183,   456,
     835,   836,   837,   838,   839,   840,   841,   184,   462,   871,
     872,   873,   874,   875,   185,   459,   850,   851,   852,   964,
      59,    75,   359,   360,   361,   519,   362,   520,   186,   460,
     859,   860,   861,   862,   863,   864,   865,   866,   187,   446,
     815,   816,   817,   944,    47,    69,   255,   256,   257,   483,
     258,   479,   259,   480,   260,   481,   261,   484,   262,   487,
     263,   486,   188,   189,   190,   191,   452,   700,   268,   192,
     449,   827,   828,   829,   953,  1066,  1067,   193,   447,    53,
      72,   819,   820,   821,   947,    55,    73,   324,   325,   326,
     327,   328,   329,   330,   505,   331,   509,   332,   508,   333,
     334,   510,   335,   194,   448,   823,   824,   825,   950,    57,
      74,   345,   346,   347,   348,   349,   514,   350,   351,   352,
     353,   270,   482,   905,   906,   907,   997,    49,    70,   283,
     284,   285,   491,   195,   450,   196,   451,   197,   458,   846,
     847,   848,   961,    51,    71,   300,   301,   302,   198,   417,
     199,   418,   200,   419,   306,   501,   910,  1000,   307,   495,
     308,   496,   309,   498,   310,   497,   311,   500,   312,   499,
     313,   494,   277,   488,   911,   201,   457,   843,   844,   958,
    1091,  1092,  1093,  1094,  1095,  1158,  1096,   202,   203,   463,
     883,   884,   885,   980,   886,   981,   204,   464,   893,   894,
     895,   896,   985,   897,   898,   987,   205,   465,    61,    76,
     381,   382,   383,   384,   525,   385,   386,   527,   387,   388,
     389,   530,   752,   390,   531,   391,   524,   392,   393,   394,
     534,   395,   535,   396,   536,   397,   537,   206,   411,    63,
      77,   400,   401,   402,   540,   403,   207,   469,   901,   902,
     991,  1128,  1129,  1130,  1131,  1170,  1132,  1168,  1188,  1189,
    1190,  1198,  1199,  1200,  1206,  1201,  1202,  1203,  1204,  1210
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     146,   212,   231,   279,   296,   280,   322,   341,   358,   378,
     323,   342,    78,   809,   274,  1058,   303,   219,   271,   286,
     298,  1059,   336,   354,   727,   379,   314,  1074,   750,   235,
     731,    28,   343,    81,   269,   282,   297,    84,   344,   316,
      40,   236,   356,   357,   273,   232,    29,   122,    30,   693,
      31,   125,   126,   681,   682,   683,   684,   220,   272,   287,
     299,   407,   337,   355,    42,   380,   398,   399,   237,   275,
     233,   304,   471,   405,   477,    44,   276,   472,   305,   478,
     234,   956,   208,   209,   957,   685,   210,   959,   238,   211,
     960,   239,    92,    93,    94,   240,   125,   126,   241,   242,
     489,   243,   492,   244,   404,   490,   245,   493,   145,   246,
     693,    46,   992,   247,   248,   993,   249,   250,   521,   251,
     252,   253,  1191,   522,   254,  1192,  1121,   264,  1122,  1123,
     538,   265,   266,    48,   267,   539,   281,   867,   868,   869,
      92,    93,    94,   356,   357,   542,   123,   145,   315,   123,
     543,  1193,   715,   716,  1194,  1195,  1196,  1197,   278,   125,
     126,    50,   125,   126,    52,   125,   126,   471,    54,    98,
      99,   100,   913,   751,   228,   542,   288,   229,   718,   719,
     914,    56,   289,   290,   291,   292,   293,   294,   477,   295,
     917,    58,   145,   915,   938,   918,   122,   123,   316,   939,
     316,    60,   317,   318,   938,    62,   319,   320,   321,   940,
     125,   126,   125,   126,   125,   126,   406,   973,  1058,   408,
     125,   126,   974,   410,  1059,   414,  1077,  1078,   978,   546,
    1074,    86,   415,   979,    87,    32,    33,    34,    35,   830,
     831,   832,   833,    88,   834,    89,    90,    91,    92,    93,
      94,    95,    96,    97,   416,   145,   295,   908,   145,   878,
     879,   145,   316,   338,   317,   318,   339,   340,   887,   888,
     889,   423,   424,   425,   125,   126,  1025,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   426,   982,   502,   122,   123,   145,   983,   145,   988,
     145,   427,   538,   503,   989,   124,   890,   990,   125,   126,
     428,   938,   489,   127,   125,   126,  1152,  1153,   128,   129,
     130,   131,   132,   696,   697,   698,   699,   133,   853,   854,
     855,   856,   857,   858,  1156,   504,   521,   134,   429,  1157,
     135,  1163,   430,   544,   545,  1171,   492,   136,   137,  1211,
    1172,  1174,   138,   431,  1212,   139,   432,   433,   435,   140,
     145,  1140,  1141,  1142,  1143,   436,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   141,
     142,   143,   144,   437,   438,   376,   377,   439,   443,   444,
     445,   453,   551,   454,   146,   455,   461,   468,   470,   476,
     212,   485,   507,   511,   145,   513,   552,   515,   512,   516,
     145,   518,   231,   523,   517,   279,   219,   280,   526,   528,
     529,   532,   533,   541,   274,   547,   296,   548,   271,   549,
     550,   286,   553,   554,   555,   556,   322,   557,   303,   235,
     323,   341,   298,   558,   269,   342,   559,   282,   560,   561,
     562,   236,   336,   565,   273,   232,   220,   354,   297,   563,
     564,   378,   566,   567,   568,   569,   343,   570,   272,   571,
     572,   287,   344,   573,   574,   577,   575,   379,   237,   275,
     233,   576,   299,   578,   579,   580,   276,   581,   582,   583,
     234,   584,   337,   304,   585,   586,   587,   355,   238,   588,
     305,   239,   589,   593,   590,   240,   594,   591,   241,   242,
     592,   243,   595,   244,   596,   597,   245,   380,   598,   246,
     599,   600,   601,   247,   248,   602,   249,   250,   603,   251,
     252,   253,  1175,   604,   254,   606,   605,   264,   608,   609,
     610,   265,   266,   613,   267,   611,   767,   614,   281,   615,
     616,   768,   769,   770,   771,   772,   773,   774,   775,   776,
     777,   778,   779,   780,   781,   782,   783,   784,   785,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   617,   618,   620,   619,   621,   622,   624,   626,
     627,   628,   629,   146,   630,   212,   631,   632,   316,   637,
     633,   635,   636,   638,   639,   640,   643,   759,   641,   644,
     645,   219,   647,   648,   651,   652,   654,   650,   657,   653,
     658,    90,    91,    92,    93,    94,   661,   655,   662,   870,
     880,   656,   378,   663,   659,   660,   664,   666,   667,   669,
     674,   670,   675,   671,   672,   876,   881,   891,   379,   673,
     676,   220,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   677,   678,   679,   689,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   680,   221,   222,   223,   690,
     123,   691,   687,   688,   692,   877,   882,   892,   380,    30,
     695,   224,   701,   125,   126,   225,   226,   227,   127,   702,
     703,   710,   704,   128,   129,   130,   145,   705,   228,   706,
     707,   229,   133,   708,   709,   712,   711,   713,   724,   230,
     721,   722,    90,    91,    92,    93,    94,   723,   729,   753,
     758,   725,   726,   763,   728,   730,   732,   810,   733,   814,
     818,   734,   735,   736,   737,   738,   739,   740,   741,   742,
     743,   744,   745,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   747,   141,   142,   748,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   822,   826,   842,
     845,   123,   316,   749,   849,   755,   900,   904,   756,   145,
     923,   924,   925,   926,   125,   126,   927,   226,   757,   127,
     932,   933,   934,   935,   128,   129,   130,   936,   937,   228,
     943,   942,   229,   946,   945,   948,   949,   951,   952,   994,
     230,   955,   954,   962,   963,   965,   966,  1010,   967,   968,
     969,   970,   971,   972,   975,   976,   977,   984,   986,   999,
    1009,   998,  1011,  1003,  1002,  1001,  1005,  1006,  1007,  1008,
    1012,  1014,  1013,  1015,  1016,  1017,  1018,  1019,  1020,  1021,
    1113,  1023,  1022,  1102,  1103,   141,   142,   231,  1104,  1109,
     322,  1114,  1105,   341,   323,  1106,  1033,   342,  1060,   274,
    1057,  1079,  1116,   271,   296,  1083,   336,   358,  1071,   354,
     145,  1117,  1069,  1088,   235,  1119,   303,  1086,   343,   269,
     298,   870,  1084,  1037,   344,   880,   236,  1134,  1068,   273,
     232,  1107,  1110,  1085,  1124,  1038,   297,   876,  1125,  1034,
     279,   881,   280,   272,  1080,  1135,   337,   891,  1138,   355,
    1126,  1111,  1070,   237,   275,   233,   286,  1087,  1118,  1139,
     299,   276,  1039,  1072,  1035,   234,  1145,  1146,  1089,  1081,
    1073,   304,   282,   238,  1036,  1090,   239,   877,   305,  1082,
     240,   882,  1040,   241,   242,  1041,   243,   892,   244,  1042,
    1127,   245,  1043,  1044,   246,  1045,   287,  1046,   247,   248,
    1047,   249,   250,  1048,   251,   252,   253,  1049,  1050,   254,
    1051,  1052,   264,  1053,  1054,  1055,   265,   266,  1056,   267,
    1147,  1062,  1154,  1155,  1159,  1063,  1064,  1160,  1065,  1061,
    1161,  1162,  1169,  1177,  1148,  1180,  1149,  1182,   746,  1185,
    1207,  1208,  1187,  1209,  1213,  1217,   760,   754,  1026,   762,
     607,  1004,   912,  1024,  1150,  1151,  1076,   612,  1101,  1100,
    1164,  1112,  1165,  1108,   649,  1027,  1166,  1173,  1075,  1028,
    1181,  1178,  1184,   281,  1186,  1219,  1214,  1167,  1215,  1216,
    1220,  1176,   623,  1031,  1030,  1029,  1137,   625,  1136,  1098,
    1099,  1032,  1179,   634,   642,  1133,   909,   899,  1115,  1033,
     646,  1060,  1097,  1057,  1079,  1120,  1183,  1205,  1083,     0,
    1218,  1071,     0,   761,  1124,  1069,  1088,     0,  1125,     0,
    1086,   665,     0,     0,     0,  1084,  1037,     0,   668,     0,
    1126,  1068,     0,     0,     0,     0,  1085,     0,  1038,     0,
       0,     0,  1034,     0,     0,     0,     0,  1080,     0,     0,
       0,     0,     0,     0,     0,  1070,     0,     0,     0,     0,
    1087,     0,     0,     0,     0,  1039,  1072,  1035,     0,     0,
    1127,  1089,  1081,  1073,     0,     0,     0,  1036,  1090,     0,
       0,     0,  1082,     0,     0,  1040,     0,     0,  1041,     0,
       0,     0,  1042,     0,     0,  1043,  1044,     0,  1045,     0,
    1046,     0,     0,  1047,     0,     0,  1048,     0,     0,     0,
    1049,  1050,     0,  1051,  1052,     0,  1053,  1054,  1055,     0,
       0,  1056,     0,     0,  1062,     0,     0,     0,  1063,  1064,
       0,  1065,  1061
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   678,    69,   953,    71,    68,    69,    70,
      71,   953,    73,    74,   620,    76,    72,   953,    18,    69,
     626,     0,    74,   194,    69,    70,    71,    10,    74,    86,
       7,    69,   128,   129,    69,    69,     5,    84,     7,   587,
       9,    98,    99,   165,   166,   167,   168,    68,    69,    70,
      71,     8,    73,    74,     7,    76,    12,    13,    69,    69,
      69,    71,     3,     3,     3,     7,    69,     8,    71,     8,
      69,     3,    15,    16,     6,   197,    19,     3,    69,    22,
       6,    69,    28,    29,    30,    69,    98,    99,    69,    69,
       3,    69,     3,    69,     6,     8,    69,     8,   194,    69,
     648,     7,     3,    69,    69,     6,    69,    69,     3,    69,
      69,    69,     3,     8,    69,     6,   173,    69,   175,   176,
       3,    69,    69,     7,    69,     8,    70,   139,   140,   141,
      28,    29,    30,   128,   129,     3,    85,   194,    34,    85,
       8,   174,    17,    18,   177,   178,   179,   180,    97,    98,
      99,     7,    98,    99,     7,    98,    99,     3,     7,    57,
      58,    59,     8,   163,   113,     3,   112,   116,    20,    21,
       8,     7,   118,   119,   120,   121,   122,   123,     3,   125,
       3,     7,   194,     8,     3,     8,    84,    85,    86,     8,
      86,     7,    88,    89,     3,     7,    92,    93,    94,     8,
      98,    99,    98,    99,    98,    99,     4,     3,  1156,     3,
      98,    99,     8,     8,  1156,     4,   114,   115,     3,   194,
    1156,    11,     4,     8,    14,   194,   195,   196,   197,   118,
     119,   120,   121,    23,   123,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     4,   194,   125,   126,   194,   143,
     144,   194,    86,    87,    88,    89,    90,    91,   146,   147,
     148,     4,     4,     4,    98,    99,   941,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,     4,     3,     8,    84,    85,   194,     8,   194,     3,
     194,     4,     3,     3,     8,    95,   194,     8,    98,    99,
       4,     3,     3,   103,    98,    99,     8,     8,   108,   109,
     110,   111,   112,   104,   105,   106,   107,   117,   131,   132,
     133,   134,   135,   136,     3,     8,     3,   127,     4,     8,
     130,     8,     4,   405,   406,     3,     3,   137,   138,     3,
       8,     8,   142,     4,     8,   145,     4,     4,     4,   149,
     194,    35,    36,    37,    38,     4,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   169,
     170,   171,   172,     4,     4,   169,   170,     4,     4,     4,
       4,     4,   197,     4,   471,     4,     4,     4,     4,     4,
     477,     4,     4,     4,   194,     3,   197,     4,     8,     4,
     194,     3,   489,     4,     8,   492,   477,   492,     4,     4,
       4,     4,     4,     4,   489,     4,   503,     4,   489,     4,
       4,   492,   197,     4,     4,     4,   513,     4,   503,   489,
     513,   518,   503,     4,   489,   518,     4,   492,   195,   195,
     195,   489,   513,   197,   489,   489,   477,   518,   503,   195,
     195,   538,   196,   196,   196,   195,   518,   195,   489,     4,
     195,   492,   518,   195,   197,     4,   197,   538,   489,   489,
     489,   197,   503,     4,     4,   197,   489,   197,   197,     4,
     489,     4,   513,   503,     4,     4,     4,   518,   489,     4,
     503,   489,     4,     4,   197,   489,     4,   197,   489,   489,
     197,   489,     4,   489,     4,     4,   489,   538,   195,   489,
       4,     4,     4,   489,   489,     4,   489,   489,     4,   489,
     489,   489,  1138,     4,   489,     4,   197,   489,     4,     4,
       4,   489,   489,     4,   489,   197,    34,     4,   492,     4,
       4,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,     4,     4,     4,   195,     4,     4,     4,     4,
       4,     4,     4,   670,     4,   672,     4,     4,    86,   195,
       4,     4,     4,     4,     4,     4,     4,   669,   197,   197,
     197,   672,     4,     4,     4,     4,     4,   197,     4,   195,
       4,    26,    27,    28,    29,    30,     4,   195,     4,   706,
     707,   195,   709,     4,   197,   197,     4,     4,   195,     4,
     194,     7,   194,     7,     7,   706,   707,   708,   709,     7,
     194,   672,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     7,     7,     5,     5,    71,    72,    73,    74,
      75,    76,    77,    78,    79,   194,    81,    82,    83,     5,
      85,     5,   194,   194,     5,   706,   707,   708,   709,     7,
     194,    96,     5,    98,    99,   100,   101,   102,   103,     5,
       5,   194,     5,   108,   109,   110,   194,     7,   113,     7,
       7,   116,   117,     7,     7,     5,   194,     5,     5,   124,
     194,   194,    26,    27,    28,    29,    30,   194,     7,   164,
       5,   194,   194,    24,   194,   194,   194,     7,   194,     7,
       7,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,   194,   169,   170,   194,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     7,     7,     7,
       7,    85,    86,   194,     7,   194,     7,     7,   194,   194,
       4,     4,     4,     4,    98,    99,     4,   101,   194,   103,
       4,     4,     4,     4,   108,   109,   110,     4,     4,   113,
       3,     6,   116,     3,     6,     6,     3,     6,     3,   194,
     124,     3,     6,     6,     3,     6,     3,   197,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     195,     6,   195,     4,     6,     8,     4,     4,     4,     4,
     197,     4,   195,     4,     4,     4,   195,   195,   195,   195,
       4,   195,   197,   195,   195,   169,   170,   944,   195,   197,
     947,     4,   195,   950,   947,   195,   953,   950,   953,   944,
     953,   958,   197,   944,   961,   958,   947,   964,   953,   950,
     194,     4,   953,   958,   944,     4,   961,   958,   950,   944,
     961,   978,   958,   953,   950,   982,   944,     6,   953,   944,
     944,   195,   195,   958,   991,   953,   961,   978,   991,   953,
     997,   982,   997,   944,   958,     3,   947,   988,     4,   950,
     991,   195,   953,   944,   944,   944,   997,   958,   195,   194,
     961,   944,   953,   953,   953,   944,   194,   194,   958,   958,
     953,   961,   997,   944,   953,   958,   944,   978,   961,   958,
     944,   982,   953,   944,   944,   953,   944,   988,   944,   953,
     991,   944,   953,   953,   944,   953,   997,   953,   944,   944,
     953,   944,   944,   953,   944,   944,   944,   953,   953,   944,
     953,   953,   944,   953,   953,   953,   944,   944,   953,   944,
     194,   953,     8,     8,     4,   953,   953,     8,   953,   953,
       3,     8,     4,     4,   194,     4,   194,     4,   648,     5,
       4,     4,     7,     4,     4,     4,   670,   661,   943,   672,
     471,   917,   758,   938,   194,   194,   956,   477,   966,   964,
     194,   978,   194,   973,   521,   944,   194,   194,   955,   946,
     195,   197,   194,   997,   194,   194,   197,  1119,   195,   195,
     194,  1156,   489,   950,   949,   947,   999,   492,   997,   961,
     963,   952,  1161,   503,   513,   992,   729,   709,   982,  1156,
     518,  1156,   959,  1156,  1161,   988,  1171,  1191,  1161,    -1,
    1211,  1156,    -1,   671,  1171,  1156,  1161,    -1,  1171,    -1,
    1161,   538,    -1,    -1,    -1,  1161,  1156,    -1,   542,    -1,
    1171,  1156,    -1,    -1,    -1,    -1,  1161,    -1,  1156,    -1,
      -1,    -1,  1156,    -1,    -1,    -1,    -1,  1161,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1156,    -1,    -1,    -1,    -1,
    1161,    -1,    -1,    -1,    -1,  1156,  1156,  1156,    -1,    -1,
    1171,  1161,  1161,  1156,    -1,    -1,    -1,  1156,  1161,    -1,
      -1,    -1,  1161,    -1,    -1,  1156,    -1,    -1,  1156,    -1,
      -1,    -1,  1156,    -1,    -1,  1156,  1156,    -1,  1156,    -1,
    1156,    -1,    -1,  1156,    -1,    -1,  1156,    -1,    -1,    -1,
    1156,  1156,    -1,  1156,  1156,    -1,  1156,  1156,  1156,    -1,
      -1,  1156,    -1,    -1,  1156,    -1,    -1,    -1,  1156,  1156,
      -1,  1156,  1156
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     5,
       7,     9,   194,   195,   196,   197,   213,   214,   215,   220,
       7,   229,     7,   233,     7,   277,     7,   382,     7,   465,
       7,   481,     7,   417,     7,   423,     7,   447,     7,   358,
       7,   546,     7,   577,   221,   216,   230,   234,   278,   383,
     466,   482,   418,   424,   448,   359,   547,   578,   213,   222,
     223,   194,   218,   219,    10,   231,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    84,    85,    95,    98,    99,   103,   108,   109,
     110,   111,   112,   117,   127,   130,   137,   138,   142,   145,
     149,   169,   170,   171,   172,   194,   228,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   250,   251,   252,   253,   254,   255,   256,   259,   261,
     263,   264,   265,   267,   269,   270,   271,   272,   273,   288,
     290,   296,   298,   336,   345,   352,   366,   376,   400,   401,
     402,   403,   407,   415,   441,   471,   473,   475,   486,   488,
     490,   513,   525,   526,   534,   544,   575,   584,    15,    16,
      19,    22,   228,   275,   276,   279,   281,   284,   287,   471,
     473,    81,    82,    83,    96,   100,   101,   102,   113,   116,
     124,   228,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   251,   252,   253,   254,   255,   256,   259,   261,
     263,   264,   265,   267,   269,   384,   385,   386,   388,   390,
     392,   394,   396,   398,   400,   401,   402,   403,   406,   441,
     459,   471,   473,   475,   486,   488,   490,   510,    97,   228,
     396,   398,   441,   467,   468,   469,   471,   473,   112,   118,
     119,   120,   121,   122,   123,   125,   228,   441,   471,   473,
     483,   484,   485,   486,   488,   490,   492,   496,   498,   500,
     502,   504,   506,   508,   415,    34,    86,    88,    89,    92,
      93,    94,   228,   316,   425,   426,   427,   428,   429,   430,
     431,   433,   435,   437,   438,   440,   471,   473,    87,    90,
      91,   228,   316,   429,   435,   449,   450,   451,   452,   453,
     455,   456,   457,   458,   471,   473,   128,   129,   228,   360,
     361,   362,   364,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   169,   170,   228,   471,
     473,   548,   549,   550,   551,   553,   554,   556,   557,   558,
     561,   563,   565,   566,   567,   569,   571,   573,    12,    13,
     579,   580,   581,   583,     6,     3,     4,     8,     3,   232,
       8,   576,   274,   291,     4,     4,     4,   487,   489,   491,
     289,   297,   299,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   249,     4,     4,     4,     4,     4,
     257,   260,   262,     4,     4,     4,   377,   416,   442,   408,
     472,   474,   404,     4,     4,     4,   337,   514,   476,   353,
     367,     4,   346,   527,   535,   545,   266,   268,     4,   585,
       4,     3,     8,   280,   282,   285,     4,     3,     8,   389,
     391,   393,   460,   387,   395,     4,   399,   397,   511,     3,
       8,   470,     3,     8,   509,   497,   499,   503,   501,   507,
     505,   493,     8,     3,     8,   432,   317,     4,   436,   434,
     439,     4,     8,     3,   454,     4,     4,     8,     3,   363,
     365,     3,     8,     4,   564,   552,     4,   555,     4,     4,
     559,   562,     4,     4,   568,   570,   572,   574,     3,     8,
     582,     4,     3,     8,   213,   213,   194,     4,     4,     4,
       4,   197,   197,   197,     4,     4,     4,     4,     4,     4,
     195,   195,   195,   195,   195,   197,   196,   196,   196,   195,
     195,     4,   195,   195,   197,   197,   197,     4,     4,     4,
     197,   197,   197,     4,     4,     4,     4,     4,     4,     4,
     197,   197,   197,     4,     4,     4,     4,     4,   195,     4,
       4,     4,     4,     4,     4,   197,     4,   236,     4,     4,
       4,   197,   276,     4,     4,     4,     4,     4,     4,   195,
       4,     4,     4,   385,     4,   468,     4,     4,     4,     4,
       4,     4,     4,     4,   485,     4,     4,   195,     4,     4,
       4,   197,   427,     4,   197,   197,   451,     4,     4,   361,
     197,     4,     4,   195,     4,   195,   195,     4,     4,   197,
     197,     4,     4,     4,     4,   549,     4,   195,   580,     4,
       7,     7,     7,     7,   194,   194,   194,     7,     7,     5,
     194,   165,   166,   167,   168,   197,   258,   194,   194,     5,
       5,     5,     5,   215,   217,   194,   104,   105,   106,   107,
     405,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     194,   194,     5,     5,   224,    17,    18,   283,    20,    21,
     286,   194,   194,   194,     5,   194,   194,   224,   194,     7,
     194,   224,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   217,   194,   194,   194,
      18,   163,   560,   164,   258,   194,   194,   194,     5,   213,
     235,   579,   275,    24,   292,   293,   294,    34,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,   228,   304,   305,   306,
     309,   311,   313,   315,   316,   318,   319,   320,   321,   322,
     323,   324,   325,   327,   329,   331,   333,   334,   335,   304,
       7,   300,   301,   302,     7,   378,   379,   380,     7,   419,
     420,   421,     7,   443,   444,   445,     7,   409,   410,   411,
     118,   119,   120,   121,   123,   338,   339,   340,   341,   342,
     343,   344,     7,   515,   516,     7,   477,   478,   479,     7,
     354,   355,   356,   131,   132,   133,   134,   135,   136,   368,
     369,   370,   371,   372,   373,   374,   375,   139,   140,   141,
     228,   347,   348,   349,   350,   351,   471,   473,   143,   144,
     228,   471,   473,   528,   529,   530,   532,   146,   147,   148,
     194,   471,   473,   536,   537,   538,   539,   541,   542,   548,
       7,   586,   587,   225,     7,   461,   462,   463,   126,   492,
     494,   512,   300,     8,     8,     8,   295,     3,     8,   307,
     310,   312,   314,     4,     4,     4,     4,     4,   326,   328,
     330,   332,     4,     4,     4,     4,     4,     4,     3,     8,
       8,   303,     6,     3,   381,     6,     3,   422,     6,     3,
     446,     6,     3,   412,     6,     3,     3,     6,   517,     3,
       6,   480,     6,     3,   357,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     531,   533,     3,     8,     4,   540,     4,   543,     3,     8,
       8,   588,     3,     6,   194,   226,   227,   464,     6,     3,
     495,     8,     6,     4,   293,     4,     4,     4,     4,   195,
     197,   195,   197,   195,     4,     4,     4,     4,   195,   195,
     195,   195,   197,   195,   305,   304,   302,   384,   380,   425,
     421,   449,   445,   228,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   251,   252,   253,   254,   255,   256,
     259,   261,   263,   264,   265,   267,   269,   316,   376,   394,
     396,   398,   400,   401,   402,   403,   413,   414,   441,   471,
     473,   486,   488,   490,   510,   411,   339,   114,   115,   228,
     237,   238,   239,   316,   415,   441,   471,   473,   486,   488,
     490,   518,   519,   520,   521,   522,   524,   516,   483,   479,
     360,   356,   195,   195,   195,   195,   195,   195,   369,   197,
     195,   195,   348,     4,     4,   529,   197,     4,   195,     4,
     537,   173,   175,   176,   228,   316,   471,   473,   589,   590,
     591,   592,   594,   587,     6,     3,   467,   463,     4,   194,
      35,    36,    37,    38,   308,   194,   194,   194,   194,   194,
     194,   194,     8,     8,     8,     8,     3,     8,   523,     4,
       8,     3,     8,     8,   194,   194,   194,   213,   595,     4,
     593,     3,     8,   194,     8,   224,   414,     4,   197,   520,
       4,   195,     4,   590,   194,     5,   194,     7,   596,   597,
     598,     3,     6,   174,   177,   178,   179,   180,   599,   600,
     601,   603,   604,   605,   606,   597,   602,     4,     4,     4,
     607,     3,     8,     4,   197,   195,   195,     4,   600,   194,
     194
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   198,   200,   199,   201,   199,   202,   199,   203,   199,
     204,   199,   205,   199,   206,   199,   207,   199,   208,   199,
     209,   199,   210,   199,   211,   199,   212,   199,   213,   213,
     213,   213,   213,   213,   213,   214,   216,   215,   217,   218,
     218,   219,   219,   221,   220,   222,   222,   223,   223,   225,
     224,   226,   226,   227,   227,   228,   230,   229,   232,   231,
     234,   233,   235,   235,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   249,   248,   250,   251,   252,
     253,   254,   255,   257,   256,   258,   258,   258,   258,   258,
     260,   259,   262,   261,   263,   264,   266,   265,   268,   267,
     269,   270,   271,   272,   274,   273,   275,   275,   276,   276,
     276,   276,   276,   276,   276,   278,   277,   280,   279,   282,
     281,   283,   283,   285,   284,   286,   286,   287,   289,   288,
     291,   290,   292,   292,   293,   295,   294,   297,   296,   299,
     298,   300,   300,   301,   301,   303,   302,   304,   304,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     307,   306,   308,   308,   308,   308,   310,   309,   312,   311,
     314,   313,   315,   317,   316,   318,   319,   320,   321,   322,
     323,   324,   326,   325,   328,   327,   330,   329,   332,   331,
     333,   334,   335,   337,   336,   338,   338,   339,   339,   339,
     339,   339,   340,   341,   342,   343,   344,   346,   345,   347,
     347,   348,   348,   348,   348,   348,   348,   349,   350,   351,
     353,   352,   354,   354,   355,   355,   357,   356,   359,   358,
     360,   360,   360,   361,   361,   363,   362,   365,   364,   367,
     366,   368,   368,   369,   369,   369,   369,   369,   369,   370,
     371,   372,   373,   374,   375,   377,   376,   378,   378,   379,
     379,   381,   380,   383,   382,   384,   384,   385,   385,   385,
     385,   385,   385,   385,   385,   385,   385,   385,   385,   385,
     385,   385,   385,   385,   385,   385,   385,   385,   385,   385,
     385,   385,   385,   385,   385,   385,   385,   385,   385,   385,
     385,   385,   385,   385,   385,   385,   385,   385,   385,   385,
     385,   385,   387,   386,   389,   388,   391,   390,   393,   392,
     395,   394,   397,   396,   399,   398,   400,   401,   402,   404,
     403,   405,   405,   405,   405,   406,   408,   407,   409,   409,
     410,   410,   412,   411,   413,   413,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   416,   415,   418,   417,
     419,   419,   420,   420,   422,   421,   424,   423,   425,   425,
     426,   426,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   428,   429,   430,   432,   431,   434,   433,   436,
     435,   437,   439,   438,   440,   442,   441,   443,   443,   444,
     444,   446,   445,   448,   447,   449,   449,   450,   450,   451,
     451,   451,   451,   451,   451,   451,   451,   451,   452,   454,
     453,   455,   456,   457,   458,   460,   459,   461,   461,   462,
     462,   464,   463,   466,   465,   467,   467,   468,   468,   468,
     468,   468,   468,   468,   470,   469,   472,   471,   474,   473,
     476,   475,   477,   477,   478,   478,   480,   479,   482,   481,
     483,   483,   484,   484,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   487,
     486,   489,   488,   491,   490,   493,   492,   495,   494,   497,
     496,   499,   498,   501,   500,   503,   502,   505,   504,   507,
     506,   509,   508,   511,   510,   512,   512,   514,   513,   515,
     515,   517,   516,   518,   518,   519,   519,   520,   520,   520,
     520,   520,   520,   520,   520,   520,   520,   520,   520,   520,
     520,   521,   523,   522,   524,   525,   527,   526,   528,   528,
     529,   529,   529,   529,   529,   531,   530,   533,   532,   535,
     534,   536,   536,   537,   537,   537,   537,   537,   537,   538,
     540,   539,   541,   543,   542,   545,   544,   547,   546,   548,
     548,   549,   549,   549,   549,   549,   549,   549,   549,   549,
     549,   549,   549,   549,   549,   549,   549,   549,   549,   550,
     552,   551,   553,   555,   554,   556,   557,   559,   558,   560,
     560,   562,   561,   564,   563,   565,   566,   568,   567,   570,
     569,   572,   571,   574,   573,   576,   575,   578,   577,   579,
     579,   580,   580,   582,   581,   583,   585,   584,   586,   586,
     588,   587,   589,   589,   590,   590,   590,   590,   590,   590,
     590,   591,   593,   592,   595,   594,   596,   596,   598,   597,
     599,   599,   600,   600,   600,   600,   600,   602,   601,   603,
     604,   605,   607,   606
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
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     1,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     0,     6,     3,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4
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
  "$@62", "require_client_classes", "$@63", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
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
       0,   285,   285,   285,   286,   286,   287,   287,   288,   288,
     289,   289,   290,   290,   291,   291,   292,   292,   293,   293,
     294,   294,   295,   295,   296,   296,   297,   297,   305,   306,
     307,   308,   309,   310,   311,   314,   319,   319,   330,   333,
     334,   337,   342,   350,   350,   357,   358,   361,   365,   372,
     372,   379,   380,   383,   387,   398,   407,   407,   422,   422,
     439,   439,   448,   449,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   516,   522,   528,   534,   540,   546,
     552,   558,   564,   570,   576,   582,   582,   591,   597,   603,
     609,   615,   621,   627,   627,   636,   639,   642,   645,   648,
     654,   654,   663,   663,   672,   678,   684,   684,   693,   693,
     702,   708,   714,   720,   726,   726,   738,   739,   742,   743,
     744,   745,   746,   747,   748,   751,   751,   760,   760,   771,
     771,   779,   780,   783,   783,   791,   793,   797,   804,   804,
     817,   817,   828,   829,   831,   833,   833,   852,   852,   865,
     865,   876,   877,   880,   881,   884,   884,   894,   895,   898,
     899,   900,   901,   902,   903,   904,   905,   906,   907,   908,
     909,   910,   911,   912,   913,   914,   915,   916,   917,   918,
     921,   921,   929,   930,   931,   932,   935,   935,   944,   944,
     953,   953,   962,   968,   968,   977,   983,   989,   995,  1001,
    1007,  1013,  1019,  1019,  1028,  1028,  1037,  1037,  1046,  1046,
    1055,  1061,  1067,  1074,  1074,  1085,  1086,  1089,  1090,  1091,
    1092,  1093,  1096,  1101,  1106,  1111,  1116,  1123,  1123,  1136,
    1137,  1140,  1141,  1142,  1143,  1144,  1145,  1148,  1154,  1160,
    1166,  1166,  1177,  1178,  1181,  1182,  1185,  1185,  1195,  1195,
    1205,  1206,  1207,  1210,  1211,  1214,  1214,  1223,  1223,  1232,
    1232,  1244,  1245,  1248,  1249,  1250,  1251,  1252,  1253,  1256,
    1262,  1268,  1274,  1280,  1286,  1295,  1295,  1309,  1310,  1313,
    1314,  1321,  1321,  1347,  1347,  1358,  1359,  1363,  1364,  1365,
    1366,  1367,  1368,  1369,  1370,  1371,  1372,  1373,  1374,  1375,
    1376,  1377,  1378,  1379,  1380,  1381,  1382,  1383,  1384,  1385,
    1386,  1387,  1388,  1389,  1390,  1391,  1392,  1393,  1394,  1395,
    1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,
    1406,  1407,  1410,  1410,  1419,  1419,  1428,  1428,  1437,  1437,
    1446,  1446,  1455,  1455,  1464,  1464,  1475,  1481,  1487,  1493,
    1493,  1501,  1502,  1503,  1504,  1507,  1515,  1515,  1527,  1528,
    1532,  1533,  1536,  1536,  1544,  1545,  1548,  1549,  1550,  1551,
    1552,  1553,  1554,  1555,  1556,  1557,  1558,  1559,  1560,  1561,
    1562,  1563,  1564,  1565,  1566,  1567,  1568,  1569,  1570,  1571,
    1572,  1573,  1574,  1575,  1576,  1577,  1578,  1579,  1580,  1581,
    1582,  1583,  1584,  1585,  1586,  1587,  1594,  1594,  1608,  1608,
    1617,  1618,  1621,  1622,  1627,  1627,  1642,  1642,  1656,  1657,
    1660,  1661,  1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,
    1672,  1673,  1676,  1678,  1684,  1686,  1686,  1695,  1695,  1704,
    1704,  1713,  1715,  1715,  1724,  1734,  1734,  1747,  1748,  1753,
    1754,  1759,  1759,  1771,  1771,  1783,  1784,  1789,  1790,  1795,
    1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1806,  1808,
    1808,  1817,  1819,  1821,  1827,  1836,  1836,  1849,  1850,  1853,
    1854,  1857,  1857,  1867,  1867,  1877,  1878,  1881,  1882,  1883,
    1884,  1885,  1886,  1887,  1890,  1890,  1899,  1899,  1924,  1924,
    1954,  1954,  1965,  1966,  1969,  1970,  1973,  1973,  1982,  1982,
    1991,  1992,  1995,  1996,  2000,  2001,  2002,  2003,  2004,  2005,
    2006,  2007,  2008,  2009,  2010,  2011,  2012,  2013,  2014,  2017,
    2017,  2026,  2026,  2035,  2035,  2044,  2044,  2053,  2053,  2064,
    2064,  2073,  2073,  2082,  2082,  2091,  2091,  2100,  2100,  2109,
    2109,  2118,  2118,  2132,  2132,  2143,  2144,  2150,  2150,  2161,
    2162,  2165,  2165,  2175,  2176,  2179,  2180,  2183,  2184,  2185,
    2186,  2187,  2188,  2189,  2190,  2191,  2192,  2193,  2194,  2195,
    2196,  2199,  2201,  2201,  2210,  2218,  2226,  2226,  2237,  2238,
    2241,  2242,  2243,  2244,  2245,  2248,  2248,  2257,  2257,  2269,
    2269,  2282,  2283,  2286,  2287,  2288,  2289,  2290,  2291,  2294,
    2300,  2300,  2309,  2315,  2315,  2325,  2325,  2338,  2338,  2348,
    2349,  2352,  2353,  2354,  2355,  2356,  2357,  2358,  2359,  2360,
    2361,  2362,  2363,  2364,  2365,  2366,  2367,  2368,  2369,  2372,
    2378,  2378,  2387,  2393,  2393,  2402,  2408,  2414,  2414,  2423,
    2424,  2427,  2427,  2437,  2437,  2447,  2454,  2461,  2461,  2470,
    2470,  2480,  2480,  2490,  2490,  2502,  2502,  2514,  2514,  2524,
    2525,  2529,  2530,  2533,  2533,  2544,  2552,  2552,  2565,  2566,
    2570,  2570,  2578,  2579,  2582,  2583,  2584,  2585,  2586,  2587,
    2588,  2591,  2597,  2597,  2606,  2606,  2617,  2618,  2621,  2621,
    2629,  2630,  2633,  2634,  2635,  2636,  2637,  2640,  2640,  2649,
    2655,  2661,  2667,  2667
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
#line 5694 "dhcp4_parser.cc"

#line 2676 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
