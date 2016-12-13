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
      case 117: // value
      case 341: // version_value
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
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 117: // value
      case 341: // version_value
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
            case 100: // "constant string"

#line 191 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 101: // "integer"

#line 191 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 102: // "floating point"

#line 191 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 103: // "boolean"

#line 191 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 117: // value

#line 191 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 341: // version_value

#line 191 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 117: // value
      case 341: // version_value
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
#line 200 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 201 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 202 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 203 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 204 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 205 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 206 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 207 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 208 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 209 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 210 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 218 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 219 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 220 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 221 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 790 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 844 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 327 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 418 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 173:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 754 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1584 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1029 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1108 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 1940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 1958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1158 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1166 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2119 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2186 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2278 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("version", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1382 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 2319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 2325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2351 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2537 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2556 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -424;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     191,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,    36,    22,    45,    62,    69,   124,   182,   186,
     220,   221,   222,   223,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,    22,   -57,    16,    85,
     141,    15,    29,    76,    73,    52,   116,   -26,  -424,    75,
     203,   218,   205,   228,  -424,  -424,  -424,  -424,   229,  -424,
      51,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,   231,
     235,   236,   238,   239,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,   240,  -424,  -424,  -424,  -424,    67,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,   224,  -424,  -424,  -424,  -424,  -424,
    -424,   241,   243,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,    92,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,    98,
    -424,  -424,  -424,   246,  -424,   247,   248,  -424,  -424,   156,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,   245,   251,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,   257,  -424,  -424,  -424,   258,
    -424,  -424,  -424,   256,   264,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,   265,  -424,  -424,  -424,
    -424,   260,   268,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,   160,  -424,  -424,  -424,  -424,    22,    22,  -424,
     172,   269,   270,   271,   272,  -424,    16,  -424,   274,   287,
     288,   192,   193,   194,   195,   198,   293,   294,   296,   297,
     298,   299,   300,   301,   302,   303,   208,   304,   306,   307,
      85,  -424,   308,  -424,    27,   309,   310,   311,   312,   313,
     219,   216,   314,   317,   318,   319,    15,  -424,   320,    29,
    -424,   321,   225,   325,   230,   232,    76,  -424,   326,   328,
     330,   331,   332,   333,  -424,    73,   334,   335,   242,   336,
     337,   338,   244,  -424,    52,   340,   249,  -424,   116,   341,
     342,    25,  -424,  -424,  -424,   344,   343,   346,    22,    22,
    -424,   347,   348,   351,  -424,  -424,  -424,  -424,  -424,   354,
     355,   356,   357,   360,   361,   362,   363,   364,   365,  -424,
     -67,   366,   367,  -424,   360,  -424,  -424,  -424,  -424,   368,
     374,  -424,  -424,  -424,   375,   376,   279,   282,   283,  -424,
    -424,   284,   286,   382,   381,  -424,   289,  -424,   290,  -424,
     291,  -424,  -424,  -424,   360,   360,   360,   292,   295,   305,
    -424,   315,   316,  -424,   322,   323,   324,  -424,  -424,   327,
    -424,  -424,   329,    22,  -424,    22,    85,   267,  -424,  -424,
     141,    30,    30,   387,   389,   390,   -29,  -424,  -424,   105,
      21,   391,   339,    71,  -424,  -424,  -424,  -424,   146,   -57,
    -424,   395,  -424,    27,   393,   394,  -424,  -424,  -424,  -424,
    -424,   396,   345,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,   166,  -424,   167,  -424,  -424,   398,  -424,  -424,  -424,
     403,   404,   405,  -424,   176,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,   180,  -424,   406,   408,  -424,  -424,
     407,   411,  -424,  -424,   412,   414,  -424,  -424,  -424,    74,
    -424,  -424,  -424,    22,  -424,  -424,    88,  -424,  -424,  -424,
     174,  -424,   413,   417,  -424,   421,   183,  -424,  -424,   422,
     424,   426,  -424,  -424,  -424,   184,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,   187,  -424,  -424,  -424,   196,   349,  -424,
    -424,   415,   428,  -424,  -424,   427,   429,  -424,  -424,   430,
     431,  -424,  -424,   432,  -424,   433,   267,  -424,  -424,   434,
     437,   438,   266,   250,   350,    30,  -424,  -424,    15,  -424,
     387,    52,  -424,   389,   116,  -424,   390,   -29,  -424,   439,
     105,  -424,    21,  -424,   -26,  -424,   391,   353,   339,  -424,
     440,   358,   359,   369,    71,  -424,   442,   443,   146,  -424,
    -424,  -424,    29,  -424,   393,    76,  -424,   394,    73,  -424,
     396,   444,  -424,   445,  -424,   352,   371,   372,  -424,  -424,
    -424,  -424,   197,  -424,   435,  -424,   447,  -424,  -424,  -424,
    -424,  -424,   199,  -424,  -424,  -424,   373,  -424,  -424,  -424,
    -424,   377,   378,  -424,   200,  -424,   206,  -424,   448,  -424,
     379,   450,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,   215,  -424,   111,
     450,  -424,  -424,   454,  -424,  -424,  -424,   207,  -424,  -424,
    -424,  -424,  -424,   457,   380,   458,   111,  -424,   446,  -424,
     383,  -424,   456,  -424,  -424,   217,  -424,   384,   456,  -424,
    -424,   209,  -424,  -424,   460,   384,  -424,   385,  -424,  -424
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      92,     9,   173,    11,   274,    13,   291,    15,   317,    17,
     214,    19,   248,    21,   149,    23,    42,    34,     0,     0,
       0,     0,     0,     0,   319,   216,   250,     0,    44,     0,
      43,     0,     0,    35,    56,   402,   398,   400,     0,    55,
       0,    49,    51,    53,    54,    52,    90,    96,    98,     0,
       0,     0,     0,     0,   165,   206,   240,   124,   139,   132,
     347,   141,   160,   364,     0,   381,   386,   396,    84,     0,
      60,    62,    63,    64,    65,    66,    68,    69,    70,    71,
      73,    72,    77,    78,    67,    75,    76,    74,    79,    80,
      81,    82,    83,    94,     0,   351,   266,   283,   194,   196,
     198,     0,     0,   202,   200,   309,   343,   193,   177,   178,
     179,   180,     0,   175,   184,   185,   186,   189,   191,   187,
     188,   181,   182,   183,   190,   192,   281,   280,   279,     0,
     276,   278,   302,     0,   305,     0,     0,   301,   298,     0,
     293,   295,   296,   299,   300,   297,   341,   331,   333,   335,
     337,   339,   330,   329,     0,   320,   321,   325,   326,   323,
     327,   328,   324,   111,   119,     0,   234,   232,   237,     0,
     227,   231,   228,     0,   217,   218,   220,   230,   221,   222,
     223,   236,   224,   225,   226,   261,     0,   259,   260,   263,
     264,     0,   251,   252,   254,   255,   256,   257,   258,   156,
     158,   153,     0,   151,   154,   155,    39,     0,     0,    33,
       0,     0,     0,     0,     0,    46,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,     0,    93,   353,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   174,     0,     0,
     275,     0,     0,     0,     0,     0,     0,   292,     0,     0,
       0,     0,     0,     0,   318,     0,     0,     0,     0,     0,
       0,     0,     0,   215,     0,     0,     0,   249,     0,     0,
       0,     0,   150,    45,    36,     0,     0,     0,     0,     0,
      50,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   380,
       0,     0,     0,    61,     0,   362,   360,   361,   359,     0,
     354,   355,   357,   358,     0,     0,     0,     0,     0,   204,
     205,     0,     0,     0,     0,   176,     0,   277,     0,   304,
       0,   307,   308,   294,     0,     0,     0,     0,     0,     0,
     322,     0,     0,   229,     0,     0,     0,   239,   219,     0,
     265,   253,     0,     0,   152,     0,     0,     0,   399,   401,
       0,     0,     0,   167,   208,   242,     0,    40,   140,     0,
       0,   143,     0,     0,   385,   383,   384,   382,     0,     0,
      95,     0,   352,     0,   268,   285,   195,   197,   199,   203,
     201,   311,     0,   282,   303,   306,   342,   332,   334,   336,
     338,   340,   112,   120,   235,   233,   238,   262,   157,   159,
      37,     0,   407,     0,   404,   406,     0,   113,   115,   117,
       0,     0,     0,   110,     0,   100,   102,   103,   104,   105,
     106,   107,   108,   109,     0,   171,     0,   168,   169,   212,
       0,   209,   210,   246,     0,   243,   244,   130,   131,     0,
     126,   128,   129,    42,   138,   136,     0,   134,   137,   349,
       0,   147,     0,   144,   145,     0,     0,   162,   376,     0,
       0,     0,   374,   368,   373,     0,   366,   371,   369,   370,
     372,   392,   394,     0,   388,   390,   391,     0,     0,   356,
     272,     0,   269,   270,   289,     0,   286,   287,   315,     0,
     312,   313,   345,     0,    57,     0,     0,   403,    91,     0,
       0,     0,     0,     0,     0,     0,    97,    99,     0,   166,
       0,   216,   207,     0,   250,   241,     0,     0,   125,     0,
       0,   133,     0,   348,     0,   142,     0,     0,     0,   161,
       0,     0,     0,     0,     0,   365,     0,     0,     0,   387,
     397,   363,     0,   267,     0,     0,   284,     0,   319,   310,
       0,     0,   344,     0,   405,     0,     0,     0,   121,   122,
     123,   101,     0,   170,     0,   211,     0,   245,   127,    41,
     135,   350,     0,   146,   164,   163,     0,   375,   378,   379,
     367,     0,     0,   389,     0,   271,     0,   288,     0,   314,
       0,     0,   114,   116,   118,   172,   213,   247,   148,   377,
     393,   395,   273,   290,   316,   346,   411,     0,   409,     0,
       0,   408,   423,     0,   421,   419,   415,     0,   413,   417,
     418,   416,   410,     0,     0,     0,     0,   412,     0,   420,
       0,   414,     0,   422,   427,     0,   425,     0,     0,   424,
     431,     0,   429,   426,     0,     0,   428,     0,   430,   432
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,   -11,  -424,  -424,  -424,  -424,   -69,  -424,
    -424,  -238,  -424,   -78,  -424,   -58,  -424,  -424,  -424,   210,
    -424,  -424,  -424,  -424,    49,   189,   -41,   -38,   -37,   -36,
    -424,  -424,  -424,  -424,  -424,    47,  -424,  -424,  -424,  -424,
    -424,    53,  -101,  -403,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,   -65,  -424,  -423,  -424,  -424,  -424,  -424,  -424,  -111,
    -408,  -424,  -424,  -424,  -424,  -110,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -114,  -424,  -424,  -424,  -108,   153,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -109,  -424,  -424,  -424,
    -424,   -93,  -424,  -424,  -424,   -90,   201,  -424,  -424,  -424,
    -424,  -424,  -424,  -414,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,   -92,  -424,  -424,  -424,   -91,  -424,   168,
    -424,   -51,  -424,  -424,  -424,  -424,   -49,  -424,  -424,  -424,
    -424,  -424,   -50,  -424,  -424,  -424,   -88,  -424,  -424,  -424,
     -89,  -424,   165,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -120,  -424,  -424,  -424,  -116,   202,  -424,
    -424,  -424,  -424,  -424,  -424,  -118,  -424,  -424,  -424,  -115,
     212,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -117,  -424,  -424,  -424,  -113,  -424,   214,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,    59,  -424,  -424,  -424,  -424,  -424,  -424,  -100,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -102,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,   -59,  -424,  -424,  -424,  -172,
    -424,  -424,  -187,  -424,  -424,  -424,  -424,  -424,  -424,  -197,
    -424,  -424,  -203,  -424
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   428,   513,    69,    70,   108,    37,    58,    80,    81,
      82,   251,    39,    59,   109,   110,   111,   112,   113,   114,
     115,   116,   258,    41,    60,   134,   282,   117,   259,   118,
     260,   484,   485,   211,   316,   487,   569,   488,   570,   489,
     571,   212,   317,   491,   492,   493,   119,   269,   509,   510,
     511,   512,   120,   271,   516,   517,   518,   121,   270,   122,
     273,   522,   523,   524,   594,    55,    67,   242,   243,   244,
     329,   245,   330,   123,   274,   526,   527,   124,   266,   496,
     497,   498,   578,    43,    61,   152,   153,   154,   287,   155,
     288,   156,   289,   157,   293,   158,   292,   159,   160,   125,
     267,   500,   501,   502,   581,    51,    65,   213,   214,   215,
     216,   217,   218,   219,   220,   320,   221,   319,   222,   223,
     321,   224,   126,   268,   504,   505,   506,   584,    53,    66,
     231,   232,   233,   234,   235,   325,   236,   237,   238,   162,
     285,   551,   552,   553,   612,    45,    62,   169,   170,   171,
     298,   163,   286,   555,   556,   557,   615,    47,    63,   179,
     180,   181,   301,   182,   183,   303,   184,   185,   164,   294,
     559,   560,   561,   618,    49,    64,   194,   195,   196,   197,
     309,   198,   310,   199,   311,   200,   312,   201,   313,   202,
     308,   165,   295,   563,   621,   127,   272,   520,   284,   369,
     370,   371,   372,   373,   441,   128,   275,   535,   536,   537,
     538,   600,   539,   540,   129,   130,   277,   437,   131,   278,
     543,   544,   545,   606,   546,   607,   132,   279,    83,   253,
      84,   254,    85,   252,   473,   474,   475,   565,   677,   678,
     679,   687,   688,   689,   690,   695,   691,   693,   705,   706,
     707,   711,   712,   714
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   228,    32,   147,   167,   177,   192,   210,   227,   241,
     534,   161,   168,   178,   193,   229,   519,   230,   486,   486,
     148,   515,   135,   149,   150,   151,    74,    25,   135,    26,
     533,    27,   507,   434,   435,   436,    24,    89,    90,    91,
      92,   239,   240,    71,    96,   203,   477,   478,   479,   480,
     481,   482,    36,   136,   256,   137,    96,   204,    96,   257,
     204,   138,   139,   140,   141,   142,   143,   203,   166,    38,
     280,   508,   144,   145,    78,   281,    40,   587,   144,   146,
     588,   246,   204,   365,   205,   206,   203,   207,   208,   209,
     480,   590,   239,   240,   591,   296,    86,    75,    87,    88,
     297,   299,    96,    76,    77,    96,   300,    89,    90,    91,
      92,    93,    94,    95,    96,    78,    78,   172,   173,   174,
     175,   176,    28,    29,    30,    31,   440,    78,   186,    78,
      78,    42,   187,   188,   189,   190,   191,    97,    98,    99,
     100,   204,   528,   529,   530,   531,   204,   225,   205,   206,
     226,   101,    78,   133,   102,   103,   456,   457,   458,   306,
     104,   105,   106,   331,   307,   107,   507,   514,   332,   280,
     566,    78,   486,    78,   564,   567,    78,   592,   641,   575,
     593,   534,   515,   575,   576,    78,   598,   604,   577,    44,
     608,   599,   605,    46,   682,   609,   683,   684,    79,   250,
     296,   533,   331,   299,   610,   665,   247,   668,   672,   306,
     696,    78,   715,   249,   673,   697,    78,   716,   680,   367,
     708,   681,   248,   709,   541,   542,   366,    48,    50,    52,
      54,   250,   283,   255,   368,   261,   333,   334,   147,   262,
     263,   167,   264,   265,   276,   290,   161,   291,   177,   168,
     302,   304,   305,   314,   315,   148,   178,   192,   149,   150,
     151,   318,   322,   228,   323,   193,   210,   324,   327,   326,
     227,   328,   335,   336,   337,   338,   339,   229,   341,   230,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,   342,   343,   344,   345,   346,   347,   349,   350,   348,
     351,   352,   353,   354,   355,   356,   357,   358,   360,   359,
     361,   362,   364,   374,   375,   376,   377,   378,   381,   380,
     379,   382,   383,   384,   386,   388,   389,   418,   419,   390,
     394,   391,   395,   392,   396,   397,   398,   399,   401,   402,
     404,   405,   406,   403,   409,   412,   413,   407,   415,   472,
     416,   629,   410,   417,   420,   421,   490,   490,   422,   423,
     424,   425,   426,   483,   483,   427,   429,   430,   431,   628,
     547,   432,   433,   438,   439,   532,   442,   443,   367,   446,
     444,   445,   447,   448,   449,   366,   450,   451,   452,   453,
     454,   455,   459,   368,   495,   460,   499,   503,   521,   548,
     550,   554,   469,   558,   470,   461,   568,   572,   573,   574,
     562,   580,   579,   582,   583,   462,   463,   586,   585,   595,
     596,   613,   464,   465,   466,   597,   601,   467,   602,   468,
     603,   614,   617,   616,   620,   589,   619,   623,   625,   525,
     622,   626,   627,   666,   646,   639,   651,   652,   660,   611,
     661,   702,   662,   630,   644,   667,   674,   676,   694,   647,
     648,   698,   700,   704,   717,   471,   340,   476,   710,   363,
     649,   663,   664,   669,   631,   494,   638,   670,   671,   675,
     640,   699,   643,   703,   414,   719,   642,   633,   632,   645,
     634,   635,   408,   411,   655,   636,   654,   385,   637,   657,
     656,   387,   549,   659,   650,   658,   653,   624,   692,   701,
     490,   713,   718,     0,     0,     0,     0,   483,   393,   228,
     147,     0,     0,   210,     0,     0,   227,     0,   161,   400,
       0,     0,     0,   229,     0,   230,   241,   148,     0,     0,
     149,   150,   151,     0,     0,     0,   532,     0,     0,     0,
       0,     0,     0,     0,   167,     0,     0,   177,     0,     0,
     192,     0,   168,     0,     0,   178,     0,     0,   193,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   686,     0,     0,     0,     0,     0,
       0,   685,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   686,     0,     0,     0,     0,     0,     0,   685
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,    13,    61,    62,    63,    64,    65,    66,    67,
     433,    61,    62,    63,    64,    66,   430,    66,   421,   422,
      61,   429,     7,    61,    61,    61,    10,     5,     7,     7,
     433,     9,    61,   100,   101,   102,     0,    22,    23,    24,
      25,    67,    68,   100,    29,    15,    16,    17,    18,    19,
      20,    21,     7,    38,     3,    40,    29,    30,    29,     8,
      30,    46,    47,    48,    49,    50,    51,    15,    39,     7,
       3,   100,    57,    58,   100,     8,     7,     3,    57,    64,
       6,     6,    30,    56,    32,    33,    15,    35,    36,    37,
      19,     3,    67,    68,     6,     3,    11,    81,    13,    14,
       8,     3,    29,    87,    88,    29,     8,    22,    23,    24,
      25,    26,    27,    28,    29,   100,   100,    41,    42,    43,
      44,    45,   100,   101,   102,   103,   364,   100,    55,   100,
     100,     7,    59,    60,    61,    62,    63,    52,    53,    54,
      55,    30,    71,    72,    73,    74,    30,    31,    32,    33,
      34,    66,   100,    12,    69,    70,   394,   395,   396,     3,
      75,    76,    77,     3,     8,    80,    61,    62,     8,     3,
       3,   100,   575,   100,     8,     8,   100,     3,   592,     3,
       6,   604,   590,     3,     8,   100,     3,     3,     8,     7,
       3,     8,     8,     7,    83,     8,    85,    86,   256,     3,
       3,   604,     3,     3,     8,     8,     3,     8,     8,     3,
       3,   100,     3,     8,     8,     8,   100,     8,     3,   284,
       3,     6,     4,     6,    78,    79,   284,     7,     7,     7,
       7,     3,     8,     4,   284,     4,   247,   248,   296,     4,
       4,   299,     4,     4,     4,     4,   296,     4,   306,   299,
       4,     4,     4,     8,     3,   296,   306,   315,   296,   296,
     296,     4,     4,   328,     8,   315,   324,     3,     8,     4,
     328,     3,   100,     4,     4,     4,     4,   328,     4,   328,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,     4,     4,   101,   101,   101,   101,     4,     4,   101,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   101,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   103,
     101,     4,     4,     4,     4,     4,   101,   338,   339,     4,
       4,   101,     4,   101,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   101,     4,     4,     4,   103,     4,    82,
       7,   101,   103,     7,     7,     7,   421,   422,     7,     5,
       5,     5,     5,   421,   422,     5,     5,     5,     5,   103,
     439,     7,     7,     7,     7,   433,     8,     3,   443,   100,
       5,     5,   100,   100,   100,   443,   100,     5,     7,   100,
     100,   100,   100,   443,     7,   100,     7,     7,     7,     4,
       7,     7,   413,     7,   415,   100,     8,     4,     4,     4,
      65,     3,     6,     6,     3,   100,   100,     3,     6,     6,
       3,     6,   100,   100,   100,     4,     4,   100,     4,   100,
       4,     3,     3,     6,     3,   513,     6,     4,     4,   100,
       8,     4,     4,     8,     4,     6,     4,     4,     4,   100,
       5,     5,   100,   103,   101,     8,     8,     7,     4,   101,
     101,     4,     4,     7,     4,   416,   256,   420,    84,   280,
     101,   100,   100,   100,   575,   422,   587,   100,   100,   100,
     590,   101,   596,   100,   331,   100,   594,   580,   578,   598,
     581,   583,   324,   328,   614,   584,   612,   296,   586,   617,
     615,   299,   443,   620,   604,   618,   608,   566,   680,   696,
     575,   708,   715,    -1,    -1,    -1,    -1,   575,   306,   584,
     578,    -1,    -1,   581,    -1,    -1,   584,    -1,   578,   315,
      -1,    -1,    -1,   584,    -1,   584,   594,   578,    -1,    -1,
     578,   578,   578,    -1,    -1,    -1,   604,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   612,    -1,    -1,   615,    -1,    -1,
     618,    -1,   612,    -1,    -1,   615,    -1,    -1,   618,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   679,    -1,    -1,    -1,    -1,    -1,
      -1,   679,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   696,    -1,    -1,    -1,    -1,    -1,    -1,   696
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     0,     5,     7,     9,   100,   101,
     102,   103,   117,   118,   119,   123,     7,   130,     7,   136,
       7,   147,     7,   207,     7,   269,     7,   281,     7,   298,
       7,   229,     7,   252,     7,   189,   124,   120,   131,   137,
     148,   208,   270,   282,   299,   230,   253,   190,   117,   127,
     128,   100,   121,   122,    10,    81,    87,    88,   100,   129,
     132,   133,   134,   352,   354,   356,    11,    13,    14,    22,
      23,    24,    25,    26,    27,    28,    29,    52,    53,    54,
      55,    66,    69,    70,    75,    76,    77,    80,   129,   138,
     139,   140,   141,   142,   143,   144,   145,   151,   153,   170,
     176,   181,   183,   197,   201,   223,   246,   319,   329,   338,
     339,   342,   350,    12,   149,     7,    38,    40,    46,    47,
      48,    49,    50,    51,    57,    58,    64,   129,   140,   141,
     142,   143,   209,   210,   211,   213,   215,   217,   219,   221,
     222,   246,   263,   275,   292,   315,    39,   129,   246,   271,
     272,   273,    41,    42,    43,    44,    45,   129,   246,   283,
     284,   285,   287,   288,   290,   291,    55,    59,    60,    61,
      62,    63,   129,   246,   300,   301,   302,   303,   305,   307,
     309,   311,   313,    15,    30,    32,    33,    35,    36,    37,
     129,   157,   165,   231,   232,   233,   234,   235,   236,   237,
     238,   240,   242,   243,   245,    31,    34,   129,   165,   235,
     240,   254,   255,   256,   257,   258,   260,   261,   262,    67,
      68,   129,   191,   192,   193,   195,     6,     3,     4,     8,
       3,   135,   357,   353,   355,     4,     3,     8,   146,   152,
     154,     4,     4,     4,     4,     4,   202,   224,   247,   171,
     182,   177,   320,   184,   198,   330,     4,   340,   343,   351,
       3,     8,   150,     8,   322,   264,   276,   212,   214,   216,
       4,     4,   220,   218,   293,   316,     3,     8,   274,     3,
       8,   286,     4,   289,     4,     4,     3,     8,   314,   304,
     306,   308,   310,   312,     8,     3,   158,   166,     4,   241,
     239,   244,     4,     8,     3,   259,     4,     8,     3,   194,
     196,     3,     8,   117,   117,   100,     4,     4,     4,     4,
     133,     4,     4,     4,   101,   101,   101,   101,   101,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   101,
       4,     4,     4,   139,     4,    56,   129,   165,   246,   323,
     324,   325,   326,   327,     4,     4,     4,     4,     4,   101,
     103,     4,     4,     4,     4,   210,     4,   272,     4,   101,
       4,   101,   101,   284,     4,     4,     4,     4,     4,     4,
     302,     4,     4,   101,     4,     4,     4,   103,   233,     4,
     103,   256,     4,     4,   192,     4,     7,     7,   117,   117,
       7,     7,     7,     5,     5,     5,     5,     5,   125,     5,
       5,     5,     7,     7,   100,   101,   102,   341,     7,     7,
     125,   328,     8,     3,     5,     5,   100,   100,   100,   100,
     100,     5,     7,   100,   100,   100,   125,   125,   125,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   117,
     117,   138,    82,   358,   359,   360,   149,    16,    17,    18,
      19,    20,    21,   129,   155,   156,   157,   159,   161,   163,
     165,   167,   168,   169,   155,     7,   203,   204,   205,     7,
     225,   226,   227,     7,   248,   249,   250,    61,   100,   172,
     173,   174,   175,   126,    62,   174,   178,   179,   180,   217,
     321,     7,   185,   186,   187,   100,   199,   200,    71,    72,
      73,    74,   129,   157,   167,   331,   332,   333,   334,   336,
     337,    78,    79,   344,   345,   346,   348,   122,     4,   325,
       7,   265,   266,   267,     7,   277,   278,   279,     7,   294,
     295,   296,    65,   317,     8,   361,     3,     8,     8,   160,
     162,   164,     4,     4,     4,     3,     8,     8,   206,     6,
       3,   228,     6,     3,   251,     6,     3,     3,     6,   127,
       3,     6,     3,     6,   188,     6,     3,     4,     3,     8,
     335,     4,     4,     4,     3,     8,   347,   349,     3,     8,
       8,   100,   268,     6,     3,   280,     6,     3,   297,     6,
       3,   318,     8,     4,   359,     4,     4,     4,   103,   101,
     103,   156,   209,   205,   231,   227,   254,   250,   173,     6,
     179,   217,   191,   187,   101,   200,     4,   101,   101,   101,
     332,     4,     4,   345,   271,   267,   283,   279,   300,   296,
       4,     5,   100,   100,   100,     8,     8,     8,     8,   100,
     100,   100,     8,     8,     8,   100,     7,   362,   363,   364,
       3,     6,    83,    85,    86,   129,   165,   365,   366,   367,
     368,   370,   363,   371,     4,   369,     3,     8,     4,   101,
       4,   366,     5,   100,     7,   372,   373,   374,     3,     6,
      84,   375,   376,   373,   377,     3,     8,     4,   376,   100
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   104,   106,   105,   107,   105,   108,   105,   109,   105,
     110,   105,   111,   105,   112,   105,   113,   105,   114,   105,
     115,   105,   116,   105,   117,   117,   117,   117,   117,   117,
     117,   118,   120,   119,   121,   121,   122,   122,   124,   123,
     126,   125,   127,   127,   128,   128,   129,   131,   130,   132,
     132,   133,   133,   133,   133,   133,   135,   134,   137,   136,
     138,   138,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   140,   141,   142,   143,   144,
     146,   145,   148,   147,   150,   149,   152,   151,   154,   153,
     155,   155,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   158,   157,   160,   159,   162,   161,   164,   163,   166,
     165,   167,   168,   169,   171,   170,   172,   172,   173,   173,
     174,   175,   177,   176,   178,   178,   179,   179,   180,   182,
     181,   184,   183,   185,   185,   186,   186,   188,   187,   190,
     189,   191,   191,   191,   192,   192,   194,   193,   196,   195,
     198,   197,   199,   199,   200,   202,   201,   203,   203,   204,
     204,   206,   205,   208,   207,   209,   209,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   212,   211,   214,   213,   216,   215,
     218,   217,   220,   219,   221,   222,   224,   223,   225,   225,
     226,   226,   228,   227,   230,   229,   231,   231,   232,   232,
     233,   233,   233,   233,   233,   233,   233,   233,   234,   235,
     236,   237,   239,   238,   241,   240,   242,   244,   243,   245,
     247,   246,   248,   248,   249,   249,   251,   250,   253,   252,
     254,   254,   255,   255,   256,   256,   256,   256,   256,   256,
     257,   259,   258,   260,   261,   262,   264,   263,   265,   265,
     266,   266,   268,   267,   270,   269,   271,   271,   272,   272,
     272,   274,   273,   276,   275,   277,   277,   278,   278,   280,
     279,   282,   281,   283,   283,   284,   284,   284,   284,   284,
     284,   284,   286,   285,   287,   289,   288,   290,   291,   293,
     292,   294,   294,   295,   295,   297,   296,   299,   298,   300,
     300,   301,   301,   302,   302,   302,   302,   302,   302,   302,
     302,   304,   303,   306,   305,   308,   307,   310,   309,   312,
     311,   314,   313,   316,   315,   318,   317,   320,   319,   321,
     321,   322,   217,   323,   323,   324,   324,   325,   325,   325,
     325,   326,   328,   327,   330,   329,   331,   331,   332,   332,
     332,   332,   332,   332,   332,   333,   335,   334,   336,   337,
     338,   340,   339,   341,   341,   341,   343,   342,   344,   344,
     345,   345,   347,   346,   349,   348,   351,   350,   353,   352,
     355,   354,   357,   356,   358,   358,   359,   361,   360,   362,
     362,   364,   363,   365,   365,   366,   366,   366,   366,   366,
     367,   369,   368,   371,   370,   372,   372,   374,   373,   375,
     375,   377,   376
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
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       0,     6,     0,     4,     0,     4,     0,     6,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     3,     0,     6,     0,     1,     1,
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
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"version\"",
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
  "time", "enterprise_id", "dhcp4o6_port", "version", "$@80",
  "version_value", "control_socket", "$@81", "control_socket_params",
  "control_socket_param", "socket_type", "$@82", "socket_name", "$@83",
  "dhcp_ddns", "$@84", "dhcp4_json_object", "$@85", "dhcpddns_json_object",
  "$@86", "logging_object", "$@87", "logging_params", "logging_param",
  "loggers", "$@88", "loggers_entries", "logger_entry", "$@89",
  "logger_params", "logger_param", "debuglevel", "severity", "$@90",
  "output_options_list", "$@91", "output_options_list_content",
  "output_entry", "$@92", "output_params", "output_param", "$@93", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   200,   200,   200,   201,   201,   202,   202,   203,   203,
     204,   204,   205,   205,   206,   206,   207,   207,   208,   208,
     209,   209,   210,   210,   218,   219,   220,   221,   222,   223,
     224,   227,   232,   232,   244,   245,   248,   252,   259,   259,
     267,   267,   274,   275,   278,   282,   293,   303,   303,   315,
     316,   320,   321,   322,   323,   324,   327,   327,   344,   344,
     352,   353,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   383,   388,   393,   398,   403,
     408,   408,   418,   418,   426,   426,   436,   436,   446,   446,
     456,   457,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   471,   471,   479,   479,   487,   487,   495,   495,   503,
     503,   511,   516,   521,   526,   526,   536,   537,   540,   541,
     544,   549,   554,   554,   564,   565,   568,   569,   572,   577,
     577,   587,   587,   597,   598,   601,   602,   605,   605,   613,
     613,   621,   622,   623,   626,   627,   630,   630,   638,   638,
     646,   646,   656,   657,   663,   671,   671,   684,   685,   688,
     689,   696,   696,   719,   719,   728,   729,   733,   734,   735,
     736,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,   752,   752,   760,   760,   768,   768,
     776,   776,   784,   784,   792,   797,   806,   806,   818,   819,
     822,   823,   828,   828,   839,   839,   849,   850,   853,   854,
     857,   858,   859,   860,   861,   862,   863,   864,   867,   869,
     874,   876,   878,   878,   886,   886,   894,   896,   896,   904,
     913,   913,   925,   926,   931,   932,   937,   937,   948,   948,
     959,   960,   965,   966,   971,   972,   973,   974,   975,   976,
     979,   981,   981,   989,   991,   993,  1001,  1001,  1013,  1014,
    1017,  1018,  1021,  1021,  1029,  1029,  1037,  1038,  1041,  1042,
    1043,  1046,  1046,  1057,  1057,  1069,  1070,  1073,  1074,  1077,
    1077,  1085,  1085,  1093,  1094,  1097,  1098,  1099,  1100,  1101,
    1102,  1103,  1106,  1106,  1114,  1119,  1119,  1127,  1132,  1140,
    1140,  1150,  1151,  1154,  1155,  1158,  1158,  1166,  1166,  1174,
    1175,  1178,  1179,  1183,  1184,  1185,  1186,  1187,  1188,  1189,
    1190,  1193,  1193,  1203,  1203,  1213,  1213,  1221,  1221,  1229,
    1229,  1237,  1237,  1250,  1250,  1260,  1260,  1271,  1271,  1281,
    1282,  1285,  1285,  1293,  1294,  1297,  1298,  1301,  1302,  1303,
    1304,  1307,  1309,  1309,  1320,  1320,  1330,  1331,  1334,  1335,
    1336,  1337,  1338,  1339,  1340,  1343,  1348,  1348,  1356,  1361,
    1368,  1374,  1374,  1382,  1383,  1384,  1389,  1389,  1399,  1400,
    1403,  1404,  1407,  1407,  1415,  1415,  1425,  1425,  1437,  1437,
    1444,  1444,  1456,  1456,  1469,  1470,  1474,  1478,  1478,  1490,
    1491,  1495,  1495,  1503,  1504,  1507,  1508,  1509,  1510,  1511,
    1514,  1518,  1518,  1526,  1526,  1536,  1537,  1540,  1540,  1548,
    1549,  1552,  1552
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
#line 3560 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1560 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
