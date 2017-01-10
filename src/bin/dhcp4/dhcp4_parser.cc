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
      case 122: // value
      case 161: // socket_type
        value.move< ElementPtr > (that.value);
        break;

      case 109: // "boolean"
        value.move< bool > (that.value);
        break;

      case 108: // "floating point"
        value.move< double > (that.value);
        break;

      case 107: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 106: // "constant string"
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
      case 122: // value
      case 161: // socket_type
        value.copy< ElementPtr > (that.value);
        break;

      case 109: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 108: // "floating point"
        value.copy< double > (that.value);
        break;

      case 107: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 106: // "constant string"
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
            case 106: // "constant string"

#line 198 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 107: // "integer"

#line 198 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 108: // "floating point"

#line 198 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 109: // "boolean"

#line 198 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 122: // value

#line 198 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 161: // socket_type

#line 198 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 122: // value
      case 161: // socket_type
        yylhs.value.build< ElementPtr > ();
        break;

      case 109: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 108: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 107: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 106: // "constant string"
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
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 208 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 209 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 210 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 211 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 212 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 213 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 214 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 340 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 970 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1903 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1950 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1214 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2129 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2336 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2345 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2365 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2475 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2596 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -411;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     179,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    39,    22,    34,    54,    61,    94,   113,   155,   173,
     209,   218,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,    22,   -29,    18,    65,   106,    19,    -6,    96,
      17,    67,   -17,  -411,   170,   175,   192,   199,   224,  -411,
    -411,  -411,  -411,   226,  -411,    72,  -411,  -411,  -411,  -411,
    -411,  -411,   227,   228,  -411,  -411,  -411,   230,   231,   232,
     235,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   237,
    -411,  -411,  -411,   131,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   134,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     238,   240,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   142,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   143,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,   241,   245,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     248,  -411,  -411,  -411,   249,  -411,  -411,  -411,   257,   266,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   267,  -411,  -411,  -411,  -411,   264,   270,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   167,  -411,  -411,
    -411,  -411,    22,    22,  -411,   180,   281,   283,   284,   285,
    -411,    18,  -411,   286,   182,   183,   289,   290,   291,   193,
     194,   195,   196,   292,   293,   294,   295,   300,   301,   302,
     303,   204,   304,   305,    65,  -411,   306,   308,   106,  -411,
      26,   309,   310,   311,   312,   313,   314,   315,   213,   215,
     317,   318,   319,   321,    19,  -411,   322,    -6,  -411,   323,
     324,   325,   326,   327,   328,   329,   330,   333,  -411,    96,
     334,   335,   233,   337,   338,   339,   236,  -411,    17,   340,
     239,  -411,    67,   342,   343,   -22,  -411,  -411,  -411,   345,
     344,   346,    22,    22,  -411,   347,  -411,  -411,   244,   348,
     349,  -411,  -411,  -411,  -411,   352,   353,   354,   357,   358,
     359,   360,   361,  -411,   362,   363,  -411,   366,   112,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   364,   370,  -411,
    -411,  -411,   246,   269,   271,   371,   272,   274,   275,  -411,
    -411,   276,   277,   380,   379,  -411,   282,  -411,   287,   288,
     366,   296,   297,   298,   299,   316,   320,  -411,   331,   332,
    -411,   336,   341,   350,  -411,  -411,   351,  -411,  -411,   355,
      22,  -411,    22,    65,   307,  -411,  -411,   106,  -411,   161,
     161,   382,   383,   385,   197,    35,   390,    92,    11,    70,
     -29,  -411,  -411,  -411,  -411,  -411,   394,  -411,    26,  -411,
    -411,  -411,   392,  -411,  -411,  -411,  -411,  -411,   393,   356,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   169,
    -411,   171,  -411,  -411,   190,  -411,  -411,  -411,   397,   402,
     403,  -411,   191,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,   200,  -411,   381,   405,  -411,  -411,   404,   406,
    -411,  -411,   408,   409,  -411,  -411,  -411,  -411,  -411,  -411,
      29,  -411,  -411,  -411,  -411,  -411,    99,  -411,   410,   414,
    -411,   407,   415,   416,   417,   420,   421,   201,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,   423,   424,   425,  -411,
    -411,  -411,   202,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     203,  -411,  -411,  -411,   210,    22,   365,  -411,  -411,   412,
     427,  -411,  -411,   426,   428,  -411,  -411,   431,  -411,   429,
     307,  -411,  -411,   430,   432,   436,   367,   368,   369,   161,
    -411,  -411,    19,  -411,   382,    17,  -411,   383,    67,  -411,
     385,   197,  -411,    35,  -411,   -17,  -411,   390,   372,   373,
     374,   375,   376,   377,    92,  -411,   437,   378,   384,   386,
      11,  -411,   439,   440,    70,  -411,  -411,   442,  -411,    -6,
    -411,   392,    96,  -411,   393,   441,  -411,   444,  -411,   388,
     389,   391,  -411,  -411,  -411,  -411,   211,  -411,   438,  -411,
     443,  -411,  -411,  -411,   212,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,   395,  -411,  -411,  -411,  -411,   396,   398,
    -411,  -411,   214,  -411,   445,  -411,   399,   447,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,   141,  -411,    48,   447,  -411,  -411,   446,  -411,
    -411,  -411,   220,  -411,  -411,  -411,  -411,  -411,   448,   400,
     451,    48,  -411,   453,  -411,   411,  -411,   452,  -411,  -411,
     189,  -411,   401,   452,  -411,  -411,   221,  -411,  -411,   456,
     401,  -411,   413,  -411,  -411
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    94,     9,
     185,    11,   295,    13,   312,    15,   235,    17,   269,    19,
     150,    21,    40,    32,     0,     0,     0,     0,     0,   314,
     237,   271,     0,    42,     0,    41,     0,     0,    33,    54,
     407,   403,   405,     0,    53,     0,    47,    49,    51,    52,
      50,    88,     0,     0,   330,   102,   104,     0,     0,     0,
       0,   177,   227,   261,   131,   354,   142,   161,   374,     0,
     391,   401,    81,     0,    58,    60,    61,    62,    63,    78,
      79,    65,    66,    67,    68,    72,    73,    64,    70,    71,
      80,    69,    74,    75,    76,    77,    96,    98,     0,    90,
      92,    93,   358,   211,   213,   215,   287,   209,   217,   219,
       0,     0,   223,   221,   304,   350,   208,   189,   190,   191,
     203,     0,   187,   194,   205,   206,   207,   195,   196,   199,
     201,   197,   198,   192,   193,   200,   204,   202,   302,   301,
     300,     0,   297,   299,   332,   334,   348,   338,   340,   344,
     342,   346,   336,   329,   325,     0,   315,   316,   326,   327,
     328,   322,   318,   323,   320,   321,   324,   319,   117,   125,
       0,   255,   253,   258,     0,   248,   252,   249,     0,   238,
     239,   241,   251,   242,   243,   244,   257,   245,   246,   247,
     282,     0,   280,   281,   284,   285,     0,   272,   273,   275,
     276,   277,   278,   279,   157,   159,   154,     0,   152,   155,
     156,    37,     0,     0,    31,     0,     0,     0,     0,     0,
      44,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    95,
     360,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   186,     0,     0,   296,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   313,     0,
       0,     0,     0,     0,     0,     0,     0,   236,     0,     0,
       0,   270,     0,     0,     0,     0,   151,    43,    34,     0,
       0,     0,     0,     0,    48,     0,    86,    87,     0,     0,
       0,    82,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,   390,     0,     0,    59,     0,     0,    91,
     372,   370,   371,   366,   367,   368,   369,     0,   361,   362,
     364,   365,     0,     0,     0,     0,     0,     0,     0,   225,
     226,     0,     0,     0,     0,   188,     0,   298,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   317,     0,     0,
     250,     0,     0,     0,   260,   240,     0,   286,   274,     0,
       0,   153,     0,     0,     0,   404,   406,     0,   331,     0,
       0,   179,   229,   263,     0,     0,   144,     0,     0,     0,
       0,    38,    97,   100,   101,    99,     0,   359,     0,   212,
     214,   216,   289,   210,   218,   220,   224,   222,   306,     0,
     303,   333,   335,   349,   339,   341,   345,   343,   347,   337,
     118,   126,   256,   254,   259,   283,   158,   160,    35,     0,
     412,     0,   409,   411,     0,   119,   121,   123,     0,     0,
       0,   116,     0,   106,   108,   109,   110,   111,   112,   113,
     114,   115,     0,   183,     0,   180,   181,   233,     0,   230,
     231,   267,     0,   264,   265,   130,   139,   140,   141,   135,
       0,   133,   136,   137,   138,   356,     0,   148,     0,   145,
     146,     0,     0,     0,     0,     0,     0,     0,   163,   165,
     166,   167,   168,   169,   170,   386,     0,     0,     0,   384,
     378,   383,     0,   376,   381,   379,   380,   382,   397,   399,
       0,   393,   395,   396,     0,    40,     0,   363,   293,     0,
     290,   291,   310,     0,   307,   308,   352,     0,    55,     0,
       0,   408,    89,     0,     0,     0,     0,     0,     0,     0,
     103,   105,     0,   178,     0,   237,   228,     0,   271,   262,
       0,     0,   132,     0,   355,     0,   143,     0,     0,     0,
       0,     0,     0,     0,     0,   162,     0,     0,     0,     0,
       0,   375,     0,     0,     0,   392,   402,     0,   373,     0,
     288,     0,   314,   305,     0,     0,   351,     0,   410,     0,
       0,     0,   127,   128,   129,   107,     0,   182,     0,   232,
       0,   266,   134,   357,     0,   147,   171,   172,   173,   174,
     175,   176,   164,     0,   385,   388,   389,   377,     0,     0,
     394,    39,     0,   292,     0,   309,     0,     0,   120,   122,
     124,   184,   234,   268,   149,   387,   398,   400,   294,   311,
     353,   416,     0,   414,     0,     0,   413,   428,     0,   426,
     424,   420,     0,   418,   422,   423,   421,   415,     0,     0,
       0,     0,   417,     0,   425,     0,   419,     0,   427,   432,
       0,   430,     0,     0,   429,   436,     0,   434,   431,     0,
       0,   433,     0,   435,   437
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,     3,  -411,  -411,  -411,  -411,     5,  -411,  -411,
      73,  -411,   -93,  -411,   -54,  -411,  -411,  -411,   216,  -411,
    -411,  -411,  -411,    51,   198,   -56,   -40,   -38,  -411,  -411,
     -37,  -411,  -411,    49,   187,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,    50,  -111,  -398,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,   -59,  -411,  -410,  -411,
    -411,  -411,  -411,  -411,  -411,  -122,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -124,  -411,  -411,  -411,  -121,   152,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -118,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   -97,  -411,  -411,
    -411,   -94,   205,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -402,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,   -98,  -411,  -411,  -411,   -95,
    -411,   178,  -411,   -52,  -411,  -411,  -411,  -411,   -48,  -411,
    -411,  -411,  -411,  -411,   -47,  -411,  -411,  -411,   -92,  -411,
    -411,  -411,   -88,  -411,   181,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -115,  -411,  -411,  -411,  -110,
     217,  -411,  -411,  -411,  -411,  -411,  -411,  -116,  -411,  -411,
    -411,  -112,  -411,   206,   -43,  -411,  -256,  -411,  -255,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,    74,  -411,  -411,  -411,  -411,  -411,
    -411,   -99,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -101,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,   -49,  -411,  -411,  -411,  -169,
    -411,  -411,  -183,  -411,  -411,  -411,  -411,  -411,  -411,  -191,
    -411,  -411,  -197,  -411
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,    67,    68,    33,    52,
     432,   555,    64,    65,   102,    35,    54,    75,    76,    77,
     246,    37,    55,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   253,   128,   129,    39,    56,   130,   276,   131,
     277,   435,   112,   257,   113,   258,   482,   483,   206,   310,
     485,   573,   486,   574,   487,   575,   207,   311,   489,   490,
     491,   509,   114,   266,   510,   511,   512,   513,   514,   115,
     268,   518,   519,   520,   595,    51,    62,   237,   238,   239,
     323,   240,   324,   116,   269,   527,   528,   529,   530,   531,
     532,   533,   534,   117,   263,   494,   495,   496,   582,    41,
      57,   151,   152,   153,   285,   154,   281,   155,   282,   156,
     283,   157,   286,   158,   287,   159,   291,   160,   290,   161,
     162,   118,   264,   498,   499,   500,   585,    47,    60,   208,
     209,   210,   211,   212,   213,   214,   215,   314,   216,   313,
     217,   218,   315,   219,   119,   265,   502,   503,   504,   588,
      49,    61,   226,   227,   228,   229,   230,   319,   231,   232,
     233,   164,   284,   559,   560,   561,   619,    43,    58,   171,
     172,   173,   296,   165,   292,   563,   564,   565,   622,    45,
      59,   185,   186,   187,   120,   256,   189,   299,   190,   300,
     191,   307,   192,   302,   193,   303,   194,   305,   195,   304,
     196,   306,   197,   301,   167,   293,   567,   625,   121,   267,
     516,   280,   367,   368,   369,   370,   371,   436,   122,   270,
     542,   543,   544,   545,   606,   546,   547,   123,   124,   272,
     550,   551,   552,   612,   553,   613,   125,   273,    78,   248,
      79,   249,    80,   247,   471,   472,   473,   569,   682,   683,
     684,   692,   693,   694,   695,   700,   696,   698,   710,   711,
     712,   716,   717,   719
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   147,   223,   146,   169,   183,   205,   222,   236,   224,
     163,   170,   184,   225,   166,    30,   188,   148,   541,   149,
     150,   484,   484,   515,   365,   366,   132,    23,    69,    24,
     540,    25,   591,    93,   198,   592,    83,    84,   478,    22,
     198,    34,   132,   168,    84,   174,   175,   234,   235,    87,
      88,    89,   234,   235,   133,   134,   135,   199,    93,   200,
     201,    36,   202,   203,   204,    93,   199,   136,    38,   137,
     138,   139,   140,   141,   142,   251,    81,    66,   143,   144,
     252,    82,    83,    84,   360,   145,    85,    86,   199,    73,
     535,   536,   537,   538,   143,    87,    88,    89,    90,    91,
      73,    40,   593,    92,    93,   594,    70,   199,   220,   200,
     201,   221,    71,    72,    84,   174,   175,    73,   126,   127,
      42,    94,    95,    73,    73,    73,   433,   434,    26,    27,
      28,    29,    73,    96,   274,    93,    97,   278,   687,   275,
     688,   689,   279,    98,   685,   294,   297,   686,    99,   100,
     295,   298,   101,   176,    73,   548,   549,   177,   178,   179,
     180,   181,    44,   182,   521,   522,   523,   524,   525,   526,
     325,    73,   274,    73,   570,   326,   241,   568,   242,   571,
      46,   484,   365,   366,   198,   475,   476,   477,   478,   479,
     480,   643,   713,   278,   579,   714,   243,    74,   572,   580,
     541,   199,    73,   579,   604,   610,   614,   244,   581,   605,
     611,   615,   540,   245,   294,   325,    48,   297,   616,   671,
     674,   362,   678,   701,   720,    50,   361,   245,   702,   721,
     250,   254,   255,   363,   259,   260,   261,   364,   147,   262,
     146,   271,   288,   169,   289,   327,   328,   163,   309,   308,
     170,   166,   312,   316,   148,   183,   149,   150,   505,   506,
     507,   508,   184,   223,   205,   317,   188,    73,   222,   318,
     224,   320,   321,   322,   225,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,   330,   329,   331,   332,   333,
     335,   336,   337,   338,   339,   340,   345,   346,   347,   348,
     341,   342,   343,   344,   349,   350,   351,   352,   354,   355,
     357,   353,   358,   372,   373,   374,   375,   376,   377,   378,
     379,   381,   382,   383,   380,   384,   386,   388,   389,   390,
     391,   392,   393,   394,   395,   415,   416,   396,   398,   399,
     400,   401,   402,   403,   406,   404,   409,   410,   407,   412,
     418,   413,   439,   414,   417,   419,   420,   421,   422,   423,
     488,   488,   424,   425,   426,   481,   481,   427,   428,   429,
     430,   431,   437,   438,   539,   440,   442,   441,   443,   362,
     444,   445,   446,   447,   361,   448,   449,   583,   450,   493,
     497,   363,   501,   451,   452,   364,   470,   517,   556,   558,
     562,   576,   454,   455,   456,   457,   577,   578,   584,   587,
     586,   598,   590,   467,   589,   468,   596,   597,   620,   599,
     600,   601,   458,   566,   602,   603,   459,   607,   608,   609,
     621,   624,   623,   627,   629,   554,   630,   460,   461,   626,
     631,   653,   462,   658,   659,   666,   672,   463,   661,   667,
     699,   673,   703,   679,   681,   705,   464,   465,   707,   709,
     722,   466,   617,   453,   469,   359,   474,   334,   635,   642,
     492,   618,   356,   645,   644,   633,   632,   411,   634,   646,
     647,   648,   649,   650,   651,   654,   652,   637,   636,   639,
     638,   655,   715,   656,   668,   669,   405,   670,   641,   385,
     640,   675,   676,   408,   677,   680,   663,   704,   665,   662,
     664,   657,   557,   660,   387,   397,   697,   708,   706,   724,
     488,   628,   718,   723,     0,   481,   147,     0,   146,   223,
       0,   205,     0,     0,   222,   163,   224,     0,     0,   166,
     225,   236,   148,     0,   149,   150,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   539,     0,     0,     0,
       0,     0,     0,     0,     0,   169,     0,     0,   183,     0,
       0,     0,   170,     0,     0,   184,     0,     0,     0,   188,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   691,     0,     0,     0,     0,
     690,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   691,     0,     0,     0,     0,   690
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,    12,    59,    57,   428,    57,
      57,   419,   420,   425,   280,   280,     7,     5,    10,     7,
     428,     9,     3,    39,    23,     6,    17,    18,    27,     0,
      23,     7,     7,    49,    18,    19,    20,    69,    70,    30,
      31,    32,    69,    70,    35,    36,    37,    40,    39,    42,
      43,     7,    45,    46,    47,    39,    40,    48,     7,    50,
      51,    52,    53,    54,    55,     3,    11,   106,    59,    60,
       8,    16,    17,    18,    58,    66,    21,    22,    40,   106,
      79,    80,    81,    82,    59,    30,    31,    32,    33,    34,
     106,     7,     3,    38,    39,     6,    88,    40,    41,    42,
      43,    44,    94,    95,    18,    19,    20,   106,    12,    13,
       7,    56,    57,   106,   106,   106,    14,    15,   106,   107,
     108,   109,   106,    68,     3,    39,    71,     3,    90,     8,
      92,    93,     8,    78,     3,     3,     3,     6,    83,    84,
       8,     8,    87,    57,   106,    85,    86,    61,    62,    63,
      64,    65,     7,    67,    72,    73,    74,    75,    76,    77,
       3,   106,     3,   106,     3,     8,     6,     8,     3,     8,
       7,   579,   438,   438,    23,    24,    25,    26,    27,    28,
      29,   593,     3,     3,     3,     6,     4,   251,     8,     8,
     610,    40,   106,     3,     3,     3,     3,     8,     8,     8,
       8,     8,   610,     3,     3,     3,     7,     3,     8,     8,
       8,   280,     8,     3,     3,     7,   280,     3,     8,     8,
       4,     4,     4,   280,     4,     4,     4,   280,   294,     4,
     294,     4,     4,   297,     4,   242,   243,   294,     3,     8,
     297,   294,     4,     4,   294,   309,   294,   294,    61,    62,
      63,    64,   309,   322,   318,     8,   309,   106,   322,     3,
     322,     4,     8,     3,   322,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     4,   106,     4,     4,     4,
       4,   109,   109,     4,     4,     4,     4,     4,     4,     4,
     107,   107,   107,   107,     4,     4,     4,     4,     4,     4,
       4,   107,     4,     4,     4,     4,     4,     4,     4,     4,
     107,     4,     4,     4,   109,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   332,   333,     4,     4,     4,
     107,     4,     4,     4,     4,   109,     4,     4,   109,     4,
     106,     7,   106,     7,     7,     7,     7,     5,     5,     5,
     419,   420,     5,     5,     5,   419,   420,     7,     7,     7,
       7,     5,     8,     3,   428,   106,     5,   106,   106,   438,
     106,   106,   106,   106,   438,     5,     7,     6,   106,     7,
       7,   438,     7,   106,   106,   438,    89,     7,     4,     7,
       7,     4,   106,   106,   106,   106,     4,     4,     3,     3,
       6,     4,     3,   410,     6,   412,     6,     3,     6,     4,
       4,     4,   106,    67,     4,     4,   106,     4,     4,     4,
       3,     3,     6,     4,     4,   430,     4,   106,   106,     8,
       4,     4,   106,     4,     4,     4,     8,   106,     6,     5,
       4,     8,     4,     8,     7,     4,   106,   106,     5,     7,
       4,   106,   555,   390,   413,   278,   417,   251,   579,   591,
     420,   106,   274,   597,   595,   107,   109,   325,   109,   107,
     107,   107,   107,   107,   107,   107,   604,   584,   582,   587,
     585,   107,    91,   107,   106,   106,   318,   106,   590,   294,
     588,   106,   106,   322,   106,   106,   621,   107,   624,   619,
     622,   610,   438,   614,   297,   309,   685,   106,   701,   106,
     579,   570,   713,   720,    -1,   579,   582,    -1,   582,   588,
      -1,   585,    -1,    -1,   588,   582,   588,    -1,    -1,   582,
     588,   595,   582,    -1,   582,   582,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   610,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   619,    -1,    -1,   622,    -1,
      -1,    -1,   619,    -1,    -1,   622,    -1,    -1,    -1,   622,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   684,    -1,    -1,    -1,    -1,
     684,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   701,    -1,    -1,    -1,    -1,   701
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,     0,     5,     7,     9,   106,   107,   108,   109,
     122,   123,   124,   128,     7,   135,     7,   141,     7,   155,
       7,   219,     7,   287,     7,   299,     7,   247,     7,   270,
       7,   195,   129,   125,   136,   142,   156,   220,   288,   300,
     248,   271,   196,   122,   132,   133,   106,   126,   127,    10,
      88,    94,    95,   106,   134,   137,   138,   139,   358,   360,
     362,    11,    16,    17,    18,    21,    22,    30,    31,    32,
      33,    34,    38,    39,    56,    57,    68,    71,    78,    83,
      84,    87,   134,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   162,   164,   182,   189,   203,   213,   241,   264,
     304,   328,   338,   347,   348,   356,    12,    13,   153,   154,
     157,   159,     7,    35,    36,    37,    48,    50,    51,    52,
      53,    54,    55,    59,    60,    66,   134,   145,   146,   147,
     150,   221,   222,   223,   225,   227,   229,   231,   233,   235,
     237,   239,   240,   264,   281,   293,   304,   324,    49,   134,
     264,   289,   290,   291,    19,    20,    57,    61,    62,    63,
      64,    65,    67,   134,   264,   301,   302,   303,   304,   306,
     308,   310,   312,   314,   316,   318,   320,   322,    23,    40,
      42,    43,    45,    46,    47,   134,   168,   176,   249,   250,
     251,   252,   253,   254,   255,   256,   258,   260,   261,   263,
      41,    44,   134,   176,   253,   258,   272,   273,   274,   275,
     276,   278,   279,   280,    69,    70,   134,   197,   198,   199,
     201,     6,     3,     4,     8,     3,   140,   363,   359,   361,
       4,     3,     8,   152,     4,     4,   305,   163,   165,     4,
       4,     4,     4,   214,   242,   265,   183,   329,   190,   204,
     339,     4,   349,   357,     3,     8,   158,   160,     3,     8,
     331,   226,   228,   230,   282,   224,   232,   234,     4,     4,
     238,   236,   294,   325,     3,     8,   292,     3,     8,   307,
     309,   323,   313,   315,   319,   317,   321,   311,     8,     3,
     169,   177,     4,   259,   257,   262,     4,     8,     3,   277,
       4,     8,     3,   200,   202,     3,     8,   122,   122,   106,
       4,     4,     4,     4,   138,     4,   109,   109,     4,     4,
       4,   107,   107,   107,   107,     4,     4,     4,     4,     4,
       4,     4,     4,   107,     4,     4,   144,     4,     4,   154,
      58,   134,   176,   264,   304,   306,   308,   332,   333,   334,
     335,   336,     4,     4,     4,     4,     4,     4,     4,   107,
     109,     4,     4,     4,     4,   222,     4,   290,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   303,     4,     4,
     107,     4,     4,     4,   109,   251,     4,   109,   274,     4,
       4,   198,     4,     7,     7,   122,   122,     7,   106,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   130,    14,    15,   161,   337,     8,     3,   106,
     106,   106,     5,   106,   106,   106,   106,   106,     5,     7,
     106,   106,   106,   130,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   122,   122,   143,
      89,   364,   365,   366,   153,    24,    25,    26,    27,    28,
      29,   134,   166,   167,   168,   170,   172,   174,   176,   178,
     179,   180,   166,     7,   215,   216,   217,     7,   243,   244,
     245,     7,   266,   267,   268,    61,    62,    63,    64,   181,
     184,   185,   186,   187,   188,   235,   330,     7,   191,   192,
     193,    72,    73,    74,    75,    76,    77,   205,   206,   207,
     208,   209,   210,   211,   212,    79,    80,    81,    82,   134,
     168,   178,   340,   341,   342,   343,   345,   346,    85,    86,
     350,   351,   352,   354,   127,   131,     4,   334,     7,   283,
     284,   285,     7,   295,   296,   297,    67,   326,     8,   367,
       3,     8,     8,   171,   173,   175,     4,     4,     4,     3,
       8,     8,   218,     6,     3,   246,     6,     3,   269,     6,
       3,     3,     6,     3,     6,   194,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   344,     4,     4,     4,
       3,     8,   353,   355,     3,     8,     8,   132,   106,   286,
       6,     3,   298,     6,     3,   327,     8,     4,   365,     4,
       4,     4,   109,   107,   109,   167,   221,   217,   249,   245,
     272,   268,   185,   235,   197,   193,   107,   107,   107,   107,
     107,   107,   206,     4,   107,   107,   107,   341,     4,     4,
     351,     6,   289,   285,   301,   297,     4,     5,   106,   106,
     106,     8,     8,     8,     8,   106,   106,   106,     8,     8,
     106,     7,   368,   369,   370,     3,     6,    90,    92,    93,
     134,   176,   371,   372,   373,   374,   376,   369,   377,     4,
     375,     3,     8,     4,   107,     4,   372,     5,   106,     7,
     378,   379,   380,     3,     6,    91,   381,   382,   379,   383,
       3,     8,     4,   382,   106
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   110,   112,   111,   113,   111,   114,   111,   115,   111,
     116,   111,   117,   111,   118,   111,   119,   111,   120,   111,
     121,   111,   122,   122,   122,   122,   122,   122,   122,   123,
     125,   124,   126,   126,   127,   127,   129,   128,   131,   130,
     132,   132,   133,   133,   134,   136,   135,   137,   137,   138,
     138,   138,   138,   138,   140,   139,   142,   141,   143,   143,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   145,   146,   147,   148,   149,   150,   152,   151,
     153,   153,   154,   154,   156,   155,   158,   157,   160,   159,
     161,   161,   163,   162,   165,   164,   166,   166,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   169,   168,   171,
     170,   173,   172,   175,   174,   177,   176,   178,   179,   180,
     181,   183,   182,   184,   184,   185,   185,   185,   185,   186,
     187,   188,   190,   189,   191,   191,   192,   192,   194,   193,
     196,   195,   197,   197,   197,   198,   198,   200,   199,   202,
     201,   204,   203,   205,   205,   206,   206,   206,   206,   206,
     206,   207,   208,   209,   210,   211,   212,   214,   213,   215,
     215,   216,   216,   218,   217,   220,   219,   221,   221,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   224,
     223,   226,   225,   228,   227,   230,   229,   232,   231,   234,
     233,   236,   235,   238,   237,   239,   240,   242,   241,   243,
     243,   244,   244,   246,   245,   248,   247,   249,   249,   250,
     250,   251,   251,   251,   251,   251,   251,   251,   251,   252,
     253,   254,   255,   257,   256,   259,   258,   260,   262,   261,
     263,   265,   264,   266,   266,   267,   267,   269,   268,   271,
     270,   272,   272,   273,   273,   274,   274,   274,   274,   274,
     274,   275,   277,   276,   278,   279,   280,   282,   281,   283,
     283,   284,   284,   286,   285,   288,   287,   289,   289,   290,
     290,   290,   292,   291,   294,   293,   295,   295,   296,   296,
     298,   297,   300,   299,   301,   301,   302,   302,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     305,   304,   307,   306,   309,   308,   311,   310,   313,   312,
     315,   314,   317,   316,   319,   318,   321,   320,   323,   322,
     325,   324,   327,   326,   329,   328,   330,   330,   331,   235,
     332,   332,   333,   333,   334,   334,   334,   334,   334,   334,
     334,   335,   337,   336,   339,   338,   340,   340,   341,   341,
     341,   341,   341,   341,   341,   342,   344,   343,   345,   346,
     347,   349,   348,   350,   350,   351,   351,   353,   352,   355,
     354,   357,   356,   359,   358,   361,   360,   363,   362,   364,
     364,   365,   367,   366,   368,   368,   370,   369,   371,   371,
     372,   372,   372,   372,   372,   373,   375,   374,   377,   376,
     378,   378,   380,   379,   381,   381,   383,   382
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
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"next-server\"", "\"server-hostname\"", "\"boot-file-name\"",
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"user\"",
  "\"password\"", "\"host\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"record-types\"", "\"encapsulate\"",
  "\"array\"", "\"pools\"", "\"pool\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"identifier\"",
  "\"htype\"", "\"time\"", "\"enterprise-id\"", "\"dhcp4o6-port\"",
  "\"control-socket\"", "\"socket-type\"", "\"socket-name\"",
  "\"dhcp-ddns\"", "\"Logging\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4",
  "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "value", "sub_json", "map2", "$@11",
  "map_content", "not_empty_map", "list_generic", "$@12", "list2", "$@13",
  "list_content", "not_empty_list", "unknown_map_entry", "syntax_map",
  "$@14", "global_objects", "global_object", "dhcp4_object", "$@15",
  "sub_dhcp4", "$@16", "global_params", "global_param", "valid_lifetime",
  "renew_timer", "rebind_timer", "decline_probation_period",
  "echo_client_id", "match_client_id", "interfaces_config", "$@17",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@18", "interfaces_list", "$@19", "dhcp_socket_type", "$@20",
  "socket_type", "lease_database", "$@21", "hosts_database", "$@22",
  "database_map_params", "database_map_param", "type", "$@23", "user",
  "$@24", "password", "$@25", "host", "$@26", "name", "$@27", "persist",
  "lfc_interval", "readonly", "duid_id", "host_reservation_identifiers",
  "$@28", "host_reservation_identifiers_list",
  "host_reservation_identifier", "hw_address_id", "circuit_id",
  "client_id", "hooks_libraries", "$@29", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@30",
  "sub_hooks_library", "$@31", "hooks_params", "hooks_param", "library",
  "$@32", "parameters", "$@33", "expired_leases_processing", "$@34",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@35",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@36",
  "sub_subnet4", "$@37", "subnet4_params", "subnet4_param", "subnet",
  "$@38", "subnet_4o6_interface", "$@39", "subnet_4o6_interface_id",
  "$@40", "subnet_4o6_subnet", "$@41", "interface", "$@42", "interface_id",
  "$@43", "client_class", "$@44", "reservation_mode", "$@45", "id",
  "rapid_commit", "option_def_list", "$@46", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@47",
  "sub_option_def", "$@48", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "option_def_record_types",
  "$@49", "space", "$@50", "option_def_space", "option_def_encapsulate",
  "$@51", "option_def_array", "option_data_list", "$@52",
  "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@53", "sub_option_data", "$@54",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@55",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@56", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@57", "sub_pool4", "$@58", "pool_params",
  "pool_param", "pool_entry", "$@59", "reservations", "$@60",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@61", "sub_reservation", "$@62", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@63", "server_hostname", "$@64", "boot_file_name", "$@65",
  "ip_address", "$@66", "duid", "$@67", "hw_address", "$@68",
  "client_id_value", "$@69", "circuit_id_value", "$@70", "hostname",
  "$@71", "reservation_client_classes", "$@72", "relay", "$@73",
  "relay_map", "$@74", "client_classes", "$@75", "client_classes_list",
  "$@76", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@77",
  "server_id", "$@78", "server_id_params", "server_id_param", "htype",
  "identifier", "$@79", "time", "enterprise_id", "dhcp4o6_port",
  "control_socket", "$@80", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@81",
  "control_socket_name", "$@82", "dhcp_ddns", "$@83", "dhcp6_json_object",
  "$@84", "dhcpddns_json_object", "$@85", "logging_object", "$@86",
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
       0,   207,   207,   207,   208,   208,   209,   209,   210,   210,
     211,   211,   212,   212,   213,   213,   214,   214,   215,   215,
     216,   216,   224,   225,   226,   227,   228,   229,   230,   233,
     238,   238,   250,   251,   254,   258,   265,   265,   273,   273,
     280,   281,   284,   288,   299,   309,   309,   321,   322,   326,
     327,   328,   329,   330,   333,   333,   350,   350,   358,   359,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   388,   393,   398,   403,   408,   413,   419,   419,
     429,   430,   433,   434,   437,   437,   445,   445,   455,   455,
     462,   463,   466,   466,   476,   476,   486,   487,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   501,   501,   509,
     509,   517,   517,   525,   525,   533,   533,   541,   546,   551,
     556,   561,   561,   571,   572,   575,   576,   577,   578,   581,
     586,   591,   596,   596,   606,   607,   610,   611,   614,   614,
     622,   622,   630,   631,   632,   635,   636,   639,   639,   647,
     647,   655,   655,   665,   666,   669,   670,   671,   672,   673,
     674,   677,   682,   687,   692,   697,   702,   710,   710,   723,
     724,   727,   728,   735,   735,   758,   758,   767,   768,   772,
     773,   774,   775,   776,   777,   778,   779,   780,   781,   782,
     783,   784,   785,   786,   787,   788,   789,   790,   791,   794,
     794,   802,   802,   810,   810,   818,   818,   826,   826,   834,
     834,   842,   842,   850,   850,   858,   863,   872,   872,   884,
     885,   888,   889,   894,   894,   905,   905,   915,   916,   919,
     920,   923,   924,   925,   926,   927,   928,   929,   930,   933,
     935,   940,   942,   944,   944,   952,   952,   960,   962,   962,
     970,   979,   979,   991,   992,   997,   998,  1003,  1003,  1014,
    1014,  1025,  1026,  1031,  1032,  1037,  1038,  1039,  1040,  1041,
    1042,  1045,  1047,  1047,  1055,  1057,  1059,  1067,  1067,  1079,
    1080,  1083,  1084,  1087,  1087,  1095,  1095,  1103,  1104,  1107,
    1108,  1109,  1112,  1112,  1123,  1123,  1133,  1134,  1137,  1138,
    1141,  1141,  1149,  1149,  1157,  1158,  1161,  1162,  1166,  1167,
    1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,
    1180,  1180,  1188,  1188,  1196,  1196,  1204,  1204,  1212,  1212,
    1220,  1220,  1228,  1228,  1236,  1236,  1245,  1245,  1253,  1253,
    1266,  1266,  1276,  1276,  1287,  1287,  1297,  1298,  1301,  1301,
    1309,  1310,  1313,  1314,  1317,  1318,  1319,  1320,  1321,  1322,
    1323,  1326,  1328,  1328,  1339,  1339,  1349,  1350,  1353,  1354,
    1355,  1356,  1357,  1358,  1359,  1362,  1367,  1367,  1375,  1380,
    1387,  1394,  1394,  1404,  1405,  1408,  1409,  1412,  1412,  1420,
    1420,  1430,  1430,  1442,  1442,  1449,  1449,  1461,  1461,  1474,
    1475,  1479,  1483,  1483,  1495,  1496,  1500,  1500,  1508,  1509,
    1512,  1513,  1514,  1515,  1516,  1519,  1523,  1523,  1531,  1531,
    1541,  1542,  1545,  1545,  1553,  1554,  1557,  1557
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
#line 3583 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1565 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
