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

  case 37: // not_empty_map: not_empty_map ","
#line 185 "d2_parser.yy"
                                   {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 856 "d2_parser.cc"
    break;

  case 38: // $@12: %empty
#line 190 "d2_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 865 "d2_parser.cc"
    break;

  case 39: // list_generic: "[" $@12 list_content "]"
#line 193 "d2_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 873 "d2_parser.cc"
    break;

  case 42: // not_empty_list: value
#line 201 "d2_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 882 "d2_parser.cc"
    break;

  case 43: // not_empty_list: not_empty_list "," value
#line 205 "d2_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 891 "d2_parser.cc"
    break;

  case 44: // not_empty_list: not_empty_list ","
#line 209 "d2_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 899 "d2_parser.cc"
    break;

  case 45: // unknown_map_entry: "constant string" ":"
#line 219 "d2_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 910 "d2_parser.cc"
    break;

  case 46: // $@13: %empty
#line 228 "d2_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 921 "d2_parser.cc"
    break;

  case 47: // syntax_map: "{" $@13 global_object "}"
#line 233 "d2_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 931 "d2_parser.cc"
    break;

  case 48: // $@14: %empty
#line 241 "d2_parser.yy"
                        {
    ctx.unique("DhcpDdns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 943 "d2_parser.cc"
    break;

  case 49: // global_object: "DhcpDdns" $@14 ":" "{" dhcpddns_params "}"
#line 247 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 952 "d2_parser.cc"
    break;

  case 51: // global_object_comma: global_object ","
#line 254 "d2_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 960 "d2_parser.cc"
    break;

  case 52: // $@15: %empty
#line 258 "d2_parser.yy"
                             {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 970 "d2_parser.cc"
    break;

  case 53: // sub_dhcpddns: "{" $@15 dhcpddns_params "}"
#line 262 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 978 "d2_parser.cc"
    break;

  case 56: // dhcpddns_params: dhcpddns_params ","
#line 268 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 986 "d2_parser.cc"
    break;

  case 71: // $@16: %empty
#line 290 "d2_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 995 "d2_parser.cc"
    break;

  case 72: // ip_address: "ip-address" $@16 ":" "constant string"
#line 293 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1005 "d2_parser.cc"
    break;

  case 73: // port: "port" ":" "integer"
#line 299 "d2_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1018 "d2_parser.cc"
    break;

  case 74: // dns_server_timeout: "dns-server-timeout" ":" "integer"
#line 308 "d2_parser.yy"
                                                     {
    ctx.unique("dns-server-timeout", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 1032 "d2_parser.cc"
    break;

  case 75: // $@17: %empty
#line 318 "d2_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 1041 "d2_parser.cc"
    break;

  case 76: // ncr_protocol: "ncr-protocol" $@17 ":" ncr_protocol_value
#line 321 "d2_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1050 "d2_parser.cc"
    break;

  case 77: // ncr_protocol_value: "UDP"
#line 327 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1056 "d2_parser.cc"
    break;

  case 78: // ncr_protocol_value: "TCP"
#line 328 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1062 "d2_parser.cc"
    break;

  case 79: // $@18: %empty
#line 331 "d2_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1071 "d2_parser.cc"
    break;

  case 80: // ncr_format: "ncr-format" $@18 ":" "JSON"
#line 334 "d2_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1081 "d2_parser.cc"
    break;

  case 81: // $@19: %empty
#line 340 "d2_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1089 "d2_parser.cc"
    break;

  case 82: // user_context: "user-context" $@19 ":" map_value
#line 342 "d2_parser.yy"
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
#line 1116 "d2_parser.cc"
    break;

  case 83: // $@20: %empty
#line 365 "d2_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1124 "d2_parser.cc"
    break;

  case 84: // comment: "comment" $@20 ":" "constant string"
#line 367 "d2_parser.yy"
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
#line 1153 "d2_parser.cc"
    break;

  case 85: // $@21: %empty
#line 392 "d2_parser.yy"
                            {
    ctx.unique("forward-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1165 "d2_parser.cc"
    break;

  case 86: // forward_ddns: "forward-ddns" $@21 ":" "{" ddns_mgr_params "}"
#line 398 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1174 "d2_parser.cc"
    break;

  case 87: // $@22: %empty
#line 403 "d2_parser.yy"
                            {
    ctx.unique("reverse-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1186 "d2_parser.cc"
    break;

  case 88: // reverse_ddns: "reverse-ddns" $@22 ":" "{" ddns_mgr_params "}"
#line 409 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1195 "d2_parser.cc"
    break;

  case 93: // not_empty_ddns_mgr_params: ddns_mgr_params ","
#line 420 "d2_parser.yy"
                                                 {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 1203 "d2_parser.cc"
    break;

  case 96: // $@23: %empty
#line 431 "d2_parser.yy"
                           {
    ctx.unique("ddns-domains", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1215 "d2_parser.cc"
    break;

  case 97: // ddns_domains: "ddns-domains" $@23 ":" "[" ddns_domain_list "]"
#line 437 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1224 "d2_parser.cc"
    break;

  case 98: // $@24: %empty
#line 442 "d2_parser.yy"
                                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1233 "d2_parser.cc"
    break;

  case 99: // sub_ddns_domains: "[" $@24 ddns_domain_list "]"
#line 445 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1241 "d2_parser.cc"
    break;

  case 104: // not_empty_ddns_domain_list: not_empty_ddns_domain_list ","
#line 455 "d2_parser.yy"
                                                           {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1249 "d2_parser.cc"
    break;

  case 105: // $@25: %empty
#line 460 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1259 "d2_parser.cc"
    break;

  case 106: // ddns_domain: "{" $@25 ddns_domain_params "}"
#line 464 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1267 "d2_parser.cc"
    break;

  case 107: // $@26: %empty
#line 468 "d2_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1276 "d2_parser.cc"
    break;

  case 108: // sub_ddns_domain: "{" $@26 ddns_domain_params "}"
#line 471 "d2_parser.yy"
                                    {
    // parsing completed
}
#line 1284 "d2_parser.cc"
    break;

  case 111: // ddns_domain_params: ddns_domain_params ","
#line 477 "d2_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 1292 "d2_parser.cc"
    break;

  case 118: // $@27: %empty
#line 491 "d2_parser.yy"
                       {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1301 "d2_parser.cc"
    break;

  case 119: // ddns_domain_name: "name" $@27 ":" "constant string"
#line 494 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1315 "d2_parser.cc"
    break;

  case 120: // $@28: %empty
#line 504 "d2_parser.yy"
                        {
    ctx.unique("key-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "d2_parser.cc"
    break;

  case 121: // ddns_key_name: "key-name" $@28 ":" "constant string"
#line 507 "d2_parser.yy"
               {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1335 "d2_parser.cc"
    break;

  case 122: // $@29: %empty
#line 517 "d2_parser.yy"
                         {
    ctx.unique("dns-servers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1347 "d2_parser.cc"
    break;

  case 123: // dns_servers: "dns-servers" $@29 ":" "[" dns_server_list "]"
#line 523 "d2_parser.yy"
                                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1356 "d2_parser.cc"
    break;

  case 124: // $@30: %empty
#line 528 "d2_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1365 "d2_parser.cc"
    break;

  case 125: // sub_dns_servers: "[" $@30 dns_server_list "]"
#line 531 "d2_parser.yy"
                                  {
    // parsing completed
}
#line 1373 "d2_parser.cc"
    break;

  case 128: // dns_server_list: dns_server_list ","
#line 537 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1381 "d2_parser.cc"
    break;

  case 129: // $@31: %empty
#line 542 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1391 "d2_parser.cc"
    break;

  case 130: // dns_server: "{" $@31 dns_server_params "}"
#line 546 "d2_parser.yy"
                                   {
    ctx.stack_.pop_back();
}
#line 1399 "d2_parser.cc"
    break;

  case 131: // $@32: %empty
#line 550 "d2_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1408 "d2_parser.cc"
    break;

  case 132: // sub_dns_server: "{" $@32 dns_server_params "}"
#line 553 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1416 "d2_parser.cc"
    break;

  case 135: // dns_server_params: dns_server_params ","
#line 559 "d2_parser.yy"
                                         {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1424 "d2_parser.cc"
    break;

  case 143: // $@33: %empty
#line 573 "d2_parser.yy"
                              {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1433 "d2_parser.cc"
    break;

  case 144: // dns_server_hostname: "hostname" $@33 ":" "constant string"
#line 576 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1447 "d2_parser.cc"
    break;

  case 145: // $@34: %empty
#line 586 "d2_parser.yy"
                                  {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1456 "d2_parser.cc"
    break;

  case 146: // dns_server_ip_address: "ip-address" $@34 ":" "constant string"
#line 589 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1466 "d2_parser.cc"
    break;

  case 147: // dns_server_port: "port" ":" "integer"
#line 595 "d2_parser.yy"
                                    {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1479 "d2_parser.cc"
    break;

  case 148: // $@35: %empty
#line 610 "d2_parser.yy"
                     {
    ctx.unique("tsig-keys", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1491 "d2_parser.cc"
    break;

  case 149: // tsig_keys: "tsig-keys" $@35 ":" "[" tsig_keys_list "]"
#line 616 "d2_parser.yy"
                                                       {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1500 "d2_parser.cc"
    break;

  case 150: // $@36: %empty
#line 621 "d2_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1509 "d2_parser.cc"
    break;

  case 151: // sub_tsig_keys: "[" $@36 tsig_keys_list "]"
#line 624 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1517 "d2_parser.cc"
    break;

  case 156: // not_empty_tsig_keys_list: not_empty_tsig_keys_list ","
#line 634 "d2_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1525 "d2_parser.cc"
    break;

  case 157: // $@37: %empty
#line 639 "d2_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1535 "d2_parser.cc"
    break;

  case 158: // tsig_key: "{" $@37 tsig_key_params "}"
#line 643 "d2_parser.yy"
                                 {
    ctx.stack_.pop_back();
}
#line 1543 "d2_parser.cc"
    break;

  case 159: // $@38: %empty
#line 647 "d2_parser.yy"
                             {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1553 "d2_parser.cc"
    break;

  case 160: // sub_tsig_key: "{" $@38 tsig_key_params "}"
#line 651 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1561 "d2_parser.cc"
    break;

  case 163: // tsig_key_params: tsig_key_params ","
#line 658 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1569 "d2_parser.cc"
    break;

  case 171: // $@39: %empty
#line 672 "d2_parser.yy"
                    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1578 "d2_parser.cc"
    break;

  case 172: // tsig_key_name: "name" $@39 ":" "constant string"
#line 675 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1592 "d2_parser.cc"
    break;

  case 173: // $@40: %empty
#line 685 "d2_parser.yy"
                              {
    ctx.unique("algorithm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1601 "d2_parser.cc"
    break;

  case 174: // tsig_key_algorithm: "algorithm" $@40 ":" "constant string"
#line 688 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1614 "d2_parser.cc"
    break;

  case 175: // tsig_key_digest_bits: "digest-bits" ":" "integer"
#line 697 "d2_parser.yy"
                                                {
    ctx.unique("digest-bits", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1627 "d2_parser.cc"
    break;

  case 176: // $@41: %empty
#line 706 "d2_parser.yy"
                        {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1636 "d2_parser.cc"
    break;

  case 177: // tsig_key_secret: "secret" $@41 ":" "constant string"
#line 709 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1649 "d2_parser.cc"
    break;

  case 178: // $@42: %empty
#line 723 "d2_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1661 "d2_parser.cc"
    break;

  case 179: // control_socket: "control-socket" $@42 ":" "{" control_socket_params "}"
#line 729 "d2_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1670 "d2_parser.cc"
    break;

  case 182: // control_socket_params: control_socket_params ","
#line 736 "d2_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1678 "d2_parser.cc"
    break;

  case 188: // $@43: %empty
#line 748 "d2_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1687 "d2_parser.cc"
    break;

  case 189: // control_socket_type: "socket-type" $@43 ":" "constant string"
#line 751 "d2_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 1697 "d2_parser.cc"
    break;

  case 190: // $@44: %empty
#line 757 "d2_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1706 "d2_parser.cc"
    break;

  case 191: // control_socket_name: "socket-name" $@44 ":" "constant string"
#line 760 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1716 "d2_parser.cc"
    break;

  case 192: // $@45: %empty
#line 768 "d2_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1728 "d2_parser.cc"
    break;

  case 193: // hooks_libraries: "hooks-libraries" $@45 ":" "[" hooks_libraries_list "]"
#line 774 "d2_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "d2_parser.cc"
    break;

  case 198: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 785 "d2_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 1745 "d2_parser.cc"
    break;

  case 199: // $@46: %empty
#line 790 "d2_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1755 "d2_parser.cc"
    break;

  case 200: // hooks_library: "{" $@46 hooks_params "}"
#line 794 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1765 "d2_parser.cc"
    break;

  case 201: // $@47: %empty
#line 800 "d2_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1775 "d2_parser.cc"
    break;

  case 202: // sub_hooks_library: "{" $@47 hooks_params "}"
#line 804 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1785 "d2_parser.cc"
    break;

  case 205: // hooks_params: hooks_params ","
#line 812 "d2_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 1793 "d2_parser.cc"
    break;

  case 209: // $@48: %empty
#line 822 "d2_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1802 "d2_parser.cc"
    break;

  case 210: // library: "library" $@48 ":" "constant string"
#line 825 "d2_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1812 "d2_parser.cc"
    break;

  case 211: // $@49: %empty
#line 831 "d2_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1821 "d2_parser.cc"
    break;

  case 212: // parameters: "parameters" $@49 ":" map_value
#line 834 "d2_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1830 "d2_parser.cc"
    break;

  case 213: // $@50: %empty
#line 841 "d2_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1842 "d2_parser.cc"
    break;

  case 214: // loggers: "loggers" $@50 ":" "[" loggers_entries "]"
#line 847 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1851 "d2_parser.cc"
    break;

  case 217: // loggers_entries: loggers_entries ","
#line 856 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1859 "d2_parser.cc"
    break;

  case 218: // $@51: %empty
#line 862 "d2_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1869 "d2_parser.cc"
    break;

  case 219: // logger_entry: "{" $@51 logger_params "}"
#line 866 "d2_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1877 "d2_parser.cc"
    break;

  case 222: // logger_params: logger_params ","
#line 872 "d2_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1885 "d2_parser.cc"
    break;

  case 230: // $@52: %empty
#line 886 "d2_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1894 "d2_parser.cc"
    break;

  case 231: // name: "name" $@52 ":" "constant string"
#line 889 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1904 "d2_parser.cc"
    break;

  case 232: // debuglevel: "debuglevel" ":" "integer"
#line 895 "d2_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1914 "d2_parser.cc"
    break;

  case 233: // $@53: %empty
#line 901 "d2_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "d2_parser.cc"
    break;

  case 234: // severity: "severity" $@53 ":" "constant string"
#line 904 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1933 "d2_parser.cc"
    break;

  case 235: // $@54: %empty
#line 910 "d2_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1945 "d2_parser.cc"
    break;

  case 236: // output_options_list: "output_options" $@54 ":" "[" output_options_list_content "]"
#line 916 "d2_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1954 "d2_parser.cc"
    break;

  case 239: // output_options_list_content: output_options_list_content ","
#line 923 "d2_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 1962 "d2_parser.cc"
    break;

  case 240: // $@55: %empty
#line 928 "d2_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1972 "d2_parser.cc"
    break;

  case 241: // output_entry: "{" $@55 output_params_list "}"
#line 932 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1980 "d2_parser.cc"
    break;

  case 244: // output_params_list: output_params_list ","
#line 938 "d2_parser.yy"
                                        {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1988 "d2_parser.cc"
    break;

  case 250: // $@56: %empty
#line 950 "d2_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1997 "d2_parser.cc"
    break;

  case 251: // output: "output" $@56 ":" "constant string"
#line 953 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2007 "d2_parser.cc"
    break;

  case 252: // flush: "flush" ":" "boolean"
#line 959 "d2_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 2017 "d2_parser.cc"
    break;

  case 253: // maxsize: "maxsize" ":" "integer"
#line 965 "d2_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 2027 "d2_parser.cc"
    break;

  case 254: // maxver: "maxver" ":" "integer"
#line 971 "d2_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 2037 "d2_parser.cc"
    break;

  case 255: // $@57: %empty
#line 977 "d2_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "d2_parser.cc"
    break;

  case 256: // pattern: "pattern" $@57 ":" "constant string"
#line 980 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 2056 "d2_parser.cc"
    break;


#line 2060 "d2_parser.cc"

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


  const short D2Parser::yypact_ninf_ = -212;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short
  D2Parser::yypact_[] =
  {
      49,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,    10,     8,    24,    30,    42,    48,    64,   128,    74,
     136,   127,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,     8,   -22,    33,     7,    31,   146,    38,   156,
      28,   160,    37,  -212,   137,   163,   166,   164,   168,  -212,
      22,  -212,  -212,   169,   170,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,   171,  -212,    76,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,   172,  -212,  -212,  -212,  -212,  -212,    79,
    -212,  -212,  -212,  -212,  -212,  -212,   173,   174,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,   103,  -212,  -212,  -212,  -212,
    -212,   175,   177,  -212,  -212,   178,  -212,  -212,  -212,  -212,
    -212,   104,  -212,  -212,  -212,  -212,  -212,    77,  -212,  -212,
    -212,  -212,   105,  -212,  -212,  -212,  -212,     8,     8,  -212,
     121,   179,  -212,  -212,   180,   130,   131,   181,   182,   183,
     186,   187,   188,   189,   190,   191,   192,  -212,     7,  -212,
     193,   140,   195,   196,    31,  -212,    31,  -212,   146,   197,
     198,   201,    38,  -212,    38,  -212,   156,   205,   154,   206,
      28,  -212,    28,   160,  -212,   207,   209,   -13,  -212,  -212,
    -212,   210,   208,   162,  -212,  -212,   153,   199,   213,   165,
     214,   216,   211,   217,   220,   221,  -212,   176,  -212,   184,
     185,  -212,   106,  -212,   203,   222,   204,  -212,   107,  -212,
     215,  -212,   218,  -212,   115,  -212,   219,   213,  -212,     8,
       7,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,   -15,
     -15,   146,    13,   223,   224,  -212,  -212,  -212,  -212,  -212,
     160,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,   116,
    -212,  -212,   117,  -212,  -212,  -212,   118,   226,  -212,  -212,
    -212,  -212,  -212,   119,  -212,  -212,  -212,  -212,   228,   225,
    -212,  -212,   129,  -212,   158,  -212,   231,   -15,  -212,  -212,
    -212,   232,   233,    13,  -212,    37,  -212,   223,    36,   224,
    -212,  -212,   234,  -212,   227,   229,  -212,   149,  -212,  -212,
    -212,   236,  -212,  -212,  -212,  -212,   151,  -212,  -212,  -212,
    -212,  -212,  -212,   156,  -212,  -212,  -212,   239,   240,   194,
     241,    36,  -212,   242,   230,   244,  -212,   235,  -212,  -212,
    -212,   243,  -212,  -212,   159,  -212,    46,   243,  -212,  -212,
     249,   250,   251,  -212,   152,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,   252,   237,   212,   245,   260,    46,  -212,   247,
    -212,  -212,  -212,   248,  -212,  -212,  -212
  };

  const short
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    38,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    46,     5,    52,     7,   159,     9,
     150,    11,   107,    13,    98,    15,   131,    17,   124,    19,
     201,    21,    40,    33,     0,     0,     0,   152,     0,   100,
       0,     0,     0,    42,     0,    41,     0,     0,    34,    48,
       0,    50,    71,     0,     0,    75,    79,    81,    83,    85,
      87,   148,   178,   192,   213,     0,    70,     0,    54,    57,
      58,    59,    60,    61,    68,    69,    62,    63,    64,    65,
      66,    67,   173,     0,   176,   171,   170,   168,   169,     0,
     161,   164,   165,   166,   167,   157,     0,   153,   154,   120,
     122,   118,   117,   115,   116,     0,   109,   112,   113,   114,
     105,     0,   101,   102,   145,     0,   143,   142,   140,   141,
     139,     0,   133,   136,   137,   138,   129,     0,   126,   209,
     211,   206,     0,   203,   207,   208,    39,    44,     0,    31,
      37,     0,    51,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    56,    53,
       0,     0,     0,     0,   163,   160,     0,   151,   156,     0,
       0,     0,   111,   108,     0,    99,   104,     0,     0,     0,
     135,   132,     0,   128,   125,     0,     0,   205,   202,    43,
      35,     0,     0,     0,    73,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    55,     0,   175,     0,
       0,   162,     0,   155,     0,     0,     0,   110,     0,   103,
       0,   147,     0,   134,     0,   127,     0,     0,   204,     0,
       0,    72,    77,    78,    76,    80,    32,    82,    84,    89,
      89,   152,     0,   194,     0,   174,   177,   172,   158,   121,
       0,   119,   106,   146,   144,   130,   210,   212,    36,     0,
      96,    95,     0,    90,    91,    94,     0,     0,   188,   190,
     187,   185,   186,     0,   180,   183,   184,   199,     0,   195,
     196,   218,     0,   215,     0,    49,     0,    93,    86,    88,
     149,     0,     0,   182,   179,     0,   193,   198,     0,   217,
     214,   123,     0,    92,     0,     0,   181,     0,   197,   230,
     235,     0,   233,   229,   227,   228,     0,   220,   223,   225,
     226,   224,   216,   100,   189,   191,   200,     0,     0,     0,
       0,   222,   219,     0,     0,     0,   232,     0,   221,    97,
     231,     0,   234,   240,     0,   237,     0,   239,   236,   250,
       0,     0,     0,   255,     0,   242,   245,   246,   247,   248,
     249,   238,     0,     0,     0,     0,     0,   244,   241,     0,
     252,   253,   254,     0,   243,   251,   256
  };

  const short
  D2Parser::yypgoto_[] =
  {
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,   -41,  -212,  -211,  -212,   -18,  -212,  -212,  -212,
    -212,  -212,  -212,   -56,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,   -12,    68,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,   -55,  -212,   -44,  -212,  -212,  -212,  -212,  -212,
       5,  -212,   -60,  -212,  -212,  -212,  -212,   -77,  -212,    71,
    -212,  -212,  -212,    83,    81,  -212,  -212,   -51,  -212,  -212,
    -212,  -212,  -212,    -2,    75,  -212,  -212,  -212,    69,    80,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,    18,
    -212,    93,  -212,  -212,  -212,    96,    99,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,   -28,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,   -29,  -212,  -212,  -212,
     -26,    84,  -212,  -212,  -212,  -212,  -212,  -212,  -212,   -25,
    -212,  -212,   -61,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,   -74,  -212,  -212,   -89,  -212,  -212,  -212,  -212,  -212,
    -212,  -212
  };

  const short
  D2Parser::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    30,    31,    32,    53,   257,    67,    68,    33,
      52,    64,    65,    86,    35,    54,    70,   161,    71,    37,
      55,    87,    88,    89,   164,    90,    91,    92,   167,   254,
      93,   168,    94,   169,    95,   170,    96,   171,    97,   172,
     282,   283,   284,   285,   306,    45,    59,   131,   132,   133,
     194,    43,    58,   125,   126,   127,   191,   128,   189,   129,
     190,    49,    61,   147,   148,   202,    47,    60,   141,   142,
     143,   199,   144,   197,   145,    98,   173,    41,    57,   116,
     117,   118,   186,    39,    56,   109,   110,   111,   183,   112,
     180,   113,   114,   182,    99,   174,   293,   294,   295,   311,
     296,   312,   100,   175,   298,   299,   300,   315,    51,    62,
     152,   153,   154,   205,   155,   206,   101,   176,   302,   303,
     318,   336,   337,   338,   347,   339,   340,   350,   341,   348,
     364,   365,   366,   374,   375,   376,   382,   377,   378,   379,
     380,   386
  };

  const short
  D2Parser::yytable_[] =
  {
     106,   107,   122,   123,   137,   138,   151,   256,   280,   140,
      22,    63,   108,    23,   124,    24,   139,    25,    72,    73,
      74,    75,   149,   150,    76,   162,    77,    78,    79,    80,
     163,    34,    77,    78,    81,    66,   256,    36,    82,   134,
     135,    83,    85,    69,    84,   288,   289,    77,    78,    38,
      77,    78,   119,    40,   136,    77,    78,    77,    78,   102,
     103,   104,   119,   120,    85,    26,    27,    28,    29,   105,
      85,    42,   149,   150,   329,   330,   121,   331,   332,   178,
     203,    46,   184,   204,   179,    85,   369,   185,    85,   370,
     371,   372,   373,    85,    85,    85,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,   192,   200,   207,   184,
     192,   193,   201,   208,   268,   272,   209,   210,   200,   178,
     307,   307,   313,   275,   305,   308,   309,   314,   106,   107,
     106,   107,   319,    44,    50,   320,   122,   123,   122,   123,
     108,    48,   108,   156,   137,   138,   137,   138,   124,   140,
     124,   140,   207,   115,   351,   387,   139,   346,   139,   352,
     388,   203,   367,   130,   321,   368,   157,   146,   252,   253,
     158,   160,   159,   165,   166,   177,   181,   188,   211,   187,
     196,   195,   198,   212,   213,   216,   217,   218,   214,   215,
     219,   220,   221,   222,   223,   224,   225,   227,   228,   229,
     230,   234,   235,   281,   281,   236,   290,   291,   278,   240,
     242,   246,   241,   247,   249,   250,   261,   255,   292,   251,
      24,   259,   258,   260,   262,   263,   264,   270,   317,   277,
     297,   301,   310,   265,   316,   322,   324,   325,   279,   343,
     349,   266,   267,   354,   355,   357,   226,   323,   359,   361,
     363,   281,   356,   383,   384,   385,   389,   290,   291,   151,
     269,   271,   333,   334,   393,   286,   353,   239,   304,   292,
     391,   244,   273,   237,   335,   274,   276,   238,   245,   287,
     243,   233,   232,   231,   344,   326,   345,   360,   328,   327,
     358,   248,   362,   381,   342,   333,   334,   390,   394,     0,
       0,     0,     0,   392,   395,   396,     0,   335
  };

  const short
  D2Parser::yycheck_[] =
  {
      56,    56,    58,    58,    60,    60,    62,   218,    23,    60,
       0,    52,    56,     5,    58,     7,    60,     9,    11,    12,
      13,    14,    35,    36,    17,     3,    19,    20,    21,    22,
       8,     7,    19,    20,    27,    57,   247,     7,    31,    11,
      12,    34,    57,    10,    37,    32,    33,    19,    20,     7,
      19,    20,    24,     5,    26,    19,    20,    19,    20,    28,
      29,    30,    24,    25,    57,    57,    58,    59,    60,    38,
      57,     7,    35,    36,    38,    39,    38,    41,    42,     3,
       3,     7,     3,     6,     8,    57,    40,     8,    57,    43,
      44,    45,    46,    57,    57,    57,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,   157,   158,     3,     3,
       3,     3,     3,     8,     8,     8,     8,     8,   184,   184,
     186,   186,     3,     5,     7,     6,   192,   192,   194,   194,
     184,     5,   186,     6,   200,   200,   202,   202,   192,   200,
     194,   202,     3,     7,     3,     3,   200,     8,   202,     8,
       8,     3,     3,     7,     6,     6,     3,     7,    15,    16,
       4,     3,     8,     4,     4,     4,     4,     3,    57,     6,
       3,     6,     4,     4,     4,     4,     4,     4,    58,    58,
       4,     4,     4,     4,     4,     4,     4,     4,    58,     4,
       4,     4,     4,   259,   260,     4,   262,   262,   249,     4,
       4,     4,    58,     4,     4,     7,     5,    18,   262,    57,
       7,     7,    57,     7,     7,     5,     5,     5,     3,   247,
       7,     7,     6,    57,     6,     4,     4,     4,   250,     5,
       4,    57,    57,     4,     4,     4,   178,   307,     6,     5,
       7,   307,    58,     4,     4,     4,     4,   313,   313,   315,
      57,    57,   318,   318,     4,   260,   343,   196,   270,   313,
      58,   202,    57,   192,   318,    57,    57,   194,   203,   261,
     200,   188,   186,   184,    57,   313,    57,    57,   317,   315,
     351,   207,    57,   367,   319,   351,   351,    60,   387,    -1,
      -1,    -1,    -1,    58,    57,    57,    -1,   351
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,     0,     5,     7,     9,    57,    58,    59,    60,
      73,    74,    75,    80,     7,    85,     7,    90,     7,   154,
       5,   148,     7,   122,     5,   116,     7,   137,     5,   132,
       7,   179,    81,    76,    86,    91,   155,   149,   123,   117,
     138,   133,   180,    73,    82,    83,    57,    78,    79,    10,
      87,    89,    11,    12,    13,    14,    17,    19,    20,    21,
      22,    27,    31,    34,    37,    57,    84,    92,    93,    94,
      96,    97,    98,   101,   103,   105,   107,   109,   146,   165,
     173,   187,    28,    29,    30,    38,    84,   103,   105,   156,
     157,   158,   160,   162,   163,     7,   150,   151,   152,    24,
      25,    38,    84,   103,   105,   124,   125,   126,   128,   130,
       7,   118,   119,   120,    11,    12,    26,    84,   103,   105,
     128,   139,   140,   141,   143,   145,     7,   134,   135,    35,
      36,    84,   181,   182,   183,   185,     6,     3,     4,     8,
       3,    88,     3,     8,    95,     4,     4,    99,   102,   104,
     106,   108,   110,   147,   166,   174,   188,     4,     3,     8,
     161,     4,   164,   159,     3,     8,   153,     6,     3,   129,
     131,   127,     3,     8,   121,     6,     3,   144,     4,   142,
       3,     8,   136,     3,     6,   184,   186,     3,     8,    73,
      73,    57,     4,     4,    58,    58,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    93,     4,    58,     4,
       4,   157,   156,   152,     4,     4,     4,   125,   124,   120,
       4,    58,     4,   140,   139,   135,     4,     4,   182,     4,
       7,    57,    15,    16,   100,    18,    75,    77,    57,     7,
       7,     5,     7,     5,     5,    57,    57,    57,     8,    57,
       5,    57,     8,    57,    57,     8,    57,    77,    73,    92,
      23,    84,   111,   112,   113,   114,   111,   150,    32,    33,
      84,   103,   105,   167,   168,   169,   171,     7,   175,   176,
     177,     7,   189,   190,   134,     8,   115,     3,     8,     8,
       6,   170,   172,     3,     8,   178,     6,     3,   191,     3,
       6,     6,     4,   113,     4,     4,   168,   181,   177,    38,
      39,    41,    42,    84,   103,   105,   192,   193,   194,   196,
     197,   199,   190,     5,    57,    57,     8,   195,   200,     4,
     198,     3,     8,   118,     4,     4,    58,     4,   193,     6,
      57,     5,    57,     7,   201,   202,   203,     3,     6,    40,
      43,    44,    45,    46,   204,   205,   206,   208,   209,   210,
     211,   202,   207,     4,     4,     4,   212,     3,     8,     4,
      60,    58,    58,     4,   205,    57,    57
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    61,    63,    62,    64,    62,    65,    62,    66,    62,
      67,    62,    68,    62,    69,    62,    70,    62,    71,    62,
      72,    62,    73,    73,    73,    73,    73,    73,    73,    74,
      76,    75,    77,    78,    78,    79,    79,    79,    81,    80,
      82,    82,    83,    83,    83,    84,    86,    85,    88,    87,
      87,    89,    91,    90,    92,    92,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    95,    94,    96,    97,    99,    98,   100,   100,   102,
     101,   104,   103,   106,   105,   108,   107,   110,   109,   111,
     111,   112,   112,   112,   113,   113,   115,   114,   117,   116,
     118,   118,   119,   119,   119,   121,   120,   123,   122,   124,
     124,   124,   125,   125,   125,   125,   125,   125,   127,   126,
     129,   128,   131,   130,   133,   132,   134,   134,   134,   136,
     135,   138,   137,   139,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   142,   141,   144,   143,   145,   147,   146,
     149,   148,   150,   150,   151,   151,   151,   153,   152,   155,
     154,   156,   156,   156,   157,   157,   157,   157,   157,   157,
     157,   159,   158,   161,   160,   162,   164,   163,   166,   165,
     167,   167,   167,   168,   168,   168,   168,   168,   170,   169,
     172,   171,   174,   173,   175,   175,   176,   176,   176,   178,
     177,   180,   179,   181,   181,   181,   181,   182,   182,   184,
     183,   186,   185,   188,   187,   189,   189,   189,   191,   190,
     192,   192,   192,   193,   193,   193,   193,   193,   193,   193,
     195,   194,   196,   198,   197,   200,   199,   201,   201,   201,
     203,   202,   204,   204,   204,   205,   205,   205,   205,   205,
     207,   206,   208,   209,   210,   212,   211
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
       1,     0,     4,     0,     4,     3,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
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
     156,   156,   167,   170,   171,   174,   179,   185,   190,   190,
     197,   198,   201,   205,   209,   219,   228,   228,   241,   241,
     251,   254,   258,   258,   266,   267,   268,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   290,   290,   299,   308,   318,   318,   327,   328,   331,
     331,   340,   340,   365,   365,   392,   392,   403,   403,   414,
     415,   418,   419,   420,   425,   426,   431,   431,   442,   442,
     449,   450,   453,   454,   455,   460,   460,   468,   468,   475,
     476,   477,   482,   483,   484,   485,   486,   487,   491,   491,
     504,   504,   517,   517,   528,   528,   535,   536,   537,   542,
     542,   550,   550,   557,   558,   559,   564,   565,   566,   567,
     568,   569,   570,   573,   573,   586,   586,   595,   610,   610,
     621,   621,   628,   629,   632,   633,   634,   639,   639,   647,
     647,   656,   657,   658,   663,   664,   665,   666,   667,   668,
     669,   672,   672,   685,   685,   697,   706,   706,   723,   723,
     734,   735,   736,   741,   742,   743,   744,   745,   748,   748,
     757,   757,   768,   768,   779,   780,   783,   784,   785,   790,
     790,   800,   800,   810,   811,   812,   815,   818,   819,   822,
     822,   831,   831,   841,   841,   854,   855,   856,   862,   862,
     870,   871,   872,   877,   878,   879,   880,   881,   882,   883,
     886,   886,   895,   901,   901,   910,   910,   921,   922,   923,
     928,   928,   936,   937,   938,   943,   944,   945,   946,   947,
     950,   950,   959,   965,   971,   977,   977
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
#line 2849 "d2_parser.cc"

#line 986 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
