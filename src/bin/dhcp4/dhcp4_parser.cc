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
      case 120: // value
        value.move< ElementPtr > (that.value);
        break;

      case 107: // "boolean"
        value.move< bool > (that.value);
        break;

      case 106: // "floating point"
        value.move< double > (that.value);
        break;

      case 105: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 104: // "constant string"
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
      case 120: // value
        value.copy< ElementPtr > (that.value);
        break;

      case 107: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 106: // "floating point"
        value.copy< double > (that.value);
        break;

      case 105: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 104: // "constant string"
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
            case 104: // "constant string"

#line 195 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 352 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 105: // "integer"

#line 195 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 359 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 106: // "floating point"

#line 195 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 107: // "boolean"

#line 195 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 120: // value

#line 195 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 120: // value
        yylhs.value.build< ElementPtr > ();
        break;

      case 107: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 106: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 105: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 104: // "constant string"
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
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 208 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 209 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 210 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 211 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 212 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 213 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 225 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 390 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 405 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr type(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-socket-type", type);
    ctx.leave();
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1430 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1497 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1515 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1587 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1605 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1835 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1864 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1122 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1135 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1139 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1174 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 1992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2028 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1214 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2118 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2156 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2184 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2501 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2519 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2549 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2557 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2575 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2579 "dhcp4_parser.cc" // lalr1.cc:859
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
     117,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    39,    22,    52,    59,    66,    81,    90,    96,   111,
     131,   147,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,    22,   -58,    18,    70,    20,    19,     4,    98,
      17,   102,    45,  -411,    99,    75,   105,   148,   159,  -411,
    -411,  -411,  -411,   160,  -411,    42,  -411,  -411,  -411,  -411,
    -411,  -411,   184,   203,  -411,  -411,  -411,   237,   238,   248,
     255,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   256,
    -411,  -411,  -411,    71,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,    72,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     257,   261,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    88,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   129,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,   259,   266,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     267,  -411,  -411,  -411,   268,  -411,  -411,  -411,   265,   276,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   277,  -411,  -411,  -411,  -411,   272,   279,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   142,  -411,  -411,
    -411,  -411,    22,    22,  -411,   179,   280,   281,   282,   283,
    -411,    18,  -411,   284,   182,   183,   287,   288,   289,   189,
     190,   191,   192,   294,   295,   296,   297,   298,   299,   300,
     301,   202,   302,   304,    70,  -411,   305,   306,    20,  -411,
      26,   307,   308,   309,   310,   311,   312,   313,   213,   212,
     316,   317,   318,   319,    19,  -411,   320,     4,  -411,   321,
     322,   323,   324,   325,   326,   327,   328,   329,  -411,    98,
     330,   333,   233,   335,   336,   337,   235,  -411,    17,   339,
     239,  -411,   102,   340,   341,    80,  -411,  -411,  -411,   343,
     342,   344,    22,    22,  -411,   345,  -411,  -411,   244,   346,
     347,  -411,  -411,  -411,  -411,   350,   351,   352,   353,   354,
     357,   356,   360,  -411,   361,   362,  -411,   359,   246,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   363,   367,  -411,
    -411,  -411,   269,   271,   274,   371,   275,   286,   290,  -411,
    -411,   291,   292,   375,   365,  -411,   293,  -411,   303,   314,
     359,   315,   331,   332,   334,   338,   348,  -411,   349,   355,
    -411,   358,   364,   366,  -411,  -411,   368,  -411,  -411,   369,
      22,  -411,    22,    70,   370,  -411,  -411,    20,  -411,   144,
     144,   374,   376,   377,   216,    30,   378,   120,    15,    92,
     -58,  -411,  -411,  -411,   382,  -411,    26,  -411,  -411,  -411,
     380,  -411,  -411,  -411,  -411,  -411,   381,   372,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   169,  -411,   170,
    -411,  -411,   193,  -411,  -411,  -411,   387,   388,   394,  -411,
     197,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     200,  -411,   393,   397,  -411,  -411,   395,   399,  -411,  -411,
     398,   400,  -411,  -411,  -411,  -411,  -411,  -411,   114,  -411,
    -411,  -411,  -411,  -411,   128,  -411,   402,   403,  -411,   401,
     405,   406,   407,   408,   410,   201,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,   412,   413,   416,  -411,  -411,  -411,
     219,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   220,  -411,
    -411,  -411,   221,    22,   373,  -411,  -411,   415,   419,  -411,
    -411,   417,   421,  -411,  -411,   418,  -411,   423,   370,  -411,
    -411,   424,   425,   426,   379,   383,   384,   144,  -411,  -411,
      19,  -411,   374,    17,  -411,   376,   102,  -411,   377,   216,
    -411,    30,  -411,    45,  -411,   378,   385,   389,   390,   391,
     392,   396,   120,  -411,   427,   404,   409,   411,    15,  -411,
     428,   429,    92,  -411,  -411,   433,  -411,     4,  -411,   380,
      98,  -411,   381,   430,  -411,   420,  -411,   431,   432,   437,
    -411,  -411,  -411,  -411,   222,  -411,   435,  -411,   436,  -411,
    -411,  -411,   228,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   440,  -411,  -411,  -411,  -411,   441,   442,  -411,  -411,
     231,  -411,   438,  -411,   443,   434,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     181,  -411,    95,   434,  -411,  -411,   444,  -411,  -411,  -411,
     241,  -411,  -411,  -411,  -411,  -411,   445,   414,   446,    95,
    -411,   449,  -411,   447,  -411,   448,  -411,  -411,   229,  -411,
     386,   448,  -411,  -411,   250,  -411,  -411,   452,   386,  -411,
     451,  -411,  -411
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    94,     9,
     183,    11,   293,    13,   310,    15,   233,    17,   267,    19,
     148,    21,    40,    32,     0,     0,     0,     0,     0,   312,
     235,   269,     0,    42,     0,    41,     0,     0,    33,    54,
     405,   401,   403,     0,    53,     0,    47,    49,    51,    52,
      50,    88,     0,     0,   328,   100,   102,     0,     0,     0,
       0,   175,   225,   259,   129,   352,   140,   159,   372,     0,
     389,   399,    81,     0,    58,    60,    61,    62,    63,    78,
      79,    65,    66,    67,    68,    72,    73,    64,    70,    71,
      80,    69,    74,    75,    76,    77,    96,    98,     0,    90,
      92,    93,   356,   209,   211,   213,   285,   207,   215,   217,
       0,     0,   221,   219,   302,   348,   206,   187,   188,   189,
     201,     0,   185,   192,   203,   204,   205,   193,   194,   197,
     199,   195,   196,   190,   191,   198,   202,   200,   300,   299,
     298,     0,   295,   297,   330,   332,   346,   336,   338,   342,
     340,   344,   334,   327,   323,     0,   313,   314,   324,   325,
     326,   320,   316,   321,   318,   319,   322,   317,   115,   123,
       0,   253,   251,   256,     0,   246,   250,   247,     0,   236,
     237,   239,   249,   240,   241,   242,   255,   243,   244,   245,
     280,     0,   278,   279,   282,   283,     0,   270,   271,   273,
     274,   275,   276,   277,   155,   157,   152,     0,   150,   153,
     154,    37,     0,     0,    31,     0,     0,     0,     0,     0,
      44,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    95,
     358,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   184,     0,     0,   294,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   311,     0,
       0,     0,     0,     0,     0,     0,     0,   234,     0,     0,
       0,   268,     0,     0,     0,     0,   149,    43,    34,     0,
       0,     0,     0,     0,    48,     0,    86,    87,     0,     0,
       0,    82,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,   388,     0,     0,    59,     0,     0,    91,
     370,   368,   369,   364,   365,   366,   367,     0,   359,   360,
     362,   363,     0,     0,     0,     0,     0,     0,     0,   223,
     224,     0,     0,     0,     0,   186,     0,   296,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   315,     0,     0,
     248,     0,     0,     0,   258,   238,     0,   284,   272,     0,
       0,   151,     0,     0,     0,   402,   404,     0,   329,     0,
       0,   177,   227,   261,     0,     0,   142,     0,     0,     0,
       0,    38,    97,    99,     0,   357,     0,   210,   212,   214,
     287,   208,   216,   218,   222,   220,   304,     0,   301,   331,
     333,   347,   337,   339,   343,   341,   345,   335,   116,   124,
     254,   252,   257,   281,   156,   158,    35,     0,   410,     0,
     407,   409,     0,   117,   119,   121,     0,     0,     0,   114,
       0,   104,   106,   107,   108,   109,   110,   111,   112,   113,
       0,   181,     0,   178,   179,   231,     0,   228,   229,   265,
       0,   262,   263,   128,   137,   138,   139,   133,     0,   131,
     134,   135,   136,   354,     0,   146,     0,   143,   144,     0,
       0,     0,     0,     0,     0,     0,   161,   163,   164,   165,
     166,   167,   168,   384,     0,     0,     0,   382,   376,   381,
       0,   374,   379,   377,   378,   380,   395,   397,     0,   391,
     393,   394,     0,    40,     0,   361,   291,     0,   288,   289,
     308,     0,   305,   306,   350,     0,    55,     0,     0,   406,
      89,     0,     0,     0,     0,     0,     0,     0,   101,   103,
       0,   176,     0,   235,   226,     0,   269,   260,     0,     0,
     130,     0,   353,     0,   141,     0,     0,     0,     0,     0,
       0,     0,     0,   160,     0,     0,     0,     0,     0,   373,
       0,     0,     0,   390,   400,     0,   371,     0,   286,     0,
     312,   303,     0,     0,   349,     0,   408,     0,     0,     0,
     125,   126,   127,   105,     0,   180,     0,   230,     0,   264,
     132,   355,     0,   145,   169,   170,   171,   172,   173,   174,
     162,     0,   383,   386,   387,   375,     0,     0,   392,    39,
       0,   290,     0,   307,     0,     0,   118,   120,   122,   182,
     232,   266,   147,   385,   396,   398,   292,   309,   351,   414,
       0,   412,     0,     0,   411,   426,     0,   424,   422,   418,
       0,   416,   420,   421,   419,   413,     0,     0,     0,     0,
     415,     0,   423,     0,   417,     0,   425,   430,     0,   428,
       0,     0,   427,   434,     0,   432,   429,     0,     0,   431,
       0,   433,   435
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,     3,  -411,  -411,  -411,  -411,    10,  -411,  -411,
      55,  -411,  -106,  -411,   -54,  -411,  -411,  -411,   207,  -411,
    -411,  -411,  -411,    38,   186,   -56,   -40,   -38,  -411,  -411,
     -37,  -411,  -411,    44,   185,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,    46,  -113,  -398,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,   -59,  -411,  -410,  -411,  -411,
    -411,  -411,  -411,  -411,  -124,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -128,  -411,  -411,  -411,  -122,   149,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -133,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -104,  -411,  -411,  -411,
    -101,   187,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -402,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -109,  -411,  -411,  -411,  -103,  -411,
     164,  -411,   -52,  -411,  -411,  -411,  -411,   -48,  -411,  -411,
    -411,  -411,  -411,   -47,  -411,  -411,  -411,  -105,  -411,  -411,
    -411,  -102,  -411,   163,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -132,  -411,  -411,  -411,  -125,   196,
    -411,  -411,  -411,  -411,  -411,  -411,  -123,  -411,  -411,  -411,
    -131,  -411,   194,   -43,  -411,  -256,  -411,  -255,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,    62,  -411,  -411,  -411,  -411,  -411,  -411,
    -108,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -110,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,   -64,  -411,  -411,  -411,  -178,  -411,
    -411,  -193,  -411,  -411,  -411,  -411,  -411,  -411,  -204,  -411,
    -411,  -210,  -411
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,    67,    68,    33,    52,
     432,   553,    64,    65,   102,    35,    54,    75,    76,    77,
     246,    37,    55,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   253,   128,   129,    39,    56,   130,   276,   131,
     277,   112,   257,   113,   258,   480,   481,   206,   310,   483,
     571,   484,   572,   485,   573,   207,   311,   487,   488,   489,
     507,   114,   266,   508,   509,   510,   511,   512,   115,   268,
     516,   517,   518,   593,    51,    62,   237,   238,   239,   323,
     240,   324,   116,   269,   525,   526,   527,   528,   529,   530,
     531,   532,   117,   263,   492,   493,   494,   580,    41,    57,
     151,   152,   153,   285,   154,   281,   155,   282,   156,   283,
     157,   286,   158,   287,   159,   291,   160,   290,   161,   162,
     118,   264,   496,   497,   498,   583,    47,    60,   208,   209,
     210,   211,   212,   213,   214,   215,   314,   216,   313,   217,
     218,   315,   219,   119,   265,   500,   501,   502,   586,    49,
      61,   226,   227,   228,   229,   230,   319,   231,   232,   233,
     164,   284,   557,   558,   559,   617,    43,    58,   171,   172,
     173,   296,   165,   292,   561,   562,   563,   620,    45,    59,
     185,   186,   187,   120,   256,   189,   299,   190,   300,   191,
     307,   192,   302,   193,   303,   194,   305,   195,   304,   196,
     306,   197,   301,   167,   293,   565,   623,   121,   267,   514,
     280,   367,   368,   369,   370,   371,   434,   122,   270,   540,
     541,   542,   543,   604,   544,   545,   123,   124,   272,   548,
     549,   550,   610,   551,   611,   125,   273,    78,   248,    79,
     249,    80,   247,   469,   470,   471,   567,   680,   681,   682,
     690,   691,   692,   693,   698,   694,   696,   708,   709,   710,
     714,   715,   717
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   147,   223,   146,   169,   183,   205,   222,   236,   224,
     163,   170,   184,   225,   166,    30,   188,   148,   539,   149,
     150,   482,   482,   513,   365,   366,   132,    23,    69,    24,
     538,    25,   126,   127,    83,    84,   198,   132,   198,    22,
     476,    93,    84,   174,   175,   251,    66,    87,    88,    89,
     252,   168,   133,   134,   135,   199,    93,   200,   201,    34,
     202,   203,   204,    93,   199,   136,    36,   137,   138,   139,
     140,   141,   142,    38,   274,   278,   143,   144,   242,   275,
     279,    81,   360,   145,    82,    83,    84,   143,    40,    85,
      86,   294,   533,   534,   535,   536,   295,    42,    87,    88,
      89,    90,    91,    44,    70,   241,    92,    93,    73,   243,
      71,    72,   234,   235,    84,   174,   175,   589,    46,    73,
     590,    73,    73,    73,    94,    95,    26,    27,    28,    29,
      73,   591,   297,   199,   592,    93,    96,   298,    48,    97,
     199,   220,   200,   201,   221,   325,    98,   234,   235,    73,
     326,    99,   100,   176,    50,   101,   244,   177,   178,   179,
     180,   181,   245,   182,   250,   198,   473,   474,   475,   476,
     477,   478,   274,   568,    73,   546,   547,   566,   569,   482,
     365,   366,   199,   685,   683,   686,   687,   684,   254,   641,
     519,   520,   521,   522,   523,   524,   278,    74,   539,    73,
     577,   570,    73,   577,   602,   578,    73,   255,   579,   603,
     538,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   362,   608,   612,   245,   294,   361,   609,   613,   614,
     669,   325,   711,   363,   297,   712,   672,   364,   147,   676,
     146,   259,   260,   169,   699,   327,   328,   163,    73,   700,
     170,   166,   261,   718,   148,   183,   149,   150,   719,   262,
     271,   288,   184,   223,   205,   289,   188,   308,   222,   309,
     224,   312,   316,   317,   225,   503,   504,   505,   506,   318,
     321,   320,   322,   329,   330,   331,   332,   333,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   354,   353,   355,   357,
     358,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   386,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   398,   415,   416,   399,   400,   401,
     402,   403,   404,   406,   409,   410,   407,   412,   418,   413,
     433,   414,   417,   419,   420,   421,   422,   423,   424,   425,
     486,   486,   426,   427,   431,   479,   479,   428,   429,   430,
     436,   435,   447,   437,   537,   438,   440,   362,   439,   441,
     446,   491,   361,   495,   499,   515,   554,   556,   560,   363,
     442,   574,   575,   364,   443,   444,   445,   448,   576,   581,
     582,   584,   585,   588,   587,   596,   595,   449,   594,   597,
     598,   599,   600,   465,   601,   466,   605,   606,   450,   452,
     607,   618,   619,   621,   622,   665,   624,   625,   627,   628,
     629,   651,   656,   657,   664,   453,   454,   564,   455,   659,
     552,   679,   456,   670,   671,   451,   677,   615,   697,   701,
     703,   467,   457,   458,   705,   707,   720,   468,   334,   459,
     356,   472,   460,   359,   633,   640,   490,   643,   461,   650,
     462,   642,   463,   464,   411,   713,   637,   616,   635,   634,
     636,   385,   405,   639,   638,   408,   630,   661,   631,   662,
     644,   632,   660,   387,   645,   646,   647,   648,   555,   663,
     655,   649,   658,   397,   626,   695,   704,   716,   721,   652,
       0,     0,     0,     0,   653,     0,   654,     0,   486,   702,
       0,     0,     0,   479,   147,     0,   146,   223,     0,   205,
       0,     0,   222,   163,   224,   666,   667,   166,   225,   236,
     148,   668,   149,   150,   673,   674,   675,   678,     0,     0,
       0,   706,     0,     0,   537,   722,     0,     0,     0,     0,
       0,     0,     0,   169,     0,     0,   183,     0,     0,     0,
     170,     0,     0,   184,     0,     0,     0,   188,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   689,     0,     0,     0,     0,   688,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     689,     0,     0,     0,     0,   688
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,    12,    59,    57,   428,    57,
      57,   419,   420,   425,   280,   280,     7,     5,    10,     7,
     428,     9,    12,    13,    15,    16,    21,     7,    21,     0,
      25,    37,    16,    17,    18,     3,   104,    28,    29,    30,
       8,    47,    33,    34,    35,    38,    37,    40,    41,     7,
      43,    44,    45,    37,    38,    46,     7,    48,    49,    50,
      51,    52,    53,     7,     3,     3,    57,    58,     3,     8,
       8,    11,    56,    64,    14,    15,    16,    57,     7,    19,
      20,     3,    77,    78,    79,    80,     8,     7,    28,    29,
      30,    31,    32,     7,    86,     6,    36,    37,   104,     4,
      92,    93,    67,    68,    16,    17,    18,     3,     7,   104,
       6,   104,   104,   104,    54,    55,   104,   105,   106,   107,
     104,     3,     3,    38,     6,    37,    66,     8,     7,    69,
      38,    39,    40,    41,    42,     3,    76,    67,    68,   104,
       8,    81,    82,    55,     7,    85,     8,    59,    60,    61,
      62,    63,     3,    65,     4,    21,    22,    23,    24,    25,
      26,    27,     3,     3,   104,    83,    84,     8,     8,   577,
     436,   436,    38,    88,     3,    90,    91,     6,     4,   591,
      70,    71,    72,    73,    74,    75,     3,   251,   608,   104,
       3,     8,   104,     3,     3,     8,   104,     4,     8,     8,
     608,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   280,     3,     3,     3,     3,   280,     8,     8,     8,
       8,     3,     3,   280,     3,     6,     8,   280,   294,     8,
     294,     4,     4,   297,     3,   242,   243,   294,   104,     8,
     297,   294,     4,     3,   294,   309,   294,   294,     8,     4,
       4,     4,   309,   322,   318,     4,   309,     8,   322,     3,
     322,     4,     4,     8,   322,    59,    60,    61,    62,     3,
       8,     4,     3,   104,     4,     4,     4,     4,     4,   107,
     107,     4,     4,     4,   105,   105,   105,   105,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   105,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   105,   107,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   332,   333,     4,   105,     4,
       4,     4,   107,     4,     4,     4,   107,     4,   104,     7,
     104,     7,     7,     7,     7,     5,     5,     5,     5,     5,
     419,   420,     5,     7,     5,   419,   420,     7,     7,     7,
       3,     8,     7,   104,   428,   104,     5,   436,   104,   104,
       5,     7,   436,     7,     7,     7,     4,     7,     7,   436,
     104,     4,     4,   436,   104,   104,   104,   104,     4,     6,
       3,     6,     3,     3,     6,     4,     3,   104,     6,     4,
       4,     4,     4,   410,     4,   412,     4,     4,   104,   104,
       4,     6,     3,     6,     3,     5,     8,     4,     4,     4,
       4,     4,     4,     4,     4,   104,   104,    65,   104,     6,
     430,     7,   104,     8,     8,   390,     8,   553,     4,     4,
       4,   413,   104,   104,     5,     7,     4,    87,   251,   104,
     274,   417,   104,   278,   577,   589,   420,   595,   104,   602,
     104,   593,   104,   104,   325,    89,   585,   104,   582,   580,
     583,   294,   318,   588,   586,   322,   107,   619,   105,   620,
     105,   107,   617,   297,   105,   105,   105,   105,   436,   622,
     608,   105,   612,   309,   568,   683,   699,   711,   718,   105,
      -1,    -1,    -1,    -1,   105,    -1,   105,    -1,   577,   105,
      -1,    -1,    -1,   577,   580,    -1,   580,   586,    -1,   583,
      -1,    -1,   586,   580,   586,   104,   104,   580,   586,   593,
     580,   104,   580,   580,   104,   104,   104,   104,    -1,    -1,
      -1,   104,    -1,    -1,   608,   104,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   617,    -1,    -1,   620,    -1,    -1,    -1,
     617,    -1,    -1,   620,    -1,    -1,    -1,   620,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   682,    -1,    -1,    -1,    -1,   682,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     699,    -1,    -1,    -1,    -1,   699
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,     0,     5,     7,     9,   104,   105,   106,   107,
     120,   121,   122,   126,     7,   133,     7,   139,     7,   153,
       7,   216,     7,   284,     7,   296,     7,   244,     7,   267,
       7,   192,   127,   123,   134,   140,   154,   217,   285,   297,
     245,   268,   193,   120,   130,   131,   104,   124,   125,    10,
      86,    92,    93,   104,   132,   135,   136,   137,   355,   357,
     359,    11,    14,    15,    16,    19,    20,    28,    29,    30,
      31,    32,    36,    37,    54,    55,    66,    69,    76,    81,
      82,    85,   132,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   159,   161,   179,   186,   200,   210,   238,   261,
     301,   325,   335,   344,   345,   353,    12,    13,   151,   152,
     155,   157,     7,    33,    34,    35,    46,    48,    49,    50,
      51,    52,    53,    57,    58,    64,   132,   143,   144,   145,
     148,   218,   219,   220,   222,   224,   226,   228,   230,   232,
     234,   236,   237,   261,   278,   290,   301,   321,    47,   132,
     261,   286,   287,   288,    17,    18,    55,    59,    60,    61,
      62,    63,    65,   132,   261,   298,   299,   300,   301,   303,
     305,   307,   309,   311,   313,   315,   317,   319,    21,    38,
      40,    41,    43,    44,    45,   132,   165,   173,   246,   247,
     248,   249,   250,   251,   252,   253,   255,   257,   258,   260,
      39,    42,   132,   173,   250,   255,   269,   270,   271,   272,
     273,   275,   276,   277,    67,    68,   132,   194,   195,   196,
     198,     6,     3,     4,     8,     3,   138,   360,   356,   358,
       4,     3,     8,   150,     4,     4,   302,   160,   162,     4,
       4,     4,     4,   211,   239,   262,   180,   326,   187,   201,
     336,     4,   346,   354,     3,     8,   156,   158,     3,     8,
     328,   223,   225,   227,   279,   221,   229,   231,     4,     4,
     235,   233,   291,   322,     3,     8,   289,     3,     8,   304,
     306,   320,   310,   312,   316,   314,   318,   308,     8,     3,
     166,   174,     4,   256,   254,   259,     4,     8,     3,   274,
       4,     8,     3,   197,   199,     3,     8,   120,   120,   104,
       4,     4,     4,     4,   136,     4,   107,   107,     4,     4,
       4,   105,   105,   105,   105,     4,     4,     4,     4,     4,
       4,     4,     4,   105,     4,     4,   142,     4,     4,   152,
      56,   132,   173,   261,   301,   303,   305,   329,   330,   331,
     332,   333,     4,     4,     4,     4,     4,     4,     4,   105,
     107,     4,     4,     4,     4,   219,     4,   287,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   300,     4,     4,
     105,     4,     4,     4,   107,   248,     4,   107,   271,     4,
       4,   195,     4,     7,     7,   120,   120,     7,   104,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   128,   104,   334,     8,     3,   104,   104,   104,
       5,   104,   104,   104,   104,   104,     5,     7,   104,   104,
     104,   128,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   120,   120,   141,    87,   361,
     362,   363,   151,    22,    23,    24,    25,    26,    27,   132,
     163,   164,   165,   167,   169,   171,   173,   175,   176,   177,
     163,     7,   212,   213,   214,     7,   240,   241,   242,     7,
     263,   264,   265,    59,    60,    61,    62,   178,   181,   182,
     183,   184,   185,   232,   327,     7,   188,   189,   190,    70,
      71,    72,    73,    74,    75,   202,   203,   204,   205,   206,
     207,   208,   209,    77,    78,    79,    80,   132,   165,   175,
     337,   338,   339,   340,   342,   343,    83,    84,   347,   348,
     349,   351,   125,   129,     4,   331,     7,   280,   281,   282,
       7,   292,   293,   294,    65,   323,     8,   364,     3,     8,
       8,   168,   170,   172,     4,     4,     4,     3,     8,     8,
     215,     6,     3,   243,     6,     3,   266,     6,     3,     3,
       6,     3,     6,   191,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   341,     4,     4,     4,     3,     8,
     350,   352,     3,     8,     8,   130,   104,   283,     6,     3,
     295,     6,     3,   324,     8,     4,   362,     4,     4,     4,
     107,   105,   107,   164,   218,   214,   246,   242,   269,   265,
     182,   232,   194,   190,   105,   105,   105,   105,   105,   105,
     203,     4,   105,   105,   105,   338,     4,     4,   348,     6,
     286,   282,   298,   294,     4,     5,   104,   104,   104,     8,
       8,     8,     8,   104,   104,   104,     8,     8,   104,     7,
     365,   366,   367,     3,     6,    88,    90,    91,   132,   173,
     368,   369,   370,   371,   373,   366,   374,     4,   372,     3,
       8,     4,   105,     4,   369,     5,   104,     7,   375,   376,
     377,     3,     6,    89,   378,   379,   376,   380,     3,     8,
       4,   379,   104
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   108,   110,   109,   111,   109,   112,   109,   113,   109,
     114,   109,   115,   109,   116,   109,   117,   109,   118,   109,
     119,   109,   120,   120,   120,   120,   120,   120,   120,   121,
     123,   122,   124,   124,   125,   125,   127,   126,   129,   128,
     130,   130,   131,   131,   132,   134,   133,   135,   135,   136,
     136,   136,   136,   136,   138,   137,   140,   139,   141,   141,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   143,   144,   145,   146,   147,   148,   150,   149,
     151,   151,   152,   152,   154,   153,   156,   155,   158,   157,
     160,   159,   162,   161,   163,   163,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   166,   165,   168,   167,   170,
     169,   172,   171,   174,   173,   175,   176,   177,   178,   180,
     179,   181,   181,   182,   182,   182,   182,   183,   184,   185,
     187,   186,   188,   188,   189,   189,   191,   190,   193,   192,
     194,   194,   194,   195,   195,   197,   196,   199,   198,   201,
     200,   202,   202,   203,   203,   203,   203,   203,   203,   204,
     205,   206,   207,   208,   209,   211,   210,   212,   212,   213,
     213,   215,   214,   217,   216,   218,   218,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   221,   220,   223,
     222,   225,   224,   227,   226,   229,   228,   231,   230,   233,
     232,   235,   234,   236,   237,   239,   238,   240,   240,   241,
     241,   243,   242,   245,   244,   246,   246,   247,   247,   248,
     248,   248,   248,   248,   248,   248,   248,   249,   250,   251,
     252,   254,   253,   256,   255,   257,   259,   258,   260,   262,
     261,   263,   263,   264,   264,   266,   265,   268,   267,   269,
     269,   270,   270,   271,   271,   271,   271,   271,   271,   272,
     274,   273,   275,   276,   277,   279,   278,   280,   280,   281,
     281,   283,   282,   285,   284,   286,   286,   287,   287,   287,
     289,   288,   291,   290,   292,   292,   293,   293,   295,   294,
     297,   296,   298,   298,   299,   299,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   302,   301,
     304,   303,   306,   305,   308,   307,   310,   309,   312,   311,
     314,   313,   316,   315,   318,   317,   320,   319,   322,   321,
     324,   323,   326,   325,   327,   327,   328,   232,   329,   329,
     330,   330,   331,   331,   331,   331,   331,   331,   331,   332,
     334,   333,   336,   335,   337,   337,   338,   338,   338,   338,
     338,   338,   338,   339,   341,   340,   342,   343,   344,   346,
     345,   347,   347,   348,   348,   350,   349,   352,   351,   354,
     353,   356,   355,   358,   357,   360,   359,   361,   361,   362,
     364,   363,   365,   365,   367,   366,   368,   368,   369,   369,
     369,   369,   369,   370,   372,   371,   374,   373,   375,   375,
     377,   376,   378,   378,   380,   379
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
       0,     6,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     1,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"echo-client-id\"", "\"match-client-id\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"type\"", "\"user\"", "\"password\"", "\"host\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"valid-lifetime\"",
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
  "lease_database", "$@21", "hosts_database", "$@22",
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
  "control_socket_param", "socket_type", "$@81", "socket_name", "$@82",
  "dhcp_ddns", "$@83", "dhcp6_json_object", "$@84", "dhcpddns_json_object",
  "$@85", "logging_object", "$@86", "logging_params", "logging_param",
  "loggers", "$@87", "loggers_entries", "logger_entry", "$@88",
  "logger_params", "logger_param", "debuglevel", "severity", "$@89",
  "output_options_list", "$@90", "output_options_list_content",
  "output_entry", "$@91", "output_params", "output_param", "$@92", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   204,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   209,   209,   210,   210,   211,   211,   212,   212,
     213,   213,   221,   222,   223,   224,   225,   226,   227,   230,
     235,   235,   247,   248,   251,   255,   262,   262,   270,   270,
     277,   278,   281,   285,   296,   306,   306,   318,   319,   323,
     324,   325,   326,   327,   330,   330,   347,   347,   355,   356,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   385,   390,   395,   400,   405,   410,   416,   416,
     426,   427,   430,   431,   434,   434,   442,   442,   452,   452,
     460,   460,   470,   470,   480,   481,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   495,   495,   503,   503,   511,
     511,   519,   519,   527,   527,   535,   540,   545,   550,   555,
     555,   565,   566,   569,   570,   571,   572,   575,   580,   585,
     590,   590,   600,   601,   604,   605,   608,   608,   616,   616,
     624,   625,   626,   629,   630,   633,   633,   641,   641,   649,
     649,   659,   660,   663,   664,   665,   666,   667,   668,   671,
     676,   681,   686,   691,   696,   704,   704,   717,   718,   721,
     722,   729,   729,   752,   752,   761,   762,   766,   767,   768,
     769,   770,   771,   772,   773,   774,   775,   776,   777,   778,
     779,   780,   781,   782,   783,   784,   785,   788,   788,   796,
     796,   804,   804,   812,   812,   820,   820,   828,   828,   836,
     836,   844,   844,   852,   857,   866,   866,   878,   879,   882,
     883,   888,   888,   899,   899,   909,   910,   913,   914,   917,
     918,   919,   920,   921,   922,   923,   924,   927,   929,   934,
     936,   938,   938,   946,   946,   954,   956,   956,   964,   973,
     973,   985,   986,   991,   992,   997,   997,  1008,  1008,  1019,
    1020,  1025,  1026,  1031,  1032,  1033,  1034,  1035,  1036,  1039,
    1041,  1041,  1049,  1051,  1053,  1061,  1061,  1073,  1074,  1077,
    1078,  1081,  1081,  1089,  1089,  1097,  1098,  1101,  1102,  1103,
    1106,  1106,  1117,  1117,  1127,  1128,  1131,  1132,  1135,  1135,
    1143,  1143,  1151,  1152,  1155,  1156,  1160,  1161,  1162,  1163,
    1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1174,  1174,
    1182,  1182,  1190,  1190,  1198,  1198,  1206,  1206,  1214,  1214,
    1222,  1222,  1230,  1230,  1239,  1239,  1247,  1247,  1260,  1260,
    1270,  1270,  1281,  1281,  1291,  1292,  1295,  1295,  1303,  1304,
    1307,  1308,  1311,  1312,  1313,  1314,  1315,  1316,  1317,  1320,
    1322,  1322,  1333,  1333,  1343,  1344,  1347,  1348,  1349,  1350,
    1351,  1352,  1353,  1356,  1361,  1361,  1369,  1374,  1381,  1388,
    1388,  1398,  1399,  1402,  1403,  1406,  1406,  1414,  1414,  1424,
    1424,  1436,  1436,  1443,  1443,  1455,  1455,  1468,  1469,  1473,
    1477,  1477,  1489,  1490,  1494,  1494,  1502,  1503,  1506,  1507,
    1508,  1509,  1510,  1513,  1517,  1517,  1525,  1525,  1535,  1536,
    1539,  1539,  1547,  1548,  1551,  1551
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
#line 3561 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1559 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
