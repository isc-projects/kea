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
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 268 "dhcp4_parser.yy"
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
#line 277 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 278 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 279 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 280 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 281 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 774 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 282 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 283 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 786 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 284 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 792 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 285 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 798 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 286 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 804 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 287 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 810 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 288 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 816 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 289 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 822 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 297 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 298 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 299 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 300 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 301 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 302 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 303 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 306 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 873 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 311 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 316 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 894 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 322 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 329 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 334 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 342 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 930 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 345 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 938 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 353 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 357 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 364 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 964 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 366 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 973 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 375 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 379 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 991 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 390 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1002 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 399 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 404 "dhcp4_parser.yy"
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
#line 414 "dhcp4_parser.yy"
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
#line 423 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 431 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1061 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 435 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1070 "dhcp4_parser.cc"
    break;

  case 116: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 500 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1080 "dhcp4_parser.cc"
    break;

  case 117: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 506 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 118: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 512 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1100 "dhcp4_parser.cc"
    break;

  case 119: // renew_timer: "renew-timer" ":" "integer"
#line 518 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 120: // rebind_timer: "rebind-timer" ":" "integer"
#line 524 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 121: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 530 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 122: // t1_percent: "t1-percent" ":" "floating point"
#line 536 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 123: // t2_percent: "t2-percent" ":" "floating point"
#line 542 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1150 "dhcp4_parser.cc"
    break;

  case 124: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 548 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1160 "dhcp4_parser.cc"
    break;

  case 125: // $@20: %empty
#line 554 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1169 "dhcp4_parser.cc"
    break;

  case 126: // server_tag: "server-tag" $@20 ":" "constant string"
#line 557 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1179 "dhcp4_parser.cc"
    break;

  case 127: // echo_client_id: "echo-client-id" ":" "boolean"
#line 563 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 128: // match_client_id: "match-client-id" ":" "boolean"
#line 569 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1199 "dhcp4_parser.cc"
    break;

  case 129: // authoritative: "authoritative" ":" "boolean"
#line 575 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1209 "dhcp4_parser.cc"
    break;

  case 130: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 581 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1219 "dhcp4_parser.cc"
    break;

  case 131: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 587 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 132: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 593 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1239 "dhcp4_parser.cc"
    break;

  case 133: // $@21: %empty
#line 599 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1248 "dhcp4_parser.cc"
    break;

  case 134: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 602 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1257 "dhcp4_parser.cc"
    break;

  case 135: // ddns_replace_client_name_value: "when-present"
#line 608 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1265 "dhcp4_parser.cc"
    break;

  case 136: // ddns_replace_client_name_value: "never"
#line 611 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1273 "dhcp4_parser.cc"
    break;

  case 137: // ddns_replace_client_name_value: "always"
#line 614 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1281 "dhcp4_parser.cc"
    break;

  case 138: // ddns_replace_client_name_value: "when-not-present"
#line 617 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1289 "dhcp4_parser.cc"
    break;

  case 139: // ddns_replace_client_name_value: "boolean"
#line 620 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1298 "dhcp4_parser.cc"
    break;

  case 140: // $@22: %empty
#line 626 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1307 "dhcp4_parser.cc"
    break;

  case 141: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 629 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1317 "dhcp4_parser.cc"
    break;

  case 142: // $@23: %empty
#line 635 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 143: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 638 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1336 "dhcp4_parser.cc"
    break;

  case 144: // $@24: %empty
#line 644 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 145: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 647 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 146: // $@25: %empty
#line 653 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 147: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 656 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1374 "dhcp4_parser.cc"
    break;

  case 148: // store_extended_info: "store-extended-info" ":" "boolean"
#line 662 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1384 "dhcp4_parser.cc"
    break;

  case 149: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 668 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 150: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 674 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1404 "dhcp4_parser.cc"
    break;

  case 151: // $@26: %empty
#line 680 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1416 "dhcp4_parser.cc"
    break;

  case 152: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 686 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 162: // $@27: %empty
#line 705 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 163: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 709 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1445 "dhcp4_parser.cc"
    break;

  case 164: // $@28: %empty
#line 714 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1457 "dhcp4_parser.cc"
    break;

  case 165: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 720 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1466 "dhcp4_parser.cc"
    break;

  case 166: // $@29: %empty
#line 725 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 167: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 728 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 168: // socket_type: "raw"
#line 733 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1490 "dhcp4_parser.cc"
    break;

  case 169: // socket_type: "udp"
#line 734 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1496 "dhcp4_parser.cc"
    break;

  case 170: // $@30: %empty
#line 737 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 171: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 740 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 172: // outbound_interface_value: "same-as-inbound"
#line 745 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1522 "dhcp4_parser.cc"
    break;

  case 173: // outbound_interface_value: "use-routing"
#line 747 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1530 "dhcp4_parser.cc"
    break;

  case 174: // re_detect: "re-detect" ":" "boolean"
#line 751 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1540 "dhcp4_parser.cc"
    break;

  case 175: // $@31: %empty
#line 758 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1552 "dhcp4_parser.cc"
    break;

  case 176: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 764 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1563 "dhcp4_parser.cc"
    break;

  case 177: // $@32: %empty
#line 771 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 178: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 777 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 182: // $@33: %empty
#line 787 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1593 "dhcp4_parser.cc"
    break;

  case 183: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 790 "dhcp4_parser.yy"
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
#line 1613 "dhcp4_parser.cc"
    break;

  case 184: // $@34: %empty
#line 806 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 185: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 812 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc"
    break;

  case 186: // $@35: %empty
#line 819 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1648 "dhcp4_parser.cc"
    break;

  case 187: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 825 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc"
    break;

  case 192: // $@36: %empty
#line 838 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1667 "dhcp4_parser.cc"
    break;

  case 193: // database: "{" $@36 database_map_params "}"
#line 842 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1677 "dhcp4_parser.cc"
    break;

  case 217: // $@37: %empty
#line 875 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1686 "dhcp4_parser.cc"
    break;

  case 218: // database_type: "type" $@37 ":" db_type
#line 878 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1695 "dhcp4_parser.cc"
    break;

  case 219: // db_type: "memfile"
#line 883 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1701 "dhcp4_parser.cc"
    break;

  case 220: // db_type: "mysql"
#line 884 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1707 "dhcp4_parser.cc"
    break;

  case 221: // db_type: "postgresql"
#line 885 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1713 "dhcp4_parser.cc"
    break;

  case 222: // db_type: "cql"
#line 886 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1719 "dhcp4_parser.cc"
    break;

  case 223: // $@38: %empty
#line 889 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 224: // user: "user" $@38 ":" "constant string"
#line 892 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 225: // $@39: %empty
#line 898 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1747 "dhcp4_parser.cc"
    break;

  case 226: // password: "password" $@39 ":" "constant string"
#line 901 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1757 "dhcp4_parser.cc"
    break;

  case 227: // $@40: %empty
#line 907 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "dhcp4_parser.cc"
    break;

  case 228: // host: "host" $@40 ":" "constant string"
#line 910 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1776 "dhcp4_parser.cc"
    break;

  case 229: // port: "port" ":" "integer"
#line 916 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1786 "dhcp4_parser.cc"
    break;

  case 230: // $@41: %empty
#line 922 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1795 "dhcp4_parser.cc"
    break;

  case 231: // name: "name" $@41 ":" "constant string"
#line 925 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1805 "dhcp4_parser.cc"
    break;

  case 232: // persist: "persist" ":" "boolean"
#line 931 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1815 "dhcp4_parser.cc"
    break;

  case 233: // lfc_interval: "lfc-interval" ":" "integer"
#line 937 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1825 "dhcp4_parser.cc"
    break;

  case 234: // readonly: "readonly" ":" "boolean"
#line 943 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1835 "dhcp4_parser.cc"
    break;

  case 235: // connect_timeout: "connect-timeout" ":" "integer"
#line 949 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1845 "dhcp4_parser.cc"
    break;

  case 236: // request_timeout: "request-timeout" ":" "integer"
#line 955 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1855 "dhcp4_parser.cc"
    break;

  case 237: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 961 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1865 "dhcp4_parser.cc"
    break;

  case 238: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 967 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1875 "dhcp4_parser.cc"
    break;

  case 239: // $@42: %empty
#line 973 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1884 "dhcp4_parser.cc"
    break;

  case 240: // contact_points: "contact-points" $@42 ":" "constant string"
#line 976 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1894 "dhcp4_parser.cc"
    break;

  case 241: // $@43: %empty
#line 982 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1903 "dhcp4_parser.cc"
    break;

  case 242: // keyspace: "keyspace" $@43 ":" "constant string"
#line 985 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1913 "dhcp4_parser.cc"
    break;

  case 243: // $@44: %empty
#line 991 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1922 "dhcp4_parser.cc"
    break;

  case 244: // consistency: "consistency" $@44 ":" "constant string"
#line 994 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1932 "dhcp4_parser.cc"
    break;

  case 245: // $@45: %empty
#line 1000 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc"
    break;

  case 246: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1003 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc"
    break;

  case 247: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1009 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1961 "dhcp4_parser.cc"
    break;

  case 248: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1015 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 249: // max_row_errors: "max-row-errors" ":" "integer"
#line 1021 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 250: // $@46: %empty
#line 1028 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1993 "dhcp4_parser.cc"
    break;

  case 251: // host_reservation_identifiers: "host-reservation-identifiers" $@46 ":" "[" host_reservation_identifiers_list "]"
#line 1034 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2002 "dhcp4_parser.cc"
    break;

  case 259: // duid_id: "duid"
#line 1050 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 260: // hw_address_id: "hw-address"
#line 1055 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 261: // circuit_id: "circuit-id"
#line 1060 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2029 "dhcp4_parser.cc"
    break;

  case 262: // client_id: "client-id"
#line 1065 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2038 "dhcp4_parser.cc"
    break;

  case 263: // flex_id: "flex-id"
#line 1070 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2047 "dhcp4_parser.cc"
    break;

  case 264: // $@47: %empty
#line 1077 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 265: // dhcp_multi_threading: "multi-threading" $@47 ":" "{" multi_threading_params "}"
#line 1083 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2070 "dhcp4_parser.cc"
    break;

  case 274: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1102 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2080 "dhcp4_parser.cc"
    break;

  case 275: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1108 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2090 "dhcp4_parser.cc"
    break;

  case 276: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1114 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 277: // $@48: %empty
#line 1120 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2112 "dhcp4_parser.cc"
    break;

  case 278: // hooks_libraries: "hooks-libraries" $@48 ":" "[" hooks_libraries_list "]"
#line 1126 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2121 "dhcp4_parser.cc"
    break;

  case 283: // $@49: %empty
#line 1139 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2131 "dhcp4_parser.cc"
    break;

  case 284: // hooks_library: "{" $@49 hooks_params "}"
#line 1143 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2141 "dhcp4_parser.cc"
    break;

  case 285: // $@50: %empty
#line 1149 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2151 "dhcp4_parser.cc"
    break;

  case 286: // sub_hooks_library: "{" $@50 hooks_params "}"
#line 1153 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2161 "dhcp4_parser.cc"
    break;

  case 292: // $@51: %empty
#line 1168 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2170 "dhcp4_parser.cc"
    break;

  case 293: // library: "library" $@51 ":" "constant string"
#line 1171 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2180 "dhcp4_parser.cc"
    break;

  case 294: // $@52: %empty
#line 1177 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2189 "dhcp4_parser.cc"
    break;

  case 295: // parameters: "parameters" $@52 ":" map_value
#line 1180 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2198 "dhcp4_parser.cc"
    break;

  case 296: // $@53: %empty
#line 1186 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2210 "dhcp4_parser.cc"
    break;

  case 297: // expired_leases_processing: "expired-leases-processing" $@53 ":" "{" expired_leases_params "}"
#line 1192 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2220 "dhcp4_parser.cc"
    break;

  case 306: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1210 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 307: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1216 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2240 "dhcp4_parser.cc"
    break;

  case 308: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1222 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2250 "dhcp4_parser.cc"
    break;

  case 309: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1228 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 310: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1234 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2270 "dhcp4_parser.cc"
    break;

  case 311: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1240 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2280 "dhcp4_parser.cc"
    break;

  case 312: // $@54: %empty
#line 1249 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2292 "dhcp4_parser.cc"
    break;

  case 313: // subnet4_list: "subnet4" $@54 ":" "[" subnet4_list_content "]"
#line 1255 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 318: // $@55: %empty
#line 1275 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2311 "dhcp4_parser.cc"
    break;

  case 319: // subnet4: "{" $@55 subnet4_params "}"
#line 1279 "dhcp4_parser.yy"
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
#line 2337 "dhcp4_parser.cc"
    break;

  case 320: // $@56: %empty
#line 1301 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 321: // sub_subnet4: "{" $@56 subnet4_params "}"
#line 1305 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 362: // $@57: %empty
#line 1357 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 363: // subnet: "subnet" $@57 ":" "constant string"
#line 1360 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 364: // $@58: %empty
#line 1366 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 365: // subnet_4o6_interface: "4o6-interface" $@58 ":" "constant string"
#line 1369 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 366: // $@59: %empty
#line 1375 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2404 "dhcp4_parser.cc"
    break;

  case 367: // subnet_4o6_interface_id: "4o6-interface-id" $@59 ":" "constant string"
#line 1378 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2414 "dhcp4_parser.cc"
    break;

  case 368: // $@60: %empty
#line 1384 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2423 "dhcp4_parser.cc"
    break;

  case 369: // subnet_4o6_subnet: "4o6-subnet" $@60 ":" "constant string"
#line 1387 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2433 "dhcp4_parser.cc"
    break;

  case 370: // $@61: %empty
#line 1393 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp4_parser.cc"
    break;

  case 371: // interface: "interface" $@61 ":" "constant string"
#line 1396 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2452 "dhcp4_parser.cc"
    break;

  case 372: // $@62: %empty
#line 1402 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp4_parser.cc"
    break;

  case 373: // client_class: "client-class" $@62 ":" "constant string"
#line 1405 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2471 "dhcp4_parser.cc"
    break;

  case 374: // $@63: %empty
#line 1411 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 375: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1417 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 376: // $@64: %empty
#line 1422 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 377: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1425 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 378: // hr_mode: "disabled"
#line 1430 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2516 "dhcp4_parser.cc"
    break;

  case 379: // hr_mode: "out-of-pool"
#line 1431 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2522 "dhcp4_parser.cc"
    break;

  case 380: // hr_mode: "global"
#line 1432 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2528 "dhcp4_parser.cc"
    break;

  case 381: // hr_mode: "all"
#line 1433 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2534 "dhcp4_parser.cc"
    break;

  case 382: // id: "id" ":" "integer"
#line 1436 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2544 "dhcp4_parser.cc"
    break;

  case 383: // $@65: %empty
#line 1444 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2556 "dhcp4_parser.cc"
    break;

  case 384: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1450 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 389: // $@66: %empty
#line 1465 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2575 "dhcp4_parser.cc"
    break;

  case 390: // shared_network: "{" $@66 shared_network_params "}"
#line 1469 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2583 "dhcp4_parser.cc"
    break;

  case 426: // $@67: %empty
#line 1516 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 427: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1522 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2604 "dhcp4_parser.cc"
    break;

  case 428: // $@68: %empty
#line 1530 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2613 "dhcp4_parser.cc"
    break;

  case 429: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1533 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2621 "dhcp4_parser.cc"
    break;

  case 434: // $@69: %empty
#line 1549 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2631 "dhcp4_parser.cc"
    break;

  case 435: // option_def_entry: "{" $@69 option_def_params "}"
#line 1553 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2643 "dhcp4_parser.cc"
    break;

  case 436: // $@70: %empty
#line 1564 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 437: // sub_option_def: "{" $@70 option_def_params "}"
#line 1568 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2665 "dhcp4_parser.cc"
    break;

  case 453: // code: "code" ":" "integer"
#line 1600 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 455: // $@71: %empty
#line 1608 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2684 "dhcp4_parser.cc"
    break;

  case 456: // option_def_type: "type" $@71 ":" "constant string"
#line 1611 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2694 "dhcp4_parser.cc"
    break;

  case 457: // $@72: %empty
#line 1617 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2703 "dhcp4_parser.cc"
    break;

  case 458: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1620 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2713 "dhcp4_parser.cc"
    break;

  case 459: // $@73: %empty
#line 1626 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 460: // space: "space" $@73 ":" "constant string"
#line 1629 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 462: // $@74: %empty
#line 1637 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp4_parser.cc"
    break;

  case 463: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1640 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2751 "dhcp4_parser.cc"
    break;

  case 464: // option_def_array: "array" ":" "boolean"
#line 1646 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2761 "dhcp4_parser.cc"
    break;

  case 465: // $@75: %empty
#line 1656 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2773 "dhcp4_parser.cc"
    break;

  case 466: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1662 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2782 "dhcp4_parser.cc"
    break;

  case 471: // $@76: %empty
#line 1681 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 472: // option_data_entry: "{" $@76 option_data_params "}"
#line 1685 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 473: // $@77: %empty
#line 1693 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2811 "dhcp4_parser.cc"
    break;

  case 474: // sub_option_data: "{" $@77 option_data_params "}"
#line 1697 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2820 "dhcp4_parser.cc"
    break;

  case 489: // $@78: %empty
#line 1730 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp4_parser.cc"
    break;

  case 490: // option_data_data: "data" $@78 ":" "constant string"
#line 1733 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2839 "dhcp4_parser.cc"
    break;

  case 493: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1743 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2849 "dhcp4_parser.cc"
    break;

  case 494: // option_data_always_send: "always-send" ":" "boolean"
#line 1749 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 495: // $@79: %empty
#line 1758 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 496: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1764 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2880 "dhcp4_parser.cc"
    break;

  case 501: // $@80: %empty
#line 1779 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 502: // pool_list_entry: "{" $@80 pool_params "}"
#line 1783 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 503: // $@81: %empty
#line 1789 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2910 "dhcp4_parser.cc"
    break;

  case 504: // sub_pool4: "{" $@81 pool_params "}"
#line 1793 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 514: // $@82: %empty
#line 1812 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2929 "dhcp4_parser.cc"
    break;

  case 515: // pool_entry: "pool" $@82 ":" "constant string"
#line 1815 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2939 "dhcp4_parser.cc"
    break;

  case 516: // $@83: %empty
#line 1821 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 517: // user_context: "user-context" $@83 ":" map_value
#line 1823 "dhcp4_parser.yy"
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
#line 2974 "dhcp4_parser.cc"
    break;

  case 518: // $@84: %empty
#line 1846 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2982 "dhcp4_parser.cc"
    break;

  case 519: // comment: "comment" $@84 ":" "constant string"
#line 1848 "dhcp4_parser.yy"
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
#line 3011 "dhcp4_parser.cc"
    break;

  case 520: // $@85: %empty
#line 1876 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3023 "dhcp4_parser.cc"
    break;

  case 521: // reservations: "reservations" $@85 ":" "[" reservations_list "]"
#line 1882 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3032 "dhcp4_parser.cc"
    break;

  case 526: // $@86: %empty
#line 1895 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3042 "dhcp4_parser.cc"
    break;

  case 527: // reservation: "{" $@86 reservation_params "}"
#line 1899 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3051 "dhcp4_parser.cc"
    break;

  case 528: // $@87: %empty
#line 1904 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3061 "dhcp4_parser.cc"
    break;

  case 529: // sub_reservation: "{" $@87 reservation_params "}"
#line 1908 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3070 "dhcp4_parser.cc"
    break;

  case 549: // $@88: %empty
#line 1939 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3079 "dhcp4_parser.cc"
    break;

  case 550: // next_server: "next-server" $@88 ":" "constant string"
#line 1942 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3089 "dhcp4_parser.cc"
    break;

  case 551: // $@89: %empty
#line 1948 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3098 "dhcp4_parser.cc"
    break;

  case 552: // server_hostname: "server-hostname" $@89 ":" "constant string"
#line 1951 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3108 "dhcp4_parser.cc"
    break;

  case 553: // $@90: %empty
#line 1957 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3117 "dhcp4_parser.cc"
    break;

  case 554: // boot_file_name: "boot-file-name" $@90 ":" "constant string"
#line 1960 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3127 "dhcp4_parser.cc"
    break;

  case 555: // $@91: %empty
#line 1966 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3136 "dhcp4_parser.cc"
    break;

  case 556: // ip_address: "ip-address" $@91 ":" "constant string"
#line 1969 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3146 "dhcp4_parser.cc"
    break;

  case 557: // $@92: %empty
#line 1975 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3158 "dhcp4_parser.cc"
    break;

  case 558: // ip_addresses: "ip-addresses" $@92 ":" list_strings
#line 1981 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 559: // $@93: %empty
#line 1986 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3176 "dhcp4_parser.cc"
    break;

  case 560: // duid: "duid" $@93 ":" "constant string"
#line 1989 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 561: // $@94: %empty
#line 1995 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3195 "dhcp4_parser.cc"
    break;

  case 562: // hw_address: "hw-address" $@94 ":" "constant string"
#line 1998 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3205 "dhcp4_parser.cc"
    break;

  case 563: // $@95: %empty
#line 2004 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 564: // client_id_value: "client-id" $@95 ":" "constant string"
#line 2007 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3224 "dhcp4_parser.cc"
    break;

  case 565: // $@96: %empty
#line 2013 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 566: // circuit_id_value: "circuit-id" $@96 ":" "constant string"
#line 2016 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 567: // $@97: %empty
#line 2022 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3252 "dhcp4_parser.cc"
    break;

  case 568: // flex_id_value: "flex-id" $@97 ":" "constant string"
#line 2025 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3262 "dhcp4_parser.cc"
    break;

  case 569: // $@98: %empty
#line 2031 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3271 "dhcp4_parser.cc"
    break;

  case 570: // hostname: "hostname" $@98 ":" "constant string"
#line 2034 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3281 "dhcp4_parser.cc"
    break;

  case 571: // $@99: %empty
#line 2040 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 572: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2046 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3302 "dhcp4_parser.cc"
    break;

  case 573: // $@100: %empty
#line 2054 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3314 "dhcp4_parser.cc"
    break;

  case 574: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2060 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3323 "dhcp4_parser.cc"
    break;

  case 577: // $@101: %empty
#line 2072 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3335 "dhcp4_parser.cc"
    break;

  case 578: // client_classes: "client-classes" $@101 ":" "[" client_classes_list "]"
#line 2078 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3344 "dhcp4_parser.cc"
    break;

  case 581: // $@102: %empty
#line 2087 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3354 "dhcp4_parser.cc"
    break;

  case 582: // client_class_entry: "{" $@102 client_class_params "}"
#line 2091 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3364 "dhcp4_parser.cc"
    break;

  case 599: // $@103: %empty
#line 2120 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3373 "dhcp4_parser.cc"
    break;

  case 600: // client_class_test: "test" $@103 ":" "constant string"
#line 2123 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3383 "dhcp4_parser.cc"
    break;

  case 601: // only_if_required: "only-if-required" ":" "boolean"
#line 2129 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3393 "dhcp4_parser.cc"
    break;

  case 602: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2137 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 603: // $@104: %empty
#line 2145 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3415 "dhcp4_parser.cc"
    break;

  case 604: // control_socket: "control-socket" $@104 ":" "{" control_socket_params "}"
#line 2151 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3424 "dhcp4_parser.cc"
    break;

  case 612: // $@105: %empty
#line 2167 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3433 "dhcp4_parser.cc"
    break;

  case 613: // control_socket_type: "socket-type" $@105 ":" "constant string"
#line 2170 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3443 "dhcp4_parser.cc"
    break;

  case 614: // $@106: %empty
#line 2176 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3452 "dhcp4_parser.cc"
    break;

  case 615: // control_socket_name: "socket-name" $@106 ":" "constant string"
#line 2179 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 616: // $@107: %empty
#line 2188 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3474 "dhcp4_parser.cc"
    break;

  case 617: // dhcp_queue_control: "dhcp-queue-control" $@107 ":" "{" queue_control_params "}"
#line 2194 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 626: // enable_queue: "enable-queue" ":" "boolean"
#line 2213 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 627: // $@108: %empty
#line 2219 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3504 "dhcp4_parser.cc"
    break;

  case 628: // queue_type: "queue-type" $@108 ":" "constant string"
#line 2222 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3514 "dhcp4_parser.cc"
    break;

  case 629: // capacity: "capacity" ":" "integer"
#line 2228 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3524 "dhcp4_parser.cc"
    break;

  case 630: // $@109: %empty
#line 2234 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3533 "dhcp4_parser.cc"
    break;

  case 631: // arbitrary_map_entry: "constant string" $@109 ":" value
#line 2237 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 632: // $@110: %empty
#line 2244 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 633: // dhcp_ddns: "dhcp-ddns" $@110 ":" "{" dhcp_ddns_params "}"
#line 2250 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 634: // $@111: %empty
#line 2257 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3575 "dhcp4_parser.cc"
    break;

  case 635: // sub_dhcp_ddns: "{" $@111 dhcp_ddns_params "}"
#line 2261 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3585 "dhcp4_parser.cc"
    break;

  case 656: // enable_updates: "enable-updates" ":" "boolean"
#line 2291 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3595 "dhcp4_parser.cc"
    break;

  case 657: // $@112: %empty
#line 2297 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3604 "dhcp4_parser.cc"
    break;

  case 658: // server_ip: "server-ip" $@112 ":" "constant string"
#line 2300 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3614 "dhcp4_parser.cc"
    break;

  case 659: // server_port: "server-port" ":" "integer"
#line 2306 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3624 "dhcp4_parser.cc"
    break;

  case 660: // $@113: %empty
#line 2312 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3633 "dhcp4_parser.cc"
    break;

  case 661: // sender_ip: "sender-ip" $@113 ":" "constant string"
#line 2315 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3643 "dhcp4_parser.cc"
    break;

  case 662: // sender_port: "sender-port" ":" "integer"
#line 2321 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 663: // max_queue_size: "max-queue-size" ":" "integer"
#line 2327 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3663 "dhcp4_parser.cc"
    break;

  case 664: // $@114: %empty
#line 2333 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3672 "dhcp4_parser.cc"
    break;

  case 665: // ncr_protocol: "ncr-protocol" $@114 ":" ncr_protocol_value
#line 2336 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3681 "dhcp4_parser.cc"
    break;

  case 666: // ncr_protocol_value: "udp"
#line 2342 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3687 "dhcp4_parser.cc"
    break;

  case 667: // ncr_protocol_value: "tcp"
#line 2343 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3693 "dhcp4_parser.cc"
    break;

  case 668: // $@115: %empty
#line 2346 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 669: // ncr_format: "ncr-format" $@115 ":" "JSON"
#line 2349 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 670: // $@116: %empty
#line 2356 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3721 "dhcp4_parser.cc"
    break;

  case 671: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2359 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 672: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2366 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 673: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2373 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 674: // $@117: %empty
#line 2380 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 675: // dep_replace_client_name: "replace-client-name" $@117 ":" ddns_replace_client_name_value
#line 2383 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 676: // $@118: %empty
#line 2389 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 677: // dep_generated_prefix: "generated-prefix" $@118 ":" "constant string"
#line 2392 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3788 "dhcp4_parser.cc"
    break;

  case 678: // $@119: %empty
#line 2399 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3797 "dhcp4_parser.cc"
    break;

  case 679: // dep_hostname_char_set: "hostname-char-set" $@119 ":" "constant string"
#line 2402 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3807 "dhcp4_parser.cc"
    break;

  case 680: // $@120: %empty
#line 2409 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3816 "dhcp4_parser.cc"
    break;

  case 681: // dep_hostname_char_replacement: "hostname-char-replacement" $@120 ":" "constant string"
#line 2412 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3826 "dhcp4_parser.cc"
    break;

  case 682: // $@121: %empty
#line 2421 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3838 "dhcp4_parser.cc"
    break;

  case 683: // config_control: "config-control" $@121 ":" "{" config_control_params "}"
#line 2427 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3848 "dhcp4_parser.cc"
    break;

  case 684: // $@122: %empty
#line 2433 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 685: // sub_config_control: "{" $@122 config_control_params "}"
#line 2437 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3867 "dhcp4_parser.cc"
    break;

  case 690: // $@123: %empty
#line 2452 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3879 "dhcp4_parser.cc"
    break;

  case 691: // config_databases: "config-databases" $@123 ":" "[" database_list "]"
#line 2458 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3888 "dhcp4_parser.cc"
    break;

  case 692: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2463 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3898 "dhcp4_parser.cc"
    break;

  case 693: // $@124: %empty
#line 2471 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 694: // loggers: "loggers" $@124 ":" "[" loggers_entries "]"
#line 2477 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3919 "dhcp4_parser.cc"
    break;

  case 697: // $@125: %empty
#line 2489 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 698: // logger_entry: "{" $@125 logger_params "}"
#line 2493 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3937 "dhcp4_parser.cc"
    break;

  case 708: // debuglevel: "debuglevel" ":" "integer"
#line 2510 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3947 "dhcp4_parser.cc"
    break;

  case 709: // $@126: %empty
#line 2516 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3956 "dhcp4_parser.cc"
    break;

  case 710: // severity: "severity" $@126 ":" "constant string"
#line 2519 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3966 "dhcp4_parser.cc"
    break;

  case 711: // $@127: %empty
#line 2525 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3978 "dhcp4_parser.cc"
    break;

  case 712: // output_options_list: "output_options" $@127 ":" "[" output_options_list_content "]"
#line 2531 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3987 "dhcp4_parser.cc"
    break;

  case 715: // $@128: %empty
#line 2540 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3997 "dhcp4_parser.cc"
    break;

  case 716: // output_entry: "{" $@128 output_params_list "}"
#line 2544 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4005 "dhcp4_parser.cc"
    break;

  case 724: // $@129: %empty
#line 2559 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4014 "dhcp4_parser.cc"
    break;

  case 725: // output: "output" $@129 ":" "constant string"
#line 2562 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4024 "dhcp4_parser.cc"
    break;

  case 726: // flush: "flush" ":" "boolean"
#line 2568 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4034 "dhcp4_parser.cc"
    break;

  case 727: // maxsize: "maxsize" ":" "integer"
#line 2574 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4044 "dhcp4_parser.cc"
    break;

  case 728: // maxver: "maxver" ":" "integer"
#line 2580 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4054 "dhcp4_parser.cc"
    break;

  case 729: // $@130: %empty
#line 2586 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4063 "dhcp4_parser.cc"
    break;

  case 730: // pattern: "pattern" $@130 ":" "constant string"
#line 2589 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4073 "dhcp4_parser.cc"
    break;


#line 4077 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -891;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     356,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,    31,    41,    72,    74,    78,    93,
     101,   111,   131,   157,   158,   159,   168,   189,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,    41,  -147,   167,   174,    67,   498,
      65,   230,   -33,   267,   128,   -79,   588,    98,  -891,   210,
     253,   258,   186,   260,  -891,   256,  -891,  -891,  -891,   262,
     266,   270,  -891,  -891,  -891,  -891,  -891,  -891,   271,   277,
     283,   284,   285,   296,   302,   313,   322,  -891,   328,   329,
     335,   336,   343,  -891,  -891,  -891,   346,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,   366,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,   367,  -891,    58,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,   371,  -891,    84,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,   372,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,    94,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
     164,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,   291,   316,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,   360,  -891,  -891,   374,  -891,  -891,  -891,   381,  -891,
    -891,   378,   389,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,   393,   394,  -891,  -891,
    -891,  -891,   385,   396,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,   170,  -891,  -891,  -891,
     397,  -891,  -891,   398,  -891,   400,   402,  -891,  -891,   404,
     405,  -891,  -891,  -891,  -891,  -891,  -891,  -891,   173,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,   407,   181,  -891,  -891,
    -891,  -891,    41,    41,  -891,  -135,   408,  -891,   409,   410,
     418,   211,   236,   238,   424,   425,   428,   434,   435,   437,
     255,   257,   259,   261,   265,   254,   272,   274,   268,   445,
     276,   279,   275,   278,   281,   450,   464,   469,   286,   470,
     474,   477,   478,   481,   482,   485,   487,   488,   489,   490,
     493,   312,   496,   500,   503,   504,   505,   507,   508,  -891,
     174,  -891,   509,   510,   511,   327,    67,  -891,   513,   514,
     515,   516,   517,   518,   355,   539,   540,   541,   498,  -891,
     542,    65,  -891,   543,   544,   545,   546,   547,   548,   549,
     550,  -891,   230,  -891,   559,   561,   387,   576,   577,   579,
     395,  -891,   267,   581,   399,   413,  -891,   128,   582,   583,
      87,  -891,   416,   585,   587,   411,   595,   419,   422,   606,
     607,   423,   431,   609,   610,   617,   619,   588,  -891,   620,
     438,    98,  -891,  -891,  -891,   622,   621,   623,   629,   630,
    -891,  -891,  -891,   441,   443,   452,   632,   633,   636,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,   456,  -891,
    -891,  -891,  -891,  -891,  -105,   457,   458,  -891,   640,   641,
     642,   643,   644,   463,   280,   645,   647,   648,   649,   663,
    -891,   664,   665,   666,   678,   502,   506,   650,  -891,   684,
     123,   133,  -891,  -891,   512,   519,   520,   685,   521,   522,
    -891,   684,   523,   686,  -891,   524,  -891,   684,   526,   527,
     529,   530,   531,   532,   533,  -891,   534,   535,  -891,   537,
     538,   558,  -891,  -891,   560,  -891,  -891,  -891,   562,   644,
    -891,  -891,   563,   566,  -891,   567,  -891,  -891,    12,   568,
    -891,  -891,  -105,   569,   570,   571,  -891,   689,  -891,  -891,
      41,   174,    98,    67,   667,  -891,  -891,  -891,    81,    81,
     688,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
     690,   694,   696,   719,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,   -39,   720,   721,   722,    23,   188,   191,    85,
     588,  -891,  -891,   723,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,   738,  -891,  -891,  -891,  -891,
     100,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,   688,
    -891,   183,   184,   187,  -891,   190,  -891,  -891,  -891,  -891,
    -891,  -891,   692,   743,   750,   754,   755,  -891,  -891,  -891,
    -891,   756,   757,   758,   759,   760,   761,  -891,   249,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
     269,  -891,   763,   767,  -891,  -891,   765,   769,  -891,  -891,
     770,   772,  -891,  -891,   771,   775,  -891,  -891,   773,   777,
    -891,  -891,  -891,  -891,  -891,  -891,    34,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,    46,  -891,  -891,   776,   778,  -891,
    -891,   779,   780,  -891,   762,   782,   783,   784,   785,   786,
     287,  -891,  -891,  -891,  -891,  -891,  -891,  -891,   788,   789,
     790,  -891,   288,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,   295,  -891,  -891,  -891,   791,  -891,
     792,  -891,  -891,  -891,   299,  -891,  -891,  -891,  -891,  -891,
     305,  -891,    61,  -891,   598,  -891,   793,   794,  -891,  -891,
    -891,  -891,   795,   796,  -891,  -891,  -891,   797,   667,  -891,
     800,   801,   802,   803,   586,   611,   624,   625,   626,   804,
     805,   806,   808,   628,   631,   634,   635,   627,   637,    81,
    -891,  -891,    81,  -891,   688,   498,  -891,   690,   267,  -891,
     694,   128,  -891,   696,   605,  -891,   719,   -39,  -891,    75,
     720,  -891,   230,  -891,   721,   -79,  -891,   722,   638,   639,
     646,   652,   653,   655,    23,  -891,   654,   659,   674,   188,
    -891,   813,   815,   191,  -891,   673,   816,   679,   819,    85,
    -891,  -891,   198,   723,  -891,  -891,   821,   825,    65,  -891,
     738,   826,  -891,  -891,   612,  -891,   352,   651,   697,   709,
    -891,  -891,  -891,  -891,  -891,   710,   713,   716,   724,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,   307,  -891,   315,  -891,
     823,  -891,   824,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
     326,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,   830,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,   827,   833,  -891,  -891,  -891,  -891,  -891,   845,
    -891,   350,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,   731,   732,  -891,  -891,   734,  -891,
      41,  -891,  -891,   874,  -891,  -891,  -891,  -891,  -891,   351,
    -891,  -891,  -891,  -891,  -891,  -891,   774,   361,  -891,   684,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,   605,  -891,   878,
     766,  -891,    75,  -891,  -891,  -891,  -891,  -891,  -891,   905,
     781,   952,   198,  -891,  -891,  -891,  -891,  -891,   787,  -891,
    -891,   959,  -891,   798,  -891,  -891,   822,  -891,  -891,    90,
    -891,   -27,   822,  -891,  -891,   961,   962,   963,  -891,   364,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,   965,   799,   807,
     809,   966,   -27,  -891,   811,  -891,  -891,  -891,   812,  -891,
    -891,  -891
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   162,     9,   320,    11,   503,    13,
     528,    15,   428,    17,   436,    19,   473,    21,   285,    23,
     634,    25,   684,    27,    45,    39,     0,     0,     0,     0,
       0,   530,     0,   438,   475,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   682,   151,   177,     0,
       0,     0,   549,   551,   553,   175,   184,   186,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   125,     0,     0,
       0,     0,     0,   133,   140,   142,     0,   312,   426,   465,
     383,   516,   518,   376,   250,   577,   520,   277,   296,     0,
     264,   603,   616,   632,   144,   146,   693,     0,   115,     0,
      62,    64,    65,    66,    67,    68,    99,   100,   101,    69,
      97,    86,    87,    88,   105,   106,   107,   108,   109,   110,
     103,   104,   111,   112,   113,    72,    73,    94,    74,    75,
      76,   114,    80,    81,    70,    98,    71,    78,    79,    92,
      93,    95,    89,    90,    91,    77,    82,    83,    84,    85,
      96,   102,   164,   166,   170,     0,   161,     0,   153,   155,
     156,   157,   158,   159,   160,   364,   366,   368,   495,   362,
     370,     0,   374,   372,   573,   361,   324,   325,   326,   327,
     328,   349,   350,   351,   339,   340,   352,   353,   354,   355,
     356,   357,   358,   359,   360,     0,   322,   331,   344,   345,
     346,   332,   334,   335,   337,   333,   329,   330,   347,   348,
     336,   341,   342,   343,   338,   514,   513,   509,   510,   508,
       0,   505,   507,   511,   512,   571,   559,   561,   565,   563,
     569,   567,   555,   548,   542,   546,   547,     0,   531,   532,
     543,   544,   545,   539,   534,   540,   536,   537,   538,   541,
     535,     0,   455,   230,     0,   459,   457,   462,     0,   451,
     452,     0,   439,   440,   442,   454,   443,   444,   445,   461,
     446,   447,   448,   449,   450,   489,     0,     0,   487,   488,
     491,   492,     0,   476,   477,   479,   480,   481,   482,   483,
     484,   485,   486,   292,   294,   289,     0,   287,   290,   291,
       0,   670,   657,     0,   660,     0,     0,   664,   668,     0,
       0,   674,   676,   678,   680,   655,   653,   654,     0,   636,
     638,   639,   640,   641,   642,   643,   644,   645,   650,   646,
     647,   648,   649,   651,   652,   690,     0,     0,   686,   688,
     689,    44,     0,     0,    37,     0,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
       0,    61,     0,     0,     0,     0,     0,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   321,
       0,     0,   504,     0,     0,     0,     0,     0,     0,     0,
       0,   529,     0,   429,     0,     0,     0,     0,     0,     0,
       0,   437,     0,     0,     0,     0,   474,     0,     0,     0,
       0,   286,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   635,     0,
       0,     0,   685,    48,    41,     0,     0,     0,     0,     0,
     127,   128,   129,     0,     0,     0,     0,     0,     0,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,   149,
     150,   130,   131,   132,     0,     0,     0,   148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     602,     0,     0,     0,     0,     0,     0,     0,    63,     0,
       0,     0,   174,   154,     0,     0,     0,     0,     0,     0,
     382,     0,     0,     0,   323,     0,   506,     0,     0,     0,
       0,     0,     0,     0,     0,   533,     0,     0,   453,     0,
       0,     0,   464,   441,     0,   493,   494,   478,     0,     0,
     288,   656,     0,     0,   659,     0,   662,   663,     0,     0,
     672,   673,     0,     0,     0,     0,   637,     0,   692,   687,
       0,     0,     0,     0,     0,   550,   552,   554,     0,     0,
     188,   126,   135,   136,   137,   138,   139,   134,   141,   143,
     314,   430,   467,   385,    38,   517,   519,   378,   379,   380,
     381,   377,     0,     0,   522,   279,     0,     0,     0,     0,
       0,   145,   147,     0,    49,   165,   168,   169,   167,   172,
     173,   171,   365,   367,   369,   497,   363,   371,   375,   373,
       0,   515,   572,   560,   562,   566,   564,   570,   568,   556,
     456,   231,   460,   458,   463,   490,   293,   295,   671,   658,
     661,   666,   667,   665,   669,   675,   677,   679,   681,   188,
      42,     0,     0,     0,   182,     0,   179,   181,   217,   223,
     225,   227,     0,     0,     0,     0,     0,   239,   241,   243,
     245,     0,     0,     0,     0,     0,     0,   216,     0,   194,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     209,   210,   211,   206,   212,   213,   214,   207,   208,   215,
       0,   192,     0,   189,   190,   318,     0,   315,   316,   434,
       0,   431,   432,   471,     0,   468,   469,   389,     0,   386,
     387,   259,   260,   261,   262,   263,     0,   252,   254,   255,
     256,   257,   258,   581,     0,   579,   526,     0,   523,   524,
     283,     0,   280,   281,     0,     0,     0,     0,     0,     0,
       0,   298,   300,   301,   302,   303,   304,   305,     0,     0,
       0,   273,     0,   266,   268,   269,   270,   271,   272,   612,
     614,   611,   609,   610,     0,   605,   607,   608,     0,   627,
       0,   630,   623,   624,     0,   618,   620,   621,   622,   625,
       0,   697,     0,   695,    51,   501,     0,   498,   499,   557,
     575,   576,     0,     0,    59,   683,   152,     0,     0,   178,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   185,     0,   187,     0,     0,   313,     0,   438,   427,
       0,   475,   466,     0,     0,   384,     0,     0,   251,   583,
       0,   578,   530,   521,     0,     0,   278,     0,     0,     0,
       0,     0,     0,     0,     0,   297,     0,     0,     0,     0,
     265,     0,     0,     0,   604,     0,     0,     0,     0,     0,
     617,   633,     0,     0,   694,    53,     0,    52,     0,   496,
       0,     0,   574,   691,     0,   180,     0,     0,     0,     0,
     229,   232,   233,   234,   235,     0,     0,     0,     0,   247,
     248,   236,   237,   238,   249,   195,     0,   191,     0,   317,
       0,   433,     0,   470,   425,   408,   409,   410,   396,   397,
     413,   414,   415,   399,   400,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   393,   394,   395,   406,   407,   405,
       0,   391,   398,   411,   412,   401,   402,   403,   404,   388,
     253,   599,     0,   597,   598,   590,   591,   595,   596,   592,
     593,   594,     0,   584,   585,   587,   588,   589,   580,     0,
     525,     0,   282,   306,   307,   308,   309,   310,   311,   299,
     274,   275,   276,   267,     0,     0,   606,   626,     0,   629,
       0,   619,   711,     0,   709,   707,   701,   705,   706,     0,
     699,   703,   704,   702,   696,    50,     0,     0,   500,     0,
     183,   219,   220,   221,   222,   218,   224,   226,   228,   240,
     242,   244,   246,   193,   319,   435,   472,     0,   390,     0,
       0,   582,     0,   527,   284,   613,   615,   628,   631,     0,
       0,     0,     0,   698,    54,   502,   558,   392,     0,   601,
     586,     0,   708,     0,   700,   600,     0,   710,   715,     0,
     713,     0,     0,   712,   724,     0,     0,     0,   729,     0,
     717,   719,   720,   721,   722,   723,   714,     0,     0,     0,
       0,     0,     0,   716,     0,   726,   727,   728,     0,   718,
     725,   730
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,   -52,  -891,  -519,  -891,   362,
    -891,  -891,  -891,  -891,  -891,  -891,  -566,  -891,  -891,  -891,
     -67,  -891,  -891,  -891,  -891,  -891,  -891,   341,   536,   -40,
     -28,   -24,    -1,     1,    11,    19,    22,  -891,  -891,  -891,
    -891,    25,    26,    29,    30,    32,    37,  -891,   353,    40,
    -891,    43,  -891,    44,  -891,    45,  -891,    47,  -891,  -891,
    -891,  -891,   344,   528,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
     102,  -891,  -891,  -891,  -891,  -891,  -891,   263,  -891,    77,
    -891,  -626,    79,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,   -63,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,    62,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,    50,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,    56,  -891,  -891,  -891,    60,   497,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,    52,  -891,  -891,  -891,
    -891,  -891,  -891,  -890,  -891,  -891,  -891,    83,  -891,  -891,
    -891,    86,   551,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -887,  -891,   -65,  -891,    49,  -891,    48,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,    76,  -891,  -891,  -114,   -46,
    -891,  -891,  -891,  -891,  -891,    89,  -891,  -891,  -891,    92,
    -891,   552,  -891,   -42,  -891,  -891,  -891,  -891,  -891,   -36,
    -891,  -891,  -891,  -891,  -891,   -35,  -891,  -891,  -891,    82,
    -891,  -891,  -891,    91,  -891,   525,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,    51,  -891,  -891,
    -891,    55,   553,  -891,  -891,   -51,  -891,   -11,  -891,   -25,
    -891,  -891,  -891,    80,  -891,  -891,  -891,    88,  -891,   554,
     -55,  -891,     0,  -891,     7,  -891,   311,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -886,  -891,  -891,  -891,  -891,  -891,
      95,  -891,  -891,  -891,  -109,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,    63,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,    59,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,   347,   555,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,  -891,
    -891,  -891,  -891,   373,   557,  -891,  -891,  -891,  -891,  -891,
    -891,    66,  -891,  -891,  -106,  -891,  -891,  -891,  -891,  -891,
    -891,  -122,  -891,  -891,  -141,  -891,  -891,  -891,  -891,  -891,
    -891,  -891
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   655,
      82,    83,    39,    64,    79,    80,   675,   864,   956,   957,
     747,    41,    66,    85,   386,    43,    67,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   409,
     151,   152,   153,   154,   155,   156,   157,   415,   647,   158,
     416,   159,   417,   160,   436,   161,   437,   162,   163,   164,
     165,   389,   197,   198,    45,    68,   199,   442,   200,   443,
     678,   201,   444,   681,   202,   166,   397,   167,   390,   725,
     726,   727,   877,   168,   398,   169,   399,   772,   773,   774,
     902,   748,   749,   750,   880,  1095,   751,   881,   752,   882,
     753,   883,   754,   755,   475,   756,   757,   758,   759,   760,
     761,   762,   763,   889,   764,   890,   765,   891,   766,   892,
     767,   768,   769,   170,   426,   796,   797,   798,   799,   800,
     801,   802,   171,   432,   832,   833,   834,   835,   836,   172,
     429,   811,   812,   813,   925,    59,    75,   336,   337,   338,
     488,   339,   489,   173,   430,   820,   821,   822,   823,   824,
     825,   826,   827,   174,   419,   776,   777,   778,   905,    47,
      69,   235,   236,   237,   452,   238,   448,   239,   449,   240,
     450,   241,   453,   242,   456,   243,   455,   175,   425,   661,
     245,   176,   422,   788,   789,   790,   914,  1020,  1021,   177,
     420,    53,    72,   780,   781,   782,   908,    55,    73,   301,
     302,   303,   304,   305,   306,   307,   474,   308,   478,   309,
     477,   310,   311,   479,   312,   178,   421,   784,   785,   786,
     911,    57,    74,   322,   323,   324,   325,   326,   483,   327,
     328,   329,   330,   247,   451,   866,   867,   868,   958,    49,
      70,   260,   261,   262,   460,   179,   423,   180,   424,   181,
     428,   807,   808,   809,   922,    51,    71,   277,   278,   279,
     182,   394,   183,   395,   184,   396,   283,   470,   871,   961,
     284,   464,   285,   465,   286,   467,   287,   466,   288,   469,
     289,   468,   290,   463,   254,   457,   872,   185,   427,   804,
     805,   919,  1042,  1043,  1044,  1045,  1046,  1109,  1047,   186,
     187,   433,   844,   845,   846,   941,   847,   942,   188,   434,
     854,   855,   856,   857,   946,   858,   859,   948,   189,   435,
      61,    76,   358,   359,   360,   361,   494,   362,   363,   496,
     364,   365,   366,   499,   713,   367,   500,   368,   493,   369,
     370,   371,   503,   372,   504,   373,   505,   374,   506,   190,
     388,    63,    77,   377,   378,   379,   509,   380,   191,   438,
     862,   863,   952,  1079,  1080,  1081,  1082,  1121,  1083,  1119,
    1139,  1140,  1141,  1149,  1150,  1151,  1157,  1152,  1153,  1154,
    1155,  1161
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     138,   196,   215,   256,   273,   257,   299,   318,   335,   355,
     300,   319,    78,   770,   251,   688,   280,   203,   248,   263,
     275,   692,   313,   331,  1015,   356,   291,  1016,  1028,   216,
     711,    28,   320,   654,   246,   259,   274,   917,   321,    81,
     918,   217,   333,   334,   250,   218,    29,   118,    30,   920,
      31,   515,   921,   642,   643,   644,   645,   204,   249,   264,
     276,   440,   314,   332,   953,   357,   441,   954,   219,   252,
     220,   281,   791,   792,   793,   794,   253,   795,   282,    40,
     221,    42,   192,   193,   646,    44,   194,   446,   222,   195,
     654,   223,   447,  1142,   224,   225,  1143,   458,   226,   227,
      46,   228,   459,    92,    93,    94,   229,   137,    48,   230,
     375,   376,   231,   232,   233,   728,   234,   244,    50,   258,
     729,   730,   731,   732,   733,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,    52,  1144,
     676,   677,  1145,  1146,  1147,  1148,   119,   814,   815,   816,
     817,   818,   819,   679,   680,   118,   119,   293,   255,   121,
     122,   121,   122,   293,    54,    56,    58,   461,   712,   121,
     122,   212,   462,   490,   213,    60,   507,    84,   491,   121,
     122,   508,  1031,  1032,   511,    86,   440,   511,    87,   512,
     446,   874,   875,   878,   384,   876,    62,    88,   879,    89,
      90,    91,    92,    93,    94,    95,    96,    97,   333,   334,
     293,   315,   294,   295,   316,   317,   381,  1015,   272,   869,
    1016,  1028,   121,   122,   848,   849,   850,    32,    33,    34,
      35,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   137,   899,   137,   118,   119,   382,   900,    92,    93,
      94,   137,   383,   385,   387,   120,   391,   137,   121,   122,
     392,   851,   899,   123,   393,   400,   986,   901,   124,   125,
     293,   401,   121,   122,   126,   121,   122,   402,   403,   404,
     934,   939,   121,   122,   127,   935,   940,   128,   943,   471,
     405,   292,   949,   944,   129,   130,   406,   950,   507,   131,
     899,   119,   132,   951,   137,  1103,   133,   407,   458,   472,
     828,   829,   830,  1104,   121,   122,   408,   839,   840,  1107,
     513,   514,   410,   411,  1108,   265,   134,   135,   136,   412,
     413,   266,   267,   268,   269,   270,   271,   414,   272,   293,
     418,   294,   295,   490,  1122,   296,   297,   298,  1114,  1123,
     137,   121,   122,  1072,   461,  1073,  1074,  1162,   473,  1125,
     431,   439,  1163,   138,   137,   445,   454,   137,   476,   196,
     657,   658,   659,   660,   137,   480,   481,  1091,  1092,  1093,
    1094,   215,   482,   486,   256,   203,   257,   484,   485,   487,
     520,   492,   495,   251,   497,   273,   498,   248,   501,   502,
     263,   510,   516,   517,   518,   299,   137,   280,   216,   300,
     318,   275,   519,   246,   319,   521,   259,   522,   523,   524,
     217,   313,   525,   250,   218,   204,   331,   274,   526,   527,
     355,   528,   529,   534,   530,   320,   531,   249,   532,   538,
     264,   321,   533,   137,   544,   537,   356,   219,   252,   220,
     535,   276,   536,   539,   541,   253,   540,   542,   545,   221,
     543,   314,   281,   546,   548,   547,   332,   222,   549,   282,
     223,   550,   551,   224,   225,   552,   553,   226,   227,   554,
     228,   555,   556,   557,   558,   229,   357,   559,   230,   560,
     561,   231,   232,   233,   562,   234,   244,   563,   564,   565,
     258,   566,   567,   569,   570,   571,   572,   574,   575,   576,
     577,   578,   579,  1126,    90,    91,    92,    93,    94,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   580,   581,   582,   583,   585,   587,   588,   589,
     590,   591,   592,   593,   594,    98,    99,   100,   101,   102,
     103,   104,   105,   596,   138,   597,   196,   110,   111,   112,
     113,   114,   115,   116,   598,   205,   206,   207,   720,   119,
     599,   600,   203,   601,   602,   604,   608,   609,   605,   612,
     208,   613,   121,   122,   209,   210,   211,   123,   614,   615,
     831,   841,   606,   355,   212,   611,   616,   213,   126,   617,
     618,   619,   620,   622,   623,   214,   837,   842,   852,   356,
     621,   624,   204,   625,   627,   628,   630,   635,   631,   636,
     632,    90,    91,    92,    93,    94,   633,   634,   637,   638,
     639,   640,   641,   648,   649,   650,   651,   652,   653,   656,
     662,    30,   663,   664,   665,   673,   838,   843,   853,   357,
     134,   135,    98,    99,   100,   101,   102,   103,   104,   105,
     666,   667,   668,   669,   110,   111,   112,   113,   114,   115,
     116,   117,   121,   122,   137,   670,   119,   293,   671,   674,
     685,   724,   672,   690,   719,   771,   884,   775,   682,   121,
     122,   779,   210,   783,   123,   683,   684,   686,   687,   689,
     691,   212,   693,   694,   213,   695,   696,   697,   698,   699,
     700,   701,   214,   702,   703,   714,   787,   803,   806,   810,
     861,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   704,   865,   705,   885,   706,   708,
     353,   354,   709,   710,   886,   716,   717,   718,   887,   888,
     893,   894,   895,   896,   897,   898,   928,   134,   135,   903,
     904,   906,   907,   970,   137,   910,   909,   912,   913,   915,
     916,   924,   923,   927,   955,   926,   929,   930,   931,   932,
     933,   137,   936,   937,   938,   945,   947,   960,  1090,   959,
     971,   964,   963,   962,   966,   967,   968,   969,   975,   976,
     977,   972,   978,   974,   973,   979,   983,  1064,   980,  1065,
    1068,   981,   982,  1070,   984,  1053,  1054,  1085,  1086,  1138,
    1089,  1105,  1106,  1055,  1110,  1111,  1112,  1096,   215,  1056,
    1057,   299,  1058,  1060,   318,   300,  1061,   994,   319,  1017,
     251,  1014,  1033,  1113,   248,   273,  1034,   313,   335,  1025,
     331,  1062,  1067,  1023,  1039,   216,  1069,   280,  1037,   320,
     246,   275,   831,  1035,   995,   321,   841,   217,  1120,  1022,
     250,   218,  1128,  1097,  1036,  1075,   996,   274,   837,  1076,
     997,   256,   842,   257,   249,  1098,  1099,   314,   852,  1100,
     332,  1077,  1101,  1024,   219,   252,   220,   263,  1038,  1131,
    1102,   276,   253,   998,  1026,   999,   221,  1115,  1116,  1040,
    1117,  1027,   281,   259,   222,  1000,  1041,   223,   838,   282,
     224,   225,   843,  1001,   226,   227,  1002,   228,   853,  1003,
    1004,  1078,   229,  1005,  1006,   230,  1007,   264,   231,   232,
     233,  1008,   234,   244,  1009,  1129,  1133,  1010,  1011,  1012,
    1124,  1013,  1019,  1018,  1136,  1158,  1159,  1160,  1132,  1164,
    1168,   707,   721,  1135,   573,   715,   568,   723,   985,  1030,
     965,   987,   873,  1052,  1137,  1051,  1059,   610,  1165,  1063,
     989,   988,  1029,  1127,  1166,   993,  1167,  1170,  1171,   991,
     990,   870,   992,  1130,  1050,   722,  1066,   258,  1071,   584,
    1049,  1088,   607,  1087,   586,  1048,  1134,   860,  1118,  1084,
    1156,  1169,     0,     0,     0,     0,   595,     0,     0,     0,
       0,     0,     0,     0,   603,     0,     0,     0,     0,     0,
     994,     0,  1017,     0,  1014,  1033,     0,     0,     0,  1034,
       0,     0,  1025,     0,     0,  1075,  1023,  1039,     0,  1076,
       0,  1037,   626,     0,     0,     0,  1035,   995,   629,     0,
       0,  1077,  1022,     0,     0,     0,     0,  1036,     0,   996,
       0,     0,     0,   997,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1024,     0,     0,     0,
       0,  1038,     0,     0,     0,     0,   998,  1026,   999,     0,
       0,  1078,  1040,     0,  1027,     0,     0,     0,  1000,  1041,
       0,     0,     0,     0,     0,     0,  1001,     0,     0,  1002,
       0,     0,  1003,  1004,     0,     0,  1005,  1006,     0,  1007,
       0,     0,     0,     0,  1008,     0,     0,  1009,     0,     0,
    1010,  1011,  1012,     0,  1013,  1019,  1018
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   639,    69,   581,    71,    68,    69,    70,
      71,   587,    73,    74,   914,    76,    72,   914,   914,    69,
      18,     0,    74,   552,    69,    70,    71,     3,    74,   186,
       6,    69,   121,   122,    69,    69,     5,    80,     7,     3,
       9,   186,     6,   158,   159,   160,   161,    68,    69,    70,
      71,     3,    73,    74,     3,    76,     8,     6,    69,    69,
      69,    71,   111,   112,   113,   114,    69,   116,    71,     7,
      69,     7,    15,    16,   189,     7,    19,     3,    69,    22,
     609,    69,     8,     3,    69,    69,     6,     3,    69,    69,
       7,    69,     8,    28,    29,    30,    69,   186,     7,    69,
      12,    13,    69,    69,    69,    34,    69,    69,     7,    70,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,     7,   166,
      17,    18,   169,   170,   171,   172,    81,   124,   125,   126,
     127,   128,   129,    20,    21,    80,    81,    82,    93,    94,
      95,    94,    95,    82,     7,     7,     7,     3,   156,    94,
      95,   106,     8,     3,   109,     7,     3,    10,     8,    94,
      95,     8,   107,   108,     3,    11,     3,     3,    14,     8,
       3,     8,     8,     3,     8,     8,     7,    23,     8,    25,
      26,    27,    28,    29,    30,    31,    32,    33,   121,   122,
      82,    83,    84,    85,    86,    87,     6,  1107,   118,   119,
    1107,  1107,    94,    95,   139,   140,   141,   186,   187,   188,
     189,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,   186,     3,   186,    80,    81,     3,     8,    28,    29,
      30,   186,     4,     3,     8,    91,     4,   186,    94,    95,
       4,   186,     3,    99,     4,     4,   902,     8,   104,   105,
      82,     4,    94,    95,   110,    94,    95,     4,     4,     4,
       3,     3,    94,    95,   120,     8,     8,   123,     3,     8,
       4,    34,     3,     8,   130,   131,     4,     8,     3,   135,
       3,    81,   138,     8,   186,     8,   142,     4,     3,     3,
     132,   133,   134,     8,    94,    95,     4,   136,   137,     3,
     382,   383,     4,     4,     8,   105,   162,   163,   164,     4,
       4,   111,   112,   113,   114,   115,   116,     4,   118,    82,
       4,    84,    85,     3,     3,    88,    89,    90,     8,     8,
     186,    94,    95,   165,     3,   167,   168,     3,     8,     8,
       4,     4,     8,   440,   186,     4,     4,   186,     4,   446,
     100,   101,   102,   103,   186,     4,     8,    35,    36,    37,
      38,   458,     3,     8,   461,   446,   461,     4,     4,     3,
     189,     4,     4,   458,     4,   472,     4,   458,     4,     4,
     461,     4,     4,     4,     4,   482,   186,   472,   458,   482,
     487,   472,     4,   458,   487,   189,   461,   189,     4,     4,
     458,   482,     4,   458,   458,   446,   487,   472,     4,     4,
     507,     4,   187,   189,   187,   487,   187,   458,   187,     4,
     461,   487,   187,   186,     4,   187,   507,   458,   458,   458,
     188,   472,   188,   187,   189,   458,   187,   189,     4,   458,
     189,   482,   472,     4,     4,   189,   487,   458,     4,   472,
     458,     4,     4,   458,   458,     4,     4,   458,   458,     4,
     458,     4,     4,     4,     4,   458,   507,     4,   458,   187,
       4,   458,   458,   458,     4,   458,   458,     4,     4,     4,
     461,     4,     4,     4,     4,     4,   189,     4,     4,     4,
       4,     4,     4,  1089,    26,    27,    28,    29,    30,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   187,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,    57,    58,    59,    60,    61,
      62,    63,    64,     4,   631,     4,   633,    69,    70,    71,
      72,    73,    74,    75,   187,    77,    78,    79,   630,    81,
       4,     4,   633,     4,   189,     4,     4,     4,   189,     4,
      92,     4,    94,    95,    96,    97,    98,    99,   187,     4,
     667,   668,   189,   670,   106,   189,   187,   109,   110,   187,
       4,     4,   189,     4,     4,   117,   667,   668,   669,   670,
     189,     4,   633,     4,     4,   187,     4,   186,     7,   186,
       7,    26,    27,    28,    29,    30,     7,     7,   186,     7,
       7,     5,   186,   186,   186,     5,     5,     5,     5,   186,
       5,     7,     5,     5,     5,     5,   667,   668,   669,   670,
     162,   163,    57,    58,    59,    60,    61,    62,    63,    64,
       7,     7,     7,     7,    69,    70,    71,    72,    73,    74,
      75,    76,    94,    95,   186,     7,    81,    82,   186,     5,
       5,    24,   186,     7,     5,     7,     4,     7,   186,    94,
      95,     7,    97,     7,    99,   186,   186,   186,   186,   186,
     186,   106,   186,   186,   109,   186,   186,   186,   186,   186,
     186,   186,   117,   186,   186,   157,     7,     7,     7,     7,
       7,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   186,     7,   186,     4,   186,   186,
     162,   163,   186,   186,     4,   186,   186,   186,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   162,   163,     6,
       3,     6,     3,   187,   186,     3,     6,     6,     3,     6,
       3,     3,     6,     3,   186,     6,     4,     4,     4,     4,
       4,   186,     4,     4,     4,     4,     4,     3,   186,     6,
     189,     4,     6,     8,     4,     4,     4,     4,     4,     4,
       4,   187,     4,   187,   189,   187,   189,     4,   187,     4,
       4,   187,   187,     4,   187,   187,   187,     6,     3,     7,
       4,     8,     8,   187,     4,     8,     3,   186,   905,   187,
     187,   908,   187,   189,   911,   908,   187,   914,   911,   914,
     905,   914,   919,     8,   905,   922,   919,   908,   925,   914,
     911,   187,   189,   914,   919,   905,   187,   922,   919,   911,
     905,   922,   939,   919,   914,   911,   943,   905,     4,   914,
     905,   905,     4,   186,   919,   952,   914,   922,   939,   952,
     914,   958,   943,   958,   905,   186,   186,   908,   949,   186,
     911,   952,   186,   914,   905,   905,   905,   958,   919,     4,
     186,   922,   905,   914,   914,   914,   905,   186,   186,   919,
     186,   914,   922,   958,   905,   914,   919,   905,   939,   922,
     905,   905,   943,   914,   905,   905,   914,   905,   949,   914,
     914,   952,   905,   914,   914,   905,   914,   958,   905,   905,
     905,   914,   905,   905,   914,   189,     4,   914,   914,   914,
     186,   914,   914,   914,     5,     4,     4,     4,   187,     4,
       4,   609,   631,   186,   446,   622,   440,   633,   899,   917,
     878,   904,   719,   927,   186,   925,   934,   490,   189,   939,
     907,   905,   916,  1107,   187,   913,   187,   186,   186,   910,
     908,   690,   911,  1112,   924,   632,   943,   958,   949,   458,
     922,   960,   487,   958,   461,   920,  1122,   670,  1070,   953,
    1142,  1162,    -1,    -1,    -1,    -1,   472,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   482,    -1,    -1,    -1,    -1,    -1,
    1107,    -1,  1107,    -1,  1107,  1112,    -1,    -1,    -1,  1112,
      -1,    -1,  1107,    -1,    -1,  1122,  1107,  1112,    -1,  1122,
      -1,  1112,   507,    -1,    -1,    -1,  1112,  1107,   511,    -1,
      -1,  1122,  1107,    -1,    -1,    -1,    -1,  1112,    -1,  1107,
      -1,    -1,    -1,  1107,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1107,    -1,    -1,    -1,
      -1,  1112,    -1,    -1,    -1,    -1,  1107,  1107,  1107,    -1,
      -1,  1122,  1112,    -1,  1107,    -1,    -1,    -1,  1107,  1112,
      -1,    -1,    -1,    -1,    -1,    -1,  1107,    -1,    -1,  1107,
      -1,    -1,  1107,  1107,    -1,    -1,  1107,  1107,    -1,  1107,
      -1,    -1,    -1,    -1,  1107,    -1,    -1,  1107,    -1,    -1,
    1107,  1107,  1107,    -1,  1107,  1107,  1107
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,     0,     5,
       7,     9,   186,   187,   188,   189,   205,   206,   207,   212,
       7,   221,     7,   225,     7,   264,     7,   369,     7,   449,
       7,   465,     7,   401,     7,   407,     7,   431,     7,   345,
       7,   530,     7,   561,   213,   208,   222,   226,   265,   370,
     450,   466,   402,   408,   432,   346,   531,   562,   205,   214,
     215,   186,   210,   211,    10,   223,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    80,    81,
      91,    94,    95,    99,   104,   105,   110,   120,   123,   130,
     131,   135,   138,   142,   162,   163,   164,   186,   220,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   240,   241,   242,   243,   244,   245,   246,   249,   251,
     253,   255,   257,   258,   259,   260,   275,   277,   283,   285,
     323,   332,   339,   353,   363,   387,   391,   399,   425,   455,
     457,   459,   470,   472,   474,   497,   509,   510,   518,   528,
     559,   568,    15,    16,    19,    22,   220,   262,   263,   266,
     268,   271,   274,   455,   457,    77,    78,    79,    92,    96,
      97,    98,   106,   109,   117,   220,   229,   230,   231,   232,
     233,   234,   235,   236,   241,   242,   243,   244,   245,   246,
     249,   251,   253,   255,   257,   371,   372,   373,   375,   377,
     379,   381,   383,   385,   387,   390,   425,   443,   455,   457,
     459,   470,   472,   474,   494,    93,   220,   383,   385,   425,
     451,   452,   453,   455,   457,   105,   111,   112,   113,   114,
     115,   116,   118,   220,   425,   455,   457,   467,   468,   469,
     470,   472,   474,   476,   480,   482,   484,   486,   488,   490,
     492,   399,    34,    82,    84,    85,    88,    89,    90,   220,
     303,   409,   410,   411,   412,   413,   414,   415,   417,   419,
     421,   422,   424,   455,   457,    83,    86,    87,   220,   303,
     413,   419,   433,   434,   435,   436,   437,   439,   440,   441,
     442,   455,   457,   121,   122,   220,   347,   348,   349,   351,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   162,   163,   220,   455,   457,   532,   533,
     534,   535,   537,   538,   540,   541,   542,   545,   547,   549,
     550,   551,   553,   555,   557,    12,    13,   563,   564,   565,
     567,     6,     3,     4,     8,     3,   224,     8,   560,   261,
     278,     4,     4,     4,   471,   473,   475,   276,   284,   286,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   239,
       4,     4,     4,     4,     4,   247,   250,   252,     4,   364,
     400,   426,   392,   456,   458,   388,   324,   498,   460,   340,
     354,     4,   333,   511,   519,   529,   254,   256,   569,     4,
       3,     8,   267,   269,   272,     4,     3,     8,   376,   378,
     380,   444,   374,   382,     4,   386,   384,   495,     3,     8,
     454,     3,     8,   493,   481,   483,   487,   485,   491,   489,
     477,     8,     3,     8,   416,   304,     4,   420,   418,   423,
       4,     8,     3,   438,     4,     4,     8,     3,   350,   352,
       3,     8,     4,   548,   536,     4,   539,     4,     4,   543,
     546,     4,     4,   552,   554,   556,   558,     3,     8,   566,
       4,     3,     8,   205,   205,   186,     4,     4,     4,     4,
     189,   189,   189,     4,     4,     4,     4,     4,     4,   187,
     187,   187,   187,   187,   189,   188,   188,   187,     4,   187,
     187,   189,   189,   189,     4,     4,     4,   189,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     187,     4,     4,     4,     4,     4,     4,     4,   228,     4,
       4,     4,   189,   263,     4,     4,     4,     4,     4,     4,
     187,     4,     4,     4,   372,     4,   452,     4,     4,     4,
       4,     4,     4,     4,     4,   469,     4,     4,   187,     4,
       4,     4,   189,   411,     4,   189,   189,   435,     4,     4,
     348,   189,     4,     4,   187,     4,   187,   187,     4,     4,
     189,   189,     4,     4,     4,     4,   533,     4,   187,   564,
       4,     7,     7,     7,     7,   186,   186,   186,     7,     7,
       5,   186,   158,   159,   160,   161,   189,   248,   186,   186,
       5,     5,     5,     5,   207,   209,   186,   100,   101,   102,
     103,   389,     5,     5,     5,     5,     7,     7,     7,     7,
       7,   186,   186,     5,     5,   216,    17,    18,   270,    20,
      21,   273,   186,   186,   186,     5,   186,   186,   216,   186,
       7,   186,   216,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   209,   186,   186,
     186,    18,   156,   544,   157,   248,   186,   186,   186,     5,
     205,   227,   563,   262,    24,   279,   280,   281,    34,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,   220,   291,   292,
     293,   296,   298,   300,   302,   303,   305,   306,   307,   308,
     309,   310,   311,   312,   314,   316,   318,   320,   321,   322,
     291,     7,   287,   288,   289,     7,   365,   366,   367,     7,
     403,   404,   405,     7,   427,   428,   429,     7,   393,   394,
     395,   111,   112,   113,   114,   116,   325,   326,   327,   328,
     329,   330,   331,     7,   499,   500,     7,   461,   462,   463,
       7,   341,   342,   343,   124,   125,   126,   127,   128,   129,
     355,   356,   357,   358,   359,   360,   361,   362,   132,   133,
     134,   220,   334,   335,   336,   337,   338,   455,   457,   136,
     137,   220,   455,   457,   512,   513,   514,   516,   139,   140,
     141,   186,   455,   457,   520,   521,   522,   523,   525,   526,
     532,     7,   570,   571,   217,     7,   445,   446,   447,   119,
     476,   478,   496,   287,     8,     8,     8,   282,     3,     8,
     294,   297,   299,   301,     4,     4,     4,     4,     4,   313,
     315,   317,   319,     4,     4,     4,     4,     4,     4,     3,
       8,     8,   290,     6,     3,   368,     6,     3,   406,     6,
       3,   430,     6,     3,   396,     6,     3,     3,     6,   501,
       3,     6,   464,     6,     3,   344,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   515,   517,     3,     8,     4,   524,     4,   527,     3,
       8,     8,   572,     3,     6,   186,   218,   219,   448,     6,
       3,   479,     8,     6,     4,   280,     4,     4,     4,     4,
     187,   189,   187,   189,   187,     4,     4,     4,     4,   187,
     187,   187,   187,   189,   187,   292,   291,   289,   371,   367,
     409,   405,   433,   429,   220,   229,   230,   231,   232,   233,
     234,   235,   236,   241,   242,   243,   244,   245,   246,   249,
     251,   253,   255,   257,   303,   363,   381,   383,   385,   387,
     397,   398,   425,   455,   457,   470,   472,   474,   494,   395,
     326,   107,   108,   220,   303,   399,   425,   455,   457,   470,
     472,   474,   502,   503,   504,   505,   506,   508,   500,   467,
     463,   347,   343,   187,   187,   187,   187,   187,   187,   356,
     189,   187,   187,   335,     4,     4,   513,   189,     4,   187,
       4,   521,   165,   167,   168,   220,   303,   455,   457,   573,
     574,   575,   576,   578,   571,     6,     3,   451,   447,     4,
     186,    35,    36,    37,    38,   295,   186,   186,   186,   186,
     186,   186,   186,     8,     8,     8,     8,     3,     8,   507,
       4,     8,     3,     8,     8,   186,   186,   186,   205,   579,
       4,   577,     3,     8,   186,     8,   216,   398,     4,   189,
     504,     4,   187,     4,   574,   186,     5,   186,     7,   580,
     581,   582,     3,     6,   166,   169,   170,   171,   172,   583,
     584,   585,   587,   588,   589,   590,   581,   586,     4,     4,
       4,   591,     3,     8,     4,   189,   187,   187,     4,   584,
     186,   186
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   190,   192,   191,   193,   191,   194,   191,   195,   191,
     196,   191,   197,   191,   198,   191,   199,   191,   200,   191,
     201,   191,   202,   191,   203,   191,   204,   191,   205,   205,
     205,   205,   205,   205,   205,   206,   208,   207,   209,   210,
     210,   211,   211,   213,   212,   214,   214,   215,   215,   217,
     216,   218,   218,   219,   219,   220,   222,   221,   224,   223,
     226,   225,   227,   227,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   239,   238,   240,   241,   242,
     243,   244,   245,   247,   246,   248,   248,   248,   248,   248,
     250,   249,   252,   251,   254,   253,   256,   255,   257,   258,
     259,   261,   260,   262,   262,   263,   263,   263,   263,   263,
     263,   263,   265,   264,   267,   266,   269,   268,   270,   270,
     272,   271,   273,   273,   274,   276,   275,   278,   277,   279,
     279,   280,   282,   281,   284,   283,   286,   285,   287,   287,
     288,   288,   290,   289,   291,   291,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   294,   293,   295,
     295,   295,   295,   297,   296,   299,   298,   301,   300,   302,
     304,   303,   305,   306,   307,   308,   309,   310,   311,   313,
     312,   315,   314,   317,   316,   319,   318,   320,   321,   322,
     324,   323,   325,   325,   326,   326,   326,   326,   326,   327,
     328,   329,   330,   331,   333,   332,   334,   334,   335,   335,
     335,   335,   335,   335,   336,   337,   338,   340,   339,   341,
     341,   342,   342,   344,   343,   346,   345,   347,   347,   347,
     348,   348,   350,   349,   352,   351,   354,   353,   355,   355,
     356,   356,   356,   356,   356,   356,   357,   358,   359,   360,
     361,   362,   364,   363,   365,   365,   366,   366,   368,   367,
     370,   369,   371,   371,   372,   372,   372,   372,   372,   372,
     372,   372,   372,   372,   372,   372,   372,   372,   372,   372,
     372,   372,   372,   372,   372,   372,   372,   372,   372,   372,
     372,   372,   372,   372,   372,   372,   372,   372,   372,   372,
     372,   372,   374,   373,   376,   375,   378,   377,   380,   379,
     382,   381,   384,   383,   386,   385,   388,   387,   389,   389,
     389,   389,   390,   392,   391,   393,   393,   394,   394,   396,
     395,   397,   397,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   400,   399,   402,   401,
     403,   403,   404,   404,   406,   405,   408,   407,   409,   409,
     410,   410,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   412,   413,   414,   416,   415,   418,   417,   420,
     419,   421,   423,   422,   424,   426,   425,   427,   427,   428,
     428,   430,   429,   432,   431,   433,   433,   434,   434,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   436,   438,
     437,   439,   440,   441,   442,   444,   443,   445,   445,   446,
     446,   448,   447,   450,   449,   451,   451,   452,   452,   452,
     452,   452,   452,   452,   454,   453,   456,   455,   458,   457,
     460,   459,   461,   461,   462,   462,   464,   463,   466,   465,
     467,   467,   468,   468,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   471,
     470,   473,   472,   475,   474,   477,   476,   479,   478,   481,
     480,   483,   482,   485,   484,   487,   486,   489,   488,   491,
     490,   493,   492,   495,   494,   496,   496,   498,   497,   499,
     499,   501,   500,   502,   502,   503,   503,   504,   504,   504,
     504,   504,   504,   504,   504,   504,   504,   504,   505,   507,
     506,   508,   509,   511,   510,   512,   512,   513,   513,   513,
     513,   513,   515,   514,   517,   516,   519,   518,   520,   520,
     521,   521,   521,   521,   521,   521,   522,   524,   523,   525,
     527,   526,   529,   528,   531,   530,   532,   532,   533,   533,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   534,   536,   535,   537,
     539,   538,   540,   541,   543,   542,   544,   544,   546,   545,
     548,   547,   549,   550,   552,   551,   554,   553,   556,   555,
     558,   557,   560,   559,   562,   561,   563,   563,   564,   564,
     566,   565,   567,   569,   568,   570,   570,   572,   571,   573,
     573,   574,   574,   574,   574,   574,   574,   574,   575,   577,
     576,   579,   578,   580,   580,   582,   581,   583,   583,   584,
     584,   584,   584,   584,   586,   585,   587,   588,   589,   591,
     590
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
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     1,     1,
       0,     4,     1,     1,     3,     0,     6,     0,     6,     1,
       3,     1,     0,     4,     0,     6,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       0,     6,     3,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4
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
  "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@20", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@21", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@22", "ddns_qualifying_suffix", "$@23",
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
       0,   277,   277,   277,   278,   278,   279,   279,   280,   280,
     281,   281,   282,   282,   283,   283,   284,   284,   285,   285,
     286,   286,   287,   287,   288,   288,   289,   289,   297,   298,
     299,   300,   301,   302,   303,   306,   311,   311,   322,   325,
     326,   329,   334,   342,   342,   349,   350,   353,   357,   364,
     364,   371,   372,   375,   379,   390,   399,   399,   414,   414,
     431,   431,   440,   441,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   500,   506,   512,   518,
     524,   530,   536,   542,   548,   554,   554,   563,   569,   575,
     581,   587,   593,   599,   599,   608,   611,   614,   617,   620,
     626,   626,   635,   635,   644,   644,   653,   653,   662,   668,
     674,   680,   680,   692,   693,   696,   697,   698,   699,   700,
     701,   702,   705,   705,   714,   714,   725,   725,   733,   734,
     737,   737,   745,   747,   751,   758,   758,   771,   771,   782,
     783,   785,   787,   787,   806,   806,   819,   819,   830,   831,
     834,   835,   838,   838,   848,   849,   852,   853,   854,   855,
     856,   857,   858,   859,   860,   861,   862,   863,   864,   865,
     866,   867,   868,   869,   870,   871,   872,   875,   875,   883,
     884,   885,   886,   889,   889,   898,   898,   907,   907,   916,
     922,   922,   931,   937,   943,   949,   955,   961,   967,   973,
     973,   982,   982,   991,   991,  1000,  1000,  1009,  1015,  1021,
    1028,  1028,  1039,  1040,  1043,  1044,  1045,  1046,  1047,  1050,
    1055,  1060,  1065,  1070,  1077,  1077,  1090,  1091,  1094,  1095,
    1096,  1097,  1098,  1099,  1102,  1108,  1114,  1120,  1120,  1131,
    1132,  1135,  1136,  1139,  1139,  1149,  1149,  1159,  1160,  1161,
    1164,  1165,  1168,  1168,  1177,  1177,  1186,  1186,  1198,  1199,
    1202,  1203,  1204,  1205,  1206,  1207,  1210,  1216,  1222,  1228,
    1234,  1240,  1249,  1249,  1263,  1264,  1267,  1268,  1275,  1275,
    1301,  1301,  1312,  1313,  1317,  1318,  1319,  1320,  1321,  1322,
    1323,  1324,  1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,
    1333,  1334,  1335,  1336,  1337,  1338,  1339,  1340,  1341,  1342,
    1343,  1344,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,
    1353,  1354,  1357,  1357,  1366,  1366,  1375,  1375,  1384,  1384,
    1393,  1393,  1402,  1402,  1411,  1411,  1422,  1422,  1430,  1431,
    1432,  1433,  1436,  1444,  1444,  1456,  1457,  1461,  1462,  1465,
    1465,  1473,  1474,  1477,  1478,  1479,  1480,  1481,  1482,  1483,
    1484,  1485,  1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,
    1494,  1495,  1496,  1497,  1498,  1499,  1500,  1501,  1502,  1503,
    1504,  1505,  1506,  1507,  1508,  1509,  1516,  1516,  1530,  1530,
    1539,  1540,  1543,  1544,  1549,  1549,  1564,  1564,  1578,  1579,
    1582,  1583,  1586,  1587,  1588,  1589,  1590,  1591,  1592,  1593,
    1594,  1595,  1598,  1600,  1606,  1608,  1608,  1617,  1617,  1626,
    1626,  1635,  1637,  1637,  1646,  1656,  1656,  1669,  1670,  1675,
    1676,  1681,  1681,  1693,  1693,  1705,  1706,  1711,  1712,  1717,
    1718,  1719,  1720,  1721,  1722,  1723,  1724,  1725,  1728,  1730,
    1730,  1739,  1741,  1743,  1749,  1758,  1758,  1771,  1772,  1775,
    1776,  1779,  1779,  1789,  1789,  1799,  1800,  1803,  1804,  1805,
    1806,  1807,  1808,  1809,  1812,  1812,  1821,  1821,  1846,  1846,
    1876,  1876,  1887,  1888,  1891,  1892,  1895,  1895,  1904,  1904,
    1913,  1914,  1917,  1918,  1922,  1923,  1924,  1925,  1926,  1927,
    1928,  1929,  1930,  1931,  1932,  1933,  1934,  1935,  1936,  1939,
    1939,  1948,  1948,  1957,  1957,  1966,  1966,  1975,  1975,  1986,
    1986,  1995,  1995,  2004,  2004,  2013,  2013,  2022,  2022,  2031,
    2031,  2040,  2040,  2054,  2054,  2065,  2066,  2072,  2072,  2083,
    2084,  2087,  2087,  2097,  2098,  2101,  2102,  2105,  2106,  2107,
    2108,  2109,  2110,  2111,  2112,  2113,  2114,  2115,  2118,  2120,
    2120,  2129,  2137,  2145,  2145,  2156,  2157,  2160,  2161,  2162,
    2163,  2164,  2167,  2167,  2176,  2176,  2188,  2188,  2201,  2202,
    2205,  2206,  2207,  2208,  2209,  2210,  2213,  2219,  2219,  2228,
    2234,  2234,  2244,  2244,  2257,  2257,  2267,  2268,  2271,  2272,
    2273,  2274,  2275,  2276,  2277,  2278,  2279,  2280,  2281,  2282,
    2283,  2284,  2285,  2286,  2287,  2288,  2291,  2297,  2297,  2306,
    2312,  2312,  2321,  2327,  2333,  2333,  2342,  2343,  2346,  2346,
    2356,  2356,  2366,  2373,  2380,  2380,  2389,  2389,  2399,  2399,
    2409,  2409,  2421,  2421,  2433,  2433,  2443,  2444,  2448,  2449,
    2452,  2452,  2463,  2471,  2471,  2484,  2485,  2489,  2489,  2497,
    2498,  2501,  2502,  2503,  2504,  2505,  2506,  2507,  2510,  2516,
    2516,  2525,  2525,  2536,  2537,  2540,  2540,  2548,  2549,  2552,
    2553,  2554,  2555,  2556,  2559,  2559,  2568,  2574,  2580,  2586,
    2586
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
#line 5569 "dhcp4_parser.cc"

#line 2595 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
