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
      case 125: // value
      case 350: // duid_type
        value.move< ElementPtr > (that.value);
        break;

      case 111: // "boolean"
        value.move< bool > (that.value);
        break;

      case 110: // "floating point"
        value.move< double > (that.value);
        break;

      case 109: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 108: // "constant string"
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
      case 125: // value
      case 350: // duid_type
        value.copy< ElementPtr > (that.value);
        break;

      case 111: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 110: // "floating point"
        value.copy< double > (that.value);
        break;

      case 109: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 108: // "constant string"
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
            case 108: // "constant string"

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 109: // "integer"

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 110: // "floating point"

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 111: // "boolean"

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 125: // value

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 350: // duid_type

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 125: // value
      case 350: // duid_type
        yylhs.value.build< ElementPtr > ();
        break;

      case 111: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 110: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 109: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 108: // "constant string"
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
#line 208 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 209 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 210 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 211 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 212 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 213 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 214 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 215 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 216 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 217 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 218 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 790 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 844 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 335 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 342 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 410 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 685 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1473 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1527 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1571 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1581 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1590 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 834 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1599 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1745 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1044 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2088 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2097 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2117 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1258 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2182 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2191 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1314 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2305 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2562 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2571 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2645 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2649 "dhcp6_parser.cc" // lalr1.cc:859
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
     107,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,    29,    21,    32,    56,    58,    60,    67,    71,
      73,    83,   103,   108,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,    21,   -56,    12,    59,
      42,    11,    -8,    95,    93,    61,    72,    50,  -427,   117,
     124,   129,   134,   148,  -427,  -427,  -427,  -427,   153,  -427,
      45,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   196,
     198,   237,   245,   246,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   265,  -427,  -427,  -427,    47,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   217,  -427,  -427,  -427,  -427,  -427,  -427,   266,
     267,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
      63,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,   118,  -427,  -427,
    -427,   268,  -427,   270,   272,  -427,  -427,   138,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   250,   274,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   275,  -427,  -427,  -427,   276,  -427,  -427,
     273,   279,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   280,  -427,  -427,  -427,  -427,   277,   283,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   156,
    -427,  -427,  -427,  -427,    21,    21,  -427,   170,   284,   285,
     286,   287,  -427,    12,  -427,   288,   289,   290,   174,   187,
     192,   193,   194,   291,   293,   294,   295,   296,   300,   301,
     302,   303,   304,   200,   306,   307,    59,  -427,   308,  -427,
       8,   309,   310,   311,   312,   313,   209,   176,   315,   316,
     317,   318,    11,  -427,   319,    -8,  -427,   320,   216,   322,
     218,   219,    95,  -427,   325,   326,   327,   328,   329,   330,
    -427,    93,   331,   332,   231,   335,   337,   338,   234,  -427,
      61,   339,   235,  -427,    72,   340,   343,    82,  -427,  -427,
    -427,   344,   342,   346,    21,    21,  -427,   347,   348,   349,
    -427,  -427,  -427,  -427,  -427,   345,   352,   355,   356,   357,
     358,   359,   360,   361,   364,  -427,   365,   366,  -427,   357,
    -427,  -427,  -427,  -427,   367,   363,  -427,  -427,  -427,   362,
     369,   269,   271,   278,  -427,  -427,   281,   282,   373,   374,
    -427,   292,  -427,   297,  -427,   298,  -427,  -427,  -427,   357,
     357,   357,   299,   314,   321,  -427,   323,   324,  -427,   333,
     334,   336,  -427,  -427,   341,  -427,  -427,   350,    21,  -427,
      21,    59,   305,  -427,  -427,    42,    26,    26,   375,   376,
     378,   -29,  -427,  -427,   123,    20,   380,   146,    80,   181,
     -56,  -427,   384,  -427,     8,   385,   386,  -427,  -427,  -427,
    -427,  -427,   387,   351,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   163,  -427,   171,  -427,  -427,   372,  -427,  -427,
    -427,  -427,   392,   393,   394,  -427,   175,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,   178,  -427,   395,   388,
    -427,  -427,   396,   400,  -427,  -427,   398,   405,  -427,  -427,
    -427,    86,  -427,  -427,  -427,    21,  -427,  -427,   162,  -427,
    -427,  -427,   233,  -427,   403,   407,  -427,   408,   410,   411,
     413,   414,   415,   188,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   416,   417,   419,  -427,  -427,   189,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,   190,  -427,  -427,
    -427,   191,   353,  -427,  -427,   418,   422,  -427,  -427,   420,
     424,  -427,  -427,   427,   425,  -427,  -427,   391,  -427,   426,
     305,  -427,  -427,   430,   431,   432,   433,   354,   368,   370,
      26,  -427,  -427,    11,  -427,   375,    61,  -427,   376,    72,
    -427,   378,   -29,  -427,   434,   123,  -427,    20,  -427,    50,
    -427,   380,   371,   377,   379,   381,   382,   383,   146,  -427,
     435,   439,   389,   390,   397,    80,  -427,   441,   442,   181,
    -427,  -427,  -427,    -8,  -427,   385,    95,  -427,   386,    93,
    -427,   387,   443,  -427,   445,  -427,   399,   401,   402,   404,
    -427,  -427,  -427,  -427,   220,  -427,   440,  -427,   444,  -427,
    -427,  -427,  -427,  -427,   221,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   186,   406,  -427,  -427,  -427,  -427,   409,
     412,  -427,   223,  -427,   224,  -427,   446,  -427,   421,   448,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
     240,  -427,    79,   448,  -427,  -427,   447,  -427,  -427,  -427,
     230,  -427,  -427,  -427,  -427,  -427,   449,   423,   452,    79,
    -427,   454,  -427,   428,  -427,   450,  -427,  -427,   254,  -427,
     429,   450,  -427,  -427,   232,  -427,  -427,   456,   429,  -427,
     436,  -427,  -427
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      91,     9,   183,    11,   285,    13,   302,    15,   328,    17,
     224,    19,   259,    21,   148,    23,    42,    34,     0,     0,
       0,     0,     0,     0,   330,   226,   261,     0,    44,     0,
      43,     0,     0,    35,    56,   413,   409,   411,     0,    55,
       0,    49,    51,    53,    54,    52,    89,    95,    97,     0,
       0,     0,     0,     0,   175,   216,   251,   123,   138,   131,
     358,   140,   159,   375,     0,   397,   407,    83,     0,    60,
      62,    63,    64,    65,    66,    68,    69,    70,    71,    73,
      72,    77,    78,    67,    75,    76,    74,    79,    80,    81,
      82,    93,     0,   362,   277,   294,   204,   206,   208,     0,
       0,   212,   210,   320,   354,   203,   187,   188,   189,   190,
       0,   185,   194,   195,   196,   199,   201,   197,   198,   191,
     192,   193,   200,   202,   292,   291,   290,     0,   287,   289,
     313,     0,   316,     0,     0,   312,   309,     0,   304,   306,
     307,   310,   311,   308,   352,   342,   344,   346,   348,   350,
     341,   340,     0,   331,   332,   336,   337,   334,   338,   339,
     335,   241,   118,     0,   245,   243,   248,     0,   237,   238,
       0,   227,   228,   230,   240,   231,   232,   233,   247,   234,
     235,   236,   272,     0,   270,   271,   274,   275,     0,   262,
     263,   265,   266,   267,   268,   269,   155,   157,   152,     0,
     150,   153,   154,    39,     0,     0,    33,     0,     0,     0,
       0,     0,    46,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,     0,    92,
     364,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   184,     0,     0,   286,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,     0,     0,     0,
     329,     0,     0,     0,     0,     0,     0,     0,     0,   225,
       0,     0,     0,   260,     0,     0,     0,     0,   149,    45,
      36,     0,     0,     0,     0,     0,    50,     0,     0,     0,
      84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   396,     0,     0,    61,     0,
     373,   371,   372,   370,     0,   365,   366,   368,   369,     0,
       0,     0,     0,     0,   214,   215,     0,     0,     0,     0,
     186,     0,   288,     0,   315,     0,   318,   319,   305,     0,
       0,     0,     0,     0,     0,   333,     0,     0,   239,     0,
       0,     0,   250,   229,     0,   276,   264,     0,     0,   151,
       0,     0,     0,   410,   412,     0,     0,     0,   177,   218,
     253,     0,    40,   139,     0,     0,   142,     0,     0,     0,
       0,    94,     0,   363,     0,   279,   296,   205,   207,   209,
     213,   211,   322,     0,   293,   314,   317,   353,   343,   345,
     347,   349,   351,   242,   119,   246,   244,   249,   273,   156,
     158,    37,     0,   418,     0,   415,   417,     0,   110,   112,
     114,   116,     0,     0,     0,   109,     0,    99,   101,   102,
     103,   104,   105,   106,   107,   108,     0,   181,     0,   178,
     179,   222,     0,   219,   220,   257,     0,   254,   255,   129,
     130,     0,   125,   127,   128,    42,   137,   135,     0,   133,
     136,   360,     0,   146,     0,   143,   144,     0,     0,     0,
       0,     0,     0,     0,   161,   163,   164,   165,   166,   167,
     168,   386,   392,     0,     0,     0,   385,   384,     0,   377,
     379,   382,   380,   381,   383,   403,   405,     0,   399,   401,
     402,     0,     0,   367,   283,     0,   280,   281,   300,     0,
     297,   298,   326,     0,   323,   324,   356,     0,    57,     0,
       0,   414,    90,     0,     0,     0,     0,     0,     0,     0,
       0,    96,    98,     0,   176,     0,   226,   217,     0,   261,
     252,     0,     0,   124,     0,     0,   132,     0,   359,     0,
     141,     0,     0,     0,     0,     0,     0,     0,     0,   160,
       0,     0,     0,     0,     0,     0,   376,     0,     0,     0,
     398,   408,   374,     0,   278,     0,     0,   295,     0,   330,
     321,     0,     0,   355,     0,   416,     0,     0,     0,     0,
     120,   121,   122,   100,     0,   180,     0,   221,     0,   256,
     126,    41,   134,   361,     0,   145,   169,   170,   171,   172,
     173,   174,   162,     0,     0,   391,   394,   395,   378,     0,
       0,   400,     0,   282,     0,   299,     0,   325,     0,     0,
     111,   113,   115,   117,   182,   223,   258,   147,   388,   389,
     390,   387,   393,   404,   406,   284,   301,   327,   357,   422,
       0,   420,     0,     0,   419,   434,     0,   432,   430,   426,
       0,   424,   428,   429,   427,   421,     0,     0,     0,     0,
     423,     0,   431,     0,   425,     0,   433,   438,     0,   436,
       0,     0,   435,   442,     0,   440,   437,     0,     0,   439,
       0,   441,   443
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,     3,  -427,  -427,  -427,  -427,    33,  -427,
    -427,  -214,  -427,   -67,  -427,   -58,  -427,  -427,  -427,   211,
    -427,  -427,  -427,  -427,    51,   195,   -41,   -38,   -37,   -36,
    -427,  -427,  -427,  -427,  -427,    52,  -427,  -427,  -427,  -427,
    -427,    49,  -112,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,   -65,  -427,  -426,  -427,  -427,  -427,  -427,  -427,  -123,
    -405,  -427,  -427,  -427,  -427,  -125,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -129,  -427,  -427,  -427,  -126,   147,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -133,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -109,  -427,  -427,
    -427,  -105,   197,  -427,  -427,  -427,  -427,  -427,  -427,  -415,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -106,
    -427,  -427,  -427,  -107,  -427,   164,  -427,   -51,  -427,  -427,
    -427,  -427,  -427,   -49,  -427,  -427,  -427,  -427,  -427,   -50,
    -427,  -427,  -427,  -108,  -427,  -427,  -427,  -104,  -427,   169,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -138,  -427,  -427,  -427,  -128,   199,  -427,  -427,  -427,  -427,
    -427,  -427,  -132,  -427,  -427,  -427,  -124,   201,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -134,
    -427,  -427,  -427,  -121,  -427,   202,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,    66,  -427,
    -427,  -427,  -427,  -427,  -427,  -114,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -115,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   -59,  -427,  -427,  -427,  -198,  -427,  -427,  -203,
    -427,  -427,  -427,  -427,  -427,  -427,  -213,  -427,  -427,  -219,
    -427
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   423,   505,    69,    70,   107,    37,    58,    80,    81,
      82,   248,    39,    59,   108,   109,   110,   111,   112,   113,
     114,   115,   255,    41,    60,   132,   278,   116,   256,   117,
     257,   476,   477,   478,   573,   479,   574,   480,   575,   481,
     576,   209,   313,   483,   484,   485,   118,   266,   501,   502,
     503,   504,   119,   268,   508,   509,   510,   120,   267,   121,
     270,   514,   515,   516,   599,    55,    67,   239,   240,   241,
     325,   242,   326,   122,   271,   523,   524,   525,   526,   527,
     528,   529,   530,   123,   263,   488,   489,   490,   583,    43,
      61,   150,   151,   152,   283,   153,   284,   154,   285,   155,
     289,   156,   288,   157,   158,   124,   264,   492,   493,   494,
     586,    51,    65,   210,   211,   212,   213,   214,   215,   216,
     312,   217,   316,   218,   315,   219,   220,   317,   221,   125,
     265,   496,   497,   498,   589,    53,    66,   228,   229,   230,
     231,   232,   321,   233,   234,   235,   160,   281,   555,   556,
     557,   623,    45,    62,   167,   168,   169,   294,   161,   282,
     559,   560,   561,   626,    47,    63,   177,   178,   179,   297,
     180,   181,   299,   182,   183,   162,   290,   563,   564,   565,
     629,    49,    64,   192,   193,   194,   195,   305,   196,   306,
     197,   307,   198,   308,   199,   309,   200,   304,   163,   291,
     567,   632,   126,   269,   512,   280,   364,   365,   366,   367,
     368,   432,   127,   272,   538,   539,   540,   610,   691,   541,
     542,   611,   543,   544,   128,   129,   274,   547,   548,   549,
     617,   550,   618,   130,   275,    83,   250,    84,   251,    85,
     249,   464,   465,   466,   569,   700,   701,   702,   710,   711,
     712,   713,   718,   714,   716,   728,   729,   730,   734,   735,
     737
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   225,   537,   145,   165,   175,   190,   208,   224,   238,
     511,   159,   166,   176,   191,   226,    32,   227,   133,   507,
     146,    96,    74,   147,   148,   149,    25,   133,    26,    24,
      27,   164,   499,    89,    90,    91,    92,    96,   202,    36,
      96,   468,   469,   470,   471,   472,   473,   474,   253,   134,
     276,   135,    71,   254,   131,   277,   202,   136,   137,   138,
     139,   140,   141,    38,   360,    40,   292,    42,   142,   143,
      86,   293,    87,    88,    44,   144,   201,   142,    46,   500,
      48,    89,    90,    91,    92,    93,    94,    95,    96,   592,
      50,   202,   593,   203,   204,   531,   205,   206,   207,   472,
      78,    75,   202,   222,   203,   204,   223,    76,    77,   202,
      52,    97,    98,    99,   100,    54,    78,   236,   237,    78,
      78,   295,    96,   243,    96,   101,   296,   244,   102,    28,
      29,    30,    31,   245,    78,   103,   170,   171,   172,   173,
     174,   302,   246,   104,   105,   431,   303,   106,   184,   236,
     237,   247,   185,   186,   187,   188,   189,   252,    78,   327,
     532,   533,   534,   535,   328,   595,   276,    78,   596,    78,
     705,   568,   706,   707,   570,   447,   448,   449,   580,   571,
      78,   580,   653,   581,   499,   506,   582,    78,    78,   537,
     507,   608,   615,   619,   247,    79,   609,   616,   620,   621,
     258,    78,   259,    78,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,   362,   517,   518,   519,   520,
     521,   522,   361,   292,   327,   279,   295,   302,   684,   687,
     363,   695,   696,   719,   145,   738,   597,   165,   720,   598,
     739,   260,   159,   703,   175,   166,   704,   329,   330,   261,
     262,   146,   176,   190,   147,   148,   149,   731,   310,   225,
     732,   191,   208,   688,   689,   690,   224,   545,   546,   273,
     286,   287,   298,   226,   300,   227,   301,   311,   331,   314,
     318,   319,   320,   340,   322,   323,   324,   375,   332,   333,
     334,   335,   337,   338,   339,   345,   341,   346,   347,   348,
     349,   342,   343,   344,   350,   351,   352,   353,   354,   355,
     356,   357,   359,   369,   370,   371,   372,   373,   374,   376,
     377,   378,   379,   381,   383,   384,   385,   386,   387,   389,
     390,   391,   392,   393,   394,   396,   397,   413,   414,   399,
     398,   400,   401,   404,   407,   402,   405,   408,   410,   411,
     418,   482,   482,   412,   415,   416,   417,   419,   475,   475,
     420,   421,   422,   424,   425,   426,   434,   435,   427,   362,
     536,   428,   429,   430,   436,   433,   361,   437,   442,   438,
     572,   443,   487,   491,   363,   495,   439,   513,   552,   440,
     441,   585,   554,   558,   562,   463,   577,   578,   579,   633,
     444,   584,   587,   588,   590,   445,   446,   450,   591,   600,
     601,   460,   602,   461,   603,   604,   566,   605,   606,   607,
     612,   613,   451,   614,   624,   625,   627,   628,   631,   452,
     634,   453,   454,   630,   636,   637,   638,   639,   594,   663,
     651,   455,   456,   664,   457,   669,   670,   678,   685,   458,
     679,   717,   686,   721,   697,   699,   723,   727,   459,   725,
     740,   622,   462,   551,   336,   640,   486,   467,   643,   650,
     652,   358,   655,   654,   409,   662,   645,   641,   644,   646,
     656,   642,   647,   649,   403,   648,   657,   673,   658,   380,
     659,   660,   661,   406,   382,   672,   675,   677,   665,   666,
     553,   668,   674,   388,   671,   715,   667,   680,   676,   681,
     682,   635,   683,   395,   692,   482,   724,   693,   736,   741,
     694,   733,   475,     0,   225,   145,     0,     0,   208,   698,
       0,   224,   722,   159,     0,     0,   726,     0,   226,     0,
     227,   238,   146,     0,   742,   147,   148,   149,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   536,     0,     0,
       0,     0,     0,     0,     0,   165,     0,     0,   175,     0,
       0,   190,     0,   166,     0,     0,   176,     0,     0,   191,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   709,     0,     0,
       0,     0,     0,     0,   708,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   709,     0,     0,     0,     0,     0,
       0,   708
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,   428,    61,    62,    63,    64,    65,    66,    67,
     425,    61,    62,    63,    64,    66,    13,    66,     7,   424,
      61,    29,    10,    61,    61,    61,     5,     7,     7,     0,
       9,    39,    61,    22,    23,    24,    25,    29,    30,     7,
      29,    15,    16,    17,    18,    19,    20,    21,     3,    38,
       3,    40,   108,     8,    12,     8,    30,    46,    47,    48,
      49,    50,    51,     7,    56,     7,     3,     7,    57,    58,
      11,     8,    13,    14,     7,    64,    15,    57,     7,   108,
       7,    22,    23,    24,    25,    26,    27,    28,    29,     3,
       7,    30,     6,    32,    33,    15,    35,    36,    37,    19,
     108,    89,    30,    31,    32,    33,    34,    95,    96,    30,
       7,    52,    53,    54,    55,     7,   108,    67,    68,   108,
     108,     3,    29,     6,    29,    66,     8,     3,    69,   108,
     109,   110,   111,     4,   108,    76,    41,    42,    43,    44,
      45,     3,     8,    84,    85,   359,     8,    88,    55,    67,
      68,     3,    59,    60,    61,    62,    63,     4,   108,     3,
      80,    81,    82,    83,     8,     3,     3,   108,     6,   108,
      91,     8,    93,    94,     3,   389,   390,   391,     3,     8,
     108,     3,   597,     8,    61,    62,     8,   108,   108,   615,
     595,     3,     3,     3,     3,   253,     8,     8,     8,     8,
       4,   108,     4,   108,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   280,    70,    71,    72,    73,
      74,    75,   280,     3,     3,     8,     3,     3,     8,     8,
     280,     8,     8,     3,   292,     3,     3,   295,     8,     6,
       8,     4,   292,     3,   302,   295,     6,   244,   245,     4,
       4,   292,   302,   311,   292,   292,   292,     3,     8,   324,
       6,   311,   320,    77,    78,    79,   324,    86,    87,     4,
       4,     4,     4,   324,     4,   324,     4,     3,   108,     4,
       4,     8,     3,   109,     4,     8,     3,   111,     4,     4,
       4,     4,     4,     4,     4,     4,   109,     4,     4,     4,
       4,   109,   109,   109,     4,     4,     4,     4,     4,   109,
       4,     4,     4,     4,     4,     4,     4,     4,   109,     4,
       4,     4,     4,     4,     4,   109,     4,   109,   109,     4,
       4,     4,     4,     4,     4,     4,     4,   334,   335,     4,
     109,     4,     4,     4,     4,   111,   111,     4,     4,     7,
       5,   416,   417,     7,     7,     7,     7,     5,   416,   417,
       5,     5,     5,     5,     5,     5,     3,     5,     7,   434,
     428,     7,     7,     7,     5,     8,   434,   108,     5,   108,
       8,     7,     7,     7,   434,     7,   108,     7,     4,   108,
     108,     3,     7,     7,     7,    90,     4,     4,     4,     8,
     108,     6,     6,     3,     6,   108,   108,   108,     3,     6,
       3,   408,     4,   410,     4,     4,    65,     4,     4,     4,
       4,     4,   108,     4,     6,     3,     6,     3,     3,   108,
       4,   108,   108,     6,     4,     4,     4,     4,   505,     4,
       6,   108,   108,     4,   108,     4,     4,     4,     8,   108,
       5,     4,     8,     4,     8,     7,     4,     7,   108,     5,
       4,   108,   411,   430,   253,   111,   417,   415,   580,   592,
     595,   276,   601,   599,   327,   608,   585,   109,   583,   586,
     109,   111,   588,   591,   320,   589,   109,   625,   109,   292,
     109,   109,   109,   324,   295,   623,   628,   631,   109,   109,
     434,   615,   626,   302,   619,   703,   109,   108,   629,   108,
     108,   570,   108,   311,   108,   580,   719,   108,   731,   738,
     108,    92,   580,    -1,   589,   583,    -1,    -1,   586,   108,
      -1,   589,   109,   583,    -1,    -1,   108,    -1,   589,    -1,
     589,   599,   583,    -1,   108,   583,   583,   583,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   615,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   623,    -1,    -1,   626,    -1,
      -1,   629,    -1,   623,    -1,    -1,   626,    -1,    -1,   629,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   702,    -1,    -1,
      -1,    -1,    -1,    -1,   702,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   719,    -1,    -1,    -1,    -1,    -1,
      -1,   719
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,     0,     5,     7,     9,   108,   109,
     110,   111,   125,   126,   127,   131,     7,   138,     7,   144,
       7,   155,     7,   221,     7,   284,     7,   296,     7,   313,
       7,   243,     7,   267,     7,   197,   132,   128,   139,   145,
     156,   222,   285,   297,   314,   244,   268,   198,   125,   135,
     136,   108,   129,   130,    10,    89,    95,    96,   108,   137,
     140,   141,   142,   367,   369,   371,    11,    13,    14,    22,
      23,    24,    25,    26,    27,    28,    29,    52,    53,    54,
      55,    66,    69,    76,    84,    85,    88,   137,   146,   147,
     148,   149,   150,   151,   152,   153,   159,   161,   178,   184,
     189,   191,   205,   215,   237,   261,   334,   344,   356,   357,
     365,    12,   157,     7,    38,    40,    46,    47,    48,    49,
      50,    51,    57,    58,    64,   137,   148,   149,   150,   151,
     223,   224,   225,   227,   229,   231,   233,   235,   236,   261,
     278,   290,   307,   330,    39,   137,   261,   286,   287,   288,
      41,    42,    43,    44,    45,   137,   261,   298,   299,   300,
     302,   303,   305,   306,    55,    59,    60,    61,    62,    63,
     137,   261,   315,   316,   317,   318,   320,   322,   324,   326,
     328,    15,    30,    32,    33,    35,    36,    37,   137,   173,
     245,   246,   247,   248,   249,   250,   251,   253,   255,   257,
     258,   260,    31,    34,   137,   173,   249,   255,   269,   270,
     271,   272,   273,   275,   276,   277,    67,    68,   137,   199,
     200,   201,   203,     6,     3,     4,     8,     3,   143,   372,
     368,   370,     4,     3,     8,   154,   160,   162,     4,     4,
       4,     4,     4,   216,   238,   262,   179,   190,   185,   335,
     192,   206,   345,     4,   358,   366,     3,     8,   158,     8,
     337,   279,   291,   226,   228,   230,     4,     4,   234,   232,
     308,   331,     3,     8,   289,     3,     8,   301,     4,   304,
       4,     4,     3,     8,   329,   319,   321,   323,   325,   327,
       8,     3,   252,   174,     4,   256,   254,   259,     4,     8,
       3,   274,     4,     8,     3,   202,   204,     3,     8,   125,
     125,   108,     4,     4,     4,     4,   141,     4,     4,     4,
     109,   109,   109,   109,   109,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   109,     4,     4,   147,     4,
      56,   137,   173,   261,   338,   339,   340,   341,   342,     4,
       4,     4,     4,     4,   109,   111,     4,     4,     4,     4,
     224,     4,   287,     4,   109,     4,   109,   109,   299,     4,
       4,     4,     4,     4,     4,   317,     4,     4,   109,     4,
       4,     4,   111,   247,     4,   111,   271,     4,     4,   200,
       4,     7,     7,   125,   125,     7,     7,     7,     5,     5,
       5,     5,     5,   133,     5,     5,     5,     7,     7,     7,
       7,   133,   343,     8,     3,     5,     5,   108,   108,   108,
     108,   108,     5,     7,   108,   108,   108,   133,   133,   133,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     125,   125,   146,    90,   373,   374,   375,   157,    15,    16,
      17,    18,    19,    20,    21,   137,   163,   164,   165,   167,
     169,   171,   173,   175,   176,   177,   163,     7,   217,   218,
     219,     7,   239,   240,   241,     7,   263,   264,   265,    61,
     108,   180,   181,   182,   183,   134,    62,   182,   186,   187,
     188,   231,   336,     7,   193,   194,   195,    70,    71,    72,
      73,    74,    75,   207,   208,   209,   210,   211,   212,   213,
     214,    15,    80,    81,    82,    83,   137,   175,   346,   347,
     348,   351,   352,   354,   355,    86,    87,   359,   360,   361,
     363,   130,     4,   340,     7,   280,   281,   282,     7,   292,
     293,   294,     7,   309,   310,   311,    65,   332,     8,   376,
       3,     8,     8,   166,   168,   170,   172,     4,     4,     4,
       3,     8,     8,   220,     6,     3,   242,     6,     3,   266,
       6,     3,     3,     6,   135,     3,     6,     3,     6,   196,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     349,   353,     4,     4,     4,     3,     8,   362,   364,     3,
       8,     8,   108,   283,     6,     3,   295,     6,     3,   312,
       6,     3,   333,     8,     4,   374,     4,     4,     4,     4,
     111,   109,   111,   164,   223,   219,   245,   241,   269,   265,
     181,     6,   187,   231,   199,   195,   109,   109,   109,   109,
     109,   109,   208,     4,     4,   109,   109,   109,   347,     4,
       4,   360,   286,   282,   298,   294,   315,   311,     4,     5,
     108,   108,   108,   108,     8,     8,     8,     8,    77,    78,
      79,   350,   108,   108,   108,     8,     8,     8,   108,     7,
     377,   378,   379,     3,     6,    91,    93,    94,   137,   173,
     380,   381,   382,   383,   385,   378,   386,     4,   384,     3,
       8,     4,   109,     4,   381,     5,   108,     7,   387,   388,
     389,     3,     6,    92,   390,   391,   388,   392,     3,     8,
       4,   391,   108
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   112,   114,   113,   115,   113,   116,   113,   117,   113,
     118,   113,   119,   113,   120,   113,   121,   113,   122,   113,
     123,   113,   124,   113,   125,   125,   125,   125,   125,   125,
     125,   126,   128,   127,   129,   129,   130,   130,   132,   131,
     134,   133,   135,   135,   136,   136,   137,   139,   138,   140,
     140,   141,   141,   141,   141,   141,   143,   142,   145,   144,
     146,   146,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   148,   149,   150,   151,   152,   154,
     153,   156,   155,   158,   157,   160,   159,   162,   161,   163,
     163,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     166,   165,   168,   167,   170,   169,   172,   171,   174,   173,
     175,   176,   177,   179,   178,   180,   180,   181,   181,   182,
     183,   185,   184,   186,   186,   187,   187,   188,   190,   189,
     192,   191,   193,   193,   194,   194,   196,   195,   198,   197,
     199,   199,   199,   200,   200,   202,   201,   204,   203,   206,
     205,   207,   207,   208,   208,   208,   208,   208,   208,   209,
     210,   211,   212,   213,   214,   216,   215,   217,   217,   218,
     218,   220,   219,   222,   221,   223,   223,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   226,   225,   228,   227,   230,   229,
     232,   231,   234,   233,   235,   236,   238,   237,   239,   239,
     240,   240,   242,   241,   244,   243,   245,   245,   246,   246,
     247,   247,   247,   247,   247,   247,   247,   247,   248,   249,
     250,   252,   251,   254,   253,   256,   255,   257,   259,   258,
     260,   262,   261,   263,   263,   264,   264,   266,   265,   268,
     267,   269,   269,   270,   270,   271,   271,   271,   271,   271,
     271,   272,   274,   273,   275,   276,   277,   279,   278,   280,
     280,   281,   281,   283,   282,   285,   284,   286,   286,   287,
     287,   287,   289,   288,   291,   290,   292,   292,   293,   293,
     295,   294,   297,   296,   298,   298,   299,   299,   299,   299,
     299,   299,   299,   301,   300,   302,   304,   303,   305,   306,
     308,   307,   309,   309,   310,   310,   312,   311,   314,   313,
     315,   315,   316,   316,   317,   317,   317,   317,   317,   317,
     317,   317,   319,   318,   321,   320,   323,   322,   325,   324,
     327,   326,   329,   328,   331,   330,   333,   332,   335,   334,
     336,   336,   337,   231,   338,   338,   339,   339,   340,   340,
     340,   340,   341,   343,   342,   345,   344,   346,   346,   347,
     347,   347,   347,   347,   347,   347,   349,   348,   350,   350,
     350,   351,   353,   352,   354,   355,   356,   358,   357,   359,
     359,   360,   360,   362,   361,   364,   363,   366,   365,   368,
     367,   370,   369,   372,   371,   373,   373,   374,   376,   375,
     377,   377,   379,   378,   380,   380,   381,   381,   381,   381,
     381,   382,   384,   383,   386,   385,   387,   387,   389,   388,
     390,   390,   392,   391
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
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     0,     4
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
  "$@11", "value", "sub_json", "map2", "$@12", "map_content",
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
       0,   208,   208,   208,   209,   209,   210,   210,   211,   211,
     212,   212,   213,   213,   214,   214,   215,   215,   216,   216,
     217,   217,   218,   218,   226,   227,   228,   229,   230,   231,
     232,   235,   240,   240,   252,   253,   256,   260,   267,   267,
     275,   275,   282,   283,   286,   290,   301,   311,   311,   323,
     324,   328,   329,   330,   331,   332,   335,   335,   352,   352,
     360,   361,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   390,   395,   400,   405,   410,   415,
     415,   425,   425,   433,   433,   443,   443,   453,   453,   463,
     464,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     478,   478,   486,   486,   494,   494,   502,   502,   510,   510,
     518,   523,   528,   533,   533,   543,   544,   547,   548,   551,
     556,   561,   561,   571,   572,   575,   576,   579,   584,   584,
     594,   594,   604,   605,   608,   609,   612,   612,   620,   620,
     628,   629,   630,   633,   634,   637,   637,   645,   645,   653,
     653,   663,   664,   667,   668,   669,   670,   671,   672,   675,
     680,   685,   690,   695,   700,   708,   708,   721,   722,   725,
     726,   733,   733,   756,   756,   765,   766,   770,   771,   772,
     773,   774,   775,   776,   777,   778,   779,   780,   781,   782,
     783,   784,   785,   786,   789,   789,   797,   797,   805,   805,
     813,   813,   821,   821,   829,   834,   843,   843,   855,   856,
     859,   860,   865,   865,   876,   876,   886,   887,   890,   891,
     894,   895,   896,   897,   898,   899,   900,   901,   904,   906,
     911,   913,   913,   921,   921,   929,   929,   937,   939,   939,
     947,   956,   956,   968,   969,   974,   975,   980,   980,   991,
     991,  1002,  1003,  1008,  1009,  1014,  1015,  1016,  1017,  1018,
    1019,  1022,  1024,  1024,  1032,  1034,  1036,  1044,  1044,  1056,
    1057,  1060,  1061,  1064,  1064,  1072,  1072,  1080,  1081,  1084,
    1085,  1086,  1089,  1089,  1100,  1100,  1112,  1113,  1116,  1117,
    1120,  1120,  1128,  1128,  1136,  1137,  1140,  1141,  1142,  1143,
    1144,  1145,  1146,  1149,  1149,  1157,  1162,  1162,  1170,  1175,
    1183,  1183,  1193,  1194,  1197,  1198,  1201,  1201,  1209,  1209,
    1217,  1218,  1221,  1222,  1226,  1227,  1228,  1229,  1230,  1231,
    1232,  1233,  1236,  1236,  1246,  1246,  1256,  1256,  1264,  1264,
    1272,  1272,  1280,  1280,  1293,  1293,  1303,  1303,  1314,  1314,
    1324,  1325,  1328,  1328,  1336,  1337,  1340,  1341,  1344,  1345,
    1346,  1347,  1350,  1352,  1352,  1363,  1363,  1373,  1374,  1377,
    1378,  1379,  1380,  1381,  1382,  1383,  1386,  1386,  1393,  1394,
    1395,  1398,  1403,  1403,  1411,  1416,  1423,  1430,  1430,  1440,
    1441,  1444,  1445,  1448,  1448,  1456,  1456,  1466,  1466,  1478,
    1478,  1485,  1485,  1497,  1497,  1510,  1511,  1515,  1519,  1519,
    1531,  1532,  1536,  1536,  1544,  1545,  1548,  1549,  1550,  1551,
    1552,  1555,  1559,  1559,  1567,  1567,  1577,  1578,  1581,  1581,
    1589,  1590,  1593,  1593
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
#line 3648 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1601 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
