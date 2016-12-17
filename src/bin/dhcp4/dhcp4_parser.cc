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
      case 114: // value
      case 331: // version_value
        value.move< ElementPtr > (that.value);
        break;

      case 101: // "boolean"
        value.move< bool > (that.value);
        break;

      case 100: // "floating point"
        value.move< double > (that.value);
        break;

      case 99: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 98: // "constant string"
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
      case 114: // value
      case 331: // version_value
        value.copy< ElementPtr > (that.value);
        break;

      case 101: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 100: // "floating point"
        value.copy< double > (that.value);
        break;

      case 99: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 98: // "constant string"
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
            case 98: // "constant string"

#line 190 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 99: // "integer"

#line 190 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 100: // "floating point"

#line 190 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 101: // "boolean"

#line 190 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 114: // value

#line 190 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 331: // version_value

#line 190 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 114: // value
      case 331: // version_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 101: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 100: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 99: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 98: // "constant string"
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
#line 199 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 200 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 201 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 202 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 203 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 208 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 325 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 332 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }
    ctx.stack_.pop_back();
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1410 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1571 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 807 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 853 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1056 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1903 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 1957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 1975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 1993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2029 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1174 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1191 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("version", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 2300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 2306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2501 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2521 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2531 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2547 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2557 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2561 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -410;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     188,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,    29,    23,    30,    44,    55,    57,    77,    86,    92,
     113,   135,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,    23,   -32,    14,   134,   144,    20,     0,    27,
      91,    76,    -6,  -410,    33,   155,   156,   159,   174,  -410,
    -410,  -410,  -410,   175,  -410,    37,  -410,  -410,  -410,  -410,
    -410,  -410,   187,   190,  -410,  -410,  -410,   200,   212,   217,
     220,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,   221,
    -410,  -410,  -410,  -410,    47,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,   185,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,   227,   229,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,    72,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,    87,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,   207,   233,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,   234,  -410,
    -410,  -410,   235,  -410,  -410,  -410,   237,   238,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,   239,
    -410,  -410,  -410,  -410,   247,   243,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,   124,  -410,  -410,  -410,  -410,
      23,    23,  -410,   158,   253,   254,   258,   260,  -410,    14,
    -410,   262,   141,   167,   265,   266,   282,   191,   192,   194,
     195,   283,   284,   285,   288,   291,   292,   293,   294,   205,
     295,   297,   298,   134,  -410,   299,  -410,    42,   301,   302,
     303,   304,   305,   306,   307,   213,   215,   309,   310,   311,
     313,    20,  -410,   314,     0,  -410,   315,   316,   317,   318,
     319,   320,   321,   322,   323,  -410,    27,   324,   325,   231,
     327,   328,   329,   236,  -410,    91,   330,   240,  -410,    76,
     331,   332,     7,  -410,  -410,  -410,   336,   335,   337,    23,
      23,  -410,   338,  -410,  -410,   245,   339,   340,  -410,  -410,
    -410,  -410,   343,   344,   345,   346,   347,   348,   351,   352,
    -410,   129,   353,   356,  -410,   349,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,   357,   361,  -410,  -410,  -410,   257,   268,
     269,   363,   271,   273,   274,  -410,  -410,   275,   276,   370,
     371,  -410,   279,  -410,   281,   286,   349,   287,   289,   296,
     300,   308,   312,  -410,   326,   333,  -410,   334,   341,   342,
    -410,  -410,   350,  -410,  -410,   354,    23,  -410,    23,   134,
     355,  -410,  -410,   144,  -410,    82,    82,   373,   375,   376,
      78,    26,   379,   358,   202,  -410,  -410,  -410,  -410,    32,
     -32,  -410,  -410,   385,  -410,    42,  -410,  -410,  -410,   383,
    -410,  -410,  -410,  -410,  -410,   384,   359,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,   143,  -410,   147,  -410,
    -410,   387,  -410,  -410,  -410,   389,   392,   393,  -410,   151,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,   163,
    -410,   394,   396,  -410,  -410,   395,   399,  -410,  -410,   397,
     401,  -410,  -410,  -410,  -410,  -410,  -410,    35,  -410,  -410,
    -410,  -410,  -410,   123,  -410,   402,   404,  -410,   405,   165,
    -410,  -410,   407,   408,   409,  -410,  -410,  -410,   178,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,   182,  -410,  -410,  -410,
     189,    23,   360,  -410,  -410,   410,   411,  -410,  -410,   412,
     416,  -410,  -410,   413,  -410,   418,   355,  -410,  -410,   421,
     422,   423,   362,   365,   364,    82,  -410,  -410,    20,  -410,
     373,    91,  -410,   375,    76,  -410,   376,    78,  -410,    26,
    -410,    -6,  -410,   379,   367,   358,  -410,   424,   368,   369,
     372,   202,  -410,   425,   426,    32,  -410,  -410,   414,  -410,
       0,  -410,   383,    27,  -410,   384,   429,  -410,   400,  -410,
     374,   377,   378,  -410,  -410,  -410,  -410,   193,  -410,   427,
    -410,   430,  -410,  -410,  -410,   197,  -410,  -410,  -410,   380,
    -410,  -410,  -410,  -410,   381,   382,  -410,  -410,   203,  -410,
     433,  -410,   386,   435,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,   172,  -410,
      59,   435,  -410,  -410,   439,  -410,  -410,  -410,   204,  -410,
    -410,  -410,  -410,  -410,   440,   388,   441,    59,  -410,   432,
    -410,   390,  -410,   442,  -410,  -410,   214,  -410,   391,   442,
    -410,  -410,   211,  -410,  -410,   443,   391,  -410,   398,  -410,
    -410
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    91,     9,
     167,    11,   277,    13,   294,    15,   217,    17,   251,    19,
     143,    21,    40,    32,     0,     0,     0,     0,     0,   296,
     219,   253,     0,    42,     0,    41,     0,     0,    33,    54,
     394,   390,   392,     0,    53,     0,    47,    49,    51,    52,
      50,    89,     0,     0,   312,    95,    97,     0,     0,     0,
       0,   159,   209,   243,   124,   336,   135,   154,   356,     0,
     373,   378,   388,    82,     0,    58,    60,    61,    62,    63,
      79,    80,    65,    66,    67,    68,    72,    73,    64,    70,
      71,    81,    69,    74,    75,    76,    77,    78,    93,     0,
     340,   193,   195,   197,   269,   191,   199,   201,     0,     0,
     205,   203,   286,   332,   190,   171,   172,   173,   185,     0,
     169,   176,   187,   188,   189,   177,   178,   181,   183,   179,
     180,   174,   175,   182,   186,   184,   284,   283,   282,     0,
     279,   281,   314,   316,   330,   320,   322,   326,   324,   328,
     318,   311,   307,     0,   297,   298,   308,   309,   310,   304,
     300,   305,   302,   303,   306,   301,   110,   118,     0,   237,
     235,   240,     0,   230,   234,   231,     0,   220,   221,   223,
     233,   224,   225,   226,   239,   227,   228,   229,   264,     0,
     262,   263,   266,   267,     0,   254,   255,   257,   258,   259,
     260,   261,   150,   152,   147,     0,   145,   148,   149,    37,
       0,     0,    31,     0,     0,     0,     0,     0,    44,     0,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,     0,    92,   342,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,     0,     0,   278,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   295,     0,     0,     0,     0,
       0,     0,     0,     0,   218,     0,     0,     0,   252,     0,
       0,     0,     0,   144,    43,    34,     0,     0,     0,     0,
       0,    48,     0,    87,    88,     0,     0,     0,    83,    84,
      85,    86,     0,     0,     0,     0,     0,     0,     0,     0,
     372,     0,     0,     0,    59,     0,   354,   352,   353,   348,
     349,   350,   351,     0,   343,   344,   346,   347,     0,     0,
       0,     0,     0,     0,     0,   207,   208,     0,     0,     0,
       0,   170,     0,   280,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   299,     0,     0,   232,     0,     0,     0,
     242,   222,     0,   268,   256,     0,     0,   146,     0,     0,
       0,   391,   393,     0,   313,     0,     0,   161,   211,   245,
       0,     0,   137,     0,     0,   377,   375,   376,   374,     0,
       0,    38,    94,     0,   341,     0,   194,   196,   198,   271,
     192,   200,   202,   206,   204,   288,     0,   285,   315,   317,
     331,   321,   323,   327,   325,   329,   319,   111,   119,   238,
     236,   241,   265,   151,   153,    35,     0,   399,     0,   396,
     398,     0,   112,   114,   116,     0,     0,     0,   109,     0,
      99,   101,   102,   103,   104,   105,   106,   107,   108,     0,
     165,     0,   162,   163,   215,     0,   212,   213,   249,     0,
     246,   247,   123,   132,   133,   134,   128,     0,   126,   129,
     130,   131,   338,     0,   141,     0,   138,   139,     0,     0,
     156,   368,     0,     0,     0,   366,   360,   365,     0,   358,
     363,   361,   362,   364,   384,   386,     0,   380,   382,   383,
       0,    40,     0,   345,   275,     0,   272,   273,   292,     0,
     289,   290,   334,     0,    55,     0,     0,   395,    90,     0,
       0,     0,     0,     0,     0,     0,    96,    98,     0,   160,
       0,   219,   210,     0,   253,   244,     0,     0,   125,     0,
     337,     0,   136,     0,     0,     0,   155,     0,     0,     0,
       0,     0,   357,     0,     0,     0,   379,   389,     0,   355,
       0,   270,     0,   296,   287,     0,     0,   333,     0,   397,
       0,     0,     0,   120,   121,   122,   100,     0,   164,     0,
     214,     0,   248,   127,   339,     0,   140,   158,   157,     0,
     367,   370,   371,   359,     0,     0,   381,    39,     0,   274,
       0,   291,     0,     0,   113,   115,   117,   166,   216,   250,
     142,   369,   385,   387,   276,   293,   335,   403,     0,   401,
       0,     0,   400,   415,     0,   413,   411,   407,     0,   405,
     409,   410,   408,   402,     0,     0,     0,     0,   404,     0,
     412,     0,   406,     0,   414,   419,     0,   417,     0,     0,
     416,   423,     0,   421,   418,     0,     0,   420,     0,   422,
     424
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,     9,  -410,  -410,  -410,  -410,     4,  -410,  -410,
      60,  -410,   -91,  -410,   -54,  -410,  -410,  -410,   206,  -410,
    -410,  -410,  -410,    45,   180,   -56,   -40,   -38,  -410,  -410,
     -37,  -410,  -410,  -410,  -410,    38,  -410,  -410,  -410,  -410,
    -410,    41,  -106,  -393,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,   -59,  -410,  -409,  -410,  -410,  -410,  -410,  -410,  -410,
    -117,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -122,  -410,
    -410,  -410,  -119,   148,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -116,  -410,  -410,  -410,  -410,   -97,  -410,  -410,  -410,
     -87,   186,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -403,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,   -90,  -410,  -410,  -410,   -89,  -410,
     170,  -410,   -52,  -410,  -410,  -410,  -410,   -48,  -410,  -410,
    -410,  -410,  -410,   -47,  -410,  -410,  -410,   -86,  -410,  -410,
    -410,   -88,  -410,   173,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -113,  -410,  -410,  -410,  -109,   199,
    -410,  -410,  -410,  -410,  -410,  -410,  -111,  -410,  -410,  -410,
    -108,  -410,   196,   -43,  -410,  -252,  -410,  -251,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,    62,  -410,  -410,  -410,  -410,  -410,  -410,
     -93,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,   -96,  -410,  -410,  -410,  -410,  -410,  -410,
    -410,  -410,  -410,  -410,  -410,  -410,  -410,   -55,  -410,  -410,
    -410,  -161,  -410,  -410,  -174,  -410,  -410,  -410,  -410,  -410,
    -410,  -185,  -410,  -410,  -191,  -410
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,    67,    68,    33,    52,
     432,   541,    64,    65,   103,    35,    54,    75,    76,    77,
     244,    37,    55,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   251,    39,    56,   129,   275,   113,   255,   114,
     256,   479,   480,   204,   307,   482,   559,   483,   560,   484,
     561,   205,   308,   486,   487,   488,   506,   115,   264,   507,
     508,   509,   510,   511,   116,   266,   515,   516,   517,   581,
      51,    62,   235,   236,   237,   320,   238,   321,   117,   267,
     519,   520,   118,   261,   491,   492,   493,   568,    41,    57,
     149,   150,   151,   282,   152,   278,   153,   279,   154,   280,
     155,   283,   156,   284,   157,   288,   158,   287,   159,   160,
     119,   262,   495,   496,   497,   571,    47,    60,   206,   207,
     208,   209,   210,   211,   212,   213,   311,   214,   310,   215,
     216,   312,   217,   120,   263,   499,   500,   501,   574,    49,
      61,   224,   225,   226,   227,   228,   316,   229,   230,   231,
     162,   281,   545,   546,   547,   600,    43,    58,   169,   170,
     171,   293,   163,   289,   549,   550,   551,   603,    45,    59,
     183,   184,   185,   121,   254,   187,   296,   188,   297,   189,
     304,   190,   299,   191,   300,   192,   302,   193,   301,   194,
     303,   195,   298,   165,   290,   553,   606,   122,   265,   513,
     277,   363,   364,   365,   366,   367,   433,   123,   268,   528,
     529,   530,   531,   587,   532,   533,   124,   125,   270,   428,
     126,   271,   536,   537,   538,   593,   539,   594,   127,   272,
      78,   246,    79,   247,    80,   245,   468,   469,   470,   555,
     658,   659,   660,   668,   669,   670,   671,   676,   672,   674,
     686,   687,   688,   692,   693,   695
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   145,   221,   144,   167,   181,   203,   220,   234,   222,
     161,   168,   182,   223,   164,   527,   186,   146,   512,   147,
     148,    30,   481,   481,    69,   361,   362,   130,    23,    22,
      24,   526,    25,   130,    83,    84,    93,    34,   577,   239,
     249,   578,    84,   172,   173,   250,   166,    87,    88,    89,
     273,    36,   131,   132,   133,   274,    93,    84,   172,   173,
     232,   233,    38,    93,    40,   134,    66,   135,   136,   137,
     138,   139,   140,   232,   233,   291,   141,   142,    93,   197,
     292,   174,   141,   143,    42,   175,   176,   177,   178,   179,
     294,   180,    73,    44,    70,   295,   197,   356,    73,    46,
      71,    72,   196,   472,   473,   474,   475,   476,   477,   534,
     535,   196,    73,   197,   218,   198,   199,   219,    73,   197,
      48,    26,    27,    28,    29,    73,   579,   322,   197,   580,
     198,   199,   323,   200,   201,   202,   502,   503,   504,   505,
      73,   663,    50,   664,   665,    81,   273,    82,    83,    84,
     556,   554,    85,    86,   565,   557,   128,    73,   240,   566,
     241,    87,    88,    89,    90,    91,   565,   242,   585,    92,
      93,   567,   481,   586,    73,   661,   624,   243,   662,   248,
      73,   591,   527,   361,   362,   595,   592,    94,    95,    73,
     596,   252,   243,   276,   253,    74,   291,   597,   526,    96,
     322,   647,    97,    98,   257,   650,   294,   677,    99,   100,
     101,   654,   678,   102,   696,   305,   258,   689,   358,   697,
     690,   259,   196,   357,   260,   269,   475,   425,   426,   427,
     359,   285,    73,   286,   360,   145,   306,   144,   309,   313,
     167,   315,   333,   317,   161,   314,   319,   168,   164,   324,
     325,   146,   181,   147,   148,   318,   326,   327,   328,   182,
     221,   203,   329,   186,   330,   220,   332,   222,   334,   335,
     336,   223,   521,   522,   523,   524,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,   337,   342,   343,   344,
     338,   339,   345,   340,   341,   346,   347,   348,   349,   351,
      73,   352,   353,   355,   350,   368,   369,   370,   371,   372,
     373,   374,   375,   377,   378,   379,   376,   380,   382,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   394,   395,
     396,   397,   398,   399,   402,   405,   406,   400,   411,   412,
     408,   403,   409,   414,   410,   413,   415,   416,   417,   418,
     419,   420,   421,   422,   431,   436,   485,   485,   423,   424,
     429,   478,   478,   430,   435,   434,   437,   438,   439,   440,
     525,   441,   442,   443,   444,   445,   358,   447,   446,   448,
     490,   357,   494,   498,   449,   451,   514,   452,   359,   542,
     544,   548,   360,   562,   453,   558,   563,   564,   454,   570,
     569,   572,   573,   575,   576,   643,   455,   583,   582,   584,
     456,   588,   589,   590,   602,   464,   601,   465,   604,   605,
     637,   607,   608,   552,   457,   610,   611,   612,   629,   634,
     635,   458,   459,   642,   540,   648,   467,   683,   649,   460,
     461,   655,   657,   675,   679,   681,   450,   698,   462,   685,
     598,   471,   463,   354,   466,   331,   518,   489,   599,   616,
     623,   626,   625,   613,   614,   615,   627,   630,   631,   628,
     407,   632,   644,   618,   691,   645,   646,   381,   651,   652,
     653,   617,   619,   620,   656,   401,   621,   680,   684,   639,
     622,   638,   404,   383,   641,   640,   700,   543,   633,   636,
     673,   609,   393,   682,   694,   699,   485,     0,     0,     0,
       0,   478,   145,     0,   144,   221,     0,   203,     0,     0,
     220,   161,   222,     0,     0,   164,   223,   234,   146,     0,
     147,   148,     0,     0,     0,     0,     0,   525,     0,     0,
       0,     0,     0,     0,     0,     0,   167,     0,     0,   181,
       0,     0,     0,   168,     0,     0,   182,     0,     0,     0,
     186,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   667,     0,     0,     0,     0,   666,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   667,     0,
       0,     0,     0,   666
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,   424,    59,    57,   421,    57,
      57,    12,   415,   416,    10,   277,   277,     7,     5,     0,
       7,   424,     9,     7,    14,    15,    36,     7,     3,     6,
       3,     6,    15,    16,    17,     8,    46,    27,    28,    29,
       3,     7,    32,    33,    34,     8,    36,    15,    16,    17,
      66,    67,     7,    36,     7,    45,    98,    47,    48,    49,
      50,    51,    52,    66,    67,     3,    56,    57,    36,    37,
       8,    54,    56,    63,     7,    58,    59,    60,    61,    62,
       3,    64,    98,     7,    80,     8,    37,    55,    98,     7,
      86,    87,    20,    21,    22,    23,    24,    25,    26,    77,
      78,    20,    98,    37,    38,    39,    40,    41,    98,    37,
       7,    98,    99,   100,   101,    98,     3,     3,    37,     6,
      39,    40,     8,    42,    43,    44,    58,    59,    60,    61,
      98,    82,     7,    84,    85,    11,     3,    13,    14,    15,
       3,     8,    18,    19,     3,     8,    12,    98,     3,     8,
       4,    27,    28,    29,    30,    31,     3,     8,     3,    35,
      36,     8,   565,     8,    98,     3,   579,     3,     6,     4,
      98,     3,   591,   435,   435,     3,     8,    53,    54,    98,
       8,     4,     3,     8,     4,   249,     3,     8,   591,    65,
       3,     8,    68,    69,     4,     8,     3,     3,    74,    75,
      76,     8,     8,    79,     3,     8,     4,     3,   277,     8,
       6,     4,    20,   277,     4,     4,    24,    98,    99,   100,
     277,     4,    98,     4,   277,   291,     3,   291,     4,     4,
     294,     3,   101,     4,   291,     8,     3,   294,   291,   240,
     241,   291,   306,   291,   291,     8,    98,     4,     4,   306,
     319,   315,     4,   306,     4,   319,     4,   319,   101,     4,
       4,   319,    70,    71,    72,    73,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,     4,     4,     4,     4,
      99,    99,     4,    99,    99,     4,     4,     4,     4,     4,
      98,     4,     4,     4,    99,     4,     4,     4,     4,     4,
       4,     4,    99,     4,     4,     4,   101,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
      99,     4,     4,     4,     4,     4,     4,   101,   329,   330,
       4,   101,     7,    98,     7,     7,     7,     7,     5,     5,
       5,     5,     5,     5,     5,    98,   415,   416,     7,     7,
       7,   415,   416,     7,     3,     8,    98,    98,     5,    98,
     424,    98,    98,    98,    98,     5,   435,    98,     7,    98,
       7,   435,     7,     7,    98,    98,     7,    98,   435,     4,
       7,     7,   435,     4,    98,     8,     4,     4,    98,     3,
       6,     6,     3,     6,     3,     5,    98,     3,     6,     4,
      98,     4,     4,     4,     3,   406,     6,   408,     6,     3,
       6,     8,     4,    64,    98,     4,     4,     4,     4,     4,
       4,    98,    98,     4,   430,     8,    81,     5,     8,    98,
      98,     8,     7,     4,     4,     4,   386,     4,    98,     7,
     541,   413,    98,   273,   409,   249,    98,   416,    98,   565,
     577,   583,   581,   101,    99,   101,    99,    99,    99,   585,
     322,    99,    98,   570,    83,    98,    98,   291,    98,    98,
      98,   568,   571,   573,    98,   315,   574,    99,    98,   602,
     576,   600,   319,   294,   605,   603,    98,   435,   591,   595,
     661,   556,   306,   677,   689,   696,   565,    -1,    -1,    -1,
      -1,   565,   568,    -1,   568,   574,    -1,   571,    -1,    -1,
     574,   568,   574,    -1,    -1,   568,   574,   581,   568,    -1,
     568,   568,    -1,    -1,    -1,    -1,    -1,   591,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   600,    -1,    -1,   603,
      -1,    -1,    -1,   600,    -1,    -1,   603,    -1,    -1,    -1,
     603,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   660,    -1,    -1,    -1,    -1,   660,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   677,    -1,
      -1,    -1,    -1,   677
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     0,     5,     7,     9,    98,    99,   100,   101,
     114,   115,   116,   120,     7,   127,     7,   133,     7,   145,
       7,   200,     7,   268,     7,   280,     7,   228,     7,   251,
       7,   182,   121,   117,   128,   134,   146,   201,   269,   281,
     229,   252,   183,   114,   124,   125,    98,   118,   119,    10,
      80,    86,    87,    98,   126,   129,   130,   131,   342,   344,
     346,    11,    13,    14,    15,    18,    19,    27,    28,    29,
      30,    31,    35,    36,    53,    54,    65,    68,    69,    74,
      75,    76,    79,   126,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   149,   151,   169,   176,   190,   194,   222,
     245,   285,   309,   319,   328,   329,   332,   340,    12,   147,
       7,    32,    33,    34,    45,    47,    48,    49,    50,    51,
      52,    56,    57,    63,   126,   137,   138,   139,   142,   202,
     203,   204,   206,   208,   210,   212,   214,   216,   218,   220,
     221,   245,   262,   274,   285,   305,    46,   126,   245,   270,
     271,   272,    16,    17,    54,    58,    59,    60,    61,    62,
      64,   126,   245,   282,   283,   284,   285,   287,   289,   291,
     293,   295,   297,   299,   301,   303,    20,    37,    39,    40,
      42,    43,    44,   126,   155,   163,   230,   231,   232,   233,
     234,   235,   236,   237,   239,   241,   242,   244,    38,    41,
     126,   163,   234,   239,   253,   254,   255,   256,   257,   259,
     260,   261,    66,    67,   126,   184,   185,   186,   188,     6,
       3,     4,     8,     3,   132,   347,   343,   345,     4,     3,
       8,   144,     4,     4,   286,   150,   152,     4,     4,     4,
       4,   195,   223,   246,   170,   310,   177,   191,   320,     4,
     330,   333,   341,     3,     8,   148,     8,   312,   207,   209,
     211,   263,   205,   213,   215,     4,     4,   219,   217,   275,
     306,     3,     8,   273,     3,     8,   288,   290,   304,   294,
     296,   300,   298,   302,   292,     8,     3,   156,   164,     4,
     240,   238,   243,     4,     8,     3,   258,     4,     8,     3,
     187,   189,     3,     8,   114,   114,    98,     4,     4,     4,
       4,   130,     4,   101,   101,     4,     4,     4,    99,    99,
      99,    99,     4,     4,     4,     4,     4,     4,     4,     4,
      99,     4,     4,     4,   136,     4,    55,   126,   163,   245,
     285,   287,   289,   313,   314,   315,   316,   317,     4,     4,
       4,     4,     4,     4,     4,    99,   101,     4,     4,     4,
       4,   203,     4,   271,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   284,     4,     4,    99,     4,     4,     4,
     101,   232,     4,   101,   255,     4,     4,   185,     4,     7,
       7,   114,   114,     7,    98,     7,     7,     5,     5,     5,
       5,     5,     5,     7,     7,    98,    99,   100,   331,     7,
       7,     5,   122,   318,     8,     3,    98,    98,    98,     5,
      98,    98,    98,    98,    98,     5,     7,    98,    98,    98,
     122,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,   114,   114,   135,    81,   348,   349,
     350,   147,    21,    22,    23,    24,    25,    26,   126,   153,
     154,   155,   157,   159,   161,   163,   165,   166,   167,   153,
       7,   196,   197,   198,     7,   224,   225,   226,     7,   247,
     248,   249,    58,    59,    60,    61,   168,   171,   172,   173,
     174,   175,   216,   311,     7,   178,   179,   180,    98,   192,
     193,    70,    71,    72,    73,   126,   155,   165,   321,   322,
     323,   324,   326,   327,    77,    78,   334,   335,   336,   338,
     119,   123,     4,   315,     7,   264,   265,   266,     7,   276,
     277,   278,    64,   307,     8,   351,     3,     8,     8,   158,
     160,   162,     4,     4,     4,     3,     8,     8,   199,     6,
       3,   227,     6,     3,   250,     6,     3,     3,     6,     3,
       6,   181,     6,     3,     4,     3,     8,   325,     4,     4,
       4,     3,     8,   337,   339,     3,     8,     8,   124,    98,
     267,     6,     3,   279,     6,     3,   308,     8,     4,   349,
       4,     4,     4,   101,    99,   101,   154,   202,   198,   230,
     226,   253,   249,   172,   216,   184,   180,    99,   193,     4,
      99,    99,    99,   322,     4,     4,   335,     6,   270,   266,
     282,   278,     4,     5,    98,    98,    98,     8,     8,     8,
       8,    98,    98,    98,     8,     8,    98,     7,   352,   353,
     354,     3,     6,    82,    84,    85,   126,   163,   355,   356,
     357,   358,   360,   353,   361,     4,   359,     3,     8,     4,
      99,     4,   356,     5,    98,     7,   362,   363,   364,     3,
       6,    83,   365,   366,   363,   367,     3,     8,     4,   366,
      98
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   102,   104,   103,   105,   103,   106,   103,   107,   103,
     108,   103,   109,   103,   110,   103,   111,   103,   112,   103,
     113,   103,   114,   114,   114,   114,   114,   114,   114,   115,
     117,   116,   118,   118,   119,   119,   121,   120,   123,   122,
     124,   124,   125,   125,   126,   128,   127,   129,   129,   130,
     130,   130,   130,   130,   132,   131,   134,   133,   135,   135,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   138,   139,   140,   141,   142,   144,
     143,   146,   145,   148,   147,   150,   149,   152,   151,   153,
     153,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     156,   155,   158,   157,   160,   159,   162,   161,   164,   163,
     165,   166,   167,   168,   170,   169,   171,   171,   172,   172,
     172,   172,   173,   174,   175,   177,   176,   178,   178,   179,
     179,   181,   180,   183,   182,   184,   184,   184,   185,   185,
     187,   186,   189,   188,   191,   190,   192,   192,   193,   195,
     194,   196,   196,   197,   197,   199,   198,   201,   200,   202,
     202,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   205,   204,   207,   206,   209,   208,   211,   210,   213,
     212,   215,   214,   217,   216,   219,   218,   220,   221,   223,
     222,   224,   224,   225,   225,   227,   226,   229,   228,   230,
     230,   231,   231,   232,   232,   232,   232,   232,   232,   232,
     232,   233,   234,   235,   236,   238,   237,   240,   239,   241,
     243,   242,   244,   246,   245,   247,   247,   248,   248,   250,
     249,   252,   251,   253,   253,   254,   254,   255,   255,   255,
     255,   255,   255,   256,   258,   257,   259,   260,   261,   263,
     262,   264,   264,   265,   265,   267,   266,   269,   268,   270,
     270,   271,   271,   271,   273,   272,   275,   274,   276,   276,
     277,   277,   279,   278,   281,   280,   282,   282,   283,   283,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   286,   285,   288,   287,   290,   289,   292,   291,
     294,   293,   296,   295,   298,   297,   300,   299,   302,   301,
     304,   303,   306,   305,   308,   307,   310,   309,   311,   311,
     312,   216,   313,   313,   314,   314,   315,   315,   315,   315,
     315,   315,   315,   316,   318,   317,   320,   319,   321,   321,
     322,   322,   322,   322,   322,   322,   322,   323,   325,   324,
     326,   327,   328,   330,   329,   331,   331,   331,   333,   332,
     334,   334,   335,   335,   337,   336,   339,   338,   341,   340,
     343,   342,   345,   344,   347,   346,   348,   348,   349,   351,
     350,   352,   352,   354,   353,   355,   355,   356,   356,   356,
     356,   356,   357,   359,   358,   361,   360,   362,   362,   364,
     363,   365,   365,   367,   366
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
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     4,     0,     4,     0,     6,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"type\"", "\"user\"", "\"password\"", "\"host\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"subnet\"", "\"interface\"", "\"interface-id\"", "\"id\"",
  "\"rapid-commit\"", "\"reservation-mode\"",
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
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@17", "sub_interfaces4",
  "$@18", "interface_config_map", "$@19", "lease_database", "$@20",
  "hosts_database", "$@21", "database_map_params", "database_map_param",
  "type", "$@22", "user", "$@23", "password", "$@24", "host", "$@25",
  "name", "$@26", "persist", "lfc_interval", "readonly", "duid_id",
  "host_reservation_identifiers", "$@27",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "circuit_id", "client_id", "hooks_libraries", "$@28",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@29", "sub_hooks_library", "$@30", "hooks_params",
  "hooks_param", "library", "$@31", "parameters", "$@32",
  "expired_leases_processing", "$@33", "expired_leases_params",
  "expired_leases_param", "subnet4_list", "$@34", "subnet4_list_content",
  "not_empty_subnet4_list", "subnet4", "$@35", "sub_subnet4", "$@36",
  "subnet4_params", "subnet4_param", "subnet", "$@37",
  "subnet_4o6_interface", "$@38", "subnet_4o6_interface_id", "$@39",
  "subnet_4o6_subnet", "$@40", "interface", "$@41", "interface_id", "$@42",
  "client_class", "$@43", "reservation_mode", "$@44", "id", "rapid_commit",
  "option_def_list", "$@45", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@46",
  "sub_option_def", "$@47", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "option_def_record_types",
  "$@48", "space", "$@49", "option_def_space", "option_def_encapsulate",
  "$@50", "option_def_array", "option_data_list", "$@51",
  "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@52", "sub_option_data", "$@53",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@54",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@55", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@56", "sub_pool4", "$@57", "pool_params",
  "pool_param", "pool_entry", "$@58", "reservations", "$@59",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@60", "sub_reservation", "$@61", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@62", "server_hostname", "$@63", "boot_file_name", "$@64",
  "ip_address", "$@65", "duid", "$@66", "hw_address", "$@67",
  "client_id_value", "$@68", "circuit_id_value", "$@69", "hostname",
  "$@70", "reservation_client_classes", "$@71", "relay", "$@72",
  "relay_map", "$@73", "client_classes", "$@74", "client_classes_list",
  "$@75", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@76",
  "server_id", "$@77", "server_id_params", "server_id_param", "htype",
  "identifier", "$@78", "time", "enterprise_id", "dhcp4o6_port", "version",
  "$@79", "version_value", "control_socket", "$@80",
  "control_socket_params", "control_socket_param", "socket_type", "$@81",
  "socket_name", "$@82", "dhcp_ddns", "$@83", "dhcp6_json_object", "$@84",
  "dhcpddns_json_object", "$@85", "logging_object", "$@86",
  "logging_params", "logging_param", "loggers", "$@87", "loggers_entries",
  "logger_entry", "$@88", "logger_params", "logger_param", "debuglevel",
  "severity", "$@89", "output_options_list", "$@90",
  "output_options_list_content", "output_entry", "$@91", "output_params",
  "output_param", "$@92", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   199,   199,   199,   200,   200,   201,   201,   202,   202,
     203,   203,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   216,   217,   218,   219,   220,   221,   222,   225,
     230,   230,   242,   243,   246,   250,   257,   257,   265,   265,
     272,   273,   276,   280,   291,   301,   301,   313,   314,   318,
     319,   320,   321,   322,   325,   325,   342,   342,   350,   351,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   381,   386,   391,   396,   401,   406,   412,
     412,   422,   422,   430,   430,   440,   440,   450,   450,   460,
     461,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     475,   475,   483,   483,   491,   491,   499,   499,   507,   507,
     515,   520,   525,   530,   535,   535,   545,   546,   549,   550,
     551,   552,   555,   560,   565,   570,   570,   580,   581,   584,
     585,   588,   588,   596,   596,   604,   605,   606,   609,   610,
     613,   613,   621,   621,   629,   629,   639,   640,   646,   654,
     654,   667,   668,   671,   672,   679,   679,   702,   702,   711,
     712,   716,   717,   718,   719,   720,   721,   722,   723,   724,
     725,   726,   727,   728,   729,   730,   731,   732,   733,   734,
     735,   738,   738,   746,   746,   754,   754,   762,   762,   770,
     770,   778,   778,   786,   786,   794,   794,   802,   807,   816,
     816,   828,   829,   832,   833,   838,   838,   849,   849,   859,
     860,   863,   864,   867,   868,   869,   870,   871,   872,   873,
     874,   877,   879,   884,   886,   888,   888,   896,   896,   904,
     906,   906,   914,   923,   923,   935,   936,   941,   942,   947,
     947,   958,   958,   969,   970,   975,   976,   981,   982,   983,
     984,   985,   986,   989,   991,   991,   999,  1001,  1003,  1011,
    1011,  1023,  1024,  1027,  1028,  1031,  1031,  1039,  1039,  1047,
    1048,  1051,  1052,  1053,  1056,  1056,  1067,  1067,  1077,  1078,
    1081,  1082,  1085,  1085,  1093,  1093,  1101,  1102,  1105,  1106,
    1110,  1111,  1112,  1113,  1114,  1115,  1116,  1117,  1118,  1119,
    1120,  1121,  1124,  1124,  1132,  1132,  1140,  1140,  1148,  1148,
    1156,  1156,  1164,  1164,  1172,  1172,  1180,  1180,  1189,  1189,
    1197,  1197,  1210,  1210,  1220,  1220,  1231,  1231,  1241,  1242,
    1245,  1245,  1253,  1254,  1257,  1258,  1261,  1262,  1263,  1264,
    1265,  1266,  1267,  1270,  1272,  1272,  1283,  1283,  1293,  1294,
    1297,  1298,  1299,  1300,  1301,  1302,  1303,  1306,  1311,  1311,
    1319,  1324,  1331,  1337,  1337,  1345,  1346,  1347,  1352,  1352,
    1362,  1363,  1366,  1367,  1370,  1370,  1378,  1378,  1388,  1388,
    1400,  1400,  1407,  1407,  1419,  1419,  1432,  1433,  1437,  1441,
    1441,  1453,  1454,  1458,  1458,  1466,  1467,  1470,  1471,  1472,
    1473,  1474,  1477,  1481,  1481,  1489,  1489,  1499,  1500,  1503,
    1503,  1511,  1512,  1515,  1515
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
#line 3523 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1523 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
