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

  case 155:
#line 628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1584 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1044 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 1940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1125 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 1958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1138 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1168 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1206 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2119 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1258 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2186 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2278 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1372 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("version", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 2319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 2325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1382 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2351 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2537 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2556 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -423;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     116,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,    44,    19,    39,    54,    63,    67,    81,    89,
      96,   117,   146,   167,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,    19,   -16,    17,    86,
     123,    18,     6,   150,    87,    57,   138,    76,  -423,   139,
     197,   225,   212,   227,  -423,  -423,  -423,  -423,   230,  -423,
      31,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,   237,
     242,   245,   253,   254,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,   255,  -423,  -423,  -423,  -423,    52,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,   252,  -423,  -423,  -423,  -423,  -423,
    -423,   257,   259,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,    75,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,    77,
    -423,  -423,  -423,   262,  -423,   263,   264,  -423,  -423,    83,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,   265,   268,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,   270,  -423,  -423,  -423,   271,
    -423,  -423,  -423,   269,   275,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,   276,  -423,  -423,  -423,
    -423,   273,   279,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,    99,  -423,  -423,  -423,  -423,    19,    19,  -423,   172,
     280,   281,   282,   283,  -423,    17,  -423,   284,   285,   286,
     178,   182,   190,   191,   192,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   203,   301,   302,   303,    86,
    -423,   304,  -423,     1,   305,   306,   307,   308,   309,   215,
     211,   311,   313,   314,   315,    18,  -423,   316,     6,  -423,
     317,   221,   319,   228,   229,   150,  -423,   320,   321,   324,
     327,   328,   329,  -423,    87,   330,   331,   235,   333,   334,
     335,   238,  -423,    57,   336,   239,  -423,   138,   339,   340,
      76,  -423,  -423,  -423,   341,   342,   343,    19,    19,  -423,
     344,   345,   346,  -423,  -423,  -423,  -423,  -423,   349,   352,
     353,   354,   355,   356,   359,   360,   361,   362,  -423,   -64,
     363,   364,  -423,   355,  -423,  -423,  -423,  -423,   338,   369,
    -423,  -423,  -423,   368,   370,   247,   248,   266,  -423,  -423,
     267,   278,   371,   372,  -423,   287,  -423,   288,  -423,   289,
    -423,  -423,  -423,   355,   355,   355,   300,   310,   312,  -423,
     318,   322,  -423,   323,   325,   326,  -423,  -423,   332,  -423,
    -423,   337,    19,  -423,    19,    86,   347,  -423,  -423,   123,
      33,    33,   373,   374,   375,   -29,  -423,  -423,   128,    22,
     376,   348,    58,  -423,  -423,  -423,  -423,   165,   -16,  -423,
     381,  -423,     1,   379,   383,  -423,  -423,  -423,  -423,  -423,
     384,   350,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
     120,  -423,   151,  -423,  -423,   385,  -423,  -423,  -423,   390,
     391,   392,  -423,   157,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,   174,  -423,   393,   394,  -423,  -423,   396,
     395,  -423,  -423,   398,   402,  -423,  -423,  -423,    56,  -423,
    -423,  -423,    19,  -423,  -423,   161,  -423,  -423,  -423,   170,
    -423,   400,   404,  -423,   405,   177,  -423,  -423,   407,   409,
     410,  -423,  -423,  -423,   180,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,   193,  -423,  -423,  -423,   195,   351,  -423,  -423,
     411,   413,  -423,  -423,   414,   416,  -423,  -423,   415,   421,
    -423,  -423,   419,  -423,   424,   347,  -423,  -423,   426,   427,
     429,   357,   358,   365,    33,  -423,  -423,    18,  -423,   373,
      57,  -423,   374,   138,  -423,   375,   -29,  -423,   428,   128,
    -423,    22,  -423,    76,  -423,   376,   366,   348,  -423,   431,
     377,   378,   380,    58,  -423,   432,   434,   165,  -423,  -423,
    -423,     6,  -423,   379,   150,  -423,   383,    87,  -423,   384,
     435,  -423,   403,  -423,   382,   386,   387,  -423,  -423,  -423,
    -423,   213,  -423,   433,  -423,   436,  -423,  -423,  -423,  -423,
    -423,   214,  -423,  -423,  -423,   388,  -423,  -423,  -423,  -423,
     389,   397,  -423,   216,  -423,   220,  -423,   437,  -423,   399,
     439,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,   196,  -423,    51,   439,
    -423,  -423,   438,  -423,  -423,  -423,   223,  -423,  -423,  -423,
    -423,  -423,   443,   401,   445,    51,  -423,   447,  -423,   406,
    -423,   446,  -423,  -423,   236,  -423,   408,   446,  -423,  -423,
     224,  -423,  -423,   450,   408,  -423,   412,  -423,  -423
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      92,     9,   172,    11,   273,    13,   290,    15,   316,    17,
     213,    19,   247,    21,   149,    23,    42,    34,     0,     0,
       0,     0,     0,     0,   318,   215,   249,     0,    44,     0,
      43,     0,     0,    35,    56,   401,   397,   399,     0,    55,
       0,    49,    51,    53,    54,    52,    90,    96,    98,     0,
       0,     0,     0,     0,   164,   205,   239,   124,   139,   132,
     346,   141,   159,   363,     0,   380,   385,   395,    84,     0,
      60,    62,    63,    64,    65,    66,    68,    69,    70,    71,
      73,    72,    77,    78,    67,    75,    76,    74,    79,    80,
      81,    82,    83,    94,     0,   350,   265,   282,   193,   195,
     197,     0,     0,   201,   199,   308,   342,   192,   176,   177,
     178,   179,     0,   174,   183,   184,   185,   188,   190,   186,
     187,   180,   181,   182,   189,   191,   280,   279,   278,     0,
     275,   277,   301,     0,   304,     0,     0,   300,   297,     0,
     292,   294,   295,   298,   299,   296,   340,   330,   332,   334,
     336,   338,   329,   328,     0,   319,   320,   324,   325,   322,
     326,   327,   323,   111,   119,     0,   233,   231,   236,     0,
     226,   230,   227,     0,   216,   217,   219,   229,   220,   221,
     222,   235,   223,   224,   225,   260,     0,   258,   259,   262,
     263,     0,   250,   251,   253,   254,   255,   256,   257,   155,
     157,     0,   151,   153,   154,    39,     0,     0,    33,     0,
       0,     0,     0,     0,    46,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      59,     0,    93,   352,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,     0,     0,   274,
       0,     0,     0,     0,     0,     0,   291,     0,     0,     0,
       0,     0,     0,   317,     0,     0,     0,     0,     0,     0,
       0,     0,   214,     0,     0,     0,   248,     0,     0,     0,
       0,   150,    45,    36,     0,     0,     0,     0,     0,    50,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   379,     0,
       0,     0,    61,     0,   361,   359,   360,   358,     0,   353,
     354,   356,   357,     0,     0,     0,     0,     0,   203,   204,
       0,     0,     0,     0,   175,     0,   276,     0,   303,     0,
     306,   307,   293,     0,     0,     0,     0,     0,     0,   321,
       0,     0,   228,     0,     0,     0,   238,   218,     0,   264,
     252,     0,     0,   152,     0,     0,     0,   398,   400,     0,
       0,     0,   166,   207,   241,     0,    40,   140,     0,     0,
     143,     0,     0,   384,   382,   383,   381,     0,     0,    95,
       0,   351,     0,   267,   284,   194,   196,   198,   202,   200,
     310,     0,   281,   302,   305,   341,   331,   333,   335,   337,
     339,   112,   120,   234,   232,   237,   261,   156,   158,    37,
       0,   406,     0,   403,   405,     0,   113,   115,   117,     0,
       0,     0,   110,     0,   100,   102,   103,   104,   105,   106,
     107,   108,   109,     0,   170,     0,   167,   168,   211,     0,
     208,   209,   245,     0,   242,   243,   130,   131,     0,   126,
     128,   129,    42,   138,   136,     0,   134,   137,   348,     0,
     147,     0,   144,   145,     0,     0,   161,   375,     0,     0,
       0,   373,   367,   372,     0,   365,   370,   368,   369,   371,
     391,   393,     0,   387,   389,   390,     0,     0,   355,   271,
       0,   268,   269,   288,     0,   285,   286,   314,     0,   311,
     312,   344,     0,    57,     0,     0,   402,    91,     0,     0,
       0,     0,     0,     0,     0,    97,    99,     0,   165,     0,
     215,   206,     0,   249,   240,     0,     0,   125,     0,     0,
     133,     0,   347,     0,   142,     0,     0,     0,   160,     0,
       0,     0,     0,     0,   364,     0,     0,     0,   386,   396,
     362,     0,   266,     0,     0,   283,     0,   318,   309,     0,
       0,   343,     0,   404,     0,     0,     0,   121,   122,   123,
     101,     0,   169,     0,   210,     0,   244,   127,    41,   135,
     349,     0,   146,   163,   162,     0,   374,   377,   378,   366,
       0,     0,   388,     0,   270,     0,   287,     0,   313,     0,
       0,   114,   116,   118,   171,   212,   246,   148,   376,   392,
     394,   272,   289,   315,   345,   410,     0,   408,     0,     0,
     407,   422,     0,   420,   418,   414,     0,   412,   416,   417,
     415,   409,     0,     0,     0,     0,   411,     0,   419,     0,
     413,     0,   421,   426,     0,   424,     0,     0,   423,   430,
       0,   428,   425,     0,     0,   427,     0,   429,   431
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,   -11,  -423,  -423,  -423,  -423,     2,  -423,
    -423,  -268,  -423,   -69,  -423,   -58,  -423,  -423,  -423,   200,
    -423,  -423,  -423,  -423,    35,   179,   -44,   -43,   -42,   -41,
    -423,  -423,  -423,  -423,  -423,    37,  -423,  -423,  -423,  -423,
    -423,    36,  -113,  -399,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,   -65,  -423,  -422,  -423,  -423,  -423,  -423,  -423,  -124,
    -405,  -423,  -423,  -423,  -423,  -126,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -131,  -423,  -423,  -423,  -128,   136,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -127,  -423,  -423,  -423,
    -423,  -110,  -423,  -423,  -423,  -106,   181,  -423,  -423,  -423,
    -423,  -423,  -423,  -413,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -109,  -423,  -423,  -423,  -108,  -423,   152,
    -423,   -57,  -423,  -423,  -423,  -423,   -51,  -423,  -423,  -423,
    -423,  -423,   -50,  -423,  -423,  -423,  -111,  -423,  -423,  -423,
    -103,  -423,   156,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -136,  -423,  -423,  -423,  -121,   186,  -423,
    -423,  -423,  -423,  -423,  -423,  -125,  -423,  -423,  -423,  -129,
     188,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -123,  -423,  -423,  -423,  -122,  -423,   184,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,    59,  -423,  -423,  -423,  -423,  -423,  -423,  -100,  -423,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -107,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,  -423,   -71,  -423,  -423,  -423,  -175,
    -423,  -423,  -190,  -423,  -423,  -423,  -423,  -423,  -423,  -200,
    -423,  -423,  -206,  -423
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   427,   512,    69,    70,   108,    37,    58,    80,    81,
      82,   250,    39,    59,   109,   110,   111,   112,   113,   114,
     115,   116,   257,    41,    60,   134,   281,   117,   258,   118,
     259,   483,   484,   211,   315,   486,   568,   487,   569,   488,
     570,   212,   316,   490,   491,   492,   119,   268,   508,   509,
     510,   511,   120,   270,   515,   516,   517,   121,   269,   122,
     272,   521,   522,   523,   593,    55,    67,   241,   242,   243,
     328,   244,   329,   123,   273,   525,   526,   124,   265,   495,
     496,   497,   577,    43,    61,   152,   153,   154,   286,   155,
     287,   156,   288,   157,   292,   158,   291,   159,   160,   125,
     266,   499,   500,   501,   580,    51,    65,   213,   214,   215,
     216,   217,   218,   219,   220,   319,   221,   318,   222,   223,
     320,   224,   126,   267,   503,   504,   505,   583,    53,    66,
     231,   232,   233,   234,   235,   324,   236,   237,   238,   162,
     284,   550,   551,   552,   611,    45,    62,   169,   170,   171,
     297,   163,   285,   554,   555,   556,   614,    47,    63,   179,
     180,   181,   300,   182,   183,   302,   184,   185,   164,   293,
     558,   559,   560,   617,    49,    64,   194,   195,   196,   197,
     308,   198,   309,   199,   310,   200,   311,   201,   312,   202,
     307,   165,   294,   562,   620,   127,   271,   519,   283,   368,
     369,   370,   371,   372,   440,   128,   274,   534,   535,   536,
     537,   599,   538,   539,   129,   130,   276,   436,   131,   277,
     542,   543,   544,   605,   545,   606,   132,   278,    83,   252,
      84,   253,    85,   251,   472,   473,   474,   564,   676,   677,
     678,   686,   687,   688,   689,   694,   690,   692,   704,   705,
     706,   710,   711,   713
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   228,    32,   147,   167,   177,   192,   210,   227,   229,
     533,   161,   168,   178,   193,   230,   518,   148,   149,   150,
     151,   485,   485,   514,    25,   135,    26,    74,    27,   135,
      96,   204,   506,   532,   255,    96,   433,   434,   435,   256,
      89,    90,    91,    92,    24,   166,    36,    96,   203,   476,
     477,   478,   479,   480,   481,   279,   136,   364,   137,   586,
     280,    38,   587,   204,   138,   139,   140,   141,   142,   143,
      40,   507,   203,   203,    42,   144,   145,   479,   295,   144,
     298,   204,   146,   296,    71,   299,   305,   204,    44,   205,
     206,   306,   207,   208,   209,   439,    46,    86,    75,    87,
      88,    78,   330,    48,    76,    77,    78,   331,    89,    90,
      91,    92,    93,    94,    95,    96,    96,    78,    78,    28,
      29,    30,    31,   279,    50,   455,   456,   457,   563,   527,
     528,   529,   530,    78,   681,   133,   682,   683,    97,    98,
      99,   100,   186,   239,   240,   245,   187,   188,   189,   190,
     191,    78,   101,    52,   565,   102,   103,    78,    78,   566,
     574,   104,   105,   106,   589,   575,   107,   590,   204,   225,
     205,   206,   226,   591,    54,   485,   592,   574,   640,    96,
     597,   533,   576,   603,   514,   598,    78,    78,   604,   506,
     513,   172,   173,   174,   175,   176,   607,    79,   249,   679,
     246,   608,   680,   609,   532,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   295,   330,   366,   298,
     248,   664,   667,   305,   671,   365,   695,   714,   672,   247,
     249,   696,   715,   367,   254,   332,   333,   147,    78,   707,
     167,   260,   708,   540,   541,   161,   261,   177,   168,   262,
      78,   148,   149,   150,   151,   178,   192,   263,   264,   275,
     282,   289,   228,   290,   193,   210,   301,   303,   304,   227,
     229,   314,   334,   313,   317,   321,   230,   322,   323,   343,
     325,   326,   327,   344,   335,   336,   337,   338,   340,   341,
     342,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   363,   373,
     374,   375,   376,   377,   379,   380,   378,   381,   382,   383,
     385,   387,   388,   389,   393,   394,   417,   418,   395,   390,
     391,   396,   397,   398,   400,   401,   402,   403,   404,   405,
     408,   406,   409,   411,   412,   414,   441,   445,   446,   415,
     416,   419,   420,   421,   422,   489,   489,   423,   424,   425,
     426,   428,   482,   482,   429,   430,   447,   448,   431,   432,
     437,   438,   442,   443,   531,   444,   450,   366,   449,   451,
     494,   498,   502,   520,   365,   547,   549,   452,   453,   454,
     553,   557,   367,   567,   571,   572,   573,   579,   582,   578,
     458,   468,   581,   469,   584,   585,   594,   595,   660,   596,
     459,   600,   460,   601,   602,   561,   613,   612,   461,   616,
     615,   618,   462,   463,   619,   464,   465,   621,   622,   471,
     624,   625,   466,   626,   638,   645,   650,   467,   651,   659,
     546,   665,   693,   588,   666,   673,   675,   697,   524,   699,
     470,   610,   701,   703,   716,   339,   475,   493,   362,   628,
     627,   630,   637,   639,   642,   641,   413,   643,   629,   632,
     644,   631,   633,   634,   636,   407,   384,   654,   646,   647,
     635,   648,   661,   410,   386,   655,   662,   663,   668,   669,
     653,   656,   709,   392,   623,   657,   658,   670,   399,   674,
     652,   548,   698,   649,   691,   700,   702,   712,   717,   489,
       0,     0,   718,     0,     0,     0,   482,     0,   228,   147,
       0,     0,   210,     0,     0,   227,   229,   161,     0,     0,
       0,     0,   230,   148,   149,   150,   151,     0,     0,     0,
       0,     0,     0,     0,     0,   531,     0,     0,     0,     0,
       0,     0,     0,   167,     0,     0,   177,     0,     0,   192,
       0,   168,     0,     0,   178,     0,     0,   193,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   685,     0,     0,     0,     0,     0,     0,
     684,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     685,     0,     0,     0,     0,     0,     0,   684
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,    13,    61,    62,    63,    64,    65,    66,    66,
     432,    61,    62,    63,    64,    66,   429,    61,    61,    61,
      61,   420,   421,   428,     5,     7,     7,    10,     9,     7,
      29,    30,    61,   432,     3,    29,   100,   101,   102,     8,
      22,    23,    24,    25,     0,    39,     7,    29,    15,    16,
      17,    18,    19,    20,    21,     3,    38,    56,    40,     3,
       8,     7,     6,    30,    46,    47,    48,    49,    50,    51,
       7,   100,    15,    15,     7,    57,    58,    19,     3,    57,
       3,    30,    64,     8,   100,     8,     3,    30,     7,    32,
      33,     8,    35,    36,    37,   363,     7,    11,    81,    13,
      14,   100,     3,     7,    87,    88,   100,     8,    22,    23,
      24,    25,    26,    27,    28,    29,    29,   100,   100,   100,
     101,   102,   103,     3,     7,   393,   394,   395,     8,    71,
      72,    73,    74,   100,    83,    12,    85,    86,    52,    53,
      54,    55,    55,    67,    68,     6,    59,    60,    61,    62,
      63,   100,    66,     7,     3,    69,    70,   100,   100,     8,
       3,    75,    76,    77,     3,     8,    80,     6,    30,    31,
      32,    33,    34,     3,     7,   574,     6,     3,   591,    29,
       3,   603,     8,     3,   589,     8,   100,   100,     8,    61,
      62,    41,    42,    43,    44,    45,     3,   255,     3,     3,
       3,     8,     6,     8,   603,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,     3,     3,   283,     3,
       8,     8,     8,     3,     8,   283,     3,     3,     8,     4,
       3,     8,     8,   283,     4,   246,   247,   295,   100,     3,
     298,     4,     6,    78,    79,   295,     4,   305,   298,     4,
     100,   295,   295,   295,   295,   305,   314,     4,     4,     4,
       8,     4,   327,     4,   314,   323,     4,     4,     4,   327,
     327,     3,   100,     8,     4,     4,   327,     8,     3,   101,
       4,     8,     3,   101,     4,     4,     4,     4,     4,     4,
       4,   101,   101,   101,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   101,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   103,     4,   101,     4,     4,     4,
       4,     4,   101,     4,     4,     4,   337,   338,     4,   101,
     101,     4,     4,     4,     4,     4,   101,     4,     4,     4,
       4,   103,   103,     4,     4,     4,     8,   100,   100,     7,
       7,     7,     7,     7,     5,   420,   421,     5,     5,     5,
       5,     5,   420,   421,     5,     5,   100,   100,     7,     7,
       7,     7,     3,     5,   432,     5,     5,   442,   100,     7,
       7,     7,     7,     7,   442,     4,     7,   100,   100,   100,
       7,     7,   442,     8,     4,     4,     4,     3,     3,     6,
     100,   412,     6,   414,     6,     3,     6,     3,     5,     4,
     100,     4,   100,     4,     4,    65,     3,     6,   100,     3,
       6,     6,   100,   100,     3,   100,   100,     8,     4,    82,
       4,     4,   100,     4,     6,     4,     4,   100,     4,     4,
     438,     8,     4,   512,     8,     8,     7,     4,   100,     4,
     415,   100,     5,     7,     4,   255,   419,   421,   279,   101,
     103,   574,   586,   589,   595,   593,   330,   101,   103,   579,
     597,   577,   580,   582,   585,   323,   295,   613,   101,   101,
     583,   101,   100,   327,   298,   614,   100,   100,   100,   100,
     611,   616,    84,   305,   565,   617,   619,   100,   314,   100,
     607,   442,   101,   603,   679,   695,   100,   707,   714,   574,
      -1,    -1,   100,    -1,    -1,    -1,   574,    -1,   583,   577,
      -1,    -1,   580,    -1,    -1,   583,   583,   577,    -1,    -1,
      -1,    -1,   583,   577,   577,   577,   577,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   603,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   611,    -1,    -1,   614,    -1,    -1,   617,
      -1,   611,    -1,    -1,   614,    -1,    -1,   617,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   678,    -1,    -1,    -1,    -1,    -1,    -1,
     678,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     695,    -1,    -1,    -1,    -1,    -1,    -1,   695
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
      68,   191,   192,   193,   195,     6,     3,     4,     8,     3,
     135,   357,   353,   355,     4,     3,     8,   146,   152,   154,
       4,     4,     4,     4,     4,   202,   224,   247,   171,   182,
     177,   320,   184,   198,   330,     4,   340,   343,   351,     3,
       8,   150,     8,   322,   264,   276,   212,   214,   216,     4,
       4,   220,   218,   293,   316,     3,     8,   274,     3,     8,
     286,     4,   289,     4,     4,     3,     8,   314,   304,   306,
     308,   310,   312,     8,     3,   158,   166,     4,   241,   239,
     244,     4,     8,     3,   259,     4,     8,     3,   194,   196,
       3,     8,   117,   117,   100,     4,     4,     4,     4,   133,
       4,     4,     4,   101,   101,   101,   101,   101,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   101,     4,
       4,     4,   139,     4,    56,   129,   165,   246,   323,   324,
     325,   326,   327,     4,     4,     4,     4,     4,   101,   103,
       4,     4,     4,     4,   210,     4,   272,     4,   101,     4,
     101,   101,   284,     4,     4,     4,     4,     4,     4,   302,
       4,     4,   101,     4,     4,     4,   103,   233,     4,   103,
     256,     4,     4,   192,     4,     7,     7,   117,   117,     7,
       7,     7,     5,     5,     5,     5,     5,   125,     5,     5,
       5,     7,     7,   100,   101,   102,   341,     7,     7,   125,
     328,     8,     3,     5,     5,   100,   100,   100,   100,   100,
       5,     7,   100,   100,   100,   125,   125,   125,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   117,   117,
     138,    82,   358,   359,   360,   149,    16,    17,    18,    19,
      20,    21,   129,   155,   156,   157,   159,   161,   163,   165,
     167,   168,   169,   155,     7,   203,   204,   205,     7,   225,
     226,   227,     7,   248,   249,   250,    61,   100,   172,   173,
     174,   175,   126,    62,   174,   178,   179,   180,   217,   321,
       7,   185,   186,   187,   100,   199,   200,    71,    72,    73,
      74,   129,   157,   167,   331,   332,   333,   334,   336,   337,
      78,    79,   344,   345,   346,   348,   122,     4,   325,     7,
     265,   266,   267,     7,   277,   278,   279,     7,   294,   295,
     296,    65,   317,     8,   361,     3,     8,     8,   160,   162,
     164,     4,     4,     4,     3,     8,     8,   206,     6,     3,
     228,     6,     3,   251,     6,     3,     3,     6,   127,     3,
       6,     3,     6,   188,     6,     3,     4,     3,     8,   335,
       4,     4,     4,     3,     8,   347,   349,     3,     8,     8,
     100,   268,     6,     3,   280,     6,     3,   297,     6,     3,
     318,     8,     4,   359,     4,     4,     4,   103,   101,   103,
     156,   209,   205,   231,   227,   254,   250,   173,     6,   179,
     217,   191,   187,   101,   200,     4,   101,   101,   101,   332,
       4,     4,   345,   271,   267,   283,   279,   300,   296,     4,
       5,   100,   100,   100,     8,     8,     8,     8,   100,   100,
     100,     8,     8,     8,   100,     7,   362,   363,   364,     3,
       6,    83,    85,    86,   129,   165,   365,   366,   367,   368,
     370,   363,   371,     4,   369,     3,     8,     4,   101,     4,
     366,     5,   100,     7,   372,   373,   374,     3,     6,    84,
     375,   376,   373,   377,     3,     8,     4,   376,   100
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
     189,   191,   191,   192,   192,   194,   193,   196,   195,   198,
     197,   199,   199,   200,   202,   201,   203,   203,   204,   204,
     206,   205,   208,   207,   209,   209,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   212,   211,   214,   213,   216,   215,   218,
     217,   220,   219,   221,   222,   224,   223,   225,   225,   226,
     226,   228,   227,   230,   229,   231,   231,   232,   232,   233,
     233,   233,   233,   233,   233,   233,   233,   234,   235,   236,
     237,   239,   238,   241,   240,   242,   244,   243,   245,   247,
     246,   248,   248,   249,   249,   251,   250,   253,   252,   254,
     254,   255,   255,   256,   256,   256,   256,   256,   256,   257,
     259,   258,   260,   261,   262,   264,   263,   265,   265,   266,
     266,   268,   267,   270,   269,   271,   271,   272,   272,   272,
     274,   273,   276,   275,   277,   277,   278,   278,   280,   279,
     282,   281,   283,   283,   284,   284,   284,   284,   284,   284,
     284,   286,   285,   287,   289,   288,   290,   291,   293,   292,
     294,   294,   295,   295,   297,   296,   299,   298,   300,   300,
     301,   301,   302,   302,   302,   302,   302,   302,   302,   302,
     304,   303,   306,   305,   308,   307,   310,   309,   312,   311,
     314,   313,   316,   315,   318,   317,   320,   319,   321,   321,
     322,   217,   323,   323,   324,   324,   325,   325,   325,   325,
     326,   328,   327,   330,   329,   331,   331,   332,   332,   332,
     332,   332,   332,   332,   333,   335,   334,   336,   337,   338,
     340,   339,   341,   341,   341,   343,   342,   344,   344,   345,
     345,   347,   346,   349,   348,   351,   350,   353,   352,   355,
     354,   357,   356,   358,   358,   359,   361,   360,   362,   362,
     364,   363,   365,   365,   366,   366,   366,   366,   366,   367,
     369,   368,   371,   370,   372,   372,   374,   373,   375,   375,
     377,   376
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
       4,     1,     3,     1,     1,     0,     4,     0,     4,     0,
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
       0,     4,     1,     1,     1,     0,     6,     1,     3,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       0,     4
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
     613,   621,   622,   625,   626,   628,   628,   636,   636,   644,
     644,   654,   655,   661,   669,   669,   682,   683,   686,   687,
     694,   694,   717,   717,   726,   727,   731,   732,   733,   734,
     735,   736,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   750,   750,   758,   758,   766,   766,   774,
     774,   782,   782,   790,   795,   804,   804,   816,   817,   820,
     821,   826,   826,   837,   837,   847,   848,   851,   852,   855,
     856,   857,   858,   859,   860,   861,   862,   865,   867,   872,
     874,   876,   876,   884,   884,   892,   894,   894,   902,   911,
     911,   923,   924,   929,   930,   935,   935,   946,   946,   957,
     958,   963,   964,   969,   970,   971,   972,   973,   974,   977,
     979,   979,   987,   989,   991,   999,   999,  1011,  1012,  1015,
    1016,  1019,  1019,  1027,  1027,  1035,  1036,  1039,  1040,  1041,
    1044,  1044,  1055,  1055,  1067,  1068,  1071,  1072,  1075,  1075,
    1083,  1083,  1091,  1092,  1095,  1096,  1097,  1098,  1099,  1100,
    1101,  1104,  1104,  1112,  1117,  1117,  1125,  1130,  1138,  1138,
    1148,  1149,  1152,  1153,  1156,  1156,  1164,  1164,  1172,  1173,
    1176,  1177,  1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,
    1191,  1191,  1201,  1201,  1211,  1211,  1219,  1219,  1227,  1227,
    1235,  1235,  1248,  1248,  1258,  1258,  1269,  1269,  1279,  1280,
    1283,  1283,  1291,  1292,  1295,  1296,  1299,  1300,  1301,  1302,
    1305,  1307,  1307,  1318,  1318,  1328,  1329,  1332,  1333,  1334,
    1335,  1336,  1337,  1338,  1341,  1346,  1346,  1354,  1359,  1366,
    1372,  1372,  1380,  1381,  1382,  1387,  1387,  1397,  1398,  1401,
    1402,  1405,  1405,  1413,  1413,  1423,  1423,  1435,  1435,  1442,
    1442,  1454,  1454,  1467,  1468,  1472,  1476,  1476,  1488,  1489,
    1493,  1493,  1501,  1502,  1505,  1506,  1507,  1508,  1509,  1512,
    1516,  1516,  1524,  1524,  1534,  1535,  1538,  1538,  1546,  1547,
    1550,  1550
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
#line 1558 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
