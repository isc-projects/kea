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
#define yylex   parser4_lex

// First part of user declarations.

#line 39 "dhcp4_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp4_parser.h"

// User implementation prologue.

#line 53 "dhcp4_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:413

#include <dhcp4/parser_context.h>

#line 59 "dhcp4_parser.cc" // lalr1.cc:413


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp4_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
    :
#if PARSER4_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp4Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp4Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp4Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp4Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 108: // value
      case 315: // version_value
        value.move< ElementPtr > (that.value);
        break;

      case 95: // "boolean"
        value.move< bool > (that.value);
        break;

      case 94: // "floating point"
        value.move< double > (that.value);
        break;

      case 93: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 92: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 108: // value
      case 315: // version_value
        value.copy< ElementPtr > (that.value);
        break;

      case 95: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 94: // "floating point"
        value.copy< double > (that.value);
        break;

      case 93: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 92: // "constant string"
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo,
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
            case 92: // "constant string"

#line 183 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 93: // "integer"

#line 183 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 94: // "floating point"

#line 183 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 95: // "boolean"

#line 183 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 108: // value

#line 183 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 315: // version_value

#line 183 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 389 "dhcp4_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp4Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  inline Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::parse ()
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
      case 108: // value
      case 315: // version_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 95: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 94: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 93: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 92: // "constant string"
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
#line 192 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 193 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 194 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 195 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 196 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 197 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 198 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 199 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 200 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 201 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 209 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 210 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 211 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 212 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 213 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 214 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 80:
#line 371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 81:
#line 376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 405 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 996 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1535 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 789 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1617 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1635 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1024 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1867 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[3].location)));
    ctx.stack_.back()->set("ip-address", addr);
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1136 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1159 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("version", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 2202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1282 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 2208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2374 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2439 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2469 "dhcp4_parser.cc" // lalr1.cc:859
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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Dhcp4Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Dhcp4Parser::yypact_ninf_ = -376;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     169,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,    29,    16,    26,    46,    57,    77,    84,   107,   113,
     120,   121,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,    16,   -65,    20,    56,    43,    15,    -4,    91,
      59,   132,   -29,  -376,    92,   127,   134,   123,   147,  -376,
    -376,  -376,  -376,   173,  -376,    32,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,   174,   189,   191,   199,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,   207,  -376,  -376,  -376,
    -376,   114,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,   161,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,   211,   213,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,   149,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,   150,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,   164,   216,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,   218,  -376,  -376,  -376,   219,  -376,  -376,
    -376,   212,   223,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,   226,  -376,  -376,  -376,  -376,   227,
     224,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
     151,  -376,  -376,  -376,  -376,    16,    16,  -376,   144,   233,
     237,   238,   239,  -376,    20,  -376,   241,   243,   244,   156,
     170,   171,   172,   257,   258,   262,   263,   264,   265,   266,
     267,   179,   269,   270,   271,    56,  -376,   272,  -376,   106,
     273,   274,   275,   276,   277,   278,   190,   192,   280,   281,
     282,   284,    15,  -376,   285,    -4,  -376,   286,   287,   288,
     289,   290,   291,   292,  -376,    91,   293,   294,   206,   296,
     297,   298,   208,  -376,    59,   300,   210,  -376,   132,   302,
     303,    45,  -376,  -376,  -376,   304,   305,   306,    16,    16,
    -376,   307,   308,   311,  -376,  -376,  -376,  -376,   314,   315,
     316,   317,   318,   319,   320,   321,  -376,    48,   322,   325,
    -376,   328,  -376,  -376,  -376,  -376,   301,   331,  -376,  -376,
    -376,   245,   246,   330,   248,   249,   250,  -376,  -376,   251,
     252,   341,   329,  -376,   255,  -376,   328,   256,   259,   260,
     261,   268,   279,  -376,   283,   295,  -376,   299,   309,   310,
    -376,  -376,   312,  -376,  -376,   313,    16,  -376,    16,    56,
     235,  -376,  -376,    43,    31,    31,   342,   347,   348,   155,
      27,   349,   323,    68,  -376,  -376,  -376,  -376,   142,   -65,
    -376,  -376,   354,  -376,   106,  -376,  -376,   352,  -376,  -376,
    -376,  -376,  -376,   355,   253,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,   153,  -376,   165,  -376,  -376,   353,  -376,  -376,
    -376,   359,   360,   361,  -376,   167,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,   168,  -376,   362,   363,  -376,
    -376,   364,   366,  -376,  -376,   367,   369,  -376,  -376,  -376,
    -376,  -376,  -376,    38,  -376,  -376,  -376,  -376,  -376,    65,
    -376,   368,   373,  -376,   374,   176,  -376,  -376,   375,   376,
     377,  -376,  -376,  -376,   178,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,   182,  -376,  -376,  -376,   184,    16,   324,  -376,
    -376,   371,   379,  -376,  -376,   382,   380,  -376,  -376,   381,
    -376,   386,   235,  -376,  -376,   388,   389,   390,   326,   327,
     332,    31,  -376,  -376,    15,  -376,   342,    59,  -376,   347,
     132,  -376,   348,   155,  -376,    27,  -376,   -29,  -376,   349,
     333,   323,  -376,   391,   335,   336,   337,    68,  -376,   392,
     393,   142,  -376,  -376,   394,  -376,    -4,  -376,   352,    91,
    -376,   355,   395,  -376,   398,  -376,   339,   340,   343,  -376,
    -376,  -376,  -376,   186,  -376,   399,  -376,   400,  -376,  -376,
    -376,   188,  -376,  -376,  -376,   344,  -376,  -376,  -376,  -376,
     345,   346,  -376,  -376,   194,  -376,   401,  -376,   350,   378,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,    96,  -376,    -3,   378,  -376,  -376,
     402,  -376,  -376,  -376,   196,  -376,  -376,  -376,  -376,  -376,
     406,   351,   407,    -3,  -376,   408,  -376,   356,  -376,   405,
    -376,  -376,   110,  -376,   357,   405,  -376,  -376,   198,  -376,
    -376,   410,   357,  -376,   358,  -376,  -376
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    86,     9,
     162,    11,   267,    13,   284,    15,   207,    17,   241,    19,
     138,    21,    40,    32,     0,     0,     0,     0,     0,   286,
     209,   243,     0,    42,     0,    41,     0,     0,    33,    54,
     372,   368,   370,     0,    53,     0,    47,    49,    51,    52,
      50,    84,    90,    92,     0,     0,     0,     0,   154,   199,
     233,   119,   317,   130,   149,   334,     0,   351,   356,   366,
      79,     0,    58,    60,    61,    62,    63,    65,    66,    67,
      68,    72,    73,    64,    70,    71,    69,    74,    75,    76,
      77,    78,    88,     0,   321,   185,   187,   259,   183,   189,
     191,     0,     0,   195,   193,   276,   313,   182,   166,   167,
     168,     0,   164,   171,   180,   181,   172,   173,   176,   178,
     174,   175,   169,   170,   177,   179,   274,   273,   272,     0,
     269,   271,   311,   301,   303,   307,   305,   309,   299,   298,
     297,     0,   287,   288,   294,   290,   295,   292,   293,   296,
     291,   105,   113,     0,   227,   225,   230,     0,   220,   224,
     221,     0,   210,   211,   213,   223,   214,   215,   216,   229,
     217,   218,   219,   254,     0,   252,   253,   256,   257,     0,
     244,   245,   247,   248,   249,   250,   251,   145,   147,   142,
       0,   140,   143,   144,    37,     0,     0,    31,     0,     0,
       0,     0,     0,    44,     0,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,     0,    87,   323,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   163,     0,     0,   268,     0,     0,     0,
       0,     0,     0,     0,   285,     0,     0,     0,     0,     0,
       0,     0,     0,   208,     0,     0,     0,   242,     0,     0,
       0,     0,   139,    43,    34,     0,     0,     0,     0,     0,
      48,     0,     0,     0,    80,    81,    82,    83,     0,     0,
       0,     0,     0,     0,     0,     0,   350,     0,     0,     0,
      59,     0,   332,   330,   331,   329,     0,   324,   325,   327,
     328,     0,     0,     0,     0,     0,     0,   197,   198,     0,
       0,     0,     0,   165,     0,   270,     0,     0,     0,     0,
       0,     0,     0,   289,     0,     0,   222,     0,     0,     0,
     232,   212,     0,   258,   246,     0,     0,   141,     0,     0,
       0,   369,   371,     0,     0,     0,   156,   201,   235,     0,
       0,   132,     0,     0,   355,   353,   354,   352,     0,     0,
      38,    89,     0,   322,     0,   186,   188,   261,   184,   190,
     192,   196,   194,   278,     0,   275,   312,   302,   304,   308,
     306,   310,   300,   106,   114,   228,   226,   231,   255,   146,
     148,    35,     0,   377,     0,   374,   376,     0,   107,   109,
     111,     0,     0,     0,   104,     0,    94,    96,    97,    98,
      99,   100,   101,   102,   103,     0,   160,     0,   157,   158,
     205,     0,   202,   203,   239,     0,   236,   237,   118,   127,
     128,   129,   123,     0,   121,   124,   125,   126,   319,     0,
     136,     0,   133,   134,     0,     0,   151,   346,     0,     0,
       0,   344,   338,   343,     0,   336,   341,   339,   340,   342,
     362,   364,     0,   358,   360,   361,     0,    40,     0,   326,
     265,     0,   262,   263,   282,     0,   279,   280,   315,     0,
      55,     0,     0,   373,    85,     0,     0,     0,     0,     0,
       0,     0,    91,    93,     0,   155,     0,   209,   200,     0,
     243,   234,     0,     0,   120,     0,   318,     0,   131,     0,
       0,     0,   150,     0,     0,     0,     0,     0,   335,     0,
       0,     0,   357,   367,     0,   333,     0,   260,     0,   286,
     277,     0,     0,   314,     0,   375,     0,     0,     0,   115,
     116,   117,    95,     0,   159,     0,   204,     0,   238,   122,
     320,     0,   135,   153,   152,     0,   345,   348,   349,   337,
       0,     0,   359,    39,     0,   264,     0,   281,     0,     0,
     108,   110,   112,   161,   206,   240,   137,   347,   363,   365,
     266,   283,   316,   381,     0,   379,     0,     0,   378,   393,
       0,   391,   389,   385,     0,   383,   387,   388,   386,   380,
       0,     0,     0,     0,   382,     0,   390,     0,   384,     0,
     392,   397,     0,   395,     0,     0,   394,   401,     0,   399,
     396,     0,     0,   398,     0,   400,   402
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,     8,  -376,  -376,  -376,  -376,   -32,  -376,  -376,
      42,  -376,   -90,  -376,   -54,  -376,  -376,  -376,   185,  -376,
    -376,  -376,  -376,    39,   197,   -56,   -43,   -40,  -376,  -376,
    -376,  -376,  -376,    40,  -376,  -376,  -376,  -376,  -376,    37,
    -107,  -369,  -376,  -376,  -376,  -376,  -376,  -376,  -376,   -59,
    -376,  -375,  -376,  -376,  -376,  -376,  -376,  -376,  -118,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -116,  -376,  -376,  -376,
    -108,   139,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -110,
    -376,  -376,  -376,  -376,   -93,  -376,  -376,  -376,   -89,   175,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -371,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
     -88,  -376,  -376,  -376,   -91,  -376,   159,  -376,   -52,  -376,
    -376,  -376,  -376,   -48,  -376,  -376,  -376,  -376,  -376,   -47,
    -376,  -376,  -376,   -87,  -376,  -376,  -376,   -86,  -376,   158,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -119,  -376,  -376,  -376,  -109,   183,  -376,  -376,  -376,  -376,
    -376,  -376,  -112,  -376,  -376,  -376,  -106,  -376,   177,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,    60,  -376,  -376,  -376,  -376,  -376,  -376,
     -97,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -100,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,   -57,  -376,  -376,
    -376,  -161,  -376,  -376,  -176,  -376,  -376,  -376,  -376,  -376,
    -376,  -187,  -376,  -376,  -193,  -376
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,    67,    68,    33,    52,
     401,   507,    64,    65,   100,    35,    54,    75,    76,    77,
     229,    37,    55,   101,   102,   103,   104,   105,   106,   107,
     236,    39,    56,   123,   257,   108,   237,   109,   238,   445,
     446,   189,   286,   448,   525,   449,   526,   450,   527,   190,
     287,   452,   453,   454,   472,   110,   246,   473,   474,   475,
     476,   477,   111,   248,   481,   482,   483,   547,    51,    62,
     220,   221,   222,   299,   223,   300,   112,   249,   485,   486,
     113,   243,   457,   458,   459,   534,    41,    57,   141,   142,
     143,   263,   144,   260,   145,   261,   146,   264,   147,   265,
     148,   269,   149,   268,   150,   151,   114,   244,   461,   462,
     463,   537,    47,    60,   191,   192,   193,   194,   195,   196,
     197,   198,   290,   199,   289,   200,   201,   291,   202,   115,
     245,   465,   466,   467,   540,    49,    61,   209,   210,   211,
     212,   213,   295,   214,   215,   216,   153,   262,   511,   512,
     513,   566,    43,    58,   159,   160,   161,   274,   154,   270,
     515,   516,   517,   569,    45,    59,   171,   172,   173,   174,
     283,   175,   278,   176,   279,   177,   281,   178,   280,   179,
     282,   180,   277,   155,   271,   519,   572,   116,   247,   479,
     259,   336,   337,   338,   339,   340,   402,   117,   250,   494,
     495,   496,   497,   553,   498,   499,   118,   119,   252,   397,
     120,   253,   502,   503,   504,   559,   505,   560,   121,   254,
      78,   231,    79,   232,    80,   230,   434,   435,   436,   521,
     624,   625,   626,   634,   635,   636,   637,   642,   638,   640,
     652,   653,   654,   658,   659,   661
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   138,   206,   137,   157,   169,   188,   205,   219,   207,
     152,   158,   170,   208,   139,   447,   447,   140,   493,   478,
      30,    23,   124,    24,   492,    25,    90,    66,   182,    22,
      69,   217,   218,    34,   124,   234,   156,    84,    85,    86,
     235,   543,   125,   126,   544,    90,   181,   438,   439,   440,
     441,   442,   443,    36,   127,   122,   128,   129,   130,   131,
     132,   133,   182,    73,    38,   134,   135,    81,   545,    82,
      83,   546,   136,   629,   181,   630,   631,   134,    84,    85,
      86,    87,    88,   181,    40,    89,    90,   441,    73,    73,
     182,    42,   183,   184,    70,   185,   186,   187,   224,   627,
      71,    72,   628,    91,    92,   217,   218,    73,    26,    27,
      28,    29,    73,   655,    44,    93,   656,   255,    94,    95,
      46,    90,   256,    73,    96,    97,    98,    48,    50,    99,
     225,   227,   487,   488,   489,   490,    90,   182,   226,   162,
     394,   395,   396,   163,   164,   165,   166,   167,    73,   168,
     228,    73,   272,   275,   301,   332,   255,   273,   276,   302,
      73,   520,   447,   182,   203,   183,   184,   204,   522,   258,
     531,   531,   284,   523,   590,   532,   533,   233,   239,   551,
      74,   557,   493,    73,   552,   561,   558,   228,   492,   272,
     562,   301,   563,   240,   613,   241,   616,   275,    73,   643,
     334,   662,   620,   242,   644,   333,   663,   468,   469,   470,
     471,   251,   335,   500,   501,   266,   138,   267,   137,   285,
     293,   157,   288,   292,    73,   152,   294,   298,   158,   139,
     296,   169,   140,   303,   304,   297,   305,   306,   170,   206,
     188,   307,   308,   309,   205,   311,   207,   312,   313,   314,
     208,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   318,   319,   315,   316,   317,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   331,   341,   342,   343,
     344,   345,   346,   347,   349,   350,   351,   348,   352,   354,
     356,   357,   358,   359,   360,   361,   362,   364,   365,   366,
     367,   368,   369,   370,   372,   373,   375,   376,   378,   403,
     433,   518,   379,   380,   383,   384,   381,   382,   385,   386,
     387,   388,   389,   390,   391,   451,   451,   392,   393,   398,
     444,   444,   399,   400,   404,   407,   414,   405,   406,   491,
     408,   409,   410,   411,   412,   334,   413,   415,   417,   456,
     333,   418,   419,   420,   460,   464,   480,   335,   508,   510,
     421,   524,   514,   528,   529,   530,   536,   506,   535,   539,
     538,   422,   542,   541,   548,   423,   549,   567,   550,   554,
     555,   556,   568,   571,   430,   623,   431,   424,   570,   573,
     574,   425,   576,   577,   578,   595,   600,   601,   416,   608,
     603,   426,   427,   609,   428,   429,   641,   614,   615,   621,
     645,   647,   651,   649,   664,   484,   565,   564,   432,   310,
     580,   579,   455,   437,   582,   589,   593,   581,   596,   597,
     598,   610,   611,   592,   657,   612,   617,   618,   619,   591,
     377,   594,   622,   584,   646,   583,   585,   353,   650,   605,
     666,   586,   330,   371,   587,   588,   374,   604,   355,   607,
     599,   602,   363,   606,   509,   575,   639,   648,   660,   665,
       0,     0,   451,     0,     0,     0,     0,   444,   138,     0,
     137,   206,     0,   188,     0,     0,   205,   152,   207,     0,
       0,   139,   208,   219,   140,     0,     0,     0,     0,     0,
       0,     0,     0,   491,     0,     0,     0,     0,     0,     0,
       0,     0,   157,     0,     0,   169,     0,     0,     0,   158,
       0,     0,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   633,     0,     0,
       0,     0,   632,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   633,     0,     0,     0,     0,   632
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,   384,   385,    57,   393,   390,
      12,     5,     7,     7,   393,     9,    30,    92,    31,     0,
      10,    60,    61,     7,     7,     3,    40,    22,    23,    24,
       8,     3,    27,    28,     6,    30,    15,    16,    17,    18,
      19,    20,    21,     7,    39,    12,    41,    42,    43,    44,
      45,    46,    31,    92,     7,    50,    51,    11,     3,    13,
      14,     6,    57,    76,    15,    78,    79,    50,    22,    23,
      24,    25,    26,    15,     7,    29,    30,    19,    92,    92,
      31,     7,    33,    34,    74,    36,    37,    38,     6,     3,
      80,    81,     6,    47,    48,    60,    61,    92,    92,    93,
      94,    95,    92,     3,     7,    59,     6,     3,    62,    63,
       7,    30,     8,    92,    68,    69,    70,     7,     7,    73,
       3,     8,    64,    65,    66,    67,    30,    31,     4,    48,
      92,    93,    94,    52,    53,    54,    55,    56,    92,    58,
       3,    92,     3,     3,     3,    49,     3,     8,     8,     8,
      92,     8,   531,    31,    32,    33,    34,    35,     3,     8,
       3,     3,     8,     8,   545,     8,     8,     4,     4,     3,
     234,     3,   557,    92,     8,     3,     8,     3,   557,     3,
       8,     3,     8,     4,     8,     4,     8,     3,    92,     3,
     259,     3,     8,     4,     8,   259,     8,    52,    53,    54,
      55,     4,   259,    71,    72,     4,   272,     4,   272,     3,
       8,   275,     4,     4,    92,   272,     3,     3,   275,   272,
       4,   285,   272,   225,   226,     8,    92,     4,   285,   298,
     294,     4,     4,     4,   298,     4,   298,     4,     4,    93,
     298,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,     4,     4,    93,    93,    93,     4,     4,     4,     4,
       4,     4,    93,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    93,     4,     4,     4,    95,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    93,
       4,     4,     4,    95,     4,    95,     4,     4,     4,     8,
      75,    58,     7,     7,     7,     7,   308,   309,     7,     5,
       5,     5,     5,     5,     5,   384,   385,     7,     7,     7,
     384,   385,     7,     5,     3,     5,     7,    92,    92,   393,
      92,    92,    92,    92,    92,   404,     5,    92,    92,     7,
     404,    92,    92,    92,     7,     7,     7,   404,     4,     7,
      92,     8,     7,     4,     4,     4,     3,   399,     6,     3,
       6,    92,     3,     6,     6,    92,     3,     6,     4,     4,
       4,     4,     3,     3,   376,     7,   378,    92,     6,     8,
       4,    92,     4,     4,     4,     4,     4,     4,   356,     4,
       6,    92,    92,     5,    92,    92,     4,     8,     8,     8,
       4,     4,     7,     5,     4,    92,    92,   507,   379,   234,
      93,    95,   385,   383,   531,   543,    93,    95,    93,    93,
      93,    92,    92,   549,    77,    92,    92,    92,    92,   547,
     301,   551,    92,   536,    93,   534,   537,   272,    92,   568,
      92,   539,   255,   294,   540,   542,   298,   566,   275,   571,
     557,   561,   285,   569,   404,   522,   627,   643,   655,   662,
      -1,    -1,   531,    -1,    -1,    -1,    -1,   531,   534,    -1,
     534,   540,    -1,   537,    -1,    -1,   540,   534,   540,    -1,
      -1,   534,   540,   547,   534,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   557,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   566,    -1,    -1,   569,    -1,    -1,    -1,   566,
      -1,    -1,   569,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   626,    -1,    -1,
      -1,    -1,   626,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   643,    -1,    -1,    -1,    -1,   643
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,     0,     5,     7,     9,    92,    93,    94,    95,
     108,   109,   110,   114,     7,   121,     7,   127,     7,   137,
       7,   192,     7,   258,     7,   270,     7,   218,     7,   241,
       7,   174,   115,   111,   122,   128,   138,   193,   259,   271,
     219,   242,   175,   108,   118,   119,    92,   112,   113,    10,
      74,    80,    81,    92,   120,   123,   124,   125,   326,   328,
     330,    11,    13,    14,    22,    23,    24,    25,    26,    29,
      30,    47,    48,    59,    62,    63,    68,    69,    70,    73,
     120,   129,   130,   131,   132,   133,   134,   135,   141,   143,
     161,   168,   182,   186,   212,   235,   293,   303,   312,   313,
     316,   324,    12,   139,     7,    27,    28,    39,    41,    42,
      43,    44,    45,    46,    50,    51,    57,   120,   131,   132,
     133,   194,   195,   196,   198,   200,   202,   204,   206,   208,
     210,   211,   235,   252,   264,   289,    40,   120,   235,   260,
     261,   262,    48,    52,    53,    54,    55,    56,    58,   120,
     235,   272,   273,   274,   275,   277,   279,   281,   283,   285,
     287,    15,    31,    33,    34,    36,    37,    38,   120,   147,
     155,   220,   221,   222,   223,   224,   225,   226,   227,   229,
     231,   232,   234,    32,    35,   120,   155,   224,   229,   243,
     244,   245,   246,   247,   249,   250,   251,    60,    61,   120,
     176,   177,   178,   180,     6,     3,     4,     8,     3,   126,
     331,   327,   329,     4,     3,     8,   136,   142,   144,     4,
       4,     4,     4,   187,   213,   236,   162,   294,   169,   183,
     304,     4,   314,   317,   325,     3,     8,   140,     8,   296,
     199,   201,   253,   197,   203,   205,     4,     4,   209,   207,
     265,   290,     3,     8,   263,     3,     8,   288,   278,   280,
     284,   282,   286,   276,     8,     3,   148,   156,     4,   230,
     228,   233,     4,     8,     3,   248,     4,     8,     3,   179,
     181,     3,     8,   108,   108,    92,     4,     4,     4,     4,
     124,     4,     4,     4,    93,    93,    93,    93,     4,     4,
       4,     4,     4,     4,     4,     4,    93,     4,     4,     4,
     130,     4,    49,   120,   155,   235,   297,   298,   299,   300,
     301,     4,     4,     4,     4,     4,     4,    93,    95,     4,
       4,     4,     4,   195,     4,   261,     4,     4,     4,     4,
       4,     4,     4,   274,     4,     4,    93,     4,     4,     4,
      95,   222,     4,    95,   245,     4,     4,   177,     4,     7,
       7,   108,   108,     7,     7,     7,     5,     5,     5,     5,
       5,     5,     7,     7,    92,    93,    94,   315,     7,     7,
       5,   116,   302,     8,     3,    92,    92,     5,    92,    92,
      92,    92,    92,     5,     7,    92,   116,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
     108,   108,   129,    75,   332,   333,   334,   139,    16,    17,
      18,    19,    20,    21,   120,   145,   146,   147,   149,   151,
     153,   155,   157,   158,   159,   145,     7,   188,   189,   190,
       7,   214,   215,   216,     7,   237,   238,   239,    52,    53,
      54,    55,   160,   163,   164,   165,   166,   167,   206,   295,
       7,   170,   171,   172,    92,   184,   185,    64,    65,    66,
      67,   120,   147,   157,   305,   306,   307,   308,   310,   311,
      71,    72,   318,   319,   320,   322,   113,   117,     4,   299,
       7,   254,   255,   256,     7,   266,   267,   268,    58,   291,
       8,   335,     3,     8,     8,   150,   152,   154,     4,     4,
       4,     3,     8,     8,   191,     6,     3,   217,     6,     3,
     240,     6,     3,     3,     6,     3,     6,   173,     6,     3,
       4,     3,     8,   309,     4,     4,     4,     3,     8,   321,
     323,     3,     8,     8,   118,    92,   257,     6,     3,   269,
       6,     3,   292,     8,     4,   333,     4,     4,     4,    95,
      93,    95,   146,   194,   190,   220,   216,   243,   239,   164,
     206,   176,   172,    93,   185,     4,    93,    93,    93,   306,
       4,     4,   319,     6,   260,   256,   272,   268,     4,     5,
      92,    92,    92,     8,     8,     8,     8,    92,    92,    92,
       8,     8,    92,     7,   336,   337,   338,     3,     6,    76,
      78,    79,   120,   155,   339,   340,   341,   342,   344,   337,
     345,     4,   343,     3,     8,     4,    93,     4,   340,     5,
      92,     7,   346,   347,   348,     3,     6,    77,   349,   350,
     347,   351,     3,     8,     4,   350,    92
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,    96,    98,    97,    99,    97,   100,    97,   101,    97,
     102,    97,   103,    97,   104,    97,   105,    97,   106,    97,
     107,    97,   108,   108,   108,   108,   108,   108,   108,   109,
     111,   110,   112,   112,   113,   113,   115,   114,   117,   116,
     118,   118,   119,   119,   120,   122,   121,   123,   123,   124,
     124,   124,   124,   124,   126,   125,   128,   127,   129,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   132,   133,   134,   136,   135,   138,   137,   140,   139,
     142,   141,   144,   143,   145,   145,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   148,   147,   150,   149,   152,
     151,   154,   153,   156,   155,   157,   158,   159,   160,   162,
     161,   163,   163,   164,   164,   164,   164,   165,   166,   167,
     169,   168,   170,   170,   171,   171,   173,   172,   175,   174,
     176,   176,   176,   177,   177,   179,   178,   181,   180,   183,
     182,   184,   184,   185,   187,   186,   188,   188,   189,   189,
     191,   190,   193,   192,   194,   194,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   197,   196,   199,   198,   201,   200,   203,
     202,   205,   204,   207,   206,   209,   208,   210,   211,   213,
     212,   214,   214,   215,   215,   217,   216,   219,   218,   220,
     220,   221,   221,   222,   222,   222,   222,   222,   222,   222,
     222,   223,   224,   225,   226,   228,   227,   230,   229,   231,
     233,   232,   234,   236,   235,   237,   237,   238,   238,   240,
     239,   242,   241,   243,   243,   244,   244,   245,   245,   245,
     245,   245,   245,   246,   248,   247,   249,   250,   251,   253,
     252,   254,   254,   255,   255,   257,   256,   259,   258,   260,
     260,   261,   261,   261,   263,   262,   265,   264,   266,   266,
     267,   267,   269,   268,   271,   270,   272,   272,   273,   273,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   276,
     275,   278,   277,   280,   279,   282,   281,   284,   283,   286,
     285,   288,   287,   290,   289,   292,   291,   294,   293,   295,
     295,   296,   206,   297,   297,   298,   298,   299,   299,   299,
     299,   300,   302,   301,   304,   303,   305,   305,   306,   306,
     306,   306,   306,   306,   306,   307,   309,   308,   310,   311,
     312,   314,   313,   315,   315,   315,   317,   316,   318,   318,
     319,   319,   321,   320,   323,   322,   325,   324,   327,   326,
     329,   328,   331,   330,   332,   332,   333,   335,   334,   336,
     336,   338,   337,   339,   339,   340,   340,   340,   340,   340,
     341,   343,   342,   345,   344,   346,   346,   348,   347,   349,
     349,   351,   350
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     1,     3,     5,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     0,     6,     0,     4,     0,     4,
       0,     6,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     1,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"lease-database\"",
  "\"hosts-database\"", "\"type\"", "\"user\"", "\"password\"", "\"host\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"pools\"", "\"pool\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"server-id\"", "\"identifier\"",
  "\"htype\"", "\"time\"", "\"enterprise-id\"", "\"dhcp4o6-port\"",
  "\"version\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "value",
  "sub_json", "map2", "$@11", "map_content", "not_empty_map",
  "list_generic", "$@12", "list2", "$@13", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@14",
  "global_objects", "global_object", "dhcp4_object", "$@15", "sub_dhcp4",
  "$@16", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "interfaces_config", "$@17",
  "sub_interfaces4", "$@18", "interface_config_map", "$@19",
  "lease_database", "$@20", "hosts_database", "$@21",
  "database_map_params", "database_map_param", "type", "$@22", "user",
  "$@23", "password", "$@24", "host", "$@25", "name", "$@26", "persist",
  "lfc_interval", "readonly", "duid_id", "host_reservation_identifiers",
  "$@27", "host_reservation_identifiers_list",
  "host_reservation_identifier", "hw_address_id", "circuit_id",
  "client_id", "hooks_libraries", "$@28", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@29",
  "sub_hooks_library", "$@30", "hooks_params", "hooks_param", "library",
  "$@31", "parameters", "$@32", "expired_leases_processing", "$@33",
  "expired_leases_params", "expired_leases_param", "subnet4_list", "$@34",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@35",
  "sub_subnet4", "$@36", "subnet4_params", "subnet4_param", "subnet",
  "$@37", "subnet_4o6_interface", "$@38", "subnet_4o6_subnet", "$@39",
  "interface", "$@40", "interface_id", "$@41", "client_class", "$@42",
  "reservation_mode", "$@43", "id", "rapid_commit", "option_def_list",
  "$@44", "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@45", "sub_option_def", "$@46",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type",
  "option_def_record_types", "$@47", "space", "$@48", "option_def_space",
  "option_def_encapsulate", "$@49", "option_def_array", "option_data_list",
  "$@50", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@51", "sub_option_data", "$@52",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@53",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@54", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@55", "sub_pool4", "$@56", "pool_params",
  "pool_param", "pool_entry", "$@57", "reservations", "$@58",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@59", "sub_reservation", "$@60", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_address",
  "$@61", "duid", "$@62", "hw_address", "$@63", "client_id_value", "$@64",
  "circuit_id_value", "$@65", "hostname", "$@66",
  "reservation_client_classes", "$@67", "relay", "$@68", "relay_map",
  "$@69", "client_classes", "$@70", "client_classes_list", "$@71",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@72",
  "server_id", "$@73", "server_id_params", "server_id_param", "htype",
  "identifier", "$@74", "time", "enterprise_id", "dhcp4o6_port", "version",
  "$@75", "version_value", "control_socket", "$@76",
  "control_socket_params", "control_socket_param", "socket_type", "$@77",
  "socket_name", "$@78", "dhcp_ddns", "$@79", "dhcp6_json_object", "$@80",
  "dhcpddns_json_object", "$@81", "logging_object", "$@82",
  "logging_params", "logging_param", "loggers", "$@83", "loggers_entries",
  "logger_entry", "$@84", "logger_params", "logger_param", "debuglevel",
  "severity", "$@85", "output_options_list", "$@86",
  "output_options_list_content", "output_entry", "$@87", "output_params",
  "output_param", "$@88", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   192,   192,   192,   193,   193,   194,   194,   195,   195,
     196,   196,   197,   197,   198,   198,   199,   199,   200,   200,
     201,   201,   209,   210,   211,   212,   213,   214,   215,   218,
     223,   223,   235,   236,   239,   243,   250,   250,   258,   258,
     265,   266,   269,   273,   284,   294,   294,   306,   307,   311,
     312,   313,   314,   315,   318,   318,   335,   335,   343,   344,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     371,   376,   381,   386,   391,   391,   401,   401,   409,   409,
     419,   419,   429,   429,   439,   440,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   454,   454,   462,   462,   470,
     470,   478,   478,   486,   486,   494,   499,   504,   509,   514,
     514,   524,   525,   528,   529,   530,   531,   534,   539,   544,
     549,   549,   559,   560,   563,   564,   567,   567,   575,   575,
     583,   584,   585,   588,   589,   592,   592,   600,   600,   608,
     608,   618,   619,   625,   633,   633,   646,   647,   650,   651,
     658,   658,   681,   681,   690,   691,   695,   696,   697,   698,
     699,   700,   701,   702,   703,   704,   705,   706,   707,   708,
     709,   710,   711,   714,   714,   722,   722,   730,   730,   738,
     738,   746,   746,   754,   754,   762,   762,   770,   775,   784,
     784,   796,   797,   800,   801,   806,   806,   817,   817,   827,
     828,   831,   832,   835,   836,   837,   838,   839,   840,   841,
     842,   845,   847,   852,   854,   856,   856,   864,   864,   872,
     874,   874,   882,   891,   891,   903,   904,   909,   910,   915,
     915,   926,   926,   937,   938,   943,   944,   949,   950,   951,
     952,   953,   954,   957,   959,   959,   967,   969,   971,   979,
     979,   991,   992,   995,   996,   999,   999,  1007,  1007,  1015,
    1016,  1019,  1020,  1021,  1024,  1024,  1035,  1035,  1045,  1046,
    1049,  1050,  1053,  1053,  1061,  1061,  1069,  1070,  1073,  1074,
    1078,  1079,  1080,  1081,  1082,  1083,  1084,  1085,  1086,  1089,
    1089,  1095,  1095,  1103,  1103,  1111,  1111,  1119,  1119,  1128,
    1128,  1136,  1136,  1149,  1149,  1159,  1159,  1170,  1170,  1180,
    1181,  1184,  1184,  1192,  1193,  1196,  1197,  1200,  1201,  1202,
    1203,  1206,  1208,  1208,  1219,  1219,  1229,  1230,  1233,  1234,
    1235,  1236,  1237,  1238,  1239,  1242,  1247,  1247,  1255,  1260,
    1267,  1273,  1273,  1281,  1282,  1283,  1288,  1288,  1298,  1299,
    1302,  1303,  1306,  1306,  1314,  1314,  1324,  1324,  1336,  1336,
    1343,  1343,  1355,  1355,  1368,  1369,  1373,  1377,  1377,  1389,
    1390,  1394,  1394,  1402,  1403,  1406,  1407,  1408,  1409,  1410,
    1413,  1417,  1417,  1425,  1425,  1435,  1436,  1439,  1439,  1447,
    1448,  1451,  1451
  };

  // Print the state stack on the debug stream.
  void
  Dhcp4Parser::yystack_print_ ()
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 3397 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1459 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
