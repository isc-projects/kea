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
#line 113 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 388 "agent_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 113 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 394 "agent_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 113 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 400 "agent_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 113 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 406 "agent_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 113 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 412 "agent_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 113 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 418 "agent_parser.cc"
        break;

      case symbol_kind::S_socket_type_value: // socket_type_value
#line 113 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "agent_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 113 "agent_parser.yy"
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
#line 124 "agent_parser.yy"
                       { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 706 "agent_parser.cc"
    break;

  case 4: // $@2: %empty
#line 125 "agent_parser.yy"
                       { ctx.ctx_ = ctx.CONFIG; }
#line 712 "agent_parser.cc"
    break;

  case 6: // $@3: %empty
#line 126 "agent_parser.yy"
                       { ctx.ctx_ = ctx.AGENT; }
#line 718 "agent_parser.cc"
    break;

  case 8: // $@4: %empty
#line 134 "agent_parser.yy"
                          {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 728 "agent_parser.cc"
    break;

  case 9: // sub_agent: "{" $@4 global_params "}"
#line 138 "agent_parser.yy"
                               {
    // parsing completed
}
#line 736 "agent_parser.cc"
    break;

  case 10: // json: value
#line 145 "agent_parser.yy"
            {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 745 "agent_parser.cc"
    break;

  case 11: // value: "integer"
#line 151 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 751 "agent_parser.cc"
    break;

  case 12: // value: "floating point"
#line 152 "agent_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 757 "agent_parser.cc"
    break;

  case 13: // value: "boolean"
#line 153 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 763 "agent_parser.cc"
    break;

  case 14: // value: "constant string"
#line 154 "agent_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 769 "agent_parser.cc"
    break;

  case 15: // value: "null"
#line 155 "agent_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 775 "agent_parser.cc"
    break;

  case 16: // value: map
#line 156 "agent_parser.yy"
           { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 781 "agent_parser.cc"
    break;

  case 17: // value: list_generic
#line 157 "agent_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 787 "agent_parser.cc"
    break;

  case 18: // $@5: %empty
#line 161 "agent_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "agent_parser.cc"
    break;

  case 19: // map: "{" $@5 map_content "}"
#line 166 "agent_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "agent_parser.cc"
    break;

  case 20: // map_value: map
#line 172 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "agent_parser.cc"
    break;

  case 23: // not_empty_map: "constant string" ":" value
#line 186 "agent_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 824 "agent_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 191 "agent_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 835 "agent_parser.cc"
    break;

  case 25: // not_empty_map: not_empty_map ","
#line 197 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 843 "agent_parser.cc"
    break;

  case 26: // $@6: %empty
#line 202 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "agent_parser.cc"
    break;

  case 27: // list_generic: "[" $@6 list_content "]"
#line 205 "agent_parser.yy"
                               {
}
#line 859 "agent_parser.cc"
    break;

  case 30: // not_empty_list: value
#line 212 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 868 "agent_parser.cc"
    break;

  case 31: // not_empty_list: not_empty_list "," value
#line 216 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 877 "agent_parser.cc"
    break;

  case 32: // not_empty_list: not_empty_list ","
#line 220 "agent_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 885 "agent_parser.cc"
    break;

  case 33: // unknown_map_entry: "constant string" ":"
#line 232 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 896 "agent_parser.cc"
    break;

  case 34: // $@7: %empty
#line 240 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 907 "agent_parser.cc"
    break;

  case 35: // agent_syntax_map: "{" $@7 global_object "}"
#line 245 "agent_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 917 "agent_parser.cc"
    break;

  case 36: // $@8: %empty
#line 252 "agent_parser.yy"
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
#line 933 "agent_parser.cc"
    break;

  case 37: // global_object: "Control-agent" $@8 ":" "{" global_params "}"
#line 262 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 944 "agent_parser.cc"
    break;

  case 39: // global_object_comma: global_object ","
#line 271 "agent_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 952 "agent_parser.cc"
    break;

  case 42: // global_params: global_params ","
#line 277 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 960 "agent_parser.cc"
    break;

  case 56: // $@9: %empty
#line 299 "agent_parser.yy"
                     {
    ctx.unique("http-host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 969 "agent_parser.cc"
    break;

  case 57: // http_host: "http-host" $@9 ":" "constant string"
#line 302 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 979 "agent_parser.cc"
    break;

  case 58: // http_port: "http-port" ":" "integer"
#line 308 "agent_parser.yy"
                                   {
    ctx.unique("http-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 989 "agent_parser.cc"
    break;

  case 59: // $@10: %empty
#line 314 "agent_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 998 "agent_parser.cc"
    break;

  case 60: // trust_anchor: "trust-anchor" $@10 ":" "constant string"
#line 317 "agent_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 1008 "agent_parser.cc"
    break;

  case 61: // $@11: %empty
#line 323 "agent_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1017 "agent_parser.cc"
    break;

  case 62: // cert_file: "cert-file" $@11 ":" "constant string"
#line 326 "agent_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 1027 "agent_parser.cc"
    break;

  case 63: // $@12: %empty
#line 332 "agent_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1036 "agent_parser.cc"
    break;

  case 64: // key_file: "key-file" $@12 ":" "constant string"
#line 335 "agent_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 1046 "agent_parser.cc"
    break;

  case 65: // cert_required: "cert-required" ":" "boolean"
#line 341 "agent_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 1056 "agent_parser.cc"
    break;

  case 66: // $@13: %empty
#line 347 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1064 "agent_parser.cc"
    break;

  case 67: // user_context: "user-context" $@13 ":" map_value
#line 349 "agent_parser.yy"
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
#line 1091 "agent_parser.cc"
    break;

  case 68: // $@14: %empty
#line 372 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1099 "agent_parser.cc"
    break;

  case 69: // comment: "comment" $@14 ":" "constant string"
#line 374 "agent_parser.yy"
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
#line 1128 "agent_parser.cc"
    break;

  case 70: // $@15: %empty
#line 400 "agent_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1140 "agent_parser.cc"
    break;

  case 71: // hooks_libraries: "hooks-libraries" $@15 ":" "[" hooks_libraries_list "]"
#line 406 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1149 "agent_parser.cc"
    break;

  case 76: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 417 "agent_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 1157 "agent_parser.cc"
    break;

  case 77: // $@16: %empty
#line 422 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1167 "agent_parser.cc"
    break;

  case 78: // hooks_library: "{" $@16 hooks_params "}"
#line 426 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1175 "agent_parser.cc"
    break;

  case 81: // hooks_params: hooks_params ","
#line 432 "agent_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 1183 "agent_parser.cc"
    break;

  case 85: // $@17: %empty
#line 442 "agent_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1192 "agent_parser.cc"
    break;

  case 86: // library: "library" $@17 ":" "constant string"
#line 445 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1202 "agent_parser.cc"
    break;

  case 87: // $@18: %empty
#line 451 "agent_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1211 "agent_parser.cc"
    break;

  case 88: // parameters: "parameters" $@18 ":" map_value
#line 454 "agent_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1220 "agent_parser.cc"
    break;

  case 89: // $@19: %empty
#line 462 "agent_parser.yy"
                                                      {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[2].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1232 "agent_parser.cc"
    break;

  case 90: // control_sockets: "control-sockets" ":" "{" $@19 control_sockets_params "}"
#line 468 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1241 "agent_parser.cc"
    break;

  case 93: // control_sockets_params: control_sockets_params ","
#line 478 "agent_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1249 "agent_parser.cc"
    break;

  case 98: // $@20: %empty
#line 492 "agent_parser.yy"
                                  {
    ctx.unique("dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1261 "agent_parser.cc"
    break;

  case 99: // dhcp4_server_socket: "dhcp4" $@20 ":" "{" control_socket_params "}"
#line 498 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1270 "agent_parser.cc"
    break;

  case 100: // $@21: %empty
#line 504 "agent_parser.yy"
                                  {
    ctx.unique("dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1282 "agent_parser.cc"
    break;

  case 101: // dhcp6_server_socket: "dhcp6" $@21 ":" "{" control_socket_params "}"
#line 510 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1291 "agent_parser.cc"
    break;

  case 102: // $@22: %empty
#line 516 "agent_parser.yy"
                            {
    ctx.unique("d2", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1303 "agent_parser.cc"
    break;

  case 103: // d2_server_socket: "d2" $@22 ":" "{" control_socket_params "}"
#line 522 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1312 "agent_parser.cc"
    break;

  case 106: // control_socket_params: control_socket_params ","
#line 530 "agent_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1320 "agent_parser.cc"
    break;

  case 112: // $@23: %empty
#line 544 "agent_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1329 "agent_parser.cc"
    break;

  case 113: // socket_name: "socket-name" $@23 ":" "constant string"
#line 547 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1339 "agent_parser.cc"
    break;

  case 114: // $@24: %empty
#line 554 "agent_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1348 "agent_parser.cc"
    break;

  case 115: // socket_type: "socket-type" $@24 ":" socket_type_value
#line 557 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "agent_parser.cc"
    break;

  case 116: // socket_type_value: "unix"
#line 563 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1363 "agent_parser.cc"
    break;

  case 117: // $@25: %empty
#line 570 "agent_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 1375 "agent_parser.cc"
    break;

  case 118: // authentication: "authentication" $@25 ":" "{" auth_params "}"
#line 576 "agent_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1386 "agent_parser.cc"
    break;

  case 121: // auth_params: auth_params ","
#line 585 "agent_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 1394 "agent_parser.cc"
    break;

  case 128: // $@26: %empty
#line 598 "agent_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 1403 "agent_parser.cc"
    break;

  case 129: // auth_type: "type" $@26 ":" auth_type_value
#line 601 "agent_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1412 "agent_parser.cc"
    break;

  case 130: // auth_type_value: "basic"
#line 606 "agent_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 1418 "agent_parser.cc"
    break;

  case 131: // $@27: %empty
#line 609 "agent_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1427 "agent_parser.cc"
    break;

  case 132: // realm: "realm" $@27 ":" "constant string"
#line 612 "agent_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 1437 "agent_parser.cc"
    break;

  case 133: // $@28: %empty
#line 618 "agent_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 1449 "agent_parser.cc"
    break;

  case 134: // clients: "clients" $@28 ":" "[" clients_list "]"
#line 624 "agent_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1458 "agent_parser.cc"
    break;

  case 139: // not_empty_clients_list: not_empty_clients_list ","
#line 635 "agent_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1466 "agent_parser.cc"
    break;

  case 140: // $@29: %empty
#line 640 "agent_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1476 "agent_parser.cc"
    break;

  case 141: // basic_auth: "{" $@29 clients_params "}"
#line 644 "agent_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 1484 "agent_parser.cc"
    break;

  case 144: // clients_params: clients_params ","
#line 650 "agent_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1492 "agent_parser.cc"
    break;

  case 150: // $@30: %empty
#line 662 "agent_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1501 "agent_parser.cc"
    break;

  case 151: // user: "user" $@30 ":" "constant string"
#line 665 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1511 "agent_parser.cc"
    break;

  case 152: // $@31: %empty
#line 671 "agent_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1520 "agent_parser.cc"
    break;

  case 153: // password: "password" $@31 ":" "constant string"
#line 674 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", password);
    ctx.leave();
}
#line 1530 "agent_parser.cc"
    break;

  case 154: // $@32: %empty
#line 684 "agent_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1542 "agent_parser.cc"
    break;

  case 155: // loggers: "loggers" $@32 ":" "[" loggers_entries "]"
#line 690 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "agent_parser.cc"
    break;

  case 158: // loggers_entries: loggers_entries ","
#line 699 "agent_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1559 "agent_parser.cc"
    break;

  case 159: // $@33: %empty
#line 705 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1569 "agent_parser.cc"
    break;

  case 160: // logger_entry: "{" $@33 logger_params "}"
#line 709 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1577 "agent_parser.cc"
    break;

  case 163: // logger_params: logger_params ","
#line 715 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1585 "agent_parser.cc"
    break;

  case 171: // $@34: %empty
#line 729 "agent_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1594 "agent_parser.cc"
    break;

  case 172: // name: "name" $@34 ":" "constant string"
#line 732 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1604 "agent_parser.cc"
    break;

  case 173: // debuglevel: "debuglevel" ":" "integer"
#line 738 "agent_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1614 "agent_parser.cc"
    break;

  case 174: // $@35: %empty
#line 744 "agent_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1623 "agent_parser.cc"
    break;

  case 175: // severity: "severity" $@35 ":" "constant string"
#line 747 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1633 "agent_parser.cc"
    break;

  case 176: // $@36: %empty
#line 753 "agent_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1645 "agent_parser.cc"
    break;

  case 177: // output_options_list: "output_options" $@36 ":" "[" output_options_list_content "]"
#line 759 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1654 "agent_parser.cc"
    break;

  case 180: // output_options_list_content: output_options_list_content ","
#line 766 "agent_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 1662 "agent_parser.cc"
    break;

  case 181: // $@37: %empty
#line 771 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1672 "agent_parser.cc"
    break;

  case 182: // output_entry: "{" $@37 output_params_list "}"
#line 775 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1680 "agent_parser.cc"
    break;

  case 185: // output_params_list: output_params_list ","
#line 781 "agent_parser.yy"
                                        {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1688 "agent_parser.cc"
    break;

  case 191: // $@38: %empty
#line 793 "agent_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1697 "agent_parser.cc"
    break;

  case 192: // output: "output" $@38 ":" "constant string"
#line 796 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1707 "agent_parser.cc"
    break;

  case 193: // flush: "flush" ":" "boolean"
#line 802 "agent_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1717 "agent_parser.cc"
    break;

  case 194: // maxsize: "maxsize" ":" "integer"
#line 808 "agent_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1727 "agent_parser.cc"
    break;

  case 195: // maxver: "maxver" ":" "integer"
#line 814 "agent_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1737 "agent_parser.cc"
    break;

  case 196: // $@39: %empty
#line 820 "agent_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1746 "agent_parser.cc"
    break;

  case 197: // pattern: "pattern" $@39 ":" "constant string"
#line 823 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1756 "agent_parser.cc"
    break;


#line 1760 "agent_parser.cc"

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


  const short AgentParser::yypact_ninf_ = -159;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      28,  -159,  -159,  -159,     5,     2,     3,    51,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,     2,     7,    79,     1,  -159,    84,
      89,   109,   104,   114,  -159,     0,  -159,  -159,   115,  -159,
    -159,  -159,  -159,  -159,  -159,   116,   117,  -159,  -159,   118,
    -159,    37,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,     2,     2,  -159,    69,
     119,  -159,  -159,   123,    78,   126,   128,   129,   134,   135,
     136,    90,   137,   139,   141,  -159,     1,  -159,  -159,  -159,
     142,   140,    92,  -159,   143,   102,   145,   105,   110,   111,
    -159,  -159,   144,   148,  -159,     2,     1,  -159,  -159,  -159,
    -159,    17,  -159,  -159,  -159,    44,   149,   150,  -159,    74,
    -159,  -159,  -159,  -159,  -159,  -159,    75,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,    96,  -159,  -159,  -159,  -159,
    -159,   152,   158,  -159,  -159,    61,  -159,  -159,   151,   159,
     160,    17,  -159,   161,   162,   163,    44,  -159,   -17,  -159,
     149,     6,   150,  -159,   131,   113,   164,  -159,   165,   166,
     167,  -159,  -159,  -159,  -159,    97,  -159,  -159,  -159,  -159,
    -159,  -159,   171,  -159,  -159,  -159,  -159,    98,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,   169,     8,     8,
       8,   173,   174,    -6,  -159,   175,   176,   120,   177,     6,
    -159,  -159,   179,   168,  -159,  -159,  -159,  -159,  -159,  -159,
      99,  -159,  -159,  -159,   100,   106,   138,   143,  -159,   146,
     181,  -159,   147,  -159,    49,  -159,   169,   184,   185,     8,
    -159,  -159,  -159,  -159,  -159,  -159,   183,  -159,  -159,  -159,
    -159,  -159,  -159,   107,  -159,  -159,  -159,  -159,   153,   172,
    -159,  -159,    62,  -159,   187,   188,    49,  -159,  -159,  -159,
    -159,    52,   183,  -159,   154,   156,  -159,  -159,   189,   190,
     193,  -159,   108,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,   194,   170,   178,   180,   195,    52,  -159,   157,
    -159,  -159,  -159,   182,  -159,  -159,  -159
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    26,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      34,     5,     8,     7,    28,    21,     0,     0,    30,     0,
      29,     0,     0,    22,    36,     0,    38,    56,     0,    66,
      68,   117,    59,    61,    63,     0,     0,    70,   154,     0,
      55,     0,    40,    43,    44,    45,    46,    47,    48,    53,
      54,    51,    50,    49,    52,    27,    32,     0,    19,    25,
       0,    39,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    42,     9,    31,    23,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
      65,    89,     0,     0,    41,     0,     0,    57,    20,    67,
      69,     0,    60,    62,    64,     0,    72,     0,    24,     0,
     128,   131,   133,   127,   126,   125,     0,   119,   122,   123,
     124,    98,   100,   102,    97,     0,    91,    94,    95,    96,
      77,     0,    73,    74,   159,     0,   156,    37,     0,     0,
       0,   121,   118,     0,     0,     0,    93,    90,     0,    71,
      76,     0,   158,   155,     0,     0,     0,   120,     0,     0,
       0,    92,    85,    87,    82,     0,    79,    83,    84,    75,
     171,   176,     0,   174,   170,   168,   169,     0,   161,   164,
     166,   167,   165,   157,   130,   129,   132,   135,     0,     0,
       0,     0,     0,    81,    78,     0,     0,     0,     0,   163,
     160,   140,     0,   136,   137,   112,   114,   111,   109,   110,
       0,   104,   107,   108,     0,     0,     0,     0,    80,     0,
       0,   173,     0,   162,     0,   134,   139,     0,     0,   106,
      99,   101,   103,    86,    88,   172,     0,   175,   150,   152,
     149,   147,   148,     0,   142,   145,   146,   138,     0,     0,
     105,   181,     0,   178,     0,     0,   144,   141,   113,   116,
     115,     0,   180,   177,     0,     0,   143,   191,     0,     0,
       0,   196,     0,   183,   186,   187,   188,   189,   190,   179,
     151,   153,     0,     0,     0,     0,     0,   185,   182,     0,
     193,   194,   195,     0,   184,   192,   197
  };

  const short
  AgentParser::yypgoto_[] =
  {
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,   -18,   -90,
    -159,   -59,  -159,  -159,  -159,  -159,  -159,  -159,   -27,  -159,
    -159,  -159,  -159,  -159,    94,   124,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,   -26,  -159,   -25,  -159,
    -159,  -159,  -159,  -159,    41,  -159,  -159,     9,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,    55,  -159,  -159,  -159,  -159,
    -159,  -159,  -158,   -24,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,    63,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,   -23,  -159,  -159,   -50,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,    56,  -159,  -159,    10,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,   -55,  -159,  -159,   -77,  -159,
    -159,  -159,  -159,  -159,  -159,  -159
  };

  const short
  AgentParser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,   109,    32,    33,    19,    24,    29,    30,   217,    21,
      26,    35,    70,    36,    51,    52,    53,    73,    54,    55,
      78,    56,    79,    57,    80,    58,   218,    75,   219,    76,
      61,    83,   141,   142,   143,   158,   175,   176,   177,   201,
     178,   202,    62,   115,   135,   136,   137,   153,   138,   154,
     139,   155,   220,   221,   222,   237,   223,   238,   270,    63,
      77,   126,   127,   128,   148,   195,   129,   149,   130,   150,
     212,   213,   214,   234,   253,   254,   255,   264,   256,   265,
      64,    84,   145,   146,   161,   187,   188,   189,   205,   190,
     191,   208,   192,   206,   262,   263,   271,   282,   283,   284,
     292,   285,   286,   287,   288,   296
  };

  const short
  AgentParser::yytable_[] =
  {
      50,    59,    60,    71,   108,     8,    28,     9,    72,    10,
      20,    11,    37,    38,    39,    40,    41,   172,   173,    39,
      40,    39,    40,    42,    43,    44,    45,    46,   172,   173,
      39,    40,    49,   120,    47,   121,   122,    48,   215,   216,
      86,   224,   225,   180,   181,    87,   182,   183,    88,    89,
      49,    12,    13,    14,    15,    49,    31,    49,    22,    50,
      59,    60,    39,    40,   162,   272,    49,   163,   273,   248,
     249,   131,   132,   133,     1,     2,     3,    86,   151,    50,
      59,    60,   147,   152,   123,   124,   125,   118,   134,    34,
      65,   277,    66,    49,   278,   279,   280,   281,    49,   156,
     203,   209,   239,   239,   157,   204,   210,   240,   241,   239,
     266,   297,    68,    67,   242,   267,   298,    69,    90,    74,
      81,    82,    85,    91,   123,   124,   125,    92,    93,   134,
      94,   174,    95,    96,   184,   185,   186,   108,    97,    98,
      99,   107,   100,   102,   101,   103,   105,   106,   194,   116,
      10,   110,   111,   117,   112,   164,   140,   144,   159,   113,
     114,   160,   196,   165,   166,   168,   169,   170,   244,   197,
     231,   236,   198,   199,   200,   207,   211,   226,   227,   229,
     230,   232,   184,   185,   186,   235,   246,   243,   258,   259,
     261,   274,   275,   293,   294,   245,   247,   295,   299,   303,
     119,   179,   268,   290,   269,   291,   305,   250,   251,   252,
     104,   171,   228,   257,   167,   260,   276,   289,   193,   233,
     304,     0,   300,     0,     0,     0,     0,     0,   301,     0,
     302,   306,     0,     0,     0,     0,     0,     0,     0,   250,
     251,   252
  };

  const short
  AgentParser::yycheck_[] =
  {
      27,    27,    27,     3,    94,     0,    24,     5,     8,     7,
       7,     9,    11,    12,    13,    14,    15,    34,    35,    13,
      14,    13,    14,    22,    23,    24,    25,    26,    34,    35,
      13,    14,    49,    16,    33,    18,    19,    36,    30,    31,
       3,   199,   200,    37,    38,     8,    40,    41,    66,    67,
      49,    49,    50,    51,    52,    49,    49,    49,     7,    86,
      86,    86,    13,    14,     3,     3,    49,     6,     6,    20,
      21,    27,    28,    29,    46,    47,    48,     3,     3,   106,
     106,   106,     8,     8,   111,   111,   111,   105,   115,    10,
       6,    39,     3,    49,    42,    43,    44,    45,    49,     3,
       3,     3,     3,     3,     8,     8,     8,     8,     8,     3,
       3,     3,     8,     4,     8,     8,     8,     3,    49,     4,
       4,     4,     4,     4,   151,   151,   151,     4,    50,   156,
       4,   158,     4,     4,   161,   161,   161,   227,     4,     4,
       4,    49,    52,     4,     7,     4,     4,     7,    17,     5,
       7,    49,     7,     5,    49,     4,     7,     7,     6,    49,
      49,     3,    49,     4,     4,     4,     4,     4,   227,     5,
      50,     3,     7,     7,     7,     4,     7,     4,     4,     4,
       4,     4,   209,   209,   209,     6,     5,    49,     4,     4,
       7,     4,     4,     4,     4,    49,    49,     4,     4,     4,
     106,   160,    49,    49,    32,    49,    49,   234,   234,   234,
      86,   156,   203,   236,   151,   239,   266,   272,   162,   209,
     297,    -1,    52,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      50,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   266,
     266,   266
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    46,    47,    48,    54,    55,    56,    57,     0,     5,
       7,     9,    49,    50,    51,    52,    60,    61,    62,    67,
       7,    72,     7,    58,    68,    63,    73,    59,    61,    69,
      70,    49,    65,    66,    10,    74,    76,    11,    12,    13,
      14,    15,    22,    23,    24,    25,    26,    33,    36,    49,
      71,    77,    78,    79,    81,    82,    84,    86,    88,    89,
      91,    93,   105,   122,   143,     6,     3,     4,     8,     3,
      75,     3,     8,    80,     4,    90,    92,   123,    83,    85,
      87,     4,     4,    94,   144,     4,     3,     8,    61,    61,
      49,     4,     4,    50,     4,     4,     4,     4,     4,     4,
      52,     7,     4,     4,    78,     4,     7,    49,    62,    64,
      49,     7,    49,    49,    49,   106,     5,     5,    61,    77,
      16,    18,    19,    71,    89,    91,   124,   125,   126,   129,
     131,    27,    28,    29,    71,   107,   108,   109,   111,   113,
       7,    95,    96,    97,     7,   145,   146,     8,   127,   130,
     132,     3,     8,   110,   112,   114,     3,     8,    98,     6,
       3,   147,     3,     6,     4,     4,     4,   125,     4,     4,
       4,   108,    34,    35,    71,    99,   100,   101,   103,    97,
      37,    38,    40,    41,    71,    89,    91,   148,   149,   150,
     152,   153,   155,   146,    17,   128,    49,     5,     7,     7,
       7,   102,   104,     3,     8,   151,   156,     4,   154,     3,
       8,     7,   133,   134,   135,    30,    31,    71,    89,    91,
     115,   116,   117,   119,   115,   115,     4,     4,   100,     4,
       4,    50,     4,   149,   136,     6,     3,   118,   120,     3,
       8,     8,     8,    49,    64,    49,     5,    49,    20,    21,
      71,    89,    91,   137,   138,   139,   141,   135,     4,     4,
     116,     7,   157,   158,   140,   142,     3,     8,    49,    32,
     121,   159,     3,     6,     4,     4,   138,    39,    42,    43,
      44,    45,   160,   161,   162,   164,   165,   166,   167,   158,
      49,    49,   163,     4,     4,     4,   168,     3,     8,     4,
      52,    50,    50,     4,   161,    49,    49
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    53,    55,    54,    56,    54,    57,    54,    59,    58,
      60,    61,    61,    61,    61,    61,    61,    61,    63,    62,
      64,    65,    65,    66,    66,    66,    68,    67,    69,    69,
      70,    70,    70,    71,    73,    72,    75,    74,    74,    76,
      77,    77,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    80,    79,    81,    83,
      82,    85,    84,    87,    86,    88,    90,    89,    92,    91,
      94,    93,    95,    95,    96,    96,    96,    98,    97,    99,
      99,    99,    99,   100,   100,   102,   101,   104,   103,   106,
     105,   107,   107,   107,   108,   108,   108,   108,   110,   109,
     112,   111,   114,   113,   115,   115,   115,   116,   116,   116,
     116,   116,   118,   117,   120,   119,   121,   123,   122,   124,
     124,   124,   125,   125,   125,   125,   125,   125,   127,   126,
     128,   130,   129,   132,   131,   133,   133,   134,   134,   134,
     136,   135,   137,   137,   137,   138,   138,   138,   138,   138,
     140,   139,   142,   141,   144,   143,   145,   145,   145,   147,
     146,   148,   148,   148,   149,   149,   149,   149,   149,   149,
     149,   151,   150,   152,   154,   153,   156,   155,   157,   157,
     157,   159,   158,   160,   160,   160,   161,   161,   161,   161,
     161,   163,   162,   164,   165,   166,   168,   167
  };

  const signed char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     2,     0,     4,     0,     1,
       1,     3,     2,     2,     0,     4,     0,     6,     1,     2,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     0,     6,
       0,     6,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     1,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     6,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
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
  "\"authentication\"", "\"type\"", "\"basic\"", "\"realm\"",
  "\"clients\"", "\"user\"", "\"password\"", "\"trust-anchor\"",
  "\"cert-file\"", "\"key-file\"", "\"cert-required\"",
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
  "global_object", "$@8", "global_object_comma", "global_params",
  "global_param", "http_host", "$@9", "http_port", "trust_anchor", "$@10",
  "cert_file", "$@11", "key_file", "$@12", "cert_required", "user_context",
  "$@13", "comment", "$@14", "hooks_libraries", "$@15",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@16", "hooks_params", "hooks_param", "library",
  "$@17", "parameters", "$@18", "control_sockets", "$@19",
  "control_sockets_params", "control_socket", "dhcp4_server_socket",
  "$@20", "dhcp6_server_socket", "$@21", "d2_server_socket", "$@22",
  "control_socket_params", "control_socket_param", "socket_name", "$@23",
  "socket_type", "$@24", "socket_type_value", "authentication", "$@25",
  "auth_params", "auth_param", "auth_type", "$@26", "auth_type_value",
  "realm", "$@27", "clients", "$@28", "clients_list",
  "not_empty_clients_list", "basic_auth", "$@29", "clients_params",
  "clients_param", "user", "$@30", "password", "$@31", "loggers", "$@32",
  "loggers_entries", "logger_entry", "$@33", "logger_params",
  "logger_param", "name", "$@34", "debuglevel", "severity", "$@35",
  "output_options_list", "$@36", "output_options_list_content",
  "output_entry", "$@37", "output_params_list", "output_params", "output",
  "$@38", "flush", "maxsize", "maxver", "pattern", "$@39", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   124,   124,   124,   125,   125,   126,   126,   134,   134,
     145,   151,   152,   153,   154,   155,   156,   157,   161,   161,
     172,   177,   178,   186,   191,   197,   202,   202,   208,   209,
     212,   216,   220,   232,   240,   240,   252,   252,   268,   271,
     275,   276,   277,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   299,   299,   308,   314,
     314,   323,   323,   332,   332,   341,   347,   347,   372,   372,
     400,   400,   411,   412,   415,   416,   417,   422,   422,   430,
     431,   432,   435,   438,   439,   442,   442,   451,   451,   462,
     462,   476,   477,   478,   485,   486,   487,   488,   492,   492,
     504,   504,   516,   516,   528,   529,   530,   536,   537,   538,
     539,   540,   544,   544,   554,   554,   563,   570,   570,   583,
     584,   585,   590,   591,   592,   593,   594,   595,   598,   598,
     606,   609,   609,   618,   618,   629,   630,   633,   634,   635,
     640,   640,   648,   649,   650,   655,   656,   657,   658,   659,
     662,   662,   671,   671,   684,   684,   697,   698,   699,   705,
     705,   713,   714,   715,   720,   721,   722,   723,   724,   725,
     726,   729,   729,   738,   744,   744,   753,   753,   764,   765,
     766,   771,   771,   779,   780,   781,   786,   787,   788,   789,
     790,   793,   793,   802,   808,   814,   820,   820
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
#line 2471 "agent_parser.cc"

#line 829 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
