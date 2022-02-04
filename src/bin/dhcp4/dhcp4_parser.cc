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
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 291 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 291 "dhcp4_parser.yy"
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
#line 300 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 301 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 302 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 303 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 304 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 305 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 306 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 307 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 308 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 309 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 310 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 311 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 312 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 320 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 321 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 322 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 323 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 324 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 325 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 326 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 329 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 334 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 339 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 345 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 352 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 357 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 363 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 368 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 371 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 379 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 383 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 387 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 393 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 395 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 404 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 408 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 412 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 422 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 431 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 436 "dhcp4_parser.yy"
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
#line 446 "dhcp4_parser.yy"
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
#line 455 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 463 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 469 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 473 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 480 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 134: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 553 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 135: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 559 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 136: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 565 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 137: // renew_timer: "renew-timer" ":" "integer"
#line 571 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 138: // rebind_timer: "rebind-timer" ":" "integer"
#line 577 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 139: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 583 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 140: // t1_percent: "t1-percent" ":" "floating point"
#line 589 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 141: // t2_percent: "t2-percent" ":" "floating point"
#line 595 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 142: // cache_threshold: "cache-threshold" ":" "floating point"
#line 601 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 143: // cache_max_age: "cache-max-age" ":" "integer"
#line 607 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 144: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 613 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 145: // $@20: %empty
#line 619 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 146: // server_tag: "server-tag" $@20 ":" "constant string"
#line 622 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 147: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 628 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 148: // echo_client_id: "echo-client-id" ":" "boolean"
#line 634 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 149: // match_client_id: "match-client-id" ":" "boolean"
#line 640 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1280 "dhcp4_parser.cc"
    break;

  case 150: // authoritative: "authoritative" ":" "boolean"
#line 646 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1290 "dhcp4_parser.cc"
    break;

  case 151: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 652 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1300 "dhcp4_parser.cc"
    break;

  case 152: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 658 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1310 "dhcp4_parser.cc"
    break;

  case 153: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 664 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 154: // $@21: %empty
#line 670 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 155: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 673 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "when-present"
#line 679 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1346 "dhcp4_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "never"
#line 682 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1354 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "always"
#line 685 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1362 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-not-present"
#line 688 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "boolean"
#line 691 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1379 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 697 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1388 "dhcp4_parser.cc"
    break;

  case 162: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 700 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1398 "dhcp4_parser.cc"
    break;

  case 163: // $@23: %empty
#line 706 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 164: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 709 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 165: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 715 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1427 "dhcp4_parser.cc"
    break;

  case 166: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 721 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1437 "dhcp4_parser.cc"
    break;

  case 167: // $@24: %empty
#line 727 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 168: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 730 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 169: // $@25: %empty
#line 736 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 170: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 739 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 171: // store_extended_info: "store-extended-info" ":" "boolean"
#line 745 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 172: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 751 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 173: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 757 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 174: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 763 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 175: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 769 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 176: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 775 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1535 "dhcp4_parser.cc"
    break;

  case 177: // $@26: %empty
#line 781 "dhcp4_parser.yy"
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
#line 787 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1557 "dhcp4_parser.cc"
    break;

  case 181: // interfaces_config_params: interfaces_config_params ","
#line 795 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1565 "dhcp4_parser.cc"
    break;

  case 189: // $@27: %empty
#line 809 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 190: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 813 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 191: // $@28: %empty
#line 818 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 192: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 824 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1605 "dhcp4_parser.cc"
    break;

  case 193: // $@29: %empty
#line 829 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 194: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 832 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 195: // socket_type: "raw"
#line 837 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1629 "dhcp4_parser.cc"
    break;

  case 196: // socket_type: "udp"
#line 838 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1635 "dhcp4_parser.cc"
    break;

  case 197: // $@30: %empty
#line 841 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 198: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 844 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1653 "dhcp4_parser.cc"
    break;

  case 199: // outbound_interface_value: "same-as-inbound"
#line 849 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1661 "dhcp4_parser.cc"
    break;

  case 200: // outbound_interface_value: "use-routing"
#line 851 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1669 "dhcp4_parser.cc"
    break;

  case 201: // re_detect: "re-detect" ":" "boolean"
#line 855 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1679 "dhcp4_parser.cc"
    break;

  case 202: // $@31: %empty
#line 862 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1691 "dhcp4_parser.cc"
    break;

  case 203: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 868 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1702 "dhcp4_parser.cc"
    break;

  case 204: // $@32: %empty
#line 875 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1714 "dhcp4_parser.cc"
    break;

  case 205: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 881 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1723 "dhcp4_parser.cc"
    break;

  case 208: // sanity_checks_params: sanity_checks_params ","
#line 888 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1731 "dhcp4_parser.cc"
    break;

  case 210: // $@33: %empty
#line 895 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1740 "dhcp4_parser.cc"
    break;

  case 211: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 898 "dhcp4_parser.yy"
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
#line 1760 "dhcp4_parser.cc"
    break;

  case 212: // $@34: %empty
#line 914 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 213: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 920 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 214: // $@35: %empty
#line 927 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1795 "dhcp4_parser.cc"
    break;

  case 215: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 933 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1804 "dhcp4_parser.cc"
    break;

  case 220: // not_empty_database_list: not_empty_database_list ","
#line 944 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1812 "dhcp4_parser.cc"
    break;

  case 221: // $@36: %empty
#line 949 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1822 "dhcp4_parser.cc"
    break;

  case 222: // database: "{" $@36 database_map_params "}"
#line 953 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1832 "dhcp4_parser.cc"
    break;

  case 225: // database_map_params: database_map_params ","
#line 961 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1840 "dhcp4_parser.cc"
    break;

  case 252: // $@37: %empty
#line 994 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1849 "dhcp4_parser.cc"
    break;

  case 253: // database_type: "type" $@37 ":" db_type
#line 997 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1858 "dhcp4_parser.cc"
    break;

  case 254: // db_type: "memfile"
#line 1002 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1864 "dhcp4_parser.cc"
    break;

  case 255: // db_type: "mysql"
#line 1003 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1870 "dhcp4_parser.cc"
    break;

  case 256: // db_type: "postgresql"
#line 1004 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1876 "dhcp4_parser.cc"
    break;

  case 257: // db_type: "cql"
#line 1005 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1882 "dhcp4_parser.cc"
    break;

  case 258: // $@38: %empty
#line 1008 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1891 "dhcp4_parser.cc"
    break;

  case 259: // user: "user" $@38 ":" "constant string"
#line 1011 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1901 "dhcp4_parser.cc"
    break;

  case 260: // $@39: %empty
#line 1017 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1910 "dhcp4_parser.cc"
    break;

  case 261: // password: "password" $@39 ":" "constant string"
#line 1020 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1920 "dhcp4_parser.cc"
    break;

  case 262: // $@40: %empty
#line 1026 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1929 "dhcp4_parser.cc"
    break;

  case 263: // host: "host" $@40 ":" "constant string"
#line 1029 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1939 "dhcp4_parser.cc"
    break;

  case 264: // port: "port" ":" "integer"
#line 1035 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1949 "dhcp4_parser.cc"
    break;

  case 265: // $@41: %empty
#line 1041 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1958 "dhcp4_parser.cc"
    break;

  case 266: // name: "name" $@41 ":" "constant string"
#line 1044 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1968 "dhcp4_parser.cc"
    break;

  case 267: // persist: "persist" ":" "boolean"
#line 1050 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1978 "dhcp4_parser.cc"
    break;

  case 268: // lfc_interval: "lfc-interval" ":" "integer"
#line 1056 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1988 "dhcp4_parser.cc"
    break;

  case 269: // readonly: "readonly" ":" "boolean"
#line 1062 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 270: // connect_timeout: "connect-timeout" ":" "integer"
#line 1068 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2008 "dhcp4_parser.cc"
    break;

  case 271: // request_timeout: "request-timeout" ":" "integer"
#line 1074 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 2018 "dhcp4_parser.cc"
    break;

  case 272: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1080 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 2028 "dhcp4_parser.cc"
    break;

  case 273: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1086 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 2038 "dhcp4_parser.cc"
    break;

  case 274: // $@42: %empty
#line 1092 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp4_parser.cc"
    break;

  case 275: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1095 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 2057 "dhcp4_parser.cc"
    break;

  case 276: // $@43: %empty
#line 1101 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2066 "dhcp4_parser.cc"
    break;

  case 277: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1104 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 2076 "dhcp4_parser.cc"
    break;

  case 278: // $@44: %empty
#line 1110 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2085 "dhcp4_parser.cc"
    break;

  case 279: // consistency: "consistency" $@44 ":" "constant string"
#line 1113 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc"
    break;

  case 280: // $@45: %empty
#line 1119 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2104 "dhcp4_parser.cc"
    break;

  case 281: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1122 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2114 "dhcp4_parser.cc"
    break;

  case 282: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1128 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2124 "dhcp4_parser.cc"
    break;

  case 283: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1134 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 284: // $@46: %empty
#line 1140 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2143 "dhcp4_parser.cc"
    break;

  case 285: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1143 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 286: // on_fail_mode: "stop-retry-exit"
#line 1148 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2158 "dhcp4_parser.cc"
    break;

  case 287: // on_fail_mode: "serve-retry-exit"
#line 1149 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2164 "dhcp4_parser.cc"
    break;

  case 288: // on_fail_mode: "serve-retry-continue"
#line 1150 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2170 "dhcp4_parser.cc"
    break;

  case 289: // max_row_errors: "max-row-errors" ":" "integer"
#line 1153 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2180 "dhcp4_parser.cc"
    break;

  case 290: // $@47: %empty
#line 1159 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2189 "dhcp4_parser.cc"
    break;

  case 291: // trust_anchor: "trust-anchor" $@47 ":" "constant string"
#line 1162 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2199 "dhcp4_parser.cc"
    break;

  case 292: // $@48: %empty
#line 1168 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2208 "dhcp4_parser.cc"
    break;

  case 293: // cert_file: "cert-file" $@48 ":" "constant string"
#line 1171 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2218 "dhcp4_parser.cc"
    break;

  case 294: // $@49: %empty
#line 1177 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp4_parser.cc"
    break;

  case 295: // key_file: "key-file" $@49 ":" "constant string"
#line 1180 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2237 "dhcp4_parser.cc"
    break;

  case 296: // $@50: %empty
#line 1186 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2246 "dhcp4_parser.cc"
    break;

  case 297: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1189 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2256 "dhcp4_parser.cc"
    break;

  case 298: // $@51: %empty
#line 1195 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2268 "dhcp4_parser.cc"
    break;

  case 299: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1201 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2277 "dhcp4_parser.cc"
    break;

  case 302: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1208 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2285 "dhcp4_parser.cc"
    break;

  case 308: // duid_id: "duid"
#line 1220 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2294 "dhcp4_parser.cc"
    break;

  case 309: // hw_address_id: "hw-address"
#line 1225 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2303 "dhcp4_parser.cc"
    break;

  case 310: // circuit_id: "circuit-id"
#line 1230 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2312 "dhcp4_parser.cc"
    break;

  case 311: // client_id: "client-id"
#line 1235 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2321 "dhcp4_parser.cc"
    break;

  case 312: // flex_id: "flex-id"
#line 1240 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2330 "dhcp4_parser.cc"
    break;

  case 313: // $@52: %empty
#line 1247 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2342 "dhcp4_parser.cc"
    break;

  case 314: // dhcp_multi_threading: "multi-threading" $@52 ":" "{" multi_threading_params "}"
#line 1253 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2353 "dhcp4_parser.cc"
    break;

  case 317: // multi_threading_params: multi_threading_params ","
#line 1262 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2361 "dhcp4_parser.cc"
    break;

  case 324: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1275 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2371 "dhcp4_parser.cc"
    break;

  case 325: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1281 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2381 "dhcp4_parser.cc"
    break;

  case 326: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1287 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2391 "dhcp4_parser.cc"
    break;

  case 327: // $@53: %empty
#line 1293 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2403 "dhcp4_parser.cc"
    break;

  case 328: // hooks_libraries: "hooks-libraries" $@53 ":" "[" hooks_libraries_list "]"
#line 1299 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2412 "dhcp4_parser.cc"
    break;

  case 333: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1310 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2420 "dhcp4_parser.cc"
    break;

  case 334: // $@54: %empty
#line 1315 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2430 "dhcp4_parser.cc"
    break;

  case 335: // hooks_library: "{" $@54 hooks_params "}"
#line 1319 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2440 "dhcp4_parser.cc"
    break;

  case 336: // $@55: %empty
#line 1325 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2450 "dhcp4_parser.cc"
    break;

  case 337: // sub_hooks_library: "{" $@55 hooks_params "}"
#line 1329 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2460 "dhcp4_parser.cc"
    break;

  case 340: // hooks_params: hooks_params ","
#line 1337 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2468 "dhcp4_parser.cc"
    break;

  case 344: // $@56: %empty
#line 1347 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2477 "dhcp4_parser.cc"
    break;

  case 345: // library: "library" $@56 ":" "constant string"
#line 1350 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2487 "dhcp4_parser.cc"
    break;

  case 346: // $@57: %empty
#line 1356 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2496 "dhcp4_parser.cc"
    break;

  case 347: // parameters: "parameters" $@57 ":" map_value
#line 1359 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2505 "dhcp4_parser.cc"
    break;

  case 348: // $@58: %empty
#line 1365 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2517 "dhcp4_parser.cc"
    break;

  case 349: // expired_leases_processing: "expired-leases-processing" $@58 ":" "{" expired_leases_params "}"
#line 1371 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2527 "dhcp4_parser.cc"
    break;

  case 352: // expired_leases_params: expired_leases_params ","
#line 1379 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2535 "dhcp4_parser.cc"
    break;

  case 359: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1392 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2545 "dhcp4_parser.cc"
    break;

  case 360: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1398 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2555 "dhcp4_parser.cc"
    break;

  case 361: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1404 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 362: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1410 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2575 "dhcp4_parser.cc"
    break;

  case 363: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1416 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2585 "dhcp4_parser.cc"
    break;

  case 364: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1422 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 365: // $@59: %empty
#line 1431 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2607 "dhcp4_parser.cc"
    break;

  case 366: // subnet4_list: "subnet4" $@59 ":" "[" subnet4_list_content "]"
#line 1437 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2616 "dhcp4_parser.cc"
    break;

  case 371: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1451 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2624 "dhcp4_parser.cc"
    break;

  case 372: // $@60: %empty
#line 1460 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2634 "dhcp4_parser.cc"
    break;

  case 373: // subnet4: "{" $@60 subnet4_params "}"
#line 1464 "dhcp4_parser.yy"
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
#line 2660 "dhcp4_parser.cc"
    break;

  case 374: // $@61: %empty
#line 1486 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2670 "dhcp4_parser.cc"
    break;

  case 375: // sub_subnet4: "{" $@61 subnet4_params "}"
#line 1490 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2680 "dhcp4_parser.cc"
    break;

  case 378: // subnet4_params: subnet4_params ","
#line 1499 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2688 "dhcp4_parser.cc"
    break;

  case 424: // $@62: %empty
#line 1552 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2697 "dhcp4_parser.cc"
    break;

  case 425: // subnet: "subnet" $@62 ":" "constant string"
#line 1555 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2707 "dhcp4_parser.cc"
    break;

  case 426: // $@63: %empty
#line 1561 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp4_parser.cc"
    break;

  case 427: // subnet_4o6_interface: "4o6-interface" $@63 ":" "constant string"
#line 1564 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc"
    break;

  case 428: // $@64: %empty
#line 1570 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2735 "dhcp4_parser.cc"
    break;

  case 429: // subnet_4o6_interface_id: "4o6-interface-id" $@64 ":" "constant string"
#line 1573 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2745 "dhcp4_parser.cc"
    break;

  case 430: // $@65: %empty
#line 1579 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2754 "dhcp4_parser.cc"
    break;

  case 431: // subnet_4o6_subnet: "4o6-subnet" $@65 ":" "constant string"
#line 1582 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2764 "dhcp4_parser.cc"
    break;

  case 432: // $@66: %empty
#line 1588 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2773 "dhcp4_parser.cc"
    break;

  case 433: // interface: "interface" $@66 ":" "constant string"
#line 1591 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2783 "dhcp4_parser.cc"
    break;

  case 434: // $@67: %empty
#line 1597 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 435: // client_class: "client-class" $@67 ":" "constant string"
#line 1600 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 436: // $@68: %empty
#line 1606 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2814 "dhcp4_parser.cc"
    break;

  case 437: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1612 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 438: // reservations_global: "reservations-global" ":" "boolean"
#line 1617 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2833 "dhcp4_parser.cc"
    break;

  case 439: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1623 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2843 "dhcp4_parser.cc"
    break;

  case 440: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1629 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2853 "dhcp4_parser.cc"
    break;

  case 441: // $@69: %empty
#line 1635 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2862 "dhcp4_parser.cc"
    break;

  case 442: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1638 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 443: // hr_mode: "disabled"
#line 1643 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2877 "dhcp4_parser.cc"
    break;

  case 444: // hr_mode: "out-of-pool"
#line 1644 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2883 "dhcp4_parser.cc"
    break;

  case 445: // hr_mode: "global"
#line 1645 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2889 "dhcp4_parser.cc"
    break;

  case 446: // hr_mode: "all"
#line 1646 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2895 "dhcp4_parser.cc"
    break;

  case 447: // id: "id" ":" "integer"
#line 1649 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2905 "dhcp4_parser.cc"
    break;

  case 448: // $@70: %empty
#line 1657 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2917 "dhcp4_parser.cc"
    break;

  case 449: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1663 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2926 "dhcp4_parser.cc"
    break;

  case 454: // shared_networks_list: shared_networks_list ","
#line 1676 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2934 "dhcp4_parser.cc"
    break;

  case 455: // $@71: %empty
#line 1681 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2944 "dhcp4_parser.cc"
    break;

  case 456: // shared_network: "{" $@71 shared_network_params "}"
#line 1685 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2952 "dhcp4_parser.cc"
    break;

  case 459: // shared_network_params: shared_network_params ","
#line 1691 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2960 "dhcp4_parser.cc"
    break;

  case 500: // $@72: %empty
#line 1742 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2972 "dhcp4_parser.cc"
    break;

  case 501: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1748 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2981 "dhcp4_parser.cc"
    break;

  case 502: // $@73: %empty
#line 1756 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 503: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1759 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2998 "dhcp4_parser.cc"
    break;

  case 508: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1771 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3006 "dhcp4_parser.cc"
    break;

  case 509: // $@74: %empty
#line 1778 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3016 "dhcp4_parser.cc"
    break;

  case 510: // option_def_entry: "{" $@74 option_def_params "}"
#line 1782 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3028 "dhcp4_parser.cc"
    break;

  case 511: // $@75: %empty
#line 1793 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3038 "dhcp4_parser.cc"
    break;

  case 512: // sub_option_def: "{" $@75 option_def_params "}"
#line 1797 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3050 "dhcp4_parser.cc"
    break;

  case 517: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1813 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3058 "dhcp4_parser.cc"
    break;

  case 529: // code: "code" ":" "integer"
#line 1832 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3068 "dhcp4_parser.cc"
    break;

  case 531: // $@76: %empty
#line 1840 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3077 "dhcp4_parser.cc"
    break;

  case 532: // option_def_type: "type" $@76 ":" "constant string"
#line 1843 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3087 "dhcp4_parser.cc"
    break;

  case 533: // $@77: %empty
#line 1849 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3096 "dhcp4_parser.cc"
    break;

  case 534: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1852 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3106 "dhcp4_parser.cc"
    break;

  case 535: // $@78: %empty
#line 1858 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3115 "dhcp4_parser.cc"
    break;

  case 536: // space: "space" $@78 ":" "constant string"
#line 1861 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3125 "dhcp4_parser.cc"
    break;

  case 538: // $@79: %empty
#line 1869 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3134 "dhcp4_parser.cc"
    break;

  case 539: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1872 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3144 "dhcp4_parser.cc"
    break;

  case 540: // option_def_array: "array" ":" "boolean"
#line 1878 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3154 "dhcp4_parser.cc"
    break;

  case 541: // $@80: %empty
#line 1888 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3166 "dhcp4_parser.cc"
    break;

  case 542: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1894 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3175 "dhcp4_parser.cc"
    break;

  case 547: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1909 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3183 "dhcp4_parser.cc"
    break;

  case 548: // $@81: %empty
#line 1916 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3193 "dhcp4_parser.cc"
    break;

  case 549: // option_data_entry: "{" $@81 option_data_params "}"
#line 1920 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3202 "dhcp4_parser.cc"
    break;

  case 550: // $@82: %empty
#line 1928 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3212 "dhcp4_parser.cc"
    break;

  case 551: // sub_option_data: "{" $@82 option_data_params "}"
#line 1932 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3221 "dhcp4_parser.cc"
    break;

  case 556: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1948 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3229 "dhcp4_parser.cc"
    break;

  case 567: // $@83: %empty
#line 1968 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3238 "dhcp4_parser.cc"
    break;

  case 568: // option_data_data: "data" $@83 ":" "constant string"
#line 1971 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3248 "dhcp4_parser.cc"
    break;

  case 571: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1981 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3258 "dhcp4_parser.cc"
    break;

  case 572: // option_data_always_send: "always-send" ":" "boolean"
#line 1987 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3268 "dhcp4_parser.cc"
    break;

  case 573: // $@84: %empty
#line 1996 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3280 "dhcp4_parser.cc"
    break;

  case 574: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 2002 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3289 "dhcp4_parser.cc"
    break;

  case 579: // not_empty_pools_list: not_empty_pools_list ","
#line 2015 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3297 "dhcp4_parser.cc"
    break;

  case 580: // $@85: %empty
#line 2020 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3307 "dhcp4_parser.cc"
    break;

  case 581: // pool_list_entry: "{" $@85 pool_params "}"
#line 2024 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3317 "dhcp4_parser.cc"
    break;

  case 582: // $@86: %empty
#line 2030 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3327 "dhcp4_parser.cc"
    break;

  case 583: // sub_pool4: "{" $@86 pool_params "}"
#line 2034 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3337 "dhcp4_parser.cc"
    break;

  case 586: // pool_params: pool_params ","
#line 2042 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3345 "dhcp4_parser.cc"
    break;

  case 594: // $@87: %empty
#line 2056 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3354 "dhcp4_parser.cc"
    break;

  case 595: // pool_entry: "pool" $@87 ":" "constant string"
#line 2059 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3364 "dhcp4_parser.cc"
    break;

  case 596: // $@88: %empty
#line 2065 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3372 "dhcp4_parser.cc"
    break;

  case 597: // user_context: "user-context" $@88 ":" map_value
#line 2067 "dhcp4_parser.yy"
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
#line 3399 "dhcp4_parser.cc"
    break;

  case 598: // $@89: %empty
#line 2090 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3407 "dhcp4_parser.cc"
    break;

  case 599: // comment: "comment" $@89 ":" "constant string"
#line 2092 "dhcp4_parser.yy"
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
#line 3436 "dhcp4_parser.cc"
    break;

  case 600: // $@90: %empty
#line 2120 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3448 "dhcp4_parser.cc"
    break;

  case 601: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2126 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3457 "dhcp4_parser.cc"
    break;

  case 606: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2137 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3465 "dhcp4_parser.cc"
    break;

  case 607: // $@91: %empty
#line 2142 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3475 "dhcp4_parser.cc"
    break;

  case 608: // reservation: "{" $@91 reservation_params "}"
#line 2146 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3484 "dhcp4_parser.cc"
    break;

  case 609: // $@92: %empty
#line 2151 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3494 "dhcp4_parser.cc"
    break;

  case 610: // sub_reservation: "{" $@92 reservation_params "}"
#line 2155 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3503 "dhcp4_parser.cc"
    break;

  case 615: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2166 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3511 "dhcp4_parser.cc"
    break;

  case 631: // $@93: %empty
#line 2189 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3520 "dhcp4_parser.cc"
    break;

  case 632: // next_server: "next-server" $@93 ":" "constant string"
#line 2192 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3530 "dhcp4_parser.cc"
    break;

  case 633: // $@94: %empty
#line 2198 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3539 "dhcp4_parser.cc"
    break;

  case 634: // server_hostname: "server-hostname" $@94 ":" "constant string"
#line 2201 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3549 "dhcp4_parser.cc"
    break;

  case 635: // $@95: %empty
#line 2207 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3558 "dhcp4_parser.cc"
    break;

  case 636: // boot_file_name: "boot-file-name" $@95 ":" "constant string"
#line 2210 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3568 "dhcp4_parser.cc"
    break;

  case 637: // $@96: %empty
#line 2216 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3577 "dhcp4_parser.cc"
    break;

  case 638: // ip_address: "ip-address" $@96 ":" "constant string"
#line 2219 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3587 "dhcp4_parser.cc"
    break;

  case 639: // $@97: %empty
#line 2225 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3599 "dhcp4_parser.cc"
    break;

  case 640: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2231 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3608 "dhcp4_parser.cc"
    break;

  case 641: // $@98: %empty
#line 2236 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3617 "dhcp4_parser.cc"
    break;

  case 642: // duid: "duid" $@98 ":" "constant string"
#line 2239 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3627 "dhcp4_parser.cc"
    break;

  case 643: // $@99: %empty
#line 2245 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3636 "dhcp4_parser.cc"
    break;

  case 644: // hw_address: "hw-address" $@99 ":" "constant string"
#line 2248 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3646 "dhcp4_parser.cc"
    break;

  case 645: // $@100: %empty
#line 2254 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3655 "dhcp4_parser.cc"
    break;

  case 646: // client_id_value: "client-id" $@100 ":" "constant string"
#line 2257 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3665 "dhcp4_parser.cc"
    break;

  case 647: // $@101: %empty
#line 2263 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3674 "dhcp4_parser.cc"
    break;

  case 648: // circuit_id_value: "circuit-id" $@101 ":" "constant string"
#line 2266 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3684 "dhcp4_parser.cc"
    break;

  case 649: // $@102: %empty
#line 2272 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3693 "dhcp4_parser.cc"
    break;

  case 650: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2275 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3703 "dhcp4_parser.cc"
    break;

  case 651: // $@103: %empty
#line 2281 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 652: // hostname: "hostname" $@103 ":" "constant string"
#line 2284 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 653: // $@104: %empty
#line 2290 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3734 "dhcp4_parser.cc"
    break;

  case 654: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2296 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3743 "dhcp4_parser.cc"
    break;

  case 655: // $@105: %empty
#line 2304 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3755 "dhcp4_parser.cc"
    break;

  case 656: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2310 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3764 "dhcp4_parser.cc"
    break;

  case 659: // $@106: %empty
#line 2322 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3776 "dhcp4_parser.cc"
    break;

  case 660: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2328 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3785 "dhcp4_parser.cc"
    break;

  case 663: // client_classes_list: client_classes_list ","
#line 2335 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3793 "dhcp4_parser.cc"
    break;

  case 664: // $@107: %empty
#line 2340 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3803 "dhcp4_parser.cc"
    break;

  case 665: // client_class_entry: "{" $@107 client_class_params "}"
#line 2344 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3813 "dhcp4_parser.cc"
    break;

  case 670: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2356 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3821 "dhcp4_parser.cc"
    break;

  case 686: // $@108: %empty
#line 2379 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 687: // client_class_test: "test" $@108 ":" "constant string"
#line 2382 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3840 "dhcp4_parser.cc"
    break;

  case 688: // only_if_required: "only-if-required" ":" "boolean"
#line 2388 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3850 "dhcp4_parser.cc"
    break;

  case 689: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2396 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3860 "dhcp4_parser.cc"
    break;

  case 690: // $@109: %empty
#line 2404 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 691: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2410 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3881 "dhcp4_parser.cc"
    break;

  case 694: // control_socket_params: control_socket_params ","
#line 2417 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3889 "dhcp4_parser.cc"
    break;

  case 700: // $@110: %empty
#line 2429 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3898 "dhcp4_parser.cc"
    break;

  case 701: // control_socket_type: "socket-type" $@110 ":" "constant string"
#line 2432 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3908 "dhcp4_parser.cc"
    break;

  case 702: // $@111: %empty
#line 2438 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3917 "dhcp4_parser.cc"
    break;

  case 703: // control_socket_name: "socket-name" $@111 ":" "constant string"
#line 2441 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3927 "dhcp4_parser.cc"
    break;

  case 704: // $@112: %empty
#line 2450 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3939 "dhcp4_parser.cc"
    break;

  case 705: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2456 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3950 "dhcp4_parser.cc"
    break;

  case 708: // queue_control_params: queue_control_params ","
#line 2465 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3958 "dhcp4_parser.cc"
    break;

  case 715: // enable_queue: "enable-queue" ":" "boolean"
#line 2478 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3968 "dhcp4_parser.cc"
    break;

  case 716: // $@113: %empty
#line 2484 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 717: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2487 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3987 "dhcp4_parser.cc"
    break;

  case 718: // capacity: "capacity" ":" "integer"
#line 2493 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3997 "dhcp4_parser.cc"
    break;

  case 719: // $@114: %empty
#line 2499 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4006 "dhcp4_parser.cc"
    break;

  case 720: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2502 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4015 "dhcp4_parser.cc"
    break;

  case 721: // $@115: %empty
#line 2509 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4027 "dhcp4_parser.cc"
    break;

  case 722: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2515 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4038 "dhcp4_parser.cc"
    break;

  case 723: // $@116: %empty
#line 2522 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4048 "dhcp4_parser.cc"
    break;

  case 724: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2526 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4058 "dhcp4_parser.cc"
    break;

  case 727: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2534 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4066 "dhcp4_parser.cc"
    break;

  case 746: // enable_updates: "enable-updates" ":" "boolean"
#line 2559 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4076 "dhcp4_parser.cc"
    break;

  case 747: // $@117: %empty
#line 2565 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4085 "dhcp4_parser.cc"
    break;

  case 748: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2568 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4095 "dhcp4_parser.cc"
    break;

  case 749: // server_port: "server-port" ":" "integer"
#line 2574 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4105 "dhcp4_parser.cc"
    break;

  case 750: // $@118: %empty
#line 2580 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 751: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2583 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 752: // sender_port: "sender-port" ":" "integer"
#line 2589 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4134 "dhcp4_parser.cc"
    break;

  case 753: // max_queue_size: "max-queue-size" ":" "integer"
#line 2595 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4144 "dhcp4_parser.cc"
    break;

  case 754: // $@119: %empty
#line 2601 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4153 "dhcp4_parser.cc"
    break;

  case 755: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2604 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4162 "dhcp4_parser.cc"
    break;

  case 756: // ncr_protocol_value: "udp"
#line 2610 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4168 "dhcp4_parser.cc"
    break;

  case 757: // ncr_protocol_value: "tcp"
#line 2611 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4174 "dhcp4_parser.cc"
    break;

  case 758: // $@120: %empty
#line 2614 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4183 "dhcp4_parser.cc"
    break;

  case 759: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2617 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4193 "dhcp4_parser.cc"
    break;

  case 760: // $@121: %empty
#line 2624 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4202 "dhcp4_parser.cc"
    break;

  case 761: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2627 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4212 "dhcp4_parser.cc"
    break;

  case 762: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2634 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4222 "dhcp4_parser.cc"
    break;

  case 763: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2641 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4232 "dhcp4_parser.cc"
    break;

  case 764: // $@122: %empty
#line 2648 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4241 "dhcp4_parser.cc"
    break;

  case 765: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2651 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4250 "dhcp4_parser.cc"
    break;

  case 766: // $@123: %empty
#line 2657 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4259 "dhcp4_parser.cc"
    break;

  case 767: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2660 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4269 "dhcp4_parser.cc"
    break;

  case 768: // $@124: %empty
#line 2667 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4278 "dhcp4_parser.cc"
    break;

  case 769: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2670 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4288 "dhcp4_parser.cc"
    break;

  case 770: // $@125: %empty
#line 2677 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4297 "dhcp4_parser.cc"
    break;

  case 771: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2680 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4307 "dhcp4_parser.cc"
    break;

  case 772: // $@126: %empty
#line 2689 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4319 "dhcp4_parser.cc"
    break;

  case 773: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2695 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4329 "dhcp4_parser.cc"
    break;

  case 774: // $@127: %empty
#line 2701 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4339 "dhcp4_parser.cc"
    break;

  case 775: // sub_config_control: "{" $@127 config_control_params "}"
#line 2705 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4348 "dhcp4_parser.cc"
    break;

  case 778: // config_control_params: config_control_params ","
#line 2713 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4356 "dhcp4_parser.cc"
    break;

  case 781: // $@128: %empty
#line 2723 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4368 "dhcp4_parser.cc"
    break;

  case 782: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2729 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4377 "dhcp4_parser.cc"
    break;

  case 783: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2734 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4387 "dhcp4_parser.cc"
    break;

  case 784: // $@129: %empty
#line 2742 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4399 "dhcp4_parser.cc"
    break;

  case 785: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2748 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4408 "dhcp4_parser.cc"
    break;

  case 788: // loggers_entries: loggers_entries ","
#line 2757 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4416 "dhcp4_parser.cc"
    break;

  case 789: // $@130: %empty
#line 2763 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4426 "dhcp4_parser.cc"
    break;

  case 790: // logger_entry: "{" $@130 logger_params "}"
#line 2767 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4434 "dhcp4_parser.cc"
    break;

  case 793: // logger_params: logger_params ","
#line 2773 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4442 "dhcp4_parser.cc"
    break;

  case 801: // debuglevel: "debuglevel" ":" "integer"
#line 2787 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4452 "dhcp4_parser.cc"
    break;

  case 802: // $@131: %empty
#line 2793 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4461 "dhcp4_parser.cc"
    break;

  case 803: // severity: "severity" $@131 ":" "constant string"
#line 2796 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4471 "dhcp4_parser.cc"
    break;

  case 804: // $@132: %empty
#line 2802 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4483 "dhcp4_parser.cc"
    break;

  case 805: // output_options_list: "output_options" $@132 ":" "[" output_options_list_content "]"
#line 2808 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4492 "dhcp4_parser.cc"
    break;

  case 808: // output_options_list_content: output_options_list_content ","
#line 2815 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4500 "dhcp4_parser.cc"
    break;

  case 809: // $@133: %empty
#line 2820 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4510 "dhcp4_parser.cc"
    break;

  case 810: // output_entry: "{" $@133 output_params_list "}"
#line 2824 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4518 "dhcp4_parser.cc"
    break;

  case 813: // output_params_list: output_params_list ","
#line 2830 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4526 "dhcp4_parser.cc"
    break;

  case 819: // $@134: %empty
#line 2842 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4535 "dhcp4_parser.cc"
    break;

  case 820: // output: "output" $@134 ":" "constant string"
#line 2845 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4545 "dhcp4_parser.cc"
    break;

  case 821: // flush: "flush" ":" "boolean"
#line 2851 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4555 "dhcp4_parser.cc"
    break;

  case 822: // maxsize: "maxsize" ":" "integer"
#line 2857 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4565 "dhcp4_parser.cc"
    break;

  case 823: // maxver: "maxver" ":" "integer"
#line 2863 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4575 "dhcp4_parser.cc"
    break;

  case 824: // $@135: %empty
#line 2869 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4584 "dhcp4_parser.cc"
    break;

  case 825: // pattern: "pattern" $@135 ":" "constant string"
#line 2872 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4594 "dhcp4_parser.cc"
    break;

  case 826: // $@136: %empty
#line 2878 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4606 "dhcp4_parser.cc"
    break;

  case 827: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 2884 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4615 "dhcp4_parser.cc"
    break;

  case 830: // compatibility_params: compatibility_params ","
#line 2891 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4623 "dhcp4_parser.cc"
    break;

  case 833: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2900 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4633 "dhcp4_parser.cc"
    break;


#line 4637 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -980;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     408,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    28,    42,    26,    41,    60,    62,
      80,    86,    99,   104,   110,   132,   142,   153,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    42,  -154,   125,   136,    66,   618,
     219,   170,   -21,   315,    81,  -100,   422,   129,  -980,   119,
      73,   139,   162,   181,  -980,    67,  -980,  -980,  -980,  -980,
     223,   237,   243,  -980,  -980,  -980,  -980,  -980,  -980,   254,
     263,   288,   289,   291,   305,   306,   307,   309,   342,   352,
    -980,   371,   372,   374,   390,   391,  -980,  -980,  -980,   392,
     406,   409,  -980,  -980,  -980,   410,  -980,  -980,  -980,  -980,
     415,   416,   417,  -980,  -980,  -980,  -980,  -980,   421,  -980,
    -980,  -980,  -980,  -980,  -980,   423,   424,   425,  -980,  -980,
     426,  -980,    87,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     427,  -980,   102,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,   428,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   105,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   115,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   183,
     235,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   323,  -980,  -980,   429,  -980,  -980,  -980,
     431,  -980,  -980,   350,   366,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   433,   434,
    -980,  -980,  -980,  -980,   435,   439,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   128,  -980,
    -980,  -980,   440,  -980,  -980,   441,  -980,   442,   445,  -980,
    -980,   447,   449,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     178,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   450,   179,
    -980,  -980,  -980,  -980,    42,    42,  -980,   249,   453,  -980,
    -980,   454,   455,   457,   257,   260,   262,   469,   470,   471,
     473,   474,   475,   276,   279,   284,   285,   292,   286,   280,
     294,   295,   297,   302,   482,   303,   304,   287,   298,   308,
     510,   511,   512,   311,   313,   317,   513,   527,   529,   326,
     531,   533,   535,   536,   331,   332,   335,   547,   548,   551,
     553,   554,   351,   558,   559,   561,   565,   569,   570,   367,
     368,   369,   571,   576,  -980,   136,  -980,   590,   591,   592,
     387,    66,  -980,   594,   595,   611,   612,   613,   614,   411,
     616,   620,   621,   618,  -980,   622,   219,  -980,   623,   624,
     626,   627,   628,   630,   631,   632,  -980,   170,  -980,   633,
     634,   414,   636,   637,   638,   443,  -980,   315,   639,   444,
     446,  -980,    81,   645,   646,    34,  -980,   451,   647,   648,
     458,   651,   459,   460,   655,   658,   461,   462,   659,   661,
     665,   666,   422,  -980,   673,   472,   129,  -980,  -980,  -980,
     674,   672,   686,   687,   688,  -980,  -980,  -980,   489,   499,
     503,   705,   706,   676,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   507,  -980,  -980,  -980,  -980,
    -980,  -132,   508,   514,  -980,  -980,  -980,   715,   717,   719,
    -980,   726,   725,   526,   207,  -980,  -980,  -980,   729,   734,
     736,   737,   731,  -980,   738,   739,   740,   741,   542,   543,
    -980,  -980,  -980,   747,   746,  -980,   749,   176,   205,  -980,
    -980,   549,   550,   557,   750,   560,   562,  -980,   749,   563,
     751,  -980,   564,  -980,   749,   566,   567,   568,   572,   573,
     574,   575,  -980,   577,   578,  -980,   579,   580,   581,  -980,
    -980,   582,  -980,  -980,  -980,   583,   725,  -980,  -980,   584,
     585,  -980,   586,  -980,  -980,    13,   593,  -980,  -980,  -132,
     587,   588,   601,  -980,   760,  -980,  -980,    42,   136,   129,
      66,   744,  -980,  -980,  -980,   340,   340,   765,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,   769,   770,   771,
     776,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   103,
     802,   803,   804,   210,   -49,   -24,   -11,   422,  -980,  -980,
     815,  -143,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   816,  -980,  -980,  -980,  -980,   130,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,   765,  -980,   187,
     189,   234,  -980,   258,  -980,  -980,  -980,  -980,  -980,  -980,
     820,   824,   825,   826,   827,  -980,  -980,  -980,  -980,   828,
     829,  -980,   830,   831,   832,   833,  -980,  -980,  -980,  -980,
    -980,   268,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   271,  -980,
     836,   835,  -980,  -980,   838,   843,  -980,  -980,   841,   845,
    -980,  -980,   847,   846,  -980,  -980,   848,   853,  -980,  -980,
    -980,  -980,  -980,  -980,    49,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,    74,  -980,  -980,   851,   856,  -980,  -980,   854,
     858,  -980,   859,   860,   861,   863,   864,   865,   277,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,   866,   867,   868,  -980,
     278,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   281,  -980,  -980,  -980,   869,  -980,   870,  -980,
    -980,  -980,   300,  -980,  -980,  -980,  -980,  -980,   321,  -980,
      83,  -980,   871,  -980,   327,  -980,  -980,   669,  -980,   872,
     874,  -980,  -980,  -980,  -980,   873,   876,  -980,  -980,  -980,
     875,   744,  -980,   879,   880,   881,   882,   654,   629,   679,
     670,   680,   885,   886,   887,   888,   685,   689,   890,   690,
     691,   692,   693,   891,   892,   896,   899,   340,  -980,  -980,
     340,  -980,   765,   618,  -980,   769,   315,  -980,   770,    81,
    -980,   771,   733,  -980,   776,   103,  -980,   240,   802,  -980,
     170,  -980,   803,  -100,  -980,   804,   696,   697,   698,   699,
     700,   701,   210,  -980,   703,   702,   707,   -49,  -980,   910,
     913,   -24,  -980,   708,   916,   713,   919,   -11,  -980,  -980,
     152,   815,  -980,   714,  -143,  -980,  -980,   923,   928,   219,
    -980,   816,   930,  -980,  -980,   732,  -980,   370,   748,   754,
     766,  -980,  -980,  -980,  -980,  -980,   783,   784,   787,   791,
    -980,  -980,   101,  -980,  -980,  -980,  -980,   792,   817,   852,
     857,  -980,   334,  -980,   337,  -980,   950,  -980,   975,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   354,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  1006,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  1003,  1051,
    -980,  -980,  -980,  -980,  -980,  1050,  -980,   362,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     862,   877,  -980,  -980,   878,  -980,    42,  -980,  -980,  1059,
    -980,  -980,  -980,  -980,  -980,   363,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   883,   364,  -980,   749,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   733,  -980,  1061,   884,  -980,   240,  -980,
    -980,  -980,  -980,  -980,  -980,  1062,   889,  1063,   152,  -980,
    -980,  -980,  -980,  -980,   893,  -980,  -980,  1065,  -980,   894,
    -980,  -980,  1064,  -980,  -980,   118,  -980,   -37,  1064,  -980,
    -980,  1068,  1069,  1070,  -980,   365,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  1071,   895,   898,   900,  1072,   -37,  -980,
     897,  -980,  -980,  -980,   903,  -980,  -980,  -980
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   189,     9,   374,    11,   582,    13,
     609,    15,   502,    17,   511,    19,   550,    21,   336,    23,
     723,    25,   774,    27,    46,    39,     0,     0,     0,     0,
       0,   611,     0,   513,   552,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   772,   177,   204,
       0,     0,     0,   631,   633,   635,   202,   212,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,     0,     0,     0,     0,   154,   161,   163,     0,
       0,     0,   365,   500,   541,     0,   448,   596,   598,   441,
       0,     0,     0,   298,   659,   600,   327,   348,     0,   313,
     690,   704,   721,   167,   169,     0,     0,     0,   784,   826,
       0,   133,     0,    67,    70,    71,    72,    73,    74,   108,
     109,   110,   111,   112,    75,   103,   132,    92,    93,    94,
     116,   117,   118,   119,   120,   121,   122,   123,   114,   115,
     124,   125,   126,   128,   129,   130,    78,    79,   100,    80,
      81,    82,   127,    86,    87,    76,   105,   106,   107,   104,
      77,    84,    85,    98,    99,   101,    95,    96,    97,    83,
      88,    89,    90,    91,   102,   113,   131,   191,   193,   197,
       0,   188,     0,   179,   182,   183,   184,   185,   186,   187,
     426,   428,   430,   573,   424,   432,     0,   436,   434,   655,
     423,   379,   380,   381,   382,   383,   407,   408,   409,   410,
     411,   397,   398,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,     0,   376,   386,   402,   403,   404,
     387,   389,   390,   393,   394,   395,   392,   388,   384,   385,
     405,   406,   391,   399,   400,   401,   396,   594,   593,   589,
     590,   588,     0,   584,   587,   591,   592,   653,   641,   643,
     647,   645,   651,   649,   637,   630,   624,   628,   629,     0,
     612,   613,   625,   626,   627,   621,   616,   622,   618,   619,
     620,   623,   617,     0,   531,   265,     0,   535,   533,   538,
       0,   527,   528,     0,   514,   515,   518,   530,   519,   520,
     521,   537,   522,   523,   524,   525,   526,   567,     0,     0,
     565,   566,   569,   570,     0,   553,   554,   557,   558,   559,
     560,   561,   562,   563,   564,   344,   346,   341,     0,   338,
     342,   343,     0,   760,   747,     0,   750,     0,     0,   754,
     758,     0,     0,   764,   766,   768,   770,   745,   743,   744,
       0,   725,   728,   729,   730,   731,   732,   733,   734,   735,
     740,   736,   737,   738,   739,   741,   742,   781,     0,     0,
     776,   779,   780,    45,    50,     0,    37,    43,     0,    64,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    69,    66,     0,     0,     0,
       0,   181,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   378,   375,     0,   586,   583,     0,     0,
       0,     0,     0,     0,     0,     0,   610,   615,   503,     0,
       0,     0,     0,     0,     0,     0,   512,   517,     0,     0,
       0,   551,   556,     0,     0,   340,   337,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   727,   724,     0,     0,   778,   775,    49,    41,
       0,     0,     0,     0,     0,   148,   149,   150,     0,     0,
       0,     0,     0,     0,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,     0,   172,   173,   151,   152,
     153,     0,     0,     0,   165,   166,   171,     0,     0,     0,
     147,     0,     0,     0,     0,   438,   439,   440,     0,     0,
       0,     0,     0,   689,     0,     0,     0,     0,     0,     0,
     174,   175,   176,     0,     0,    68,     0,     0,     0,   201,
     180,     0,     0,     0,     0,     0,     0,   447,     0,     0,
       0,   377,     0,   585,     0,     0,     0,     0,     0,     0,
       0,     0,   614,     0,     0,   529,     0,     0,     0,   540,
     516,     0,   571,   572,   555,     0,     0,   339,   746,     0,
       0,   749,     0,   752,   753,     0,     0,   762,   763,     0,
       0,     0,     0,   726,     0,   783,   777,     0,     0,     0,
       0,     0,   632,   634,   636,     0,     0,   216,   146,   156,
     157,   158,   159,   160,   155,   162,   164,   367,   504,   543,
     450,    38,   597,   599,   443,   444,   445,   446,   442,     0,
       0,   602,   329,     0,     0,     0,     0,     0,   168,   170,
       0,     0,    51,   192,   195,   196,   194,   199,   200,   198,
     427,   429,   431,   575,   425,   433,   437,   435,     0,   595,
     654,   642,   644,   648,   646,   652,   650,   638,   532,   266,
     536,   534,   539,   568,   345,   347,   761,   748,   751,   756,
     757,   755,   759,   765,   767,   769,   771,   216,    42,     0,
       0,     0,   210,     0,   206,   209,   252,   258,   260,   262,
       0,     0,     0,     0,     0,   274,   276,   278,   280,     0,
       0,   284,     0,     0,     0,     0,   290,   292,   294,   296,
     251,     0,   223,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   240,   241,   242,   236,   243,   244,   245,
     237,   238,   239,   246,   247,   248,   249,   250,     0,   221,
       0,   217,   218,   372,     0,   368,   369,   509,     0,   505,
     506,   548,     0,   544,   545,   455,     0,   451,   452,   308,
     309,   310,   311,   312,     0,   300,   303,   304,   305,   306,
     307,   664,     0,   661,   607,     0,   603,   604,   334,     0,
     330,   331,     0,     0,     0,     0,     0,     0,     0,   350,
     353,   354,   355,   356,   357,   358,     0,     0,     0,   323,
       0,   315,   318,   319,   320,   321,   322,   700,   702,   699,
     697,   698,     0,   692,   695,   696,     0,   716,     0,   719,
     712,   713,     0,   706,   709,   710,   711,   714,     0,   789,
       0,   786,     0,   832,     0,   828,   831,    53,   580,     0,
     576,   577,   639,   657,   658,     0,     0,    62,   773,   178,
       0,   208,   205,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   225,   203,   213,
       0,   215,   220,     0,   366,   371,   513,   501,   508,   552,
     542,   547,     0,   449,   454,   302,   299,   666,   663,   660,
     611,   601,   606,     0,   328,   333,     0,     0,     0,     0,
       0,     0,   352,   349,     0,     0,     0,   317,   314,     0,
       0,   694,   691,     0,     0,     0,     0,   708,   705,   722,
       0,   788,   785,     0,   830,   827,    55,     0,    54,     0,
     574,   579,     0,   656,   782,     0,   207,     0,     0,     0,
       0,   264,   267,   268,   269,   270,     0,     0,     0,     0,
     282,   283,     0,   271,   272,   273,   289,     0,     0,     0,
       0,   224,     0,   219,     0,   370,     0,   507,     0,   546,
     499,   478,   479,   480,   463,   464,   483,   484,   485,   486,
     487,   466,   467,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   460,   461,   462,   476,   477,   473,
     474,   475,   472,     0,   457,   465,   481,   482,   468,   469,
     470,   471,   453,   301,   686,     0,   681,   682,   683,   684,
     685,   674,   675,   679,   680,   676,   677,   678,     0,   667,
     668,   671,   672,   673,   662,     0,   605,     0,   332,   359,
     360,   361,   362,   363,   364,   351,   324,   325,   326,   316,
       0,     0,   693,   715,     0,   718,     0,   707,   804,     0,
     802,   800,   794,   798,   799,     0,   791,   796,   797,   795,
     787,   833,   829,    52,    57,     0,   578,     0,   211,   254,
     255,   256,   257,   253,   259,   261,   263,   275,   277,   279,
     281,   286,   287,   288,   285,   291,   293,   295,   297,   222,
     373,   510,   549,   459,   456,     0,     0,   665,   670,   608,
     335,   701,   703,   717,   720,     0,     0,     0,   793,   790,
      56,   581,   640,   458,     0,   688,   669,     0,   801,     0,
     792,   687,     0,   803,   809,     0,   806,     0,   808,   805,
     819,     0,     0,     0,   824,     0,   811,   814,   815,   816,
     817,   818,   807,     0,     0,     0,     0,     0,   813,   810,
       0,   821,   822,   823,     0,   812,   820,   825
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   -54,  -980,  -563,  -980,   402,
    -980,  -980,  -980,  -980,  -980,  -980,  -617,  -980,  -980,  -980,
     -67,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   389,   596,
       4,    10,    23,   -40,   -23,   -12,    22,    25,    29,    33,
    -980,  -980,  -980,  -980,  -980,    35,    40,    43,    45,    46,
      47,  -980,   399,    50,  -980,    51,  -980,    53,    57,    58,
    -980,    61,  -980,    63,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,   393,   589,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   131,
    -980,  -980,  -980,  -980,  -980,  -980,   310,  -980,    97,  -980,
    -684,   109,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   -33,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,    93,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,    72,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,    88,  -980,  -980,  -980,    89,   556,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,    84,  -980,  -980,  -980,
    -980,  -980,  -980,  -979,  -980,  -980,  -980,   113,  -980,  -980,
    -980,   112,   599,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -977,  -980,   -65,  -980,    70,  -980,    64,    65,    68,
      69,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   117,  -980,
    -980,  -114,   -46,  -980,  -980,  -980,  -980,  -980,   126,  -980,
    -980,  -980,   121,  -980,   597,  -980,   -63,  -980,  -980,  -980,
    -980,  -980,   -42,  -980,  -980,  -980,  -980,  -980,   -35,  -980,
    -980,  -980,   122,  -980,  -980,  -980,   114,  -980,   598,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
      75,  -980,  -980,  -980,    76,   615,  -980,  -980,   -51,  -980,
      -8,  -980,   -39,  -980,  -980,  -980,   116,  -980,  -980,  -980,
     120,  -980,   600,   -55,  -980,   -15,  -980,     3,  -980,   375,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -968,  -980,  -980,
    -980,  -980,  -980,   124,  -980,  -980,  -980,   -99,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,   106,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    98,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   401,   602,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,   437,   603,  -980,  -980,
    -980,  -980,  -980,  -980,   100,  -980,  -980,   -96,  -980,  -980,
    -980,  -980,  -980,  -980,  -119,  -980,  -980,  -135,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   107,  -980
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   712,
      82,    83,    39,    64,    79,    80,   733,   937,  1037,  1038,
     810,    41,    66,    85,   418,    86,    43,    67,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   444,   166,   167,   168,   169,   170,   171,   172,
     173,   450,   704,   174,   451,   175,   452,   176,   177,   178,
     477,   179,   478,   180,   181,   182,   183,   184,   185,   186,
     422,   222,   223,    45,    68,   224,   487,   225,   488,   736,
     226,   489,   739,   227,   187,   430,   188,   423,   783,   784,
     785,   950,   189,   431,   190,   432,   840,   841,   842,   980,
     811,   812,   813,   953,  1193,   814,   954,   815,   955,   816,
     956,   817,   818,   520,   819,   820,   821,   822,   823,   824,
     825,   826,   962,   827,   963,   828,   964,   829,   965,   830,
     831,   832,   968,  1204,   833,   834,   973,   835,   974,   836,
     975,   837,   976,   191,   467,   864,   865,   866,   867,   868,
     869,   870,   192,   473,   900,   901,   902,   903,   904,   193,
     470,   879,   880,   881,  1003,    59,    75,   368,   369,   370,
     533,   371,   534,   194,   471,   888,   889,   890,   891,   892,
     893,   894,   895,   195,   456,   844,   845,   846,   983,    47,
      69,   264,   265,   266,   497,   267,   493,   268,   494,   269,
     495,   270,   498,   271,   501,   272,   500,   196,   197,   198,
     199,   463,   718,   277,   200,   460,   856,   857,   858,   992,
    1113,  1114,   201,   457,    53,    72,   848,   849,   850,   986,
      55,    73,   333,   334,   335,   336,   337,   338,   339,   519,
     340,   523,   341,   522,   342,   343,   524,   344,   202,   458,
     852,   853,   854,   989,    57,    74,   354,   355,   356,   357,
     358,   528,   359,   360,   361,   362,   279,   496,   939,   940,
     941,  1039,    49,    70,   292,   293,   294,   505,   203,   461,
     204,   462,   205,   469,   875,   876,   877,  1000,    51,    71,
     309,   310,   311,   206,   427,   207,   428,   208,   429,   315,
     515,   944,  1042,   316,   509,   317,   510,   318,   512,   319,
     511,   320,   514,   321,   513,   322,   508,   286,   502,   945,
     209,   468,   872,   873,   997,  1138,  1139,  1140,  1141,  1142,
    1215,  1143,   210,   211,   474,   912,   913,   914,  1019,   915,
    1020,   212,   475,   922,   923,   924,   925,  1024,   926,   927,
    1026,   213,   476,    61,    76,   390,   391,   392,   393,   539,
     394,   395,   541,   396,   397,   398,   544,   771,   399,   545,
     400,   538,   401,   402,   403,   548,   404,   549,   405,   550,
     406,   551,   214,   421,    63,    77,   409,   410,   411,   554,
     412,   215,   482,   930,   931,  1030,  1175,  1176,  1177,  1178,
    1227,  1179,  1225,  1245,  1246,  1247,  1255,  1256,  1257,  1263,
    1258,  1259,  1260,  1261,  1267,   216,   483,   934,   935,   936
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     151,   221,   240,   288,   305,   289,   331,   350,   367,   387,
      78,   352,   838,  1105,   283,  1106,   312,   228,   280,   295,
     307,   746,   345,   363,  1121,   388,   323,   750,    28,   244,
     282,   769,   353,    40,   278,   291,   306,   365,   366,   711,
     332,   351,   699,   700,   701,   702,   245,    29,    42,    30,
     932,    31,   995,    81,   284,   996,   313,   246,   127,   128,
     229,   281,   296,   308,   150,   346,   364,    44,   389,    46,
     419,   123,   285,   241,   314,   420,   414,   998,   703,   242,
     999,   217,   218,   127,   128,   219,  1031,    48,   220,  1032,
     485,   247,   243,    50,   248,   486,   127,   128,   249,   896,
     897,   898,   250,   711,   251,   491,    52,   150,   503,   252,
     492,    54,   253,   504,   254,   255,   256,    56,   506,   257,
     258,  1248,   259,   507,  1249,   413,   260,   261,   907,   908,
     262,   535,   263,   273,   274,    84,   536,   275,   276,    58,
     290,   407,   408,   415,   916,   917,   918,    87,  1250,    60,
      88,  1251,  1252,  1253,  1254,  1201,  1202,  1203,   150,    89,
      62,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     416,   365,   366,   127,   128,   325,   347,   326,   327,   348,
     349,   552,   556,   150,   417,   770,   553,   557,   127,   128,
     485,   516,   556,   734,   735,   947,   919,   948,    93,    94,
      95,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   737,   738,   424,   123,   124,
     859,   860,   861,   862,  1105,   863,  1106,   491,   517,   125,
     126,   425,   949,   127,   128,  1121,   325,   426,   129,    32,
      33,    34,    35,   130,   131,   132,   133,   134,   433,   127,
     128,   951,   135,   124,   304,   942,   952,   434,    93,    94,
      95,   977,   136,   150,   977,   137,   978,   127,   128,   979,
    1012,  1017,   138,   139,  1021,  1013,  1018,   140,   150,  1022,
     141,   297,   435,   436,   142,   437,  1072,   298,   299,   300,
     301,   302,   303,  1027,   304,    99,   100,   101,  1028,   438,
     439,   440,   124,   441,   143,   144,   145,   146,   147,   148,
     714,   715,   716,   717,   552,   287,   127,   128,   149,  1029,
    1034,   518,   123,   124,   325,  1035,  1168,   977,  1169,  1170,
     503,   237,  1209,   150,   238,  1210,   442,   127,   128,   324,
     882,   883,   884,   885,   886,   887,   443,  1213,   526,   150,
     558,   559,  1214,  1124,  1125,   535,  1228,   506,  1268,   527,
    1220,  1229,  1231,  1269,   786,   445,   446,   150,   447,   787,
     788,   789,   790,   791,   792,   793,   794,   795,   796,   797,
     798,   799,   800,   801,   448,   449,   453,   802,   803,   804,
     805,   806,   807,   808,   809,  1189,  1190,  1191,  1192,   325,
     454,   326,   327,   455,   459,   328,   329,   330,   151,   464,
     465,   466,   127,   128,   221,   472,   150,   479,   480,   481,
     484,   490,   499,   521,   325,   525,   240,   529,   530,   288,
     228,   289,   532,   531,   537,   540,   542,   150,   283,   543,
     305,   546,   280,   547,   555,   295,   560,   561,   562,   563,
     331,   564,   312,   244,   282,   350,   307,   565,   278,   352,
     566,   291,   567,   568,   569,   570,   345,   571,   572,   573,
     245,   363,   306,   229,   574,   387,   585,   575,   284,   580,
     353,   246,   576,   577,   332,   281,   579,   588,   296,   351,
     578,   388,   313,   581,   582,   583,   285,   241,   589,   308,
     584,   586,   587,   242,   591,   592,   593,   597,   590,   346,
     314,   594,   150,   595,   364,   247,   243,   596,   248,   127,
     128,   598,   249,   599,   600,   601,   250,   602,   251,   603,
     604,   605,   606,   252,   389,   607,   253,   150,   254,   255,
     256,   608,   609,   257,   258,   610,   259,   611,   612,   613,
     260,   261,   614,   615,   262,   616,   263,   273,   274,   617,
    1232,   275,   276,   618,   619,   623,   290,   620,   621,   622,
     624,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   626,   627,   628,   629,   631,   632,
     385,   386,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   633,   634,   635,   636,   637,
     638,   151,   655,   221,   639,   640,   642,   644,   645,   150,
     646,   647,   648,   778,   649,   650,   651,   653,   654,   228,
     656,   657,   658,   661,    91,    92,    93,    94,    95,   665,
     666,   669,   670,   659,   662,   672,   663,   899,   909,   675,
     387,   668,   676,   679,   933,   680,   671,   673,   674,   681,
     682,   677,   678,   905,   910,   920,   388,   684,   687,   688,
     685,   697,   229,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   689,   690,   691,   692,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   693,   230,   231,   232,
     694,   124,   695,   696,   698,   705,   906,   911,   921,   389,
     707,   706,   708,   233,   709,   127,   128,   234,   235,   236,
     129,   710,    30,   713,   719,   130,   131,   132,   723,   720,
     237,   721,   722,   238,   135,   724,   725,   726,   727,   728,
     729,   239,   730,   731,   732,   743,   740,   741,   748,    91,
      92,    93,    94,    95,   742,   777,   772,   744,   782,   745,
     747,   749,   839,   751,   752,   753,   843,   847,   851,   754,
     755,   756,   757,   855,   758,   759,   760,   761,   762,   763,
     764,   766,   767,   768,   774,   775,   143,   144,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   776,   871,
     874,   878,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   929,   938,   957,   150,   124,   325,   958,   959,
     960,   961,   966,   967,   969,   970,   971,   972,   982,  1052,
     127,   128,   981,   235,   984,   129,   985,   987,   988,   991,
     130,   131,   132,   990,   993,   237,   994,  1001,   238,  1002,
    1004,  1005,  1051,  1006,  1007,  1008,   239,  1009,  1010,  1011,
    1014,  1015,  1016,  1023,  1025,  1033,  1036,  1041,  1040,  1045,
    1054,  1043,  1044,  1047,  1048,  1049,  1050,  1053,  1055,  1056,
    1057,  1058,  1059,  1060,  1062,  1067,  1068,  1061,  1063,  1064,
    1069,  1066,  1065,  1070,  1149,  1150,  1151,  1152,  1153,  1154,
    1157,   143,   144,  1156,  1160,  1158,   240,  1161,  1163,   331,
    1164,  1165,   350,  1166,  1181,  1080,   352,  1107,   283,  1183,
    1126,  1184,   280,   305,  1187,   345,   367,  1118,   363,  1188,
     150,  1116,  1135,   244,   282,   312,  1133,   353,   278,   307,
     899,  1131,  1084,   332,   909,  1194,   351,  1115,  1211,  1104,
     245,  1195,  1132,  1171,  1130,   306,   905,   933,   284,  1085,
     910,   246,   288,  1196,   289,   281,   920,  1119,   346,  1173,
    1086,   364,  1136,  1212,  1117,   313,   285,   241,   295,  1134,
    1197,  1198,   308,   242,  1199,  1120,  1081,  1172,  1200,  1205,
    1137,  1127,  1082,   314,   291,   247,   243,  1128,   248,   906,
    1216,  1217,   249,   911,  1087,  1083,   250,  1088,   251,   921,
    1129,  1089,  1174,   252,  1206,  1090,   253,  1091,   254,   255,
     256,   296,  1092,   257,   258,  1093,   259,  1094,  1095,  1096,
     260,   261,  1097,  1098,   262,  1099,   263,   273,   274,  1100,
    1101,   275,   276,  1102,  1218,  1103,  1109,  1110,  1219,  1207,
    1111,  1112,  1108,  1226,  1208,  1234,  1237,  1239,   765,  1221,
    1242,  1244,  1264,  1265,  1266,  1270,  1274,   779,   773,  1073,
     630,   625,  1046,   781,  1222,  1223,  1071,   946,  1123,  1159,
    1230,   667,  1147,  1148,  1235,  1074,  1155,  1238,  1075,  1233,
    1241,  1243,   641,  1078,  1276,  1271,  1272,  1076,  1273,   290,
    1277,  1122,  1224,  1079,  1077,  1185,  1186,   652,  1146,  1236,
    1145,   643,  1144,   943,   660,  1167,   780,  1162,   928,  1262,
     664,  1180,  1240,  1275,     0,     0,     0,     0,     0,     0,
       0,  1182,     0,     0,     0,     0,  1080,     0,  1107,     0,
       0,  1126,     0,     0,   683,     0,     0,     0,  1118,   686,
       0,  1171,  1116,  1135,     0,     0,     0,  1133,     0,     0,
       0,     0,  1131,  1084,     0,     0,     0,  1173,  1115,     0,
    1104,     0,     0,  1132,     0,  1130,     0,     0,     0,     0,
    1085,     0,     0,     0,     0,  1172,     0,     0,  1119,     0,
       0,  1086,     0,  1136,     0,  1117,     0,     0,     0,     0,
    1134,     0,     0,     0,     0,     0,  1120,  1081,     0,     0,
    1174,  1137,  1127,  1082,     0,     0,     0,     0,  1128,     0,
       0,     0,     0,     0,     0,  1087,  1083,     0,  1088,     0,
       0,  1129,  1089,     0,     0,     0,  1090,     0,  1091,     0,
       0,     0,     0,  1092,     0,     0,  1093,     0,  1094,  1095,
    1096,     0,     0,  1097,  1098,     0,  1099,     0,     0,     0,
    1100,  1101,     0,     0,  1102,     0,  1103,  1109,  1110,     0,
       0,  1111,  1112,  1108
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   696,   992,    69,   992,    71,    68,    69,    70,
      71,   638,    73,    74,   992,    76,    72,   644,     0,    69,
      69,    18,    74,     7,    69,    70,    71,   137,   138,   602,
      73,    74,   174,   175,   176,   177,    69,     5,     7,     7,
     193,     9,     3,   207,    69,     6,    71,    69,   107,   108,
      68,    69,    70,    71,   207,    73,    74,     7,    76,     7,
       3,    92,    69,    69,    71,     8,     3,     3,   210,    69,
       6,    15,    16,   107,   108,    19,     3,     7,    22,     6,
       3,    69,    69,     7,    69,     8,   107,   108,    69,   148,
     149,   150,    69,   666,    69,     3,     7,   207,     3,    69,
       8,     7,    69,     8,    69,    69,    69,     7,     3,    69,
      69,     3,    69,     8,     6,     6,    69,    69,   152,   153,
      69,     3,    69,    69,    69,    10,     8,    69,    69,     7,
      70,    12,    13,     4,   155,   156,   157,    11,   185,     7,
      14,   188,   189,   190,   191,    54,    55,    56,   207,    23,
       7,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       8,   137,   138,   107,   108,    94,    95,    96,    97,    98,
      99,     3,     3,   207,     3,   172,     8,     8,   107,   108,
       3,     8,     3,    17,    18,     8,   207,     8,    28,    29,
      30,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    20,    21,     4,    92,    93,
     127,   128,   129,   130,  1213,   132,  1213,     3,     3,   103,
     104,     4,     8,   107,   108,  1213,    94,     4,   112,   207,
     208,   209,   210,   117,   118,   119,   120,   121,     4,   107,
     108,     3,   126,    93,   134,   135,     8,     4,    28,    29,
      30,     3,   136,   207,     3,   139,     8,   107,   108,     8,
       3,     3,   146,   147,     3,     8,     8,   151,   207,     8,
     154,   121,     4,     4,   158,     4,   980,   127,   128,   129,
     130,   131,   132,     3,   134,    65,    66,    67,     8,     4,
       4,     4,    93,     4,   178,   179,   180,   181,   182,   183,
     113,   114,   115,   116,     3,   106,   107,   108,   192,     8,
       3,     8,    92,    93,    94,     8,   184,     3,   186,   187,
       3,   122,     8,   207,   125,     8,     4,   107,   108,    34,
     140,   141,   142,   143,   144,   145,     4,     3,     8,   207,
     414,   415,     8,   123,   124,     3,     3,     3,     3,     3,
       8,     8,     8,     8,    34,     4,     4,   207,     4,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     4,     4,     4,    57,    58,    59,
      60,    61,    62,    63,    64,    35,    36,    37,    38,    94,
       4,    96,    97,     4,     4,   100,   101,   102,   485,     4,
       4,     4,   107,   108,   491,     4,   207,     4,     4,     4,
       4,     4,     4,     4,    94,     4,   503,     4,     4,   506,
     491,   506,     3,     8,     4,     4,     4,   207,   503,     4,
     517,     4,   503,     4,     4,   506,   207,     4,     4,     4,
     527,     4,   517,   503,   503,   532,   517,   210,   503,   532,
     210,   506,   210,     4,     4,     4,   527,     4,     4,     4,
     503,   532,   517,   491,   208,   552,     4,   208,   503,   209,
     532,   503,   208,   208,   527,   503,   210,   210,   506,   532,
     208,   552,   517,   209,   209,   208,   503,   503,   210,   517,
     208,   208,   208,   503,     4,     4,     4,     4,   210,   527,
     517,   210,   207,   210,   532,   503,   503,   210,   503,   107,
     108,     4,   503,     4,   208,     4,   503,     4,   503,     4,
       4,   210,   210,   503,   552,   210,   503,   207,   503,   503,
     503,     4,     4,   503,   503,     4,   503,     4,     4,   208,
     503,   503,     4,     4,   503,     4,   503,   503,   503,     4,
    1187,   503,   503,     4,     4,     4,   506,   210,   210,   210,
       4,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,     4,     4,     4,   210,     4,     4,
     178,   179,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,     4,     4,     4,     4,   208,
       4,   688,   208,   690,     4,     4,     4,     4,     4,   207,
       4,     4,     4,   687,     4,     4,     4,     4,     4,   690,
       4,     4,     4,     4,    26,    27,    28,    29,    30,     4,
       4,     4,     4,   210,   210,     4,   210,   724,   725,     4,
     727,   210,     4,     4,   731,     4,   208,   208,   208,     4,
       4,   210,   210,   724,   725,   726,   727,     4,     4,     7,
     208,     5,   690,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     7,     7,     7,   207,    79,    80,    81,
      82,    83,    84,    85,    86,    87,   207,    89,    90,    91,
     207,    93,     7,     7,   207,   207,   724,   725,   726,   727,
       5,   207,     5,   105,     5,   107,   108,   109,   110,   111,
     112,     5,     7,   207,     5,   117,   118,   119,     7,     5,
     122,     5,     5,   125,   126,     7,     7,     7,     7,   207,
     207,   133,     5,     7,     5,     5,   207,   207,     7,    26,
      27,    28,    29,    30,   207,     5,   173,   207,    24,   207,
     207,   207,     7,   207,   207,   207,     7,     7,     7,   207,
     207,   207,   207,     7,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   178,   179,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,   207,     7,
       7,     7,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,     7,     7,     4,   207,    93,    94,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   210,
     107,   108,     6,   110,     6,   112,     3,     6,     3,     3,
     117,   118,   119,     6,     6,   122,     3,     6,   125,     3,
       6,     3,   208,     4,     4,     4,   133,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   207,     3,     6,     4,
     210,     8,     6,     4,     4,     4,     4,   208,   208,     4,
       4,     4,     4,   208,     4,     4,     4,   208,   208,   208,
       4,   208,   210,     4,   208,   208,   208,   208,   208,   208,
     208,   178,   179,   210,     4,   208,   983,     4,   210,   986,
       4,   208,   989,     4,   210,   992,   989,   992,   983,     6,
     997,     3,   983,  1000,     4,   986,  1003,   992,   989,   207,
     207,   992,   997,   983,   983,  1000,   997,   989,   983,  1000,
    1017,   997,   992,   986,  1021,   207,   989,   992,     8,   992,
     983,   207,   997,  1030,   997,  1000,  1017,  1034,   983,   992,
    1021,   983,  1039,   207,  1039,   983,  1027,   992,   986,  1030,
     992,   989,   997,     8,   992,  1000,   983,   983,  1039,   997,
     207,   207,  1000,   983,   207,   992,   992,  1030,   207,   207,
     997,   997,   992,  1000,  1039,   983,   983,   997,   983,  1017,
       4,     8,   983,  1021,   992,   992,   983,   992,   983,  1027,
     997,   992,  1030,   983,   207,   992,   983,   992,   983,   983,
     983,  1039,   992,   983,   983,   992,   983,   992,   992,   992,
     983,   983,   992,   992,   983,   992,   983,   983,   983,   992,
     992,   983,   983,   992,     3,   992,   992,   992,     8,   207,
     992,   992,   992,     4,   207,     4,     4,     4,   666,   207,
       5,     7,     4,     4,     4,     4,     4,   688,   679,   982,
     491,   485,   951,   690,   207,   207,   977,   777,   995,  1017,
     207,   535,  1003,  1005,   210,   983,  1012,   208,   985,  1213,
     207,   207,   503,   989,   207,   210,   208,   986,   208,  1039,
     207,   994,  1166,   991,   988,  1039,  1041,   517,  1002,  1218,
    1000,   506,   998,   748,   527,  1027,   689,  1021,   727,  1248,
     532,  1031,  1228,  1268,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1034,    -1,    -1,    -1,    -1,  1213,    -1,  1213,    -1,
      -1,  1218,    -1,    -1,   552,    -1,    -1,    -1,  1213,   556,
      -1,  1228,  1213,  1218,    -1,    -1,    -1,  1218,    -1,    -1,
      -1,    -1,  1218,  1213,    -1,    -1,    -1,  1228,  1213,    -1,
    1213,    -1,    -1,  1218,    -1,  1218,    -1,    -1,    -1,    -1,
    1213,    -1,    -1,    -1,    -1,  1228,    -1,    -1,  1213,    -1,
      -1,  1213,    -1,  1218,    -1,  1213,    -1,    -1,    -1,    -1,
    1218,    -1,    -1,    -1,    -1,    -1,  1213,  1213,    -1,    -1,
    1228,  1218,  1218,  1213,    -1,    -1,    -1,    -1,  1218,    -1,
      -1,    -1,    -1,    -1,    -1,  1213,  1213,    -1,  1213,    -1,
      -1,  1218,  1213,    -1,    -1,    -1,  1213,    -1,  1213,    -1,
      -1,    -1,    -1,  1213,    -1,    -1,  1213,    -1,  1213,  1213,
    1213,    -1,    -1,  1213,  1213,    -1,  1213,    -1,    -1,    -1,
    1213,  1213,    -1,    -1,  1213,    -1,  1213,  1213,  1213,    -1,
      -1,  1213,  1213,  1213
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,     0,     5,
       7,     9,   207,   208,   209,   210,   226,   227,   228,   233,
       7,   242,     7,   247,     7,   294,     7,   410,     7,   493,
       7,   509,     7,   445,     7,   451,     7,   475,     7,   386,
       7,   574,     7,   605,   234,   229,   243,   248,   295,   411,
     494,   510,   446,   452,   476,   387,   575,   606,   226,   235,
     236,   207,   231,   232,    10,   244,   246,    11,    14,    23,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    92,    93,   103,   104,   107,   108,   112,
     117,   118,   119,   120,   121,   126,   136,   139,   146,   147,
     151,   154,   158,   178,   179,   180,   181,   182,   183,   192,
     207,   241,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   264,   265,   266,   267,
     268,   269,   270,   271,   274,   276,   278,   279,   280,   282,
     284,   285,   286,   287,   288,   289,   290,   305,   307,   313,
     315,   364,   373,   380,   394,   404,   428,   429,   430,   431,
     435,   443,   469,   499,   501,   503,   514,   516,   518,   541,
     553,   554,   562,   572,   603,   612,   636,    15,    16,    19,
      22,   241,   292,   293,   296,   298,   301,   304,   499,   501,
      89,    90,    91,   105,   109,   110,   111,   122,   125,   133,
     241,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   266,   267,   268,   269,   270,   271,   274,   276,   278,
     279,   280,   282,   284,   412,   413,   414,   416,   418,   420,
     422,   424,   426,   428,   429,   430,   431,   434,   469,   487,
     499,   501,   503,   514,   516,   518,   538,   106,   241,   424,
     426,   469,   495,   496,   497,   499,   501,   121,   127,   128,
     129,   130,   131,   132,   134,   241,   469,   499,   501,   511,
     512,   513,   514,   516,   518,   520,   524,   526,   528,   530,
     532,   534,   536,   443,    34,    94,    96,    97,   100,   101,
     102,   241,   333,   453,   454,   455,   456,   457,   458,   459,
     461,   463,   465,   466,   468,   499,   501,    95,    98,    99,
     241,   333,   457,   463,   477,   478,   479,   480,   481,   483,
     484,   485,   486,   499,   501,   137,   138,   241,   388,   389,
     390,   392,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   178,   179,   241,   499,   501,
     576,   577,   578,   579,   581,   582,   584,   585,   586,   589,
     591,   593,   594,   595,   597,   599,   601,    12,    13,   607,
     608,   609,   611,     6,     3,     4,     8,     3,   245,     3,
       8,   604,   291,   308,     4,     4,     4,   515,   517,   519,
     306,   314,   316,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   263,     4,     4,     4,     4,     4,
     272,   275,   277,     4,     4,     4,   405,   444,   470,     4,
     436,   500,   502,   432,     4,     4,     4,   365,   542,   504,
     381,   395,     4,   374,   555,   563,   573,   281,   283,     4,
       4,     4,   613,   637,     4,     3,     8,   297,   299,   302,
       4,     3,     8,   417,   419,   421,   488,   415,   423,     4,
     427,   425,   539,     3,     8,   498,     3,     8,   537,   525,
     527,   531,   529,   535,   533,   521,     8,     3,     8,   460,
     334,     4,   464,   462,   467,     4,     8,     3,   482,     4,
       4,     8,     3,   391,   393,     3,     8,     4,   592,   580,
       4,   583,     4,     4,   587,   590,     4,     4,   596,   598,
     600,   602,     3,     8,   610,     4,     3,     8,   226,   226,
     207,     4,     4,     4,     4,   210,   210,   210,     4,     4,
       4,     4,     4,     4,   208,   208,   208,   208,   208,   210,
     209,   209,   209,   208,   208,     4,   208,   208,   210,   210,
     210,     4,     4,     4,   210,   210,   210,     4,     4,     4,
     208,     4,     4,     4,     4,   210,   210,   210,     4,     4,
       4,     4,     4,   208,     4,     4,     4,     4,     4,     4,
     210,   210,   210,     4,     4,   250,     4,     4,     4,   210,
     293,     4,     4,     4,     4,     4,     4,   208,     4,     4,
       4,   413,     4,   496,     4,     4,     4,     4,     4,     4,
       4,     4,   513,     4,     4,   208,     4,     4,     4,   210,
     455,     4,   210,   210,   479,     4,     4,   389,   210,     4,
       4,   208,     4,   208,   208,     4,     4,   210,   210,     4,
       4,     4,     4,   577,     4,   208,   608,     4,     7,     7,
       7,     7,   207,   207,   207,     7,     7,     5,   207,   174,
     175,   176,   177,   210,   273,   207,   207,     5,     5,     5,
       5,   228,   230,   207,   113,   114,   115,   116,   433,     5,
       5,     5,     5,     7,     7,     7,     7,     7,   207,   207,
       5,     7,     5,   237,    17,    18,   300,    20,    21,   303,
     207,   207,   207,     5,   207,   207,   237,   207,     7,   207,
     237,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   230,   207,   207,   207,    18,
     172,   588,   173,   273,   207,   207,   207,     5,   226,   249,
     607,   292,    24,   309,   310,   311,    34,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    57,    58,    59,    60,    61,    62,    63,    64,
     241,   321,   322,   323,   326,   328,   330,   332,   333,   335,
     336,   337,   338,   339,   340,   341,   342,   344,   346,   348,
     350,   351,   352,   355,   356,   358,   360,   362,   321,     7,
     317,   318,   319,     7,   406,   407,   408,     7,   447,   448,
     449,     7,   471,   472,   473,     7,   437,   438,   439,   127,
     128,   129,   130,   132,   366,   367,   368,   369,   370,   371,
     372,     7,   543,   544,     7,   505,   506,   507,     7,   382,
     383,   384,   140,   141,   142,   143,   144,   145,   396,   397,
     398,   399,   400,   401,   402,   403,   148,   149,   150,   241,
     375,   376,   377,   378,   379,   499,   501,   152,   153,   241,
     499,   501,   556,   557,   558,   560,   155,   156,   157,   207,
     499,   501,   564,   565,   566,   567,   569,   570,   576,     7,
     614,   615,   193,   241,   638,   639,   640,   238,     7,   489,
     490,   491,   135,   520,   522,   540,   317,     8,     8,     8,
     312,     3,     8,   324,   327,   329,   331,     4,     4,     4,
       4,     4,   343,   345,   347,   349,     4,     4,   353,     4,
       4,     4,     4,   357,   359,   361,   363,     3,     8,     8,
     320,     6,     3,   409,     6,     3,   450,     6,     3,   474,
       6,     3,   440,     6,     3,     3,     6,   545,     3,     6,
     508,     6,     3,   385,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   559,
     561,     3,     8,     4,   568,     4,   571,     3,     8,     8,
     616,     3,     6,     4,     3,     8,   207,   239,   240,   492,
       6,     3,   523,     8,     6,     4,   310,     4,     4,     4,
       4,   208,   210,   208,   210,   208,     4,     4,     4,     4,
     208,   208,     4,   208,   208,   210,   208,     4,     4,     4,
       4,   322,   321,   319,   412,   408,   453,   449,   477,   473,
     241,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   266,   267,   268,   269,   270,   271,   274,   276,   278,
     279,   280,   282,   284,   333,   404,   422,   424,   426,   428,
     429,   430,   431,   441,   442,   469,   499,   501,   514,   516,
     518,   538,   439,   367,   123,   124,   241,   251,   252,   253,
     333,   443,   469,   499,   501,   514,   516,   518,   546,   547,
     548,   549,   550,   552,   544,   511,   507,   388,   384,   208,
     208,   208,   208,   208,   208,   397,   210,   208,   208,   376,
       4,     4,   557,   210,     4,   208,     4,   565,   184,   186,
     187,   241,   333,   499,   501,   617,   618,   619,   620,   622,
     615,   210,   639,     6,     3,   495,   491,     4,   207,    35,
      36,    37,    38,   325,   207,   207,   207,   207,   207,   207,
     207,    54,    55,    56,   354,   207,   207,   207,   207,     8,
       8,     8,     8,     3,     8,   551,     4,     8,     3,     8,
       8,   207,   207,   207,   226,   623,     4,   621,     3,     8,
     207,     8,   237,   442,     4,   210,   548,     4,   208,     4,
     618,   207,     5,   207,     7,   624,   625,   626,     3,     6,
     185,   188,   189,   190,   191,   627,   628,   629,   631,   632,
     633,   634,   625,   630,     4,     4,     4,   635,     3,     8,
       4,   210,   208,   208,     4,   628,   207,   207
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   211,   213,   212,   214,   212,   215,   212,   216,   212,
     217,   212,   218,   212,   219,   212,   220,   212,   221,   212,
     222,   212,   223,   212,   224,   212,   225,   212,   226,   226,
     226,   226,   226,   226,   226,   227,   229,   228,   230,   231,
     231,   232,   232,   232,   234,   233,   235,   235,   236,   236,
     236,   238,   237,   239,   239,   240,   240,   240,   241,   243,
     242,   245,   244,   244,   246,   248,   247,   249,   249,   249,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   263,   262,   264,   265,   266,
     267,   268,   269,   270,   272,   271,   273,   273,   273,   273,
     273,   275,   274,   277,   276,   278,   279,   281,   280,   283,
     282,   284,   285,   286,   287,   288,   289,   291,   290,   292,
     292,   292,   293,   293,   293,   293,   293,   293,   293,   295,
     294,   297,   296,   299,   298,   300,   300,   302,   301,   303,
     303,   304,   306,   305,   308,   307,   309,   309,   309,   310,
     312,   311,   314,   313,   316,   315,   317,   317,   318,   318,
     318,   320,   319,   321,   321,   321,   322,   322,   322,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     322,   322,   324,   323,   325,   325,   325,   325,   327,   326,
     329,   328,   331,   330,   332,   334,   333,   335,   336,   337,
     338,   339,   340,   341,   343,   342,   345,   344,   347,   346,
     349,   348,   350,   351,   353,   352,   354,   354,   354,   355,
     357,   356,   359,   358,   361,   360,   363,   362,   365,   364,
     366,   366,   366,   367,   367,   367,   367,   367,   368,   369,
     370,   371,   372,   374,   373,   375,   375,   375,   376,   376,
     376,   376,   376,   376,   377,   378,   379,   381,   380,   382,
     382,   383,   383,   383,   385,   384,   387,   386,   388,   388,
     388,   388,   389,   389,   391,   390,   393,   392,   395,   394,
     396,   396,   396,   397,   397,   397,   397,   397,   397,   398,
     399,   400,   401,   402,   403,   405,   404,   406,   406,   407,
     407,   407,   409,   408,   411,   410,   412,   412,   412,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   415,   414,   417,   416,   419,   418,
     421,   420,   423,   422,   425,   424,   427,   426,   428,   429,
     430,   432,   431,   433,   433,   433,   433,   434,   436,   435,
     437,   437,   438,   438,   438,   440,   439,   441,   441,   441,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     444,   443,   446,   445,   447,   447,   448,   448,   448,   450,
     449,   452,   451,   453,   453,   454,   454,   454,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   456,   457,
     458,   460,   459,   462,   461,   464,   463,   465,   467,   466,
     468,   470,   469,   471,   471,   472,   472,   472,   474,   473,
     476,   475,   477,   477,   478,   478,   478,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   480,   482,   481,   483,
     484,   485,   486,   488,   487,   489,   489,   490,   490,   490,
     492,   491,   494,   493,   495,   495,   495,   496,   496,   496,
     496,   496,   496,   496,   498,   497,   500,   499,   502,   501,
     504,   503,   505,   505,   506,   506,   506,   508,   507,   510,
     509,   511,   511,   512,   512,   512,   513,   513,   513,   513,
     513,   513,   513,   513,   513,   513,   513,   513,   513,   513,
     513,   515,   514,   517,   516,   519,   518,   521,   520,   523,
     522,   525,   524,   527,   526,   529,   528,   531,   530,   533,
     532,   535,   534,   537,   536,   539,   538,   540,   540,   542,
     541,   543,   543,   543,   545,   544,   546,   546,   547,   547,
     547,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   548,   549,   551,   550,   552,   553,
     555,   554,   556,   556,   556,   557,   557,   557,   557,   557,
     559,   558,   561,   560,   563,   562,   564,   564,   564,   565,
     565,   565,   565,   565,   565,   566,   568,   567,   569,   571,
     570,   573,   572,   575,   574,   576,   576,   576,   577,   577,
     577,   577,   577,   577,   577,   577,   577,   577,   577,   577,
     577,   577,   577,   577,   577,   577,   578,   580,   579,   581,
     583,   582,   584,   585,   587,   586,   588,   588,   590,   589,
     592,   591,   593,   594,   596,   595,   598,   597,   600,   599,
     602,   601,   604,   603,   606,   605,   607,   607,   607,   608,
     608,   610,   609,   611,   613,   612,   614,   614,   614,   616,
     615,   617,   617,   617,   618,   618,   618,   618,   618,   618,
     618,   619,   621,   620,   623,   622,   624,   624,   624,   626,
     625,   627,   627,   627,   628,   628,   628,   628,   628,   630,
     629,   631,   632,   633,   635,   634,   637,   636,   638,   638,
     638,   639,   639,   640
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
       3,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     1,     1,     0,     4,     1,
       1,     3,     0,     6,     0,     6,     1,     3,     2,     1,
       0,     4,     0,     6,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     0,     4,     1,     1,     1,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     1,     0,
       6,     1,     3,     2,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     0,     6,     3,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     3
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
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"trust-anchor\"",
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
  "re_detect", "lease_database", "$@31", "sanity_checks", "$@32",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@33",
  "hosts_database", "$@34", "hosts_databases", "$@35", "database_list",
  "not_empty_database_list", "database", "$@36", "database_map_params",
  "database_map_param", "database_type", "$@37", "db_type", "user", "$@38",
  "password", "$@39", "host", "$@40", "port", "name", "$@41", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@42", "keyspace",
  "$@43", "consistency", "$@44", "serial_consistency", "$@45",
  "max_reconnect_tries", "reconnect_wait_time", "on_fail", "$@46",
  "on_fail_mode", "max_row_errors", "trust_anchor", "$@47", "cert_file",
  "$@48", "key_file", "$@49", "cipher_list", "$@50",
  "host_reservation_identifiers", "$@51",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@52", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@53", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@54",
  "sub_hooks_library", "$@55", "hooks_params", "hooks_param", "library",
  "$@56", "parameters", "$@57", "expired_leases_processing", "$@58",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@59",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@60",
  "sub_subnet4", "$@61", "subnet4_params", "subnet4_param", "subnet",
  "$@62", "subnet_4o6_interface", "$@63", "subnet_4o6_interface_id",
  "$@64", "subnet_4o6_subnet", "$@65", "interface", "$@66", "client_class",
  "$@67", "require_client_classes", "$@68", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@69", "hr_mode", "id", "shared_networks", "$@70",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@71", "shared_network_params", "shared_network_param",
  "option_def_list", "$@72", "sub_option_def_list", "$@73",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@74", "sub_option_def", "$@75",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@76",
  "option_def_record_types", "$@77", "space", "$@78", "option_def_space",
  "option_def_encapsulate", "$@79", "option_def_array", "option_data_list",
  "$@80", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@81", "sub_option_data", "$@82",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@83",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@84", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@85", "sub_pool4", "$@86",
  "pool_params", "pool_param", "pool_entry", "$@87", "user_context",
  "$@88", "comment", "$@89", "reservations", "$@90", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@91", "sub_reservation",
  "$@92", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@93", "server_hostname", "$@94",
  "boot_file_name", "$@95", "ip_address", "$@96", "ip_addresses", "$@97",
  "duid", "$@98", "hw_address", "$@99", "client_id_value", "$@100",
  "circuit_id_value", "$@101", "flex_id_value", "$@102", "hostname",
  "$@103", "reservation_client_classes", "$@104", "relay", "$@105",
  "relay_map", "client_classes", "$@106", "client_classes_list",
  "client_class_entry", "$@107", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@108", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@109", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@110",
  "control_socket_name", "$@111", "dhcp_queue_control", "$@112",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@113", "capacity", "arbitrary_map_entry", "$@114",
  "dhcp_ddns", "$@115", "sub_dhcp_ddns", "$@116", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@117", "server_port",
  "sender_ip", "$@118", "sender_port", "max_queue_size", "ncr_protocol",
  "$@119", "ncr_protocol_value", "ncr_format", "$@120",
  "dep_qualifying_suffix", "$@121", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@122",
  "dep_generated_prefix", "$@123", "dep_hostname_char_set", "$@124",
  "dep_hostname_char_replacement", "$@125", "config_control", "$@126",
  "sub_config_control", "$@127", "config_control_params",
  "config_control_param", "config_databases", "$@128",
  "config_fetch_wait_time", "loggers", "$@129", "loggers_entries",
  "logger_entry", "$@130", "logger_params", "logger_param", "debuglevel",
  "severity", "$@131", "output_options_list", "$@132",
  "output_options_list_content", "output_entry", "$@133",
  "output_params_list", "output_params", "output", "$@134", "flush",
  "maxsize", "maxver", "pattern", "$@135", "compatibility", "$@136",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   300,   300,   300,   301,   301,   302,   302,   303,   303,
     304,   304,   305,   305,   306,   306,   307,   307,   308,   308,
     309,   309,   310,   310,   311,   311,   312,   312,   320,   321,
     322,   323,   324,   325,   326,   329,   334,   334,   345,   348,
     349,   352,   357,   363,   368,   368,   375,   376,   379,   383,
     387,   393,   393,   400,   401,   404,   408,   412,   422,   431,
     431,   446,   446,   460,   463,   469,   469,   478,   479,   480,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   553,   559,   565,   571,   577,   583,
     589,   595,   601,   607,   613,   619,   619,   628,   634,   640,
     646,   652,   658,   664,   670,   670,   679,   682,   685,   688,
     691,   697,   697,   706,   706,   715,   721,   727,   727,   736,
     736,   745,   751,   757,   763,   769,   775,   781,   781,   793,
     794,   795,   800,   801,   802,   803,   804,   805,   806,   809,
     809,   818,   818,   829,   829,   837,   838,   841,   841,   849,
     851,   855,   862,   862,   875,   875,   886,   887,   888,   893,
     895,   895,   914,   914,   927,   927,   938,   939,   942,   943,
     944,   949,   949,   959,   960,   961,   966,   967,   968,   969,
     970,   971,   972,   973,   974,   975,   976,   977,   978,   979,
     980,   981,   982,   983,   984,   985,   986,   987,   988,   989,
     990,   991,   994,   994,  1002,  1003,  1004,  1005,  1008,  1008,
    1017,  1017,  1026,  1026,  1035,  1041,  1041,  1050,  1056,  1062,
    1068,  1074,  1080,  1086,  1092,  1092,  1101,  1101,  1110,  1110,
    1119,  1119,  1128,  1134,  1140,  1140,  1148,  1149,  1150,  1153,
    1159,  1159,  1168,  1168,  1177,  1177,  1186,  1186,  1195,  1195,
    1206,  1207,  1208,  1213,  1214,  1215,  1216,  1217,  1220,  1225,
    1230,  1235,  1240,  1247,  1247,  1260,  1261,  1262,  1267,  1268,
    1269,  1270,  1271,  1272,  1275,  1281,  1287,  1293,  1293,  1304,
    1305,  1308,  1309,  1310,  1315,  1315,  1325,  1325,  1335,  1336,
    1337,  1340,  1343,  1344,  1347,  1347,  1356,  1356,  1365,  1365,
    1377,  1378,  1379,  1384,  1385,  1386,  1387,  1388,  1389,  1392,
    1398,  1404,  1410,  1416,  1422,  1431,  1431,  1445,  1446,  1449,
    1450,  1451,  1460,  1460,  1486,  1486,  1497,  1498,  1499,  1505,
    1506,  1507,  1508,  1509,  1510,  1511,  1512,  1513,  1514,  1515,
    1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,
    1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,
    1536,  1537,  1538,  1539,  1540,  1541,  1542,  1543,  1544,  1545,
    1546,  1547,  1548,  1549,  1552,  1552,  1561,  1561,  1570,  1570,
    1579,  1579,  1588,  1588,  1597,  1597,  1606,  1606,  1617,  1623,
    1629,  1635,  1635,  1643,  1644,  1645,  1646,  1649,  1657,  1657,
    1669,  1670,  1674,  1675,  1676,  1681,  1681,  1689,  1690,  1691,
    1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,
    1706,  1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,  1715,
    1716,  1717,  1718,  1719,  1720,  1721,  1722,  1723,  1724,  1725,
    1726,  1727,  1728,  1729,  1730,  1731,  1732,  1733,  1734,  1735,
    1742,  1742,  1756,  1756,  1765,  1766,  1769,  1770,  1771,  1778,
    1778,  1793,  1793,  1807,  1808,  1811,  1812,  1813,  1818,  1819,
    1820,  1821,  1822,  1823,  1824,  1825,  1826,  1827,  1830,  1832,
    1838,  1840,  1840,  1849,  1849,  1858,  1858,  1867,  1869,  1869,
    1878,  1888,  1888,  1901,  1902,  1907,  1908,  1909,  1916,  1916,
    1928,  1928,  1940,  1941,  1946,  1947,  1948,  1955,  1956,  1957,
    1958,  1959,  1960,  1961,  1962,  1963,  1966,  1968,  1968,  1977,
    1979,  1981,  1987,  1996,  1996,  2009,  2010,  2013,  2014,  2015,
    2020,  2020,  2030,  2030,  2040,  2041,  2042,  2047,  2048,  2049,
    2050,  2051,  2052,  2053,  2056,  2056,  2065,  2065,  2090,  2090,
    2120,  2120,  2131,  2132,  2135,  2136,  2137,  2142,  2142,  2151,
    2151,  2160,  2161,  2164,  2165,  2166,  2172,  2173,  2174,  2175,
    2176,  2177,  2178,  2179,  2180,  2181,  2182,  2183,  2184,  2185,
    2186,  2189,  2189,  2198,  2198,  2207,  2207,  2216,  2216,  2225,
    2225,  2236,  2236,  2245,  2245,  2254,  2254,  2263,  2263,  2272,
    2272,  2281,  2281,  2290,  2290,  2304,  2304,  2315,  2316,  2322,
    2322,  2333,  2334,  2335,  2340,  2340,  2350,  2351,  2354,  2355,
    2356,  2361,  2362,  2363,  2364,  2365,  2366,  2367,  2368,  2369,
    2370,  2371,  2372,  2373,  2374,  2377,  2379,  2379,  2388,  2396,
    2404,  2404,  2415,  2416,  2417,  2422,  2423,  2424,  2425,  2426,
    2429,  2429,  2438,  2438,  2450,  2450,  2463,  2464,  2465,  2470,
    2471,  2472,  2473,  2474,  2475,  2478,  2484,  2484,  2493,  2499,
    2499,  2509,  2509,  2522,  2522,  2532,  2533,  2534,  2539,  2540,
    2541,  2542,  2543,  2544,  2545,  2546,  2547,  2548,  2549,  2550,
    2551,  2552,  2553,  2554,  2555,  2556,  2559,  2565,  2565,  2574,
    2580,  2580,  2589,  2595,  2601,  2601,  2610,  2611,  2614,  2614,
    2624,  2624,  2634,  2641,  2648,  2648,  2657,  2657,  2667,  2667,
    2677,  2677,  2689,  2689,  2701,  2701,  2711,  2712,  2713,  2719,
    2720,  2723,  2723,  2734,  2742,  2742,  2755,  2756,  2757,  2763,
    2763,  2771,  2772,  2773,  2778,  2779,  2780,  2781,  2782,  2783,
    2784,  2787,  2793,  2793,  2802,  2802,  2813,  2814,  2815,  2820,
    2820,  2828,  2829,  2830,  2835,  2836,  2837,  2838,  2839,  2842,
    2842,  2851,  2857,  2863,  2869,  2869,  2878,  2878,  2889,  2890,
    2891,  2896,  2897,  2900
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
#line 6239 "dhcp4_parser.cc"

#line 2906 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
