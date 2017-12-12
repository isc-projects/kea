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
      case 66: // value
      case 93: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 54: // "boolean"
        value.move< bool > (that.value);
        break;

      case 53: // "floating point"
        value.move< double > (that.value);
        break;

      case 52: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 51: // "constant string"
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
      case 66: // value
      case 93: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 54: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 53: // "floating point"
        value.copy< double > (that.value);
        break;

      case 52: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 51: // "constant string"
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
            case 51: // "constant string"

#line 108 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "d2_parser.cc" // lalr1.cc:636
        break;

      case 52: // "integer"

#line 108 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "d2_parser.cc" // lalr1.cc:636
        break;

      case 53: // "floating point"

#line 108 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "d2_parser.cc" // lalr1.cc:636
        break;

      case 54: // "boolean"

#line 108 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "d2_parser.cc" // lalr1.cc:636
        break;

      case 66: // value

#line 108 "d2_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "d2_parser.cc" // lalr1.cc:636
        break;

      case 93: // ncr_protocol_value

#line 108 "d2_parser.yy" // lalr1.cc:636
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
      case 66: // value
      case 93: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 54: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 53: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 52: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 51: // "constant string"
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
#line 117 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "d2_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 118 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "d2_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 119 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 642 "d2_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 120 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 648 "d2_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 121 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 654 "d2_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 122 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 660 "d2_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 123 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 666 "d2_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 124 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 672 "d2_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 125 "d2_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 678 "d2_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 133 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 684 "d2_parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 134 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 690 "d2_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 135 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "d2_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 136 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "d2_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 137 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 708 "d2_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 138 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 714 "d2_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 139 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 720 "d2_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 142 "d2_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 729 "d2_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 147 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 740 "d2_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 152 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 750 "d2_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 163 "d2_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 759 "d2_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 167 "d2_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 769 "d2_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 174 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 778 "d2_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 177 "d2_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 786 "d2_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 185 "d2_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 795 "d2_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 189 "d2_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 804 "d2_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 200 "d2_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 815 "d2_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 210 "d2_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 826 "d2_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 215 "d2_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 836 "d2_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 237 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 847 "d2_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 242 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 856 "d2_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 247 "d2_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 866 "d2_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 251 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 874 "d2_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 271 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 882 "d2_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 273 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 892 "d2_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 279 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () <= 0 || yystack_[0].value.as< int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 904 "d2_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 287 "d2_parser.yy" // lalr1.cc:859
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

  case 70:
#line 296 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 925 "d2_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 298 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 934 "d2_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 304 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 940 "d2_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 305 "d2_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 946 "d2_parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 308 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 954 "d2_parser.cc" // lalr1.cc:859
    break;

  case 75:
#line 310 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 964 "d2_parser.cc" // lalr1.cc:859
    break;

  case 76:
#line 316 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 975 "d2_parser.cc" // lalr1.cc:859
    break;

  case 77:
#line 321 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 984 "d2_parser.cc" // lalr1.cc:859
    break;

  case 78:
#line 326 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 995 "d2_parser.cc" // lalr1.cc:859
    break;

  case 79:
#line 331 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1004 "d2_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 350 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1015 "d2_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 355 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1024 "d2_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 360 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1033 "d2_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 363 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1041 "d2_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 375 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1051 "d2_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 379 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1059 "d2_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 383 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1068 "d2_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 386 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1076 "d2_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 401 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1084 "d2_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 403 "d2_parser.yy" // lalr1.cc:859
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

  case 106:
#line 413 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "d2_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 415 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr elem(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1117 "d2_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 425 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1128 "d2_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 430 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1137 "d2_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 435 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1146 "d2_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 438 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1154 "d2_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 446 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1164 "d2_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 450 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1172 "d2_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 454 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1181 "d2_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 457 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1189 "d2_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 471 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1197 "d2_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 473 "d2_parser.yy" // lalr1.cc:859
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

  case 126:
#line 483 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1219 "d2_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 485 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1229 "d2_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 491 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () <= 0 || yystack_[0].value.as< int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1241 "d2_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 505 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1252 "d2_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 510 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1261 "d2_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 515 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1270 "d2_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 518 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1278 "d2_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 530 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1288 "d2_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 534 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1296 "d2_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 538 "d2_parser.yy" // lalr1.cc:859
    {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1306 "d2_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 542 "d2_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1314 "d2_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 558 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "d2_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 560 "d2_parser.yy" // lalr1.cc:859
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

  case 150:
#line 570 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1344 "d2_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 572 "d2_parser.yy" // lalr1.cc:859
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

  case 152:
#line 581 "d2_parser.yy" // lalr1.cc:859
    {
    if (yystack_[0].value.as< int64_t > () < 0 || (yystack_[0].value.as< int64_t > () > 0  && (yystack_[0].value.as< int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1369 "d2_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 589 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1377 "d2_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 591 "d2_parser.yy" // lalr1.cc:859
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

  case 155:
#line 604 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1398 "d2_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 606 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1407 "d2_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 611 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1415 "d2_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 613 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1424 "d2_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 618 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "d2_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 620 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1441 "d2_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 630 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1452 "d2_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 635 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1461 "d2_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 652 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1472 "d2_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 657 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1481 "d2_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 669 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1491 "d2_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 673 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1499 "d2_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 688 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1507 "d2_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 690 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1517 "d2_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 696 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1526 "d2_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 700 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1534 "d2_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 702 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1544 "d2_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 708 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1555 "d2_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 713 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1564 "d2_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 722 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1574 "d2_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 726 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1582 "d2_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 740 "d2_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1590 "d2_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 742 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1600 "d2_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 748 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1609 "d2_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 753 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1618 "d2_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 758 "d2_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1627 "d2_parser.cc" // lalr1.cc:859
    break;


#line 1631 "d2_parser.cc" // lalr1.cc:859
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


  const signed char D2Parser::yypact_ninf_ = -111;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short int
  D2Parser::yypact_[] =
  {
      20,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
      24,    -2,    35,    51,    96,    31,   100,   101,   102,   103,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,    -2,    59,
       2,     3,    10,   104,     4,   105,    -6,   106,  -111,   109,
     114,   115,   110,   117,  -111,  -111,  -111,  -111,  -111,   119,
    -111,     8,  -111,  -111,  -111,  -111,  -111,  -111,  -111,   121,
     122,  -111,  -111,  -111,  -111,  -111,  -111,    19,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,   123,  -111,
    -111,  -111,    25,  -111,  -111,  -111,  -111,  -111,  -111,   125,
     118,  -111,  -111,  -111,  -111,  -111,    68,  -111,  -111,  -111,
    -111,  -111,   127,   126,  -111,  -111,   124,  -111,  -111,    69,
    -111,  -111,  -111,  -111,  -111,    29,  -111,  -111,    -2,    -2,
    -111,    83,   131,   132,   133,   134,   135,  -111,     2,  -111,
     136,    92,    93,   142,   143,   144,   145,   146,     3,  -111,
     147,   107,   148,   149,    10,  -111,    10,  -111,   104,   150,
     151,   152,     4,  -111,     4,  -111,   105,   153,   108,   154,
      -6,  -111,    -6,   106,  -111,  -111,  -111,   157,    -2,    -2,
      -2,   155,   156,  -111,   113,  -111,  -111,    77,   158,   159,
     160,   163,  -111,   120,  -111,   129,   130,  -111,    71,  -111,
     137,   164,   138,  -111,    72,  -111,   139,  -111,   140,  -111,
      75,  -111,    -2,  -111,  -111,  -111,     3,   141,  -111,  -111,
    -111,  -111,  -111,   -14,   -14,   104,  -111,  -111,  -111,  -111,
    -111,   106,  -111,  -111,  -111,  -111,  -111,  -111,    78,  -111,
      79,  -111,  -111,  -111,  -111,    81,  -111,  -111,  -111,    82,
     166,    94,  -111,   161,   141,  -111,   169,   -14,  -111,  -111,
    -111,  -111,   165,  -111,   171,  -111,   170,   105,  -111,    98,
    -111,   172,    22,   170,  -111,  -111,  -111,  -111,   178,  -111,
    -111,    85,  -111,  -111,  -111,  -111,  -111,  -111,   181,   182,
     162,   183,    22,  -111,   167,   187,  -111,   168,  -111,  -111,
     186,  -111,  -111,    99,  -111,     7,   186,  -111,  -111,   190,
     191,   192,    91,  -111,  -111,  -111,  -111,  -111,  -111,   193,
     173,   174,   176,     7,  -111,   179,  -111,  -111,  -111,  -111,
    -111
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    34,    28,    24,    23,    20,    21,    22,    27,     3,
      25,    26,    41,     5,    53,     7,   139,     9,   131,    11,
      96,    13,    88,    15,   116,    17,   110,    19,    36,    30,
       0,     0,     0,   133,     0,    90,     0,     0,    38,     0,
      37,     0,     0,    31,   155,   157,   159,    51,   161,     0,
      50,     0,    43,    48,    45,    47,    49,    46,    66,     0,
       0,    70,    74,    76,    78,   129,    65,     0,    55,    57,
      58,    59,    60,    61,    62,    63,    64,   150,     0,   153,
     148,   147,     0,   141,   143,   144,   145,   146,   137,     0,
     134,   135,   106,   108,   104,   103,     0,    98,   100,   101,
     102,    94,     0,    91,    92,   126,     0,   124,   123,     0,
     118,   120,   121,   122,   114,     0,   112,    35,     0,     0,
      29,     0,     0,     0,     0,     0,     0,    40,     0,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
       0,     0,     0,     0,     0,   140,     0,   132,     0,     0,
       0,     0,     0,    97,     0,    89,     0,     0,     0,     0,
       0,   117,     0,     0,   111,    39,    32,     0,     0,     0,
       0,     0,     0,    44,     0,    68,    69,     0,     0,     0,
       0,     0,    56,     0,   152,     0,     0,   142,     0,   136,
       0,     0,     0,    99,     0,    93,     0,   128,     0,   119,
       0,   113,     0,   156,   158,   160,     0,     0,    67,    72,
      73,    71,    75,    80,    80,   133,   151,   154,   149,   138,
     107,     0,   105,    95,   127,   125,   115,    33,     0,   166,
       0,   163,   165,    86,    85,     0,    81,    82,    84,     0,
       0,     0,    52,     0,     0,   162,     0,     0,    77,    79,
     130,   109,     0,   164,     0,    83,     0,    90,   170,     0,
     168,     0,     0,     0,   167,    87,   179,   184,     0,   182,
     178,     0,   172,   174,   176,   177,   175,   169,     0,     0,
       0,     0,     0,   171,     0,     0,   181,     0,   173,   180,
       0,   183,   188,     0,   186,     0,     0,   185,   196,     0,
       0,     0,     0,   190,   192,   193,   194,   195,   187,     0,
       0,     0,     0,     0,   189,     0,   198,   199,   200,   191,
     197
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,   -47,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,   -50,  -111,  -111,  -111,    50,  -111,  -111,  -111,  -111,
     -27,    42,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,   -33,  -111,   -65,  -111,  -111,
    -111,  -111,   -74,  -111,    28,  -111,  -111,  -111,    32,    33,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,   -34,    26,
    -111,  -111,  -111,    30,    36,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,   -25,  -111,    40,  -111,  -111,  -111,
      45,    49,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,   -49,  -111,
    -111,  -111,   -63,  -111,  -111,   -81,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,   -94,  -111,  -111,  -110,  -111,  -111,
    -111,  -111,  -111
  };

  const short int
  D2Parser::yydefgoto_[] =
  {
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    28,    29,    30,    49,    62,    63,    31,    48,    59,
      60,    86,    33,    50,    71,    72,    73,   145,    35,    51,
      87,    88,    89,   150,    90,    91,    92,   153,   231,    93,
     154,    94,   155,    95,   156,   255,   256,   257,   258,   266,
      43,    55,   122,   123,   124,   174,    41,    54,   116,   117,
     118,   171,   119,   169,   120,   170,    47,    57,   135,   136,
     182,    45,    56,   129,   130,   131,   179,   132,   177,   133,
      96,   157,    39,    53,   109,   110,   111,   166,    37,    52,
     102,   103,   104,   163,   105,   160,   106,   107,   162,    74,
     142,    75,   143,    76,   144,    77,   146,   250,   251,   252,
     263,   279,   280,   282,   291,   292,   293,   298,   294,   295,
     301,   296,   299,   313,   314,   315,   322,   323,   324,   329,
     325,   326,   327
  };

  const unsigned short int
  D2Parser::yytable_[] =
  {
      70,    58,   101,    21,   115,    22,   128,    23,   125,   126,
     253,   148,    64,    65,    66,    67,   149,    78,    79,    80,
      81,   127,   158,    82,    20,    83,    84,   159,   164,   112,
     113,    85,   183,   165,    68,   184,    38,    69,   114,    97,
      98,    99,    32,   318,   100,    69,   319,   320,   321,    24,
      25,    26,    27,    69,    69,    69,   286,   287,    34,   288,
     289,    69,     1,     2,     3,     4,     5,     6,     7,     8,
       9,   172,   180,    69,   164,   172,   173,   181,   180,   239,
     243,   158,   264,   246,   267,   267,   262,   265,   302,   268,
     269,   185,   186,   303,   333,   229,   230,   183,    70,   334,
     271,   283,   316,    36,   284,   317,    42,    40,    46,    44,
      61,   108,   121,   134,   101,   137,   101,   138,   140,   139,
     141,   168,   115,   147,   115,   151,   152,   161,   178,   176,
     128,   167,   128,   175,   187,   188,   189,   190,   191,   192,
     194,   223,   224,   225,   195,   196,   197,   198,   199,   200,
     201,   203,   205,   206,   210,   211,   212,   216,   218,   204,
     217,   222,   226,   227,   228,   272,   233,   234,   235,   241,
     276,   236,   270,   274,   249,   247,   277,   278,   285,   232,
     237,   238,   300,   254,   254,   304,   305,   307,   240,   242,
     244,   245,   310,   312,   330,   331,   332,   335,   193,   248,
     202,   259,   275,   281,   215,   213,   214,   261,   209,   221,
     260,   208,   220,   207,   306,   273,   219,   254,   309,   311,
     297,   308,   328,   339,     0,     0,   337,   336,   338,     0,
     340,     0,   290,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   290
  };

  const short int
  D2Parser::yycheck_[] =
  {
      50,    48,    52,     5,    54,     7,    56,     9,    14,    15,
      24,     3,    10,    11,    12,    13,     8,    14,    15,    16,
      17,    27,     3,    20,     0,    22,    23,     8,     3,    25,
      26,    28,     3,     8,    32,     6,     5,    51,    34,    29,
      30,    31,     7,    36,    34,    51,    39,    40,    41,    51,
      52,    53,    54,    51,    51,    51,    34,    35,     7,    37,
      38,    51,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     3,     3,    51,     3,     3,     8,     8,     3,     8,
       8,     3,     3,     8,     3,     3,     8,     8,     3,     8,
       8,   138,   139,     8,     3,    18,    19,     3,   148,     8,
       6,     3,     3,     7,     6,     6,     5,     7,     5,     7,
      51,     7,     7,     7,   164,     6,   166,     3,     8,     4,
       3,     3,   172,     4,   174,     4,     4,     4,     4,     3,
     180,     6,   182,     6,    51,     4,     4,     4,     4,     4,
       4,   188,   189,   190,    52,    52,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    52,
      52,     4,     7,     7,    51,     4,     7,     7,     5,     5,
       5,    51,     6,     4,    33,   222,     5,     7,     6,    21,
      51,    51,     4,   233,   234,     4,     4,     4,    51,    51,
      51,    51,     5,     7,     4,     4,     4,     4,   148,   226,
     158,   234,   267,   277,   176,   172,   174,   241,   168,   183,
     235,   166,   182,   164,    52,   264,   180,   267,    51,    51,
     283,   302,   316,   333,    -1,    -1,    52,    54,    52,    -1,
      51,    -1,   282,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   302
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       0,     5,     7,     9,    51,    52,    53,    54,    66,    67,
      68,    72,     7,    77,     7,    83,     7,   143,     5,   137,
       7,   111,     5,   105,     7,   126,     5,   121,    73,    69,
      78,    84,   144,   138,   112,   106,   127,   122,    66,    74,
      75,    51,    70,    71,    10,    11,    12,    13,    32,    51,
      76,    79,    80,    81,   154,   156,   158,   160,    14,    15,
      16,    17,    20,    22,    23,    28,    76,    85,    86,    87,
      89,    90,    91,    94,    96,    98,   135,    29,    30,    31,
      34,    76,   145,   146,   147,   149,   151,   152,     7,   139,
     140,   141,    25,    26,    34,    76,   113,   114,   115,   117,
     119,     7,   107,   108,   109,    14,    15,    27,    76,   128,
     129,   130,   132,   134,     7,   123,   124,     6,     3,     4,
       8,     3,   155,   157,   159,    82,   161,     4,     3,     8,
      88,     4,     4,    92,    95,    97,    99,   136,     3,     8,
     150,     4,   153,   148,     3,     8,   142,     6,     3,   118,
     120,   116,     3,     8,   110,     6,     3,   133,     4,   131,
       3,     8,   125,     3,     6,    66,    66,    51,     4,     4,
       4,     4,     4,    80,     4,    52,    52,     4,     4,     4,
       4,     4,    86,     4,    52,     4,     4,   146,   145,   141,
       4,     4,     4,   114,   113,   109,     4,    52,     4,   129,
     128,   124,     4,    66,    66,    66,     7,     7,    51,    18,
      19,    93,    21,     7,     7,     5,    51,    51,    51,     8,
      51,     5,    51,     8,    51,    51,     8,    66,    85,    33,
     162,   163,   164,    24,    76,   100,   101,   102,   103,   100,
     139,   123,     8,   165,     3,     8,   104,     3,     8,     8,
       6,     6,     4,   163,     4,   102,     5,     5,     7,   166,
     167,   107,   168,     3,     6,     6,    34,    35,    37,    38,
      76,   169,   170,   171,   173,   174,   176,   167,   172,   177,
       4,   175,     3,     8,     4,     4,    52,     4,   170,    51,
       5,    51,     7,   178,   179,   180,     3,     6,    36,    39,
      40,    41,   181,   182,   183,   185,   186,   187,   179,   184,
       4,     4,     4,     3,     8,     4,    54,    52,    52,   182,
      51
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    55,    57,    56,    58,    56,    59,    56,    60,    56,
      61,    56,    62,    56,    63,    56,    64,    56,    65,    56,
      66,    66,    66,    66,    66,    66,    66,    67,    69,    68,
      70,    70,    71,    71,    73,    72,    74,    74,    75,    75,
      76,    78,    77,    79,    79,    80,    80,    80,    80,    80,
      80,    82,    81,    84,    83,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    88,    87,    89,    90,
      92,    91,    93,    93,    95,    94,    97,    96,    99,    98,
     100,   100,   101,   101,   102,   102,   104,   103,   106,   105,
     107,   107,   108,   108,   110,   109,   112,   111,   113,   113,
     114,   114,   114,   114,   116,   115,   118,   117,   120,   119,
     122,   121,   123,   123,   125,   124,   127,   126,   128,   128,
     129,   129,   129,   129,   131,   130,   133,   132,   134,   136,
     135,   138,   137,   139,   139,   140,   140,   142,   141,   144,
     143,   145,   145,   146,   146,   146,   146,   146,   148,   147,
     150,   149,   151,   153,   152,   155,   154,   157,   156,   159,
     158,   161,   160,   162,   162,   163,   165,   164,   166,   166,
     168,   167,   169,   169,   170,   170,   170,   170,   170,   172,
     171,   173,   175,   174,   177,   176,   178,   178,   180,   179,
     181,   181,   182,   182,   182,   182,   184,   183,   185,   186,
     187
  };

  const unsigned char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     1,     3,     5,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     0,     6,     0,     6,
       0,     1,     1,     3,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     0,
       6,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const D2Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"Dhcp4\"",
  "\"Control-agent\"", "\"DhcpDdns\"", "\"ip-address\"", "\"port\"",
  "\"dns-server-timeout\"", "\"ncr-protocol\"", "\"UDP\"", "\"TCP\"",
  "\"ncr-format\"", "\"JSON\"", "\"forward-ddns\"", "\"reverse-ddns\"",
  "\"ddns-domains\"", "\"key-name\"", "\"dns-servers\"", "\"hostname\"",
  "\"tsig-keys\"", "\"algorithm\"", "\"digest-bits\"", "\"secret\"",
  "\"Logging\"", "\"loggers\"", "\"name\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCPDDNS",
  "SUB_DHCPDDNS", "SUB_TSIG_KEY", "SUB_TSIG_KEYS", "SUB_DDNS_DOMAIN",
  "SUB_DDNS_DOMAINS", "SUB_DNS_SERVER", "SUB_DNS_SERVERS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "value", "sub_json", "map2", "$@10",
  "map_content", "not_empty_map", "list_generic", "$@11", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@12",
  "global_objects", "global_object", "dhcpddns_object", "$@13",
  "sub_dhcpddns", "$@14", "dhcpddns_params", "dhcpddns_param",
  "ip_address", "$@15", "port", "dns_server_timeout", "ncr_protocol",
  "$@16", "ncr_protocol_value", "ncr_format", "$@17", "forward_ddns",
  "$@18", "reverse_ddns", "$@19", "ddns_mgr_params",
  "not_empty_ddns_mgr_params", "ddns_mgr_param", "ddns_domains", "$@20",
  "sub_ddns_domains", "$@21", "ddns_domain_list",
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
  "$@39", "dhcp4_json_object", "$@40", "control_agent_json_object", "$@41",
  "logging_object", "$@42", "logging_params", "logging_param", "loggers",
  "$@43", "loggers_entries", "logger_entry", "$@44", "logger_params",
  "logger_param", "name", "$@45", "debuglevel", "severity", "$@46",
  "output_options_list", "$@47", "output_options_list_content",
  "output_entry", "$@48", "output_params_list", "output_params", "output",
  "$@49", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short int
  D2Parser::yyrline_[] =
  {
       0,   117,   117,   117,   118,   118,   119,   119,   120,   120,
     121,   121,   122,   122,   123,   123,   124,   124,   125,   125,
     133,   134,   135,   136,   137,   138,   139,   142,   147,   147,
     159,   160,   163,   167,   174,   174,   181,   182,   185,   189,
     200,   210,   210,   222,   223,   227,   228,   229,   230,   231,
     232,   237,   237,   247,   247,   255,   256,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   271,   271,   279,   287,
     296,   296,   304,   305,   308,   308,   316,   316,   326,   326,
     336,   337,   340,   341,   344,   345,   350,   350,   360,   360,
     367,   368,   371,   372,   375,   375,   383,   383,   390,   391,
     394,   395,   396,   397,   401,   401,   413,   413,   425,   425,
     435,   435,   442,   443,   446,   446,   454,   454,   461,   462,
     465,   466,   467,   468,   471,   471,   483,   483,   491,   505,
     505,   515,   515,   522,   523,   526,   527,   530,   530,   538,
     538,   547,   548,   551,   552,   553,   554,   555,   558,   558,
     570,   570,   581,   589,   589,   604,   604,   611,   611,   618,
     618,   630,   630,   643,   644,   648,   652,   652,   664,   665,
     669,   669,   677,   678,   681,   682,   683,   684,   685,   688,
     688,   696,   700,   700,   708,   708,   718,   719,   722,   722,
     730,   731,   734,   735,   736,   737,   740,   740,   748,   753,
     758
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
#line 2272 "d2_parser.cc" // lalr1.cc:1167
#line 763 "d2_parser.yy" // lalr1.cc:1168


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
