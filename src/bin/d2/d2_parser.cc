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
      case 50: // value
      case 77: // ncr_protocol_value
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
      case 50: // value
      case 77: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 44: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 43: // "floating point"
        value.copy< double > (that.value);
        break;

      case 42: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 41: // "constant string"
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
            case 41: // "constant string"

#line 98 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "d2_parser.cc" // lalr1.cc:636
        break;

      case 42: // "integer"

#line 98 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "d2_parser.cc" // lalr1.cc:636
        break;

      case 43: // "floating point"

#line 98 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "d2_parser.cc" // lalr1.cc:636
        break;

      case 44: // "boolean"

#line 98 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "d2_parser.cc" // lalr1.cc:636
        break;

      case 50: // value

#line 98 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "d2_parser.cc" // lalr1.cc:636
        break;

      case 77: // ncr_protocol_value

#line 98 "d2_parser.yy" // lalr1.cc:636
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
      case 50: // value
      case 77: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 44: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 43: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 42: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 41: // "constant string"
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
#line 107 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "d2_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 108 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "d2_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 109 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 642 "d2_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 117 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 648 "d2_parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 118 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 654 "d2_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 119 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 660 "d2_parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 120 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 666 "d2_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 121 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 672 "d2_parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 122 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 678 "d2_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 123 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 684 "d2_parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 126 "d2_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 693 "d2_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 131 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 704 "d2_parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 136 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 714 "d2_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 147 "d2_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 723 "d2_parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 151 "d2_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 733 "d2_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 158 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 742 "d2_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 161 "d2_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 750 "d2_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 169 "d2_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 759 "d2_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 173 "d2_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 768 "d2_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 184 "d2_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 779 "d2_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 194 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 790 "d2_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 199 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 800 "d2_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 220 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 811 "d2_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 225 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 820 "d2_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 230 "d2_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "d2_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 234 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 838 "d2_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 253 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 846 "d2_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 255 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 856 "d2_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 261 "d2_parser.yy" // lalr1.cc:859
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
#line 269 "d2_parser.yy" // lalr1.cc:859
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
#line 278 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 889 "d2_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 280 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 898 "d2_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 286 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 904 "d2_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 287 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 910 "d2_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 290 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 918 "d2_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 292 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 928 "d2_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 298 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 939 "d2_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 303 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 948 "d2_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 308 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 959 "d2_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 313 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 968 "d2_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 333 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 979 "d2_parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 338 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 988 "d2_parser.cc" // lalr1.cc:859
    break;

  case 79:
#line 351 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 998 "d2_parser.cc" // lalr1.cc:859
    break;

  case 80:
#line 355 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1006 "d2_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 370 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1014 "d2_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 372 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "name cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1028 "d2_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 382 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1036 "d2_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 384 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "key-name cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1050 "d2_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 397 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1061 "d2_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 402 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1070 "d2_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 415 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1080 "d2_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 419 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1088 "d2_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 433 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1096 "d2_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 435 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "hostname cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1110 "d2_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 445 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1118 "d2_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 447 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1128 "d2_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 453 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () <= 0) {
        error(yystack_[0].location, "port must be greater than zero");
    } 
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1140 "d2_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 467 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1151 "d2_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 472 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "d2_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 485 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1170 "d2_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 489 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1178 "d2_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 504 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1186 "d2_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 506 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "name cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1200 "d2_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 516 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1208 "d2_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 518 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "algorithm cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1221 "d2_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 527 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () < 0 || (yystack_[0].value.as< int64_t > () > 0  && (yystack_[0].value.as< int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "digest-bits must either be zero or a positive, multiple of eight");
    } 
    ElementPtr elem(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1233 "d2_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 535 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1241 "d2_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 537 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "secret cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1254 "d2_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 550 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1262 "d2_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 552 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1271 "d2_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 557 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1279 "d2_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 559 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1288 "d2_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 569 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1299 "d2_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 574 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1308 "d2_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 591 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1319 "d2_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 596 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1328 "d2_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 608 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1338 "d2_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 612 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1346 "d2_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 627 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1354 "d2_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 629 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1364 "d2_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 635 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1373 "d2_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 639 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1381 "d2_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 641 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1391 "d2_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 647 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1402 "d2_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 652 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1411 "d2_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 661 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1421 "d2_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 665 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1429 "d2_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 673 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1437 "d2_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 675 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1447 "d2_parser.cc" // lalr1.cc:859
    break;


#line 1451 "d2_parser.cc" // lalr1.cc:859
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


  const signed char D2Parser::yypact_ninf_ = -104;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short int
  D2Parser::yypact_[] =
  {
     -24,  -104,  -104,  -104,     3,    -3,    -2,     0,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,    -3,    -8,     1,     4,  -104,    42,
      47,    58,    68,    79,  -104,  -104,  -104,  -104,    83,  -104,
      19,  -104,  -104,  -104,  -104,  -104,  -104,    88,    89,  -104,
    -104,  -104,  -104,  -104,  -104,    21,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,    -3,    -3,  -104,    53,
      91,    92,    93,    94,  -104,     1,  -104,    95,    59,    60,
      96,    99,   100,   101,   102,     4,  -104,  -104,  -104,   103,
      -3,    -3,   104,   105,  -104,    74,  -104,  -104,    73,    90,
     107,   110,   113,  -104,    -3,  -104,  -104,     4,    87,  -104,
    -104,  -104,  -104,  -104,   -13,   -13,   114,  -104,    27,  -104,
      51,  -104,  -104,  -104,  -104,    63,  -104,  -104,  -104,    66,
    -104,   116,   106,  -104,  -104,   119,    87,  -104,   120,   -13,
    -104,  -104,    23,  -104,   114,   115,  -104,   121,  -104,  -104,
     123,  -104,  -104,  -104,    67,  -104,  -104,  -104,  -104,  -104,
    -104,   118,   122,   124,    97,   126,   127,    23,  -104,  -104,
      31,  -104,  -104,   128,   129,  -104,   108,  -104,   109,   111,
    -104,    24,   118,  -104,    22,  -104,   122,  -104,  -104,  -104,
    -104,  -104,   131,  -104,  -104,    69,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,    70,  -104,  -104,  -104,
    -104,  -104,   132,   133,    98,   134,    24,  -104,   138,   139,
     140,    22,  -104,   112,   141,  -104,   125,  -104,   130,   142,
     135,  -104,  -104,   144,  -104,  -104,   147,  -104,  -104,    80,
    -104,  -104,   150,   145,  -104,   137,   144,  -104,    -5,  -104,
     147,  -104,    76,  -104,  -104,  -104,   153,  -104,  -104,    77,
    -104,  -104,  -104,  -104,  -104,   155,   137,  -104,   156,   136,
     157,    -5,  -104,   143,  -104,   146,  -104,   148,  -104,  -104,
    -104,  -104
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    22,
      16,    12,    11,     8,     9,    10,    15,     3,    13,    14,
      29,     5,    40,     7,    24,    18,     0,     0,    26,     0,
      25,     0,     0,    19,   132,   134,    38,   136,     0,    37,
       0,    31,    36,    33,    35,    34,    53,     0,     0,    57,
      61,    63,    65,   110,    52,     0,    42,    44,    45,    46,
      47,    48,    49,    50,    51,    23,     0,     0,    17,     0,
       0,     0,     0,     0,    28,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    27,    20,     0,
       0,     0,     0,     0,    32,     0,    55,    56,     0,     0,
       0,     0,     0,    43,     0,   133,   135,     0,     0,    54,
      59,    60,    58,    62,    67,    67,   112,    21,     0,   141,
       0,   138,   140,    73,    72,     0,    68,    69,    71,     0,
     116,     0,   113,   114,    39,     0,     0,   137,     0,     0,
      64,    66,     0,   111,     0,     0,   139,     0,    70,   127,
       0,   130,   125,   124,     0,   118,   120,   121,   122,   123,
     115,     0,    75,     0,     0,     0,     0,     0,   117,   145,
       0,   143,    79,     0,    76,    77,     0,   129,     0,     0,
     119,     0,     0,   142,     0,    74,     0,   128,   131,   126,
     154,   159,     0,   157,   153,     0,   147,   149,   151,   152,
     150,   144,    89,    91,    87,    86,     0,    81,    83,    84,
      85,    78,     0,     0,     0,     0,     0,   146,     0,     0,
       0,     0,    80,     0,     0,   156,     0,   148,     0,     0,
       0,    82,   155,     0,   158,    90,    93,    88,   163,     0,
     161,    97,     0,    94,    95,     0,     0,   160,     0,    92,
       0,   167,     0,   165,   162,   107,     0,   105,   104,     0,
      99,   101,   102,   103,    96,     0,     0,   164,     0,     0,
       0,     0,    98,     0,   166,     0,   109,     0,   100,   168,
     108,   106
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
    -104,  -104,  -104,  -104,  -104,   -23,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,   -26,  -104,  -104,  -104,    33,
    -104,  -104,  -104,  -104,    26,    78,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,    30,
    -104,    25,  -104,  -104,  -104,  -104,   -21,  -104,  -104,   -59,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,   -83,  -104,
    -104,  -103,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,    29,  -104,  -104,     2,  -104,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,    34,
    -104,  -104,  -104,    -7,  -104,  -104,   -42,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,   -69,  -104,  -104,   -87,  -104
  };

  const short int
  D2Parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    16,    17,    18,    25,    32,
      33,    19,    24,    29,    30,    54,    21,    26,    40,    41,
      42,    72,    23,    27,    55,    56,    57,    77,    58,    59,
      60,    80,   112,    61,    81,    62,    82,    63,    83,   125,
     126,   127,   128,   138,   173,   174,   175,   184,   206,   207,
     208,   220,   209,   218,   210,   219,   242,   243,   244,   248,
     259,   260,   261,   270,   262,   268,   263,    64,    84,   131,
     132,   133,   142,   154,   155,   156,   166,   157,   163,   158,
     159,   165,    43,    70,    44,    71,    45,    73,   120,   121,
     122,   135,   170,   171,   181,   195,   196,   197,   212,   198,
     199,   215,   200,   213,   239,   240,   245,   252,   253,   265
  };

  const unsigned short int
  D2Parser::yytable_[] =
  {
      39,    28,     9,     8,    10,    20,    11,    22,   255,   256,
     123,    34,    35,    36,     1,     2,     3,    46,    47,    48,
      49,   257,    75,    50,    85,    51,    52,    76,    38,    86,
      85,    53,    37,    31,   182,   134,    38,   183,    12,    13,
      14,    15,    38,    87,    88,    38,   202,   203,    65,    39,
      66,   149,   150,   151,   136,   204,   152,   190,   191,   137,
     192,   193,    67,    38,    38,    38,   139,   105,   106,   139,
     167,   140,   216,   221,   141,   168,    68,   217,   222,   266,
     271,   117,    69,   246,   267,   272,   247,    74,   124,   124,
     110,   111,    78,    79,    89,    90,    91,    92,    93,    95,
      98,    96,    97,    99,   100,   101,   102,   104,    94,   144,
     113,   107,   108,   124,   114,   109,   153,   115,   116,   119,
     161,   130,   143,   145,   147,   169,   162,   164,   176,   172,
     178,   179,   186,   118,   185,   214,   223,   224,   226,   177,
     225,   153,   228,   229,   230,   129,   233,   236,   250,   187,
     188,   238,   189,   232,   241,   194,   249,   269,   205,   273,
     275,   277,   231,   103,   148,   211,   234,   264,   278,   180,
     146,   235,   251,   160,   227,   201,   237,   254,   276,   274,
       0,     0,     0,     0,   279,     0,     0,   280,     0,   281,
     194,     0,     0,     0,     0,   205,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   258,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   258
  };

  const short int
  D2Parser::yycheck_[] =
  {
      26,    24,     5,     0,     7,     7,     9,     7,    13,    14,
      23,    10,    11,    12,    38,    39,    40,    13,    14,    15,
      16,    26,     3,    19,     3,    21,    22,     8,    41,     8,
       3,    27,    31,    41,     3,     8,    41,     6,    41,    42,
      43,    44,    41,    66,    67,    41,    24,    25,     6,    75,
       3,    28,    29,    30,     3,    33,    33,    33,    34,     8,
      36,    37,     4,    41,    41,    41,     3,    90,    91,     3,
       3,     8,     3,     3,     8,     8,     8,     8,     8,     3,
       3,   104,     3,     3,     8,     8,     6,     4,   114,   115,
      17,    18,     4,     4,    41,     4,     4,     4,     4,     4,
       4,    42,    42,     4,     4,     4,     4,     4,    75,     3,
      20,     7,     7,   139,     7,    41,   142,     7,     5,    32,
       5,     7,     6,     4,     4,     7,     5,     4,     4,     7,
       4,     4,     3,   107,     6,     4,     4,     4,     4,    42,
      42,   167,     4,     4,     4,   115,     5,     5,     3,    41,
      41,     7,    41,    41,     7,   181,     6,     4,   184,     4,
       4,     4,   221,    85,   139,   186,    41,   250,   271,   167,
     136,    41,    35,   144,   216,   182,    41,   246,    42,   266,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    41,    -1,    41,
     216,    -1,    -1,    -1,    -1,   221,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   248,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   271
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    38,    39,    40,    46,    47,    48,    49,     0,     5,
       7,     9,    41,    42,    43,    44,    50,    51,    52,    56,
       7,    61,     7,    67,    57,    53,    62,    68,    50,    58,
      59,    41,    54,    55,    10,    11,    12,    31,    41,    60,
      63,    64,    65,   127,   129,   131,    13,    14,    15,    16,
      19,    21,    22,    27,    60,    69,    70,    71,    73,    74,
      75,    78,    80,    82,   112,     6,     3,     4,     8,     3,
     128,   130,    66,   132,     4,     3,     8,    72,     4,     4,
      76,    79,    81,    83,   113,     3,     8,    50,    50,    41,
       4,     4,     4,     4,    64,     4,    42,    42,     4,     4,
       4,     4,     4,    70,     4,    50,    50,     7,     7,    41,
      17,    18,    77,    20,     7,     7,     5,    50,    69,    32,
     133,   134,   135,    23,    60,    84,    85,    86,    87,    84,
       7,   114,   115,   116,     8,   136,     3,     8,    88,     3,
       8,     8,   117,     6,     3,     4,   134,     4,    86,    28,
      29,    30,    33,    60,   118,   119,   120,   122,   124,   125,
     116,     5,     5,   123,     4,   126,   121,     3,     8,     7,
     137,   138,     7,    89,    90,    91,     4,    42,     4,     4,
     119,   139,     3,     6,    92,     6,     3,    41,    41,    41,
      33,    34,    36,    37,    60,   140,   141,   142,   144,   145,
     147,   138,    24,    25,    33,    60,    93,    94,    95,    97,
      99,    91,   143,   148,     4,   146,     3,     8,    98,   100,
      96,     3,     8,     4,     4,    42,     4,   141,     4,     4,
       4,    94,    41,     5,    41,    41,     5,    41,     7,   149,
     150,     7,   101,   102,   103,   151,     3,     6,   104,     6,
       3,    35,   152,   153,   150,    13,    14,    26,    60,   105,
     106,   107,   109,   111,   103,   154,     3,     8,   110,     4,
     108,     3,     8,     4,   153,     4,    42,     4,   106,    41,
      41,    41
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    45,    47,    46,    48,    46,    49,    46,    50,    50,
      50,    50,    50,    50,    50,    51,    53,    52,    54,    54,
      55,    55,    57,    56,    58,    58,    59,    59,    60,    62,
      61,    63,    63,    64,    64,    64,    64,    64,    66,    65,
      68,    67,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    72,    71,    73,    74,    76,    75,    77,
      77,    79,    78,    81,    80,    83,    82,    84,    84,    85,
      85,    86,    86,    88,    87,    89,    89,    90,    90,    92,
      91,    93,    93,    94,    94,    94,    94,    96,    95,    98,
      97,   100,    99,   101,   101,   102,   102,   104,   103,   105,
     105,   106,   106,   106,   106,   108,   107,   110,   109,   111,
     113,   112,   114,   114,   115,   115,   117,   116,   118,   118,
     119,   119,   119,   119,   119,   121,   120,   123,   122,   124,
     126,   125,   128,   127,   130,   129,   132,   131,   133,   133,
     134,   136,   135,   137,   137,   139,   138,   140,   140,   141,
     141,   141,   141,   141,   143,   142,   144,   146,   145,   148,
     147,   149,   149,   151,   150,   152,   152,   154,   153
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
       1,     0,     4,     0,     6,     0,     6,     0,     1,     1,
       3,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     0,     4
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
  "\"forward-ddns\"", "\"reverse-ddns\"", "\"ddns-domains\"",
  "\"key-name\"", "\"dns-servers\"", "\"hostname\"", "\"tsig-keys\"",
  "\"algorithm\"", "\"digest-bits\"", "\"secret\"", "\"Logging\"",
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
  "ddns_mgr_params", "not_empty_ddns_mgr_params", "ddns_mgr_param",
  "ddns_domains", "$@14", "ddns_domain_list", "not_empty_ddns_domain_list",
  "ddns_domain", "$@15", "ddns_domain_params", "ddns_domain_param",
  "ddns_domain_name", "$@16", "ddns_domain_key_name", "$@17",
  "dns_servers", "$@18", "dns_server_list", "not_empty_dns_server_list",
  "dns_server", "$@19", "dns_server_params", "dns_server_param",
  "dns_server_hostname", "$@20", "dns_server_ip_address", "$@21",
  "dns_server_port", "tsig_keys", "$@22", "tsig_keys_list",
  "not_empty_tsig_keys_list", "tsig_key", "$@23", "tsig_key_params",
  "tsig_key_param", "tsig_key_name", "$@24", "tsig_key_algorithm", "$@25",
  "tsig_key_digest_bits", "tsig_key_secret", "$@26", "dhcp6_json_object",
  "$@27", "dhcp4_json_object", "$@28", "logging_object", "$@29",
  "logging_params", "logging_param", "loggers", "$@30", "loggers_entries",
  "logger_entry", "$@31", "logger_params", "logger_param", "name", "$@32",
  "debuglevel", "severity", "$@33", "output_options_list", "$@34",
  "output_options_list_content", "output_entry", "$@35", "output_params",
  "output_param", "$@36", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short int
  D2Parser::yyrline_[] =
  {
       0,   107,   107,   107,   108,   108,   109,   109,   117,   118,
     119,   120,   121,   122,   123,   126,   131,   131,   143,   144,
     147,   151,   158,   158,   165,   166,   169,   173,   184,   194,
     194,   206,   207,   211,   212,   213,   214,   215,   220,   220,
     230,   230,   238,   239,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   253,   253,   261,   269,   278,   278,   286,
     287,   290,   290,   298,   298,   308,   308,   318,   319,   322,
     323,   326,   327,   333,   333,   343,   344,   347,   348,   351,
     351,   359,   360,   363,   364,   365,   366,   370,   370,   382,
     382,   397,   397,   407,   408,   411,   412,   415,   415,   423,
     424,   427,   428,   429,   430,   433,   433,   445,   445,   453,
     467,   467,   477,   478,   481,   482,   485,   485,   493,   494,
     497,   498,   499,   500,   501,   504,   504,   516,   516,   527,
     535,   535,   550,   550,   557,   557,   569,   569,   582,   583,
     587,   591,   591,   603,   604,   608,   608,   616,   617,   620,
     621,   622,   623,   624,   627,   627,   635,   639,   639,   647,
     647,   657,   658,   661,   661,   669,   670,   673,   673
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
#line 2047 "d2_parser.cc" // lalr1.cc:1167
#line 681 "d2_parser.yy" // lalr1.cc:1168


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
