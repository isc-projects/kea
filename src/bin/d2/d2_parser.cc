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
      case 46: // value
      case 73: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 40: // "boolean"
        value.move< bool > (that.value);
        break;

      case 39: // "floating point"
        value.move< double > (that.value);
        break;

      case 38: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 37: // "constant string"
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
      case 46: // value
      case 73: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 40: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 39: // "floating point"
        value.copy< double > (that.value);
        break;

      case 38: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 37: // "constant string"
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
            case 37: // "constant string"

#line 94 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "d2_parser.cc" // lalr1.cc:636
        break;

      case 38: // "integer"

#line 94 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "d2_parser.cc" // lalr1.cc:636
        break;

      case 39: // "floating point"

#line 94 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "d2_parser.cc" // lalr1.cc:636
        break;

      case 40: // "boolean"

#line 94 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "d2_parser.cc" // lalr1.cc:636
        break;

      case 46: // value

#line 94 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "d2_parser.cc" // lalr1.cc:636
        break;

      case 73: // ncr_protocol_value

#line 94 "d2_parser.yy" // lalr1.cc:636
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
      case 46: // value
      case 73: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 40: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 39: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 38: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 37: // "constant string"
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
#line 103 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "d2_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 104 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "d2_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 105 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 642 "d2_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 113 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 648 "d2_parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 114 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 654 "d2_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 115 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 660 "d2_parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 116 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 666 "d2_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 117 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 672 "d2_parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 118 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 678 "d2_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 119 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 684 "d2_parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 122 "d2_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 693 "d2_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 127 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 704 "d2_parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 132 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 714 "d2_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 143 "d2_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 723 "d2_parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 147 "d2_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 733 "d2_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 154 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 742 "d2_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 157 "d2_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 750 "d2_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 173 "d2_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 759 "d2_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 177 "d2_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 768 "d2_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 188 "d2_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 779 "d2_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 198 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 790 "d2_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 203 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 800 "d2_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 224 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 811 "d2_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 229 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 820 "d2_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 234 "d2_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "d2_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 238 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 838 "d2_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 257 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 846 "d2_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 259 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 856 "d2_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 265 "d2_parser.yy" // lalr1.cc:859
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
#line 273 "d2_parser.yy" // lalr1.cc:859
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
#line 282 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 889 "d2_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 284 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 898 "d2_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 290 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 904 "d2_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 291 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 910 "d2_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 294 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 918 "d2_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 296 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 928 "d2_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 302 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 936 "d2_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 304 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("forward-ddns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 945 "d2_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 309 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 953 "d2_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 311 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reverse-ddns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 962 "d2_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 318 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 973 "d2_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 323 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 982 "d2_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 336 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 992 "d2_parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 340 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1000 "d2_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 355 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1008 "d2_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 357 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "name cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1022 "d2_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 367 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1030 "d2_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 369 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "algorithm cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1043 "d2_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 378 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () < 0 || (yystack_[0].value.as< int64_t > () > 0  && (yystack_[0].value.as< int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "digest-bits must either be zero or a positive, multiple of eight");
    } 
    ElementPtr elem(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1055 "d2_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 386 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1063 "d2_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 388 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "secret cannot be blank");
    } 
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1076 "d2_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 401 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1084 "d2_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 403 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1093 "d2_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 408 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1101 "d2_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 410 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1110 "d2_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 420 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1121 "d2_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 425 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1130 "d2_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 442 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1141 "d2_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 447 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1150 "d2_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 459 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1160 "d2_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 463 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1168 "d2_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 478 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1176 "d2_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 480 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1186 "d2_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 486 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1195 "d2_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 490 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1203 "d2_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 492 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1213 "d2_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 498 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1224 "d2_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 503 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1233 "d2_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 512 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1243 "d2_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 516 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1251 "d2_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 524 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1259 "d2_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 526 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1269 "d2_parser.cc" // lalr1.cc:859
    break;


#line 1273 "d2_parser.cc" // lalr1.cc:859
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


  const signed char D2Parser::yypact_ninf_ = -78;

  const signed char D2Parser::yytable_ninf_ = -1;

  const signed char
  D2Parser::yypact_[] =
  {
      28,   -78,   -78,   -78,     5,    -3,    12,    13,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,    -3,    -7,     1,     2,   -78,    27,
      43,    54,    52,    66,   -78,   -78,   -78,   -78,    67,   -78,
       0,   -78,   -78,   -78,   -78,   -78,   -78,    68,    69,   -78,
     -78,   -78,   -78,   -78,   -78,     6,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,    -3,    -3,   -78,    33,
      70,    71,    72,    75,   -78,     1,   -78,    76,    44,    45,
      80,    81,    82,    83,    84,     2,   -78,   -78,   -78,    85,
      -3,    -3,    86,    87,   -78,    55,   -78,   -78,    48,    77,
      -3,    -3,    90,   -78,    -3,   -78,   -78,     2,    62,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,    89,   -78,    19,   -78,
      23,   -78,   -78,   -78,    92,    88,   -78,   -78,    95,    62,
     -78,    16,   -78,    89,    96,   -78,   -78,    98,   -78,   -78,
     -78,    49,   -78,   -78,   -78,   -78,   -78,   -78,    93,    99,
      73,   100,   102,    16,   -78,   -78,     4,   -78,    78,   -78,
      79,    91,   -78,    18,    93,   -78,   -78,   -78,   -78,   -78,
     -78,   103,   -78,   -78,    51,   -78,   -78,   -78,   -78,   -78,
     -78,   104,   105,    74,   106,    18,   -78,    94,   108,   -78,
      97,   -78,   -78,   107,   -78,   -78,    26,   -78,   101,   107,
     -78,   -78,    53,   -78,   -78,   113,   101,   -78,   109,   -78,
     -78
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    22,
      16,    12,    11,     8,     9,    10,    15,     3,    13,    14,
      29,     5,    40,     7,    24,    18,     0,     0,    26,     0,
      25,     0,     0,    19,    89,    91,    38,    93,     0,    37,
       0,    31,    36,    33,    35,    34,    53,     0,     0,    57,
      61,    63,    65,    67,    52,     0,    42,    44,    45,    46,
      47,    48,    49,    50,    51,    23,     0,     0,    17,     0,
       0,     0,     0,     0,    28,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    27,    20,     0,
       0,     0,     0,     0,    32,     0,    55,    56,     0,     0,
       0,     0,     0,    43,     0,    90,    92,     0,     0,    54,
      59,    60,    58,    62,    64,    66,    69,    21,     0,    98,
       0,    95,    97,    73,     0,    70,    71,    39,     0,     0,
      94,     0,    68,     0,     0,    96,    84,     0,    87,    82,
      81,     0,    75,    77,    78,    79,    80,    72,     0,     0,
       0,     0,     0,     0,    74,   102,     0,   100,     0,    86,
       0,     0,    76,     0,     0,    99,    85,    88,    83,   111,
     116,     0,   114,   110,     0,   104,   106,   108,   109,   107,
     101,     0,     0,     0,     0,     0,   103,     0,     0,   113,
       0,   105,   112,     0,   115,   120,     0,   118,     0,     0,
     117,   124,     0,   122,   119,     0,     0,   121,     0,   123,
     125
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
     -78,   -78,   -78,   -78,   -78,   -23,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -26,   -78,   -78,   -78,    46,
     -78,   -78,   -78,   -78,    11,    34,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -13,   -78,   -78,   -31,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,    -6,   -78,   -78,   -78,   -40,   -78,   -78,   -60,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -73,   -78,   -78,
     -77,   -78
  };

  const short int
  D2Parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    16,    17,    18,    25,    32,
      33,    19,    24,    29,    30,    54,    21,    26,    40,    41,
      42,    72,    23,    27,    55,    56,    57,    77,    58,    59,
      60,    80,   112,    61,    81,    62,    82,    63,    83,    64,
      84,   124,   125,   126,   131,   141,   142,   143,   152,   144,
     149,   145,   146,   151,    43,    70,    44,    71,    45,    73,
     120,   121,   122,   128,   156,   157,   163,   174,   175,   176,
     181,   177,   178,   184,   179,   182,   196,   197,   198,   202,
     203,   205
  };

  const unsigned char
  D2Parser::yytable_[] =
  {
      39,    28,     9,    75,    10,     8,    11,   164,    76,    85,
     165,    34,    35,    36,    86,    46,    47,    48,    49,    20,
      22,    50,    85,    51,    52,    53,   129,   127,    37,   199,
      31,   130,   200,    65,    12,    13,    14,    15,    38,    38,
     136,   137,   138,    87,    88,   139,    66,   169,   170,    39,
     171,   172,   153,    38,   185,    38,   206,   154,    67,   186,
      68,   207,     1,     2,     3,   110,   111,   105,   106,    69,
      89,    74,    78,    79,    90,    91,    92,   114,   115,    93,
      95,   117,    96,    97,    98,    99,   100,   101,   102,   104,
     119,   133,   109,   107,   108,   116,   123,   113,   132,   134,
     155,   148,   150,   158,   160,   140,   161,   183,   187,   188,
     190,   159,   189,   193,   195,   166,   167,   208,   118,   103,
     147,    94,   162,   135,   180,   191,   204,   140,   168,   209,
       0,   192,   201,     0,   194,     0,     0,   173,     0,     0,
       0,     0,     0,     0,     0,     0,   210,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   173
  };

  const short int
  D2Parser::yycheck_[] =
  {
      26,    24,     5,     3,     7,     0,     9,     3,     8,     3,
       6,    10,    11,    12,     8,    13,    14,    15,    16,     7,
       7,    19,     3,    21,    22,    23,     3,     8,    27,     3,
      37,     8,     6,     6,    37,    38,    39,    40,    37,    37,
      24,    25,    26,    66,    67,    29,     3,    29,    30,    75,
      32,    33,     3,    37,     3,    37,     3,     8,     4,     8,
       8,     8,    34,    35,    36,    17,    18,    90,    91,     3,
      37,     4,     4,     4,     4,     4,     4,   100,   101,     4,
       4,   104,    38,    38,     4,     4,     4,     4,     4,     4,
      28,     3,    37,     7,     7,     5,     7,    20,     6,     4,
       7,     5,     4,     4,     4,   131,     4,     4,     4,     4,
       4,    38,    38,     5,     7,    37,    37,     4,   107,    85,
     133,    75,   153,   129,   164,   185,   199,   153,    37,   206,
      -1,    37,    31,    -1,    37,    -1,    -1,   163,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   185
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    34,    35,    36,    42,    43,    44,    45,     0,     5,
       7,     9,    37,    38,    39,    40,    46,    47,    48,    52,
       7,    57,     7,    63,    53,    49,    58,    64,    46,    54,
      55,    37,    50,    51,    10,    11,    12,    27,    37,    56,
      59,    60,    61,    95,    97,    99,    13,    14,    15,    16,
      19,    21,    22,    23,    56,    65,    66,    67,    69,    70,
      71,    74,    76,    78,    80,     6,     3,     4,     8,     3,
      96,    98,    62,   100,     4,     3,     8,    68,     4,     4,
      72,    75,    77,    79,    81,     3,     8,    46,    46,    37,
       4,     4,     4,     4,    60,     4,    38,    38,     4,     4,
       4,     4,     4,    66,     4,    46,    46,     7,     7,    37,
      17,    18,    73,    20,    46,    46,     5,    46,    65,    28,
     101,   102,   103,     7,    82,    83,    84,     8,   104,     3,
       8,    85,     6,     3,     4,   102,    24,    25,    26,    29,
      56,    86,    87,    88,    90,    92,    93,    84,     5,    91,
       4,    94,    89,     3,     8,     7,   105,   106,     4,    38,
       4,     4,    87,   107,     3,     6,    37,    37,    37,    29,
      30,    32,    33,    56,   108,   109,   110,   112,   113,   115,
     106,   111,   116,     4,   114,     3,     8,     4,     4,    38,
       4,   109,    37,     5,    37,     7,   117,   118,   119,     3,
       6,    31,   120,   121,   118,   122,     3,     8,     4,   121,
      37
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    41,    43,    42,    44,    42,    45,    42,    46,    46,
      46,    46,    46,    46,    46,    47,    49,    48,    50,    50,
      51,    51,    53,    52,    54,    54,    55,    55,    56,    58,
      57,    59,    59,    60,    60,    60,    60,    60,    62,    61,
      64,    63,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    68,    67,    69,    70,    72,    71,    73,
      73,    75,    74,    77,    76,    79,    78,    81,    80,    82,
      82,    83,    83,    85,    84,    86,    86,    87,    87,    87,
      87,    87,    89,    88,    91,    90,    92,    94,    93,    96,
      95,    98,    97,   100,    99,   101,   101,   102,   104,   103,
     105,   105,   107,   106,   108,   108,   109,   109,   109,   109,
     109,   111,   110,   112,   114,   113,   116,   115,   117,   117,
     119,   118,   120,   120,   122,   121
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
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     0,     4,     0,
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
  "\"forward-ddns\"", "\"reverse-ddns\"", "\"tsig-keys\"", "\"algorithm\"",
  "\"digest-bits\"", "\"secret\"", "\"Logging\"", "\"loggers\"",
  "\"name\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "value",
  "sub_json", "map2", "$@4", "map_content", "not_empty_map",
  "list_generic", "$@5", "list_content", "not_empty_list",
  "unknown_map_entry", "syntax_map", "$@6", "global_objects",
  "global_object", "dhcpddns_object", "$@7", "sub_dhcpddns", "$@8",
  "dhcpddns_params", "dhcpddns_param", "ip_address", "$@9", "port",
  "dns_server_timeout", "ncr_protocol", "$@10", "ncr_protocol_value",
  "ncr_format", "$@11", "forward_ddns", "$@12", "reverse_ddns", "$@13",
  "tsig_keys", "$@14", "tsig_keys_list", "not_empty_tsig_keys_list",
  "tsig_key", "$@15", "tsig_key_params", "tsig_key_param", "tsig_key_name",
  "$@16", "tsig_key_algorithm", "$@17", "tsig_key_digest_bits",
  "tsig_key_secret", "$@18", "dhcp6_json_object", "$@19",
  "dhcp4_json_object", "$@20", "logging_object", "$@21", "logging_params",
  "logging_param", "loggers", "$@22", "loggers_entries", "logger_entry",
  "$@23", "logger_params", "logger_param", "name", "$@24", "debuglevel",
  "severity", "$@25", "output_options_list", "$@26",
  "output_options_list_content", "output_entry", "$@27", "output_params",
  "output_param", "$@28", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short int
  D2Parser::yyrline_[] =
  {
       0,   103,   103,   103,   104,   104,   105,   105,   113,   114,
     115,   116,   117,   118,   119,   122,   127,   127,   139,   140,
     143,   147,   154,   154,   169,   170,   173,   177,   188,   198,
     198,   210,   211,   215,   216,   217,   218,   219,   224,   224,
     234,   234,   242,   243,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   257,   257,   265,   273,   282,   282,   290,
     291,   294,   294,   302,   302,   309,   309,   318,   318,   328,
     329,   332,   333,   336,   336,   344,   345,   348,   349,   350,
     351,   352,   355,   355,   367,   367,   378,   386,   386,   401,
     401,   408,   408,   420,   420,   433,   434,   438,   442,   442,
     454,   455,   459,   459,   467,   468,   471,   472,   473,   474,
     475,   478,   478,   486,   490,   490,   498,   498,   508,   509,
     512,   512,   520,   521,   524,   524
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
#line 1806 "d2_parser.cc" // lalr1.cc:1167
#line 532 "d2_parser.yy" // lalr1.cc:1168


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
