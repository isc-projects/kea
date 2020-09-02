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
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 812 "agent_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 176 "agent_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 822 "agent_parser.cc"
    break;

  case 25: // $@6: %empty
#line 183 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 831 "agent_parser.cc"
    break;

  case 26: // list_generic: "[" $@6 list_content "]"
#line 186 "agent_parser.yy"
                               {
}
#line 838 "agent_parser.cc"
    break;

  case 29: // not_empty_list: value
#line 193 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 847 "agent_parser.cc"
    break;

  case 30: // not_empty_list: not_empty_list "," value
#line 197 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 856 "agent_parser.cc"
    break;

  case 31: // unknown_map_entry: "constant string" ":"
#line 210 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 867 "agent_parser.cc"
    break;

  case 32: // $@7: %empty
#line 218 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 878 "agent_parser.cc"
    break;

  case 33: // agent_syntax_map: "{" $@7 global_objects "}"
#line 223 "agent_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 888 "agent_parser.cc"
    break;

  case 36: // $@8: %empty
#line 238 "agent_parser.yy"
                            {

    // Let's create a MapElement that will represent it, add it to the
    // top level map (that's already on the stack) and put the new map
    // on the stack as well, so child elements will be able to add
    // themselves to it.
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Control-agent", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AGENT);
}
#line 904 "agent_parser.cc"
    break;

  case 37: // agent_object: "Control-agent" $@8 ":" "{" global_params "}"
#line 248 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 915 "agent_parser.cc"
    break;

  case 48: // $@9: %empty
#line 271 "agent_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 923 "agent_parser.cc"
    break;

  case 49: // http_host: "http-host" $@9 ":" "constant string"
#line 273 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 933 "agent_parser.cc"
    break;

  case 50: // http_port: "http-port" ":" "integer"
#line 279 "agent_parser.yy"
                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 942 "agent_parser.cc"
    break;

  case 51: // $@10: %empty
#line 284 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 950 "agent_parser.cc"
    break;

  case 52: // user_context: "user-context" $@10 ":" map_value
#line 286 "agent_parser.yy"
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
#line 977 "agent_parser.cc"
    break;

  case 53: // $@11: %empty
#line 309 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 985 "agent_parser.cc"
    break;

  case 54: // comment: "comment" $@11 ":" "constant string"
#line 311 "agent_parser.yy"
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
#line 1014 "agent_parser.cc"
    break;

  case 55: // $@12: %empty
#line 337 "agent_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1025 "agent_parser.cc"
    break;

  case 56: // hooks_libraries: "hooks-libraries" $@12 ":" "[" hooks_libraries_list "]"
#line 342 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1034 "agent_parser.cc"
    break;

  case 61: // $@13: %empty
#line 355 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1044 "agent_parser.cc"
    break;

  case 62: // hooks_library: "{" $@13 hooks_params "}"
#line 359 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1052 "agent_parser.cc"
    break;

  case 68: // $@14: %empty
#line 372 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1060 "agent_parser.cc"
    break;

  case 69: // library: "library" $@14 ":" "constant string"
#line 374 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1070 "agent_parser.cc"
    break;

  case 70: // $@15: %empty
#line 380 "agent_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1078 "agent_parser.cc"
    break;

  case 71: // parameters: "parameters" $@15 ":" map_value
#line 382 "agent_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1087 "agent_parser.cc"
    break;

  case 72: // $@16: %empty
#line 390 "agent_parser.yy"
                                                      {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1098 "agent_parser.cc"
    break;

  case 73: // control_sockets: "control-sockets" ":" "{" $@16 control_sockets_params "}"
#line 395 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "agent_parser.cc"
    break;

  case 80: // $@17: %empty
#line 416 "agent_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1118 "agent_parser.cc"
    break;

  case 81: // dhcp4_server_socket: "dhcp4" $@17 ":" "{" control_socket_params "}"
#line 421 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1127 "agent_parser.cc"
    break;

  case 82: // $@18: %empty
#line 427 "agent_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1138 "agent_parser.cc"
    break;

  case 83: // dhcp6_server_socket: "dhcp6" $@18 ":" "{" control_socket_params "}"
#line 432 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1147 "agent_parser.cc"
    break;

  case 84: // $@19: %empty
#line 438 "agent_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1158 "agent_parser.cc"
    break;

  case 85: // d2_server_socket: "d2" $@19 ":" "{" control_socket_params "}"
#line 443 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1167 "agent_parser.cc"
    break;

  case 93: // $@20: %empty
#line 462 "agent_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1175 "agent_parser.cc"
    break;

  case 94: // socket_name: "socket-name" $@20 ":" "constant string"
#line 464 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1185 "agent_parser.cc"
    break;

  case 95: // $@21: %empty
#line 471 "agent_parser.yy"
                         {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1193 "agent_parser.cc"
    break;

  case 96: // socket_type: "socket-type" $@21 ":" socket_type_value
#line 473 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1202 "agent_parser.cc"
    break;

  case 97: // socket_type_value: "unix"
#line 479 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1208 "agent_parser.cc"
    break;

  case 98: // $@22: %empty
#line 486 "agent_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1219 "agent_parser.cc"
    break;

  case 99: // loggers: "loggers" $@22 ":" "[" loggers_entries "]"
#line 491 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1228 "agent_parser.cc"
    break;

  case 102: // $@23: %empty
#line 503 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1238 "agent_parser.cc"
    break;

  case 103: // logger_entry: "{" $@23 logger_params "}"
#line 507 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1246 "agent_parser.cc"
    break;

  case 113: // $@24: %empty
#line 524 "agent_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1254 "agent_parser.cc"
    break;

  case 114: // name: "name" $@24 ":" "constant string"
#line 526 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1264 "agent_parser.cc"
    break;

  case 115: // debuglevel: "debuglevel" ":" "integer"
#line 532 "agent_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1273 "agent_parser.cc"
    break;

  case 116: // $@25: %empty
#line 537 "agent_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1281 "agent_parser.cc"
    break;

  case 117: // severity: "severity" $@25 ":" "constant string"
#line 539 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1291 "agent_parser.cc"
    break;

  case 118: // $@26: %empty
#line 545 "agent_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1302 "agent_parser.cc"
    break;

  case 119: // output_options_list: "output_options" $@26 ":" "[" output_options_list_content "]"
#line 550 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1311 "agent_parser.cc"
    break;

  case 122: // $@27: %empty
#line 559 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1321 "agent_parser.cc"
    break;

  case 123: // output_entry: "{" $@27 output_params_list "}"
#line 563 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1329 "agent_parser.cc"
    break;

  case 131: // $@28: %empty
#line 578 "agent_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1337 "agent_parser.cc"
    break;

  case 132: // output: "output" $@28 ":" "constant string"
#line 580 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1347 "agent_parser.cc"
    break;

  case 133: // flush: "flush" ":" "boolean"
#line 586 "agent_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1356 "agent_parser.cc"
    break;

  case 134: // maxsize: "maxsize" ":" "integer"
#line 591 "agent_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1365 "agent_parser.cc"
    break;

  case 135: // maxver: "maxver" ":" "integer"
#line 596 "agent_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1374 "agent_parser.cc"
    break;

  case 136: // $@29: %empty
#line 601 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1382 "agent_parser.cc"
    break;

  case 137: // pattern: "pattern" $@29 ":" "constant string"
#line 603 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1392 "agent_parser.cc"
    break;


#line 1396 "agent_parser.cc"

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


  const short AgentParser::yypact_ninf_ = -128;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      65,  -128,  -128,  -128,     7,     1,    -2,     8,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,     1,    -6,    52,     5,  -128,    44,
      70,    80,    75,    87,  -128,    84,  -128,  -128,  -128,    89,
    -128,  -128,    93,  -128,  -128,    94,  -128,     6,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,     1,     1,  -128,
      66,    99,  -128,   101,    67,   103,   104,   102,   106,   107,
    -128,     5,  -128,  -128,  -128,   108,   109,    76,  -128,   110,
      77,  -128,   113,   114,  -128,     1,     5,  -128,  -128,  -128,
    -128,    -5,   115,   116,  -128,    18,  -128,  -128,  -128,  -128,
      28,  -128,  -128,  -128,  -128,  -128,   118,   117,  -128,  -128,
      45,  -128,  -128,   121,   122,   123,    -5,  -128,    11,  -128,
     115,    40,   116,  -128,   124,   125,   126,  -128,  -128,  -128,
    -128,    60,  -128,  -128,  -128,  -128,  -128,  -128,   133,  -128,
    -128,  -128,  -128,    68,  -128,  -128,  -128,  -128,  -128,  -128,
       9,     9,     9,   134,   135,    64,  -128,   136,   137,    74,
     138,    40,  -128,  -128,  -128,  -128,  -128,  -128,    69,  -128,
    -128,  -128,    71,    72,    83,   110,  -128,    90,   139,  -128,
      91,  -128,   141,   142,     9,  -128,  -128,  -128,  -128,  -128,
    -128,   140,  -128,    92,   127,  -128,  -128,    79,  -128,  -128,
    -128,  -128,    24,   140,  -128,  -128,   145,   146,   147,  -128,
      78,  -128,  -128,  -128,  -128,  -128,  -128,  -128,   148,   112,
     119,   120,   150,    24,  -128,   105,  -128,  -128,  -128,   128,
    -128,  -128,  -128
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    36,     0,    34,    35,    48,     0,
      51,    53,     0,    55,    98,     0,    47,     0,    38,    40,
      41,    45,    46,    43,    42,    44,    26,     0,     0,    19,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     9,    30,    23,     0,     0,     0,    50,     0,
       0,    72,     0,     0,    39,     0,     0,    49,    20,    52,
      54,     0,    57,     0,    24,     0,    80,    82,    84,    79,
       0,    74,    76,    77,    78,    61,     0,    58,    59,   102,
       0,   100,    37,     0,     0,     0,     0,    73,     0,    56,
       0,     0,     0,    99,     0,     0,     0,    75,    68,    70,
      65,     0,    63,    66,    67,    60,   113,   118,     0,   116,
     112,   110,   111,     0,   104,   106,   108,   109,   107,   101,
       0,     0,     0,     0,     0,     0,    62,     0,     0,     0,
       0,     0,   103,    93,    95,    92,    90,    91,     0,    86,
      88,    89,     0,     0,     0,     0,    64,     0,     0,   115,
       0,   105,     0,     0,     0,    81,    83,    85,    69,    71,
     114,     0,   117,     0,     0,    87,   122,     0,   120,    94,
      97,    96,     0,     0,   119,   131,     0,     0,     0,   136,
       0,   124,   126,   127,   128,   129,   130,   121,     0,     0,
       0,     0,     0,     0,   123,     0,   133,   134,   135,     0,
     125,   132,   137
  };

  const short
  AgentParser::yypgoto_[] =
  {
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,   -20,   -76,
    -128,   -19,  -128,  -128,  -128,  -128,  -128,  -128,   -27,  -128,
    -128,  -128,  -128,  -128,  -128,    81,    86,  -128,  -128,  -128,
     -26,  -128,   -25,  -128,  -128,  -128,  -128,  -128,    35,  -128,
    -128,    10,  -128,  -128,  -128,  -128,  -128,  -128,  -128,    46,
    -128,  -128,  -128,  -128,  -128,  -128,  -127,   -24,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,    39,  -128,  -128,     2,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,   -39,  -128,
    -128,   -55,  -128,  -128,  -128,  -128,  -128,  -128,  -128
  };

  const short
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    89,    32,    33,    19,    24,    29,    30,   165,    21,
      26,    35,    36,    37,    61,    47,    48,    49,    63,    50,
     166,    65,   167,    66,    53,    68,   106,   107,   108,   118,
     131,   132,   133,   153,   134,   154,    54,    91,   100,   101,
     102,   113,   103,   114,   104,   115,   168,   169,   170,   182,
     171,   183,   201,    55,    69,   110,   111,   121,   143,   144,
     145,   157,   146,   147,   160,   148,   158,   197,   198,   202,
     210,   211,   212,   218,   213,   214,   215,   216,   222
  };

  const unsigned char
  AgentParser::yytable_[] =
  {
      46,    51,    52,    88,    28,    20,     9,     8,    10,    71,
      11,    96,    97,    98,    72,    22,    38,    39,    40,    41,
      42,    71,    40,    41,   172,   173,   112,    43,   163,   164,
      44,   116,    31,    45,   128,   129,   117,    73,    74,    12,
      13,    14,    15,    45,    46,    51,    52,    45,   122,    45,
      56,   123,   205,    40,    41,   206,   207,   208,   209,    46,
      51,    52,    34,   155,    99,    94,   136,   137,   156,   138,
     139,   161,   184,    57,   184,   184,   162,   185,    45,   186,
     187,   223,   203,    59,    58,   204,   224,   128,   129,    99,
      60,   130,    62,    64,   140,   141,   142,    67,    70,    88,
       1,     2,     3,    76,    75,    77,    78,    79,    80,    81,
      82,    83,    85,   179,    87,    90,    86,    10,    92,    93,
     120,   188,   105,   109,   119,   124,   125,   126,   190,   192,
     199,   150,   151,   152,   140,   141,   142,   159,   174,   175,
     177,   178,   180,   231,   191,   193,   194,   196,   200,   219,
     220,   221,   225,   226,   229,   135,   189,    84,   227,   228,
     195,   149,   127,   181,   217,   176,   232,    95,   230
  };

  const unsigned char
  AgentParser::yycheck_[] =
  {
      27,    27,    27,    79,    24,     7,     5,     0,     7,     3,
       9,    16,    17,    18,     8,     7,    11,    12,    13,    14,
      15,     3,    13,    14,   151,   152,     8,    22,    19,    20,
      25,     3,    38,    38,    23,    24,     8,    57,    58,    38,
      39,    40,    41,    38,    71,    71,    71,    38,     3,    38,
       6,     6,    28,    13,    14,    31,    32,    33,    34,    86,
      86,    86,    10,     3,    91,    85,    26,    27,     8,    29,
      30,     3,     3,     3,     3,     3,     8,     8,    38,     8,
       8,     3,     3,     8,     4,     6,     8,    23,    24,   116,
       3,   118,     8,     4,   121,   121,   121,     4,     4,   175,
      35,    36,    37,     4,    38,     4,    39,     4,     4,     7,
       4,     4,     4,    39,    38,    38,     7,     7,     5,     5,
       3,    38,     7,     7,     6,     4,     4,     4,    38,    38,
      38,     7,     7,     7,   161,   161,   161,     4,     4,     4,
       4,     4,     4,    38,     5,     4,     4,     7,    21,     4,
       4,     4,     4,    41,     4,   120,   175,    71,    39,    39,
     184,   122,   116,   161,   203,   155,    38,    86,   223
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    35,    36,    37,    43,    44,    45,    46,     0,     5,
       7,     9,    38,    39,    40,    41,    49,    50,    51,    56,
       7,    61,     7,    47,    57,    52,    62,    48,    50,    58,
      59,    38,    54,    55,    10,    63,    64,    65,    11,    12,
      13,    14,    15,    22,    25,    38,    60,    67,    68,    69,
      71,    72,    74,    76,    88,   105,     6,     3,     4,     8,
       3,    66,     8,    70,     4,    73,    75,     4,    77,   106,
       4,     3,     8,    50,    50,    38,     4,     4,    39,     4,
       4,     7,     4,     4,    68,     4,     7,    38,    51,    53,
      38,    89,     5,     5,    50,    67,    16,    17,    18,    60,
      90,    91,    92,    94,    96,     7,    78,    79,    80,     7,
     107,   108,     8,    93,    95,    97,     3,     8,    81,     6,
       3,   109,     3,     6,     4,     4,     4,    91,    23,    24,
      60,    82,    83,    84,    86,    80,    26,    27,    29,    30,
      60,    72,    74,   110,   111,   112,   114,   115,   117,   108,
       7,     7,     7,    85,    87,     3,     8,   113,   118,     4,
     116,     3,     8,    19,    20,    60,    72,    74,    98,    99,
     100,   102,    98,    98,     4,     4,    83,     4,     4,    39,
       4,   111,   101,   103,     3,     8,     8,     8,    38,    53,
      38,     5,    38,     4,     4,    99,     7,   119,   120,    38,
      21,   104,   121,     3,     6,    28,    31,    32,    33,    34,
     122,   123,   124,   126,   127,   128,   129,   120,   125,     4,
       4,     4,   130,     3,     8,     4,    41,    39,    39,     4,
     123,    38,    38
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    42,    44,    43,    45,    43,    46,    43,    48,    47,
      49,    50,    50,    50,    50,    50,    50,    50,    52,    51,
      53,    54,    54,    55,    55,    57,    56,    58,    58,    59,
      59,    60,    62,    61,    63,    64,    66,    65,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    70,    69,
      71,    73,    72,    75,    74,    77,    76,    78,    78,    79,
      79,    81,    80,    82,    82,    82,    83,    83,    85,    84,
      87,    86,    89,    88,    90,    90,    91,    91,    91,    91,
      93,    92,    95,    94,    97,    96,    98,    98,    99,    99,
      99,    99,    99,   101,   100,   103,   102,   104,   106,   105,
     107,   107,   109,   108,   110,   110,   111,   111,   111,   111,
     111,   111,   111,   113,   112,   114,   116,   115,   118,   117,
     119,   119,   121,   120,   122,   122,   123,   123,   123,   123,
     123,   125,   124,   126,   127,   128,   130,   129
  };

  const signed char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       0,     6,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     3,     0,     4
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
  "global_objects", "global_object", "agent_object", "$@8",
  "global_params", "global_param", "http_host", "$@9", "http_port",
  "user_context", "$@10", "comment", "$@11", "hooks_libraries", "$@12",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@13", "hooks_params", "hooks_param", "library",
  "$@14", "parameters", "$@15", "control_sockets", "$@16",
  "control_sockets_params", "control_socket", "dhcp4_server_socket",
  "$@17", "dhcp6_server_socket", "$@18", "d2_server_socket", "$@19",
  "control_socket_params", "control_socket_param", "socket_name", "$@20",
  "socket_type", "$@21", "socket_type_value", "loggers", "$@22",
  "loggers_entries", "logger_entry", "$@23", "logger_params",
  "logger_param", "name", "$@24", "debuglevel", "severity", "$@25",
  "output_options_list", "$@26", "output_options_list_content",
  "output_entry", "$@27", "output_params_list", "output_params", "output",
  "$@28", "flush", "maxsize", "maxver", "pattern", "$@29", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   110,   110,   110,   111,   111,   112,   112,   120,   120,
     131,   137,   138,   139,   140,   141,   142,   143,   147,   147,
     158,   163,   164,   172,   176,   183,   183,   189,   190,   193,
     197,   210,   218,   218,   230,   234,   238,   238,   255,   256,
     261,   262,   263,   264,   265,   266,   267,   268,   271,   271,
     279,   284,   284,   309,   309,   337,   337,   347,   348,   351,
     352,   355,   355,   363,   364,   365,   368,   369,   372,   372,
     380,   380,   390,   390,   403,   404,   409,   410,   411,   412,
     416,   416,   427,   427,   438,   438,   449,   450,   454,   455,
     456,   457,   458,   462,   462,   471,   471,   479,   486,   486,
     498,   499,   503,   503,   511,   512,   515,   516,   517,   518,
     519,   520,   521,   524,   524,   532,   537,   537,   545,   545,
     555,   556,   559,   559,   567,   568,   571,   572,   573,   574,
     575,   578,   578,   586,   591,   596,   601,   601
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
#line 2035 "agent_parser.cc"

#line 609 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
