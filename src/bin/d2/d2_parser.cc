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
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 384 "d2_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 390 "d2_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 396 "d2_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 402 "d2_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 408 "d2_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "d2_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 111 "d2_parser.yy"
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
#line 120 "d2_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 695 "d2_parser.cc"
    break;

  case 4: // $@2: %empty
#line 121 "d2_parser.yy"
                         { ctx.ctx_ = ctx.CONFIG; }
#line 701 "d2_parser.cc"
    break;

  case 6: // $@3: %empty
#line 122 "d2_parser.yy"
                    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 707 "d2_parser.cc"
    break;

  case 8: // $@4: %empty
#line 123 "d2_parser.yy"
                    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 713 "d2_parser.cc"
    break;

  case 10: // $@5: %empty
#line 124 "d2_parser.yy"
                     { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 719 "d2_parser.cc"
    break;

  case 12: // $@6: %empty
#line 125 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 725 "d2_parser.cc"
    break;

  case 14: // $@7: %empty
#line 126 "d2_parser.yy"
                        { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 731 "d2_parser.cc"
    break;

  case 16: // $@8: %empty
#line 127 "d2_parser.yy"
                      { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 737 "d2_parser.cc"
    break;

  case 18: // $@9: %empty
#line 128 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 743 "d2_parser.cc"
    break;

  case 20: // value: "integer"
#line 136 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 749 "d2_parser.cc"
    break;

  case 21: // value: "floating point"
#line 137 "d2_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 755 "d2_parser.cc"
    break;

  case 22: // value: "boolean"
#line 138 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 761 "d2_parser.cc"
    break;

  case 23: // value: "constant string"
#line 139 "d2_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 767 "d2_parser.cc"
    break;

  case 24: // value: "null"
#line 140 "d2_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 773 "d2_parser.cc"
    break;

  case 25: // value: map2
#line 141 "d2_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 779 "d2_parser.cc"
    break;

  case 26: // value: list_generic
#line 142 "d2_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 785 "d2_parser.cc"
    break;

  case 27: // sub_json: value
#line 145 "d2_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 794 "d2_parser.cc"
    break;

  case 28: // $@10: %empty
#line 150 "d2_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 805 "d2_parser.cc"
    break;

  case 29: // map2: "{" $@10 map_content "}"
#line 155 "d2_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 815 "d2_parser.cc"
    break;

  case 30: // map_value: map2
#line 161 "d2_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 821 "d2_parser.cc"
    break;

  case 33: // not_empty_map: "constant string" ":" value
#line 168 "d2_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 831 "d2_parser.cc"
    break;

  case 34: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 173 "d2_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 842 "d2_parser.cc"
    break;

  case 35: // $@11: %empty
#line 181 "d2_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 851 "d2_parser.cc"
    break;

  case 36: // list_generic: "[" $@11 list_content "]"
#line 184 "d2_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 859 "d2_parser.cc"
    break;

  case 39: // not_empty_list: value
#line 192 "d2_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 868 "d2_parser.cc"
    break;

  case 40: // not_empty_list: not_empty_list "," value
#line 196 "d2_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 877 "d2_parser.cc"
    break;

  case 41: // unknown_map_entry: "constant string" ":"
#line 207 "d2_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 888 "d2_parser.cc"
    break;

  case 42: // $@12: %empty
#line 216 "d2_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 899 "d2_parser.cc"
    break;

  case 43: // syntax_map: "{" $@12 global_object "}"
#line 221 "d2_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 909 "d2_parser.cc"
    break;

  case 44: // $@13: %empty
#line 229 "d2_parser.yy"
                        {
    ctx.unique("DhcpDdns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 921 "d2_parser.cc"
    break;

  case 45: // global_object: "DhcpDdns" $@13 ":" "{" dhcpddns_params "}"
#line 235 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 930 "d2_parser.cc"
    break;

  case 46: // $@14: %empty
#line 240 "d2_parser.yy"
                             {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 940 "d2_parser.cc"
    break;

  case 47: // sub_dhcpddns: "{" $@14 dhcpddns_params "}"
#line 244 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 948 "d2_parser.cc"
    break;

  case 63: // $@15: %empty
#line 268 "d2_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 957 "d2_parser.cc"
    break;

  case 64: // ip_address: "ip-address" $@15 ":" "constant string"
#line 271 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 967 "d2_parser.cc"
    break;

  case 65: // port: "port" ":" "integer"
#line 277 "d2_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 980 "d2_parser.cc"
    break;

  case 66: // dns_server_timeout: "dns-server-timeout" ":" "integer"
#line 286 "d2_parser.yy"
                                                     {
    ctx.unique("dns-server-timeout", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 994 "d2_parser.cc"
    break;

  case 67: // $@16: %empty
#line 296 "d2_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 1003 "d2_parser.cc"
    break;

  case 68: // ncr_protocol: "ncr-protocol" $@16 ":" ncr_protocol_value
#line 299 "d2_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1012 "d2_parser.cc"
    break;

  case 69: // ncr_protocol_value: "UDP"
#line 305 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1018 "d2_parser.cc"
    break;

  case 70: // ncr_protocol_value: "TCP"
#line 306 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1024 "d2_parser.cc"
    break;

  case 71: // $@17: %empty
#line 309 "d2_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1033 "d2_parser.cc"
    break;

  case 72: // ncr_format: "ncr-format" $@17 ":" "JSON"
#line 312 "d2_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1043 "d2_parser.cc"
    break;

  case 73: // $@18: %empty
#line 318 "d2_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1051 "d2_parser.cc"
    break;

  case 74: // user_context: "user-context" $@18 ":" map_value
#line 320 "d2_parser.yy"
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
#line 1078 "d2_parser.cc"
    break;

  case 75: // $@19: %empty
#line 343 "d2_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1086 "d2_parser.cc"
    break;

  case 76: // comment: "comment" $@19 ":" "constant string"
#line 345 "d2_parser.yy"
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
#line 1115 "d2_parser.cc"
    break;

  case 77: // $@20: %empty
#line 370 "d2_parser.yy"
                            {
    ctx.unique("forward-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1127 "d2_parser.cc"
    break;

  case 78: // forward_ddns: "forward-ddns" $@20 ":" "{" ddns_mgr_params "}"
#line 376 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1136 "d2_parser.cc"
    break;

  case 79: // $@21: %empty
#line 381 "d2_parser.yy"
                            {
    ctx.unique("reverse-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1148 "d2_parser.cc"
    break;

  case 80: // reverse_ddns: "reverse-ddns" $@21 ":" "{" ddns_mgr_params "}"
#line 387 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1157 "d2_parser.cc"
    break;

  case 87: // $@22: %empty
#line 406 "d2_parser.yy"
                           {
    ctx.unique("ddns-domains", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1169 "d2_parser.cc"
    break;

  case 88: // ddns_domains: "ddns-domains" $@22 ":" "[" ddns_domain_list "]"
#line 412 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1178 "d2_parser.cc"
    break;

  case 89: // $@23: %empty
#line 417 "d2_parser.yy"
                                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1187 "d2_parser.cc"
    break;

  case 90: // sub_ddns_domains: "[" $@23 ddns_domain_list "]"
#line 420 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1195 "d2_parser.cc"
    break;

  case 95: // $@24: %empty
#line 432 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1205 "d2_parser.cc"
    break;

  case 96: // ddns_domain: "{" $@24 ddns_domain_params "}"
#line 436 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1213 "d2_parser.cc"
    break;

  case 97: // $@25: %empty
#line 440 "d2_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1222 "d2_parser.cc"
    break;

  case 98: // sub_ddns_domain: "{" $@25 ddns_domain_params "}"
#line 443 "d2_parser.yy"
                                    {
    // parsing completed
}
#line 1230 "d2_parser.cc"
    break;

  case 107: // $@26: %empty
#line 460 "d2_parser.yy"
                       {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "d2_parser.cc"
    break;

  case 108: // ddns_domain_name: "name" $@26 ":" "constant string"
#line 463 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1253 "d2_parser.cc"
    break;

  case 109: // $@27: %empty
#line 473 "d2_parser.yy"
                               {
    ctx.unique("key-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1262 "d2_parser.cc"
    break;

  case 110: // ddns_domain_key_name: "key-name" $@27 ":" "constant string"
#line 476 "d2_parser.yy"
               {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1273 "d2_parser.cc"
    break;

  case 111: // $@28: %empty
#line 486 "d2_parser.yy"
                         {
    ctx.unique("dns-servers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1285 "d2_parser.cc"
    break;

  case 112: // dns_servers: "dns-servers" $@28 ":" "[" dns_server_list "]"
#line 492 "d2_parser.yy"
                                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1294 "d2_parser.cc"
    break;

  case 113: // $@29: %empty
#line 497 "d2_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1303 "d2_parser.cc"
    break;

  case 114: // sub_dns_servers: "[" $@29 dns_server_list "]"
#line 500 "d2_parser.yy"
                                  {
    // parsing completed
}
#line 1311 "d2_parser.cc"
    break;

  case 117: // $@30: %empty
#line 508 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1321 "d2_parser.cc"
    break;

  case 118: // dns_server: "{" $@30 dns_server_params "}"
#line 512 "d2_parser.yy"
                                   {
    ctx.stack_.pop_back();
}
#line 1329 "d2_parser.cc"
    break;

  case 119: // $@31: %empty
#line 516 "d2_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1338 "d2_parser.cc"
    break;

  case 120: // sub_dns_server: "{" $@31 dns_server_params "}"
#line 519 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1346 "d2_parser.cc"
    break;

  case 129: // $@32: %empty
#line 535 "d2_parser.yy"
                              {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1355 "d2_parser.cc"
    break;

  case 130: // dns_server_hostname: "hostname" $@32 ":" "constant string"
#line 538 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1369 "d2_parser.cc"
    break;

  case 131: // $@33: %empty
#line 548 "d2_parser.yy"
                                  {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1378 "d2_parser.cc"
    break;

  case 132: // dns_server_ip_address: "ip-address" $@33 ":" "constant string"
#line 551 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1388 "d2_parser.cc"
    break;

  case 133: // dns_server_port: "port" ":" "integer"
#line 557 "d2_parser.yy"
                                    {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1401 "d2_parser.cc"
    break;

  case 134: // $@34: %empty
#line 572 "d2_parser.yy"
                     {
    ctx.unique("tsig-keys", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1413 "d2_parser.cc"
    break;

  case 135: // tsig_keys: "tsig-keys" $@34 ":" "[" tsig_keys_list "]"
#line 578 "d2_parser.yy"
                                                       {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1422 "d2_parser.cc"
    break;

  case 136: // $@35: %empty
#line 583 "d2_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1431 "d2_parser.cc"
    break;

  case 137: // sub_tsig_keys: "[" $@35 tsig_keys_list "]"
#line 586 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1439 "d2_parser.cc"
    break;

  case 142: // $@36: %empty
#line 598 "d2_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1449 "d2_parser.cc"
    break;

  case 143: // tsig_key: "{" $@36 tsig_key_params "}"
#line 602 "d2_parser.yy"
                                 {
    ctx.stack_.pop_back();
}
#line 1457 "d2_parser.cc"
    break;

  case 144: // $@37: %empty
#line 606 "d2_parser.yy"
                             {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1467 "d2_parser.cc"
    break;

  case 145: // sub_tsig_key: "{" $@37 tsig_key_params "}"
#line 610 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1475 "d2_parser.cc"
    break;

  case 155: // $@38: %empty
#line 628 "d2_parser.yy"
                    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "d2_parser.cc"
    break;

  case 156: // tsig_key_name: "name" $@38 ":" "constant string"
#line 631 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1498 "d2_parser.cc"
    break;

  case 157: // $@39: %empty
#line 641 "d2_parser.yy"
                              {
    ctx.unique("algorithm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1507 "d2_parser.cc"
    break;

  case 158: // tsig_key_algorithm: "algorithm" $@39 ":" "constant string"
#line 644 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1520 "d2_parser.cc"
    break;

  case 159: // tsig_key_digest_bits: "digest-bits" ":" "integer"
#line 653 "d2_parser.yy"
                                                {
    ctx.unique("digest-bits", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1533 "d2_parser.cc"
    break;

  case 160: // $@40: %empty
#line 662 "d2_parser.yy"
                        {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1542 "d2_parser.cc"
    break;

  case 161: // tsig_key_secret: "secret" $@40 ":" "constant string"
#line 665 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1555 "d2_parser.cc"
    break;

  case 162: // $@41: %empty
#line 679 "d2_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1567 "d2_parser.cc"
    break;

  case 163: // control_socket: "control-socket" $@41 ":" "{" control_socket_params "}"
#line 685 "d2_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1576 "d2_parser.cc"
    break;

  case 171: // $@42: %empty
#line 701 "d2_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1585 "d2_parser.cc"
    break;

  case 172: // control_socket_type: "socket-type" $@42 ":" "constant string"
#line 704 "d2_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 1595 "d2_parser.cc"
    break;

  case 173: // $@43: %empty
#line 710 "d2_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1604 "d2_parser.cc"
    break;

  case 174: // control_socket_name: "socket-name" $@43 ":" "constant string"
#line 713 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1614 "d2_parser.cc"
    break;

  case 175: // $@44: %empty
#line 721 "d2_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1626 "d2_parser.cc"
    break;

  case 176: // loggers: "loggers" $@44 ":" "[" loggers_entries "]"
#line 727 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1635 "d2_parser.cc"
    break;

  case 179: // $@45: %empty
#line 739 "d2_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1645 "d2_parser.cc"
    break;

  case 180: // logger_entry: "{" $@45 logger_params "}"
#line 743 "d2_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1653 "d2_parser.cc"
    break;

  case 190: // $@46: %empty
#line 760 "d2_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1662 "d2_parser.cc"
    break;

  case 191: // name: "name" $@46 ":" "constant string"
#line 763 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1672 "d2_parser.cc"
    break;

  case 192: // debuglevel: "debuglevel" ":" "integer"
#line 769 "d2_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1682 "d2_parser.cc"
    break;

  case 193: // $@47: %empty
#line 775 "d2_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1691 "d2_parser.cc"
    break;

  case 194: // severity: "severity" $@47 ":" "constant string"
#line 778 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1701 "d2_parser.cc"
    break;

  case 195: // $@48: %empty
#line 784 "d2_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1713 "d2_parser.cc"
    break;

  case 196: // output_options_list: "output_options" $@48 ":" "[" output_options_list_content "]"
#line 790 "d2_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1722 "d2_parser.cc"
    break;

  case 199: // $@49: %empty
#line 799 "d2_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1732 "d2_parser.cc"
    break;

  case 200: // output_entry: "{" $@49 output_params_list "}"
#line 803 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1740 "d2_parser.cc"
    break;

  case 208: // $@50: %empty
#line 818 "d2_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1749 "d2_parser.cc"
    break;

  case 209: // output: "output" $@50 ":" "constant string"
#line 821 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1759 "d2_parser.cc"
    break;

  case 210: // flush: "flush" ":" "boolean"
#line 827 "d2_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1769 "d2_parser.cc"
    break;

  case 211: // maxsize: "maxsize" ":" "integer"
#line 833 "d2_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1779 "d2_parser.cc"
    break;

  case 212: // maxver: "maxver" ":" "integer"
#line 839 "d2_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1789 "d2_parser.cc"
    break;

  case 213: // $@51: %empty
#line 845 "d2_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1798 "d2_parser.cc"
    break;

  case 214: // pattern: "pattern" $@51 ":" "constant string"
#line 848 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1808 "d2_parser.cc"
    break;


#line 1812 "d2_parser.cc"

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


  const signed char D2Parser::yypact_ninf_ = -80;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short
  D2Parser::yypact_[] =
  {
      38,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
       7,     1,     2,     8,    17,    26,    34,    53,    60,    86,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,     1,    40,
       3,     6,    15,    93,    46,   103,    10,   104,   -80,   113,
     117,   123,   121,   118,   -80,   129,   -80,   151,   153,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   154,   -80,
      39,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   155,   -80,   -80,   -80,   -80,
     -80,    45,   -80,   -80,   -80,   -80,   -80,   -80,   133,   146,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,    61,   -80,   -80,
     -80,   -80,   -80,   148,   157,   -80,   -80,   158,   -80,   -80,
     -80,   -80,    70,   -80,   -80,   -80,   -80,   -80,    43,   -80,
     -80,     1,     1,   -80,   108,   159,   -80,   160,   111,   112,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   -80,
       6,   -80,   172,   124,   173,   175,    15,   -80,    15,   -80,
      93,   176,   179,   183,    46,   -80,    46,   -80,   103,   184,
     136,   185,    10,   -80,    10,   104,   -80,   -80,   -80,   187,
     186,   139,   -80,   -80,    59,   177,   190,   141,   191,   192,
     195,   194,   197,   -80,   152,   -80,   156,   161,   -80,    98,
     -80,   162,   198,   174,   -80,    99,   -80,   180,   -80,   181,
     -80,   100,   -80,     1,     6,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,     9,     9,    93,    19,   199,   -80,   -80,
     -80,   -80,   -80,   104,   -80,   -80,   -80,   -80,   -80,   -80,
     110,   -80,   -80,   132,   -80,   -80,   -80,   135,   201,   -80,
     -80,   -80,   -80,   -80,   138,   -80,   -80,   -80,   -80,   106,
     -80,   145,   -80,   200,     9,   -80,   -80,   -80,   204,   206,
      19,   -80,    41,   199,   -80,   -80,   207,   -80,   182,   188,
     -80,   -80,   -80,   209,   -80,   -80,   -80,   -80,   142,   -80,
     -80,   -80,   -80,   -80,   -80,   103,   -80,   -80,   212,   213,
     178,   214,    41,   -80,   205,   193,   215,   -80,   196,   -80,
     -80,   -80,   216,   -80,   -80,   150,   -80,    55,   216,   -80,
     -80,   217,   220,   221,   -80,   144,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   222,   189,   202,   203,   232,    55,   -80,
     210,   -80,   -80,   -80,   211,   -80,   -80,   -80
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    35,    28,    24,    23,    20,    21,    22,    27,     3,
      25,    26,    42,     5,    46,     7,   144,     9,   136,    11,
      97,    13,    89,    15,   119,    17,   113,    19,    37,    31,
       0,     0,     0,   138,     0,    91,     0,     0,    39,     0,
      38,     0,     0,    32,    44,     0,    63,     0,     0,    67,
      71,    73,    75,    77,    79,   134,   162,   175,     0,    62,
       0,    48,    50,    51,    52,    53,    54,    60,    61,    55,
      56,    57,    58,    59,   157,     0,   160,   155,   154,   152,
     153,     0,   146,   148,   149,   150,   151,   142,     0,   139,
     140,   109,   111,   107,   106,   104,   105,     0,    99,   101,
     102,   103,    95,     0,    92,    93,   131,     0,   129,   128,
     126,   127,     0,   121,   123,   124,   125,   117,     0,   115,
      36,     0,     0,    29,     0,     0,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
       0,    47,     0,     0,     0,     0,     0,   145,     0,   137,
       0,     0,     0,     0,     0,    98,     0,    90,     0,     0,
       0,     0,     0,   120,     0,     0,   114,    40,    33,     0,
       0,     0,    65,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,     0,   159,     0,     0,   147,     0,
     141,     0,     0,     0,   100,     0,    94,     0,   133,     0,
     122,     0,   116,     0,     0,    64,    69,    70,    68,    72,
      30,    74,    76,    81,    81,   138,     0,     0,   158,   161,
     156,   143,   110,     0,   108,    96,   132,   130,   118,    34,
       0,    87,    86,     0,    82,    83,    85,     0,     0,   171,
     173,   170,   168,   169,     0,   164,   166,   167,   179,     0,
     177,     0,    45,     0,     0,    78,    80,   135,     0,     0,
       0,   163,     0,     0,   176,   112,     0,    84,     0,     0,
     165,   190,   195,     0,   193,   189,   187,   188,     0,   181,
     183,   185,   186,   184,   178,    91,   172,   174,     0,     0,
       0,     0,     0,   180,     0,     0,     0,   192,     0,   182,
      88,   191,     0,   194,   199,     0,   197,     0,     0,   196,
     208,     0,     0,     0,   213,     0,   201,   203,   204,   205,
     206,   207,   198,     0,     0,     0,     0,     0,     0,   200,
       0,   210,   211,   212,     0,   202,   209,   214
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -37,   -80,    23,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -52,   -80,   -80,   -80,   -80,   -80,   -80,    13,
      78,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -51,   -80,   -40,   -80,   -80,   -80,   -80,   -80,     5,   -80,
     -31,   -80,   -80,   -80,   -80,   -61,   -80,    69,   -80,   -80,
     -80,    72,    76,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,    11,    66,   -80,   -80,   -80,    68,    71,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,    20,   -80,    88,
     -80,   -80,   -80,    91,    96,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -15,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -17,   -80,   -80,   -45,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -60,   -80,   -80,   -79,   -80,
     -80,   -80,   -80,   -80,   -80,   -80
  };

  const short
  D2Parser::yydefgoto_[] =
  {
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    28,    29,    30,    49,   231,    62,    63,    31,    48,
      59,    60,    79,    33,    50,    65,   145,    35,    51,    80,
      81,    82,   147,    83,    84,    85,   150,   228,    86,   151,
      87,   152,    88,   153,    89,   154,    90,   155,   253,   254,
     255,   256,   273,    43,    55,   123,   124,   125,   176,    41,
      54,   117,   118,   119,   173,   120,   171,   121,   172,    47,
      57,   138,   139,   184,    45,    56,   132,   133,   134,   181,
     135,   179,   136,    91,   156,    39,    53,   108,   109,   110,
     168,    37,    52,   101,   102,   103,   165,   104,   162,   105,
     106,   164,    92,   157,   264,   265,   266,   278,   267,   279,
      93,   158,   269,   270,   282,   298,   299,   300,   308,   301,
     302,   311,   303,   309,   325,   326,   327,   335,   336,   337,
     343,   338,   339,   340,   341,   347
  };

  const short
  D2Parser::yytable_[] =
  {
      98,    99,   114,   115,   129,   130,    21,    20,    22,    32,
      23,    58,   100,    64,   116,    34,   131,    66,    67,    68,
      69,   126,   127,    70,    36,    71,    72,    73,    74,    71,
      72,    38,   251,    75,    71,    72,   128,    76,    71,    72,
      77,    40,   160,    94,    95,    96,   185,   161,   166,   186,
      97,   259,   260,   167,    24,    25,    26,    27,    42,    78,
      71,    72,    78,    78,   174,    71,    72,    44,    78,   175,
     111,   112,    78,   182,   226,   227,   291,   292,   183,   293,
     294,   113,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    46,   330,    61,    78,   331,   332,   333,   334,    78,
     107,   166,   174,   182,   187,   188,   241,   245,   248,   283,
     122,   137,   284,   160,    98,    99,    98,    99,   272,   140,
     141,   144,   114,   115,   114,   115,   100,   142,   100,   143,
     129,   130,   129,   130,   116,   274,   116,   146,   274,   169,
     275,   280,   131,   276,   131,   312,   281,   348,   185,   170,
     313,   285,   349,   328,   177,   148,   329,   149,   159,   163,
     178,   189,   180,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   204,   206,   205,   207,
     211,   252,   252,   212,   261,   262,   249,   213,   217,   219,
     218,   223,   225,   224,   232,   229,   263,    22,   233,   234,
     235,   236,   237,   243,   286,   238,   268,   277,   288,   239,
     289,   320,   305,   310,   240,   242,   315,   316,   318,   230,
     322,   344,   252,   324,   345,   346,   350,   244,   261,   262,
     295,   296,   317,   246,   247,   306,   354,   250,   203,   257,
     263,   307,   297,   287,   314,   351,   321,   216,   215,   323,
     214,   222,   221,   220,   271,   258,   352,   353,   210,   209,
     295,   296,   208,   356,   357,   290,   304,   319,   342,   355,
       0,     0,   297
  };

  const short
  D2Parser::yycheck_[] =
  {
      52,    52,    54,    54,    56,    56,     5,     0,     7,     7,
       9,    48,    52,    10,    54,     7,    56,    11,    12,    13,
      14,    11,    12,    17,     7,    19,    20,    21,    22,    19,
      20,     5,    23,    27,    19,    20,    26,    31,    19,    20,
      34,     7,     3,    28,    29,    30,     3,     8,     3,     6,
      35,    32,    33,     8,    53,    54,    55,    56,     5,    53,
      19,    20,    53,    53,     3,    19,    20,     7,    53,     8,
      24,    25,    53,     3,    15,    16,    35,    36,     8,    38,
      39,    35,    44,    45,    46,    47,    48,    49,    50,    51,
      52,     5,    37,    53,    53,    40,    41,    42,    43,    53,
       7,     3,     3,     3,   141,   142,     8,     8,     8,     3,
       7,     7,     6,     3,   166,   166,   168,   168,     8,     6,
       3,     3,   174,   174,   176,   176,   166,     4,   168,     8,
     182,   182,   184,   184,   174,     3,   176,     8,     3,     6,
       8,     3,   182,     8,   184,     3,     8,     3,     3,     3,
       8,     6,     8,     3,     6,     4,     6,     4,     4,     4,
       3,    53,     4,     4,     4,    54,    54,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,    54,     4,
       4,   233,   234,     4,   236,   236,   223,     4,     4,     4,
      54,     4,    53,     7,    53,    18,   236,     7,     7,     7,
       5,     7,     5,     5,     4,    53,     7,     6,     4,    53,
       4,     6,     5,     4,    53,    53,     4,     4,     4,   196,
       5,     4,   274,     7,     4,     4,     4,    53,   280,   280,
     282,   282,    54,    53,    53,    53,     4,   224,   160,   234,
     280,    53,   282,   274,   305,    56,    53,   178,   176,    53,
     174,   185,   184,   182,   243,   235,    54,    54,   170,   168,
     312,   312,   166,    53,    53,   280,   283,   312,   328,   348,
      -1,    -1,   312
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     5,     7,     9,    53,    54,    55,    56,    68,    69,
      70,    75,     7,    80,     7,    84,     7,   148,     5,   142,
       7,   116,     5,   110,     7,   131,     5,   126,    76,    71,
      81,    85,   149,   143,   117,   111,   132,   127,    68,    77,
      78,    53,    73,    74,    10,    82,    11,    12,    13,    14,
      17,    19,    20,    21,    22,    27,    31,    34,    53,    79,
      86,    87,    88,    90,    91,    92,    95,    97,    99,   101,
     103,   140,   159,   167,    28,    29,    30,    35,    79,    97,
      99,   150,   151,   152,   154,   156,   157,     7,   144,   145,
     146,    24,    25,    35,    79,    97,    99,   118,   119,   120,
     122,   124,     7,   112,   113,   114,    11,    12,    26,    79,
      97,    99,   133,   134,   135,   137,   139,     7,   128,   129,
       6,     3,     4,     8,     3,    83,     8,    89,     4,     4,
      93,    96,    98,   100,   102,   104,   141,   160,   168,     4,
       3,     8,   155,     4,   158,   153,     3,     8,   147,     6,
       3,   123,   125,   121,     3,     8,   115,     6,     3,   138,
       4,   136,     3,     8,   130,     3,     6,    68,    68,    53,
       4,     4,    54,    54,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    87,     4,    54,     4,     4,   151,   150,
     146,     4,     4,     4,   119,   118,   114,     4,    54,     4,
     134,   133,   129,     4,     7,    53,    15,    16,    94,    18,
      70,    72,    53,     7,     7,     5,     7,     5,    53,    53,
      53,     8,    53,     5,    53,     8,    53,    53,     8,    68,
      86,    23,    79,   105,   106,   107,   108,   105,   144,    32,
      33,    79,    97,    99,   161,   162,   163,   165,     7,   169,
     170,   128,     8,   109,     3,     8,     8,     6,   164,   166,
       3,     8,   171,     3,     6,     6,     4,   107,     4,     4,
     162,    35,    36,    38,    39,    79,    97,    99,   172,   173,
     174,   176,   177,   179,   170,     5,    53,    53,   175,   180,
       4,   178,     3,     8,   112,     4,     4,    54,     4,   173,
       6,    53,     5,    53,     7,   181,   182,   183,     3,     6,
      37,    40,    41,    42,    43,   184,   185,   186,   188,   189,
     190,   191,   182,   187,     4,     4,     4,   192,     3,     8,
       4,    56,    54,    54,     4,   185,    53,    53
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    57,    59,    58,    60,    58,    61,    58,    62,    58,
      63,    58,    64,    58,    65,    58,    66,    58,    67,    58,
      68,    68,    68,    68,    68,    68,    68,    69,    71,    70,
      72,    73,    73,    74,    74,    76,    75,    77,    77,    78,
      78,    79,    81,    80,    83,    82,    85,    84,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    89,    88,    90,    91,    93,    92,    94,
      94,    96,    95,    98,    97,   100,    99,   102,   101,   104,
     103,   105,   105,   106,   106,   107,   107,   109,   108,   111,
     110,   112,   112,   113,   113,   115,   114,   117,   116,   118,
     118,   119,   119,   119,   119,   119,   119,   121,   120,   123,
     122,   125,   124,   127,   126,   128,   128,   130,   129,   132,
     131,   133,   133,   134,   134,   134,   134,   134,   134,   136,
     135,   138,   137,   139,   141,   140,   143,   142,   144,   144,
     145,   145,   147,   146,   149,   148,   150,   150,   151,   151,
     151,   151,   151,   151,   151,   153,   152,   155,   154,   156,
     158,   157,   160,   159,   161,   161,   162,   162,   162,   162,
     162,   164,   163,   166,   165,   168,   167,   169,   169,   171,
     170,   172,   172,   173,   173,   173,   173,   173,   173,   173,
     175,   174,   176,   178,   177,   180,   179,   181,   181,   183,
     182,   184,   184,   185,   185,   185,   185,   185,   187,   186,
     188,   189,   190,   192,   191
  };

  const signed char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     3,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4
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
  "\"socket-name\"", "\"loggers\"", "\"name\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS", "SUB_TSIG_KEY", "SUB_TSIG_KEYS",
  "SUB_DDNS_DOMAIN", "SUB_DDNS_DOMAINS", "SUB_DNS_SERVER",
  "SUB_DNS_SERVERS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "value", "sub_json",
  "map2", "$@10", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@11", "list_content", "not_empty_list",
  "unknown_map_entry", "syntax_map", "$@12", "global_object", "$@13",
  "sub_dhcpddns", "$@14", "dhcpddns_params", "dhcpddns_param",
  "ip_address", "$@15", "port", "dns_server_timeout", "ncr_protocol",
  "$@16", "ncr_protocol_value", "ncr_format", "$@17", "user_context",
  "$@18", "comment", "$@19", "forward_ddns", "$@20", "reverse_ddns",
  "$@21", "ddns_mgr_params", "not_empty_ddns_mgr_params", "ddns_mgr_param",
  "ddns_domains", "$@22", "sub_ddns_domains", "$@23", "ddns_domain_list",
  "not_empty_ddns_domain_list", "ddns_domain", "$@24", "sub_ddns_domain",
  "$@25", "ddns_domain_params", "ddns_domain_param", "ddns_domain_name",
  "$@26", "ddns_domain_key_name", "$@27", "dns_servers", "$@28",
  "sub_dns_servers", "$@29", "dns_server_list", "dns_server", "$@30",
  "sub_dns_server", "$@31", "dns_server_params", "dns_server_param",
  "dns_server_hostname", "$@32", "dns_server_ip_address", "$@33",
  "dns_server_port", "tsig_keys", "$@34", "sub_tsig_keys", "$@35",
  "tsig_keys_list", "not_empty_tsig_keys_list", "tsig_key", "$@36",
  "sub_tsig_key", "$@37", "tsig_key_params", "tsig_key_param",
  "tsig_key_name", "$@38", "tsig_key_algorithm", "$@39",
  "tsig_key_digest_bits", "tsig_key_secret", "$@40", "control_socket",
  "$@41", "control_socket_params", "control_socket_param",
  "control_socket_type", "$@42", "control_socket_name", "$@43", "loggers",
  "$@44", "loggers_entries", "logger_entry", "$@45", "logger_params",
  "logger_param", "name", "$@46", "debuglevel", "severity", "$@47",
  "output_options_list", "$@48", "output_options_list_content",
  "output_entry", "$@49", "output_params_list", "output_params", "output",
  "$@50", "flush", "maxsize", "maxver", "pattern", "$@51", YY_NULLPTR
  };
#endif


#if D2_PARSER_DEBUG
  const short
  D2Parser::yyrline_[] =
  {
       0,   120,   120,   120,   121,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     136,   137,   138,   139,   140,   141,   142,   145,   150,   150,
     161,   164,   165,   168,   173,   181,   181,   188,   189,   192,
     196,   207,   216,   216,   229,   229,   240,   240,   248,   249,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   268,   268,   277,   286,   296,   296,   305,
     306,   309,   309,   318,   318,   343,   343,   370,   370,   381,
     381,   392,   393,   396,   397,   400,   401,   406,   406,   417,
     417,   424,   425,   428,   429,   432,   432,   440,   440,   447,
     448,   451,   452,   453,   454,   455,   456,   460,   460,   473,
     473,   486,   486,   497,   497,   504,   505,   508,   508,   516,
     516,   523,   524,   527,   528,   529,   530,   531,   532,   535,
     535,   548,   548,   557,   572,   572,   583,   583,   590,   591,
     594,   595,   598,   598,   606,   606,   615,   616,   619,   620,
     621,   622,   623,   624,   625,   628,   628,   641,   641,   653,
     662,   662,   679,   679,   690,   691,   694,   695,   696,   697,
     698,   701,   701,   710,   710,   721,   721,   734,   735,   739,
     739,   747,   748,   751,   752,   753,   754,   755,   756,   757,
     760,   760,   769,   775,   775,   784,   784,   795,   796,   799,
     799,   807,   808,   811,   812,   813,   814,   815,   818,   818,
     827,   833,   839,   845,   845
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
#line 2558 "d2_parser.cc"

#line 854 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
