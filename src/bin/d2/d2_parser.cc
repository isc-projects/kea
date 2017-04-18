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
      case 65: // value
      case 92: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 53: // "boolean"
        value.move< bool > (that.value);
        break;

      case 52: // "floating point"
        value.move< double > (that.value);
        break;

      case 51: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 50: // "constant string"
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
      case 65: // value
      case 92: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 53: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 52: // "floating point"
        value.copy< double > (that.value);
        break;

      case 51: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 50: // "constant string"
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
            case 50: // "constant string"

#line 107 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "d2_parser.cc" // lalr1.cc:636
        break;

      case 51: // "integer"

#line 107 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "d2_parser.cc" // lalr1.cc:636
        break;

      case 52: // "floating point"

#line 107 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "d2_parser.cc" // lalr1.cc:636
        break;

      case 53: // "boolean"

#line 107 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "d2_parser.cc" // lalr1.cc:636
        break;

      case 65: // value

#line 107 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "d2_parser.cc" // lalr1.cc:636
        break;

      case 92: // ncr_protocol_value

#line 107 "d2_parser.yy" // lalr1.cc:636
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
      case 65: // value
      case 92: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 53: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 52: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 51: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 50: // "constant string"
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
#line 116 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "d2_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 117 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "d2_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 118 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 642 "d2_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 119 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 648 "d2_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 120 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 654 "d2_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 121 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 660 "d2_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 122 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 666 "d2_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 123 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 672 "d2_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 124 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 678 "d2_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 132 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 684 "d2_parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 133 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 690 "d2_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 134 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "d2_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 135 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "d2_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 136 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 708 "d2_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 137 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 714 "d2_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 138 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 720 "d2_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 141 "d2_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 729 "d2_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 146 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 740 "d2_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 151 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 750 "d2_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 162 "d2_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 759 "d2_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 166 "d2_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 769 "d2_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 173 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 778 "d2_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 176 "d2_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 786 "d2_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 184 "d2_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 795 "d2_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 188 "d2_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 804 "d2_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 199 "d2_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 815 "d2_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 209 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 826 "d2_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 214 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 836 "d2_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 235 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 847 "d2_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 240 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 856 "d2_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 245 "d2_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 866 "d2_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 249 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 874 "d2_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 269 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 882 "d2_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 271 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 892 "d2_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 277 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () <= 0 || yystack_[0].value.as< int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 904 "d2_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 285 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 917 "d2_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 294 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 925 "d2_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 296 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 934 "d2_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 302 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 940 "d2_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 303 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 946 "d2_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 306 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 954 "d2_parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 308 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 964 "d2_parser.cc" // lalr1.cc:859
    break;

  case 75:
#line 314 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 975 "d2_parser.cc" // lalr1.cc:859
    break;

  case 76:
#line 319 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 984 "d2_parser.cc" // lalr1.cc:859
    break;

  case 77:
#line 324 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 995 "d2_parser.cc" // lalr1.cc:859
    break;

  case 78:
#line 329 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1004 "d2_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 348 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1015 "d2_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 353 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1024 "d2_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 358 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1033 "d2_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 361 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1041 "d2_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 373 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1051 "d2_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 377 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1059 "d2_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 381 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1068 "d2_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 384 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1076 "d2_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 399 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1084 "d2_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 401 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1098 "d2_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 411 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "d2_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 413 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1117 "d2_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 423 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1128 "d2_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 428 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1137 "d2_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 433 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1146 "d2_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 436 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1154 "d2_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 444 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1164 "d2_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 448 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1172 "d2_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 452 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1181 "d2_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 455 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1189 "d2_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 469 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1197 "d2_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 471 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1211 "d2_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 481 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1219 "d2_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 483 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1229 "d2_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 489 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () <= 0 || yystack_[0].value.as< int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1241 "d2_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 503 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1252 "d2_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 508 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1261 "d2_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 513 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1270 "d2_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 516 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1278 "d2_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 528 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1288 "d2_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 532 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1296 "d2_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 536 "d2_parser.yy" // lalr1.cc:859
    {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1306 "d2_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 540 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1314 "d2_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 556 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "d2_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 558 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1336 "d2_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 568 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1344 "d2_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 570 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1357 "d2_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 579 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () < 0 || (yystack_[0].value.as< int64_t > () > 0  && (yystack_[0].value.as< int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1369 "d2_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 587 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1377 "d2_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 589 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1390 "d2_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 602 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1398 "d2_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 604 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1407 "d2_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 609 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1415 "d2_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 611 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1424 "d2_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 621 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1435 "d2_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 626 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1444 "d2_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 643 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1455 "d2_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 648 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1464 "d2_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 660 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1474 "d2_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 664 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1482 "d2_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 679 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1490 "d2_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 681 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1500 "d2_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 687 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1509 "d2_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 691 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1517 "d2_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 693 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1527 "d2_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 699 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1538 "d2_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 704 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1547 "d2_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 713 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1557 "d2_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 717 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1565 "d2_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 731 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1573 "d2_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 733 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1583 "d2_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 739 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1592 "d2_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 744 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1601 "d2_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 749 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1610 "d2_parser.cc" // lalr1.cc:859
    break;


#line 1614 "d2_parser.cc" // lalr1.cc:859
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


  const signed char D2Parser::yypact_ninf_ = -108;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short int
  D2Parser::yypact_[] =
  {
      20,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
      11,    -2,    22,    94,    99,    37,   100,   103,   102,   105,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,    -2,    34,
       2,     3,     6,   107,     7,   108,    -5,   109,  -108,   106,
      91,   113,   110,   117,  -108,  -108,  -108,  -108,   118,  -108,
      12,  -108,  -108,  -108,  -108,  -108,  -108,   119,   120,  -108,
    -108,  -108,  -108,  -108,  -108,    51,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,   121,  -108,  -108,  -108,
      67,  -108,  -108,  -108,  -108,  -108,  -108,   122,   123,  -108,
    -108,  -108,  -108,  -108,    68,  -108,  -108,  -108,  -108,  -108,
     124,   128,  -108,  -108,   129,  -108,  -108,    69,  -108,  -108,
    -108,  -108,  -108,    35,  -108,  -108,    -2,    -2,  -108,    82,
     130,   131,   132,   133,  -108,     2,  -108,   136,    92,    93,
     137,   138,   141,   142,   143,     3,  -108,   144,    98,   146,
     147,     6,  -108,     6,  -108,   107,   148,   149,   150,     7,
    -108,     7,  -108,   108,   151,   111,   152,    -5,  -108,    -5,
     109,  -108,  -108,  -108,   153,    -2,    -2,   154,   156,  -108,
     114,  -108,  -108,    87,   139,   158,   159,   155,  -108,   125,
    -108,   126,   127,  -108,    70,  -108,   134,   162,   135,  -108,
      71,  -108,   140,  -108,   145,  -108,    77,  -108,    -2,  -108,
    -108,     3,   157,  -108,  -108,  -108,  -108,  -108,   -13,   -13,
     107,  -108,  -108,  -108,  -108,  -108,   109,  -108,  -108,  -108,
    -108,  -108,  -108,    78,  -108,    79,  -108,  -108,  -108,  -108,
      80,  -108,  -108,  -108,    88,   163,    52,  -108,   164,   157,
    -108,   166,   -13,  -108,  -108,  -108,  -108,   167,  -108,   168,
    -108,   173,   108,  -108,    96,  -108,   175,    10,   173,  -108,
    -108,  -108,  -108,   170,  -108,  -108,    89,  -108,  -108,  -108,
    -108,  -108,  -108,   178,   179,   160,   182,    10,  -108,   165,
     183,  -108,   169,  -108,  -108,   180,  -108,  -108,    97,  -108,
     -12,   180,  -108,  -108,   187,   188,   189,    90,  -108,  -108,
    -108,  -108,  -108,  -108,   190,   161,   171,   172,   -12,  -108,
     174,  -108,  -108,  -108,  -108,  -108
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    34,    28,    24,    23,    20,    21,    22,    27,     3,
      25,    26,    41,     5,    52,     7,   138,     9,   130,    11,
      95,    13,    87,    15,   115,    17,   109,    19,    36,    30,
       0,     0,     0,   132,     0,    89,     0,     0,    38,     0,
      37,     0,     0,    31,   154,   156,    50,   158,     0,    49,
       0,    43,    48,    45,    47,    46,    65,     0,     0,    69,
      73,    75,    77,   128,    64,     0,    54,    56,    57,    58,
      59,    60,    61,    62,    63,   149,     0,   152,   147,   146,
       0,   140,   142,   143,   144,   145,   136,     0,   133,   134,
     105,   107,   103,   102,     0,    97,    99,   100,   101,    93,
       0,    90,    91,   125,     0,   123,   122,     0,   117,   119,
     120,   121,   113,     0,   111,    35,     0,     0,    29,     0,
       0,     0,     0,     0,    40,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,     0,
       0,     0,   139,     0,   131,     0,     0,     0,     0,     0,
      96,     0,    88,     0,     0,     0,     0,     0,   116,     0,
       0,   110,    39,    32,     0,     0,     0,     0,     0,    44,
       0,    67,    68,     0,     0,     0,     0,     0,    55,     0,
     151,     0,     0,   141,     0,   135,     0,     0,     0,    98,
       0,    92,     0,   127,     0,   118,     0,   112,     0,   155,
     157,     0,     0,    66,    71,    72,    70,    74,    79,    79,
     132,   150,   153,   148,   137,   106,     0,   104,    94,   126,
     124,   114,    33,     0,   163,     0,   160,   162,    85,    84,
       0,    80,    81,    83,     0,     0,     0,    51,     0,     0,
     159,     0,     0,    76,    78,   129,   108,     0,   161,     0,
      82,     0,    89,   167,     0,   165,     0,     0,     0,   164,
      86,   176,   181,     0,   179,   175,     0,   169,   171,   173,
     174,   172,   166,     0,     0,     0,     0,     0,   168,     0,
       0,   178,     0,   170,   177,     0,   180,   185,     0,   183,
       0,     0,   182,   193,     0,     0,     0,     0,   187,   189,
     190,   191,   192,   184,     0,     0,     0,     0,     0,   186,
       0,   195,   196,   197,   188,   194
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,   -47,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,   -50,  -108,  -108,  -108,    13,  -108,  -108,  -108,  -108,
     -25,    42,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,   -31,  -108,   -63,  -108,  -108,
    -108,  -108,   -72,  -108,    28,  -108,  -108,  -108,    31,    36,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,   -33,    24,
    -108,  -108,  -108,    27,    30,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,   -22,  -108,    44,  -108,  -108,  -108,
      47,    55,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,   -46,  -108,  -108,  -108,
     -61,  -108,  -108,   -79,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,   -91,  -108,  -108,  -107,  -108,  -108,  -108,  -108,
    -108
  };

  const short int
  D2Parser::yydefgoto_[] =
  {
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    28,    29,    30,    49,    62,    63,    31,    48,    59,
      60,    84,    33,    50,    70,    71,    72,   142,    35,    51,
      85,    86,    87,   147,    88,    89,    90,   150,   226,    91,
     151,    92,   152,    93,   153,   250,   251,   252,   253,   261,
      43,    55,   120,   121,   122,   171,    41,    54,   114,   115,
     116,   168,   117,   166,   118,   167,    47,    57,   133,   134,
     179,    45,    56,   127,   128,   129,   176,   130,   174,   131,
      94,   154,    39,    53,   107,   108,   109,   163,    37,    52,
     100,   101,   102,   160,   103,   157,   104,   105,   159,    73,
     140,    74,   141,    75,   143,   245,   246,   247,   258,   274,
     275,   277,   286,   287,   288,   293,   289,   290,   296,   291,
     294,   308,   309,   310,   317,   318,   319,   324,   320,   321,
     322
  };

  const unsigned short int
  D2Parser::yytable_[] =
  {
      69,    58,    99,    21,   113,    22,   126,    23,   123,   124,
     248,    20,    64,    65,    66,   145,    76,    77,    78,    79,
     146,   125,    80,   313,    81,    82,   314,   315,   316,    32,
      83,   110,   111,    67,    95,    96,    97,    68,   180,    98,
     112,   181,    38,   281,   282,    68,   283,   284,    24,    25,
      26,    27,    68,    68,   155,   180,    68,    68,   266,   156,
      68,     1,     2,     3,     4,     5,     6,     7,     8,     9,
     161,   169,   177,   161,   169,   162,   170,   178,   234,   238,
     177,   155,   259,   262,    61,   241,   257,   260,   263,   182,
     183,   262,   297,   328,   136,    69,   264,   298,   329,   278,
     311,    34,   279,   312,   224,   225,    36,    40,    42,    44,
      46,    99,   135,    99,   106,   119,   132,   137,   138,   113,
     139,   113,   144,   148,   149,   158,   165,   126,   164,   126,
     172,   173,   184,   175,   185,   186,   187,   188,   219,   220,
     190,   193,   194,   191,   192,   195,   196,   197,   199,   200,
     201,   202,   206,   207,   208,   212,   214,   218,   189,   227,
     230,   221,   213,   222,   223,   228,   229,   236,   267,   265,
     269,   242,   271,   272,   295,   231,   232,   233,   249,   249,
     273,   280,   299,   300,   235,   237,   302,   307,   305,   244,
     239,   325,   326,   327,   330,   240,   243,   198,   254,   270,
     276,   211,   210,   256,   217,   209,   216,   215,   255,   205,
     204,   301,   249,   268,   331,   304,   203,   292,   303,   306,
     323,   334,   332,   333,   335,     0,     0,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   285
  };

  const short int
  D2Parser::yycheck_[] =
  {
      50,    48,    52,     5,    54,     7,    56,     9,    13,    14,
      23,     0,    10,    11,    12,     3,    13,    14,    15,    16,
       8,    26,    19,    35,    21,    22,    38,    39,    40,     7,
      27,    24,    25,    31,    28,    29,    30,    50,     3,    33,
      33,     6,     5,    33,    34,    50,    36,    37,    50,    51,
      52,    53,    50,    50,     3,     3,    50,    50,     6,     8,
      50,    41,    42,    43,    44,    45,    46,    47,    48,    49,
       3,     3,     3,     3,     3,     8,     8,     8,     8,     8,
       3,     3,     3,     3,    50,     8,     8,     8,     8,   136,
     137,     3,     3,     3,     3,   145,     8,     8,     8,     3,
       3,     7,     6,     6,    17,    18,     7,     7,     5,     7,
       5,   161,     6,   163,     7,     7,     7,     4,     8,   169,
       3,   171,     4,     4,     4,     4,     3,   177,     6,   179,
       6,     3,    50,     4,     4,     4,     4,     4,   185,   186,
       4,     4,     4,    51,    51,     4,     4,     4,     4,    51,
       4,     4,     4,     4,     4,     4,     4,     4,   145,    20,
       5,     7,    51,     7,    50,     7,     7,     5,     4,     6,
       4,   218,     5,     5,     4,    50,    50,    50,   228,   229,
       7,     6,     4,     4,    50,    50,     4,     7,     5,    32,
      50,     4,     4,     4,     4,    50,   221,   155,   229,   262,
     272,   173,   171,   236,   180,   169,   179,   177,   230,   165,
     163,    51,   262,   259,    53,    50,   161,   278,   297,    50,
     311,   328,    51,    51,    50,    -1,    -1,   277,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   297
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     5,     7,     9,    50,    51,    52,    53,    65,    66,
      67,    71,     7,    76,     7,    82,     7,   142,     5,   136,
       7,   110,     5,   104,     7,   125,     5,   120,    72,    68,
      77,    83,   143,   137,   111,   105,   126,   121,    65,    73,
      74,    50,    69,    70,    10,    11,    12,    31,    50,    75,
      78,    79,    80,   153,   155,   157,    13,    14,    15,    16,
      19,    21,    22,    27,    75,    84,    85,    86,    88,    89,
      90,    93,    95,    97,   134,    28,    29,    30,    33,    75,
     144,   145,   146,   148,   150,   151,     7,   138,   139,   140,
      24,    25,    33,    75,   112,   113,   114,   116,   118,     7,
     106,   107,   108,    13,    14,    26,    75,   127,   128,   129,
     131,   133,     7,   122,   123,     6,     3,     4,     8,     3,
     154,   156,    81,   158,     4,     3,     8,    87,     4,     4,
      91,    94,    96,    98,   135,     3,     8,   149,     4,   152,
     147,     3,     8,   141,     6,     3,   117,   119,   115,     3,
       8,   109,     6,     3,   132,     4,   130,     3,     8,   124,
       3,     6,    65,    65,    50,     4,     4,     4,     4,    79,
       4,    51,    51,     4,     4,     4,     4,     4,    85,     4,
      51,     4,     4,   145,   144,   140,     4,     4,     4,   113,
     112,   108,     4,    51,     4,   128,   127,   123,     4,    65,
      65,     7,     7,    50,    17,    18,    92,    20,     7,     7,
       5,    50,    50,    50,     8,    50,     5,    50,     8,    50,
      50,     8,    65,    84,    32,   159,   160,   161,    23,    75,
      99,   100,   101,   102,    99,   138,   122,     8,   162,     3,
       8,   103,     3,     8,     8,     6,     6,     4,   160,     4,
     101,     5,     5,     7,   163,   164,   106,   165,     3,     6,
       6,    33,    34,    36,    37,    75,   166,   167,   168,   170,
     171,   173,   164,   169,   174,     4,   172,     3,     8,     4,
       4,    51,     4,   167,    50,     5,    50,     7,   175,   176,
     177,     3,     6,    35,    38,    39,    40,   178,   179,   180,
     182,   183,   184,   176,   181,     4,     4,     4,     3,     8,
       4,    53,    51,    51,   179,    50
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    54,    56,    55,    57,    55,    58,    55,    59,    55,
      60,    55,    61,    55,    62,    55,    63,    55,    64,    55,
      65,    65,    65,    65,    65,    65,    65,    66,    68,    67,
      69,    69,    70,    70,    72,    71,    73,    73,    74,    74,
      75,    77,    76,    78,    78,    79,    79,    79,    79,    79,
      81,    80,    83,    82,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    87,    86,    88,    89,    91,
      90,    92,    92,    94,    93,    96,    95,    98,    97,    99,
      99,   100,   100,   101,   101,   103,   102,   105,   104,   106,
     106,   107,   107,   109,   108,   111,   110,   112,   112,   113,
     113,   113,   113,   115,   114,   117,   116,   119,   118,   121,
     120,   122,   122,   124,   123,   126,   125,   127,   127,   128,
     128,   128,   128,   130,   129,   132,   131,   133,   135,   134,
     137,   136,   138,   138,   139,   139,   141,   140,   143,   142,
     144,   144,   145,   145,   145,   145,   145,   147,   146,   149,
     148,   150,   152,   151,   154,   153,   156,   155,   158,   157,
     159,   159,   160,   162,   161,   163,   163,   165,   164,   166,
     166,   167,   167,   167,   167,   167,   169,   168,   170,   172,
     171,   174,   173,   175,   175,   177,   176,   178,   178,   179,
     179,   179,   179,   181,   180,   182,   183,   184
  };

  const unsigned char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     1,     3,     5,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     0,     6,     0,     6,     0,
       1,     1,     3,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     3,     3,     3
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
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS",
  "SUB_TSIG_KEY", "SUB_TSIG_KEYS", "SUB_DDNS_DOMAIN", "SUB_DDNS_DOMAINS",
  "SUB_DNS_SERVER", "SUB_DNS_SERVERS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "value",
  "sub_json", "map2", "$@10", "map_content", "not_empty_map",
  "list_generic", "$@11", "list_content", "not_empty_list",
  "unknown_map_entry", "syntax_map", "$@12", "global_objects",
  "global_object", "dhcpddns_object", "$@13", "sub_dhcpddns", "$@14",
  "dhcpddns_params", "dhcpddns_param", "ip_address", "$@15", "port",
  "dns_server_timeout", "ncr_protocol", "$@16", "ncr_protocol_value",
  "ncr_format", "$@17", "forward_ddns", "$@18", "reverse_ddns", "$@19",
  "ddns_mgr_params", "not_empty_ddns_mgr_params", "ddns_mgr_param",
  "ddns_domains", "$@20", "sub_ddns_domains", "$@21", "ddns_domain_list",
  "not_empty_ddns_domain_list", "ddns_domain", "$@22", "sub_ddns_domain",
  "$@23", "ddns_domain_params", "ddns_domain_param", "ddns_domain_name",
  "$@24", "ddns_domain_key_name", "$@25", "dns_servers", "$@26",
  "sub_dns_servers", "$@27", "dns_server_list", "dns_server", "$@28",
  "sub_dns_server", "$@29", "dns_server_params", "dns_server_param",
  "dns_server_hostname", "$@30", "dns_server_ip_address", "$@31",
  "dns_server_port", "tsig_keys", "$@32", "sub_tsig_keys", "$@33",
  "tsig_keys_list", "not_empty_tsig_keys_list", "tsig_key", "$@34",
  "sub_tsig_key", "$@35", "tsig_key_params", "tsig_key_param",
  "tsig_key_name", "$@36", "tsig_key_algorithm", "$@37",
  "tsig_key_digest_bits", "tsig_key_secret", "$@38", "dhcp6_json_object",
  "$@39", "dhcp4_json_object", "$@40", "logging_object", "$@41",
  "logging_params", "logging_param", "loggers", "$@42", "loggers_entries",
  "logger_entry", "$@43", "logger_params", "logger_param", "name", "$@44",
  "debuglevel", "severity", "$@45", "output_options_list", "$@46",
  "output_options_list_content", "output_entry", "$@47",
  "output_params_list", "output_params", "output", "$@48", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short int
  D2Parser::yyrline_[] =
  {
       0,   116,   116,   116,   117,   117,   118,   118,   119,   119,
     120,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     132,   133,   134,   135,   136,   137,   138,   141,   146,   146,
     158,   159,   162,   166,   173,   173,   180,   181,   184,   188,
     199,   209,   209,   221,   222,   226,   227,   228,   229,   230,
     235,   235,   245,   245,   253,   254,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   269,   269,   277,   285,   294,
     294,   302,   303,   306,   306,   314,   314,   324,   324,   334,
     335,   338,   339,   342,   343,   348,   348,   358,   358,   365,
     366,   369,   370,   373,   373,   381,   381,   388,   389,   392,
     393,   394,   395,   399,   399,   411,   411,   423,   423,   433,
     433,   440,   441,   444,   444,   452,   452,   459,   460,   463,
     464,   465,   466,   469,   469,   481,   481,   489,   503,   503,
     513,   513,   520,   521,   524,   525,   528,   528,   536,   536,
     545,   546,   549,   550,   551,   552,   553,   556,   556,   568,
     568,   579,   587,   587,   602,   602,   609,   609,   621,   621,
     634,   635,   639,   643,   643,   655,   656,   660,   660,   668,
     669,   672,   673,   674,   675,   676,   679,   679,   687,   691,
     691,   699,   699,   709,   710,   713,   713,   721,   722,   725,
     726,   727,   728,   731,   731,   739,   744,   749
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
#line 2246 "d2_parser.cc" // lalr1.cc:1167
#line 754 "d2_parser.yy" // lalr1.cc:1168


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
