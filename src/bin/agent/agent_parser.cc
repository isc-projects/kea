// A Bison parser, made by GNU Bison 3.7.1.

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
#define yylex   agent_lex



#include "agent_parser.h"


// Unqualified %code blocks.
#line 33 "agent_parser.yy"

#include <agent/parser_context.h>

#line 52 "agent_parser.cc"


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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
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
#line 145 "agent_parser.cc"

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

  /*---------------.
  | symbol kinds.  |
  `---------------*/



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
#line 99 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 384 "agent_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 99 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 390 "agent_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 99 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 396 "agent_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 99 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 402 "agent_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 99 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 408 "agent_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 99 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "agent_parser.cc"
        break;

      case symbol_kind::S_socket_type_value: // socket_type_value
#line 99 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 420 "agent_parser.cc"
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
  AgentParser::yypop_ (int n)
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
  AgentParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  AgentParser::yy_table_value_is_error_ (int yyvalue)
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
#line 110 "agent_parser.yy"
                       { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 695 "agent_parser.cc"
    break;

  case 4: // $@2: %empty
#line 111 "agent_parser.yy"
                       { ctx.ctx_ = ctx.CONFIG; }
#line 701 "agent_parser.cc"
    break;

  case 6: // $@3: %empty
#line 112 "agent_parser.yy"
                       { ctx.ctx_ = ctx.AGENT; }
#line 707 "agent_parser.cc"
    break;

  case 8: // $@4: %empty
#line 120 "agent_parser.yy"
                          {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 717 "agent_parser.cc"
    break;

  case 9: // sub_agent: "{" $@4 global_params "}"
#line 124 "agent_parser.yy"
                               {
    // parsing completed
}
#line 725 "agent_parser.cc"
    break;

  case 10: // json: value
#line 131 "agent_parser.yy"
            {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 734 "agent_parser.cc"
    break;

  case 11: // value: "integer"
#line 137 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 740 "agent_parser.cc"
    break;

  case 12: // value: "floating point"
#line 138 "agent_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 746 "agent_parser.cc"
    break;

  case 13: // value: "boolean"
#line 139 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "agent_parser.cc"
    break;

  case 14: // value: "constant string"
#line 140 "agent_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "agent_parser.cc"
    break;

  case 15: // value: "null"
#line 141 "agent_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 764 "agent_parser.cc"
    break;

  case 16: // value: map
#line 142 "agent_parser.yy"
           { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 770 "agent_parser.cc"
    break;

  case 17: // value: list_generic
#line 143 "agent_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 776 "agent_parser.cc"
    break;

  case 18: // $@5: %empty
#line 147 "agent_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 787 "agent_parser.cc"
    break;

  case 19: // map: "{" $@5 map_content "}"
#line 152 "agent_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 797 "agent_parser.cc"
    break;

  case 20: // map_value: map
#line 158 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 803 "agent_parser.cc"
    break;

  case 23: // not_empty_map: "constant string" ":" value
#line 172 "agent_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 813 "agent_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 177 "agent_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 824 "agent_parser.cc"
    break;

  case 25: // $@6: %empty
#line 185 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 833 "agent_parser.cc"
    break;

  case 26: // list_generic: "[" $@6 list_content "]"
#line 188 "agent_parser.yy"
                               {
}
#line 840 "agent_parser.cc"
    break;

  case 29: // not_empty_list: value
#line 195 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 849 "agent_parser.cc"
    break;

  case 30: // not_empty_list: not_empty_list "," value
#line 199 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 858 "agent_parser.cc"
    break;

  case 31: // unknown_map_entry: "constant string" ":"
#line 212 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 869 "agent_parser.cc"
    break;

  case 32: // $@7: %empty
#line 220 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 880 "agent_parser.cc"
    break;

  case 33: // agent_syntax_map: "{" $@7 global_object "}"
#line 225 "agent_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 890 "agent_parser.cc"
    break;

  case 34: // $@8: %empty
#line 232 "agent_parser.yy"
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
#line 907 "agent_parser.cc"
    break;

  case 35: // global_object: "Control-agent" $@8 ":" "{" global_params "}"
#line 243 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 918 "agent_parser.cc"
    break;

  case 46: // $@9: %empty
#line 266 "agent_parser.yy"
                     {
    ctx.unique("http-host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 927 "agent_parser.cc"
    break;

  case 47: // http_host: "http-host" $@9 ":" "constant string"
#line 269 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 937 "agent_parser.cc"
    break;

  case 48: // http_port: "http-port" ":" "integer"
#line 275 "agent_parser.yy"
                                   {
    ctx.unique("http-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 947 "agent_parser.cc"
    break;

  case 49: // $@10: %empty
#line 281 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 955 "agent_parser.cc"
    break;

  case 50: // user_context: "user-context" $@10 ":" map_value
#line 283 "agent_parser.yy"
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
#line 982 "agent_parser.cc"
    break;

  case 51: // $@11: %empty
#line 306 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 990 "agent_parser.cc"
    break;

  case 52: // comment: "comment" $@11 ":" "constant string"
#line 308 "agent_parser.yy"
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
#line 1019 "agent_parser.cc"
    break;

  case 53: // $@12: %empty
#line 334 "agent_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1031 "agent_parser.cc"
    break;

  case 54: // hooks_libraries: "hooks-libraries" $@12 ":" "[" hooks_libraries_list "]"
#line 340 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1040 "agent_parser.cc"
    break;

  case 59: // $@13: %empty
#line 353 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1050 "agent_parser.cc"
    break;

  case 60: // hooks_library: "{" $@13 hooks_params "}"
#line 357 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1058 "agent_parser.cc"
    break;

  case 66: // $@14: %empty
#line 370 "agent_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1067 "agent_parser.cc"
    break;

  case 67: // library: "library" $@14 ":" "constant string"
#line 373 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1077 "agent_parser.cc"
    break;

  case 68: // $@15: %empty
#line 379 "agent_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1086 "agent_parser.cc"
    break;

  case 69: // parameters: "parameters" $@15 ":" map_value
#line 382 "agent_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1095 "agent_parser.cc"
    break;

  case 70: // $@16: %empty
#line 390 "agent_parser.yy"
                                                      {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[2].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1107 "agent_parser.cc"
    break;

  case 71: // control_sockets: "control-sockets" ":" "{" $@16 control_sockets_params "}"
#line 396 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1116 "agent_parser.cc"
    break;

  case 78: // $@17: %empty
#line 417 "agent_parser.yy"
                                  {
    ctx.unique("dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1128 "agent_parser.cc"
    break;

  case 79: // dhcp4_server_socket: "dhcp4" $@17 ":" "{" control_socket_params "}"
#line 423 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1137 "agent_parser.cc"
    break;

  case 80: // $@18: %empty
#line 429 "agent_parser.yy"
                                  {
    ctx.unique("dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1149 "agent_parser.cc"
    break;

  case 81: // dhcp6_server_socket: "dhcp6" $@18 ":" "{" control_socket_params "}"
#line 435 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1158 "agent_parser.cc"
    break;

  case 82: // $@19: %empty
#line 441 "agent_parser.yy"
                            {
    ctx.unique("d2", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1170 "agent_parser.cc"
    break;

  case 83: // d2_server_socket: "d2" $@19 ":" "{" control_socket_params "}"
#line 447 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1179 "agent_parser.cc"
    break;

  case 91: // $@20: %empty
#line 466 "agent_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1188 "agent_parser.cc"
    break;

  case 92: // socket_name: "socket-name" $@20 ":" "constant string"
#line 469 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1198 "agent_parser.cc"
    break;

  case 93: // $@21: %empty
#line 476 "agent_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1207 "agent_parser.cc"
    break;

  case 94: // socket_type: "socket-type" $@21 ":" socket_type_value
#line 479 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1216 "agent_parser.cc"
    break;

  case 95: // socket_type_value: "unix"
#line 485 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1222 "agent_parser.cc"
    break;

  case 96: // $@22: %empty
#line 492 "agent_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1234 "agent_parser.cc"
    break;

  case 97: // loggers: "loggers" $@22 ":" "[" loggers_entries "]"
#line 498 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1243 "agent_parser.cc"
    break;

  case 100: // $@23: %empty
#line 510 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1253 "agent_parser.cc"
    break;

  case 101: // logger_entry: "{" $@23 logger_params "}"
#line 514 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1261 "agent_parser.cc"
    break;

  case 111: // $@24: %empty
#line 531 "agent_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1270 "agent_parser.cc"
    break;

  case 112: // name: "name" $@24 ":" "constant string"
#line 534 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1280 "agent_parser.cc"
    break;

  case 113: // debuglevel: "debuglevel" ":" "integer"
#line 540 "agent_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1290 "agent_parser.cc"
    break;

  case 114: // $@25: %empty
#line 546 "agent_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1299 "agent_parser.cc"
    break;

  case 115: // severity: "severity" $@25 ":" "constant string"
#line 549 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1309 "agent_parser.cc"
    break;

  case 116: // $@26: %empty
#line 555 "agent_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1321 "agent_parser.cc"
    break;

  case 117: // output_options_list: "output_options" $@26 ":" "[" output_options_list_content "]"
#line 561 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1330 "agent_parser.cc"
    break;

  case 120: // $@27: %empty
#line 570 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1340 "agent_parser.cc"
    break;

  case 121: // output_entry: "{" $@27 output_params_list "}"
#line 574 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1348 "agent_parser.cc"
    break;

  case 129: // $@28: %empty
#line 589 "agent_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1357 "agent_parser.cc"
    break;

  case 130: // output: "output" $@28 ":" "constant string"
#line 592 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1367 "agent_parser.cc"
    break;

  case 131: // flush: "flush" ":" "boolean"
#line 598 "agent_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1377 "agent_parser.cc"
    break;

  case 132: // maxsize: "maxsize" ":" "integer"
#line 604 "agent_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1387 "agent_parser.cc"
    break;

  case 133: // maxver: "maxver" ":" "integer"
#line 610 "agent_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1397 "agent_parser.cc"
    break;

  case 134: // $@29: %empty
#line 616 "agent_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1406 "agent_parser.cc"
    break;

  case 135: // pattern: "pattern" $@29 ":" "constant string"
#line 619 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1416 "agent_parser.cc"
    break;


#line 1420 "agent_parser.cc"

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


  const signed char AgentParser::yypact_ninf_ = -75;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
     -18,   -75,   -75,   -75,     6,     0,     1,    27,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,     0,     8,    60,    -1,   -75,    80,
      45,    86,    83,    93,   -75,    89,   -75,    96,   -75,   -75,
      97,   -75,   -75,    98,   -75,    17,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,     0,     0,   -75,    65,   100,
     -75,   101,    67,   103,   104,   102,   106,   107,   -75,    -1,
     -75,   -75,   -75,   108,   109,    77,   -75,   110,    81,   -75,
     113,   115,   -75,     0,    -1,   -75,   -75,   -75,   -75,    15,
     114,   116,   -75,    42,   -75,   -75,   -75,   -75,    46,   -75,
     -75,   -75,   -75,   -75,   118,   111,   -75,   -75,    82,   -75,
     -75,   121,   122,   123,    15,   -75,    -8,   -75,   114,    38,
     116,   -75,   124,   128,   129,   -75,   -75,   -75,   -75,    52,
     -75,   -75,   -75,   -75,   -75,   -75,   125,   -75,   -75,   -75,
     -75,    53,   -75,   -75,   -75,   -75,   -75,   -75,     9,     9,
       9,   126,   133,     3,   -75,   134,   135,   105,   136,    38,
     -75,   -75,   -75,   -75,   -75,   -75,    63,   -75,   -75,   -75,
      74,    75,    84,   110,   -75,    90,   137,   -75,   112,   -75,
     139,   141,     9,   -75,   -75,   -75,   -75,   -75,   -75,   140,
     -75,   117,   120,   -75,   -75,    92,   -75,   -75,   -75,   -75,
      41,   140,   -75,   -75,   142,   144,   145,   -75,    76,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   147,    72,   119,   127,
     148,    41,   -75,   130,   -75,   -75,   -75,   131,   -75,   -75,
     -75
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    34,     0,    46,     0,    49,    51,
       0,    53,    96,     0,    45,     0,    36,    38,    39,    43,
      44,    41,    40,    42,    26,     0,     0,    19,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       9,    30,    23,     0,     0,     0,    48,     0,     0,    70,
       0,     0,    37,     0,     0,    47,    20,    50,    52,     0,
      55,     0,    24,     0,    78,    80,    82,    77,     0,    72,
      74,    75,    76,    59,     0,    56,    57,   100,     0,    98,
      35,     0,     0,     0,     0,    71,     0,    54,     0,     0,
       0,    97,     0,     0,     0,    73,    66,    68,    63,     0,
      61,    64,    65,    58,   111,   116,     0,   114,   110,   108,
     109,     0,   102,   104,   106,   107,   105,    99,     0,     0,
       0,     0,     0,     0,    60,     0,     0,     0,     0,     0,
     101,    91,    93,    90,    88,    89,     0,    84,    86,    87,
       0,     0,     0,     0,    62,     0,     0,   113,     0,   103,
       0,     0,     0,    79,    81,    83,    67,    69,   112,     0,
     115,     0,     0,    85,   120,     0,   118,    92,    95,    94,
       0,     0,   117,   129,     0,     0,     0,   134,     0,   122,
     124,   125,   126,   127,   128,   119,     0,     0,     0,     0,
       0,     0,   121,     0,   131,   132,   133,     0,   123,   130,
     135
  };

  const signed char
  AgentParser::yypgoto_[] =
  {
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -20,   -74,
     -75,   -19,   -75,   -75,   -75,   -75,   -75,   -75,   -27,   -75,
     -75,   -75,   -75,    69,    87,   -75,   -75,   -75,   -26,   -75,
     -25,   -75,   -75,   -75,   -75,   -75,    39,   -75,   -75,     7,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,    47,   -75,   -75,
     -75,   -75,   -75,   -75,   -69,   -23,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,    43,   -75,   -75,     5,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -39,   -75,   -75,   -56,
     -75,   -75,   -75,   -75,   -75,   -75,   -75
  };

  const short
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    87,    32,    33,    19,    24,    29,    30,   163,    21,
      26,    35,    59,    45,    46,    47,    61,    48,   164,    63,
     165,    64,    51,    66,   104,   105,   106,   116,   129,   130,
     131,   151,   132,   152,    52,    89,    98,    99,   100,   111,
     101,   112,   102,   113,   166,   167,   168,   180,   169,   181,
     199,    53,    67,   108,   109,   119,   141,   142,   143,   155,
     144,   145,   158,   146,   156,   195,   196,   200,   208,   209,
     210,   216,   211,   212,   213,   214,   220
  };

  const unsigned char
  AgentParser::yytable_[] =
  {
      44,    49,    50,    86,    28,     9,     8,    10,    20,    11,
      36,    37,    38,    39,    40,   126,   127,     1,     2,     3,
      69,    41,    38,    39,    42,    70,   126,   127,   161,   162,
      43,    94,    95,    96,    22,    71,    72,    43,    12,    13,
      14,    15,    44,    49,    50,    69,    31,    43,    55,   114,
     110,    38,    39,    43,   115,   153,   159,    44,    49,    50,
     154,   160,    97,    92,   134,   135,   182,   136,   137,   203,
      34,   183,   204,   205,   206,   207,    43,   182,   182,   221,
     170,   171,   184,   185,   222,   120,    54,    97,   121,   128,
      56,    57,   138,   139,   140,   201,    58,    60,   202,    86,
      62,    65,    68,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    83,   224,   118,    85,    84,    10,    90,    88,
      91,   103,   186,   107,   117,   122,   123,   124,   188,   157,
     172,   148,   138,   139,   140,   149,   150,   173,   175,   176,
     178,   198,   189,   191,   177,   192,   217,   194,   218,   219,
     190,   223,   227,    93,   187,   197,    82,   133,   225,   193,
     174,   125,   215,   147,   179,   228,   226,     0,   229,   230
  };

  const short
  AgentParser::yycheck_[] =
  {
      27,    27,    27,    77,    24,     5,     0,     7,     7,     9,
      11,    12,    13,    14,    15,    23,    24,    35,    36,    37,
       3,    22,    13,    14,    25,     8,    23,    24,    19,    20,
      38,    16,    17,    18,     7,    55,    56,    38,    38,    39,
      40,    41,    69,    69,    69,     3,    38,    38,     3,     3,
       8,    13,    14,    38,     8,     3,     3,    84,    84,    84,
       8,     8,    89,    83,    26,    27,     3,    29,    30,    28,
      10,     8,    31,    32,    33,    34,    38,     3,     3,     3,
     149,   150,     8,     8,     8,     3,     6,   114,     6,   116,
       4,     8,   119,   119,   119,     3,     3,     8,     6,   173,
       4,     4,     4,    38,     4,     4,    39,     4,     4,     7,
       4,     4,     4,    41,     3,    38,     7,     7,     5,    38,
       5,     7,    38,     7,     6,     4,     4,     4,    38,     4,
       4,     7,   159,   159,   159,     7,     7,     4,     4,     4,
       4,    21,     5,     4,    39,     4,     4,     7,     4,     4,
      38,     4,     4,    84,   173,    38,    69,   118,    39,   182,
     153,   114,   201,   120,   159,   221,    39,    -1,    38,    38
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    35,    36,    37,    43,    44,    45,    46,     0,     5,
       7,     9,    38,    39,    40,    41,    49,    50,    51,    56,
       7,    61,     7,    47,    57,    52,    62,    48,    50,    58,
      59,    38,    54,    55,    10,    63,    11,    12,    13,    14,
      15,    22,    25,    38,    60,    65,    66,    67,    69,    70,
      72,    74,    86,   103,     6,     3,     4,     8,     3,    64,
       8,    68,     4,    71,    73,     4,    75,   104,     4,     3,
       8,    50,    50,    38,     4,     4,    39,     4,     4,     7,
       4,     4,    66,     4,     7,    38,    51,    53,    38,    87,
       5,     5,    50,    65,    16,    17,    18,    60,    88,    89,
      90,    92,    94,     7,    76,    77,    78,     7,   105,   106,
       8,    91,    93,    95,     3,     8,    79,     6,     3,   107,
       3,     6,     4,     4,     4,    89,    23,    24,    60,    80,
      81,    82,    84,    78,    26,    27,    29,    30,    60,    70,
      72,   108,   109,   110,   112,   113,   115,   106,     7,     7,
       7,    83,    85,     3,     8,   111,   116,     4,   114,     3,
       8,    19,    20,    60,    70,    72,    96,    97,    98,   100,
      96,    96,     4,     4,    81,     4,     4,    39,     4,   109,
      99,   101,     3,     8,     8,     8,    38,    53,    38,     5,
      38,     4,     4,    97,     7,   117,   118,    38,    21,   102,
     119,     3,     6,    28,    31,    32,    33,    34,   120,   121,
     122,   124,   125,   126,   127,   118,   123,     4,     4,     4,
     128,     3,     8,     4,    41,    39,    39,     4,   121,    38,
      38
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    42,    44,    43,    45,    43,    46,    43,    48,    47,
      49,    50,    50,    50,    50,    50,    50,    50,    52,    51,
      53,    54,    54,    55,    55,    57,    56,    58,    58,    59,
      59,    60,    62,    61,    64,    63,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    68,    67,    69,    71,
      70,    73,    72,    75,    74,    76,    76,    77,    77,    79,
      78,    80,    80,    80,    81,    81,    83,    82,    85,    84,
      87,    86,    88,    88,    89,    89,    89,    89,    91,    90,
      93,    92,    95,    94,    96,    96,    97,    97,    97,    97,
      97,    99,    98,   101,   100,   102,   104,   103,   105,   105,
     107,   106,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   111,   110,   112,   114,   113,   116,   115,   117,   117,
     119,   118,   120,   120,   121,   121,   121,   121,   121,   123,
     122,   124,   125,   126,   128,   127
  };

  const signed char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       0,     6,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4
  };


#if AGENT_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const AgentParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Control-agent\"",
  "\"http-host\"", "\"http-port\"", "\"user-context\"", "\"comment\"",
  "\"control-sockets\"", "\"dhcp4\"", "\"dhcp6\"", "\"d2\"",
  "\"socket-name\"", "\"socket-type\"", "\"unix\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"loggers\"", "\"name\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"", "START_JSON",
  "START_AGENT", "START_SUB_AGENT", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "sub_agent", "$@4", "json", "value", "map", "$@5", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@6", "list_content",
  "not_empty_list", "unknown_map_entry", "agent_syntax_map", "$@7",
  "global_object", "$@8", "global_params", "global_param", "http_host",
  "$@9", "http_port", "user_context", "$@10", "comment", "$@11",
  "hooks_libraries", "$@12", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@13",
  "hooks_params", "hooks_param", "library", "$@14", "parameters", "$@15",
  "control_sockets", "$@16", "control_sockets_params", "control_socket",
  "dhcp4_server_socket", "$@17", "dhcp6_server_socket", "$@18",
  "d2_server_socket", "$@19", "control_socket_params",
  "control_socket_param", "socket_name", "$@20", "socket_type", "$@21",
  "socket_type_value", "loggers", "$@22", "loggers_entries",
  "logger_entry", "$@23", "logger_params", "logger_param", "name", "$@24",
  "debuglevel", "severity", "$@25", "output_options_list", "$@26",
  "output_options_list_content", "output_entry", "$@27",
  "output_params_list", "output_params", "output", "$@28", "flush",
  "maxsize", "maxver", "pattern", "$@29", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   110,   110,   110,   111,   111,   112,   112,   120,   120,
     131,   137,   138,   139,   140,   141,   142,   143,   147,   147,
     158,   163,   164,   172,   177,   185,   185,   191,   192,   195,
     199,   212,   220,   220,   232,   232,   250,   251,   256,   257,
     258,   259,   260,   261,   262,   263,   266,   266,   275,   281,
     281,   306,   306,   334,   334,   345,   346,   349,   350,   353,
     353,   361,   362,   363,   366,   367,   370,   370,   379,   379,
     390,   390,   404,   405,   410,   411,   412,   413,   417,   417,
     429,   429,   441,   441,   453,   454,   458,   459,   460,   461,
     462,   466,   466,   476,   476,   485,   492,   492,   505,   506,
     510,   510,   518,   519,   522,   523,   524,   525,   526,   527,
     528,   531,   531,   540,   546,   546,   555,   555,   566,   567,
     570,   570,   578,   579,   582,   583,   584,   585,   586,   589,
     589,   598,   604,   610,   616,   616
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
#line 2059 "agent_parser.cc"

#line 625 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
