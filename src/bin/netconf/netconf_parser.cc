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


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
#line 146 "netconf_parser.cc"


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
      case 57: // value
      case 60: // map_value
      case 119: // socket_type_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 48: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 47: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 46: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 45: // "constant string"
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
      case 57: // value
      case 60: // map_value
      case 119: // socket_type_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 48: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 47: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 46: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 45: // "constant string"
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
      case 57: // value
      case 60: // map_value
      case 119: // socket_type_value
        value.move< ElementPtr > (that.value);
        break;

      case 48: // "boolean"
        value.move< bool > (that.value);
        break;

      case 47: // "floating point"
        value.move< double > (that.value);
        break;

      case 46: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 45: // "constant string"
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
      case 45: // "constant string"
#line 107 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 393 "netconf_parser.cc"
        break;

      case 46: // "integer"
#line 107 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 399 "netconf_parser.cc"
        break;

      case 47: // "floating point"
#line 107 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 405 "netconf_parser.cc"
        break;

      case 48: // "boolean"
#line 107 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 411 "netconf_parser.cc"
        break;

      case 57: // value
#line 107 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 417 "netconf_parser.cc"
        break;

      case 60: // map_value
#line 107 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 423 "netconf_parser.cc"
        break;

      case 119: // socket_type_value
#line 107 "netconf_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "netconf_parser.cc"
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
      case 57: // value
      case 60: // map_value
      case 119: // socket_type_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 48: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 47: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 46: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 45: // "constant string"
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
#line 118 "netconf_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 691 "netconf_parser.cc"
    break;

  case 4:
#line 119 "netconf_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 697 "netconf_parser.cc"
    break;

  case 6:
#line 120 "netconf_parser.yy"
    { ctx.ctx_ = ctx.NETCONF; }
#line 703 "netconf_parser.cc"
    break;

  case 8:
#line 128 "netconf_parser.yy"
    {
    // Parse the Netconf map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 713 "netconf_parser.cc"
    break;

  case 9:
#line 132 "netconf_parser.yy"
    {
    // parsing completed
}
#line 721 "netconf_parser.cc"
    break;

  case 10:
#line 139 "netconf_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 730 "netconf_parser.cc"
    break;

  case 11:
#line 145 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 736 "netconf_parser.cc"
    break;

  case 12:
#line 146 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "netconf_parser.cc"
    break;

  case 13:
#line 147 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "netconf_parser.cc"
    break;

  case 14:
#line 148 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "netconf_parser.cc"
    break;

  case 15:
#line 149 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 760 "netconf_parser.cc"
    break;

  case 16:
#line 150 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 766 "netconf_parser.cc"
    break;

  case 17:
#line 151 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "netconf_parser.cc"
    break;

  case 18:
#line 155 "netconf_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 783 "netconf_parser.cc"
    break;

  case 19:
#line 160 "netconf_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 793 "netconf_parser.cc"
    break;

  case 20:
#line 166 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 799 "netconf_parser.cc"
    break;

  case 23:
#line 180 "netconf_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 808 "netconf_parser.cc"
    break;

  case 24:
#line 184 "netconf_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 818 "netconf_parser.cc"
    break;

  case 25:
#line 191 "netconf_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 827 "netconf_parser.cc"
    break;

  case 26:
#line 194 "netconf_parser.yy"
    {
}
#line 834 "netconf_parser.cc"
    break;

  case 29:
#line 201 "netconf_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 843 "netconf_parser.cc"
    break;

  case 30:
#line 205 "netconf_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 852 "netconf_parser.cc"
    break;

  case 31:
#line 218 "netconf_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 863 "netconf_parser.cc"
    break;

  case 32:
#line 226 "netconf_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 874 "netconf_parser.cc"
    break;

  case 33:
#line 231 "netconf_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 884 "netconf_parser.cc"
    break;

  case 38:
#line 248 "netconf_parser.yy"
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
#line 900 "netconf_parser.cc"
    break;

  case 39:
#line 258 "netconf_parser.yy"
    {
    // Ok, we're done with parsing Netconf. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 911 "netconf_parser.cc"
    break;

  case 53:
#line 286 "netconf_parser.yy"
    {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-update", flag);
}
#line 920 "netconf_parser.cc"
    break;

  case 54:
#line 291 "netconf_parser.yy"
    {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subscribe-changes", flag);
}
#line 929 "netconf_parser.cc"
    break;

  case 55:
#line 296 "netconf_parser.yy"
    {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("validate-changes", flag);
}
#line 938 "netconf_parser.cc"
    break;

  case 56:
#line 301 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 946 "netconf_parser.cc"
    break;

  case 57:
#line 303 "netconf_parser.yy"
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
#line 973 "netconf_parser.cc"
    break;

  case 58:
#line 326 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 981 "netconf_parser.cc"
    break;

  case 59:
#line 328 "netconf_parser.yy"
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
#line 1010 "netconf_parser.cc"
    break;

  case 60:
#line 354 "netconf_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1021 "netconf_parser.cc"
    break;

  case 61:
#line 359 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1030 "netconf_parser.cc"
    break;

  case 66:
#line 372 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1040 "netconf_parser.cc"
    break;

  case 67:
#line 376 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1048 "netconf_parser.cc"
    break;

  case 73:
#line 389 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1056 "netconf_parser.cc"
    break;

  case 74:
#line 391 "netconf_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1066 "netconf_parser.cc"
    break;

  case 75:
#line 397 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1074 "netconf_parser.cc"
    break;

  case 76:
#line 399 "netconf_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1083 "netconf_parser.cc"
    break;

  case 77:
#line 407 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("managed-servers", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.MANAGED_SERVERS);
}
#line 1094 "netconf_parser.cc"
    break;

  case 78:
#line 412 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1103 "netconf_parser.cc"
    break;

  case 88:
#line 436 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1114 "netconf_parser.cc"
    break;

  case 89:
#line 441 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1123 "netconf_parser.cc"
    break;

  case 90:
#line 447 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1134 "netconf_parser.cc"
    break;

  case 91:
#line 452 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1143 "netconf_parser.cc"
    break;

  case 92:
#line 458 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1154 "netconf_parser.cc"
    break;

  case 93:
#line 463 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1163 "netconf_parser.cc"
    break;

  case 94:
#line 469 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ca", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1174 "netconf_parser.cc"
    break;

  case 95:
#line 474 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1183 "netconf_parser.cc"
    break;

  case 106:
#line 496 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1191 "netconf_parser.cc"
    break;

  case 107:
#line 498 "netconf_parser.yy"
    {
    ElementPtr model(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("model", model);
    ctx.leave();
}
#line 1201 "netconf_parser.cc"
    break;

  case 108:
#line 505 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1212 "netconf_parser.cc"
    break;

  case 109:
#line 510 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1221 "netconf_parser.cc"
    break;

  case 118:
#line 528 "netconf_parser.yy"
    {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1229 "netconf_parser.cc"
    break;

  case 119:
#line 530 "netconf_parser.yy"
    {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1238 "netconf_parser.cc"
    break;

  case 120:
#line 536 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1244 "netconf_parser.cc"
    break;

  case 121:
#line 537 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1250 "netconf_parser.cc"
    break;

  case 122:
#line 538 "netconf_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stdout", ctx.loc2pos(yystack_[0].location))); }
#line 1256 "netconf_parser.cc"
    break;

  case 123:
#line 541 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1264 "netconf_parser.cc"
    break;

  case 124:
#line 543 "netconf_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1274 "netconf_parser.cc"
    break;

  case 125:
#line 550 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1282 "netconf_parser.cc"
    break;

  case 126:
#line 552 "netconf_parser.yy"
    {
    ElementPtr url(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-url", url);
    ctx.leave();
}
#line 1292 "netconf_parser.cc"
    break;

  case 127:
#line 565 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1303 "netconf_parser.cc"
    break;

  case 128:
#line 570 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1312 "netconf_parser.cc"
    break;

  case 132:
#line 587 "netconf_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1323 "netconf_parser.cc"
    break;

  case 133:
#line 592 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1332 "netconf_parser.cc"
    break;

  case 136:
#line 604 "netconf_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1342 "netconf_parser.cc"
    break;

  case 137:
#line 608 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1350 "netconf_parser.cc"
    break;

  case 147:
#line 625 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1358 "netconf_parser.cc"
    break;

  case 148:
#line 627 "netconf_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1368 "netconf_parser.cc"
    break;

  case 149:
#line 633 "netconf_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1377 "netconf_parser.cc"
    break;

  case 150:
#line 638 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1385 "netconf_parser.cc"
    break;

  case 151:
#line 640 "netconf_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1395 "netconf_parser.cc"
    break;

  case 152:
#line 646 "netconf_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1406 "netconf_parser.cc"
    break;

  case 153:
#line 651 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1415 "netconf_parser.cc"
    break;

  case 156:
#line 660 "netconf_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1425 "netconf_parser.cc"
    break;

  case 157:
#line 664 "netconf_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1433 "netconf_parser.cc"
    break;

  case 164:
#line 678 "netconf_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1441 "netconf_parser.cc"
    break;

  case 165:
#line 680 "netconf_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1451 "netconf_parser.cc"
    break;

  case 166:
#line 686 "netconf_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1460 "netconf_parser.cc"
    break;

  case 167:
#line 691 "netconf_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1469 "netconf_parser.cc"
    break;

  case 168:
#line 696 "netconf_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1478 "netconf_parser.cc"
    break;


#line 1482 "netconf_parser.cc"

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


  const signed char NetconfParser::yypact_ninf_ = -83;

  const signed char NetconfParser::yytable_ninf_ = -1;

  const short
  NetconfParser::yypact_[] =
  {
      76,   -83,   -83,   -83,     6,    12,     0,    11,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,    12,     4,    -5,    -1,   -83,    14,
      48,    73,    82,   104,   -83,   -83,    44,   -83,   -83,   -83,
     -83,   -83,   108,   109,   123,   124,   -83,   -83,   125,   -83,
     122,   128,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,    12,    12,   -83,    87,   129,   130,    -5,   -83,
     131,   132,    89,    90,    91,   133,   137,   138,   -83,   -83,
      -1,   -83,   -83,   139,   140,   141,   -83,   142,    99,   -83,
     -83,   -83,   -83,   145,   146,   -83,    12,    -1,   112,   -83,
     -83,   -83,     5,   147,   148,   -83,   144,    77,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   152,   143,   -83,   -83,   -83,
     -83,   -83,   -83,   150,   158,   -83,   -83,    62,   -83,   -83,
     112,   -83,   149,   159,   160,   161,   -83,     5,    51,   -83,
     147,    29,   148,   -83,   -83,   155,   162,   163,   164,   -83,
     -83,   -83,   -83,    83,   -83,   -83,   -83,   -83,   -83,   -83,
     168,   -83,   -83,   -83,   -83,    84,   -83,   -83,   -83,   -83,
     -83,   -83,    24,    24,    24,    24,   169,   170,     3,   -83,
     171,   172,   120,   173,    29,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,    85,   -83,   -83,   -83,    86,    94,
      95,   134,    12,   -83,   135,   176,   -83,   151,   -83,   174,
     179,    24,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   177,
     -83,   153,   178,   -83,   -83,   102,   -83,   -83,    72,   -10,
     177,   -83,   -83,   -83,   -83,   -83,   -83,   -83,    98,   -83,
     -83,   -83,   -83,   -83,   182,   183,   184,   101,   -83,   -83,
     -83,   -83,   -83,   -83,   185,   186,   187,    72,   -83,   188,
     119,   154,   165,   -10,   -83,    97,   167,   175,   -83,   180,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83
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
     112,   113,   114,   164,     0,     0,     0,     0,   158,   160,
     161,   162,   163,   155,     0,     0,     0,     0,   109,     0,
       0,     0,     0,     0,   157,     0,     0,     0,   111,     0,
     166,   167,   168,   159,   120,   121,   122,   119,   124,   126,
     165
  };

  const signed char
  NetconfParser::yypgoto_[] =
  {
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -20,    81,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -27,   -83,
     -83,   -83,   126,   -83,   -83,    96,   -83,   115,   -24,   -19,
     -18,   -26,   -83,   -25,   -83,   -83,   -83,   -83,   -83,    57,
     -83,   -83,    21,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,    67,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -49,    -6,   -83,   -83,   -83,   -83,   -83,   -51,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,    78,   -82,
     -83,   -83,    65,   -83,   -83,    25,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -17,   -83,   -83,   -53,   -83,   -83,
     -83,   -83,   -83
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
     194,   195,   196,   209,   197,   210,   238,   239,   240,   254,
     277,   241,   255,   242,   256,    39,    67,   107,   108,    60,
      77,   127,   128,   141,   165,   166,   167,   180,   168,   169,
     183,   170,   181,   225,   226,   229,   247,   248,   249,   259,
     250,   251,   252
  };

  const unsigned short
  NetconfParser::yytable_[] =
  {
      49,    56,    57,    53,    28,    34,     8,    20,    54,    55,
      40,    41,    42,    43,    44,    45,   109,     9,    22,    10,
      61,    11,   110,   111,   112,   113,   243,    35,    46,   244,
     245,   246,    47,   150,   151,    40,    41,    42,    43,    44,
      40,    41,    81,    82,    48,   186,   187,    68,   109,    31,
      48,    62,    69,    49,    56,    57,    53,    12,    13,    14,
      15,    54,    55,   158,   159,   142,   160,   161,   143,    48,
      49,    56,    57,    53,    48,   114,   105,    63,    54,    55,
     130,   150,   151,    40,    41,   131,   178,   184,   211,   211,
      64,   179,   185,   212,   213,   232,    48,   211,   211,   233,
     234,   257,   214,   215,   263,   230,   258,    65,   231,   264,
     114,   152,    72,    73,   162,   163,   164,    48,     1,     2,
       3,   274,   275,   276,   198,   199,   200,    74,    75,    78,
      79,    80,    83,    84,    85,    87,    88,    89,    90,    91,
      92,    93,    94,    96,   101,    47,   137,    97,    98,    10,
     103,   104,   129,   145,   122,   126,   139,   162,   163,   164,
     136,   140,   172,   146,   147,   148,   206,   270,    99,   173,
     174,   175,   182,   201,   202,   204,   205,   207,   221,   216,
     218,   219,   217,   222,   224,   228,   260,   261,   262,   265,
     266,   267,   269,   106,    86,    95,   220,   157,   227,   203,
     271,   235,   236,   237,   149,   223,   268,   171,   144,   208,
     273,   272,   278,   253,     0,     0,     0,     0,     0,     0,
     279,     0,     0,     0,     0,   280,     0,     0,     0,     0,
     235,   236,   237
  };

  const short
  NetconfParser::yycheck_[] =
  {
      27,    27,    27,    27,    24,    10,     0,     7,    27,    27,
      11,    12,    13,    14,    15,    16,    98,     5,     7,     7,
       6,     9,    17,    18,    19,    20,    36,    32,    29,    39,
      40,    41,    33,    30,    31,    11,    12,    13,    14,    15,
      11,    12,    62,    63,    45,    21,    22,     3,   130,    45,
      45,     3,     8,    80,    80,    80,    80,    45,    46,    47,
      48,    80,    80,    34,    35,     3,    37,    38,     6,    45,
      97,    97,    97,    97,    45,   102,    96,     4,    97,    97,
       3,    30,    31,    11,    12,     8,     3,     3,     3,     3,
       8,     8,     8,     8,     8,    23,    45,     3,     3,    27,
      28,     3,     8,     8,     3,     3,     8,     3,     6,     8,
     137,   138,     4,     4,   141,   141,   141,    45,    42,    43,
      44,    24,    25,    26,   173,   174,   175,     4,     4,     4,
       8,     3,    45,     4,     4,     4,     4,    48,    48,    48,
       7,     4,     4,     4,    45,    33,     3,     7,     7,     7,
       5,     5,     8,     4,     7,     7,     6,   184,   184,   184,
       8,     3,     7,     4,     4,     4,    46,    48,    87,     7,
       7,     7,     4,     4,     4,     4,     4,     4,     4,    45,
      45,     5,   202,     4,     7,     7,     4,     4,     4,     4,
       4,     4,     4,    97,    68,    80,    45,   140,    45,   178,
      46,   228,   228,   228,   137,   211,   257,   142,   130,   184,
     263,    46,    45,   230,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
     257,   257,   257
  };

  const unsigned char
  NetconfParser::yystos_[] =
  {
       0,    42,    43,    44,    50,    51,    52,    53,     0,     5,
       7,     9,    45,    46,    47,    48,    56,    57,    58,    63,
       7,    68,     7,    54,    64,    59,    69,    55,    57,    65,
      66,    45,    61,    62,    10,    32,    70,    71,    72,   124,
      11,    12,    13,    14,    15,    16,    29,    33,    45,    67,
      74,    75,    76,    77,    78,    79,    80,    82,    84,    96,
     128,     6,     3,     4,     8,     3,    73,   125,     3,     8,
      81,    83,     4,     4,     4,     4,    85,   129,     4,     8,
       3,    57,    57,    45,     4,     4,    71,     4,     4,    48,
      48,    48,     7,     4,     4,    76,     4,     7,     7,    58,
      60,    45,    97,     5,     5,    57,    74,   126,   127,   128,
      17,    18,    19,    20,    67,    98,    99,   100,   101,   103,
     105,   107,     7,    86,    87,    88,     7,   130,   131,     8,
       3,     8,   102,   104,   106,   108,     8,     3,    89,     6,
       3,   132,     3,     6,   127,     4,     4,     4,     4,   100,
      30,    31,    67,    90,    91,    92,    94,    88,    34,    35,
      37,    38,    67,    80,    82,   133,   134,   135,   137,   138,
     140,   131,     7,     7,     7,     7,    93,    95,     3,     8,
     136,   141,     4,   139,     3,     8,    21,    22,    67,    77,
      78,    79,    80,    82,   109,   110,   111,   113,   109,   109,
     109,     4,     4,    91,     4,     4,    46,     4,   134,   112,
     114,     3,     8,     8,     8,     8,    45,    57,    45,     5,
      45,     4,     4,   110,     7,   142,   143,    45,     7,   144,
       3,     6,    23,    27,    28,    67,    80,    82,   115,   116,
     117,   120,   122,    36,    39,    40,    41,   145,   146,   147,
     149,   150,   151,   143,   118,   121,   123,     3,     8,   148,
       4,     4,     4,     3,     8,     4,     4,     4,   116,     4,
      48,    46,    46,   146,    24,    25,    26,   119,    45,    45,
      45
  };

  const unsigned char
  NetconfParser::yyr1_[] =
  {
       0,    49,    51,    50,    52,    50,    53,    50,    55,    54,
      56,    57,    57,    57,    57,    57,    57,    57,    59,    58,
      60,    61,    61,    62,    62,    64,    63,    65,    65,    66,
      66,    67,    69,    68,    70,    70,    71,    71,    73,    72,
      74,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    77,    78,    79,    81,    80,    83,    82,
      85,    84,    86,    86,    87,    87,    89,    88,    90,    90,
      90,    91,    91,    93,    92,    95,    94,    97,    96,    98,
      98,    99,    99,   100,   100,   100,   100,   100,   102,   101,
     104,   103,   106,   105,   108,   107,   109,   109,   110,   110,
     110,   110,   110,   110,   110,   110,   112,   111,   114,   113,
     115,   115,   116,   116,   116,   116,   116,   116,   118,   117,
     119,   119,   119,   121,   120,   123,   122,   125,   124,   126,
     126,   127,   129,   128,   130,   130,   132,   131,   133,   133,
     134,   134,   134,   134,   134,   134,   134,   136,   135,   137,
     139,   138,   141,   140,   142,   142,   144,   143,   145,   145,
     146,   146,   146,   146,   148,   147,   149,   150,   151
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
       1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"maxsize\"", "\"maxver\"", "START_JSON", "START_NETCONF",
  "START_SUB_NETCONF", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "sub_netconf", "$@4", "json", "value", "map", "$@5", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@6", "list_content",
  "not_empty_list", "unknown_map_entry", "netconf_syntax_map", "$@7",
  "global_objects", "global_object", "netconf_object", "$@8",
  "global_params", "not_empty_global_params", "global_param",
  "boot_update", "subscribe_changes", "validate_changes", "user_context",
  "$@9", "comment", "$@10", "hooks_libraries", "$@11",
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
  "maxsize", "maxver", YY_NULLPTR
  };

#if NETCONF_DEBUG
  const unsigned short
  NetconfParser::yyrline_[] =
  {
       0,   118,   118,   118,   119,   119,   120,   120,   128,   128,
     139,   145,   146,   147,   148,   149,   150,   151,   155,   155,
     166,   171,   172,   180,   184,   191,   191,   197,   198,   201,
     205,   218,   226,   226,   238,   239,   243,   244,   248,   248,
     265,   266,   269,   270,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   286,   291,   296,   301,   301,   326,   326,
     354,   354,   364,   365,   368,   369,   372,   372,   380,   381,
     382,   385,   386,   389,   389,   397,   397,   407,   407,   417,
     418,   421,   422,   428,   429,   430,   431,   432,   436,   436,
     447,   447,   458,   458,   469,   469,   480,   481,   485,   486,
     487,   488,   489,   490,   491,   492,   496,   496,   505,   505,
     516,   517,   520,   521,   522,   523,   524,   525,   528,   528,
     536,   537,   538,   541,   541,   550,   550,   565,   565,   578,
     579,   583,   587,   587,   599,   600,   604,   604,   612,   613,
     616,   617,   618,   619,   620,   621,   622,   625,   625,   633,
     638,   638,   646,   646,   656,   657,   660,   660,   668,   669,
     672,   673,   674,   675,   678,   678,   686,   691,   696
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
#line 2091 "netconf_parser.cc"

#line 701 "netconf_parser.yy"


void
isc::netconf::NetconfParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
