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
#define yylex   d2_parser_lex



#include "d2_parser.h"


// Unqualified %code blocks.
#line 35 "d2_parser.yy"

#include <d2/parser_context.h>

// Avoid warnings with the error counter.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#line 57 "d2_parser.cc"


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
#if D2_PARSER_DEBUG

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

#else // !D2_PARSER_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !D2_PARSER_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "d2_parser.yy"
namespace isc { namespace d2 {
#line 150 "d2_parser.cc"

  /// Build a parser object.
  D2Parser::D2Parser (isc::d2::D2ParserContext& ctx_yyarg)
#if D2_PARSER_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  D2Parser::~D2Parser ()
  {}

  D2Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  D2Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  D2Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  D2Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  D2Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  D2Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  D2Parser::symbol_kind_type
  D2Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  D2Parser::stack_symbol_type::stack_symbol_type ()
  {}

  D2Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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

  D2Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
  D2Parser::stack_symbol_type&
  D2Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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

  D2Parser::stack_symbol_type&
  D2Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
  D2Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if D2_PARSER_DEBUG
  template <typename Base>
  void
  D2Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 397 "d2_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 403 "d2_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 409 "d2_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 415 "d2_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 421 "d2_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 427 "d2_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 433 "d2_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 439 "d2_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 144 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 445 "d2_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  D2Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  D2Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  D2Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if D2_PARSER_DEBUG
  std::ostream&
  D2Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  D2Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  D2Parser::debug_level_type
  D2Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  D2Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // D2_PARSER_DEBUG

  D2Parser::state_type
  D2Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  D2Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  D2Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  D2Parser::operator() ()
  {
    return parse ();
  }

  int
  D2Parser::parse ()
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
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
#line 153 "d2_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 722 "d2_parser.cc"
    break;

  case 4: // $@2: %empty
#line 154 "d2_parser.yy"
                         { ctx.ctx_ = ctx.CONFIG; }
#line 728 "d2_parser.cc"
    break;

  case 6: // $@3: %empty
#line 155 "d2_parser.yy"
                    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 734 "d2_parser.cc"
    break;

  case 8: // $@4: %empty
#line 156 "d2_parser.yy"
                    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 740 "d2_parser.cc"
    break;

  case 10: // $@5: %empty
#line 157 "d2_parser.yy"
                     { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 746 "d2_parser.cc"
    break;

  case 12: // $@6: %empty
#line 158 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 752 "d2_parser.cc"
    break;

  case 14: // $@7: %empty
#line 159 "d2_parser.yy"
                        { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 758 "d2_parser.cc"
    break;

  case 16: // $@8: %empty
#line 160 "d2_parser.yy"
                      { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 764 "d2_parser.cc"
    break;

  case 18: // $@9: %empty
#line 161 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 770 "d2_parser.cc"
    break;

  case 20: // $@10: %empty
#line 162 "d2_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 776 "d2_parser.cc"
    break;

  case 22: // value: "integer"
#line 170 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "d2_parser.cc"
    break;

  case 23: // value: "floating point"
#line 171 "d2_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 788 "d2_parser.cc"
    break;

  case 24: // value: "boolean"
#line 172 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 794 "d2_parser.cc"
    break;

  case 25: // value: "constant string"
#line 173 "d2_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 800 "d2_parser.cc"
    break;

  case 26: // value: "null"
#line 174 "d2_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 806 "d2_parser.cc"
    break;

  case 27: // value: map2
#line 175 "d2_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 812 "d2_parser.cc"
    break;

  case 28: // value: list_generic
#line 176 "d2_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 818 "d2_parser.cc"
    break;

  case 29: // sub_json: value
#line 179 "d2_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 827 "d2_parser.cc"
    break;

  case 30: // $@11: %empty
#line 184 "d2_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 838 "d2_parser.cc"
    break;

  case 31: // map2: "{" $@11 map_content "}"
#line 189 "d2_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 848 "d2_parser.cc"
    break;

  case 32: // map_value: map2
#line 195 "d2_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 854 "d2_parser.cc"
    break;

  case 35: // not_empty_map: "constant string" ":" value
#line 202 "d2_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 864 "d2_parser.cc"
    break;

  case 36: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 207 "d2_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 875 "d2_parser.cc"
    break;

  case 37: // not_empty_map: not_empty_map ","
#line 213 "d2_parser.yy"
                                   {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 883 "d2_parser.cc"
    break;

  case 38: // $@12: %empty
#line 218 "d2_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 892 "d2_parser.cc"
    break;

  case 39: // list_generic: "[" $@12 list_content "]"
#line 221 "d2_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 900 "d2_parser.cc"
    break;

  case 42: // not_empty_list: value
#line 229 "d2_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 909 "d2_parser.cc"
    break;

  case 43: // not_empty_list: not_empty_list "," value
#line 233 "d2_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 918 "d2_parser.cc"
    break;

  case 44: // not_empty_list: not_empty_list ","
#line 237 "d2_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 926 "d2_parser.cc"
    break;

  case 45: // unknown_map_entry: "constant string" ":"
#line 247 "d2_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 937 "d2_parser.cc"
    break;

  case 46: // $@13: %empty
#line 256 "d2_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 948 "d2_parser.cc"
    break;

  case 47: // syntax_map: "{" $@13 global_object "}"
#line 261 "d2_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 958 "d2_parser.cc"
    break;

  case 48: // $@14: %empty
#line 269 "d2_parser.yy"
                        {
    ctx.unique("DhcpDdns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 970 "d2_parser.cc"
    break;

  case 49: // global_object: "DhcpDdns" $@14 ":" "{" dhcpddns_params "}"
#line 275 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 979 "d2_parser.cc"
    break;

  case 51: // global_object_comma: global_object ","
#line 282 "d2_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 987 "d2_parser.cc"
    break;

  case 52: // $@15: %empty
#line 286 "d2_parser.yy"
                             {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "d2_parser.cc"
    break;

  case 53: // sub_dhcpddns: "{" $@15 dhcpddns_params "}"
#line 290 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1005 "d2_parser.cc"
    break;

  case 56: // dhcpddns_params: dhcpddns_params ","
#line 296 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1013 "d2_parser.cc"
    break;

  case 71: // $@16: %empty
#line 318 "d2_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1022 "d2_parser.cc"
    break;

  case 72: // ip_address: "ip-address" $@16 ":" "constant string"
#line 321 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1032 "d2_parser.cc"
    break;

  case 73: // port: "port" ":" "integer"
#line 327 "d2_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1045 "d2_parser.cc"
    break;

  case 74: // dns_server_timeout: "dns-server-timeout" ":" "integer"
#line 336 "d2_parser.yy"
                                                     {
    ctx.unique("dns-server-timeout", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 1059 "d2_parser.cc"
    break;

  case 75: // $@17: %empty
#line 346 "d2_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 1068 "d2_parser.cc"
    break;

  case 76: // ncr_protocol: "ncr-protocol" $@17 ":" ncr_protocol_value
#line 349 "d2_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1077 "d2_parser.cc"
    break;

  case 77: // ncr_protocol_value: "UDP"
#line 355 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1083 "d2_parser.cc"
    break;

  case 78: // ncr_protocol_value: "TCP"
#line 356 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1089 "d2_parser.cc"
    break;

  case 79: // $@18: %empty
#line 359 "d2_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1098 "d2_parser.cc"
    break;

  case 80: // ncr_format: "ncr-format" $@18 ":" "JSON"
#line 362 "d2_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1108 "d2_parser.cc"
    break;

  case 81: // $@19: %empty
#line 368 "d2_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1116 "d2_parser.cc"
    break;

  case 82: // user_context: "user-context" $@19 ":" map_value
#line 370 "d2_parser.yy"
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
#line 1143 "d2_parser.cc"
    break;

  case 83: // $@20: %empty
#line 393 "d2_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1151 "d2_parser.cc"
    break;

  case 84: // comment: "comment" $@20 ":" "constant string"
#line 395 "d2_parser.yy"
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
#line 1180 "d2_parser.cc"
    break;

  case 85: // $@21: %empty
#line 420 "d2_parser.yy"
                            {
    ctx.unique("forward-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1192 "d2_parser.cc"
    break;

  case 86: // forward_ddns: "forward-ddns" $@21 ":" "{" ddns_mgr_params "}"
#line 426 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1201 "d2_parser.cc"
    break;

  case 87: // $@22: %empty
#line 431 "d2_parser.yy"
                            {
    ctx.unique("reverse-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1213 "d2_parser.cc"
    break;

  case 88: // reverse_ddns: "reverse-ddns" $@22 ":" "{" ddns_mgr_params "}"
#line 437 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1222 "d2_parser.cc"
    break;

  case 93: // not_empty_ddns_mgr_params: ddns_mgr_params ","
#line 448 "d2_parser.yy"
                                                 {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 1230 "d2_parser.cc"
    break;

  case 96: // $@23: %empty
#line 459 "d2_parser.yy"
                           {
    ctx.unique("ddns-domains", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1242 "d2_parser.cc"
    break;

  case 97: // ddns_domains: "ddns-domains" $@23 ":" "[" ddns_domain_list "]"
#line 465 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1251 "d2_parser.cc"
    break;

  case 98: // $@24: %empty
#line 470 "d2_parser.yy"
                                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1260 "d2_parser.cc"
    break;

  case 99: // sub_ddns_domains: "[" $@24 ddns_domain_list "]"
#line 473 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1268 "d2_parser.cc"
    break;

  case 104: // not_empty_ddns_domain_list: not_empty_ddns_domain_list ","
#line 483 "d2_parser.yy"
                                                           {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1276 "d2_parser.cc"
    break;

  case 105: // $@25: %empty
#line 488 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1286 "d2_parser.cc"
    break;

  case 106: // ddns_domain: "{" $@25 ddns_domain_params "}"
#line 492 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1294 "d2_parser.cc"
    break;

  case 107: // $@26: %empty
#line 496 "d2_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1303 "d2_parser.cc"
    break;

  case 108: // sub_ddns_domain: "{" $@26 ddns_domain_params "}"
#line 499 "d2_parser.yy"
                                    {
    // parsing completed
}
#line 1311 "d2_parser.cc"
    break;

  case 111: // ddns_domain_params: ddns_domain_params ","
#line 505 "d2_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 1319 "d2_parser.cc"
    break;

  case 118: // $@27: %empty
#line 519 "d2_parser.yy"
                       {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1328 "d2_parser.cc"
    break;

  case 119: // ddns_domain_name: "name" $@27 ":" "constant string"
#line 522 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1342 "d2_parser.cc"
    break;

  case 120: // $@28: %empty
#line 532 "d2_parser.yy"
                        {
    ctx.unique("key-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1351 "d2_parser.cc"
    break;

  case 121: // ddns_key_name: "key-name" $@28 ":" "constant string"
#line 535 "d2_parser.yy"
               {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1362 "d2_parser.cc"
    break;

  case 122: // $@29: %empty
#line 545 "d2_parser.yy"
                         {
    ctx.unique("dns-servers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1374 "d2_parser.cc"
    break;

  case 123: // dns_servers: "dns-servers" $@29 ":" "[" dns_server_list "]"
#line 551 "d2_parser.yy"
                                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1383 "d2_parser.cc"
    break;

  case 124: // $@30: %empty
#line 556 "d2_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1392 "d2_parser.cc"
    break;

  case 125: // sub_dns_servers: "[" $@30 dns_server_list "]"
#line 559 "d2_parser.yy"
                                  {
    // parsing completed
}
#line 1400 "d2_parser.cc"
    break;

  case 128: // dns_server_list: dns_server_list ","
#line 565 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1408 "d2_parser.cc"
    break;

  case 129: // $@31: %empty
#line 570 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1418 "d2_parser.cc"
    break;

  case 130: // dns_server: "{" $@31 dns_server_params "}"
#line 574 "d2_parser.yy"
                                   {
    ctx.stack_.pop_back();
}
#line 1426 "d2_parser.cc"
    break;

  case 131: // $@32: %empty
#line 578 "d2_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1435 "d2_parser.cc"
    break;

  case 132: // sub_dns_server: "{" $@32 dns_server_params "}"
#line 581 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1443 "d2_parser.cc"
    break;

  case 135: // dns_server_params: dns_server_params ","
#line 587 "d2_parser.yy"
                                         {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1451 "d2_parser.cc"
    break;

  case 143: // $@33: %empty
#line 601 "d2_parser.yy"
                              {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1460 "d2_parser.cc"
    break;

  case 144: // dns_server_hostname: "hostname" $@33 ":" "constant string"
#line 604 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1474 "d2_parser.cc"
    break;

  case 145: // $@34: %empty
#line 614 "d2_parser.yy"
                                  {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1483 "d2_parser.cc"
    break;

  case 146: // dns_server_ip_address: "ip-address" $@34 ":" "constant string"
#line 617 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1493 "d2_parser.cc"
    break;

  case 147: // dns_server_port: "port" ":" "integer"
#line 623 "d2_parser.yy"
                                    {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1506 "d2_parser.cc"
    break;

  case 148: // $@35: %empty
#line 638 "d2_parser.yy"
                     {
    ctx.unique("tsig-keys", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1518 "d2_parser.cc"
    break;

  case 149: // tsig_keys: "tsig-keys" $@35 ":" "[" tsig_keys_list "]"
#line 644 "d2_parser.yy"
                                                       {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1527 "d2_parser.cc"
    break;

  case 150: // $@36: %empty
#line 649 "d2_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1536 "d2_parser.cc"
    break;

  case 151: // sub_tsig_keys: "[" $@36 tsig_keys_list "]"
#line 652 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1544 "d2_parser.cc"
    break;

  case 156: // not_empty_tsig_keys_list: not_empty_tsig_keys_list ","
#line 662 "d2_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1552 "d2_parser.cc"
    break;

  case 157: // $@37: %empty
#line 667 "d2_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1562 "d2_parser.cc"
    break;

  case 158: // tsig_key: "{" $@37 tsig_key_params "}"
#line 671 "d2_parser.yy"
                                 {
    ctx.stack_.pop_back();
}
#line 1570 "d2_parser.cc"
    break;

  case 159: // $@38: %empty
#line 675 "d2_parser.yy"
                             {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1580 "d2_parser.cc"
    break;

  case 160: // sub_tsig_key: "{" $@38 tsig_key_params "}"
#line 679 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1588 "d2_parser.cc"
    break;

  case 163: // tsig_key_params: tsig_key_params ","
#line 686 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1596 "d2_parser.cc"
    break;

  case 172: // $@39: %empty
#line 701 "d2_parser.yy"
                    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1605 "d2_parser.cc"
    break;

  case 173: // tsig_key_name: "name" $@39 ":" "constant string"
#line 704 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1619 "d2_parser.cc"
    break;

  case 174: // $@40: %empty
#line 714 "d2_parser.yy"
                              {
    ctx.unique("algorithm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1628 "d2_parser.cc"
    break;

  case 175: // tsig_key_algorithm: "algorithm" $@40 ":" "constant string"
#line 717 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1641 "d2_parser.cc"
    break;

  case 176: // tsig_key_digest_bits: "digest-bits" ":" "integer"
#line 726 "d2_parser.yy"
                                                {
    ctx.unique("digest-bits", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1654 "d2_parser.cc"
    break;

  case 177: // $@41: %empty
#line 735 "d2_parser.yy"
                        {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.unique("secret-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "d2_parser.cc"
    break;

  case 178: // tsig_key_secret: "secret" $@41 ":" "constant string"
#line 739 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1677 "d2_parser.cc"
    break;

  case 179: // $@42: %empty
#line 748 "d2_parser.yy"
                                  {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.unique("secret-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1687 "d2_parser.cc"
    break;

  case 180: // tsig_key_secret_file: "secret-file" $@42 ":" "constant string"
#line 752 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret file name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret-file", elem);
    ctx.leave();
}
#line 1700 "d2_parser.cc"
    break;

  case 181: // $@43: %empty
#line 766 "d2_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1712 "d2_parser.cc"
    break;

  case 182: // control_sockets: "control-sockets" $@43 ":" "[" control_socket_list "]"
#line 772 "d2_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1721 "d2_parser.cc"
    break;

  case 187: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 783 "d2_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 1729 "d2_parser.cc"
    break;

  case 188: // $@44: %empty
#line 788 "d2_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1739 "d2_parser.cc"
    break;

  case 189: // control_socket_entry: "{" $@44 control_socket_params "}"
#line 792 "d2_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 1747 "d2_parser.cc"
    break;

  case 192: // control_socket_params: control_socket_params ","
#line 798 "d2_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1755 "d2_parser.cc"
    break;

  case 205: // $@45: %empty
#line 817 "d2_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 1764 "d2_parser.cc"
    break;

  case 206: // control_socket_type: "socket-type" $@45 ":" control_socket_type_value
#line 820 "d2_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1773 "d2_parser.cc"
    break;

  case 207: // control_socket_type_value: "unix"
#line 826 "d2_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1779 "d2_parser.cc"
    break;

  case 208: // control_socket_type_value: "http"
#line 827 "d2_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1785 "d2_parser.cc"
    break;

  case 209: // control_socket_type_value: "https"
#line 828 "d2_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "d2_parser.cc"
    break;

  case 210: // $@46: %empty
#line 831 "d2_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1801 "d2_parser.cc"
    break;

  case 211: // control_socket_name: "socket-name" $@46 ":" "constant string"
#line 835 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1811 "d2_parser.cc"
    break;

  case 212: // $@47: %empty
#line 841 "d2_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1821 "d2_parser.cc"
    break;

  case 213: // control_socket_address: "socket-address" $@47 ":" "constant string"
#line 845 "d2_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 1831 "d2_parser.cc"
    break;

  case 214: // control_socket_port: "socket-port" ":" "integer"
#line 851 "d2_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 1841 "d2_parser.cc"
    break;

  case 215: // $@48: %empty
#line 857 "d2_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1850 "d2_parser.cc"
    break;

  case 216: // trust_anchor: "trust-anchor" $@48 ":" "constant string"
#line 860 "d2_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 1860 "d2_parser.cc"
    break;

  case 217: // $@49: %empty
#line 866 "d2_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "d2_parser.cc"
    break;

  case 218: // cert_file: "cert-file" $@49 ":" "constant string"
#line 869 "d2_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 1879 "d2_parser.cc"
    break;

  case 219: // $@50: %empty
#line 875 "d2_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1888 "d2_parser.cc"
    break;

  case 220: // key_file: "key-file" $@50 ":" "constant string"
#line 878 "d2_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 1898 "d2_parser.cc"
    break;

  case 221: // cert_required: "cert-required" ":" "boolean"
#line 884 "d2_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 1908 "d2_parser.cc"
    break;

  case 222: // $@51: %empty
#line 892 "d2_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 1920 "d2_parser.cc"
    break;

  case 223: // authentication: "authentication" $@51 ":" "{" auth_params "}"
#line 898 "d2_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1931 "d2_parser.cc"
    break;

  case 226: // auth_params: auth_params ","
#line 907 "d2_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 1939 "d2_parser.cc"
    break;

  case 234: // $@52: %empty
#line 921 "d2_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 1948 "d2_parser.cc"
    break;

  case 235: // auth_type: "type" $@52 ":" auth_type_value
#line 924 "d2_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1957 "d2_parser.cc"
    break;

  case 236: // auth_type_value: "basic"
#line 929 "d2_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 1963 "d2_parser.cc"
    break;

  case 237: // $@53: %empty
#line 932 "d2_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1972 "d2_parser.cc"
    break;

  case 238: // realm: "realm" $@53 ":" "constant string"
#line 935 "d2_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 1982 "d2_parser.cc"
    break;

  case 239: // $@54: %empty
#line 941 "d2_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1991 "d2_parser.cc"
    break;

  case 240: // directory: "directory" $@54 ":" "constant string"
#line 944 "d2_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 2001 "d2_parser.cc"
    break;

  case 241: // $@55: %empty
#line 950 "d2_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 2013 "d2_parser.cc"
    break;

  case 242: // clients: "clients" $@55 ":" "[" clients_list "]"
#line 956 "d2_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2022 "d2_parser.cc"
    break;

  case 247: // not_empty_clients_list: not_empty_clients_list ","
#line 967 "d2_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2030 "d2_parser.cc"
    break;

  case 248: // $@56: %empty
#line 972 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2040 "d2_parser.cc"
    break;

  case 249: // basic_auth: "{" $@56 clients_params "}"
#line 976 "d2_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 2048 "d2_parser.cc"
    break;

  case 252: // clients_params: clients_params ","
#line 982 "d2_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2056 "d2_parser.cc"
    break;

  case 260: // $@57: %empty
#line 996 "d2_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "d2_parser.cc"
    break;

  case 261: // user: "user" $@57 ":" "constant string"
#line 999 "d2_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2075 "d2_parser.cc"
    break;

  case 262: // $@58: %empty
#line 1005 "d2_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2084 "d2_parser.cc"
    break;

  case 263: // user_file: "user-file" $@58 ":" "constant string"
#line 1008 "d2_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 2094 "d2_parser.cc"
    break;

  case 264: // $@59: %empty
#line 1014 "d2_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2103 "d2_parser.cc"
    break;

  case 265: // password: "password" $@59 ":" "constant string"
#line 1017 "d2_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2113 "d2_parser.cc"
    break;

  case 266: // $@60: %empty
#line 1023 "d2_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2122 "d2_parser.cc"
    break;

  case 267: // password_file: "password-file" $@60 ":" "constant string"
#line 1026 "d2_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2132 "d2_parser.cc"
    break;

  case 268: // $@61: %empty
#line 1034 "d2_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2144 "d2_parser.cc"
    break;

  case 269: // hooks_libraries: "hooks-libraries" $@61 ":" "[" hooks_libraries_list "]"
#line 1040 "d2_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2153 "d2_parser.cc"
    break;

  case 274: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1051 "d2_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2161 "d2_parser.cc"
    break;

  case 275: // $@62: %empty
#line 1056 "d2_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2171 "d2_parser.cc"
    break;

  case 276: // hooks_library: "{" $@62 hooks_params "}"
#line 1060 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2181 "d2_parser.cc"
    break;

  case 277: // $@63: %empty
#line 1066 "d2_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2191 "d2_parser.cc"
    break;

  case 278: // sub_hooks_library: "{" $@63 hooks_params "}"
#line 1070 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2201 "d2_parser.cc"
    break;

  case 281: // hooks_params: hooks_params ","
#line 1078 "d2_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2209 "d2_parser.cc"
    break;

  case 285: // $@64: %empty
#line 1088 "d2_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2218 "d2_parser.cc"
    break;

  case 286: // library: "library" $@64 ":" "constant string"
#line 1091 "d2_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2228 "d2_parser.cc"
    break;

  case 287: // $@65: %empty
#line 1097 "d2_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2237 "d2_parser.cc"
    break;

  case 288: // parameters: "parameters" $@65 ":" map_value
#line 1100 "d2_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2246 "d2_parser.cc"
    break;

  case 289: // $@66: %empty
#line 1107 "d2_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2258 "d2_parser.cc"
    break;

  case 290: // loggers: "loggers" $@66 ":" "[" loggers_entries "]"
#line 1113 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2267 "d2_parser.cc"
    break;

  case 293: // loggers_entries: loggers_entries ","
#line 1122 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 2275 "d2_parser.cc"
    break;

  case 294: // $@67: %empty
#line 1128 "d2_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2285 "d2_parser.cc"
    break;

  case 295: // logger_entry: "{" $@67 logger_params "}"
#line 1132 "d2_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 2293 "d2_parser.cc"
    break;

  case 298: // logger_params: logger_params ","
#line 1138 "d2_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 2301 "d2_parser.cc"
    break;

  case 306: // $@68: %empty
#line 1152 "d2_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2310 "d2_parser.cc"
    break;

  case 307: // name: "name" $@68 ":" "constant string"
#line 1155 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2320 "d2_parser.cc"
    break;

  case 308: // debuglevel: "debuglevel" ":" "integer"
#line 1161 "d2_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2330 "d2_parser.cc"
    break;

  case 309: // $@69: %empty
#line 1167 "d2_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2339 "d2_parser.cc"
    break;

  case 310: // severity: "severity" $@69 ":" "constant string"
#line 1170 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2349 "d2_parser.cc"
    break;

  case 311: // $@70: %empty
#line 1176 "d2_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2361 "d2_parser.cc"
    break;

  case 312: // output_options_list: "output-options" $@70 ":" "[" output_options_list_content "]"
#line 1182 "d2_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2370 "d2_parser.cc"
    break;

  case 315: // output_options_list_content: output_options_list_content ","
#line 1189 "d2_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2378 "d2_parser.cc"
    break;

  case 316: // $@71: %empty
#line 1194 "d2_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2388 "d2_parser.cc"
    break;

  case 317: // output_entry: "{" $@71 output_params_list "}"
#line 1198 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 2396 "d2_parser.cc"
    break;

  case 320: // output_params_list: output_params_list ","
#line 1204 "d2_parser.yy"
                                        {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 2404 "d2_parser.cc"
    break;

  case 326: // $@72: %empty
#line 1216 "d2_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "d2_parser.cc"
    break;

  case 327: // output: "output" $@72 ":" "constant string"
#line 1219 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2423 "d2_parser.cc"
    break;

  case 328: // flush: "flush" ":" "boolean"
#line 1225 "d2_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 2433 "d2_parser.cc"
    break;

  case 329: // maxsize: "maxsize" ":" "integer"
#line 1231 "d2_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 2443 "d2_parser.cc"
    break;

  case 330: // maxver: "maxver" ":" "integer"
#line 1237 "d2_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 2453 "d2_parser.cc"
    break;

  case 331: // $@73: %empty
#line 1243 "d2_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2462 "d2_parser.cc"
    break;

  case 332: // pattern: "pattern" $@73 ":" "constant string"
#line 1246 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 2472 "d2_parser.cc"
    break;


#line 2476 "d2_parser.cc"

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
  D2Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  D2Parser::yytnamerr_ (const char *yystr)
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
  D2Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // D2Parser::context.
  D2Parser::context::context (const D2Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  D2Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  D2Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  D2Parser::yysyntax_error_ (const context& yyctx) const
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


  const short D2Parser::yypact_ninf_ = -200;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short
  D2Parser::yypact_[] =
  {
     100,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,    23,     8,     1,    24,    39,    84,    83,    87,    96,
      99,   108,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,     8,   -27,   116,     7,    43,   121,    86,   122,
      21,   123,   -12,  -200,   140,   149,   154,   156,   159,  -200,
      22,  -200,  -200,   161,   174,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,   195,  -200,    67,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,   202,  -200,  -200,  -200,  -200,  -200,  -200,
      75,  -200,  -200,  -200,  -200,  -200,  -200,  -200,   203,   208,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,    94,  -200,  -200,
    -200,  -200,  -200,   206,   210,  -200,  -200,   211,  -200,  -200,
    -200,  -200,  -200,   104,  -200,  -200,  -200,  -200,  -200,     4,
    -200,  -200,  -200,  -200,   110,  -200,  -200,  -200,  -200,     8,
       8,  -200,   137,   212,  -200,  -200,   213,   120,   141,   214,
     216,   217,   218,   219,   220,   221,   222,   223,   224,  -200,
       7,  -200,   225,   153,   226,   228,   229,    43,  -200,    43,
    -200,   121,   230,   231,   232,    86,  -200,    86,  -200,   122,
     233,   160,   235,    21,  -200,    21,   123,  -200,   236,   237,
       3,  -200,  -200,  -200,   238,   239,   166,  -200,  -200,    66,
     227,   240,   167,   241,   242,   245,   247,   248,   249,  -200,
     180,  -200,   187,   188,   189,  -200,   111,  -200,   191,   254,
     197,  -200,   119,  -200,   198,  -200,   199,  -200,   152,  -200,
     200,   240,  -200,     8,     7,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,    19,    19,   121,   253,   256,   262,  -200,
    -200,  -200,  -200,  -200,  -200,   123,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,   176,  -200,  -200,   182,  -200,  -200,
    -200,   183,   264,  -200,   265,   269,  -200,  -200,   272,   276,
    -200,  -200,    45,  -200,    54,  -200,   277,    19,  -200,  -200,
    -200,    16,  -200,   253,   -12,  -200,   256,    18,   262,  -200,
    -200,   275,  -200,  -200,  -200,  -200,   278,  -200,  -200,  -200,
    -200,   279,  -200,  -200,  -200,   184,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,   185,  -200,  -200,
    -200,   280,  -200,  -200,  -200,  -200,   186,  -200,  -200,  -200,
    -200,  -200,  -200,   122,   281,   282,   283,   215,   284,   285,
     286,   287,   234,    16,  -200,  -200,   288,   290,   243,   291,
      18,  -200,   292,   169,   246,   250,  -200,   289,   251,   255,
     257,  -200,  -200,   258,   294,  -200,   260,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,    80,  -200,  -200,  -200,  -200,
     293,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,   192,
    -200,  -200,  -200,  -200,  -200,  -200,    88,  -200,   297,   298,
     299,   300,    80,  -200,   117,   293,  -200,   263,   261,   266,
     301,  -200,  -200,   303,   304,   305,  -200,   193,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,   306,
     307,   259,   244,   252,   308,   117,  -200,  -200,   309,   313,
    -200,   267,  -200,  -200,  -200,   268,  -200,    89,  -200,   306,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,   194,
    -200,  -200,  -200,  -200,  -200,  -200,   315,   316,   322,   327,
      89,  -200,   270,   271,   274,   295,  -200,  -200,  -200,  -200,
    -200
  };

  const short
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    38,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    46,     5,    52,     7,   159,     9,
     150,    11,   107,    13,    98,    15,   131,    17,   124,    19,
     277,    21,    40,    33,     0,     0,     0,   152,     0,   100,
       0,     0,     0,    42,     0,    41,     0,     0,    34,    48,
       0,    50,    71,     0,     0,    75,    79,    81,    83,    85,
      87,   148,   181,   268,   289,     0,    70,     0,    54,    57,
      58,    59,    60,    61,    68,    69,    62,    63,    64,    65,
      66,    67,   174,     0,   177,   179,   172,   171,   169,   170,
       0,   161,   164,   165,   166,   167,   168,   157,     0,   153,
     154,   120,   122,   118,   117,   115,   116,     0,   109,   112,
     113,   114,   105,     0,   101,   102,   145,     0,   143,   142,
     140,   141,   139,     0,   133,   136,   137,   138,   129,     0,
     126,   285,   287,   282,     0,   279,   283,   284,    39,    44,
       0,    31,    37,     0,    51,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
      56,    53,     0,     0,     0,     0,     0,   163,   160,     0,
     151,   156,     0,     0,     0,   111,   108,     0,    99,   104,
       0,     0,     0,   135,   132,     0,   128,   125,     0,     0,
     281,   278,    43,    35,     0,     0,     0,    73,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
       0,   176,     0,     0,     0,   162,     0,   155,     0,     0,
       0,   110,     0,   103,     0,   147,     0,   134,     0,   127,
       0,     0,   280,     0,     0,    72,    77,    78,    76,    80,
      32,    82,    84,    89,    89,   152,   183,   270,     0,   175,
     178,   180,   173,   158,   121,     0,   119,   106,   146,   144,
     130,   286,   288,    36,     0,    96,    95,     0,    90,    91,
      94,     0,     0,   188,     0,   184,   185,   275,     0,   271,
     272,   294,     0,   291,     0,    49,     0,    93,    86,    88,
     149,     0,   182,   187,     0,   269,   274,     0,   293,   290,
     123,     0,    92,   205,   210,   212,     0,   222,   215,   217,
     219,     0,   204,   202,   203,     0,   190,   193,   194,   195,
     196,   198,   199,   200,   201,   197,   186,     0,   273,   306,
     311,     0,   309,   305,   303,   304,     0,   296,   299,   301,
     302,   300,   292,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   192,   189,   276,     0,     0,     0,     0,
     298,   295,     0,     0,     0,     0,   214,     0,     0,     0,
       0,   221,   191,     0,     0,   308,     0,   297,    97,   207,
     208,   209,   206,   211,   213,     0,   216,   218,   220,   307,
       0,   310,   234,   237,   239,   241,   233,   232,   231,     0,
     224,   227,   228,   229,   230,   316,     0,   313,     0,     0,
       0,     0,   226,   223,     0,   315,   312,     0,     0,     0,
       0,   225,   326,     0,     0,     0,   331,     0,   318,   321,
     322,   323,   324,   325,   314,   236,   235,   238,   240,   243,
       0,     0,     0,     0,     0,   320,   317,   248,     0,   244,
     245,     0,   328,   329,   330,     0,   319,     0,   242,   247,
     327,   332,   260,   262,   264,   266,   259,   257,   258,     0,
     250,   253,   254,   255,   256,   246,     0,     0,     0,     0,
     252,   249,     0,     0,     0,     0,   251,   261,   263,   265,
     267
  };

  const short
  D2Parser::yypgoto_[] =
  {
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,   -43,  -200,  -199,  -200,    46,  -200,  -200,  -200,
    -200,  -200,  -200,   -56,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,    56,   162,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,   -55,  -200,   -44,  -200,  -200,  -200,  -200,  -200,
      69,  -200,    33,  -200,  -200,  -200,  -200,   -22,  -200,   147,
    -200,  -200,  -200,   155,   158,  -200,  -200,   -49,  -200,  -200,
    -200,  -200,  -200,    79,   150,  -200,  -200,  -200,   157,   163,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,    90,
    -200,   168,  -200,  -200,  -200,   171,   170,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
      50,  -200,  -200,   -15,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,   -68,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -114,  -200,  -200,  -133,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
      52,  -200,  -200,  -200,    55,   164,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,    53,  -200,  -200,   -10,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,   -62,  -200,  -200,   -90,  -200,
    -200,  -200,  -200,  -200,  -200,  -200
  };

  const short
  D2Parser::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    30,    31,    32,    53,   261,    67,    68,    33,
      52,    64,    65,    86,    35,    54,    70,   163,    71,    37,
      55,    87,    88,    89,   166,    90,    91,    92,   169,   258,
      93,   170,    94,   171,    95,   172,    96,   173,    97,   174,
     287,   288,   289,   290,   306,    45,    59,   133,   134,   135,
     197,    43,    58,   127,   128,   129,   194,   130,   192,   131,
     193,    49,    61,   149,   150,   205,    47,    60,   143,   144,
     145,   202,   146,   200,   147,    98,   175,    41,    57,   118,
     119,   120,   189,    39,    56,   110,   111,   112,   186,   113,
     182,   114,   115,   184,   116,   185,    99,   176,   294,   295,
     296,   311,   335,   336,   337,   364,   402,   338,   365,   339,
     366,   340,   341,   369,   342,   370,   343,   371,   344,   345,
     368,   419,   420,   421,   428,   456,   422,   429,   423,   430,
     424,   431,   468,   469,   470,   477,   489,   490,   491,   496,
     492,   497,   493,   498,   494,   499,   100,   177,   298,   299,
     300,   314,    51,    62,   154,   155,   156,   208,   157,   209,
     101,   178,   302,   303,   317,   356,   357,   358,   376,   359,
     360,   379,   361,   377,   426,   427,   434,   447,   448,   449,
     460,   450,   451,   452,   453,   464
  };

  const short
  D2Parser::yytable_[] =
  {
     107,   108,   124,   125,   139,   140,   153,   206,    34,    63,
     207,   142,   109,    23,   126,    24,   141,    25,    72,    73,
      74,    75,   260,    22,    76,   164,    77,    78,    79,    80,
     165,    36,   136,   137,    81,    77,    78,    77,    78,    82,
      77,    78,   285,   151,   152,   121,    38,   138,   318,   323,
      66,   319,   260,   324,   325,   326,   327,   206,   151,   152,
     320,    83,    77,    78,    84,    85,   328,   329,   330,   331,
     180,   102,   103,   104,   105,   181,   349,   350,   187,   351,
     352,   256,   257,   188,    85,    26,    27,    28,    29,    40,
      42,   435,    44,    85,   436,    85,    85,   195,    85,    77,
      78,   106,   196,    46,    48,    77,    78,   203,    77,    78,
     121,   122,   204,   210,   187,    50,   212,   213,   211,   273,
      85,   412,   195,   413,   414,   415,    69,   277,   117,   132,
     148,   107,   108,   107,   108,   482,   483,   484,   485,   124,
     125,   124,   125,   109,   123,   109,   158,   139,   140,   139,
     140,   126,   159,   126,   142,   203,   142,    85,   160,   141,
     280,   141,   162,    85,   161,   167,    85,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,   442,   168,   180,
     443,   444,   445,   446,   305,   307,   307,   373,   210,   380,
     308,   309,   374,   375,   381,   432,   465,   500,   217,   179,
     433,   466,   501,   399,   400,   401,   183,   286,   286,   190,
     283,   191,   198,   199,   214,   201,   215,   216,   219,   218,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   230,
     232,   231,   233,   234,   238,   239,   240,   244,   245,   246,
     250,   251,   253,   255,   262,   259,   254,    24,   263,   264,
     265,   286,   266,   267,   268,   332,   333,   269,   153,   275,
     293,   353,   354,   297,   270,   271,   272,   334,   274,   301,
     310,   312,   313,   355,   276,   278,   279,   281,   315,   316,
     363,   321,   367,   372,   378,   383,   384,   385,   387,   388,
     389,   390,   393,   386,   394,   396,   405,   282,   398,   410,
     425,   437,   438,   439,   440,   455,   459,   461,   462,   463,
     284,   471,   475,   467,   391,   478,   479,   332,   333,   502,
     503,   395,   473,   403,   353,   354,   504,   404,   406,   334,
     474,   505,   407,   291,   408,   409,   355,   411,   457,   472,
     322,   382,   229,   458,   480,   481,   243,   507,   508,   416,
     417,   509,   242,   241,   304,   292,   249,   235,   392,   237,
     236,   418,   248,   346,   441,   495,   247,   506,   348,   347,
     397,   362,   510,   454,   252,   476,   416,   417,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   418,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   486,   487,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   488,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   486,   487,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   488
  };

  const short
  D2Parser::yycheck_[] =
  {
      56,    56,    58,    58,    60,    60,    62,     3,     7,    52,
       6,    60,    56,     5,    58,     7,    60,     9,    11,    12,
      13,    14,   221,     0,    17,     3,    19,    20,    21,    22,
       8,     7,    11,    12,    27,    19,    20,    19,    20,    32,
      19,    20,    23,    55,    56,    24,     7,    26,     3,    33,
      77,     6,   251,    37,    38,    39,    40,     3,    55,    56,
       6,    54,    19,    20,    57,    77,    50,    51,    52,    53,
       3,    28,    29,    30,    31,     8,    58,    59,     3,    61,
      62,    15,    16,     8,    77,    77,    78,    79,    80,     5,
       7,     3,     5,    77,     6,    77,    77,     3,    77,    19,
      20,    58,     8,     7,     5,    19,    20,     3,    19,    20,
      24,    25,     8,     3,     3,     7,   159,   160,     8,     8,
      77,    41,     3,    43,    44,    45,    10,     8,     7,     7,
       7,   187,   187,   189,   189,    46,    47,    48,    49,   195,
     195,   197,   197,   187,    58,   189,     6,   203,   203,   205,
     205,   195,     3,   197,   203,     3,   205,    77,     4,   203,
       8,   205,     3,    77,     8,     4,    77,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    60,     4,     3,
      63,    64,    65,    66,     8,     3,     3,     3,     3,     3,
       8,     8,     8,     8,     8,     3,     3,     3,    78,     4,
       8,     8,     8,    34,    35,    36,     4,   263,   264,     6,
     253,     3,     6,     3,    77,     4,     4,     4,     4,    78,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,    78,     4,     4,     4,     4,     4,     4,    78,     4,
       4,     4,     4,    77,    77,    18,     7,     7,     7,     7,
       5,   307,     5,     5,     5,   311,   311,    77,   314,     5,
       7,   317,   317,     7,    77,    77,    77,   311,    77,     7,
       6,     6,     3,   317,    77,    77,    77,    77,     6,     3,
       5,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    78,     4,     4,     7,   251,     6,     5,
       7,     4,     4,     4,     4,    42,     5,     4,     4,     4,
     254,     4,     4,     7,    80,     6,     3,   373,   373,     4,
       4,    78,    78,    77,   380,   380,     4,    77,    77,   373,
      78,     4,    77,   264,    77,    77,   380,    77,    77,    80,
     307,   363,   180,    77,    77,    77,   199,    77,    77,   405,
     405,    77,   197,   195,   275,   265,   206,   187,   373,   191,
     189,   405,   205,   313,   432,   479,   203,   500,   316,   314,
     380,   318,    77,   435,   210,   465,   432,   432,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   432,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   477,   477,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   477,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   500,   500,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   500
  };

  const short
  D2Parser::yystos_[] =
  {
       0,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     0,     5,     7,     9,    77,    78,    79,    80,
      93,    94,    95,   100,     7,   105,     7,   110,     7,   174,
       5,   168,     7,   142,     5,   136,     7,   157,     5,   152,
       7,   243,   101,    96,   106,   111,   175,   169,   143,   137,
     158,   153,   244,    93,   102,   103,    77,    98,    99,    10,
     107,   109,    11,    12,    13,    14,    17,    19,    20,    21,
      22,    27,    32,    54,    57,    77,   104,   112,   113,   114,
     116,   117,   118,   121,   123,   125,   127,   129,   166,   187,
     237,   251,    28,    29,    30,    31,    58,   104,   123,   125,
     176,   177,   178,   180,   182,   183,   185,     7,   170,   171,
     172,    24,    25,    58,   104,   123,   125,   144,   145,   146,
     148,   150,     7,   138,   139,   140,    11,    12,    26,   104,
     123,   125,   148,   159,   160,   161,   163,   165,     7,   154,
     155,    55,    56,   104,   245,   246,   247,   249,     6,     3,
       4,     8,     3,   108,     3,     8,   115,     4,     4,   119,
     122,   124,   126,   128,   130,   167,   188,   238,   252,     4,
       3,     8,   181,     4,   184,   186,   179,     3,     8,   173,
       6,     3,   149,   151,   147,     3,     8,   141,     6,     3,
     164,     4,   162,     3,     8,   156,     3,     6,   248,   250,
       3,     8,    93,    93,    77,     4,     4,    78,    78,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   113,
       4,    78,     4,     4,     4,   177,   176,   172,     4,     4,
       4,   145,   144,   140,     4,    78,     4,   160,   159,   155,
       4,     4,   246,     4,     7,    77,    15,    16,   120,    18,
      95,    97,    77,     7,     7,     5,     5,     5,     5,    77,
      77,    77,    77,     8,    77,     5,    77,     8,    77,    77,
       8,    77,    97,    93,   112,    23,   104,   131,   132,   133,
     134,   131,   170,     7,   189,   190,   191,     7,   239,   240,
     241,     7,   253,   254,   154,     8,   135,     3,     8,     8,
       6,   192,     6,     3,   242,     6,     3,   255,     3,     6,
       6,     4,   133,    33,    37,    38,    39,    40,    50,    51,
      52,    53,   104,   123,   125,   193,   194,   195,   198,   200,
     202,   203,   205,   207,   209,   210,   191,   245,   241,    58,
      59,    61,    62,   104,   123,   125,   256,   257,   258,   260,
     261,   263,   254,     5,   196,   199,   201,     4,   211,   204,
     206,   208,     4,     3,     8,     8,   259,   264,     4,   262,
       3,     8,   138,     4,     4,     4,    78,     4,     4,     4,
       4,    80,   194,     4,     4,    78,     4,   257,     6,    34,
      35,    36,   197,    77,    77,     7,    77,    77,    77,    77,
       5,    77,    41,    43,    44,    45,   104,   123,   125,   212,
     213,   214,   217,   219,   221,     7,   265,   266,   215,   218,
     220,   222,     3,     8,   267,     3,     6,     4,     4,     4,
       4,   213,    60,    63,    64,    65,    66,   268,   269,   270,
     272,   273,   274,   275,   266,    42,   216,    77,    77,     5,
     271,     4,     4,     4,   276,     3,     8,     7,   223,   224,
     225,     4,    80,    78,    78,     4,   269,   226,     6,     3,
      77,    77,    46,    47,    48,    49,   104,   123,   125,   227,
     228,   229,   231,   233,   235,   225,   230,   232,   234,   236,
       3,     8,     4,     4,     4,     4,   228,    77,    77,    77,
      77
  };

  const short
  D2Parser::yyr1_[] =
  {
       0,    81,    83,    82,    84,    82,    85,    82,    86,    82,
      87,    82,    88,    82,    89,    82,    90,    82,    91,    82,
      92,    82,    93,    93,    93,    93,    93,    93,    93,    94,
      96,    95,    97,    98,    98,    99,    99,    99,   101,   100,
     102,   102,   103,   103,   103,   104,   106,   105,   108,   107,
     107,   109,   111,   110,   112,   112,   112,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   115,   114,   116,   117,   119,   118,   120,   120,   122,
     121,   124,   123,   126,   125,   128,   127,   130,   129,   131,
     131,   132,   132,   132,   133,   133,   135,   134,   137,   136,
     138,   138,   139,   139,   139,   141,   140,   143,   142,   144,
     144,   144,   145,   145,   145,   145,   145,   145,   147,   146,
     149,   148,   151,   150,   153,   152,   154,   154,   154,   156,
     155,   158,   157,   159,   159,   159,   160,   160,   160,   160,
     160,   160,   160,   162,   161,   164,   163,   165,   167,   166,
     169,   168,   170,   170,   171,   171,   171,   173,   172,   175,
     174,   176,   176,   176,   177,   177,   177,   177,   177,   177,
     177,   177,   179,   178,   181,   180,   182,   184,   183,   186,
     185,   188,   187,   189,   189,   190,   190,   190,   192,   191,
     193,   193,   193,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   196,   195,   197,   197,   197,
     199,   198,   201,   200,   202,   204,   203,   206,   205,   208,
     207,   209,   211,   210,   212,   212,   212,   213,   213,   213,
     213,   213,   213,   213,   215,   214,   216,   218,   217,   220,
     219,   222,   221,   223,   223,   224,   224,   224,   226,   225,
     227,   227,   227,   228,   228,   228,   228,   228,   228,   228,
     230,   229,   232,   231,   234,   233,   236,   235,   238,   237,
     239,   239,   240,   240,   240,   242,   241,   244,   243,   245,
     245,   245,   245,   246,   246,   248,   247,   250,   249,   252,
     251,   253,   253,   253,   255,   254,   256,   256,   256,   257,
     257,   257,   257,   257,   257,   257,   259,   258,   260,   262,
     261,   264,   263,   265,   265,   265,   267,   266,   268,   268,
     268,   269,   269,   269,   269,   269,   271,   270,   272,   273,
     274,   276,   275
  };

  const signed char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     1,     3,     5,     2,     0,     4,
       0,     1,     1,     3,     2,     2,     0,     4,     0,     6,
       1,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     6,     0,
       1,     1,     3,     2,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     0,     6,
       0,     4,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       0,     4,     0,     4,     3,     0,     4,     0,     4,     0,
       4,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4
  };


#if D2_PARSER_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const D2Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"DhcpDdns\"",
  "\"ip-address\"", "\"port\"", "\"dns-server-timeout\"",
  "\"ncr-protocol\"", "\"UDP\"", "\"TCP\"", "\"ncr-format\"", "\"JSON\"",
  "\"user-context\"", "\"comment\"", "\"forward-ddns\"",
  "\"reverse-ddns\"", "\"ddns-domains\"", "\"key-name\"",
  "\"dns-servers\"", "\"hostname\"", "\"tsig-keys\"", "\"algorithm\"",
  "\"digest-bits\"", "\"secret\"", "\"secret-file\"",
  "\"control-sockets\"", "\"socket-type\"", "\"unix\"", "\"http\"",
  "\"https\"", "\"socket-name\"", "\"socket-address\"", "\"socket-port\"",
  "\"authentication\"", "\"type\"", "\"basic\"", "\"realm\"",
  "\"directory\"", "\"clients\"", "\"user\"", "\"user-file\"",
  "\"password\"", "\"password-file\"", "\"trust-anchor\"", "\"cert-file\"",
  "\"key-file\"", "\"cert-required\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"loggers\"", "\"name\"",
  "\"output-options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS", "SUB_TSIG_KEY", "SUB_TSIG_KEYS",
  "SUB_DDNS_DOMAIN", "SUB_DDNS_DOMAINS", "SUB_DNS_SERVER",
  "SUB_DNS_SERVERS", "SUB_HOOKS_LIBRARY", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "value", "sub_json", "map2", "$@11", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@12", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@13",
  "global_object", "$@14", "global_object_comma", "sub_dhcpddns", "$@15",
  "dhcpddns_params", "dhcpddns_param", "ip_address", "$@16", "port",
  "dns_server_timeout", "ncr_protocol", "$@17", "ncr_protocol_value",
  "ncr_format", "$@18", "user_context", "$@19", "comment", "$@20",
  "forward_ddns", "$@21", "reverse_ddns", "$@22", "ddns_mgr_params",
  "not_empty_ddns_mgr_params", "ddns_mgr_param", "ddns_domains", "$@23",
  "sub_ddns_domains", "$@24", "ddns_domain_list",
  "not_empty_ddns_domain_list", "ddns_domain", "$@25", "sub_ddns_domain",
  "$@26", "ddns_domain_params", "ddns_domain_param", "ddns_domain_name",
  "$@27", "ddns_key_name", "$@28", "dns_servers", "$@29",
  "sub_dns_servers", "$@30", "dns_server_list", "dns_server", "$@31",
  "sub_dns_server", "$@32", "dns_server_params", "dns_server_param",
  "dns_server_hostname", "$@33", "dns_server_ip_address", "$@34",
  "dns_server_port", "tsig_keys", "$@35", "sub_tsig_keys", "$@36",
  "tsig_keys_list", "not_empty_tsig_keys_list", "tsig_key", "$@37",
  "sub_tsig_key", "$@38", "tsig_key_params", "tsig_key_param",
  "tsig_key_name", "$@39", "tsig_key_algorithm", "$@40",
  "tsig_key_digest_bits", "tsig_key_secret", "$@41",
  "tsig_key_secret_file", "$@42", "control_sockets", "$@43",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@44", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@45",
  "control_socket_type_value", "control_socket_name", "$@46",
  "control_socket_address", "$@47", "control_socket_port", "trust_anchor",
  "$@48", "cert_file", "$@49", "key_file", "$@50", "cert_required",
  "authentication", "$@51", "auth_params", "auth_param", "auth_type",
  "$@52", "auth_type_value", "realm", "$@53", "directory", "$@54",
  "clients", "$@55", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@56", "clients_params", "clients_param", "user", "$@57",
  "user_file", "$@58", "password", "$@59", "password_file", "$@60",
  "hooks_libraries", "$@61", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@62",
  "sub_hooks_library", "$@63", "hooks_params", "hooks_param", "library",
  "$@64", "parameters", "$@65", "loggers", "$@66", "loggers_entries",
  "logger_entry", "$@67", "logger_params", "logger_param", "name", "$@68",
  "debuglevel", "severity", "$@69", "output_options_list", "$@70",
  "output_options_list_content", "output_entry", "$@71",
  "output_params_list", "output_params", "output", "$@72", "flush",
  "maxsize", "maxver", "pattern", "$@73", YY_NULLPTR
  };
#endif


#if D2_PARSER_DEBUG
  const short
  D2Parser::yyrline_[] =
  {
       0,   153,   153,   153,   154,   154,   155,   155,   156,   156,
     157,   157,   158,   158,   159,   159,   160,   160,   161,   161,
     162,   162,   170,   171,   172,   173,   174,   175,   176,   179,
     184,   184,   195,   198,   199,   202,   207,   213,   218,   218,
     225,   226,   229,   233,   237,   247,   256,   256,   269,   269,
     279,   282,   286,   286,   294,   295,   296,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   318,   318,   327,   336,   346,   346,   355,   356,   359,
     359,   368,   368,   393,   393,   420,   420,   431,   431,   442,
     443,   446,   447,   448,   453,   454,   459,   459,   470,   470,
     477,   478,   481,   482,   483,   488,   488,   496,   496,   503,
     504,   505,   510,   511,   512,   513,   514,   515,   519,   519,
     532,   532,   545,   545,   556,   556,   563,   564,   565,   570,
     570,   578,   578,   585,   586,   587,   592,   593,   594,   595,
     596,   597,   598,   601,   601,   614,   614,   623,   638,   638,
     649,   649,   656,   657,   660,   661,   662,   667,   667,   675,
     675,   684,   685,   686,   691,   692,   693,   694,   695,   696,
     697,   698,   701,   701,   714,   714,   726,   735,   735,   748,
     748,   766,   766,   777,   778,   781,   782,   783,   788,   788,
     796,   797,   798,   803,   804,   805,   806,   807,   808,   809,
     810,   811,   812,   813,   814,   817,   817,   826,   827,   828,
     831,   831,   841,   841,   851,   857,   857,   866,   866,   875,
     875,   884,   892,   892,   905,   906,   907,   912,   913,   914,
     915,   916,   917,   918,   921,   921,   929,   932,   932,   941,
     941,   950,   950,   961,   962,   965,   966,   967,   972,   972,
     980,   981,   982,   987,   988,   989,   990,   991,   992,   993,
     996,   996,  1005,  1005,  1014,  1014,  1023,  1023,  1034,  1034,
    1045,  1046,  1049,  1050,  1051,  1056,  1056,  1066,  1066,  1076,
    1077,  1078,  1081,  1084,  1085,  1088,  1088,  1097,  1097,  1107,
    1107,  1120,  1121,  1122,  1128,  1128,  1136,  1137,  1138,  1143,
    1144,  1145,  1146,  1147,  1148,  1149,  1152,  1152,  1161,  1167,
    1167,  1176,  1176,  1187,  1188,  1189,  1194,  1194,  1202,  1203,
    1204,  1209,  1210,  1211,  1212,  1213,  1216,  1216,  1225,  1231,
    1237,  1243,  1243
  };

  void
  D2Parser::yy_stack_print_ () const
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
  D2Parser::yy_reduce_print_ (int yyrule) const
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
#endif // D2_PARSER_DEBUG


#line 14 "d2_parser.yy"
} } // isc::d2
#line 3378 "d2_parser.cc"

#line 1252 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
