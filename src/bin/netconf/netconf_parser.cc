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
      case 54: // value
      case 57: // map_value
      case 113: // socket_type_value
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

  }

  NetconfParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    switch (that.type_get ())
    {
      case 54: // value
      case 57: // map_value
      case 113: // socket_type_value
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

    // that is emptied.
    that.type = empty_symbol;
  }

  NetconfParser::stack_symbol_type&
  NetconfParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 54: // value
      case 57: // map_value
      case 113: // socket_type_value
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
            case 42: // "constant string"

#line 103 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< std::string > (); }
#line 378 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 43: // "integer"

#line 103 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 385 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 44: // "floating point"

#line 103 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< double > (); }
#line 392 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 45: // "boolean"

#line 103 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< bool > (); }
#line 399 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 54: // value

#line 103 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 57: // map_value

#line 103 "netconf_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "netconf_parser.cc" // lalr1.cc:635
        break;

      case 113: // socket_type_value

#line 103 "netconf_parser.yy" // lalr1.cc:635
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
      case 54: // value
      case 57: // map_value
      case 113: // socket_type_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 45: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 44: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 43: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 42: // "constant string"
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
#line 114 "netconf_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 660 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 115 "netconf_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.CONFIG; }
#line 666 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 116 "netconf_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.NETCONF; }
#line 672 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 124 "netconf_parser.yy" // lalr1.cc:856
    {
    // Parse the Control-netconf map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 682 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 9:
#line 128 "netconf_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 690 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 135 "netconf_parser.yy" // lalr1.cc:856
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 699 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 11:
#line 141 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 705 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 142 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 711 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 13:
#line 143 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 717 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 14:
#line 144 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 723 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 15:
#line 145 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 729 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 16:
#line 146 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 735 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 17:
#line 147 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 741 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 18:
#line 151 "netconf_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 752 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 19:
#line 156 "netconf_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 762 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 20:
#line 162 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 768 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 23:
#line 176 "netconf_parser.yy" // lalr1.cc:856
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 777 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 24:
#line 180 "netconf_parser.yy" // lalr1.cc:856
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 787 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 25:
#line 187 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 796 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 26:
#line 190 "netconf_parser.yy" // lalr1.cc:856
    {
}
#line 803 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 29:
#line 197 "netconf_parser.yy" // lalr1.cc:856
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 812 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 30:
#line 201 "netconf_parser.yy" // lalr1.cc:856
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 821 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 31:
#line 214 "netconf_parser.yy" // lalr1.cc:856
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 832 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 32:
#line 222 "netconf_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 843 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 33:
#line 227 "netconf_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 853 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 38:
#line 244 "netconf_parser.yy" // lalr1.cc:856
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

  case 39:
#line 254 "netconf_parser.yy" // lalr1.cc:856
    {
    // Ok, we're done with parsing control-netconf. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 880 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 49:
#line 278 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 888 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 50:
#line 280 "netconf_parser.yy" // lalr1.cc:856
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

  case 51:
#line 303 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 923 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 52:
#line 305 "netconf_parser.yy" // lalr1.cc:856
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

  case 53:
#line 331 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 963 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 54:
#line 336 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 972 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 59:
#line 349 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 982 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 60:
#line 353 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 990 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 66:
#line 366 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 998 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 67:
#line 368 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1008 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 68:
#line 374 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1016 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 69:
#line 376 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1025 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 70:
#line 384 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("managed-servers", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.MANAGED_SERVERS);
}
#line 1036 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 71:
#line 389 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1045 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 81:
#line 413 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1056 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 82:
#line 418 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1065 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 83:
#line 424 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1076 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 84:
#line 429 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1085 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 85:
#line 435 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1096 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 86:
#line 440 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1105 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 87:
#line 446 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ca", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1116 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 88:
#line 451 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1125 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 96:
#line 470 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1133 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 97:
#line 472 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr model(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("model", model);
    ctx.leave();
}
#line 1143 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 98:
#line 479 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1154 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 99:
#line 484 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1163 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 108:
#line 502 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1171 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 109:
#line 504 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1180 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 110:
#line 510 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1186 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 111:
#line 511 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1192 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 112:
#line 512 "netconf_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("stdout", ctx.loc2pos(yystack_[0].location))); }
#line 1198 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 113:
#line 515 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1206 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 114:
#line 517 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1216 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 115:
#line 524 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1224 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 116:
#line 526 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr url(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-url", url);
    ctx.leave();
}
#line 1234 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 117:
#line 539 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1245 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 118:
#line 544 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1254 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 122:
#line 561 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1265 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 123:
#line 566 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1274 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 126:
#line 578 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1284 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 127:
#line 582 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1292 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 137:
#line 599 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1300 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 138:
#line 601 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1310 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 139:
#line 607 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1319 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 140:
#line 612 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1327 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 141:
#line 614 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1337 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 142:
#line 620 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1348 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 143:
#line 625 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1357 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 146:
#line 634 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1367 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 147:
#line 638 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 1375 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 154:
#line 652 "netconf_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1383 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 155:
#line 654 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1393 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 156:
#line 660 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1402 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 157:
#line 665 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1411 "netconf_parser.cc" // lalr1.cc:856
    break;

  case 158:
#line 670 "netconf_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1420 "netconf_parser.cc" // lalr1.cc:856
    break;


#line 1424 "netconf_parser.cc" // lalr1.cc:856
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


  const signed char NetconfParser::yypact_ninf_ = -73;

  const signed char NetconfParser::yytable_ninf_ = -1;

  const short int
  NetconfParser::yypact_[] =
  {
      55,   -73,   -73,   -73,    17,     2,     3,    31,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,     2,     6,    10,    11,   -73,    46,
      68,    86,    95,    88,   -73,   -73,     0,   -73,   -73,   -73,
     -73,   -73,   100,   -73,   101,   -73,    98,   104,   -73,   -73,
     -73,   -73,   -73,   -73,     2,     2,   -73,    66,   105,   106,
      10,   -73,   107,   108,   109,   110,   -73,   -73,    11,   -73,
     -73,   111,   112,   113,   -73,   114,    75,   -73,   117,   -73,
       2,    11,    93,   -73,   -73,   -73,    -2,   118,   -73,   116,
     -73,    13,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   119,
     115,   -73,   -73,   -73,   -73,   -73,   -73,   120,   125,   -73,
     -73,   126,    93,   -73,   127,   128,   129,   130,   -73,    -2,
      34,   -73,   118,   124,   -73,   134,   135,   137,   138,   -73,
     -73,   -73,   -73,    61,   -73,   -73,   -73,   -73,   139,    39,
      39,    39,    39,   131,   132,    57,   -73,   -73,    27,   -73,
     -73,   -73,   -73,   -73,   -73,    62,   -73,   -73,   -73,    69,
      70,    71,   121,     2,   -73,    -6,   139,   -73,   133,   143,
      39,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   144,
     -73,   -73,   -73,   -73,    72,   -73,   -73,   -73,   -73,   -73,
     -73,   122,   142,   -73,   146,   147,   123,   148,    -6,   -73,
     -73,     7,   136,   149,   -73,   140,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,    79,   -73,   -73,   -73,   -73,   -73,   150,
     -73,   151,   152,   154,     7,   -73,   -73,    83,   -73,    76,
     141,   145,   -73,    30,   150,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   155,   156,   157,    80,   -73,   -73,   -73,
     -73,   -73,   -73,   158,   159,   153,   160,    30,   -73,   163,
     -73,   -73,   -73,   -73,   -73
  };

  const unsigned char
  NetconfParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,    40,    29,     0,
      28,     0,     0,    22,    38,   117,     0,    34,    36,    37,
      49,    51,     0,    53,     0,    48,     0,    41,    42,    46,
      47,    45,    44,    26,     0,     0,    19,     0,     0,     0,
       0,    33,     0,     0,     0,     0,    31,     9,     0,    30,
      23,     0,     0,     0,    35,     0,     0,    70,     0,    43,
       0,    40,     0,    20,    50,    52,    72,    55,    24,     0,
     122,     0,   119,   121,    81,    83,    85,    87,    80,     0,
      73,    74,    76,    77,    78,    79,    59,     0,    56,    57,
      39,     0,     0,   118,     0,     0,     0,     0,    71,     0,
       0,    54,     0,     0,   120,     0,     0,     0,     0,    75,
      66,    68,    63,     0,    61,    64,    65,    58,     0,     0,
       0,     0,     0,     0,     0,     0,    60,   126,     0,   124,
      96,    98,    95,    93,    94,     0,    89,    91,    92,     0,
       0,     0,     0,     0,    62,     0,     0,   123,     0,     0,
       0,    82,    84,    86,    88,    67,    69,   137,   142,     0,
     140,   136,   134,   135,     0,   128,   130,   132,   133,   131,
     125,     0,     0,    90,     0,     0,     0,     0,     0,   127,
      97,     0,     0,     0,   139,     0,   129,   108,   113,   115,
     107,   105,   106,     0,   100,   102,   103,   104,   138,     0,
     141,     0,     0,     0,     0,    99,   146,     0,   144,     0,
       0,     0,   101,     0,     0,   143,   110,   111,   112,   109,
     114,   116,   154,     0,     0,     0,     0,   148,   150,   151,
     152,   153,   145,     0,     0,     0,     0,     0,   147,     0,
     156,   157,   158,   149,   155
  };

  const short int
  NetconfParser::yypgoto_[] =
  {
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -20,    38,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -27,   -73,
     -73,   -73,   161,   -73,   -73,    84,   -73,    85,   -26,   -73,
     -25,   -73,   -73,   -73,   -73,   -73,    45,   -73,   -73,    23,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,    50,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -40,     9,   -73,
     -73,   -73,   -73,   -73,   -54,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,    65,   -73,   -73,   -73,    14,
     -73,   -73,   -17,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -50,   -73,   -73,   -72,   -73,   -73,   -73,   -73,   -73
  };

  const short int
  NetconfParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    84,    32,    33,    19,    24,    29,    30,   152,    21,
      26,    36,    37,    38,    58,    46,    47,    48,   153,    62,
     154,    63,    51,    65,   107,   108,   109,   120,   133,   134,
     135,   143,   136,   144,    52,    86,    99,   100,   101,   102,
     114,   103,   115,   104,   116,   105,   117,   155,   156,   157,
     168,   158,   169,   213,   214,   215,   221,   239,   216,   222,
     217,   223,    39,    59,    91,    92,    93,   111,   148,   149,
     165,   184,   185,   186,   194,   187,   188,   197,   189,   195,
     227,   228,   233,   246,   247,   248,   253,   249,   250,   251
  };

  const unsigned short int
  NetconfParser::yytable_[] =
  {
      45,    49,    50,    60,    28,    40,    41,     9,    61,    10,
      20,    11,    94,    95,    96,    97,   112,     8,    40,    41,
      34,   113,    40,    41,    42,   177,   178,   207,   179,   180,
     166,   208,   209,   167,    69,    70,    44,    43,    22,    35,
      44,    45,    49,    50,    12,    13,    14,    15,    31,    44,
      40,    41,    53,    44,    45,    49,    50,   150,   151,    98,
      88,   130,   131,   242,   145,   170,   243,   244,   245,   146,
     171,    54,   170,   170,   170,   198,    44,   172,   173,   174,
     199,    44,   224,   257,   130,   131,   234,   225,   258,   235,
      55,    57,    98,   132,     1,     2,     3,   236,   237,   238,
     159,   160,   161,    56,    64,    66,    67,    68,    71,    72,
      73,    75,    76,    83,    78,    80,    77,    85,   119,    81,
      82,    10,    87,    90,   110,   106,   121,   118,   122,   138,
     123,   125,   126,   127,   128,   162,   163,   191,   181,   182,
     183,   139,   140,   176,   141,   142,   147,   192,   196,   201,
     202,   203,   205,    79,   219,   229,   230,   226,   231,   254,
     255,   256,   259,   175,   200,    89,   204,   137,   164,   129,
     232,   181,   182,   183,   210,   211,   212,   124,   218,   193,
     190,   206,   220,   240,   252,   263,     0,   241,     0,     0,
       0,     0,     0,     0,     0,     0,   261,   210,   211,   212,
       0,     0,     0,   262,   260,   264,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74
  };

  const short int
  NetconfParser::yycheck_[] =
  {
      27,    27,    27,     3,    24,    11,    12,     5,     8,     7,
       7,     9,    14,    15,    16,    17,     3,     0,    11,    12,
      10,     8,    11,    12,    13,    31,    32,    20,    34,    35,
       3,    24,    25,     6,    54,    55,    42,    26,     7,    29,
      42,    68,    68,    68,    42,    43,    44,    45,    42,    42,
      11,    12,     6,    42,    81,    81,    81,    18,    19,    86,
      80,    27,    28,    33,     3,     3,    36,    37,    38,     8,
       8,     3,     3,     3,     3,     3,    42,     8,     8,     8,
       8,    42,     3,     3,    27,    28,     3,     8,     8,     6,
       4,     3,   119,   120,    39,    40,    41,    21,    22,    23,
     140,   141,   142,     8,     4,     4,     8,     3,    42,     4,
       4,     4,     4,    75,     4,     4,     7,    42,     3,     7,
       7,     7,     5,    30,     8,     7,     6,     8,     3,     5,
       4,     4,     4,     4,     4,     4,     4,     4,   165,   165,
     165,     7,     7,   163,     7,     7,     7,     4,     4,     7,
       4,     4,     4,    68,     5,     4,     4,     7,     4,     4,
       4,     4,     4,    42,    42,    81,    43,   122,   145,   119,
     224,   198,   198,   198,   201,   201,   201,   112,    42,   170,
     166,   198,    42,    42,   234,   257,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,   224,   224,   224,
      -1,    -1,    -1,    43,    45,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60
  };

  const unsigned char
  NetconfParser::yystos_[] =
  {
       0,    39,    40,    41,    47,    48,    49,    50,     0,     5,
       7,     9,    42,    43,    44,    45,    53,    54,    55,    60,
       7,    65,     7,    51,    61,    56,    66,    52,    54,    62,
      63,    42,    58,    59,    10,    29,    67,    68,    69,   118,
      11,    12,    13,    26,    42,    64,    71,    72,    73,    74,
      76,    78,    90,     6,     3,     4,     8,     3,    70,   119,
       3,     8,    75,    77,     4,    79,     4,     8,     3,    54,
      54,    42,     4,     4,    68,     4,     4,     7,     4,    73,
       4,     7,     7,    55,    57,    42,    91,     5,    54,    71,
      30,   120,   121,   122,    14,    15,    16,    17,    64,    92,
      93,    94,    95,    97,    99,   101,     7,    80,    81,    82,
       8,   123,     3,     8,    96,    98,   100,   102,     8,     3,
      83,     6,     3,     4,   121,     4,     4,     4,     4,    94,
      27,    28,    64,    84,    85,    86,    88,    82,     5,     7,
       7,     7,     7,    87,    89,     3,     8,     7,   124,   125,
      18,    19,    64,    74,    76,   103,   104,   105,   107,   103,
     103,   103,     4,     4,    85,   126,     3,     6,   106,   108,
       3,     8,     8,     8,     8,    42,    54,    31,    32,    34,
      35,    64,    74,    76,   127,   128,   129,   131,   132,   134,
     125,     4,     4,   104,   130,   135,     4,   133,     3,     8,
      42,     7,     4,     4,    43,     4,   128,    20,    24,    25,
      64,    74,    76,   109,   110,   111,   114,   116,    42,     5,
      42,   112,   115,   117,     3,     8,     7,   136,   137,     4,
       4,     4,   110,   138,     3,     6,    21,    22,    23,   113,
      42,    42,    33,    36,    37,    38,   139,   140,   141,   143,
     144,   145,   137,   142,     4,     4,     4,     3,     8,     4,
      45,    43,    43,   140,    42
  };

  const unsigned char
  NetconfParser::yyr1_[] =
  {
       0,    46,    48,    47,    49,    47,    50,    47,    52,    51,
      53,    54,    54,    54,    54,    54,    54,    54,    56,    55,
      57,    58,    58,    59,    59,    61,    60,    62,    62,    63,
      63,    64,    66,    65,    67,    67,    68,    68,    70,    69,
      71,    71,    72,    72,    73,    73,    73,    73,    73,    75,
      74,    77,    76,    79,    78,    80,    80,    81,    81,    83,
      82,    84,    84,    84,    85,    85,    87,    86,    89,    88,
      91,    90,    92,    92,    93,    93,    94,    94,    94,    94,
      94,    96,    95,    98,    97,   100,    99,   102,   101,   103,
     103,   104,   104,   104,   104,   104,   106,   105,   108,   107,
     109,   109,   110,   110,   110,   110,   110,   110,   112,   111,
     113,   113,   113,   115,   114,   117,   116,   119,   118,   120,
     120,   121,   123,   122,   124,   124,   126,   125,   127,   127,
     128,   128,   128,   128,   128,   128,   128,   130,   129,   131,
     133,   132,   135,   134,   136,   136,   138,   137,   139,   139,
     140,   140,   140,   140,   142,   141,   143,   144,   145
  };

  const unsigned char
  NetconfParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     0,     6,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     0,     6,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     0,     6,
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
  "\"comment\"", "\"managed-servers\"", "\"dhcp4\"", "\"dhcp6\"", "\"d2\"",
  "\"ca\"", "\"model\"", "\"control-socket\"", "\"socket-type\"",
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
  "maxsize", "maxver", YY_NULLPTR
  };

#if NETCONF_DEBUG
  const unsigned short int
  NetconfParser::yyrline_[] =
  {
       0,   114,   114,   114,   115,   115,   116,   116,   124,   124,
     135,   141,   142,   143,   144,   145,   146,   147,   151,   151,
     162,   167,   168,   176,   180,   187,   187,   193,   194,   197,
     201,   214,   222,   222,   234,   235,   239,   240,   244,   244,
     261,   262,   265,   266,   271,   272,   273,   274,   275,   278,
     278,   303,   303,   331,   331,   341,   342,   345,   346,   349,
     349,   357,   358,   359,   362,   363,   366,   366,   374,   374,
     384,   384,   394,   395,   398,   399,   405,   406,   407,   408,
     409,   413,   413,   424,   424,   435,   435,   446,   446,   457,
     458,   462,   463,   464,   465,   466,   470,   470,   479,   479,
     490,   491,   494,   495,   496,   497,   498,   499,   502,   502,
     510,   511,   512,   515,   515,   524,   524,   539,   539,   552,
     553,   557,   561,   561,   573,   574,   578,   578,   586,   587,
     590,   591,   592,   593,   594,   595,   596,   599,   599,   607,
     612,   612,   620,   620,   630,   631,   634,   634,   642,   643,
     646,   647,   648,   649,   652,   652,   660,   665,   670
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
#line 2001 "netconf_parser.cc" // lalr1.cc:1163
#line 675 "netconf_parser.yy" // lalr1.cc:1164


void
isc::netconf::NetconfParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
