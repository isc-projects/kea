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
#line 116 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 388 "agent_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 116 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 394 "agent_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 116 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 400 "agent_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 116 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 406 "agent_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 116 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 412 "agent_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 116 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 418 "agent_parser.cc"
        break;

      case symbol_kind::S_socket_type_value: // socket_type_value
#line 116 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "agent_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 116 "agent_parser.yy"
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
#line 127 "agent_parser.yy"
                       { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 706 "agent_parser.cc"
    break;

  case 4: // $@2: %empty
#line 128 "agent_parser.yy"
                       { ctx.ctx_ = ctx.CONFIG; }
#line 712 "agent_parser.cc"
    break;

  case 6: // $@3: %empty
#line 129 "agent_parser.yy"
                       { ctx.ctx_ = ctx.AGENT; }
#line 718 "agent_parser.cc"
    break;

  case 8: // $@4: %empty
#line 137 "agent_parser.yy"
                          {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 728 "agent_parser.cc"
    break;

  case 9: // sub_agent: "{" $@4 global_params "}"
#line 141 "agent_parser.yy"
                               {
    // parsing completed
}
#line 736 "agent_parser.cc"
    break;

  case 10: // json: value
#line 148 "agent_parser.yy"
            {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 745 "agent_parser.cc"
    break;

  case 11: // value: "integer"
#line 154 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 751 "agent_parser.cc"
    break;

  case 12: // value: "floating point"
#line 155 "agent_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 757 "agent_parser.cc"
    break;

  case 13: // value: "boolean"
#line 156 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 763 "agent_parser.cc"
    break;

  case 14: // value: "constant string"
#line 157 "agent_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 769 "agent_parser.cc"
    break;

  case 15: // value: "null"
#line 158 "agent_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 775 "agent_parser.cc"
    break;

  case 16: // value: map
#line 159 "agent_parser.yy"
           { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 781 "agent_parser.cc"
    break;

  case 17: // value: list_generic
#line 160 "agent_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 787 "agent_parser.cc"
    break;

  case 18: // $@5: %empty
#line 164 "agent_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "agent_parser.cc"
    break;

  case 19: // map: "{" $@5 map_content "}"
#line 169 "agent_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "agent_parser.cc"
    break;

  case 20: // map_value: map
#line 175 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "agent_parser.cc"
    break;

  case 23: // not_empty_map: "constant string" ":" value
#line 189 "agent_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 824 "agent_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 194 "agent_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 835 "agent_parser.cc"
    break;

  case 25: // not_empty_map: not_empty_map ","
#line 200 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 843 "agent_parser.cc"
    break;

  case 26: // $@6: %empty
#line 205 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "agent_parser.cc"
    break;

  case 27: // list_generic: "[" $@6 list_content "]"
#line 208 "agent_parser.yy"
                               {
}
#line 859 "agent_parser.cc"
    break;

  case 30: // not_empty_list: value
#line 215 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 868 "agent_parser.cc"
    break;

  case 31: // not_empty_list: not_empty_list "," value
#line 219 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 877 "agent_parser.cc"
    break;

  case 32: // not_empty_list: not_empty_list ","
#line 223 "agent_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 885 "agent_parser.cc"
    break;

  case 33: // unknown_map_entry: "constant string" ":"
#line 235 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 896 "agent_parser.cc"
    break;

  case 34: // $@7: %empty
#line 243 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 907 "agent_parser.cc"
    break;

  case 35: // agent_syntax_map: "{" $@7 global_object "}"
#line 248 "agent_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 917 "agent_parser.cc"
    break;

  case 36: // $@8: %empty
#line 255 "agent_parser.yy"
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
#line 265 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 944 "agent_parser.cc"
    break;

  case 39: // global_object_comma: global_object ","
#line 274 "agent_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 952 "agent_parser.cc"
    break;

  case 42: // global_params: global_params ","
#line 280 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 960 "agent_parser.cc"
    break;

  case 56: // $@9: %empty
#line 302 "agent_parser.yy"
                     {
    ctx.unique("http-host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 969 "agent_parser.cc"
    break;

  case 57: // http_host: "http-host" $@9 ":" "constant string"
#line 305 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 979 "agent_parser.cc"
    break;

  case 58: // http_port: "http-port" ":" "integer"
#line 311 "agent_parser.yy"
                                   {
    ctx.unique("http-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 989 "agent_parser.cc"
    break;

  case 59: // $@10: %empty
#line 317 "agent_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 998 "agent_parser.cc"
    break;

  case 60: // trust_anchor: "trust-anchor" $@10 ":" "constant string"
#line 320 "agent_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 1008 "agent_parser.cc"
    break;

  case 61: // $@11: %empty
#line 326 "agent_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1017 "agent_parser.cc"
    break;

  case 62: // cert_file: "cert-file" $@11 ":" "constant string"
#line 329 "agent_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 1027 "agent_parser.cc"
    break;

  case 63: // $@12: %empty
#line 335 "agent_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1036 "agent_parser.cc"
    break;

  case 64: // key_file: "key-file" $@12 ":" "constant string"
#line 338 "agent_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 1046 "agent_parser.cc"
    break;

  case 65: // cert_required: "cert-required" ":" "boolean"
#line 344 "agent_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 1056 "agent_parser.cc"
    break;

  case 66: // $@13: %empty
#line 350 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1064 "agent_parser.cc"
    break;

  case 67: // user_context: "user-context" $@13 ":" map_value
#line 352 "agent_parser.yy"
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
#line 375 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1099 "agent_parser.cc"
    break;

  case 69: // comment: "comment" $@14 ":" "constant string"
#line 377 "agent_parser.yy"
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
#line 403 "agent_parser.yy"
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
#line 409 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1149 "agent_parser.cc"
    break;

  case 76: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 420 "agent_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 1157 "agent_parser.cc"
    break;

  case 77: // $@16: %empty
#line 425 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1167 "agent_parser.cc"
    break;

  case 78: // hooks_library: "{" $@16 hooks_params "}"
#line 429 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1175 "agent_parser.cc"
    break;

  case 81: // hooks_params: hooks_params ","
#line 435 "agent_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 1183 "agent_parser.cc"
    break;

  case 85: // $@17: %empty
#line 445 "agent_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1192 "agent_parser.cc"
    break;

  case 86: // library: "library" $@17 ":" "constant string"
#line 448 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1202 "agent_parser.cc"
    break;

  case 87: // $@18: %empty
#line 454 "agent_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1211 "agent_parser.cc"
    break;

  case 88: // parameters: "parameters" $@18 ":" map_value
#line 457 "agent_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1220 "agent_parser.cc"
    break;

  case 89: // $@19: %empty
#line 465 "agent_parser.yy"
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
#line 471 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1241 "agent_parser.cc"
    break;

  case 93: // control_sockets_params: control_sockets_params ","
#line 481 "agent_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1249 "agent_parser.cc"
    break;

  case 98: // $@20: %empty
#line 495 "agent_parser.yy"
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
#line 501 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1270 "agent_parser.cc"
    break;

  case 100: // $@21: %empty
#line 507 "agent_parser.yy"
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
#line 513 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1291 "agent_parser.cc"
    break;

  case 102: // $@22: %empty
#line 519 "agent_parser.yy"
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
#line 525 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1312 "agent_parser.cc"
    break;

  case 106: // control_socket_params: control_socket_params ","
#line 533 "agent_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1320 "agent_parser.cc"
    break;

  case 112: // $@23: %empty
#line 547 "agent_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1329 "agent_parser.cc"
    break;

  case 113: // socket_name: "socket-name" $@23 ":" "constant string"
#line 550 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1339 "agent_parser.cc"
    break;

  case 114: // $@24: %empty
#line 557 "agent_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1348 "agent_parser.cc"
    break;

  case 115: // socket_type: "socket-type" $@24 ":" socket_type_value
#line 560 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "agent_parser.cc"
    break;

  case 116: // socket_type_value: "unix"
#line 566 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1363 "agent_parser.cc"
    break;

  case 117: // $@25: %empty
#line 573 "agent_parser.yy"
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
#line 579 "agent_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1386 "agent_parser.cc"
    break;

  case 121: // auth_params: auth_params ","
#line 588 "agent_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 1394 "agent_parser.cc"
    break;

  case 129: // $@26: %empty
#line 602 "agent_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 1403 "agent_parser.cc"
    break;

  case 130: // auth_type: "type" $@26 ":" auth_type_value
#line 605 "agent_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1412 "agent_parser.cc"
    break;

  case 131: // auth_type_value: "basic"
#line 610 "agent_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 1418 "agent_parser.cc"
    break;

  case 132: // $@27: %empty
#line 613 "agent_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1427 "agent_parser.cc"
    break;

  case 133: // realm: "realm" $@27 ":" "constant string"
#line 616 "agent_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 1437 "agent_parser.cc"
    break;

  case 134: // $@28: %empty
#line 622 "agent_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1446 "agent_parser.cc"
    break;

  case 135: // directory: "directory" $@28 ":" "constant string"
#line 625 "agent_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 1456 "agent_parser.cc"
    break;

  case 136: // $@29: %empty
#line 631 "agent_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 1468 "agent_parser.cc"
    break;

  case 137: // clients: "clients" $@29 ":" "[" clients_list "]"
#line 637 "agent_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1477 "agent_parser.cc"
    break;

  case 142: // not_empty_clients_list: not_empty_clients_list ","
#line 648 "agent_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1485 "agent_parser.cc"
    break;

  case 143: // $@30: %empty
#line 653 "agent_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1495 "agent_parser.cc"
    break;

  case 144: // basic_auth: "{" $@30 clients_params "}"
#line 657 "agent_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 1503 "agent_parser.cc"
    break;

  case 147: // clients_params: clients_params ","
#line 663 "agent_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1511 "agent_parser.cc"
    break;

  case 155: // $@31: %empty
#line 677 "agent_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1520 "agent_parser.cc"
    break;

  case 156: // user: "user" $@31 ":" "constant string"
#line 680 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1530 "agent_parser.cc"
    break;

  case 157: // $@32: %empty
#line 686 "agent_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1539 "agent_parser.cc"
    break;

  case 158: // user_file: "user-file" $@32 ":" "constant string"
#line 689 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 1549 "agent_parser.cc"
    break;

  case 159: // $@33: %empty
#line 695 "agent_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1558 "agent_parser.cc"
    break;

  case 160: // password: "password" $@33 ":" "constant string"
#line 698 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", password);
    ctx.leave();
}
#line 1568 "agent_parser.cc"
    break;

  case 161: // $@34: %empty
#line 704 "agent_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1577 "agent_parser.cc"
    break;

  case 162: // password_file: "password-file" $@34 ":" "constant string"
#line 707 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 1587 "agent_parser.cc"
    break;

  case 163: // $@35: %empty
#line 717 "agent_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1599 "agent_parser.cc"
    break;

  case 164: // loggers: "loggers" $@35 ":" "[" loggers_entries "]"
#line 723 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1608 "agent_parser.cc"
    break;

  case 167: // loggers_entries: loggers_entries ","
#line 732 "agent_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1616 "agent_parser.cc"
    break;

  case 168: // $@36: %empty
#line 738 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1626 "agent_parser.cc"
    break;

  case 169: // logger_entry: "{" $@36 logger_params "}"
#line 742 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1634 "agent_parser.cc"
    break;

  case 172: // logger_params: logger_params ","
#line 748 "agent_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1642 "agent_parser.cc"
    break;

  case 180: // $@37: %empty
#line 762 "agent_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1651 "agent_parser.cc"
    break;

  case 181: // name: "name" $@37 ":" "constant string"
#line 765 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1661 "agent_parser.cc"
    break;

  case 182: // debuglevel: "debuglevel" ":" "integer"
#line 771 "agent_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1671 "agent_parser.cc"
    break;

  case 183: // $@38: %empty
#line 777 "agent_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1680 "agent_parser.cc"
    break;

  case 184: // severity: "severity" $@38 ":" "constant string"
#line 780 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1690 "agent_parser.cc"
    break;

  case 185: // $@39: %empty
#line 786 "agent_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1702 "agent_parser.cc"
    break;

  case 186: // output_options_list: "output_options" $@39 ":" "[" output_options_list_content "]"
#line 792 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1711 "agent_parser.cc"
    break;

  case 189: // output_options_list_content: output_options_list_content ","
#line 799 "agent_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 1719 "agent_parser.cc"
    break;

  case 190: // $@40: %empty
#line 804 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1729 "agent_parser.cc"
    break;

  case 191: // output_entry: "{" $@40 output_params_list "}"
#line 808 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1737 "agent_parser.cc"
    break;

  case 194: // output_params_list: output_params_list ","
#line 814 "agent_parser.yy"
                                        {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1745 "agent_parser.cc"
    break;

  case 200: // $@41: %empty
#line 826 "agent_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1754 "agent_parser.cc"
    break;

  case 201: // output: "output" $@41 ":" "constant string"
#line 829 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1764 "agent_parser.cc"
    break;

  case 202: // flush: "flush" ":" "boolean"
#line 835 "agent_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1774 "agent_parser.cc"
    break;

  case 203: // maxsize: "maxsize" ":" "integer"
#line 841 "agent_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1784 "agent_parser.cc"
    break;

  case 204: // maxver: "maxver" ":" "integer"
#line 847 "agent_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1794 "agent_parser.cc"
    break;

  case 205: // $@42: %empty
#line 853 "agent_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1803 "agent_parser.cc"
    break;

  case 206: // pattern: "pattern" $@42 ":" "constant string"
#line 856 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1813 "agent_parser.cc"
    break;


#line 1817 "agent_parser.cc"

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


  const short AgentParser::yypact_ninf_ = -136;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      71,  -136,  -136,  -136,     4,     0,     1,    16,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,  -136,     0,   -31,    19,    -1,  -136,    40,
      55,    78,    83,   107,  -136,    14,  -136,  -136,   112,  -136,
    -136,  -136,  -136,  -136,  -136,   114,   119,  -136,  -136,   120,
    -136,    42,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,     0,     0,  -136,    73,
     122,  -136,  -136,   126,    80,   127,   131,   132,   136,   138,
     139,    89,   140,   141,   142,  -136,    -1,  -136,  -136,  -136,
     144,   143,   100,  -136,   146,   102,   148,   104,   106,   108,
    -136,  -136,   152,   154,  -136,     0,    -1,  -136,  -136,  -136,
    -136,    23,  -136,  -136,  -136,   -12,   155,   156,  -136,    75,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,    91,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,    95,  -136,  -136,
    -136,  -136,  -136,   145,   158,  -136,  -136,    28,  -136,  -136,
     160,   161,   162,   163,    23,  -136,   164,   165,   166,   -12,
    -136,   -22,  -136,   155,    49,   156,  -136,   157,   121,   123,
     167,  -136,   169,   170,   171,  -136,  -136,  -136,  -136,    97,
    -136,  -136,  -136,  -136,  -136,  -136,   175,  -136,  -136,  -136,
    -136,    99,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,   173,    63,    63,    63,   177,   178,    -5,  -136,
     179,   180,    96,   181,    49,  -136,  -136,   184,   168,  -136,
    -136,  -136,  -136,  -136,  -136,   101,  -136,  -136,  -136,   103,
     105,   134,   146,  -136,   147,   186,  -136,   149,  -136,    43,
    -136,   173,   188,   189,    63,  -136,  -136,  -136,  -136,  -136,
    -136,   187,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
     109,  -136,  -136,  -136,  -136,  -136,  -136,   150,   172,  -136,
    -136,    41,  -136,   191,   192,   193,   194,    43,  -136,  -136,
    -136,  -136,    26,   187,  -136,   151,   153,   159,   174,  -136,
    -136,   196,   200,   202,  -136,   111,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,   204,   176,   182,
     183,   205,    26,  -136,   185,  -136,  -136,  -136,   190,  -136,
    -136,  -136
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    26,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      34,     5,     8,     7,    28,    21,     0,     0,    30,     0,
      29,     0,     0,    22,    36,     0,    38,    56,     0,    66,
      68,   117,    59,    61,    63,     0,     0,    70,   163,     0,
      55,     0,    40,    43,    44,    45,    46,    47,    48,    53,
      54,    51,    50,    49,    52,    27,    32,     0,    19,    25,
       0,    39,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    42,     9,    31,    23,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
      65,    89,     0,     0,    41,     0,     0,    57,    20,    67,
      69,     0,    60,    62,    64,     0,    72,     0,    24,     0,
     129,   132,   134,   136,   128,   127,   126,     0,   119,   122,
     123,   124,   125,    98,   100,   102,    97,     0,    91,    94,
      95,    96,    77,     0,    73,    74,   168,     0,   165,    37,
       0,     0,     0,     0,   121,   118,     0,     0,     0,    93,
      90,     0,    71,    76,     0,   167,   164,     0,     0,     0,
       0,   120,     0,     0,     0,    92,    85,    87,    82,     0,
      79,    83,    84,    75,   180,   185,     0,   183,   179,   177,
     178,     0,   170,   173,   175,   176,   174,   166,   131,   130,
     133,   135,   138,     0,     0,     0,     0,     0,    81,    78,
       0,     0,     0,     0,   172,   169,   143,     0,   139,   140,
     112,   114,   111,   109,   110,     0,   104,   107,   108,     0,
       0,     0,     0,    80,     0,     0,   182,     0,   171,     0,
     137,   142,     0,     0,   106,    99,   101,   103,    86,    88,
     181,     0,   184,   155,   157,   159,   161,   154,   152,   153,
       0,   145,   148,   149,   150,   151,   141,     0,     0,   105,
     190,     0,   187,     0,     0,     0,     0,   147,   144,   113,
     116,   115,     0,   189,   186,     0,     0,     0,     0,   146,
     200,     0,     0,     0,   205,     0,   192,   195,   196,   197,
     198,   199,   188,   156,   158,   160,   162,     0,     0,     0,
       0,     0,   194,   191,     0,   202,   203,   204,     0,   193,
     201,   206
  };

  const short
  AgentParser::yypgoto_[] =
  {
    -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,   -18,   -91,
    -136,   -17,  -136,  -136,  -136,  -136,  -136,  -136,   -27,  -136,
    -136,  -136,  -136,  -136,   110,   124,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,   -26,  -136,   -25,  -136,
    -136,  -136,  -136,  -136,    54,  -136,  -136,    10,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,    60,  -136,  -136,  -136,  -136,
    -136,  -136,  -135,   -24,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,    67,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,  -136,   -19,  -136,  -136,   -54,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,    59,
    -136,  -136,    11,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,   -56,  -136,  -136,   -84,  -136,  -136,  -136,  -136,  -136,
    -136,  -136
  };

  const short
  AgentParser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,   109,    32,    33,    19,    24,    29,    30,   222,    21,
      26,    35,    70,    36,    51,    52,    53,    73,    54,    55,
      78,    56,    79,    57,    80,    58,   223,    75,   224,    76,
      61,    83,   143,   144,   145,   161,   179,   180,   181,   206,
     182,   207,    62,   115,   137,   138,   139,   156,   140,   157,
     141,   158,   225,   226,   227,   242,   228,   243,   281,    63,
      77,   127,   128,   129,   150,   199,   130,   151,   131,   152,
     132,   153,   217,   218,   219,   239,   260,   261,   262,   273,
     263,   274,   264,   275,   265,   276,    64,    84,   147,   148,
     164,   191,   192,   193,   210,   194,   195,   213,   196,   211,
     271,   272,   282,   295,   296,   297,   307,   298,   299,   300,
     301,   311
  };

  const short
  AgentParser::yytable_[] =
  {
      50,    59,    60,   108,     8,     9,    28,    10,    20,    11,
      37,    38,    39,    40,    41,   176,   177,    71,   133,   134,
     135,    31,    72,    22,    42,    43,    44,    45,    46,    34,
      49,   165,   176,   177,   166,    47,    39,    40,    48,   120,
      49,   121,   122,   123,   283,    86,    65,   284,    88,    89,
      87,    49,    12,    13,    14,    15,    39,    40,    66,    50,
      59,    60,    39,    40,   253,   254,   255,   256,   290,   229,
     230,   291,   292,   293,   294,    49,    39,    40,    86,    50,
      59,    60,    67,   149,   124,   125,   126,   118,   136,   184,
     185,    68,   186,   187,   154,    49,   220,   221,   159,   155,
     208,    49,   214,   160,   244,   209,   244,   215,   244,   245,
      69,   246,   277,   247,   312,    49,    74,   278,    81,   313,
       1,     2,     3,    82,    85,    90,    91,   124,   125,   126,
      92,    94,   136,    93,   178,    95,    96,   188,   189,   190,
      97,   108,    98,    99,   100,   102,   103,   101,   105,   236,
     106,   162,   107,    10,   110,   111,   112,   116,   113,   117,
     114,   163,   142,   146,   167,   168,   169,   170,   172,   173,
     174,   241,   202,   200,   198,   201,   203,   204,   205,   212,
     216,   231,   232,   234,   235,   237,   248,   188,   189,   190,
     240,   251,   267,   268,   270,   285,   286,   287,   288,   250,
     308,   252,   279,   303,   309,   304,   310,   280,   314,   318,
     104,   305,   257,   258,   259,   249,   119,   183,   233,   175,
     269,   171,   266,   289,   197,   238,   306,   302,   319,     0,
       0,   315,     0,     0,     0,   316,   317,   320,     0,     0,
       0,     0,   321,     0,     0,     0,     0,     0,     0,     0,
     257,   258,   259
  };

  const short
  AgentParser::yycheck_[] =
  {
      27,    27,    27,    94,     0,     5,    24,     7,     7,     9,
      11,    12,    13,    14,    15,    37,    38,     3,    30,    31,
      32,    52,     8,     7,    25,    26,    27,    28,    29,    10,
      52,     3,    37,    38,     6,    36,    13,    14,    39,    16,
      52,    18,    19,    20,     3,     3,     6,     6,    66,    67,
       8,    52,    52,    53,    54,    55,    13,    14,     3,    86,
      86,    86,    13,    14,    21,    22,    23,    24,    42,   204,
     205,    45,    46,    47,    48,    52,    13,    14,     3,   106,
     106,   106,     4,     8,   111,   111,   111,   105,   115,    40,
      41,     8,    43,    44,     3,    52,    33,    34,     3,     8,
       3,    52,     3,     8,     3,     8,     3,     8,     3,     8,
       3,     8,     3,     8,     3,    52,     4,     8,     4,     8,
      49,    50,    51,     4,     4,    52,     4,   154,   154,   154,
       4,     4,   159,    53,   161,     4,     4,   164,   164,   164,
       4,   232,     4,     4,    55,     4,     4,     7,     4,    53,
       7,     6,    52,     7,    52,     7,    52,     5,    52,     5,
      52,     3,     7,     7,     4,     4,     4,     4,     4,     4,
       4,     3,     5,    52,    17,    52,     7,     7,     7,     4,
       7,     4,     4,     4,     4,     4,    52,   214,   214,   214,
       6,     5,     4,     4,     7,     4,     4,     4,     4,    52,
       4,    52,    52,    52,     4,    52,     4,    35,     4,     4,
      86,    52,   239,   239,   239,   232,   106,   163,   208,   159,
     244,   154,   241,   277,   165,   214,    52,   283,   312,    -1,
      -1,    55,    -1,    -1,    -1,    53,    53,    52,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     277,   277,   277
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    49,    50,    51,    57,    58,    59,    60,     0,     5,
       7,     9,    52,    53,    54,    55,    63,    64,    65,    70,
       7,    75,     7,    61,    71,    66,    76,    62,    64,    72,
      73,    52,    68,    69,    10,    77,    79,    11,    12,    13,
      14,    15,    25,    26,    27,    28,    29,    36,    39,    52,
      74,    80,    81,    82,    84,    85,    87,    89,    91,    92,
      94,    96,   108,   125,   152,     6,     3,     4,     8,     3,
      78,     3,     8,    83,     4,    93,    95,   126,    86,    88,
      90,     4,     4,    97,   153,     4,     3,     8,    64,    64,
      52,     4,     4,    53,     4,     4,     4,     4,     4,     4,
      55,     7,     4,     4,    81,     4,     7,    52,    65,    67,
      52,     7,    52,    52,    52,   109,     5,     5,    64,    80,
      16,    18,    19,    20,    74,    92,    94,   127,   128,   129,
     132,   134,   136,    30,    31,    32,    74,   110,   111,   112,
     114,   116,     7,    98,    99,   100,     7,   154,   155,     8,
     130,   133,   135,   137,     3,     8,   113,   115,   117,     3,
       8,   101,     6,     3,   156,     3,     6,     4,     4,     4,
       4,   128,     4,     4,     4,   111,    37,    38,    74,   102,
     103,   104,   106,   100,    40,    41,    43,    44,    74,    92,
      94,   157,   158,   159,   161,   162,   164,   155,    17,   131,
      52,    52,     5,     7,     7,     7,   105,   107,     3,     8,
     160,   165,     4,   163,     3,     8,     7,   138,   139,   140,
      33,    34,    74,    92,    94,   118,   119,   120,   122,   118,
     118,     4,     4,   103,     4,     4,    53,     4,   158,   141,
       6,     3,   121,   123,     3,     8,     8,     8,    52,    67,
      52,     5,    52,    21,    22,    23,    24,    74,    92,    94,
     142,   143,   144,   146,   148,   150,   140,     4,     4,   119,
       7,   166,   167,   145,   147,   149,   151,     3,     8,    52,
      35,   124,   168,     3,     6,     4,     4,     4,     4,   143,
      42,    45,    46,    47,    48,   169,   170,   171,   173,   174,
     175,   176,   167,    52,    52,    52,    52,   172,     4,     4,
       4,   177,     3,     8,     4,    55,    53,    53,     4,   170,
      52,    52
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    56,    58,    57,    59,    57,    60,    57,    62,    61,
      63,    64,    64,    64,    64,    64,    64,    64,    66,    65,
      67,    68,    68,    69,    69,    69,    71,    70,    72,    72,
      73,    73,    73,    74,    76,    75,    78,    77,    77,    79,
      80,    80,    80,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    83,    82,    84,    86,
      85,    88,    87,    90,    89,    91,    93,    92,    95,    94,
      97,    96,    98,    98,    99,    99,    99,   101,   100,   102,
     102,   102,   102,   103,   103,   105,   104,   107,   106,   109,
     108,   110,   110,   110,   111,   111,   111,   111,   113,   112,
     115,   114,   117,   116,   118,   118,   118,   119,   119,   119,
     119,   119,   121,   120,   123,   122,   124,   126,   125,   127,
     127,   127,   128,   128,   128,   128,   128,   128,   128,   130,
     129,   131,   133,   132,   135,   134,   137,   136,   138,   138,
     139,   139,   139,   141,   140,   142,   142,   142,   143,   143,
     143,   143,   143,   143,   143,   145,   144,   147,   146,   149,
     148,   151,   150,   153,   152,   154,   154,   154,   156,   155,
     157,   157,   157,   158,   158,   158,   158,   158,   158,   158,
     160,   159,   161,   163,   162,   165,   164,   166,   166,   166,
     168,   167,   169,   169,   169,   170,   170,   170,   170,   170,
     172,   171,   173,   174,   175,   177,   176
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
       3,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     0,     6,     1,     3,     2,
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
  "\"http-host\"", "\"http-port\"", "\"user-context\"", "\"comment\"",
  "\"authentication\"", "\"type\"", "\"basic\"", "\"realm\"",
  "\"directory\"", "\"clients\"", "\"user\"", "\"user-file\"",
  "\"password\"", "\"password-file\"", "\"trust-anchor\"", "\"cert-file\"",
  "\"key-file\"", "\"cert-required\"", "\"control-sockets\"", "\"dhcp4\"",
  "\"dhcp6\"", "\"d2\"", "\"socket-name\"", "\"socket-type\"", "\"unix\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"", "\"loggers\"",
  "\"name\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "START_JSON", "START_AGENT", "START_SUB_AGENT", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "sub_agent", "$@4", "json", "value", "map", "$@5",
  "map_value", "map_content", "not_empty_map", "list_generic", "$@6",
  "list_content", "not_empty_list", "unknown_map_entry",
  "agent_syntax_map", "$@7", "global_object", "$@8", "global_object_comma",
  "global_params", "global_param", "http_host", "$@9", "http_port",
  "trust_anchor", "$@10", "cert_file", "$@11", "key_file", "$@12",
  "cert_required", "user_context", "$@13", "comment", "$@14",
  "hooks_libraries", "$@15", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@16",
  "hooks_params", "hooks_param", "library", "$@17", "parameters", "$@18",
  "control_sockets", "$@19", "control_sockets_params", "control_socket",
  "dhcp4_server_socket", "$@20", "dhcp6_server_socket", "$@21",
  "d2_server_socket", "$@22", "control_socket_params",
  "control_socket_param", "socket_name", "$@23", "socket_type", "$@24",
  "socket_type_value", "authentication", "$@25", "auth_params",
  "auth_param", "auth_type", "$@26", "auth_type_value", "realm", "$@27",
  "directory", "$@28", "clients", "$@29", "clients_list",
  "not_empty_clients_list", "basic_auth", "$@30", "clients_params",
  "clients_param", "user", "$@31", "user_file", "$@32", "password", "$@33",
  "password_file", "$@34", "loggers", "$@35", "loggers_entries",
  "logger_entry", "$@36", "logger_params", "logger_param", "name", "$@37",
  "debuglevel", "severity", "$@38", "output_options_list", "$@39",
  "output_options_list_content", "output_entry", "$@40",
  "output_params_list", "output_params", "output", "$@41", "flush",
  "maxsize", "maxver", "pattern", "$@42", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   127,   127,   127,   128,   128,   129,   129,   137,   137,
     148,   154,   155,   156,   157,   158,   159,   160,   164,   164,
     175,   180,   181,   189,   194,   200,   205,   205,   211,   212,
     215,   219,   223,   235,   243,   243,   255,   255,   271,   274,
     278,   279,   280,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   302,   302,   311,   317,
     317,   326,   326,   335,   335,   344,   350,   350,   375,   375,
     403,   403,   414,   415,   418,   419,   420,   425,   425,   433,
     434,   435,   438,   441,   442,   445,   445,   454,   454,   465,
     465,   479,   480,   481,   488,   489,   490,   491,   495,   495,
     507,   507,   519,   519,   531,   532,   533,   539,   540,   541,
     542,   543,   547,   547,   557,   557,   566,   573,   573,   586,
     587,   588,   593,   594,   595,   596,   597,   598,   599,   602,
     602,   610,   613,   613,   622,   622,   631,   631,   642,   643,
     646,   647,   648,   653,   653,   661,   662,   663,   668,   669,
     670,   671,   672,   673,   674,   677,   677,   686,   686,   695,
     695,   704,   704,   717,   717,   730,   731,   732,   738,   738,
     746,   747,   748,   753,   754,   755,   756,   757,   758,   759,
     762,   762,   771,   777,   777,   786,   786,   797,   798,   799,
     804,   804,   812,   813,   814,   819,   820,   821,   822,   823,
     826,   826,   835,   841,   847,   853,   853
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
#line 2543 "agent_parser.cc"

#line 862 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
