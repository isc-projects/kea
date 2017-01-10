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
      case 124: // value
      case 166: // db_type
      case 345: // duid_type
        value.move< ElementPtr > (that.value);
        break;

      case 110: // "boolean"
        value.move< bool > (that.value);
        break;

      case 109: // "floating point"
        value.move< double > (that.value);
        break;

      case 108: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 107: // "constant string"
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
      case 124: // value
      case 166: // db_type
      case 345: // duid_type
        value.copy< ElementPtr > (that.value);
        break;

      case 110: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 109: // "floating point"
        value.copy< double > (that.value);
        break;

      case 108: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 107: // "constant string"
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
            case 107: // "constant string"

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 356 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 108: // "integer"

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 363 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 109: // "floating point"

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 370 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 110: // "boolean"

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 377 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 124: // value

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 384 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 166: // db_type

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 391 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 345: // duid_type

#line 199 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 124: // value
      case 166: // db_type
      case 345: // duid_type
        yylhs.value.build< ElementPtr > ();
        break;

      case 110: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 109: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 108: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 107: // "constant string"
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
#line 640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 209 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 210 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 211 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 212 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 213 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 214 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 215 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 216 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 217 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 218 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 751 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 854 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 875 "dhcp6_parser.cc" // lalr1.cc:859
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
#line 888 "dhcp6_parser.cc" // lalr1.cc:859
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
#line 900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 927 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 410 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 488 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 489 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1192 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1248 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1361 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 718 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 788 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 824 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1790 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1005 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1863 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1955 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1138 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1982 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1990 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1194 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1222 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1232 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2264 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2302 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2310 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2501 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2551 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2624 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2642 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
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
     180,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,    56,    21,    51,    83,    95,   104,   158,   205,
     213,   214,   216,   217,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,    21,    72,    11,    20,
     178,    12,     1,    99,    76,    47,   125,    25,  -427,   219,
     223,   224,   221,   228,  -427,  -427,  -427,  -427,   229,  -427,
      19,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   231,
     232,   234,   235,   236,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   237,  -427,  -427,  -427,    68,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   238,  -427,  -427,  -427,  -427,  -427,  -427,   239,
     245,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
      93,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,   106,  -427,  -427,
    -427,   246,  -427,   253,   254,  -427,  -427,   109,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   252,   260,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   261,  -427,  -427,  -427,   263,  -427,  -427,
     256,   265,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,   266,  -427,  -427,  -427,  -427,   264,   268,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   131,
    -427,  -427,  -427,  -427,    21,    21,  -427,   120,   270,   283,
     284,   285,  -427,    11,  -427,   286,   287,   288,   161,   187,
     188,   189,   190,   289,   290,   295,   296,   297,   298,   299,
     300,   301,   302,   199,   304,   305,    20,  -427,   306,  -427,
       9,   307,   308,   309,   310,   311,   208,   207,   314,   315,
     316,   317,    12,  -427,   318,     1,  -427,   319,   218,   320,
     220,   222,    99,  -427,   321,   323,   325,   327,   328,   329,
    -427,    76,   330,   331,   233,   332,   335,   336,   240,  -427,
      47,   338,   243,  -427,   125,   339,   340,    65,  -427,  -427,
    -427,   341,   342,   347,    21,    21,  -427,   348,   349,   350,
    -427,  -427,  -427,  -427,  -427,   343,   355,   356,   357,   358,
     359,   360,   361,   364,   365,  -427,   366,   367,  -427,   358,
    -427,  -427,  -427,  -427,   369,   344,  -427,  -427,  -427,   362,
     363,   271,   272,   273,  -427,  -427,   274,   275,   370,   376,
    -427,   278,  -427,   279,  -427,   280,  -427,  -427,  -427,   358,
     358,   358,   281,   282,   291,  -427,   292,   293,  -427,   294,
     303,   312,  -427,  -427,   313,  -427,  -427,   322,    21,  -427,
      21,    20,   257,  -427,  -427,   178,   100,   100,   383,   384,
     385,   -34,  -427,  -427,   -30,    31,   386,   324,    77,   133,
      72,  -427,   390,  -427,     9,   388,   389,  -427,  -427,  -427,
    -427,  -427,   395,   333,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   147,  -427,   164,  -427,  -427,   396,  -427,  -427,
    -427,  -427,   393,   401,   402,   403,  -427,   170,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   172,  -427,
     406,   405,  -427,  -427,   408,   412,  -427,  -427,   410,   414,
    -427,  -427,  -427,    66,  -427,  -427,  -427,    21,  -427,  -427,
      80,  -427,  -427,  -427,   163,  -427,   415,   419,  -427,   420,
     174,  -427,  -427,  -427,   421,   422,   423,  -427,  -427,   183,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   184,  -427,
    -427,  -427,   185,   326,  -427,  -427,   417,   425,  -427,  -427,
     424,   429,  -427,  -427,   428,   432,  -427,  -427,   430,  -427,
     433,   257,  -427,  -427,   435,   436,   437,   438,   334,   337,
     345,   346,   100,  -427,  -427,    12,  -427,   383,    47,  -427,
     384,   125,  -427,   385,   -34,  -427,   440,   -30,  -427,    31,
    -427,    25,  -427,   386,   351,   324,  -427,   439,   443,   352,
     353,   354,    77,  -427,   444,   445,   133,  -427,  -427,  -427,
       1,  -427,   388,    99,  -427,   389,    76,  -427,   395,   446,
    -427,   404,  -427,   192,   368,   371,   372,  -427,  -427,  -427,
    -427,  -427,   186,  -427,   448,  -427,   449,  -427,  -427,  -427,
    -427,  -427,   193,  -427,  -427,  -427,    75,   373,  -427,  -427,
    -427,  -427,   374,   375,  -427,   194,  -427,   195,  -427,   450,
    -427,   377,   411,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,   210,  -427,    78,
     411,  -427,  -427,   447,  -427,  -427,  -427,   196,  -427,  -427,
    -427,  -427,  -427,   459,   378,   460,    78,  -427,   431,  -427,
     380,  -427,   458,  -427,  -427,   211,  -427,   379,   458,  -427,
    -427,   197,  -427,  -427,   462,   379,  -427,   381,  -427,  -427
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    38,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    47,     5,    58,     7,
      91,     9,   178,    11,   280,    13,   297,    15,   323,    17,
     219,    19,   254,    21,   154,    23,    42,    34,     0,     0,
       0,     0,     0,     0,   325,   221,   256,     0,    44,     0,
      43,     0,     0,    35,    56,   408,   404,   406,     0,    55,
       0,    49,    51,    53,    54,    52,    89,    95,    97,     0,
       0,     0,     0,     0,   170,   211,   246,   129,   144,   137,
     353,   146,   165,   370,     0,   392,   402,    83,     0,    60,
      62,    63,    64,    65,    66,    68,    69,    70,    71,    73,
      72,    77,    78,    67,    75,    76,    74,    79,    80,    81,
      82,    93,     0,   357,   272,   289,   199,   201,   203,     0,
       0,   207,   205,   315,   349,   198,   182,   183,   184,   185,
       0,   180,   189,   190,   191,   194,   196,   192,   193,   186,
     187,   188,   195,   197,   287,   286,   285,     0,   282,   284,
     308,     0,   311,     0,     0,   307,   304,     0,   299,   301,
     302,   305,   306,   303,   347,   337,   339,   341,   343,   345,
     336,   335,     0,   326,   327,   331,   332,   329,   333,   334,
     330,   236,   123,     0,   240,   238,   243,     0,   232,   233,
       0,   222,   223,   225,   235,   226,   227,   228,   242,   229,
     230,   231,   267,     0,   265,   266,   269,   270,     0,   257,
     258,   260,   261,   262,   263,   264,   161,   163,   158,     0,
     156,   159,   160,    39,     0,     0,    33,     0,     0,     0,
       0,     0,    46,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,     0,    92,
     359,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,   281,     0,     0,     0,
       0,     0,     0,   298,     0,     0,     0,     0,     0,     0,
     324,     0,     0,     0,     0,     0,     0,     0,     0,   220,
       0,     0,     0,   255,     0,     0,     0,     0,   155,    45,
      36,     0,     0,     0,     0,     0,    50,     0,     0,     0,
      84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   391,     0,     0,    61,     0,
     368,   366,   367,   365,     0,   360,   361,   363,   364,     0,
       0,     0,     0,     0,   209,   210,     0,     0,     0,     0,
     181,     0,   283,     0,   310,     0,   313,   314,   300,     0,
       0,     0,     0,     0,     0,   328,     0,     0,   234,     0,
       0,     0,   245,   224,     0,   271,   259,     0,     0,   157,
       0,     0,     0,   405,   407,     0,     0,     0,   172,   213,
     248,     0,    40,   145,     0,     0,   148,     0,     0,     0,
       0,    94,     0,   358,     0,   274,   291,   200,   202,   204,
     208,   206,   317,     0,   288,   309,   312,   348,   338,   340,
     342,   344,   346,   237,   124,   241,   239,   244,   268,   162,
     164,    37,     0,   413,     0,   410,   412,     0,   111,   117,
     119,   121,     0,     0,     0,     0,   110,     0,    99,   101,
     102,   103,   104,   105,   106,   107,   108,   109,     0,   176,
       0,   173,   174,   217,     0,   214,   215,   252,     0,   249,
     250,   135,   136,     0,   131,   133,   134,    42,   143,   141,
       0,   139,   142,   355,     0,   152,     0,   149,   150,     0,
       0,   167,   381,   387,     0,     0,     0,   380,   379,     0,
     372,   374,   377,   375,   376,   378,   398,   400,     0,   394,
     396,   397,     0,     0,   362,   278,     0,   275,   276,   295,
       0,   292,   293,   321,     0,   318,   319,   351,     0,    57,
       0,     0,   409,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,    98,     0,   171,     0,   221,   212,
       0,   256,   247,     0,     0,   130,     0,     0,   138,     0,
     354,     0,   147,     0,     0,     0,   166,     0,     0,     0,
       0,     0,     0,   371,     0,     0,     0,   393,   403,   369,
       0,   273,     0,     0,   290,     0,   325,   316,     0,     0,
     350,     0,   411,     0,     0,     0,     0,   125,   126,   127,
     128,   100,     0,   175,     0,   216,     0,   251,   132,    41,
     140,   356,     0,   151,   169,   168,     0,     0,   386,   389,
     390,   373,     0,     0,   395,     0,   277,     0,   294,     0,
     320,     0,     0,   113,   114,   115,   116,   112,   118,   120,
     122,   177,   218,   253,   153,   383,   384,   385,   382,   388,
     399,   401,   279,   296,   322,   352,   417,     0,   415,     0,
       0,   414,   429,     0,   427,   425,   421,     0,   419,   423,
     424,   422,   416,     0,     0,     0,     0,   418,     0,   426,
       0,   420,     0,   428,   433,     0,   431,     0,     0,   430,
     437,     0,   435,   432,     0,     0,   434,     0,   436,   438
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,     3,  -427,  -427,  -427,  -427,    22,  -427,
    -427,  -330,  -427,   -54,  -427,   -58,  -427,  -427,  -427,   215,
    -427,  -427,  -427,  -427,    58,   191,   -41,   -38,   -37,   -36,
    -427,  -427,  -427,  -427,  -427,    57,  -427,  -427,  -427,  -427,
    -427,    54,   -99,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   -65,  -427,  -426,  -427,  -427,  -427,  -427,  -427,
    -427,  -110,  -406,  -427,  -427,  -427,  -427,  -111,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -116,  -427,  -427,  -427,  -108,
     162,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -105,  -427,
    -427,  -427,  -427,   -92,  -427,  -427,  -427,   -84,   200,  -427,
    -427,  -427,  -427,  -427,  -427,  -415,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,   -87,  -427,  -427,  -427,   -83,
    -427,   176,  -427,   -51,  -427,  -427,  -427,  -427,  -427,   -49,
    -427,  -427,  -427,  -427,  -427,   -50,  -427,  -427,  -427,   -89,
    -427,  -427,  -427,   -82,  -427,   173,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -114,  -427,  -427,  -427,
    -109,   209,  -427,  -427,  -427,  -427,  -427,  -427,  -115,  -427,
    -427,  -427,  -107,   201,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -113,  -427,  -427,  -427,  -106,
    -427,   198,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,    74,  -427,  -427,  -427,  -427,  -427,
    -427,  -100,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,   -95,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,   -48,  -427,
    -427,  -427,  -178,  -427,  -427,  -191,  -427,  -427,  -427,  -427,
    -427,  -427,  -200,  -427,  -427,  -206,  -427
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    68,    33,    34,    57,    72,    73,    35,
      56,   423,   507,    69,    70,   107,    37,    58,    80,    81,
      82,   248,    39,    59,   108,   109,   110,   111,   112,   113,
     114,   115,   255,    41,    60,   132,   278,   116,   256,   117,
     257,   477,   478,   479,   564,   667,   480,   565,   481,   566,
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
     529,   530,   531,   597,   678,   532,   533,   598,   534,   535,
     128,   129,   274,   538,   539,   540,   604,   541,   605,   130,
     275,    83,   250,    84,   251,    85,   249,   464,   465,   466,
     560,   687,   688,   689,   697,   698,   699,   700,   705,   701,
     703,   715,   716,   717,   721,   722,   724
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      79,   225,   528,   145,   165,   175,   190,   208,   224,   238,
     513,   159,   166,   176,   191,   226,    32,   227,   509,   133,
     146,    74,   253,   147,   148,   149,    25,   254,    26,   431,
      27,    86,   501,    87,    88,    96,   501,   508,   133,    89,
      90,    91,    92,    96,   202,   164,    96,    89,    90,    91,
      92,    93,    94,    95,    96,   134,    24,   135,    36,   447,
     448,   449,   201,   136,   137,   138,   139,   140,   141,   584,
     360,   276,   585,   502,   142,   143,   277,    97,    98,    99,
     100,   144,   202,   587,   203,   204,   588,   205,   206,   207,
      38,   101,   522,   142,   102,   103,   292,   236,   237,    75,
     472,   293,    40,   104,   105,    76,    77,   106,    78,   295,
      96,    42,   302,   202,   296,   468,    78,   303,    78,    78,
     469,   470,   471,   472,   473,   474,   475,    78,    28,    29,
      30,    31,    78,    96,   327,   202,   184,   236,   237,   328,
     185,   186,   187,   188,   189,   170,   171,   172,   173,   174,
     276,   675,   676,   677,    78,   559,   523,   524,   525,   526,
     202,   222,   203,   204,   223,    44,   589,   561,   692,   590,
     693,   694,   562,   572,   641,   572,   528,   595,   573,    71,
     574,   509,   596,    78,    78,    78,   602,   606,   247,   292,
     131,   603,   607,   608,   671,    79,   327,   295,   302,   706,
     725,   674,   682,   683,   707,   726,    78,    78,   663,   664,
     665,   666,    46,   690,   718,   362,   691,   719,   536,   537,
      48,    50,   361,    52,    54,   243,   244,   331,   245,   246,
     363,   247,    78,   252,   145,   258,   259,   165,   260,   261,
     262,   273,   159,   286,   175,   166,   279,   329,   330,   287,
     298,   146,   176,   190,   147,   148,   149,   300,   301,   225,
     310,   191,   208,   311,   319,   314,   224,   318,   320,   340,
     322,   324,   323,   226,   332,   227,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,   333,   334,   335,
     337,   338,   339,   345,   346,   341,   342,   343,   344,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     359,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   381,   383,   385,   389,   384,   390,   386,   391,
     387,   392,   393,   394,   396,   397,   399,   413,   414,   400,
     401,   398,   404,   407,   408,   410,   463,   434,   418,   411,
     402,   483,   483,   405,   412,   415,   416,   417,   476,   476,
     419,   420,   421,   422,   424,   425,   426,   435,   436,   362,
     527,   427,   428,   429,   430,   442,   361,   433,   437,   438,
     439,   440,   441,   443,   363,   444,   445,   446,   450,   451,
     489,   493,   497,   515,   543,   545,   549,   568,   452,   453,
     454,   455,   553,   557,   563,   569,   570,   571,   577,   662,
     456,   460,   576,   461,   579,   580,   582,   583,   686,   457,
     458,   592,   593,   611,   594,   599,   600,   601,   612,   459,
     614,   519,   615,   609,   617,   618,   712,   621,   620,   623,
     624,   625,   626,   646,   627,   628,   639,   647,   652,   653,
     661,   704,   542,   586,   630,   629,   672,   673,   684,   644,
     648,   649,   650,   708,   710,   714,   727,   358,   336,   462,
     720,   488,   467,   631,   638,   668,   640,   643,   669,   670,
     679,   680,   681,   642,   685,   633,   709,   713,   729,   409,
     645,   632,   380,   635,   637,   634,   403,   406,   656,   636,
     658,   655,   651,   388,   382,   660,   657,   483,   544,   395,
     659,   654,   702,   622,   476,   711,   225,   145,   723,   728,
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
       0,     0,     0,     0,   696,     0,     0,     0,     0,     0,
       0,   695,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   696,     0,     0,     0,     0,     0,     0,   695
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      58,    66,   428,    61,    62,    63,    64,    65,    66,    67,
     425,    61,    62,    63,    64,    66,    13,    66,   424,     7,
      61,    10,     3,    61,    61,    61,     5,     8,     7,   359,
       9,    11,    66,    13,    14,    34,    66,    67,     7,    27,
      28,    29,    30,    34,    35,    44,    34,    27,    28,    29,
      30,    31,    32,    33,    34,    43,     0,    45,     7,   389,
     390,   391,    15,    51,    52,    53,    54,    55,    56,     3,
      61,     3,     6,   107,    62,    63,     8,    57,    58,    59,
      60,    69,    35,     3,    37,    38,     6,    40,    41,    42,
       7,    71,    15,    62,    74,    75,     3,    72,    73,    88,
      23,     8,     7,    83,    84,    94,    95,    87,   107,     3,
      34,     7,     3,    35,     8,    15,   107,     8,   107,   107,
      20,    21,    22,    23,    24,    25,    26,   107,   107,   108,
     109,   110,   107,    34,     3,    35,    60,    72,    73,     8,
      64,    65,    66,    67,    68,    46,    47,    48,    49,    50,
       3,    76,    77,    78,   107,     8,    79,    80,    81,    82,
      35,    36,    37,    38,    39,     7,     3,     3,    90,     6,
      92,    93,     8,     3,   589,     3,   602,     3,     8,   107,
       8,   587,     8,   107,   107,   107,     3,     3,     3,     3,
      12,     8,     8,     8,     8,   253,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,   107,   107,    16,    17,
      18,    19,     7,     3,     3,   280,     6,     6,    85,    86,
       7,     7,   280,     7,     7,     6,     3,   107,     4,     8,
     280,     3,   107,     4,   292,     4,     4,   295,     4,     4,
       4,     4,   292,     4,   302,   295,     8,   244,   245,     4,
       4,   292,   302,   311,   292,   292,   292,     4,     4,   324,
       8,   311,   320,     3,     8,     4,   324,     4,     3,   108,
       4,     3,     8,   324,     4,   324,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,     4,     4,     4,
       4,     4,     4,     4,     4,   108,   108,   108,   108,     4,
       4,     4,     4,     4,     4,     4,     4,   108,     4,     4,
       4,     4,     4,     4,     4,     4,   108,   110,     4,     4,
       4,     4,     4,     4,     4,     4,   108,     4,   108,     4,
     108,     4,     4,     4,     4,     4,     4,   334,   335,     4,
       4,   108,     4,     4,     4,     4,    89,     3,     5,     7,
     110,   416,   417,   110,     7,     7,     7,     7,   416,   417,
       5,     5,     5,     5,     5,     5,     5,     5,     5,   434,
     428,     7,     7,     7,     7,     5,   434,     8,   107,   107,
     107,   107,   107,     7,   434,   107,   107,   107,   107,   107,
       7,     7,     7,     7,     4,     7,     7,     4,   107,   107,
     107,   107,     7,    70,     8,     4,     4,     4,     3,     5,
     107,   408,     6,   410,     6,     3,     6,     3,     7,   107,
     107,     6,     3,     6,     4,     4,     4,     4,     3,   107,
       6,   107,     3,   107,     6,     3,     5,     4,     8,     4,
       4,     4,     4,     4,   110,   108,     6,     4,     4,     4,
       4,     4,   430,   507,   108,   110,     8,     8,     8,   108,
     108,   108,   108,     4,     4,     7,     4,   276,   253,   411,
      91,   417,   415,   572,   584,   107,   587,   593,   107,   107,
     107,   107,   107,   591,   107,   577,   108,   107,   107,   327,
     595,   575,   292,   580,   583,   578,   320,   324,   612,   581,
     615,   610,   602,   302,   295,   618,   613,   572,   434,   311,
     616,   606,   690,   561,   572,   706,   581,   575,   718,   725,
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
      -1,    -1,    -1,    -1,   689,    -1,    -1,    -1,    -1,    -1,
      -1,   689,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   706,    -1,    -1,    -1,    -1,    -1,    -1,   706
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,     0,     5,     7,     9,   107,   108,
     109,   110,   124,   125,   126,   130,     7,   137,     7,   143,
       7,   154,     7,   216,     7,   279,     7,   291,     7,   308,
       7,   238,     7,   262,     7,   198,   131,   127,   138,   144,
     155,   217,   280,   292,   309,   239,   263,   199,   124,   134,
     135,   107,   128,   129,    10,    88,    94,    95,   107,   136,
     139,   140,   141,   362,   364,   366,    11,    13,    14,    27,
      28,    29,    30,    31,    32,    33,    34,    57,    58,    59,
      60,    71,    74,    75,    83,    84,    87,   136,   145,   146,
     147,   148,   149,   150,   151,   152,   158,   160,   179,   185,
     190,   192,   206,   210,   232,   256,   329,   339,   351,   352,
     360,    12,   156,     7,    43,    45,    51,    52,    53,    54,
      55,    56,    62,    63,    69,   136,   147,   148,   149,   150,
     218,   219,   220,   222,   224,   226,   228,   230,   231,   256,
     273,   285,   302,   325,    44,   136,   256,   281,   282,   283,
      46,    47,    48,    49,    50,   136,   256,   293,   294,   295,
     297,   298,   300,   301,    60,    64,    65,    66,    67,    68,
     136,   256,   310,   311,   312,   313,   315,   317,   319,   321,
     323,    15,    35,    37,    38,    40,    41,    42,   136,   173,
     240,   241,   242,   243,   244,   245,   246,   248,   250,   252,
     253,   255,    36,    39,   136,   173,   244,   250,   264,   265,
     266,   267,   268,   270,   271,   272,    72,    73,   136,   200,
     201,   202,   204,     6,     3,     4,     8,     3,   142,   367,
     363,   365,     4,     3,     8,   153,   159,   161,     4,     4,
       4,     4,     4,   211,   233,   257,   180,   191,   186,   330,
     193,   207,   340,     4,   353,   361,     3,     8,   157,     8,
     332,   274,   286,   221,   223,   225,     4,     4,   229,   227,
     303,   326,     3,     8,   284,     3,     8,   296,     4,   299,
       4,     4,     3,     8,   324,   314,   316,   318,   320,   322,
       8,     3,   247,   174,     4,   251,   249,   254,     4,     8,
       3,   269,     4,     8,     3,   203,   205,     3,     8,   124,
     124,   107,     4,     4,     4,     4,   140,     4,     4,     4,
     108,   108,   108,   108,   108,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   108,     4,     4,   146,     4,
      61,   136,   173,   256,   333,   334,   335,   336,   337,     4,
       4,     4,     4,     4,   108,   110,     4,     4,     4,     4,
     219,     4,   282,     4,   108,     4,   108,   108,   294,     4,
       4,     4,     4,     4,     4,   312,     4,     4,   108,     4,
       4,     4,   110,   242,     4,   110,   266,     4,     4,   201,
       4,     7,     7,   124,   124,     7,     7,     7,     5,     5,
       5,     5,     5,   132,     5,     5,     5,     7,     7,     7,
       7,   132,   338,     8,     3,     5,     5,   107,   107,   107,
     107,   107,     5,     7,   107,   107,   107,   132,   132,   132,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     124,   124,   145,    89,   368,   369,   370,   156,    15,    20,
      21,    22,    23,    24,    25,    26,   136,   162,   163,   164,
     167,   169,   171,   173,   175,   176,   177,   178,   162,     7,
     212,   213,   214,     7,   234,   235,   236,     7,   258,   259,
     260,    66,   107,   181,   182,   183,   184,   133,    67,   183,
     187,   188,   189,   226,   331,     7,   194,   195,   196,   107,
     208,   209,    15,    79,    80,    81,    82,   136,   175,   341,
     342,   343,   346,   347,   349,   350,    85,    86,   354,   355,
     356,   358,   129,     4,   335,     7,   275,   276,   277,     7,
     287,   288,   289,     7,   304,   305,   306,    70,   327,     8,
     371,     3,     8,     8,   165,   168,   170,   172,     4,     4,
       4,     4,     3,     8,     8,   215,     6,     3,   237,     6,
       3,   261,     6,     3,     3,     6,   134,     3,     6,     3,
       6,   197,     6,     3,     4,     3,     8,   344,   348,     4,
       4,     4,     3,     8,   357,   359,     3,     8,     8,   107,
     278,     6,     3,   290,     6,     3,   307,     6,     3,   328,
       8,     4,   369,     4,     4,     4,     4,   110,   108,   110,
     108,   163,   218,   214,   240,   236,   264,   260,   182,     6,
     188,   226,   200,   196,   108,   209,     4,     4,   108,   108,
     108,   342,     4,     4,   355,   281,   277,   293,   289,   310,
     306,     4,     5,    16,    17,    18,    19,   166,   107,   107,
     107,     8,     8,     8,     8,    76,    77,    78,   345,   107,
     107,   107,     8,     8,     8,   107,     7,   372,   373,   374,
       3,     6,    90,    92,    93,   136,   173,   375,   376,   377,
     378,   380,   373,   381,     4,   379,     3,     8,     4,   108,
       4,   376,     5,   107,     7,   382,   383,   384,     3,     6,
      91,   385,   386,   383,   387,     3,     8,     4,   386,   107
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   111,   113,   112,   114,   112,   115,   112,   116,   112,
     117,   112,   118,   112,   119,   112,   120,   112,   121,   112,
     122,   112,   123,   112,   124,   124,   124,   124,   124,   124,
     124,   125,   127,   126,   128,   128,   129,   129,   131,   130,
     133,   132,   134,   134,   135,   135,   136,   138,   137,   139,
     139,   140,   140,   140,   140,   140,   142,   141,   144,   143,
     145,   145,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   147,   148,   149,   150,   151,   153,
     152,   155,   154,   157,   156,   159,   158,   161,   160,   162,
     162,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   165,   164,   166,   166,   166,   166,   168,   167,   170,
     169,   172,   171,   174,   173,   175,   176,   177,   178,   180,
     179,   181,   181,   182,   182,   183,   184,   186,   185,   187,
     187,   188,   188,   189,   191,   190,   193,   192,   194,   194,
     195,   195,   197,   196,   199,   198,   200,   200,   200,   201,
     201,   203,   202,   205,   204,   207,   206,   208,   208,   209,
     211,   210,   212,   212,   213,   213,   215,   214,   217,   216,
     218,   218,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   221,
     220,   223,   222,   225,   224,   227,   226,   229,   228,   230,
     231,   233,   232,   234,   234,   235,   235,   237,   236,   239,
     238,   240,   240,   241,   241,   242,   242,   242,   242,   242,
     242,   242,   242,   243,   244,   245,   247,   246,   249,   248,
     251,   250,   252,   254,   253,   255,   257,   256,   258,   258,
     259,   259,   261,   260,   263,   262,   264,   264,   265,   265,
     266,   266,   266,   266,   266,   266,   267,   269,   268,   270,
     271,   272,   274,   273,   275,   275,   276,   276,   278,   277,
     280,   279,   281,   281,   282,   282,   282,   284,   283,   286,
     285,   287,   287,   288,   288,   290,   289,   292,   291,   293,
     293,   294,   294,   294,   294,   294,   294,   294,   296,   295,
     297,   299,   298,   300,   301,   303,   302,   304,   304,   305,
     305,   307,   306,   309,   308,   310,   310,   311,   311,   312,
     312,   312,   312,   312,   312,   312,   312,   314,   313,   316,
     315,   318,   317,   320,   319,   322,   321,   324,   323,   326,
     325,   328,   327,   330,   329,   331,   331,   332,   226,   333,
     333,   334,   334,   335,   335,   335,   335,   336,   338,   337,
     340,   339,   341,   341,   342,   342,   342,   342,   342,   342,
     342,   344,   343,   345,   345,   345,   346,   348,   347,   349,
     350,   351,   353,   352,   354,   354,   355,   355,   357,   356,
     359,   358,   361,   360,   363,   362,   365,   364,   367,   366,
     368,   368,   369,   371,   370,   372,   372,   374,   373,   375,
     375,   376,   376,   376,   376,   376,   377,   379,   378,   381,
     380,   382,   382,   384,   383,   385,   385,   387,   386
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
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     0,     4
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
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
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
     476,   479,   479,   486,   487,   488,   489,   492,   492,   500,
     500,   508,   508,   516,   516,   524,   529,   534,   539,   544,
     544,   554,   555,   558,   559,   562,   567,   572,   572,   582,
     583,   586,   587,   590,   595,   595,   605,   605,   615,   616,
     619,   620,   623,   623,   631,   631,   639,   640,   641,   644,
     645,   648,   648,   656,   656,   664,   664,   674,   675,   681,
     689,   689,   702,   703,   706,   707,   714,   714,   737,   737,
     746,   747,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,   767,   770,
     770,   778,   778,   786,   786,   794,   794,   802,   802,   810,
     815,   824,   824,   836,   837,   840,   841,   846,   846,   857,
     857,   867,   868,   871,   872,   875,   876,   877,   878,   879,
     880,   881,   882,   885,   887,   892,   894,   894,   902,   902,
     910,   910,   918,   920,   920,   928,   937,   937,   949,   950,
     955,   956,   961,   961,   972,   972,   983,   984,   989,   990,
     995,   996,   997,   998,   999,  1000,  1003,  1005,  1005,  1013,
    1015,  1017,  1025,  1025,  1037,  1038,  1041,  1042,  1045,  1045,
    1053,  1053,  1061,  1062,  1065,  1066,  1067,  1070,  1070,  1081,
    1081,  1093,  1094,  1097,  1098,  1101,  1101,  1109,  1109,  1117,
    1118,  1121,  1122,  1123,  1124,  1125,  1126,  1127,  1130,  1130,
    1138,  1143,  1143,  1151,  1156,  1164,  1164,  1174,  1175,  1178,
    1179,  1182,  1182,  1190,  1190,  1198,  1199,  1202,  1203,  1207,
    1208,  1209,  1210,  1211,  1212,  1213,  1214,  1217,  1217,  1227,
    1227,  1237,  1237,  1245,  1245,  1253,  1253,  1261,  1261,  1274,
    1274,  1284,  1284,  1295,  1295,  1305,  1306,  1309,  1309,  1317,
    1318,  1321,  1322,  1325,  1326,  1327,  1328,  1331,  1333,  1333,
    1344,  1344,  1354,  1355,  1358,  1359,  1360,  1361,  1362,  1363,
    1364,  1367,  1367,  1374,  1375,  1376,  1379,  1384,  1384,  1392,
    1397,  1404,  1411,  1411,  1421,  1422,  1425,  1426,  1429,  1429,
    1437,  1437,  1447,  1447,  1459,  1459,  1466,  1466,  1478,  1478,
    1491,  1492,  1496,  1500,  1500,  1512,  1513,  1517,  1517,  1525,
    1526,  1529,  1530,  1531,  1532,  1533,  1536,  1540,  1540,  1548,
    1548,  1558,  1559,  1562,  1562,  1570,  1571,  1574,  1574
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
#line 3626 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1582 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
