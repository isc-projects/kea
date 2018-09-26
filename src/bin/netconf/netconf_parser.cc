// A Bison parser, made by GNU Bison 3.0.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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
#define yylex   netconf_lex

// First part of user declarations.

#line 39 "netconf_parser.cc" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "netconf_parser.h"

// User implementation prologue.

#line 53 "netconf_parser.cc" // lalr1.cc:414
// Unqualified %code blocks.
#line 33 "netconf_parser.yy" // lalr1.cc:415

#include <netconf/parser_context.h>

#line 59 "netconf_parser.cc" // lalr1.cc:415


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

#line 14 "netconf_parser.yy" // lalr1.cc:481
namespace isc { namespace netconf {
#line 145 "netconf_parser.cc" // lalr1.cc:481

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


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  NetconfParser::by_state::by_state ()
    : state (empty_state)
  {}

  NetconfParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  NetconfParser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  NetconfParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  NetconfParser::by_state::by_state (state_type s)
    : state (s)
  {}

  NetconfParser::symbol_number_type
  NetconfParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  NetconfParser::stack_symbol_type::stack_symbol_type ()
  {}

  NetconfParser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    switch (that.type_get ())
    {
      case 58: // value
      case 61: // map_value
      case 116: // socket_type_value
        value.copy< ElementPtr > (that.value);
        break;

      case 49: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 48: // "floating point"
        value.copy< double > (that.value);
        break;

      case 47: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 46: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

  }

  NetconfParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    switch (that.type_get ())
    {
      case 58: // value
      case 61: // map_value
      case 116: // socket_type_value
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

    // that is emptied.
    that.type = empty_symbol;
  }

  NetconfParser::stack_symbol_type&
  NetconfParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 58: // value
      case 61: // map_value
      case 116: // socket_type_value
        value.copy< ElementPtr > (that.value);
        break;

      case 49: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 48: // "floating point"
        value.copy< double > (that.value);
        break;

      case 47: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 46: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 46: // "constant string"

#line 108 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< std::string > (); }
#line 378 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 47: // "integer"

#line 108 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 385 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 48: // "floating point"

#line 108 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< double > (); }
#line 392 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 49: // "boolean"

#line 108 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< bool > (); }
#line 399 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 58: // value

#line 108 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 61: // map_value

#line 108 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 116: // socket_type_value

#line 108 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "netconf_parser.cc" // lalr1.cc:635
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  NetconfParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  NetconfParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  NetconfParser::yypop_ (unsigned n)
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

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
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 58: // value
      case 61: // map_value
      case 116: // socket_type_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 49: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 48: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 47: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 46: // "constant string"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 119 "netconf_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 660 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 120 "netconf_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.CONFIG; }
#line 666 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 121 "netconf_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.NETCONF; }
#line 672 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 129 "netconf_parser.yy" // lalr1.cc:856
    {
    // Parse the Control-netconf map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 682 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 9:
#line 133 "netconf_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 690 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 140 "netconf_parser.yy" // lalr1.cc:856
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 699 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 11:
#line 146 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 705 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 147 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 711 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 13:
#line 148 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 717 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 14:
#line 149 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 723 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 15:
#line 150 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 729 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 16:
#line 151 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 735 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 17:
#line 152 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 741 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 18:
#line 156 "netconf_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 752 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 19:
#line 161 "netconf_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 762 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 20:
#line 167 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 768 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 23:
#line 181 "netconf_parser.yy" // lalr1.cc:856
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 777 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 24:
#line 185 "netconf_parser.yy" // lalr1.cc:856
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 787 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 25:
#line 192 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 796 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 26:
#line 195 "netconf_parser.yy" // lalr1.cc:856
    {
}
#line 803 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 29:
#line 202 "netconf_parser.yy" // lalr1.cc:856
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 812 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 30:
#line 206 "netconf_parser.yy" // lalr1.cc:856
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 821 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 31:
#line 219 "netconf_parser.yy" // lalr1.cc:856
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 832 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 32:
#line 228 "netconf_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 843 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 33:
#line 233 "netconf_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 853 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 43:
#line 255 "netconf_parser.yy" // lalr1.cc:856
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
#line 869 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 44:
#line 265 "netconf_parser.yy" // lalr1.cc:856
    {
    // Ok, we're done with parsing control-netconf. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 880 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 52:
#line 285 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 888 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 53:
#line 287 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
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
#line 915 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 54:
#line 310 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 923 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 55:
#line 312 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
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
#line 952 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 56:
#line 338 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 963 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 57:
#line 343 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 972 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 62:
#line 356 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 982 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 63:
#line 360 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 990 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 69:
#line 373 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 998 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 70:
#line 375 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1008 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 71:
#line 381 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1016 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 72:
#line 383 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1025 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 73:
#line 391 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("managed-servers", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.MANAGED_SERVERS);
}
#line 1036 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 74:
#line 396 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1045 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 84:
#line 420 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1056 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 85:
#line 425 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1065 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 86:
#line 431 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1076 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 87:
#line 436 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1085 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 88:
#line 442 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1096 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 89:
#line 447 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1105 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 90:
#line 453 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ca", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1116 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 91:
#line 458 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1125 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 99:
#line 477 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1133 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 100:
#line 479 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr model(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("model", model);
    ctx.leave();
}
#line 1143 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 101:
#line 486 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1154 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 102:
#line 491 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1163 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 112:
#line 510 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1171 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 113:
#line 512 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1180 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 114:
#line 518 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1186 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 115:
#line 519 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1192 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 116:
#line 520 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("stdout", ctx.loc2pos(yystack_[0].location))); }
#line 1198 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 117:
#line 523 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1206 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 118:
#line 525 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1216 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 119:
#line 532 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1224 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 120:
#line 534 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", host);
    ctx.leave();
}
#line 1234 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 121:
#line 541 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr port(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", port);
}
#line 1243 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 122:
#line 549 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1251 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 123:
#line 551 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1260 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 124:
#line 556 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1268 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 125:
#line 558 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1277 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 126:
#line 563 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1285 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 127:
#line 565 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1294 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 128:
#line 570 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1302 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 129:
#line 572 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1311 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 130:
#line 583 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1322 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 131:
#line 588 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1331 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 135:
#line 605 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1342 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 136:
#line 610 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1351 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 139:
#line 622 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1361 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 140:
#line 626 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1369 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 150:
#line 643 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1378 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 151:
#line 648 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1386 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 152:
#line 650 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1396 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 153:
#line 656 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1407 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 154:
#line 661 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1416 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 157:
#line 670 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1426 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 158:
#line 674 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1434 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 165:
#line 688 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1442 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 166:
#line 690 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1452 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 167:
#line 696 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1461 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 168:
#line 701 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1470 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 169:
#line 706 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1479 "netconf_parser.cc" // lalr1.cc:856
    break;


#line 1483 "netconf_parser.cc" // lalr1.cc:856
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
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
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


  const short int NetconfParser::yypact_ninf_ = -216;

  const signed char NetconfParser::yytable_ninf_ = -1;

  const short int
  NetconfParser::yypact_[] =
  {
      74,  -216,  -216,  -216,     8,     2,     3,    39,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,     2,   -13,    -5,    11,  -216,    52,
      72,    79,    77,    84,  -216,  -216,  -216,  -216,  -216,  -216,
     102,  -216,    23,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,   107,  -216,  -216,    53,  -216,  -216,  -216,  -216,
    -216,  -216,     2,     2,  -216,    59,   111,   122,   123,   124,
     125,   126,  -216,    -5,  -216,   127,   128,   129,   130,    11,
    -216,  -216,  -216,   131,   132,   133,     2,     2,     2,     2,
    -216,   134,    87,  -216,   137,  -216,     2,    11,   106,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,    -2,   136,  -216,    56,
    -216,    62,  -216,  -216,  -216,  -216,  -216,  -216,  -216,   138,
     135,  -216,  -216,  -216,  -216,  -216,  -216,   139,   141,  -216,
    -216,   143,   106,  -216,   144,   145,   146,   147,  -216,    -2,
      -1,  -216,   136,   148,  -216,   149,   150,   151,   155,  -216,
    -216,  -216,  -216,    76,  -216,  -216,  -216,  -216,   157,    70,
      70,    70,    70,   161,   162,   -11,  -216,  -216,    26,  -216,
    -216,  -216,  -216,  -216,  -216,    90,  -216,  -216,  -216,    91,
      92,    93,   108,     2,  -216,    28,   157,  -216,   163,   164,
      70,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,   165,
    -216,  -216,  -216,  -216,  -216,    94,  -216,  -216,  -216,  -216,
    -216,   109,   166,  -216,   167,   168,   105,   170,    28,  -216,
    -216,    66,   140,   171,  -216,   142,  -216,  -216,  -216,   173,
    -216,  -216,  -216,   100,  -216,  -216,  -216,  -216,  -216,  -216,
     172,  -216,   174,   176,   152,    66,  -216,  -216,   104,  -216,
      99,   154,  -216,  -216,   -17,   172,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,   177,   178,   179,   101,  -216,  -216,  -216,
    -216,  -216,  -216,   180,   121,   156,   158,   -17,  -216,   160,
    -216,  -216,  -216,  -216,  -216
  };

  const unsigned char
  NetconfParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,     0,    29,     0,
      28,     0,     0,    22,    43,   130,   122,   124,   126,   128,
       0,    42,     0,    34,    36,    38,    39,    40,    41,    37,
      52,    54,     0,    56,    51,     0,    45,    49,    50,    48,
      47,    26,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,    31,     0,    33,     0,     0,     0,     0,     0,
       9,    30,    23,     0,     0,     0,     0,     0,     0,     0,
      35,     0,     0,    73,     0,    46,     0,     0,     0,   123,
     125,   127,   129,    20,    53,    55,    75,    58,    24,     0,
     135,     0,   132,   134,    84,    86,    88,    90,    83,     0,
      76,    77,    79,    80,    81,    82,    62,     0,    59,    60,
      44,     0,     0,   131,     0,     0,     0,     0,    74,     0,
       0,    57,     0,     0,   133,     0,     0,     0,     0,    78,
      69,    71,    66,     0,    64,    67,    68,    61,     0,     0,
       0,     0,     0,     0,     0,     0,    63,   139,     0,   137,
      99,   101,    98,    96,    97,     0,    92,    94,    95,     0,
       0,     0,     0,     0,    65,     0,     0,   136,     0,     0,
       0,    85,    87,    89,    91,    70,    72,   117,   153,     0,
     151,   149,   147,   148,   143,     0,   141,   145,   146,   144,
     138,     0,     0,    93,     0,     0,     0,     0,     0,   140,
     100,     0,     0,     0,   150,     0,   142,   112,   119,     0,
     111,   109,   110,     0,   103,   105,   106,   107,   108,   118,
       0,   152,     0,     0,     0,     0,   102,   157,     0,   155,
       0,     0,   121,   104,     0,     0,   154,   114,   115,   116,
     113,   120,   165,     0,     0,     0,     0,   159,   161,   162,
     163,   164,   156,     0,     0,     0,     0,     0,   158,     0,
     167,   168,   169,   160,   166
  };

  const short int
  NetconfParser::yypgoto_[] =
  {
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,   -20,    96,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,   -26,  -216,
    -216,  -216,   112,  -216,  -216,    78,   110,   -25,  -216,   -24,
    -216,  -216,  -216,  -216,  -216,    48,  -216,  -216,    33,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,    63,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,   -37,     1,  -216,  -216,
    -216,  -216,  -216,   -44,  -216,  -216,  -216,  -215,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,    75,  -216,  -216,  -216,    18,  -216,  -216,
     -10,  -216,  -216,  -216,  -216,  -216,  -216,   -46,  -216,  -216,
     -67,  -216,  -216,  -216,  -216,  -216
  };

  const short int
  NetconfParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,   104,    32,    33,    19,    24,    29,    30,   172,    21,
      26,    42,    43,    44,    66,    55,    56,   173,    75,   174,
      76,    59,    78,   127,   128,   129,   140,   153,   154,   155,
     163,   156,   164,    60,   106,   119,   120,   121,   122,   134,
     123,   135,   124,   136,   125,   137,   175,   176,   177,   188,
     178,   189,   233,   234,   235,   242,   260,   204,   214,   237,
     243,   238,    45,    68,    46,    69,    47,    70,    48,    71,
      49,    67,   111,   112,   113,   131,   168,   169,   185,   205,
     206,   207,   208,   217,   209,   215,   248,   249,   254,   266,
     267,   268,   273,   269,   270,   271
  };

  const unsigned short int
  NetconfParser::yytable_[] =
  {
      41,    54,    57,    58,    28,    34,   236,     9,     8,    10,
      20,    11,   114,   115,   116,   117,   262,   150,   151,   263,
     264,   265,    50,    51,    52,    35,    73,   150,   151,   186,
     236,    74,   187,    31,    36,    37,    38,    39,    53,    50,
      51,    40,    81,    82,    40,    40,    22,    41,    12,    13,
      14,    15,   197,    54,    57,    58,    79,    40,    61,    79,
     198,    80,   199,   200,   130,   132,    99,   100,   101,   102,
     133,    54,    57,    58,    40,    62,   108,    50,    51,   165,
     118,    50,    51,    63,   166,    64,   227,    65,   170,   171,
     197,   228,   229,   190,   190,   190,   190,   218,   191,   192,
     193,   194,   219,   245,   277,    83,    72,   255,   246,   278,
     256,    77,    40,   118,   152,    84,    40,     1,     2,     3,
     257,   258,   259,   179,   180,   181,    85,    86,    87,    88,
      89,    91,    92,   105,    94,    96,    93,   110,   139,    97,
      98,    10,   107,   126,   142,   141,   138,   143,   145,   146,
     147,   148,   224,   158,   195,   220,   159,   160,   161,   201,
     202,   203,   162,   196,   167,   182,   183,   211,   212,   216,
     280,   222,   223,   221,   225,   109,   240,   244,   250,   247,
     251,   274,   275,   276,   279,    90,   239,   103,   241,    95,
     157,   213,   201,   202,   203,   230,   231,   232,   184,   252,
     261,   253,   149,   281,   210,   282,   284,   144,   226,   272,
     283,     0,     0,     0,     0,     0,     0,     0,     0,   230,
     231,   232
  };

  const short int
  NetconfParser::yycheck_[] =
  {
      26,    27,    27,    27,    24,    10,   221,     5,     0,     7,
       7,     9,    14,    15,    16,    17,    33,    28,    29,    36,
      37,    38,    11,    12,    13,    30,     3,    28,    29,     3,
     245,     8,     6,    46,    39,    40,    41,    42,    27,    11,
      12,    46,    62,    63,    46,    46,     7,    73,    46,    47,
      48,    49,    24,    79,    79,    79,     3,    46,     6,     3,
      32,     8,    34,    35,     8,     3,    86,    87,    88,    89,
       8,    97,    97,    97,    46,     3,    96,    11,    12,     3,
     106,    11,    12,     4,     8,     8,    20,     3,    18,    19,
      24,    25,    26,     3,     3,     3,     3,     3,     8,     8,
       8,     8,     8,     3,     3,    46,     4,     3,     8,     8,
       6,     4,    46,   139,   140,     4,    46,    43,    44,    45,
      21,    22,    23,   160,   161,   162,     4,     4,     4,     4,
       4,     4,     4,    46,     4,     4,     7,    31,     3,     7,
       7,     7,     5,     7,     3,     6,     8,     4,     4,     4,
       4,     4,    47,     5,    46,    46,     7,     7,     7,   185,
     185,   185,     7,   183,     7,     4,     4,     4,     4,     4,
      49,     4,     4,     7,     4,    97,     5,     4,     4,     7,
       4,     4,     4,     4,     4,    73,    46,    91,    46,    79,
     142,   190,   218,   218,   218,   221,   221,   221,   165,    47,
      46,   245,   139,    47,   186,    47,    46,   132,   218,   255,
     277,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,
     245,   245
  };

  const unsigned char
  NetconfParser::yystos_[] =
  {
       0,    43,    44,    45,    51,    52,    53,    54,     0,     5,
       7,     9,    46,    47,    48,    49,    57,    58,    59,    64,
       7,    69,     7,    55,    65,    60,    70,    56,    58,    66,
      67,    46,    62,    63,    10,    30,    39,    40,    41,    42,
      46,    68,    71,    72,    73,   122,   124,   126,   128,   130,
      11,    12,    13,    27,    68,    75,    76,    77,    79,    81,
      93,     6,     3,     4,     8,     3,    74,   131,   123,   125,
     127,   129,     4,     3,     8,    78,    80,     4,    82,     3,
       8,    58,    58,    46,     4,     4,     4,     4,     4,     4,
      72,     4,     4,     7,     4,    76,     4,     7,     7,    58,
      58,    58,    58,    59,    61,    46,    94,     5,    58,    75,
      31,   132,   133,   134,    14,    15,    16,    17,    68,    95,
      96,    97,    98,   100,   102,   104,     7,    83,    84,    85,
       8,   135,     3,     8,    99,   101,   103,   105,     8,     3,
      86,     6,     3,     4,   133,     4,     4,     4,     4,    97,
      28,    29,    68,    87,    88,    89,    91,    85,     5,     7,
       7,     7,     7,    90,    92,     3,     8,     7,   136,   137,
      18,    19,    68,    77,    79,   106,   107,   108,   110,   106,
     106,   106,     4,     4,    88,   138,     3,     6,   109,   111,
       3,     8,     8,     8,     8,    46,    58,    24,    32,    34,
      35,    68,    77,    79,   117,   139,   140,   141,   142,   144,
     137,     4,     4,   107,   118,   145,     4,   143,     3,     8,
      46,     7,     4,     4,    47,     4,   140,    20,    25,    26,
      68,    77,    79,   112,   113,   114,   117,   119,   121,    46,
       5,    46,   115,   120,     4,     3,     8,     7,   146,   147,
       4,     4,    47,   113,   148,     3,     6,    21,    22,    23,
     116,    46,    33,    36,    37,    38,   149,   150,   151,   153,
     154,   155,   147,   152,     4,     4,     4,     3,     8,     4,
      49,    47,    47,   150,    46
  };

  const unsigned char
  NetconfParser::yyr1_[] =
  {
       0,    50,    52,    51,    53,    51,    54,    51,    56,    55,
      57,    58,    58,    58,    58,    58,    58,    58,    60,    59,
      61,    62,    62,    63,    63,    65,    64,    66,    66,    67,
      67,    68,    70,    69,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    74,    73,    75,    75,    76,    76,    76,
      76,    76,    78,    77,    80,    79,    82,    81,    83,    83,
      84,    84,    86,    85,    87,    87,    87,    88,    88,    90,
      89,    92,    91,    94,    93,    95,    95,    96,    96,    97,
      97,    97,    97,    97,    99,    98,   101,   100,   103,   102,
     105,   104,   106,   106,   107,   107,   107,   107,   107,   109,
     108,   111,   110,   112,   112,   113,   113,   113,   113,   113,
     113,   113,   115,   114,   116,   116,   116,   118,   117,   120,
     119,   121,   123,   122,   125,   124,   127,   126,   129,   128,
     131,   130,   132,   132,   133,   135,   134,   136,   136,   138,
     137,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     141,   143,   142,   145,   144,   146,   146,   148,   147,   149,
     149,   150,   150,   150,   150,   152,   151,   153,   154,   155
  };

  const unsigned char
  NetconfParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     0,     6,     0,     6,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     0,     4,     0,
       4,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const NetconfParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Netconf\"", "\"user-context\"",
  "\"comment\"", "\"managed-servers\"", "\"dhcp4\"", "\"dhcp6\"", "\"d2\"",
  "\"ca\"", "\"model\"", "\"control-socket\"", "\"type\"", "\"unix\"",
  "\"http\"", "\"stdout\"", "\"name\"", "\"host\"", "\"port\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"", "START_JSON",
  "START_NETCONF", "START_SUB_NETCONF", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "sub_netconf", "$@4", "json", "value", "map", "$@5",
  "map_value", "map_content", "not_empty_map", "list_generic", "$@6",
  "list_content", "not_empty_list", "unknown_map_entry",
  "netconf_syntax_map", "$@7", "global_objects", "global_object",
  "netconf_object", "$@8", "global_params", "global_param", "user_context",
  "$@9", "comment", "$@10", "hooks_libraries", "$@11",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@12", "hooks_params", "hooks_param", "library",
  "$@13", "parameters", "$@14", "managed_servers", "$@15",
  "servers_entries", "not_empty_servers_entries", "server_entry",
  "dhcp4_server", "$@16", "dhcp6_server", "$@17", "d2_server", "$@18",
  "ca_server", "$@19", "managed_server_params", "managed_server_param",
  "model", "$@20", "control_socket", "$@21", "control_socket_params",
  "control_socket_param", "socket_type", "$@22", "socket_type_value",
  "name", "$@23", "host", "$@24", "port", "dhcp4_json_object", "$@25",
  "dhcp6_json_object", "$@26", "dhcpddns_json_object", "$@27",
  "control_agent_object", "$@28", "logging_object", "$@29",
  "logging_params", "logging_param", "loggers", "$@30", "loggers_entries",
  "logger_entry", "$@31", "logger_params", "logger_param", "debuglevel",
  "severity", "$@32", "output_options_list", "$@33",
  "output_options_list_content", "output_entry", "$@34",
  "output_params_list", "output_params", "output", "$@35", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if NETCONF_DEBUG
  const unsigned short int
  NetconfParser::yyrline_[] =
  {
       0,   119,   119,   119,   120,   120,   121,   121,   129,   129,
     140,   146,   147,   148,   149,   150,   151,   152,   156,   156,
     167,   172,   173,   181,   185,   192,   192,   198,   199,   202,
     206,   219,   228,   228,   240,   241,   245,   246,   247,   248,
     249,   250,   251,   255,   255,   272,   273,   278,   279,   280,
     281,   282,   285,   285,   310,   310,   338,   338,   348,   349,
     352,   353,   356,   356,   364,   365,   366,   369,   370,   373,
     373,   381,   381,   391,   391,   401,   402,   405,   406,   412,
     413,   414,   415,   416,   420,   420,   431,   431,   442,   442,
     453,   453,   464,   465,   469,   470,   471,   472,   473,   477,
     477,   486,   486,   497,   498,   501,   502,   503,   504,   505,
     506,   507,   510,   510,   518,   519,   520,   523,   523,   532,
     532,   541,   549,   549,   556,   556,   563,   563,   570,   570,
     583,   583,   596,   597,   601,   605,   605,   617,   618,   622,
     622,   630,   631,   634,   635,   636,   637,   638,   639,   640,
     643,   648,   648,   656,   656,   666,   667,   670,   670,   678,
     679,   682,   683,   684,   685,   688,   688,   696,   701,   706
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


#line 14 "netconf_parser.yy" // lalr1.cc:1163
} } // isc::netconf
#line 2073 "netconf_parser.cc" // lalr1.cc:1163
#line 711 "netconf_parser.yy" // lalr1.cc:1164


void
isc::netconf::NetconfParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
