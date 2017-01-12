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
      case 123: // value
      case 127: // map_value
      case 163: // socket_type
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 123: // value
      case 127: // map_value
      case 163: // socket_type
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
            case 107: // "constant string"

#line 200 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 356 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 108: // "integer"

#line 200 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 363 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 109: // "floating point"

#line 200 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 370 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 110: // "boolean"

#line 200 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 377 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 123: // value

#line 200 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 384 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 127: // map_value

#line 200 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 391 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 163: // socket_type

#line 200 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 398 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 123: // value
      case 127: // map_value
      case 163: // socket_type
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
#line 209 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 210 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 211 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 652 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 212 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 213 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 214 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 226 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 854 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 936 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 954 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1038 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 466 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1254 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1328 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1336 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1374 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1410 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1419 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1437 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1448 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1457 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 848 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1652 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1661 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 867 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1743 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 974 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1854 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1135 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2028 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1218 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2118 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2210 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1317 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2519 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2593 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2611 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2629 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2633 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -419;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     184,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,    27,    23,    35,    60,    67,    78,    86,    95,   106,
     145,   149,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,    23,    13,    19,    65,    24,    17,    -6,    99,
     165,    48,    -7,  -419,    49,   155,   166,   152,   178,  -419,
    -419,  -419,  -419,   216,  -419,    42,  -419,  -419,  -419,  -419,
    -419,  -419,   218,   237,  -419,  -419,  -419,   239,   240,   241,
     243,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,   244,
    -419,  -419,  -419,    43,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,    54,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
     250,   251,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,    58,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,    72,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,   193,   234,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,   257,  -419,  -419,  -419,   258,  -419,  -419,  -419,
     255,   261,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,   265,  -419,  -419,  -419,  -419,   262,   271,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,   102,
    -419,  -419,  -419,  -419,    23,    23,  -419,   168,   272,   273,
     274,   275,  -419,    19,  -419,   287,   182,   183,   290,   291,
     292,   189,   190,   191,   192,   297,   298,   299,   300,   301,
     302,   303,   304,   202,   305,   307,    65,  -419,   308,   309,
      24,  -419,    20,   310,   311,   312,   313,   314,   315,   316,
     214,   215,   317,   319,   320,   322,    17,  -419,   323,   324,
      -6,  -419,   325,   326,   327,   328,   329,   330,   331,   332,
     333,  -419,    99,   334,   335,   232,   339,   340,   341,   236,
    -419,   165,   343,   238,  -419,    48,   345,   346,    36,  -419,
    -419,  -419,   347,   348,   349,    23,    23,  -419,   350,  -419,
    -419,   245,   351,   352,  -419,  -419,  -419,  -419,   355,   356,
     357,   358,   361,   362,   364,   365,  -419,   366,   367,  -419,
     363,   114,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
     368,   372,  -419,  -419,  -419,   246,   247,   270,   374,   277,
     278,   279,  -419,  -419,   280,   282,   375,   383,  -419,   284,
     385,  -419,   286,   289,   363,   293,   294,   295,   296,   306,
     318,  -419,   321,   336,  -419,   337,   338,   342,  -419,  -419,
     344,  -419,  -419,   353,    23,  -419,    23,    65,   360,  -419,
    -419,    24,  -419,   150,   150,   387,   390,   392,   162,    34,
     397,   156,   112,    82,    13,  -419,  -419,  -419,  -419,  -419,
     377,  -419,    20,  -419,  -419,  -419,   398,  -419,  -419,  -419,
    -419,  -419,   399,   359,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,   113,  -419,   133,  -419,  -419,
     137,  -419,  -419,  -419,   378,   403,   404,  -419,   139,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,   140,  -419,
     405,   406,  -419,  -419,   408,   407,  -419,  -419,   409,   413,
    -419,  -419,  -419,  -419,  -419,  -419,   177,  -419,  -419,  -419,
    -419,  -419,   197,  -419,   411,   415,  -419,   417,   419,   420,
     422,   425,   426,   143,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,   427,   428,   429,  -419,  -419,  -419,   151,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,   163,  -419,  -419,  -419,
     179,    23,   354,  -419,  -419,   430,   416,  -419,  -419,   431,
     432,  -419,  -419,   433,  -419,   434,   360,  -419,  -419,   435,
     436,   438,   369,   370,   371,   150,  -419,  -419,    17,  -419,
     387,   165,  -419,   390,    48,  -419,   392,   162,  -419,    34,
    -419,    -7,  -419,   397,   376,   379,   380,   381,   382,   384,
     156,  -419,   442,   386,   388,   389,   112,  -419,   443,   444,
      82,  -419,  -419,   446,  -419,    -6,  -419,   398,    99,  -419,
     399,   449,  -419,   450,  -419,   373,   391,   393,  -419,  -419,
    -419,  -419,   188,  -419,   448,  -419,   451,  -419,  -419,  -419,
     194,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,   394,
    -419,  -419,  -419,  -419,   395,   396,  -419,  -419,   201,  -419,
     454,  -419,   400,   447,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,   211,  -419,
      18,   447,  -419,  -419,   453,  -419,  -419,  -419,   210,  -419,
    -419,  -419,  -419,  -419,   459,   401,   460,    18,  -419,   461,
    -419,   410,  -419,   458,  -419,  -419,   233,  -419,   412,   458,
    -419,  -419,   213,  -419,  -419,   463,   412,  -419,   414,  -419,
    -419
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    37,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    46,     5,    57,     7,    95,     9,
     186,    11,   296,    13,   316,    15,   236,    17,   270,    19,
     151,    21,    41,    33,     0,     0,     0,     0,     0,   318,
     238,   272,     0,    43,     0,    42,     0,     0,    34,    55,
     411,   407,   409,     0,    54,     0,    48,    50,    52,    53,
      51,    89,     0,     0,   334,   103,   105,     0,     0,     0,
       0,   178,   228,   262,   132,   358,   143,   162,   378,     0,
     395,   405,    82,     0,    59,    61,    62,    63,    64,    79,
      80,    66,    67,    68,    69,    73,    74,    65,    71,    72,
      81,    70,    75,    76,    77,    78,    97,    99,     0,    91,
      93,    94,   362,   212,   214,   216,   288,   210,   218,   220,
       0,     0,   224,   222,   308,   354,   209,   190,   191,   192,
     204,     0,   188,   195,   206,   207,   208,   196,   197,   200,
     202,   198,   199,   193,   194,   201,   205,   203,   304,   306,
     303,   301,     0,   298,   300,   302,   336,   338,   352,   342,
     344,   348,   346,   350,   340,   333,   329,     0,   319,   320,
     330,   331,   332,   326,   322,   327,   324,   325,   328,   323,
     118,   126,     0,   256,   254,   259,     0,   249,   253,   250,
       0,   239,   240,   242,   252,   243,   244,   245,   258,   246,
     247,   248,   283,     0,   281,   282,   285,   286,     0,   273,
     274,   276,   277,   278,   279,   280,   158,   160,   155,     0,
     153,   156,   157,    38,     0,     0,    31,     0,     0,     0,
       0,     0,    45,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,     0,     0,
       0,    96,   364,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   187,     0,     0,
       0,   297,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   317,     0,     0,     0,     0,     0,     0,     0,     0,
     237,     0,     0,     0,   271,     0,     0,     0,     0,   152,
      44,    35,     0,     0,     0,     0,     0,    49,     0,    87,
      88,     0,     0,     0,    83,    84,    85,    86,     0,     0,
       0,     0,     0,     0,     0,     0,   394,     0,     0,    60,
       0,     0,    92,   376,   374,   375,   370,   371,   372,   373,
       0,   365,   366,   368,   369,     0,     0,     0,     0,     0,
       0,     0,   226,   227,     0,     0,     0,     0,   189,     0,
       0,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   321,     0,     0,   251,     0,     0,     0,   261,   241,
       0,   287,   275,     0,     0,   154,     0,     0,     0,   408,
     410,     0,   335,     0,     0,   180,   230,   264,     0,     0,
     145,     0,     0,     0,     0,    39,    98,   101,   102,   100,
       0,   363,     0,   213,   215,   217,   290,   211,   219,   221,
     225,   223,   310,     0,   305,    32,   307,   337,   339,   353,
     343,   345,   349,   347,   351,   341,   119,   127,   257,   255,
     260,   284,   159,   161,    36,     0,   416,     0,   413,   415,
       0,   120,   122,   124,     0,     0,     0,   117,     0,   107,
     109,   110,   111,   112,   113,   114,   115,   116,     0,   184,
       0,   181,   182,   234,     0,   231,   232,   268,     0,   265,
     266,   131,   140,   141,   142,   136,     0,   134,   137,   138,
     139,   360,     0,   149,     0,   146,   147,     0,     0,     0,
       0,     0,     0,     0,   164,   166,   167,   168,   169,   170,
     171,   390,     0,     0,     0,   388,   382,   387,     0,   380,
     385,   383,   384,   386,   401,   403,     0,   397,   399,   400,
       0,    41,     0,   367,   294,     0,   291,   292,   314,     0,
     311,   312,   356,     0,    56,     0,     0,   412,    90,     0,
       0,     0,     0,     0,     0,     0,   104,   106,     0,   179,
       0,   238,   229,     0,   272,   263,     0,     0,   133,     0,
     359,     0,   144,     0,     0,     0,     0,     0,     0,     0,
       0,   163,     0,     0,     0,     0,     0,   379,     0,     0,
       0,   396,   406,     0,   377,     0,   289,     0,   318,   309,
       0,     0,   355,     0,   414,     0,     0,     0,   128,   129,
     130,   108,     0,   183,     0,   233,     0,   267,   135,   361,
       0,   148,   172,   173,   174,   175,   176,   177,   165,     0,
     389,   392,   393,   381,     0,     0,   398,    40,     0,   293,
       0,   313,     0,     0,   121,   123,   125,   185,   235,   269,
     150,   391,   402,   404,   295,   315,   357,   420,     0,   418,
       0,     0,   417,   432,     0,   430,   428,   424,     0,   422,
     426,   427,   425,   419,     0,     0,     0,     0,   421,     0,
     429,     0,   423,     0,   431,   436,     0,   434,     0,     0,
     433,   440,     0,   438,   435,     0,     0,   437,     0,   439,
     441
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,     6,  -419,    22,  -419,  -419,  -419,     0,  -419,
    -419,    64,  -419,   -93,  -419,   -54,  -419,  -419,  -419,   217,
    -419,  -419,  -419,  -419,    52,   195,   -56,   -40,   -37,  -419,
    -419,   -36,  -419,  -419,    51,   196,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,    50,  -112,  -401,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,   -59,  -419,  -418,
    -419,  -419,  -419,  -419,  -419,  -419,  -122,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -126,  -419,  -419,  -419,  -119,   157,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -127,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -104,  -419,
    -419,  -419,   -97,   199,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -410,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -100,  -419,  -419,  -419,
     -92,  -419,   185,  -419,   -52,  -419,  -419,  -419,  -419,   -45,
    -419,  -419,  -419,  -419,  -419,   -47,  -419,  -419,  -419,   -91,
    -419,  -419,  -419,   -86,  -419,   186,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -117,  -419,  -419,  -419,
    -113,   219,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -116,  -419,  -419,  -419,  -115,  -419,   203,   -44,  -419,  -257,
    -419,  -256,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,    74,  -419,  -419,
    -419,  -419,  -419,  -419,   -98,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,   -96,  -419,  -419,  -419,  -419,  -419,
    -419,  -419,  -419,  -419,  -419,  -419,  -419,  -419,   -53,  -419,
    -419,  -419,  -171,  -419,  -419,  -185,  -419,  -419,  -419,  -419,
    -419,  -419,  -194,  -419,  -419,  -199,  -419
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,   456,    67,    68,    33,
      52,   436,   561,    64,    65,   102,    35,    54,    75,    76,
      77,   248,    37,    55,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   255,   128,   129,    39,    56,   130,   278,
     131,   279,   439,   112,   259,   113,   260,   488,   489,   208,
     313,   491,   579,   492,   580,   493,   581,   209,   314,   495,
     496,   497,   515,   114,   268,   516,   517,   518,   519,   520,
     115,   270,   524,   525,   526,   601,    51,    62,   239,   240,
     241,   326,   242,   327,   116,   271,   533,   534,   535,   536,
     537,   538,   539,   540,   117,   265,   500,   501,   502,   588,
      41,    57,   151,   152,   153,   287,   154,   283,   155,   284,
     156,   285,   157,   288,   158,   289,   159,   293,   160,   292,
     161,   162,   118,   266,   504,   505,   506,   591,    47,    60,
     210,   211,   212,   213,   214,   215,   216,   217,   317,   218,
     316,   219,   220,   318,   221,   119,   267,   508,   509,   510,
     594,    49,    61,   228,   229,   230,   231,   232,   322,   233,
     234,   235,   164,   286,   565,   566,   567,   625,    43,    58,
     172,   173,   174,   298,   175,   299,   165,   294,   569,   570,
     571,   628,    45,    59,   187,   188,   189,   120,   258,   191,
     302,   192,   303,   193,   310,   194,   305,   195,   306,   196,
     308,   197,   307,   198,   309,   199,   304,   167,   295,   573,
     631,   121,   269,   522,   282,   370,   371,   372,   373,   374,
     440,   122,   272,   548,   549,   550,   551,   612,   552,   553,
     123,   124,   274,   556,   557,   558,   618,   559,   619,   125,
     275,    78,   250,    79,   251,    80,   249,   477,   478,   479,
     575,   688,   689,   690,   698,   699,   700,   701,   706,   702,
     704,   716,   717,   718,   722,   723,   725
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   147,   225,   146,   170,   185,   207,   224,   238,   226,
     163,   171,   186,   166,   547,   190,   227,   148,    30,   521,
     149,   150,   490,   490,   132,   368,   369,    22,    23,    69,
      24,   546,    25,    93,    83,    84,   126,   127,    84,   176,
     177,   132,    34,   168,   169,   253,   276,    87,    88,    89,
     254,   277,   133,   134,   135,   243,    93,   280,   201,    93,
     201,   296,   281,   236,   237,   136,   297,    36,   137,   138,
     139,   140,   141,   142,    38,   300,    81,   143,   144,   363,
     301,    82,    83,    84,   145,    40,    85,    86,   201,   222,
     202,   203,   223,    42,   143,    87,    88,    89,    90,    91,
      73,    73,    44,    92,    93,   328,   236,   237,    70,   693,
     329,   694,   695,    46,    71,    72,   276,    84,   176,   177,
      66,   574,    94,    95,    73,    73,    73,    73,   437,   438,
      26,    27,    28,    29,    96,   200,   576,    97,    93,   484,
     280,   577,   585,   585,    98,   578,   610,   586,   587,    99,
     100,   611,    48,   101,   616,    73,    50,   178,   244,   617,
     246,   179,   180,   181,   182,   183,   620,   184,   554,   555,
     245,   621,    73,   200,   481,   482,   483,   484,   485,   486,
     597,   247,   247,   598,   490,   368,   369,   622,   200,   649,
     201,   296,   541,   542,   543,   544,   677,   328,   547,    74,
     599,   311,   680,   600,   300,   201,    73,   202,   203,   684,
     204,   205,   206,   707,   691,   546,   726,   692,   708,    73,
     252,   727,   256,   365,   511,   512,   513,   514,   364,   527,
     528,   529,   530,   531,   532,   366,   719,   312,   367,   720,
     147,   257,   146,   261,   262,   263,   170,   264,   273,   163,
     330,   331,   166,   171,   290,   291,   148,    73,   185,   149,
     150,   315,   319,   320,   321,   186,   225,   207,   190,   323,
     324,   224,    73,   226,   325,   332,   333,   334,   335,   336,
     227,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   357,
     356,   358,   360,   361,   375,   376,   377,   378,   379,   380,
     381,   384,   382,   385,   386,   383,   387,   389,   390,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   402,   403,
     404,   419,   420,   405,   406,   407,   408,   410,   411,   413,
     414,   416,   422,   443,   444,   417,   418,   421,   423,   424,
     425,   426,   427,   428,   494,   494,   429,   430,   435,   487,
     487,   431,   432,   433,   434,   442,   441,   445,   545,   446,
     452,   562,   582,   365,   447,   448,   449,   450,   364,   451,
     453,   454,    24,   457,   499,   366,   458,   503,   367,   507,
     460,   461,   462,   463,   523,   564,   568,   583,   584,   590,
     593,   589,   455,   464,   592,   595,   596,   602,   603,   627,
     473,   604,   474,   605,   606,   465,   607,   572,   466,   608,
     609,   613,   614,   615,   560,   630,   626,   629,   633,   635,
     636,   632,   637,   467,   468,   469,   659,   664,   665,   470,
     476,   471,   667,   672,   687,   673,   678,   705,   459,   679,
     472,   624,   685,   709,   711,   715,   713,   728,   623,   475,
     337,   359,   480,   641,   498,   648,   362,   651,   639,   638,
     674,   640,   650,   658,   652,   415,   643,   653,   654,   655,
     656,   642,   657,   645,   660,   388,   661,   662,   675,   644,
     676,   681,   682,   683,   721,   647,   409,   686,   646,   710,
     669,   412,   668,   670,   671,   401,   563,   714,   663,   391,
     703,   730,   712,   634,   666,   724,   494,   729,     0,     0,
       0,   487,   147,     0,   146,   225,     0,   207,     0,     0,
     224,   163,   226,     0,   166,     0,     0,   238,   148,   227,
       0,   149,   150,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   545,     0,     0,     0,     0,     0,     0,     0,
       0,   170,     0,     0,   185,     0,     0,     0,   171,     0,
       0,   186,     0,     0,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   697,     0,     0,     0,     0,   696,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   697,     0,
       0,     0,     0,   696
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    57,   432,    59,    61,    57,    12,   429,
      57,    57,   423,   424,     7,   282,   282,     0,     5,    10,
       7,   432,     9,    39,    17,    18,    12,    13,    18,    19,
      20,     7,     7,    49,    50,     3,     3,    30,    31,    32,
       8,     8,    35,    36,    37,     6,    39,     3,    40,    39,
      40,     3,     8,    70,    71,    48,     8,     7,    51,    52,
      53,    54,    55,    56,     7,     3,    11,    60,    61,    59,
       8,    16,    17,    18,    67,     7,    21,    22,    40,    41,
      42,    43,    44,     7,    60,    30,    31,    32,    33,    34,
     107,   107,     7,    38,    39,     3,    70,    71,    89,    91,
       8,    93,    94,     7,    95,    96,     3,    18,    19,    20,
     107,     8,    57,    58,   107,   107,   107,   107,    14,    15,
     107,   108,   109,   110,    69,    23,     3,    72,    39,    27,
       3,     8,     3,     3,    79,     8,     3,     8,     8,    84,
      85,     8,     7,    88,     3,   107,     7,    58,     3,     8,
       8,    62,    63,    64,    65,    66,     3,    68,    86,    87,
       4,     8,   107,    23,    24,    25,    26,    27,    28,    29,
       3,     3,     3,     6,   585,   442,   442,     8,    23,   599,
      40,     3,    80,    81,    82,    83,     8,     3,   616,   253,
       3,     8,     8,     6,     3,    40,   107,    42,    43,     8,
      45,    46,    47,     3,     3,   616,     3,     6,     8,   107,
       4,     8,     4,   282,    62,    63,    64,    65,   282,    73,
      74,    75,    76,    77,    78,   282,     3,     3,   282,     6,
     296,     4,   296,     4,     4,     4,   300,     4,     4,   296,
     244,   245,   296,   300,     4,     4,   296,   107,   312,   296,
     296,     4,     4,     8,     3,   312,   325,   321,   312,     4,
       8,   325,   107,   325,     3,   107,     4,     4,     4,     4,
     325,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,     4,   110,   110,     4,     4,     4,   108,   108,   108,
     108,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     108,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   108,     4,     4,   110,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     108,   335,   336,     4,     4,     4,   110,     4,   110,     4,
       4,     4,   107,   107,   107,     7,     7,     7,     7,     7,
       5,     5,     5,     5,   423,   424,     5,     5,     5,   423,
     424,     7,     7,     7,     7,     3,     8,   107,   432,     5,
       5,     4,     4,   442,   107,   107,   107,   107,   442,   107,
       7,   107,     7,   107,     7,   442,   107,     7,   442,     7,
     107,   107,   107,   107,     7,     7,     7,     4,     4,     3,
       3,     6,   390,   107,     6,     6,     3,     6,     3,     3,
     414,     4,   416,     4,     4,   107,     4,    68,   107,     4,
       4,     4,     4,     4,   434,     3,     6,     6,     4,     4,
       4,     8,     4,   107,   107,   107,     4,     4,     4,   107,
      90,   107,     6,     4,     7,     5,     8,     4,   394,     8,
     107,   107,     8,     4,     4,     7,     5,     4,   561,   417,
     253,   276,   421,   585,   424,   597,   280,   603,   108,   110,
     107,   110,   601,   610,   108,   328,   590,   108,   108,   108,
     108,   588,   108,   593,   108,   296,   108,   108,   107,   591,
     107,   107,   107,   107,    92,   596,   321,   107,   594,   108,
     627,   325,   625,   628,   630,   312,   442,   107,   616,   300,
     691,   107,   707,   576,   620,   719,   585,   726,    -1,    -1,
      -1,   585,   588,    -1,   588,   594,    -1,   591,    -1,    -1,
     594,   588,   594,    -1,   588,    -1,    -1,   601,   588,   594,
      -1,   588,   588,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   616,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   625,    -1,    -1,   628,    -1,    -1,    -1,   625,    -1,
      -1,   628,    -1,    -1,   628,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   690,    -1,    -1,    -1,    -1,   690,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   707,    -1,
      -1,    -1,    -1,   707
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,     0,     5,     7,     9,   107,   108,   109,   110,
     123,   124,   125,   130,     7,   137,     7,   143,     7,   157,
       7,   221,     7,   289,     7,   303,     7,   249,     7,   272,
       7,   197,   131,   126,   138,   144,   158,   222,   290,   304,
     250,   273,   198,   123,   134,   135,   107,   128,   129,    10,
      89,    95,    96,   107,   136,   139,   140,   141,   362,   364,
     366,    11,    16,    17,    18,    21,    22,    30,    31,    32,
      33,    34,    38,    39,    57,    58,    69,    72,    79,    84,
      85,    88,   136,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   164,   166,   184,   191,   205,   215,   243,   266,
     308,   332,   342,   351,   352,   360,    12,    13,   155,   156,
     159,   161,     7,    35,    36,    37,    48,    51,    52,    53,
      54,    55,    56,    60,    61,    67,   136,   147,   148,   149,
     152,   223,   224,   225,   227,   229,   231,   233,   235,   237,
     239,   241,   242,   266,   283,   297,   308,   328,    49,    50,
     136,   266,   291,   292,   293,   295,    19,    20,    58,    62,
      63,    64,    65,    66,    68,   136,   266,   305,   306,   307,
     308,   310,   312,   314,   316,   318,   320,   322,   324,   326,
      23,    40,    42,    43,    45,    46,    47,   136,   170,   178,
     251,   252,   253,   254,   255,   256,   257,   258,   260,   262,
     263,   265,    41,    44,   136,   178,   255,   260,   274,   275,
     276,   277,   278,   280,   281,   282,    70,    71,   136,   199,
     200,   201,   203,     6,     3,     4,     8,     3,   142,   367,
     363,   365,     4,     3,     8,   154,     4,     4,   309,   165,
     167,     4,     4,     4,     4,   216,   244,   267,   185,   333,
     192,   206,   343,     4,   353,   361,     3,     8,   160,   162,
       3,     8,   335,   228,   230,   232,   284,   226,   234,   236,
       4,     4,   240,   238,   298,   329,     3,     8,   294,   296,
       3,     8,   311,   313,   327,   317,   319,   323,   321,   325,
     315,     8,     3,   171,   179,     4,   261,   259,   264,     4,
       8,     3,   279,     4,     8,     3,   202,   204,     3,     8,
     123,   123,   107,     4,     4,     4,     4,   140,     4,   110,
     110,     4,     4,     4,   108,   108,   108,   108,     4,     4,
       4,     4,     4,     4,     4,     4,   108,     4,     4,   146,
       4,     4,   156,    59,   136,   178,   266,   308,   310,   312,
     336,   337,   338,   339,   340,     4,     4,     4,     4,     4,
       4,     4,   108,   110,     4,     4,     4,     4,   224,     4,
       4,   292,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   307,     4,     4,   108,     4,     4,     4,   110,   253,
       4,   110,   276,     4,     4,   200,     4,     7,     7,   123,
     123,     7,   107,     7,     7,     5,     5,     5,     5,     5,
       5,     7,     7,     7,     7,     5,   132,    14,    15,   163,
     341,     8,     3,   107,   107,   107,     5,   107,   107,   107,
     107,   107,     5,     7,   107,   125,   127,   107,   107,   132,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   123,   123,   145,    90,   368,   369,   370,
     155,    24,    25,    26,    27,    28,    29,   136,   168,   169,
     170,   172,   174,   176,   178,   180,   181,   182,   168,     7,
     217,   218,   219,     7,   245,   246,   247,     7,   268,   269,
     270,    62,    63,    64,    65,   183,   186,   187,   188,   189,
     190,   237,   334,     7,   193,   194,   195,    73,    74,    75,
      76,    77,    78,   207,   208,   209,   210,   211,   212,   213,
     214,    80,    81,    82,    83,   136,   170,   180,   344,   345,
     346,   347,   349,   350,    86,    87,   354,   355,   356,   358,
     129,   133,     4,   338,     7,   285,   286,   287,     7,   299,
     300,   301,    68,   330,     8,   371,     3,     8,     8,   173,
     175,   177,     4,     4,     4,     3,     8,     8,   220,     6,
       3,   248,     6,     3,   271,     6,     3,     3,     6,     3,
       6,   196,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   348,     4,     4,     4,     3,     8,   357,   359,
       3,     8,     8,   134,   107,   288,     6,     3,   302,     6,
       3,   331,     8,     4,   369,     4,     4,     4,   110,   108,
     110,   169,   223,   219,   251,   247,   274,   270,   187,   237,
     199,   195,   108,   108,   108,   108,   108,   108,   208,     4,
     108,   108,   108,   345,     4,     4,   355,     6,   291,   287,
     305,   301,     4,     5,   107,   107,   107,     8,     8,     8,
       8,   107,   107,   107,     8,     8,   107,     7,   372,   373,
     374,     3,     6,    91,    93,    94,   136,   178,   375,   376,
     377,   378,   380,   373,   381,     4,   379,     3,     8,     4,
     108,     4,   376,     5,   107,     7,   382,   383,   384,     3,
       6,    92,   385,   386,   383,   387,     3,     8,     4,   386,
     107
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   111,   113,   112,   114,   112,   115,   112,   116,   112,
     117,   112,   118,   112,   119,   112,   120,   112,   121,   112,
     122,   112,   123,   123,   123,   123,   123,   123,   123,   124,
     126,   125,   127,   128,   128,   129,   129,   131,   130,   133,
     132,   134,   134,   135,   135,   136,   138,   137,   139,   139,
     140,   140,   140,   140,   140,   142,   141,   144,   143,   145,
     145,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   147,   148,   149,   150,   151,   152,   154,
     153,   155,   155,   156,   156,   158,   157,   160,   159,   162,
     161,   163,   163,   165,   164,   167,   166,   168,   168,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   171,   170,
     173,   172,   175,   174,   177,   176,   179,   178,   180,   181,
     182,   183,   185,   184,   186,   186,   187,   187,   187,   187,
     188,   189,   190,   192,   191,   193,   193,   194,   194,   196,
     195,   198,   197,   199,   199,   199,   200,   200,   202,   201,
     204,   203,   206,   205,   207,   207,   208,   208,   208,   208,
     208,   208,   209,   210,   211,   212,   213,   214,   216,   215,
     217,   217,   218,   218,   220,   219,   222,   221,   223,   223,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     226,   225,   228,   227,   230,   229,   232,   231,   234,   233,
     236,   235,   238,   237,   240,   239,   241,   242,   244,   243,
     245,   245,   246,   246,   248,   247,   250,   249,   251,   251,
     252,   252,   253,   253,   253,   253,   253,   253,   253,   253,
     254,   255,   256,   257,   259,   258,   261,   260,   262,   264,
     263,   265,   267,   266,   268,   268,   269,   269,   271,   270,
     273,   272,   274,   274,   275,   275,   276,   276,   276,   276,
     276,   276,   277,   279,   278,   280,   281,   282,   284,   283,
     285,   285,   286,   286,   288,   287,   290,   289,   291,   291,
     292,   292,   292,   292,   294,   293,   296,   295,   298,   297,
     299,   299,   300,   300,   302,   301,   304,   303,   305,   305,
     306,   306,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   309,   308,   311,   310,   313,   312,
     315,   314,   317,   316,   319,   318,   321,   320,   323,   322,
     325,   324,   327,   326,   329,   328,   331,   330,   333,   332,
     334,   334,   335,   237,   336,   336,   337,   337,   338,   338,
     338,   338,   338,   338,   338,   339,   341,   340,   343,   342,
     344,   344,   345,   345,   345,   345,   345,   345,   345,   346,
     348,   347,   349,   350,   351,   353,   352,   354,   354,   355,
     355,   357,   356,   359,   358,   361,   360,   363,   362,   365,
     364,   367,   366,   368,   368,   369,   371,   370,   372,   372,
     374,   373,   375,   375,   376,   376,   376,   376,   376,   377,
     379,   378,   381,   380,   382,   382,   384,   383,   385,   385,
     387,   386
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     1,     3,     5,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     6,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       0,     4
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
  "\"array\"", "\"pools\"", "\"pool\"", "\"user-context\"", "\"subnet\"",
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
  "\"reservation-mode\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"duid\"", "\"hw-address\"", "\"circuit-id\"", "\"client-id\"",
  "\"hostname\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "value",
  "sub_json", "map2", "$@11", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@12", "list2", "$@13", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@14",
  "global_objects", "global_object", "dhcp4_object", "$@15", "sub_dhcp4",
  "$@16", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@17",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@18", "interfaces_list", "$@19", "dhcp_socket_type", "$@20",
  "socket_type", "lease_database", "$@21", "hosts_database", "$@22",
  "database_map_params", "database_map_param", "type", "$@23", "user",
  "$@24", "password", "$@25", "host", "$@26", "name", "$@27", "persist",
  "lfc_interval", "readonly", "duid_id", "host_reservation_identifiers",
  "$@28", "host_reservation_identifiers_list",
  "host_reservation_identifier", "hw_address_id", "circuit_id",
  "client_id", "hooks_libraries", "$@29", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@30",
  "sub_hooks_library", "$@31", "hooks_params", "hooks_param", "library",
  "$@32", "parameters", "$@33", "expired_leases_processing", "$@34",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@35",
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
  "pool_param", "pool_entry", "$@59", "user_context", "$@60",
  "reservations", "$@61", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@62", "sub_reservation",
  "$@63", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@64", "server_hostname", "$@65",
  "boot_file_name", "$@66", "ip_address", "$@67", "duid", "$@68",
  "hw_address", "$@69", "client_id_value", "$@70", "circuit_id_value",
  "$@71", "hostname", "$@72", "reservation_client_classes", "$@73",
  "relay", "$@74", "relay_map", "$@75", "client_classes", "$@76",
  "client_classes_list", "$@77", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@78", "server_id", "$@79",
  "server_id_params", "server_id_param", "htype", "identifier", "$@80",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@81",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@82", "control_socket_name", "$@83", "dhcp_ddns", "$@84",
  "dhcp6_json_object", "$@85", "dhcpddns_json_object", "$@86",
  "logging_object", "$@87", "logging_params", "logging_param", "loggers",
  "$@88", "loggers_entries", "logger_entry", "$@89", "logger_params",
  "logger_param", "debuglevel", "severity", "$@90", "output_options_list",
  "$@91", "output_options_list_content", "output_entry", "$@92",
  "output_params", "output_param", "$@93", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   209,   209,   209,   210,   210,   211,   211,   212,   212,
     213,   213,   214,   214,   215,   215,   216,   216,   217,   217,
     218,   218,   226,   227,   228,   229,   230,   231,   232,   235,
     240,   240,   251,   254,   255,   258,   262,   269,   269,   277,
     277,   284,   285,   288,   292,   303,   313,   313,   325,   326,
     330,   331,   332,   333,   334,   337,   337,   354,   354,   362,
     363,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   392,   397,   402,   407,   412,   417,   423,
     423,   433,   434,   437,   438,   441,   441,   449,   449,   459,
     459,   466,   467,   470,   470,   480,   480,   490,   491,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   505,   505,
     513,   513,   521,   521,   529,   529,   537,   537,   545,   550,
     555,   560,   565,   565,   575,   576,   579,   580,   581,   582,
     585,   590,   595,   600,   600,   610,   611,   614,   615,   618,
     618,   626,   626,   634,   635,   636,   639,   640,   643,   643,
     651,   651,   659,   659,   669,   670,   673,   674,   675,   676,
     677,   678,   681,   686,   691,   696,   701,   706,   714,   714,
     727,   728,   731,   732,   739,   739,   762,   762,   771,   772,
     776,   777,   778,   779,   780,   781,   782,   783,   784,   785,
     786,   787,   788,   789,   790,   791,   792,   793,   794,   795,
     798,   798,   806,   806,   814,   814,   822,   822,   830,   830,
     838,   838,   846,   846,   854,   854,   862,   867,   876,   876,
     888,   889,   892,   893,   898,   898,   909,   909,   919,   920,
     923,   924,   927,   928,   929,   930,   931,   932,   933,   934,
     937,   939,   944,   946,   948,   948,   956,   956,   964,   966,
     966,   974,   983,   983,   995,   996,  1001,  1002,  1007,  1007,
    1018,  1018,  1029,  1030,  1035,  1036,  1041,  1042,  1043,  1044,
    1045,  1046,  1049,  1051,  1051,  1059,  1061,  1063,  1071,  1071,
    1083,  1084,  1087,  1088,  1091,  1091,  1099,  1099,  1107,  1108,
    1111,  1112,  1113,  1114,  1117,  1117,  1125,  1125,  1135,  1135,
    1145,  1146,  1149,  1150,  1153,  1153,  1161,  1161,  1169,  1170,
    1173,  1174,  1178,  1179,  1180,  1181,  1182,  1183,  1184,  1185,
    1186,  1187,  1188,  1189,  1192,  1192,  1200,  1200,  1208,  1208,
    1216,  1216,  1224,  1224,  1232,  1232,  1240,  1240,  1248,  1248,
    1257,  1257,  1265,  1265,  1278,  1278,  1288,  1288,  1299,  1299,
    1309,  1310,  1313,  1313,  1321,  1322,  1325,  1326,  1329,  1330,
    1331,  1332,  1333,  1334,  1335,  1338,  1340,  1340,  1351,  1351,
    1361,  1362,  1365,  1366,  1367,  1368,  1369,  1370,  1371,  1374,
    1379,  1379,  1387,  1392,  1399,  1406,  1406,  1416,  1417,  1420,
    1421,  1424,  1424,  1432,  1432,  1442,  1442,  1454,  1454,  1461,
    1461,  1473,  1473,  1486,  1487,  1491,  1495,  1495,  1507,  1508,
    1512,  1512,  1520,  1521,  1524,  1525,  1526,  1527,  1528,  1531,
    1535,  1535,  1543,  1543,  1553,  1554,  1557,  1557,  1565,  1566,
    1569,  1569
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
#line 3625 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1577 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
