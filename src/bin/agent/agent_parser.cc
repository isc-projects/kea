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
#define yylex   agent_lex



#include "agent_parser.h"


// Unqualified %code blocks.
#line 33 "agent_parser.yy"

#include <agent/parser_context.h>

// Avoid warnings with the error counter.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#line 57 "agent_parser.cc"


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
#if AGENT_DEBUG

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

#else // !AGENT_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !AGENT_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "agent_parser.yy"
namespace isc { namespace agent {
#line 150 "agent_parser.cc"

  /// Build a parser object.
  AgentParser::AgentParser (isc::agent::ParserContext& ctx_yyarg)
#if AGENT_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  AgentParser::~AgentParser ()
  {}

  AgentParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  AgentParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  AgentParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  AgentParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  AgentParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  AgentParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  AgentParser::symbol_kind_type
  AgentParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  AgentParser::stack_symbol_type::stack_symbol_type ()
  {}

  AgentParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
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

  AgentParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
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
  AgentParser::stack_symbol_type&
  AgentParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
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

  AgentParser::stack_symbol_type&
  AgentParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
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
  AgentParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if AGENT_DEBUG
  template <typename Base>
  void
  AgentParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
#line 124 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 393 "agent_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 124 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 399 "agent_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 124 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 405 "agent_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 124 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 411 "agent_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 124 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 417 "agent_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 124 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 423 "agent_parser.cc"
        break;

      case symbol_kind::S_socket_type_value: // socket_type_value
#line 124 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "agent_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 124 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 435 "agent_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  AgentParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  AgentParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  AgentParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if AGENT_DEBUG
  std::ostream&
  AgentParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  AgentParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  AgentParser::debug_level_type
  AgentParser::debug_level () const
  {
    return yydebug_;
  }

  void
  AgentParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // AGENT_DEBUG

  AgentParser::state_type
  AgentParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  AgentParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  AgentParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  AgentParser::operator() ()
  {
    return parse ();
  }

  int
  AgentParser::parse ()
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
      case symbol_kind::S_socket_type_value: // socket_type_value
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
#line 135 "agent_parser.yy"
                       { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 711 "agent_parser.cc"
    break;

  case 4: // $@2: %empty
#line 136 "agent_parser.yy"
                       { ctx.ctx_ = ctx.CONFIG; }
#line 717 "agent_parser.cc"
    break;

  case 6: // $@3: %empty
#line 137 "agent_parser.yy"
                       { ctx.ctx_ = ctx.AGENT; }
#line 723 "agent_parser.cc"
    break;

  case 8: // $@4: %empty
#line 145 "agent_parser.yy"
                          {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 733 "agent_parser.cc"
    break;

  case 9: // sub_agent: "{" $@4 global_params "}"
#line 149 "agent_parser.yy"
                               {
    // parsing completed
}
#line 741 "agent_parser.cc"
    break;

  case 10: // json: value
#line 156 "agent_parser.yy"
            {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 750 "agent_parser.cc"
    break;

  case 11: // value: "integer"
#line 162 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 756 "agent_parser.cc"
    break;

  case 12: // value: "floating point"
#line 163 "agent_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 762 "agent_parser.cc"
    break;

  case 13: // value: "boolean"
#line 164 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "agent_parser.cc"
    break;

  case 14: // value: "constant string"
#line 165 "agent_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "agent_parser.cc"
    break;

  case 15: // value: "null"
#line 166 "agent_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 780 "agent_parser.cc"
    break;

  case 16: // value: map
#line 167 "agent_parser.yy"
           { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 786 "agent_parser.cc"
    break;

  case 17: // value: list_generic
#line 168 "agent_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 792 "agent_parser.cc"
    break;

  case 18: // $@5: %empty
#line 172 "agent_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 803 "agent_parser.cc"
    break;

  case 19: // map: "{" $@5 map_content "}"
#line 177 "agent_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 813 "agent_parser.cc"
    break;

  case 20: // map_value: map
#line 183 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 819 "agent_parser.cc"
    break;

  case 23: // not_empty_map: "constant string" ":" value
#line 197 "agent_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 829 "agent_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 202 "agent_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 840 "agent_parser.cc"
    break;

  case 25: // not_empty_map: not_empty_map ","
#line 208 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 848 "agent_parser.cc"
    break;

  case 26: // $@6: %empty
#line 213 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 857 "agent_parser.cc"
    break;

  case 27: // list_generic: "[" $@6 list_content "]"
#line 216 "agent_parser.yy"
                               {
}
#line 864 "agent_parser.cc"
    break;

  case 30: // not_empty_list: value
#line 223 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 873 "agent_parser.cc"
    break;

  case 31: // not_empty_list: not_empty_list "," value
#line 227 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 882 "agent_parser.cc"
    break;

  case 32: // not_empty_list: not_empty_list ","
#line 231 "agent_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 890 "agent_parser.cc"
    break;

  case 33: // unknown_map_entry: "constant string" ":"
#line 243 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 901 "agent_parser.cc"
    break;

  case 34: // $@7: %empty
#line 251 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 912 "agent_parser.cc"
    break;

  case 35: // agent_syntax_map: "{" $@7 global_object "}"
#line 256 "agent_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 922 "agent_parser.cc"
    break;

  case 36: // $@8: %empty
#line 263 "agent_parser.yy"
                             {
    // Let's create a MapElement that will represent it, add it to the
    // top level map (that's already on the stack) and put the new map
    // on the stack as well, so child elements will be able to add
    // themselves to it.
    ctx.unique("Control-agent", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Control-agent", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AGENT);
}
#line 938 "agent_parser.cc"
    break;

  case 37: // global_object: "Control-agent" $@8 ":" "{" global_params "}"
#line 273 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 949 "agent_parser.cc"
    break;

  case 39: // global_object_comma: global_object ","
#line 282 "agent_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 957 "agent_parser.cc"
    break;

  case 42: // global_params: global_params ","
#line 288 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 965 "agent_parser.cc"
    break;

  case 57: // $@9: %empty
#line 311 "agent_parser.yy"
                     {
    ctx.unique("http-host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 974 "agent_parser.cc"
    break;

  case 58: // http_host: "http-host" $@9 ":" "constant string"
#line 314 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 984 "agent_parser.cc"
    break;

  case 59: // http_port: "http-port" ":" "integer"
#line 320 "agent_parser.yy"
                                   {
    ctx.unique("http-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 994 "agent_parser.cc"
    break;

  case 60: // $@10: %empty
#line 326 "agent_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1003 "agent_parser.cc"
    break;

  case 61: // trust_anchor: "trust-anchor" $@10 ":" "constant string"
#line 329 "agent_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 1013 "agent_parser.cc"
    break;

  case 62: // $@11: %empty
#line 335 "agent_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1022 "agent_parser.cc"
    break;

  case 63: // cert_file: "cert-file" $@11 ":" "constant string"
#line 338 "agent_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 1032 "agent_parser.cc"
    break;

  case 64: // $@12: %empty
#line 344 "agent_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1041 "agent_parser.cc"
    break;

  case 65: // key_file: "key-file" $@12 ":" "constant string"
#line 347 "agent_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 1051 "agent_parser.cc"
    break;

  case 66: // cert_required: "cert-required" ":" "boolean"
#line 353 "agent_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 1061 "agent_parser.cc"
    break;

  case 67: // $@13: %empty
#line 359 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1069 "agent_parser.cc"
    break;

  case 68: // user_context: "user-context" $@13 ":" map_value
#line 361 "agent_parser.yy"
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
#line 1096 "agent_parser.cc"
    break;

  case 69: // $@14: %empty
#line 384 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1104 "agent_parser.cc"
    break;

  case 70: // comment: "comment" $@14 ":" "constant string"
#line 386 "agent_parser.yy"
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
#line 1133 "agent_parser.cc"
    break;

  case 71: // $@15: %empty
#line 411 "agent_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 1145 "agent_parser.cc"
    break;

  case 72: // http_headers: "http-headers" $@15 ":" "[" http_header_list "]"
#line 417 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1154 "agent_parser.cc"
    break;

  case 77: // not_empty_http_header_list: not_empty_http_header_list ","
#line 428 "agent_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 1162 "agent_parser.cc"
    break;

  case 78: // $@16: %empty
#line 433 "agent_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1172 "agent_parser.cc"
    break;

  case 79: // http_header: "{" $@16 http_header_params "}"
#line 437 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1180 "agent_parser.cc"
    break;

  case 82: // http_header_params: http_header_params ","
#line 443 "agent_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 1188 "agent_parser.cc"
    break;

  case 88: // $@17: %empty
#line 455 "agent_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1197 "agent_parser.cc"
    break;

  case 89: // name: "name" $@17 ":" "constant string"
#line 458 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1207 "agent_parser.cc"
    break;

  case 90: // $@18: %empty
#line 464 "agent_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1216 "agent_parser.cc"
    break;

  case 91: // header_value: "value" $@18 ":" "constant string"
#line 467 "agent_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 1226 "agent_parser.cc"
    break;

  case 92: // $@19: %empty
#line 474 "agent_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1238 "agent_parser.cc"
    break;

  case 93: // hooks_libraries: "hooks-libraries" $@19 ":" "[" hooks_libraries_list "]"
#line 480 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1247 "agent_parser.cc"
    break;

  case 98: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 491 "agent_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 1255 "agent_parser.cc"
    break;

  case 99: // $@20: %empty
#line 496 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "agent_parser.cc"
    break;

  case 100: // hooks_library: "{" $@20 hooks_params "}"
#line 500 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1273 "agent_parser.cc"
    break;

  case 103: // hooks_params: hooks_params ","
#line 506 "agent_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 1281 "agent_parser.cc"
    break;

  case 107: // $@21: %empty
#line 516 "agent_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1290 "agent_parser.cc"
    break;

  case 108: // library: "library" $@21 ":" "constant string"
#line 519 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1300 "agent_parser.cc"
    break;

  case 109: // $@22: %empty
#line 525 "agent_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1309 "agent_parser.cc"
    break;

  case 110: // parameters: "parameters" $@22 ":" map_value
#line 528 "agent_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1318 "agent_parser.cc"
    break;

  case 111: // $@23: %empty
#line 536 "agent_parser.yy"
                                                      {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[2].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1330 "agent_parser.cc"
    break;

  case 112: // control_sockets: "control-sockets" ":" "{" $@23 control_sockets_params "}"
#line 542 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1339 "agent_parser.cc"
    break;

  case 115: // control_sockets_params: control_sockets_params ","
#line 552 "agent_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1347 "agent_parser.cc"
    break;

  case 120: // $@24: %empty
#line 566 "agent_parser.yy"
                                  {
    ctx.unique("dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1359 "agent_parser.cc"
    break;

  case 121: // dhcp4_server_socket: "dhcp4" $@24 ":" "{" control_socket_params "}"
#line 572 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1368 "agent_parser.cc"
    break;

  case 122: // $@25: %empty
#line 578 "agent_parser.yy"
                                  {
    ctx.unique("dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1380 "agent_parser.cc"
    break;

  case 123: // dhcp6_server_socket: "dhcp6" $@25 ":" "{" control_socket_params "}"
#line 584 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1389 "agent_parser.cc"
    break;

  case 124: // $@26: %empty
#line 590 "agent_parser.yy"
                            {
    ctx.unique("d2", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1401 "agent_parser.cc"
    break;

  case 125: // d2_server_socket: "d2" $@26 ":" "{" control_socket_params "}"
#line 596 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1410 "agent_parser.cc"
    break;

  case 128: // control_socket_params: control_socket_params ","
#line 604 "agent_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1418 "agent_parser.cc"
    break;

  case 134: // $@27: %empty
#line 618 "agent_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1427 "agent_parser.cc"
    break;

  case 135: // socket_name: "socket-name" $@27 ":" "constant string"
#line 621 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1437 "agent_parser.cc"
    break;

  case 136: // $@28: %empty
#line 628 "agent_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1446 "agent_parser.cc"
    break;

  case 137: // socket_type: "socket-type" $@28 ":" socket_type_value
#line 631 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1455 "agent_parser.cc"
    break;

  case 138: // socket_type_value: "unix"
#line 637 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1461 "agent_parser.cc"
    break;

  case 139: // $@29: %empty
#line 644 "agent_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 1473 "agent_parser.cc"
    break;

  case 140: // authentication: "authentication" $@29 ":" "{" auth_params "}"
#line 650 "agent_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1484 "agent_parser.cc"
    break;

  case 143: // auth_params: auth_params ","
#line 659 "agent_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 1492 "agent_parser.cc"
    break;

  case 151: // $@30: %empty
#line 673 "agent_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 1501 "agent_parser.cc"
    break;

  case 152: // auth_type: "type" $@30 ":" auth_type_value
#line 676 "agent_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1510 "agent_parser.cc"
    break;

  case 153: // auth_type_value: "basic"
#line 681 "agent_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 1516 "agent_parser.cc"
    break;

  case 154: // $@31: %empty
#line 684 "agent_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1525 "agent_parser.cc"
    break;

  case 155: // realm: "realm" $@31 ":" "constant string"
#line 687 "agent_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 1535 "agent_parser.cc"
    break;

  case 156: // $@32: %empty
#line 693 "agent_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1544 "agent_parser.cc"
    break;

  case 157: // directory: "directory" $@32 ":" "constant string"
#line 696 "agent_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 1554 "agent_parser.cc"
    break;

  case 158: // $@33: %empty
#line 702 "agent_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 1566 "agent_parser.cc"
    break;

  case 159: // clients: "clients" $@33 ":" "[" clients_list "]"
#line 708 "agent_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1575 "agent_parser.cc"
    break;

  case 164: // not_empty_clients_list: not_empty_clients_list ","
#line 719 "agent_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1583 "agent_parser.cc"
    break;

  case 165: // $@34: %empty
#line 724 "agent_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1593 "agent_parser.cc"
    break;

  case 166: // basic_auth: "{" $@34 clients_params "}"
#line 728 "agent_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 1601 "agent_parser.cc"
    break;

  case 169: // clients_params: clients_params ","
#line 734 "agent_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1609 "agent_parser.cc"
    break;

  case 177: // $@35: %empty
#line 748 "agent_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1618 "agent_parser.cc"
    break;

  case 178: // user: "user" $@35 ":" "constant string"
#line 751 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1628 "agent_parser.cc"
    break;

  case 179: // $@36: %empty
#line 757 "agent_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1637 "agent_parser.cc"
    break;

  case 180: // user_file: "user-file" $@36 ":" "constant string"
#line 760 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 1647 "agent_parser.cc"
    break;

  case 181: // $@37: %empty
#line 766 "agent_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1656 "agent_parser.cc"
    break;

  case 182: // password: "password" $@37 ":" "constant string"
#line 769 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", password);
    ctx.leave();
}
#line 1666 "agent_parser.cc"
    break;

  case 183: // $@38: %empty
#line 775 "agent_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1675 "agent_parser.cc"
    break;

  case 184: // password_file: "password-file" $@38 ":" "constant string"
#line 778 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 1685 "agent_parser.cc"
    break;

  case 185: // $@39: %empty
#line 788 "agent_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1697 "agent_parser.cc"
    break;

  case 186: // loggers: "loggers" $@39 ":" "[" loggers_entries "]"
#line 794 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1706 "agent_parser.cc"
    break;

  case 189: // loggers_entries: loggers_entries ","
#line 803 "agent_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1714 "agent_parser.cc"
    break;

  case 190: // $@40: %empty
#line 809 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1724 "agent_parser.cc"
    break;

  case 191: // logger_entry: "{" $@40 logger_params "}"
#line 813 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1732 "agent_parser.cc"
    break;

  case 194: // logger_params: logger_params ","
#line 819 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1740 "agent_parser.cc"
    break;

  case 202: // debuglevel: "debuglevel" ":" "integer"
#line 833 "agent_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1750 "agent_parser.cc"
    break;

  case 203: // $@41: %empty
#line 839 "agent_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1759 "agent_parser.cc"
    break;

  case 204: // severity: "severity" $@41 ":" "constant string"
#line 842 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1769 "agent_parser.cc"
    break;

  case 205: // $@42: %empty
#line 848 "agent_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1781 "agent_parser.cc"
    break;

  case 206: // output_options_list: "output-options" $@42 ":" "[" output_options_list_content "]"
#line 854 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1790 "agent_parser.cc"
    break;

  case 209: // output_options_list_content: output_options_list_content ","
#line 861 "agent_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 1798 "agent_parser.cc"
    break;

  case 210: // $@43: %empty
#line 866 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1808 "agent_parser.cc"
    break;

  case 211: // output_entry: "{" $@43 output_params_list "}"
#line 870 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1816 "agent_parser.cc"
    break;

  case 214: // output_params_list: output_params_list ","
#line 876 "agent_parser.yy"
                                        {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1824 "agent_parser.cc"
    break;

  case 220: // $@44: %empty
#line 888 "agent_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1833 "agent_parser.cc"
    break;

  case 221: // output: "output" $@44 ":" "constant string"
#line 891 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1843 "agent_parser.cc"
    break;

  case 222: // flush: "flush" ":" "boolean"
#line 897 "agent_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1853 "agent_parser.cc"
    break;

  case 223: // maxsize: "maxsize" ":" "integer"
#line 903 "agent_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1863 "agent_parser.cc"
    break;

  case 224: // maxver: "maxver" ":" "integer"
#line 909 "agent_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1873 "agent_parser.cc"
    break;

  case 225: // $@45: %empty
#line 915 "agent_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1882 "agent_parser.cc"
    break;

  case 226: // pattern: "pattern" $@45 ":" "constant string"
#line 918 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1892 "agent_parser.cc"
    break;


#line 1896 "agent_parser.cc"

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
  AgentParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  AgentParser::yytnamerr_ (const char *yystr)
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
  AgentParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // AgentParser::context.
  AgentParser::context::context (const AgentParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  AgentParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  AgentParser::yy_syntax_error_arguments_ (const context& yyctx,
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
  AgentParser::yysyntax_error_ (const context& yyctx) const
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


  const short AgentParser::yypact_ninf_ = -205;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      76,  -205,  -205,  -205,     5,     1,     2,    20,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,     1,   -20,    25,     0,  -205,    34,
      35,    63,    41,    85,  -205,    79,  -205,  -205,    90,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,    93,   131,  -205,  -205,
     132,  -205,   102,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,     1,     1,
    -205,    84,   139,  -205,  -205,   141,    53,   143,   144,   148,
     149,   150,   151,   152,   100,   153,   154,   155,  -205,     0,
    -205,  -205,  -205,   157,   156,   108,  -205,   160,   159,   117,
     161,   118,   119,   120,  -205,  -205,   162,   164,  -205,     1,
       0,  -205,   163,  -205,  -205,  -205,    22,  -205,  -205,  -205,
      46,   168,   169,  -205,   103,  -205,   171,   175,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,   104,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,   106,  -205,  -205,  -205,
    -205,  -205,   173,   177,  -205,  -205,    47,  -205,  -205,     7,
    -205,   163,   178,   179,   180,   181,    22,  -205,   182,   183,
     184,    46,  -205,   -21,  -205,   168,    32,   169,  -205,  -205,
    -205,  -205,  -205,  -205,   112,  -205,  -205,  -205,  -205,   170,
     127,   135,   186,  -205,   185,   190,   191,  -205,  -205,  -205,
    -205,   113,  -205,  -205,  -205,  -205,  -205,   189,  -205,  -205,
    -205,  -205,  -205,   114,  -205,  -205,  -205,  -205,  -205,   195,
     196,     7,  -205,  -205,  -205,  -205,  -205,   194,    59,    59,
      59,   198,   199,   -24,  -205,   200,   165,   201,    32,  -205,
     167,   172,  -205,  -205,   202,   203,  -205,  -205,  -205,  -205,
    -205,  -205,   115,  -205,  -205,  -205,   116,   122,   174,   159,
    -205,   204,  -205,   176,  -205,  -205,  -205,    45,  -205,   194,
     206,   210,    59,  -205,  -205,  -205,  -205,  -205,   208,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,   123,  -205,  -205,
    -205,  -205,  -205,  -205,   192,   187,  -205,  -205,    62,  -205,
     212,   213,   214,   215,    45,  -205,  -205,  -205,  -205,    54,
     208,  -205,   193,   197,   205,   207,  -205,  -205,   218,   219,
     220,  -205,   134,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,   223,   188,   209,   211,   225,    54,
    -205,   216,  -205,  -205,  -205,   217,  -205,  -205,  -205
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    26,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      34,     5,     8,     7,    28,    21,     0,     0,    30,     0,
      29,     0,     0,    22,    36,     0,    38,    57,     0,    71,
      67,    69,   139,    60,    62,    64,     0,     0,    92,   185,
       0,    56,     0,    40,    43,    44,    46,    47,    48,    49,
      54,    55,    45,    52,    51,    50,    53,    27,    32,     0,
      19,    25,     0,    39,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    42,
       9,    31,    23,     0,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,    66,   111,     0,     0,    41,     0,
       0,    58,    73,    20,    68,    70,     0,    61,    63,    65,
       0,    94,     0,    24,     0,    78,     0,    74,    75,   151,
     154,   156,   158,   150,   149,   148,     0,   141,   144,   145,
     146,   147,   120,   122,   124,   119,     0,   113,   116,   117,
     118,    99,     0,    95,    96,   190,     0,   187,    37,     0,
      72,    77,     0,     0,     0,     0,   143,   140,     0,     0,
       0,   115,   112,     0,    93,    98,     0,   189,   186,    88,
      90,    87,    85,    86,     0,    80,    83,    84,    76,     0,
       0,     0,     0,   142,     0,     0,     0,   114,   107,   109,
     104,     0,   101,   105,   106,    97,   205,     0,   203,   201,
     199,   200,   195,     0,   192,   197,   198,   196,   188,     0,
       0,    82,    79,   153,   152,   155,   157,   160,     0,     0,
       0,     0,     0,   103,   100,     0,     0,     0,   194,   191,
       0,     0,    81,   165,     0,   161,   162,   134,   136,   133,
     131,   132,     0,   126,   129,   130,     0,     0,     0,     0,
     102,     0,   202,     0,   193,    89,    91,     0,   159,   164,
       0,     0,   128,   121,   123,   125,   108,   110,     0,   204,
     177,   179,   181,   183,   176,   174,   175,     0,   167,   170,
     171,   172,   173,   163,     0,     0,   127,   210,     0,   207,
       0,     0,     0,     0,   169,   166,   135,   138,   137,     0,
     209,   206,     0,     0,     0,     0,   168,   220,     0,     0,
       0,   225,     0,   212,   215,   216,   217,   218,   219,   208,
     178,   180,   182,   184,     0,     0,     0,     0,     0,   214,
     211,     0,   222,   223,   224,     0,   213,   221,   226
  };

  const short
  AgentParser::yypgoto_[] =
  {
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,   -17,   -95,
    -205,   -52,  -205,  -205,  -205,  -205,  -205,  -205,   -27,  -205,
    -205,  -205,  -205,  -205,   121,   145,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,   -26,  -205,   -25,  -205,
    -205,  -205,  -205,  -205,    71,  -205,  -205,    12,  -172,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,    60,  -205,  -205,     3,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,    66,  -205,  -205,
    -205,  -205,  -205,  -205,  -204,   -34,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,    73,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,   -19,  -205,  -205,   -61,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,    67,  -205,  -205,    10,  -205,  -205,  -205,  -205,  -205,
    -205,   -58,  -205,  -205,   -90,  -205,  -205,  -205,  -205,  -205,
    -205,  -205
  };

  const short
  AgentParser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,   114,    32,    33,    19,    24,    29,    30,   249,    21,
      26,    35,    72,    36,    52,    53,    54,    75,    55,    56,
      81,    57,    82,    58,    83,    59,   250,    78,   251,    79,
      62,    77,   126,   127,   128,   159,   184,   185,   186,   219,
     187,   220,    63,    86,   152,   153,   154,   173,   201,   202,
     203,   231,   204,   232,    64,   120,   146,   147,   148,   168,
     149,   169,   150,   170,   252,   253,   254,   270,   255,   271,
     308,    65,    80,   136,   137,   138,   162,   224,   139,   163,
     140,   164,   141,   165,   244,   245,   246,   267,   287,   288,
     289,   300,   290,   301,   291,   302,   292,   303,    66,    87,
     156,   157,   176,   213,   214,   215,   216,   237,   217,   235,
     298,   299,   309,   322,   323,   324,   334,   325,   326,   327,
     328,   338
  };

  const short
  AgentParser::yytable_[] =
  {
      51,    60,    61,   113,   212,     8,     9,    28,    10,    20,
      11,    37,    38,    39,    40,    41,   198,   199,    42,   198,
     199,    40,    41,   179,   180,   256,   257,    22,    43,    44,
      45,    46,    47,    50,    31,    34,    40,    41,    68,    48,
      67,   129,    49,   130,   131,   132,    40,    41,   179,    70,
     177,    91,    92,   178,    50,    12,    13,    14,    15,    40,
      41,    50,    51,    60,    61,   310,   212,    69,   311,   280,
     281,   282,   283,    40,    41,   206,    50,   207,   208,   142,
     143,   144,    73,    51,    60,    61,    50,    74,    71,   133,
     134,   135,   123,   145,    76,   247,   248,    84,   317,    50,
      50,   318,   319,   320,   321,    89,    89,   166,    96,   171,
      90,   158,   167,    50,   172,   221,   233,   238,   272,   272,
     222,   234,   239,   273,   274,   272,   304,     1,     2,     3,
     275,   305,   181,   182,   183,    85,    88,   339,    93,   133,
     134,   135,   340,    94,   145,    95,   200,    97,    98,   209,
     210,   211,    99,   100,   101,   102,   103,   104,   106,   107,
     105,   109,   111,   110,   113,   112,    10,   121,   116,   122,
     125,   115,   117,   118,   119,   151,   155,   160,   161,   174,
     175,   225,   189,   190,   191,   192,   194,   195,   196,   226,
     223,   227,   228,   236,   181,   182,   183,   229,   230,   240,
     241,   243,   258,   259,   261,   263,   269,   277,   268,   278,
     294,   209,   210,   211,   295,   297,   312,   313,   314,   315,
     262,   265,   335,   336,   337,   307,   266,   341,   276,   345,
     279,   124,   188,   242,   108,   205,   260,   197,   296,   193,
     284,   285,   286,   316,   218,   342,   306,   330,   264,   346,
     293,   331,   329,     0,     0,     0,     0,     0,     0,   332,
       0,   333,     0,     0,   343,     0,   344,     0,     0,     0,
     347,   348,     0,     0,     0,     0,     0,   284,   285,   286
  };

  const short
  AgentParser::yycheck_[] =
  {
      27,    27,    27,    98,   176,     0,     5,    24,     7,     7,
       9,    11,    12,    13,    14,    15,    40,    41,    18,    40,
      41,    14,    15,    16,    17,   229,   230,     7,    28,    29,
      30,    31,    32,    54,    54,    10,    14,    15,     3,    39,
       6,    19,    42,    21,    22,    23,    14,    15,    16,     8,
       3,    68,    69,     6,    54,    54,    55,    56,    57,    14,
      15,    54,    89,    89,    89,     3,   238,     4,     6,    24,
      25,    26,    27,    14,    15,    43,    54,    45,    46,    33,
      34,    35,     3,   110,   110,   110,    54,     8,     3,   116,
     116,   116,   109,   120,     4,    36,    37,     4,    44,    54,
      54,    47,    48,    49,    50,     3,     3,     3,    55,     3,
       8,     8,     8,    54,     8,     3,     3,     3,     3,     3,
       8,     8,     8,     8,     8,     3,     3,    51,    52,    53,
       8,     8,   159,   159,   159,     4,     4,     3,    54,   166,
     166,   166,     8,     4,   171,     4,   173,     4,     4,   176,
     176,   176,     4,     4,     4,     4,     4,    57,     4,     4,
       7,     4,    54,     7,   259,     5,     7,     5,     7,     5,
       7,    54,    54,    54,    54,     7,     7,     6,     3,     6,
       3,    54,     4,     4,     4,     4,     4,     4,     4,    54,
      20,     5,     7,     4,   221,   221,   221,     7,     7,     4,
       4,     7,     4,     4,     4,     4,     3,   259,     6,     5,
       4,   238,   238,   238,     4,     7,     4,     4,     4,     4,
      55,    54,     4,     4,     4,    38,    54,     4,    54,     4,
      54,   110,   161,   221,    89,   175,   233,   171,   272,   166,
     267,   267,   267,   304,   177,    57,    54,    54,   238,   339,
     269,    54,   310,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    54,    -1,    -1,    55,    -1,    55,    -1,    -1,    -1,
      54,    54,    -1,    -1,    -1,    -1,    -1,   304,   304,   304
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    51,    52,    53,    59,    60,    61,    62,     0,     5,
       7,     9,    54,    55,    56,    57,    65,    66,    67,    72,
       7,    77,     7,    63,    73,    68,    78,    64,    66,    74,
      75,    54,    70,    71,    10,    79,    81,    11,    12,    13,
      14,    15,    18,    28,    29,    30,    31,    32,    39,    42,
      54,    76,    82,    83,    84,    86,    87,    89,    91,    93,
      94,    96,    98,   110,   122,   139,   166,     6,     3,     4,
       8,     3,    80,     3,     8,    85,     4,    99,    95,    97,
     140,    88,    90,    92,     4,     4,   111,   167,     4,     3,
       8,    66,    66,    54,     4,     4,    55,     4,     4,     4,
       4,     4,     4,     4,    57,     7,     4,     4,    83,     4,
       7,    54,     5,    67,    69,    54,     7,    54,    54,    54,
     123,     5,     5,    66,    82,     7,   100,   101,   102,    19,
      21,    22,    23,    76,    94,    96,   141,   142,   143,   146,
     148,   150,    33,    34,    35,    76,   124,   125,   126,   128,
     130,     7,   112,   113,   114,     7,   168,   169,     8,   103,
       6,     3,   144,   147,   149,   151,     3,     8,   127,   129,
     131,     3,     8,   115,     6,     3,   170,     3,     6,    16,
      17,    76,    94,    96,   104,   105,   106,   108,   102,     4,
       4,     4,     4,   142,     4,     4,     4,   125,    40,    41,
      76,   116,   117,   118,   120,   114,    43,    45,    46,    76,
      94,    96,   106,   171,   172,   173,   174,   176,   169,   107,
     109,     3,     8,    20,   145,    54,    54,     5,     7,     7,
       7,   119,   121,     3,     8,   177,     4,   175,     3,     8,
       4,     4,   105,     7,   152,   153,   154,    36,    37,    76,
      94,    96,   132,   133,   134,   136,   132,   132,     4,     4,
     117,     4,    55,     4,   172,    54,    54,   155,     6,     3,
     135,   137,     3,     8,     8,     8,    54,    69,     5,    54,
      24,    25,    26,    27,    76,    94,    96,   156,   157,   158,
     160,   162,   164,   154,     4,     4,   133,     7,   178,   179,
     159,   161,   163,   165,     3,     8,    54,    38,   138,   180,
       3,     6,     4,     4,     4,     4,   157,    44,    47,    48,
      49,    50,   181,   182,   183,   185,   186,   187,   188,   179,
      54,    54,    54,    54,   184,     4,     4,     4,   189,     3,
       8,     4,    57,    55,    55,     4,   182,    54,    54
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    58,    60,    59,    61,    59,    62,    59,    64,    63,
      65,    66,    66,    66,    66,    66,    66,    66,    68,    67,
      69,    70,    70,    71,    71,    71,    73,    72,    74,    74,
      75,    75,    75,    76,    78,    77,    80,    79,    79,    81,
      82,    82,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    85,    84,    86,
      88,    87,    90,    89,    92,    91,    93,    95,    94,    97,
      96,    99,    98,   100,   100,   101,   101,   101,   103,   102,
     104,   104,   104,   105,   105,   105,   105,   105,   107,   106,
     109,   108,   111,   110,   112,   112,   113,   113,   113,   115,
     114,   116,   116,   116,   116,   117,   117,   119,   118,   121,
     120,   123,   122,   124,   124,   124,   125,   125,   125,   125,
     127,   126,   129,   128,   131,   130,   132,   132,   132,   133,
     133,   133,   133,   133,   135,   134,   137,   136,   138,   140,
     139,   141,   141,   141,   142,   142,   142,   142,   142,   142,
     142,   144,   143,   145,   147,   146,   149,   148,   151,   150,
     152,   152,   153,   153,   153,   155,   154,   156,   156,   156,
     157,   157,   157,   157,   157,   157,   157,   159,   158,   161,
     160,   163,   162,   165,   164,   167,   166,   168,   168,   168,
     170,   169,   171,   171,   171,   172,   172,   172,   172,   172,
     172,   172,   173,   175,   174,   177,   176,   178,   178,   178,
     180,   179,   181,   181,   181,   182,   182,   182,   182,   182,
     184,   183,   185,   186,   187,   189,   188
  };

  const signed char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     2,     0,     4,     0,     1,
       1,     3,     2,     2,     0,     4,     0,     6,     1,     2,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       0,     6,     0,     6,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     1,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
  };


#if AGENT_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const AgentParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Control-agent\"",
  "\"http-host\"", "\"http-port\"", "\"http-headers\"", "\"user-context\"",
  "\"comment\"", "\"name\"", "\"value\"", "\"authentication\"", "\"type\"",
  "\"basic\"", "\"realm\"", "\"directory\"", "\"clients\"", "\"user\"",
  "\"user-file\"", "\"password\"", "\"password-file\"", "\"trust-anchor\"",
  "\"cert-file\"", "\"key-file\"", "\"cert-required\"",
  "\"control-sockets\"", "\"dhcp4\"", "\"dhcp6\"", "\"d2\"",
  "\"socket-name\"", "\"socket-type\"", "\"unix\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"loggers\"", "\"output-options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "START_JSON", "START_AGENT",
  "START_SUB_AGENT", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "sub_agent", "$@4", "json", "value", "map", "$@5", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@6", "list_content",
  "not_empty_list", "unknown_map_entry", "agent_syntax_map", "$@7",
  "global_object", "$@8", "global_object_comma", "global_params",
  "global_param", "http_host", "$@9", "http_port", "trust_anchor", "$@10",
  "cert_file", "$@11", "key_file", "$@12", "cert_required", "user_context",
  "$@13", "comment", "$@14", "http_headers", "$@15", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@16",
  "http_header_params", "http_header_param", "name", "$@17",
  "header_value", "$@18", "hooks_libraries", "$@19",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@20", "hooks_params", "hooks_param", "library",
  "$@21", "parameters", "$@22", "control_sockets", "$@23",
  "control_sockets_params", "control_socket", "dhcp4_server_socket",
  "$@24", "dhcp6_server_socket", "$@25", "d2_server_socket", "$@26",
  "control_socket_params", "control_socket_param", "socket_name", "$@27",
  "socket_type", "$@28", "socket_type_value", "authentication", "$@29",
  "auth_params", "auth_param", "auth_type", "$@30", "auth_type_value",
  "realm", "$@31", "directory", "$@32", "clients", "$@33", "clients_list",
  "not_empty_clients_list", "basic_auth", "$@34", "clients_params",
  "clients_param", "user", "$@35", "user_file", "$@36", "password", "$@37",
  "password_file", "$@38", "loggers", "$@39", "loggers_entries",
  "logger_entry", "$@40", "logger_params", "logger_param", "debuglevel",
  "severity", "$@41", "output_options_list", "$@42",
  "output_options_list_content", "output_entry", "$@43",
  "output_params_list", "output_params", "output", "$@44", "flush",
  "maxsize", "maxver", "pattern", "$@45", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   135,   135,   135,   136,   136,   137,   137,   145,   145,
     156,   162,   163,   164,   165,   166,   167,   168,   172,   172,
     183,   188,   189,   197,   202,   208,   213,   213,   219,   220,
     223,   227,   231,   243,   251,   251,   263,   263,   279,   282,
     286,   287,   288,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   311,   311,   320,
     326,   326,   335,   335,   344,   344,   353,   359,   359,   384,
     384,   411,   411,   422,   423,   426,   427,   428,   433,   433,
     441,   442,   443,   448,   449,   450,   451,   452,   455,   455,
     464,   464,   474,   474,   485,   486,   489,   490,   491,   496,
     496,   504,   505,   506,   509,   512,   513,   516,   516,   525,
     525,   536,   536,   550,   551,   552,   559,   560,   561,   562,
     566,   566,   578,   578,   590,   590,   602,   603,   604,   610,
     611,   612,   613,   614,   618,   618,   628,   628,   637,   644,
     644,   657,   658,   659,   664,   665,   666,   667,   668,   669,
     670,   673,   673,   681,   684,   684,   693,   693,   702,   702,
     713,   714,   717,   718,   719,   724,   724,   732,   733,   734,
     739,   740,   741,   742,   743,   744,   745,   748,   748,   757,
     757,   766,   766,   775,   775,   788,   788,   801,   802,   803,
     809,   809,   817,   818,   819,   824,   825,   826,   827,   828,
     829,   830,   833,   839,   839,   848,   848,   859,   860,   861,
     866,   866,   874,   875,   876,   881,   882,   883,   884,   885,
     888,   888,   897,   903,   909,   915,   915
  };

  void
  AgentParser::yy_stack_print_ () const
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
  AgentParser::yy_reduce_print_ (int yyrule) const
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
#endif // AGENT_DEBUG


#line 14 "agent_parser.yy"
} } // isc::agent
#line 2643 "agent_parser.cc"

#line 924 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
