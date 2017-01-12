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
      case 126: // value
      case 130: // map_value
      case 354: // duid_type
        value.move< ElementPtr > (that.value);
        break;

      case 112: // "boolean"
        value.move< bool > (that.value);
        break;

      case 111: // "floating point"
        value.move< double > (that.value);
        break;

      case 110: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 109: // "constant string"
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
      case 126: // value
      case 130: // map_value
      case 354: // duid_type
        value.copy< ElementPtr > (that.value);
        break;

      case 112: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 111: // "floating point"
        value.copy< double > (that.value);
        break;

      case 110: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 109: // "constant string"
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
            case 109: // "constant string"

#line 201 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 356 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 110: // "integer"

#line 201 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 363 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 111: // "floating point"

#line 201 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 370 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 112: // "boolean"

#line 201 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 377 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 126: // value

#line 201 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 384 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 130: // map_value

#line 201 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 391 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 354: // duid_type

#line 201 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 126: // value
      case 130: // map_value
      case 354: // duid_type
        yylhs.value.build< ElementPtr > ();
        break;

      case 112: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 111: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 110: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 109: // "constant string"
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
#line 210 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 211 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 212 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 213 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 214 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 215 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 216 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 217 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 218 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 219 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 220 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 751 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 840 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 294 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 339 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 906 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 933 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1007 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1489 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1533 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1551 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 988 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1799 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1040 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1844 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1955 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1136 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1144 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1214 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1218 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1222 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2186 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2361 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1418 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2473 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2503 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2520 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2537 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2557 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2604 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2633 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2682 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -432;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     101,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,    43,    19,    40,    89,   108,   110,   138,   152,
     154,   163,   165,   174,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,    19,    80,    17,    65,
      47,    16,    66,     7,    77,    67,    39,    -8,  -432,   190,
     210,   216,   220,   229,  -432,  -432,  -432,  -432,   234,  -432,
      54,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,   238,
     247,   250,   260,   263,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,   267,  -432,  -432,  -432,   119,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,   264,  -432,  -432,  -432,  -432,  -432,  -432,   269,
     270,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
     144,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,   150,  -432,
    -432,  -432,  -432,   271,  -432,   272,   273,  -432,  -432,  -432,
     170,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,   274,   275,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,   276,  -432,  -432,  -432,
     279,  -432,  -432,   277,   281,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,   282,  -432,  -432,  -432,
    -432,   280,   284,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,   176,  -432,  -432,  -432,  -432,    19,    19,  -432,
     183,   285,   286,   287,   289,  -432,    17,  -432,   290,   291,
     292,   188,   191,   192,   193,   194,   293,   295,   296,   301,
     302,   303,   304,   305,   306,   307,   202,   309,   310,    65,
    -432,   311,  -432,   114,   312,   313,   314,   315,   316,   212,
     213,   317,   319,   320,   322,    16,  -432,   323,   324,    66,
    -432,   325,   222,   326,   223,   224,     7,  -432,   327,   331,
     332,   333,   334,   335,  -432,    77,   336,   337,   232,   341,
     342,   343,   236,  -432,    67,   345,   239,  -432,    39,   346,
     348,   178,  -432,  -432,  -432,   349,   347,   351,    19,    19,
    -432,   352,   353,   354,  -432,  -432,  -432,  -432,  -432,   350,
     357,   360,   361,   362,   363,   364,   365,   366,   369,  -432,
     370,   371,  -432,   362,  -432,  -432,  -432,  -432,   372,   368,
    -432,  -432,  -432,   367,   374,   278,   283,   288,  -432,  -432,
     294,   297,   377,   376,  -432,   298,   378,  -432,   299,  -432,
     300,  -432,  -432,  -432,   362,   362,   362,   308,   318,   321,
    -432,   328,   329,  -432,   330,   338,   339,  -432,  -432,   340,
    -432,  -432,   344,    19,  -432,    19,    65,   355,  -432,  -432,
      47,    14,    14,   379,   381,   383,   -25,  -432,  -432,    23,
      76,   384,    93,    27,   181,    80,  -432,   380,  -432,   114,
     386,   387,  -432,  -432,  -432,  -432,  -432,   388,   356,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,   177,
    -432,   179,  -432,  -432,   390,  -432,  -432,  -432,  -432,   392,
     395,   396,  -432,   180,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,   189,  -432,   398,   399,  -432,  -432,   404,
     402,  -432,  -432,   405,   409,  -432,  -432,  -432,    52,  -432,
    -432,  -432,    19,  -432,  -432,    74,  -432,  -432,  -432,   143,
    -432,   407,   411,  -432,   397,   412,   415,   417,   419,   420,
     207,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
     421,   422,   424,  -432,  -432,   208,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,   209,  -432,  -432,  -432,   211,   358,
    -432,  -432,   423,   428,  -432,  -432,   426,   430,  -432,  -432,
     429,   431,  -432,  -432,   432,  -432,   437,   355,  -432,  -432,
     438,   439,   440,   441,   359,   373,   375,    14,  -432,  -432,
      16,  -432,   379,    67,  -432,   381,    39,  -432,   383,   -25,
    -432,   444,    23,  -432,    76,  -432,    -8,  -432,   384,   382,
     385,   389,   391,   393,   394,    93,  -432,   447,   448,   400,
     401,   403,    27,  -432,   450,   451,   181,  -432,  -432,  -432,
      66,  -432,   386,     7,  -432,   387,    77,  -432,   388,   452,
    -432,   410,  -432,   406,   408,   414,   416,  -432,  -432,  -432,
    -432,   218,  -432,   449,  -432,   453,  -432,  -432,  -432,  -432,
    -432,   219,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
     182,   418,  -432,  -432,  -432,  -432,   425,   427,  -432,   221,
    -432,   227,  -432,   454,  -432,   433,   456,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,   187,  -432,    68,
     456,  -432,  -432,   455,  -432,  -432,  -432,   228,  -432,  -432,
    -432,  -432,  -432,   460,   434,   461,    68,  -432,   463,  -432,
     442,  -432,   459,  -432,  -432,   237,  -432,   413,   459,  -432,
    -432,   231,  -432,  -432,   465,   413,  -432,   443,  -432,  -432
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    48,     5,    59,     7,
      92,     9,   184,    11,   286,    13,   306,    15,   333,    17,
     225,    19,   260,    21,   149,    23,    43,    35,     0,     0,
       0,     0,     0,     0,   335,   227,   262,     0,    45,     0,
      44,     0,     0,    36,    57,   418,   414,   416,     0,    56,
       0,    50,    52,    54,    55,    53,    90,    96,    98,     0,
       0,     0,     0,     0,   176,   217,   252,   124,   139,   132,
     363,   141,   160,   380,     0,   402,   412,    84,     0,    61,
      63,    64,    65,    66,    67,    69,    70,    71,    72,    74,
      73,    78,    79,    68,    76,    77,    75,    80,    81,    82,
      83,    94,     0,   367,   278,   298,   205,   207,   209,     0,
       0,   213,   211,   325,   359,   204,   188,   189,   190,   191,
       0,   186,   195,   196,   197,   200,   202,   198,   199,   192,
     193,   194,   201,   203,   294,   296,   293,   291,     0,   288,
     290,   292,   318,     0,   321,     0,     0,   317,   313,   316,
       0,   308,   310,   311,   314,   315,   312,   357,   347,   349,
     351,   353,   355,   346,   345,     0,   336,   337,   341,   342,
     339,   343,   344,   340,   242,   119,     0,   246,   244,   249,
       0,   238,   239,     0,   228,   229,   231,   241,   232,   233,
     234,   248,   235,   236,   237,   273,     0,   271,   272,   275,
     276,     0,   263,   264,   266,   267,   268,   269,   270,   156,
     158,   153,     0,   151,   154,   155,    40,     0,     0,    33,
       0,     0,     0,     0,     0,    47,     0,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,    93,   369,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   185,     0,     0,     0,
     287,     0,     0,     0,     0,     0,     0,   307,     0,     0,
       0,     0,     0,     0,   334,     0,     0,     0,     0,     0,
       0,     0,     0,   226,     0,     0,     0,   261,     0,     0,
       0,     0,   150,    46,    37,     0,     0,     0,     0,     0,
      51,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   401,
       0,     0,    62,     0,   378,   376,   377,   375,     0,   370,
     371,   373,   374,     0,     0,     0,     0,     0,   215,   216,
       0,     0,     0,     0,   187,     0,     0,   289,     0,   320,
       0,   323,   324,   309,     0,     0,     0,     0,     0,     0,
     338,     0,     0,   240,     0,     0,     0,   251,   230,     0,
     277,   265,     0,     0,   152,     0,     0,     0,   415,   417,
       0,     0,     0,   178,   219,   254,     0,    41,   140,     0,
       0,   143,     0,     0,     0,     0,    95,     0,   368,     0,
     280,   300,   206,   208,   210,   214,   212,   327,     0,   295,
      34,   297,   319,   322,   358,   348,   350,   352,   354,   356,
     243,   120,   247,   245,   250,   274,   157,   159,    38,     0,
     423,     0,   420,   422,     0,   111,   113,   115,   117,     0,
       0,     0,   110,     0,   100,   102,   103,   104,   105,   106,
     107,   108,   109,     0,   182,     0,   179,   180,   223,     0,
     220,   221,   258,     0,   255,   256,   130,   131,     0,   126,
     128,   129,    43,   138,   136,     0,   134,   137,   365,     0,
     147,     0,   144,   145,     0,     0,     0,     0,     0,     0,
       0,   162,   164,   165,   166,   167,   168,   169,   391,   397,
       0,     0,     0,   390,   389,     0,   382,   384,   387,   385,
     386,   388,   408,   410,     0,   404,   406,   407,     0,     0,
     372,   284,     0,   281,   282,   304,     0,   301,   302,   331,
       0,   328,   329,   361,     0,    58,     0,     0,   419,    91,
       0,     0,     0,     0,     0,     0,     0,     0,    97,    99,
       0,   177,     0,   227,   218,     0,   262,   253,     0,     0,
     125,     0,     0,   133,     0,   364,     0,   142,     0,     0,
       0,     0,     0,     0,     0,     0,   161,     0,     0,     0,
       0,     0,     0,   381,     0,     0,     0,   403,   413,   379,
       0,   279,     0,     0,   299,     0,   335,   326,     0,     0,
     360,     0,   421,     0,     0,     0,     0,   121,   122,   123,
     101,     0,   181,     0,   222,     0,   257,   127,    42,   135,
     366,     0,   146,   170,   171,   172,   173,   174,   175,   163,
       0,     0,   396,   399,   400,   383,     0,     0,   405,     0,
     283,     0,   303,     0,   330,     0,     0,   112,   114,   116,
     118,   183,   224,   259,   148,   393,   394,   395,   392,   398,
     409,   411,   285,   305,   332,   362,   427,     0,   425,     0,
       0,   424,   439,     0,   437,   435,   431,     0,   429,   433,
     434,   432,   426,     0,     0,     0,     0,   428,     0,   436,
       0,   430,     0,   438,   443,     0,   441,     0,     0,   440,
     447,     0,   445,   442,     0,     0,   444,     0,   446,   448
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,     5,  -432,    50,  -432,  -432,  -432,    25,
    -432,  -432,  -239,  -432,   -54,  -432,   -58,  -432,  -432,  -432,
     214,  -432,  -432,  -432,  -432,    56,   195,   -51,   -45,   -40,
     -36,  -432,  -432,  -432,  -432,  -432,    53,  -432,  -432,  -432,
    -432,  -432,    55,  -112,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,   -65,  -432,  -431,  -432,  -432,  -432,  -432,  -432,
    -123,  -407,  -432,  -432,  -432,  -432,  -124,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -129,  -432,  -432,  -432,  -126,   151,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -134,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -108,  -432,
    -432,  -432,  -105,   196,  -432,  -432,  -432,  -432,  -432,  -432,
    -410,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -109,  -432,  -432,  -432,  -104,  -432,   164,  -432,   -49,  -432,
    -432,  -432,  -432,  -432,   -47,  -432,  -432,  -432,  -432,  -432,
     -50,  -432,  -432,  -432,  -102,  -432,  -432,  -432,  -106,  -432,
     166,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -139,  -432,  -432,  -432,  -133,   199,  -432,  -432,   -48,
    -432,  -432,  -432,  -432,  -432,  -135,  -432,  -432,  -432,  -131,
     201,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -130,  -432,  -432,  -432,  -127,  -432,   197,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,    75,  -432,  -432,  -432,  -432,  -432,  -432,  -117,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -110,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,   -59,  -432,  -432,  -432,  -191,
    -432,  -432,  -206,  -432,  -432,  -432,  -432,  -432,  -432,  -217,
    -432,  -432,  -221,  -432
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,   451,    72,    73,
      35,    56,   428,   512,    69,    70,   107,    37,    58,    80,
      81,    82,   251,    39,    59,   108,   109,   110,   111,   112,
     113,   114,   115,   258,    41,    60,   132,   281,   116,   259,
     117,   260,   483,   484,   485,   580,   486,   581,   487,   582,
     488,   583,   212,   317,   490,   491,   492,   118,   269,   508,
     509,   510,   511,   119,   271,   515,   516,   517,   120,   270,
     121,   273,   521,   522,   523,   606,    55,    67,   242,   243,
     244,   329,   245,   330,   122,   274,   530,   531,   532,   533,
     534,   535,   536,   537,   123,   266,   495,   496,   497,   590,
      43,    61,   150,   151,   152,   286,   153,   287,   154,   288,
     155,   292,   156,   291,   157,   158,   124,   267,   499,   500,
     501,   593,    51,    65,   213,   214,   215,   216,   217,   218,
     219,   316,   220,   320,   221,   319,   222,   223,   321,   224,
     125,   268,   503,   504,   505,   596,    53,    66,   231,   232,
     233,   234,   235,   325,   236,   237,   238,   160,   284,   562,
     563,   564,   630,    45,    62,   168,   169,   170,   297,   171,
     298,   161,   285,   566,   567,   568,   633,    47,    63,   180,
     181,   182,   301,   183,   184,   303,   185,   186,   162,   293,
     570,   571,   572,   636,    49,    64,   195,   196,   197,   198,
     309,   199,   310,   200,   311,   201,   312,   202,   313,   203,
     308,   163,   294,   574,   639,   126,   272,   519,   283,   368,
     369,   370,   371,   372,   437,   127,   275,   545,   546,   547,
     617,   698,   548,   549,   618,   550,   551,   128,   129,   277,
     554,   555,   556,   624,   557,   625,   130,   278,    83,   253,
      84,   254,    85,   252,   471,   472,   473,   576,   707,   708,
     709,   717,   718,   719,   720,   725,   721,   723,   735,   736,
     737,   741,   742,   744
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   228,   544,   145,   166,   177,   193,   211,   227,   241,
     146,   159,   167,   178,   194,   179,   147,   229,    32,   230,
     518,   148,   514,   133,    25,   149,    26,    74,    27,   475,
     476,   477,   478,   479,   480,   481,    96,   506,    89,    90,
      91,    92,   538,    24,   205,    96,   479,    36,   172,   173,
     174,   175,   176,   165,   134,   599,   135,   256,   600,   131,
     239,   240,   257,   136,   137,   138,   139,   140,   141,   205,
     225,   206,   207,   226,   142,   143,    86,   602,    87,    88,
     603,   144,   204,   133,   507,   506,   513,    89,    90,    91,
      92,    93,    94,    95,    96,    96,    38,   205,   205,   206,
     207,    78,   208,   209,   210,   164,    96,    75,   539,   540,
     541,   542,   165,    76,    77,    40,    78,    42,    97,    98,
      99,   100,   279,    78,   436,    78,    78,   280,    28,    29,
      30,    31,   101,   187,   142,   102,    78,   188,   189,   190,
     191,   192,   103,    96,   205,    44,   604,   295,    78,   605,
     104,   105,   296,   299,   106,   454,   455,   456,   300,    46,
     712,    48,   713,   714,   524,   525,   526,   527,   528,   529,
      50,   364,    52,   306,    78,    78,    78,    78,   307,   331,
     279,    54,   577,   587,   332,   575,    78,   578,   588,    71,
     710,   544,   587,   711,   660,   514,   246,   589,    79,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
     615,   622,   626,   247,   250,   616,   623,   627,   366,   628,
     248,   295,   331,    78,   299,   365,   691,   694,   249,   702,
     306,   726,   250,   367,   745,   703,   727,   145,   255,   746,
     738,   166,   261,   739,   146,   159,   239,   240,   177,   167,
     147,   262,   333,   334,   263,   148,   178,   193,   179,   149,
     695,   696,   697,   228,   264,   194,   211,   265,   552,   553,
     227,   276,   282,   289,   290,   302,   304,   305,   315,   229,
     318,   230,   314,   322,   324,   323,   326,   328,   327,   336,
     337,   338,   335,   339,   341,   342,   343,   349,   344,   350,
     351,   345,   346,   347,   348,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   363,   373,   374,   375,   376,
     377,   380,   378,   381,   382,   379,   383,   385,   386,   388,
     390,   394,   389,   391,   392,   395,   396,   397,   398,   399,
     401,   402,   403,   418,   419,   404,   405,   406,   407,   409,
     412,   410,   413,   415,   416,   423,   489,   489,   417,   420,
     421,   422,   424,   482,   482,   425,   426,   427,   429,   430,
     431,   439,   440,   432,   366,   543,   433,   434,   435,   441,
     438,   365,   447,   448,   559,    26,   494,   442,   498,   367,
     502,   520,   443,   561,   565,   569,   584,   444,   579,   585,
     586,   609,   592,   445,   591,   595,   446,   449,   452,   453,
     594,   597,   598,   607,   608,   686,   610,   457,   467,   611,
     468,   612,   573,   613,   614,   619,   620,   458,   621,   631,
     459,   632,   634,   635,   638,   637,   450,   460,   461,   462,
     640,   641,   643,   644,   645,   646,   470,   463,   464,   465,
     658,   670,   671,   466,   676,   677,   685,   692,   601,   724,
     558,   693,   704,   706,   728,   730,   734,   629,   732,   747,
     340,   647,   469,   474,   362,   650,   657,   493,   659,   662,
     661,   669,   414,   648,   652,   651,   654,   649,   408,   653,
     655,   384,   663,   680,   411,   664,   656,   679,   387,   665,
     682,   666,   681,   667,   668,   675,   740,   393,   684,   683,
     672,   673,   400,   674,   560,   687,   678,   688,   642,   722,
     731,   743,   489,   689,   748,   690,     0,   699,     0,   482,
       0,   228,   145,     0,   700,   211,   701,     0,   227,   146,
     159,     0,   705,     0,   729,   147,     0,   229,   241,   230,
     148,   733,   749,     0,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   543,     0,     0,     0,     0,     0,
       0,     0,   166,     0,     0,   177,     0,     0,   193,     0,
     167,     0,     0,   178,     0,   179,   194,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   716,     0,     0,     0,     0,     0,
       0,   715,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   716,     0,     0,     0,     0,     0,     0,   715
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,   433,    61,    62,    63,    64,    65,    66,    67,
      61,    61,    62,    63,    64,    63,    61,    66,    13,    66,
     430,    61,   429,     7,     5,    61,     7,    10,     9,    15,
      16,    17,    18,    19,    20,    21,    29,    62,    22,    23,
      24,    25,    15,     0,    30,    29,    19,     7,    41,    42,
      43,    44,    45,    46,    38,     3,    40,     3,     6,    12,
      68,    69,     8,    47,    48,    49,    50,    51,    52,    30,
      31,    32,    33,    34,    58,    59,    11,     3,    13,    14,
       6,    65,    15,     7,   109,    62,    63,    22,    23,    24,
      25,    26,    27,    28,    29,    29,     7,    30,    30,    32,
      33,   109,    35,    36,    37,    39,    29,    90,    81,    82,
      83,    84,    46,    96,    97,     7,   109,     7,    53,    54,
      55,    56,     3,   109,   363,   109,   109,     8,   109,   110,
     111,   112,    67,    56,    58,    70,   109,    60,    61,    62,
      63,    64,    77,    29,    30,     7,     3,     3,   109,     6,
      85,    86,     8,     3,    89,   394,   395,   396,     8,     7,
      92,     7,    94,    95,    71,    72,    73,    74,    75,    76,
       7,    57,     7,     3,   109,   109,   109,   109,     8,     3,
       3,     7,     3,     3,     8,     8,   109,     8,     8,   109,
       3,   622,     3,     6,   604,   602,     6,     8,   256,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       3,     3,     3,     3,     3,     8,     8,     8,   283,     8,
       4,     3,     3,   109,     3,   283,     8,     8,     8,     8,
       3,     3,     3,   283,     3,     8,     8,   295,     4,     8,
       3,   299,     4,     6,   295,   295,    68,    69,   306,   299,
     295,     4,   247,   248,     4,   295,   306,   315,   306,   295,
      78,    79,    80,   328,     4,   315,   324,     4,    87,    88,
     328,     4,     8,     4,     4,     4,     4,     4,     3,   328,
       4,   328,     8,     4,     3,     8,     4,     3,     8,     4,
       4,     4,   109,     4,     4,     4,     4,     4,   110,     4,
       4,   110,   110,   110,   110,     4,     4,     4,     4,     4,
       4,     4,   110,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   110,     4,     4,   112,     4,     4,     4,     4,
       4,     4,   110,   110,   110,     4,     4,     4,     4,     4,
       4,     4,   110,   338,   339,     4,     4,     4,   112,     4,
       4,   112,     4,     4,     7,     5,   421,   422,     7,     7,
       7,     7,     5,   421,   422,     5,     5,     5,     5,     5,
       5,     3,     5,     7,   439,   433,     7,     7,     7,     5,
       8,   439,     5,     7,     4,     7,     7,   109,     7,   439,
       7,     7,   109,     7,     7,     7,     4,   109,     8,     4,
       4,     4,     3,   109,     6,     3,   109,   109,   109,   109,
       6,     6,     3,     6,     3,     5,     4,   109,   413,     4,
     415,     4,    66,     4,     4,     4,     4,   109,     4,     6,
     109,     3,     6,     3,     3,     6,   386,   109,   109,   109,
       8,     4,     4,     4,     4,     4,    91,   109,   109,   109,
       6,     4,     4,   109,     4,     4,     4,     8,   512,     4,
     435,     8,     8,     7,     4,     4,     7,   109,     5,     4,
     256,   112,   416,   420,   279,   587,   599,   422,   602,   608,
     606,   615,   331,   110,   592,   590,   595,   112,   324,   593,
     596,   295,   110,   632,   328,   110,   598,   630,   299,   110,
     635,   110,   633,   110,   110,   622,    93,   306,   638,   636,
     110,   110,   315,   110,   439,   109,   626,   109,   577,   710,
     726,   738,   587,   109,   745,   109,    -1,   109,    -1,   587,
      -1,   596,   590,    -1,   109,   593,   109,    -1,   596,   590,
     590,    -1,   109,    -1,   110,   590,    -1,   596,   606,   596,
     590,   109,   109,    -1,   590,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   622,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   630,    -1,    -1,   633,    -1,    -1,   636,    -1,
     630,    -1,    -1,   633,    -1,   633,   636,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   709,    -1,    -1,    -1,    -1,    -1,
      -1,   709,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   726,    -1,    -1,    -1,    -1,    -1,    -1,   726
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     5,     7,     9,   109,   110,
     111,   112,   126,   127,   128,   133,     7,   140,     7,   146,
       7,   157,     7,   223,     7,   286,     7,   300,     7,   317,
       7,   245,     7,   269,     7,   199,   134,   129,   141,   147,
     158,   224,   287,   301,   318,   246,   270,   200,   126,   137,
     138,   109,   131,   132,    10,    90,    96,    97,   109,   139,
     142,   143,   144,   371,   373,   375,    11,    13,    14,    22,
      23,    24,    25,    26,    27,    28,    29,    53,    54,    55,
      56,    67,    70,    77,    85,    86,    89,   139,   148,   149,
     150,   151,   152,   153,   154,   155,   161,   163,   180,   186,
     191,   193,   207,   217,   239,   263,   338,   348,   360,   361,
     369,    12,   159,     7,    38,    40,    47,    48,    49,    50,
      51,    52,    58,    59,    65,   139,   150,   151,   152,   153,
     225,   226,   227,   229,   231,   233,   235,   237,   238,   263,
     280,   294,   311,   334,    39,    46,   139,   263,   288,   289,
     290,   292,    41,    42,    43,    44,    45,   139,   263,   292,
     302,   303,   304,   306,   307,   309,   310,    56,    60,    61,
      62,    63,    64,   139,   263,   319,   320,   321,   322,   324,
     326,   328,   330,   332,    15,    30,    32,    33,    35,    36,
      37,   139,   175,   247,   248,   249,   250,   251,   252,   253,
     255,   257,   259,   260,   262,    31,    34,   139,   175,   251,
     257,   271,   272,   273,   274,   275,   277,   278,   279,    68,
      69,   139,   201,   202,   203,   205,     6,     3,     4,     8,
       3,   145,   376,   372,   374,     4,     3,     8,   156,   162,
     164,     4,     4,     4,     4,     4,   218,   240,   264,   181,
     192,   187,   339,   194,   208,   349,     4,   362,   370,     3,
       8,   160,     8,   341,   281,   295,   228,   230,   232,     4,
       4,   236,   234,   312,   335,     3,     8,   291,   293,     3,
       8,   305,     4,   308,     4,     4,     3,     8,   333,   323,
     325,   327,   329,   331,     8,     3,   254,   176,     4,   258,
     256,   261,     4,     8,     3,   276,     4,     8,     3,   204,
     206,     3,     8,   126,   126,   109,     4,     4,     4,     4,
     143,     4,     4,     4,   110,   110,   110,   110,   110,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   110,
       4,     4,   149,     4,    57,   139,   175,   263,   342,   343,
     344,   345,   346,     4,     4,     4,     4,     4,   110,   112,
       4,     4,     4,     4,   226,     4,     4,   289,     4,   110,
       4,   110,   110,   303,     4,     4,     4,     4,     4,     4,
     321,     4,     4,   110,     4,     4,     4,   112,   249,     4,
     112,   273,     4,     4,   202,     4,     7,     7,   126,   126,
       7,     7,     7,     5,     5,     5,     5,     5,   135,     5,
       5,     5,     7,     7,     7,     7,   135,   347,     8,     3,
       5,     5,   109,   109,   109,   109,   109,     5,     7,   109,
     128,   130,   109,   109,   135,   135,   135,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   126,   126,   148,
      91,   377,   378,   379,   159,    15,    16,    17,    18,    19,
      20,    21,   139,   165,   166,   167,   169,   171,   173,   175,
     177,   178,   179,   165,     7,   219,   220,   221,     7,   241,
     242,   243,     7,   265,   266,   267,    62,   109,   182,   183,
     184,   185,   136,    63,   184,   188,   189,   190,   233,   340,
       7,   195,   196,   197,    71,    72,    73,    74,    75,    76,
     209,   210,   211,   212,   213,   214,   215,   216,    15,    81,
      82,    83,    84,   139,   177,   350,   351,   352,   355,   356,
     358,   359,    87,    88,   363,   364,   365,   367,   132,     4,
     344,     7,   282,   283,   284,     7,   296,   297,   298,     7,
     313,   314,   315,    66,   336,     8,   380,     3,     8,     8,
     168,   170,   172,   174,     4,     4,     4,     3,     8,     8,
     222,     6,     3,   244,     6,     3,   268,     6,     3,     3,
       6,   137,     3,     6,     3,     6,   198,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   353,   357,     4,
       4,     4,     3,     8,   366,   368,     3,     8,     8,   109,
     285,     6,     3,   299,     6,     3,   316,     6,     3,   337,
       8,     4,   378,     4,     4,     4,     4,   112,   110,   112,
     166,   225,   221,   247,   243,   271,   267,   183,     6,   189,
     233,   201,   197,   110,   110,   110,   110,   110,   110,   210,
       4,     4,   110,   110,   110,   351,     4,     4,   364,   288,
     284,   302,   298,   319,   315,     4,     5,   109,   109,   109,
     109,     8,     8,     8,     8,    78,    79,    80,   354,   109,
     109,   109,     8,     8,     8,   109,     7,   381,   382,   383,
       3,     6,    92,    94,    95,   139,   175,   384,   385,   386,
     387,   389,   382,   390,     4,   388,     3,     8,     4,   110,
       4,   385,     5,   109,     7,   391,   392,   393,     3,     6,
      93,   394,   395,   392,   396,     3,     8,     4,   395,   109
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   113,   115,   114,   116,   114,   117,   114,   118,   114,
     119,   114,   120,   114,   121,   114,   122,   114,   123,   114,
     124,   114,   125,   114,   126,   126,   126,   126,   126,   126,
     126,   127,   129,   128,   130,   131,   131,   132,   132,   134,
     133,   136,   135,   137,   137,   138,   138,   139,   141,   140,
     142,   142,   143,   143,   143,   143,   143,   145,   144,   147,
     146,   148,   148,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   150,   151,   152,   153,   154,
     156,   155,   158,   157,   160,   159,   162,   161,   164,   163,
     165,   165,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   168,   167,   170,   169,   172,   171,   174,   173,   176,
     175,   177,   178,   179,   181,   180,   182,   182,   183,   183,
     184,   185,   187,   186,   188,   188,   189,   189,   190,   192,
     191,   194,   193,   195,   195,   196,   196,   198,   197,   200,
     199,   201,   201,   201,   202,   202,   204,   203,   206,   205,
     208,   207,   209,   209,   210,   210,   210,   210,   210,   210,
     211,   212,   213,   214,   215,   216,   218,   217,   219,   219,
     220,   220,   222,   221,   224,   223,   225,   225,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   228,   227,   230,   229,   232,
     231,   234,   233,   236,   235,   237,   238,   240,   239,   241,
     241,   242,   242,   244,   243,   246,   245,   247,   247,   248,
     248,   249,   249,   249,   249,   249,   249,   249,   249,   250,
     251,   252,   254,   253,   256,   255,   258,   257,   259,   261,
     260,   262,   264,   263,   265,   265,   266,   266,   268,   267,
     270,   269,   271,   271,   272,   272,   273,   273,   273,   273,
     273,   273,   274,   276,   275,   277,   278,   279,   281,   280,
     282,   282,   283,   283,   285,   284,   287,   286,   288,   288,
     289,   289,   289,   289,   291,   290,   293,   292,   295,   294,
     296,   296,   297,   297,   299,   298,   301,   300,   302,   302,
     303,   303,   303,   303,   303,   303,   303,   303,   305,   304,
     306,   308,   307,   309,   310,   312,   311,   313,   313,   314,
     314,   316,   315,   318,   317,   319,   319,   320,   320,   321,
     321,   321,   321,   321,   321,   321,   321,   323,   322,   325,
     324,   327,   326,   329,   328,   331,   330,   333,   332,   335,
     334,   337,   336,   339,   338,   340,   340,   341,   233,   342,
     342,   343,   343,   344,   344,   344,   344,   345,   347,   346,
     349,   348,   350,   350,   351,   351,   351,   351,   351,   351,
     351,   353,   352,   354,   354,   354,   355,   357,   356,   358,
     359,   360,   362,   361,   363,   363,   364,   364,   366,   365,
     368,   367,   370,   369,   372,   371,   374,   373,   376,   375,
     377,   377,   378,   380,   379,   381,   381,   383,   382,   384,
     384,   385,   385,   385,   385,   385,   386,   388,   387,   390,
     389,   391,   391,   393,   392,   394,   394,   396,   395
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     0,     1,     3,     5,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       0,     6,     0,     4,     0,     4,     0,     6,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     0,     4
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
  "\"delegated-len\"", "\"user-context\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"Dhcp4\"", "\"DhcpDdns\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "value", "sub_json", "map2", "$@12", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@13", "list2", "$@14", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@15",
  "global_objects", "global_object", "dhcp6_object", "$@16", "sub_dhcp6",
  "$@17", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@18",
  "sub_interfaces6", "$@19", "interface_config_map", "$@20",
  "lease_database", "$@21", "hosts_database", "$@22",
  "database_map_params", "database_map_param", "database_type", "$@23",
  "user", "$@24", "password", "$@25", "host", "$@26", "name", "$@27",
  "persist", "lfc_interval", "readonly", "mac_sources", "$@28",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@29",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "relay_supplied_options", "$@30", "hooks_libraries",
  "$@31", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@32", "sub_hooks_library", "$@33", "hooks_params",
  "hooks_param", "library", "$@34", "parameters", "$@35",
  "expired_leases_processing", "$@36", "expired_leases_params",
  "expired_leases_param", "reclaim_timer_wait_time",
  "flush_reclaimed_timer_wait_time", "hold_reclaimed_time",
  "max_reclaim_leases", "max_reclaim_time", "unwarned_reclaim_cycles",
  "subnet6_list", "$@37", "subnet6_list_content", "not_empty_subnet6_list",
  "subnet6", "$@38", "sub_subnet6", "$@39", "subnet6_params",
  "subnet6_param", "subnet", "$@40", "interface", "$@41", "interface_id",
  "$@42", "client_class", "$@43", "reservation_mode", "$@44", "id",
  "rapid_commit", "option_def_list", "$@45", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@46",
  "sub_option_def", "$@47", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@48",
  "option_def_record_types", "$@49", "space", "$@50", "option_def_space",
  "option_def_encapsulate", "$@51", "option_def_array", "option_data_list",
  "$@52", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@53", "sub_option_data", "$@54",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@55",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@56", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@57", "sub_pool6", "$@58", "pool_params",
  "pool_param", "pool_entry", "$@59", "user_context", "$@60",
  "pd_pools_list", "$@61", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@62", "sub_pd_pool",
  "$@63", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@64",
  "pd_prefix_len", "excluded_prefix", "$@65", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@66", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@67", "sub_reservation",
  "$@68", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@69", "prefixes", "$@70", "duid",
  "$@71", "hw_address", "$@72", "hostname", "$@73",
  "reservation_client_classes", "$@74", "relay", "$@75", "relay_map",
  "$@76", "client_classes", "$@77", "client_classes_list", "$@78",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@79",
  "server_id", "$@80", "server_id_params", "server_id_param",
  "server_id_type", "$@81", "duid_type", "htype", "identifier", "$@82",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@83",
  "control_socket_params", "control_socket_param", "socket_type", "$@84",
  "socket_name", "$@85", "dhcp_ddns", "$@86", "dhcp4_json_object", "$@87",
  "dhcpddns_json_object", "$@88", "logging_object", "$@89",
  "logging_params", "logging_param", "loggers", "$@90", "loggers_entries",
  "logger_entry", "$@91", "logger_params", "logger_param", "debuglevel",
  "severity", "$@92", "output_options_list", "$@93",
  "output_options_list_content", "output_entry", "$@94", "output_params",
  "output_param", "$@95", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   210,   210,   210,   211,   211,   212,   212,   213,   213,
     214,   214,   215,   215,   216,   216,   217,   217,   218,   218,
     219,   219,   220,   220,   228,   229,   230,   231,   232,   233,
     234,   237,   242,   242,   253,   256,   257,   260,   264,   271,
     271,   279,   279,   286,   287,   290,   294,   305,   315,   315,
     327,   328,   332,   333,   334,   335,   336,   339,   339,   356,
     356,   364,   365,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   394,   399,   404,   409,   414,
     419,   419,   429,   429,   437,   437,   447,   447,   457,   457,
     467,   468,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   482,   482,   490,   490,   498,   498,   506,   506,   514,
     514,   522,   527,   532,   537,   537,   547,   548,   551,   552,
     555,   560,   565,   565,   575,   576,   579,   580,   583,   588,
     588,   598,   598,   608,   609,   612,   613,   616,   616,   624,
     624,   632,   633,   634,   637,   638,   641,   641,   649,   649,
     657,   657,   667,   668,   671,   672,   673,   674,   675,   676,
     679,   684,   689,   694,   699,   704,   712,   712,   725,   726,
     729,   730,   737,   737,   760,   760,   769,   770,   774,   775,
     776,   777,   778,   779,   780,   781,   782,   783,   784,   785,
     786,   787,   788,   789,   790,   793,   793,   801,   801,   809,
     809,   817,   817,   825,   825,   833,   838,   847,   847,   859,
     860,   863,   864,   869,   869,   880,   880,   890,   891,   894,
     895,   898,   899,   900,   901,   902,   903,   904,   905,   908,
     910,   915,   917,   917,   925,   925,   933,   933,   941,   943,
     943,   951,   960,   960,   972,   973,   978,   979,   984,   984,
     995,   995,  1006,  1007,  1012,  1013,  1018,  1019,  1020,  1021,
    1022,  1023,  1026,  1028,  1028,  1036,  1038,  1040,  1048,  1048,
    1060,  1061,  1064,  1065,  1068,  1068,  1076,  1076,  1084,  1085,
    1088,  1089,  1090,  1091,  1094,  1094,  1102,  1102,  1112,  1112,
    1124,  1125,  1128,  1129,  1132,  1132,  1140,  1140,  1148,  1149,
    1152,  1153,  1154,  1155,  1156,  1157,  1158,  1159,  1162,  1162,
    1170,  1175,  1175,  1183,  1188,  1196,  1196,  1206,  1207,  1210,
    1211,  1214,  1214,  1222,  1222,  1230,  1231,  1234,  1235,  1239,
    1240,  1241,  1242,  1243,  1244,  1245,  1246,  1249,  1249,  1259,
    1259,  1269,  1269,  1277,  1277,  1285,  1285,  1293,  1293,  1306,
    1306,  1316,  1316,  1327,  1327,  1337,  1338,  1341,  1341,  1349,
    1350,  1353,  1354,  1357,  1358,  1359,  1360,  1363,  1365,  1365,
    1376,  1376,  1386,  1387,  1390,  1391,  1392,  1393,  1394,  1395,
    1396,  1399,  1399,  1406,  1407,  1408,  1411,  1416,  1416,  1424,
    1429,  1436,  1443,  1443,  1453,  1454,  1457,  1458,  1461,  1461,
    1469,  1469,  1479,  1479,  1491,  1491,  1498,  1498,  1510,  1510,
    1523,  1524,  1528,  1532,  1532,  1544,  1545,  1549,  1549,  1557,
    1558,  1561,  1562,  1563,  1564,  1565,  1568,  1572,  1572,  1580,
    1580,  1590,  1591,  1594,  1594,  1602,  1603,  1606,  1606
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
#line 3683 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1614 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
