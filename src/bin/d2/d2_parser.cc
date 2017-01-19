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
namespace isc { namespace dhcp {
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
  D2Parser::D2Parser (isc::dhcp::D2ParserContext& ctx_yyarg)
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
      case 40: // value
      case 67: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 34: // "boolean"
        value.move< bool > (that.value);
        break;

      case 33: // "floating point"
        value.move< double > (that.value);
        break;

      case 32: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 31: // "constant string"
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
      case 40: // value
      case 67: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 34: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 33: // "floating point"
        value.copy< double > (that.value);
        break;

      case 32: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 31: // "constant string"
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
            case 31: // "constant string"

#line 88 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "d2_parser.cc" // lalr1.cc:636
        break;

      case 32: // "integer"

#line 88 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "d2_parser.cc" // lalr1.cc:636
        break;

      case 33: // "floating point"

#line 88 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "d2_parser.cc" // lalr1.cc:636
        break;

      case 34: // "boolean"

#line 88 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "d2_parser.cc" // lalr1.cc:636
        break;

      case 40: // value

#line 88 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "d2_parser.cc" // lalr1.cc:636
        break;

      case 67: // ncr_protocol_value

#line 88 "d2_parser.yy" // lalr1.cc:636
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
      case 40: // value
      case 67: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 34: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 33: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 32: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 31: // "constant string"
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
#line 97 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "d2_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 98 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "d2_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 99 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 642 "d2_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 107 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 648 "d2_parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 108 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 654 "d2_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 109 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 660 "d2_parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 110 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 666 "d2_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 111 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 672 "d2_parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 112 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 678 "d2_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 113 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 684 "d2_parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 116 "d2_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 693 "d2_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 121 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 704 "d2_parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 126 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 714 "d2_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 137 "d2_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 723 "d2_parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 141 "d2_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 733 "d2_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 148 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 742 "d2_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 151 "d2_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 750 "d2_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 167 "d2_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 759 "d2_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 171 "d2_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 768 "d2_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 182 "d2_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 779 "d2_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 192 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 790 "d2_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 197 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 800 "d2_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 218 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 811 "d2_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 223 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 820 "d2_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 228 "d2_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "d2_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 232 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 838 "d2_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 248 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 846 "d2_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 250 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 856 "d2_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 256 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 865 "d2_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 261 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-server-timeout", i);
}
#line 874 "d2_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 266 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 882 "d2_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 268 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 891 "d2_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 274 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 897 "d2_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 275 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 903 "d2_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 278 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 911 "d2_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 280 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 921 "d2_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 286 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 929 "d2_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 288 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 938 "d2_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 293 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 946 "d2_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 295 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 955 "d2_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 305 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 966 "d2_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 310 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 975 "d2_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 327 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 986 "d2_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 332 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 995 "d2_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 344 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1005 "d2_parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 348 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1013 "d2_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 363 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1021 "d2_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 365 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1031 "d2_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 371 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1040 "d2_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 375 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1048 "d2_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 377 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1058 "d2_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 383 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1069 "d2_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 388 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1078 "d2_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 397 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1088 "d2_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 401 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1096 "d2_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 409 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1104 "d2_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 411 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1114 "d2_parser.cc" // lalr1.cc:859
    break;


#line 1118 "d2_parser.cc" // lalr1.cc:859
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


  const signed char D2Parser::yypact_ninf_ = -57;

  const signed char D2Parser::yytable_ninf_ = -1;

  const signed char
  D2Parser::yypact_[] =
  {
      22,   -57,   -57,   -57,     5,    -3,    41,    46,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,    -3,    -4,     1,     2,   -57,    30,
      51,    52,    47,    54,   -57,   -57,   -57,   -57,    56,   -57,
       0,   -57,   -57,   -57,   -57,   -57,   -57,    57,    58,   -57,
     -57,   -57,     6,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
      -3,    -3,   -57,    33,    59,    61,    62,    63,   -57,     1,
     -57,    64,    38,    39,    68,    69,     2,   -57,   -57,   -57,
      70,    -3,    -3,    71,    72,   -57,    44,   -57,   -57,    29,
      60,   -57,    -3,   -57,   -57,     2,    55,   -57,   -57,   -57,
     -57,   -57,   -57,    16,   -57,    17,   -57,   -57,   -57,    77,
      55,   -57,    78,   -57,    75,   -57,     4,   -57,    18,    75,
     -57,   -57,   -57,    80,   -57,   -57,    31,   -57,   -57,   -57,
     -57,   -57,   -57,    81,    82,    65,    83,    18,   -57,    45,
      84,   -57,    67,   -57,   -57,    86,   -57,   -57,    20,   -57,
      66,    86,   -57,   -57,    32,   -57,   -57,    90,    66,   -57,
      73,   -57,   -57
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    22,
      16,    12,    11,     8,     9,    10,    15,     3,    13,    14,
      29,     5,    40,     7,    24,    18,     0,     0,    26,     0,
      25,     0,     0,    19,    60,    62,    38,    64,     0,    37,
       0,    31,    36,    33,    35,    34,    50,     0,     0,    54,
      58,    49,     0,    42,    44,    45,    46,    47,    48,    23,
       0,     0,    17,     0,     0,     0,     0,     0,    28,     0,
      30,     0,     0,     0,     0,     0,     0,    41,    27,    20,
       0,     0,     0,     0,     0,    32,     0,    52,    53,     0,
       0,    43,     0,    61,    63,     0,     0,    51,    56,    57,
      55,    59,    21,     0,    69,     0,    66,    68,    39,     0,
       0,    65,     0,    67,     0,    73,     0,    71,     0,     0,
      70,    82,    87,     0,    85,    81,     0,    75,    77,    79,
      80,    78,    72,     0,     0,     0,     0,     0,    74,     0,
       0,    84,     0,    76,    83,     0,    86,    91,     0,    89,
       0,     0,    88,    95,     0,    93,    90,     0,     0,    92,
       0,    94,    96
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
     -57,   -57,   -57,   -57,   -57,   -23,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -26,   -57,   -57,   -57,    19,
     -57,   -57,   -57,   -57,    -5,    23,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -15,   -57,   -57,   -57,   -19,   -57,   -57,   -41,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -50,   -57,
     -57,   -56,   -57
  };

  const short int
  D2Parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    16,    17,    18,    25,    32,
      33,    19,    24,    29,    30,    51,    21,    26,    40,    41,
      42,    66,    23,    27,    52,    53,    54,    71,    55,    56,
      57,    74,   100,    58,    75,    43,    64,    44,    65,    45,
      67,   105,   106,   107,   109,   116,   117,   118,   126,   127,
     128,   133,   129,   130,   136,   131,   134,   148,   149,   150,
     154,   155,   157
  };

  const unsigned char
  D2Parser::yytable_[] =
  {
      39,    28,     9,    69,    10,     8,    11,   119,    70,    76,
     120,    34,    35,    36,    77,    46,    47,    48,    49,    76,
     110,    50,    37,   151,   108,   111,   152,    31,    12,    13,
      14,    15,    38,    38,   137,   158,    59,    78,    79,   138,
     159,   121,   122,    39,   123,   124,    98,    99,    20,    38,
       1,     2,     3,    22,    60,    62,    61,    63,    93,    94,
      68,    72,    73,    81,    80,    82,    83,    84,    86,   102,
      87,    88,    89,    90,    92,    97,   144,   104,    95,    96,
     101,   112,   115,   114,   135,   139,   140,   142,    85,   145,
     103,   153,   125,   147,   160,   113,   143,   141,   146,    91,
     132,   156,   161,     0,   162,     0,     0,     0,     0,     0,
       0,   125
  };

  const short int
  D2Parser::yycheck_[] =
  {
      26,    24,     5,     3,     7,     0,     9,     3,     8,     3,
       6,    10,    11,    12,     8,    13,    14,    15,    16,     3,
       3,    19,    21,     3,     8,     8,     6,    31,    31,    32,
      33,    34,    31,    31,     3,     3,     6,    60,    61,     8,
       8,    23,    24,    69,    26,    27,    17,    18,     7,    31,
      28,    29,    30,     7,     3,     8,     4,     3,    81,    82,
       4,     4,     4,     4,    31,     4,     4,     4,     4,    92,
      32,    32,     4,     4,     4,    31,    31,    22,     7,     7,
      20,     4,     7,     5,     4,     4,     4,     4,    69,     5,
      95,    25,   118,     7,     4,   110,   137,    32,    31,    76,
     119,   151,   158,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,   137
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    28,    29,    30,    36,    37,    38,    39,     0,     5,
       7,     9,    31,    32,    33,    34,    40,    41,    42,    46,
       7,    51,     7,    57,    47,    43,    52,    58,    40,    48,
      49,    31,    44,    45,    10,    11,    12,    21,    31,    50,
      53,    54,    55,    70,    72,    74,    13,    14,    15,    16,
      19,    50,    59,    60,    61,    63,    64,    65,    68,     6,
       3,     4,     8,     3,    71,    73,    56,    75,     4,     3,
       8,    62,     4,     4,    66,    69,     3,     8,    40,    40,
      31,     4,     4,     4,     4,    54,     4,    32,    32,     4,
       4,    60,     4,    40,    40,     7,     7,    31,    17,    18,
      67,    20,    40,    59,    22,    76,    77,    78,     8,    79,
       3,     8,     4,    77,     5,     7,    80,    81,    82,     3,
       6,    23,    24,    26,    27,    50,    83,    84,    85,    87,
      88,    90,    81,    86,    91,     4,    89,     3,     8,     4,
       4,    32,     4,    84,    31,     5,    31,     7,    92,    93,
      94,     3,     6,    25,    95,    96,    93,    97,     3,     8,
       4,    96,    31
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    35,    37,    36,    38,    36,    39,    36,    40,    40,
      40,    40,    40,    40,    40,    41,    43,    42,    44,    44,
      45,    45,    47,    46,    48,    48,    49,    49,    50,    52,
      51,    53,    53,    54,    54,    54,    54,    54,    56,    55,
      58,    57,    59,    59,    60,    60,    60,    60,    60,    60,
      62,    61,    63,    64,    66,    65,    67,    67,    69,    68,
      71,    70,    73,    72,    75,    74,    76,    76,    77,    79,
      78,    80,    80,    82,    81,    83,    83,    84,    84,    84,
      84,    84,    86,    85,    87,    89,    88,    91,    90,    92,
      92,    94,    93,    95,    95,    97,    96
  };

  const unsigned char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     1,
       3,     5,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     0,     4
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
  "\"Logging\"", "\"loggers\"", "\"name\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "value", "sub_json", "map2", "$@4", "map_content",
  "not_empty_map", "list_generic", "$@5", "list_content", "not_empty_list",
  "unknown_map_entry", "syntax_map", "$@6", "global_objects",
  "global_object", "dhcpddns_object", "$@7", "sub_dhcpddns", "$@8",
  "dhcpddns_params", "dhcpddns_param", "ip_address", "$@9", "port",
  "dns_server_timeout", "ncr_protocol", "$@10", "ncr_protocol_value",
  "ncr_format", "$@11", "dhcp6_json_object", "$@12", "dhcp4_json_object",
  "$@13", "logging_object", "$@14", "logging_params", "logging_param",
  "loggers", "$@15", "loggers_entries", "logger_entry", "$@16",
  "logger_params", "logger_param", "name", "$@17", "debuglevel",
  "severity", "$@18", "output_options_list", "$@19",
  "output_options_list_content", "output_entry", "$@20", "output_params",
  "output_param", "$@21", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short int
  D2Parser::yyrline_[] =
  {
       0,    97,    97,    97,    98,    98,    99,    99,   107,   108,
     109,   110,   111,   112,   113,   116,   121,   121,   133,   134,
     137,   141,   148,   148,   163,   164,   167,   171,   182,   192,
     192,   204,   205,   209,   210,   211,   212,   213,   218,   218,
     228,   228,   236,   237,   240,   241,   242,   243,   244,   245,
     248,   248,   256,   261,   266,   266,   274,   275,   278,   278,
     286,   286,   293,   293,   305,   305,   318,   319,   323,   327,
     327,   339,   340,   344,   344,   352,   353,   356,   357,   358,
     359,   360,   363,   363,   371,   375,   375,   383,   383,   393,
     394,   397,   397,   405,   406,   409,   409
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
} } // isc::dhcp
#line 1609 "d2_parser.cc" // lalr1.cc:1167
#line 417 "d2_parser.yy" // lalr1.cc:1168


void
isc::dhcp::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
