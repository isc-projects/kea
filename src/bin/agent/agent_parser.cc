// A Bison parser, made by GNU Bison 3.3.2.

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
#line 33 "agent_parser.yy" // lalr1.cc:435

#include <agent/parser_context.h>

#line 51 "agent_parser.cc" // lalr1.cc:435


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

#line 14 "agent_parser.yy" // lalr1.cc:510
namespace isc { namespace agent {
#line 146 "agent_parser.cc" // lalr1.cc:510

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
#line 103 "agent_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 392 "agent_parser.cc" // lalr1.cc:676
        break;

      case 42: // "integer"
#line 103 "agent_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 398 "agent_parser.cc" // lalr1.cc:676
        break;

      case 43: // "floating point"
#line 103 "agent_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 404 "agent_parser.cc" // lalr1.cc:676
        break;

      case 44: // "boolean"
#line 103 "agent_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 410 "agent_parser.cc" // lalr1.cc:676
        break;

      case 53: // value
#line 103 "agent_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 416 "agent_parser.cc" // lalr1.cc:676
        break;

      case 56: // map_value
#line 103 "agent_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 422 "agent_parser.cc" // lalr1.cc:676
        break;

      case 107: // socket_type_value
#line 103 "agent_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "agent_parser.cc" // lalr1.cc:676
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
#line 114 "agent_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 690 "agent_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 115 "agent_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "agent_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 116 "agent_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.AGENT; }
#line 702 "agent_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 124 "agent_parser.yy" // lalr1.cc:919
    {
    // Parse the Control-agent map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 712 "agent_parser.cc" // lalr1.cc:919
    break;

  case 9:
#line 128 "agent_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 720 "agent_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 135 "agent_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 729 "agent_parser.cc" // lalr1.cc:919
    break;

  case 11:
#line 141 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 735 "agent_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 142 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 741 "agent_parser.cc" // lalr1.cc:919
    break;

  case 13:
#line 143 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 747 "agent_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 144 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 753 "agent_parser.cc" // lalr1.cc:919
    break;

  case 15:
#line 145 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 759 "agent_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 146 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 765 "agent_parser.cc" // lalr1.cc:919
    break;

  case 17:
#line 147 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 771 "agent_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 151 "agent_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 782 "agent_parser.cc" // lalr1.cc:919
    break;

  case 19:
#line 156 "agent_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 792 "agent_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 162 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "agent_parser.cc" // lalr1.cc:919
    break;

  case 23:
#line 176 "agent_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 807 "agent_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 180 "agent_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 817 "agent_parser.cc" // lalr1.cc:919
    break;

  case 25:
#line 187 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 826 "agent_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 190 "agent_parser.yy" // lalr1.cc:919
    {
}
#line 833 "agent_parser.cc" // lalr1.cc:919
    break;

  case 29:
#line 197 "agent_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 842 "agent_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 201 "agent_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 851 "agent_parser.cc" // lalr1.cc:919
    break;

  case 31:
#line 214 "agent_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 862 "agent_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 223 "agent_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 873 "agent_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 228 "agent_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 883 "agent_parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 249 "agent_parser.yy" // lalr1.cc:919
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
#line 899 "agent_parser.cc" // lalr1.cc:919
    break;

  case 43:
#line 259 "agent_parser.yy" // lalr1.cc:919
    {
    // Ok, we're done with parsing control-agent. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 910 "agent_parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 281 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 918 "agent_parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 283 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-host", host);
    ctx.leave();
}
#line 928 "agent_parser.cc" // lalr1.cc:919
    break;

  case 55:
#line 289 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-port", prf);
}
#line 937 "agent_parser.cc" // lalr1.cc:919
    break;

  case 56:
#line 294 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 945 "agent_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 296 "agent_parser.yy" // lalr1.cc:919
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
#line 972 "agent_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 319 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 980 "agent_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 321 "agent_parser.yy" // lalr1.cc:919
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
#line 1009 "agent_parser.cc" // lalr1.cc:919
    break;

  case 60:
#line 347 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1020 "agent_parser.cc" // lalr1.cc:919
    break;

  case 61:
#line 352 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1029 "agent_parser.cc" // lalr1.cc:919
    break;

  case 66:
#line 365 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1039 "agent_parser.cc" // lalr1.cc:919
    break;

  case 67:
#line 369 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 1047 "agent_parser.cc" // lalr1.cc:919
    break;

  case 73:
#line 382 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1055 "agent_parser.cc" // lalr1.cc:919
    break;

  case 74:
#line 384 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1065 "agent_parser.cc" // lalr1.cc:919
    break;

  case 75:
#line 390 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1073 "agent_parser.cc" // lalr1.cc:919
    break;

  case 76:
#line 392 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1082 "agent_parser.cc" // lalr1.cc:919
    break;

  case 77:
#line 400 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("control-sockets", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 1093 "agent_parser.cc" // lalr1.cc:919
    break;

  case 78:
#line 405 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "agent_parser.cc" // lalr1.cc:919
    break;

  case 85:
#line 426 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1113 "agent_parser.cc" // lalr1.cc:919
    break;

  case 86:
#line 431 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1122 "agent_parser.cc" // lalr1.cc:919
    break;

  case 87:
#line 437 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1133 "agent_parser.cc" // lalr1.cc:919
    break;

  case 88:
#line 442 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1142 "agent_parser.cc" // lalr1.cc:919
    break;

  case 89:
#line 448 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1153 "agent_parser.cc" // lalr1.cc:919
    break;

  case 90:
#line 453 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "agent_parser.cc" // lalr1.cc:919
    break;

  case 98:
#line 472 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1170 "agent_parser.cc" // lalr1.cc:919
    break;

  case 99:
#line 474 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1180 "agent_parser.cc" // lalr1.cc:919
    break;

  case 100:
#line 481 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1188 "agent_parser.cc" // lalr1.cc:919
    break;

  case 101:
#line 483 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1197 "agent_parser.cc" // lalr1.cc:919
    break;

  case 102:
#line 489 "agent_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1203 "agent_parser.cc" // lalr1.cc:919
    break;

  case 103:
#line 495 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1211 "agent_parser.cc" // lalr1.cc:919
    break;

  case 104:
#line 497 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1220 "agent_parser.cc" // lalr1.cc:919
    break;

  case 105:
#line 502 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1228 "agent_parser.cc" // lalr1.cc:919
    break;

  case 106:
#line 504 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1237 "agent_parser.cc" // lalr1.cc:919
    break;

  case 107:
#line 509 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1245 "agent_parser.cc" // lalr1.cc:919
    break;

  case 108:
#line 511 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1254 "agent_parser.cc" // lalr1.cc:919
    break;

  case 109:
#line 521 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1265 "agent_parser.cc" // lalr1.cc:919
    break;

  case 110:
#line 526 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1274 "agent_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 543 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1285 "agent_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 548 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1294 "agent_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 560 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1304 "agent_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 564 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 1312 "agent_parser.cc" // lalr1.cc:919
    break;

  case 129:
#line 581 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1320 "agent_parser.cc" // lalr1.cc:919
    break;

  case 130:
#line 583 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1330 "agent_parser.cc" // lalr1.cc:919
    break;

  case 131:
#line 589 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1339 "agent_parser.cc" // lalr1.cc:919
    break;

  case 132:
#line 594 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1347 "agent_parser.cc" // lalr1.cc:919
    break;

  case 133:
#line 596 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1357 "agent_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 602 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1368 "agent_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 607 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1377 "agent_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 616 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1387 "agent_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 620 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 1395 "agent_parser.cc" // lalr1.cc:919
    break;

  case 146:
#line 634 "agent_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1403 "agent_parser.cc" // lalr1.cc:919
    break;

  case 147:
#line 636 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1413 "agent_parser.cc" // lalr1.cc:919
    break;

  case 148:
#line 642 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1422 "agent_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 647 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1431 "agent_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 652 "agent_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1440 "agent_parser.cc" // lalr1.cc:919
    break;


#line 1444 "agent_parser.cc" // lalr1.cc:919
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


  const signed char AgentParser::yypact_ninf_ = -68;

  const signed char AgentParser::yytable_ninf_ = -1;

  const short
  AgentParser::yypact_[] =
  {
      59,   -68,   -68,   -68,     6,     8,     9,    34,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,     8,   -29,    -5,    -4,   -68,    41,
      51,    98,    85,   100,   -68,   -68,   -68,   -68,   -68,   101,
     -68,    11,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   102,
     -68,   -68,   103,   -68,   -68,    21,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,     8,     8,   -68,    63,   104,   105,
     106,   107,   109,   -68,    -5,   -68,   111,    74,   113,   114,
     112,   116,    -4,   -68,   -68,   -68,   117,   115,   118,     8,
       8,     8,   -68,    83,   -68,   119,    87,   -68,   122,   -68,
       8,    -4,    97,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
       5,   123,   -68,    64,   -68,    65,   -68,   -68,   -68,   -68,
     -68,   -68,    71,   -68,   -68,   -68,   -68,   -68,   125,   126,
     -68,   -68,   128,    97,   -68,   129,   130,   131,     5,   -68,
      37,   -68,   123,   132,   -68,   133,   134,   135,   -68,   -68,
     -68,   -68,    78,   -68,   -68,   -68,   -68,   136,    14,    14,
      14,   140,   141,    42,   -68,   -68,    32,   -68,   -68,   -68,
     -68,   -68,   -68,    79,   -68,   -68,   -68,    80,    82,    95,
       8,   -68,    12,   136,   -68,   142,   143,    14,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   144,   -68,   -68,   -68,   -68,
      86,   -68,   -68,   -68,   -68,   -68,   -68,   108,   138,   -68,
     146,   147,    96,   148,    12,   -68,   -68,   -68,   -68,   120,
     149,   -68,   121,   -68,   -68,   156,   -68,   -68,    89,   -68,
      30,   156,   -68,   -68,   151,   160,   161,    88,   -68,   -68,
     -68,   -68,   -68,   -68,   162,   124,   127,   137,    30,   -68,
     139,   -68,   -68,   -68,   -68,   -68
  };

  const unsigned char
  AgentParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    42,   109,   103,   105,   107,     0,
      41,     0,    34,    36,    38,    39,    40,    37,    53,     0,
      56,    58,     0,    60,    52,     0,    44,    46,    47,    50,
      51,    49,    48,    26,     0,     0,    19,     0,     0,     0,
       0,     0,     0,    31,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     9,    30,    23,     0,     0,     0,     0,
       0,     0,    35,     0,    55,     0,     0,    77,     0,    45,
       0,     0,     0,   104,   106,   108,    54,    20,    57,    59,
       0,    62,    24,     0,   114,     0,   111,   113,    85,    87,
      89,    84,     0,    79,    81,    82,    83,    66,     0,    63,
      64,    43,     0,     0,   110,     0,     0,     0,     0,    78,
       0,    61,     0,     0,   112,     0,     0,     0,    80,    73,
      75,    70,     0,    68,    71,    72,    65,     0,     0,     0,
       0,     0,     0,     0,    67,   118,     0,   116,    98,   100,
      97,    95,    96,     0,    91,    93,    94,     0,     0,     0,
       0,    69,     0,     0,   115,     0,     0,     0,    86,    88,
      90,    74,    76,   129,   134,     0,   132,   128,   126,   127,
       0,   120,   122,   124,   125,   123,   117,     0,     0,    92,
       0,     0,     0,     0,     0,   119,    99,   102,   101,     0,
       0,   131,     0,   121,   130,     0,   133,   138,     0,   136,
       0,     0,   135,   146,     0,     0,     0,     0,   140,   142,
     143,   144,   145,   137,     0,     0,     0,     0,     0,   139,
       0,   148,   149,   150,   141,   147
  };

  const signed char
  AgentParser::yypgoto_[] =
  {
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -20,    44,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -26,   -68,
     -68,   -68,    93,   -68,   -68,    52,    90,   -68,   -68,   -68,
     -25,   -68,   -24,   -68,   -68,   -68,   -68,   -68,    28,   -68,
     -68,    10,   -68,   -68,   -68,   -68,   -68,   -68,   -68,    33,
     -68,   -68,   -68,   -68,   -68,   -68,   -59,   -13,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,    43,   -68,   -68,   -68,    -8,   -68,   -68,   -37,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -53,   -68,
     -68,   -67,   -68,   -68,   -68,   -68,   -68
  };

  const short
  AgentParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,   108,    32,    33,    19,    24,    29,    30,   170,    21,
      26,    41,    42,    43,    68,    55,    56,    57,    76,    58,
     171,    78,   172,    79,    61,    81,   128,   129,   130,   140,
     152,   153,   154,   161,   155,   162,    62,   110,   122,   123,
     124,   135,   125,   136,   126,   137,   173,   174,   175,   185,
     176,   186,   218,    44,    70,    45,    71,    46,    72,    47,
      69,   115,   116,   117,   132,   166,   167,   182,   200,   201,
     202,   210,   203,   204,   213,   205,   211,   228,   229,   230,
     237,   238,   239,   244,   240,   241,   242
  };

  const unsigned char
  AgentParser::yytable_[] =
  {
      40,    54,    59,    60,    28,    34,     8,    48,    49,    50,
      51,    52,    31,     9,    74,    10,    20,    11,    53,    75,
      35,   118,   119,   120,    82,    50,    51,    50,    51,    83,
      36,    37,    38,   168,   169,   183,    39,    39,   184,   193,
     194,    22,   195,   196,    84,    85,    39,    63,    40,    12,
      13,    14,    15,    39,    64,    39,    54,    59,    60,   233,
     149,   150,   234,   235,   236,   149,   150,    82,   133,   103,
     104,   105,   131,   134,   138,    54,    59,    60,    39,   139,
     112,   163,   187,   187,   121,   187,   164,   188,   189,   214,
     190,   248,   231,    66,   215,   232,   249,     1,     2,     3,
     177,   178,    65,    67,    86,    73,    77,    80,    87,    88,
      89,    90,   121,    91,   151,    93,    94,    95,    96,    97,
      98,   100,   101,   114,   106,   102,    10,   111,   109,   142,
     127,   141,   143,   145,   146,   147,   191,   157,   221,   107,
     158,   159,   160,   165,   179,   180,   207,   208,   212,   216,
     219,   220,   222,   113,   225,   245,   197,   198,   199,   217,
     192,   224,   226,   227,   246,   247,   250,    92,   251,   252,
     156,   148,    99,   181,   209,   206,   144,   223,   243,   253,
     255,   254,     0,     0,     0,     0,     0,     0,   197,   198,
     199
  };

  const short
  AgentParser::yycheck_[] =
  {
      26,    27,    27,    27,    24,    10,     0,    11,    12,    13,
      14,    15,    41,     5,     3,     7,     7,     9,    22,     8,
      25,    16,    17,    18,     3,    13,    14,    13,    14,     8,
      35,    36,    37,    19,    20,     3,    41,    41,     6,    27,
      28,     7,    30,    31,    64,    65,    41,     6,    74,    41,
      42,    43,    44,    41,     3,    41,    82,    82,    82,    29,
      23,    24,    32,    33,    34,    23,    24,     3,     3,    89,
      90,    91,     8,     8,     3,   101,   101,   101,    41,     8,
     100,     3,     3,     3,   110,     3,     8,     8,     8,     3,
       8,     3,     3,     8,     8,     6,     8,    38,    39,    40,
     159,   160,     4,     3,    41,     4,     4,     4,     4,     4,
       4,     4,   138,     4,   140,     4,    42,     4,     4,     7,
       4,     4,     7,    26,    41,     7,     7,     5,    41,     3,
       7,     6,     4,     4,     4,     4,    41,     5,    42,    95,
       7,     7,     7,     7,     4,     4,     4,     4,     4,    41,
       4,     4,     4,   101,     5,     4,   182,   182,   182,    21,
     180,    41,    41,     7,     4,     4,     4,    74,    44,    42,
     142,   138,    82,   163,   187,   183,   133,   214,   231,    42,
      41,   248,    -1,    -1,    -1,    -1,    -1,    -1,   214,   214,
     214
  };

  const unsigned char
  AgentParser::yystos_[] =
  {
       0,    38,    39,    40,    46,    47,    48,    49,     0,     5,
       7,     9,    41,    42,    43,    44,    52,    53,    54,    59,
       7,    64,     7,    50,    60,    55,    65,    51,    53,    61,
      62,    41,    57,    58,    10,    25,    35,    36,    37,    41,
      63,    66,    67,    68,   108,   110,   112,   114,    11,    12,
      13,    14,    15,    22,    63,    70,    71,    72,    74,    75,
      77,    79,    91,     6,     3,     4,     8,     3,    69,   115,
     109,   111,   113,     4,     3,     8,    73,     4,    76,    78,
       4,    80,     3,     8,    53,    53,    41,     4,     4,     4,
       4,     4,    67,     4,    42,     4,     4,     7,     4,    71,
       4,     7,     7,    53,    53,    53,    41,    54,    56,    41,
      92,     5,    53,    70,    26,   116,   117,   118,    16,    17,
      18,    63,    93,    94,    95,    97,    99,     7,    81,    82,
      83,     8,   119,     3,     8,    96,    98,   100,     3,     8,
      84,     6,     3,     4,   117,     4,     4,     4,    94,    23,
      24,    63,    85,    86,    87,    89,    83,     5,     7,     7,
       7,    88,    90,     3,     8,     7,   120,   121,    19,    20,
      63,    75,    77,   101,   102,   103,   105,   101,   101,     4,
       4,    86,   122,     3,     6,   104,   106,     3,     8,     8,
       8,    41,    53,    27,    28,    30,    31,    63,    75,    77,
     123,   124,   125,   127,   128,   130,   121,     4,     4,   102,
     126,   131,     4,   129,     3,     8,    41,    21,   107,     4,
       4,    42,     4,   124,    41,     5,    41,     7,   132,   133,
     134,     3,     6,    29,    32,    33,    34,   135,   136,   137,
     139,   140,   141,   133,   138,     4,     4,     4,     3,     8,
       4,    44,    42,    42,   136,    41
  };

  const unsigned char
  AgentParser::yyr1_[] =
  {
       0,    45,    47,    46,    48,    46,    49,    46,    51,    50,
      52,    53,    53,    53,    53,    53,    53,    53,    55,    54,
      56,    57,    57,    58,    58,    60,    59,    61,    61,    62,
      62,    63,    65,    64,    66,    66,    67,    67,    67,    67,
      67,    67,    69,    68,    70,    70,    71,    71,    71,    71,
      71,    71,    71,    73,    72,    74,    76,    75,    78,    77,
      80,    79,    81,    81,    82,    82,    84,    83,    85,    85,
      85,    86,    86,    88,    87,    90,    89,    92,    91,    93,
      93,    94,    94,    94,    94,    96,    95,    98,    97,   100,
      99,   101,   101,   102,   102,   102,   102,   102,   104,   103,
     106,   105,   107,   109,   108,   111,   110,   113,   112,   115,
     114,   116,   116,   117,   119,   118,   120,   120,   122,   121,
     123,   123,   124,   124,   124,   124,   124,   124,   124,   126,
     125,   127,   129,   128,   131,   130,   132,   132,   134,   133,
     135,   135,   136,   136,   136,   136,   138,   137,   139,   140,
     141
  };

  const unsigned char
  AgentParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     0,     6,     0,     6,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
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
     276,   277,   278,   281,   281,   289,   294,   294,   319,   319,
     347,   347,   357,   358,   361,   362,   365,   365,   373,   374,
     375,   378,   379,   382,   382,   390,   390,   400,   400,   413,
     414,   419,   420,   421,   422,   426,   426,   437,   437,   448,
     448,   459,   460,   464,   465,   466,   467,   468,   472,   472,
     481,   481,   489,   495,   495,   502,   502,   509,   509,   521,
     521,   534,   535,   539,   543,   543,   555,   556,   560,   560,
     568,   569,   572,   573,   574,   575,   576,   577,   578,   581,
     581,   589,   594,   594,   602,   602,   612,   613,   616,   616,
     624,   625,   628,   629,   630,   631,   634,   634,   642,   647,
     652
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


#line 14 "agent_parser.yy" // lalr1.cc:1242
} } // isc::agent
#line 2027 "agent_parser.cc" // lalr1.cc:1242
#line 657 "agent_parser.yy" // lalr1.cc:1243


void
isc::agent::AgentParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
