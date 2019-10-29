// A Bison parser, made by GNU Bison 3.4.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.


// Take the name prefix into account.
#define yylex   agent_lex



#include "agent_parser.h"


// Unqualified %code blocks.
#line 33 "agent_parser.yy"

#include <agent/parser_context.h>

#line 51 "agent_parser.cc"


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
      yystack_print_ ();                \
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
#line 143 "agent_parser.cc"


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

  AgentParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
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

  AgentParser::symbol_number_type
  AgentParser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  AgentParser::stack_symbol_type::stack_symbol_type ()
  {}

  AgentParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 54: // value
      case 57: // map_value
      case 108: // socket_type_value
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
    switch (that.type_get ())
    {
      case 54: // value
      case 57: // map_value
      case 108: // socket_type_value
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
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  AgentParser::stack_symbol_type&
  AgentParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 54: // value
      case 57: // map_value
      case 108: // socket_type_value
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
  AgentParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 42: // "constant string"
#line 104 "agent_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 390 "agent_parser.cc"
        break;

      case 43: // "integer"
#line 104 "agent_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 396 "agent_parser.cc"
        break;

      case 44: // "floating point"
#line 104 "agent_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 402 "agent_parser.cc"
        break;

      case 45: // "boolean"
#line 104 "agent_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 408 "agent_parser.cc"
        break;

      case 54: // value
#line 104 "agent_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "agent_parser.cc"
        break;

      case 57: // map_value
#line 104 "agent_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 420 "agent_parser.cc"
        break;

      case 108: // socket_type_value
#line 104 "agent_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 426 "agent_parser.cc"
        break;

      default:
        break;
    }
    yyo << ')';
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
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
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
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
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
      case 108: // socket_type_value
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
#line 688 "agent_parser.cc"
    break;

  case 4:
#line 116 "agent_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 694 "agent_parser.cc"
    break;

  case 6:
#line 117 "agent_parser.yy"
    { ctx.ctx_ = ctx.AGENT; }
#line 700 "agent_parser.cc"
    break;

  case 8:
#line 125 "agent_parser.yy"
    {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 710 "agent_parser.cc"
    break;

  case 9:
#line 129 "agent_parser.yy"
    {
    // parsing completed
}
#line 718 "agent_parser.cc"
    break;

  case 10:
#line 136 "agent_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 727 "agent_parser.cc"
    break;

  case 11:
#line 142 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 733 "agent_parser.cc"
    break;

  case 12:
#line 143 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 739 "agent_parser.cc"
    break;

  case 13:
#line 144 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 745 "agent_parser.cc"
    break;

  case 14:
#line 145 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 751 "agent_parser.cc"
    break;

  case 15:
#line 146 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 757 "agent_parser.cc"
    break;

  case 16:
#line 147 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 763 "agent_parser.cc"
    break;

  case 17:
#line 148 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 769 "agent_parser.cc"
    break;

  case 18:
#line 152 "agent_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 780 "agent_parser.cc"
    break;

  case 19:
#line 157 "agent_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 790 "agent_parser.cc"
    break;

  case 20:
#line 163 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 796 "agent_parser.cc"
    break;

  case 23:
#line 177 "agent_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 805 "agent_parser.cc"
    break;

  case 24:
#line 181 "agent_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 815 "agent_parser.cc"
    break;

  case 25:
#line 188 "agent_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 824 "agent_parser.cc"
    break;

  case 26:
#line 191 "agent_parser.yy"
    {
}
#line 831 "agent_parser.cc"
    break;

  case 29:
#line 198 "agent_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 840 "agent_parser.cc"
    break;

  case 30:
#line 202 "agent_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 849 "agent_parser.cc"
    break;

  case 31:
#line 215 "agent_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 860 "agent_parser.cc"
    break;

  case 32:
#line 224 "agent_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 871 "agent_parser.cc"
    break;

  case 33:
#line 229 "agent_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 881 "agent_parser.cc"
    break;

  case 42:
#line 250 "agent_parser.yy"
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
#line 897 "agent_parser.cc"
    break;

  case 43:
#line 260 "agent_parser.yy"
    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 908 "agent_parser.cc"
    break;

  case 54:
#line 283 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 916 "agent_parser.cc"
    break;

  case 55:
#line 285 "agent_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 926 "agent_parser.cc"
    break;

  case 56:
#line 291 "agent_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 935 "agent_parser.cc"
    break;

  case 57:
#line 296 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 943 "agent_parser.cc"
    break;

  case 58:
#line 298 "agent_parser.yy"
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
#line 970 "agent_parser.cc"
    break;

  case 59:
#line 321 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 978 "agent_parser.cc"
    break;

  case 60:
#line 323 "agent_parser.yy"
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
#line 1007 "agent_parser.cc"
    break;

  case 61:
#line 349 "agent_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1018 "agent_parser.cc"
    break;

  case 62:
#line 354 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1027 "agent_parser.cc"
    break;

  case 67:
#line 367 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1037 "agent_parser.cc"
    break;

  case 68:
#line 371 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1045 "agent_parser.cc"
    break;

  case 74:
#line 384 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1053 "agent_parser.cc"
    break;

  case 75:
#line 386 "agent_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1063 "agent_parser.cc"
    break;

  case 76:
#line 392 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1071 "agent_parser.cc"
    break;

  case 77:
#line 394 "agent_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1080 "agent_parser.cc"
    break;

  case 78:
#line 402 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1091 "agent_parser.cc"
    break;

  case 79:
#line 407 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1100 "agent_parser.cc"
    break;

  case 86:
#line 428 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1111 "agent_parser.cc"
    break;

  case 87:
#line 433 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "agent_parser.cc"
    break;

  case 88:
#line 439 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1131 "agent_parser.cc"
    break;

  case 89:
#line 444 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "agent_parser.cc"
    break;

  case 90:
#line 450 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1151 "agent_parser.cc"
    break;

  case 91:
#line 455 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "agent_parser.cc"
    break;

  case 99:
#line 474 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1168 "agent_parser.cc"
    break;

  case 100:
#line 476 "agent_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1178 "agent_parser.cc"
    break;

  case 101:
#line 483 "agent_parser.yy"
    {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1186 "agent_parser.cc"
    break;

  case 102:
#line 485 "agent_parser.yy"
    {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1195 "agent_parser.cc"
    break;

  case 103:
#line 491 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "agent_parser.cc"
    break;

  case 104:
#line 497 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1209 "agent_parser.cc"
    break;

  case 105:
#line 499 "agent_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1218 "agent_parser.cc"
    break;

  case 106:
#line 504 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1226 "agent_parser.cc"
    break;

  case 107:
#line 506 "agent_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1235 "agent_parser.cc"
    break;

  case 108:
#line 511 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1243 "agent_parser.cc"
    break;

  case 109:
#line 513 "agent_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1252 "agent_parser.cc"
    break;

  case 110:
#line 523 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1263 "agent_parser.cc"
    break;

  case 111:
#line 528 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1272 "agent_parser.cc"
    break;

  case 115:
#line 545 "agent_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1283 "agent_parser.cc"
    break;

  case 116:
#line 550 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1292 "agent_parser.cc"
    break;

  case 119:
#line 562 "agent_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1302 "agent_parser.cc"
    break;

  case 120:
#line 566 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1310 "agent_parser.cc"
    break;

  case 130:
#line 583 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1318 "agent_parser.cc"
    break;

  case 131:
#line 585 "agent_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1328 "agent_parser.cc"
    break;

  case 132:
#line 591 "agent_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1337 "agent_parser.cc"
    break;

  case 133:
#line 596 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1345 "agent_parser.cc"
    break;

  case 134:
#line 598 "agent_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1355 "agent_parser.cc"
    break;

  case 135:
#line 604 "agent_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1366 "agent_parser.cc"
    break;

  case 136:
#line 609 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1375 "agent_parser.cc"
    break;

  case 139:
#line 618 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1385 "agent_parser.cc"
    break;

  case 140:
#line 622 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1393 "agent_parser.cc"
    break;

  case 148:
#line 637 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1401 "agent_parser.cc"
    break;

  case 149:
#line 639 "agent_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1411 "agent_parser.cc"
    break;

  case 150:
#line 645 "agent_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1420 "agent_parser.cc"
    break;

  case 151:
#line 650 "agent_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1429 "agent_parser.cc"
    break;

  case 152:
#line 655 "agent_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1438 "agent_parser.cc"
    break;

  case 153:
#line 660 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1446 "agent_parser.cc"
    break;

  case 154:
#line 662 "agent_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1456 "agent_parser.cc"
    break;


#line 1460 "agent_parser.cc"

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
      YY_STACK_PRINT ();

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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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


  const signed char AgentParser::yypact_ninf_ = -115;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      71,  -115,  -115,  -115,     8,     2,    -5,     3,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,     2,   -19,    12,    13,  -115,    15,
      35,    48,    51,    74,  -115,  -115,  -115,  -115,  -115,    75,
    -115,    28,  -115,  -115,  -115,  -115,  -115,  -115,  -115,    83,
    -115,  -115,    84,  -115,  -115,  -115,    53,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,     2,     2,  -115,    65,
     104,   109,   110,   111,   112,  -115,    12,  -115,   113,    76,
     114,   116,   115,   120,   121,    13,  -115,  -115,  -115,   125,
     123,   124,     2,     2,     2,  -115,    90,  -115,   126,    92,
    -115,   130,   131,  -115,     2,    13,   117,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,    -2,   132,   133,  -115,    57,    70,
    -115,  -115,  -115,  -115,  -115,  -115,    73,  -115,  -115,  -115,
    -115,  -115,   135,   134,  -115,  -115,    14,  -115,  -115,   117,
    -115,   138,   140,   141,    -2,  -115,     9,  -115,   132,    44,
     133,  -115,  -115,   139,   142,   143,  -115,  -115,  -115,  -115,
      82,  -115,  -115,  -115,  -115,  -115,  -115,   144,  -115,  -115,
    -115,  -115,    93,  -115,  -115,  -115,  -115,  -115,  -115,    -1,
      -1,    -1,   147,   148,     6,  -115,   149,   150,   118,   151,
      44,  -115,  -115,  -115,  -115,  -115,  -115,    94,  -115,  -115,
    -115,    95,    96,   105,     2,  -115,   122,   152,  -115,   128,
    -115,   154,   155,    -1,  -115,  -115,  -115,  -115,  -115,  -115,
     153,  -115,   129,   145,  -115,  -115,   103,  -115,  -115,  -115,
    -115,    60,   153,  -115,  -115,   158,   159,   161,  -115,    97,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,   168,   136,   146,
     156,   169,    60,  -115,   137,  -115,  -115,  -115,   160,  -115,
    -115,  -115
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    42,   110,   104,   106,   108,     0,
      41,     0,    34,    36,    38,    39,    40,    37,    54,     0,
      57,    59,     0,    61,   115,    53,     0,    44,    46,    47,
      51,    52,    49,    48,    50,    26,     0,     0,    19,     0,
       0,     0,     0,     0,     0,    31,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     9,    30,    23,     0,
       0,     0,     0,     0,     0,    35,     0,    56,     0,     0,
      78,     0,     0,    45,     0,     0,     0,   105,   107,   109,
      55,    20,    58,    60,     0,    63,     0,    24,     0,     0,
     112,   114,    86,    88,    90,    85,     0,    80,    82,    83,
      84,    67,     0,    64,    65,   119,     0,   117,    43,     0,
     111,     0,     0,     0,     0,    79,     0,    62,     0,     0,
       0,   116,   113,     0,     0,     0,    81,    74,    76,    71,
       0,    69,    72,    73,    66,   130,   135,     0,   133,   129,
     127,   128,     0,   121,   123,   125,   126,   124,   118,     0,
       0,     0,     0,     0,     0,    68,     0,     0,     0,     0,
       0,   120,    99,   101,    98,    96,    97,     0,    92,    94,
      95,     0,     0,     0,     0,    70,     0,     0,   132,     0,
     122,     0,     0,     0,    87,    89,    91,    75,    77,   131,
       0,   134,     0,     0,    93,   139,     0,   137,   100,   103,
     102,     0,     0,   136,   148,     0,     0,     0,   153,     0,
     141,   143,   144,   145,   146,   147,   138,     0,     0,     0,
       0,     0,     0,   140,     0,   150,   151,   152,     0,   142,
     149,   154
  };

  const signed char
  AgentParser::yypgoto_[] =
  {
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,   -24,    40,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,   -23,  -115,
    -115,  -115,    80,  -115,  -115,    69,    91,  -115,  -115,  -115,
     -22,  -115,   -21,  -115,  -115,  -115,  -115,  -115,    27,  -115,
    -115,    -7,  -115,  -115,  -115,  -115,  -115,  -115,  -115,    34,
    -115,  -115,  -115,  -115,  -115,  -115,  -114,   -31,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,    45,  -105,  -115,  -115,    33,  -115,  -115,    -4,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,   -47,  -115,
    -115,   -65,  -115,  -115,  -115,  -115,  -115,  -115,  -115
  };

  const short
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,   112,    32,    33,    19,    24,    29,    30,   194,    21,
      26,    41,    42,    43,    70,    56,    57,    58,    78,    59,
     195,    80,   196,    81,    62,    83,   132,   133,   134,   146,
     160,   161,   162,   182,   163,   183,    63,   114,   126,   127,
     128,   141,   129,   142,   130,   143,   197,   198,   199,   211,
     200,   212,   230,    44,    72,    45,    73,    46,    74,    47,
      71,   119,   120,    64,    84,   136,   137,   149,   172,   173,
     174,   186,   175,   176,   189,   177,   187,   226,   227,   231,
     239,   240,   241,   247,   242,   243,   244,   245,   251
  };

  const unsigned short
  AgentParser::yytable_[] =
  {
      28,   121,    20,    40,    55,    60,    61,     9,     8,    10,
      22,    11,    50,    51,   122,   123,   124,   150,   192,   193,
     151,    65,    34,    31,    48,    49,    50,    51,    52,   157,
     158,    76,   157,   158,   121,    53,    77,    35,    66,    54,
      39,    39,    87,    88,    12,    13,    14,    15,    36,    37,
      38,    39,    67,    40,    39,    39,    85,    50,    51,    68,
      85,    86,    55,    60,    61,   138,   201,   202,   107,   108,
     109,   165,   166,   139,   167,   168,   144,    69,   140,    75,
     117,   145,    55,    60,    61,   184,    39,    79,    82,   234,
     185,   125,   235,   236,   237,   238,   190,   213,   213,   213,
     252,   191,   214,   215,   216,   253,   232,    89,    90,   233,
       1,     2,     3,    91,    92,    93,    94,    96,    98,    97,
      99,   125,   100,   159,   101,   102,   169,   170,   171,   104,
     105,   106,   110,    10,   113,   115,   116,   148,   111,   131,
     135,   147,   153,    54,   154,   155,   179,   217,   188,   180,
     181,   203,   204,   206,   207,   209,    95,   220,   222,   223,
     225,   208,   248,   249,   219,   250,   229,   169,   170,   171,
     221,   228,   254,   258,   118,   164,   103,   205,   156,   260,
     218,   255,   224,   178,   152,   246,   210,   259,     0,   256,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   257,
       0,     0,   261
  };

  const short
  AgentParser::yycheck_[] =
  {
      24,   106,     7,    26,    27,    27,    27,     5,     0,     7,
       7,     9,    13,    14,    16,    17,    18,     3,    19,    20,
       6,     6,    10,    42,    11,    12,    13,    14,    15,    23,
      24,     3,    23,    24,   139,    22,     8,    25,     3,    26,
      42,    42,    66,    67,    42,    43,    44,    45,    36,    37,
      38,    42,     4,    76,    42,    42,     3,    13,    14,     8,
       3,     8,    85,    85,    85,     8,   180,   181,    92,    93,
      94,    27,    28,     3,    30,    31,     3,     3,     8,     4,
     104,     8,   105,   105,   105,     3,    42,     4,     4,    29,
       8,   114,    32,    33,    34,    35,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,     3,    42,     4,     6,
      39,    40,    41,     4,     4,     4,     4,     4,     4,    43,
       4,   144,     7,   146,     4,     4,   149,   149,   149,     4,
       7,     7,    42,     7,    42,     5,     5,     3,    98,     7,
       7,     6,     4,    26,     4,     4,     7,    42,     4,     7,
       7,     4,     4,     4,     4,     4,    76,     5,     4,     4,
       7,    43,     4,     4,    42,     4,    21,   190,   190,   190,
      42,    42,     4,     4,   105,   148,    85,   184,   144,    42,
     204,    45,   213,   150,   139,   232,   190,   252,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    42
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    39,    40,    41,    47,    48,    49,    50,     0,     5,
       7,     9,    42,    43,    44,    45,    53,    54,    55,    60,
       7,    65,     7,    51,    61,    56,    66,    52,    54,    62,
      63,    42,    58,    59,    10,    25,    36,    37,    38,    42,
      64,    67,    68,    69,   109,   111,   113,   115,    11,    12,
      13,    14,    15,    22,    26,    64,    71,    72,    73,    75,
      76,    78,    80,    92,   119,     6,     3,     4,     8,     3,
      70,   116,   110,   112,   114,     4,     3,     8,    74,     4,
      77,    79,     4,    81,   120,     3,     8,    54,    54,    42,
       4,     4,     4,     4,     4,    68,     4,    43,     4,     4,
       7,     4,     4,    72,     4,     7,     7,    54,    54,    54,
      42,    55,    57,    42,    93,     5,     5,    54,    71,   117,
     118,   119,    16,    17,    18,    64,    94,    95,    96,    98,
     100,     7,    82,    83,    84,     7,   121,   122,     8,     3,
       8,    97,    99,   101,     3,     8,    85,     6,     3,   123,
       3,     6,   118,     4,     4,     4,    95,    23,    24,    64,
      86,    87,    88,    90,    84,    27,    28,    30,    31,    64,
      76,    78,   124,   125,   126,   128,   129,   131,   122,     7,
       7,     7,    89,    91,     3,     8,   127,   132,     4,   130,
       3,     8,    19,    20,    64,    76,    78,   102,   103,   104,
     106,   102,   102,     4,     4,    87,     4,     4,    43,     4,
     125,   105,   107,     3,     8,     8,     8,    42,    54,    42,
       5,    42,     4,     4,   103,     7,   133,   134,    42,    21,
     108,   135,     3,     6,    29,    32,    33,    34,    35,   136,
     137,   138,   140,   141,   142,   143,   134,   139,     4,     4,
       4,   144,     3,     8,     4,    45,    43,    43,     4,   137,
      42,    42
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    46,    48,    47,    49,    47,    50,    47,    52,    51,
      53,    54,    54,    54,    54,    54,    54,    54,    56,    55,
      57,    58,    58,    59,    59,    61,    60,    62,    62,    63,
      63,    64,    66,    65,    67,    67,    68,    68,    68,    68,
      68,    68,    70,    69,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    74,    73,    75,    77,    76,    79,
      78,    81,    80,    82,    82,    83,    83,    85,    84,    86,
      86,    86,    87,    87,    89,    88,    91,    90,    93,    92,
      94,    94,    95,    95,    95,    95,    97,    96,    99,    98,
     101,   100,   102,   102,   103,   103,   103,   103,   103,   105,
     104,   107,   106,   108,   110,   109,   112,   111,   114,   113,
     116,   115,   117,   117,   118,   120,   119,   121,   121,   123,
     122,   124,   124,   125,   125,   125,   125,   125,   125,   125,
     127,   126,   128,   130,   129,   132,   131,   133,   133,   135,
     134,   136,   136,   137,   137,   137,   137,   137,   139,   138,
     140,   141,   142,   144,   143
  };

  const unsigned char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const AgentParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Control-agent\"",
  "\"http-host\"", "\"http-port\"", "\"user-context\"", "\"comment\"",
  "\"control-sockets\"", "\"dhcp4\"", "\"dhcp6\"", "\"d2\"",
  "\"socket-name\"", "\"socket-type\"", "\"unix\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"Logging\"", "\"loggers\"",
  "\"name\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp4\"", "\"Dhcp6\"", "\"DhcpDdns\"", "START_JSON", "START_AGENT",
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
  "socket_type", "$@21", "socket_type_value", "dhcp4_json_object", "$@22",
  "dhcp6_json_object", "$@23", "dhcpddns_json_object", "$@24",
  "logging_object", "$@25", "logging_params", "logging_param", "loggers",
  "$@26", "loggers_entries", "logger_entry", "$@27", "logger_params",
  "logger_param", "name", "$@28", "debuglevel", "severity", "$@29",
  "output_options_list", "$@30", "output_options_list_content",
  "output_entry", "$@31", "output_params_list", "output_params", "output",
  "$@32", "flush", "maxsize", "maxver", "pattern", "$@33", YY_NULLPTR
  };

#if AGENT_DEBUG
  const unsigned short
  AgentParser::yyrline_[] =
  {
       0,   115,   115,   115,   116,   116,   117,   117,   125,   125,
     136,   142,   143,   144,   145,   146,   147,   148,   152,   152,
     163,   168,   169,   177,   181,   188,   188,   194,   195,   198,
     202,   215,   224,   224,   236,   237,   241,   242,   243,   244,
     245,   246,   250,   250,   267,   268,   273,   274,   275,   276,
     277,   278,   279,   280,   283,   283,   291,   296,   296,   321,
     321,   349,   349,   359,   360,   363,   364,   367,   367,   375,
     376,   377,   380,   381,   384,   384,   392,   392,   402,   402,
     415,   416,   421,   422,   423,   424,   428,   428,   439,   439,
     450,   450,   461,   462,   466,   467,   468,   469,   470,   474,
     474,   483,   483,   491,   497,   497,   504,   504,   511,   511,
     523,   523,   536,   537,   541,   545,   545,   557,   558,   562,
     562,   570,   571,   574,   575,   576,   577,   578,   579,   580,
     583,   583,   591,   596,   596,   604,   604,   614,   615,   618,
     618,   626,   627,   630,   631,   632,   633,   634,   637,   637,
     645,   650,   655,   660,   660
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
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  AgentParser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
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
#line 2049 "agent_parser.cc"

#line 668 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
