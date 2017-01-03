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
      case 116: // value
        value.move< ElementPtr > (that.value);
        break;

      case 103: // "boolean"
        value.move< bool > (that.value);
        break;

      case 102: // "floating point"
        value.move< double > (that.value);
        break;

      case 101: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 100: // "constant string"
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
      case 116: // value
        value.copy< ElementPtr > (that.value);
        break;

      case 103: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 102: // "floating point"
        value.copy< double > (that.value);
        break;

      case 101: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 100: // "constant string"
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
            case 100: // "constant string"

#line 191 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 352 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 101: // "integer"

#line 191 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 359 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 102: // "floating point"

#line 191 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 103: // "boolean"

#line 191 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 116: // value

#line 191 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 116: // value
        yylhs.value.build< ElementPtr > ();
        break;

      case 103: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 102: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 101: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 100: // "constant string"
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
#line 200 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 201 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 202 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 203 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 208 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 209 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 326 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr type(new StringElement("raw", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-socket-type", type);
}
#line 1013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr type(new StringElement("udp", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-socket-type", type);
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 174:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1661 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1707 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1080 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1903 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1213 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2439 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2504 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1525 "dhcp4_parser.yy" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -414;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     187,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,    33,    20,    34,    53,    69,    75,    92,   100,   104,
     110,   130,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,    20,   -69,    24,    70,   163,    19,    -7,    96,
     126,    54,   -23,  -414,   146,    36,   152,   200,   211,  -414,
    -414,  -414,  -414,   218,  -414,    32,  -414,  -414,  -414,  -414,
    -414,  -414,   223,   227,  -414,  -414,  -414,   228,   229,   230,
     232,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,   233,
    -414,  -414,  -414,    45,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   234,    49,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,   237,   239,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,    58,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,    60,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   236,   243,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,   246,  -414,  -414,  -414,   247,  -414,  -414,  -414,
     252,   251,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,   257,  -414,  -414,  -414,  -414,   254,   260,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,    72,
    -414,  -414,  -414,  -414,    20,    20,  -414,   167,   265,   267,
     269,   270,  -414,    24,  -414,   271,   184,   185,   285,   286,
     287,   154,   191,   193,   194,   289,   292,   293,   294,   295,
     296,   297,   298,   202,   300,   301,    70,  -414,   302,   169,
     163,  -414,    25,   303,   304,   305,   306,   307,   308,   309,
     213,   212,   312,   313,   314,   315,    19,  -414,   316,    -7,
    -414,   317,   318,   319,   320,   321,   322,   323,   324,   325,
    -414,    96,   326,   327,   231,   329,   330,   331,   238,  -414,
     126,   332,   240,  -414,    54,   335,   336,   155,  -414,  -414,
    -414,   338,   337,   339,    20,    20,  -414,   340,  -414,  -414,
     245,   341,   342,  -414,  -414,  -414,  -414,   345,   346,   347,
     348,   349,   350,   351,   352,  -414,   353,   354,  -414,   357,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
     358,   362,  -414,  -414,  -414,   256,   272,   273,   365,   274,
     275,   276,  -414,  -414,   278,   280,   366,   360,  -414,   281,
    -414,   282,   283,   357,   288,   290,   299,   310,   311,   328,
    -414,   333,   334,  -414,   343,   344,   355,  -414,  -414,   356,
    -414,  -414,   359,    20,  -414,    20,    70,   363,  -414,  -414,
     163,  -414,   105,   105,   378,   379,   380,   157,    31,   382,
     361,   113,   150,   -69,  -414,  -414,   388,  -414,    25,  -414,
    -414,  -414,   386,  -414,  -414,  -414,  -414,  -414,   387,   364,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,    81,
    -414,   102,  -414,  -414,   136,  -414,  -414,  -414,   392,   393,
     394,  -414,   147,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,   182,  -414,   395,   397,  -414,  -414,   396,   400,
    -414,  -414,   398,   402,  -414,  -414,  -414,  -414,  -414,  -414,
      56,  -414,  -414,  -414,  -414,  -414,   140,  -414,   401,   403,
    -414,   404,   189,  -414,  -414,   405,   408,   409,  -414,  -414,
    -414,   192,  -414,  -414,  -414,  -414,  -414,  -414,  -414,   195,
    -414,  -414,  -414,   198,    20,   367,  -414,  -414,   411,   412,
    -414,  -414,   413,   417,  -414,  -414,   406,  -414,   418,   363,
    -414,  -414,   419,   420,   421,   368,   369,   370,   105,  -414,
    -414,    19,  -414,   378,   126,  -414,   379,    54,  -414,   380,
     157,  -414,    31,  -414,   -23,  -414,   382,   371,   361,  -414,
     422,   373,   374,   375,   113,  -414,   423,   425,   150,  -414,
    -414,   415,  -414,    -7,  -414,   386,    96,  -414,   387,   426,
    -414,   427,  -414,   377,   381,   383,  -414,  -414,  -414,  -414,
     199,  -414,   428,  -414,   429,  -414,  -414,  -414,   201,  -414,
    -414,  -414,   384,  -414,  -414,  -414,  -414,   385,   389,  -414,
    -414,   207,  -414,   430,  -414,   390,   432,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,   171,  -414,    78,   432,  -414,  -414,   431,  -414,  -414,
    -414,   208,  -414,  -414,  -414,  -414,  -414,   436,   391,   437,
      78,  -414,   440,  -414,   399,  -414,   435,  -414,  -414,   188,
    -414,   372,   435,  -414,  -414,   209,  -414,  -414,   443,   372,
    -414,   407,  -414,  -414
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    94,     9,
     174,    11,   284,    13,   301,    15,   224,    17,   258,    19,
     150,    21,    40,    32,     0,     0,     0,     0,     0,   303,
     226,   260,     0,    42,     0,    41,     0,     0,    33,    54,
     396,   392,   394,     0,    53,     0,    47,    49,    51,    52,
      50,    88,     0,     0,   319,   102,   104,     0,     0,     0,
       0,   166,   216,   250,   131,   343,   142,   161,   363,     0,
     380,   390,    81,     0,    58,    60,    61,    62,    63,    78,
      79,    65,    66,    67,    68,    72,    73,    64,    70,    71,
      80,    69,    74,    75,    76,    77,    96,     0,     0,    90,
      92,    93,    98,    99,   347,   200,   202,   204,   276,   198,
     206,   208,     0,     0,   212,   210,   293,   339,   197,   178,
     179,   180,   192,     0,   176,   183,   194,   195,   196,   184,
     185,   188,   190,   186,   187,   181,   182,   189,   193,   191,
     291,   290,   289,     0,   286,   288,   321,   323,   337,   327,
     329,   333,   331,   335,   325,   318,   314,     0,   304,   305,
     315,   316,   317,   311,   307,   312,   309,   310,   313,   308,
     117,   125,     0,   244,   242,   247,     0,   237,   241,   238,
       0,   227,   228,   230,   240,   231,   232,   233,   246,   234,
     235,   236,   271,     0,   269,   270,   273,   274,     0,   261,
     262,   264,   265,   266,   267,   268,   157,   159,   154,     0,
     152,   155,   156,    37,     0,     0,    31,     0,     0,     0,
       0,     0,    44,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,     0,     0,
       0,    95,   349,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   175,     0,     0,
     285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     302,     0,     0,     0,     0,     0,     0,     0,     0,   225,
       0,     0,     0,   259,     0,     0,     0,     0,   151,    43,
      34,     0,     0,     0,     0,     0,    48,     0,    86,    87,
       0,     0,     0,    82,    83,    84,    85,     0,     0,     0,
       0,     0,     0,     0,     0,   379,     0,     0,    59,     0,
     100,   101,    91,   361,   359,   360,   355,   356,   357,   358,
       0,   350,   351,   353,   354,     0,     0,     0,     0,     0,
       0,     0,   214,   215,     0,     0,     0,     0,   177,     0,
     287,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     306,     0,     0,   239,     0,     0,     0,   249,   229,     0,
     275,   263,     0,     0,   153,     0,     0,     0,   393,   395,
       0,   320,     0,     0,   168,   218,   252,     0,     0,   144,
       0,     0,     0,     0,    38,    97,     0,   348,     0,   201,
     203,   205,   278,   199,   207,   209,   213,   211,   295,     0,
     292,   322,   324,   338,   328,   330,   334,   332,   336,   326,
     118,   126,   245,   243,   248,   272,   158,   160,    35,     0,
     401,     0,   398,   400,     0,   119,   121,   123,     0,     0,
       0,   116,     0,   106,   108,   109,   110,   111,   112,   113,
     114,   115,     0,   172,     0,   169,   170,   222,     0,   219,
     220,   256,     0,   253,   254,   130,   139,   140,   141,   135,
       0,   133,   136,   137,   138,   345,     0,   148,     0,   145,
     146,     0,     0,   163,   375,     0,     0,     0,   373,   367,
     372,     0,   365,   370,   368,   369,   371,   386,   388,     0,
     382,   384,   385,     0,    40,     0,   352,   282,     0,   279,
     280,   299,     0,   296,   297,   341,     0,    55,     0,     0,
     397,    89,     0,     0,     0,     0,     0,     0,     0,   103,
     105,     0,   167,     0,   226,   217,     0,   260,   251,     0,
       0,   132,     0,   344,     0,   143,     0,     0,     0,   162,
       0,     0,     0,     0,     0,   364,     0,     0,     0,   381,
     391,     0,   362,     0,   277,     0,   303,   294,     0,     0,
     340,     0,   399,     0,     0,     0,   127,   128,   129,   107,
       0,   171,     0,   221,     0,   255,   134,   346,     0,   147,
     165,   164,     0,   374,   377,   378,   366,     0,     0,   383,
      39,     0,   281,     0,   298,     0,     0,   120,   122,   124,
     173,   223,   257,   149,   376,   387,   389,   283,   300,   342,
     405,     0,   403,     0,     0,   402,   417,     0,   415,   413,
     409,     0,   407,   411,   412,   410,   404,     0,     0,     0,
       0,   406,     0,   414,     0,   408,     0,   416,   421,     0,
     419,     0,     0,   418,   425,     0,   423,   420,     0,     0,
     422,     0,   424,   426
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,     3,  -414,  -414,  -414,  -414,   -76,  -414,  -414,
      55,  -414,   -95,  -414,   -54,  -414,  -414,  -414,   197,  -414,
    -414,  -414,  -414,    35,   176,   -56,   -40,   -38,  -414,  -414,
     -37,  -414,  -414,    38,   173,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,    37,  -114,  -401,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,   -59,  -414,  -413,  -414,
    -414,  -414,  -414,  -414,  -414,  -118,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -123,  -414,  -414,  -414,  -120,   138,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -122,  -414,  -414,  -414,
    -414,  -105,  -414,  -414,  -414,  -102,   183,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -400,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,   -98,
    -414,  -414,  -414,   -94,  -414,   162,  -414,   -52,  -414,  -414,
    -414,  -414,   -48,  -414,  -414,  -414,  -414,  -414,   -47,  -414,
    -414,  -414,   -93,  -414,  -414,  -414,   -90,  -414,   164,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -112,
    -414,  -414,  -414,  -109,   196,  -414,  -414,  -414,  -414,  -414,
    -414,  -117,  -414,  -414,  -414,  -110,  -414,   186,   -43,  -414,
    -259,  -414,  -258,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,    62,  -414,
    -414,  -414,  -414,  -414,  -414,   -96,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,   -97,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,   -57,
    -414,  -414,  -414,  -161,  -414,  -414,  -176,  -414,  -414,  -414,
    -414,  -414,  -414,  -187,  -414,  -414,  -193,  -414
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,    67,    68,    33,    52,
     435,   544,    64,    65,   102,    35,    54,    75,    76,    77,
     248,    37,    55,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   255,   128,   129,    39,    56,   130,   278,   131,
     132,   133,   112,   259,   113,   260,   482,   483,   208,   312,
     485,   562,   486,   563,   487,   564,   209,   313,   489,   490,
     491,   509,   114,   268,   510,   511,   512,   513,   514,   115,
     270,   518,   519,   520,   584,    51,    62,   239,   240,   241,
     325,   242,   326,   116,   271,   522,   523,   117,   265,   494,
     495,   496,   571,    41,    57,   153,   154,   155,   287,   156,
     283,   157,   284,   158,   285,   159,   288,   160,   289,   161,
     293,   162,   292,   163,   164,   118,   266,   498,   499,   500,
     574,    47,    60,   210,   211,   212,   213,   214,   215,   216,
     217,   316,   218,   315,   219,   220,   317,   221,   119,   267,
     502,   503,   504,   577,    49,    61,   228,   229,   230,   231,
     232,   321,   233,   234,   235,   166,   286,   548,   549,   550,
     603,    43,    58,   173,   174,   175,   298,   167,   294,   552,
     553,   554,   606,    45,    59,   187,   188,   189,   120,   258,
     191,   301,   192,   302,   193,   309,   194,   304,   195,   305,
     196,   307,   197,   306,   198,   308,   199,   303,   169,   295,
     556,   609,   121,   269,   516,   282,   370,   371,   372,   373,
     374,   436,   122,   272,   531,   532,   533,   534,   590,   535,
     536,   123,   124,   274,   539,   540,   541,   596,   542,   597,
     125,   275,    78,   250,    79,   251,    80,   249,   471,   472,
     473,   558,   661,   662,   663,   671,   672,   673,   674,   679,
     675,   677,   689,   690,   691,   695,   696,   698
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   149,   225,   148,   171,   185,   207,   224,   238,   226,
     165,   172,   186,   227,   168,    30,   190,   150,   530,   151,
     152,   484,   484,   368,   369,    23,   134,    24,   515,    25,
     529,    66,    93,    22,    69,   253,    83,    84,   134,   244,
     254,    34,   170,    84,   176,   177,   236,   237,   276,    87,
      88,    89,   280,   277,   135,   136,   137,   281,    93,   580,
      36,   296,   581,   299,    93,   201,   297,   138,   300,   139,
     140,   141,   142,   143,   144,   327,    38,    73,   145,   146,
     328,    81,    40,   363,   276,   147,    82,    83,    84,   557,
     145,    85,    86,    73,   201,   222,   202,   203,   223,    42,
      87,    88,    89,    90,    91,   559,    70,    44,    92,    93,
     560,    46,    71,    72,    84,   176,   177,    48,   201,    73,
      26,    27,    28,    29,    73,    73,    94,    95,   200,   475,
     476,   477,   478,   479,   480,    93,   200,    50,    96,   280,
     478,    97,    98,   582,   561,   201,   583,    99,   100,   200,
     568,   101,   243,   178,    73,   569,   245,   179,   180,   181,
     182,   183,   666,   184,   667,   668,   201,   484,   202,   203,
      73,   204,   205,   206,   664,   126,   127,   665,    73,   368,
     369,   530,   627,   360,   361,   568,   524,   525,   526,   527,
     570,   692,   588,   529,   693,   594,    73,   589,   598,    74,
     595,   247,   296,   599,   327,    73,   600,   650,   246,   653,
     299,   680,   699,    73,   247,   657,   681,   700,   505,   506,
     507,   508,   252,   365,   236,   237,    73,   256,   364,   537,
     538,   257,   261,   262,   263,   366,   264,   273,   279,   367,
     149,   290,   148,   291,   310,   171,   311,   329,   330,   165,
     314,   318,   172,   168,   320,   343,   150,   185,   151,   152,
     319,   322,   323,   324,   186,   225,   207,   331,   190,   332,
     224,   333,   226,   334,   335,   337,   227,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,   338,   339,   340,
     341,   342,   344,   347,   345,   346,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   359,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     389,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     401,   402,   403,   404,   405,   406,   409,   418,   419,   412,
     413,   407,   415,   410,   416,   421,   417,   420,   422,   423,
     424,   425,   426,   427,   428,   429,   439,   543,   430,   431,
     432,   433,   434,   488,   488,   438,   437,   449,   481,   481,
     442,   448,   440,   441,   443,   444,   445,   528,   446,   365,
     447,   450,   451,   452,   364,   493,   497,   501,   454,   517,
     455,   366,   545,   547,   551,   367,   565,   566,   567,   456,
     573,   572,   575,   576,   578,   579,   586,   585,   587,   591,
     457,   458,   592,   593,   610,   605,   467,   604,   468,   607,
     608,   640,   611,   613,   614,   615,   632,   637,   459,   638,
     645,   555,   646,   460,   461,   678,   651,   652,   658,   660,
     682,   684,   688,   462,   463,   686,   470,   701,   453,   601,
     336,   469,   358,   362,   619,   464,   465,   694,   474,   466,
     492,   521,   626,   629,   628,   414,   631,   602,   621,   620,
     617,   616,   630,   618,   633,   634,   635,   647,   623,   388,
     622,   648,   408,   649,   654,   655,   625,   624,   411,   656,
     659,   644,   683,   642,   641,   390,   643,   400,   636,   687,
     546,   639,   612,   676,   685,   697,   702,   703,     0,   488,
       0,     0,     0,     0,   481,   149,     0,   148,   225,     0,
     207,     0,     0,   224,   165,   226,     0,     0,   168,   227,
     238,   150,     0,   151,   152,     0,     0,     0,     0,     0,
     528,     0,     0,     0,     0,     0,     0,     0,     0,   171,
       0,     0,   185,     0,     0,     0,   172,     0,     0,   186,
       0,     0,     0,   190,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   670,     0,     0,     0,     0,   669,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   670,     0,     0,     0,     0,   669
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,    12,    59,    57,   431,    57,
      57,   422,   423,   282,   282,     5,     7,     7,   428,     9,
     431,   100,    39,     0,    10,     3,    17,    18,     7,     3,
       8,     7,    49,    18,    19,    20,    69,    70,     3,    30,
      31,    32,     3,     8,    35,    36,    37,     8,    39,     3,
       7,     3,     6,     3,    39,    40,     8,    48,     8,    50,
      51,    52,    53,    54,    55,     3,     7,   100,    59,    60,
       8,    11,     7,    58,     3,    66,    16,    17,    18,     8,
      59,    21,    22,   100,    40,    41,    42,    43,    44,     7,
      30,    31,    32,    33,    34,     3,    82,     7,    38,    39,
       8,     7,    88,    89,    18,    19,    20,     7,    40,   100,
     100,   101,   102,   103,   100,   100,    56,    57,    23,    24,
      25,    26,    27,    28,    29,    39,    23,     7,    68,     3,
      27,    71,    72,     3,     8,    40,     6,    77,    78,    23,
       3,    81,     6,    57,   100,     8,     4,    61,    62,    63,
      64,    65,    84,    67,    86,    87,    40,   568,    42,    43,
     100,    45,    46,    47,     3,    12,    13,     6,   100,   438,
     438,   594,   582,    14,    15,     3,    73,    74,    75,    76,
       8,     3,     3,   594,     6,     3,   100,     8,     3,   253,
       8,     3,     3,     8,     3,   100,     8,     8,     8,     8,
       3,     3,     3,   100,     3,     8,     8,     8,    61,    62,
      63,    64,     4,   282,    69,    70,   100,     4,   282,    79,
      80,     4,     4,     4,     4,   282,     4,     4,     4,   282,
     296,     4,   296,     4,     8,   299,     3,   244,   245,   296,
       4,     4,   299,   296,     3,   101,   296,   311,   296,   296,
       8,     4,     8,     3,   311,   324,   320,   100,   311,     4,
     324,     4,   324,     4,     4,     4,   324,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   103,   103,     4,
       4,     4,   101,     4,   101,   101,     4,     4,     4,     4,
       4,     4,     4,   101,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   101,   103,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   101,     4,     4,     4,     4,   334,   335,     4,
       4,   103,     4,   103,     7,   100,     7,     7,     7,     7,
       5,     5,     5,     5,     5,     5,   100,   433,     7,     7,
       7,     7,     5,   422,   423,     3,     8,     7,   422,   423,
       5,     5,   100,   100,   100,   100,   100,   431,   100,   438,
     100,   100,   100,   100,   438,     7,     7,     7,   100,     7,
     100,   438,     4,     7,     7,   438,     4,     4,     4,   100,
       3,     6,     6,     3,     6,     3,     3,     6,     4,     4,
     100,   100,     4,     4,     8,     3,   413,     6,   415,     6,
       3,     6,     4,     4,     4,     4,     4,     4,   100,     4,
       4,    67,     5,   100,   100,     4,     8,     8,     8,     7,
       4,     4,     7,   100,   100,     5,    83,     4,   393,   544,
     253,   416,   276,   280,   568,   100,   100,    85,   420,   100,
     423,   100,   580,   586,   584,   327,   588,   100,   573,   571,
     101,   103,   101,   103,   101,   101,   101,   100,   576,   296,
     574,   100,   320,   100,   100,   100,   579,   577,   324,   100,
     100,   608,   101,   605,   603,   299,   606,   311,   594,   100,
     438,   598,   559,   664,   680,   692,   699,   100,    -1,   568,
      -1,    -1,    -1,    -1,   568,   571,    -1,   571,   577,    -1,
     574,    -1,    -1,   577,   571,   577,    -1,    -1,   571,   577,
     584,   571,    -1,   571,   571,    -1,    -1,    -1,    -1,    -1,
     594,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   603,
      -1,    -1,   606,    -1,    -1,    -1,   603,    -1,    -1,   606,
      -1,    -1,    -1,   606,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   663,    -1,    -1,    -1,    -1,   663,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   680,    -1,    -1,    -1,    -1,   680
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     0,     5,     7,     9,   100,   101,   102,   103,
     116,   117,   118,   122,     7,   129,     7,   135,     7,   149,
       7,   207,     7,   275,     7,   287,     7,   235,     7,   258,
       7,   189,   123,   119,   130,   136,   150,   208,   276,   288,
     236,   259,   190,   116,   126,   127,   100,   120,   121,    10,
      82,    88,    89,   100,   128,   131,   132,   133,   346,   348,
     350,    11,    16,    17,    18,    21,    22,    30,    31,    32,
      33,    34,    38,    39,    56,    57,    68,    71,    72,    77,
      78,    81,   128,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   156,   158,   176,   183,   197,   201,   229,   252,
     292,   316,   326,   335,   336,   344,    12,    13,   147,   148,
     151,   153,   154,   155,     7,    35,    36,    37,    48,    50,
      51,    52,    53,    54,    55,    59,    60,    66,   128,   139,
     140,   141,   144,   209,   210,   211,   213,   215,   217,   219,
     221,   223,   225,   227,   228,   252,   269,   281,   292,   312,
      49,   128,   252,   277,   278,   279,    19,    20,    57,    61,
      62,    63,    64,    65,    67,   128,   252,   289,   290,   291,
     292,   294,   296,   298,   300,   302,   304,   306,   308,   310,
      23,    40,    42,    43,    45,    46,    47,   128,   162,   170,
     237,   238,   239,   240,   241,   242,   243,   244,   246,   248,
     249,   251,    41,    44,   128,   170,   241,   246,   260,   261,
     262,   263,   264,   266,   267,   268,    69,    70,   128,   191,
     192,   193,   195,     6,     3,     4,     8,     3,   134,   351,
     347,   349,     4,     3,     8,   146,     4,     4,   293,   157,
     159,     4,     4,     4,     4,   202,   230,   253,   177,   317,
     184,   198,   327,     4,   337,   345,     3,     8,   152,     4,
       3,     8,   319,   214,   216,   218,   270,   212,   220,   222,
       4,     4,   226,   224,   282,   313,     3,     8,   280,     3,
       8,   295,   297,   311,   301,   303,   307,   305,   309,   299,
       8,     3,   163,   171,     4,   247,   245,   250,     4,     8,
       3,   265,     4,     8,     3,   194,   196,     3,     8,   116,
     116,   100,     4,     4,     4,     4,   132,     4,   103,   103,
       4,     4,     4,   101,   101,   101,   101,     4,     4,     4,
       4,     4,     4,     4,     4,   101,     4,     4,   138,     4,
      14,    15,   148,    58,   128,   170,   252,   292,   294,   296,
     320,   321,   322,   323,   324,     4,     4,     4,     4,     4,
       4,     4,   101,   103,     4,     4,     4,     4,   210,     4,
     278,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     291,     4,     4,   101,     4,     4,     4,   103,   239,     4,
     103,   262,     4,     4,   192,     4,     7,     7,   116,   116,
       7,   100,     7,     7,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   124,   325,     8,     3,   100,
     100,   100,     5,   100,   100,   100,   100,   100,     5,     7,
     100,   100,   100,   124,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   116,   116,   137,
      83,   352,   353,   354,   147,    24,    25,    26,    27,    28,
      29,   128,   160,   161,   162,   164,   166,   168,   170,   172,
     173,   174,   160,     7,   203,   204,   205,     7,   231,   232,
     233,     7,   254,   255,   256,    61,    62,    63,    64,   175,
     178,   179,   180,   181,   182,   223,   318,     7,   185,   186,
     187,   100,   199,   200,    73,    74,    75,    76,   128,   162,
     172,   328,   329,   330,   331,   333,   334,    79,    80,   338,
     339,   340,   342,   121,   125,     4,   322,     7,   271,   272,
     273,     7,   283,   284,   285,    67,   314,     8,   355,     3,
       8,     8,   165,   167,   169,     4,     4,     4,     3,     8,
       8,   206,     6,     3,   234,     6,     3,   257,     6,     3,
       3,     6,     3,     6,   188,     6,     3,     4,     3,     8,
     332,     4,     4,     4,     3,     8,   341,   343,     3,     8,
       8,   126,   100,   274,     6,     3,   286,     6,     3,   315,
       8,     4,   353,     4,     4,     4,   103,   101,   103,   161,
     209,   205,   237,   233,   260,   256,   179,   223,   191,   187,
     101,   200,     4,   101,   101,   101,   329,     4,     4,   339,
       6,   277,   273,   289,   285,     4,     5,   100,   100,   100,
       8,     8,     8,     8,   100,   100,   100,     8,     8,   100,
       7,   356,   357,   358,     3,     6,    84,    86,    87,   128,
     170,   359,   360,   361,   362,   364,   357,   365,     4,   363,
       3,     8,     4,   101,     4,   360,     5,   100,     7,   366,
     367,   368,     3,     6,    85,   369,   370,   367,   371,     3,
       8,     4,   370,   100
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   104,   106,   105,   107,   105,   108,   105,   109,   105,
     110,   105,   111,   105,   112,   105,   113,   105,   114,   105,
     115,   105,   116,   116,   116,   116,   116,   116,   116,   117,
     119,   118,   120,   120,   121,   121,   123,   122,   125,   124,
     126,   126,   127,   127,   128,   130,   129,   131,   131,   132,
     132,   132,   132,   132,   134,   133,   136,   135,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   139,   140,   141,   142,   143,   144,   146,   145,
     147,   147,   148,   148,   150,   149,   152,   151,   153,   153,
     154,   155,   157,   156,   159,   158,   160,   160,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   163,   162,   165,
     164,   167,   166,   169,   168,   171,   170,   172,   173,   174,
     175,   177,   176,   178,   178,   179,   179,   179,   179,   180,
     181,   182,   184,   183,   185,   185,   186,   186,   188,   187,
     190,   189,   191,   191,   191,   192,   192,   194,   193,   196,
     195,   198,   197,   199,   199,   200,   202,   201,   203,   203,
     204,   204,   206,   205,   208,   207,   209,   209,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   212,   211,
     214,   213,   216,   215,   218,   217,   220,   219,   222,   221,
     224,   223,   226,   225,   227,   228,   230,   229,   231,   231,
     232,   232,   234,   233,   236,   235,   237,   237,   238,   238,
     239,   239,   239,   239,   239,   239,   239,   239,   240,   241,
     242,   243,   245,   244,   247,   246,   248,   250,   249,   251,
     253,   252,   254,   254,   255,   255,   257,   256,   259,   258,
     260,   260,   261,   261,   262,   262,   262,   262,   262,   262,
     263,   265,   264,   266,   267,   268,   270,   269,   271,   271,
     272,   272,   274,   273,   276,   275,   277,   277,   278,   278,
     278,   280,   279,   282,   281,   283,   283,   284,   284,   286,
     285,   288,   287,   289,   289,   290,   290,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   293,
     292,   295,   294,   297,   296,   299,   298,   301,   300,   303,
     302,   305,   304,   307,   306,   309,   308,   311,   310,   313,
     312,   315,   314,   317,   316,   318,   318,   319,   223,   320,
     320,   321,   321,   322,   322,   322,   322,   322,   322,   322,
     323,   325,   324,   327,   326,   328,   328,   329,   329,   329,
     329,   329,   329,   329,   330,   332,   331,   333,   334,   335,
     337,   336,   338,   338,   339,   339,   341,   340,   343,   342,
     345,   344,   347,   346,   349,   348,   351,   350,   352,   352,
     353,   355,   354,   356,   356,   358,   357,   359,   359,   360,
     360,   360,   360,   360,   361,   363,   362,   365,   364,   366,
     366,   368,   367,   369,   369,   371,   370
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
       1,     3,     1,     1,     0,     4,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     0,     4
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
  "$@18", "interfaces_list", "$@19", "dhcp_socket_type",
  "dhcp_socket_type_raw", "dhcp_socket_type_udp", "lease_database", "$@20",
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
  "identifier", "$@78", "time", "enterprise_id", "dhcp4o6_port",
  "control_socket", "$@79", "control_socket_params",
  "control_socket_param", "socket_type", "$@80", "socket_name", "$@81",
  "dhcp_ddns", "$@82", "dhcp6_json_object", "$@83", "dhcpddns_json_object",
  "$@84", "logging_object", "$@85", "logging_params", "logging_param",
  "loggers", "$@86", "loggers_entries", "logger_entry", "$@87",
  "logger_params", "logger_param", "debuglevel", "severity", "$@88",
  "output_options_list", "$@89", "output_options_list_content",
  "output_entry", "$@90", "output_params", "output_param", "$@91", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   200,   200,   200,   201,   201,   202,   202,   203,   203,
     204,   204,   205,   205,   206,   206,   207,   207,   208,   208,
     209,   209,   217,   218,   219,   220,   221,   222,   223,   226,
     231,   231,   243,   244,   247,   251,   258,   258,   266,   266,
     273,   274,   277,   281,   292,   302,   302,   314,   315,   319,
     320,   321,   322,   323,   326,   326,   343,   343,   351,   352,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   381,   386,   391,   396,   401,   406,   412,   412,
     422,   423,   426,   427,   430,   430,   438,   438,   448,   449,
     452,   457,   462,   462,   472,   472,   482,   483,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   497,   497,   505,
     505,   513,   513,   521,   521,   529,   529,   537,   542,   547,
     552,   557,   557,   567,   568,   571,   572,   573,   574,   577,
     582,   587,   592,   592,   602,   603,   606,   607,   610,   610,
     618,   618,   626,   627,   628,   631,   632,   635,   635,   643,
     643,   651,   651,   661,   662,   668,   676,   676,   689,   690,
     693,   694,   701,   701,   724,   724,   733,   734,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
     750,   751,   752,   753,   754,   755,   756,   757,   760,   760,
     768,   768,   776,   776,   784,   784,   792,   792,   800,   800,
     808,   808,   816,   816,   824,   829,   838,   838,   850,   851,
     854,   855,   860,   860,   871,   871,   881,   882,   885,   886,
     889,   890,   891,   892,   893,   894,   895,   896,   899,   901,
     906,   908,   910,   910,   918,   918,   926,   928,   928,   936,
     945,   945,   957,   958,   963,   964,   969,   969,   980,   980,
     991,   992,   997,   998,  1003,  1004,  1005,  1006,  1007,  1008,
    1011,  1013,  1013,  1021,  1023,  1025,  1033,  1033,  1045,  1046,
    1049,  1050,  1053,  1053,  1061,  1061,  1069,  1070,  1073,  1074,
    1075,  1078,  1078,  1089,  1089,  1099,  1100,  1103,  1104,  1107,
    1107,  1115,  1115,  1123,  1124,  1127,  1128,  1132,  1133,  1134,
    1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,  1143,  1146,
    1146,  1154,  1154,  1162,  1162,  1170,  1170,  1178,  1178,  1186,
    1186,  1194,  1194,  1202,  1202,  1211,  1211,  1219,  1219,  1232,
    1232,  1242,  1242,  1253,  1253,  1263,  1264,  1267,  1267,  1275,
    1276,  1279,  1280,  1283,  1284,  1285,  1286,  1287,  1288,  1289,
    1292,  1294,  1294,  1305,  1305,  1315,  1316,  1319,  1320,  1321,
    1322,  1323,  1324,  1325,  1328,  1333,  1333,  1341,  1346,  1353,
    1360,  1360,  1370,  1371,  1374,  1375,  1378,  1378,  1386,  1386,
    1396,  1396,  1408,  1408,  1415,  1415,  1427,  1427,  1440,  1441,
    1445,  1449,  1449,  1461,  1462,  1466,  1466,  1474,  1475,  1478,
    1479,  1480,  1481,  1482,  1485,  1489,  1489,  1497,  1497,  1507,
    1508,  1511,  1511,  1519,  1520,  1523,  1523
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
#line 3496 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1531 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
