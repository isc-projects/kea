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
      case 114: // value
      case 161: // db_type
        value.move< ElementPtr > (that.value);
        break;

      case 101: // "boolean"
        value.move< bool > (that.value);
        break;

      case 100: // "floating point"
        value.move< double > (that.value);
        break;

      case 99: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 98: // "constant string"
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
      case 114: // value
      case 161: // db_type
        value.copy< ElementPtr > (that.value);
        break;

      case 101: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 100: // "floating point"
        value.copy< double > (that.value);
        break;

      case 99: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 98: // "constant string"
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
            case 98: // "constant string"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 99: // "integer"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 100: // "floating point"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 101: // "boolean"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 114: // value

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 161: // db_type

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 389 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 114: // value
      case 161: // db_type
        yylhs.value.build< ElementPtr > ();
        break;

      case 101: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 100: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 99: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 98: // "constant string"
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
#line 198 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 199 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 200 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 201 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 202 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 203 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 81:
#line 378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr type(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-socket-type", type);
    ctx.leave();
}
#line 1032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 498 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1277 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1368 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1504 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1602 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1641 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 845 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1721 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1787 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 992 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2061 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1221 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2274 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2515 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2525 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2529 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -399;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     183,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,    31,    18,    37,    47,    60,    62,    78,    94,    98,
     105,   113,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,    18,   -34,    16,   111,    30,    17,   -14,    23,
      61,     2,   -36,  -399,   159,   140,   195,   198,   204,  -399,
    -399,  -399,  -399,   206,  -399,    26,  -399,  -399,  -399,  -399,
    -399,  -399,   207,   208,  -399,  -399,  -399,   214,   215,   216,
     217,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   219,  -399,
    -399,  -399,    27,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,    58,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   220,   221,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,    73,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   146,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,   200,   223,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   224,  -399,
    -399,  -399,   226,  -399,  -399,   227,   228,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   233,  -399,
    -399,  -399,  -399,   230,   229,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,   148,  -399,  -399,  -399,  -399,    18,
      18,  -399,   129,   236,   237,   238,   240,  -399,    16,  -399,
     241,   153,   156,   251,   252,   257,   164,   166,   168,   169,
     265,   277,   278,   279,   280,   281,   282,   193,   283,   284,
     111,  -399,   285,   286,    30,  -399,    81,   287,   289,   290,
     291,   292,   293,   294,   201,   202,   295,   297,   298,   300,
      17,  -399,   301,   -14,  -399,   302,   303,   304,   305,   306,
     307,   308,   309,   310,  -399,    23,   311,   312,   218,   314,
     315,   316,   222,  -399,    61,   317,   225,  -399,     2,   318,
     320,     5,  -399,  -399,  -399,   321,   322,   323,    18,    18,
    -399,   324,  -399,  -399,   234,   326,   327,  -399,  -399,  -399,
    -399,   330,   331,   334,   335,   336,   337,   338,  -399,   339,
     340,  -399,   343,   245,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,   319,   325,  -399,  -399,  -399,   246,   253,   254,
     344,   255,   256,   259,  -399,  -399,   260,   261,   345,   355,
    -399,   266,  -399,   267,   268,   343,   269,   270,   271,   272,
     274,   275,  -399,   276,   288,  -399,   296,   299,   313,  -399,
    -399,   328,  -399,  -399,   329,    18,  -399,    18,   111,   332,
    -399,  -399,    30,  -399,   107,   107,   356,   368,   370,   137,
      51,   371,   333,    63,   -34,  -399,  -399,  -399,   375,  -399,
      81,  -399,  -399,  -399,   373,  -399,  -399,  -399,  -399,  -399,
     374,   342,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,   152,  -399,   154,  -399,  -399,   155,  -399,  -399,  -399,
    -399,   378,   380,   381,   384,  -399,   158,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,   170,  -399,   383,
     387,  -399,  -399,   385,   389,  -399,  -399,   390,   392,  -399,
    -399,  -399,  -399,  -399,    57,  -399,  -399,  -399,  -399,  -399,
    -399,   126,  -399,   393,   395,  -399,   396,   172,  -399,  -399,
    -399,   173,  -399,  -399,  -399,   180,    18,   341,  -399,  -399,
     397,   398,  -399,  -399,   399,   401,  -399,  -399,   394,  -399,
     402,   332,  -399,  -399,   403,   404,   405,   406,   346,   347,
     348,   349,   107,  -399,  -399,    17,  -399,   356,    61,  -399,
     368,     2,  -399,   370,   137,  -399,    51,  -399,   -36,  -399,
     371,   351,   333,  -399,   411,   413,    63,  -399,  -399,   412,
    -399,   -14,  -399,   373,    23,  -399,   374,   415,  -399,   388,
    -399,   191,   353,   354,   357,  -399,  -399,  -399,  -399,  -399,
     181,  -399,   414,  -399,   416,  -399,  -399,  -399,   188,  -399,
    -399,  -399,   358,   359,  -399,  -399,   189,  -399,   417,  -399,
     360,   421,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
     161,  -399,    10,   421,  -399,  -399,   419,  -399,  -399,  -399,
     190,  -399,  -399,  -399,  -399,  -399,   425,   361,   426,    10,
    -399,   427,  -399,   363,  -399,   428,  -399,  -399,   171,  -399,
     350,   428,  -399,  -399,   192,  -399,  -399,   430,   350,  -399,
     364,  -399,  -399
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    93,     9,
     177,    11,   288,    13,   305,    15,   227,    17,   262,    19,
     153,    21,    40,    32,     0,     0,     0,     0,     0,   307,
     229,   264,     0,    42,     0,    41,     0,     0,    33,    54,
     384,   380,   382,     0,    53,     0,    47,    49,    51,    52,
      50,    87,     0,     0,   323,    99,   101,     0,     0,     0,
       0,   169,   219,   254,   133,   347,   145,   164,     0,   368,
     378,    80,     0,    58,    60,    61,    62,    63,    77,    78,
      65,    66,    67,    68,    72,    73,    64,    70,    71,    79,
      69,    74,    75,    76,    95,    97,     0,    89,    91,    92,
     351,   203,   205,   207,   280,   201,   209,   211,     0,     0,
     215,   213,   297,   343,   200,   181,   182,   183,   195,     0,
     179,   186,   197,   198,   199,   187,   188,   191,   193,   189,
     190,   184,   185,   192,   196,   194,   295,   294,   293,     0,
     290,   292,   325,   327,   341,   331,   333,   337,   335,   339,
     329,   322,   318,     0,   308,   309,   319,   320,   321,   315,
     311,   316,   313,   314,   317,   312,   244,   127,     0,   248,
     246,   251,     0,   240,   241,     0,   230,   231,   233,   243,
     234,   235,   236,   250,   237,   238,   239,   275,     0,   273,
     274,   277,   278,     0,   265,   266,   268,   269,   270,   271,
     272,   160,   162,   157,     0,   155,   158,   159,    37,     0,
       0,    31,     0,     0,     0,     0,     0,    44,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,     0,     0,     0,    94,   353,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,     0,     0,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   306,     0,     0,     0,     0,     0,
       0,     0,     0,   228,     0,     0,     0,   263,     0,     0,
       0,     0,   154,    43,    34,     0,     0,     0,     0,     0,
      48,     0,    85,    86,     0,     0,     0,    81,    82,    83,
      84,     0,     0,     0,     0,     0,     0,     0,   367,     0,
       0,    59,     0,     0,    90,   365,   363,   364,   359,   360,
     361,   362,     0,   354,   355,   357,   358,     0,     0,     0,
       0,     0,     0,     0,   217,   218,     0,     0,     0,     0,
     180,     0,   291,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   310,     0,     0,   242,     0,     0,     0,   253,
     232,     0,   279,   267,     0,     0,   156,     0,     0,     0,
     381,   383,     0,   324,     0,     0,   171,   221,   256,     0,
       0,   147,     0,     0,     0,    38,    96,    98,     0,   352,
       0,   204,   206,   208,   282,   202,   210,   212,   216,   214,
     299,     0,   296,   326,   328,   342,   332,   334,   338,   336,
     340,   330,   245,   128,   249,   247,   252,   276,   161,   163,
      35,     0,   389,     0,   386,   388,     0,   115,   121,   123,
     125,     0,     0,     0,     0,   114,     0,   103,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,   175,     0,
     172,   173,   225,     0,   222,   223,   260,     0,   257,   258,
     141,   142,   143,   144,     0,   135,   137,   138,   139,   140,
     349,     0,   151,     0,   148,   149,     0,     0,   166,   374,
     376,     0,   370,   372,   373,     0,    40,     0,   356,   286,
       0,   283,   284,   303,     0,   300,   301,   345,     0,    55,
       0,     0,   385,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,   102,     0,   170,     0,   229,   220,
       0,   264,   255,     0,     0,   134,     0,   348,     0,   146,
       0,     0,     0,   165,     0,     0,     0,   369,   379,     0,
     366,     0,   281,     0,   307,   298,     0,     0,   344,     0,
     387,     0,     0,     0,     0,   129,   130,   131,   132,   104,
       0,   174,     0,   224,     0,   259,   136,   350,     0,   150,
     168,   167,     0,     0,   371,    39,     0,   285,     0,   302,
       0,     0,   117,   118,   119,   120,   116,   122,   124,   126,
     176,   226,   261,   152,   375,   377,   287,   304,   346,   393,
       0,   391,     0,     0,   390,   405,     0,   403,   401,   397,
       0,   395,   399,   400,   398,   392,     0,     0,     0,     0,
     394,     0,   402,     0,   396,     0,   404,   409,     0,   407,
       0,     0,   406,   413,     0,   411,   408,     0,     0,   410,
       0,   412,   414
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,     9,  -399,  -399,  -399,  -399,    -4,  -399,  -399,
      36,  -399,   -90,  -399,   -54,  -399,  -399,  -399,   194,  -399,
    -399,  -399,  -399,    29,   174,   -56,   -40,   -38,  -399,  -399,
     -37,  -399,  -399,    28,   167,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,    38,  -114,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,   -59,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -121,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -125,  -399,  -399,  -399,  -109,   133,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -108,  -399,  -399,
    -399,  -399,   -94,  -399,  -399,  -399,   -89,   175,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -398,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
     -93,  -399,  -399,  -399,   -88,  -399,   157,  -399,   -52,  -399,
    -399,  -399,  -399,  -399,   -48,  -399,  -399,  -399,  -399,  -399,
     -47,  -399,  -399,  -399,   -95,  -399,  -399,  -399,   -92,  -399,
     160,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -111,  -399,  -399,  -399,  -107,   182,  -399,  -399,  -399,
    -399,  -399,  -399,  -113,  -399,  -399,  -399,  -105,  -399,   176,
     -43,  -399,  -261,  -399,  -258,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
      46,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   -99,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,   -61,  -399,  -399,  -399,  -161,  -399,  -399,  -176,
    -399,  -399,  -399,  -399,  -399,  -399,  -187,  -399,  -399,  -193,
    -399
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,    67,    68,    33,    52,
     426,   526,    64,    65,   101,    35,    54,    75,    76,    77,
     243,    37,    55,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   250,   126,   127,    39,    56,   128,   272,   129,
     273,   111,   254,   112,   255,   476,   477,   478,   544,   626,
     479,   545,   480,   546,   481,   547,   204,   307,   483,   484,
     485,   486,   113,   263,   504,   505,   506,   507,   508,   509,
     114,   265,   513,   514,   515,   568,    51,    62,   234,   235,
     236,   319,   237,   320,   115,   266,   517,   518,   116,   260,
     489,   490,   491,   555,    41,    57,   149,   150,   151,   281,
     152,   277,   153,   278,   154,   279,   155,   282,   156,   283,
     157,   287,   158,   286,   159,   160,   117,   261,   493,   494,
     495,   558,    47,    60,   205,   206,   207,   208,   209,   210,
     211,   306,   212,   310,   213,   309,   214,   215,   311,   216,
     118,   262,   497,   498,   499,   561,    49,    61,   223,   224,
     225,   226,   227,   315,   228,   229,   230,   162,   280,   530,
     531,   532,   581,    43,    58,   169,   170,   171,   292,   163,
     288,   534,   535,   536,   584,    45,    59,   183,   184,   185,
     119,   253,   187,   295,   188,   296,   189,   303,   190,   298,
     191,   299,   192,   301,   193,   300,   194,   302,   195,   297,
     165,   289,   538,   587,   120,   264,   511,   276,   362,   363,
     364,   365,   366,   428,   121,   122,   268,   521,   522,   523,
     574,   524,   575,   123,   269,    78,   245,    79,   246,    80,
     244,   463,   464,   465,   540,   640,   641,   642,   650,   651,
     652,   653,   658,   654,   656,   668,   669,   670,   674,   675,
     677
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   145,   220,   144,   167,   181,   203,   219,   233,   221,
     161,   168,   182,   222,   164,   360,   186,   146,   361,   147,
     148,    30,   510,    23,   130,    24,    69,    25,    93,   248,
     270,    22,    83,    84,   249,   271,   231,   232,   166,    84,
     172,   173,   124,   125,    34,   197,   217,   198,   199,   218,
      87,    88,    89,   197,    36,   131,   132,   133,   130,    93,
     564,   274,    73,   565,    66,    93,   275,    38,   134,    40,
     135,   136,   137,   138,   139,   140,   290,   231,   232,   141,
     142,   291,   196,   174,    73,    42,   143,   175,   176,   177,
     178,   179,   645,   180,   646,   647,    70,    84,   172,   173,
      73,    44,    71,    72,   197,    46,   198,   199,    73,   200,
     201,   202,    48,   141,    73,    73,    26,    27,    28,    29,
      50,    73,    81,    93,   197,    82,    83,    84,   467,   566,
      85,    86,   567,   468,   469,   470,   471,   472,   473,   474,
     519,   520,   355,   239,    87,    88,    89,    90,    91,   293,
     197,   321,    92,    93,   294,   270,   322,   541,   274,    73,
     539,   552,   542,   543,   643,   238,   553,   644,   607,   360,
      94,    95,   361,   552,   671,   572,   576,   672,   554,    73,
     573,   577,    96,   242,   290,    97,    98,    99,   578,   630,
     100,   321,   293,   659,    74,   678,   633,   636,   660,   240,
     679,   500,   501,   502,   503,    73,   241,   242,   304,    73,
     247,   251,   252,   622,   623,   624,   625,   357,   256,   257,
     258,   259,   356,   267,   284,   285,   305,   325,   308,   358,
     312,   314,   318,   359,   145,   313,   144,   316,   317,   167,
     326,   327,   328,   161,   329,   331,   168,   164,   323,   324,
     146,   181,   147,   148,   332,   334,   335,   333,   182,   220,
     203,   336,   186,   337,   219,   338,   221,   339,   340,   341,
     222,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   342,   343,   344,   345,   346,   347,   349,   350,   352,
     353,   367,   348,   368,   369,   370,   371,   372,   373,   376,
     374,   377,   378,   375,   379,   381,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   393,   394,   395,   396,   397,
     398,   401,   404,   399,   405,   407,   402,   429,   430,   408,
     409,   412,   413,   414,   415,   416,   417,   410,   411,   418,
     419,   420,   421,   427,   431,   422,   423,   424,   425,   434,
     440,   432,   433,   435,   436,   482,   482,   437,   438,   439,
     475,   475,   441,   488,   442,   443,   444,   446,   447,   448,
     449,   357,   450,   451,   452,   492,   356,   496,   512,   527,
     529,   533,   548,   358,   549,   550,   453,   359,   551,   556,
     557,   559,   560,   621,   454,   563,   562,   455,   570,   569,
     571,   583,   588,   582,   586,   585,   589,   591,   592,   593,
     594,   456,   537,   462,   459,   612,   460,   613,   615,   620,
     525,   445,   631,   657,   632,   637,   457,   458,   639,   661,
     663,   516,   665,   673,   680,   667,   579,   461,   599,   580,
     466,   354,   330,   606,   351,   609,   596,   595,   598,   597,
     610,   627,   628,   487,   406,   629,   634,   635,   638,   608,
     662,   666,   682,   601,   611,   380,   600,   603,   605,   604,
     602,   400,   617,   619,   616,   382,   528,   614,   403,   618,
     590,   392,   655,   664,   676,   681,     0,     0,     0,     0,
       0,     0,     0,   482,     0,     0,     0,     0,   475,   145,
       0,   144,   220,     0,   203,     0,     0,   219,   161,   221,
       0,     0,   164,   222,   233,   146,     0,   147,   148,     0,
       0,     0,     0,     0,     0,     0,     0,   167,     0,     0,
     181,     0,     0,     0,   168,     0,     0,   182,     0,     0,
       0,   186,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   649,     0,     0,     0,     0,   648,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     649,     0,     0,     0,     0,   648
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,   276,    59,    57,   276,    57,
      57,    12,   420,     5,     7,     7,    10,     9,    42,     3,
       3,     0,    15,    16,     8,     8,    72,    73,    52,    16,
      17,    18,    12,    13,     7,    43,    44,    45,    46,    47,
      33,    34,    35,    43,     7,    38,    39,    40,     7,    42,
       3,     3,    98,     6,    98,    42,     8,     7,    51,     7,
      53,    54,    55,    56,    57,    58,     3,    72,    73,    62,
      63,     8,    21,    60,    98,     7,    69,    64,    65,    66,
      67,    68,    82,    70,    84,    85,    80,    16,    17,    18,
      98,     7,    86,    87,    43,     7,    45,    46,    98,    48,
      49,    50,     7,    62,    98,    98,    98,    99,   100,   101,
       7,    98,    11,    42,    43,    14,    15,    16,    21,     3,
      19,    20,     6,    26,    27,    28,    29,    30,    31,    32,
      77,    78,    61,     3,    33,    34,    35,    36,    37,     3,
      43,     3,    41,    42,     8,     3,     8,     3,     3,    98,
       8,     3,     8,     8,     3,     6,     8,     6,   566,   430,
      59,    60,   430,     3,     3,     3,     3,     6,     8,    98,
       8,     8,    71,     3,     3,    74,    75,    76,     8,     8,
      79,     3,     3,     3,   248,     3,     8,     8,     8,     4,
       8,    64,    65,    66,    67,    98,     8,     3,     8,    98,
       4,     4,     4,    22,    23,    24,    25,   276,     4,     4,
       4,     4,   276,     4,     4,     4,     3,    98,     4,   276,
       4,     3,     3,   276,   290,     8,   290,     4,     8,   293,
       4,     4,     4,   290,     4,     4,   293,   290,   239,   240,
     290,   305,   290,   290,   101,     4,     4,   101,   305,   318,
     314,     4,   305,    99,   318,    99,   318,    99,    99,     4,
     318,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,    99,     4,     4,     4,     4,     4,     4,     4,
      99,     4,     4,   101,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,    99,     4,     4,
       4,     4,     4,   101,     4,     4,   101,     8,     3,     7,
       7,     7,    98,     7,     7,     5,     5,   328,   329,     5,
       5,     5,     5,    98,    98,     7,     7,     7,     5,     5,
       5,    98,    98,    98,    98,   414,   415,    98,    98,    98,
     414,   415,     7,     7,    98,    98,    98,    98,    98,    98,
      98,   430,    98,    98,    98,     7,   430,     7,     7,     4,
       7,     7,     4,   430,     4,     4,    98,   430,     4,     6,
       3,     6,     3,     5,    98,     3,     6,    98,     3,     6,
       4,     3,     8,     6,     3,     6,     4,     4,     4,     4,
       4,    98,    70,    81,   405,     4,   407,     4,     6,     4,
     424,   385,     8,     4,     8,     8,    98,    98,     7,     4,
       4,    98,     5,    83,     4,     7,   526,   408,   552,    98,
     412,   274,   248,   564,   270,   570,    99,   101,    99,   101,
      99,    98,    98,   415,   321,    98,    98,    98,    98,   568,
      99,    98,    98,   557,   572,   290,   555,   560,   563,   561,
     558,   314,   583,   586,   581,   293,   430,   576,   318,   584,
     541,   305,   643,   659,   671,   678,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   552,    -1,    -1,    -1,    -1,   552,   555,
      -1,   555,   561,    -1,   558,    -1,    -1,   561,   555,   561,
      -1,    -1,   555,   561,   568,   555,    -1,   555,   555,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   581,    -1,    -1,
     584,    -1,    -1,    -1,   581,    -1,    -1,   584,    -1,    -1,
      -1,   584,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   642,    -1,    -1,    -1,    -1,   642,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     659,    -1,    -1,    -1,    -1,   659
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     0,     5,     7,     9,    98,    99,   100,   101,
     114,   115,   116,   120,     7,   127,     7,   133,     7,   147,
       7,   206,     7,   275,     7,   287,     7,   234,     7,   258,
       7,   188,   121,   117,   128,   134,   148,   207,   276,   288,
     235,   259,   189,   114,   124,   125,    98,   118,   119,    10,
      80,    86,    87,    98,   126,   129,   130,   131,   337,   339,
     341,    11,    14,    15,    16,    19,    20,    33,    34,    35,
      36,    37,    41,    42,    59,    60,    71,    74,    75,    76,
      79,   126,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   153,   155,   174,   182,   196,   200,   228,   252,   292,
     316,   326,   327,   335,    12,    13,   145,   146,   149,   151,
       7,    38,    39,    40,    51,    53,    54,    55,    56,    57,
      58,    62,    63,    69,   126,   137,   138,   139,   142,   208,
     209,   210,   212,   214,   216,   218,   220,   222,   224,   226,
     227,   252,   269,   281,   292,   312,    52,   126,   252,   277,
     278,   279,    17,    18,    60,    64,    65,    66,    67,    68,
      70,   126,   252,   289,   290,   291,   292,   294,   296,   298,
     300,   302,   304,   306,   308,   310,    21,    43,    45,    46,
      48,    49,    50,   126,   168,   236,   237,   238,   239,   240,
     241,   242,   244,   246,   248,   249,   251,    44,    47,   126,
     168,   240,   246,   260,   261,   262,   263,   264,   266,   267,
     268,    72,    73,   126,   190,   191,   192,   194,     6,     3,
       4,     8,     3,   132,   342,   338,   340,     4,     3,     8,
     144,     4,     4,   293,   154,   156,     4,     4,     4,     4,
     201,   229,   253,   175,   317,   183,   197,     4,   328,   336,
       3,     8,   150,   152,     3,     8,   319,   213,   215,   217,
     270,   211,   219,   221,     4,     4,   225,   223,   282,   313,
       3,     8,   280,     3,     8,   295,   297,   311,   301,   303,
     307,   305,   309,   299,     8,     3,   243,   169,     4,   247,
     245,   250,     4,     8,     3,   265,     4,     8,     3,   193,
     195,     3,     8,   114,   114,    98,     4,     4,     4,     4,
     130,     4,   101,   101,     4,     4,     4,    99,    99,    99,
      99,     4,     4,     4,     4,     4,     4,     4,    99,     4,
       4,   136,     4,     4,   146,    61,   126,   168,   252,   292,
     294,   296,   320,   321,   322,   323,   324,     4,     4,     4,
       4,     4,     4,     4,    99,   101,     4,     4,     4,     4,
     209,     4,   278,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   291,     4,     4,    99,     4,     4,     4,   101,
     238,     4,   101,   262,     4,     4,   191,     4,     7,     7,
     114,   114,     7,    98,     7,     7,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     5,   122,    98,   325,     8,
       3,    98,    98,    98,     5,    98,    98,    98,    98,    98,
       5,     7,    98,    98,    98,   122,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,   114,
     114,   135,    81,   343,   344,   345,   145,    21,    26,    27,
      28,    29,    30,    31,    32,   126,   157,   158,   159,   162,
     164,   166,   168,   170,   171,   172,   173,   157,     7,   202,
     203,   204,     7,   230,   231,   232,     7,   254,   255,   256,
      64,    65,    66,    67,   176,   177,   178,   179,   180,   181,
     222,   318,     7,   184,   185,   186,    98,   198,   199,    77,
      78,   329,   330,   331,   333,   119,   123,     4,   322,     7,
     271,   272,   273,     7,   283,   284,   285,    70,   314,     8,
     346,     3,     8,     8,   160,   163,   165,   167,     4,     4,
       4,     4,     3,     8,     8,   205,     6,     3,   233,     6,
       3,   257,     6,     3,     3,     6,     3,     6,   187,     6,
       3,     4,     3,     8,   332,   334,     3,     8,     8,   124,
      98,   274,     6,     3,   286,     6,     3,   315,     8,     4,
     344,     4,     4,     4,     4,   101,    99,   101,    99,   158,
     208,   204,   236,   232,   260,   256,   177,   222,   190,   186,
      99,   199,     4,     4,   330,     6,   277,   273,   289,   285,
       4,     5,    22,    23,    24,    25,   161,    98,    98,    98,
       8,     8,     8,     8,    98,    98,     8,     8,    98,     7,
     347,   348,   349,     3,     6,    82,    84,    85,   126,   168,
     350,   351,   352,   353,   355,   348,   356,     4,   354,     3,
       8,     4,    99,     4,   351,     5,    98,     7,   357,   358,
     359,     3,     6,    83,   360,   361,   358,   362,     3,     8,
       4,   361,    98
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   102,   104,   103,   105,   103,   106,   103,   107,   103,
     108,   103,   109,   103,   110,   103,   111,   103,   112,   103,
     113,   103,   114,   114,   114,   114,   114,   114,   114,   115,
     117,   116,   118,   118,   119,   119,   121,   120,   123,   122,
     124,   124,   125,   125,   126,   128,   127,   129,   129,   130,
     130,   130,   130,   130,   132,   131,   134,   133,   135,   135,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   137,   138,   139,   140,   141,   142,   144,   143,   145,
     145,   146,   146,   148,   147,   150,   149,   152,   151,   154,
     153,   156,   155,   157,   157,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   160,   159,   161,   161,   161,
     161,   163,   162,   165,   164,   167,   166,   169,   168,   170,
     171,   172,   173,   175,   174,   176,   176,   177,   177,   177,
     177,   178,   179,   180,   181,   183,   182,   184,   184,   185,
     185,   187,   186,   189,   188,   190,   190,   190,   191,   191,
     193,   192,   195,   194,   197,   196,   198,   198,   199,   201,
     200,   202,   202,   203,   203,   205,   204,   207,   206,   208,
     208,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   211,   210,   213,   212,   215,   214,   217,   216,   219,
     218,   221,   220,   223,   222,   225,   224,   226,   227,   229,
     228,   230,   230,   231,   231,   233,   232,   235,   234,   236,
     236,   237,   237,   238,   238,   238,   238,   238,   238,   238,
     238,   239,   240,   241,   243,   242,   245,   244,   247,   246,
     248,   250,   249,   251,   253,   252,   254,   254,   255,   255,
     257,   256,   259,   258,   260,   260,   261,   261,   262,   262,
     262,   262,   262,   262,   263,   265,   264,   266,   267,   268,
     270,   269,   271,   271,   272,   272,   274,   273,   276,   275,
     277,   277,   278,   278,   278,   280,   279,   282,   281,   283,
     283,   284,   284,   286,   285,   288,   287,   289,   289,   290,
     290,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   293,   292,   295,   294,   297,   296,   299,
     298,   301,   300,   303,   302,   305,   304,   307,   306,   309,
     308,   311,   310,   313,   312,   315,   314,   317,   316,   318,
     318,   319,   222,   320,   320,   321,   321,   322,   322,   322,
     322,   322,   322,   322,   323,   325,   324,   326,   328,   327,
     329,   329,   330,   330,   332,   331,   334,   333,   336,   335,
     338,   337,   340,   339,   342,   341,   343,   343,   344,   346,
     345,   347,   347,   349,   348,   350,   350,   351,   351,   351,
     351,   351,   352,   354,   353,   356,   355,   357,   357,   359,
     358,   360,   360,   362,   361
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
       1,     3,     3,     3,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       1,     3,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"echo-client-id\"", "\"match-client-id\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"pools\"", "\"pool\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"dhcp4o6-port\"",
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
  "$@18", "interfaces_list", "$@19", "dhcp_socket_type", "$@20",
  "lease_database", "$@21", "hosts_database", "$@22",
  "database_map_params", "database_map_param", "database_type", "$@23",
  "db_type", "user", "$@24", "password", "$@25", "host", "$@26", "name",
  "$@27", "persist", "lfc_interval", "readonly", "connect_timeout",
  "host_reservation_identifiers", "$@28",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "hooks_libraries",
  "$@29", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@30", "sub_hooks_library", "$@31", "hooks_params",
  "hooks_param", "library", "$@32", "parameters", "$@33",
  "expired_leases_processing", "$@34", "expired_leases_params",
  "expired_leases_param", "subnet4_list", "$@35", "subnet4_list_content",
  "not_empty_subnet4_list", "subnet4", "$@36", "sub_subnet4", "$@37",
  "subnet4_params", "subnet4_param", "subnet", "$@38",
  "subnet_4o6_interface", "$@39", "subnet_4o6_interface_id", "$@40",
  "subnet_4o6_subnet", "$@41", "interface", "$@42", "interface_id", "$@43",
  "client_class", "$@44", "reservation_mode", "$@45", "id", "rapid_commit",
  "option_def_list", "$@46", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@47",
  "sub_option_def", "$@48", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@49",
  "option_def_record_types", "$@50", "space", "$@51", "option_def_space",
  "option_def_encapsulate", "$@52", "option_def_array", "option_data_list",
  "$@53", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@54", "sub_option_data", "$@55",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@56",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@57", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@58", "sub_pool4", "$@59", "pool_params",
  "pool_param", "pool_entry", "$@60", "reservations", "$@61",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@62", "sub_reservation", "$@63", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@64", "server_hostname", "$@65", "boot_file_name", "$@66",
  "ip_address", "$@67", "duid", "$@68", "hw_address", "$@69",
  "client_id_value", "$@70", "circuit_id_value", "$@71", "hostname",
  "$@72", "reservation_client_classes", "$@73", "relay", "$@74",
  "relay_map", "$@75", "client_classes", "$@76", "client_classes_list",
  "$@77", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@78",
  "dhcp4o6_port", "control_socket", "$@79", "control_socket_params",
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
       0,   198,   198,   198,   199,   199,   200,   200,   201,   201,
     202,   202,   203,   203,   204,   204,   205,   205,   206,   206,
     207,   207,   215,   216,   217,   218,   219,   220,   221,   224,
     229,   229,   241,   242,   245,   249,   256,   256,   264,   264,
     271,   272,   275,   279,   290,   300,   300,   312,   313,   317,
     318,   319,   320,   321,   324,   324,   341,   341,   349,   350,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   378,   383,   388,   393,   398,   403,   409,   409,   419,
     420,   423,   424,   427,   427,   435,   435,   445,   445,   453,
     453,   463,   463,   473,   474,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   489,   489,   496,   497,   498,
     499,   502,   502,   510,   510,   518,   518,   526,   526,   534,
     539,   544,   549,   554,   554,   564,   565,   568,   569,   570,
     571,   574,   579,   584,   589,   594,   594,   604,   605,   608,
     609,   612,   612,   620,   620,   628,   629,   630,   633,   634,
     637,   637,   645,   645,   653,   653,   663,   664,   670,   678,
     678,   691,   692,   695,   696,   703,   703,   726,   726,   735,
     736,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,   750,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   762,   762,   770,   770,   778,   778,   786,   786,   794,
     794,   802,   802,   810,   810,   818,   818,   826,   831,   840,
     840,   852,   853,   856,   857,   862,   862,   873,   873,   883,
     884,   887,   888,   891,   892,   893,   894,   895,   896,   897,
     898,   901,   903,   908,   910,   910,   918,   918,   926,   926,
     934,   936,   936,   944,   953,   953,   965,   966,   971,   972,
     977,   977,   988,   988,   999,  1000,  1005,  1006,  1011,  1012,
    1013,  1014,  1015,  1016,  1019,  1021,  1021,  1029,  1031,  1033,
    1041,  1041,  1053,  1054,  1057,  1058,  1061,  1061,  1069,  1069,
    1077,  1078,  1081,  1082,  1083,  1086,  1086,  1097,  1097,  1107,
    1108,  1111,  1112,  1115,  1115,  1123,  1123,  1131,  1132,  1135,
    1136,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,
    1149,  1150,  1151,  1154,  1154,  1162,  1162,  1170,  1170,  1178,
    1178,  1186,  1186,  1194,  1194,  1202,  1202,  1210,  1210,  1219,
    1219,  1227,  1227,  1240,  1240,  1250,  1250,  1261,  1261,  1271,
    1272,  1275,  1275,  1283,  1284,  1287,  1288,  1291,  1292,  1293,
    1294,  1295,  1296,  1297,  1300,  1302,  1302,  1314,  1321,  1321,
    1331,  1332,  1335,  1336,  1339,  1339,  1347,  1347,  1357,  1357,
    1369,  1369,  1376,  1376,  1388,  1388,  1401,  1402,  1406,  1410,
    1410,  1422,  1423,  1427,  1427,  1435,  1436,  1439,  1440,  1441,
    1442,  1443,  1446,  1450,  1450,  1458,  1458,  1468,  1469,  1472,
    1472,  1480,  1481,  1484,  1484
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
#line 3476 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1492 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
