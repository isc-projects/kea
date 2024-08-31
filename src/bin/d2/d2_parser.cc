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
#line 34 "d2_parser.yy"

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

  case 72: // $@16: %empty
#line 319 "d2_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1022 "d2_parser.cc"
    break;

  case 73: // ip_address: "ip-address" $@16 ":" "constant string"
#line 322 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1032 "d2_parser.cc"
    break;

  case 74: // port: "port" ":" "integer"
#line 328 "d2_parser.yy"
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

  case 75: // dns_server_timeout: "dns-server-timeout" ":" "integer"
#line 337 "d2_parser.yy"
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

  case 76: // $@17: %empty
#line 347 "d2_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 1068 "d2_parser.cc"
    break;

  case 77: // ncr_protocol: "ncr-protocol" $@17 ":" ncr_protocol_value
#line 350 "d2_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1077 "d2_parser.cc"
    break;

  case 78: // ncr_protocol_value: "UDP"
#line 356 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1083 "d2_parser.cc"
    break;

  case 79: // ncr_protocol_value: "TCP"
#line 357 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1089 "d2_parser.cc"
    break;

  case 80: // $@18: %empty
#line 360 "d2_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1098 "d2_parser.cc"
    break;

  case 81: // ncr_format: "ncr-format" $@18 ":" "JSON"
#line 363 "d2_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1108 "d2_parser.cc"
    break;

  case 82: // $@19: %empty
#line 369 "d2_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1116 "d2_parser.cc"
    break;

  case 83: // user_context: "user-context" $@19 ":" map_value
#line 371 "d2_parser.yy"
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

  case 84: // $@20: %empty
#line 394 "d2_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1151 "d2_parser.cc"
    break;

  case 85: // comment: "comment" $@20 ":" "constant string"
#line 396 "d2_parser.yy"
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

  case 86: // $@21: %empty
#line 421 "d2_parser.yy"
                            {
    ctx.unique("forward-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1192 "d2_parser.cc"
    break;

  case 87: // forward_ddns: "forward-ddns" $@21 ":" "{" ddns_mgr_params "}"
#line 427 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1201 "d2_parser.cc"
    break;

  case 88: // $@22: %empty
#line 432 "d2_parser.yy"
                            {
    ctx.unique("reverse-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1213 "d2_parser.cc"
    break;

  case 89: // reverse_ddns: "reverse-ddns" $@22 ":" "{" ddns_mgr_params "}"
#line 438 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1222 "d2_parser.cc"
    break;

  case 94: // not_empty_ddns_mgr_params: ddns_mgr_params ","
#line 449 "d2_parser.yy"
                                                 {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 1230 "d2_parser.cc"
    break;

  case 97: // $@23: %empty
#line 460 "d2_parser.yy"
                           {
    ctx.unique("ddns-domains", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1242 "d2_parser.cc"
    break;

  case 98: // ddns_domains: "ddns-domains" $@23 ":" "[" ddns_domain_list "]"
#line 466 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1251 "d2_parser.cc"
    break;

  case 99: // $@24: %empty
#line 471 "d2_parser.yy"
                                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1260 "d2_parser.cc"
    break;

  case 100: // sub_ddns_domains: "[" $@24 ddns_domain_list "]"
#line 474 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1268 "d2_parser.cc"
    break;

  case 105: // not_empty_ddns_domain_list: not_empty_ddns_domain_list ","
#line 484 "d2_parser.yy"
                                                           {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1276 "d2_parser.cc"
    break;

  case 106: // $@25: %empty
#line 489 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1286 "d2_parser.cc"
    break;

  case 107: // ddns_domain: "{" $@25 ddns_domain_params "}"
#line 493 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1294 "d2_parser.cc"
    break;

  case 108: // $@26: %empty
#line 497 "d2_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1303 "d2_parser.cc"
    break;

  case 109: // sub_ddns_domain: "{" $@26 ddns_domain_params "}"
#line 500 "d2_parser.yy"
                                    {
    // parsing completed
}
#line 1311 "d2_parser.cc"
    break;

  case 112: // ddns_domain_params: ddns_domain_params ","
#line 506 "d2_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 1319 "d2_parser.cc"
    break;

  case 119: // $@27: %empty
#line 520 "d2_parser.yy"
                       {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1328 "d2_parser.cc"
    break;

  case 120: // ddns_domain_name: "name" $@27 ":" "constant string"
#line 523 "d2_parser.yy"
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

  case 121: // $@28: %empty
#line 533 "d2_parser.yy"
                        {
    ctx.unique("key-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1351 "d2_parser.cc"
    break;

  case 122: // ddns_key_name: "key-name" $@28 ":" "constant string"
#line 536 "d2_parser.yy"
               {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1362 "d2_parser.cc"
    break;

  case 123: // $@29: %empty
#line 546 "d2_parser.yy"
                         {
    ctx.unique("dns-servers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1374 "d2_parser.cc"
    break;

  case 124: // dns_servers: "dns-servers" $@29 ":" "[" dns_server_list "]"
#line 552 "d2_parser.yy"
                                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1383 "d2_parser.cc"
    break;

  case 125: // $@30: %empty
#line 557 "d2_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1392 "d2_parser.cc"
    break;

  case 126: // sub_dns_servers: "[" $@30 dns_server_list "]"
#line 560 "d2_parser.yy"
                                  {
    // parsing completed
}
#line 1400 "d2_parser.cc"
    break;

  case 129: // dns_server_list: dns_server_list ","
#line 566 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1408 "d2_parser.cc"
    break;

  case 130: // $@31: %empty
#line 571 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1418 "d2_parser.cc"
    break;

  case 131: // dns_server: "{" $@31 dns_server_params "}"
#line 575 "d2_parser.yy"
                                   {
    ctx.stack_.pop_back();
}
#line 1426 "d2_parser.cc"
    break;

  case 132: // $@32: %empty
#line 579 "d2_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1435 "d2_parser.cc"
    break;

  case 133: // sub_dns_server: "{" $@32 dns_server_params "}"
#line 582 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1443 "d2_parser.cc"
    break;

  case 136: // dns_server_params: dns_server_params ","
#line 588 "d2_parser.yy"
                                         {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1451 "d2_parser.cc"
    break;

  case 144: // $@33: %empty
#line 602 "d2_parser.yy"
                              {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1460 "d2_parser.cc"
    break;

  case 145: // dns_server_hostname: "hostname" $@33 ":" "constant string"
#line 605 "d2_parser.yy"
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

  case 146: // $@34: %empty
#line 615 "d2_parser.yy"
                                  {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1483 "d2_parser.cc"
    break;

  case 147: // dns_server_ip_address: "ip-address" $@34 ":" "constant string"
#line 618 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1493 "d2_parser.cc"
    break;

  case 148: // dns_server_port: "port" ":" "integer"
#line 624 "d2_parser.yy"
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

  case 149: // $@35: %empty
#line 639 "d2_parser.yy"
                     {
    ctx.unique("tsig-keys", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1518 "d2_parser.cc"
    break;

  case 150: // tsig_keys: "tsig-keys" $@35 ":" "[" tsig_keys_list "]"
#line 645 "d2_parser.yy"
                                                       {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1527 "d2_parser.cc"
    break;

  case 151: // $@36: %empty
#line 650 "d2_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1536 "d2_parser.cc"
    break;

  case 152: // sub_tsig_keys: "[" $@36 tsig_keys_list "]"
#line 653 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1544 "d2_parser.cc"
    break;

  case 157: // not_empty_tsig_keys_list: not_empty_tsig_keys_list ","
#line 663 "d2_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1552 "d2_parser.cc"
    break;

  case 158: // $@37: %empty
#line 668 "d2_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1562 "d2_parser.cc"
    break;

  case 159: // tsig_key: "{" $@37 tsig_key_params "}"
#line 672 "d2_parser.yy"
                                 {
    ctx.stack_.pop_back();
}
#line 1570 "d2_parser.cc"
    break;

  case 160: // $@38: %empty
#line 676 "d2_parser.yy"
                             {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1580 "d2_parser.cc"
    break;

  case 161: // sub_tsig_key: "{" $@38 tsig_key_params "}"
#line 680 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1588 "d2_parser.cc"
    break;

  case 164: // tsig_key_params: tsig_key_params ","
#line 687 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1596 "d2_parser.cc"
    break;

  case 173: // $@39: %empty
#line 702 "d2_parser.yy"
                    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1605 "d2_parser.cc"
    break;

  case 174: // tsig_key_name: "name" $@39 ":" "constant string"
#line 705 "d2_parser.yy"
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

  case 175: // $@40: %empty
#line 715 "d2_parser.yy"
                              {
    ctx.unique("algorithm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1628 "d2_parser.cc"
    break;

  case 176: // tsig_key_algorithm: "algorithm" $@40 ":" "constant string"
#line 718 "d2_parser.yy"
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

  case 177: // tsig_key_digest_bits: "digest-bits" ":" "integer"
#line 727 "d2_parser.yy"
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

  case 178: // $@41: %empty
#line 736 "d2_parser.yy"
                        {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.unique("secret-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "d2_parser.cc"
    break;

  case 179: // tsig_key_secret: "secret" $@41 ":" "constant string"
#line 740 "d2_parser.yy"
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

  case 180: // $@42: %empty
#line 749 "d2_parser.yy"
                                  {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.unique("secret-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1687 "d2_parser.cc"
    break;

  case 181: // tsig_key_secret_file: "secret-file" $@42 ":" "constant string"
#line 753 "d2_parser.yy"
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

  case 182: // $@43: %empty
#line 767 "d2_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1713 "d2_parser.cc"
    break;

  case 183: // control_socket: "control-socket" $@43 ":" "{" control_socket_params "}"
#line 774 "d2_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1722 "d2_parser.cc"
    break;

  case 184: // $@44: %empty
#line 779 "d2_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1735 "d2_parser.cc"
    break;

  case 185: // control_sockets: "control-sockets" $@44 ":" "[" control_socket_list "]"
#line 786 "d2_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1744 "d2_parser.cc"
    break;

  case 190: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 797 "d2_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 1752 "d2_parser.cc"
    break;

  case 191: // $@45: %empty
#line 802 "d2_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1762 "d2_parser.cc"
    break;

  case 192: // control_socket_entry: "{" $@45 control_socket_params "}"
#line 806 "d2_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 1770 "d2_parser.cc"
    break;

  case 195: // control_socket_params: control_socket_params ","
#line 812 "d2_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1778 "d2_parser.cc"
    break;

  case 208: // $@46: %empty
#line 831 "d2_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 1787 "d2_parser.cc"
    break;

  case 209: // control_socket_type: "socket-type" $@46 ":" control_socket_type_value
#line 834 "d2_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1796 "d2_parser.cc"
    break;

  case 210: // control_socket_type_value: "unix"
#line 840 "d2_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1802 "d2_parser.cc"
    break;

  case 211: // control_socket_type_value: "http"
#line 841 "d2_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1808 "d2_parser.cc"
    break;

  case 212: // control_socket_type_value: "https"
#line 842 "d2_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 1814 "d2_parser.cc"
    break;

  case 213: // $@47: %empty
#line 845 "d2_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1824 "d2_parser.cc"
    break;

  case 214: // control_socket_name: "socket-name" $@47 ":" "constant string"
#line 849 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1834 "d2_parser.cc"
    break;

  case 215: // $@48: %empty
#line 855 "d2_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1844 "d2_parser.cc"
    break;

  case 216: // control_socket_address: "socket-address" $@48 ":" "constant string"
#line 859 "d2_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 1854 "d2_parser.cc"
    break;

  case 217: // control_socket_port: "socket-port" ":" "integer"
#line 865 "d2_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 1864 "d2_parser.cc"
    break;

  case 218: // $@49: %empty
#line 871 "d2_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "d2_parser.cc"
    break;

  case 219: // trust_anchor: "trust-anchor" $@49 ":" "constant string"
#line 874 "d2_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 1883 "d2_parser.cc"
    break;

  case 220: // $@50: %empty
#line 880 "d2_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "d2_parser.cc"
    break;

  case 221: // cert_file: "cert-file" $@50 ":" "constant string"
#line 883 "d2_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 1902 "d2_parser.cc"
    break;

  case 222: // $@51: %empty
#line 889 "d2_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1911 "d2_parser.cc"
    break;

  case 223: // key_file: "key-file" $@51 ":" "constant string"
#line 892 "d2_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 1921 "d2_parser.cc"
    break;

  case 224: // cert_required: "cert-required" ":" "boolean"
#line 898 "d2_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 1931 "d2_parser.cc"
    break;

  case 225: // $@52: %empty
#line 906 "d2_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 1943 "d2_parser.cc"
    break;

  case 226: // authentication: "authentication" $@52 ":" "{" auth_params "}"
#line 912 "d2_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1954 "d2_parser.cc"
    break;

  case 229: // auth_params: auth_params ","
#line 921 "d2_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 1962 "d2_parser.cc"
    break;

  case 237: // $@53: %empty
#line 935 "d2_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 1971 "d2_parser.cc"
    break;

  case 238: // auth_type: "type" $@53 ":" auth_type_value
#line 938 "d2_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1980 "d2_parser.cc"
    break;

  case 239: // auth_type_value: "basic"
#line 943 "d2_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 1986 "d2_parser.cc"
    break;

  case 240: // $@54: %empty
#line 946 "d2_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "d2_parser.cc"
    break;

  case 241: // realm: "realm" $@54 ":" "constant string"
#line 949 "d2_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 2005 "d2_parser.cc"
    break;

  case 242: // $@55: %empty
#line 955 "d2_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2014 "d2_parser.cc"
    break;

  case 243: // directory: "directory" $@55 ":" "constant string"
#line 958 "d2_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 2024 "d2_parser.cc"
    break;

  case 244: // $@56: %empty
#line 964 "d2_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 2036 "d2_parser.cc"
    break;

  case 245: // clients: "clients" $@56 ":" "[" clients_list "]"
#line 970 "d2_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2045 "d2_parser.cc"
    break;

  case 250: // not_empty_clients_list: not_empty_clients_list ","
#line 981 "d2_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2053 "d2_parser.cc"
    break;

  case 251: // $@57: %empty
#line 986 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2063 "d2_parser.cc"
    break;

  case 252: // basic_auth: "{" $@57 clients_params "}"
#line 990 "d2_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 2071 "d2_parser.cc"
    break;

  case 255: // clients_params: clients_params ","
#line 996 "d2_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2079 "d2_parser.cc"
    break;

  case 263: // $@58: %empty
#line 1010 "d2_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2088 "d2_parser.cc"
    break;

  case 264: // user: "user" $@58 ":" "constant string"
#line 1013 "d2_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2098 "d2_parser.cc"
    break;

  case 265: // $@59: %empty
#line 1019 "d2_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "d2_parser.cc"
    break;

  case 266: // user_file: "user-file" $@59 ":" "constant string"
#line 1022 "d2_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 2117 "d2_parser.cc"
    break;

  case 267: // $@60: %empty
#line 1028 "d2_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2126 "d2_parser.cc"
    break;

  case 268: // password: "password" $@60 ":" "constant string"
#line 1031 "d2_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2136 "d2_parser.cc"
    break;

  case 269: // $@61: %empty
#line 1037 "d2_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2145 "d2_parser.cc"
    break;

  case 270: // password_file: "password-file" $@61 ":" "constant string"
#line 1040 "d2_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2155 "d2_parser.cc"
    break;

  case 271: // $@62: %empty
#line 1048 "d2_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2167 "d2_parser.cc"
    break;

  case 272: // hooks_libraries: "hooks-libraries" $@62 ":" "[" hooks_libraries_list "]"
#line 1054 "d2_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2176 "d2_parser.cc"
    break;

  case 277: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1065 "d2_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2184 "d2_parser.cc"
    break;

  case 278: // $@63: %empty
#line 1070 "d2_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2194 "d2_parser.cc"
    break;

  case 279: // hooks_library: "{" $@63 hooks_params "}"
#line 1074 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2204 "d2_parser.cc"
    break;

  case 280: // $@64: %empty
#line 1080 "d2_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2214 "d2_parser.cc"
    break;

  case 281: // sub_hooks_library: "{" $@64 hooks_params "}"
#line 1084 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2224 "d2_parser.cc"
    break;

  case 284: // hooks_params: hooks_params ","
#line 1092 "d2_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2232 "d2_parser.cc"
    break;

  case 288: // $@65: %empty
#line 1102 "d2_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "d2_parser.cc"
    break;

  case 289: // library: "library" $@65 ":" "constant string"
#line 1105 "d2_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2251 "d2_parser.cc"
    break;

  case 290: // $@66: %empty
#line 1111 "d2_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2260 "d2_parser.cc"
    break;

  case 291: // parameters: "parameters" $@66 ":" map_value
#line 1114 "d2_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2269 "d2_parser.cc"
    break;

  case 292: // $@67: %empty
#line 1121 "d2_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2281 "d2_parser.cc"
    break;

  case 293: // loggers: "loggers" $@67 ":" "[" loggers_entries "]"
#line 1127 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2290 "d2_parser.cc"
    break;

  case 296: // loggers_entries: loggers_entries ","
#line 1136 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 2298 "d2_parser.cc"
    break;

  case 297: // $@68: %empty
#line 1142 "d2_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2308 "d2_parser.cc"
    break;

  case 298: // logger_entry: "{" $@68 logger_params "}"
#line 1146 "d2_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 2316 "d2_parser.cc"
    break;

  case 301: // logger_params: logger_params ","
#line 1152 "d2_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 2324 "d2_parser.cc"
    break;

  case 309: // $@69: %empty
#line 1166 "d2_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2333 "d2_parser.cc"
    break;

  case 310: // name: "name" $@69 ":" "constant string"
#line 1169 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2343 "d2_parser.cc"
    break;

  case 311: // debuglevel: "debuglevel" ":" "integer"
#line 1175 "d2_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2353 "d2_parser.cc"
    break;

  case 312: // $@70: %empty
#line 1181 "d2_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2362 "d2_parser.cc"
    break;

  case 313: // severity: "severity" $@70 ":" "constant string"
#line 1184 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2372 "d2_parser.cc"
    break;

  case 314: // $@71: %empty
#line 1190 "d2_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2384 "d2_parser.cc"
    break;

  case 315: // output_options_list: "output-options" $@71 ":" "[" output_options_list_content "]"
#line 1196 "d2_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2393 "d2_parser.cc"
    break;

  case 318: // output_options_list_content: output_options_list_content ","
#line 1203 "d2_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2401 "d2_parser.cc"
    break;

  case 319: // $@72: %empty
#line 1208 "d2_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2411 "d2_parser.cc"
    break;

  case 320: // output_entry: "{" $@72 output_params_list "}"
#line 1212 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 2419 "d2_parser.cc"
    break;

  case 323: // output_params_list: output_params_list ","
#line 1218 "d2_parser.yy"
                                        {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 2427 "d2_parser.cc"
    break;

  case 329: // $@73: %empty
#line 1230 "d2_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2436 "d2_parser.cc"
    break;

  case 330: // output: "output" $@73 ":" "constant string"
#line 1233 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2446 "d2_parser.cc"
    break;

  case 331: // flush: "flush" ":" "boolean"
#line 1239 "d2_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 2456 "d2_parser.cc"
    break;

  case 332: // maxsize: "maxsize" ":" "integer"
#line 1245 "d2_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 2466 "d2_parser.cc"
    break;

  case 333: // maxver: "maxver" ":" "integer"
#line 1251 "d2_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 2476 "d2_parser.cc"
    break;

  case 334: // $@74: %empty
#line 1257 "d2_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2485 "d2_parser.cc"
    break;

  case 335: // pattern: "pattern" $@74 ":" "constant string"
#line 1260 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 2495 "d2_parser.cc"
    break;


#line 2499 "d2_parser.cc"

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


  const short D2Parser::yypact_ninf_ = -215;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short
  D2Parser::yypact_[] =
  {
      99,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,    33,     8,     0,    38,    42,    55,    73,   105,    96,
     107,   125,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,     8,    44,   129,     7,    47,   133,   141,   140,
      24,   142,   -25,  -215,   153,   160,   197,   194,   200,  -215,
      22,  -215,  -215,   201,   202,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,   203,  -215,    39,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,   204,  -215,  -215,  -215,  -215,
    -215,  -215,    43,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
     198,   206,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    65,
    -215,  -215,  -215,  -215,  -215,   207,   214,  -215,  -215,   216,
    -215,  -215,  -215,  -215,  -215,    71,  -215,  -215,  -215,  -215,
    -215,    58,  -215,  -215,  -215,  -215,   115,  -215,  -215,  -215,
    -215,     8,     8,  -215,   132,   217,  -215,  -215,   218,   139,
     144,   220,   221,   223,   224,   225,   226,   227,   228,   229,
     230,   231,  -215,     7,  -215,   232,   158,   234,   235,   236,
      47,  -215,    47,  -215,   133,   237,   238,   239,   141,  -215,
     141,  -215,   140,   240,   166,   242,    24,  -215,    24,   142,
    -215,   243,   244,   -34,  -215,  -215,  -215,   245,   246,   172,
    -215,  -215,    76,   233,   247,   179,   248,   249,   253,   252,
     255,   256,   257,  -215,   189,  -215,   190,   191,   192,  -215,
     116,  -215,   193,   258,   195,  -215,   123,  -215,   196,  -215,
     199,  -215,   130,  -215,   205,   247,  -215,     8,     7,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,   -15,   -15,   133,
      18,   259,   265,   268,  -215,  -215,  -215,  -215,  -215,  -215,
     142,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   174,
    -215,  -215,   175,  -215,  -215,  -215,   176,   270,  -215,  -215,
    -215,   260,  -215,  -215,  -215,  -215,   261,  -215,  -215,  -215,
     177,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,   272,   277,  -215,  -215,   275,   279,  -215,  -215,
      78,  -215,    87,  -215,   280,   -15,  -215,  -215,  -215,   281,
     282,   283,   173,   284,   285,   286,   287,   215,    18,  -215,
      18,  -215,   259,   -25,  -215,   265,    35,   268,  -215,  -215,
     293,  -215,   162,   241,   250,  -215,   292,   251,   254,   262,
    -215,  -215,   178,  -215,   184,  -215,  -215,  -215,   298,  -215,
    -215,  -215,  -215,   185,  -215,  -215,  -215,  -215,  -215,  -215,
     140,  -215,  -215,  -215,  -215,  -215,  -215,    63,  -215,  -215,
    -215,  -215,  -215,   299,   301,   264,   303,    35,  -215,   302,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,   186,  -215,  -215,
    -215,  -215,  -215,   266,   304,  -215,   267,  -215,  -215,   306,
     307,   309,   310,    63,  -215,  -215,   308,  -215,   273,   269,
     271,   312,  -215,  -215,    98,  -215,  -215,  -215,  -215,  -215,
     311,    50,   308,  -215,  -215,   314,   318,  -215,  -215,   319,
     320,   321,  -215,   187,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,    80,  -215,   311,   322,   274,   278,   288,   323,    50,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   188,  -215,
    -215,  -215,  -215,  -215,  -215,   276,  -215,  -215,  -215,   290,
    -215,   326,   327,   329,   330,    80,  -215,  -215,  -215,   291,
     294,   295,   296,  -215,  -215,  -215,  -215,  -215
  };

  const short
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    38,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    46,     5,    52,     7,   160,     9,
     151,    11,   108,    13,    99,    15,   132,    17,   125,    19,
     280,    21,    40,    33,     0,     0,     0,   153,     0,   101,
       0,     0,     0,    42,     0,    41,     0,     0,    34,    48,
       0,    50,    72,     0,     0,    76,    80,    82,    84,    86,
      88,   149,   182,   184,   271,   292,     0,    71,     0,    54,
      57,    58,    59,    60,    61,    69,    70,    62,    63,    64,
      65,    66,    67,    68,   175,     0,   178,   180,   173,   172,
     170,   171,     0,   162,   165,   166,   167,   168,   169,   158,
       0,   154,   155,   121,   123,   119,   118,   116,   117,     0,
     110,   113,   114,   115,   106,     0,   102,   103,   146,     0,
     144,   143,   141,   142,   140,     0,   134,   137,   138,   139,
     130,     0,   127,   288,   290,   285,     0,   282,   286,   287,
      39,    44,     0,    31,    37,     0,    51,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,    56,    53,     0,     0,     0,     0,     0,
     164,   161,     0,   152,   157,     0,     0,     0,   112,   109,
       0,   100,   105,     0,     0,     0,   136,   133,     0,   129,
     126,     0,     0,   284,   281,    43,    35,     0,     0,     0,
      74,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,     0,   177,     0,     0,     0,   163,
       0,   156,     0,     0,     0,   111,     0,   104,     0,   148,
       0,   135,     0,   128,     0,     0,   283,     0,     0,    73,
      78,    79,    77,    81,    32,    83,    85,    90,    90,   153,
       0,   186,   273,     0,   176,   179,   181,   174,   159,   122,
       0,   120,   107,   147,   145,   131,   289,   291,    36,     0,
      97,    96,     0,    91,    92,    95,     0,     0,   208,   213,
     215,     0,   225,   218,   220,   222,     0,   207,   205,   206,
       0,   193,   196,   197,   198,   199,   201,   202,   203,   204,
     200,   191,     0,   187,   188,   278,     0,   274,   275,   297,
       0,   294,     0,    49,     0,    94,    87,    89,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   195,   183,
       0,   185,   190,     0,   272,   277,     0,   296,   293,   124,
       0,    93,     0,     0,     0,   217,     0,     0,     0,     0,
     224,   194,     0,   189,     0,   276,   309,   314,     0,   312,
     308,   306,   307,     0,   299,   302,   304,   305,   303,   295,
     101,   210,   211,   212,   209,   214,   216,     0,   219,   221,
     223,   192,   279,     0,     0,     0,     0,   301,   298,     0,
     237,   240,   242,   244,   236,   235,   234,     0,   227,   230,
     231,   232,   233,     0,     0,   311,     0,   300,    98,     0,
       0,     0,     0,   229,   226,   310,     0,   313,     0,     0,
       0,     0,   228,   319,     0,   316,   239,   238,   241,   243,
     246,     0,   318,   315,   251,     0,   247,   248,   329,     0,
       0,     0,   334,     0,   321,   324,   325,   326,   327,   328,
     317,     0,   245,   250,     0,     0,     0,     0,     0,   323,
     320,   263,   265,   267,   269,   262,   260,   261,     0,   253,
     256,   257,   258,   259,   249,     0,   331,   332,   333,     0,
     322,     0,     0,     0,     0,   255,   252,   330,   335,     0,
       0,     0,     0,   254,   264,   266,   268,   270
  };

  const short
  D2Parser::yypgoto_[] =
  {
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,   -41,  -215,  -214,  -215,    67,  -215,  -215,  -215,
    -215,  -215,  -215,   -56,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,    77,   154,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,   -55,  -215,   -44,  -215,  -215,  -215,  -215,  -215,
      68,  -215,     3,  -215,  -215,  -215,  -215,   -42,  -215,   137,
    -215,  -215,  -215,   146,   152,  -215,  -215,   -51,  -215,  -215,
    -215,  -215,  -215,    79,   147,  -215,  -215,  -215,   150,   155,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    91,
    -215,   168,  -215,  -215,  -215,   183,   180,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,    12,  -215,    15,    23,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,   -67,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,   -97,  -215,  -215,  -126,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,    25,  -215,  -215,  -215,    28,   169,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,    26,  -215,  -215,   -23,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,   -66,  -215,  -215,
     -94,  -215,  -215,  -215,  -215,  -215,  -215,  -215
  };

  const short
  D2Parser::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    30,    31,    32,    53,   265,    67,    68,    33,
      52,    64,    65,    87,    35,    54,    70,   165,    71,    37,
      55,    88,    89,    90,   168,    91,    92,    93,   171,   262,
      94,   172,    95,   173,    96,   174,    97,   175,    98,   176,
     292,   293,   294,   295,   334,    45,    59,   135,   136,   137,
     200,    43,    58,   129,   130,   131,   197,   132,   195,   133,
     196,    49,    61,   151,   152,   208,    47,    60,   145,   146,
     147,   205,   148,   203,   149,    99,   177,    41,    57,   120,
     121,   122,   192,    39,    56,   112,   113,   114,   189,   115,
     185,   116,   117,   187,   118,   188,   100,   178,   101,   179,
     322,   323,   324,   350,   310,   311,   312,   339,   394,   313,
     340,   314,   341,   315,   316,   344,   317,   345,   318,   346,
     319,   320,   343,   417,   418,   419,   429,   447,   420,   430,
     421,   431,   422,   432,   455,   456,   457,   471,   488,   489,
     490,   501,   491,   502,   492,   503,   493,   504,   102,   180,
     326,   327,   328,   353,    51,    62,   156,   157,   158,   211,
     159,   212,   103,   181,   330,   331,   356,   383,   384,   385,
     403,   386,   387,   406,   388,   404,   444,   445,   451,   463,
     464,   465,   474,   466,   467,   468,   469,   478
  };

  const short
  D2Parser::yytable_[] =
  {
     109,   110,   126,   127,   141,   142,   155,    34,   290,   144,
     264,    63,   111,    23,   128,    24,   143,    25,    72,    73,
      74,    75,   153,   154,    76,   166,    77,    78,    79,    80,
     167,   153,   154,    22,    81,   138,   139,    77,    78,    82,
      83,   264,   183,    77,    78,    36,   190,   184,   123,    38,
     140,   191,   298,    86,    77,    78,   299,   300,   301,   302,
      40,   209,    84,    86,   210,    85,    77,    78,   198,   303,
     304,   305,   306,   199,   206,   104,   105,   106,   107,   207,
      42,   357,    77,    78,   358,    86,    26,    27,    28,    29,
     209,   260,   261,   359,   376,   377,    86,   378,   379,    77,
      78,   452,    86,    46,   453,   410,   108,   411,   412,   413,
      44,   458,    48,    86,   459,   460,   461,   462,   213,   190,
     215,   216,    66,   214,   278,    86,   198,   481,   482,   483,
     484,   282,    50,   206,   109,   110,   109,   110,   285,    69,
     119,    86,   126,   127,   126,   127,   111,   134,   111,   150,
     141,   142,   141,   142,   128,   144,   128,   144,    86,   160,
      77,    78,   143,   161,   143,   123,   124,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,   183,   335,   335,
     348,   348,   333,   336,   337,   349,   401,   213,   407,   433,
     479,   505,   402,   408,   434,   480,   506,   391,   392,   393,
     125,   162,   163,   164,   193,   169,   170,   182,   186,   194,
     217,   291,   291,   201,   307,   308,   288,   202,   220,    86,
     204,   218,   219,   221,   222,   223,   309,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   234,   235,   236,   237,
     238,   242,   243,   244,   248,   249,   250,   254,   255,   257,
     259,   263,   365,   258,    24,   267,   268,   266,   269,   270,
     271,   272,   273,   280,   342,   347,   321,   274,   275,   276,
     277,   279,   325,   281,   283,   329,   338,   284,   351,   291,
     352,   354,   355,   286,   360,   362,   363,   364,   366,   367,
     368,   369,   307,   308,   307,   308,   370,   155,   390,   397,
     380,   381,   405,   423,   309,   424,   309,   426,   428,   436,
     438,   439,   382,   440,   441,   443,   446,   450,   454,   395,
     472,   473,   287,   475,   476,   477,   495,   499,   396,   398,
     509,   510,   399,   511,   512,   289,   296,   233,   361,   247,
     400,   414,   415,   425,   435,   437,   246,   448,   409,   449,
     245,   380,   381,   416,   507,   496,   253,   497,   252,   332,
     297,   251,   241,   382,   373,   372,   442,   498,   508,   514,
     239,   371,   515,   516,   517,   240,   494,   414,   415,   513,
     375,   374,   256,   389,   427,   500,   470,     0,     0,   416,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   485,   486,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   487,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   485,
     486,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   487
  };

  const short
  D2Parser::yycheck_[] =
  {
      56,    56,    58,    58,    60,    60,    62,     7,    23,    60,
     224,    52,    56,     5,    58,     7,    60,     9,    11,    12,
      13,    14,    56,    57,    17,     3,    19,    20,    21,    22,
       8,    56,    57,     0,    27,    11,    12,    19,    20,    32,
      33,   255,     3,    19,    20,     7,     3,     8,    24,     7,
      26,     8,    34,    78,    19,    20,    38,    39,    40,    41,
       5,     3,    55,    78,     6,    58,    19,    20,     3,    51,
      52,    53,    54,     8,     3,    28,    29,    30,    31,     8,
       7,     3,    19,    20,     6,    78,    78,    79,    80,    81,
       3,    15,    16,     6,    59,    60,    78,    62,    63,    19,
      20,     3,    78,     7,     6,    42,    59,    44,    45,    46,
       5,    61,     5,    78,    64,    65,    66,    67,     3,     3,
     161,   162,    78,     8,     8,    78,     3,    47,    48,    49,
      50,     8,     7,     3,   190,   190,   192,   192,     8,    10,
       7,    78,   198,   198,   200,   200,   190,     7,   192,     7,
     206,   206,   208,   208,   198,   206,   200,   208,    78,     6,
      19,    20,   206,     3,   208,    24,    25,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,     3,     3,     3,
       3,     3,     8,     8,     8,     8,     8,     3,     3,     3,
       3,     3,     8,     8,     8,     8,     8,    35,    36,    37,
      59,     4,     8,     3,     6,     4,     4,     4,     4,     3,
      78,   267,   268,     6,   270,   270,   257,     3,    79,    78,
       4,     4,     4,    79,     4,     4,   270,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,    79,     4,     4,
       4,     4,     4,     4,     4,    79,     4,     4,     4,     4,
      78,    18,    79,     7,     7,     7,     7,    78,     5,     7,
       5,     5,     5,     5,     4,     4,     7,    78,    78,    78,
      78,    78,     7,    78,    78,     7,     6,    78,     6,   335,
       3,     6,     3,    78,     4,     4,     4,     4,     4,     4,
       4,     4,   348,   348,   350,   350,    81,   353,     5,     7,
     356,   356,     4,     4,   348,     4,   350,     4,     6,     5,
       4,     4,   356,     4,     4,     7,    43,     5,     7,    78,
       6,     3,   255,     4,     4,     4,     4,     4,    78,    78,
       4,     4,    78,     4,     4,   258,   268,   183,   335,   202,
      78,   397,   397,    79,    78,    78,   200,    78,   390,    78,
     198,   407,   407,   397,    78,    81,   209,    79,   208,   280,
     269,   206,   194,   407,   352,   350,   433,    79,    78,    78,
     190,   348,    78,    78,    78,   192,   473,   433,   433,   505,
     355,   353,   213,   357,   407,   479,   452,    -1,    -1,   433,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   471,   471,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   471,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   505,
     505,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   505
  };

  const short
  D2Parser::yystos_[] =
  {
       0,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,     0,     5,     7,     9,    78,    79,    80,    81,
      94,    95,    96,   101,     7,   106,     7,   111,     7,   175,
       5,   169,     7,   143,     5,   137,     7,   158,     5,   153,
       7,   246,   102,    97,   107,   112,   176,   170,   144,   138,
     159,   154,   247,    94,   103,   104,    78,    99,   100,    10,
     108,   110,    11,    12,    13,    14,    17,    19,    20,    21,
      22,    27,    32,    33,    55,    58,    78,   105,   113,   114,
     115,   117,   118,   119,   122,   124,   126,   128,   130,   167,
     188,   190,   240,   254,    28,    29,    30,    31,    59,   105,
     124,   126,   177,   178,   179,   181,   183,   184,   186,     7,
     171,   172,   173,    24,    25,    59,   105,   124,   126,   145,
     146,   147,   149,   151,     7,   139,   140,   141,    11,    12,
      26,   105,   124,   126,   149,   160,   161,   162,   164,   166,
       7,   155,   156,    56,    57,   105,   248,   249,   250,   252,
       6,     3,     4,     8,     3,   109,     3,     8,   116,     4,
       4,   120,   123,   125,   127,   129,   131,   168,   189,   191,
     241,   255,     4,     3,     8,   182,     4,   185,   187,   180,
       3,     8,   174,     6,     3,   150,   152,   148,     3,     8,
     142,     6,     3,   165,     4,   163,     3,     8,   157,     3,
       6,   251,   253,     3,     8,    94,    94,    78,     4,     4,
      79,    79,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   114,     4,    79,     4,     4,     4,   178,
     177,   173,     4,     4,     4,   146,   145,   141,     4,    79,
       4,   161,   160,   156,     4,     4,   249,     4,     7,    78,
      15,    16,   121,    18,    96,    98,    78,     7,     7,     5,
       7,     5,     5,     5,    78,    78,    78,    78,     8,    78,
       5,    78,     8,    78,    78,     8,    78,    98,    94,   113,
      23,   105,   132,   133,   134,   135,   132,   171,    34,    38,
      39,    40,    41,    51,    52,    53,    54,   105,   124,   126,
     196,   197,   198,   201,   203,   205,   206,   208,   210,   212,
     213,     7,   192,   193,   194,     7,   242,   243,   244,     7,
     256,   257,   155,     8,   136,     3,     8,     8,     6,   199,
     202,   204,     4,   214,   207,   209,   211,     4,     3,     8,
     195,     6,     3,   245,     6,     3,   258,     3,     6,     6,
       4,   134,     4,     4,     4,    79,     4,     4,     4,     4,
      81,   197,   196,   194,   248,   244,    59,    60,    62,    63,
     105,   124,   126,   259,   260,   261,   263,   264,   266,   257,
       5,    35,    36,    37,   200,    78,    78,     7,    78,    78,
      78,     8,     8,   262,   267,     4,   265,     3,     8,   139,
      42,    44,    45,    46,   105,   124,   126,   215,   216,   217,
     220,   222,   224,     4,     4,    79,     4,   260,     6,   218,
     221,   223,   225,     3,     8,    78,     5,    78,     4,     4,
       4,     4,   216,     7,   268,   269,    43,   219,    78,    78,
       5,   270,     3,     6,     7,   226,   227,   228,    61,    64,
      65,    66,    67,   271,   272,   273,   275,   276,   277,   278,
     269,   229,     6,     3,   274,     4,     4,     4,   279,     3,
       8,    47,    48,    49,    50,   105,   124,   126,   230,   231,
     232,   234,   236,   238,   228,     4,    81,    79,    79,     4,
     272,   233,   235,   237,   239,     3,     8,    78,    78,     4,
       4,     4,     4,   231,    78,    78,    78,    78
  };

  const short
  D2Parser::yyr1_[] =
  {
       0,    82,    84,    83,    85,    83,    86,    83,    87,    83,
      88,    83,    89,    83,    90,    83,    91,    83,    92,    83,
      93,    83,    94,    94,    94,    94,    94,    94,    94,    95,
      97,    96,    98,    99,    99,   100,   100,   100,   102,   101,
     103,   103,   104,   104,   104,   105,   107,   106,   109,   108,
     108,   110,   112,   111,   113,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   116,   115,   117,   118,   120,   119,   121,   121,
     123,   122,   125,   124,   127,   126,   129,   128,   131,   130,
     132,   132,   133,   133,   133,   134,   134,   136,   135,   138,
     137,   139,   139,   140,   140,   140,   142,   141,   144,   143,
     145,   145,   145,   146,   146,   146,   146,   146,   146,   148,
     147,   150,   149,   152,   151,   154,   153,   155,   155,   155,
     157,   156,   159,   158,   160,   160,   160,   161,   161,   161,
     161,   161,   161,   161,   163,   162,   165,   164,   166,   168,
     167,   170,   169,   171,   171,   172,   172,   172,   174,   173,
     176,   175,   177,   177,   177,   178,   178,   178,   178,   178,
     178,   178,   178,   180,   179,   182,   181,   183,   185,   184,
     187,   186,   189,   188,   191,   190,   192,   192,   193,   193,
     193,   195,   194,   196,   196,   196,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   199,   198,
     200,   200,   200,   202,   201,   204,   203,   205,   207,   206,
     209,   208,   211,   210,   212,   214,   213,   215,   215,   215,
     216,   216,   216,   216,   216,   216,   216,   218,   217,   219,
     221,   220,   223,   222,   225,   224,   226,   226,   227,   227,
     227,   229,   228,   230,   230,   230,   231,   231,   231,   231,
     231,   231,   231,   233,   232,   235,   234,   237,   236,   239,
     238,   241,   240,   242,   242,   243,   243,   243,   245,   244,
     247,   246,   248,   248,   248,   248,   249,   249,   251,   250,
     253,   252,   255,   254,   256,   256,   256,   258,   257,   259,
     259,   259,   260,   260,   260,   260,   260,   260,   260,   262,
     261,   263,   265,   264,   267,   266,   268,   268,   268,   270,
     269,   271,   271,   271,   272,   272,   272,   272,   272,   274,
     273,   275,   276,   277,   279,   278
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
       1,     1,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     6,
       0,     1,     1,     3,     2,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     0,
       6,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     0,     4,
       0,     4,     0,     6,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     0,     4,     0,     4,     3,     0,     4,
       0,     4,     0,     4,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4
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
  "\"digest-bits\"", "\"secret\"", "\"secret-file\"", "\"control-socket\"",
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
  "tsig_key_secret_file", "$@42", "control_socket", "$@43",
  "control_sockets", "$@44", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@45",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@46", "control_socket_type_value", "control_socket_name", "$@47",
  "control_socket_address", "$@48", "control_socket_port", "trust_anchor",
  "$@49", "cert_file", "$@50", "key_file", "$@51", "cert_required",
  "authentication", "$@52", "auth_params", "auth_param", "auth_type",
  "$@53", "auth_type_value", "realm", "$@54", "directory", "$@55",
  "clients", "$@56", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@57", "clients_params", "clients_param", "user", "$@58",
  "user_file", "$@59", "password", "$@60", "password_file", "$@61",
  "hooks_libraries", "$@62", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@63",
  "sub_hooks_library", "$@64", "hooks_params", "hooks_param", "library",
  "$@65", "parameters", "$@66", "loggers", "$@67", "loggers_entries",
  "logger_entry", "$@68", "logger_params", "logger_param", "name", "$@69",
  "debuglevel", "severity", "$@70", "output_options_list", "$@71",
  "output_options_list_content", "output_entry", "$@72",
  "output_params_list", "output_params", "output", "$@73", "flush",
  "maxsize", "maxver", "pattern", "$@74", YY_NULLPTR
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
     315,   316,   319,   319,   328,   337,   347,   347,   356,   357,
     360,   360,   369,   369,   394,   394,   421,   421,   432,   432,
     443,   444,   447,   448,   449,   454,   455,   460,   460,   471,
     471,   478,   479,   482,   483,   484,   489,   489,   497,   497,
     504,   505,   506,   511,   512,   513,   514,   515,   516,   520,
     520,   533,   533,   546,   546,   557,   557,   564,   565,   566,
     571,   571,   579,   579,   586,   587,   588,   593,   594,   595,
     596,   597,   598,   599,   602,   602,   615,   615,   624,   639,
     639,   650,   650,   657,   658,   661,   662,   663,   668,   668,
     676,   676,   685,   686,   687,   692,   693,   694,   695,   696,
     697,   698,   699,   702,   702,   715,   715,   727,   736,   736,
     749,   749,   767,   767,   779,   779,   791,   792,   795,   796,
     797,   802,   802,   810,   811,   812,   817,   818,   819,   820,
     821,   822,   823,   824,   825,   826,   827,   828,   831,   831,
     840,   841,   842,   845,   845,   855,   855,   865,   871,   871,
     880,   880,   889,   889,   898,   906,   906,   919,   920,   921,
     926,   927,   928,   929,   930,   931,   932,   935,   935,   943,
     946,   946,   955,   955,   964,   964,   975,   976,   979,   980,
     981,   986,   986,   994,   995,   996,  1001,  1002,  1003,  1004,
    1005,  1006,  1007,  1010,  1010,  1019,  1019,  1028,  1028,  1037,
    1037,  1048,  1048,  1059,  1060,  1063,  1064,  1065,  1070,  1070,
    1080,  1080,  1090,  1091,  1092,  1095,  1098,  1099,  1102,  1102,
    1111,  1111,  1121,  1121,  1134,  1135,  1136,  1142,  1142,  1150,
    1151,  1152,  1157,  1158,  1159,  1160,  1161,  1162,  1163,  1166,
    1166,  1175,  1181,  1181,  1190,  1190,  1201,  1202,  1203,  1208,
    1208,  1216,  1217,  1218,  1223,  1224,  1225,  1226,  1227,  1230,
    1230,  1239,  1245,  1251,  1257,  1257
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
#line 3403 "d2_parser.cc"

#line 1266 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
