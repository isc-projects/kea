// A Bison parser, made by GNU Bison 3.7.4.

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
#line 108 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 388 "agent_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 108 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 394 "agent_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 108 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 400 "agent_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 108 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 406 "agent_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 108 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 412 "agent_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 108 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 418 "agent_parser.cc"
        break;

      case symbol_kind::S_socket_type_value: // socket_type_value
#line 108 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "agent_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 108 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 430 "agent_parser.cc"
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
#line 119 "agent_parser.yy"
                       { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 706 "agent_parser.cc"
    break;

  case 4: // $@2: %empty
#line 120 "agent_parser.yy"
                       { ctx.ctx_ = ctx.CONFIG; }
#line 712 "agent_parser.cc"
    break;

  case 6: // $@3: %empty
#line 121 "agent_parser.yy"
                       { ctx.ctx_ = ctx.AGENT; }
#line 718 "agent_parser.cc"
    break;

  case 8: // $@4: %empty
#line 129 "agent_parser.yy"
                          {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 728 "agent_parser.cc"
    break;

  case 9: // sub_agent: "{" $@4 global_params "}"
#line 133 "agent_parser.yy"
                               {
    // parsing completed
}
#line 736 "agent_parser.cc"
    break;

  case 10: // json: value
#line 140 "agent_parser.yy"
            {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 745 "agent_parser.cc"
    break;

  case 11: // value: "integer"
#line 146 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 751 "agent_parser.cc"
    break;

  case 12: // value: "floating point"
#line 147 "agent_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 757 "agent_parser.cc"
    break;

  case 13: // value: "boolean"
#line 148 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 763 "agent_parser.cc"
    break;

  case 14: // value: "constant string"
#line 149 "agent_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 769 "agent_parser.cc"
    break;

  case 15: // value: "null"
#line 150 "agent_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 775 "agent_parser.cc"
    break;

  case 16: // value: map
#line 151 "agent_parser.yy"
           { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 781 "agent_parser.cc"
    break;

  case 17: // value: list_generic
#line 152 "agent_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 787 "agent_parser.cc"
    break;

  case 18: // $@5: %empty
#line 156 "agent_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "agent_parser.cc"
    break;

  case 19: // map: "{" $@5 map_content "}"
#line 161 "agent_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "agent_parser.cc"
    break;

  case 20: // map_value: map
#line 167 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "agent_parser.cc"
    break;

  case 23: // not_empty_map: "constant string" ":" value
#line 181 "agent_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 824 "agent_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 186 "agent_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 835 "agent_parser.cc"
    break;

  case 25: // $@6: %empty
#line 194 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 844 "agent_parser.cc"
    break;

  case 26: // list_generic: "[" $@6 list_content "]"
#line 197 "agent_parser.yy"
                               {
}
#line 851 "agent_parser.cc"
    break;

  case 29: // not_empty_list: value
#line 204 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 860 "agent_parser.cc"
    break;

  case 30: // not_empty_list: not_empty_list "," value
#line 208 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 869 "agent_parser.cc"
    break;

  case 31: // unknown_map_entry: "constant string" ":"
#line 221 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 880 "agent_parser.cc"
    break;

  case 32: // $@7: %empty
#line 229 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 891 "agent_parser.cc"
    break;

  case 33: // agent_syntax_map: "{" $@7 global_object "}"
#line 234 "agent_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 901 "agent_parser.cc"
    break;

  case 34: // $@8: %empty
#line 241 "agent_parser.yy"
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
#line 918 "agent_parser.cc"
    break;

  case 35: // global_object: "Control-agent" $@8 ":" "{" global_params "}"
#line 252 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 929 "agent_parser.cc"
    break;

  case 47: // $@9: %empty
#line 276 "agent_parser.yy"
                     {
    ctx.unique("http-host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 938 "agent_parser.cc"
    break;

  case 48: // http_host: "http-host" $@9 ":" "constant string"
#line 279 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 948 "agent_parser.cc"
    break;

  case 49: // http_port: "http-port" ":" "integer"
#line 285 "agent_parser.yy"
                                   {
    ctx.unique("http-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 958 "agent_parser.cc"
    break;

  case 50: // $@10: %empty
#line 291 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 966 "agent_parser.cc"
    break;

  case 51: // user_context: "user-context" $@10 ":" map_value
#line 293 "agent_parser.yy"
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
#line 993 "agent_parser.cc"
    break;

  case 52: // $@11: %empty
#line 316 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1001 "agent_parser.cc"
    break;

  case 53: // comment: "comment" $@11 ":" "constant string"
#line 318 "agent_parser.yy"
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
#line 1030 "agent_parser.cc"
    break;

  case 54: // $@12: %empty
#line 344 "agent_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1042 "agent_parser.cc"
    break;

  case 55: // hooks_libraries: "hooks-libraries" $@12 ":" "[" hooks_libraries_list "]"
#line 350 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "agent_parser.cc"
    break;

  case 60: // $@13: %empty
#line 363 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1061 "agent_parser.cc"
    break;

  case 61: // hooks_library: "{" $@13 hooks_params "}"
#line 367 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1069 "agent_parser.cc"
    break;

  case 67: // $@14: %empty
#line 380 "agent_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1078 "agent_parser.cc"
    break;

  case 68: // library: "library" $@14 ":" "constant string"
#line 383 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1088 "agent_parser.cc"
    break;

  case 69: // $@15: %empty
#line 389 "agent_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1097 "agent_parser.cc"
    break;

  case 70: // parameters: "parameters" $@15 ":" map_value
#line 392 "agent_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1106 "agent_parser.cc"
    break;

  case 71: // $@16: %empty
#line 400 "agent_parser.yy"
                                                      {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[2].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1118 "agent_parser.cc"
    break;

  case 72: // control_sockets: "control-sockets" ":" "{" $@16 control_sockets_params "}"
#line 406 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1127 "agent_parser.cc"
    break;

  case 79: // $@17: %empty
#line 427 "agent_parser.yy"
                                  {
    ctx.unique("dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1139 "agent_parser.cc"
    break;

  case 80: // dhcp4_server_socket: "dhcp4" $@17 ":" "{" control_socket_params "}"
#line 433 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1148 "agent_parser.cc"
    break;

  case 81: // $@18: %empty
#line 439 "agent_parser.yy"
                                  {
    ctx.unique("dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1160 "agent_parser.cc"
    break;

  case 82: // dhcp6_server_socket: "dhcp6" $@18 ":" "{" control_socket_params "}"
#line 445 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1169 "agent_parser.cc"
    break;

  case 83: // $@19: %empty
#line 451 "agent_parser.yy"
                            {
    ctx.unique("d2", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1181 "agent_parser.cc"
    break;

  case 84: // d2_server_socket: "d2" $@19 ":" "{" control_socket_params "}"
#line 457 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1190 "agent_parser.cc"
    break;

  case 92: // $@20: %empty
#line 476 "agent_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1199 "agent_parser.cc"
    break;

  case 93: // socket_name: "socket-name" $@20 ":" "constant string"
#line 479 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1209 "agent_parser.cc"
    break;

  case 94: // $@21: %empty
#line 486 "agent_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1218 "agent_parser.cc"
    break;

  case 95: // socket_type: "socket-type" $@21 ":" socket_type_value
#line 489 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1227 "agent_parser.cc"
    break;

  case 96: // socket_type_value: "unix"
#line 495 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1233 "agent_parser.cc"
    break;

  case 97: // $@22: %empty
#line 502 "agent_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 1245 "agent_parser.cc"
    break;

  case 98: // authentication: "authentication" $@22 ":" "{" auth_params "}"
#line 508 "agent_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1256 "agent_parser.cc"
    break;

  case 107: // $@23: %empty
#line 527 "agent_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 1265 "agent_parser.cc"
    break;

  case 108: // auth_type: "type" $@23 ":" auth_type_value
#line 530 "agent_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1274 "agent_parser.cc"
    break;

  case 109: // auth_type_value: "basic"
#line 535 "agent_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 1280 "agent_parser.cc"
    break;

  case 110: // $@24: %empty
#line 538 "agent_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1289 "agent_parser.cc"
    break;

  case 111: // realm: "realm" $@24 ":" "constant string"
#line 541 "agent_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 1299 "agent_parser.cc"
    break;

  case 112: // $@25: %empty
#line 547 "agent_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 1311 "agent_parser.cc"
    break;

  case 113: // clients: "clients" $@25 ":" "[" clients_list "]"
#line 553 "agent_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1320 "agent_parser.cc"
    break;

  case 118: // $@26: %empty
#line 566 "agent_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1330 "agent_parser.cc"
    break;

  case 119: // basic_auth: "{" $@26 clients_params "}"
#line 570 "agent_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 1338 "agent_parser.cc"
    break;

  case 127: // $@27: %empty
#line 585 "agent_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1347 "agent_parser.cc"
    break;

  case 128: // user: "user" $@27 ":" "constant string"
#line 588 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1357 "agent_parser.cc"
    break;

  case 129: // $@28: %empty
#line 594 "agent_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1366 "agent_parser.cc"
    break;

  case 130: // password: "password" $@28 ":" "constant string"
#line 597 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", password);
    ctx.leave();
}
#line 1376 "agent_parser.cc"
    break;

  case 131: // $@29: %empty
#line 607 "agent_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1388 "agent_parser.cc"
    break;

  case 132: // loggers: "loggers" $@29 ":" "[" loggers_entries "]"
#line 613 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1397 "agent_parser.cc"
    break;

  case 135: // $@30: %empty
#line 625 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1407 "agent_parser.cc"
    break;

  case 136: // logger_entry: "{" $@30 logger_params "}"
#line 629 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1415 "agent_parser.cc"
    break;

  case 146: // $@31: %empty
#line 646 "agent_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1424 "agent_parser.cc"
    break;

  case 147: // name: "name" $@31 ":" "constant string"
#line 649 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1434 "agent_parser.cc"
    break;

  case 148: // debuglevel: "debuglevel" ":" "integer"
#line 655 "agent_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1444 "agent_parser.cc"
    break;

  case 149: // $@32: %empty
#line 661 "agent_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1453 "agent_parser.cc"
    break;

  case 150: // severity: "severity" $@32 ":" "constant string"
#line 664 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1463 "agent_parser.cc"
    break;

  case 151: // $@33: %empty
#line 670 "agent_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1475 "agent_parser.cc"
    break;

  case 152: // output_options_list: "output_options" $@33 ":" "[" output_options_list_content "]"
#line 676 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1484 "agent_parser.cc"
    break;

  case 155: // $@34: %empty
#line 685 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1494 "agent_parser.cc"
    break;

  case 156: // output_entry: "{" $@34 output_params_list "}"
#line 689 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1502 "agent_parser.cc"
    break;

  case 164: // $@35: %empty
#line 704 "agent_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1511 "agent_parser.cc"
    break;

  case 165: // output: "output" $@35 ":" "constant string"
#line 707 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1521 "agent_parser.cc"
    break;

  case 166: // flush: "flush" ":" "boolean"
#line 713 "agent_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1531 "agent_parser.cc"
    break;

  case 167: // maxsize: "maxsize" ":" "integer"
#line 719 "agent_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1541 "agent_parser.cc"
    break;

  case 168: // maxver: "maxver" ":" "integer"
#line 725 "agent_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1551 "agent_parser.cc"
    break;

  case 169: // $@36: %empty
#line 731 "agent_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1560 "agent_parser.cc"
    break;

  case 170: // pattern: "pattern" $@36 ":" "constant string"
#line 734 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1570 "agent_parser.cc"
    break;


#line 1574 "agent_parser.cc"

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


  const signed char AgentParser::yypact_ninf_ = -80;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      56,   -80,   -80,   -80,     6,     4,     3,     5,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,     4,   -37,    34,    10,   -80,    14,
      30,    67,    69,    98,   -80,   103,   -80,   113,   -80,   -80,
     -80,   118,   -80,   -80,   119,   -80,    23,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,     4,     4,   -80,
      79,   121,   -80,   122,    82,   125,   126,   127,   128,   129,
     130,   -80,    10,   -80,   -80,   -80,   132,   131,    92,   -80,
     133,    96,   135,   -80,   134,   138,   -80,     4,    10,   -80,
     -80,   -80,   -80,    40,    51,   137,   139,   -80,    54,   -80,
     -80,   -80,   -80,   -80,   -80,    57,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,    83,   -80,   -80,   -80,   -80,   -80,
     141,   142,   -80,   -80,    13,   -80,   -80,   144,   145,   146,
      40,   -80,   147,   148,   149,    51,   -80,    -2,   -80,   137,
       1,   139,   -80,   115,   109,   150,   -80,   151,   152,   153,
     -80,   -80,   -80,   -80,    84,   -80,   -80,   -80,   -80,   -80,
     -80,   158,   -80,   -80,   -80,   -80,    85,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   159,    -9,    -9,    -9,
     161,   163,    88,   -80,   164,   165,   110,   166,     1,   -80,
     -80,   167,   154,   -80,   -80,   -80,   -80,   -80,   -80,    86,
     -80,   -80,   -80,    87,    94,   136,   133,   -80,   140,   169,
     -80,   155,   -80,    59,   -80,   159,   168,   171,    -9,   -80,
     -80,   -80,   -80,   -80,   -80,   170,   -80,   -80,   -80,   -80,
     -80,   -80,   104,   -80,   -80,   -80,   -80,   156,   143,   -80,
     -80,    24,   -80,   172,   174,    59,   -80,   -80,   -80,   -80,
      43,   170,   -80,   157,   160,   -80,   -80,   175,   176,   178,
     -80,   106,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   179,   162,   173,   177,   180,    43,   -80,   181,   -80,
     -80,   -80,   182,   -80,   -80,   -80
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    34,     0,    47,     0,    50,    52,
      97,     0,    54,   131,     0,    46,     0,    36,    38,    39,
      44,    45,    42,    41,    40,    43,    26,     0,     0,    19,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     9,    30,    23,     0,     0,     0,    49,
       0,     0,     0,    71,     0,     0,    37,     0,     0,    48,
      20,    51,    53,     0,     0,    56,     0,    24,     0,   107,
     110,   112,   106,   105,   104,     0,    99,   101,   102,   103,
      79,    81,    83,    78,     0,    73,    75,    76,    77,    60,
       0,    57,    58,   135,     0,   133,    35,     0,     0,     0,
       0,    98,     0,     0,     0,     0,    72,     0,    55,     0,
       0,     0,   132,     0,     0,     0,   100,     0,     0,     0,
      74,    67,    69,    64,     0,    62,    65,    66,    59,   146,
     151,     0,   149,   145,   143,   144,     0,   137,   139,   141,
     142,   140,   134,   109,   108,   111,   114,     0,     0,     0,
       0,     0,     0,    61,     0,     0,     0,     0,     0,   136,
     118,     0,   115,   116,    92,    94,    91,    89,    90,     0,
      85,    87,    88,     0,     0,     0,     0,    63,     0,     0,
     148,     0,   138,     0,   113,     0,     0,     0,     0,    80,
      82,    84,    68,    70,   147,     0,   150,   127,   129,   126,
     124,   125,     0,   120,   122,   123,   117,     0,     0,    86,
     155,     0,   153,     0,     0,     0,   119,    93,    96,    95,
       0,     0,   152,     0,     0,   121,   164,     0,     0,     0,
     169,     0,   157,   159,   160,   161,   162,   163,   154,   128,
     130,     0,     0,     0,     0,     0,     0,   156,     0,   166,
     167,   168,     0,   158,   165,   170
  };

  const signed char
  AgentParser::yypgoto_[] =
  {
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -17,   -79,
     -80,   -19,   -80,   -80,   -80,   -80,   -80,   -80,   -27,   -80,
     -80,   -80,   -80,   102,   120,   -80,   -80,   -80,   -25,   -80,
     -24,   -80,   -80,   -80,   -80,   -80,    52,   -80,   -80,    11,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,    60,   -80,   -80,
     -80,   -80,   -80,   -80,   -58,   -22,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,    64,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -18,   -80,   -80,   -47,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,    58,   -80,   -80,    15,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -45,   -80,   -80,
     -72,   -80,   -80,   -80,   -80,   -80,   -80,   -80
  };

  const short
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    91,    32,    33,    19,    24,    29,    30,   196,    21,
      26,    35,    61,    46,    47,    48,    63,    49,   197,    65,
     198,    66,    52,    69,   120,   121,   122,   137,   154,   155,
     156,   180,   157,   181,    53,    94,   114,   115,   116,   132,
     117,   133,   118,   134,   199,   200,   201,   216,   202,   217,
     249,    54,    67,   105,   106,   107,   127,   174,   108,   128,
     109,   129,   191,   192,   193,   213,   232,   233,   234,   243,
     235,   244,    55,    70,   124,   125,   140,   166,   167,   168,
     184,   169,   170,   187,   171,   185,   241,   242,   250,   261,
     262,   263,   271,   264,   265,   266,   267,   275
  };

  const short
  AgentParser::yytable_[] =
  {
      45,    90,    50,    51,    38,    39,     8,    28,    31,     9,
      20,    10,    22,    11,    38,    39,   141,   194,   195,   142,
      56,    36,    37,    38,    39,    40,    72,   251,   151,   152,
     252,    73,    41,    57,   159,   160,    44,   161,   162,    42,
      74,    75,    43,    44,    34,    45,    44,    50,    51,    12,
      13,    14,    15,    38,    39,    44,    99,    72,   100,   101,
     130,    45,   126,    50,    51,   131,   102,   113,   103,   104,
      97,    58,    38,    39,   110,   111,   112,    59,   256,   227,
     228,   257,   258,   259,   260,    44,   135,   182,   188,   218,
     218,   136,   183,   189,   219,   220,    44,   218,     1,     2,
       3,    60,   221,   102,    44,   103,   104,   245,   113,   276,
     153,    62,   246,   163,   277,   164,   165,    64,   151,   152,
     203,   204,    68,    71,    76,    77,    78,    90,    79,    80,
      81,    82,   173,    84,    85,    83,    87,    89,    88,    95,
      10,    92,    93,    96,   119,   139,   123,   138,   143,   144,
     145,   147,   148,   149,   175,   176,   210,   215,   177,   178,
     179,   163,   186,   164,   165,   205,   190,   206,   208,   209,
     211,   248,   237,   214,   225,   238,   253,   240,   254,   272,
     273,   222,   274,   278,   282,   224,   229,   223,   230,   231,
      98,   158,    86,   207,   146,   150,   239,   236,   255,   172,
     226,   247,   269,   212,   283,   270,   268,     0,     0,     0,
     279,     0,     0,     0,     0,     0,     0,     0,   229,   280,
     230,   231,     0,   281,     0,     0,   284,   285
  };

  const short
  AgentParser::yycheck_[] =
  {
      27,    80,    27,    27,    13,    14,     0,    24,    45,     5,
       7,     7,     7,     9,    13,    14,     3,    26,    27,     6,
       6,    11,    12,    13,    14,    15,     3,     3,    30,    31,
       6,     8,    22,     3,    33,    34,    45,    36,    37,    29,
      57,    58,    32,    45,    10,    72,    45,    72,    72,    45,
      46,    47,    48,    13,    14,    45,    16,     3,    18,    19,
       3,    88,     8,    88,    88,     8,    93,    94,    93,    93,
      87,     4,    13,    14,    23,    24,    25,     8,    35,    20,
      21,    38,    39,    40,    41,    45,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,    45,     3,    42,    43,
      44,     3,     8,   130,    45,   130,   130,     3,   135,     3,
     137,     8,     8,   140,     8,   140,   140,     4,    30,    31,
     178,   179,     4,     4,    45,     4,     4,   206,    46,     4,
       4,     4,    17,     4,     4,     7,     4,    45,     7,     5,
       7,    45,     7,     5,     7,     3,     7,     6,     4,     4,
       4,     4,     4,     4,    45,     5,    46,     3,     7,     7,
       7,   188,     4,   188,   188,     4,     7,     4,     4,     4,
       4,    28,     4,     6,     5,     4,     4,     7,     4,     4,
       4,    45,     4,     4,     4,    45,   213,   206,   213,   213,
      88,   139,    72,   182,   130,   135,   218,   215,   245,   141,
      45,    45,    45,   188,   276,    45,   251,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,    46,
     245,   245,    -1,    46,    -1,    -1,    45,    45
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    42,    43,    44,    50,    51,    52,    53,     0,     5,
       7,     9,    45,    46,    47,    48,    56,    57,    58,    63,
       7,    68,     7,    54,    64,    59,    69,    55,    57,    65,
      66,    45,    61,    62,    10,    70,    11,    12,    13,    14,
      15,    22,    29,    32,    45,    67,    72,    73,    74,    76,
      77,    79,    81,    93,   110,   131,     6,     3,     4,     8,
       3,    71,     8,    75,     4,    78,    80,   111,     4,    82,
     132,     4,     3,     8,    57,    57,    45,     4,     4,    46,
       4,     4,     4,     7,     4,     4,    73,     4,     7,    45,
      58,    60,    45,     7,    94,     5,     5,    57,    72,    16,
      18,    19,    67,    77,    79,   112,   113,   114,   117,   119,
      23,    24,    25,    67,    95,    96,    97,    99,   101,     7,
      83,    84,    85,     7,   133,   134,     8,   115,   118,   120,
       3,     8,    98,   100,   102,     3,     8,    86,     6,     3,
     135,     3,     6,     4,     4,     4,   113,     4,     4,     4,
      96,    30,    31,    67,    87,    88,    89,    91,    85,    33,
      34,    36,    37,    67,    77,    79,   136,   137,   138,   140,
     141,   143,   134,    17,   116,    45,     5,     7,     7,     7,
      90,    92,     3,     8,   139,   144,     4,   142,     3,     8,
       7,   121,   122,   123,    26,    27,    67,    77,    79,   103,
     104,   105,   107,   103,   103,     4,     4,    88,     4,     4,
      46,     4,   137,   124,     6,     3,   106,   108,     3,     8,
       8,     8,    45,    60,    45,     5,    45,    20,    21,    67,
      77,    79,   125,   126,   127,   129,   123,     4,     4,   104,
       7,   145,   146,   128,   130,     3,     8,    45,    28,   109,
     147,     3,     6,     4,     4,   126,    35,    38,    39,    40,
      41,   148,   149,   150,   152,   153,   154,   155,   146,    45,
      45,   151,     4,     4,     4,   156,     3,     8,     4,    48,
      46,    46,     4,   149,    45,    45
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    49,    51,    50,    52,    50,    53,    50,    55,    54,
      56,    57,    57,    57,    57,    57,    57,    57,    59,    58,
      60,    61,    61,    62,    62,    64,    63,    65,    65,    66,
      66,    67,    69,    68,    71,    70,    72,    72,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    75,    74,    76,
      78,    77,    80,    79,    82,    81,    83,    83,    84,    84,
      86,    85,    87,    87,    87,    88,    88,    90,    89,    92,
      91,    94,    93,    95,    95,    96,    96,    96,    96,    98,
      97,   100,    99,   102,   101,   103,   103,   104,   104,   104,
     104,   104,   106,   105,   108,   107,   109,   111,   110,   112,
     112,   113,   113,   113,   113,   113,   113,   115,   114,   116,
     118,   117,   120,   119,   121,   121,   122,   122,   124,   123,
     125,   125,   126,   126,   126,   126,   126,   128,   127,   130,
     129,   132,   131,   133,   133,   135,   134,   136,   136,   137,
     137,   137,   137,   137,   137,   137,   139,   138,   140,   142,
     141,   144,   143,   145,   145,   147,   146,   148,   148,   149,
     149,   149,   149,   149,   151,   150,   152,   153,   154,   156,
     155
  };

  const signed char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     0,
       6,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4
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
  "\"authentication\"", "\"type\"", "\"basic\"", "\"realm\"",
  "\"clients\"", "\"user\"", "\"password\"", "\"control-sockets\"",
  "\"dhcp4\"", "\"dhcp6\"", "\"d2\"", "\"socket-name\"", "\"socket-type\"",
  "\"unix\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"loggers\"", "\"name\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"pattern\"", "START_JSON", "START_AGENT",
  "START_SUB_AGENT", "\"constant string\"", "\"integer\"",
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
  "socket_type_value", "authentication", "$@22", "auth_params",
  "auth_param", "auth_type", "$@23", "auth_type_value", "realm", "$@24",
  "clients", "$@25", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@26", "clients_params", "clients_param", "user", "$@27",
  "password", "$@28", "loggers", "$@29", "loggers_entries", "logger_entry",
  "$@30", "logger_params", "logger_param", "name", "$@31", "debuglevel",
  "severity", "$@32", "output_options_list", "$@33",
  "output_options_list_content", "output_entry", "$@34",
  "output_params_list", "output_params", "output", "$@35", "flush",
  "maxsize", "maxver", "pattern", "$@36", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   119,   119,   119,   120,   120,   121,   121,   129,   129,
     140,   146,   147,   148,   149,   150,   151,   152,   156,   156,
     167,   172,   173,   181,   186,   194,   194,   200,   201,   204,
     208,   221,   229,   229,   241,   241,   259,   260,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   276,   276,   285,
     291,   291,   316,   316,   344,   344,   355,   356,   359,   360,
     363,   363,   371,   372,   373,   376,   377,   380,   380,   389,
     389,   400,   400,   414,   415,   420,   421,   422,   423,   427,
     427,   439,   439,   451,   451,   463,   464,   468,   469,   470,
     471,   472,   476,   476,   486,   486,   495,   502,   502,   515,
     516,   519,   520,   521,   522,   523,   524,   527,   527,   535,
     538,   538,   547,   547,   558,   559,   562,   563,   566,   566,
     574,   575,   578,   579,   580,   581,   582,   585,   585,   594,
     594,   607,   607,   620,   621,   625,   625,   633,   634,   637,
     638,   639,   640,   641,   642,   643,   646,   646,   655,   661,
     661,   670,   670,   681,   682,   685,   685,   693,   694,   697,
     698,   699,   700,   701,   704,   704,   713,   719,   725,   731,
     731
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
#line 2262 "agent_parser.cc"

#line 740 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
