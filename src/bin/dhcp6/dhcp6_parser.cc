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

  case 40:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 325 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 332 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 410 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 981 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 992 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1236 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1356 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 697 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1582 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 978 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1003 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1022 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1840 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1867 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1103 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1118 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 1939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1155 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1163 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1200 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1212 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1218 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2088 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1228 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1234 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2186 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1347 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1372 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2396 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2416 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2471 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2501 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2527 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2537 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
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
     110,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,    28,    22,    34,    47,    51,    60,    63,    67,
      87,   106,   119,   128,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,    22,    -1,    16,    64,
     150,    15,    56,    39,    91,   112,     2,    32,  -428,   135,
     161,   170,   174,   181,  -428,  -428,  -428,  -428,   228,  -428,
      68,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,   240,
     243,   254,   255,   257,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,   260,  -428,  -428,  -428,   129,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,   185,  -428,  -428,  -428,  -428,  -428,  -428,   261,
     262,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
     157,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,   158,  -428,  -428,
    -428,   264,  -428,   265,   266,  -428,  -428,   167,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,   222,   268,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,   269,  -428,  -428,  -428,   271,  -428,  -428,
    -428,   270,   274,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,   275,  -428,  -428,  -428,  -428,   272,
     278,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
     168,  -428,  -428,  -428,  -428,    22,    22,  -428,   183,   279,
     280,   281,   282,  -428,    16,  -428,   283,   284,   285,   172,
     190,   191,   192,   193,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   204,   301,   302,    64,  -428,   303,
    -428,    13,   304,   305,   306,   307,   308,   213,   212,   311,
     312,   313,   314,    15,  -428,   315,    56,  -428,   316,   221,
     318,   223,   224,    39,  -428,   321,   322,   323,   324,   325,
     326,  -428,    91,   327,   328,   235,   329,   330,   332,   238,
    -428,   112,   333,   239,  -428,     2,   338,   339,    38,  -428,
    -428,  -428,   340,   341,   342,    22,    22,  -428,   343,   344,
     347,  -428,  -428,  -428,  -428,  -428,   350,   351,   352,   353,
     356,   357,   358,   359,   360,   361,  -428,   362,   365,  -428,
     356,  -428,  -428,  -428,  -428,   337,   363,  -428,  -428,  -428,
     368,   369,   247,   248,   276,  -428,  -428,   277,   287,   373,
     372,  -428,   288,  -428,   289,  -428,   300,  -428,  -428,  -428,
     356,   356,   356,   309,   310,   317,  -428,   319,   320,  -428,
     331,   334,   335,  -428,  -428,   336,  -428,  -428,   345,    22,
    -428,    22,    64,   346,  -428,  -428,   150,    30,    30,   374,
     375,   376,    -2,  -428,  -428,   180,    50,   377,   348,    37,
     173,    -1,  -428,   385,  -428,    13,   383,   384,  -428,  -428,
    -428,  -428,  -428,   386,   355,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,   169,  -428,   175,  -428,  -428,   387,  -428,
    -428,  -428,   388,   390,   392,  -428,   177,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,   178,  -428,   391,   395,
    -428,  -428,   394,   398,  -428,  -428,   396,   400,  -428,  -428,
    -428,   122,  -428,  -428,  -428,    22,  -428,  -428,   188,  -428,
    -428,  -428,   189,  -428,   399,   401,  -428,   402,   206,  -428,
    -428,   403,   406,   407,  -428,  -428,  -428,   207,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,   209,  -428,  -428,  -428,   210,
     349,  -428,  -428,   409,   410,  -428,  -428,   411,   418,  -428,
    -428,   416,   420,  -428,  -428,   417,  -428,   422,   346,  -428,
    -428,   424,   425,   427,   263,   354,   364,    30,  -428,  -428,
      15,  -428,   374,   112,  -428,   375,     2,  -428,   376,    -2,
    -428,   426,   180,  -428,    50,  -428,    32,  -428,   377,   367,
     348,  -428,   432,   370,   371,   378,    37,  -428,   433,   434,
     173,  -428,  -428,  -428,    56,  -428,   383,    39,  -428,   384,
      91,  -428,   386,   435,  -428,   419,  -428,   366,   380,   381,
    -428,  -428,  -428,  -428,   216,  -428,   437,  -428,   438,  -428,
    -428,  -428,  -428,  -428,   217,  -428,  -428,  -428,   382,  -428,
    -428,  -428,  -428,   389,   393,  -428,   218,  -428,   219,  -428,
     441,  -428,   397,   436,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,   233,
    -428,    74,   436,  -428,  -428,   446,  -428,  -428,  -428,   225,
    -428,  -428,  -428,  -428,  -428,   447,   404,   448,    74,  -428,
     450,  -428,   408,  -428,   449,  -428,  -428,   234,  -428,   379,
     449,  -428,  -428,   226,  -428,  -428,   453,   379,  -428,   414,
    -428,  -428
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      91,     9,   172,    11,   273,    13,   290,    15,   316,    17,
     213,    19,   247,    21,   148,    23,    42,    34,     0,     0,
       0,     0,     0,     0,   318,   215,   249,     0,    44,     0,
      43,     0,     0,    35,    56,   396,   392,   394,     0,    55,
       0,    49,    51,    53,    54,    52,    89,    95,    97,     0,
       0,     0,     0,     0,   164,   205,   239,   123,   138,   131,
     346,   140,   159,   363,     0,   380,   390,    83,     0,    60,
      62,    63,    64,    65,    66,    68,    69,    70,    71,    73,
      72,    77,    78,    67,    75,    76,    74,    79,    80,    81,
      82,    93,     0,   350,   265,   282,   193,   195,   197,     0,
       0,   201,   199,   308,   342,   192,   176,   177,   178,   179,
       0,   174,   183,   184,   185,   188,   190,   186,   187,   180,
     181,   182,   189,   191,   280,   279,   278,     0,   275,   277,
     301,     0,   304,     0,     0,   300,   297,     0,   292,   294,
     295,   298,   299,   296,   340,   330,   332,   334,   336,   338,
     329,   328,     0,   319,   320,   324,   325,   322,   326,   327,
     323,   110,   118,     0,   233,   231,   236,     0,   226,   230,
     227,     0,   216,   217,   219,   229,   220,   221,   222,   235,
     223,   224,   225,   260,     0,   258,   259,   262,   263,     0,
     250,   251,   253,   254,   255,   256,   257,   155,   157,   152,
       0,   150,   153,   154,    39,     0,     0,    33,     0,     0,
       0,     0,     0,    46,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
      92,   352,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,     0,     0,   274,     0,     0,
       0,     0,     0,     0,   291,     0,     0,     0,     0,     0,
       0,   317,     0,     0,     0,     0,     0,     0,     0,     0,
     214,     0,     0,     0,   248,     0,     0,     0,     0,   149,
      45,    36,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    84,    85,    86,    87,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   379,     0,     0,    61,
       0,   361,   359,   360,   358,     0,   353,   354,   356,   357,
       0,     0,     0,     0,     0,   203,   204,     0,     0,     0,
       0,   175,     0,   276,     0,   303,     0,   306,   307,   293,
       0,     0,     0,     0,     0,     0,   321,     0,     0,   228,
       0,     0,     0,   238,   218,     0,   264,   252,     0,     0,
     151,     0,     0,     0,   393,   395,     0,     0,     0,   166,
     207,   241,     0,    40,   139,     0,     0,   142,     0,     0,
       0,     0,    94,     0,   351,     0,   267,   284,   194,   196,
     198,   202,   200,   310,     0,   281,   302,   305,   341,   331,
     333,   335,   337,   339,   111,   119,   234,   232,   237,   261,
     156,   158,    37,     0,   401,     0,   398,   400,     0,   112,
     114,   116,     0,     0,     0,   109,     0,    99,   101,   102,
     103,   104,   105,   106,   107,   108,     0,   170,     0,   167,
     168,   211,     0,   208,   209,   245,     0,   242,   243,   129,
     130,     0,   125,   127,   128,    42,   137,   135,     0,   133,
     136,   348,     0,   146,     0,   143,   144,     0,     0,   161,
     375,     0,     0,     0,   373,   367,   372,     0,   365,   370,
     368,   369,   371,   386,   388,     0,   382,   384,   385,     0,
       0,   355,   271,     0,   268,   269,   288,     0,   285,   286,
     314,     0,   311,   312,   344,     0,    57,     0,     0,   397,
      90,     0,     0,     0,     0,     0,     0,     0,    96,    98,
       0,   165,     0,   215,   206,     0,   249,   240,     0,     0,
     124,     0,     0,   132,     0,   347,     0,   141,     0,     0,
       0,   160,     0,     0,     0,     0,     0,   364,     0,     0,
       0,   381,   391,   362,     0,   266,     0,     0,   283,     0,
     318,   309,     0,     0,   343,     0,   399,     0,     0,     0,
     120,   121,   122,   100,     0,   169,     0,   210,     0,   244,
     126,    41,   134,   349,     0,   145,   163,   162,     0,   374,
     377,   378,   366,     0,     0,   383,     0,   270,     0,   287,
       0,   313,     0,     0,   113,   115,   117,   171,   212,   246,
     147,   376,   387,   389,   272,   289,   315,   345,   405,     0,
     403,     0,     0,   402,   417,     0,   415,   413,   409,     0,
     407,   411,   412,   410,   404,     0,     0,     0,     0,   406,
       0,   414,     0,   408,     0,   416,   421,     0,   419,     0,
       0,   418,   425,     0,   423,   420,     0,     0,   422,     0,
     424,   426
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,     3,  -428,  -428,  -428,  -428,     9,  -428,
    -428,  -203,  -428,  -125,  -428,   -58,  -428,  -428,  -428,   187,
    -428,  -428,  -428,  -428,    41,   165,   -41,   -38,   -37,   -36,
    -428,  -428,  -428,  -428,  -428,    42,  -428,  -428,  -428,  -428,
    -428,    43,  -108,  -399,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,   -65,  -428,  -427,  -428,  -428,  -428,  -428,  -428,  -119,
    -415,  -428,  -428,  -428,  -428,  -118,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -120,  -428,  -428,  -428,  -123,   141,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -117,  -428,  -428,  -428,
    -428,  -100,  -428,  -428,  -428,   -96,   182,  -428,  -428,  -428,
    -428,  -428,  -428,  -405,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,   -99,  -428,  -428,  -428,   -91,  -428,   156,
    -428,   -51,  -428,  -428,  -428,  -428,   -49,  -428,  -428,  -428,
    -428,  -428,   -50,  -428,  -428,  -428,   -95,  -428,  -428,  -428,
     -92,  -428,   160,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -116,  -428,  -428,  -428,  -115,   195,  -428,
    -428,  -428,  -428,  -428,  -428,  -122,  -428,  -428,  -428,  -121,
     194,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -114,  -428,  -428,  -428,  -111,  -428,   196,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,    58,  -428,  -428,  -428,  -428,  -428,  -428,  -102,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -105,  -428,
    -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,  -428,
    -428,  -428,   -57,  -428,  -428,  -428,  -172,  -428,  -428,  -185,
    -428,  -428,  -428,  -428,  -428,  -428,  -195,  -428,  -428,  -201,
    -428
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   424,   505,    69,    70,   107,    37,    58,    80,    81,
      82,   249,    39,    59,   108,   109,   110,   111,   112,   113,
     114,   115,   256,    41,    60,   132,   279,   116,   257,   117,
     258,   476,   477,   209,   313,   479,   561,   480,   562,   481,
     563,   210,   314,   483,   484,   485,   118,   267,   501,   502,
     503,   504,   119,   269,   508,   509,   510,   120,   268,   121,
     271,   514,   515,   516,   586,    55,    67,   240,   241,   242,
     326,   243,   327,   122,   272,   518,   519,   123,   264,   488,
     489,   490,   570,    43,    61,   150,   151,   152,   284,   153,
     285,   154,   286,   155,   290,   156,   289,   157,   158,   124,
     265,   492,   493,   494,   573,    51,    65,   211,   212,   213,
     214,   215,   216,   217,   218,   317,   219,   316,   220,   221,
     318,   222,   125,   266,   496,   497,   498,   576,    53,    66,
     229,   230,   231,   232,   233,   322,   234,   235,   236,   160,
     282,   543,   544,   545,   604,    45,    62,   167,   168,   169,
     295,   161,   283,   547,   548,   549,   607,    47,    63,   177,
     178,   179,   298,   180,   181,   300,   182,   183,   162,   291,
     551,   552,   553,   610,    49,    64,   192,   193,   194,   195,
     306,   196,   307,   197,   308,   198,   309,   199,   310,   200,
     305,   163,   292,   555,   613,   126,   270,   512,   281,   365,
     366,   367,   368,   369,   433,   127,   273,   527,   528,   529,
     530,   592,   531,   532,   128,   129,   275,   535,   536,   537,
     598,   538,   599,   130,   276,    83,   251,    84,   252,    85,
     250,   465,   466,   467,   557,   669,   670,   671,   679,   680,
     681,   682,   687,   683,   685,   697,   698,   699,   703,   704,
     706
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   226,   526,   145,   165,   175,   190,   208,   225,   239,
     507,   159,   166,   176,   191,   227,    32,   228,   478,   478,
     146,   511,   133,   147,   148,   149,    74,    25,    24,    26,
     525,    27,   202,   223,   203,   204,   224,    89,    90,    91,
      92,    36,    96,   202,    96,   201,   469,   470,   471,   472,
     473,   474,   201,   134,    38,   135,   472,   133,    40,   499,
     202,   136,   137,   138,   139,   140,   141,    42,    96,   361,
      44,   254,   142,   143,    46,    86,   255,    87,    88,   144,
     170,   171,   172,   173,   174,    96,    89,    90,    91,    92,
      93,    94,    95,    96,    48,   164,    75,   500,    71,   237,
     238,    78,    76,    77,   202,   237,   238,   142,   520,   521,
     522,   523,    78,    50,    78,    78,    97,    98,    99,   100,
      96,    28,    29,    30,    31,   579,    52,   201,   580,    78,
     101,    78,   277,   102,   103,    54,    78,   278,    78,   104,
     105,   244,   202,   106,   203,   204,   184,   205,   206,   207,
     185,   186,   187,   188,   189,    78,   674,   432,   675,   676,
     293,   296,   131,    78,   245,   294,   297,   507,   478,   526,
     303,   328,   277,    78,   246,   304,   329,   556,   558,   633,
     567,   567,   247,   559,   248,   568,   569,   448,   449,   450,
      78,   582,   584,   280,   583,   585,    79,   525,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,   590,
     596,    78,   600,   248,   591,   597,   363,   601,   602,   293,
     328,   296,   303,   362,   657,   660,   664,   665,   688,   707,
     311,   364,   253,   689,   708,   145,   672,   700,   165,   673,
     701,   499,   506,   159,   259,   175,   166,   260,   330,   331,
     533,   534,   146,   176,   190,   147,   148,   149,   261,   262,
     226,   263,   191,   208,   274,   287,   288,   225,   299,   301,
     302,   312,   341,   315,   227,   319,   228,   321,   320,   323,
     324,   325,   332,   333,   334,   335,   336,   338,   339,   340,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   360,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   382,
     384,   385,   386,   387,   388,   390,   391,   392,   393,   394,
     395,   397,   398,   400,   401,   399,   402,   405,   414,   415,
     403,   406,   408,   409,   411,   434,   438,   439,   412,   413,
     416,   417,   482,   482,   418,   419,   420,   421,   422,   475,
     475,   423,   425,   426,   427,   620,   435,   428,   429,   430,
     363,   524,   431,   436,   437,   440,   441,   362,   443,   444,
     581,   487,   491,   495,   513,   364,   442,   445,   446,   540,
     542,   546,   564,   550,   565,   560,   566,   571,   572,   447,
     574,   575,   577,   578,   588,   587,   589,   593,   451,   452,
     594,   595,   461,   606,   462,   605,   453,   608,   454,   455,
     554,   609,   611,   612,   653,   614,   615,   464,   617,   618,
     456,   619,   631,   457,   458,   459,   638,   643,   644,   652,
     539,   337,   359,   668,   460,   658,   659,   517,   603,   666,
     686,   690,   692,   463,   621,   694,   696,   709,   468,   623,
     630,   486,   702,   634,   632,   654,   622,   636,   635,   410,
     639,   640,   625,   637,   624,   381,   627,   404,   641,   655,
     656,   661,   626,   629,   628,   407,   648,   649,   662,   646,
     647,   383,   663,   541,   642,   645,   667,   389,   651,   650,
     684,   616,   482,   693,   691,   705,   710,   695,   396,   475,
       0,   226,   145,   711,     0,   208,     0,     0,   225,     0,
     159,     0,     0,     0,     0,   227,     0,   228,   239,   146,
       0,     0,   147,   148,   149,     0,     0,     0,   524,     0,
       0,     0,     0,     0,     0,     0,   165,     0,     0,   175,
       0,     0,   190,     0,   166,     0,     0,   176,     0,     0,
     191,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   678,     0,     0,     0,
       0,     0,     0,   677,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   678,     0,     0,     0,     0,     0,     0,
     677
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,   429,    61,    62,    63,    64,    65,    66,    67,
     425,    61,    62,    63,    64,    66,    13,    66,   417,   418,
      61,   426,     7,    61,    61,    61,    10,     5,     0,     7,
     429,     9,    30,    31,    32,    33,    34,    22,    23,    24,
      25,     7,    29,    30,    29,    15,    16,    17,    18,    19,
      20,    21,    15,    38,     7,    40,    19,     7,     7,    61,
      30,    46,    47,    48,    49,    50,    51,     7,    29,    56,
       7,     3,    57,    58,     7,    11,     8,    13,    14,    64,
      41,    42,    43,    44,    45,    29,    22,    23,    24,    25,
      26,    27,    28,    29,     7,    39,    80,    99,    99,    67,
      68,    99,    86,    87,    30,    67,    68,    57,    71,    72,
      73,    74,    99,     7,    99,    99,    52,    53,    54,    55,
      29,    99,   100,   101,   102,     3,     7,    15,     6,    99,
      66,    99,     3,    69,    70,     7,    99,     8,    99,    75,
      76,     6,    30,    79,    32,    33,    55,    35,    36,    37,
      59,    60,    61,    62,    63,    99,    82,   360,    84,    85,
       3,     3,    12,    99,     3,     8,     8,   582,   567,   596,
       3,     3,     3,    99,     4,     8,     8,     8,     3,   584,
       3,     3,     8,     8,     3,     8,     8,   390,   391,   392,
      99,     3,     3,     8,     6,     6,   254,   596,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,     3,
       3,    99,     3,     3,     8,     8,   281,     8,     8,     3,
       3,     3,     3,   281,     8,     8,     8,     8,     3,     3,
       8,   281,     4,     8,     8,   293,     3,     3,   296,     6,
       6,    61,    62,   293,     4,   303,   296,     4,   245,   246,
      77,    78,   293,   303,   312,   293,   293,   293,     4,     4,
     325,     4,   312,   321,     4,     4,     4,   325,     4,     4,
       4,     3,   100,     4,   325,     4,   325,     3,     8,     4,
       8,     3,    99,     4,     4,     4,     4,     4,     4,     4,
     100,   100,   100,   100,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   100,     4,     4,     4,     4,     4,
       4,     4,     4,   100,   102,     4,     4,     4,     4,     4,
       4,   100,     4,   100,   100,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   100,     4,     4,   335,   336,
     102,   102,     4,     4,     4,     8,    99,    99,     7,     7,
       7,     7,   417,   418,     7,     5,     5,     5,     5,   417,
     418,     5,     5,     5,     5,   102,     3,     7,     7,     7,
     435,   429,     7,     5,     5,    99,    99,   435,     5,     7,
     505,     7,     7,     7,     7,   435,    99,    99,    99,     4,
       7,     7,     4,     7,     4,     8,     4,     6,     3,    99,
       6,     3,     6,     3,     3,     6,     4,     4,    99,    99,
       4,     4,   409,     3,   411,     6,    99,     6,    99,    99,
      65,     3,     6,     3,     5,     8,     4,    81,     4,     4,
      99,     4,     6,    99,    99,    99,     4,     4,     4,     4,
     431,   254,   277,     7,    99,     8,     8,    99,    99,     8,
       4,     4,     4,   412,   100,     5,     7,     4,   416,   567,
     579,   418,    83,   586,   582,    99,   102,   100,   588,   328,
     100,   100,   572,   590,   570,   293,   575,   321,   100,    99,
      99,    99,   573,   578,   576,   325,   607,   609,    99,   604,
     606,   296,    99,   435,   596,   600,    99,   303,   612,   610,
     672,   558,   567,   688,   100,   700,   707,    99,   312,   567,
      -1,   576,   570,    99,    -1,   573,    -1,    -1,   576,    -1,
     570,    -1,    -1,    -1,    -1,   576,    -1,   576,   586,   570,
      -1,    -1,   570,   570,   570,    -1,    -1,    -1,   596,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   604,    -1,    -1,   607,
      -1,    -1,   610,    -1,   604,    -1,    -1,   607,    -1,    -1,
     610,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   671,    -1,    -1,    -1,
      -1,    -1,    -1,   671,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   688,    -1,    -1,    -1,    -1,    -1,    -1,
     688
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     0,     5,     7,     9,    99,   100,
     101,   102,   116,   117,   118,   122,     7,   129,     7,   135,
       7,   146,     7,   206,     7,   268,     7,   280,     7,   297,
       7,   228,     7,   251,     7,   188,   123,   119,   130,   136,
     147,   207,   269,   281,   298,   229,   252,   189,   116,   126,
     127,    99,   120,   121,    10,    80,    86,    87,    99,   128,
     131,   132,   133,   348,   350,   352,    11,    13,    14,    22,
      23,    24,    25,    26,    27,    28,    29,    52,    53,    54,
      55,    66,    69,    70,    75,    76,    79,   128,   137,   138,
     139,   140,   141,   142,   143,   144,   150,   152,   169,   175,
     180,   182,   196,   200,   222,   245,   318,   328,   337,   338,
     346,    12,   148,     7,    38,    40,    46,    47,    48,    49,
      50,    51,    57,    58,    64,   128,   139,   140,   141,   142,
     208,   209,   210,   212,   214,   216,   218,   220,   221,   245,
     262,   274,   291,   314,    39,   128,   245,   270,   271,   272,
      41,    42,    43,    44,    45,   128,   245,   282,   283,   284,
     286,   287,   289,   290,    55,    59,    60,    61,    62,    63,
     128,   245,   299,   300,   301,   302,   304,   306,   308,   310,
     312,    15,    30,    32,    33,    35,    36,    37,   128,   156,
     164,   230,   231,   232,   233,   234,   235,   236,   237,   239,
     241,   242,   244,    31,    34,   128,   164,   234,   239,   253,
     254,   255,   256,   257,   259,   260,   261,    67,    68,   128,
     190,   191,   192,   194,     6,     3,     4,     8,     3,   134,
     353,   349,   351,     4,     3,     8,   145,   151,   153,     4,
       4,     4,     4,     4,   201,   223,   246,   170,   181,   176,
     319,   183,   197,   329,     4,   339,   347,     3,     8,   149,
       8,   321,   263,   275,   211,   213,   215,     4,     4,   219,
     217,   292,   315,     3,     8,   273,     3,     8,   285,     4,
     288,     4,     4,     3,     8,   313,   303,   305,   307,   309,
     311,     8,     3,   157,   165,     4,   240,   238,   243,     4,
       8,     3,   258,     4,     8,     3,   193,   195,     3,     8,
     116,   116,    99,     4,     4,     4,     4,   132,     4,     4,
       4,   100,   100,   100,   100,   100,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   100,     4,     4,   138,
       4,    56,   128,   164,   245,   322,   323,   324,   325,   326,
       4,     4,     4,     4,     4,   100,   102,     4,     4,     4,
       4,   209,     4,   271,     4,   100,     4,   100,   100,   283,
       4,     4,     4,     4,     4,     4,   301,     4,     4,   100,
       4,     4,     4,   102,   232,     4,   102,   255,     4,     4,
     191,     4,     7,     7,   116,   116,     7,     7,     7,     5,
       5,     5,     5,     5,   124,     5,     5,     5,     7,     7,
       7,     7,   124,   327,     8,     3,     5,     5,    99,    99,
      99,    99,    99,     5,     7,    99,    99,    99,   124,   124,
     124,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   116,   116,   137,    81,   354,   355,   356,   148,    16,
      17,    18,    19,    20,    21,   128,   154,   155,   156,   158,
     160,   162,   164,   166,   167,   168,   154,     7,   202,   203,
     204,     7,   224,   225,   226,     7,   247,   248,   249,    61,
      99,   171,   172,   173,   174,   125,    62,   173,   177,   178,
     179,   216,   320,     7,   184,   185,   186,    99,   198,   199,
      71,    72,    73,    74,   128,   156,   166,   330,   331,   332,
     333,   335,   336,    77,    78,   340,   341,   342,   344,   121,
       4,   324,     7,   264,   265,   266,     7,   276,   277,   278,
       7,   293,   294,   295,    65,   316,     8,   357,     3,     8,
       8,   159,   161,   163,     4,     4,     4,     3,     8,     8,
     205,     6,     3,   227,     6,     3,   250,     6,     3,     3,
       6,   126,     3,     6,     3,     6,   187,     6,     3,     4,
       3,     8,   334,     4,     4,     4,     3,     8,   343,   345,
       3,     8,     8,    99,   267,     6,     3,   279,     6,     3,
     296,     6,     3,   317,     8,     4,   355,     4,     4,     4,
     102,   100,   102,   155,   208,   204,   230,   226,   253,   249,
     172,     6,   178,   216,   190,   186,   100,   199,     4,   100,
     100,   100,   331,     4,     4,   341,   270,   266,   282,   278,
     299,   295,     4,     5,    99,    99,    99,     8,     8,     8,
       8,    99,    99,    99,     8,     8,     8,    99,     7,   358,
     359,   360,     3,     6,    82,    84,    85,   128,   164,   361,
     362,   363,   364,   366,   359,   367,     4,   365,     3,     8,
       4,   100,     4,   362,     5,    99,     7,   368,   369,   370,
       3,     6,    83,   371,   372,   369,   373,     3,     8,     4,
     372,    99
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   103,   105,   104,   106,   104,   107,   104,   108,   104,
     109,   104,   110,   104,   111,   104,   112,   104,   113,   104,
     114,   104,   115,   104,   116,   116,   116,   116,   116,   116,
     116,   117,   119,   118,   120,   120,   121,   121,   123,   122,
     125,   124,   126,   126,   127,   127,   128,   130,   129,   131,
     131,   132,   132,   132,   132,   132,   134,   133,   136,   135,
     137,   137,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   140,   141,   142,   143,   145,
     144,   147,   146,   149,   148,   151,   150,   153,   152,   154,
     154,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     157,   156,   159,   158,   161,   160,   163,   162,   165,   164,
     166,   167,   168,   170,   169,   171,   171,   172,   172,   173,
     174,   176,   175,   177,   177,   178,   178,   179,   181,   180,
     183,   182,   184,   184,   185,   185,   187,   186,   189,   188,
     190,   190,   190,   191,   191,   193,   192,   195,   194,   197,
     196,   198,   198,   199,   201,   200,   202,   202,   203,   203,
     205,   204,   207,   206,   208,   208,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   211,   210,   213,   212,   215,   214,   217,
     216,   219,   218,   220,   221,   223,   222,   224,   224,   225,
     225,   227,   226,   229,   228,   230,   230,   231,   231,   232,
     232,   232,   232,   232,   232,   232,   232,   233,   234,   235,
     236,   238,   237,   240,   239,   241,   243,   242,   244,   246,
     245,   247,   247,   248,   248,   250,   249,   252,   251,   253,
     253,   254,   254,   255,   255,   255,   255,   255,   255,   256,
     258,   257,   259,   260,   261,   263,   262,   264,   264,   265,
     265,   267,   266,   269,   268,   270,   270,   271,   271,   271,
     273,   272,   275,   274,   276,   276,   277,   277,   279,   278,
     281,   280,   282,   282,   283,   283,   283,   283,   283,   283,
     283,   285,   284,   286,   288,   287,   289,   290,   292,   291,
     293,   293,   294,   294,   296,   295,   298,   297,   299,   299,
     300,   300,   301,   301,   301,   301,   301,   301,   301,   301,
     303,   302,   305,   304,   307,   306,   309,   308,   311,   310,
     313,   312,   315,   314,   317,   316,   319,   318,   320,   320,
     321,   216,   322,   322,   323,   323,   324,   324,   324,   324,
     325,   327,   326,   329,   328,   330,   330,   331,   331,   331,
     331,   331,   331,   331,   332,   334,   333,   335,   336,   337,
     339,   338,   340,   340,   341,   341,   343,   342,   345,   344,
     347,   346,   349,   348,   351,   350,   353,   352,   354,   354,
     355,   357,   356,   358,   358,   360,   359,   361,   361,   362,
     362,   362,   362,   362,   363,   365,   364,   367,   366,   368,
     368,   370,   369,   371,   371,   373,   372
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
       6,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
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
  "not_empty_map", "list_generic", "$@13", "list2", "$@14", "list_content",
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
     265,   265,   272,   273,   276,   280,   291,   301,   301,   313,
     314,   318,   319,   320,   321,   322,   325,   325,   342,   342,
     350,   351,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   380,   385,   390,   395,   400,   405,
     405,   415,   415,   423,   423,   433,   433,   443,   443,   453,
     454,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     468,   468,   476,   476,   484,   484,   492,   492,   500,   500,
     508,   513,   518,   523,   523,   533,   534,   537,   538,   541,
     546,   551,   551,   561,   562,   565,   566,   569,   574,   574,
     584,   584,   594,   595,   598,   599,   602,   602,   610,   610,
     618,   619,   620,   623,   624,   627,   627,   635,   635,   643,
     643,   653,   654,   660,   668,   668,   681,   682,   685,   686,
     693,   693,   716,   716,   725,   726,   730,   731,   732,   733,
     734,   735,   736,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   749,   749,   757,   757,   765,   765,   773,
     773,   781,   781,   789,   794,   803,   803,   815,   816,   819,
     820,   825,   825,   836,   836,   846,   847,   850,   851,   854,
     855,   856,   857,   858,   859,   860,   861,   864,   866,   871,
     873,   875,   875,   883,   883,   891,   893,   893,   901,   910,
     910,   922,   923,   928,   929,   934,   934,   945,   945,   956,
     957,   962,   963,   968,   969,   970,   971,   972,   973,   976,
     978,   978,   986,   988,   990,   998,   998,  1010,  1011,  1014,
    1015,  1018,  1018,  1026,  1026,  1034,  1035,  1038,  1039,  1040,
    1043,  1043,  1054,  1054,  1066,  1067,  1070,  1071,  1074,  1074,
    1082,  1082,  1090,  1091,  1094,  1095,  1096,  1097,  1098,  1099,
    1100,  1103,  1103,  1111,  1116,  1116,  1124,  1129,  1137,  1137,
    1147,  1148,  1151,  1152,  1155,  1155,  1163,  1163,  1171,  1172,
    1175,  1176,  1180,  1181,  1182,  1183,  1184,  1185,  1186,  1187,
    1190,  1190,  1200,  1200,  1210,  1210,  1218,  1218,  1226,  1226,
    1234,  1234,  1247,  1247,  1257,  1257,  1268,  1268,  1278,  1279,
    1282,  1282,  1290,  1291,  1294,  1295,  1298,  1299,  1300,  1301,
    1304,  1306,  1306,  1317,  1317,  1327,  1328,  1331,  1332,  1333,
    1334,  1335,  1336,  1337,  1340,  1345,  1345,  1353,  1358,  1365,
    1372,  1372,  1382,  1383,  1386,  1387,  1390,  1390,  1398,  1398,
    1408,  1408,  1420,  1420,  1427,  1427,  1439,  1439,  1452,  1453,
    1457,  1461,  1461,  1473,  1474,  1478,  1478,  1486,  1487,  1490,
    1491,  1492,  1493,  1494,  1497,  1501,  1501,  1509,  1509,  1519,
    1520,  1523,  1523,  1531,  1532,  1535,  1535
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
#line 3511 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1543 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
