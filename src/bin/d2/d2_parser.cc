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
#define yylex   d2_parser_lex

// First part of user declarations.

#line 39 "d2_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "d2_parser.h"

// User implementation prologue.

#line 53 "d2_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "d2_parser.yy" // lalr1.cc:413

#include <d2/parser_context.h>

#line 59 "d2_parser.cc" // lalr1.cc:413


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
#if D2_PARSER_DEBUG

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

#else // !D2_PARSER_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !D2_PARSER_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "d2_parser.yy" // lalr1.cc:479
namespace isc { namespace d2 {
#line 145 "d2_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  D2Parser::yytnamerr_ (const char *yystr)
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
  D2Parser::D2Parser (isc::d2::D2ParserContext& ctx_yyarg)
    :
#if D2_PARSER_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  D2Parser::~D2Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  D2Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  D2Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  D2Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  D2Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  D2Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  D2Parser::symbol_number_type
  D2Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  D2Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  D2Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 43: // value
      case 70: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 37: // "boolean"
        value.move< bool > (that.value);
        break;

      case 36: // "floating point"
        value.move< double > (that.value);
        break;

      case 35: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 34: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  D2Parser::stack_symbol_type&
  D2Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 43: // value
      case 70: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 37: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 36: // "floating point"
        value.copy< double > (that.value);
        break;

      case 35: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 34: // "constant string"
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
  D2Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if D2_PARSER_DEBUG
  template <typename Base>
  void
  D2Parser::yy_print_ (std::ostream& yyo,
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
            case 34: // "constant string"

#line 91 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "d2_parser.cc" // lalr1.cc:636
        break;

      case 35: // "integer"

#line 91 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "d2_parser.cc" // lalr1.cc:636
        break;

      case 36: // "floating point"

#line 91 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "d2_parser.cc" // lalr1.cc:636
        break;

      case 37: // "boolean"

#line 91 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "d2_parser.cc" // lalr1.cc:636
        break;

      case 43: // value

#line 91 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "d2_parser.cc" // lalr1.cc:636
        break;

      case 70: // ncr_protocol_value

#line 91 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 389 "d2_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  D2Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  D2Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  D2Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if D2_PARSER_DEBUG
  std::ostream&
  D2Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  D2Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  D2Parser::debug_level_type
  D2Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  D2Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // D2_PARSER_DEBUG

  inline D2Parser::state_type
  D2Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  D2Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  D2Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  D2Parser::parse ()
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
      case 43: // value
      case 70: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 37: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 36: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 35: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 34: // "constant string"
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
#line 100 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "d2_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 101 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "d2_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 102 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 642 "d2_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 110 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 648 "d2_parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 111 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 654 "d2_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 112 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 660 "d2_parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 113 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 666 "d2_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 114 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 672 "d2_parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 115 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 678 "d2_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 116 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 684 "d2_parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 119 "d2_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 693 "d2_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 124 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 704 "d2_parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 129 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 714 "d2_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 140 "d2_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 723 "d2_parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 144 "d2_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 733 "d2_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 151 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 742 "d2_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 154 "d2_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 750 "d2_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 170 "d2_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 759 "d2_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 174 "d2_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 768 "d2_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 185 "d2_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 779 "d2_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 195 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 790 "d2_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 200 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 800 "d2_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 221 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 811 "d2_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 226 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 820 "d2_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 231 "d2_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "d2_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 235 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 838 "d2_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 254 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 846 "d2_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 256 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 856 "d2_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 262 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () <= 0) {
        error(yystack_[0].location, "port must be greater than zero");
    } 
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 868 "d2_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 270 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else { 
        ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 881 "d2_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 279 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 889 "d2_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 281 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 898 "d2_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 287 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 904 "d2_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 288 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 910 "d2_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 291 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 918 "d2_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 293 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 928 "d2_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 299 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 936 "d2_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 301 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("forward-ddns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 945 "d2_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 306 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 953 "d2_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 308 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reverse-ddns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 962 "d2_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 313 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 970 "d2_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 315 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("tsig-keys", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 979 "d2_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 320 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 987 "d2_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 322 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 996 "d2_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 327 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1004 "d2_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 329 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1013 "d2_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 339 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1024 "d2_parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 344 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1033 "d2_parser.cc" // lalr1.cc:859
    break;

  case 78:
#line 361 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1044 "d2_parser.cc" // lalr1.cc:859
    break;

  case 79:
#line 366 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1053 "d2_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 378 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1063 "d2_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 382 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1071 "d2_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 397 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1079 "d2_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 399 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1089 "d2_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 405 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1098 "d2_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 409 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "d2_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 411 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1116 "d2_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 417 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1127 "d2_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 422 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1136 "d2_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 431 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1146 "d2_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 435 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1154 "d2_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 443 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1162 "d2_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 445 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1172 "d2_parser.cc" // lalr1.cc:859
    break;


#line 1176 "d2_parser.cc" // lalr1.cc:859
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
  D2Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  D2Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char D2Parser::yypact_ninf_ = -62;

  const signed char D2Parser::yytable_ninf_ = -1;

  const signed char
  D2Parser::yypact_[] =
  {
      25,   -62,   -62,   -62,     7,    -3,    16,    22,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,    -3,    -4,     1,     5,   -62,    30,
      45,    50,    51,    57,   -62,   -62,   -62,   -62,    58,   -62,
       0,   -62,   -62,   -62,   -62,   -62,   -62,    59,    60,   -62,
     -62,   -62,   -62,   -62,   -62,     2,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,    -3,    -3,   -62,    27,
      61,    62,    65,    66,   -62,     1,   -62,    67,    37,    38,
      70,    71,    72,    76,    78,     5,   -62,   -62,   -62,    79,
      -3,    -3,    77,    80,   -62,    52,   -62,   -62,    -2,    68,
      -3,    -3,    -3,   -62,    -3,   -62,   -62,     5,    64,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,     6,   -62,
      14,   -62,   -62,   -62,    81,    64,   -62,    85,   -62,    84,
     -62,    47,   -62,    11,    84,   -62,   -62,   -62,    88,   -62,
     -62,    39,   -62,   -62,   -62,   -62,   -62,   -62,    89,    90,
      63,    91,    11,   -62,    69,    92,   -62,    74,   -62,   -62,
      93,   -62,   -62,    49,   -62,    73,    93,   -62,   -62,    43,
     -62,   -62,    95,    73,   -62,    75,   -62,   -62
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    22,
      16,    12,    11,     8,     9,    10,    15,     3,    13,    14,
      29,     5,    40,     7,    24,    18,     0,     0,    26,     0,
      25,     0,     0,    19,    69,    71,    38,    73,     0,    37,
       0,    31,    36,    33,    35,    34,    53,     0,     0,    57,
      61,    63,    65,    67,    52,     0,    42,    44,    45,    46,
      47,    48,    49,    50,    51,    23,     0,     0,    17,     0,
       0,     0,     0,     0,    28,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    27,    20,     0,
       0,     0,     0,     0,    32,     0,    55,    56,     0,     0,
       0,     0,     0,    43,     0,    70,    72,     0,     0,    54,
      59,    60,    58,    62,    64,    66,    68,    21,     0,    78,
       0,    75,    77,    39,     0,     0,    74,     0,    76,     0,
      82,     0,    80,     0,     0,    79,    91,    96,     0,    94,
      90,     0,    84,    86,    88,    89,    87,    81,     0,     0,
       0,     0,     0,    83,     0,     0,    93,     0,    85,    92,
       0,    95,   100,     0,    98,     0,     0,    97,   104,     0,
     102,    99,     0,     0,   101,     0,   103,   105
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
     -62,   -62,   -62,   -62,   -62,   -23,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -26,   -62,   -62,   -62,    21,
     -62,   -62,   -62,   -62,    -5,    19,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -20,   -62,
     -62,   -62,   -28,   -62,   -62,   -42,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -55,   -62,   -62,   -61,   -62
  };

  const short int
  D2Parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    16,    17,    18,    25,    32,
      33,    19,    24,    29,    30,    54,    21,    26,    40,    41,
      42,    72,    23,    27,    55,    56,    57,    77,    58,    59,
      60,    80,   112,    61,    81,    62,    82,    63,    83,    64,
      84,    43,    70,    44,    71,    45,    73,   120,   121,   122,
     124,   131,   132,   133,   141,   142,   143,   148,   144,   145,
     151,   146,   149,   163,   164,   165,   169,   170,   172
  };

  const unsigned char
  D2Parser::yytable_[] =
  {
      39,    28,     9,    75,    10,    85,    11,     8,    76,    85,
      86,    34,    35,    36,   123,   110,   111,   125,    46,    47,
      48,    49,   126,    20,    50,    37,    51,    52,    53,    22,
      31,    12,    13,    14,    15,    38,    65,   136,   137,    38,
     138,   139,   152,    87,    88,    38,   173,   153,    66,    39,
     134,   174,   166,   135,    67,   167,     1,     2,     3,    68,
      69,    89,    74,    78,    79,    90,    91,   105,   106,    92,
      93,    95,    96,    97,    98,    99,   100,   114,   115,   116,
     101,   117,   102,   104,   107,   127,   109,   108,   113,   119,
     129,   130,   150,   154,   155,   157,    94,   160,   156,   175,
     162,   168,   118,   159,   103,   128,   147,   140,   161,   177,
     158,   171,   176,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   140
  };

  const short int
  D2Parser::yycheck_[] =
  {
      26,    24,     5,     3,     7,     3,     9,     0,     8,     3,
       8,    10,    11,    12,     8,    17,    18,     3,    13,    14,
      15,    16,     8,     7,    19,    24,    21,    22,    23,     7,
      34,    34,    35,    36,    37,    34,     6,    26,    27,    34,
      29,    30,     3,    66,    67,    34,     3,     8,     3,    75,
       3,     8,     3,     6,     4,     6,    31,    32,    33,     8,
       3,    34,     4,     4,     4,     4,     4,    90,    91,     4,
       4,     4,    35,    35,     4,     4,     4,   100,   101,   102,
       4,   104,     4,     4,     7,     4,    34,     7,    20,    25,
       5,     7,     4,     4,     4,     4,    75,     5,    35,     4,
       7,    28,   107,    34,    85,   125,   134,   133,    34,    34,
     152,   166,   173,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   152
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    31,    32,    33,    39,    40,    41,    42,     0,     5,
       7,     9,    34,    35,    36,    37,    43,    44,    45,    49,
       7,    54,     7,    60,    50,    46,    55,    61,    43,    51,
      52,    34,    47,    48,    10,    11,    12,    24,    34,    53,
      56,    57,    58,    79,    81,    83,    13,    14,    15,    16,
      19,    21,    22,    23,    53,    62,    63,    64,    66,    67,
      68,    71,    73,    75,    77,     6,     3,     4,     8,     3,
      80,    82,    59,    84,     4,     3,     8,    65,     4,     4,
      69,    72,    74,    76,    78,     3,     8,    43,    43,    34,
       4,     4,     4,     4,    57,     4,    35,    35,     4,     4,
       4,     4,     4,    63,     4,    43,    43,     7,     7,    34,
      17,    18,    70,    20,    43,    43,    43,    43,    62,    25,
      85,    86,    87,     8,    88,     3,     8,     4,    86,     5,
       7,    89,    90,    91,     3,     6,    26,    27,    29,    30,
      53,    92,    93,    94,    96,    97,    99,    90,    95,   100,
       4,    98,     3,     8,     4,     4,    35,     4,    93,    34,
       5,    34,     7,   101,   102,   103,     3,     6,    28,   104,
     105,   102,   106,     3,     8,     4,   105,    34
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    38,    40,    39,    41,    39,    42,    39,    43,    43,
      43,    43,    43,    43,    43,    44,    46,    45,    47,    47,
      48,    48,    50,    49,    51,    51,    52,    52,    53,    55,
      54,    56,    56,    57,    57,    57,    57,    57,    59,    58,
      61,    60,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    65,    64,    66,    67,    69,    68,    70,
      70,    72,    71,    74,    73,    76,    75,    78,    77,    80,
      79,    82,    81,    84,    83,    85,    85,    86,    88,    87,
      89,    89,    91,    90,    92,    92,    93,    93,    93,    93,
      93,    95,    94,    96,    98,    97,   100,    99,   101,   101,
     103,   102,   104,   104,   106,   105
  };

  const unsigned char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     1,
       3,     5,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const D2Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"Dhcp4\"",
  "\"DhcpDdns\"", "\"ip-address\"", "\"port\"", "\"dns-server-timeout\"",
  "\"ncr-protocol\"", "\"UDP\"", "\"TCP\"", "\"ncr-format\"", "\"JSON\"",
  "\"forward-ddns\"", "\"reverse-ddns\"", "\"tsig-keys\"", "\"Logging\"",
  "\"loggers\"", "\"name\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCPDDNS",
  "SUB_DHCPDDNS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "value", "sub_json", "map2", "$@4", "map_content",
  "not_empty_map", "list_generic", "$@5", "list_content", "not_empty_list",
  "unknown_map_entry", "syntax_map", "$@6", "global_objects",
  "global_object", "dhcpddns_object", "$@7", "sub_dhcpddns", "$@8",
  "dhcpddns_params", "dhcpddns_param", "ip_address", "$@9", "port",
  "dns_server_timeout", "ncr_protocol", "$@10", "ncr_protocol_value",
  "ncr_format", "$@11", "forward_ddns", "$@12", "reverse_ddns", "$@13",
  "tsig_keys", "$@14", "dhcp6_json_object", "$@15", "dhcp4_json_object",
  "$@16", "logging_object", "$@17", "logging_params", "logging_param",
  "loggers", "$@18", "loggers_entries", "logger_entry", "$@19",
  "logger_params", "logger_param", "name", "$@20", "debuglevel",
  "severity", "$@21", "output_options_list", "$@22",
  "output_options_list_content", "output_entry", "$@23", "output_params",
  "output_param", "$@24", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short int
  D2Parser::yyrline_[] =
  {
       0,   100,   100,   100,   101,   101,   102,   102,   110,   111,
     112,   113,   114,   115,   116,   119,   124,   124,   136,   137,
     140,   144,   151,   151,   166,   167,   170,   174,   185,   195,
     195,   207,   208,   212,   213,   214,   215,   216,   221,   221,
     231,   231,   239,   240,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   254,   254,   262,   270,   279,   279,   287,
     288,   291,   291,   299,   299,   306,   306,   313,   313,   320,
     320,   327,   327,   339,   339,   352,   353,   357,   361,   361,
     373,   374,   378,   378,   386,   387,   390,   391,   392,   393,
     394,   397,   397,   405,   409,   409,   417,   417,   427,   428,
     431,   431,   439,   440,   443,   443
  };

  // Print the state stack on the debug stream.
  void
  D2Parser::yystack_print_ ()
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
  D2Parser::yy_reduce_print_ (int yyrule)
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
#endif // D2_PARSER_DEBUG


#line 14 "d2_parser.yy" // lalr1.cc:1167
} } // isc::d2
#line 1677 "d2_parser.cc" // lalr1.cc:1167
#line 451 "d2_parser.yy" // lalr1.cc:1168


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
