// A Bison parser, made by GNU Bison 3.6.4.

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
      case 54: // value
      case 57: // map_value
      case 110: // socket_type_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 45: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 44: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 43: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 42: // "constant string"
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
      case 54: // value
      case 57: // map_value
      case 110: // socket_type_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 45: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 44: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 43: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 42: // "constant string"
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
      case 54: // value
      case 57: // map_value
      case 110: // socket_type_value
        value.copy< ElementPtr > (that.value);
        break;

      case 45: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 44: // "floating point"
        value.copy< double > (that.value);
        break;

      case 43: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 42: // "constant string"
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
      case 54: // value
      case 57: // map_value
      case 110: // socket_type_value
        value.move< ElementPtr > (that.value);
        break;

      case 45: // "boolean"
        value.move< bool > (that.value);
        break;

      case 44: // "floating point"
        value.move< double > (that.value);
        break;

      case 43: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 42: // "constant string"
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
      case 42: // "constant string"
#line 104 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 384 "agent_parser.cc"
        break;

      case 43: // "integer"
#line 104 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 390 "agent_parser.cc"
        break;

      case 44: // "floating point"
#line 104 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 396 "agent_parser.cc"
        break;

      case 45: // "boolean"
#line 104 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 402 "agent_parser.cc"
        break;

      case 54: // value
#line 104 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 408 "agent_parser.cc"
        break;

      case 57: // map_value
#line 104 "agent_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "agent_parser.cc"
        break;

      case 110: // socket_type_value
#line 104 "agent_parser.yy"
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
      case 54: // value
      case 57: // map_value
      case 110: // socket_type_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 45: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 44: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 43: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 42: // "constant string"
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
  case 2:
#line 115 "agent_parser.yy"
                       { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 695 "agent_parser.cc"
    break;

  case 4:
#line 116 "agent_parser.yy"
                       { ctx.ctx_ = ctx.CONFIG; }
#line 701 "agent_parser.cc"
    break;

  case 6:
#line 117 "agent_parser.yy"
                       { ctx.ctx_ = ctx.AGENT; }
#line 707 "agent_parser.cc"
    break;

  case 8:
#line 125 "agent_parser.yy"
                          {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 717 "agent_parser.cc"
    break;

  case 9:
#line 129 "agent_parser.yy"
                               {
    // parsing completed
}
#line 725 "agent_parser.cc"
    break;

  case 10:
#line 136 "agent_parser.yy"
            {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 734 "agent_parser.cc"
    break;

  case 11:
#line 142 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 740 "agent_parser.cc"
    break;

  case 12:
#line 143 "agent_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 746 "agent_parser.cc"
    break;

  case 13:
#line 144 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "agent_parser.cc"
    break;

  case 14:
#line 145 "agent_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "agent_parser.cc"
    break;

  case 15:
#line 146 "agent_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 764 "agent_parser.cc"
    break;

  case 16:
#line 147 "agent_parser.yy"
           { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 770 "agent_parser.cc"
    break;

  case 17:
#line 148 "agent_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 776 "agent_parser.cc"
    break;

  case 18:
#line 152 "agent_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 787 "agent_parser.cc"
    break;

  case 19:
#line 157 "agent_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 797 "agent_parser.cc"
    break;

  case 20:
#line 163 "agent_parser.yy"
               { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 803 "agent_parser.cc"
    break;

  case 23:
#line 177 "agent_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 812 "agent_parser.cc"
    break;

  case 24:
#line 181 "agent_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 822 "agent_parser.cc"
    break;

  case 25:
#line 188 "agent_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 831 "agent_parser.cc"
    break;

  case 26:
#line 191 "agent_parser.yy"
                               {
}
#line 838 "agent_parser.cc"
    break;

  case 29:
#line 198 "agent_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 847 "agent_parser.cc"
    break;

  case 30:
#line 202 "agent_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 856 "agent_parser.cc"
    break;

  case 31:
#line 215 "agent_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 867 "agent_parser.cc"
    break;

  case 32:
#line 223 "agent_parser.yy"
                                 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 878 "agent_parser.cc"
    break;

  case 33:
#line 228 "agent_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 888 "agent_parser.cc"
    break;

  case 36:
#line 243 "agent_parser.yy"
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

  case 37:
#line 253 "agent_parser.yy"
                                                    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 915 "agent_parser.cc"
    break;

  case 50:
#line 278 "agent_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 923 "agent_parser.cc"
    break;

  case 51:
#line 280 "agent_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 933 "agent_parser.cc"
    break;

  case 52:
#line 286 "agent_parser.yy"
                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 942 "agent_parser.cc"
    break;

  case 53:
#line 291 "agent_parser.yy"
                                                       {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 950 "agent_parser.cc"
    break;

  case 54:
#line 293 "agent_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("basic-authentication-realm", realm);
    ctx.leave();
}
#line 960 "agent_parser.cc"
    break;

  case 55:
#line 299 "agent_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 968 "agent_parser.cc"
    break;

  case 56:
#line 301 "agent_parser.yy"
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
#line 995 "agent_parser.cc"
    break;

  case 57:
#line 324 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1003 "agent_parser.cc"
    break;

  case 58:
#line 326 "agent_parser.yy"
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
#line 1032 "agent_parser.cc"
    break;

  case 59:
#line 352 "agent_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1043 "agent_parser.cc"
    break;

  case 60:
#line 357 "agent_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1052 "agent_parser.cc"
    break;

  case 65:
#line 370 "agent_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1062 "agent_parser.cc"
    break;

  case 66:
#line 374 "agent_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1070 "agent_parser.cc"
    break;

  case 72:
#line 387 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1078 "agent_parser.cc"
    break;

  case 73:
#line 389 "agent_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1088 "agent_parser.cc"
    break;

  case 74:
#line 395 "agent_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1096 "agent_parser.cc"
    break;

  case 75:
#line 397 "agent_parser.yy"
              {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1105 "agent_parser.cc"
    break;

  case 76:
#line 405 "agent_parser.yy"
                                                      {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1116 "agent_parser.cc"
    break;

  case 77:
#line 410 "agent_parser.yy"
                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1125 "agent_parser.cc"
    break;

  case 84:
#line 431 "agent_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1136 "agent_parser.cc"
    break;

  case 85:
#line 436 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1145 "agent_parser.cc"
    break;

  case 86:
#line 442 "agent_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1156 "agent_parser.cc"
    break;

  case 87:
#line 447 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1165 "agent_parser.cc"
    break;

  case 88:
#line 453 "agent_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1176 "agent_parser.cc"
    break;

  case 89:
#line 458 "agent_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1185 "agent_parser.cc"
    break;

  case 97:
#line 477 "agent_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1193 "agent_parser.cc"
    break;

  case 98:
#line 479 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1203 "agent_parser.cc"
    break;

  case 99:
#line 486 "agent_parser.yy"
                         {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1211 "agent_parser.cc"
    break;

  case 100:
#line 488 "agent_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1220 "agent_parser.cc"
    break;

  case 101:
#line 494 "agent_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1226 "agent_parser.cc"
    break;

  case 102:
#line 501 "agent_parser.yy"
                                             {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("basic-authentications", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.BASIC_AUTHENTICATIONS);
}
#line 1237 "agent_parser.cc"
    break;

  case 103:
#line 506 "agent_parser.yy"
                                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1246 "agent_parser.cc"
    break;

  case 108:
#line 519 "agent_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1256 "agent_parser.cc"
    break;

  case 109:
#line 523 "agent_parser.yy"
                                   {
    ctx.stack_.pop_back();
}
#line 1264 "agent_parser.cc"
    break;

  case 117:
#line 538 "agent_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1272 "agent_parser.cc"
    break;

  case 118:
#line 540 "agent_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1282 "agent_parser.cc"
    break;

  case 119:
#line 546 "agent_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1290 "agent_parser.cc"
    break;

  case 120:
#line 548 "agent_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", password);
    ctx.leave();
}
#line 1300 "agent_parser.cc"
    break;

  case 121:
#line 558 "agent_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1311 "agent_parser.cc"
    break;

  case 122:
#line 563 "agent_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1320 "agent_parser.cc"
    break;

  case 125:
#line 575 "agent_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1330 "agent_parser.cc"
    break;

  case 126:
#line 579 "agent_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1338 "agent_parser.cc"
    break;

  case 136:
#line 596 "agent_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1346 "agent_parser.cc"
    break;

  case 137:
#line 598 "agent_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1356 "agent_parser.cc"
    break;

  case 138:
#line 604 "agent_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1365 "agent_parser.cc"
    break;

  case 139:
#line 609 "agent_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1373 "agent_parser.cc"
    break;

  case 140:
#line 611 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1383 "agent_parser.cc"
    break;

  case 141:
#line 617 "agent_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1394 "agent_parser.cc"
    break;

  case 142:
#line 622 "agent_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1403 "agent_parser.cc"
    break;

  case 145:
#line 631 "agent_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1413 "agent_parser.cc"
    break;

  case 146:
#line 635 "agent_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1421 "agent_parser.cc"
    break;

  case 154:
#line 650 "agent_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1429 "agent_parser.cc"
    break;

  case 155:
#line 652 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1439 "agent_parser.cc"
    break;

  case 156:
#line 658 "agent_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1448 "agent_parser.cc"
    break;

  case 157:
#line 663 "agent_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1457 "agent_parser.cc"
    break;

  case 158:
#line 668 "agent_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1466 "agent_parser.cc"
    break;

  case 159:
#line 673 "agent_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1474 "agent_parser.cc"
    break;

  case 160:
#line 675 "agent_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1484 "agent_parser.cc"
    break;


#line 1488 "agent_parser.cc"

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


  const signed char AgentParser::yypact_ninf_ = -103;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      56,  -103,  -103,  -103,     8,     2,    -5,     3,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,     2,   -14,    42,     1,  -103,    44,
      51,    60,    62,    97,  -103,    93,  -103,  -103,  -103,    98,
    -103,  -103,  -103,    99,  -103,  -103,  -103,   101,  -103,    57,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,     2,     2,  -103,    65,   104,  -103,   109,    71,   111,
     114,   115,   113,   117,   118,   119,  -103,     1,  -103,  -103,
    -103,   120,   121,    85,  -103,    87,   123,    89,  -103,   127,
     128,   129,  -103,     2,     1,  -103,  -103,  -103,  -103,  -103,
      40,   130,   131,   132,  -103,    59,  -103,  -103,  -103,  -103,
      63,  -103,  -103,  -103,  -103,  -103,   134,   122,  -103,  -103,
     135,   133,  -103,  -103,    15,  -103,  -103,   138,   139,   140,
      40,  -103,    11,  -103,   130,    21,  -103,   131,   -11,   132,
    -103,   141,   142,   143,  -103,  -103,  -103,  -103,  -103,  -103,
      80,  -103,  -103,  -103,  -103,  -103,  -103,  -103,    81,  -103,
    -103,  -103,  -103,  -103,  -103,   147,  -103,  -103,  -103,  -103,
      82,  -103,  -103,  -103,  -103,  -103,  -103,    19,    19,    19,
     148,   149,    11,  -103,   150,   151,    14,  -103,   153,   154,
      92,   155,   -11,  -103,  -103,  -103,  -103,  -103,  -103,    83,
    -103,  -103,  -103,    84,    90,   103,   105,  -103,   125,     2,
    -103,   126,   157,  -103,   136,  -103,   159,   160,    19,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,   158,  -103,   137,
     124,  -103,  -103,    26,  -103,  -103,  -103,  -103,    43,   158,
    -103,  -103,   165,   168,   169,  -103,    91,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,   170,   144,   145,   152,   171,    43,
    -103,   156,  -103,  -103,  -103,   161,  -103,  -103,  -103
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    36,     0,    34,    35,    50,     0,
      53,    55,    57,     0,   102,    59,   121,     0,    49,     0,
      38,    40,    41,    42,    47,    48,    45,    43,    44,    46,
      26,     0,     0,    19,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     9,    30,
      23,     0,     0,     0,    52,     0,     0,     0,    76,     0,
       0,     0,    39,     0,     0,    51,    54,    20,    56,    58,
       0,   104,    61,     0,    24,     0,    84,    86,    88,    83,
       0,    78,    80,    81,    82,   108,     0,   105,   106,    65,
       0,    62,    63,   125,     0,   123,    37,     0,     0,     0,
       0,    77,     0,   103,     0,     0,    60,     0,     0,     0,
     122,     0,     0,     0,    79,   117,   119,   116,   114,   115,
       0,   110,   112,   113,   107,    72,    74,    69,     0,    67,
      70,    71,    64,   136,   141,     0,   139,   135,   133,   134,
       0,   127,   129,   131,   132,   130,   124,     0,     0,     0,
       0,     0,     0,   109,     0,     0,     0,    66,     0,     0,
       0,     0,     0,   126,    97,    99,    96,    94,    95,     0,
      90,    92,    93,     0,     0,     0,     0,   111,     0,     0,
      68,     0,     0,   138,     0,   128,     0,     0,     0,    85,
      87,    89,   118,   120,    73,    75,   137,     0,   140,     0,
       0,    91,   145,     0,   143,    98,   101,   100,     0,     0,
     142,   154,     0,     0,     0,   159,     0,   147,   149,   150,
     151,   152,   153,   144,     0,     0,     0,     0,     0,     0,
     146,     0,   156,   157,   158,     0,   148,   155,   160
  };

  const signed char
  AgentParser::yypgoto_[] =
  {
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,   -24,    94,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,   -26,  -103,
    -103,  -103,  -103,  -103,  -103,    32,   100,  -103,  -103,  -103,
    -103,  -103,   -22,  -103,   -21,  -103,  -103,  -103,  -103,  -103,
      39,  -103,  -103,    -4,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,    53,  -103,  -103,  -103,  -103,  -103,  -103,  -102,   -37,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,    50,
    -103,  -103,     4,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
      48,  -103,  -103,    -2,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,   -48,  -103,  -103,   -67,  -103,  -103,  -103,  -103,
    -103,  -103,  -103
  };

  const short
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    98,    32,    33,    19,    24,    29,    30,   196,    21,
      26,    35,    36,    37,    65,    49,    50,    51,    67,    52,
      53,    69,   197,    70,   198,    71,    56,    74,   120,   121,
     122,   135,   158,   159,   160,   184,   161,   185,    57,   100,
     110,   111,   112,   127,   113,   128,   114,   129,   199,   200,
     201,   216,   202,   217,   237,    58,    73,   116,   117,   118,
     132,   150,   151,   152,   180,   153,   181,    59,    75,   124,
     125,   138,   170,   171,   172,   188,   173,   174,   191,   175,
     189,   233,   234,   238,   246,   247,   248,   254,   249,   250,
     251,   252,   258
  };

  const short
  AgentParser::yytable_[] =
  {
      28,    48,    20,    41,    42,    54,    55,     9,     8,    10,
      22,    11,    38,    39,    40,    41,    42,    43,   139,   163,
     164,   140,   165,   166,    44,    41,    42,    45,    31,   239,
      46,    47,   240,    41,    42,   145,   146,    79,    80,   194,
     195,   155,   156,    47,    12,    13,    14,    15,   155,   156,
      60,    48,    34,    47,    61,    54,    55,   106,   107,   108,
      77,    47,    77,    47,    62,    78,   130,   126,    48,   104,
      63,   131,    54,    55,   109,   241,   203,   204,   242,   243,
     244,   245,    47,   182,   186,   192,   218,   218,   183,   187,
     193,   219,   220,   218,   259,     1,     2,     3,   221,   260,
      64,    66,    68,    72,   109,    76,   147,    81,    82,   157,
     148,   149,   167,    83,    84,    85,   168,   169,    86,    87,
      88,    89,    90,    91,    93,   134,   105,    95,    94,    96,
      10,    99,   101,   102,   103,   213,   137,   115,   119,   123,
     133,   136,   141,   142,   143,   222,   236,   223,   177,   178,
     179,   190,   205,   206,   208,   209,   147,   211,   212,   214,
     148,   149,   227,   229,   230,   232,   167,   224,   226,   255,
     168,   169,   256,   257,   261,   265,   162,    92,   228,   235,
      97,   231,   210,   144,   154,   225,   207,   176,   263,   262,
     215,   253,   266,     0,     0,   264,     0,     0,   267,     0,
       0,     0,     0,   268
  };

  const short
  AgentParser::yycheck_[] =
  {
      24,    27,     7,    14,    15,    27,    27,     5,     0,     7,
       7,     9,    11,    12,    13,    14,    15,    16,     3,    30,
      31,     6,    33,    34,    23,    14,    15,    26,    42,     3,
      29,    42,     6,    14,    15,    24,    25,    61,    62,    20,
      21,    27,    28,    42,    42,    43,    44,    45,    27,    28,
       6,    77,    10,    42,     3,    77,    77,    17,    18,    19,
       3,    42,     3,    42,     4,     8,     3,     8,    94,    93,
       8,     8,    94,    94,   100,    32,   178,   179,    35,    36,
      37,    38,    42,     3,     3,     3,     3,     3,     8,     8,
       8,     8,     8,     3,     3,    39,    40,    41,     8,     8,
       3,     8,     4,     4,   130,     4,   132,    42,     4,   135,
     132,   132,   138,     4,    43,     4,   138,   138,     4,     4,
       7,     4,     4,     4,     4,     3,    94,    42,     7,    42,
       7,    42,     5,     5,     5,    43,     3,     7,     7,     7,
       6,     6,     4,     4,     4,    42,    22,    42,     7,     7,
       7,     4,     4,     4,     4,     4,   182,     4,     4,     4,
     182,   182,     5,     4,     4,     7,   192,    42,    42,     4,
     192,   192,     4,     4,     4,     4,   137,    77,    42,    42,
      86,   218,   186,   130,   134,   209,   182,   139,    43,    45,
     192,   239,   259,    -1,    -1,    43,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    42
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    39,    40,    41,    47,    48,    49,    50,     0,     5,
       7,     9,    42,    43,    44,    45,    53,    54,    55,    60,
       7,    65,     7,    51,    61,    56,    66,    52,    54,    62,
      63,    42,    58,    59,    10,    67,    68,    69,    11,    12,
      13,    14,    15,    16,    23,    26,    29,    42,    64,    71,
      72,    73,    75,    76,    78,    80,    82,    94,   111,   123,
       6,     3,     4,     8,     3,    70,     8,    74,     4,    77,
      79,    81,     4,   112,    83,   124,     4,     3,     8,    54,
      54,    42,     4,     4,    43,     4,     4,     4,     7,     4,
       4,     4,    72,     4,     7,    42,    42,    55,    57,    42,
      95,     5,     5,     5,    54,    71,    17,    18,    19,    64,
      96,    97,    98,   100,   102,     7,   113,   114,   115,     7,
      84,    85,    86,     7,   125,   126,     8,    99,   101,   103,
       3,     8,   116,     6,     3,    87,     6,     3,   127,     3,
       6,     4,     4,     4,    97,    24,    25,    64,    78,    80,
     117,   118,   119,   121,   115,    27,    28,    64,    88,    89,
      90,    92,    86,    30,    31,    33,    34,    64,    78,    80,
     128,   129,   130,   132,   133,   135,   126,     7,     7,     7,
     120,   122,     3,     8,    91,    93,     3,     8,   131,   136,
       4,   134,     3,     8,    20,    21,    64,    78,    80,   104,
     105,   106,   108,   104,   104,     4,     4,   118,     4,     4,
      89,     4,     4,    43,     4,   129,   107,   109,     3,     8,
       8,     8,    42,    42,    42,    54,    42,     5,    42,     4,
       4,   105,     7,   137,   138,    42,    22,   110,   139,     3,
       6,    32,    35,    36,    37,    38,   140,   141,   142,   144,
     145,   146,   147,   138,   143,     4,     4,     4,   148,     3,
       8,     4,    45,    43,    43,     4,   141,    42,    42
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    46,    48,    47,    49,    47,    50,    47,    52,    51,
      53,    54,    54,    54,    54,    54,    54,    54,    56,    55,
      57,    58,    58,    59,    59,    61,    60,    62,    62,    63,
      63,    64,    66,    65,    67,    68,    70,    69,    71,    71,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      74,    73,    75,    77,    76,    79,    78,    81,    80,    83,
      82,    84,    84,    85,    85,    87,    86,    88,    88,    88,
      89,    89,    91,    90,    93,    92,    95,    94,    96,    96,
      97,    97,    97,    97,    99,    98,   101,   100,   103,   102,
     104,   104,   105,   105,   105,   105,   105,   107,   106,   109,
     108,   110,   112,   111,   113,   113,   114,   114,   116,   115,
     117,   117,   118,   118,   118,   118,   118,   120,   119,   122,
     121,   124,   123,   125,   125,   127,   126,   128,   128,   129,
     129,   129,   129,   129,   129,   129,   131,   130,   132,   134,
     133,   136,   135,   137,   137,   139,   138,   140,   140,   141,
     141,   141,   141,   141,   143,   142,   144,   145,   146,   148,
     147
  };

  const signed char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     0,     6,     0,     6,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     1,     0,     6,     0,     1,     1,     3,     0,     4,
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
  "\"http-host\"", "\"http-port\"", "\"basic-authentication-realm\"",
  "\"user-context\"", "\"comment\"", "\"control-sockets\"", "\"dhcp4\"",
  "\"dhcp6\"", "\"d2\"", "\"socket-name\"", "\"socket-type\"", "\"unix\"",
  "\"basic-authentications\"", "\"user\"", "\"password\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"", "\"loggers\"",
  "\"name\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "START_JSON", "START_AGENT", "START_SUB_AGENT", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "sub_agent", "$@4", "json", "value", "map", "$@5",
  "map_value", "map_content", "not_empty_map", "list_generic", "$@6",
  "list_content", "not_empty_list", "unknown_map_entry",
  "agent_syntax_map", "$@7", "global_objects", "global_object",
  "agent_object", "$@8", "global_params", "global_param", "http_host",
  "$@9", "http_port", "basic_authentication_realm", "$@10", "user_context",
  "$@11", "comment", "$@12", "hooks_libraries", "$@13",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@14", "hooks_params", "hooks_param", "library",
  "$@15", "parameters", "$@16", "control_sockets", "$@17",
  "control_sockets_params", "control_socket", "dhcp4_server_socket",
  "$@18", "dhcp6_server_socket", "$@19", "d2_server_socket", "$@20",
  "control_socket_params", "control_socket_param", "socket_name", "$@21",
  "socket_type", "$@22", "socket_type_value", "basic_authentications",
  "$@23", "basic_auth_list", "not_empty_basic_auth_list", "basic_auth",
  "$@24", "basic_auth_params", "basic_auth_param", "user", "$@25",
  "password", "$@26", "loggers", "$@27", "loggers_entries", "logger_entry",
  "$@28", "logger_params", "logger_param", "name", "$@29", "debuglevel",
  "severity", "$@30", "output_options_list", "$@31",
  "output_options_list_content", "output_entry", "$@32",
  "output_params_list", "output_params", "output", "$@33", "flush",
  "maxsize", "maxver", "pattern", "$@34", YY_NULLPTR
  };
#endif


#if AGENT_DEBUG
  const short
  AgentParser::yyrline_[] =
  {
       0,   115,   115,   115,   116,   116,   117,   117,   125,   125,
     136,   142,   143,   144,   145,   146,   147,   148,   152,   152,
     163,   168,   169,   177,   181,   188,   188,   194,   195,   198,
     202,   215,   223,   223,   235,   239,   243,   243,   260,   261,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     278,   278,   286,   291,   291,   299,   299,   324,   324,   352,
     352,   362,   363,   366,   367,   370,   370,   378,   379,   380,
     383,   384,   387,   387,   395,   395,   405,   405,   418,   419,
     424,   425,   426,   427,   431,   431,   442,   442,   453,   453,
     464,   465,   469,   470,   471,   472,   473,   477,   477,   486,
     486,   494,   501,   501,   511,   512,   515,   516,   519,   519,
     527,   528,   531,   532,   533,   534,   535,   538,   538,   546,
     546,   558,   558,   570,   571,   575,   575,   583,   584,   587,
     588,   589,   590,   591,   592,   593,   596,   596,   604,   609,
     609,   617,   617,   627,   628,   631,   631,   639,   640,   643,
     644,   645,   646,   647,   650,   650,   658,   663,   668,   673,
     673
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
#line 2162 "agent_parser.cc"

#line 681 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
