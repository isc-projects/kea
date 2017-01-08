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
#define yylex   parser6_lex

// First part of user declarations.

#line 39 "dhcp6_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp6_parser.h"

// User implementation prologue.

#line 53 "dhcp6_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:413

#include <dhcp6/parser_context.h>

#line 59 "dhcp6_parser.cc" // lalr1.cc:413


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
#if PARSER6_DEBUG

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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp6_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
    :
#if PARSER6_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 116: // value
        value.move< ElementPtr > (that.value);
        break;

      case 102: // "boolean"
        value.move< bool > (that.value);
        break;

      case 101: // "floating point"
        value.move< double > (that.value);
        break;

      case 100: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 99: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 116: // value
        value.copy< ElementPtr > (that.value);
        break;

      case 102: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 101: // "floating point"
        value.copy< double > (that.value);
        break;

      case 100: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 99: // "constant string"
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
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo,
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
            case 99: // "constant string"

#line 189 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 352 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 100: // "integer"

#line 189 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 359 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 101: // "floating point"

#line 189 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 366 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 102: // "boolean"

#line 189 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 373 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 116: // value

#line 189 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 380 "dhcp6_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp6Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  inline Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::parse ()
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
      case 116: // value
        yylhs.value.build< ElementPtr > ();
        break;

      case 102: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 101: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 100: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 99: // "constant string"
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
#line 198 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 199 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 200 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 201 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 202 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 203 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 204 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 205 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 662 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 206 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 207 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 208 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 216 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 217 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 218 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 219 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 220 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 221 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 731 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 832 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 294 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 863 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 339 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 981 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1019 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1030 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1263 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1274 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }
    ctx.stack_.pop_back();
}
#line 1436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1562 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1573 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 824 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1582 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1618 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1681 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 994 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1867 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 1966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1153 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1158 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1206 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1228 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1234 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2088 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2106 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2136 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2380 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2425 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2434 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2489 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2510 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2529 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2537 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2555 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
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
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Dhcp6Parser::yypact_ninf_ = -427;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     184,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,    49,    19,    46,    52,    60,    77,    87,    93,
      95,    99,   108,   110,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,    19,    24,    17,    85,
     123,    23,    25,   145,   107,    53,     6,   -33,  -427,   119,
     141,   142,   149,   160,  -427,  -427,  -427,  -427,   161,  -427,
      47,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   187,
     188,   189,   203,   228,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   232,  -427,  -427,  -427,    48,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   193,  -427,  -427,  -427,  -427,  -427,  -427,   233,
     235,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
      54,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,    57,  -427,  -427,
    -427,   236,  -427,   237,   238,  -427,  -427,   150,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   239,   240,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   244,  -427,  -427,  -427,   247,  -427,  -427,
    -427,   251,   252,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   256,  -427,  -427,  -427,  -427,   253,
     259,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
     173,  -427,  -427,  -427,  -427,    19,    19,  -427,   165,   262,
     264,   279,   280,  -427,    17,  -427,   281,   282,   283,   190,
     192,   194,   195,   196,   284,   285,   287,   289,   293,   294,
     295,   296,   297,   298,   204,   299,   301,    85,  -427,   302,
    -427,     2,   303,   304,   305,   306,   307,   213,   215,   308,
     310,   311,   312,    23,  -427,   314,    25,  -427,   315,   220,
     317,   222,   223,   145,  -427,   320,   321,   322,   323,   324,
     325,  -427,   107,   326,   327,   234,   328,   329,   331,   241,
    -427,    53,   332,   242,  -427,     6,   333,   334,     9,  -427,
    -427,  -427,   335,   338,   339,    19,    19,  -427,   342,   343,
     344,  -427,  -427,  -427,  -427,  -427,   336,   337,   347,   348,
     349,   350,   351,   352,   356,   357,  -427,   358,   359,  -427,
     353,  -427,  -427,  -427,  -427,   360,   364,  -427,  -427,  -427,
     366,   367,   270,   274,   275,  -427,  -427,   276,   277,   373,
     374,  -427,   286,  -427,   288,  -427,   290,  -427,  -427,  -427,
     353,   353,   353,   291,   292,   300,  -427,   309,   313,  -427,
     316,   318,   319,  -427,  -427,   330,  -427,  -427,   340,    19,
    -427,    19,    85,   341,  -427,  -427,   123,   111,   111,   375,
     376,   377,   -17,    19,    31,    22,   379,   345,    76,    56,
      24,  -427,  -427,   388,  -427,     2,   386,   387,  -427,  -427,
    -427,  -427,  -427,   389,   346,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   174,  -427,   175,  -427,  -427,   372,  -427,
    -427,  -427,   391,   393,   394,  -427,   177,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,   191,  -427,   395,   397,
    -427,  -427,   396,   400,  -427,  -427,   398,   402,  -427,  -427,
    -427,    72,  -427,  -427,  -427,   401,  -427,  -427,   139,  -427,
    -427,  -427,   153,  -427,   403,   407,  -427,   409,   197,  -427,
    -427,   410,   412,   415,  -427,  -427,  -427,   200,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,   201,  -427,  -427,  -427,   208,
     354,   355,  -427,  -427,   414,   421,  -427,  -427,   419,   423,
    -427,  -427,   422,   424,  -427,  -427,   425,  -427,   426,   341,
    -427,  -427,   427,   428,   430,   361,   362,   363,   111,  -427,
    -427,    23,  -427,   375,    53,  -427,   376,     6,  -427,   377,
     -17,  -427,  -427,    31,  -427,    22,  -427,   -33,  -427,   379,
     368,   345,  -427,   431,   369,   370,   371,    76,  -427,   432,
     433,    56,  -427,  -427,  -427,   434,   435,  -427,    25,  -427,
     386,   145,  -427,   387,   107,  -427,   389,   437,  -427,   438,
    -427,   365,   378,   380,  -427,  -427,  -427,  -427,   210,  -427,
     439,  -427,   440,  -427,  -427,  -427,  -427,   211,  -427,  -427,
    -427,   381,  -427,  -427,  -427,  -427,   382,   383,  -427,  -427,
     384,   212,  -427,   214,  -427,   441,  -427,   385,   399,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,   224,  -427,   113,   399,  -427,
    -427,   442,  -427,  -427,  -427,   218,  -427,  -427,  -427,  -427,
    -427,   446,   390,   447,   113,  -427,   450,  -427,   392,  -427,
     445,  -427,  -427,   225,  -427,   257,   445,  -427,  -427,   221,
    -427,  -427,   452,   257,  -427,   404,  -427,  -427
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    51,     5,    62,     7,
      95,     9,   176,    11,   277,    13,   294,    15,   320,    17,
     217,    19,   251,    21,   152,    23,    40,    34,     0,     0,
       0,     0,     0,     0,   322,   219,   253,     0,    42,     0,
      41,     0,     0,    35,    60,   400,   396,   398,     0,    59,
       0,    53,    55,    57,    58,    56,    93,    99,   101,     0,
       0,     0,     0,     0,   168,   209,   243,   127,   142,   135,
     350,   144,   163,   367,     0,   384,   394,    87,     0,    64,
      66,    67,    68,    69,    70,    72,    73,    74,    75,    77,
      76,    81,    82,    71,    79,    80,    78,    83,    84,    85,
      86,    97,     0,   354,   269,   286,   197,   199,   201,     0,
       0,   205,   203,   312,   346,   196,   180,   181,   182,   183,
       0,   178,   187,   188,   189,   192,   194,   190,   191,   184,
     185,   186,   193,   195,   284,   283,   282,     0,   279,   281,
     305,     0,   308,     0,     0,   304,   301,     0,   296,   298,
     299,   302,   303,   300,   344,   334,   336,   338,   340,   342,
     333,   332,     0,   323,   324,   328,   329,   326,   330,   331,
     327,   114,   122,     0,   237,   235,   240,     0,   230,   234,
     231,     0,   220,   221,   223,   233,   224,   225,   226,   239,
     227,   228,   229,   264,     0,   262,   263,   266,   267,     0,
     254,   255,   257,   258,   259,   260,   261,   159,   161,   156,
       0,   154,   157,   158,    39,     0,     0,    33,     0,     0,
       0,     0,     0,    50,     0,    52,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,     0,
      96,   356,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   177,     0,     0,   278,     0,     0,
       0,     0,     0,     0,   295,     0,     0,     0,     0,     0,
       0,   321,     0,     0,     0,     0,     0,     0,     0,     0,
     218,     0,     0,     0,   252,     0,     0,     0,     0,   153,
      43,    36,     0,     0,     0,     0,     0,    54,     0,     0,
       0,    88,    89,    90,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   383,     0,     0,    65,
       0,   365,   363,   364,   362,     0,   357,   358,   360,   361,
       0,     0,     0,     0,     0,   207,   208,     0,     0,     0,
       0,   179,     0,   280,     0,   307,     0,   310,   311,   297,
       0,     0,     0,     0,     0,     0,   325,     0,     0,   232,
       0,     0,     0,   242,   222,     0,   268,   256,     0,     0,
     155,     0,     0,     0,   397,   399,     0,     0,     0,   170,
     211,   245,     0,    40,     0,     0,   146,     0,     0,     0,
       0,    44,    98,     0,   355,     0,   271,   288,   198,   200,
     202,   206,   204,   314,     0,   285,   306,   309,   345,   335,
     337,   339,   341,   343,   115,   123,   238,   236,   241,   265,
     160,   162,    37,     0,   405,     0,   402,   404,     0,   116,
     118,   120,     0,     0,     0,   113,     0,   103,   105,   106,
     107,   108,   109,   110,   111,   112,     0,   174,     0,   171,
     172,   215,     0,   212,   213,   249,     0,   246,   247,   133,
     134,     0,   129,   131,   132,     0,   141,   139,     0,   137,
     140,   352,     0,   150,     0,   147,   148,     0,     0,   165,
     379,     0,     0,     0,   377,   371,   376,     0,   369,   374,
     372,   373,   375,   390,   392,     0,   386,   388,   389,     0,
      46,     0,   359,   275,     0,   272,   273,   292,     0,   289,
     290,   318,     0,   315,   316,   348,     0,    61,     0,     0,
     401,    94,     0,     0,     0,     0,     0,     0,     0,   100,
     102,     0,   169,     0,   219,   210,     0,   253,   244,     0,
       0,   128,   143,     0,   136,     0,   351,     0,   145,     0,
       0,     0,   164,     0,     0,     0,     0,     0,   368,     0,
       0,     0,   385,   395,    48,     0,    47,   366,     0,   270,
       0,     0,   287,     0,   322,   313,     0,     0,   347,     0,
     403,     0,     0,     0,   124,   125,   126,   104,     0,   173,
       0,   214,     0,   248,   130,   138,   353,     0,   149,   167,
     166,     0,   378,   381,   382,   370,     0,     0,   387,    45,
       0,     0,   274,     0,   291,     0,   317,     0,     0,   117,
     119,   121,   175,   216,   250,   151,   380,   391,   393,    49,
     276,   293,   319,   349,   409,     0,   407,     0,     0,   406,
     421,     0,   419,   417,   413,     0,   411,   415,   416,   414,
     408,     0,     0,     0,     0,   410,     0,   418,     0,   412,
       0,   420,   425,     0,   423,     0,     0,   422,   429,     0,
     427,   424,     0,     0,   426,     0,   428,   430
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,    12,  -427,  -427,  -427,  -427,    15,  -427,
    -427,    34,  -427,  -349,  -427,  -427,  -427,   -58,  -427,  -427,
    -427,   205,  -427,  -427,  -427,  -427,    30,   181,   -60,   -43,
     -41,   -40,  -427,  -427,  -427,  -427,  -427,    44,  -427,  -427,
    -427,  -427,  -427,    43,  -102,  -395,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   -56,  -427,  -426,  -427,  -427,  -427,  -427,
    -427,  -113,  -411,  -427,  -427,  -427,  -427,  -111,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -116,  -427,  -427,  -427,  -112,
     146,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -115,  -427,
    -427,  -427,  -427,   -95,  -427,  -427,  -427,   -86,   199,  -427,
    -427,  -427,  -427,  -427,  -427,  -406,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,   -90,  -427,  -427,  -427,   -87,
    -427,   167,  -427,   -55,  -427,  -427,  -427,  -427,   -54,  -427,
    -427,  -427,  -427,  -427,   -47,  -427,  -427,  -427,   -85,  -427,
    -427,  -427,   -88,  -427,   168,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -114,  -427,  -427,  -427,  -110,
     206,  -427,  -427,  -427,  -427,  -427,  -427,  -118,  -427,  -427,
    -427,  -107,   198,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -119,  -427,  -427,  -427,  -109,  -427,
     202,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,    64,  -427,  -427,  -427,  -427,  -427,  -427,
     -97,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
     -94,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   -53,  -427,  -427,  -427,  -170,  -427,
    -427,  -185,  -427,  -427,  -427,  -427,  -427,  -427,  -191,  -427,
    -427,  -196,  -427
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,    69,    70,   432,   540,   605,   606,   107,    37,    58,
      80,    81,    82,   249,    39,    59,   108,   109,   110,   111,
     112,   113,   114,   115,   256,    41,    60,   132,   279,   116,
     257,   117,   258,   476,   477,   209,   313,   479,   562,   480,
     563,   481,   564,   210,   314,   483,   484,   485,   118,   267,
     501,   502,   503,   504,   119,   269,   508,   509,   510,   120,
     268,   121,   271,   514,   515,   516,   587,    55,    67,   240,
     241,   242,   326,   243,   327,   122,   272,   518,   519,   123,
     264,   488,   489,   490,   571,    43,    61,   150,   151,   152,
     284,   153,   285,   154,   286,   155,   290,   156,   289,   157,
     158,   124,   265,   492,   493,   494,   574,    51,    65,   211,
     212,   213,   214,   215,   216,   217,   218,   317,   219,   316,
     220,   221,   318,   222,   125,   266,   496,   497,   498,   577,
      53,    66,   229,   230,   231,   232,   233,   322,   234,   235,
     236,   160,   282,   544,   545,   546,   608,    45,    62,   167,
     168,   169,   295,   161,   283,   548,   549,   550,   611,    47,
      63,   177,   178,   179,   298,   180,   181,   300,   182,   183,
     162,   291,   552,   553,   554,   614,    49,    64,   192,   193,
     194,   195,   306,   196,   307,   197,   308,   198,   309,   199,
     310,   200,   305,   163,   292,   556,   617,   126,   270,   512,
     281,   365,   366,   367,   368,   369,   433,   127,   273,   527,
     528,   529,   530,   593,   531,   532,   128,   129,   275,   535,
     536,   537,   599,   538,   600,   130,   276,    83,   251,    84,
     252,    85,   250,   465,   466,   467,   558,   675,   676,   677,
     685,   686,   687,   688,   693,   689,   691,   703,   704,   705,
     709,   710,   712
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   146,   526,   145,   165,   175,   190,   208,   225,   239,
     226,   227,   228,   507,   159,   166,   176,   191,   147,   511,
     148,   149,   478,   478,    25,    32,    26,    74,    27,   133,
     133,    96,   202,   525,   237,   238,   202,   223,   203,   204,
     224,   448,   449,   450,   499,    89,    90,    91,    92,    24,
     254,   277,    96,    36,    96,   255,   278,   293,   361,    38,
     296,   134,   294,   135,   164,   297,    78,    40,   201,   136,
     137,   138,   139,   140,   141,   580,   237,   238,   581,   142,
     142,   143,   500,   202,    42,   203,   204,   144,   205,   206,
     207,   201,   499,   506,    44,   472,    86,    75,    87,    88,
      46,    78,    48,    76,    77,    78,    50,    89,    90,    91,
      92,    93,    94,    95,    96,    52,    78,    54,    28,    29,
      30,    31,    78,    71,    78,   244,   201,   469,   470,   471,
     472,   473,   474,   533,   534,   131,    96,    97,    98,    99,
     100,   202,   583,   202,   245,   584,   246,   520,   521,   522,
     523,   101,    78,   303,   102,   103,   585,   247,   304,   586,
     104,   105,   184,   248,   106,   253,   185,   186,   187,   188,
     189,   526,   507,   478,    96,    78,   328,   277,   559,   636,
     568,   329,   557,   560,    78,   569,   170,   171,   172,   173,
     174,   259,   260,   261,   568,   680,    79,   681,   682,   570,
     591,   280,   525,   597,   601,   592,    78,   262,   598,   602,
      78,   248,    78,   293,   328,   296,   603,   303,   662,   665,
     670,   694,   671,   362,   713,   363,   695,   678,   706,   714,
     679,   707,   263,   146,   364,   145,   274,   287,   165,   288,
     299,   301,   302,   312,    78,   175,   159,   311,   315,   166,
     147,   319,   148,   149,   190,   321,   176,   330,   331,   320,
     323,   324,   325,   208,   332,   191,   333,   225,   334,   226,
     227,   228,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,   335,   336,   338,   339,   340,   346,   347,
     341,   348,   342,   349,   343,   344,   345,   350,   351,   352,
     353,   354,   355,   357,   356,   358,   360,   370,   371,   372,
     373,   374,   377,   375,   378,   379,   380,   376,   382,   384,
     385,   386,   387,   388,   390,   391,   392,   393,   394,   395,
     397,   398,   400,   401,   399,   402,   405,   408,   409,   411,
     708,   419,   420,   403,   406,   412,   413,   414,   415,   416,
     417,   418,   421,   422,   423,   424,   425,   426,   431,   475,
     475,   482,   482,   427,   428,   429,   430,   435,   434,   438,
     524,   436,   437,   439,   440,   441,   442,   362,   443,   363,
     561,   444,   487,   491,   495,   445,   513,   446,   364,   447,
     451,   452,   541,   543,   547,   565,   551,   566,   567,   453,
     573,   572,   575,   576,   578,   579,   674,   582,   454,   588,
     589,   555,   455,   590,   594,   456,   595,   457,   458,   596,
     609,   461,   464,   462,   610,   612,   613,   616,   615,   459,
     619,   621,   622,   618,   623,   641,   646,   647,   650,   460,
     649,   657,   463,   658,   517,   539,   692,   663,   664,   672,
     696,   698,   702,   604,   607,   700,   715,   505,   359,   337,
     468,   486,   625,   624,   659,   626,   627,   634,   639,   642,
     643,   644,   635,   638,   410,   637,   640,   660,   629,   661,
     666,   667,   668,   669,   673,   628,   631,   630,   404,   632,
     697,   701,   381,   407,   633,   654,   652,   656,   651,   542,
     645,   389,   383,   717,   653,   655,   620,   648,   690,   699,
     475,   146,   482,   145,   396,   711,   208,   716,     0,   225,
       0,   226,   227,   228,   159,     0,     0,     0,   147,   239,
     148,   149,     0,     0,     0,     0,     0,     0,     0,   524,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     165,     0,     0,   175,     0,     0,   190,     0,     0,     0,
       0,   166,     0,     0,   176,     0,     0,   191,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   683,
       0,   684,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   683,     0,   684
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    61,   428,    61,    62,    63,    64,    65,    66,    67,
      66,    66,    66,   424,    61,    62,    63,    64,    61,   425,
      61,    61,   417,   418,     5,    13,     7,    10,     9,     7,
       7,    29,    30,   428,    67,    68,    30,    31,    32,    33,
      34,   390,   391,   392,    61,    22,    23,    24,    25,     0,
       3,     3,    29,     7,    29,     8,     8,     3,    56,     7,
       3,    38,     8,    40,    39,     8,    99,     7,    15,    46,
      47,    48,    49,    50,    51,     3,    67,    68,     6,    57,
      57,    58,    99,    30,     7,    32,    33,    64,    35,    36,
      37,    15,    61,    62,     7,    19,    11,    80,    13,    14,
       7,    99,     7,    86,    87,    99,     7,    22,    23,    24,
      25,    26,    27,    28,    29,     7,    99,     7,    99,   100,
     101,   102,    99,    99,    99,     6,    15,    16,    17,    18,
      19,    20,    21,    77,    78,    12,    29,    52,    53,    54,
      55,    30,     3,    30,     3,     6,     4,    71,    72,    73,
      74,    66,    99,     3,    69,    70,     3,     8,     8,     6,
      75,    76,    55,     3,    79,     4,    59,    60,    61,    62,
      63,   597,   583,   568,    29,    99,     3,     3,     3,   585,
       3,     8,     8,     8,    99,     8,    41,    42,    43,    44,
      45,     4,     4,     4,     3,    82,   254,    84,    85,     8,
       3,     8,   597,     3,     3,     8,    99,     4,     8,     8,
      99,     3,    99,     3,     3,     3,     8,     3,     8,     8,
       8,     3,     8,   281,     3,   281,     8,     3,     3,     8,
       6,     6,     4,   293,   281,   293,     4,     4,   296,     4,
       4,     4,     4,     3,    99,   303,   293,     8,     4,   296,
     293,     4,   293,   293,   312,     3,   303,   245,   246,     8,
       4,     8,     3,   321,    99,   312,     4,   325,     4,   325,
     325,   325,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     4,     4,     4,     4,     4,     4,     4,
     100,     4,   100,     4,   100,   100,   100,     4,     4,     4,
       4,     4,     4,     4,   100,     4,     4,     4,     4,     4,
       4,     4,     4,   100,     4,     4,     4,   102,     4,     4,
     100,     4,   100,   100,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   100,     4,     4,     4,     4,     4,
      83,     5,     5,   102,   102,     7,     7,   335,   336,     7,
       7,     7,     5,     5,     5,     5,     5,     5,     5,   417,
     418,   417,   418,     7,     7,     7,     7,     3,     8,    99,
     428,     5,     5,    99,    99,    99,    99,   435,     5,   435,
       8,     7,     7,     7,     7,    99,     7,    99,   435,    99,
      99,    99,     4,     7,     7,     4,     7,     4,     4,    99,
       3,     6,     6,     3,     6,     3,     7,     6,    99,     6,
       3,    65,    99,     4,     4,    99,     4,    99,    99,     4,
       6,   409,    81,   411,     3,     6,     3,     3,     6,    99,
       4,     4,     4,     8,     4,     4,     4,     4,     3,    99,
       6,     4,   412,     5,    99,   430,     4,     8,     8,     8,
       4,     4,     7,    99,    99,     5,     4,   423,   277,   254,
     416,   418,   100,   102,    99,   102,   568,   580,   100,   100,
     100,   100,   583,   589,   328,   587,   591,    99,   573,    99,
      99,    99,    99,    99,    99,   571,   576,   574,   321,   577,
     100,    99,   293,   325,   579,   613,   610,   616,   608,   435,
     597,   303,   296,    99,   611,   614,   559,   601,   678,   694,
     568,   571,   568,   571,   312,   706,   574,   713,    -1,   577,
      -1,   577,   577,   577,   571,    -1,    -1,    -1,   571,   587,
     571,   571,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   597,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     608,    -1,    -1,   611,    -1,    -1,   614,    -1,    -1,    -1,
      -1,   608,    -1,    -1,   611,    -1,    -1,   614,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   677,
      -1,   677,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   694,    -1,   694
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     0,     5,     7,     9,    99,   100,
     101,   102,   116,   117,   118,   122,     7,   131,     7,   137,
       7,   148,     7,   208,     7,   270,     7,   282,     7,   299,
       7,   230,     7,   253,     7,   190,   123,   119,   132,   138,
     149,   209,   271,   283,   300,   231,   254,   191,   116,   124,
     125,    99,   120,   121,    10,    80,    86,    87,    99,   130,
     133,   134,   135,   350,   352,   354,    11,    13,    14,    22,
      23,    24,    25,    26,    27,    28,    29,    52,    53,    54,
      55,    66,    69,    70,    75,    76,    79,   130,   139,   140,
     141,   142,   143,   144,   145,   146,   152,   154,   171,   177,
     182,   184,   198,   202,   224,   247,   320,   330,   339,   340,
     348,    12,   150,     7,    38,    40,    46,    47,    48,    49,
      50,    51,    57,    58,    64,   130,   141,   142,   143,   144,
     210,   211,   212,   214,   216,   218,   220,   222,   223,   247,
     264,   276,   293,   316,    39,   130,   247,   272,   273,   274,
      41,    42,    43,    44,    45,   130,   247,   284,   285,   286,
     288,   289,   291,   292,    55,    59,    60,    61,    62,    63,
     130,   247,   301,   302,   303,   304,   306,   308,   310,   312,
     314,    15,    30,    32,    33,    35,    36,    37,   130,   158,
     166,   232,   233,   234,   235,   236,   237,   238,   239,   241,
     243,   244,   246,    31,    34,   130,   166,   236,   241,   255,
     256,   257,   258,   259,   261,   262,   263,    67,    68,   130,
     192,   193,   194,   196,     6,     3,     4,     8,     3,   136,
     355,   351,   353,     4,     3,     8,   147,   153,   155,     4,
       4,     4,     4,     4,   203,   225,   248,   172,   183,   178,
     321,   185,   199,   331,     4,   341,   349,     3,     8,   151,
       8,   323,   265,   277,   213,   215,   217,     4,     4,   221,
     219,   294,   317,     3,     8,   275,     3,     8,   287,     4,
     290,     4,     4,     3,     8,   315,   305,   307,   309,   311,
     313,     8,     3,   159,   167,     4,   242,   240,   245,     4,
       8,     3,   260,     4,     8,     3,   195,   197,     3,     8,
     116,   116,    99,     4,     4,     4,     4,   134,     4,     4,
       4,   100,   100,   100,   100,   100,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   100,     4,     4,   140,
       4,    56,   130,   166,   247,   324,   325,   326,   327,   328,
       4,     4,     4,     4,     4,   100,   102,     4,     4,     4,
       4,   211,     4,   273,     4,   100,     4,   100,   100,   285,
       4,     4,     4,     4,     4,     4,   303,     4,     4,   100,
       4,     4,     4,   102,   234,     4,   102,   257,     4,     4,
     193,     4,     7,     7,   116,   116,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   126,   329,     8,     3,     5,     5,    99,    99,
      99,    99,    99,     5,     7,    99,    99,    99,   126,   126,
     126,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   116,   116,   139,    81,   356,   357,   358,   150,    16,
      17,    18,    19,    20,    21,   130,   156,   157,   158,   160,
     162,   164,   166,   168,   169,   170,   156,     7,   204,   205,
     206,     7,   226,   227,   228,     7,   249,   250,   251,    61,
      99,   173,   174,   175,   176,   124,    62,   175,   179,   180,
     181,   218,   322,     7,   186,   187,   188,    99,   200,   201,
      71,    72,    73,    74,   130,   158,   168,   332,   333,   334,
     335,   337,   338,    77,    78,   342,   343,   344,   346,   121,
     127,     4,   326,     7,   266,   267,   268,     7,   278,   279,
     280,     7,   295,   296,   297,    65,   318,     8,   359,     3,
       8,     8,   161,   163,   165,     4,     4,     4,     3,     8,
       8,   207,     6,     3,   229,     6,     3,   252,     6,     3,
       3,     6,     6,     3,     6,     3,     6,   189,     6,     3,
       4,     3,     8,   336,     4,     4,     4,     3,     8,   345,
     347,     3,     8,     8,    99,   128,   129,    99,   269,     6,
       3,   281,     6,     3,   298,     6,     3,   319,     8,     4,
     357,     4,     4,     4,   102,   100,   102,   157,   210,   206,
     232,   228,   255,   251,   174,   180,   218,   192,   188,   100,
     201,     4,   100,   100,   100,   333,     4,     4,   343,     6,
       3,   272,   268,   284,   280,   301,   297,     4,     5,    99,
      99,    99,     8,     8,     8,     8,    99,    99,    99,    99,
       8,     8,     8,    99,     7,   360,   361,   362,     3,     6,
      82,    84,    85,   130,   166,   363,   364,   365,   366,   368,
     361,   369,     4,   367,     3,     8,     4,   100,     4,   364,
       5,    99,     7,   370,   371,   372,     3,     6,    83,   373,
     374,   371,   375,     3,     8,     4,   374,    99
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   103,   105,   104,   106,   104,   107,   104,   108,   104,
     109,   104,   110,   104,   111,   104,   112,   104,   113,   104,
     114,   104,   115,   104,   116,   116,   116,   116,   116,   116,
     116,   117,   119,   118,   120,   120,   121,   121,   123,   122,
     124,   124,   125,   125,   127,   126,   128,   128,   129,   129,
     130,   132,   131,   133,   133,   134,   134,   134,   134,   134,
     136,   135,   138,   137,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   141,   142,
     143,   144,   145,   147,   146,   149,   148,   151,   150,   153,
     152,   155,   154,   156,   156,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   159,   158,   161,   160,   163,   162,
     165,   164,   167,   166,   168,   169,   170,   172,   171,   173,
     173,   174,   174,   175,   176,   178,   177,   179,   179,   180,
     180,   181,   183,   182,   185,   184,   186,   186,   187,   187,
     189,   188,   191,   190,   192,   192,   192,   193,   193,   195,
     194,   197,   196,   199,   198,   200,   200,   201,   203,   202,
     204,   204,   205,   205,   207,   206,   209,   208,   210,   210,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   213,   212,   215,
     214,   217,   216,   219,   218,   221,   220,   222,   223,   225,
     224,   226,   226,   227,   227,   229,   228,   231,   230,   232,
     232,   233,   233,   234,   234,   234,   234,   234,   234,   234,
     234,   235,   236,   237,   238,   240,   239,   242,   241,   243,
     245,   244,   246,   248,   247,   249,   249,   250,   250,   252,
     251,   254,   253,   255,   255,   256,   256,   257,   257,   257,
     257,   257,   257,   258,   260,   259,   261,   262,   263,   265,
     264,   266,   266,   267,   267,   269,   268,   271,   270,   272,
     272,   273,   273,   273,   275,   274,   277,   276,   278,   278,
     279,   279,   281,   280,   283,   282,   284,   284,   285,   285,
     285,   285,   285,   285,   285,   287,   286,   288,   290,   289,
     291,   292,   294,   293,   295,   295,   296,   296,   298,   297,
     300,   299,   301,   301,   302,   302,   303,   303,   303,   303,
     303,   303,   303,   303,   305,   304,   307,   306,   309,   308,
     311,   310,   313,   312,   315,   314,   317,   316,   319,   318,
     321,   320,   322,   322,   323,   218,   324,   324,   325,   325,
     326,   326,   326,   326,   327,   329,   328,   331,   330,   332,
     332,   333,   333,   333,   333,   333,   333,   333,   334,   336,
     335,   337,   338,   339,   341,   340,   342,   342,   343,   343,
     345,   344,   347,   346,   349,   348,   351,   350,   353,   352,
     355,   354,   356,   356,   357,   359,   358,   360,   360,   362,
     361,   363,   363,   364,   364,   364,   364,   364,   365,   367,
     366,   369,   368,   370,   370,   372,   371,   373,   373,   375,
     374
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     1,     3,     5,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     0,     6,     0,     4,     0,     4,     0,
       6,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     0,     6,     1,     3,     1,
       1,     1,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     0,
       4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"lease-database\"",
  "\"hosts-database\"", "\"type\"", "\"user\"", "\"password\"", "\"host\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"preferred-lifetime\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"record-types\"", "\"encapsulate\"",
  "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"", "\"prefix\"",
  "\"prefix-len\"", "\"excluded-prefix\"", "\"excluded-prefix-len\"",
  "\"delegated-len\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"server-id\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"Dhcp4\"", "\"DhcpDdns\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "value", "sub_json", "map2", "$@12", "map_content",
  "not_empty_map", "list_generic", "$@13", "list_content",
  "not_empty_list", "list_strings", "$@14", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@15",
  "global_objects", "global_object", "dhcp6_object", "$@16", "sub_dhcp6",
  "$@17", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@18",
  "sub_interfaces6", "$@19", "interface_config_map", "$@20",
  "lease_database", "$@21", "hosts_database", "$@22",
  "database_map_params", "database_map_param", "type", "$@23", "user",
  "$@24", "password", "$@25", "host", "$@26", "name", "$@27", "persist",
  "lfc_interval", "readonly", "mac_sources", "$@28", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@29",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "relay_supplied_options", "$@30", "hooks_libraries",
  "$@31", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@32", "sub_hooks_library", "$@33", "hooks_params",
  "hooks_param", "library", "$@34", "parameters", "$@35",
  "expired_leases_processing", "$@36", "expired_leases_params",
  "expired_leases_param", "subnet6_list", "$@37", "subnet6_list_content",
  "not_empty_subnet6_list", "subnet6", "$@38", "sub_subnet6", "$@39",
  "subnet6_params", "subnet6_param", "subnet", "$@40", "interface", "$@41",
  "interface_id", "$@42", "client_class", "$@43", "reservation_mode",
  "$@44", "id", "rapid_commit", "option_def_list", "$@45",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@46", "sub_option_def", "$@47",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type",
  "option_def_record_types", "$@48", "space", "$@49", "option_def_space",
  "option_def_encapsulate", "$@50", "option_def_array", "option_data_list",
  "$@51", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@52", "sub_option_data", "$@53",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@54",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@55", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@56", "sub_pool6", "$@57", "pool_params",
  "pool_param", "pool_entry", "$@58", "pd_pools_list", "$@59",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@60", "sub_pd_pool", "$@61", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@62", "pd_prefix_len", "excluded_prefix", "$@63",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@64",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@65", "sub_reservation", "$@66", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@67", "prefixes", "$@68", "duid", "$@69", "hw_address", "$@70",
  "hostname", "$@71", "reservation_client_classes", "$@72", "relay",
  "$@73", "relay_map", "$@74", "client_classes", "$@75",
  "client_classes_list", "$@76", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@77", "server_id", "$@78",
  "server_id_params", "server_id_param", "htype", "identifier", "$@79",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@80",
  "control_socket_params", "control_socket_param", "socket_type", "$@81",
  "socket_name", "$@82", "dhcp_ddns", "$@83", "dhcp4_json_object", "$@84",
  "dhcpddns_json_object", "$@85", "logging_object", "$@86",
  "logging_params", "logging_param", "loggers", "$@87", "loggers_entries",
  "logger_entry", "$@88", "logger_params", "logger_param", "debuglevel",
  "severity", "$@89", "output_options_list", "$@90",
  "output_options_list_content", "output_entry", "$@91", "output_params",
  "output_param", "$@92", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   198,   198,   198,   199,   199,   200,   200,   201,   201,
     202,   202,   203,   203,   204,   204,   205,   205,   206,   206,
     207,   207,   208,   208,   216,   217,   218,   219,   220,   221,
     222,   225,   230,   230,   242,   243,   246,   250,   257,   257,
     264,   265,   268,   272,   279,   279,   286,   287,   290,   294,
     305,   315,   315,   327,   328,   332,   333,   334,   335,   336,
     339,   339,   356,   356,   364,   365,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   394,   399,
     404,   409,   414,   419,   419,   429,   429,   437,   437,   447,
     447,   457,   457,   467,   468,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   482,   482,   490,   490,   498,   498,
     506,   506,   514,   514,   522,   527,   532,   537,   537,   547,
     548,   551,   552,   555,   560,   565,   565,   575,   576,   579,
     580,   583,   590,   590,   600,   600,   610,   611,   614,   615,
     618,   618,   626,   626,   634,   635,   636,   639,   640,   643,
     643,   651,   651,   659,   659,   669,   670,   676,   684,   684,
     697,   698,   701,   702,   709,   709,   732,   732,   741,   742,
     746,   747,   748,   749,   750,   751,   752,   753,   754,   755,
     756,   757,   758,   759,   760,   761,   762,   765,   765,   773,
     773,   781,   781,   789,   789,   797,   797,   805,   810,   819,
     819,   831,   832,   835,   836,   841,   841,   852,   852,   862,
     863,   866,   867,   870,   871,   872,   873,   874,   875,   876,
     877,   880,   882,   887,   889,   891,   891,   899,   899,   907,
     909,   909,   917,   926,   926,   938,   939,   944,   945,   950,
     950,   961,   961,   972,   973,   978,   979,   984,   985,   986,
     987,   988,   989,   992,   994,   994,  1002,  1004,  1006,  1014,
    1014,  1026,  1027,  1030,  1031,  1034,  1034,  1042,  1042,  1050,
    1051,  1054,  1055,  1056,  1059,  1059,  1070,  1070,  1082,  1083,
    1086,  1087,  1090,  1090,  1098,  1098,  1106,  1107,  1110,  1111,
    1112,  1113,  1114,  1115,  1116,  1119,  1119,  1127,  1132,  1132,
    1140,  1145,  1153,  1153,  1163,  1164,  1167,  1168,  1171,  1171,
    1179,  1179,  1187,  1188,  1191,  1192,  1196,  1197,  1198,  1199,
    1200,  1201,  1202,  1203,  1206,  1206,  1216,  1216,  1226,  1226,
    1234,  1234,  1242,  1242,  1250,  1250,  1263,  1263,  1273,  1273,
    1284,  1284,  1294,  1295,  1298,  1298,  1306,  1307,  1310,  1311,
    1314,  1315,  1316,  1317,  1320,  1322,  1322,  1333,  1333,  1343,
    1344,  1347,  1348,  1349,  1350,  1351,  1352,  1353,  1356,  1361,
    1361,  1369,  1374,  1381,  1388,  1388,  1398,  1399,  1402,  1403,
    1406,  1406,  1414,  1414,  1424,  1424,  1436,  1436,  1443,  1443,
    1455,  1455,  1468,  1469,  1473,  1477,  1477,  1489,  1490,  1494,
    1494,  1502,  1503,  1506,  1507,  1508,  1509,  1510,  1513,  1517,
    1517,  1525,  1525,  1535,  1536,  1539,  1539,  1547,  1548,  1551,
    1551
  };

  // Print the state stack on the debug stream.
  void
  Dhcp6Parser::yystack_print_ ()
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
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 3533 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1559 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
