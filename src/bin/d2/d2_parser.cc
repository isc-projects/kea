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
#define yylex   d2_parser_lex



#include "d2_parser.h"


// Unqualified %code blocks.
#line 34 "d2_parser.yy"

#include <d2/parser_context.h>

#line 52 "d2_parser.cc"


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
#line 145 "d2_parser.cc"

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

  /*---------------.
  | symbol kinds.  |
  `---------------*/



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
#line 116 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 384 "d2_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 116 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 390 "d2_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 116 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 396 "d2_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 116 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 402 "d2_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 116 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 408 "d2_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 116 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "d2_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 116 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 420 "d2_parser.cc"
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
  D2Parser::yypop_ (int n)
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
  D2Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  D2Parser::yy_table_value_is_error_ (int yyvalue)
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
#line 125 "d2_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 695 "d2_parser.cc"
    break;

  case 4: // $@2: %empty
#line 126 "d2_parser.yy"
                         { ctx.ctx_ = ctx.CONFIG; }
#line 701 "d2_parser.cc"
    break;

  case 6: // $@3: %empty
#line 127 "d2_parser.yy"
                    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 707 "d2_parser.cc"
    break;

  case 8: // $@4: %empty
#line 128 "d2_parser.yy"
                    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 713 "d2_parser.cc"
    break;

  case 10: // $@5: %empty
#line 129 "d2_parser.yy"
                     { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 719 "d2_parser.cc"
    break;

  case 12: // $@6: %empty
#line 130 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 725 "d2_parser.cc"
    break;

  case 14: // $@7: %empty
#line 131 "d2_parser.yy"
                        { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 731 "d2_parser.cc"
    break;

  case 16: // $@8: %empty
#line 132 "d2_parser.yy"
                      { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 737 "d2_parser.cc"
    break;

  case 18: // $@9: %empty
#line 133 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 743 "d2_parser.cc"
    break;

  case 20: // $@10: %empty
#line 134 "d2_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 749 "d2_parser.cc"
    break;

  case 22: // value: "integer"
#line 142 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 755 "d2_parser.cc"
    break;

  case 23: // value: "floating point"
#line 143 "d2_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 761 "d2_parser.cc"
    break;

  case 24: // value: "boolean"
#line 144 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 767 "d2_parser.cc"
    break;

  case 25: // value: "constant string"
#line 145 "d2_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 773 "d2_parser.cc"
    break;

  case 26: // value: "null"
#line 146 "d2_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 779 "d2_parser.cc"
    break;

  case 27: // value: map2
#line 147 "d2_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 785 "d2_parser.cc"
    break;

  case 28: // value: list_generic
#line 148 "d2_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 791 "d2_parser.cc"
    break;

  case 29: // sub_json: value
#line 151 "d2_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 800 "d2_parser.cc"
    break;

  case 30: // $@11: %empty
#line 156 "d2_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 811 "d2_parser.cc"
    break;

  case 31: // map2: "{" $@11 map_content "}"
#line 161 "d2_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 821 "d2_parser.cc"
    break;

  case 32: // map_value: map2
#line 167 "d2_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 827 "d2_parser.cc"
    break;

  case 35: // not_empty_map: "constant string" ":" value
#line 174 "d2_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 837 "d2_parser.cc"
    break;

  case 36: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 179 "d2_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 848 "d2_parser.cc"
    break;

  case 37: // $@12: %empty
#line 187 "d2_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 857 "d2_parser.cc"
    break;

  case 38: // list_generic: "[" $@12 list_content "]"
#line 190 "d2_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 865 "d2_parser.cc"
    break;

  case 41: // not_empty_list: value
#line 198 "d2_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 874 "d2_parser.cc"
    break;

  case 42: // not_empty_list: not_empty_list "," value
#line 202 "d2_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 883 "d2_parser.cc"
    break;

  case 43: // unknown_map_entry: "constant string" ":"
#line 213 "d2_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 894 "d2_parser.cc"
    break;

  case 44: // $@13: %empty
#line 222 "d2_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 905 "d2_parser.cc"
    break;

  case 45: // syntax_map: "{" $@13 global_object "}"
#line 227 "d2_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 915 "d2_parser.cc"
    break;

  case 46: // $@14: %empty
#line 235 "d2_parser.yy"
                        {
    ctx.unique("DhcpDdns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 927 "d2_parser.cc"
    break;

  case 47: // global_object: "DhcpDdns" $@14 ":" "{" dhcpddns_params "}"
#line 241 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 936 "d2_parser.cc"
    break;

  case 48: // $@15: %empty
#line 246 "d2_parser.yy"
                             {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 946 "d2_parser.cc"
    break;

  case 49: // sub_dhcpddns: "{" $@15 dhcpddns_params "}"
#line 250 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 954 "d2_parser.cc"
    break;

  case 66: // $@16: %empty
#line 275 "d2_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 963 "d2_parser.cc"
    break;

  case 67: // ip_address: "ip-address" $@16 ":" "constant string"
#line 278 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 973 "d2_parser.cc"
    break;

  case 68: // port: "port" ":" "integer"
#line 284 "d2_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 986 "d2_parser.cc"
    break;

  case 69: // dns_server_timeout: "dns-server-timeout" ":" "integer"
#line 293 "d2_parser.yy"
                                                     {
    ctx.unique("dns-server-timeout", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 1000 "d2_parser.cc"
    break;

  case 70: // $@17: %empty
#line 303 "d2_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 1009 "d2_parser.cc"
    break;

  case 71: // ncr_protocol: "ncr-protocol" $@17 ":" ncr_protocol_value
#line 306 "d2_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1018 "d2_parser.cc"
    break;

  case 72: // ncr_protocol_value: "UDP"
#line 312 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1024 "d2_parser.cc"
    break;

  case 73: // ncr_protocol_value: "TCP"
#line 313 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1030 "d2_parser.cc"
    break;

  case 74: // $@18: %empty
#line 316 "d2_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1039 "d2_parser.cc"
    break;

  case 75: // ncr_format: "ncr-format" $@18 ":" "JSON"
#line 319 "d2_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1049 "d2_parser.cc"
    break;

  case 76: // $@19: %empty
#line 325 "d2_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1057 "d2_parser.cc"
    break;

  case 77: // user_context: "user-context" $@19 ":" map_value
#line 327 "d2_parser.yy"
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
#line 1084 "d2_parser.cc"
    break;

  case 78: // $@20: %empty
#line 350 "d2_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1092 "d2_parser.cc"
    break;

  case 79: // comment: "comment" $@20 ":" "constant string"
#line 352 "d2_parser.yy"
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
#line 1121 "d2_parser.cc"
    break;

  case 80: // $@21: %empty
#line 377 "d2_parser.yy"
                            {
    ctx.unique("forward-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1133 "d2_parser.cc"
    break;

  case 81: // forward_ddns: "forward-ddns" $@21 ":" "{" ddns_mgr_params "}"
#line 383 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1142 "d2_parser.cc"
    break;

  case 82: // $@22: %empty
#line 388 "d2_parser.yy"
                            {
    ctx.unique("reverse-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1154 "d2_parser.cc"
    break;

  case 83: // reverse_ddns: "reverse-ddns" $@22 ":" "{" ddns_mgr_params "}"
#line 394 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1163 "d2_parser.cc"
    break;

  case 90: // $@23: %empty
#line 413 "d2_parser.yy"
                           {
    ctx.unique("ddns-domains", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1175 "d2_parser.cc"
    break;

  case 91: // ddns_domains: "ddns-domains" $@23 ":" "[" ddns_domain_list "]"
#line 419 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1184 "d2_parser.cc"
    break;

  case 92: // $@24: %empty
#line 424 "d2_parser.yy"
                                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1193 "d2_parser.cc"
    break;

  case 93: // sub_ddns_domains: "[" $@24 ddns_domain_list "]"
#line 427 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1201 "d2_parser.cc"
    break;

  case 98: // $@25: %empty
#line 439 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1211 "d2_parser.cc"
    break;

  case 99: // ddns_domain: "{" $@25 ddns_domain_params "}"
#line 443 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1219 "d2_parser.cc"
    break;

  case 100: // $@26: %empty
#line 447 "d2_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1228 "d2_parser.cc"
    break;

  case 101: // sub_ddns_domain: "{" $@26 ddns_domain_params "}"
#line 450 "d2_parser.yy"
                                    {
    // parsing completed
}
#line 1236 "d2_parser.cc"
    break;

  case 110: // $@27: %empty
#line 467 "d2_parser.yy"
                       {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1245 "d2_parser.cc"
    break;

  case 111: // ddns_domain_name: "name" $@27 ":" "constant string"
#line 470 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1259 "d2_parser.cc"
    break;

  case 112: // $@28: %empty
#line 480 "d2_parser.yy"
                               {
    ctx.unique("key-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1268 "d2_parser.cc"
    break;

  case 113: // ddns_domain_key_name: "key-name" $@28 ":" "constant string"
#line 483 "d2_parser.yy"
               {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1279 "d2_parser.cc"
    break;

  case 114: // $@29: %empty
#line 493 "d2_parser.yy"
                         {
    ctx.unique("dns-servers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1291 "d2_parser.cc"
    break;

  case 115: // dns_servers: "dns-servers" $@29 ":" "[" dns_server_list "]"
#line 499 "d2_parser.yy"
                                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1300 "d2_parser.cc"
    break;

  case 116: // $@30: %empty
#line 504 "d2_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1309 "d2_parser.cc"
    break;

  case 117: // sub_dns_servers: "[" $@30 dns_server_list "]"
#line 507 "d2_parser.yy"
                                  {
    // parsing completed
}
#line 1317 "d2_parser.cc"
    break;

  case 120: // $@31: %empty
#line 515 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1327 "d2_parser.cc"
    break;

  case 121: // dns_server: "{" $@31 dns_server_params "}"
#line 519 "d2_parser.yy"
                                   {
    ctx.stack_.pop_back();
}
#line 1335 "d2_parser.cc"
    break;

  case 122: // $@32: %empty
#line 523 "d2_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1344 "d2_parser.cc"
    break;

  case 123: // sub_dns_server: "{" $@32 dns_server_params "}"
#line 526 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1352 "d2_parser.cc"
    break;

  case 132: // $@33: %empty
#line 542 "d2_parser.yy"
                              {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1361 "d2_parser.cc"
    break;

  case 133: // dns_server_hostname: "hostname" $@33 ":" "constant string"
#line 545 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1375 "d2_parser.cc"
    break;

  case 134: // $@34: %empty
#line 555 "d2_parser.yy"
                                  {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1384 "d2_parser.cc"
    break;

  case 135: // dns_server_ip_address: "ip-address" $@34 ":" "constant string"
#line 558 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1394 "d2_parser.cc"
    break;

  case 136: // dns_server_port: "port" ":" "integer"
#line 564 "d2_parser.yy"
                                    {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1407 "d2_parser.cc"
    break;

  case 137: // $@35: %empty
#line 579 "d2_parser.yy"
                     {
    ctx.unique("tsig-keys", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1419 "d2_parser.cc"
    break;

  case 138: // tsig_keys: "tsig-keys" $@35 ":" "[" tsig_keys_list "]"
#line 585 "d2_parser.yy"
                                                       {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1428 "d2_parser.cc"
    break;

  case 139: // $@36: %empty
#line 590 "d2_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1437 "d2_parser.cc"
    break;

  case 140: // sub_tsig_keys: "[" $@36 tsig_keys_list "]"
#line 593 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1445 "d2_parser.cc"
    break;

  case 145: // $@37: %empty
#line 605 "d2_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1455 "d2_parser.cc"
    break;

  case 146: // tsig_key: "{" $@37 tsig_key_params "}"
#line 609 "d2_parser.yy"
                                 {
    ctx.stack_.pop_back();
}
#line 1463 "d2_parser.cc"
    break;

  case 147: // $@38: %empty
#line 613 "d2_parser.yy"
                             {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1473 "d2_parser.cc"
    break;

  case 148: // sub_tsig_key: "{" $@38 tsig_key_params "}"
#line 617 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1481 "d2_parser.cc"
    break;

  case 158: // $@39: %empty
#line 635 "d2_parser.yy"
                    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1490 "d2_parser.cc"
    break;

  case 159: // tsig_key_name: "name" $@39 ":" "constant string"
#line 638 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1504 "d2_parser.cc"
    break;

  case 160: // $@40: %empty
#line 648 "d2_parser.yy"
                              {
    ctx.unique("algorithm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "d2_parser.cc"
    break;

  case 161: // tsig_key_algorithm: "algorithm" $@40 ":" "constant string"
#line 651 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1526 "d2_parser.cc"
    break;

  case 162: // tsig_key_digest_bits: "digest-bits" ":" "integer"
#line 660 "d2_parser.yy"
                                                {
    ctx.unique("digest-bits", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1539 "d2_parser.cc"
    break;

  case 163: // $@41: %empty
#line 669 "d2_parser.yy"
                        {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1548 "d2_parser.cc"
    break;

  case 164: // tsig_key_secret: "secret" $@41 ":" "constant string"
#line 672 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1561 "d2_parser.cc"
    break;

  case 165: // $@42: %empty
#line 686 "d2_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1573 "d2_parser.cc"
    break;

  case 166: // control_socket: "control-socket" $@42 ":" "{" control_socket_params "}"
#line 692 "d2_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1582 "d2_parser.cc"
    break;

  case 174: // $@43: %empty
#line 708 "d2_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1591 "d2_parser.cc"
    break;

  case 175: // control_socket_type: "socket-type" $@43 ":" "constant string"
#line 711 "d2_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 1601 "d2_parser.cc"
    break;

  case 176: // $@44: %empty
#line 717 "d2_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1610 "d2_parser.cc"
    break;

  case 177: // control_socket_name: "socket-name" $@44 ":" "constant string"
#line 720 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1620 "d2_parser.cc"
    break;

  case 178: // $@45: %empty
#line 728 "d2_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1632 "d2_parser.cc"
    break;

  case 179: // hooks_libraries: "hooks-libraries" $@45 ":" "[" hooks_libraries_list "]"
#line 734 "d2_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1641 "d2_parser.cc"
    break;

  case 184: // $@46: %empty
#line 747 "d2_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1651 "d2_parser.cc"
    break;

  case 185: // hooks_library: "{" $@46 hooks_params "}"
#line 751 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1661 "d2_parser.cc"
    break;

  case 186: // $@47: %empty
#line 757 "d2_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1671 "d2_parser.cc"
    break;

  case 187: // sub_hooks_library: "{" $@47 hooks_params "}"
#line 761 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1681 "d2_parser.cc"
    break;

  case 193: // $@48: %empty
#line 776 "d2_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1690 "d2_parser.cc"
    break;

  case 194: // library: "library" $@48 ":" "constant string"
#line 779 "d2_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1700 "d2_parser.cc"
    break;

  case 195: // $@49: %empty
#line 785 "d2_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1709 "d2_parser.cc"
    break;

  case 196: // parameters: "parameters" $@49 ":" map_value
#line 788 "d2_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1718 "d2_parser.cc"
    break;

  case 197: // $@50: %empty
#line 795 "d2_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1730 "d2_parser.cc"
    break;

  case 198: // loggers: "loggers" $@50 ":" "[" loggers_entries "]"
#line 801 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1739 "d2_parser.cc"
    break;

  case 201: // $@51: %empty
#line 813 "d2_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1749 "d2_parser.cc"
    break;

  case 202: // logger_entry: "{" $@51 logger_params "}"
#line 817 "d2_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1757 "d2_parser.cc"
    break;

  case 212: // $@52: %empty
#line 834 "d2_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "d2_parser.cc"
    break;

  case 213: // name: "name" $@52 ":" "constant string"
#line 837 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1776 "d2_parser.cc"
    break;

  case 214: // debuglevel: "debuglevel" ":" "integer"
#line 843 "d2_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1786 "d2_parser.cc"
    break;

  case 215: // $@53: %empty
#line 849 "d2_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1795 "d2_parser.cc"
    break;

  case 216: // severity: "severity" $@53 ":" "constant string"
#line 852 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1805 "d2_parser.cc"
    break;

  case 217: // $@54: %empty
#line 858 "d2_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1817 "d2_parser.cc"
    break;

  case 218: // output_options_list: "output_options" $@54 ":" "[" output_options_list_content "]"
#line 864 "d2_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1826 "d2_parser.cc"
    break;

  case 221: // $@55: %empty
#line 873 "d2_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1836 "d2_parser.cc"
    break;

  case 222: // output_entry: "{" $@55 output_params_list "}"
#line 877 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1844 "d2_parser.cc"
    break;

  case 230: // $@56: %empty
#line 892 "d2_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1853 "d2_parser.cc"
    break;

  case 231: // output: "output" $@56 ":" "constant string"
#line 895 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1863 "d2_parser.cc"
    break;

  case 232: // flush: "flush" ":" "boolean"
#line 901 "d2_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1873 "d2_parser.cc"
    break;

  case 233: // maxsize: "maxsize" ":" "integer"
#line 907 "d2_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1883 "d2_parser.cc"
    break;

  case 234: // maxver: "maxver" ":" "integer"
#line 913 "d2_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1893 "d2_parser.cc"
    break;

  case 235: // $@57: %empty
#line 919 "d2_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1902 "d2_parser.cc"
    break;

  case 236: // pattern: "pattern" $@57 ":" "constant string"
#line 922 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1912 "d2_parser.cc"
    break;


#line 1916 "d2_parser.cc"

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


  const short D2Parser::yypact_ninf_ = -208;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short
  D2Parser::yypact_[] =
  {
      42,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,    45,     8,     0,    41,    49,    67,    55,    80,    95,
     124,   114,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,     8,    65,   120,     7,    23,   125,    50,   131,
      20,   133,    14,  -208,   142,   128,   158,   159,   147,  -208,
     160,  -208,   162,   165,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,   166,  -208,    96,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,   167,  -208,  -208,  -208,  -208,  -208,    97,  -208,
    -208,  -208,  -208,  -208,  -208,   168,   169,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,    98,  -208,  -208,  -208,  -208,  -208,
     170,   172,  -208,  -208,   173,  -208,  -208,  -208,  -208,   100,
    -208,  -208,  -208,  -208,  -208,    27,  -208,  -208,  -208,  -208,
     108,  -208,  -208,  -208,  -208,     8,     8,  -208,   121,   175,
    -208,   176,   115,   123,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,  -208,     7,  -208,   188,   135,   190,
     191,    23,  -208,    23,  -208,   125,   192,   193,   194,    50,
    -208,    50,  -208,   131,   195,   144,   202,    20,  -208,    20,
     133,  -208,   203,   204,    51,  -208,  -208,  -208,   205,   206,
     154,  -208,  -208,    94,   196,   209,   161,   210,   212,   207,
     213,   216,   217,  -208,   171,  -208,   174,   177,  -208,   109,
    -208,   189,   218,   200,  -208,   110,  -208,   201,  -208,   208,
    -208,   116,  -208,   211,   209,  -208,     8,     7,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,     2,     2,   125,   -10,
     219,   220,  -208,  -208,  -208,  -208,  -208,   133,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,   143,  -208,  -208,   146,
    -208,  -208,  -208,   149,   223,  -208,  -208,  -208,  -208,  -208,
     153,  -208,  -208,  -208,  -208,   224,   221,  -208,  -208,    57,
    -208,    73,  -208,   228,     2,  -208,  -208,  -208,   229,   231,
     -10,  -208,    14,  -208,   219,    16,   220,  -208,  -208,   232,
    -208,   215,   222,  -208,   155,  -208,  -208,  -208,   234,  -208,
    -208,  -208,  -208,   156,  -208,  -208,  -208,  -208,  -208,  -208,
     131,  -208,  -208,  -208,   235,   236,   152,   237,    16,  -208,
     230,   225,   238,  -208,   226,  -208,  -208,  -208,   240,  -208,
    -208,   117,  -208,    38,   240,  -208,  -208,   241,   245,   246,
    -208,   157,  -208,  -208,  -208,  -208,  -208,  -208,  -208,   247,
     214,   227,   233,   248,    38,  -208,   239,  -208,  -208,  -208,
     242,  -208,  -208,  -208
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    37,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    44,     5,    48,     7,   147,     9,
     139,    11,   100,    13,    92,    15,   122,    17,   116,    19,
     186,    21,    39,    33,     0,     0,     0,   141,     0,    94,
       0,     0,     0,    41,     0,    40,     0,     0,    34,    46,
       0,    66,     0,     0,    70,    74,    76,    78,    80,    82,
     137,   165,   178,   197,     0,    65,     0,    50,    52,    53,
      54,    55,    56,    63,    64,    57,    58,    59,    60,    61,
      62,   160,     0,   163,   158,   157,   155,   156,     0,   149,
     151,   152,   153,   154,   145,     0,   142,   143,   112,   114,
     110,   109,   107,   108,     0,   102,   104,   105,   106,    98,
       0,    95,    96,   134,     0,   132,   131,   129,   130,     0,
     124,   126,   127,   128,   120,     0,   118,   193,   195,   190,
       0,   188,   191,   192,    38,     0,     0,    31,     0,     0,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    43,     0,    49,     0,     0,     0,
       0,     0,   148,     0,   140,     0,     0,     0,     0,     0,
     101,     0,    93,     0,     0,     0,     0,     0,   123,     0,
       0,   117,     0,     0,     0,   187,    42,    35,     0,     0,
       0,    68,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,   162,     0,     0,   150,     0,
     144,     0,     0,     0,   103,     0,    97,     0,   136,     0,
     125,     0,   119,     0,     0,   189,     0,     0,    67,    72,
      73,    71,    75,    32,    77,    79,    84,    84,   141,     0,
     180,     0,   161,   164,   159,   146,   113,     0,   111,    99,
     135,   133,   121,   194,   196,    36,     0,    90,    89,     0,
      85,    86,    88,     0,     0,   174,   176,   173,   171,   172,
       0,   167,   169,   170,   184,     0,   181,   182,   201,     0,
     199,     0,    47,     0,     0,    81,    83,   138,     0,     0,
       0,   166,     0,   179,     0,     0,     0,   198,   115,     0,
      87,     0,     0,   168,     0,   183,   212,   217,     0,   215,
     211,   209,   210,     0,   203,   205,   207,   208,   206,   200,
      94,   175,   177,   185,     0,     0,     0,     0,     0,   202,
       0,     0,     0,   214,     0,   204,    91,   213,     0,   216,
     221,     0,   219,     0,     0,   218,   230,     0,     0,     0,
     235,     0,   223,   225,   226,   227,   228,   229,   220,     0,
       0,     0,     0,     0,     0,   222,     0,   232,   233,   234,
       0,   224,   231,   236
  };

  const short
  D2Parser::yypgoto_[] =
  {
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,   -41,  -208,  -207,  -208,   -19,  -208,  -208,  -208,
    -208,  -208,  -208,   -56,  -208,  -208,  -208,  -208,  -208,  -208,
      -5,    69,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,   -55,  -208,   -44,  -208,  -208,  -208,  -208,  -208,    -4,
    -208,   -43,  -208,  -208,  -208,  -208,   -78,  -208,    70,  -208,
    -208,  -208,    76,    75,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,     3,    77,  -208,  -208,  -208,    74,    72,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,    17,  -208,
      91,  -208,  -208,  -208,   101,    99,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,   -32,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,   -33,  -208,  -208,  -208,   -26,
      83,  -208,  -208,  -208,  -208,  -208,  -208,  -208,   -28,  -208,
    -208,   -59,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
     -74,  -208,  -208,   -90,  -208,  -208,  -208,  -208,  -208,  -208,
    -208
  };

  const short
  D2Parser::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    30,    31,    32,    53,   254,    67,    68,    33,
      52,    64,    65,    85,    35,    54,    70,   159,    37,    55,
      86,    87,    88,   161,    89,    90,    91,   164,   251,    92,
     165,    93,   166,    94,   167,    95,   168,    96,   169,   279,
     280,   281,   282,   303,    45,    59,   130,   131,   132,   191,
      43,    58,   124,   125,   126,   188,   127,   186,   128,   187,
      49,    61,   145,   146,   199,    47,    60,   139,   140,   141,
     196,   142,   194,   143,    97,   170,    41,    57,   115,   116,
     117,   183,    39,    56,   108,   109,   110,   180,   111,   177,
     112,   113,   179,    98,   171,   290,   291,   292,   308,   293,
     309,    99,   172,   295,   296,   297,   312,    51,    62,   150,
     151,   152,   202,   153,   203,   100,   173,   299,   300,   315,
     333,   334,   335,   344,   336,   337,   347,   338,   345,   361,
     362,   363,   371,   372,   373,   379,   374,   375,   376,   377,
     383
  };

  const short
  D2Parser::yytable_[] =
  {
     105,   106,   121,   122,   136,   137,   149,    34,   253,    76,
      77,    63,   107,    23,   123,    24,   138,    25,    71,    72,
      73,    74,   285,   286,    75,   277,    76,    77,    78,    79,
     200,   133,   134,   201,    80,    76,    77,   253,    81,    76,
      77,    82,    76,    77,    83,    22,   135,    84,    36,   147,
     148,   101,   102,   103,   326,   327,    38,   328,   329,    84,
     316,   104,    42,   317,    84,    26,    27,    28,    29,    76,
      77,    84,    40,    84,   118,   119,   200,    84,   366,   318,
      84,   367,   368,   369,   370,    44,   147,   148,   120,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,   175,
     181,   189,    46,   197,   176,   182,   190,    84,   198,   249,
     250,   204,   181,   189,   206,   207,   205,   265,   269,   197,
     364,    50,    66,   365,   272,   105,   106,   105,   106,    48,
      69,   155,   114,   121,   122,   121,   122,   107,   129,   107,
     144,   136,   137,   136,   137,   123,   175,   123,   154,   304,
     158,   302,   304,   138,   305,   138,   310,   306,   204,   348,
     384,   311,   156,   343,   349,   385,   162,   157,   160,   163,
     174,   178,   185,   211,   184,   193,   192,   195,   208,   209,
     210,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   224,   225,   226,   227,   231,   232,   233,   237,
     278,   278,   238,   287,   288,   275,   239,   243,   244,   246,
     353,   248,   258,   247,   252,   289,    24,   256,   255,   257,
     259,   260,   261,   267,   314,   274,   294,   298,   262,   307,
     313,   263,   319,   321,   264,   322,   356,   340,   346,   351,
     352,   354,   276,   358,   223,   380,   266,   360,   278,   381,
     382,   386,   390,   283,   287,   288,   149,   268,   270,   330,
     331,   320,   350,   236,   234,   271,   289,   235,   273,   240,
     301,   332,   341,   241,   387,   284,   230,   242,   323,   342,
     228,   325,   357,   359,   229,   388,   324,   245,   339,   355,
     378,   389,   330,   331,   391,     0,   392,     0,     0,   393,
       0,     0,     0,     0,   332
  };

  const short
  D2Parser::yycheck_[] =
  {
      56,    56,    58,    58,    60,    60,    62,     7,   215,    19,
      20,    52,    56,     5,    58,     7,    60,     9,    11,    12,
      13,    14,    32,    33,    17,    23,    19,    20,    21,    22,
       3,    11,    12,     6,    27,    19,    20,   244,    31,    19,
      20,    34,    19,    20,    37,     0,    26,    57,     7,    35,
      36,    28,    29,    30,    38,    39,     7,    41,    42,    57,
       3,    38,     7,     6,    57,    57,    58,    59,    60,    19,
      20,    57,     5,    57,    24,    25,     3,    57,    40,     6,
      57,    43,    44,    45,    46,     5,    35,    36,    38,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,     3,
       3,     3,     7,     3,     8,     8,     8,    57,     8,    15,
      16,     3,     3,     3,   155,   156,     8,     8,     8,     3,
       3,     7,    57,     6,     8,   181,   181,   183,   183,     5,
      10,     3,     7,   189,   189,   191,   191,   181,     7,   183,
       7,   197,   197,   199,   199,   189,     3,   191,     6,     3,
       3,     8,     3,   197,     8,   199,     3,     8,     3,     3,
       3,     8,     4,     8,     8,     8,     4,     8,     8,     4,
       4,     4,     3,    58,     6,     3,     6,     4,    57,     4,
       4,    58,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    58,     4,     4,     4,     4,     4,     4,
     256,   257,    58,   259,   259,   246,     4,     4,     4,     4,
      58,    57,     5,     7,    18,   259,     7,     7,    57,     7,
       7,     5,     5,     5,     3,   244,     7,     7,    57,     6,
       6,    57,     4,     4,    57,     4,     6,     5,     4,     4,
       4,     4,   247,     5,   175,     4,    57,     7,   304,     4,
       4,     4,     4,   257,   310,   310,   312,    57,    57,   315,
     315,   304,   340,   193,   189,    57,   310,   191,    57,   197,
     267,   315,    57,   199,    60,   258,   185,   200,   310,    57,
     181,   314,    57,    57,   183,    58,   312,   204,   316,   348,
     364,    58,   348,   348,   384,    -1,    57,    -1,    -1,    57,
      -1,    -1,    -1,    -1,   348
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,     0,     5,     7,     9,    57,    58,    59,    60,
      73,    74,    75,    80,     7,    85,     7,    89,     7,   153,
       5,   147,     7,   121,     5,   115,     7,   136,     5,   131,
       7,   178,    81,    76,    86,    90,   154,   148,   122,   116,
     137,   132,   179,    73,    82,    83,    57,    78,    79,    10,
      87,    11,    12,    13,    14,    17,    19,    20,    21,    22,
      27,    31,    34,    37,    57,    84,    91,    92,    93,    95,
      96,    97,   100,   102,   104,   106,   108,   145,   164,   172,
     186,    28,    29,    30,    38,    84,   102,   104,   155,   156,
     157,   159,   161,   162,     7,   149,   150,   151,    24,    25,
      38,    84,   102,   104,   123,   124,   125,   127,   129,     7,
     117,   118,   119,    11,    12,    26,    84,   102,   104,   138,
     139,   140,   142,   144,     7,   133,   134,    35,    36,    84,
     180,   181,   182,   184,     6,     3,     4,     8,     3,    88,
       8,    94,     4,     4,    98,   101,   103,   105,   107,   109,
     146,   165,   173,   187,     4,     3,     8,   160,     4,   163,
     158,     3,     8,   152,     6,     3,   128,   130,   126,     3,
       8,   120,     6,     3,   143,     4,   141,     3,     8,   135,
       3,     6,   183,   185,     3,     8,    73,    73,    57,     4,
       4,    58,    58,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    92,     4,    58,     4,     4,   156,   155,
     151,     4,     4,     4,   124,   123,   119,     4,    58,     4,
     139,   138,   134,     4,     4,   181,     4,     7,    57,    15,
      16,    99,    18,    75,    77,    57,     7,     7,     5,     7,
       5,     5,    57,    57,    57,     8,    57,     5,    57,     8,
      57,    57,     8,    57,    77,    73,    91,    23,    84,   110,
     111,   112,   113,   110,   149,    32,    33,    84,   102,   104,
     166,   167,   168,   170,     7,   174,   175,   176,     7,   188,
     189,   133,     8,   114,     3,     8,     8,     6,   169,   171,
       3,     8,   177,     6,     3,   190,     3,     6,     6,     4,
     112,     4,     4,   167,   180,   176,    38,    39,    41,    42,
      84,   102,   104,   191,   192,   193,   195,   196,   198,   189,
       5,    57,    57,     8,   194,   199,     4,   197,     3,     8,
     117,     4,     4,    58,     4,   192,     6,    57,     5,    57,
       7,   200,   201,   202,     3,     6,    40,    43,    44,    45,
      46,   203,   204,   205,   207,   208,   209,   210,   201,   206,
       4,     4,     4,   211,     3,     8,     4,    60,    58,    58,
       4,   204,    57,    57
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    61,    63,    62,    64,    62,    65,    62,    66,    62,
      67,    62,    68,    62,    69,    62,    70,    62,    71,    62,
      72,    62,    73,    73,    73,    73,    73,    73,    73,    74,
      76,    75,    77,    78,    78,    79,    79,    81,    80,    82,
      82,    83,    83,    84,    86,    85,    88,    87,    90,    89,
      91,    91,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    94,    93,    95,    96,
      98,    97,    99,    99,   101,   100,   103,   102,   105,   104,
     107,   106,   109,   108,   110,   110,   111,   111,   112,   112,
     114,   113,   116,   115,   117,   117,   118,   118,   120,   119,
     122,   121,   123,   123,   124,   124,   124,   124,   124,   124,
     126,   125,   128,   127,   130,   129,   132,   131,   133,   133,
     135,   134,   137,   136,   138,   138,   139,   139,   139,   139,
     139,   139,   141,   140,   143,   142,   144,   146,   145,   148,
     147,   149,   149,   150,   150,   152,   151,   154,   153,   155,
     155,   156,   156,   156,   156,   156,   156,   156,   158,   157,
     160,   159,   161,   163,   162,   165,   164,   166,   166,   167,
     167,   167,   167,   167,   169,   168,   171,   170,   173,   172,
     174,   174,   175,   175,   177,   176,   179,   178,   180,   180,
     180,   181,   181,   183,   182,   185,   184,   187,   186,   188,
     188,   190,   189,   191,   191,   192,   192,   192,   192,   192,
     192,   192,   194,   193,   195,   197,   196,   199,   198,   200,
     200,   202,   201,   203,   203,   204,   204,   204,   204,   204,
     206,   205,   207,   208,   209,   211,   210
  };

  const signed char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     1,     3,     5,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     6,     0,     1,     1,     3,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
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
  "\"digest-bits\"", "\"secret\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"loggers\"", "\"name\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS", "SUB_TSIG_KEY", "SUB_TSIG_KEYS",
  "SUB_DDNS_DOMAIN", "SUB_DDNS_DOMAINS", "SUB_DNS_SERVER",
  "SUB_DNS_SERVERS", "SUB_HOOKS_LIBRARY", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "value", "sub_json", "map2", "$@11", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@12", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@13",
  "global_object", "$@14", "sub_dhcpddns", "$@15", "dhcpddns_params",
  "dhcpddns_param", "ip_address", "$@16", "port", "dns_server_timeout",
  "ncr_protocol", "$@17", "ncr_protocol_value", "ncr_format", "$@18",
  "user_context", "$@19", "comment", "$@20", "forward_ddns", "$@21",
  "reverse_ddns", "$@22", "ddns_mgr_params", "not_empty_ddns_mgr_params",
  "ddns_mgr_param", "ddns_domains", "$@23", "sub_ddns_domains", "$@24",
  "ddns_domain_list", "not_empty_ddns_domain_list", "ddns_domain", "$@25",
  "sub_ddns_domain", "$@26", "ddns_domain_params", "ddns_domain_param",
  "ddns_domain_name", "$@27", "ddns_domain_key_name", "$@28",
  "dns_servers", "$@29", "sub_dns_servers", "$@30", "dns_server_list",
  "dns_server", "$@31", "sub_dns_server", "$@32", "dns_server_params",
  "dns_server_param", "dns_server_hostname", "$@33",
  "dns_server_ip_address", "$@34", "dns_server_port", "tsig_keys", "$@35",
  "sub_tsig_keys", "$@36", "tsig_keys_list", "not_empty_tsig_keys_list",
  "tsig_key", "$@37", "sub_tsig_key", "$@38", "tsig_key_params",
  "tsig_key_param", "tsig_key_name", "$@39", "tsig_key_algorithm", "$@40",
  "tsig_key_digest_bits", "tsig_key_secret", "$@41", "control_socket",
  "$@42", "control_socket_params", "control_socket_param",
  "control_socket_type", "$@43", "control_socket_name", "$@44",
  "hooks_libraries", "$@45", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@46",
  "sub_hooks_library", "$@47", "hooks_params", "hooks_param", "library",
  "$@48", "parameters", "$@49", "loggers", "$@50", "loggers_entries",
  "logger_entry", "$@51", "logger_params", "logger_param", "name", "$@52",
  "debuglevel", "severity", "$@53", "output_options_list", "$@54",
  "output_options_list_content", "output_entry", "$@55",
  "output_params_list", "output_params", "output", "$@56", "flush",
  "maxsize", "maxver", "pattern", "$@57", YY_NULLPTR
  };
#endif


#if D2_PARSER_DEBUG
  const short
  D2Parser::yyrline_[] =
  {
       0,   125,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   130,   131,   131,   132,   132,   133,   133,
     134,   134,   142,   143,   144,   145,   146,   147,   148,   151,
     156,   156,   167,   170,   171,   174,   179,   187,   187,   194,
     195,   198,   202,   213,   222,   222,   235,   235,   246,   246,
     254,   255,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   275,   275,   284,   293,
     303,   303,   312,   313,   316,   316,   325,   325,   350,   350,
     377,   377,   388,   388,   399,   400,   403,   404,   407,   408,
     413,   413,   424,   424,   431,   432,   435,   436,   439,   439,
     447,   447,   454,   455,   458,   459,   460,   461,   462,   463,
     467,   467,   480,   480,   493,   493,   504,   504,   511,   512,
     515,   515,   523,   523,   530,   531,   534,   535,   536,   537,
     538,   539,   542,   542,   555,   555,   564,   579,   579,   590,
     590,   597,   598,   601,   602,   605,   605,   613,   613,   622,
     623,   626,   627,   628,   629,   630,   631,   632,   635,   635,
     648,   648,   660,   669,   669,   686,   686,   697,   698,   701,
     702,   703,   704,   705,   708,   708,   717,   717,   728,   728,
     739,   740,   743,   744,   747,   747,   757,   757,   767,   768,
     769,   772,   773,   776,   776,   785,   785,   795,   795,   808,
     809,   813,   813,   821,   822,   825,   826,   827,   828,   829,
     830,   831,   834,   834,   843,   849,   849,   858,   858,   869,
     870,   873,   873,   881,   882,   885,   886,   887,   888,   889,
     892,   892,   901,   907,   913,   919,   919
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
#line 2695 "d2_parser.cc"

#line 928 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
