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

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 352 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 99: // "integer"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 359 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 100: // "floating point"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 101: // "boolean"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 114: // value

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 114: // value
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
#line 198 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 199 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 200 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 201 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 202 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 203 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 331 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr type(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-socket-type", type);
    ctx.leave();
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 867 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1661 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1707 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1903 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1263 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2439 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2504 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2534 "dhcp4_parser.cc" // lalr1.cc:859
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
     187,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    32,    20,    73,    80,   106,   110,   122,   123,   126,
     134,   153,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,    20,    64,    18,    95,    56,    24,    -4,    30,
     146,   115,   -33,  -411,   179,   193,   212,   198,   215,  -411,
    -411,  -411,  -411,   216,  -411,    34,  -411,  -411,  -411,  -411,
    -411,  -411,   218,   219,  -411,  -411,  -411,   220,   227,   228,
     230,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   231,
    -411,  -411,  -411,    41,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,    42,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     232,   235,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    48,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    52,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,   207,   238,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     244,  -411,  -411,  -411,   245,  -411,  -411,  -411,   234,   249,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   254,  -411,  -411,  -411,  -411,   251,   250,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,    63,  -411,  -411,
    -411,  -411,    20,    20,  -411,   162,   257,   261,   263,   265,
    -411,    18,  -411,   267,   171,   172,   281,   282,   283,   190,
     191,   192,   194,   284,   288,   290,   291,   292,   293,   294,
     295,   203,   296,   297,    95,  -411,   299,   300,    56,  -411,
      46,   301,   302,   303,   304,   305,   306,   307,   213,   214,
     309,   310,   312,   313,    24,  -411,   314,    -4,  -411,   315,
     316,   317,   318,   319,   320,   321,   322,   323,  -411,    30,
     324,   325,   233,   326,   327,   329,   236,  -411,   146,   330,
     237,  -411,   115,   335,   336,    11,  -411,  -411,  -411,   337,
     338,   339,    20,    20,  -411,   340,  -411,  -411,   246,   341,
     342,  -411,  -411,  -411,  -411,   345,   346,   347,   348,   349,
     350,   351,   352,  -411,   355,   356,  -411,   359,   258,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   334,   354,  -411,
    -411,  -411,   269,   270,   271,   365,   273,   274,   275,  -411,
    -411,   277,   278,   373,   372,  -411,   285,  -411,   286,   287,
     359,   289,   298,   308,   311,   328,   331,  -411,   332,   333,
    -411,   343,   344,   353,  -411,  -411,   357,  -411,  -411,   358,
      20,  -411,    20,    95,   262,  -411,  -411,    56,  -411,   113,
     113,   374,   379,   381,   168,    29,   383,   360,   127,    98,
      64,  -411,  -411,  -411,   376,  -411,    46,  -411,  -411,  -411,
     384,  -411,  -411,  -411,  -411,  -411,   385,   362,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,    93,  -411,   100,
    -411,  -411,   104,  -411,  -411,  -411,   390,   391,   393,  -411,
     139,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     155,  -411,   392,   396,  -411,  -411,   394,   398,  -411,  -411,
     397,   399,  -411,  -411,  -411,  -411,  -411,  -411,    35,  -411,
    -411,  -411,  -411,  -411,    94,  -411,   401,   402,  -411,   400,
     169,  -411,  -411,   404,   406,   407,  -411,  -411,  -411,   170,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   180,  -411,  -411,
    -411,   199,    20,   361,  -411,  -411,   408,   409,  -411,  -411,
     410,   414,  -411,  -411,   411,  -411,   416,   262,  -411,  -411,
     417,   418,   419,   363,   364,   366,   113,  -411,  -411,    24,
    -411,   374,   146,  -411,   379,   115,  -411,   381,   168,  -411,
      29,  -411,   -33,  -411,   383,   367,   360,  -411,   420,   369,
     370,   371,   127,  -411,   421,   424,    98,  -411,  -411,   412,
    -411,    -4,  -411,   384,    30,  -411,   385,   428,  -411,   429,
    -411,   375,   377,   378,  -411,  -411,  -411,  -411,   200,  -411,
     425,  -411,   427,  -411,  -411,  -411,   201,  -411,  -411,  -411,
     380,  -411,  -411,  -411,  -411,   382,   386,  -411,  -411,   202,
    -411,   430,  -411,   387,   432,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   163,
    -411,    61,   432,  -411,  -411,   433,  -411,  -411,  -411,   209,
    -411,  -411,  -411,  -411,  -411,   436,   388,   439,    61,  -411,
     431,  -411,   395,  -411,   437,  -411,  -411,   189,  -411,   389,
     437,  -411,  -411,   211,  -411,  -411,   441,   389,  -411,   403,
    -411,  -411
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    94,     9,
     172,    11,   282,    13,   299,    15,   222,    17,   256,    19,
     148,    21,    40,    32,     0,     0,     0,     0,     0,   301,
     224,   258,     0,    42,     0,    41,     0,     0,    33,    54,
     394,   390,   392,     0,    53,     0,    47,    49,    51,    52,
      50,    88,     0,     0,   317,   100,   102,     0,     0,     0,
       0,   164,   214,   248,   129,   341,   140,   159,   361,     0,
     378,   388,    81,     0,    58,    60,    61,    62,    63,    78,
      79,    65,    66,    67,    68,    72,    73,    64,    70,    71,
      80,    69,    74,    75,    76,    77,    96,    98,     0,    90,
      92,    93,   345,   198,   200,   202,   274,   196,   204,   206,
       0,     0,   210,   208,   291,   337,   195,   176,   177,   178,
     190,     0,   174,   181,   192,   193,   194,   182,   183,   186,
     188,   184,   185,   179,   180,   187,   191,   189,   289,   288,
     287,     0,   284,   286,   319,   321,   335,   325,   327,   331,
     329,   333,   323,   316,   312,     0,   302,   303,   313,   314,
     315,   309,   305,   310,   307,   308,   311,   306,   115,   123,
       0,   242,   240,   245,     0,   235,   239,   236,     0,   225,
     226,   228,   238,   229,   230,   231,   244,   232,   233,   234,
     269,     0,   267,   268,   271,   272,     0,   259,   260,   262,
     263,   264,   265,   266,   155,   157,   152,     0,   150,   153,
     154,    37,     0,     0,    31,     0,     0,     0,     0,     0,
      44,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    95,
     347,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   173,     0,     0,   283,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   300,     0,
       0,     0,     0,     0,     0,     0,     0,   223,     0,     0,
       0,   257,     0,     0,     0,     0,   149,    43,    34,     0,
       0,     0,     0,     0,    48,     0,    86,    87,     0,     0,
       0,    82,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,   377,     0,     0,    59,     0,     0,    91,
     359,   357,   358,   353,   354,   355,   356,     0,   348,   349,
     351,   352,     0,     0,     0,     0,     0,     0,     0,   212,
     213,     0,     0,     0,     0,   175,     0,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   304,     0,     0,
     237,     0,     0,     0,   247,   227,     0,   273,   261,     0,
       0,   151,     0,     0,     0,   391,   393,     0,   318,     0,
       0,   166,   216,   250,     0,     0,   142,     0,     0,     0,
       0,    38,    97,    99,     0,   346,     0,   199,   201,   203,
     276,   197,   205,   207,   211,   209,   293,     0,   290,   320,
     322,   336,   326,   328,   332,   330,   334,   324,   116,   124,
     243,   241,   246,   270,   156,   158,    35,     0,   399,     0,
     396,   398,     0,   117,   119,   121,     0,     0,     0,   114,
       0,   104,   106,   107,   108,   109,   110,   111,   112,   113,
       0,   170,     0,   167,   168,   220,     0,   217,   218,   254,
       0,   251,   252,   128,   137,   138,   139,   133,     0,   131,
     134,   135,   136,   343,     0,   146,     0,   143,   144,     0,
       0,   161,   373,     0,     0,     0,   371,   365,   370,     0,
     363,   368,   366,   367,   369,   384,   386,     0,   380,   382,
     383,     0,    40,     0,   350,   280,     0,   277,   278,   297,
       0,   294,   295,   339,     0,    55,     0,     0,   395,    89,
       0,     0,     0,     0,     0,     0,     0,   101,   103,     0,
     165,     0,   224,   215,     0,   258,   249,     0,     0,   130,
       0,   342,     0,   141,     0,     0,     0,   160,     0,     0,
       0,     0,     0,   362,     0,     0,     0,   379,   389,     0,
     360,     0,   275,     0,   301,   292,     0,     0,   338,     0,
     397,     0,     0,     0,   125,   126,   127,   105,     0,   169,
       0,   219,     0,   253,   132,   344,     0,   145,   163,   162,
       0,   372,   375,   376,   364,     0,     0,   381,    39,     0,
     279,     0,   296,     0,     0,   118,   120,   122,   171,   221,
     255,   147,   374,   385,   387,   281,   298,   340,   403,     0,
     401,     0,     0,   400,   415,     0,   413,   411,   407,     0,
     405,   409,   410,   408,   402,     0,     0,     0,     0,   404,
       0,   412,     0,   406,     0,   414,   419,     0,   417,     0,
       0,   416,   423,     0,   421,   418,     0,     0,   420,     0,
     422,   424
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,     3,  -411,  -411,  -411,  -411,    16,  -411,  -411,
      57,  -411,   -94,  -411,   -54,  -411,  -411,  -411,   206,  -411,
    -411,  -411,  -411,    36,   176,   -56,   -40,   -38,  -411,  -411,
     -37,  -411,  -411,    37,   174,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,    33,  -106,  -398,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,   -59,  -411,  -410,  -411,  -411,
    -411,  -411,  -411,  -411,  -117,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -122,  -411,  -411,  -411,  -111,   140,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -112,  -411,  -411,  -411,  -411,
     -92,  -411,  -411,  -411,   -88,   183,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -399,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   -91,  -411,
    -411,  -411,   -90,  -411,   173,  -411,   -52,  -411,  -411,  -411,
    -411,   -48,  -411,  -411,  -411,  -411,  -411,   -47,  -411,  -411,
    -411,   -89,  -411,  -411,  -411,   -86,  -411,   164,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -113,  -411,
    -411,  -411,  -109,   197,  -411,  -411,  -411,  -411,  -411,  -411,
    -110,  -411,  -411,  -411,  -107,  -411,   186,   -43,  -411,  -257,
    -411,  -256,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,    62,  -411,  -411,
    -411,  -411,  -411,  -411,   -93,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,   -96,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   -55,  -411,
    -411,  -411,  -159,  -411,  -411,  -174,  -411,  -411,  -411,  -411,
    -411,  -411,  -185,  -411,  -411,  -191,  -411
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,    67,    68,    33,    52,
     432,   542,    64,    65,   102,    35,    54,    75,    76,    77,
     246,    37,    55,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   253,   128,   129,    39,    56,   130,   276,   131,
     277,   112,   257,   113,   258,   480,   481,   206,   310,   483,
     560,   484,   561,   485,   562,   207,   311,   487,   488,   489,
     507,   114,   266,   508,   509,   510,   511,   512,   115,   268,
     516,   517,   518,   582,    51,    62,   237,   238,   239,   323,
     240,   324,   116,   269,   520,   521,   117,   263,   492,   493,
     494,   569,    41,    57,   151,   152,   153,   285,   154,   281,
     155,   282,   156,   283,   157,   286,   158,   287,   159,   291,
     160,   290,   161,   162,   118,   264,   496,   497,   498,   572,
      47,    60,   208,   209,   210,   211,   212,   213,   214,   215,
     314,   216,   313,   217,   218,   315,   219,   119,   265,   500,
     501,   502,   575,    49,    61,   226,   227,   228,   229,   230,
     319,   231,   232,   233,   164,   284,   546,   547,   548,   601,
      43,    58,   171,   172,   173,   296,   165,   292,   550,   551,
     552,   604,    45,    59,   185,   186,   187,   120,   256,   189,
     299,   190,   300,   191,   307,   192,   302,   193,   303,   194,
     305,   195,   304,   196,   306,   197,   301,   167,   293,   554,
     607,   121,   267,   514,   280,   367,   368,   369,   370,   371,
     434,   122,   270,   529,   530,   531,   532,   588,   533,   534,
     123,   124,   272,   537,   538,   539,   594,   540,   595,   125,
     273,    78,   248,    79,   249,    80,   247,   469,   470,   471,
     556,   659,   660,   661,   669,   670,   671,   672,   677,   673,
     675,   687,   688,   689,   693,   694,   696
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   147,   223,   146,   169,   183,   205,   222,   236,   224,
     163,   170,   184,   225,   166,    30,   188,   148,   528,   149,
     150,   482,   482,   365,   366,    23,   513,    24,    69,    25,
     527,   132,    22,    93,   234,   235,   132,   251,   578,    83,
      84,   579,   252,   168,   274,   278,    84,   174,   175,   275,
     279,   294,    87,    88,    89,   297,   295,   133,   134,   135,
     298,    93,    84,   174,   175,    73,   325,    93,   126,   127,
     136,   326,   137,   138,   139,   140,   141,   142,   234,   235,
      34,   143,   144,    93,   199,   176,   143,    36,   145,   177,
     178,   179,   180,   181,    73,   182,   274,   580,    70,   199,
     581,   555,   360,   557,    71,    72,    81,   278,   558,    82,
      83,    84,   559,    38,    85,    86,    73,    40,    26,    27,
      28,    29,    73,    87,    88,    89,    90,    91,    73,    42,
      44,    92,    93,    46,   198,   473,   474,   475,   476,   477,
     478,    48,   566,   664,    73,   665,   666,   567,   198,    94,
      95,   199,   476,   199,   220,   200,   201,   221,   566,    73,
      50,    96,    66,   568,    97,    98,   662,   198,   482,   663,
      99,   100,   586,   592,   101,   535,   536,   587,   593,   365,
     366,   625,   528,   596,   199,   241,   200,   201,   597,   202,
     203,   204,   690,    73,   527,   691,   242,    74,   522,   523,
     524,   525,   245,   294,   325,   297,   244,   598,   648,   651,
     655,    73,   678,    73,   697,   308,   243,   679,   245,   698,
     250,   362,   254,   255,   259,    73,   361,   503,   504,   505,
     506,   260,   261,   363,   262,   271,   288,   364,   147,   289,
     146,   309,   317,   169,    73,   327,   328,   163,   312,   316,
     170,   166,   318,   322,   148,   183,   149,   150,   320,   321,
     329,   330,   184,   223,   205,   331,   188,   332,   222,   333,
     224,   335,   336,   337,   225,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,   338,   339,   340,   345,   341,
     342,   343,   346,   344,   347,   348,   349,   350,   351,   352,
     354,   355,   353,   357,   358,   372,   373,   374,   375,   376,
     377,   378,   379,   381,   382,   380,   383,   384,   386,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   398,   399,
     401,   402,   400,   403,   406,   415,   416,   404,   407,   409,
     410,   412,   435,   468,   418,   413,   414,   417,   419,   420,
     421,   422,   423,   424,   425,   426,   433,   436,   427,   428,
     486,   486,   429,   430,   431,   479,   479,   437,   438,   439,
     440,   441,   442,   443,   526,   444,   445,   362,   446,   447,
     543,   491,   361,   448,   449,   450,   495,   452,   499,   363,
     515,   545,   549,   364,   563,   564,   453,   565,   570,   571,
     573,   574,   577,   576,   585,   584,   454,   583,   589,   455,
     590,   591,   603,   465,   602,   466,   605,   606,   638,   608,
     609,   611,   612,   613,   630,   635,   456,   553,   636,   457,
     458,   459,   643,   649,   644,   650,   684,   676,   656,   658,
     680,   460,   461,   682,   686,   699,   541,   451,   599,   467,
     356,   462,   359,   490,   472,   463,   464,   334,   519,   600,
     617,   624,   627,   615,   614,   411,   628,   616,   631,   632,
     633,   626,   692,   645,   629,   646,   647,   385,   652,   619,
     653,   618,   620,   621,   654,   657,   408,   681,   623,   622,
     640,   405,   639,   685,   387,   397,   642,   641,   544,   634,
     637,   701,   610,   674,   683,   695,   700,   486,     0,     0,
       0,     0,   479,   147,     0,   146,   223,     0,   205,     0,
       0,   222,   163,   224,     0,     0,   166,   225,   236,   148,
       0,   149,   150,     0,     0,     0,     0,     0,   526,     0,
       0,     0,     0,     0,     0,     0,     0,   169,     0,     0,
     183,     0,     0,     0,   170,     0,     0,   184,     0,     0,
       0,   188,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   668,     0,     0,     0,     0,   667,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   668,
       0,     0,     0,     0,   667
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,    12,    59,    57,   428,    57,
      57,   419,   420,   280,   280,     5,   425,     7,    10,     9,
     428,     7,     0,    37,    67,    68,     7,     3,     3,    15,
      16,     6,     8,    47,     3,     3,    16,    17,    18,     8,
       8,     3,    28,    29,    30,     3,     8,    33,    34,    35,
       8,    37,    16,    17,    18,    98,     3,    37,    12,    13,
      46,     8,    48,    49,    50,    51,    52,    53,    67,    68,
       7,    57,    58,    37,    38,    55,    57,     7,    64,    59,
      60,    61,    62,    63,    98,    65,     3,     3,    80,    38,
       6,     8,    56,     3,    86,    87,    11,     3,     8,    14,
      15,    16,     8,     7,    19,    20,    98,     7,    98,    99,
     100,   101,    98,    28,    29,    30,    31,    32,    98,     7,
       7,    36,    37,     7,    21,    22,    23,    24,    25,    26,
      27,     7,     3,    82,    98,    84,    85,     8,    21,    54,
      55,    38,    25,    38,    39,    40,    41,    42,     3,    98,
       7,    66,    98,     8,    69,    70,     3,    21,   566,     6,
      75,    76,     3,     3,    79,    77,    78,     8,     8,   436,
     436,   580,   592,     3,    38,     6,    40,    41,     8,    43,
      44,    45,     3,    98,   592,     6,     3,   251,    71,    72,
      73,    74,     3,     3,     3,     3,     8,     8,     8,     8,
       8,    98,     3,    98,     3,     8,     4,     8,     3,     8,
       4,   280,     4,     4,     4,    98,   280,    59,    60,    61,
      62,     4,     4,   280,     4,     4,     4,   280,   294,     4,
     294,     3,     8,   297,    98,   242,   243,   294,     4,     4,
     297,   294,     3,     3,   294,   309,   294,   294,     4,     8,
      98,     4,   309,   322,   318,     4,   309,     4,   322,     4,
     322,     4,   101,   101,   322,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,     4,     4,     4,     4,    99,
      99,    99,     4,    99,     4,     4,     4,     4,     4,     4,
       4,     4,    99,     4,     4,     4,     4,     4,     4,     4,
       4,     4,    99,     4,     4,   101,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,    99,     4,     4,   332,   333,   101,   101,     4,
       4,     4,     8,    81,    98,     7,     7,     7,     7,     7,
       5,     5,     5,     5,     5,     5,    98,     3,     7,     7,
     419,   420,     7,     7,     5,   419,   420,    98,    98,    98,
       5,    98,    98,    98,   428,    98,    98,   436,     5,     7,
       4,     7,   436,    98,    98,    98,     7,    98,     7,   436,
       7,     7,     7,   436,     4,     4,    98,     4,     6,     3,
       6,     3,     3,     6,     4,     3,    98,     6,     4,    98,
       4,     4,     3,   410,     6,   412,     6,     3,     6,     8,
       4,     4,     4,     4,     4,     4,    98,    65,     4,    98,
      98,    98,     4,     8,     5,     8,     5,     4,     8,     7,
       4,    98,    98,     4,     7,     4,   430,   390,   542,   413,
     274,    98,   278,   420,   417,    98,    98,   251,    98,    98,
     566,   578,   584,    99,   101,   325,    99,   101,    99,    99,
      99,   582,    83,    98,   586,    98,    98,   294,    98,   571,
      98,   569,   572,   574,    98,    98,   322,    99,   577,   575,
     603,   318,   601,    98,   297,   309,   606,   604,   436,   592,
     596,    98,   557,   662,   678,   690,   697,   566,    -1,    -1,
      -1,    -1,   566,   569,    -1,   569,   575,    -1,   572,    -1,
      -1,   575,   569,   575,    -1,    -1,   569,   575,   582,   569,
      -1,   569,   569,    -1,    -1,    -1,    -1,    -1,   592,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   601,    -1,    -1,
     604,    -1,    -1,    -1,   601,    -1,    -1,   604,    -1,    -1,
      -1,   604,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   661,    -1,    -1,    -1,    -1,   661,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   678,
      -1,    -1,    -1,    -1,   678
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     0,     5,     7,     9,    98,    99,   100,   101,
     114,   115,   116,   120,     7,   127,     7,   133,     7,   147,
       7,   204,     7,   272,     7,   284,     7,   232,     7,   255,
       7,   186,   121,   117,   128,   134,   148,   205,   273,   285,
     233,   256,   187,   114,   124,   125,    98,   118,   119,    10,
      80,    86,    87,    98,   126,   129,   130,   131,   343,   345,
     347,    11,    14,    15,    16,    19,    20,    28,    29,    30,
      31,    32,    36,    37,    54,    55,    66,    69,    70,    75,
      76,    79,   126,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   153,   155,   173,   180,   194,   198,   226,   249,
     289,   313,   323,   332,   333,   341,    12,    13,   145,   146,
     149,   151,     7,    33,    34,    35,    46,    48,    49,    50,
      51,    52,    53,    57,    58,    64,   126,   137,   138,   139,
     142,   206,   207,   208,   210,   212,   214,   216,   218,   220,
     222,   224,   225,   249,   266,   278,   289,   309,    47,   126,
     249,   274,   275,   276,    17,    18,    55,    59,    60,    61,
      62,    63,    65,   126,   249,   286,   287,   288,   289,   291,
     293,   295,   297,   299,   301,   303,   305,   307,    21,    38,
      40,    41,    43,    44,    45,   126,   159,   167,   234,   235,
     236,   237,   238,   239,   240,   241,   243,   245,   246,   248,
      39,    42,   126,   167,   238,   243,   257,   258,   259,   260,
     261,   263,   264,   265,    67,    68,   126,   188,   189,   190,
     192,     6,     3,     4,     8,     3,   132,   348,   344,   346,
       4,     3,     8,   144,     4,     4,   290,   154,   156,     4,
       4,     4,     4,   199,   227,   250,   174,   314,   181,   195,
     324,     4,   334,   342,     3,     8,   150,   152,     3,     8,
     316,   211,   213,   215,   267,   209,   217,   219,     4,     4,
     223,   221,   279,   310,     3,     8,   277,     3,     8,   292,
     294,   308,   298,   300,   304,   302,   306,   296,     8,     3,
     160,   168,     4,   244,   242,   247,     4,     8,     3,   262,
       4,     8,     3,   191,   193,     3,     8,   114,   114,    98,
       4,     4,     4,     4,   130,     4,   101,   101,     4,     4,
       4,    99,    99,    99,    99,     4,     4,     4,     4,     4,
       4,     4,     4,    99,     4,     4,   136,     4,     4,   146,
      56,   126,   167,   249,   289,   291,   293,   317,   318,   319,
     320,   321,     4,     4,     4,     4,     4,     4,     4,    99,
     101,     4,     4,     4,     4,   207,     4,   275,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   288,     4,     4,
      99,     4,     4,     4,   101,   236,     4,   101,   259,     4,
       4,   189,     4,     7,     7,   114,   114,     7,    98,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   122,    98,   322,     8,     3,    98,    98,    98,
       5,    98,    98,    98,    98,    98,     5,     7,    98,    98,
      98,   122,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,   114,   114,   135,    81,   349,
     350,   351,   145,    22,    23,    24,    25,    26,    27,   126,
     157,   158,   159,   161,   163,   165,   167,   169,   170,   171,
     157,     7,   200,   201,   202,     7,   228,   229,   230,     7,
     251,   252,   253,    59,    60,    61,    62,   172,   175,   176,
     177,   178,   179,   220,   315,     7,   182,   183,   184,    98,
     196,   197,    71,    72,    73,    74,   126,   159,   169,   325,
     326,   327,   328,   330,   331,    77,    78,   335,   336,   337,
     339,   119,   123,     4,   319,     7,   268,   269,   270,     7,
     280,   281,   282,    65,   311,     8,   352,     3,     8,     8,
     162,   164,   166,     4,     4,     4,     3,     8,     8,   203,
       6,     3,   231,     6,     3,   254,     6,     3,     3,     6,
       3,     6,   185,     6,     3,     4,     3,     8,   329,     4,
       4,     4,     3,     8,   338,   340,     3,     8,     8,   124,
      98,   271,     6,     3,   283,     6,     3,   312,     8,     4,
     350,     4,     4,     4,   101,    99,   101,   158,   206,   202,
     234,   230,   257,   253,   176,   220,   188,   184,    99,   197,
       4,    99,    99,    99,   326,     4,     4,   336,     6,   274,
     270,   286,   282,     4,     5,    98,    98,    98,     8,     8,
       8,     8,    98,    98,    98,     8,     8,    98,     7,   353,
     354,   355,     3,     6,    82,    84,    85,   126,   167,   356,
     357,   358,   359,   361,   354,   362,     4,   360,     3,     8,
       4,    99,     4,   357,     5,    98,     7,   363,   364,   365,
       3,     6,    83,   366,   367,   364,   368,     3,     8,     4,
     367,    98
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
     136,   136,   137,   138,   139,   140,   141,   142,   144,   143,
     145,   145,   146,   146,   148,   147,   150,   149,   152,   151,
     154,   153,   156,   155,   157,   157,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   160,   159,   162,   161,   164,
     163,   166,   165,   168,   167,   169,   170,   171,   172,   174,
     173,   175,   175,   176,   176,   176,   176,   177,   178,   179,
     181,   180,   182,   182,   183,   183,   185,   184,   187,   186,
     188,   188,   188,   189,   189,   191,   190,   193,   192,   195,
     194,   196,   196,   197,   199,   198,   200,   200,   201,   201,
     203,   202,   205,   204,   206,   206,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   209,   208,   211,   210,
     213,   212,   215,   214,   217,   216,   219,   218,   221,   220,
     223,   222,   224,   225,   227,   226,   228,   228,   229,   229,
     231,   230,   233,   232,   234,   234,   235,   235,   236,   236,
     236,   236,   236,   236,   236,   236,   237,   238,   239,   240,
     242,   241,   244,   243,   245,   247,   246,   248,   250,   249,
     251,   251,   252,   252,   254,   253,   256,   255,   257,   257,
     258,   258,   259,   259,   259,   259,   259,   259,   260,   262,
     261,   263,   264,   265,   267,   266,   268,   268,   269,   269,
     271,   270,   273,   272,   274,   274,   275,   275,   275,   277,
     276,   279,   278,   280,   280,   281,   281,   283,   282,   285,
     284,   286,   286,   287,   287,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   290,   289,   292,
     291,   294,   293,   296,   295,   298,   297,   300,   299,   302,
     301,   304,   303,   306,   305,   308,   307,   310,   309,   312,
     311,   314,   313,   315,   315,   316,   220,   317,   317,   318,
     318,   319,   319,   319,   319,   319,   319,   319,   320,   322,
     321,   324,   323,   325,   325,   326,   326,   326,   326,   326,
     326,   326,   327,   329,   328,   330,   331,   332,   334,   333,
     335,   335,   336,   336,   338,   337,   340,   339,   342,   341,
     344,   343,   346,   345,   348,   347,   349,   349,   350,   352,
     351,   353,   353,   355,   354,   356,   356,   357,   357,   357,
     357,   357,   358,   360,   359,   362,   361,   363,   363,   365,
     364,   366,   366,   368,   367
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
       6,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     0,     6,     1,     3,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
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
  "\"expired-leases-processing\"", "\"server-id\"", "\"identifier\"",
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
  "expired_leases_params", "expired_leases_param", "subnet4_list", "$@35",
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
       0,   198,   198,   198,   199,   199,   200,   200,   201,   201,
     202,   202,   203,   203,   204,   204,   205,   205,   206,   206,
     207,   207,   215,   216,   217,   218,   219,   220,   221,   224,
     229,   229,   241,   242,   245,   249,   256,   256,   264,   264,
     271,   272,   275,   279,   290,   300,   300,   312,   313,   317,
     318,   319,   320,   321,   324,   324,   341,   341,   349,   350,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   379,   384,   389,   394,   399,   404,   410,   410,
     420,   421,   424,   425,   428,   428,   436,   436,   446,   446,
     454,   454,   464,   464,   474,   475,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   489,   489,   497,   497,   505,
     505,   513,   513,   521,   521,   529,   534,   539,   544,   549,
     549,   559,   560,   563,   564,   565,   566,   569,   574,   579,
     584,   584,   594,   595,   598,   599,   602,   602,   610,   610,
     618,   619,   620,   623,   624,   627,   627,   635,   635,   643,
     643,   653,   654,   660,   668,   668,   681,   682,   685,   686,
     693,   693,   716,   716,   725,   726,   730,   731,   732,   733,
     734,   735,   736,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   752,   752,   760,   760,
     768,   768,   776,   776,   784,   784,   792,   792,   800,   800,
     808,   808,   816,   821,   830,   830,   842,   843,   846,   847,
     852,   852,   863,   863,   873,   874,   877,   878,   881,   882,
     883,   884,   885,   886,   887,   888,   891,   893,   898,   900,
     902,   902,   910,   910,   918,   920,   920,   928,   937,   937,
     949,   950,   955,   956,   961,   961,   972,   972,   983,   984,
     989,   990,   995,   996,   997,   998,   999,  1000,  1003,  1005,
    1005,  1013,  1015,  1017,  1025,  1025,  1037,  1038,  1041,  1042,
    1045,  1045,  1053,  1053,  1061,  1062,  1065,  1066,  1067,  1070,
    1070,  1081,  1081,  1091,  1092,  1095,  1096,  1099,  1099,  1107,
    1107,  1115,  1116,  1119,  1120,  1124,  1125,  1126,  1127,  1128,
    1129,  1130,  1131,  1132,  1133,  1134,  1135,  1138,  1138,  1146,
    1146,  1154,  1154,  1162,  1162,  1170,  1170,  1178,  1178,  1186,
    1186,  1194,  1194,  1203,  1203,  1211,  1211,  1224,  1224,  1234,
    1234,  1245,  1245,  1255,  1256,  1259,  1259,  1267,  1268,  1271,
    1272,  1275,  1276,  1277,  1278,  1279,  1280,  1281,  1284,  1286,
    1286,  1297,  1297,  1307,  1308,  1311,  1312,  1313,  1314,  1315,
    1316,  1317,  1320,  1325,  1325,  1333,  1338,  1345,  1352,  1352,
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
#line 3495 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1523 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
