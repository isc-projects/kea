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
      case 122: // value
        value.move< ElementPtr > (that.value);
        break;

      case 108: // "boolean"
        value.move< bool > (that.value);
        break;

      case 107: // "floating point"
        value.move< double > (that.value);
        break;

      case 106: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 105: // "constant string"
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
      case 122: // value
        value.copy< ElementPtr > (that.value);
        break;

      case 108: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 107: // "floating point"
        value.copy< double > (that.value);
        break;

      case 106: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 105: // "constant string"
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
            case 105: // "constant string"

#line 195 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 352 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 106: // "integer"

#line 195 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 359 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 107: // "floating point"

#line 195 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 366 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 108: // "boolean"

#line 195 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 373 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 122: // value

#line 195 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 122: // value
        yylhs.value.build< ElementPtr > ();
        break;

      case 108: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 107: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 106: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 105: // "constant string"
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
#line 204 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 205 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 206 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 207 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 208 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 209 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 210 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 211 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 662 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 212 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 213 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 214 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 731 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 880 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 391 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 981 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 992 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 547 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1236 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1356 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 733 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1473 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1489 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1580 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1662 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1110 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1118 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1199 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2060 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2097 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2133 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2163 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2191 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1304 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2257 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2351 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2537 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2556 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -428;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     183,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,    35,    22,    52,    63,    93,   103,   119,   134,
     158,   177,   186,   188,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,    22,   -53,    16,    70,
      65,    15,    28,    62,    27,   127,    81,   -34,  -428,   141,
     215,   176,   225,   231,  -428,  -428,  -428,  -428,   232,  -428,
      33,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,   233,
     235,   236,   237,   238,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,   240,  -428,  -428,  -428,    77,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,   239,  -428,  -428,  -428,  -428,  -428,  -428,   246,
     247,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
     137,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,   140,  -428,  -428,
    -428,   254,  -428,   255,   257,  -428,  -428,   146,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,   256,   262,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,   264,  -428,  -428,  -428,   265,  -428,  -428,
    -428,   258,   267,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,   268,  -428,  -428,  -428,  -428,   263,
     270,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
     150,  -428,  -428,  -428,  -428,    22,    22,  -428,   170,   284,
     285,   286,   287,  -428,    16,  -428,   288,   289,   290,   189,
     190,   192,   193,   194,   293,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   206,   306,   307,    70,  -428,   309,
    -428,    45,   310,   311,   312,   313,   314,   213,   216,   316,
     317,   318,   319,    15,  -428,   321,    28,  -428,   322,   223,
     323,   226,   227,    62,  -428,   324,   326,   327,   330,   331,
     332,  -428,    27,   333,   336,   241,   337,   338,   339,   242,
    -428,   127,   340,   243,  -428,    81,   341,   342,   -25,  -428,
    -428,  -428,   344,   347,   348,    22,    22,  -428,   349,   350,
     351,  -428,  -428,  -428,  -428,  -428,   356,   357,   358,   359,
     360,   361,   362,   363,   365,   366,  -428,   367,   368,  -428,
     360,  -428,  -428,  -428,  -428,   370,   346,  -428,  -428,  -428,
     364,   371,   274,   275,   276,  -428,  -428,   277,   278,   379,
     380,  -428,   281,  -428,   283,  -428,   291,  -428,  -428,  -428,
     360,   360,   360,   292,   294,   295,  -428,   296,   308,  -428,
     315,   320,   325,  -428,  -428,   328,  -428,  -428,   329,    22,
    -428,    22,    70,   334,  -428,  -428,    65,    30,    30,   382,
     383,   384,   -29,  -428,  -428,     7,    21,   385,   128,    39,
      90,   -53,  -428,   389,  -428,    45,   387,   388,  -428,  -428,
    -428,  -428,  -428,   391,   343,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,   153,  -428,   163,  -428,  -428,   394,  -428,
    -428,  -428,   399,   400,   401,  -428,   169,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,   173,  -428,   403,   404,
    -428,  -428,   405,   407,  -428,  -428,   409,   413,  -428,  -428,
    -428,   131,  -428,  -428,  -428,    22,  -428,  -428,   191,  -428,
    -428,  -428,   205,  -428,   411,   415,  -428,   402,   418,   419,
     420,   422,   423,   179,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,   424,   425,   427,  -428,  -428,  -428,   180,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,   201,  -428,  -428,  -428,
     202,   335,  -428,  -428,   426,   416,  -428,  -428,   429,   433,
    -428,  -428,   431,   435,  -428,  -428,   434,  -428,   437,   334,
    -428,  -428,   439,   440,   441,   345,   352,   353,    30,  -428,
    -428,    15,  -428,   382,   127,  -428,   383,    81,  -428,   384,
     -29,  -428,   442,     7,  -428,    21,  -428,   -34,  -428,   385,
     354,   369,   372,   373,   374,   375,   128,  -428,   443,   376,
     377,   378,    39,  -428,   445,   446,    90,  -428,  -428,  -428,
      28,  -428,   387,    62,  -428,   388,    27,  -428,   391,   447,
    -428,   449,  -428,   381,   386,   390,  -428,  -428,  -428,  -428,
     204,  -428,   438,  -428,   444,  -428,  -428,  -428,  -428,  -428,
     211,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,   392,
    -428,  -428,  -428,  -428,   393,   395,  -428,   212,  -428,   214,
    -428,   448,  -428,   396,   432,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
     222,  -428,   101,   432,  -428,  -428,   451,  -428,  -428,  -428,
     218,  -428,  -428,  -428,  -428,  -428,   453,   397,   455,   101,
    -428,   457,  -428,   406,  -428,   456,  -428,  -428,   224,  -428,
     398,   456,  -428,  -428,   221,  -428,  -428,   460,   398,  -428,
     410,  -428,  -428
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      91,     9,   183,    11,   284,    13,   301,    15,   327,    17,
     224,    19,   258,    21,   148,    23,    42,    34,     0,     0,
       0,     0,     0,     0,   329,   226,   260,     0,    44,     0,
      43,     0,     0,    35,    56,   407,   403,   405,     0,    55,
       0,    49,    51,    53,    54,    52,    89,    95,    97,     0,
       0,     0,     0,     0,   175,   216,   250,   123,   138,   131,
     357,   140,   159,   374,     0,   391,   401,    83,     0,    60,
      62,    63,    64,    65,    66,    68,    69,    70,    71,    73,
      72,    77,    78,    67,    75,    76,    74,    79,    80,    81,
      82,    93,     0,   361,   276,   293,   204,   206,   208,     0,
       0,   212,   210,   319,   353,   203,   187,   188,   189,   190,
       0,   185,   194,   195,   196,   199,   201,   197,   198,   191,
     192,   193,   200,   202,   291,   290,   289,     0,   286,   288,
     312,     0,   315,     0,     0,   311,   308,     0,   303,   305,
     306,   309,   310,   307,   351,   341,   343,   345,   347,   349,
     340,   339,     0,   330,   331,   335,   336,   333,   337,   338,
     334,   110,   118,     0,   244,   242,   247,     0,   237,   241,
     238,     0,   227,   228,   230,   240,   231,   232,   233,   246,
     234,   235,   236,   271,     0,   269,   270,   273,   274,     0,
     261,   262,   264,   265,   266,   267,   268,   155,   157,   152,
       0,   150,   153,   154,    39,     0,     0,    33,     0,     0,
       0,     0,     0,    46,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
      92,   363,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   184,     0,     0,   285,     0,     0,
       0,     0,     0,     0,   302,     0,     0,     0,     0,     0,
       0,   328,     0,     0,     0,     0,     0,     0,     0,     0,
     225,     0,     0,     0,   259,     0,     0,     0,     0,   149,
      45,    36,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    84,    85,    86,    87,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   390,     0,     0,    61,
       0,   372,   370,   371,   369,     0,   364,   365,   367,   368,
       0,     0,     0,     0,     0,   214,   215,     0,     0,     0,
       0,   186,     0,   287,     0,   314,     0,   317,   318,   304,
       0,     0,     0,     0,     0,     0,   332,     0,     0,   239,
       0,     0,     0,   249,   229,     0,   275,   263,     0,     0,
     151,     0,     0,     0,   404,   406,     0,     0,     0,   177,
     218,   252,     0,    40,   139,     0,     0,   142,     0,     0,
       0,     0,    94,     0,   362,     0,   278,   295,   205,   207,
     209,   213,   211,   321,     0,   292,   313,   316,   352,   342,
     344,   346,   348,   350,   111,   119,   245,   243,   248,   272,
     156,   158,    37,     0,   412,     0,   409,   411,     0,   112,
     114,   116,     0,     0,     0,   109,     0,    99,   101,   102,
     103,   104,   105,   106,   107,   108,     0,   181,     0,   178,
     179,   222,     0,   219,   220,   256,     0,   253,   254,   129,
     130,     0,   125,   127,   128,    42,   137,   135,     0,   133,
     136,   359,     0,   146,     0,   143,   144,     0,     0,     0,
       0,     0,     0,     0,   161,   163,   164,   165,   166,   167,
     168,   386,     0,     0,     0,   384,   378,   383,     0,   376,
     381,   379,   380,   382,   397,   399,     0,   393,   395,   396,
       0,     0,   366,   282,     0,   279,   280,   299,     0,   296,
     297,   325,     0,   322,   323,   355,     0,    57,     0,     0,
     408,    90,     0,     0,     0,     0,     0,     0,     0,    96,
      98,     0,   176,     0,   226,   217,     0,   260,   251,     0,
       0,   124,     0,     0,   132,     0,   358,     0,   141,     0,
       0,     0,     0,     0,     0,     0,     0,   160,     0,     0,
       0,     0,     0,   375,     0,     0,     0,   392,   402,   373,
       0,   277,     0,     0,   294,     0,   329,   320,     0,     0,
     354,     0,   410,     0,     0,     0,   120,   121,   122,   100,
       0,   180,     0,   221,     0,   255,   126,    41,   134,   360,
       0,   145,   169,   170,   171,   172,   173,   174,   162,     0,
     385,   388,   389,   377,     0,     0,   394,     0,   281,     0,
     298,     0,   324,     0,     0,   113,   115,   117,   182,   223,
     257,   147,   387,   398,   400,   283,   300,   326,   356,   416,
       0,   414,     0,     0,   413,   428,     0,   426,   424,   420,
       0,   418,   422,   423,   421,   415,     0,     0,     0,     0,
     417,     0,   425,     0,   419,     0,   427,   432,     0,   430,
       0,     0,   429,   436,     0,   434,   431,     0,     0,   433,
       0,   435,   437
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,     3,  -428,  -428,  -428,  -428,    34,  -428,
    -428,  -222,  -428,   -39,  -428,   -58,  -428,  -428,  -428,   217,
    -428,  -428,  -428,  -428,    55,   195,   -41,   -38,   -37,   -36,
    -428,  -428,  -428,  -428,  -428,    53,  -428,  -428,  -428,  -428,
    -428,    50,  -108,  -399,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,   -65,  -428,  -427,  -428,  -428,  -428,  -428,  -428,  -117,
    -415,  -428,  -428,  -428,  -428,  -119,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -123,  -428,  -428,  -428,  -120,   157,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -118,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,   -94,  -428,  -428,
    -428,   -91,   199,  -428,  -428,  -428,  -428,  -428,  -428,  -405,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,   -93,
    -428,  -428,  -428,   -90,  -428,   175,  -428,   -51,  -428,  -428,
    -428,  -428,   -49,  -428,  -428,  -428,  -428,  -428,   -50,  -428,
    -428,  -428,   -87,  -428,  -428,  -428,   -88,  -428,   181,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -115,
    -428,  -428,  -428,  -116,   209,  -428,  -428,  -428,  -428,  -428,
    -428,  -113,  -428,  -428,  -428,  -114,   207,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -112,  -428,
    -428,  -428,  -109,  -428,   196,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,    79,  -428,  -428,
    -428,  -428,  -428,  -428,   -85,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,   -98,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,   -48,  -428,
    -428,  -428,  -174,  -428,  -428,  -185,  -428,  -428,  -428,  -428,
    -428,  -428,  -196,  -428,  -428,  -200,  -428
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   424,   505,    69,    70,   107,    37,    58,    80,    81,
      82,   249,    39,    59,   108,   109,   110,   111,   112,   113,
     114,   115,   256,    41,    60,   132,   279,   116,   257,   117,
     258,   476,   477,   209,   313,   479,   572,   480,   573,   481,
     574,   210,   314,   483,   484,   485,   118,   267,   501,   502,
     503,   504,   119,   269,   508,   509,   510,   120,   268,   121,
     271,   514,   515,   516,   597,    55,    67,   240,   241,   242,
     326,   243,   327,   122,   272,   523,   524,   525,   526,   527,
     528,   529,   530,   123,   264,   488,   489,   490,   581,    43,
      61,   150,   151,   152,   284,   153,   285,   154,   286,   155,
     290,   156,   289,   157,   158,   124,   265,   492,   493,   494,
     584,    51,    65,   211,   212,   213,   214,   215,   216,   217,
     218,   317,   219,   316,   220,   221,   318,   222,   125,   266,
     496,   497,   498,   587,    53,    66,   229,   230,   231,   232,
     233,   322,   234,   235,   236,   160,   282,   554,   555,   556,
     620,    45,    62,   167,   168,   169,   295,   161,   283,   558,
     559,   560,   623,    47,    63,   177,   178,   179,   298,   180,
     181,   300,   182,   183,   162,   291,   562,   563,   564,   626,
      49,    64,   192,   193,   194,   195,   306,   196,   307,   197,
     308,   198,   309,   199,   310,   200,   305,   163,   292,   566,
     629,   126,   270,   512,   281,   365,   366,   367,   368,   369,
     433,   127,   273,   538,   539,   540,   541,   608,   542,   543,
     128,   129,   275,   546,   547,   548,   614,   549,   615,   130,
     276,    83,   251,    84,   252,    85,   250,   465,   466,   467,
     568,   690,   691,   692,   700,   701,   702,   703,   708,   704,
     706,   718,   719,   720,   724,   725,   727
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   226,   537,   145,   165,   175,   190,   208,   225,   239,
     507,   159,   166,   176,   191,   227,    32,   228,   478,   478,
     146,   511,   133,   147,   148,   149,    74,    25,   133,    26,
     536,    27,   499,   237,   238,    24,   254,    89,    90,    91,
      92,   255,   237,   238,    96,   201,   469,   470,   471,   472,
     473,   474,    71,   134,   201,   135,    96,    96,   472,    36,
     202,   136,   137,   138,   139,   140,   141,   164,   499,   506,
      38,    78,   142,   143,    96,   202,   500,   131,   142,   144,
     277,    86,   184,    87,    88,   278,   185,   186,   187,   188,
     189,    96,    89,    90,    91,    92,    93,    94,    95,    96,
      40,   361,    75,   170,   171,   172,   173,   174,    76,    77,
      42,   202,   223,   203,   204,   224,   531,   532,   533,   534,
      78,    78,    97,    98,    99,   100,    44,    28,    29,    30,
      31,   202,    78,    78,   590,    78,   101,   591,   432,   102,
     293,    46,   201,   296,    78,   294,   103,   244,   297,   303,
      78,   104,   105,   328,   304,   106,   277,   202,   329,   203,
     204,   567,   205,   206,   207,    48,   569,    78,   448,   449,
     450,   570,   578,   544,   545,    78,   578,   579,   507,   478,
     246,   580,   606,   612,    50,   537,    78,   607,   613,   695,
     649,   696,   697,    52,   593,    54,    79,   594,   517,   518,
     519,   520,   521,   522,   616,   248,    78,   293,   595,   617,
     618,   596,   678,   536,   328,   296,   363,   303,   245,   681,
     685,   709,   686,   362,   728,   693,   710,   721,   694,   729,
     722,   364,    78,   247,   248,   145,   253,   259,   165,   260,
     261,   262,   263,   159,   274,   175,   166,   280,   330,   331,
     287,   288,   146,   176,   190,   147,   148,   149,   299,   301,
     226,   302,   191,   208,   311,   312,   320,   225,   315,   319,
     321,   324,   323,   325,   227,   332,   228,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   333,   334,
     335,   336,   338,   339,   340,   341,   342,   346,   343,   344,
     345,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     357,   358,   356,   360,   370,   371,   372,   373,   374,   375,
     377,   378,   379,   380,   376,   382,   384,   386,   390,   385,
     391,   392,   387,   388,   393,   394,   395,   397,   414,   415,
     398,   400,   401,   402,   405,   408,   409,   399,   411,   435,
     403,   406,   482,   482,   412,   413,   416,   417,   418,   475,
     475,   419,   420,   421,   422,   423,   425,   426,   427,   436,
     363,   535,   428,   429,   430,   431,   437,   362,   434,   438,
     439,   440,   441,   442,   443,   364,   445,   444,   446,   487,
     491,   495,   513,   551,   553,   557,   447,   451,   561,   452,
     453,   454,   571,   575,   576,   577,   600,   583,   565,   582,
     586,   585,   461,   455,   462,   588,   589,   598,   599,   622,
     456,   464,   601,   602,   603,   457,   604,   605,   609,   610,
     458,   611,   621,   459,   460,   624,   625,   627,   628,   689,
     619,   631,   630,   633,   634,   635,   679,   659,   647,   664,
     665,   673,   680,   636,   674,   707,   687,   711,   637,   713,
     652,   638,   715,   717,   730,   550,   592,   463,   486,   468,
     639,   337,   359,   646,   648,   653,   651,   650,   654,   655,
     656,   657,   660,   661,   662,   410,   675,   723,   658,   641,
     640,   676,   381,   643,   642,   677,   404,   682,   683,   644,
     684,   688,   645,   712,   667,   383,   407,   668,   396,   669,
     389,   716,   670,   482,   552,   732,   672,   671,   666,   705,
     475,   632,   226,   145,   714,   726,   208,   663,   731,   225,
       0,   159,     0,     0,     0,     0,   227,     0,   228,   239,
     146,     0,     0,   147,   148,   149,     0,     0,     0,     0,
       0,     0,     0,     0,   535,     0,     0,     0,     0,     0,
       0,     0,   165,     0,     0,   175,     0,     0,   190,     0,
     166,     0,     0,   176,     0,     0,   191,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   699,     0,     0,
       0,     0,     0,     0,   698,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   699,     0,     0,     0,     0,     0,
       0,   698
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,   429,    61,    62,    63,    64,    65,    66,    67,
     425,    61,    62,    63,    64,    66,    13,    66,   417,   418,
      61,   426,     7,    61,    61,    61,    10,     5,     7,     7,
     429,     9,    61,    67,    68,     0,     3,    22,    23,    24,
      25,     8,    67,    68,    29,    15,    16,    17,    18,    19,
      20,    21,   105,    38,    15,    40,    29,    29,    19,     7,
      30,    46,    47,    48,    49,    50,    51,    39,    61,    62,
       7,   105,    57,    58,    29,    30,   105,    12,    57,    64,
       3,    11,    55,    13,    14,     8,    59,    60,    61,    62,
      63,    29,    22,    23,    24,    25,    26,    27,    28,    29,
       7,    56,    86,    41,    42,    43,    44,    45,    92,    93,
       7,    30,    31,    32,    33,    34,    77,    78,    79,    80,
     105,   105,    52,    53,    54,    55,     7,   105,   106,   107,
     108,    30,   105,   105,     3,   105,    66,     6,   360,    69,
       3,     7,    15,     3,   105,     8,    76,     6,     8,     3,
     105,    81,    82,     3,     8,    85,     3,    30,     8,    32,
      33,     8,    35,    36,    37,     7,     3,   105,   390,   391,
     392,     8,     3,    83,    84,   105,     3,     8,   593,   578,
       4,     8,     3,     3,     7,   612,   105,     8,     8,    88,
     595,    90,    91,     7,     3,     7,   254,     6,    70,    71,
      72,    73,    74,    75,     3,     3,   105,     3,     3,     8,
       8,     6,     8,   612,     3,     3,   281,     3,     3,     8,
       8,     3,     8,   281,     3,     3,     8,     3,     6,     8,
       6,   281,   105,     8,     3,   293,     4,     4,   296,     4,
       4,     4,     4,   293,     4,   303,   296,     8,   245,   246,
       4,     4,   293,   303,   312,   293,   293,   293,     4,     4,
     325,     4,   312,   321,     8,     3,     8,   325,     4,     4,
       3,     8,     4,     3,   325,   105,   325,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,     4,     4,
       4,     4,     4,     4,     4,   106,   106,     4,   106,   106,
     106,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   106,     4,     4,     4,     4,     4,     4,   106,
       4,     4,     4,     4,   108,     4,     4,     4,     4,   106,
       4,     4,   106,   106,     4,     4,     4,     4,   335,   336,
       4,     4,     4,     4,     4,     4,     4,   106,     4,     3,
     108,   108,   417,   418,     7,     7,     7,     7,     7,   417,
     418,     5,     5,     5,     5,     5,     5,     5,     5,     5,
     435,   429,     7,     7,     7,     7,     5,   435,     8,   105,
     105,   105,   105,   105,     5,   435,   105,     7,   105,     7,
       7,     7,     7,     4,     7,     7,   105,   105,     7,   105,
     105,   105,     8,     4,     4,     4,     4,     3,    65,     6,
       3,     6,   409,   105,   411,     6,     3,     6,     3,     3,
     105,    87,     4,     4,     4,   105,     4,     4,     4,     4,
     105,     4,     6,   105,   105,     6,     3,     6,     3,     7,
     105,     4,     8,     4,     4,     4,     8,     4,     6,     4,
       4,     4,     8,   108,     5,     4,     8,     4,   106,     4,
     106,   108,     5,     7,     4,   431,   505,   412,   418,   416,
     578,   254,   277,   590,   593,   106,   599,   597,   106,   106,
     106,   106,   106,   106,   106,   328,   105,    89,   606,   583,
     581,   105,   293,   586,   584,   105,   321,   105,   105,   587,
     105,   105,   589,   106,   620,   296,   325,   622,   312,   623,
     303,   105,   625,   578,   435,   105,   628,   626,   616,   693,
     578,   569,   587,   581,   709,   721,   584,   612,   728,   587,
      -1,   581,    -1,    -1,    -1,    -1,   587,    -1,   587,   597,
     581,    -1,    -1,   581,   581,   581,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   612,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   620,    -1,    -1,   623,    -1,    -1,   626,    -1,
     620,    -1,    -1,   623,    -1,    -1,   626,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   692,    -1,    -1,
      -1,    -1,    -1,    -1,   692,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   709,    -1,    -1,    -1,    -1,    -1,
      -1,   709
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,     0,     5,     7,     9,   105,   106,
     107,   108,   122,   123,   124,   128,     7,   135,     7,   141,
       7,   152,     7,   218,     7,   280,     7,   292,     7,   309,
       7,   240,     7,   263,     7,   194,   129,   125,   136,   142,
     153,   219,   281,   293,   310,   241,   264,   195,   122,   132,
     133,   105,   126,   127,    10,    86,    92,    93,   105,   134,
     137,   138,   139,   360,   362,   364,    11,    13,    14,    22,
      23,    24,    25,    26,    27,    28,    29,    52,    53,    54,
      55,    66,    69,    76,    81,    82,    85,   134,   143,   144,
     145,   146,   147,   148,   149,   150,   156,   158,   175,   181,
     186,   188,   202,   212,   234,   257,   330,   340,   349,   350,
     358,    12,   154,     7,    38,    40,    46,    47,    48,    49,
      50,    51,    57,    58,    64,   134,   145,   146,   147,   148,
     220,   221,   222,   224,   226,   228,   230,   232,   233,   257,
     274,   286,   303,   326,    39,   134,   257,   282,   283,   284,
      41,    42,    43,    44,    45,   134,   257,   294,   295,   296,
     298,   299,   301,   302,    55,    59,    60,    61,    62,    63,
     134,   257,   311,   312,   313,   314,   316,   318,   320,   322,
     324,    15,    30,    32,    33,    35,    36,    37,   134,   162,
     170,   242,   243,   244,   245,   246,   247,   248,   249,   251,
     253,   254,   256,    31,    34,   134,   170,   246,   251,   265,
     266,   267,   268,   269,   271,   272,   273,    67,    68,   134,
     196,   197,   198,   200,     6,     3,     4,     8,     3,   140,
     365,   361,   363,     4,     3,     8,   151,   157,   159,     4,
       4,     4,     4,     4,   213,   235,   258,   176,   187,   182,
     331,   189,   203,   341,     4,   351,   359,     3,     8,   155,
       8,   333,   275,   287,   223,   225,   227,     4,     4,   231,
     229,   304,   327,     3,     8,   285,     3,     8,   297,     4,
     300,     4,     4,     3,     8,   325,   315,   317,   319,   321,
     323,     8,     3,   163,   171,     4,   252,   250,   255,     4,
       8,     3,   270,     4,     8,     3,   199,   201,     3,     8,
     122,   122,   105,     4,     4,     4,     4,   138,     4,     4,
       4,   106,   106,   106,   106,   106,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   106,     4,     4,   144,
       4,    56,   134,   170,   257,   334,   335,   336,   337,   338,
       4,     4,     4,     4,     4,   106,   108,     4,     4,     4,
       4,   221,     4,   283,     4,   106,     4,   106,   106,   295,
       4,     4,     4,     4,     4,     4,   313,     4,     4,   106,
       4,     4,     4,   108,   244,     4,   108,   267,     4,     4,
     197,     4,     7,     7,   122,   122,     7,     7,     7,     5,
       5,     5,     5,     5,   130,     5,     5,     5,     7,     7,
       7,     7,   130,   339,     8,     3,     5,     5,   105,   105,
     105,   105,   105,     5,     7,   105,   105,   105,   130,   130,
     130,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   122,   122,   143,    87,   366,   367,   368,   154,    16,
      17,    18,    19,    20,    21,   134,   160,   161,   162,   164,
     166,   168,   170,   172,   173,   174,   160,     7,   214,   215,
     216,     7,   236,   237,   238,     7,   259,   260,   261,    61,
     105,   177,   178,   179,   180,   131,    62,   179,   183,   184,
     185,   228,   332,     7,   190,   191,   192,    70,    71,    72,
      73,    74,    75,   204,   205,   206,   207,   208,   209,   210,
     211,    77,    78,    79,    80,   134,   162,   172,   342,   343,
     344,   345,   347,   348,    83,    84,   352,   353,   354,   356,
     127,     4,   336,     7,   276,   277,   278,     7,   288,   289,
     290,     7,   305,   306,   307,    65,   328,     8,   369,     3,
       8,     8,   165,   167,   169,     4,     4,     4,     3,     8,
       8,   217,     6,     3,   239,     6,     3,   262,     6,     3,
       3,     6,   132,     3,     6,     3,     6,   193,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   346,     4,
       4,     4,     3,     8,   355,   357,     3,     8,     8,   105,
     279,     6,     3,   291,     6,     3,   308,     6,     3,   329,
       8,     4,   367,     4,     4,     4,   108,   106,   108,   161,
     220,   216,   242,   238,   265,   261,   178,     6,   184,   228,
     196,   192,   106,   106,   106,   106,   106,   106,   205,     4,
     106,   106,   106,   343,     4,     4,   353,   282,   278,   294,
     290,   311,   307,     4,     5,   105,   105,   105,     8,     8,
       8,     8,   105,   105,   105,     8,     8,     8,   105,     7,
     370,   371,   372,     3,     6,    88,    90,    91,   134,   170,
     373,   374,   375,   376,   378,   371,   379,     4,   377,     3,
       8,     4,   106,     4,   374,     5,   105,     7,   380,   381,
     382,     3,     6,    89,   383,   384,   381,   385,     3,     8,
       4,   384,   105
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   109,   111,   110,   112,   110,   113,   110,   114,   110,
     115,   110,   116,   110,   117,   110,   118,   110,   119,   110,
     120,   110,   121,   110,   122,   122,   122,   122,   122,   122,
     122,   123,   125,   124,   126,   126,   127,   127,   129,   128,
     131,   130,   132,   132,   133,   133,   134,   136,   135,   137,
     137,   138,   138,   138,   138,   138,   140,   139,   142,   141,
     143,   143,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   145,   146,   147,   148,   149,   151,
     150,   153,   152,   155,   154,   157,   156,   159,   158,   160,
     160,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     163,   162,   165,   164,   167,   166,   169,   168,   171,   170,
     172,   173,   174,   176,   175,   177,   177,   178,   178,   179,
     180,   182,   181,   183,   183,   184,   184,   185,   187,   186,
     189,   188,   190,   190,   191,   191,   193,   192,   195,   194,
     196,   196,   196,   197,   197,   199,   198,   201,   200,   203,
     202,   204,   204,   205,   205,   205,   205,   205,   205,   206,
     207,   208,   209,   210,   211,   213,   212,   214,   214,   215,
     215,   217,   216,   219,   218,   220,   220,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   223,   222,   225,   224,   227,   226,
     229,   228,   231,   230,   232,   233,   235,   234,   236,   236,
     237,   237,   239,   238,   241,   240,   242,   242,   243,   243,
     244,   244,   244,   244,   244,   244,   244,   244,   245,   246,
     247,   248,   250,   249,   252,   251,   253,   255,   254,   256,
     258,   257,   259,   259,   260,   260,   262,   261,   264,   263,
     265,   265,   266,   266,   267,   267,   267,   267,   267,   267,
     268,   270,   269,   271,   272,   273,   275,   274,   276,   276,
     277,   277,   279,   278,   281,   280,   282,   282,   283,   283,
     283,   285,   284,   287,   286,   288,   288,   289,   289,   291,
     290,   293,   292,   294,   294,   295,   295,   295,   295,   295,
     295,   295,   297,   296,   298,   300,   299,   301,   302,   304,
     303,   305,   305,   306,   306,   308,   307,   310,   309,   311,
     311,   312,   312,   313,   313,   313,   313,   313,   313,   313,
     313,   315,   314,   317,   316,   319,   318,   321,   320,   323,
     322,   325,   324,   327,   326,   329,   328,   331,   330,   332,
     332,   333,   228,   334,   334,   335,   335,   336,   336,   336,
     336,   337,   339,   338,   341,   340,   342,   342,   343,   343,
     343,   343,   343,   343,   343,   344,   346,   345,   347,   348,
     349,   351,   350,   352,   352,   353,   353,   355,   354,   357,
     356,   359,   358,   361,   360,   363,   362,   365,   364,   366,
     366,   367,   369,   368,   370,   370,   372,   371,   373,   373,
     374,   374,   374,   374,   374,   375,   377,   376,   379,   378,
     380,   380,   382,   381,   383,   383,   385,   384
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     1,     3,     5,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     0,
       6,     0,     4,     0,     4,     0,     6,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     0,     6,     1,     3,     1,     1,     1,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
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
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"Dhcp4\"", "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "value",
  "sub_json", "map2", "$@12", "map_content", "not_empty_map",
  "list_generic", "$@13", "list2", "$@14", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@15",
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
  "code", "option_def_code", "option_def_type", "option_def_record_types",
  "$@48", "space", "$@49", "option_def_space", "option_def_encapsulate",
  "$@50", "option_def_array", "option_data_list", "$@51",
  "option_data_list_content", "not_empty_option_data_list",
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
       0,   204,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   209,   209,   210,   210,   211,   211,   212,   212,
     213,   213,   214,   214,   222,   223,   224,   225,   226,   227,
     228,   231,   236,   236,   248,   249,   252,   256,   263,   263,
     271,   271,   278,   279,   282,   286,   297,   307,   307,   319,
     320,   324,   325,   326,   327,   328,   331,   331,   348,   348,
     356,   357,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   386,   391,   396,   401,   406,   411,
     411,   421,   421,   429,   429,   439,   439,   449,   449,   459,
     460,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     474,   474,   482,   482,   490,   490,   498,   498,   506,   506,
     514,   519,   524,   529,   529,   539,   540,   543,   544,   547,
     552,   557,   557,   567,   568,   571,   572,   575,   580,   580,
     590,   590,   600,   601,   604,   605,   608,   608,   616,   616,
     624,   625,   626,   629,   630,   633,   633,   641,   641,   649,
     649,   659,   660,   663,   664,   665,   666,   667,   668,   671,
     676,   681,   686,   691,   696,   704,   704,   717,   718,   721,
     722,   729,   729,   752,   752,   761,   762,   766,   767,   768,
     769,   770,   771,   772,   773,   774,   775,   776,   777,   778,
     779,   780,   781,   782,   785,   785,   793,   793,   801,   801,
     809,   809,   817,   817,   825,   830,   839,   839,   851,   852,
     855,   856,   861,   861,   872,   872,   882,   883,   886,   887,
     890,   891,   892,   893,   894,   895,   896,   897,   900,   902,
     907,   909,   911,   911,   919,   919,   927,   929,   929,   937,
     946,   946,   958,   959,   964,   965,   970,   970,   981,   981,
     992,   993,   998,   999,  1004,  1005,  1006,  1007,  1008,  1009,
    1012,  1014,  1014,  1022,  1024,  1026,  1034,  1034,  1046,  1047,
    1050,  1051,  1054,  1054,  1062,  1062,  1070,  1071,  1074,  1075,
    1076,  1079,  1079,  1090,  1090,  1102,  1103,  1106,  1107,  1110,
    1110,  1118,  1118,  1126,  1127,  1130,  1131,  1132,  1133,  1134,
    1135,  1136,  1139,  1139,  1147,  1152,  1152,  1160,  1165,  1173,
    1173,  1183,  1184,  1187,  1188,  1191,  1191,  1199,  1199,  1207,
    1208,  1211,  1212,  1216,  1217,  1218,  1219,  1220,  1221,  1222,
    1223,  1226,  1226,  1236,  1236,  1246,  1246,  1254,  1254,  1262,
    1262,  1270,  1270,  1283,  1283,  1293,  1293,  1304,  1304,  1314,
    1315,  1318,  1318,  1326,  1327,  1330,  1331,  1334,  1335,  1336,
    1337,  1340,  1342,  1342,  1353,  1353,  1363,  1364,  1367,  1368,
    1369,  1370,  1371,  1372,  1373,  1376,  1381,  1381,  1389,  1394,
    1401,  1408,  1408,  1418,  1419,  1422,  1423,  1426,  1426,  1434,
    1434,  1444,  1444,  1456,  1456,  1463,  1463,  1475,  1475,  1488,
    1489,  1493,  1497,  1497,  1509,  1510,  1514,  1514,  1522,  1523,
    1526,  1527,  1528,  1529,  1530,  1533,  1537,  1537,  1545,  1545,
    1555,  1556,  1559,  1559,  1567,  1568,  1571,  1571
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
#line 3575 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1579 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
