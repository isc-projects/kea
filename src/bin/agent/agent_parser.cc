// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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

// Take the name prefix into account.
#define yylex   agent_lex

// First part of user declarations.

#line 39 "agent_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "agent_parser.h"

// User implementation prologue.

#line 53 "agent_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 33 "agent_parser.yy" // lalr1.cc:413

#include <agent/parser_context.h>

#line 59 "agent_parser.cc" // lalr1.cc:413


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
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
      yystack_print_ ();                \
  } while (false)

#else // !AGENT_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !AGENT_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "agent_parser.yy" // lalr1.cc:479
namespace isc { namespace agent {
#line 145 "agent_parser.cc" // lalr1.cc:479

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
        std::string yyr = "";
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
              // Fall through.
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


  /// Build a parser object.
  AgentParser::AgentParser (isc::agent::ParserContext& ctx_yyarg)
    :
#if AGENT_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  AgentParser::~AgentParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  AgentParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  AgentParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  AgentParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  AgentParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  AgentParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  AgentParser::symbol_number_type
  AgentParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  AgentParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  AgentParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 48: // value
      case 97: // socket_type_value
        value.move< ElementPtr > (that.value);
        break;

      case 39: // "boolean"
        value.move< bool > (that.value);
        break;

      case 38: // "floating point"
        value.move< double > (that.value);
        break;

      case 37: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 36: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  AgentParser::stack_symbol_type&
  AgentParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 48: // value
      case 97: // socket_type_value
        value.copy< ElementPtr > (that.value);
        break;

      case 39: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 38: // "floating point"
        value.copy< double > (that.value);
        break;

      case 37: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 36: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  AgentParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if AGENT_DEBUG
  template <typename Base>
  void
  AgentParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 36: // "constant string"

#line 96 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "agent_parser.cc" // lalr1.cc:636
        break;

      case 37: // "integer"

#line 96 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "agent_parser.cc" // lalr1.cc:636
        break;

      case 38: // "floating point"

#line 96 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "agent_parser.cc" // lalr1.cc:636
        break;

      case 39: // "boolean"

#line 96 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "agent_parser.cc" // lalr1.cc:636
        break;

      case 48: // value

#line 96 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "agent_parser.cc" // lalr1.cc:636
        break;

      case 97: // socket_type_value

#line 96 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 389 "agent_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  AgentParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  AgentParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  AgentParser::yypop_ (unsigned int n)
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

  inline AgentParser::state_type
  AgentParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  AgentParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  AgentParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  AgentParser::parse ()
  {
    // State.
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 48: // value
      case 97: // socket_type_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 39: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 38: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 37: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 36: // "constant string"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 107 "agent_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 630 "agent_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 108 "agent_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "agent_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 109 "agent_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.AGENT; }
#line 642 "agent_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 117 "agent_parser.yy" // lalr1.cc:859
    {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 652 "agent_parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 121 "agent_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 660 "agent_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 128 "agent_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 669 "agent_parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 134 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 675 "agent_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 135 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 681 "agent_parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 136 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 687 "agent_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 137 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 693 "agent_parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 138 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 699 "agent_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 139 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 705 "agent_parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 140 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 711 "agent_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 144 "agent_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 722 "agent_parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 149 "agent_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 732 "agent_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 167 "agent_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 741 "agent_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 171 "agent_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 751 "agent_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 178 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 760 "agent_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 181 "agent_parser.yy" // lalr1.cc:859
    {
}
#line 767 "agent_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 188 "agent_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 776 "agent_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 192 "agent_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 785 "agent_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 205 "agent_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 796 "agent_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 214 "agent_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 807 "agent_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 219 "agent_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 817 "agent_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 240 "agent_parser.yy" // lalr1.cc:859
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
#line 833 "agent_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 250 "agent_parser.yy" // lalr1.cc:859
    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 844 "agent_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 270 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 852 "agent_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 272 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 862 "agent_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 278 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 871 "agent_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 284 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 882 "agent_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 289 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 891 "agent_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 302 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 901 "agent_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 306 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 909 "agent_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 319 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 917 "agent_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 321 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 927 "agent_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 327 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 935 "agent_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 329 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 944 "agent_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 337 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 955 "agent_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 342 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 964 "agent_parser.cc" // lalr1.cc:859
    break;

  case 78:
#line 363 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4-server", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 975 "agent_parser.cc" // lalr1.cc:859
    break;

  case 79:
#line 368 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 984 "agent_parser.cc" // lalr1.cc:859
    break;

  case 80:
#line 374 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6-server", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 995 "agent_parser.cc" // lalr1.cc:859
    break;

  case 81:
#line 379 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1004 "agent_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 385 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2-server", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1015 "agent_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 390 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1024 "agent_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 406 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1032 "agent_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 408 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1042 "agent_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 415 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1050 "agent_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 417 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1059 "agent_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 423 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1065 "agent_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 429 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1073 "agent_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 431 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1082 "agent_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 436 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1090 "agent_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 438 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1099 "agent_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 443 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1107 "agent_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 445 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1116 "agent_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 455 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1127 "agent_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 460 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1136 "agent_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 477 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1147 "agent_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 482 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1156 "agent_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 494 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1166 "agent_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 498 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1174 "agent_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 513 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1182 "agent_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 515 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1192 "agent_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 521 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1201 "agent_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 526 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1209 "agent_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 528 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1219 "agent_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 534 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1230 "agent_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 539 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1239 "agent_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 548 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1249 "agent_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 552 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1257 "agent_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 560 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1265 "agent_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 562 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1275 "agent_parser.cc" // lalr1.cc:859
    break;


#line 1279 "agent_parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  AgentParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  AgentParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char AgentParser::yypact_ninf_ = -75;

  const signed char AgentParser::yytable_ninf_ = -1;

  const signed char
  AgentParser::yypact_[] =
  {
      43,   -75,   -75,   -75,     5,    -3,     0,    34,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,    -3,    -4,    -7,     6,   -75,    37,
      48,    53,    56,    80,   -75,   -75,   -75,   -75,   -75,    81,
     -75,    12,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    82,
      83,   -75,   -75,    44,   -75,   -75,   -75,   -75,   -75,   -75,
      -3,    -3,   -75,    52,    85,    86,    87,    88,    89,   -75,
      -7,   -75,    90,    58,    77,    92,     6,   -75,   -75,   -75,
      93,    91,    95,    -3,    -3,    -3,   -75,    68,   -75,   -75,
      94,   -75,    -3,     6,    76,   -75,   -75,   -75,   -75,    -6,
      98,   -75,    47,   -75,    50,   -75,   -75,   -75,   -75,   -75,
     -75,    51,   -75,   -75,   -75,   -75,   -75,   100,   104,   -75,
     -75,   105,    76,   -75,   106,   107,   108,    -6,   -75,    -9,
     -75,    98,   103,   -75,   109,   110,   111,   -75,   -75,   -75,
     -75,    60,   -75,   -75,   -75,   -75,   112,     4,     4,     4,
     116,   117,    18,   -75,   -75,     8,   -75,   -75,   -75,    62,
     -75,   -75,   -75,    63,    64,    78,    -3,   -75,    20,   112,
     -75,   118,   119,     4,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   120,   -75,   -75,    71,   -75,   -75,   -75,   -75,   -75,
     -75,    79,   113,   -75,   121,   122,    96,   123,    20,   -75,
     -75,   -75,   -75,    99,   124,   -75,   101,   -75,   -75,   127,
     -75,   -75,    25,   -75,   114,   127,   -75,   -75,    72,   -75,
     -75,   126,   114,   -75,   102,   -75,   -75
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    24,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      31,     5,     8,     7,    26,    20,     0,     0,    28,     0,
      27,     0,     0,    21,    41,    99,    93,    95,    97,     0,
      40,     0,    33,    35,    37,    38,    39,    36,    50,     0,
       0,    53,    49,     0,    43,    45,    46,    48,    47,    25,
       0,     0,    19,     0,     0,     0,     0,     0,     0,    30,
       0,    32,     0,     0,     0,     0,     0,     9,    29,    22,
       0,     0,     0,     0,     0,     0,    34,     0,    52,    70,
       0,    44,     0,     0,     0,    94,    96,    98,    51,     0,
      55,    23,     0,   104,     0,   101,   103,    78,    80,    82,
      77,     0,    72,    74,    75,    76,    59,     0,    56,    57,
      42,     0,     0,   100,     0,     0,     0,     0,    71,     0,
      54,     0,     0,   102,     0,     0,     0,    73,    66,    68,
      63,     0,    61,    64,    65,    58,     0,     0,     0,     0,
       0,     0,     0,    60,   108,     0,   106,    88,    90,     0,
      84,    86,    87,     0,     0,     0,     0,    62,     0,     0,
     105,     0,     0,     0,    79,    81,    83,    67,    69,   117,
     122,     0,   120,   116,     0,   110,   112,   114,   115,   113,
     107,     0,     0,    85,     0,     0,     0,     0,     0,   109,
      89,    92,    91,     0,     0,   119,     0,   111,   118,     0,
     121,   126,     0,   124,     0,     0,   123,   130,     0,   128,
     125,     0,     0,   127,     0,   129,   131
  };

  const signed char
  AgentParser::yypgoto_[] =
  {
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -23,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -26,   -75,   -75,
     -75,    61,   -75,   -75,    35,    69,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -18,   -75,   -75,   -16,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,    13,   -75,   -75,   -75,   -75,   -75,
     -75,   -67,   -34,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,    22,   -75,   -75,
     -75,   -22,   -75,   -75,   -52,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -66,   -75,   -75,   -74,   -75
  };

  const short int
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    32,    33,    19,    24,    29,    30,    52,    21,    26,
      41,    42,    43,    64,    53,    54,    55,    72,    56,    57,
      75,   117,   118,   119,   129,   141,   142,   143,   150,   144,
     151,    58,    99,   111,   112,   113,   124,   114,   125,   115,
     126,   159,   160,   161,   171,   162,   172,   202,    44,    66,
      45,    67,    46,    68,    47,    65,   104,   105,   106,   121,
     155,   156,   168,   184,   185,   186,   194,   187,   188,   197,
     189,   195,   212,   213,   214,   218,   219,   221
  };

  const unsigned char
  AgentParser::yytable_[] =
  {
      40,    28,     9,    34,    10,     8,    11,    20,   107,   108,
     109,   169,   138,   139,   170,    70,    35,    48,    49,    50,
      71,   157,   158,    36,    37,    38,    51,    39,   215,    39,
      39,   216,    31,    12,    13,    14,    15,    78,    79,   138,
     139,    22,    39,    59,    40,   179,   180,    76,   181,   182,
      76,    60,    77,   122,   127,   120,    39,    61,   123,   128,
      95,    96,    97,   152,    62,   173,   173,   173,   153,   101,
     174,   175,   176,   110,   198,   222,     1,     2,     3,   199,
     223,   163,   164,    63,    89,    69,    73,    74,    80,    81,
      82,    83,    84,    85,    87,    88,    90,    92,    93,   100,
     103,   110,    94,   140,    98,   116,   130,   131,   146,   132,
     134,   135,   136,   145,   177,   200,   147,   148,   149,   154,
     165,   166,   191,   192,   196,   203,   204,   206,   102,   209,
     224,    86,   201,   205,   211,   208,   167,   210,   226,   193,
     137,   217,   183,   178,   133,    91,   207,   190,   225,   220,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   183
  };

  const short int
  AgentParser::yycheck_[] =
  {
      26,    24,     5,    10,     7,     0,     9,     7,    14,    15,
      16,     3,    21,    22,     6,     3,    23,    11,    12,    13,
       8,    17,    18,    30,    31,    32,    20,    36,     3,    36,
      36,     6,    36,    36,    37,    38,    39,    60,    61,    21,
      22,     7,    36,     6,    70,    25,    26,     3,    28,    29,
       3,     3,     8,     3,     3,     8,    36,     4,     8,     8,
      83,    84,    85,     3,     8,     3,     3,     3,     8,    92,
       8,     8,     8,    99,     3,     3,    33,    34,    35,     8,
       8,   148,   149,     3,     7,     4,     4,     4,    36,     4,
       4,     4,     4,     4,     4,    37,     4,     4,     7,     5,
      24,   127,     7,   129,    36,     7,     6,     3,     5,     4,
       4,     4,     4,   131,    36,    36,     7,     7,     7,     7,
       4,     4,     4,     4,     4,     4,     4,     4,    93,     5,
       4,    70,    19,    37,     7,    36,   152,    36,    36,   173,
     127,    27,   168,   166,   122,    76,   198,   169,   222,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   198
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    33,    34,    35,    41,    42,    43,    44,     0,     5,
       7,     9,    36,    37,    38,    39,    47,    48,    49,    53,
       7,    58,     7,    45,    54,    50,    59,    46,    48,    55,
      56,    36,    51,    52,    10,    23,    30,    31,    32,    36,
      57,    60,    61,    62,    98,   100,   102,   104,    11,    12,
      13,    20,    57,    64,    65,    66,    68,    69,    81,     6,
       3,     4,     8,     3,    63,   105,    99,   101,   103,     4,
       3,     8,    67,     4,     4,    70,     3,     8,    48,    48,
      36,     4,     4,     4,     4,     4,    61,     4,    37,     7,
       4,    65,     4,     7,     7,    48,    48,    48,    36,    82,
       5,    48,    64,    24,   106,   107,   108,    14,    15,    16,
      57,    83,    84,    85,    87,    89,     7,    71,    72,    73,
       8,   109,     3,     8,    86,    88,    90,     3,     8,    74,
       6,     3,     4,   107,     4,     4,     4,    84,    21,    22,
      57,    75,    76,    77,    79,    73,     5,     7,     7,     7,
      78,    80,     3,     8,     7,   110,   111,    17,    18,    91,
      92,    93,    95,    91,    91,     4,     4,    76,   112,     3,
       6,    94,    96,     3,     8,     8,     8,    36,    48,    25,
      26,    28,    29,    57,   113,   114,   115,   117,   118,   120,
     111,     4,     4,    92,   116,   121,     4,   119,     3,     8,
      36,    19,    97,     4,     4,    37,     4,   114,    36,     5,
      36,     7,   122,   123,   124,     3,     6,    27,   125,   126,
     123,   127,     3,     8,     4,   126,    36
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    40,    42,    41,    43,    41,    44,    41,    46,    45,
      47,    48,    48,    48,    48,    48,    48,    48,    50,    49,
      51,    51,    52,    52,    54,    53,    55,    55,    56,    56,
      57,    59,    58,    60,    60,    61,    61,    61,    61,    61,
      61,    63,    62,    64,    64,    65,    65,    65,    65,    65,
      67,    66,    68,    70,    69,    71,    71,    72,    72,    74,
      73,    75,    75,    75,    76,    76,    78,    77,    80,    79,
      82,    81,    83,    83,    84,    84,    84,    84,    86,    85,
      88,    87,    90,    89,    91,    91,    92,    92,    94,    93,
      96,    95,    97,    99,    98,   101,   100,   103,   102,   105,
     104,   106,   106,   107,   109,   108,   110,   110,   112,   111,
     113,   113,   114,   114,   114,   114,   114,   116,   115,   117,
     119,   118,   121,   120,   122,   122,   124,   123,   125,   125,
     127,   126
  };

  const unsigned char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     1,     3,     5,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       0,     6,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const AgentParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Control-agent\"",
  "\"http-host\"", "\"http-port\"", "\"control-sockets\"",
  "\"dhcp4-server\"", "\"dhcp6-server\"", "\"d2-server\"",
  "\"socket-name\"", "\"socket-type\"", "\"unix\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"Logging\"", "\"loggers\"",
  "\"name\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"Dhcp4\"", "\"Dhcp6\"", "\"DhcpDdns\"", "START_JSON",
  "START_AGENT", "START_SUB_AGENT", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "sub_agent", "$@4", "json", "value", "map", "$@5", "map_content",
  "not_empty_map", "list_generic", "$@6", "list_content", "not_empty_list",
  "unknown_map_entry", "agent_syntax_map", "$@7", "global_objects",
  "global_object", "agent_object", "$@8", "global_params", "global_param",
  "http_host", "$@9", "http_port", "hooks_libraries", "$@10",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@11", "hooks_params", "hooks_param", "library",
  "$@12", "parameters", "$@13", "control_sockets", "$@14",
  "control_sockets_params", "control_socket", "dhcp4_server_socket",
  "$@15", "dhcp6_server_socket", "$@16", "d2_server_socket", "$@17",
  "control_socket_params", "control_socket_param", "socket_name", "$@18",
  "socket_type", "$@19", "socket_type_value", "dhcp4_json_object", "$@20",
  "dhcp6_json_object", "$@21", "dhcpddns_json_object", "$@22",
  "logging_object", "$@23", "logging_params", "logging_param", "loggers",
  "$@24", "loggers_entries", "logger_entry", "$@25", "logger_params",
  "logger_param", "name", "$@26", "debuglevel", "severity", "$@27",
  "output_options_list", "$@28", "output_options_list_content",
  "output_entry", "$@29", "output_params", "output_param", "$@30", YY_NULLPTR
  };

#if AGENT_DEBUG
  const unsigned short int
  AgentParser::yyrline_[] =
  {
       0,   107,   107,   107,   108,   108,   109,   109,   117,   117,
     128,   134,   135,   136,   137,   138,   139,   140,   144,   144,
     158,   159,   167,   171,   178,   178,   184,   185,   188,   192,
     205,   214,   214,   226,   227,   231,   232,   233,   234,   235,
     236,   240,   240,   257,   258,   263,   264,   265,   266,   267,
     270,   270,   278,   284,   284,   294,   295,   298,   299,   302,
     302,   310,   311,   312,   315,   316,   319,   319,   327,   327,
     337,   337,   350,   351,   356,   357,   358,   359,   363,   363,
     374,   374,   385,   385,   396,   397,   401,   402,   406,   406,
     415,   415,   423,   429,   429,   436,   436,   443,   443,   455,
     455,   468,   469,   473,   477,   477,   489,   490,   494,   494,
     502,   503,   506,   507,   508,   509,   510,   513,   513,   521,
     526,   526,   534,   534,   544,   545,   548,   548,   556,   557,
     560,   560
  };

  // Print the state stack on the debug stream.
  void
  AgentParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  AgentParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // AGENT_DEBUG


#line 14 "agent_parser.yy" // lalr1.cc:1167
} } // isc::agent
#line 1823 "agent_parser.cc" // lalr1.cc:1167
#line 568 "agent_parser.yy" // lalr1.cc:1168


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
