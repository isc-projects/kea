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
      case 94: // socket_type_value
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
      case 94: // socket_type_value
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

#line 97 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "agent_parser.cc" // lalr1.cc:636
        break;

      case 37: // "integer"

#line 97 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "agent_parser.cc" // lalr1.cc:636
        break;

      case 38: // "floating point"

#line 97 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "agent_parser.cc" // lalr1.cc:636
        break;

      case 39: // "boolean"

#line 97 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "agent_parser.cc" // lalr1.cc:636
        break;

      case 48: // value

#line 97 "agent_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "agent_parser.cc" // lalr1.cc:636
        break;

      case 94: // socket_type_value

#line 97 "agent_parser.yy" // lalr1.cc:636
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
      case 94: // socket_type_value
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
#line 108 "agent_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 630 "agent_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 109 "agent_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.KEYWORDS; }
#line 636 "agent_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 110 "agent_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.KEYWORDS; }
#line 642 "agent_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 118 "agent_parser.yy" // lalr1.cc:859
    {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 652 "agent_parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 122 "agent_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 660 "agent_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 129 "agent_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 669 "agent_parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 135 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 675 "agent_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 136 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 681 "agent_parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 137 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 687 "agent_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 138 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 693 "agent_parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 139 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 699 "agent_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 140 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 705 "agent_parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 141 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 711 "agent_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 145 "agent_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 722 "agent_parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 150 "agent_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 732 "agent_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 168 "agent_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 741 "agent_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 172 "agent_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 751 "agent_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 179 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 760 "agent_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 182 "agent_parser.yy" // lalr1.cc:859
    {
}
#line 767 "agent_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 189 "agent_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 776 "agent_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 193 "agent_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 785 "agent_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 206 "agent_parser.yy" // lalr1.cc:859
    {
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in map.");
}
#line 795 "agent_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 214 "agent_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 806 "agent_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 219 "agent_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 816 "agent_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 240 "agent_parser.yy" // lalr1.cc:859
    {
    // Let's create a MapElement that will represent it, add it to the top level
    // map (that's already on the stack) and put the new map on the stack as well,
    // so child elements will be able to add themselves to it.
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Control-agent", m);
    ctx.stack_.push_back(m);

    // And tell the lexer that we definitely want keywords to be recognized.
    ctx.enter(ctx.KEYWORDS);
}
#line 832 "agent_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 250 "agent_parser.yy" // lalr1.cc:859
    {
    // Ok, we're done with parsing control-agent. Let's take the map off the stack.
    ctx.stack_.pop_back();

    // And tell the lexer to return to its previous state (probably KEYWORDS as well)
    ctx.leave();
}
#line 844 "agent_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 271 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
}
#line 853 "agent_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 276 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 862 "agent_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 282 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
}
#line 872 "agent_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 286 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 880 "agent_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 298 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 890 "agent_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 302 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 898 "agent_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 315 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 906 "agent_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 317 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 916 "agent_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 323 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 924 "agent_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 325 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 933 "agent_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 333 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
}
#line 943 "agent_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 337 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 951 "agent_parser.cc" // lalr1.cc:859
    break;

  case 77:
#line 357 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4-server", m);
    ctx.stack_.push_back(m);
}
#line 961 "agent_parser.cc" // lalr1.cc:859
    break;

  case 78:
#line 361 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 969 "agent_parser.cc" // lalr1.cc:859
    break;

  case 79:
#line 366 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6-server", m);
    ctx.stack_.push_back(m);
}
#line 979 "agent_parser.cc" // lalr1.cc:859
    break;

  case 80:
#line 370 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 987 "agent_parser.cc" // lalr1.cc:859
    break;

  case 81:
#line 375 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2-server", m);
    ctx.stack_.push_back(m);
}
#line 997 "agent_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 379 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1005 "agent_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 394 "agent_parser.yy" // lalr1.cc:859
    {
}
#line 1012 "agent_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 395 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as< ElementPtr > ());
}
#line 1020 "agent_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 400 "agent_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1026 "agent_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 403 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1034 "agent_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 405 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1044 "agent_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 414 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1052 "agent_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 416 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1061 "agent_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 421 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1069 "agent_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 423 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1078 "agent_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 428 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1086 "agent_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 430 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1095 "agent_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 440 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
}
#line 1105 "agent_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 444 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1113 "agent_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 460 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
}
#line 1123 "agent_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 464 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1131 "agent_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 475 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1141 "agent_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 479 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1149 "agent_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 494 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1157 "agent_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 496 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1167 "agent_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 502 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1176 "agent_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 506 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1184 "agent_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 508 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1194 "agent_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 514 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
}
#line 1204 "agent_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 518 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1212 "agent_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 526 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1222 "agent_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 530 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1230 "agent_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 538 "agent_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1238 "agent_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 540 "agent_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1248 "agent_parser.cc" // lalr1.cc:859
    break;


#line 1252 "agent_parser.cc" // lalr1.cc:859
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


  const signed char AgentParser::yypact_ninf_ = -81;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short int
  AgentParser::yypact_[] =
  {
       7,   -81,   -81,   -81,     5,    -3,    14,    42,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,    -3,   -24,    -7,    -4,   -81,     8,
      27,    81,    67,    83,   -81,   -81,   -81,   -81,   -81,    84,
     -81,    12,   -81,   -81,   -81,   -81,   -81,   -81,    85,    86,
      87,   -81,   -81,    19,   -81,   -81,   -81,   -81,   -81,   -81,
      -3,    -3,   -81,    51,    88,    89,    90,    91,    92,   -81,
      -7,   -81,    93,    68,    60,    94,    -4,   -81,   -81,   -81,
      95,    96,    98,    -3,    -3,    -3,   -81,   -81,   -81,   -81,
     101,   -81,    -3,    -4,    77,   -81,   -81,   -81,     3,   100,
     -81,    23,   -81,    45,   -81,   -81,   -81,   -81,   -81,   -81,
      47,   -81,   -81,   -81,   -81,   -81,   102,   106,   -81,   -81,
     107,    77,   -81,   108,   109,   110,    64,   -81,    -8,   -81,
     100,   105,   -81,   111,   112,   113,   -81,   -81,   -81,   -81,
      48,   -81,   -81,   -81,   -81,   114,    61,    61,    61,   118,
     119,    65,   -81,   -81,    70,   -81,   -81,   -81,    49,   -81,
     -81,   -81,    55,    56,    79,    -3,   -81,    18,   114,   -81,
     120,   121,    61,   -81,   -81,   -81,   -81,   -81,   -81,   122,
     -81,   -81,   -81,    62,   -81,   -81,   -81,   -81,   -81,   -81,
     115,    80,   -81,   123,    97,   124,   125,    18,   -81,   -81,
     -81,   -81,   126,   -81,    99,   103,   -81,   129,   -81,   -81,
     -81,    71,   -81,   104,   129,   -81,   -81,    63,   -81,   -81,
     128,   104,   -81,   116,   -81,   -81
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    24,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      31,     5,     8,     7,    26,    20,     0,     0,    28,     0,
      27,     0,     0,    21,    41,    98,    92,    94,    96,     0,
      40,     0,    33,    35,    37,    38,    39,    36,     0,     0,
       0,    52,    49,     0,    43,    45,    46,    48,    47,    25,
       0,     0,    19,     0,     0,     0,     0,     0,     0,    30,
       0,    32,     0,     0,     0,     0,     0,     9,    29,    22,
       0,     0,     0,     0,     0,     0,    34,    69,    50,    51,
       0,    44,     0,     0,     0,    93,    95,    97,     0,    54,
      23,     0,   103,     0,   100,   102,    77,    79,    81,    73,
       0,    71,    74,    75,    76,    58,     0,    55,    56,    42,
       0,     0,    99,     0,     0,     0,     0,    70,     0,    53,
       0,     0,   101,     0,     0,     0,    72,    65,    67,    62,
       0,    60,    63,    64,    57,     0,     0,     0,     0,     0,
       0,     0,    59,   107,     0,   105,    87,    90,     0,    83,
      85,    86,     0,     0,     0,     0,    61,     0,     0,   104,
       0,     0,     0,    78,    80,    82,    66,    68,   121,     0,
     119,   116,   115,     0,   109,   111,   113,   114,   112,   106,
       0,     0,    84,     0,     0,     0,     0,     0,   108,    89,
      88,    91,     0,   118,     0,     0,   110,     0,   120,   117,
     125,     0,   123,     0,     0,   122,   129,     0,   127,   124,
       0,     0,   126,     0,   128,   130
  };

  const signed char
  AgentParser::yypgoto_[] =
  {
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -23,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -26,   -81,   -81,
     -81,    73,   -81,   -81,    24,    57,   -81,   -81,   -81,   -81,
     -81,   -81,    10,   -81,   -81,   -13,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,    20,   -81,   -81,   -81,   -81,   -81,   -81,
     -80,   -28,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,    26,   -81,   -81,   -81,
     -20,   -81,   -81,   -52,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -65,   -81,   -81,   -71,   -81
  };

  const short int
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    32,    33,    19,    24,    29,    30,    52,    21,    26,
      41,    42,    43,    64,    53,    54,    55,    56,    57,    75,
     116,   117,   118,   128,   140,   141,   142,   149,   143,   150,
      58,    98,   110,   111,   112,   123,   113,   124,   114,   125,
     158,   159,   160,   170,   200,   161,   171,    44,    66,    45,
      67,    46,    68,    47,    65,   103,   104,   105,   120,   154,
     155,   167,   183,   184,   185,   196,   186,   187,   195,   188,
     193,   211,   212,   213,   217,   218,   220
  };

  const unsigned char
  AgentParser::yytable_[] =
  {
      40,    28,     9,    34,    10,     8,    11,    48,    49,    50,
     137,   138,    31,    51,    59,    70,    35,   106,   107,   108,
      71,    20,    76,    36,    37,    38,    76,    77,    39,    39,
      60,   119,    39,    12,    13,    14,    15,    78,    79,    39,
       1,     2,     3,   178,    40,   179,   180,   181,   121,    22,
     126,   151,   172,   122,    39,   127,   152,   173,   172,   172,
      95,    96,    97,   174,   175,   197,   221,   162,   163,   100,
     198,   222,   109,   168,   214,    62,   169,   215,   106,   107,
     108,   156,   157,   137,   138,    61,    63,    80,    69,    72,
      73,    74,    81,    82,    83,    84,    85,    89,    90,    92,
      87,   102,   139,    93,    88,    94,    99,   115,   129,   130,
     145,   131,   133,   134,   135,   176,   201,   101,   146,   147,
     148,   153,   164,   165,   190,   191,   194,   202,   204,   205,
     216,   207,   223,    91,   203,   208,   210,   199,   166,   209,
     144,   182,   177,    86,   192,   206,   136,   132,   189,   219,
     224,     0,   225,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182
  };

  const short int
  AgentParser::yycheck_[] =
  {
      26,    24,     5,    10,     7,     0,     9,    11,    12,    13,
      18,    19,    36,    17,     6,     3,    23,    14,    15,    16,
       8,     7,     3,    30,    31,    32,     3,     8,    36,    36,
       3,     8,    36,    36,    37,    38,    39,    60,    61,    36,
      33,    34,    35,    25,    70,    27,    28,    29,     3,     7,
       3,     3,     3,     8,    36,     8,     8,     8,     3,     3,
      83,    84,    85,     8,     8,     3,     3,   147,   148,    92,
       8,     8,    98,     3,     3,     8,     6,     6,    14,    15,
      16,    20,    21,    18,    19,     4,     3,    36,     4,     4,
       4,     4,     4,     4,     4,     4,     4,    37,     4,     4,
       7,    24,   128,     7,    36,     7,     5,     7,     6,     3,
       5,     4,     4,     4,     4,    36,    36,    93,     7,     7,
       7,     7,     4,     4,     4,     4,     4,     4,     4,     4,
      26,     5,     4,    76,    37,    36,     7,    22,   151,    36,
     130,   167,   165,    70,   172,   197,   126,   121,   168,   214,
     221,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   197
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    33,    34,    35,    41,    42,    43,    44,     0,     5,
       7,     9,    36,    37,    38,    39,    47,    48,    49,    53,
       7,    58,     7,    45,    54,    50,    59,    46,    48,    55,
      56,    36,    51,    52,    10,    23,    30,    31,    32,    36,
      57,    60,    61,    62,    97,    99,   101,   103,    11,    12,
      13,    17,    57,    64,    65,    66,    67,    68,    80,     6,
       3,     4,     8,     3,    63,   104,    98,   100,   102,     4,
       3,     8,     4,     4,     4,    69,     3,     8,    48,    48,
      36,     4,     4,     4,     4,     4,    61,     7,    36,    37,
       4,    65,     4,     7,     7,    48,    48,    48,    81,     5,
      48,    64,    24,   105,   106,   107,    14,    15,    16,    57,
      82,    83,    84,    86,    88,     7,    70,    71,    72,     8,
     108,     3,     8,    85,    87,    89,     3,     8,    73,     6,
       3,     4,   106,     4,     4,     4,    83,    18,    19,    57,
      74,    75,    76,    78,    72,     5,     7,     7,     7,    77,
      79,     3,     8,     7,   109,   110,    20,    21,    90,    91,
      92,    95,    90,    90,     4,     4,    75,   111,     3,     6,
      93,    96,     3,     8,     8,     8,    36,    48,    25,    27,
      28,    29,    57,   112,   113,   114,   116,   117,   119,   110,
       4,     4,    91,   120,     4,   118,   115,     3,     8,    22,
      94,    36,     4,    37,     4,     4,   113,     5,    36,    36,
       7,   121,   122,   123,     3,     6,    26,   124,   125,   122,
     126,     3,     8,     4,   125,    36
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    40,    42,    41,    43,    41,    44,    41,    46,    45,
      47,    48,    48,    48,    48,    48,    48,    48,    50,    49,
      51,    51,    52,    52,    54,    53,    55,    55,    56,    56,
      57,    59,    58,    60,    60,    61,    61,    61,    61,    61,
      61,    63,    62,    64,    64,    65,    65,    65,    65,    65,
      66,    67,    69,    68,    70,    70,    71,    71,    73,    72,
      74,    74,    74,    75,    75,    77,    76,    79,    78,    81,
      80,    82,    82,    82,    83,    83,    83,    85,    84,    87,
      86,    89,    88,    90,    90,    91,    91,    93,    92,    94,
      96,    95,    98,    97,   100,    99,   102,   101,   104,   103,
     105,   105,   106,   108,   107,   109,   109,   111,   110,   112,
     112,   113,   113,   113,   113,   113,   115,   114,   116,   118,
     117,   120,   119,   121,   121,   123,   122,   124,   124,   126,
     125
  };

  const unsigned char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     1,     3,     5,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     6,     1,     3,     1,     1,     0,     4,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     0,
       4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const AgentParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Control-agent\"",
  "\"control-sockets\"", "\"http-host\"", "\"http-port\"",
  "\"dhcp4-server\"", "\"dhcp6-server\"", "\"d2-server\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"socket-type\"", "\"socket-name\"", "\"unix\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"name\"", "\"Dhcp4\"", "\"Dhcp6\"", "\"DhcpDdns\"",
  "START_JSON", "START_AGENT", "START_SUB_AGENT", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "sub_agent", "$@4", "json", "value", "map", "$@5",
  "map_content", "not_empty_map", "list_generic", "$@6", "list_content",
  "not_empty_list", "unknown_map_entry", "agent_syntax_map", "$@7",
  "global_objects", "global_object", "agent_object", "$@8",
  "global_params", "global_param", "http_host", "http_port",
  "hooks_libraries", "$@9", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@10",
  "hooks_params", "hooks_param", "library", "$@11", "parameters", "$@12",
  "control_sockets", "$@13", "control_sockets_params", "control_socket",
  "dhcp4_server_socket", "$@14", "dhcp6_server_socket", "$@15",
  "d2_server_socket", "$@16", "control_socket_params",
  "control_socket_param", "socket_type", "$@17", "socket_type_value",
  "socket_name", "$@18", "dhcp4_json_object", "$@19", "dhcp6_json_object",
  "$@20", "dhcpddns_json_object", "$@21", "logging_object", "$@22",
  "logging_params", "logging_param", "loggers", "$@23", "loggers_entries",
  "logger_entry", "$@24", "logger_params", "logger_param", "name", "$@25",
  "debuglevel", "severity", "$@26", "output_options_list", "$@27",
  "output_options_list_content", "output_entry", "$@28", "output_params",
  "output_param", "$@29", YY_NULLPTR
  };

#if AGENT_DEBUG
  const unsigned short int
  AgentParser::yyrline_[] =
  {
       0,   108,   108,   108,   109,   109,   110,   110,   118,   118,
     129,   135,   136,   137,   138,   139,   140,   141,   145,   145,
     159,   160,   168,   172,   179,   179,   185,   186,   189,   193,
     206,   214,   214,   226,   227,   231,   232,   233,   234,   235,
     236,   240,   240,   258,   259,   264,   265,   266,   267,   268,
     271,   276,   282,   282,   290,   291,   294,   295,   298,   298,
     306,   307,   308,   311,   312,   315,   315,   323,   323,   333,
     333,   344,   345,   346,   351,   352,   353,   357,   357,   366,
     366,   375,   375,   384,   385,   389,   390,   394,   394,   400,
     403,   403,   414,   414,   421,   421,   428,   428,   440,   440,
     451,   452,   456,   460,   460,   470,   471,   475,   475,   483,
     484,   487,   488,   489,   490,   491,   494,   494,   502,   506,
     506,   514,   514,   522,   523,   526,   526,   534,   535,   538,
     538
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
#line 1797 "agent_parser.cc" // lalr1.cc:1167
#line 546 "agent_parser.yy" // lalr1.cc:1168


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
