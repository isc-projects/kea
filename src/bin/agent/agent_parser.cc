// A Bison parser, made by GNU Bison 3.7.2.

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
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 823 "agent_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 185 "agent_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 833 "agent_parser.cc"
    break;

  case 25: // $@6: %empty
#line 192 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 842 "agent_parser.cc"
    break;

  case 26: // list_generic: "[" $@6 list_content "]"
#line 195 "agent_parser.yy"
                               {
}
#line 849 "agent_parser.cc"
    break;

  case 29: // not_empty_list: value
#line 202 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 858 "agent_parser.cc"
    break;

  case 30: // not_empty_list: not_empty_list "," value
#line 206 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 867 "agent_parser.cc"
    break;

  case 31: // unknown_map_entry: "constant string" ":"
#line 219 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 878 "agent_parser.cc"
    break;

  case 32: // $@7: %empty
#line 227 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 889 "agent_parser.cc"
    break;

  case 33: // agent_syntax_map: "{" $@7 global_objects "}"
#line 232 "agent_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 899 "agent_parser.cc"
    break;

  case 36: // $@8: %empty
#line 247 "agent_parser.yy"
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
#line 915 "agent_parser.cc"
    break;

  case 37: // agent_object: "Control-agent" $@8 ":" "{" global_params "}"
#line 257 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 926 "agent_parser.cc"
    break;

  case 49: // $@9: %empty
#line 281 "agent_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 934 "agent_parser.cc"
    break;

  case 50: // http_host: "http-host" $@9 ":" "constant string"
#line 283 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 944 "agent_parser.cc"
    break;

  case 51: // http_port: "http-port" ":" "integer"
#line 289 "agent_parser.yy"
                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 953 "agent_parser.cc"
    break;

  case 52: // $@10: %empty
#line 294 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 961 "agent_parser.cc"
    break;

  case 53: // user_context: "user-context" $@10 ":" map_value
#line 296 "agent_parser.yy"
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
#line 988 "agent_parser.cc"
    break;

  case 54: // $@11: %empty
#line 319 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 996 "agent_parser.cc"
    break;

  case 55: // comment: "comment" $@11 ":" "constant string"
#line 321 "agent_parser.yy"
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
#line 1025 "agent_parser.cc"
    break;

  case 56: // $@12: %empty
#line 347 "agent_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1036 "agent_parser.cc"
    break;

  case 57: // hooks_libraries: "hooks-libraries" $@12 ":" "[" hooks_libraries_list "]"
#line 352 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1045 "agent_parser.cc"
    break;

  case 62: // $@13: %empty
#line 365 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1055 "agent_parser.cc"
    break;

  case 63: // hooks_library: "{" $@13 hooks_params "}"
#line 369 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1063 "agent_parser.cc"
    break;

  case 69: // $@14: %empty
#line 382 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1071 "agent_parser.cc"
    break;

  case 70: // library: "library" $@14 ":" "constant string"
#line 384 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1081 "agent_parser.cc"
    break;

  case 71: // $@15: %empty
#line 390 "agent_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1089 "agent_parser.cc"
    break;

  case 72: // parameters: "parameters" $@15 ":" map_value
#line 392 "agent_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1098 "agent_parser.cc"
    break;

  case 73: // $@16: %empty
#line 400 "agent_parser.yy"
                                                      {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1109 "agent_parser.cc"
    break;

  case 74: // control_sockets: "control-sockets" ":" "{" $@16 control_sockets_params "}"
#line 405 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1118 "agent_parser.cc"
    break;

  case 81: // $@17: %empty
#line 426 "agent_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1129 "agent_parser.cc"
    break;

  case 82: // dhcp4_server_socket: "dhcp4" $@17 ":" "{" control_socket_params "}"
#line 431 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "agent_parser.cc"
    break;

  case 83: // $@18: %empty
#line 437 "agent_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1149 "agent_parser.cc"
    break;

  case 84: // dhcp6_server_socket: "dhcp6" $@18 ":" "{" control_socket_params "}"
#line 442 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1158 "agent_parser.cc"
    break;

  case 85: // $@19: %empty
#line 448 "agent_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1169 "agent_parser.cc"
    break;

  case 86: // d2_server_socket: "d2" $@19 ":" "{" control_socket_params "}"
#line 453 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1178 "agent_parser.cc"
    break;

  case 94: // $@20: %empty
#line 472 "agent_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1186 "agent_parser.cc"
    break;

  case 95: // socket_name: "socket-name" $@20 ":" "constant string"
#line 474 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1196 "agent_parser.cc"
    break;

  case 96: // $@21: %empty
#line 481 "agent_parser.yy"
                         {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1204 "agent_parser.cc"
    break;

  case 97: // socket_type: "socket-type" $@21 ":" socket_type_value
#line 483 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1213 "agent_parser.cc"
    break;

  case 98: // socket_type_value: "unix"
#line 489 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1219 "agent_parser.cc"
    break;

  case 99: // $@22: %empty
#line 496 "agent_parser.yy"
                               {
    // Add unique here
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 1231 "agent_parser.cc"
    break;

  case 100: // authentication: "authentication" $@22 ":" "{" auth_params "}"
#line 502 "agent_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1242 "agent_parser.cc"
    break;

  case 106: // $@23: %empty
#line 518 "agent_parser.yy"
                {
    // Add unique here
    ctx.enter(ctx.AUTH_TYPE);
}
#line 1251 "agent_parser.cc"
    break;

  case 107: // auth_type: "type" $@23 ":" auth_type_value
#line 521 "agent_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1260 "agent_parser.cc"
    break;

  case 108: // auth_type_value: "basic"
#line 526 "agent_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 1266 "agent_parser.cc"
    break;

  case 109: // $@24: %empty
#line 529 "agent_parser.yy"
             {
    // Add unique here
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1275 "agent_parser.cc"
    break;

  case 110: // realm: "realm" $@24 ":" "constant string"
#line 532 "agent_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 1285 "agent_parser.cc"
    break;

  case 111: // $@25: %empty
#line 538 "agent_parser.yy"
                 {
    // Add unique here
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 1297 "agent_parser.cc"
    break;

  case 112: // clients: "clients" $@25 ":" "[" clients_list "]"
#line 544 "agent_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1306 "agent_parser.cc"
    break;

  case 117: // $@26: %empty
#line 557 "agent_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1316 "agent_parser.cc"
    break;

  case 118: // basic_auth: "{" $@26 clients_params "}"
#line 561 "agent_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 1324 "agent_parser.cc"
    break;

  case 126: // $@27: %empty
#line 576 "agent_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1332 "agent_parser.cc"
    break;

  case 127: // user: "user" $@27 ":" "constant string"
#line 578 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1342 "agent_parser.cc"
    break;

  case 128: // $@28: %empty
#line 584 "agent_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1350 "agent_parser.cc"
    break;

  case 129: // password: "password" $@28 ":" "constant string"
#line 586 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", password);
    ctx.leave();
}
#line 1360 "agent_parser.cc"
    break;

  case 130: // $@29: %empty
#line 596 "agent_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1371 "agent_parser.cc"
    break;

  case 131: // loggers: "loggers" $@29 ":" "[" loggers_entries "]"
#line 601 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1380 "agent_parser.cc"
    break;

  case 134: // $@30: %empty
#line 613 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1390 "agent_parser.cc"
    break;

  case 135: // logger_entry: "{" $@30 logger_params "}"
#line 617 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1398 "agent_parser.cc"
    break;

  case 145: // $@31: %empty
#line 634 "agent_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1406 "agent_parser.cc"
    break;

  case 146: // name: "name" $@31 ":" "constant string"
#line 636 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1416 "agent_parser.cc"
    break;

  case 147: // debuglevel: "debuglevel" ":" "integer"
#line 642 "agent_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1425 "agent_parser.cc"
    break;

  case 148: // $@32: %empty
#line 647 "agent_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1433 "agent_parser.cc"
    break;

  case 149: // severity: "severity" $@32 ":" "constant string"
#line 649 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1443 "agent_parser.cc"
    break;

  case 150: // $@33: %empty
#line 655 "agent_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1454 "agent_parser.cc"
    break;

  case 151: // output_options_list: "output_options" $@33 ":" "[" output_options_list_content "]"
#line 660 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1463 "agent_parser.cc"
    break;

  case 154: // $@34: %empty
#line 669 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1473 "agent_parser.cc"
    break;

  case 155: // output_entry: "{" $@34 output_params_list "}"
#line 673 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1481 "agent_parser.cc"
    break;

  case 163: // $@35: %empty
#line 688 "agent_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1489 "agent_parser.cc"
    break;

  case 164: // output: "output" $@35 ":" "constant string"
#line 690 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1499 "agent_parser.cc"
    break;

  case 165: // flush: "flush" ":" "boolean"
#line 696 "agent_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1508 "agent_parser.cc"
    break;

  case 166: // maxsize: "maxsize" ":" "integer"
#line 701 "agent_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1517 "agent_parser.cc"
    break;

  case 167: // maxver: "maxver" ":" "integer"
#line 706 "agent_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1526 "agent_parser.cc"
    break;

  case 168: // $@36: %empty
#line 711 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1534 "agent_parser.cc"
    break;

  case 169: // pattern: "pattern" $@36 ":" "constant string"
#line 713 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1544 "agent_parser.cc"
    break;


#line 1548 "agent_parser.cc"

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


  const short AgentParser::yypact_ninf_ = -133;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      59,  -133,  -133,  -133,     8,     5,     6,    13,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,     5,   -34,    18,    10,  -133,    48,
      83,    58,    96,   102,  -133,    98,  -133,  -133,  -133,   104,
    -133,  -133,  -133,   106,  -133,  -133,   107,  -133,     1,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,     5,
       5,  -133,    70,   112,  -133,   113,    72,   115,   116,   117,
     118,   119,   120,  -133,    10,  -133,  -133,  -133,   123,   121,
      88,  -133,   122,    89,   124,  -133,   125,   127,  -133,     5,
      10,  -133,  -133,  -133,  -133,    80,    -8,   128,   129,  -133,
      28,  -133,  -133,  -133,    73,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,    74,  -133,  -133,  -133,  -133,  -133,   131,
     135,  -133,  -133,    55,  -133,  -133,   136,   137,   138,    80,
    -133,   139,   140,   141,    -8,  -133,   -12,  -133,   128,    -7,
     129,  -133,   105,   101,   134,  -133,   142,   143,   144,  -133,
    -133,  -133,  -133,    75,  -133,  -133,  -133,  -133,  -133,  -133,
     148,  -133,  -133,  -133,  -133,    76,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,   146,    30,    30,    30,   150,
     151,     4,  -133,   152,   153,   126,   154,    -7,  -133,  -133,
     157,   145,  -133,  -133,  -133,  -133,  -133,  -133,    77,  -133,
    -133,  -133,    84,    85,   114,   122,  -133,   130,   159,  -133,
     132,  -133,    46,  -133,   146,   161,   162,    30,  -133,  -133,
    -133,  -133,  -133,  -133,   160,  -133,  -133,  -133,  -133,  -133,
    -133,    86,  -133,  -133,  -133,  -133,   133,   155,  -133,  -133,
      94,  -133,   164,   165,    46,  -133,  -133,  -133,  -133,    33,
     160,  -133,   147,   149,  -133,  -133,   166,   167,   169,  -133,
      87,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
     170,    99,   156,   158,   172,    33,  -133,   163,  -133,  -133,
    -133,   168,  -133,  -133,  -133
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    36,     0,    34,    35,    49,     0,
      52,    54,    99,     0,    56,   130,     0,    48,     0,    38,
      40,    41,    46,    47,    44,    43,    42,    45,    26,     0,
       0,    19,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     9,    30,    23,     0,     0,
       0,    51,     0,     0,     0,    73,     0,     0,    39,     0,
       0,    50,    20,    53,    55,     0,     0,    58,     0,    24,
       0,   106,   109,   111,     0,   101,   103,   104,   105,    81,
      83,    85,    80,     0,    75,    77,    78,    79,    62,     0,
      59,    60,   134,     0,   132,    37,     0,     0,     0,     0,
     100,     0,     0,     0,     0,    74,     0,    57,     0,     0,
       0,   131,     0,     0,     0,   102,     0,     0,     0,    76,
      69,    71,    66,     0,    64,    67,    68,    61,   145,   150,
       0,   148,   144,   142,   143,     0,   136,   138,   140,   141,
     139,   133,   108,   107,   110,   113,     0,     0,     0,     0,
       0,     0,    63,     0,     0,     0,     0,     0,   135,   117,
       0,   114,   115,    94,    96,    93,    91,    92,     0,    87,
      89,    90,     0,     0,     0,     0,    65,     0,     0,   147,
       0,   137,     0,   112,     0,     0,     0,     0,    82,    84,
      86,    70,    72,   146,     0,   149,   126,   128,   125,   123,
     124,     0,   119,   121,   122,   116,     0,     0,    88,   154,
       0,   152,     0,     0,     0,   118,    95,    98,    97,     0,
       0,   151,     0,     0,   120,   163,     0,     0,     0,   168,
       0,   156,   158,   159,   160,   161,   162,   153,   127,   129,
       0,     0,     0,     0,     0,     0,   155,     0,   165,   166,
     167,     0,   157,   164,   169
  };

  const short
  AgentParser::yypgoto_[] =
  {
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -19,   -79,
    -133,   -24,  -133,  -133,  -133,  -133,  -133,  -133,   -27,  -133,
    -133,  -133,  -133,  -133,  -133,    90,   108,  -133,  -133,  -133,
     -26,  -133,   -25,  -133,  -133,  -133,  -133,  -133,    41,  -133,
    -133,     3,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    54,
    -133,  -133,  -133,  -133,  -133,  -133,  -132,   -28,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,    61,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,   -23,  -133,  -133,   -51,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,    56,  -133,  -133,
      11,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -55,
    -133,  -133,   -78,  -133,  -133,  -133,  -133,  -133,  -133,  -133
  };

  const short
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    93,    32,    33,    19,    24,    29,    30,   195,    21,
      26,    35,    36,    37,    63,    48,    49,    50,    65,    51,
     196,    67,   197,    68,    54,    71,   119,   120,   121,   136,
     153,   154,   155,   179,   156,   180,    55,    96,   113,   114,
     115,   131,   116,   132,   117,   133,   198,   199,   200,   215,
     201,   216,   248,    56,    69,   104,   105,   106,   126,   173,
     107,   127,   108,   128,   190,   191,   192,   212,   231,   232,
     233,   242,   234,   243,    57,    72,   123,   124,   139,   165,
     166,   167,   183,   168,   169,   186,   170,   184,   240,   241,
     249,   260,   261,   262,   270,   263,   264,   265,   266,   274
  };

  const short
  AgentParser::yytable_[] =
  {
      47,    52,    53,    92,    74,    28,    40,    41,     8,    75,
       9,    31,    10,    20,    11,   109,   110,   111,   150,   151,
      22,    38,    39,    40,    41,    42,   158,   159,    34,   160,
     161,    74,    43,    46,   150,   151,   125,    46,    46,    44,
      76,    77,    45,    40,    41,   202,   203,    47,    52,    53,
      12,    13,    14,    15,    58,    46,   193,   194,   140,    40,
      41,   141,    60,    47,    52,    53,   226,   227,   255,   112,
      99,   256,   257,   258,   259,    46,   129,   134,   181,   187,
     217,   130,   135,   182,   188,   218,    59,   217,   217,   244,
     275,    46,   219,   220,   245,   276,   101,   250,   102,   103,
     251,     1,     2,     3,    61,    62,    64,   112,    66,   152,
      70,    73,   162,   163,   164,    78,    79,    80,    81,    82,
      83,    84,   172,    86,    87,    85,    92,    89,    90,    10,
      97,    95,    98,    91,    94,   118,   122,   137,   138,   175,
     142,   143,   144,   146,   147,   148,   174,   278,   214,   176,
     177,   178,   185,   189,   204,   205,   207,   208,   210,   221,
     162,   163,   164,   213,   224,   236,   237,   239,   252,   253,
     271,   272,   209,   273,   277,   223,   281,   225,   246,   157,
     100,   222,    88,   247,   206,   228,   229,   230,   149,   238,
     145,   235,   268,   254,   269,   267,   171,   282,   211,     0,
       0,     0,   279,     0,   280,     0,     0,     0,   283,     0,
       0,     0,     0,   284,     0,     0,     0,   228,   229,   230
  };

  const short
  AgentParser::yycheck_[] =
  {
      27,    27,    27,    82,     3,    24,    13,    14,     0,     8,
       5,    45,     7,     7,     9,    23,    24,    25,    30,    31,
       7,    11,    12,    13,    14,    15,    33,    34,    10,    36,
      37,     3,    22,    45,    30,    31,     8,    45,    45,    29,
      59,    60,    32,    13,    14,   177,   178,    74,    74,    74,
      45,    46,    47,    48,     6,    45,    26,    27,     3,    13,
      14,     6,     4,    90,    90,    90,    20,    21,    35,    96,
      89,    38,    39,    40,    41,    45,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,     3,     3,     3,     3,
       3,    45,     8,     8,     8,     8,    16,     3,    18,    19,
       6,    42,    43,    44,     8,     3,     8,   134,     4,   136,
       4,     4,   139,   139,   139,    45,     4,     4,    46,     4,
       4,     4,    17,     4,     4,     7,   205,     4,     7,     7,
       5,     7,     5,    45,    45,     7,     7,     6,     3,     5,
       4,     4,     4,     4,     4,     4,    45,    48,     3,     7,
       7,     7,     4,     7,     4,     4,     4,     4,     4,    45,
     187,   187,   187,     6,     5,     4,     4,     7,     4,     4,
       4,     4,    46,     4,     4,    45,     4,    45,    45,   138,
      90,   205,    74,    28,   181,   212,   212,   212,   134,   217,
     129,   214,    45,   244,    45,   250,   140,   275,   187,    -1,
      -1,    -1,    46,    -1,    46,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,   244,   244,   244
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    42,    43,    44,    50,    51,    52,    53,     0,     5,
       7,     9,    45,    46,    47,    48,    56,    57,    58,    63,
       7,    68,     7,    54,    64,    59,    69,    55,    57,    65,
      66,    45,    61,    62,    10,    70,    71,    72,    11,    12,
      13,    14,    15,    22,    29,    32,    45,    67,    74,    75,
      76,    78,    79,    81,    83,    95,   112,   133,     6,     3,
       4,     8,     3,    73,     8,    77,     4,    80,    82,   113,
       4,    84,   134,     4,     3,     8,    57,    57,    45,     4,
       4,    46,     4,     4,     4,     7,     4,     4,    75,     4,
       7,    45,    58,    60,    45,     7,    96,     5,     5,    57,
      74,    16,    18,    19,   114,   115,   116,   119,   121,    23,
      24,    25,    67,    97,    98,    99,   101,   103,     7,    85,
      86,    87,     7,   135,   136,     8,   117,   120,   122,     3,
       8,   100,   102,   104,     3,     8,    88,     6,     3,   137,
       3,     6,     4,     4,     4,   115,     4,     4,     4,    98,
      30,    31,    67,    89,    90,    91,    93,    87,    33,    34,
      36,    37,    67,    79,    81,   138,   139,   140,   142,   143,
     145,   136,    17,   118,    45,     5,     7,     7,     7,    92,
      94,     3,     8,   141,   146,     4,   144,     3,     8,     7,
     123,   124,   125,    26,    27,    67,    79,    81,   105,   106,
     107,   109,   105,   105,     4,     4,    90,     4,     4,    46,
       4,   139,   126,     6,     3,   108,   110,     3,     8,     8,
       8,    45,    60,    45,     5,    45,    20,    21,    67,    79,
      81,   127,   128,   129,   131,   125,     4,     4,   106,     7,
     147,   148,   130,   132,     3,     8,    45,    28,   111,   149,
       3,     6,     4,     4,   128,    35,    38,    39,    40,    41,
     150,   151,   152,   154,   155,   156,   157,   148,    45,    45,
     153,     4,     4,     4,   158,     3,     8,     4,    48,    46,
      46,     4,   151,    45,    45
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    49,    51,    50,    52,    50,    53,    50,    55,    54,
      56,    57,    57,    57,    57,    57,    57,    57,    59,    58,
      60,    61,    61,    62,    62,    64,    63,    65,    65,    66,
      66,    67,    69,    68,    70,    71,    73,    72,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    77,
      76,    78,    80,    79,    82,    81,    84,    83,    85,    85,
      86,    86,    88,    87,    89,    89,    89,    90,    90,    92,
      91,    94,    93,    96,    95,    97,    97,    98,    98,    98,
      98,   100,    99,   102,   101,   104,   103,   105,   105,   106,
     106,   106,   106,   106,   108,   107,   110,   109,   111,   113,
     112,   114,   114,   115,   115,   115,   117,   116,   118,   120,
     119,   122,   121,   123,   123,   124,   124,   126,   125,   127,
     127,   128,   128,   128,   128,   128,   130,   129,   132,   131,
     134,   133,   135,   135,   137,   136,   138,   138,   139,   139,
     139,   139,   139,   139,   139,   141,   140,   142,   144,   143,
     146,   145,   147,   147,   149,   148,   150,   150,   151,   151,
     151,   151,   151,   153,   152,   154,   155,   156,   158,   157
  };

  const signed char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     0,     6,     0,     6,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     1,     0,
       6,     1,     3,     1,     1,     1,     0,     4,     1,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4
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
  "global_objects", "global_object", "agent_object", "$@8",
  "global_params", "global_param", "http_host", "$@9", "http_port",
  "user_context", "$@10", "comment", "$@11", "hooks_libraries", "$@12",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@13", "hooks_params", "hooks_param", "library",
  "$@14", "parameters", "$@15", "control_sockets", "$@16",
  "control_sockets_params", "control_socket", "dhcp4_server_socket",
  "$@17", "dhcp6_server_socket", "$@18", "d2_server_socket", "$@19",
  "control_socket_params", "control_socket_param", "socket_name", "$@20",
  "socket_type", "$@21", "socket_type_value", "authentication", "$@22",
  "auth_params", "auth_param", "auth_type", "$@23", "auth_type_value",
  "realm", "$@24", "clients", "$@25", "clients_list",
  "not_empty_clients_list", "basic_auth", "$@26", "clients_params",
  "clients_param", "user", "$@27", "password", "$@28", "loggers", "$@29",
  "loggers_entries", "logger_entry", "$@30", "logger_params",
  "logger_param", "name", "$@31", "debuglevel", "severity", "$@32",
  "output_options_list", "$@33", "output_options_list_content",
  "output_entry", "$@34", "output_params_list", "output_params", "output",
  "$@35", "flush", "maxsize", "maxver", "pattern", "$@36", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   119,   119,   119,   120,   120,   121,   121,   129,   129,
     140,   146,   147,   148,   149,   150,   151,   152,   156,   156,
     167,   172,   173,   181,   185,   192,   192,   198,   199,   202,
     206,   219,   227,   227,   239,   243,   247,   247,   264,   265,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   281,
     281,   289,   294,   294,   319,   319,   347,   347,   357,   358,
     361,   362,   365,   365,   373,   374,   375,   378,   379,   382,
     382,   390,   390,   400,   400,   413,   414,   419,   420,   421,
     422,   426,   426,   437,   437,   448,   448,   459,   460,   464,
     465,   466,   467,   468,   472,   472,   481,   481,   489,   496,
     496,   509,   510,   513,   514,   515,   518,   518,   526,   529,
     529,   538,   538,   549,   550,   553,   554,   557,   557,   565,
     566,   569,   570,   571,   572,   573,   576,   576,   584,   584,
     596,   596,   608,   609,   613,   613,   621,   622,   625,   626,
     627,   628,   629,   630,   631,   634,   634,   642,   647,   647,
     655,   655,   665,   666,   669,   669,   677,   678,   681,   682,
     683,   684,   685,   688,   688,   696,   701,   706,   711,   711
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
#line 2231 "agent_parser.cc"

#line 719 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
