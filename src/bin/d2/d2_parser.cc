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
#line 122 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 389 "d2_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 122 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 395 "d2_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 122 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 401 "d2_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 122 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 407 "d2_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 122 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 413 "d2_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 122 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 419 "d2_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 122 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 425 "d2_parser.cc"
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
#line 131 "d2_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 700 "d2_parser.cc"
    break;

  case 4: // $@2: %empty
#line 132 "d2_parser.yy"
                         { ctx.ctx_ = ctx.CONFIG; }
#line 706 "d2_parser.cc"
    break;

  case 6: // $@3: %empty
#line 133 "d2_parser.yy"
                    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 712 "d2_parser.cc"
    break;

  case 8: // $@4: %empty
#line 134 "d2_parser.yy"
                    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 718 "d2_parser.cc"
    break;

  case 10: // $@5: %empty
#line 135 "d2_parser.yy"
                     { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 724 "d2_parser.cc"
    break;

  case 12: // $@6: %empty
#line 136 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 730 "d2_parser.cc"
    break;

  case 14: // $@7: %empty
#line 137 "d2_parser.yy"
                        { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 736 "d2_parser.cc"
    break;

  case 16: // $@8: %empty
#line 138 "d2_parser.yy"
                      { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 742 "d2_parser.cc"
    break;

  case 18: // $@9: %empty
#line 139 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 748 "d2_parser.cc"
    break;

  case 20: // $@10: %empty
#line 140 "d2_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 754 "d2_parser.cc"
    break;

  case 22: // value: "integer"
#line 148 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 760 "d2_parser.cc"
    break;

  case 23: // value: "floating point"
#line 149 "d2_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 766 "d2_parser.cc"
    break;

  case 24: // value: "boolean"
#line 150 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 772 "d2_parser.cc"
    break;

  case 25: // value: "constant string"
#line 151 "d2_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 778 "d2_parser.cc"
    break;

  case 26: // value: "null"
#line 152 "d2_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 784 "d2_parser.cc"
    break;

  case 27: // value: map2
#line 153 "d2_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 790 "d2_parser.cc"
    break;

  case 28: // value: list_generic
#line 154 "d2_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 796 "d2_parser.cc"
    break;

  case 29: // sub_json: value
#line 157 "d2_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 805 "d2_parser.cc"
    break;

  case 30: // $@11: %empty
#line 162 "d2_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 816 "d2_parser.cc"
    break;

  case 31: // map2: "{" $@11 map_content "}"
#line 167 "d2_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 826 "d2_parser.cc"
    break;

  case 32: // map_value: map2
#line 173 "d2_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 832 "d2_parser.cc"
    break;

  case 35: // not_empty_map: "constant string" ":" value
#line 180 "d2_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 842 "d2_parser.cc"
    break;

  case 36: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 185 "d2_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 853 "d2_parser.cc"
    break;

  case 37: // not_empty_map: not_empty_map ","
#line 191 "d2_parser.yy"
                                   {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 861 "d2_parser.cc"
    break;

  case 38: // $@12: %empty
#line 196 "d2_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 870 "d2_parser.cc"
    break;

  case 39: // list_generic: "[" $@12 list_content "]"
#line 199 "d2_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 878 "d2_parser.cc"
    break;

  case 42: // not_empty_list: value
#line 207 "d2_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 887 "d2_parser.cc"
    break;

  case 43: // not_empty_list: not_empty_list "," value
#line 211 "d2_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 896 "d2_parser.cc"
    break;

  case 44: // not_empty_list: not_empty_list ","
#line 215 "d2_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 904 "d2_parser.cc"
    break;

  case 45: // unknown_map_entry: "constant string" ":"
#line 225 "d2_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 915 "d2_parser.cc"
    break;

  case 46: // $@13: %empty
#line 234 "d2_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 926 "d2_parser.cc"
    break;

  case 47: // syntax_map: "{" $@13 global_object "}"
#line 239 "d2_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 936 "d2_parser.cc"
    break;

  case 48: // $@14: %empty
#line 247 "d2_parser.yy"
                        {
    ctx.unique("DhcpDdns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 948 "d2_parser.cc"
    break;

  case 49: // global_object: "DhcpDdns" $@14 ":" "{" dhcpddns_params "}"
#line 253 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 957 "d2_parser.cc"
    break;

  case 51: // global_object_comma: global_object ","
#line 260 "d2_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 965 "d2_parser.cc"
    break;

  case 52: // $@15: %empty
#line 264 "d2_parser.yy"
                             {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 975 "d2_parser.cc"
    break;

  case 53: // sub_dhcpddns: "{" $@15 dhcpddns_params "}"
#line 268 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 983 "d2_parser.cc"
    break;

  case 56: // dhcpddns_params: dhcpddns_params ","
#line 274 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 991 "d2_parser.cc"
    break;

  case 71: // $@16: %empty
#line 296 "d2_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1000 "d2_parser.cc"
    break;

  case 72: // ip_address: "ip-address" $@16 ":" "constant string"
#line 299 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1010 "d2_parser.cc"
    break;

  case 73: // port: "port" ":" "integer"
#line 305 "d2_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1023 "d2_parser.cc"
    break;

  case 74: // dns_server_timeout: "dns-server-timeout" ":" "integer"
#line 314 "d2_parser.yy"
                                                     {
    ctx.unique("dns-server-timeout", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 1037 "d2_parser.cc"
    break;

  case 75: // $@17: %empty
#line 324 "d2_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 1046 "d2_parser.cc"
    break;

  case 76: // ncr_protocol: "ncr-protocol" $@17 ":" ncr_protocol_value
#line 327 "d2_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1055 "d2_parser.cc"
    break;

  case 77: // ncr_protocol_value: "UDP"
#line 333 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1061 "d2_parser.cc"
    break;

  case 78: // ncr_protocol_value: "TCP"
#line 334 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1067 "d2_parser.cc"
    break;

  case 79: // $@18: %empty
#line 337 "d2_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1076 "d2_parser.cc"
    break;

  case 80: // ncr_format: "ncr-format" $@18 ":" "JSON"
#line 340 "d2_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1086 "d2_parser.cc"
    break;

  case 81: // $@19: %empty
#line 346 "d2_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1094 "d2_parser.cc"
    break;

  case 82: // user_context: "user-context" $@19 ":" map_value
#line 348 "d2_parser.yy"
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
#line 1121 "d2_parser.cc"
    break;

  case 83: // $@20: %empty
#line 371 "d2_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1129 "d2_parser.cc"
    break;

  case 84: // comment: "comment" $@20 ":" "constant string"
#line 373 "d2_parser.yy"
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
#line 1158 "d2_parser.cc"
    break;

  case 85: // $@21: %empty
#line 398 "d2_parser.yy"
                            {
    ctx.unique("forward-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1170 "d2_parser.cc"
    break;

  case 86: // forward_ddns: "forward-ddns" $@21 ":" "{" ddns_mgr_params "}"
#line 404 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1179 "d2_parser.cc"
    break;

  case 87: // $@22: %empty
#line 409 "d2_parser.yy"
                            {
    ctx.unique("reverse-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1191 "d2_parser.cc"
    break;

  case 88: // reverse_ddns: "reverse-ddns" $@22 ":" "{" ddns_mgr_params "}"
#line 415 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1200 "d2_parser.cc"
    break;

  case 93: // not_empty_ddns_mgr_params: ddns_mgr_params ","
#line 426 "d2_parser.yy"
                                                 {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 1208 "d2_parser.cc"
    break;

  case 96: // $@23: %empty
#line 437 "d2_parser.yy"
                           {
    ctx.unique("ddns-domains", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1220 "d2_parser.cc"
    break;

  case 97: // ddns_domains: "ddns-domains" $@23 ":" "[" ddns_domain_list "]"
#line 443 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "d2_parser.cc"
    break;

  case 98: // $@24: %empty
#line 448 "d2_parser.yy"
                                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1238 "d2_parser.cc"
    break;

  case 99: // sub_ddns_domains: "[" $@24 ddns_domain_list "]"
#line 451 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1246 "d2_parser.cc"
    break;

  case 104: // not_empty_ddns_domain_list: not_empty_ddns_domain_list ","
#line 461 "d2_parser.yy"
                                                           {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1254 "d2_parser.cc"
    break;

  case 105: // $@25: %empty
#line 466 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1264 "d2_parser.cc"
    break;

  case 106: // ddns_domain: "{" $@25 ddns_domain_params "}"
#line 470 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1272 "d2_parser.cc"
    break;

  case 107: // $@26: %empty
#line 474 "d2_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1281 "d2_parser.cc"
    break;

  case 108: // sub_ddns_domain: "{" $@26 ddns_domain_params "}"
#line 477 "d2_parser.yy"
                                    {
    // parsing completed
}
#line 1289 "d2_parser.cc"
    break;

  case 111: // ddns_domain_params: ddns_domain_params ","
#line 483 "d2_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 1297 "d2_parser.cc"
    break;

  case 118: // $@27: %empty
#line 497 "d2_parser.yy"
                       {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "d2_parser.cc"
    break;

  case 119: // ddns_domain_name: "name" $@27 ":" "constant string"
#line 500 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1320 "d2_parser.cc"
    break;

  case 120: // $@28: %empty
#line 510 "d2_parser.yy"
                        {
    ctx.unique("key-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1329 "d2_parser.cc"
    break;

  case 121: // ddns_key_name: "key-name" $@28 ":" "constant string"
#line 513 "d2_parser.yy"
               {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1340 "d2_parser.cc"
    break;

  case 122: // $@29: %empty
#line 523 "d2_parser.yy"
                         {
    ctx.unique("dns-servers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1352 "d2_parser.cc"
    break;

  case 123: // dns_servers: "dns-servers" $@29 ":" "[" dns_server_list "]"
#line 529 "d2_parser.yy"
                                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1361 "d2_parser.cc"
    break;

  case 124: // $@30: %empty
#line 534 "d2_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1370 "d2_parser.cc"
    break;

  case 125: // sub_dns_servers: "[" $@30 dns_server_list "]"
#line 537 "d2_parser.yy"
                                  {
    // parsing completed
}
#line 1378 "d2_parser.cc"
    break;

  case 128: // dns_server_list: dns_server_list ","
#line 543 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1386 "d2_parser.cc"
    break;

  case 129: // $@31: %empty
#line 548 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1396 "d2_parser.cc"
    break;

  case 130: // dns_server: "{" $@31 dns_server_params "}"
#line 552 "d2_parser.yy"
                                   {
    ctx.stack_.pop_back();
}
#line 1404 "d2_parser.cc"
    break;

  case 131: // $@32: %empty
#line 556 "d2_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1413 "d2_parser.cc"
    break;

  case 132: // sub_dns_server: "{" $@32 dns_server_params "}"
#line 559 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1421 "d2_parser.cc"
    break;

  case 135: // dns_server_params: dns_server_params ","
#line 565 "d2_parser.yy"
                                         {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1429 "d2_parser.cc"
    break;

  case 143: // $@33: %empty
#line 579 "d2_parser.yy"
                              {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1438 "d2_parser.cc"
    break;

  case 144: // dns_server_hostname: "hostname" $@33 ":" "constant string"
#line 582 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1452 "d2_parser.cc"
    break;

  case 145: // $@34: %empty
#line 592 "d2_parser.yy"
                                  {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1461 "d2_parser.cc"
    break;

  case 146: // dns_server_ip_address: "ip-address" $@34 ":" "constant string"
#line 595 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1471 "d2_parser.cc"
    break;

  case 147: // dns_server_port: "port" ":" "integer"
#line 601 "d2_parser.yy"
                                    {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1484 "d2_parser.cc"
    break;

  case 148: // $@35: %empty
#line 616 "d2_parser.yy"
                     {
    ctx.unique("tsig-keys", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1496 "d2_parser.cc"
    break;

  case 149: // tsig_keys: "tsig-keys" $@35 ":" "[" tsig_keys_list "]"
#line 622 "d2_parser.yy"
                                                       {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1505 "d2_parser.cc"
    break;

  case 150: // $@36: %empty
#line 627 "d2_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1514 "d2_parser.cc"
    break;

  case 151: // sub_tsig_keys: "[" $@36 tsig_keys_list "]"
#line 630 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1522 "d2_parser.cc"
    break;

  case 156: // not_empty_tsig_keys_list: not_empty_tsig_keys_list ","
#line 640 "d2_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1530 "d2_parser.cc"
    break;

  case 157: // $@37: %empty
#line 645 "d2_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1540 "d2_parser.cc"
    break;

  case 158: // tsig_key: "{" $@37 tsig_key_params "}"
#line 649 "d2_parser.yy"
                                 {
    ctx.stack_.pop_back();
}
#line 1548 "d2_parser.cc"
    break;

  case 159: // $@38: %empty
#line 653 "d2_parser.yy"
                             {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1558 "d2_parser.cc"
    break;

  case 160: // sub_tsig_key: "{" $@38 tsig_key_params "}"
#line 657 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1566 "d2_parser.cc"
    break;

  case 163: // tsig_key_params: tsig_key_params ","
#line 664 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1574 "d2_parser.cc"
    break;

  case 172: // $@39: %empty
#line 679 "d2_parser.yy"
                    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1583 "d2_parser.cc"
    break;

  case 173: // tsig_key_name: "name" $@39 ":" "constant string"
#line 682 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1597 "d2_parser.cc"
    break;

  case 174: // $@40: %empty
#line 692 "d2_parser.yy"
                              {
    ctx.unique("algorithm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1606 "d2_parser.cc"
    break;

  case 175: // tsig_key_algorithm: "algorithm" $@40 ":" "constant string"
#line 695 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1619 "d2_parser.cc"
    break;

  case 176: // tsig_key_digest_bits: "digest-bits" ":" "integer"
#line 704 "d2_parser.yy"
                                                {
    ctx.unique("digest-bits", ctx.loc2pos(yystack_[2].location));
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1632 "d2_parser.cc"
    break;

  case 177: // $@41: %empty
#line 713 "d2_parser.yy"
                        {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.unique("secret-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1642 "d2_parser.cc"
    break;

  case 178: // tsig_key_secret: "secret" $@41 ":" "constant string"
#line 717 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1655 "d2_parser.cc"
    break;

  case 179: // $@42: %empty
#line 726 "d2_parser.yy"
                                  {
    ctx.unique("secret", ctx.loc2pos(yystack_[0].location));
    ctx.unique("secret-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "d2_parser.cc"
    break;

  case 180: // tsig_key_secret_file: "secret-file" $@42 ":" "constant string"
#line 730 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret file name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret-file", elem);
    ctx.leave();
}
#line 1678 "d2_parser.cc"
    break;

  case 181: // $@43: %empty
#line 744 "d2_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1690 "d2_parser.cc"
    break;

  case 182: // control_socket: "control-socket" $@43 ":" "{" control_socket_params "}"
#line 750 "d2_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1699 "d2_parser.cc"
    break;

  case 185: // control_socket_params: control_socket_params ","
#line 757 "d2_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1707 "d2_parser.cc"
    break;

  case 191: // $@44: %empty
#line 769 "d2_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "d2_parser.cc"
    break;

  case 192: // control_socket_type: "socket-type" $@44 ":" "constant string"
#line 772 "d2_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 1726 "d2_parser.cc"
    break;

  case 193: // $@45: %empty
#line 778 "d2_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1735 "d2_parser.cc"
    break;

  case 194: // control_socket_name: "socket-name" $@45 ":" "constant string"
#line 781 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1745 "d2_parser.cc"
    break;

  case 195: // $@46: %empty
#line 789 "d2_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1757 "d2_parser.cc"
    break;

  case 196: // hooks_libraries: "hooks-libraries" $@46 ":" "[" hooks_libraries_list "]"
#line 795 "d2_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1766 "d2_parser.cc"
    break;

  case 201: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 806 "d2_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 1774 "d2_parser.cc"
    break;

  case 202: // $@47: %empty
#line 811 "d2_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1784 "d2_parser.cc"
    break;

  case 203: // hooks_library: "{" $@47 hooks_params "}"
#line 815 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1794 "d2_parser.cc"
    break;

  case 204: // $@48: %empty
#line 821 "d2_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1804 "d2_parser.cc"
    break;

  case 205: // sub_hooks_library: "{" $@48 hooks_params "}"
#line 825 "d2_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1814 "d2_parser.cc"
    break;

  case 208: // hooks_params: hooks_params ","
#line 833 "d2_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 1822 "d2_parser.cc"
    break;

  case 212: // $@49: %empty
#line 843 "d2_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1831 "d2_parser.cc"
    break;

  case 213: // library: "library" $@49 ":" "constant string"
#line 846 "d2_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1841 "d2_parser.cc"
    break;

  case 214: // $@50: %empty
#line 852 "d2_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1850 "d2_parser.cc"
    break;

  case 215: // parameters: "parameters" $@50 ":" map_value
#line 855 "d2_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1859 "d2_parser.cc"
    break;

  case 216: // $@51: %empty
#line 862 "d2_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1871 "d2_parser.cc"
    break;

  case 217: // loggers: "loggers" $@51 ":" "[" loggers_entries "]"
#line 868 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1880 "d2_parser.cc"
    break;

  case 220: // loggers_entries: loggers_entries ","
#line 877 "d2_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1888 "d2_parser.cc"
    break;

  case 221: // $@52: %empty
#line 883 "d2_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1898 "d2_parser.cc"
    break;

  case 222: // logger_entry: "{" $@52 logger_params "}"
#line 887 "d2_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1906 "d2_parser.cc"
    break;

  case 225: // logger_params: logger_params ","
#line 893 "d2_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1914 "d2_parser.cc"
    break;

  case 233: // $@53: %empty
#line 907 "d2_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "d2_parser.cc"
    break;

  case 234: // name: "name" $@53 ":" "constant string"
#line 910 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1933 "d2_parser.cc"
    break;

  case 235: // debuglevel: "debuglevel" ":" "integer"
#line 916 "d2_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1943 "d2_parser.cc"
    break;

  case 236: // $@54: %empty
#line 922 "d2_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1952 "d2_parser.cc"
    break;

  case 237: // severity: "severity" $@54 ":" "constant string"
#line 925 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1962 "d2_parser.cc"
    break;

  case 238: // $@55: %empty
#line 931 "d2_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1974 "d2_parser.cc"
    break;

  case 239: // output_options_list: "output-options" $@55 ":" "[" output_options_list_content "]"
#line 937 "d2_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1983 "d2_parser.cc"
    break;

  case 242: // output_options_list_content: output_options_list_content ","
#line 944 "d2_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 1991 "d2_parser.cc"
    break;

  case 243: // $@56: %empty
#line 949 "d2_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2001 "d2_parser.cc"
    break;

  case 244: // output_entry: "{" $@56 output_params_list "}"
#line 953 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 2009 "d2_parser.cc"
    break;

  case 247: // output_params_list: output_params_list ","
#line 959 "d2_parser.yy"
                                        {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 2017 "d2_parser.cc"
    break;

  case 253: // $@57: %empty
#line 971 "d2_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2026 "d2_parser.cc"
    break;

  case 254: // output: "output" $@57 ":" "constant string"
#line 974 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2036 "d2_parser.cc"
    break;

  case 255: // flush: "flush" ":" "boolean"
#line 980 "d2_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 2046 "d2_parser.cc"
    break;

  case 256: // maxsize: "maxsize" ":" "integer"
#line 986 "d2_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 2056 "d2_parser.cc"
    break;

  case 257: // maxver: "maxver" ":" "integer"
#line 992 "d2_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 2066 "d2_parser.cc"
    break;

  case 258: // $@58: %empty
#line 998 "d2_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "d2_parser.cc"
    break;

  case 259: // pattern: "pattern" $@58 ":" "constant string"
#line 1001 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 2085 "d2_parser.cc"
    break;


#line 2089 "d2_parser.cc"

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
      53,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,    10,     8,     1,    16,    18,    27,    33,    42,    57,
      44,    65,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,     8,    23,    77,     7,    32,    82,    59,   105,
      24,   106,    22,  -215,   123,   111,   133,   128,   141,  -215,
      30,  -215,  -215,   142,   164,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,   174,  -215,    38,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,   175,  -215,  -215,  -215,  -215,  -215,  -215,
      67,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   150,   177,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,    85,  -215,  -215,
    -215,  -215,  -215,   176,   178,  -215,  -215,   179,  -215,  -215,
    -215,  -215,  -215,   108,  -215,  -215,  -215,  -215,  -215,   132,
    -215,  -215,  -215,  -215,   112,  -215,  -215,  -215,  -215,     8,
       8,  -215,   109,   180,  -215,  -215,   181,   127,   129,   183,
     185,   186,   187,   188,   189,   190,   191,   192,   193,  -215,
       7,  -215,   194,   140,   196,   197,   198,    32,  -215,    32,
    -215,    82,   199,   200,   201,    59,  -215,    59,  -215,   105,
     202,   156,   205,    24,  -215,    24,   106,  -215,   209,   210,
      -6,  -215,  -215,  -215,   212,   211,   159,  -215,  -215,    40,
     203,   213,   165,   217,   218,   214,   219,   222,   223,  -215,
     172,  -215,   173,   182,   184,  -215,   118,  -215,   195,   224,
     207,  -215,   119,  -215,   208,  -215,   215,  -215,   120,  -215,
     220,   213,  -215,     8,     7,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,    -1,    -1,    82,    66,   225,   226,  -215,
    -215,  -215,  -215,  -215,  -215,   106,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,   122,  -215,  -215,   152,  -215,  -215,
    -215,   154,   228,  -215,  -215,  -215,  -215,  -215,   155,  -215,
    -215,  -215,  -215,   229,   233,  -215,  -215,   169,  -215,   170,
    -215,   234,    -1,  -215,  -215,  -215,   235,   237,    66,  -215,
      22,  -215,   225,    34,   226,  -215,  -215,   232,  -215,   227,
     230,  -215,   161,  -215,  -215,  -215,   239,  -215,  -215,  -215,
    -215,   162,  -215,  -215,  -215,  -215,  -215,  -215,   105,  -215,
    -215,  -215,   240,   241,   216,   242,    34,  -215,   243,   231,
     245,  -215,   236,  -215,  -215,  -215,   244,  -215,  -215,   171,
    -215,    50,   244,  -215,  -215,   248,   250,   251,  -215,   163,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,   253,   221,   238,
     246,   254,    50,  -215,   249,  -215,  -215,  -215,   252,  -215,
    -215,  -215
  };

  const short
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    38,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    46,     5,    52,     7,   159,     9,
     150,    11,   107,    13,    98,    15,   131,    17,   124,    19,
     204,    21,    40,    33,     0,     0,     0,   152,     0,   100,
       0,     0,     0,    42,     0,    41,     0,     0,    34,    48,
       0,    50,    71,     0,     0,    75,    79,    81,    83,    85,
      87,   148,   181,   195,   216,     0,    70,     0,    54,    57,
      58,    59,    60,    61,    68,    69,    62,    63,    64,    65,
      66,    67,   174,     0,   177,   179,   172,   171,   169,   170,
       0,   161,   164,   165,   166,   167,   168,   157,     0,   153,
     154,   120,   122,   118,   117,   115,   116,     0,   109,   112,
     113,   114,   105,     0,   101,   102,   145,     0,   143,   142,
     140,   141,   139,     0,   133,   136,   137,   138,   129,     0,
     126,   212,   214,   209,     0,   206,   210,   211,    39,    44,
       0,    31,    37,     0,    51,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
      56,    53,     0,     0,     0,     0,     0,   163,   160,     0,
     151,   156,     0,     0,     0,   111,   108,     0,    99,   104,
       0,     0,     0,   135,   132,     0,   128,   125,     0,     0,
     208,   205,    43,    35,     0,     0,     0,    73,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
       0,   176,     0,     0,     0,   162,     0,   155,     0,     0,
       0,   110,     0,   103,     0,   147,     0,   134,     0,   127,
       0,     0,   207,     0,     0,    72,    77,    78,    76,    80,
      32,    82,    84,    89,    89,   152,     0,   197,     0,   175,
     178,   180,   173,   158,   121,     0,   119,   106,   146,   144,
     130,   213,   215,    36,     0,    96,    95,     0,    90,    91,
      94,     0,     0,   191,   193,   190,   188,   189,     0,   183,
     186,   187,   202,     0,   198,   199,   221,     0,   218,     0,
      49,     0,    93,    86,    88,   149,     0,     0,   185,   182,
       0,   196,   201,     0,   220,   217,   123,     0,    92,     0,
       0,   184,     0,   200,   233,   238,     0,   236,   232,   230,
     231,     0,   223,   226,   228,   229,   227,   219,   100,   192,
     194,   203,     0,     0,     0,     0,   225,   222,     0,     0,
       0,   235,     0,   224,    97,   234,     0,   237,   243,     0,
     240,     0,   242,   239,   253,     0,     0,     0,   258,     0,
     245,   248,   249,   250,   251,   252,   241,     0,     0,     0,
       0,     0,   247,   244,     0,   255,   256,   257,     0,   246,
     254,   259
  };

  const short
  D2Parser::yypgoto_[] =
  {
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,   -41,  -215,  -214,  -215,    -4,  -215,  -215,  -215,
    -215,  -215,  -215,   -56,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,     5,    68,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,   -55,  -215,   -44,  -215,  -215,  -215,  -215,  -215,
      -3,  -215,   -52,  -215,  -215,  -215,  -215,   -79,  -215,    71,
    -215,  -215,  -215,    74,    81,  -215,  -215,   -51,  -215,  -215,
    -215,  -215,  -215,     2,    75,  -215,  -215,  -215,    78,    69,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    15,
    -215,    93,  -215,  -215,  -215,    97,   100,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   -28,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   -31,  -215,
    -215,  -215,   -27,    86,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,   -32,  -215,  -215,   -61,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,   -74,  -215,  -215,   -93,  -215,  -215,  -215,
    -215,  -215,  -215,  -215
  };

  const short
  D2Parser::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    30,    31,    32,    53,   261,    67,    68,    33,
      52,    64,    65,    86,    35,    54,    70,   163,    71,    37,
      55,    87,    88,    89,   166,    90,    91,    92,   169,   258,
      93,   170,    94,   171,    95,   172,    96,   173,    97,   174,
     287,   288,   289,   290,   311,    45,    59,   133,   134,   135,
     197,    43,    58,   127,   128,   129,   194,   130,   192,   131,
     193,    49,    61,   149,   150,   205,    47,    60,   143,   144,
     145,   202,   146,   200,   147,    98,   175,    41,    57,   118,
     119,   120,   189,    39,    56,   110,   111,   112,   186,   113,
     182,   114,   115,   184,   116,   185,    99,   176,   298,   299,
     300,   316,   301,   317,   100,   177,   303,   304,   305,   320,
      51,    62,   154,   155,   156,   208,   157,   209,   101,   178,
     307,   308,   323,   341,   342,   343,   352,   344,   345,   355,
     346,   353,   369,   370,   371,   379,   380,   381,   387,   382,
     383,   384,   385,   391
  };

  const short
  D2Parser::yytable_[] =
  {
     107,   108,   124,   125,   139,   140,   153,   260,    34,   142,
      22,    63,   109,    23,   126,    24,   141,    25,    72,    73,
      74,    75,   285,    36,    76,    38,    77,    78,    79,    80,
     151,   152,    40,   164,    81,   136,   137,   260,   165,    82,
      42,   180,    83,    77,    78,    84,   181,    44,   121,    48,
     138,    77,    78,    77,    78,   256,   257,    85,   151,   152,
     102,   103,   104,   105,    46,    85,    26,    27,    28,    29,
     187,   106,    50,   334,   335,   188,   336,   337,    77,    78,
      85,    66,    85,   121,   122,    77,    78,    69,   195,   117,
      85,   374,    85,   196,   375,   376,   377,   378,   123,   293,
     294,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   203,   132,   148,   159,   210,   204,    85,   212,   213,
     211,   187,   195,   203,    85,   180,   273,   277,   280,   158,
     310,   107,   108,   107,   108,   206,   161,   160,   207,   124,
     125,   124,   125,   109,   162,   109,   167,   139,   140,   139,
     140,   126,   142,   126,   142,   312,   190,   312,   318,   141,
     313,   141,   314,   319,   210,   356,   392,   214,   168,   351,
     357,   393,   324,   206,   372,   325,   326,   373,   179,   183,
     191,   199,   198,   201,   215,   216,   217,   219,   218,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   230,   231,
     232,   233,   234,   238,   239,   240,   244,   286,   286,   246,
     295,   296,   283,   250,   251,   245,   253,   255,   254,   265,
      24,   259,   297,   262,   263,   264,   266,   267,   268,   275,
     269,   270,   302,   306,   315,   321,   322,   348,   327,   329,
     271,   330,   272,   354,   359,   360,   362,   282,   229,   364,
     366,   368,   388,   274,   389,   390,   286,   394,   398,   284,
     328,   291,   295,   296,   153,   276,   278,   338,   339,   358,
     243,   242,   247,   279,   297,   361,   241,   309,   281,   340,
     292,   249,   395,   248,   237,   349,   236,   235,   350,   365,
     331,   333,   347,   332,   367,   363,   252,   396,   386,   399,
     338,   339,     0,     0,     0,   397,     0,   400,     0,     0,
     401,     0,   340
  };

  const short
  D2Parser::yycheck_[] =
  {
      56,    56,    58,    58,    60,    60,    62,   221,     7,    60,
       0,    52,    56,     5,    58,     7,    60,     9,    11,    12,
      13,    14,    23,     7,    17,     7,    19,    20,    21,    22,
      36,    37,     5,     3,    27,    11,    12,   251,     8,    32,
       7,     3,    35,    19,    20,    38,     8,     5,    24,     5,
      26,    19,    20,    19,    20,    15,    16,    58,    36,    37,
      28,    29,    30,    31,     7,    58,    58,    59,    60,    61,
       3,    39,     7,    39,    40,     8,    42,    43,    19,    20,
      58,    58,    58,    24,    25,    19,    20,    10,     3,     7,
      58,    41,    58,     8,    44,    45,    46,    47,    39,    33,
      34,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,     3,     7,     7,     3,     3,     8,    58,   159,   160,
       8,     3,     3,     3,    58,     3,     8,     8,     8,     6,
       8,   187,   187,   189,   189,     3,     8,     4,     6,   195,
     195,   197,   197,   187,     3,   189,     4,   203,   203,   205,
     205,   195,   203,   197,   205,     3,     6,     3,     3,   203,
       8,   205,     8,     8,     3,     3,     3,    58,     4,     8,
       8,     8,     3,     3,     3,     6,     6,     6,     4,     4,
       3,     3,     6,     4,     4,     4,    59,     4,    59,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    59,
       4,     4,     4,     4,     4,     4,     4,   263,   264,     4,
     266,   266,   253,     4,     4,    59,     4,    58,     7,     5,
       7,    18,   266,    58,     7,     7,     7,     5,     5,     5,
      58,    58,     7,     7,     6,     6,     3,     5,     4,     4,
      58,     4,    58,     4,     4,     4,     4,   251,   180,     6,
       5,     7,     4,    58,     4,     4,   312,     4,     4,   254,
     312,   264,   318,   318,   320,    58,    58,   323,   323,   348,
     199,   197,   203,    58,   318,    59,   195,   275,    58,   323,
     265,   206,    61,   205,   191,    58,   189,   187,    58,    58,
     318,   322,   324,   320,    58,   356,   210,    59,   372,   392,
     356,   356,    -1,    -1,    -1,    59,    -1,    58,    -1,    -1,
      58,    -1,   356
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     0,     5,     7,     9,    58,    59,    60,    61,
      74,    75,    76,    81,     7,    86,     7,    91,     7,   155,
       5,   149,     7,   123,     5,   117,     7,   138,     5,   133,
       7,   182,    82,    77,    87,    92,   156,   150,   124,   118,
     139,   134,   183,    74,    83,    84,    58,    79,    80,    10,
      88,    90,    11,    12,    13,    14,    17,    19,    20,    21,
      22,    27,    32,    35,    38,    58,    85,    93,    94,    95,
      97,    98,    99,   102,   104,   106,   108,   110,   147,   168,
     176,   190,    28,    29,    30,    31,    39,    85,   104,   106,
     157,   158,   159,   161,   163,   164,   166,     7,   151,   152,
     153,    24,    25,    39,    85,   104,   106,   125,   126,   127,
     129,   131,     7,   119,   120,   121,    11,    12,    26,    85,
     104,   106,   129,   140,   141,   142,   144,   146,     7,   135,
     136,    36,    37,    85,   184,   185,   186,   188,     6,     3,
       4,     8,     3,    89,     3,     8,    96,     4,     4,   100,
     103,   105,   107,   109,   111,   148,   169,   177,   191,     4,
       3,     8,   162,     4,   165,   167,   160,     3,     8,   154,
       6,     3,   130,   132,   128,     3,     8,   122,     6,     3,
     145,     4,   143,     3,     8,   137,     3,     6,   187,   189,
       3,     8,    74,    74,    58,     4,     4,    59,    59,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    94,
       4,    59,     4,     4,     4,   158,   157,   153,     4,     4,
       4,   126,   125,   121,     4,    59,     4,   141,   140,   136,
       4,     4,   185,     4,     7,    58,    15,    16,   101,    18,
      76,    78,    58,     7,     7,     5,     7,     5,     5,    58,
      58,    58,    58,     8,    58,     5,    58,     8,    58,    58,
       8,    58,    78,    74,    93,    23,    85,   112,   113,   114,
     115,   112,   151,    33,    34,    85,   104,   106,   170,   171,
     172,   174,     7,   178,   179,   180,     7,   192,   193,   135,
       8,   116,     3,     8,     8,     6,   173,   175,     3,     8,
     181,     6,     3,   194,     3,     6,     6,     4,   114,     4,
       4,   171,   184,   180,    39,    40,    42,    43,    85,   104,
     106,   195,   196,   197,   199,   200,   202,   193,     5,    58,
      58,     8,   198,   203,     4,   201,     3,     8,   119,     4,
       4,    59,     4,   196,     6,    58,     5,    58,     7,   204,
     205,   206,     3,     6,    41,    44,    45,    46,    47,   207,
     208,   209,   211,   212,   213,   214,   205,   210,     4,     4,
       4,   215,     3,     8,     4,    61,    59,    59,     4,   208,
      58,    58
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    62,    64,    63,    65,    63,    66,    63,    67,    63,
      68,    63,    69,    63,    70,    63,    71,    63,    72,    63,
      73,    63,    74,    74,    74,    74,    74,    74,    74,    75,
      77,    76,    78,    79,    79,    80,    80,    80,    82,    81,
      83,    83,    84,    84,    84,    85,    87,    86,    89,    88,
      88,    90,    92,    91,    93,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    96,    95,    97,    98,   100,    99,   101,   101,   103,
     102,   105,   104,   107,   106,   109,   108,   111,   110,   112,
     112,   113,   113,   113,   114,   114,   116,   115,   118,   117,
     119,   119,   120,   120,   120,   122,   121,   124,   123,   125,
     125,   125,   126,   126,   126,   126,   126,   126,   128,   127,
     130,   129,   132,   131,   134,   133,   135,   135,   135,   137,
     136,   139,   138,   140,   140,   140,   141,   141,   141,   141,
     141,   141,   141,   143,   142,   145,   144,   146,   148,   147,
     150,   149,   151,   151,   152,   152,   152,   154,   153,   156,
     155,   157,   157,   157,   158,   158,   158,   158,   158,   158,
     158,   158,   160,   159,   162,   161,   163,   165,   164,   167,
     166,   169,   168,   170,   170,   170,   171,   171,   171,   171,
     171,   173,   172,   175,   174,   177,   176,   178,   178,   179,
     179,   179,   181,   180,   183,   182,   184,   184,   184,   184,
     185,   185,   187,   186,   189,   188,   191,   190,   192,   192,
     192,   194,   193,   195,   195,   195,   196,   196,   196,   196,
     196,   196,   196,   198,   197,   199,   201,   200,   203,   202,
     204,   204,   204,   206,   205,   207,   207,   207,   208,   208,
     208,   208,   208,   210,   209,   211,   212,   213,   215,   214
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
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4
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
  "\"socket-type\"", "\"socket-name\"", "\"hooks-libraries\"",
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
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@44", "control_socket_name", "$@45", "hooks_libraries", "$@46",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@47", "sub_hooks_library", "$@48", "hooks_params",
  "hooks_param", "library", "$@49", "parameters", "$@50", "loggers",
  "$@51", "loggers_entries", "logger_entry", "$@52", "logger_params",
  "logger_param", "name", "$@53", "debuglevel", "severity", "$@54",
  "output_options_list", "$@55", "output_options_list_content",
  "output_entry", "$@56", "output_params_list", "output_params", "output",
  "$@57", "flush", "maxsize", "maxver", "pattern", "$@58", YY_NULLPTR
  };
#endif


#if D2_PARSER_DEBUG
  const short
  D2Parser::yyrline_[] =
  {
       0,   131,   131,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   148,   149,   150,   151,   152,   153,   154,   157,
     162,   162,   173,   176,   177,   180,   185,   191,   196,   196,
     203,   204,   207,   211,   215,   225,   234,   234,   247,   247,
     257,   260,   264,   264,   272,   273,   274,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   296,   296,   305,   314,   324,   324,   333,   334,   337,
     337,   346,   346,   371,   371,   398,   398,   409,   409,   420,
     421,   424,   425,   426,   431,   432,   437,   437,   448,   448,
     455,   456,   459,   460,   461,   466,   466,   474,   474,   481,
     482,   483,   488,   489,   490,   491,   492,   493,   497,   497,
     510,   510,   523,   523,   534,   534,   541,   542,   543,   548,
     548,   556,   556,   563,   564,   565,   570,   571,   572,   573,
     574,   575,   576,   579,   579,   592,   592,   601,   616,   616,
     627,   627,   634,   635,   638,   639,   640,   645,   645,   653,
     653,   662,   663,   664,   669,   670,   671,   672,   673,   674,
     675,   676,   679,   679,   692,   692,   704,   713,   713,   726,
     726,   744,   744,   755,   756,   757,   762,   763,   764,   765,
     766,   769,   769,   778,   778,   789,   789,   800,   801,   804,
     805,   806,   811,   811,   821,   821,   831,   832,   833,   836,
     839,   840,   843,   843,   852,   852,   862,   862,   875,   876,
     877,   883,   883,   891,   892,   893,   898,   899,   900,   901,
     902,   903,   904,   907,   907,   916,   922,   922,   931,   931,
     942,   943,   944,   949,   949,   957,   958,   959,   964,   965,
     966,   967,   968,   971,   971,   980,   986,   992,   998,   998
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
#line 2883 "d2_parser.cc"

#line 1007 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
