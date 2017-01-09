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
      case 119: // value
      case 338: // duid_type
        value.move< ElementPtr > (that.value);
        break;

      case 105: // "boolean"
        value.move< bool > (that.value);
        break;

      case 104: // "floating point"
        value.move< double > (that.value);
        break;

      case 103: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 102: // "constant string"
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
      case 119: // value
      case 338: // duid_type
        value.copy< ElementPtr > (that.value);
        break;

      case 105: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 104: // "floating point"
        value.copy< double > (that.value);
        break;

      case 103: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 102: // "constant string"
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
            case 102: // "constant string"

#line 193 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 103: // "integer"

#line 193 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 104: // "floating point"

#line 193 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 105: // "boolean"

#line 193 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 119: // value

#line 193 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 338: // duid_type

#line 193 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 389 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 119: // value
      case 338: // duid_type
        yylhs.value.build< ElementPtr > ();
        break;

      case 105: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 104: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 103: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 102: // "constant string"
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
#line 202 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 203 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 204 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 205 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 206 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 207 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 208 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 209 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 210 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 211 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 212 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 220 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 221 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 790 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 844 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 329 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 798 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1584 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1681 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1711 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 988 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1774 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1040 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 1958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 1976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1200 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1222 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1228 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1357 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2416 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2425 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2433 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2442 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2479 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2509 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2582 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2590 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2604 "dhcp6_parser.cc" // lalr1.cc:859
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
      89,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,    31,    21,    22,    57,    66,    92,   121,   134,
     154,   203,   207,   216,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,    21,    72,    11,    64,
     164,    12,    -7,    38,    43,   117,   125,    29,  -427,   223,
     221,   228,   227,   230,  -427,  -427,  -427,  -427,   232,  -427,
      30,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   234,
     239,   242,   245,   246,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   253,  -427,  -427,  -427,    48,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   250,  -427,  -427,  -427,  -427,  -427,  -427,   256,
     259,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
     119,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,   136,  -427,  -427,
    -427,   260,  -427,   261,   263,  -427,  -427,   167,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   262,   265,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   267,  -427,  -427,  -427,   268,  -427,  -427,
     266,   273,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   274,  -427,  -427,  -427,  -427,   269,   276,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   169,
    -427,  -427,  -427,  -427,    21,    21,  -427,   178,   277,   278,
     279,   280,  -427,    11,  -427,   281,   282,   283,   166,   185,
     186,   187,   192,   287,   288,   289,   290,   292,   293,   294,
     295,   296,   297,   202,   298,   299,    64,  -427,   300,  -427,
      10,   302,   303,   304,   305,   306,   211,   206,   308,   309,
     311,   312,    12,  -427,   313,    -7,  -427,   314,   219,   315,
     220,   222,    38,  -427,   316,   317,   320,   322,   323,   324,
    -427,    43,   325,   326,   229,   327,   329,   330,   231,  -427,
     117,   331,   235,  -427,   125,   335,   337,   -13,  -427,  -427,
    -427,   338,   336,   339,    21,    21,  -427,   340,   341,   342,
    -427,  -427,  -427,  -427,  -427,   345,   348,   349,   350,   351,
     352,   355,   356,   357,   358,  -427,   359,   360,  -427,   351,
    -427,  -427,  -427,  -427,   354,   365,  -427,  -427,  -427,   366,
     367,   243,   271,   272,  -427,  -427,   275,   284,   370,   371,
    -427,   285,  -427,   286,  -427,   291,  -427,  -427,  -427,   351,
     351,   351,   301,   307,   310,  -427,   318,   319,  -427,   321,
     328,   332,  -427,  -427,   333,  -427,  -427,   334,    21,  -427,
      21,    64,   343,  -427,  -427,   164,    27,    27,   372,   373,
     374,   -34,  -427,  -427,    23,    58,   375,   344,    34,    40,
      72,  -427,   379,  -427,    10,   378,   382,  -427,  -427,  -427,
    -427,  -427,   383,   353,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   188,  -427,   189,  -427,  -427,   384,  -427,  -427,
    -427,  -427,   387,   390,   391,  -427,   190,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,   191,  -427,   392,   393,
    -427,  -427,   394,   396,  -427,  -427,   395,   399,  -427,  -427,
    -427,    68,  -427,  -427,  -427,    21,  -427,  -427,   132,  -427,
    -427,  -427,   145,  -427,   398,   402,  -427,   403,   197,  -427,
    -427,  -427,   404,   406,   410,  -427,  -427,   198,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,   199,  -427,  -427,  -427,
     200,   346,  -427,  -427,   400,   412,  -427,  -427,   411,   413,
    -427,  -427,   416,   421,  -427,  -427,   389,  -427,   415,   343,
    -427,  -427,   422,   424,   425,   427,   258,   241,   347,    27,
    -427,  -427,    12,  -427,   372,   117,  -427,   373,   125,  -427,
     374,   -34,  -427,   419,    23,  -427,    58,  -427,    29,  -427,
     375,   361,   344,  -427,   428,   429,   362,   363,   364,    34,
    -427,   433,   434,    40,  -427,  -427,  -427,    -7,  -427,   378,
      38,  -427,   382,    43,  -427,   383,   435,  -427,   436,  -427,
     368,   369,   376,   377,  -427,  -427,  -427,  -427,   201,  -427,
     432,  -427,   437,  -427,  -427,  -427,  -427,  -427,   208,  -427,
    -427,  -427,   168,   380,  -427,  -427,  -427,  -427,   381,   385,
    -427,   209,  -427,   210,  -427,   439,  -427,   386,   442,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   157,
    -427,    77,   442,  -427,  -427,   438,  -427,  -427,  -427,   217,
    -427,  -427,  -427,  -427,  -427,   440,   388,   446,    77,  -427,
     448,  -427,   397,  -427,   444,  -427,  -427,   225,  -427,   407,
     444,  -427,  -427,   218,  -427,  -427,   450,   407,  -427,   401,
    -427,  -427
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      91,     9,   172,    11,   274,    13,   291,    15,   317,    17,
     213,    19,   248,    21,   148,    23,    42,    34,     0,     0,
       0,     0,     0,     0,   319,   215,   250,     0,    44,     0,
      43,     0,     0,    35,    56,   402,   398,   400,     0,    55,
       0,    49,    51,    53,    54,    52,    89,    95,    97,     0,
       0,     0,     0,     0,   164,   205,   240,   123,   138,   131,
     347,   140,   159,   364,     0,   386,   396,    83,     0,    60,
      62,    63,    64,    65,    66,    68,    69,    70,    71,    73,
      72,    77,    78,    67,    75,    76,    74,    79,    80,    81,
      82,    93,     0,   351,   266,   283,   193,   195,   197,     0,
       0,   201,   199,   309,   343,   192,   176,   177,   178,   179,
       0,   174,   183,   184,   185,   188,   190,   186,   187,   180,
     181,   182,   189,   191,   281,   280,   279,     0,   276,   278,
     302,     0,   305,     0,     0,   301,   298,     0,   293,   295,
     296,   299,   300,   297,   341,   331,   333,   335,   337,   339,
     330,   329,     0,   320,   321,   325,   326,   323,   327,   328,
     324,   230,   118,     0,   234,   232,   237,     0,   226,   227,
       0,   216,   217,   219,   229,   220,   221,   222,   236,   223,
     224,   225,   261,     0,   259,   260,   263,   264,     0,   251,
     252,   254,   255,   256,   257,   258,   155,   157,   152,     0,
     150,   153,   154,    39,     0,     0,    33,     0,     0,     0,
       0,     0,    46,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,     0,    92,
     353,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   173,     0,     0,   275,     0,     0,     0,
       0,     0,     0,   292,     0,     0,     0,     0,     0,     0,
     318,     0,     0,     0,     0,     0,     0,     0,     0,   214,
       0,     0,     0,   249,     0,     0,     0,     0,   149,    45,
      36,     0,     0,     0,     0,     0,    50,     0,     0,     0,
      84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   385,     0,     0,    61,     0,
     362,   360,   361,   359,     0,   354,   355,   357,   358,     0,
       0,     0,     0,     0,   203,   204,     0,     0,     0,     0,
     175,     0,   277,     0,   304,     0,   307,   308,   294,     0,
       0,     0,     0,     0,     0,   322,     0,     0,   228,     0,
       0,     0,   239,   218,     0,   265,   253,     0,     0,   151,
       0,     0,     0,   399,   401,     0,     0,     0,   166,   207,
     242,     0,    40,   139,     0,     0,   142,     0,     0,     0,
       0,    94,     0,   352,     0,   268,   285,   194,   196,   198,
     202,   200,   311,     0,   282,   303,   306,   342,   332,   334,
     336,   338,   340,   231,   119,   235,   233,   238,   262,   156,
     158,    37,     0,   407,     0,   404,   406,     0,   110,   112,
     114,   116,     0,     0,     0,   109,     0,    99,   101,   102,
     103,   104,   105,   106,   107,   108,     0,   170,     0,   167,
     168,   211,     0,   208,   209,   246,     0,   243,   244,   129,
     130,     0,   125,   127,   128,    42,   137,   135,     0,   133,
     136,   349,     0,   146,     0,   143,   144,     0,     0,   161,
     375,   381,     0,     0,     0,   374,   373,     0,   366,   368,
     371,   369,   370,   372,   392,   394,     0,   388,   390,   391,
       0,     0,   356,   272,     0,   269,   270,   289,     0,   286,
     287,   315,     0,   312,   313,   345,     0,    57,     0,     0,
     403,    90,     0,     0,     0,     0,     0,     0,     0,     0,
      96,    98,     0,   165,     0,   215,   206,     0,   250,   241,
       0,     0,   124,     0,     0,   132,     0,   348,     0,   141,
       0,     0,     0,   160,     0,     0,     0,     0,     0,     0,
     365,     0,     0,     0,   387,   397,   363,     0,   267,     0,
       0,   284,     0,   319,   310,     0,     0,   344,     0,   405,
       0,     0,     0,     0,   120,   121,   122,   100,     0,   169,
       0,   210,     0,   245,   126,    41,   134,   350,     0,   145,
     163,   162,     0,     0,   380,   383,   384,   367,     0,     0,
     389,     0,   271,     0,   288,     0,   314,     0,     0,   111,
     113,   115,   117,   171,   212,   247,   147,   377,   378,   379,
     376,   382,   393,   395,   273,   290,   316,   346,   411,     0,
     409,     0,     0,   408,   423,     0,   421,   419,   415,     0,
     413,   417,   418,   416,   410,     0,     0,     0,     0,   412,
       0,   420,     0,   414,     0,   422,   427,     0,   425,     0,
       0,   424,   431,     0,   429,   426,     0,     0,   428,     0,
     430,   432
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,     3,  -427,  -427,  -427,  -427,    13,  -427,
    -427,  -222,  -427,   -48,  -427,   -58,  -427,  -427,  -427,   205,
    -427,  -427,  -427,  -427,    44,   180,   -41,   -38,   -37,   -36,
    -427,  -427,  -427,  -427,  -427,    45,  -427,  -427,  -427,  -427,
    -427,    42,  -108,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,   -65,  -427,  -426,  -427,  -427,  -427,  -427,  -427,  -119,
    -406,  -427,  -427,  -427,  -427,  -121,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -122,  -427,  -427,  -427,  -116,   142,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -118,  -427,  -427,  -427,
    -427,  -101,  -427,  -427,  -427,   -97,   184,  -427,  -427,  -427,
    -427,  -427,  -427,  -415,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -100,  -427,  -427,  -427,   -95,  -427,   161,
    -427,   -51,  -427,  -427,  -427,  -427,  -427,   -49,  -427,  -427,
    -427,  -427,  -427,   -50,  -427,  -427,  -427,   -96,  -427,  -427,
    -427,   -93,  -427,   162,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -120,  -427,  -427,  -427,  -117,   212,
    -427,  -427,  -427,  -427,  -427,  -427,  -115,  -427,  -427,  -427,
    -114,   193,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -123,  -427,  -427,  -427,  -113,  -427,   183,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,    67,  -427,  -427,  -427,  -427,  -427,  -427,   -94,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -105,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,   -57,  -427,  -427,  -427,
    -176,  -427,  -427,  -190,  -427,  -427,  -427,  -427,  -427,  -427,
    -201,  -427,  -427,  -207,  -427
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   423,   505,    69,    70,   107,    37,    58,    80,    81,
      82,   248,    39,    59,   108,   109,   110,   111,   112,   113,
     114,   115,   255,    41,    60,   132,   278,   116,   256,   117,
     257,   476,   477,   478,   562,   479,   563,   480,   564,   481,
     565,   209,   313,   483,   484,   485,   118,   266,   501,   502,
     503,   504,   119,   268,   508,   509,   510,   120,   267,   121,
     270,   514,   515,   516,   588,    55,    67,   239,   240,   241,
     325,   242,   326,   122,   271,   518,   519,   123,   263,   488,
     489,   490,   572,    43,    61,   150,   151,   152,   283,   153,
     284,   154,   285,   155,   289,   156,   288,   157,   158,   124,
     264,   492,   493,   494,   575,    51,    65,   210,   211,   212,
     213,   214,   215,   216,   312,   217,   316,   218,   315,   219,
     220,   317,   221,   125,   265,   496,   497,   498,   578,    53,
      66,   228,   229,   230,   231,   232,   321,   233,   234,   235,
     160,   281,   544,   545,   546,   607,    45,    62,   167,   168,
     169,   294,   161,   282,   548,   549,   550,   610,    47,    63,
     177,   178,   179,   297,   180,   181,   299,   182,   183,   162,
     290,   552,   553,   554,   613,    49,    64,   192,   193,   194,
     195,   305,   196,   306,   197,   307,   198,   308,   199,   309,
     200,   304,   163,   291,   556,   616,   126,   269,   512,   280,
     364,   365,   366,   367,   368,   432,   127,   272,   527,   528,
     529,   594,   670,   530,   531,   595,   532,   533,   128,   129,
     274,   536,   537,   538,   601,   539,   602,   130,   275,    83,
     250,    84,   251,    85,   249,   464,   465,   466,   558,   679,
     680,   681,   689,   690,   691,   692,   697,   693,   695,   707,
     708,   709,   713,   714,   716
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   225,   526,   145,   165,   175,   190,   208,   224,   238,
     511,   159,   166,   176,   191,   226,    32,   227,   507,   133,
     146,    74,    96,   147,   148,   149,    25,   499,    26,    36,
      27,    24,   164,   253,    89,    90,    91,    92,   254,    96,
     202,    96,   468,   469,   470,   471,   472,   473,   474,   520,
     134,   276,   135,   472,   236,   237,   277,   202,   136,   137,
     138,   139,   140,   141,    38,   133,   360,    96,   500,   142,
     143,   581,    96,    40,   582,    86,   144,    87,    88,   170,
     171,   172,   173,   174,   499,   506,    89,    90,    91,    92,
      93,    94,    95,    96,    75,    78,   236,   237,   184,    42,
      76,    77,   185,   186,   187,   188,   189,   202,   521,   522,
     523,   524,    78,    78,    78,   142,    97,    98,    99,   100,
     534,   535,   292,    28,    29,    30,    31,   293,    44,    78,
     101,    78,   201,   102,   103,   584,    78,   431,   585,   295,
      78,    46,   104,   105,   296,    78,   106,   202,   586,   203,
     204,   587,   205,   206,   207,   202,   222,   203,   204,   223,
     682,    48,   684,   683,   685,   686,    78,   447,   448,   449,
     302,   637,   327,   526,    71,   303,   131,   328,   507,    78,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,   276,   559,   569,   569,    79,   557,   560,   570,   571,
     592,   599,   603,   247,   292,   593,   600,   604,   605,   663,
      50,   327,   295,   302,    52,   362,   666,   674,   675,    78,
     698,   717,   361,    54,   244,   699,   718,    78,   710,   243,
     363,   711,   245,   247,   145,   246,   252,   165,   258,   667,
     668,   669,   159,   259,   175,   166,   260,   329,   330,   261,
     262,   146,   176,   190,   147,   148,   149,   273,   279,   225,
     286,   191,   208,   287,   298,   300,   224,   301,   311,   340,
     310,   314,   318,   226,   319,   227,   320,   323,   322,   324,
     331,   332,   333,   334,   335,   337,   338,   339,   341,   342,
     343,   345,   346,   347,   348,   344,   349,   350,   351,   352,
     353,   354,   356,   357,   359,   355,   369,   370,   371,   372,
     373,   375,   376,   377,   374,   378,   379,   381,   383,   385,
     389,   390,   384,   386,   391,   387,   392,   393,   394,   396,
     397,   399,   398,   400,   401,   404,   402,   413,   414,   407,
     405,   408,   410,   411,   625,   437,   412,   415,   416,   417,
     418,   482,   482,   419,   420,   421,   422,   424,   475,   475,
     425,   426,   433,   624,   427,   428,   429,   430,   434,   362,
     525,   435,   436,   438,   439,   442,   361,   440,   443,   487,
     491,   495,   513,   541,   363,   543,   441,   444,   445,   547,
     551,   566,   561,   446,   567,   568,   574,   617,   573,   577,
     576,   579,   580,   450,   589,   590,   608,   591,   596,   451,
     597,   460,   452,   461,   598,   609,   612,   611,   555,   618,
     453,   454,   614,   455,   615,   635,   620,   463,   621,   622,
     456,   623,   642,   643,   457,   458,   459,   648,   649,   657,
     664,   658,   696,   540,   700,   665,   517,   676,   606,   678,
     702,   706,   626,   704,   719,   462,   358,   583,   336,   486,
     467,   627,   634,   636,   640,   644,   645,   646,   639,   409,
     659,   660,   638,   629,   641,   628,   380,   631,   661,   662,
     630,   403,   671,   672,   633,   632,   406,   673,   677,   652,
     651,   701,   656,   712,   395,   388,   653,   654,   650,   705,
     655,   542,   619,   721,   482,   647,   694,   382,   703,   715,
     720,   475,     0,   225,   145,     0,     0,   208,     0,     0,
     224,     0,   159,     0,     0,     0,     0,   226,     0,   227,
     238,   146,     0,     0,   147,   148,   149,     0,     0,     0,
       0,   525,     0,     0,     0,     0,     0,     0,     0,   165,
       0,     0,   175,     0,     0,   190,     0,   166,     0,     0,
     176,     0,     0,   191,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   688,     0,     0,     0,
       0,     0,     0,   687,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   688,     0,     0,     0,     0,     0,     0,
     687
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,   428,    61,    62,    63,    64,    65,    66,    67,
     425,    61,    62,    63,    64,    66,    13,    66,   424,     7,
      61,    10,    29,    61,    61,    61,     5,    61,     7,     7,
       9,     0,    39,     3,    22,    23,    24,    25,     8,    29,
      30,    29,    15,    16,    17,    18,    19,    20,    21,    15,
      38,     3,    40,    19,    67,    68,     8,    30,    46,    47,
      48,    49,    50,    51,     7,     7,    56,    29,   102,    57,
      58,     3,    29,     7,     6,    11,    64,    13,    14,    41,
      42,    43,    44,    45,    61,    62,    22,    23,    24,    25,
      26,    27,    28,    29,    83,   102,    67,    68,    55,     7,
      89,    90,    59,    60,    61,    62,    63,    30,    74,    75,
      76,    77,   102,   102,   102,    57,    52,    53,    54,    55,
      80,    81,     3,   102,   103,   104,   105,     8,     7,   102,
      66,   102,    15,    69,    70,     3,   102,   359,     6,     3,
     102,     7,    78,    79,     8,   102,    82,    30,     3,    32,
      33,     6,    35,    36,    37,    30,    31,    32,    33,    34,
       3,     7,    85,     6,    87,    88,   102,   389,   390,   391,
       3,   586,     3,   599,   102,     8,    12,     8,   584,   102,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,     3,     3,     3,     3,   253,     8,     8,     8,     8,
       3,     3,     3,     3,     3,     8,     8,     8,     8,     8,
       7,     3,     3,     3,     7,   280,     8,     8,     8,   102,
       3,     3,   280,     7,     3,     8,     8,   102,     3,     6,
     280,     6,     4,     3,   292,     8,     4,   295,     4,    71,
      72,    73,   292,     4,   302,   295,     4,   244,   245,     4,
       4,   292,   302,   311,   292,   292,   292,     4,     8,   324,
       4,   311,   320,     4,     4,     4,   324,     4,     3,   103,
       8,     4,     4,   324,     8,   324,     3,     8,     4,     3,
     102,     4,     4,     4,     4,     4,     4,     4,   103,   103,
     103,     4,     4,     4,     4,   103,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   103,     4,     4,     4,     4,
       4,   105,     4,     4,   103,     4,     4,     4,     4,     4,
       4,     4,   103,   103,     4,   103,     4,     4,     4,     4,
       4,     4,   103,     4,     4,     4,   105,   334,   335,     4,
     105,     4,     4,     7,   103,   102,     7,     7,     7,     7,
       5,   416,   417,     5,     5,     5,     5,     5,   416,   417,
       5,     5,     8,   105,     7,     7,     7,     7,     3,   434,
     428,     5,     5,   102,   102,     5,   434,   102,     7,     7,
       7,     7,     7,     4,   434,     7,   102,   102,   102,     7,
       7,     4,     8,   102,     4,     4,     3,     8,     6,     3,
       6,     6,     3,   102,     6,     3,     6,     4,     4,   102,
       4,   408,   102,   410,     4,     3,     3,     6,    65,     4,
     102,   102,     6,   102,     3,     6,     4,    84,     4,     4,
     102,     4,     4,     4,   102,   102,   102,     4,     4,     4,
       8,     5,     4,   430,     4,     8,   102,     8,   102,     7,
       4,     7,   105,     5,     4,   411,   276,   505,   253,   417,
     415,   569,   581,   584,   103,   103,   103,   103,   590,   327,
     102,   102,   588,   574,   592,   572,   292,   577,   102,   102,
     575,   320,   102,   102,   580,   578,   324,   102,   102,   609,
     607,   103,   615,    86,   311,   302,   610,   612,   603,   102,
     613,   434,   559,   102,   569,   599,   682,   295,   698,   710,
     717,   569,    -1,   578,   572,    -1,    -1,   575,    -1,    -1,
     578,    -1,   572,    -1,    -1,    -1,    -1,   578,    -1,   578,
     588,   572,    -1,    -1,   572,   572,   572,    -1,    -1,    -1,
      -1,   599,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   607,
      -1,    -1,   610,    -1,    -1,   613,    -1,   607,    -1,    -1,
     610,    -1,    -1,   613,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   681,    -1,    -1,    -1,
      -1,    -1,    -1,   681,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   698,    -1,    -1,    -1,    -1,    -1,    -1,
     698
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,     0,     5,     7,     9,   102,   103,
     104,   105,   119,   120,   121,   125,     7,   132,     7,   138,
       7,   149,     7,   209,     7,   272,     7,   284,     7,   301,
       7,   231,     7,   255,     7,   191,   126,   122,   133,   139,
     150,   210,   273,   285,   302,   232,   256,   192,   119,   129,
     130,   102,   123,   124,    10,    83,    89,    90,   102,   131,
     134,   135,   136,   355,   357,   359,    11,    13,    14,    22,
      23,    24,    25,    26,    27,    28,    29,    52,    53,    54,
      55,    66,    69,    70,    78,    79,    82,   131,   140,   141,
     142,   143,   144,   145,   146,   147,   153,   155,   172,   178,
     183,   185,   199,   203,   225,   249,   322,   332,   344,   345,
     353,    12,   151,     7,    38,    40,    46,    47,    48,    49,
      50,    51,    57,    58,    64,   131,   142,   143,   144,   145,
     211,   212,   213,   215,   217,   219,   221,   223,   224,   249,
     266,   278,   295,   318,    39,   131,   249,   274,   275,   276,
      41,    42,    43,    44,    45,   131,   249,   286,   287,   288,
     290,   291,   293,   294,    55,    59,    60,    61,    62,    63,
     131,   249,   303,   304,   305,   306,   308,   310,   312,   314,
     316,    15,    30,    32,    33,    35,    36,    37,   131,   167,
     233,   234,   235,   236,   237,   238,   239,   241,   243,   245,
     246,   248,    31,    34,   131,   167,   237,   243,   257,   258,
     259,   260,   261,   263,   264,   265,    67,    68,   131,   193,
     194,   195,   197,     6,     3,     4,     8,     3,   137,   360,
     356,   358,     4,     3,     8,   148,   154,   156,     4,     4,
       4,     4,     4,   204,   226,   250,   173,   184,   179,   323,
     186,   200,   333,     4,   346,   354,     3,     8,   152,     8,
     325,   267,   279,   214,   216,   218,     4,     4,   222,   220,
     296,   319,     3,     8,   277,     3,     8,   289,     4,   292,
       4,     4,     3,     8,   317,   307,   309,   311,   313,   315,
       8,     3,   240,   168,     4,   244,   242,   247,     4,     8,
       3,   262,     4,     8,     3,   196,   198,     3,     8,   119,
     119,   102,     4,     4,     4,     4,   135,     4,     4,     4,
     103,   103,   103,   103,   103,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   103,     4,     4,   141,     4,
      56,   131,   167,   249,   326,   327,   328,   329,   330,     4,
       4,     4,     4,     4,   103,   105,     4,     4,     4,     4,
     212,     4,   275,     4,   103,     4,   103,   103,   287,     4,
       4,     4,     4,     4,     4,   305,     4,     4,   103,     4,
       4,     4,   105,   235,     4,   105,   259,     4,     4,   194,
       4,     7,     7,   119,   119,     7,     7,     7,     5,     5,
       5,     5,     5,   127,     5,     5,     5,     7,     7,     7,
       7,   127,   331,     8,     3,     5,     5,   102,   102,   102,
     102,   102,     5,     7,   102,   102,   102,   127,   127,   127,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     119,   119,   140,    84,   361,   362,   363,   151,    15,    16,
      17,    18,    19,    20,    21,   131,   157,   158,   159,   161,
     163,   165,   167,   169,   170,   171,   157,     7,   205,   206,
     207,     7,   227,   228,   229,     7,   251,   252,   253,    61,
     102,   174,   175,   176,   177,   128,    62,   176,   180,   181,
     182,   219,   324,     7,   187,   188,   189,   102,   201,   202,
      15,    74,    75,    76,    77,   131,   169,   334,   335,   336,
     339,   340,   342,   343,    80,    81,   347,   348,   349,   351,
     124,     4,   328,     7,   268,   269,   270,     7,   280,   281,
     282,     7,   297,   298,   299,    65,   320,     8,   364,     3,
       8,     8,   160,   162,   164,   166,     4,     4,     4,     3,
       8,     8,   208,     6,     3,   230,     6,     3,   254,     6,
       3,     3,     6,   129,     3,     6,     3,     6,   190,     6,
       3,     4,     3,     8,   337,   341,     4,     4,     4,     3,
       8,   350,   352,     3,     8,     8,   102,   271,     6,     3,
     283,     6,     3,   300,     6,     3,   321,     8,     4,   362,
       4,     4,     4,     4,   105,   103,   105,   158,   211,   207,
     233,   229,   257,   253,   175,     6,   181,   219,   193,   189,
     103,   202,     4,     4,   103,   103,   103,   335,     4,     4,
     348,   274,   270,   286,   282,   303,   299,     4,     5,   102,
     102,   102,   102,     8,     8,     8,     8,    71,    72,    73,
     338,   102,   102,   102,     8,     8,     8,   102,     7,   365,
     366,   367,     3,     6,    85,    87,    88,   131,   167,   368,
     369,   370,   371,   373,   366,   374,     4,   372,     3,     8,
       4,   103,     4,   369,     5,   102,     7,   375,   376,   377,
       3,     6,    86,   378,   379,   376,   380,     3,     8,     4,
     379,   102
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   106,   108,   107,   109,   107,   110,   107,   111,   107,
     112,   107,   113,   107,   114,   107,   115,   107,   116,   107,
     117,   107,   118,   107,   119,   119,   119,   119,   119,   119,
     119,   120,   122,   121,   123,   123,   124,   124,   126,   125,
     128,   127,   129,   129,   130,   130,   131,   133,   132,   134,
     134,   135,   135,   135,   135,   135,   137,   136,   139,   138,
     140,   140,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   142,   143,   144,   145,   146,   148,
     147,   150,   149,   152,   151,   154,   153,   156,   155,   157,
     157,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     160,   159,   162,   161,   164,   163,   166,   165,   168,   167,
     169,   170,   171,   173,   172,   174,   174,   175,   175,   176,
     177,   179,   178,   180,   180,   181,   181,   182,   184,   183,
     186,   185,   187,   187,   188,   188,   190,   189,   192,   191,
     193,   193,   193,   194,   194,   196,   195,   198,   197,   200,
     199,   201,   201,   202,   204,   203,   205,   205,   206,   206,
     208,   207,   210,   209,   211,   211,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   214,   213,   216,   215,   218,   217,   220,
     219,   222,   221,   223,   224,   226,   225,   227,   227,   228,
     228,   230,   229,   232,   231,   233,   233,   234,   234,   235,
     235,   235,   235,   235,   235,   235,   235,   236,   237,   238,
     240,   239,   242,   241,   244,   243,   245,   247,   246,   248,
     250,   249,   251,   251,   252,   252,   254,   253,   256,   255,
     257,   257,   258,   258,   259,   259,   259,   259,   259,   259,
     260,   262,   261,   263,   264,   265,   267,   266,   268,   268,
     269,   269,   271,   270,   273,   272,   274,   274,   275,   275,
     275,   277,   276,   279,   278,   280,   280,   281,   281,   283,
     282,   285,   284,   286,   286,   287,   287,   287,   287,   287,
     287,   287,   289,   288,   290,   292,   291,   293,   294,   296,
     295,   297,   297,   298,   298,   300,   299,   302,   301,   303,
     303,   304,   304,   305,   305,   305,   305,   305,   305,   305,
     305,   307,   306,   309,   308,   311,   310,   313,   312,   315,
     314,   317,   316,   319,   318,   321,   320,   323,   322,   324,
     324,   325,   219,   326,   326,   327,   327,   328,   328,   328,
     328,   329,   331,   330,   333,   332,   334,   334,   335,   335,
     335,   335,   335,   335,   335,   337,   336,   338,   338,   338,
     339,   341,   340,   342,   343,   344,   346,   345,   347,   347,
     348,   348,   350,   349,   352,   351,   354,   353,   356,   355,
     358,   357,   360,   359,   361,   361,   362,   364,   363,   365,
     365,   367,   366,   368,   368,   369,   369,   369,   369,   369,
     370,   372,   371,   374,   373,   375,   375,   377,   376,   378,
     378,   380,   379
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
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
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
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     0,     4
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
  "\"server-id\"", "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"",
  "\"htype\"", "\"time\"", "\"enterprise-id\"", "\"dhcp4o6-port\"",
  "\"control-socket\"", "\"socket-type\"", "\"socket-name\"",
  "\"dhcp-ddns\"", "\"Logging\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"Dhcp4\"",
  "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
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
  "expired_leases_param", "subnet6_list", "$@37", "subnet6_list_content",
  "not_empty_subnet6_list", "subnet6", "$@38", "sub_subnet6", "$@39",
  "subnet6_params", "subnet6_param", "subnet", "$@40", "interface", "$@41",
  "interface_id", "$@42", "client_class", "$@43", "reservation_mode",
  "$@44", "id", "rapid_commit", "option_def_list", "$@45",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@46", "sub_option_def", "$@47",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@48",
  "option_def_record_types", "$@49", "space", "$@50", "option_def_space",
  "option_def_encapsulate", "$@51", "option_def_array", "option_data_list",
  "$@52", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@53", "sub_option_data", "$@54",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@55",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@56", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@57", "sub_pool6", "$@58", "pool_params",
  "pool_param", "pool_entry", "$@59", "pd_pools_list", "$@60",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@61", "sub_pd_pool", "$@62", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@63", "pd_prefix_len", "excluded_prefix", "$@64",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@65",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@66", "sub_reservation", "$@67", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@68", "prefixes", "$@69", "duid", "$@70", "hw_address", "$@71",
  "hostname", "$@72", "reservation_client_classes", "$@73", "relay",
  "$@74", "relay_map", "$@75", "client_classes", "$@76",
  "client_classes_list", "$@77", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@78", "server_id", "$@79",
  "server_id_params", "server_id_param", "server_id_type", "$@80",
  "duid_type", "htype", "identifier", "$@81", "time", "enterprise_id",
  "dhcp4o6_port", "control_socket", "$@82", "control_socket_params",
  "control_socket_param", "socket_type", "$@83", "socket_name", "$@84",
  "dhcp_ddns", "$@85", "dhcp4_json_object", "$@86", "dhcpddns_json_object",
  "$@87", "logging_object", "$@88", "logging_params", "logging_param",
  "loggers", "$@89", "loggers_entries", "logger_entry", "$@90",
  "logger_params", "logger_param", "debuglevel", "severity", "$@91",
  "output_options_list", "$@92", "output_options_list_content",
  "output_entry", "$@93", "output_params", "output_param", "$@94", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   202,   202,   202,   203,   203,   204,   204,   205,   205,
     206,   206,   207,   207,   208,   208,   209,   209,   210,   210,
     211,   211,   212,   212,   220,   221,   222,   223,   224,   225,
     226,   229,   234,   234,   246,   247,   250,   254,   261,   261,
     269,   269,   276,   277,   280,   284,   295,   305,   305,   317,
     318,   322,   323,   324,   325,   326,   329,   329,   346,   346,
     354,   355,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   384,   389,   394,   399,   404,   409,
     409,   419,   419,   427,   427,   437,   437,   447,   447,   457,
     458,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     472,   472,   480,   480,   488,   488,   496,   496,   504,   504,
     512,   517,   522,   527,   527,   537,   538,   541,   542,   545,
     550,   555,   555,   565,   566,   569,   570,   573,   578,   578,
     588,   588,   598,   599,   602,   603,   606,   606,   614,   614,
     622,   623,   624,   627,   628,   631,   631,   639,   639,   647,
     647,   657,   658,   664,   672,   672,   685,   686,   689,   690,
     697,   697,   720,   720,   729,   730,   734,   735,   736,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   753,   753,   761,   761,   769,   769,   777,
     777,   785,   785,   793,   798,   807,   807,   819,   820,   823,
     824,   829,   829,   840,   840,   850,   851,   854,   855,   858,
     859,   860,   861,   862,   863,   864,   865,   868,   870,   875,
     877,   877,   885,   885,   893,   893,   901,   903,   903,   911,
     920,   920,   932,   933,   938,   939,   944,   944,   955,   955,
     966,   967,   972,   973,   978,   979,   980,   981,   982,   983,
     986,   988,   988,   996,   998,  1000,  1008,  1008,  1020,  1021,
    1024,  1025,  1028,  1028,  1036,  1036,  1044,  1045,  1048,  1049,
    1050,  1053,  1053,  1064,  1064,  1076,  1077,  1080,  1081,  1084,
    1084,  1092,  1092,  1100,  1101,  1104,  1105,  1106,  1107,  1108,
    1109,  1110,  1113,  1113,  1121,  1126,  1126,  1134,  1139,  1147,
    1147,  1157,  1158,  1161,  1162,  1165,  1165,  1173,  1173,  1181,
    1182,  1185,  1186,  1190,  1191,  1192,  1193,  1194,  1195,  1196,
    1197,  1200,  1200,  1210,  1210,  1220,  1220,  1228,  1228,  1236,
    1236,  1244,  1244,  1257,  1257,  1267,  1267,  1278,  1278,  1288,
    1289,  1292,  1292,  1300,  1301,  1304,  1305,  1308,  1309,  1310,
    1311,  1314,  1316,  1316,  1327,  1327,  1337,  1338,  1341,  1342,
    1343,  1344,  1345,  1346,  1347,  1350,  1350,  1357,  1358,  1359,
    1362,  1367,  1367,  1375,  1380,  1387,  1394,  1394,  1404,  1405,
    1408,  1409,  1412,  1412,  1420,  1420,  1430,  1430,  1442,  1442,
    1449,  1449,  1461,  1461,  1474,  1475,  1479,  1483,  1483,  1495,
    1496,  1500,  1500,  1508,  1509,  1512,  1513,  1514,  1515,  1516,
    1519,  1523,  1523,  1531,  1531,  1541,  1542,  1545,  1545,  1553,
    1554,  1557,  1557
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
#line 3583 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1565 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
