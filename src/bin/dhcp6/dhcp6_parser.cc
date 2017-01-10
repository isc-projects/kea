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
      case 123: // value
      case 165: // db_type
      case 344: // duid_type
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
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 123: // value
      case 165: // db_type
      case 344: // duid_type
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
            case 106: // "constant string"

#line 198 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 356 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 107: // "integer"

#line 198 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 363 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 108: // "floating point"

#line 198 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 370 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 109: // "boolean"

#line 198 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 377 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 123: // value

#line 198 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 384 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 165: // db_type

#line 198 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 391 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 344: // duid_type

#line 198 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 123: // value
      case 165: // db_type
      case 344: // duid_type
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
#line 207 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 208 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 209 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 210 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 211 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 212 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 213 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 214 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 215 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 216 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 217 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 751 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 285 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 289 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 854 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 355 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 927 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 485 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1186 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 547 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1302 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
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
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
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
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1562 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1572 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1581 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1590 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1601 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1628 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1681 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1727 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 940 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1774 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1003 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1005 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1810 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1867 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1103 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1136 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 1994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2060 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1192 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2079 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2088 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1225 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2182 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1347 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1372 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1382 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2396 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2562 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2580 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2591 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2618 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2636 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2640 "dhcp6_parser.cc" // lalr1.cc:859
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
     181,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,    27,    21,    29,    61,    63,    74,    84,    92,
     136,   138,   162,   219,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,    21,    -5,    11,    20,
     159,    12,   -11,    38,    83,    73,   117,   -14,  -427,   178,
     197,   223,   220,   226,  -427,  -427,  -427,  -427,   227,  -427,
      34,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   228,
     229,   231,   232,   234,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   235,  -427,  -427,  -427,   153,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   233,  -427,  -427,  -427,  -427,  -427,  -427,   236,
     239,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
     154,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,   156,  -427,  -427,
    -427,   242,  -427,   245,   246,  -427,  -427,   157,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   249,   255,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   256,  -427,  -427,  -427,   259,  -427,  -427,
     257,   261,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   263,  -427,  -427,  -427,  -427,   260,   266,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   160,
    -427,  -427,  -427,  -427,    21,    21,  -427,   165,   268,   270,
     283,   284,  -427,    11,  -427,   285,   286,   287,   163,   185,
     186,   187,   188,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   199,   303,   304,    20,  -427,   305,  -427,
      98,   306,   307,   308,   309,   310,   209,   210,   311,   313,
     314,   316,    12,  -427,   317,   -11,  -427,   318,   216,   320,
     218,   221,    38,  -427,   322,   323,   325,   326,   327,   328,
    -427,    83,   329,   330,   237,   331,   332,   335,   238,  -427,
      73,   336,   240,  -427,   117,   337,   338,   -28,  -427,  -427,
    -427,   339,   341,   343,    21,    21,  -427,   346,   347,   348,
    -427,  -427,  -427,  -427,  -427,   340,   351,   352,   355,   356,
     357,   358,   359,   360,   361,  -427,   364,   365,  -427,   356,
    -427,  -427,  -427,  -427,   366,   362,  -427,  -427,  -427,   368,
     370,   271,   272,   273,  -427,  -427,   274,   275,   377,   376,
    -427,   279,  -427,   280,  -427,   281,  -427,  -427,  -427,   356,
     356,   356,   282,   288,   289,  -427,   290,   291,  -427,   302,
     312,   315,  -427,  -427,   319,  -427,  -427,   321,    21,  -427,
      21,    20,   258,  -427,  -427,   159,   100,   100,   382,   383,
     384,   -10,  -427,  -427,   155,    28,   385,   324,    60,   140,
      -5,  -427,   389,  -427,    98,   391,   392,  -427,  -427,  -427,
    -427,  -427,   393,   333,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   164,  -427,   167,  -427,  -427,   395,  -427,  -427,
    -427,  -427,   397,   400,   401,   402,  -427,   170,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   174,  -427,
     403,   363,  -427,  -427,   404,   409,  -427,  -427,   408,   412,
    -427,  -427,  -427,    66,  -427,  -427,  -427,    21,  -427,  -427,
      94,  -427,  -427,  -427,   105,  -427,   410,   414,  -427,   415,
     177,  -427,  -427,  -427,   416,   418,   419,  -427,  -427,   184,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   190,  -427,
    -427,  -427,   191,   334,  -427,  -427,   420,   421,  -427,  -427,
     422,   426,  -427,  -427,   425,   429,  -427,  -427,   399,  -427,
     430,   258,  -427,  -427,   431,   432,   433,   434,   342,   345,
     344,   349,   100,  -427,  -427,    12,  -427,   382,    73,  -427,
     383,   117,  -427,   384,   -10,  -427,   427,   155,  -427,    28,
    -427,   -14,  -427,   385,   350,   324,  -427,   435,   437,   353,
     354,   367,    60,  -427,   438,   439,   140,  -427,  -427,  -427,
     -11,  -427,   391,    38,  -427,   392,    83,  -427,   393,   440,
    -427,   441,  -427,   119,   369,   371,   372,  -427,  -427,  -427,
    -427,  -427,   193,  -427,   442,  -427,   446,  -427,  -427,  -427,
    -427,  -427,   194,  -427,  -427,  -427,   142,   373,  -427,  -427,
    -427,  -427,   374,   375,  -427,   200,  -427,   204,  -427,   447,
    -427,   378,   451,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,   180,  -427,    99,   451,
    -427,  -427,   443,  -427,  -427,  -427,   206,  -427,  -427,  -427,
    -427,  -427,   444,   379,   445,    99,  -427,   454,  -427,   381,
    -427,   455,  -427,  -427,   207,  -427,   380,   455,  -427,  -427,
     208,  -427,  -427,   459,   380,  -427,   386,  -427,  -427
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      91,     9,   177,    11,   279,    13,   296,    15,   322,    17,
     218,    19,   253,    21,   153,    23,    42,    34,     0,     0,
       0,     0,     0,     0,   324,   220,   255,     0,    44,     0,
      43,     0,     0,    35,    56,   407,   403,   405,     0,    55,
       0,    49,    51,    53,    54,    52,    89,    95,    97,     0,
       0,     0,     0,     0,   169,   210,   245,   128,   143,   136,
     352,   145,   164,   369,     0,   391,   401,    83,     0,    60,
      62,    63,    64,    65,    66,    68,    69,    70,    71,    73,
      72,    77,    78,    67,    75,    76,    74,    79,    80,    81,
      82,    93,     0,   356,   271,   288,   198,   200,   202,     0,
       0,   206,   204,   314,   348,   197,   181,   182,   183,   184,
       0,   179,   188,   189,   190,   193,   195,   191,   192,   185,
     186,   187,   194,   196,   286,   285,   284,     0,   281,   283,
     307,     0,   310,     0,     0,   306,   303,     0,   298,   300,
     301,   304,   305,   302,   346,   336,   338,   340,   342,   344,
     335,   334,     0,   325,   326,   330,   331,   328,   332,   333,
     329,   235,   122,     0,   239,   237,   242,     0,   231,   232,
       0,   221,   222,   224,   234,   225,   226,   227,   241,   228,
     229,   230,   266,     0,   264,   265,   268,   269,     0,   256,
     257,   259,   260,   261,   262,   263,   160,   162,   157,     0,
     155,   158,   159,    39,     0,     0,    33,     0,     0,     0,
       0,     0,    46,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,     0,    92,
     358,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   178,     0,     0,   280,     0,     0,     0,
       0,     0,     0,   297,     0,     0,     0,     0,     0,     0,
     323,     0,     0,     0,     0,     0,     0,     0,     0,   219,
       0,     0,     0,   254,     0,     0,     0,     0,   154,    45,
      36,     0,     0,     0,     0,     0,    50,     0,     0,     0,
      84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   390,     0,     0,    61,     0,
     367,   365,   366,   364,     0,   359,   360,   362,   363,     0,
       0,     0,     0,     0,   208,   209,     0,     0,     0,     0,
     180,     0,   282,     0,   309,     0,   312,   313,   299,     0,
       0,     0,     0,     0,     0,   327,     0,     0,   233,     0,
       0,     0,   244,   223,     0,   270,   258,     0,     0,   156,
       0,     0,     0,   404,   406,     0,     0,     0,   171,   212,
     247,     0,    40,   144,     0,     0,   147,     0,     0,     0,
       0,    94,     0,   357,     0,   273,   290,   199,   201,   203,
     207,   205,   316,     0,   287,   308,   311,   347,   337,   339,
     341,   343,   345,   236,   123,   240,   238,   243,   267,   161,
     163,    37,     0,   412,     0,   409,   411,     0,   111,   116,
     118,   120,     0,     0,     0,     0,   110,     0,    99,   101,
     102,   103,   104,   105,   106,   107,   108,   109,     0,   175,
       0,   172,   173,   216,     0,   213,   214,   251,     0,   248,
     249,   134,   135,     0,   130,   132,   133,    42,   142,   140,
       0,   138,   141,   354,     0,   151,     0,   148,   149,     0,
       0,   166,   380,   386,     0,     0,     0,   379,   378,     0,
     371,   373,   376,   374,   375,   377,   397,   399,     0,   393,
     395,   396,     0,     0,   361,   277,     0,   274,   275,   294,
       0,   291,   292,   320,     0,   317,   318,   350,     0,    57,
       0,     0,   408,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,    98,     0,   170,     0,   220,   211,
       0,   255,   246,     0,     0,   129,     0,     0,   137,     0,
     353,     0,   146,     0,     0,     0,   165,     0,     0,     0,
       0,     0,     0,   370,     0,     0,     0,   392,   402,   368,
       0,   272,     0,     0,   289,     0,   324,   315,     0,     0,
     349,     0,   410,     0,     0,     0,     0,   124,   125,   126,
     127,   100,     0,   174,     0,   215,     0,   250,   131,    41,
     139,   355,     0,   150,   168,   167,     0,     0,   385,   388,
     389,   372,     0,     0,   394,     0,   276,     0,   293,     0,
     319,     0,     0,   113,   114,   115,   112,   117,   119,   121,
     176,   217,   252,   152,   382,   383,   384,   381,   387,   398,
     400,   278,   295,   321,   351,   416,     0,   414,     0,     0,
     413,   428,     0,   426,   424,   420,     0,   418,   422,   423,
     421,   415,     0,     0,     0,     0,   417,     0,   425,     0,
     419,     0,   427,   432,     0,   430,     0,     0,   429,   436,
       0,   434,   431,     0,     0,   433,     0,   435,   437
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,     3,  -427,  -427,  -427,  -427,    15,  -427,
    -427,  -330,  -427,   -43,  -427,   -58,  -427,  -427,  -427,   212,
    -427,  -427,  -427,  -427,    55,   192,   -41,   -38,   -37,   -36,
    -427,  -427,  -427,  -427,  -427,    52,  -427,  -427,  -427,  -427,
    -427,    54,  -103,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   -65,  -427,  -426,  -427,  -427,  -427,  -427,  -427,
    -427,  -112,  -406,  -427,  -427,  -427,  -427,  -114,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -117,  -427,  -427,  -427,  -109,
     158,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -107,  -427,
    -427,  -427,  -427,   -94,  -427,  -427,  -427,   -86,   198,  -427,
    -427,  -427,  -427,  -427,  -427,  -415,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,   -89,  -427,  -427,  -427,   -85,
    -427,   175,  -427,   -51,  -427,  -427,  -427,  -427,  -427,   -49,
    -427,  -427,  -427,  -427,  -427,   -50,  -427,  -427,  -427,   -87,
    -427,  -427,  -427,   -84,  -427,   176,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -118,  -427,  -427,  -427,
    -111,   203,  -427,  -427,  -427,  -427,  -427,  -427,  -113,  -427,
    -427,  -427,  -110,   202,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -108,  -427,  -427,  -427,  -115,
    -427,   195,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,    71,  -427,  -427,  -427,  -427,  -427,
    -427,   -93,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   -98,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   -48,  -427,
    -427,  -427,  -178,  -427,  -427,  -193,  -427,  -427,  -427,  -427,
    -427,  -427,  -202,  -427,  -427,  -206,  -427
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   423,   507,    69,    70,   107,    37,    58,    80,    81,
      82,   248,    39,    59,   108,   109,   110,   111,   112,   113,
     114,   115,   255,    41,    60,   132,   278,   116,   256,   117,
     257,   477,   478,   479,   564,   666,   480,   565,   481,   566,
     482,   567,   209,   313,   484,   485,   486,   487,   118,   266,
     503,   504,   505,   506,   119,   268,   510,   511,   512,   120,
     267,   121,   270,   516,   517,   518,   591,    55,    67,   239,
     240,   241,   325,   242,   326,   122,   271,   520,   521,   123,
     263,   490,   491,   492,   575,    43,    61,   150,   151,   152,
     283,   153,   284,   154,   285,   155,   289,   156,   288,   157,
     158,   124,   264,   494,   495,   496,   578,    51,    65,   210,
     211,   212,   213,   214,   215,   216,   312,   217,   316,   218,
     315,   219,   220,   317,   221,   125,   265,   498,   499,   500,
     581,    53,    66,   228,   229,   230,   231,   232,   321,   233,
     234,   235,   160,   281,   546,   547,   548,   610,    45,    62,
     167,   168,   169,   294,   161,   282,   550,   551,   552,   613,
      47,    63,   177,   178,   179,   297,   180,   181,   299,   182,
     183,   162,   290,   554,   555,   556,   616,    49,    64,   192,
     193,   194,   195,   305,   196,   306,   197,   307,   198,   308,
     199,   309,   200,   304,   163,   291,   558,   619,   126,   269,
     514,   280,   364,   365,   366,   367,   368,   432,   127,   272,
     529,   530,   531,   597,   677,   532,   533,   598,   534,   535,
     128,   129,   274,   538,   539,   540,   604,   541,   605,   130,
     275,    83,   250,    84,   251,    85,   249,   464,   465,   466,
     560,   686,   687,   688,   696,   697,   698,   699,   704,   700,
     702,   714,   715,   716,   720,   721,   723
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   225,   528,   145,   165,   175,   190,   208,   224,   238,
     513,   159,   166,   176,   191,   226,    32,   227,   509,   133,
     146,    74,    96,   147,   148,   149,    25,    24,    26,   431,
      27,    86,   164,    87,    88,   133,    36,   253,    89,    90,
      91,    92,   254,   236,   237,    96,    89,    90,    91,    92,
      93,    94,    95,    96,   134,   501,   135,   236,   237,   447,
     448,   449,   136,   137,   138,   139,   140,   141,    38,   584,
      40,    96,   585,   142,   143,   522,    97,    98,    99,   100,
     144,    42,   472,   170,   171,   172,   173,   174,   201,   142,
     101,    44,    78,   102,   103,    78,   502,   587,    75,    46,
     588,    71,   104,   105,    76,    77,   106,   202,   589,   203,
     204,   590,   205,   206,   207,   468,    96,    78,    78,   469,
     470,   471,   472,   473,   474,   475,    78,    28,    29,    30,
      31,    96,   202,   202,   202,   663,   664,   665,   523,   524,
     525,   526,   184,    48,    78,    50,   185,   186,   187,   188,
     189,   202,   222,   203,   204,   223,   276,   292,   360,   295,
     302,   277,   293,   327,   296,   303,    78,   276,   328,    52,
     561,   131,   559,   572,   641,   562,   528,   572,   573,    78,
     595,   509,   574,   689,   243,   596,   690,   602,   691,    78,
     692,   693,   603,   606,   247,    79,   292,   327,   607,   608,
     244,   670,   673,   295,    78,    78,    78,   302,   681,   705,
     717,   724,   682,   718,   706,   362,   725,   674,   675,   676,
     501,   508,   361,    78,   536,   537,    54,   245,   246,   247,
     363,   252,   258,   259,   145,   260,   261,   165,   262,   273,
     286,   279,   159,   287,   175,   166,   298,   329,   330,   300,
     301,   146,   176,   190,   147,   148,   149,   310,   311,   225,
     314,   191,   208,   318,   320,   319,   224,   322,   323,   324,
     340,   331,   332,   226,   333,   227,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,   334,   335,   337,
     338,   339,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   359,
     369,   370,   371,   372,   373,   376,   374,   377,   378,   375,
     379,   381,   383,   384,   385,   386,   389,   390,   387,   391,
     392,   393,   394,   396,   397,   399,   400,   413,   414,   401,
     404,   407,   408,   410,   398,   418,   463,   402,   411,   405,
     412,   483,   483,   415,   416,   417,   419,   420,   476,   476,
     421,   422,   424,   425,   426,   434,   577,   427,   428,   362,
     527,   429,   430,   435,   433,   436,   361,   437,   438,   439,
     440,   441,   442,   443,   363,   444,   445,   446,   450,   489,
     493,   497,   515,   543,   451,   452,   453,   454,   545,   549,
     553,   568,   557,   563,   569,   570,   571,   620,   455,   576,
     579,   460,   580,   461,   582,   583,   592,   593,   456,   594,
     599,   457,   600,   601,   612,   458,   611,   459,   614,   615,
     519,   617,   618,   639,   621,   623,   624,   625,   626,   646,
     609,   647,   652,   653,   661,   542,   662,   703,   707,   709,
     671,   627,   628,   629,   672,   683,   630,   644,   685,   711,
     648,   649,   713,   726,   586,   336,   462,   467,   358,   631,
     719,   488,   638,   640,   650,   667,   643,   668,   669,   678,
     679,   680,   642,   633,   684,   409,   708,   712,   645,   632,
     380,   635,   728,   634,   656,   403,   637,   636,   382,   655,
     406,   659,   658,   657,   388,   544,   395,   483,   654,   651,
     660,   701,   710,   622,   476,   722,   225,   145,   727,     0,
     208,     0,     0,   224,     0,   159,     0,     0,     0,     0,
     226,     0,   227,   238,   146,     0,     0,   147,   148,   149,
       0,     0,     0,     0,   527,     0,     0,     0,     0,     0,
       0,     0,   165,     0,     0,   175,     0,     0,   190,     0,
     166,     0,     0,   176,     0,     0,   191,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   695,     0,     0,     0,     0,     0,     0,
     694,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     695,     0,     0,     0,     0,     0,     0,   694
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,   428,    61,    62,    63,    64,    65,    66,    67,
     425,    61,    62,    63,    64,    66,    13,    66,   424,     7,
      61,    10,    33,    61,    61,    61,     5,     0,     7,   359,
       9,    11,    43,    13,    14,     7,     7,     3,    26,    27,
      28,    29,     8,    71,    72,    33,    26,    27,    28,    29,
      30,    31,    32,    33,    42,    65,    44,    71,    72,   389,
     390,   391,    50,    51,    52,    53,    54,    55,     7,     3,
       7,    33,     6,    61,    62,    15,    56,    57,    58,    59,
      68,     7,    22,    45,    46,    47,    48,    49,    15,    61,
      70,     7,   106,    73,    74,   106,   106,     3,    87,     7,
       6,   106,    82,    83,    93,    94,    86,    34,     3,    36,
      37,     6,    39,    40,    41,    15,    33,   106,   106,    19,
      20,    21,    22,    23,    24,    25,   106,   106,   107,   108,
     109,    33,    34,    34,    34,    16,    17,    18,    78,    79,
      80,    81,    59,     7,   106,     7,    63,    64,    65,    66,
      67,    34,    35,    36,    37,    38,     3,     3,    60,     3,
       3,     8,     8,     3,     8,     8,   106,     3,     8,     7,
       3,    12,     8,     3,   589,     8,   602,     3,     8,   106,
       3,   587,     8,     3,     6,     8,     6,     3,    89,   106,
      91,    92,     8,     3,     3,   253,     3,     3,     8,     8,
       3,     8,     8,     3,   106,   106,   106,     3,     8,     3,
       3,     3,     8,     6,     8,   280,     8,    75,    76,    77,
      65,    66,   280,   106,    84,    85,     7,     4,     8,     3,
     280,     4,     4,     4,   292,     4,     4,   295,     4,     4,
       4,     8,   292,     4,   302,   295,     4,   244,   245,     4,
       4,   292,   302,   311,   292,   292,   292,     8,     3,   324,
       4,   311,   320,     4,     3,     8,   324,     4,     8,     3,
     107,   106,     4,   324,     4,   324,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     4,     4,     4,
       4,     4,   107,   107,   107,   107,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   107,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   107,     4,     4,   109,
       4,     4,     4,   107,     4,   107,     4,     4,   107,     4,
       4,     4,     4,     4,     4,     4,     4,   334,   335,     4,
       4,     4,     4,     4,   107,     5,    88,   109,     7,   109,
       7,   416,   417,     7,     7,     7,     5,     5,   416,   417,
       5,     5,     5,     5,     5,     3,     3,     7,     7,   434,
     428,     7,     7,     5,     8,     5,   434,   106,   106,   106,
     106,   106,     5,     7,   434,   106,   106,   106,   106,     7,
       7,     7,     7,     4,   106,   106,   106,   106,     7,     7,
       7,     4,    69,     8,     4,     4,     4,     8,   106,     6,
       6,   408,     3,   410,     6,     3,     6,     3,   106,     4,
       4,   106,     4,     4,     3,   106,     6,   106,     6,     3,
     106,     6,     3,     6,     4,     4,     4,     4,     4,     4,
     106,     4,     4,     4,     4,   430,     5,     4,     4,     4,
       8,   109,   107,   109,     8,     8,   107,   107,     7,     5,
     107,   107,     7,     4,   507,   253,   411,   415,   276,   572,
      90,   417,   584,   587,   107,   106,   593,   106,   106,   106,
     106,   106,   591,   577,   106,   327,   107,   106,   595,   575,
     292,   580,   106,   578,   612,   320,   583,   581,   295,   610,
     324,   616,   615,   613,   302,   434,   311,   572,   606,   602,
     618,   689,   705,   561,   572,   717,   581,   575,   724,    -1,
     578,    -1,    -1,   581,    -1,   575,    -1,    -1,    -1,    -1,
     581,    -1,   581,   591,   575,    -1,    -1,   575,   575,   575,
      -1,    -1,    -1,    -1,   602,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   610,    -1,    -1,   613,    -1,    -1,   616,    -1,
     610,    -1,    -1,   613,    -1,    -1,   616,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   688,    -1,    -1,    -1,    -1,    -1,    -1,
     688,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     705,    -1,    -1,    -1,    -1,    -1,    -1,   705
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,     0,     5,     7,     9,   106,   107,
     108,   109,   123,   124,   125,   129,     7,   136,     7,   142,
       7,   153,     7,   215,     7,   278,     7,   290,     7,   307,
       7,   237,     7,   261,     7,   197,   130,   126,   137,   143,
     154,   216,   279,   291,   308,   238,   262,   198,   123,   133,
     134,   106,   127,   128,    10,    87,    93,    94,   106,   135,
     138,   139,   140,   361,   363,   365,    11,    13,    14,    26,
      27,    28,    29,    30,    31,    32,    33,    56,    57,    58,
      59,    70,    73,    74,    82,    83,    86,   135,   144,   145,
     146,   147,   148,   149,   150,   151,   157,   159,   178,   184,
     189,   191,   205,   209,   231,   255,   328,   338,   350,   351,
     359,    12,   155,     7,    42,    44,    50,    51,    52,    53,
      54,    55,    61,    62,    68,   135,   146,   147,   148,   149,
     217,   218,   219,   221,   223,   225,   227,   229,   230,   255,
     272,   284,   301,   324,    43,   135,   255,   280,   281,   282,
      45,    46,    47,    48,    49,   135,   255,   292,   293,   294,
     296,   297,   299,   300,    59,    63,    64,    65,    66,    67,
     135,   255,   309,   310,   311,   312,   314,   316,   318,   320,
     322,    15,    34,    36,    37,    39,    40,    41,   135,   172,
     239,   240,   241,   242,   243,   244,   245,   247,   249,   251,
     252,   254,    35,    38,   135,   172,   243,   249,   263,   264,
     265,   266,   267,   269,   270,   271,    71,    72,   135,   199,
     200,   201,   203,     6,     3,     4,     8,     3,   141,   366,
     362,   364,     4,     3,     8,   152,   158,   160,     4,     4,
       4,     4,     4,   210,   232,   256,   179,   190,   185,   329,
     192,   206,   339,     4,   352,   360,     3,     8,   156,     8,
     331,   273,   285,   220,   222,   224,     4,     4,   228,   226,
     302,   325,     3,     8,   283,     3,     8,   295,     4,   298,
       4,     4,     3,     8,   323,   313,   315,   317,   319,   321,
       8,     3,   246,   173,     4,   250,   248,   253,     4,     8,
       3,   268,     4,     8,     3,   202,   204,     3,     8,   123,
     123,   106,     4,     4,     4,     4,   139,     4,     4,     4,
     107,   107,   107,   107,   107,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   107,     4,     4,   145,     4,
      60,   135,   172,   255,   332,   333,   334,   335,   336,     4,
       4,     4,     4,     4,   107,   109,     4,     4,     4,     4,
     218,     4,   281,     4,   107,     4,   107,   107,   293,     4,
       4,     4,     4,     4,     4,   311,     4,     4,   107,     4,
       4,     4,   109,   241,     4,   109,   265,     4,     4,   200,
       4,     7,     7,   123,   123,     7,     7,     7,     5,     5,
       5,     5,     5,   131,     5,     5,     5,     7,     7,     7,
       7,   131,   337,     8,     3,     5,     5,   106,   106,   106,
     106,   106,     5,     7,   106,   106,   106,   131,   131,   131,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     123,   123,   144,    88,   367,   368,   369,   155,    15,    19,
      20,    21,    22,    23,    24,    25,   135,   161,   162,   163,
     166,   168,   170,   172,   174,   175,   176,   177,   161,     7,
     211,   212,   213,     7,   233,   234,   235,     7,   257,   258,
     259,    65,   106,   180,   181,   182,   183,   132,    66,   182,
     186,   187,   188,   225,   330,     7,   193,   194,   195,   106,
     207,   208,    15,    78,    79,    80,    81,   135,   174,   340,
     341,   342,   345,   346,   348,   349,    84,    85,   353,   354,
     355,   357,   128,     4,   334,     7,   274,   275,   276,     7,
     286,   287,   288,     7,   303,   304,   305,    69,   326,     8,
     370,     3,     8,     8,   164,   167,   169,   171,     4,     4,
       4,     4,     3,     8,     8,   214,     6,     3,   236,     6,
       3,   260,     6,     3,     3,     6,   133,     3,     6,     3,
       6,   196,     6,     3,     4,     3,     8,   343,   347,     4,
       4,     4,     3,     8,   356,   358,     3,     8,     8,   106,
     277,     6,     3,   289,     6,     3,   306,     6,     3,   327,
       8,     4,   368,     4,     4,     4,     4,   109,   107,   109,
     107,   162,   217,   213,   239,   235,   263,   259,   181,     6,
     187,   225,   199,   195,   107,   208,     4,     4,   107,   107,
     107,   341,     4,     4,   354,   280,   276,   292,   288,   309,
     305,     4,     5,    16,    17,    18,   165,   106,   106,   106,
       8,     8,     8,     8,    75,    76,    77,   344,   106,   106,
     106,     8,     8,     8,   106,     7,   371,   372,   373,     3,
       6,    89,    91,    92,   135,   172,   374,   375,   376,   377,
     379,   372,   380,     4,   378,     3,     8,     4,   107,     4,
     375,     5,   106,     7,   381,   382,   383,     3,     6,    90,
     384,   385,   382,   386,     3,     8,     4,   385,   106
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   110,   112,   111,   113,   111,   114,   111,   115,   111,
     116,   111,   117,   111,   118,   111,   119,   111,   120,   111,
     121,   111,   122,   111,   123,   123,   123,   123,   123,   123,
     123,   124,   126,   125,   127,   127,   128,   128,   130,   129,
     132,   131,   133,   133,   134,   134,   135,   137,   136,   138,
     138,   139,   139,   139,   139,   139,   141,   140,   143,   142,
     144,   144,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   146,   147,   148,   149,   150,   152,
     151,   154,   153,   156,   155,   158,   157,   160,   159,   161,
     161,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   164,   163,   165,   165,   165,   167,   166,   169,   168,
     171,   170,   173,   172,   174,   175,   176,   177,   179,   178,
     180,   180,   181,   181,   182,   183,   185,   184,   186,   186,
     187,   187,   188,   190,   189,   192,   191,   193,   193,   194,
     194,   196,   195,   198,   197,   199,   199,   199,   200,   200,
     202,   201,   204,   203,   206,   205,   207,   207,   208,   210,
     209,   211,   211,   212,   212,   214,   213,   216,   215,   217,
     217,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   220,   219,
     222,   221,   224,   223,   226,   225,   228,   227,   229,   230,
     232,   231,   233,   233,   234,   234,   236,   235,   238,   237,
     239,   239,   240,   240,   241,   241,   241,   241,   241,   241,
     241,   241,   242,   243,   244,   246,   245,   248,   247,   250,
     249,   251,   253,   252,   254,   256,   255,   257,   257,   258,
     258,   260,   259,   262,   261,   263,   263,   264,   264,   265,
     265,   265,   265,   265,   265,   266,   268,   267,   269,   270,
     271,   273,   272,   274,   274,   275,   275,   277,   276,   279,
     278,   280,   280,   281,   281,   281,   283,   282,   285,   284,
     286,   286,   287,   287,   289,   288,   291,   290,   292,   292,
     293,   293,   293,   293,   293,   293,   293,   295,   294,   296,
     298,   297,   299,   300,   302,   301,   303,   303,   304,   304,
     306,   305,   308,   307,   309,   309,   310,   310,   311,   311,
     311,   311,   311,   311,   311,   311,   313,   312,   315,   314,
     317,   316,   319,   318,   321,   320,   323,   322,   325,   324,
     327,   326,   329,   328,   330,   330,   331,   225,   332,   332,
     333,   333,   334,   334,   334,   334,   335,   337,   336,   339,
     338,   340,   340,   341,   341,   341,   341,   341,   341,   341,
     343,   342,   344,   344,   344,   345,   347,   346,   348,   349,
     350,   352,   351,   353,   353,   354,   354,   356,   355,   358,
     357,   360,   359,   362,   361,   364,   363,   366,   365,   367,
     367,   368,   370,   369,   371,   371,   373,   372,   374,   374,
     375,   375,   375,   375,   375,   376,   378,   377,   380,   379,
     381,   381,   383,   382,   384,   384,   386,   385
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
       1,     0,     4,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
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
  "\"hosts-database\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"user\"", "\"password\"", "\"host\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
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
  "db_type", "user", "$@24", "password", "$@25", "host", "$@26", "name",
  "$@27", "persist", "lfc_interval", "readonly", "connect_timeout",
  "mac_sources", "$@28", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@29",
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
       0,   207,   207,   207,   208,   208,   209,   209,   210,   210,
     211,   211,   212,   212,   213,   213,   214,   214,   215,   215,
     216,   216,   217,   217,   225,   226,   227,   228,   229,   230,
     231,   234,   239,   239,   251,   252,   255,   259,   266,   266,
     274,   274,   281,   282,   285,   289,   300,   310,   310,   322,
     323,   327,   328,   329,   330,   331,   334,   334,   351,   351,
     359,   360,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   389,   394,   399,   404,   409,   414,
     414,   424,   424,   432,   432,   442,   442,   452,   452,   462,
     463,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   478,   478,   485,   486,   487,   490,   490,   498,   498,
     506,   506,   514,   514,   522,   527,   532,   537,   542,   542,
     552,   553,   556,   557,   560,   565,   570,   570,   580,   581,
     584,   585,   588,   593,   593,   603,   603,   613,   614,   617,
     618,   621,   621,   629,   629,   637,   638,   639,   642,   643,
     646,   646,   654,   654,   662,   662,   672,   673,   679,   687,
     687,   700,   701,   704,   705,   712,   712,   735,   735,   744,
     745,   749,   750,   751,   752,   753,   754,   755,   756,   757,
     758,   759,   760,   761,   762,   763,   764,   765,   768,   768,
     776,   776,   784,   784,   792,   792,   800,   800,   808,   813,
     822,   822,   834,   835,   838,   839,   844,   844,   855,   855,
     865,   866,   869,   870,   873,   874,   875,   876,   877,   878,
     879,   880,   883,   885,   890,   892,   892,   900,   900,   908,
     908,   916,   918,   918,   926,   935,   935,   947,   948,   953,
     954,   959,   959,   970,   970,   981,   982,   987,   988,   993,
     994,   995,   996,   997,   998,  1001,  1003,  1003,  1011,  1013,
    1015,  1023,  1023,  1035,  1036,  1039,  1040,  1043,  1043,  1051,
    1051,  1059,  1060,  1063,  1064,  1065,  1068,  1068,  1079,  1079,
    1091,  1092,  1095,  1096,  1099,  1099,  1107,  1107,  1115,  1116,
    1119,  1120,  1121,  1122,  1123,  1124,  1125,  1128,  1128,  1136,
    1141,  1141,  1149,  1154,  1162,  1162,  1172,  1173,  1176,  1177,
    1180,  1180,  1188,  1188,  1196,  1197,  1200,  1201,  1205,  1206,
    1207,  1208,  1209,  1210,  1211,  1212,  1215,  1215,  1225,  1225,
    1235,  1235,  1243,  1243,  1251,  1251,  1259,  1259,  1272,  1272,
    1282,  1282,  1293,  1293,  1303,  1304,  1307,  1307,  1315,  1316,
    1319,  1320,  1323,  1324,  1325,  1326,  1329,  1331,  1331,  1342,
    1342,  1352,  1353,  1356,  1357,  1358,  1359,  1360,  1361,  1362,
    1365,  1365,  1372,  1373,  1374,  1377,  1382,  1382,  1390,  1395,
    1402,  1409,  1409,  1419,  1420,  1423,  1424,  1427,  1427,  1435,
    1435,  1445,  1445,  1457,  1457,  1464,  1464,  1476,  1476,  1489,
    1490,  1494,  1498,  1498,  1510,  1511,  1515,  1515,  1523,  1524,
    1527,  1528,  1529,  1530,  1531,  1534,  1538,  1538,  1546,  1546,
    1556,  1557,  1560,  1560,  1568,  1569,  1572,  1572
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
#line 3620 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1580 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
