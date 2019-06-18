// A Bison parser, made by GNU Bison 3.4.1.

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
#line 146 "agent_parser.cc"


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
      case 53: // value
      case 56: // map_value
      case 107: // socket_type_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 44: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 43: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 42: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 41: // "constant string"
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
      case 53: // value
      case 56: // map_value
      case 107: // socket_type_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 44: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 43: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 42: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 41: // "constant string"
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
      case 53: // value
      case 56: // map_value
      case 107: // socket_type_value
        value.move< ElementPtr > (that.value);
        break;

      case 44: // "boolean"
        value.move< bool > (that.value);
        break;

      case 43: // "floating point"
        value.move< double > (that.value);
        break;

      case 42: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 41: // "constant string"
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
      case 41: // "constant string"
#line 103 "agent_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 393 "agent_parser.cc"
        break;

      case 42: // "integer"
#line 103 "agent_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 399 "agent_parser.cc"
        break;

      case 43: // "floating point"
#line 103 "agent_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 405 "agent_parser.cc"
        break;

      case 44: // "boolean"
#line 103 "agent_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 411 "agent_parser.cc"
        break;

      case 53: // value
#line 103 "agent_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 417 "agent_parser.cc"
        break;

      case 56: // map_value
#line 103 "agent_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 423 "agent_parser.cc"
        break;

      case 107: // socket_type_value
#line 103 "agent_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "agent_parser.cc"
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
      case 53: // value
      case 56: // map_value
      case 107: // socket_type_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 44: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 43: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 42: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 41: // "constant string"
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
#line 114 "agent_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 691 "agent_parser.cc"
    break;

  case 4:
#line 115 "agent_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 697 "agent_parser.cc"
    break;

  case 6:
#line 116 "agent_parser.yy"
    { ctx.ctx_ = ctx.AGENT; }
#line 703 "agent_parser.cc"
    break;

  case 8:
#line 124 "agent_parser.yy"
    {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 713 "agent_parser.cc"
    break;

  case 9:
#line 128 "agent_parser.yy"
    {
    // parsing completed
}
#line 721 "agent_parser.cc"
    break;

  case 10:
#line 135 "agent_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 730 "agent_parser.cc"
    break;

  case 11:
#line 141 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 736 "agent_parser.cc"
    break;

  case 12:
#line 142 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "agent_parser.cc"
    break;

  case 13:
#line 143 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "agent_parser.cc"
    break;

  case 14:
#line 144 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "agent_parser.cc"
    break;

  case 15:
#line 145 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 760 "agent_parser.cc"
    break;

  case 16:
#line 146 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 766 "agent_parser.cc"
    break;

  case 17:
#line 147 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "agent_parser.cc"
    break;

  case 18:
#line 151 "agent_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 783 "agent_parser.cc"
    break;

  case 19:
#line 156 "agent_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 793 "agent_parser.cc"
    break;

  case 20:
#line 162 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 799 "agent_parser.cc"
    break;

  case 23:
#line 176 "agent_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 808 "agent_parser.cc"
    break;

  case 24:
#line 180 "agent_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 818 "agent_parser.cc"
    break;

  case 25:
#line 187 "agent_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 827 "agent_parser.cc"
    break;

  case 26:
#line 190 "agent_parser.yy"
    {
}
#line 834 "agent_parser.cc"
    break;

  case 29:
#line 197 "agent_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 843 "agent_parser.cc"
    break;

  case 30:
#line 201 "agent_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 852 "agent_parser.cc"
    break;

  case 31:
#line 214 "agent_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 863 "agent_parser.cc"
    break;

  case 32:
#line 223 "agent_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 874 "agent_parser.cc"
    break;

  case 33:
#line 228 "agent_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 884 "agent_parser.cc"
    break;

  case 42:
#line 249 "agent_parser.yy"
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
#line 900 "agent_parser.cc"
    break;

  case 43:
#line 259 "agent_parser.yy"
    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 911 "agent_parser.cc"
    break;

  case 54:
#line 282 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 919 "agent_parser.cc"
    break;

  case 55:
#line 284 "agent_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 929 "agent_parser.cc"
    break;

  case 56:
#line 290 "agent_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 938 "agent_parser.cc"
    break;

  case 57:
#line 295 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 946 "agent_parser.cc"
    break;

  case 58:
#line 297 "agent_parser.yy"
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
#line 973 "agent_parser.cc"
    break;

  case 59:
#line 320 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 981 "agent_parser.cc"
    break;

  case 60:
#line 322 "agent_parser.yy"
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
#line 1010 "agent_parser.cc"
    break;

  case 61:
#line 348 "agent_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1021 "agent_parser.cc"
    break;

  case 62:
#line 353 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1030 "agent_parser.cc"
    break;

  case 67:
#line 366 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1040 "agent_parser.cc"
    break;

  case 68:
#line 370 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1048 "agent_parser.cc"
    break;

  case 74:
#line 383 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1056 "agent_parser.cc"
    break;

  case 75:
#line 385 "agent_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1066 "agent_parser.cc"
    break;

  case 76:
#line 391 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1074 "agent_parser.cc"
    break;

  case 77:
#line 393 "agent_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1083 "agent_parser.cc"
    break;

  case 78:
#line 401 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1094 "agent_parser.cc"
    break;

  case 79:
#line 406 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1103 "agent_parser.cc"
    break;

  case 86:
#line 427 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1114 "agent_parser.cc"
    break;

  case 87:
#line 432 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1123 "agent_parser.cc"
    break;

  case 88:
#line 438 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1134 "agent_parser.cc"
    break;

  case 89:
#line 443 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1143 "agent_parser.cc"
    break;

  case 90:
#line 449 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1154 "agent_parser.cc"
    break;

  case 91:
#line 454 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1163 "agent_parser.cc"
    break;

  case 99:
#line 473 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1171 "agent_parser.cc"
    break;

  case 100:
#line 475 "agent_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1181 "agent_parser.cc"
    break;

  case 101:
#line 482 "agent_parser.yy"
    {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1189 "agent_parser.cc"
    break;

  case 102:
#line 484 "agent_parser.yy"
    {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1198 "agent_parser.cc"
    break;

  case 103:
#line 490 "agent_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1204 "agent_parser.cc"
    break;

  case 104:
#line 496 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1212 "agent_parser.cc"
    break;

  case 105:
#line 498 "agent_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1221 "agent_parser.cc"
    break;

  case 106:
#line 503 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1229 "agent_parser.cc"
    break;

  case 107:
#line 505 "agent_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1238 "agent_parser.cc"
    break;

  case 108:
#line 510 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1246 "agent_parser.cc"
    break;

  case 109:
#line 512 "agent_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1255 "agent_parser.cc"
    break;

  case 110:
#line 522 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1266 "agent_parser.cc"
    break;

  case 111:
#line 527 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1275 "agent_parser.cc"
    break;

  case 115:
#line 544 "agent_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1286 "agent_parser.cc"
    break;

  case 116:
#line 549 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1295 "agent_parser.cc"
    break;

  case 119:
#line 561 "agent_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1305 "agent_parser.cc"
    break;

  case 120:
#line 565 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1313 "agent_parser.cc"
    break;

  case 130:
#line 582 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1321 "agent_parser.cc"
    break;

  case 131:
#line 584 "agent_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1331 "agent_parser.cc"
    break;

  case 132:
#line 590 "agent_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1340 "agent_parser.cc"
    break;

  case 133:
#line 595 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1348 "agent_parser.cc"
    break;

  case 134:
#line 597 "agent_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1358 "agent_parser.cc"
    break;

  case 135:
#line 603 "agent_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1369 "agent_parser.cc"
    break;

  case 136:
#line 608 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1378 "agent_parser.cc"
    break;

  case 139:
#line 617 "agent_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1388 "agent_parser.cc"
    break;

  case 140:
#line 621 "agent_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1396 "agent_parser.cc"
    break;

  case 147:
#line 635 "agent_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1404 "agent_parser.cc"
    break;

  case 148:
#line 637 "agent_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1414 "agent_parser.cc"
    break;

  case 149:
#line 643 "agent_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1423 "agent_parser.cc"
    break;

  case 150:
#line 648 "agent_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1432 "agent_parser.cc"
    break;

  case 151:
#line 653 "agent_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1441 "agent_parser.cc"
    break;


#line 1445 "agent_parser.cc"

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


  const short AgentParser::yypact_ninf_ = -133;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      71,  -133,  -133,  -133,     7,     3,     2,     4,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,     3,   -28,    -8,     9,  -133,    20,
      29,    54,    49,    76,  -133,  -133,  -133,  -133,  -133,    95,
    -133,    22,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   101,
    -133,  -133,   103,  -133,  -133,  -133,    69,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,     3,     3,  -133,    63,
     104,   108,   109,   110,   111,  -133,    -8,  -133,   112,    75,
     114,   115,   113,   118,   120,     9,  -133,  -133,  -133,   121,
     122,   123,     3,     3,     3,  -133,    91,  -133,   124,    96,
    -133,   128,   129,  -133,     3,     9,   116,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,    -2,   131,   132,  -133,    70,    78,
    -133,  -133,  -133,  -133,  -133,  -133,    82,  -133,  -133,  -133,
    -133,  -133,   130,   137,  -133,  -133,    53,  -133,  -133,   116,
    -133,   139,   140,   141,    -2,  -133,    -5,  -133,   131,    24,
     132,  -133,  -133,   134,   142,   143,  -133,  -133,  -133,  -133,
      84,  -133,  -133,  -133,  -133,  -133,  -133,   144,  -133,  -133,
    -133,  -133,    86,  -133,  -133,  -133,  -133,  -133,  -133,    47,
      47,    47,   147,   148,    17,  -133,   149,   150,   105,   151,
      24,  -133,  -133,  -133,  -133,  -133,  -133,    90,  -133,  -133,
    -133,    92,    93,   117,     3,  -133,   119,   152,  -133,   125,
    -133,   155,   157,    47,  -133,  -133,  -133,  -133,  -133,  -133,
     156,  -133,   133,   135,  -133,  -133,   100,  -133,  -133,  -133,
    -133,    42,   156,  -133,  -133,   158,   160,   161,    94,  -133,
    -133,  -133,  -133,  -133,  -133,   166,   102,   136,   145,    42,
    -133,   138,  -133,  -133,  -133,  -133,  -133
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
     102,     0,     0,   136,   147,     0,     0,     0,     0,   141,
     143,   144,   145,   146,   138,     0,     0,     0,     0,     0,
     140,     0,   149,   150,   151,   142,   148
  };

  const short
  AgentParser::yypgoto_[] =
  {
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -24,    37,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -23,  -133,
    -133,  -133,    97,  -133,  -133,    66,    87,  -133,  -133,  -133,
     -22,  -133,   -21,  -133,  -133,  -133,  -133,  -133,    27,  -133,
    -133,    -7,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    32,
    -133,  -133,  -133,  -133,  -133,  -133,  -132,   -32,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,    43,  -105,  -133,  -133,    33,  -133,  -133,    -6,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -47,  -133,
    -133,   -63,  -133,  -133,  -133,  -133,  -133
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
     238,   239,   240,   245,   241,   242,   243
  };

  const unsigned short
  AgentParser::yytable_[] =
  {
      28,   121,    34,    40,    55,    60,    61,     8,     9,    20,
      10,    22,    11,    31,   122,   123,   124,    35,   157,   158,
      48,    49,    50,    51,    52,    76,    65,    36,    37,    38,
      77,    53,    66,    39,   121,    54,    39,    50,    51,    39,
     157,   158,    87,    88,    12,    13,    14,    15,   201,   202,
      39,   165,   166,    40,   167,   168,   150,    68,    67,   151,
      50,    51,    55,    60,    61,    39,   192,   193,   107,   108,
     109,   234,    85,    85,   235,   236,   237,    86,   138,    69,
     117,   139,    55,    60,    61,   144,   140,   184,    39,   190,
     145,   125,   185,   213,   191,   213,   213,   249,   214,    75,
     215,   216,   250,   232,    89,    79,   233,    82,    90,     1,
       2,     3,    91,    92,    93,    94,    96,    97,    98,    99,
     100,   125,   101,   159,   102,   104,   169,   170,   171,   105,
     106,    10,   110,   115,   116,   111,   147,   113,   131,   135,
     148,   179,    54,   153,   154,   155,   252,   208,   188,   180,
     181,   203,   204,   206,   207,   209,   229,   220,   217,   222,
     219,   223,   246,   225,   247,   248,   221,   169,   170,   171,
     251,   118,   103,    95,   228,   164,   156,   205,   253,   256,
     218,   224,   152,   178,   210,   244,   255,   254
  };

  const unsigned char
  AgentParser::yycheck_[] =
  {
      24,   106,    10,    26,    27,    27,    27,     0,     5,     7,
       7,     7,     9,    41,    16,    17,    18,    25,    23,    24,
      11,    12,    13,    14,    15,     3,     6,    35,    36,    37,
       8,    22,     3,    41,   139,    26,    41,    13,    14,    41,
      23,    24,    66,    67,    41,    42,    43,    44,   180,   181,
      41,    27,    28,    76,    30,    31,     3,     8,     4,     6,
      13,    14,    85,    85,    85,    41,    19,    20,    92,    93,
      94,    29,     3,     3,    32,    33,    34,     8,     8,     3,
     104,     3,   105,   105,   105,     3,     8,     3,    41,     3,
       8,   114,     8,     3,     8,     3,     3,     3,     8,     4,
       8,     8,     8,     3,    41,     4,     6,     4,     4,    38,
      39,    40,     4,     4,     4,     4,     4,    42,     4,     4,
       7,   144,     4,   146,     4,     4,   149,   149,   149,     7,
       7,     7,    41,     5,     5,    98,     6,    41,     7,     7,
       3,     7,    26,     4,     4,     4,    44,    42,     4,     7,
       7,     4,     4,     4,     4,     4,    21,     5,    41,     4,
      41,     4,     4,     7,     4,     4,    41,   190,   190,   190,
       4,   105,    85,    76,    41,   148,   144,   184,    42,    41,
     204,   213,   139,   150,   190,   232,   249,    42
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    38,    39,    40,    46,    47,    48,    49,     0,     5,
       7,     9,    41,    42,    43,    44,    52,    53,    54,    59,
       7,    64,     7,    50,    60,    55,    65,    51,    53,    61,
      62,    41,    57,    58,    10,    25,    35,    36,    37,    41,
      63,    66,    67,    68,   108,   110,   112,   114,    11,    12,
      13,    14,    15,    22,    26,    63,    70,    71,    72,    74,
      75,    77,    79,    91,   118,     6,     3,     4,     8,     3,
      69,   115,   109,   111,   113,     4,     3,     8,    73,     4,
      76,    78,     4,    80,   119,     3,     8,    53,    53,    41,
       4,     4,     4,     4,     4,    67,     4,    42,     4,     4,
       7,     4,     4,    71,     4,     7,     7,    53,    53,    53,
      41,    54,    56,    41,    92,     5,     5,    53,    70,   116,
     117,   118,    16,    17,    18,    63,    93,    94,    95,    97,
      99,     7,    81,    82,    83,     7,   120,   121,     8,     3,
       8,    96,    98,   100,     3,     8,    84,     6,     3,   122,
       3,     6,   117,     4,     4,     4,    94,    23,    24,    63,
      85,    86,    87,    89,    83,    27,    28,    30,    31,    63,
      75,    77,   123,   124,   125,   127,   128,   130,   121,     7,
       7,     7,    88,    90,     3,     8,   126,   131,     4,   129,
       3,     8,    19,    20,    63,    75,    77,   101,   102,   103,
     105,   101,   101,     4,     4,    86,     4,     4,    42,     4,
     124,   104,   106,     3,     8,     8,     8,    41,    53,    41,
       5,    41,     4,     4,   102,     7,   132,   133,    41,    21,
     107,   134,     3,     6,    29,    32,    33,    34,   135,   136,
     137,   139,   140,   141,   133,   138,     4,     4,     4,     3,
       8,     4,    44,    42,    42,   136,    41
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    45,    47,    46,    48,    46,    49,    46,    51,    50,
      52,    53,    53,    53,    53,    53,    53,    53,    55,    54,
      56,    57,    57,    58,    58,    60,    59,    61,    61,    62,
      62,    63,    65,    64,    66,    66,    67,    67,    67,    67,
      67,    67,    69,    68,    70,    70,    71,    71,    71,    71,
      71,    71,    71,    71,    73,    72,    74,    76,    75,    78,
      77,    80,    79,    81,    81,    82,    82,    84,    83,    85,
      85,    85,    86,    86,    88,    87,    90,    89,    92,    91,
      93,    93,    94,    94,    94,    94,    96,    95,    98,    97,
     100,    99,   101,   101,   102,   102,   102,   102,   102,   104,
     103,   106,   105,   107,   109,   108,   111,   110,   113,   112,
     115,   114,   116,   116,   117,   119,   118,   120,   120,   122,
     121,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     126,   125,   127,   129,   128,   131,   130,   132,   132,   134,
     133,   135,   135,   136,   136,   136,   136,   138,   137,   139,
     140,   141
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
       4,     1,     3,     1,     1,     1,     1,     0,     4,     3,
       3,     3
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
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "START_JSON", "START_AGENT",
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
  "$@32", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if AGENT_DEBUG
  const unsigned short
  AgentParser::yyrline_[] =
  {
       0,   114,   114,   114,   115,   115,   116,   116,   124,   124,
     135,   141,   142,   143,   144,   145,   146,   147,   151,   151,
     162,   167,   168,   176,   180,   187,   187,   193,   194,   197,
     201,   214,   223,   223,   235,   236,   240,   241,   242,   243,
     244,   245,   249,   249,   266,   267,   272,   273,   274,   275,
     276,   277,   278,   279,   282,   282,   290,   295,   295,   320,
     320,   348,   348,   358,   359,   362,   363,   366,   366,   374,
     375,   376,   379,   380,   383,   383,   391,   391,   401,   401,
     414,   415,   420,   421,   422,   423,   427,   427,   438,   438,
     449,   449,   460,   461,   465,   466,   467,   468,   469,   473,
     473,   482,   482,   490,   496,   496,   503,   503,   510,   510,
     522,   522,   535,   536,   540,   544,   544,   556,   557,   561,
     561,   569,   570,   573,   574,   575,   576,   577,   578,   579,
     582,   582,   590,   595,   595,   603,   603,   613,   614,   617,
     617,   625,   626,   629,   630,   631,   632,   635,   635,   643,
     648,   653
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
#line 2027 "agent_parser.cc"

#line 658 "agent_parser.yy"


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
