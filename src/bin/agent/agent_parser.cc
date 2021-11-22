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

  case 25: // $@6: %empty
#line 199 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 844 "agent_parser.cc"
    break;

  case 26: // list_generic: "[" $@6 list_content "]"
#line 202 "agent_parser.yy"
                               {
}
#line 851 "agent_parser.cc"
    break;

  case 29: // not_empty_list: value
#line 209 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 860 "agent_parser.cc"
    break;

  case 30: // not_empty_list: not_empty_list "," value
#line 213 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 869 "agent_parser.cc"
    break;

  case 31: // unknown_map_entry: "constant string" ":"
#line 226 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 880 "agent_parser.cc"
    break;

  case 32: // $@7: %empty
#line 234 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 891 "agent_parser.cc"
    break;

  case 33: // agent_syntax_map: "{" $@7 global_object "}"
#line 239 "agent_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 901 "agent_parser.cc"
    break;

  case 34: // $@8: %empty
#line 246 "agent_parser.yy"
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
#line 257 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 929 "agent_parser.cc"
    break;

  case 51: // $@9: %empty
#line 285 "agent_parser.yy"
                     {
    ctx.unique("http-host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 938 "agent_parser.cc"
    break;

  case 52: // http_host: "http-host" $@9 ":" "constant string"
#line 288 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 948 "agent_parser.cc"
    break;

  case 53: // http_port: "http-port" ":" "integer"
#line 294 "agent_parser.yy"
                                   {
    ctx.unique("http-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 958 "agent_parser.cc"
    break;

  case 54: // $@10: %empty
#line 300 "agent_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 967 "agent_parser.cc"
    break;

  case 55: // trust_anchor: "trust-anchor" $@10 ":" "constant string"
#line 303 "agent_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 977 "agent_parser.cc"
    break;

  case 56: // $@11: %empty
#line 309 "agent_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 986 "agent_parser.cc"
    break;

  case 57: // cert_file: "cert-file" $@11 ":" "constant string"
#line 312 "agent_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 996 "agent_parser.cc"
    break;

  case 58: // $@12: %empty
#line 318 "agent_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1005 "agent_parser.cc"
    break;

  case 59: // key_file: "key-file" $@12 ":" "constant string"
#line 321 "agent_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 1015 "agent_parser.cc"
    break;

  case 60: // cert_required: "cert-required" ":" "boolean"
#line 327 "agent_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 1025 "agent_parser.cc"
    break;

  case 61: // $@13: %empty
#line 333 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1033 "agent_parser.cc"
    break;

  case 62: // user_context: "user-context" $@13 ":" map_value
#line 335 "agent_parser.yy"
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
#line 1060 "agent_parser.cc"
    break;

  case 63: // $@14: %empty
#line 358 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1068 "agent_parser.cc"
    break;

  case 64: // comment: "comment" $@14 ":" "constant string"
#line 360 "agent_parser.yy"
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
#line 1097 "agent_parser.cc"
    break;

  case 65: // $@15: %empty
#line 386 "agent_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1109 "agent_parser.cc"
    break;

  case 66: // hooks_libraries: "hooks-libraries" $@15 ":" "[" hooks_libraries_list "]"
#line 392 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1118 "agent_parser.cc"
    break;

  case 71: // $@16: %empty
#line 405 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1128 "agent_parser.cc"
    break;

  case 72: // hooks_library: "{" $@16 hooks_params "}"
#line 409 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1136 "agent_parser.cc"
    break;

  case 78: // $@17: %empty
#line 422 "agent_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1145 "agent_parser.cc"
    break;

  case 79: // library: "library" $@17 ":" "constant string"
#line 425 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1155 "agent_parser.cc"
    break;

  case 80: // $@18: %empty
#line 431 "agent_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1164 "agent_parser.cc"
    break;

  case 81: // parameters: "parameters" $@18 ":" map_value
#line 434 "agent_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1173 "agent_parser.cc"
    break;

  case 82: // $@19: %empty
#line 442 "agent_parser.yy"
                                                      {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[2].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1185 "agent_parser.cc"
    break;

  case 83: // control_sockets: "control-sockets" ":" "{" $@19 control_sockets_params "}"
#line 448 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1194 "agent_parser.cc"
    break;

  case 90: // $@20: %empty
#line 469 "agent_parser.yy"
                                  {
    ctx.unique("dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1206 "agent_parser.cc"
    break;

  case 91: // dhcp4_server_socket: "dhcp4" $@20 ":" "{" control_socket_params "}"
#line 475 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1215 "agent_parser.cc"
    break;

  case 92: // $@21: %empty
#line 481 "agent_parser.yy"
                                  {
    ctx.unique("dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1227 "agent_parser.cc"
    break;

  case 93: // dhcp6_server_socket: "dhcp6" $@21 ":" "{" control_socket_params "}"
#line 487 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1236 "agent_parser.cc"
    break;

  case 94: // $@22: %empty
#line 493 "agent_parser.yy"
                            {
    ctx.unique("d2", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1248 "agent_parser.cc"
    break;

  case 95: // d2_server_socket: "d2" $@22 ":" "{" control_socket_params "}"
#line 499 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1257 "agent_parser.cc"
    break;

  case 103: // $@23: %empty
#line 518 "agent_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1266 "agent_parser.cc"
    break;

  case 104: // socket_name: "socket-name" $@23 ":" "constant string"
#line 521 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1276 "agent_parser.cc"
    break;

  case 105: // $@24: %empty
#line 528 "agent_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1285 "agent_parser.cc"
    break;

  case 106: // socket_type: "socket-type" $@24 ":" socket_type_value
#line 531 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1294 "agent_parser.cc"
    break;

  case 107: // socket_type_value: "unix"
#line 537 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1300 "agent_parser.cc"
    break;

  case 108: // $@25: %empty
#line 544 "agent_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 1312 "agent_parser.cc"
    break;

  case 109: // authentication: "authentication" $@25 ":" "{" auth_params "}"
#line 550 "agent_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1323 "agent_parser.cc"
    break;

  case 118: // $@26: %empty
#line 569 "agent_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 1332 "agent_parser.cc"
    break;

  case 119: // auth_type: "type" $@26 ":" auth_type_value
#line 572 "agent_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1341 "agent_parser.cc"
    break;

  case 120: // auth_type_value: "basic"
#line 577 "agent_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 1347 "agent_parser.cc"
    break;

  case 121: // $@27: %empty
#line 580 "agent_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1356 "agent_parser.cc"
    break;

  case 122: // realm: "realm" $@27 ":" "constant string"
#line 583 "agent_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 1366 "agent_parser.cc"
    break;

  case 123: // $@28: %empty
#line 589 "agent_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 1378 "agent_parser.cc"
    break;

  case 124: // clients: "clients" $@28 ":" "[" clients_list "]"
#line 595 "agent_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1387 "agent_parser.cc"
    break;

  case 129: // $@29: %empty
#line 608 "agent_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1397 "agent_parser.cc"
    break;

  case 130: // basic_auth: "{" $@29 clients_params "}"
#line 612 "agent_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 1405 "agent_parser.cc"
    break;

  case 138: // $@30: %empty
#line 627 "agent_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1414 "agent_parser.cc"
    break;

  case 139: // user: "user" $@30 ":" "constant string"
#line 630 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1424 "agent_parser.cc"
    break;

  case 140: // $@31: %empty
#line 636 "agent_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1433 "agent_parser.cc"
    break;

  case 141: // password: "password" $@31 ":" "constant string"
#line 639 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", password);
    ctx.leave();
}
#line 1443 "agent_parser.cc"
    break;

  case 142: // $@32: %empty
#line 649 "agent_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1455 "agent_parser.cc"
    break;

  case 143: // loggers: "loggers" $@32 ":" "[" loggers_entries "]"
#line 655 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1464 "agent_parser.cc"
    break;

  case 146: // $@33: %empty
#line 667 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1474 "agent_parser.cc"
    break;

  case 147: // logger_entry: "{" $@33 logger_params "}"
#line 671 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1482 "agent_parser.cc"
    break;

  case 157: // $@34: %empty
#line 688 "agent_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1491 "agent_parser.cc"
    break;

  case 158: // name: "name" $@34 ":" "constant string"
#line 691 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1501 "agent_parser.cc"
    break;

  case 159: // debuglevel: "debuglevel" ":" "integer"
#line 697 "agent_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1511 "agent_parser.cc"
    break;

  case 160: // $@35: %empty
#line 703 "agent_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1520 "agent_parser.cc"
    break;

  case 161: // severity: "severity" $@35 ":" "constant string"
#line 706 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1530 "agent_parser.cc"
    break;

  case 162: // $@36: %empty
#line 712 "agent_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1542 "agent_parser.cc"
    break;

  case 163: // output_options_list: "output_options" $@36 ":" "[" output_options_list_content "]"
#line 718 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "agent_parser.cc"
    break;

  case 166: // $@37: %empty
#line 727 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1561 "agent_parser.cc"
    break;

  case 167: // output_entry: "{" $@37 output_params_list "}"
#line 731 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1569 "agent_parser.cc"
    break;

  case 175: // $@38: %empty
#line 746 "agent_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1578 "agent_parser.cc"
    break;

  case 176: // output: "output" $@38 ":" "constant string"
#line 749 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1588 "agent_parser.cc"
    break;

  case 177: // flush: "flush" ":" "boolean"
#line 755 "agent_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1598 "agent_parser.cc"
    break;

  case 178: // maxsize: "maxsize" ":" "integer"
#line 761 "agent_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1608 "agent_parser.cc"
    break;

  case 179: // maxver: "maxver" ":" "integer"
#line 767 "agent_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1618 "agent_parser.cc"
    break;

  case 180: // $@39: %empty
#line 773 "agent_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1627 "agent_parser.cc"
    break;

  case 181: // pattern: "pattern" $@39 ":" "constant string"
#line 776 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1637 "agent_parser.cc"
    break;


#line 1641 "agent_parser.cc"

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


  const short AgentParser::yypact_ninf_ = -165;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      71,  -165,  -165,  -165,    14,     0,    -3,    37,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,     0,    -4,    44,     4,  -165,    49,
      72,    86,    90,   106,  -165,   102,  -165,   109,  -165,  -165,
    -165,  -165,  -165,  -165,   110,   111,  -165,  -165,   116,  -165,
       5,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,     0,     0,  -165,    76,   117,
    -165,   122,    78,   126,   127,   131,   133,   134,   135,    89,
     136,   138,   140,  -165,     4,  -165,  -165,  -165,   141,   139,
      91,  -165,   142,    99,   143,   103,   107,   108,  -165,  -165,
     146,   148,  -165,     0,     4,  -165,  -165,  -165,  -165,    54,
    -165,  -165,  -165,   -17,   147,   151,  -165,    28,  -165,  -165,
    -165,  -165,  -165,  -165,    53,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,    61,  -165,  -165,  -165,  -165,  -165,   149,
     144,  -165,  -165,    40,  -165,  -165,   155,   156,   157,    54,
    -165,   158,   159,   160,   -17,  -165,   -14,  -165,   147,    25,
     151,  -165,   150,   119,   161,  -165,   162,   163,   164,  -165,
    -165,  -165,  -165,    68,  -165,  -165,  -165,  -165,  -165,  -165,
     168,  -165,  -165,  -165,  -165,    88,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,   166,    11,    11,    11,   170,
     171,   -12,  -165,   172,   173,   115,   174,    25,  -165,  -165,
     177,   176,  -165,  -165,  -165,  -165,  -165,  -165,    94,  -165,
    -165,  -165,    96,    97,   137,   142,  -165,   145,   179,  -165,
     152,  -165,    67,  -165,   166,   181,   183,    11,  -165,  -165,
    -165,  -165,  -165,  -165,   182,  -165,  -165,  -165,  -165,  -165,
    -165,    98,  -165,  -165,  -165,  -165,   153,   165,  -165,  -165,
     105,  -165,   184,   186,    67,  -165,  -165,  -165,  -165,    50,
     182,  -165,   154,   167,  -165,  -165,   187,   188,   189,  -165,
     104,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
     191,   169,   175,   178,   192,    50,  -165,   180,  -165,  -165,
    -165,   185,  -165,  -165,  -165
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    34,     0,    51,     0,    61,    63,
     108,    54,    56,    58,     0,     0,    65,   142,     0,    50,
       0,    36,    38,    39,    40,    41,    42,    43,    48,    49,
      46,    45,    44,    47,    26,     0,     0,    19,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     9,    30,    23,     0,     0,
       0,    53,     0,     0,     0,     0,     0,     0,    60,    82,
       0,     0,    37,     0,     0,    52,    20,    62,    64,     0,
      55,    57,    59,     0,    67,     0,    24,     0,   118,   121,
     123,   117,   116,   115,     0,   110,   112,   113,   114,    90,
      92,    94,    89,     0,    84,    86,    87,    88,    71,     0,
      68,    69,   146,     0,   144,    35,     0,     0,     0,     0,
     109,     0,     0,     0,     0,    83,     0,    66,     0,     0,
       0,   143,     0,     0,     0,   111,     0,     0,     0,    85,
      78,    80,    75,     0,    73,    76,    77,    70,   157,   162,
       0,   160,   156,   154,   155,     0,   148,   150,   152,   153,
     151,   145,   120,   119,   122,   125,     0,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,   147,   129,
       0,   126,   127,   103,   105,   102,   100,   101,     0,    96,
      98,    99,     0,     0,     0,     0,    74,     0,     0,   159,
       0,   149,     0,   124,     0,     0,     0,     0,    91,    93,
      95,    79,    81,   158,     0,   161,   138,   140,   137,   135,
     136,     0,   131,   133,   134,   128,     0,     0,    97,   166,
       0,   164,     0,     0,     0,   130,   104,   107,   106,     0,
       0,   163,     0,     0,   132,   175,     0,     0,     0,   180,
       0,   168,   170,   171,   172,   173,   174,   165,   139,   141,
       0,     0,     0,     0,     0,     0,   167,     0,   177,   178,
     179,     0,   169,   176,   181
  };

  const short
  AgentParser::yypgoto_[] =
  {
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   -18,   -89,
    -165,   -21,  -165,  -165,  -165,  -165,  -165,  -165,   -27,  -165,
    -165,  -165,  -165,    95,   114,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,   -26,  -165,   -25,  -165,  -165,
    -165,  -165,  -165,    42,  -165,  -165,     7,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,    55,  -165,  -165,  -165,  -165,  -165,
    -165,  -164,   -24,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,    62,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,   -22,  -165,  -165,   -54,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,    57,  -165,  -165,     8,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   -56,  -165,  -165,   -77,  -165,  -165,
    -165,  -165,  -165,  -165,  -165
  };

  const short
  AgentParser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,   107,    32,    33,    19,    24,    29,    30,   215,    21,
      26,    35,    69,    50,    51,    52,    71,    53,    54,    76,
      55,    77,    56,    78,    57,   216,    73,   217,    74,    60,
      81,   139,   140,   141,   156,   173,   174,   175,   199,   176,
     200,    61,   113,   133,   134,   135,   151,   136,   152,   137,
     153,   218,   219,   220,   235,   221,   236,   268,    62,    75,
     124,   125,   126,   146,   193,   127,   147,   128,   148,   210,
     211,   212,   232,   251,   252,   253,   262,   254,   263,    63,
      82,   143,   144,   159,   185,   186,   187,   203,   188,   189,
     206,   190,   204,   260,   261,   269,   280,   281,   282,   290,
     283,   284,   285,   286,   294
  };

  const short
  AgentParser::yytable_[] =
  {
      49,    58,    59,   106,    20,     9,    28,    10,    84,    11,
     129,   130,   131,    85,     8,    36,    37,    38,    39,    40,
     170,   171,   170,   171,    38,    39,    41,    42,    43,    44,
      45,    84,    48,   222,   223,    48,   145,    46,    38,    39,
      47,   213,   214,   160,    22,    31,   161,    86,    87,    12,
      13,    14,    15,    48,    34,    64,   149,    49,    58,    59,
      48,   150,   178,   179,   154,   180,   181,    38,    39,   155,
     118,   201,   119,   120,    48,    65,   202,    49,    58,    59,
      38,    39,   121,   122,   123,   116,   132,   246,   247,   275,
      66,   207,   276,   277,   278,   279,   208,   237,    67,   237,
     237,   264,   238,    48,   239,   240,   265,   295,   270,    68,
      70,   271,   296,    72,    79,    80,    48,     1,     2,     3,
      83,    89,   121,   122,   123,    88,    90,   132,    91,   172,
      92,    93,   182,   183,   184,    94,   106,    95,    96,    97,
     105,    98,   100,    99,   101,   103,   104,   158,   108,    10,
     109,   114,   110,   115,   138,   157,   111,   112,   142,   162,
     163,   164,   166,   167,   168,   229,   195,   192,   194,   196,
     197,   198,   205,   209,   224,   225,   227,   228,   230,   234,
     182,   183,   184,   233,   244,   256,   241,   257,   272,   259,
     273,   291,   292,   293,   243,   297,   301,   267,   102,   117,
     177,   245,   266,   288,   242,   248,   249,   250,   226,   169,
     274,   165,   255,   258,   287,   231,   289,   191,   302,     0,
       0,   298,     0,     0,     0,   299,     0,     0,   300,   303,
       0,     0,     0,     0,   304,     0,     0,   248,   249,   250
  };

  const short
  AgentParser::yycheck_[] =
  {
      27,    27,    27,    92,     7,     5,    24,     7,     3,     9,
      27,    28,    29,     8,     0,    11,    12,    13,    14,    15,
      34,    35,    34,    35,    13,    14,    22,    23,    24,    25,
      26,     3,    49,   197,   198,    49,     8,    33,    13,    14,
      36,    30,    31,     3,     7,    49,     6,    65,    66,    49,
      50,    51,    52,    49,    10,     6,     3,    84,    84,    84,
      49,     8,    37,    38,     3,    40,    41,    13,    14,     8,
      16,     3,    18,    19,    49,     3,     8,   104,   104,   104,
      13,    14,   109,   109,   109,   103,   113,    20,    21,    39,
       4,     3,    42,    43,    44,    45,     8,     3,     8,     3,
       3,     3,     8,    49,     8,     8,     8,     3,     3,     3,
       8,     6,     8,     4,     4,     4,    49,    46,    47,    48,
       4,     4,   149,   149,   149,    49,     4,   154,    50,   156,
       4,     4,   159,   159,   159,     4,   225,     4,     4,     4,
      49,    52,     4,     7,     4,     4,     7,     3,    49,     7,
       7,     5,    49,     5,     7,     6,    49,    49,     7,     4,
       4,     4,     4,     4,     4,    50,     5,    17,    49,     7,
       7,     7,     4,     7,     4,     4,     4,     4,     4,     3,
     207,   207,   207,     6,     5,     4,    49,     4,     4,     7,
       4,     4,     4,     4,    49,     4,     4,    32,    84,   104,
     158,    49,    49,    49,   225,   232,   232,   232,   201,   154,
     264,   149,   234,   237,   270,   207,    49,   160,   295,    -1,
      -1,    52,    -1,    -1,    -1,    50,    -1,    -1,    50,    49,
      -1,    -1,    -1,    -1,    49,    -1,    -1,   264,   264,   264
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    46,    47,    48,    54,    55,    56,    57,     0,     5,
       7,     9,    49,    50,    51,    52,    60,    61,    62,    67,
       7,    72,     7,    58,    68,    63,    73,    59,    61,    69,
      70,    49,    65,    66,    10,    74,    11,    12,    13,    14,
      15,    22,    23,    24,    25,    26,    33,    36,    49,    71,
      76,    77,    78,    80,    81,    83,    85,    87,    88,    90,
      92,   104,   121,   142,     6,     3,     4,     8,     3,    75,
       8,    79,     4,    89,    91,   122,    82,    84,    86,     4,
       4,    93,   143,     4,     3,     8,    61,    61,    49,     4,
       4,    50,     4,     4,     4,     4,     4,     4,    52,     7,
       4,     4,    77,     4,     7,    49,    62,    64,    49,     7,
      49,    49,    49,   105,     5,     5,    61,    76,    16,    18,
      19,    71,    88,    90,   123,   124,   125,   128,   130,    27,
      28,    29,    71,   106,   107,   108,   110,   112,     7,    94,
      95,    96,     7,   144,   145,     8,   126,   129,   131,     3,
       8,   109,   111,   113,     3,     8,    97,     6,     3,   146,
       3,     6,     4,     4,     4,   124,     4,     4,     4,   107,
      34,    35,    71,    98,    99,   100,   102,    96,    37,    38,
      40,    41,    71,    88,    90,   147,   148,   149,   151,   152,
     154,   145,    17,   127,    49,     5,     7,     7,     7,   101,
     103,     3,     8,   150,   155,     4,   153,     3,     8,     7,
     132,   133,   134,    30,    31,    71,    88,    90,   114,   115,
     116,   118,   114,   114,     4,     4,    99,     4,     4,    50,
       4,   148,   135,     6,     3,   117,   119,     3,     8,     8,
       8,    49,    64,    49,     5,    49,    20,    21,    71,    88,
      90,   136,   137,   138,   140,   134,     4,     4,   115,     7,
     156,   157,   139,   141,     3,     8,    49,    32,   120,   158,
       3,     6,     4,     4,   137,    39,    42,    43,    44,    45,
     159,   160,   161,   163,   164,   165,   166,   157,    49,    49,
     162,     4,     4,     4,   167,     3,     8,     4,    52,    50,
      50,     4,   160,    49,    49
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    53,    55,    54,    56,    54,    57,    54,    59,    58,
      60,    61,    61,    61,    61,    61,    61,    61,    63,    62,
      64,    65,    65,    66,    66,    68,    67,    69,    69,    70,
      70,    71,    73,    72,    75,    74,    76,    76,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    79,    78,    80,    82,    81,    84,    83,    86,    85,
      87,    89,    88,    91,    90,    93,    92,    94,    94,    95,
      95,    97,    96,    98,    98,    98,    99,    99,   101,   100,
     103,   102,   105,   104,   106,   106,   107,   107,   107,   107,
     109,   108,   111,   110,   113,   112,   114,   114,   115,   115,
     115,   115,   115,   117,   116,   119,   118,   120,   122,   121,
     123,   123,   124,   124,   124,   124,   124,   124,   126,   125,
     127,   129,   128,   131,   130,   132,   132,   133,   133,   135,
     134,   136,   136,   137,   137,   137,   137,   137,   139,   138,
     141,   140,   143,   142,   144,   144,   146,   145,   147,   147,
     148,   148,   148,   148,   148,   148,   148,   150,   149,   151,
     153,   152,   155,   154,   156,   156,   158,   157,   159,   159,
     160,   160,   160,   160,   160,   162,   161,   163,   164,   165,
     167,   166
  };

  const signed char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       0,     6,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4
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
  "global_object", "$@8", "global_params", "global_param", "http_host",
  "$@9", "http_port", "trust_anchor", "$@10", "cert_file", "$@11",
  "key_file", "$@12", "cert_required", "user_context", "$@13", "comment",
  "$@14", "hooks_libraries", "$@15", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@16",
  "hooks_params", "hooks_param", "library", "$@17", "parameters", "$@18",
  "control_sockets", "$@19", "control_sockets_params", "control_socket",
  "dhcp4_server_socket", "$@20", "dhcp6_server_socket", "$@21",
  "d2_server_socket", "$@22", "control_socket_params",
  "control_socket_param", "socket_name", "$@23", "socket_type", "$@24",
  "socket_type_value", "authentication", "$@25", "auth_params",
  "auth_param", "auth_type", "$@26", "auth_type_value", "realm", "$@27",
  "clients", "$@28", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@29", "clients_params", "clients_param", "user", "$@30",
  "password", "$@31", "loggers", "$@32", "loggers_entries", "logger_entry",
  "$@33", "logger_params", "logger_param", "name", "$@34", "debuglevel",
  "severity", "$@35", "output_options_list", "$@36",
  "output_options_list_content", "output_entry", "$@37",
  "output_params_list", "output_params", "output", "$@38", "flush",
  "maxsize", "maxver", "pattern", "$@39", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   124,   124,   124,   125,   125,   126,   126,   134,   134,
     145,   151,   152,   153,   154,   155,   156,   157,   161,   161,
     172,   177,   178,   186,   191,   199,   199,   205,   206,   209,
     213,   226,   234,   234,   246,   246,   264,   265,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   285,   285,   294,   300,   300,   309,   309,   318,   318,
     327,   333,   333,   358,   358,   386,   386,   397,   398,   401,
     402,   405,   405,   413,   414,   415,   418,   419,   422,   422,
     431,   431,   442,   442,   456,   457,   462,   463,   464,   465,
     469,   469,   481,   481,   493,   493,   505,   506,   510,   511,
     512,   513,   514,   518,   518,   528,   528,   537,   544,   544,
     557,   558,   561,   562,   563,   564,   565,   566,   569,   569,
     577,   580,   580,   589,   589,   600,   601,   604,   605,   608,
     608,   616,   617,   620,   621,   622,   623,   624,   627,   627,
     636,   636,   649,   649,   662,   663,   667,   667,   675,   676,
     679,   680,   681,   682,   683,   684,   685,   688,   688,   697,
     703,   703,   712,   712,   723,   724,   727,   727,   735,   736,
     739,   740,   741,   742,   743,   746,   746,   755,   761,   767,
     773,   773
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
#line 2347 "agent_parser.cc"

#line 782 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
