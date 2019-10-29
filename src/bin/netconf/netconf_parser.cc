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
#define yylex   netconf_lex



#include "netconf_parser.h"


// Unqualified %code blocks.
#line 33 "netconf_parser.yy"

#include <netconf/parser_context.h>

#line 51 "netconf_parser.cc"


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
#if NETCONF_DEBUG

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

#else // !NETCONF_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !NETCONF_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "netconf_parser.yy"
namespace isc { namespace netconf {
#line 143 "netconf_parser.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  NetconfParser::yytnamerr_ (const char *yystr)
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
  NetconfParser::NetconfParser (isc::netconf::ParserContext& ctx_yyarg)
    :
#if NETCONF_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  NetconfParser::~NetconfParser ()
  {}

  NetconfParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  NetconfParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  NetconfParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  NetconfParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  NetconfParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  NetconfParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  NetconfParser::symbol_number_type
  NetconfParser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  NetconfParser::stack_symbol_type::stack_symbol_type ()
  {}

  NetconfParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 58: // value
      case 61: // map_value
      case 120: // socket_type_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 49: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 48: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 47: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 46: // "constant string"
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

  NetconfParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 58: // value
      case 61: // map_value
      case 120: // socket_type_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 49: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 48: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 47: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 46: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  NetconfParser::stack_symbol_type&
  NetconfParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 58: // value
      case 61: // map_value
      case 120: // socket_type_value
        value.move< ElementPtr > (that.value);
        break;

      case 49: // "boolean"
        value.move< bool > (that.value);
        break;

      case 48: // "floating point"
        value.move< double > (that.value);
        break;

      case 47: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 46: // "constant string"
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
  NetconfParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if NETCONF_DEBUG
  template <typename Base>
  void
  NetconfParser::yy_print_ (std::ostream& yyo,
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
      case 46: // "constant string"
#line 108 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 390 "netconf_parser.cc"
        break;

      case 47: // "integer"
#line 108 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 396 "netconf_parser.cc"
        break;

      case 48: // "floating point"
#line 108 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 402 "netconf_parser.cc"
        break;

      case 49: // "boolean"
#line 108 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 408 "netconf_parser.cc"
        break;

      case 58: // value
#line 108 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "netconf_parser.cc"
        break;

      case 61: // map_value
#line 108 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 420 "netconf_parser.cc"
        break;

      case 120: // socket_type_value
#line 108 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 426 "netconf_parser.cc"
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  NetconfParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  NetconfParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  NetconfParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if NETCONF_DEBUG
  std::ostream&
  NetconfParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  NetconfParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  NetconfParser::debug_level_type
  NetconfParser::debug_level () const
  {
    return yydebug_;
  }

  void
  NetconfParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // NETCONF_DEBUG

  NetconfParser::state_type
  NetconfParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  NetconfParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  NetconfParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  NetconfParser::operator() ()
  {
    return parse ();
  }

  int
  NetconfParser::parse ()
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
      case 58: // value
      case 61: // map_value
      case 120: // socket_type_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 49: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 48: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 47: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 46: // "constant string"
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
#line 119 "netconf_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 688 "netconf_parser.cc"
    break;

  case 4:
#line 120 "netconf_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 694 "netconf_parser.cc"
    break;

  case 6:
#line 121 "netconf_parser.yy"
    { ctx.ctx_ = ctx.NETCONF; }
#line 700 "netconf_parser.cc"
    break;

  case 8:
#line 129 "netconf_parser.yy"
    {
    // Parse the Netconf map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 710 "netconf_parser.cc"
    break;

  case 9:
#line 133 "netconf_parser.yy"
    {
    // parsing completed
}
#line 718 "netconf_parser.cc"
    break;

  case 10:
#line 140 "netconf_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 727 "netconf_parser.cc"
    break;

  case 11:
#line 146 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 733 "netconf_parser.cc"
    break;

  case 12:
#line 147 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 739 "netconf_parser.cc"
    break;

  case 13:
#line 148 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 745 "netconf_parser.cc"
    break;

  case 14:
#line 149 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 751 "netconf_parser.cc"
    break;

  case 15:
#line 150 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 757 "netconf_parser.cc"
    break;

  case 16:
#line 151 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 763 "netconf_parser.cc"
    break;

  case 17:
#line 152 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 769 "netconf_parser.cc"
    break;

  case 18:
#line 156 "netconf_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 780 "netconf_parser.cc"
    break;

  case 19:
#line 161 "netconf_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 790 "netconf_parser.cc"
    break;

  case 20:
#line 167 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 796 "netconf_parser.cc"
    break;

  case 23:
#line 181 "netconf_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 805 "netconf_parser.cc"
    break;

  case 24:
#line 185 "netconf_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 815 "netconf_parser.cc"
    break;

  case 25:
#line 192 "netconf_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 824 "netconf_parser.cc"
    break;

  case 26:
#line 195 "netconf_parser.yy"
    {
}
#line 831 "netconf_parser.cc"
    break;

  case 29:
#line 202 "netconf_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 840 "netconf_parser.cc"
    break;

  case 30:
#line 206 "netconf_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 849 "netconf_parser.cc"
    break;

  case 31:
#line 219 "netconf_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 860 "netconf_parser.cc"
    break;

  case 32:
#line 227 "netconf_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 871 "netconf_parser.cc"
    break;

  case 33:
#line 232 "netconf_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 881 "netconf_parser.cc"
    break;

  case 38:
#line 249 "netconf_parser.yy"
    {

    // Let's create a MapElement that will represent it, add it to the
    // top level map (that's already on the stack) and put the new map
    // on the stack as well, so child elements will be able to add
    // themselves to it.
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Netconf", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NETCONF);
}
#line 897 "netconf_parser.cc"
    break;

  case 39:
#line 259 "netconf_parser.yy"
    {
    // Ok, we're done with parsing Netconf. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 908 "netconf_parser.cc"
    break;

  case 53:
#line 287 "netconf_parser.yy"
    {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-update", flag);
}
#line 917 "netconf_parser.cc"
    break;

  case 54:
#line 292 "netconf_parser.yy"
    {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subscribe-changes", flag);
}
#line 926 "netconf_parser.cc"
    break;

  case 55:
#line 297 "netconf_parser.yy"
    {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("validate-changes", flag);
}
#line 935 "netconf_parser.cc"
    break;

  case 56:
#line 302 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 943 "netconf_parser.cc"
    break;

  case 57:
#line 304 "netconf_parser.yy"
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
#line 970 "netconf_parser.cc"
    break;

  case 58:
#line 327 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 978 "netconf_parser.cc"
    break;

  case 59:
#line 329 "netconf_parser.yy"
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
#line 1007 "netconf_parser.cc"
    break;

  case 60:
#line 355 "netconf_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1018 "netconf_parser.cc"
    break;

  case 61:
#line 360 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1027 "netconf_parser.cc"
    break;

  case 66:
#line 373 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1037 "netconf_parser.cc"
    break;

  case 67:
#line 377 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1045 "netconf_parser.cc"
    break;

  case 73:
#line 390 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1053 "netconf_parser.cc"
    break;

  case 74:
#line 392 "netconf_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1063 "netconf_parser.cc"
    break;

  case 75:
#line 398 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1071 "netconf_parser.cc"
    break;

  case 76:
#line 400 "netconf_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1080 "netconf_parser.cc"
    break;

  case 77:
#line 408 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("managed-servers", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.MANAGED_SERVERS);
}
#line 1091 "netconf_parser.cc"
    break;

  case 78:
#line 413 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1100 "netconf_parser.cc"
    break;

  case 88:
#line 437 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1111 "netconf_parser.cc"
    break;

  case 89:
#line 442 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "netconf_parser.cc"
    break;

  case 90:
#line 448 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1131 "netconf_parser.cc"
    break;

  case 91:
#line 453 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "netconf_parser.cc"
    break;

  case 92:
#line 459 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1151 "netconf_parser.cc"
    break;

  case 93:
#line 464 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "netconf_parser.cc"
    break;

  case 94:
#line 470 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ca", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1171 "netconf_parser.cc"
    break;

  case 95:
#line 475 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "netconf_parser.cc"
    break;

  case 106:
#line 497 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1188 "netconf_parser.cc"
    break;

  case 107:
#line 499 "netconf_parser.yy"
    {
    ElementPtr model(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("model", model);
    ctx.leave();
}
#line 1198 "netconf_parser.cc"
    break;

  case 108:
#line 506 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1209 "netconf_parser.cc"
    break;

  case 109:
#line 511 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1218 "netconf_parser.cc"
    break;

  case 118:
#line 529 "netconf_parser.yy"
    {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1226 "netconf_parser.cc"
    break;

  case 119:
#line 531 "netconf_parser.yy"
    {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1235 "netconf_parser.cc"
    break;

  case 120:
#line 537 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "netconf_parser.cc"
    break;

  case 121:
#line 538 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1247 "netconf_parser.cc"
    break;

  case 122:
#line 539 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stdout", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "netconf_parser.cc"
    break;

  case 123:
#line 542 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1261 "netconf_parser.cc"
    break;

  case 124:
#line 544 "netconf_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1271 "netconf_parser.cc"
    break;

  case 125:
#line 551 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1279 "netconf_parser.cc"
    break;

  case 126:
#line 553 "netconf_parser.yy"
    {
    ElementPtr url(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-url", url);
    ctx.leave();
}
#line 1289 "netconf_parser.cc"
    break;

  case 127:
#line 566 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1300 "netconf_parser.cc"
    break;

  case 128:
#line 571 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1309 "netconf_parser.cc"
    break;

  case 132:
#line 588 "netconf_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1320 "netconf_parser.cc"
    break;

  case 133:
#line 593 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1329 "netconf_parser.cc"
    break;

  case 136:
#line 605 "netconf_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1339 "netconf_parser.cc"
    break;

  case 137:
#line 609 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1347 "netconf_parser.cc"
    break;

  case 147:
#line 626 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1355 "netconf_parser.cc"
    break;

  case 148:
#line 628 "netconf_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1365 "netconf_parser.cc"
    break;

  case 149:
#line 634 "netconf_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1374 "netconf_parser.cc"
    break;

  case 150:
#line 639 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1382 "netconf_parser.cc"
    break;

  case 151:
#line 641 "netconf_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1392 "netconf_parser.cc"
    break;

  case 152:
#line 647 "netconf_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1403 "netconf_parser.cc"
    break;

  case 153:
#line 652 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1412 "netconf_parser.cc"
    break;

  case 156:
#line 661 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1422 "netconf_parser.cc"
    break;

  case 157:
#line 665 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1430 "netconf_parser.cc"
    break;

  case 165:
#line 680 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1438 "netconf_parser.cc"
    break;

  case 166:
#line 682 "netconf_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1448 "netconf_parser.cc"
    break;

  case 167:
#line 688 "netconf_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1457 "netconf_parser.cc"
    break;

  case 168:
#line 693 "netconf_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1466 "netconf_parser.cc"
    break;

  case 169:
#line 698 "netconf_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1475 "netconf_parser.cc"
    break;

  case 170:
#line 703 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1483 "netconf_parser.cc"
    break;

  case 171:
#line 705 "netconf_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1493 "netconf_parser.cc"
    break;


#line 1497 "netconf_parser.cc"

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
  NetconfParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  NetconfParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char NetconfParser::yypact_ninf_ = -92;

  const signed char NetconfParser::yytable_ninf_ = -1;

  const short
  NetconfParser::yypact_[] =
  {
      -8,   -92,   -92,   -92,    27,    11,    44,    99,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,    11,    35,     9,    -1,   -92,   106,
     104,   109,   110,   116,   -92,   -92,    26,   -92,   -92,   -92,
     -92,   -92,   122,   123,   124,   125,   -92,   -92,   126,   -92,
     127,   128,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,    11,    11,   -92,    87,   130,   132,     9,   -92,
     133,   134,    83,    90,    91,   135,   137,   139,   -92,   -92,
      -1,   -92,   -92,   140,   138,   141,   -92,   142,   100,   -92,
     -92,   -92,   -92,   145,   146,   -92,    11,    -1,   114,   -92,
     -92,   -92,     6,   147,   148,   -92,   144,    30,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   152,   150,   -92,   -92,   -92,
     -92,   -92,   -92,   155,   153,   -92,   -92,    74,   -92,   -92,
     114,   -92,   158,   159,   160,   161,   -92,     6,     0,   -92,
     147,    53,   148,   -92,   -92,   162,   163,   164,   165,   -92,
     -92,   -92,   -92,    60,   -92,   -92,   -92,   -92,   -92,   -92,
     169,   -92,   -92,   -92,   -92,    66,   -92,   -92,   -92,   -92,
     -92,   -92,    71,    71,    71,    71,   170,   171,    36,   -92,
     172,   173,   119,   174,    53,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,    86,   -92,   -92,   -92,    92,    93,
      94,   121,    11,   -92,   143,   175,   -92,   149,   -92,   177,
     179,    71,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   178,
     -92,   151,   180,   -92,   -92,   102,   -92,   -92,    -6,     8,
     178,   -92,   -92,   -92,   -92,   -92,   -92,   -92,    95,   -92,
     -92,   -92,   -92,   -92,   182,   184,   186,   -92,   101,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   187,   188,   189,    -6,
     -92,   190,   156,   157,   166,   192,     8,   -92,    96,   154,
     168,   -92,   176,   -92,   -92,   -92,   181,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92
  };

  const unsigned char
  NetconfParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,    40,    29,     0,
      28,     0,     0,    22,    38,   127,     0,    34,    36,    37,
      56,    58,     0,     0,     0,     0,    60,   132,     0,    52,
       0,    41,    42,    44,    45,    46,    50,    51,    48,    47,
      49,    26,     0,     0,    19,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     9,
       0,    30,    23,     0,     0,     0,    35,     0,     0,    53,
      54,    55,    77,     0,     0,    43,     0,    40,     0,    20,
      57,    59,    79,    62,     0,    24,     0,     0,   129,   131,
      88,    90,    92,    94,    87,     0,    80,    81,    83,    84,
      85,    86,    66,     0,    63,    64,   136,     0,   134,    39,
       0,   128,     0,     0,     0,     0,    78,     0,     0,    61,
       0,     0,     0,   133,   130,     0,     0,     0,     0,    82,
      73,    75,    70,     0,    68,    71,    72,    65,   147,   152,
       0,   150,   146,   144,   145,     0,   138,   140,   142,   143,
     141,   135,     0,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,     0,   137,   106,   108,   105,    99,
     100,   101,   103,   104,     0,    96,    98,   102,     0,     0,
       0,     0,     0,    69,     0,     0,   149,     0,   139,     0,
       0,     0,    89,    91,    93,    95,    74,    76,   148,     0,
     151,     0,     0,    97,   156,     0,   154,   107,     0,     0,
       0,   153,   118,   123,   125,   117,   115,   116,     0,   110,
     112,   113,   114,   165,     0,     0,     0,   170,     0,   158,
     160,   161,   162,   163,   164,   155,     0,     0,     0,     0,
     109,     0,     0,     0,     0,     0,     0,   157,     0,     0,
       0,   111,     0,   167,   168,   169,     0,   159,   120,   121,
     122,   119,   124,   126,   166,   171
  };

  const signed char
  NetconfParser::yypgoto_[] =
  {
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -20,    81,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -27,   -92,
     -92,   -92,   111,   -92,   -92,   112,   -92,   118,   -24,   -19,
     -18,   -26,   -92,   -25,   -92,   -92,   -92,   -92,   -92,    59,
     -92,   -92,    28,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,    47,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -50,    -4,   -92,   -92,   -92,   -92,   -92,   -51,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,    80,   -91,
     -92,   -92,    69,   -92,   -92,    31,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -14,   -92,   -92,   -54,   -92,   -92,
     -92,   -92,   -92,   -92,   -92
  };

  const short
  NetconfParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,   100,    32,    33,    19,    24,    29,    30,   188,    21,
      26,    36,    37,    38,    66,    50,    51,    52,   189,   190,
     191,   192,    70,   193,    71,    58,    76,   123,   124,   125,
     138,   153,   154,   155,   176,   156,   177,    59,   102,   115,
     116,   117,   118,   132,   119,   133,   120,   134,   121,   135,
     194,   195,   196,   209,   197,   210,   238,   239,   240,   256,
     281,   241,   257,   242,   258,    39,    67,   107,   108,    60,
      77,   127,   128,   141,   165,   166,   167,   180,   168,   169,
     183,   170,   181,   225,   226,   229,   248,   249,   250,   261,
     251,   252,   253,   254,   265
  };

  const unsigned short
  NetconfParser::yytable_[] =
  {
      49,    56,    57,    53,    28,    40,    41,   109,    54,    55,
      40,    41,    42,    43,    44,    45,     9,   232,    10,    34,
      11,   233,   234,   110,   111,   112,   113,     8,    46,    68,
     150,   151,    47,   130,    69,     1,     2,     3,   131,   109,
      48,    35,    81,    82,   243,    48,    48,   244,   245,   246,
     247,    20,    48,    49,    56,    57,    53,    12,    13,    14,
      15,    54,    55,   178,    40,    41,   150,   151,   179,   184,
      49,    56,    57,    53,   185,   114,   105,   142,    54,    55,
     143,    31,    40,    41,    42,    43,    44,   158,   159,   211,
     160,   161,   186,   187,   212,   211,   211,   211,   259,    48,
     213,   214,   215,   260,   266,   230,    22,    62,   231,   267,
     114,   152,    61,    63,   162,   163,   164,    48,    64,    65,
     278,   279,   280,   198,   199,   200,    72,    73,    74,    75,
      78,    80,    89,    83,    84,    79,    85,    87,    88,    90,
      91,    93,    92,    94,    96,    97,   101,    47,    98,    10,
     103,   104,   129,   137,   122,   126,   140,   162,   163,   164,
     136,   139,   145,   146,   147,   148,   206,   216,    99,   172,
     173,   174,   175,   182,   201,   202,   204,   205,   207,    86,
     219,   221,   217,   222,   149,   224,   262,   228,   263,   218,
     264,   268,   269,   270,   272,   220,   276,   227,    95,   157,
     282,   235,   236,   237,   274,   273,   203,   223,   271,   106,
     144,   171,   277,   275,   283,   208,   255,     0,     0,     0,
       0,     0,   284,     0,     0,     0,     0,   285,     0,     0,
       0,     0,   235,   236,   237
  };

  const short
  NetconfParser::yycheck_[] =
  {
      27,    27,    27,    27,    24,    11,    12,    98,    27,    27,
      11,    12,    13,    14,    15,    16,     5,    23,     7,    10,
       9,    27,    28,    17,    18,    19,    20,     0,    29,     3,
      30,    31,    33,     3,     8,    43,    44,    45,     8,   130,
      46,    32,    62,    63,    36,    46,    46,    39,    40,    41,
      42,     7,    46,    80,    80,    80,    80,    46,    47,    48,
      49,    80,    80,     3,    11,    12,    30,    31,     8,     3,
      97,    97,    97,    97,     8,   102,    96,     3,    97,    97,
       6,    46,    11,    12,    13,    14,    15,    34,    35,     3,
      37,    38,    21,    22,     8,     3,     3,     3,     3,    46,
       8,     8,     8,     8,     3,     3,     7,     3,     6,     8,
     137,   138,     6,     4,   141,   141,   141,    46,     8,     3,
      24,    25,    26,   173,   174,   175,     4,     4,     4,     4,
       4,     3,    49,    46,     4,     8,     4,     4,     4,    49,
      49,     4,     7,     4,     4,     7,    46,    33,     7,     7,
       5,     5,     8,     3,     7,     7,     3,   184,   184,   184,
       8,     6,     4,     4,     4,     4,    47,    46,    87,     7,
       7,     7,     7,     4,     4,     4,     4,     4,     4,    68,
       5,     4,   202,     4,   137,     7,     4,     7,     4,    46,
       4,     4,     4,     4,     4,    46,     4,    46,    80,   140,
      46,   228,   228,   228,    47,    49,   178,   211,   259,    97,
     130,   142,   266,    47,    46,   184,   230,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    -1,   259,   259,   259
  };

  const unsigned char
  NetconfParser::yystos_[] =
  {
       0,    43,    44,    45,    51,    52,    53,    54,     0,     5,
       7,     9,    46,    47,    48,    49,    57,    58,    59,    64,
       7,    69,     7,    55,    65,    60,    70,    56,    58,    66,
      67,    46,    62,    63,    10,    32,    71,    72,    73,   125,
      11,    12,    13,    14,    15,    16,    29,    33,    46,    68,
      75,    76,    77,    78,    79,    80,    81,    83,    85,    97,
     129,     6,     3,     4,     8,     3,    74,   126,     3,     8,
      82,    84,     4,     4,     4,     4,    86,   130,     4,     8,
       3,    58,    58,    46,     4,     4,    72,     4,     4,    49,
      49,    49,     7,     4,     4,    77,     4,     7,     7,    59,
      61,    46,    98,     5,     5,    58,    75,   127,   128,   129,
      17,    18,    19,    20,    68,    99,   100,   101,   102,   104,
     106,   108,     7,    87,    88,    89,     7,   131,   132,     8,
       3,     8,   103,   105,   107,   109,     8,     3,    90,     6,
       3,   133,     3,     6,   128,     4,     4,     4,     4,   101,
      30,    31,    68,    91,    92,    93,    95,    89,    34,    35,
      37,    38,    68,    81,    83,   134,   135,   136,   138,   139,
     141,   132,     7,     7,     7,     7,    94,    96,     3,     8,
     137,   142,     4,   140,     3,     8,    21,    22,    68,    78,
      79,    80,    81,    83,   110,   111,   112,   114,   110,   110,
     110,     4,     4,    92,     4,     4,    47,     4,   135,   113,
     115,     3,     8,     8,     8,     8,    46,    58,    46,     5,
      46,     4,     4,   111,     7,   143,   144,    46,     7,   145,
       3,     6,    23,    27,    28,    68,    81,    83,   116,   117,
     118,   121,   123,    36,    39,    40,    41,    42,   146,   147,
     148,   150,   151,   152,   153,   144,   119,   122,   124,     3,
       8,   149,     4,     4,     4,   154,     3,     8,     4,     4,
       4,   117,     4,    49,    47,    47,     4,   147,    24,    25,
      26,   120,    46,    46,    46,    46
  };

  const unsigned char
  NetconfParser::yyr1_[] =
  {
       0,    50,    52,    51,    53,    51,    54,    51,    56,    55,
      57,    58,    58,    58,    58,    58,    58,    58,    60,    59,
      61,    62,    62,    63,    63,    65,    64,    66,    66,    67,
      67,    68,    70,    69,    71,    71,    72,    72,    74,    73,
      75,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    78,    79,    80,    82,    81,    84,    83,
      86,    85,    87,    87,    88,    88,    90,    89,    91,    91,
      91,    92,    92,    94,    93,    96,    95,    98,    97,    99,
      99,   100,   100,   101,   101,   101,   101,   101,   103,   102,
     105,   104,   107,   106,   109,   108,   110,   110,   111,   111,
     111,   111,   111,   111,   111,   111,   113,   112,   115,   114,
     116,   116,   117,   117,   117,   117,   117,   117,   119,   118,
     120,   120,   120,   122,   121,   124,   123,   126,   125,   127,
     127,   128,   130,   129,   131,   131,   133,   132,   134,   134,
     135,   135,   135,   135,   135,   135,   135,   137,   136,   138,
     140,   139,   142,   141,   143,   143,   145,   144,   146,   146,
     147,   147,   147,   147,   147,   149,   148,   150,   151,   152,
     154,   153
  };

  const unsigned char
  NetconfParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     0,     6,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     6,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const NetconfParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Netconf\"", "\"user-context\"",
  "\"comment\"", "\"boot-update\"", "\"subscribe-changes\"",
  "\"validate-changes\"", "\"managed-servers\"", "\"dhcp4\"", "\"dhcp6\"",
  "\"d2\"", "\"ca\"", "\"model\"", "\"control-socket\"", "\"socket-type\"",
  "\"unix\"", "\"http\"", "\"stdout\"", "\"socket-name\"",
  "\"socket-url\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"Logging\"", "\"loggers\"", "\"name\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "START_JSON",
  "START_NETCONF", "START_SUB_NETCONF", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "sub_netconf", "$@4", "json", "value", "map", "$@5",
  "map_value", "map_content", "not_empty_map", "list_generic", "$@6",
  "list_content", "not_empty_list", "unknown_map_entry",
  "netconf_syntax_map", "$@7", "global_objects", "global_object",
  "netconf_object", "$@8", "global_params", "not_empty_global_params",
  "global_param", "boot_update", "subscribe_changes", "validate_changes",
  "user_context", "$@9", "comment", "$@10", "hooks_libraries", "$@11",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@12", "hooks_params", "hooks_param", "library",
  "$@13", "parameters", "$@14", "managed_servers", "$@15",
  "servers_entries", "not_empty_servers_entries", "server_entry",
  "dhcp4_server", "$@16", "dhcp6_server", "$@17", "d2_server", "$@18",
  "ca_server", "$@19", "managed_server_params", "managed_server_param",
  "model", "$@20", "control_socket", "$@21", "control_socket_params",
  "control_socket_param", "socket_type", "$@22", "socket_type_value",
  "socket_name", "$@23", "socket_url", "$@24", "logging_object", "$@25",
  "logging_params", "logging_param", "loggers", "$@26", "loggers_entries",
  "logger_entry", "$@27", "logger_params", "logger_param", "name", "$@28",
  "debuglevel", "severity", "$@29", "output_options_list", "$@30",
  "output_options_list_content", "output_entry", "$@31",
  "output_params_list", "output_params", "output", "$@32", "flush",
  "maxsize", "maxver", "pattern", "$@33", YY_NULLPTR
  };

#if NETCONF_DEBUG
  const unsigned short
  NetconfParser::yyrline_[] =
  {
       0,   119,   119,   119,   120,   120,   121,   121,   129,   129,
     140,   146,   147,   148,   149,   150,   151,   152,   156,   156,
     167,   172,   173,   181,   185,   192,   192,   198,   199,   202,
     206,   219,   227,   227,   239,   240,   244,   245,   249,   249,
     266,   267,   270,   271,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   287,   292,   297,   302,   302,   327,   327,
     355,   355,   365,   366,   369,   370,   373,   373,   381,   382,
     383,   386,   387,   390,   390,   398,   398,   408,   408,   418,
     419,   422,   423,   429,   430,   431,   432,   433,   437,   437,
     448,   448,   459,   459,   470,   470,   481,   482,   486,   487,
     488,   489,   490,   491,   492,   493,   497,   497,   506,   506,
     517,   518,   521,   522,   523,   524,   525,   526,   529,   529,
     537,   538,   539,   542,   542,   551,   551,   566,   566,   579,
     580,   584,   588,   588,   600,   601,   605,   605,   613,   614,
     617,   618,   619,   620,   621,   622,   623,   626,   626,   634,
     639,   639,   647,   647,   657,   658,   661,   661,   669,   670,
     673,   674,   675,   676,   677,   680,   680,   688,   693,   698,
     703,   703
  };

  // Print the state stack on the debug stream.
  void
  NetconfParser::yystack_print_ ()
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
  NetconfParser::yy_reduce_print_ (int yyrule)
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
#endif // NETCONF_DEBUG


#line 14 "netconf_parser.yy"
} } // isc::netconf
#line 2109 "netconf_parser.cc"

#line 711 "netconf_parser.yy"


void
isc::netconf::NetconfParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
