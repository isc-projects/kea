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
      case 113: // value
      case 160: // db_type
        value.move< ElementPtr > (that.value);
        break;

      case 100: // "boolean"
        value.move< bool > (that.value);
        break;

      case 99: // "floating point"
        value.move< double > (that.value);
        break;

      case 98: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 97: // "constant string"
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
      case 113: // value
      case 160: // db_type
        value.copy< ElementPtr > (that.value);
        break;

      case 100: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 99: // "floating point"
        value.copy< double > (that.value);
        break;

      case 98: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 97: // "constant string"
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
            case 97: // "constant string"

#line 188 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 98: // "integer"

#line 188 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 99: // "floating point"

#line 188 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 100: // "boolean"

#line 188 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 113: // value

#line 188 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 160: // db_type

#line 188 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 113: // value
      case 160: // db_type
        yylhs.value.build< ElementPtr > ();
        break;

      case 100: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 99: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 98: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 97: // "constant string"
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
#line 197 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 198 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 199 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 200 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 201 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 202 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 203 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 214 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 323 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 330 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 81:
#line 377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr type(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-socket-type", type);
    ctx.leave();
}
#line 1032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1345 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1635 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1707 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1715 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1743 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1751 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 986 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1864 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2156 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2165 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2193 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2493 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2501 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2519 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2523 "dhcp4_parser.cc" // lalr1.cc:859
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
     108,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,    30,    18,    40,    52,    59,    70,    91,    99,   112,
     130,   138,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,    18,   -60,    16,    89,   202,    17,   -13,    23,
     129,     0,   -36,  -399,   160,   146,   205,   173,   213,  -399,
    -399,  -399,  -399,   219,  -399,    45,  -399,  -399,  -399,  -399,
    -399,  -399,   220,   221,  -399,  -399,  -399,   223,   224,   226,
     227,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   228,  -399,
    -399,  -399,    54,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,    57,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   231,   233,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,    60,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,    72,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,   230,   237,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   238,  -399,
    -399,  -399,   240,  -399,  -399,   246,   242,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   251,  -399,
    -399,  -399,  -399,   248,   254,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,    73,  -399,  -399,  -399,  -399,    18,
      18,  -399,   164,   259,   261,   263,   264,  -399,    16,  -399,
     265,   141,   171,   268,   269,   270,   178,   181,   182,   183,
     271,   273,   274,   278,   279,   280,   281,   188,   283,   284,
      89,  -399,   285,   286,   202,  -399,    94,   287,   288,   289,
     290,   291,   292,   293,   200,   199,   296,   297,   298,   299,
      17,  -399,   300,   -13,  -399,   301,   302,   303,   304,   305,
     306,   307,   308,   309,  -399,    23,   310,   311,   218,   313,
     314,   315,   222,  -399,   129,   316,   225,  -399,     0,   317,
     319,   147,  -399,  -399,  -399,   320,   321,   322,    18,    18,
    -399,   323,  -399,  -399,   229,   324,   325,  -399,  -399,  -399,
    -399,   328,   329,   330,   331,   334,   335,   336,  -399,   337,
     338,  -399,   341,   244,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,   339,   345,  -399,  -399,  -399,   245,   252,   253,
     346,   255,   256,   257,  -399,  -399,   260,   262,   353,   355,
    -399,   266,  -399,   267,   272,   341,   275,   276,   277,   282,
     294,   295,  -399,   312,   318,  -399,   326,   327,   332,  -399,
    -399,   333,  -399,  -399,   340,    18,  -399,    18,    89,   247,
    -399,  -399,   202,  -399,   113,   113,   358,   359,   360,   142,
      22,   361,   342,   144,   -60,  -399,  -399,  -399,   366,  -399,
      94,  -399,  -399,  -399,   368,  -399,  -399,  -399,  -399,  -399,
     370,   343,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,   123,  -399,   124,  -399,  -399,   125,  -399,  -399,  -399,
    -399,   374,   376,   377,   378,  -399,   143,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,   149,  -399,   379,
     381,  -399,  -399,   380,   385,  -399,  -399,   383,   387,  -399,
    -399,  -399,  -399,  -399,    28,  -399,  -399,  -399,  -399,  -399,
    -399,    93,  -399,   388,   390,  -399,   391,   150,  -399,  -399,
    -399,   153,  -399,  -399,  -399,   157,    18,   344,  -399,  -399,
     392,   393,  -399,  -399,   394,   396,  -399,  -399,   389,  -399,
     397,   247,  -399,  -399,   398,   399,   400,   401,   347,   348,
     349,   350,   113,  -399,  -399,    17,  -399,   358,   129,  -399,
     359,     0,  -399,   360,   142,  -399,    22,  -399,   -36,  -399,
     361,   352,   342,  -399,   402,   403,   144,  -399,  -399,   404,
    -399,   -13,  -399,   368,    23,  -399,   370,   407,  -399,   408,
    -399,   189,   354,   356,   357,  -399,  -399,  -399,  -399,  -399,
     167,  -399,   409,  -399,   410,  -399,  -399,  -399,   176,  -399,
    -399,  -399,   362,   363,  -399,  -399,   177,  -399,   411,  -399,
     364,   413,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   186,
    -399,    10,   413,  -399,  -399,   417,  -399,  -399,  -399,   179,
    -399,  -399,  -399,  -399,  -399,   418,   365,   421,    10,  -399,
     422,  -399,   367,  -399,   419,  -399,  -399,   187,  -399,   351,
     419,  -399,  -399,   180,  -399,  -399,   424,   351,  -399,   369,
    -399,  -399
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    93,     9,
     176,    11,   287,    13,   304,    15,   226,    17,   261,    19,
     152,    21,    40,    32,     0,     0,     0,     0,     0,   306,
     228,   263,     0,    42,     0,    41,     0,     0,    33,    54,
     383,   379,   381,     0,    53,     0,    47,    49,    51,    52,
      50,    87,     0,     0,   322,    99,   101,     0,     0,     0,
       0,   168,   218,   253,   132,   346,   144,   163,     0,   367,
     377,    80,     0,    58,    60,    61,    62,    63,    77,    78,
      65,    66,    67,    68,    72,    73,    64,    70,    71,    79,
      69,    74,    75,    76,    95,    97,     0,    89,    91,    92,
     350,   202,   204,   206,   279,   200,   208,   210,     0,     0,
     214,   212,   296,   342,   199,   180,   181,   182,   194,     0,
     178,   185,   196,   197,   198,   186,   187,   190,   192,   188,
     189,   183,   184,   191,   195,   193,   294,   293,   292,     0,
     289,   291,   324,   326,   340,   330,   332,   336,   334,   338,
     328,   321,   317,     0,   307,   308,   318,   319,   320,   314,
     310,   315,   312,   313,   316,   311,   243,   126,     0,   247,
     245,   250,     0,   239,   240,     0,   229,   230,   232,   242,
     233,   234,   235,   249,   236,   237,   238,   274,     0,   272,
     273,   276,   277,     0,   264,   265,   267,   268,   269,   270,
     271,   159,   161,   156,     0,   154,   157,   158,    37,     0,
       0,    31,     0,     0,     0,     0,     0,    44,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,     0,     0,     0,    94,   352,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   177,     0,     0,   288,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   305,     0,     0,     0,     0,     0,
       0,     0,     0,   227,     0,     0,     0,   262,     0,     0,
       0,     0,   153,    43,    34,     0,     0,     0,     0,     0,
      48,     0,    85,    86,     0,     0,     0,    81,    82,    83,
      84,     0,     0,     0,     0,     0,     0,     0,   366,     0,
       0,    59,     0,     0,    90,   364,   362,   363,   358,   359,
     360,   361,     0,   353,   354,   356,   357,     0,     0,     0,
       0,     0,     0,     0,   216,   217,     0,     0,     0,     0,
     179,     0,   290,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   309,     0,     0,   241,     0,     0,     0,   252,
     231,     0,   278,   266,     0,     0,   155,     0,     0,     0,
     380,   382,     0,   323,     0,     0,   170,   220,   255,     0,
       0,   146,     0,     0,     0,    38,    96,    98,     0,   351,
       0,   203,   205,   207,   281,   201,   209,   211,   215,   213,
     298,     0,   295,   325,   327,   341,   331,   333,   337,   335,
     339,   329,   244,   127,   248,   246,   251,   275,   160,   162,
      35,     0,   388,     0,   385,   387,     0,   115,   120,   122,
     124,     0,     0,     0,     0,   114,     0,   103,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,   174,     0,
     171,   172,   224,     0,   221,   222,   259,     0,   256,   257,
     140,   141,   142,   143,     0,   134,   136,   137,   138,   139,
     348,     0,   150,     0,   147,   148,     0,     0,   165,   373,
     375,     0,   369,   371,   372,     0,    40,     0,   355,   285,
       0,   282,   283,   302,     0,   299,   300,   344,     0,    55,
       0,     0,   384,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,   102,     0,   169,     0,   228,   219,
       0,   263,   254,     0,     0,   133,     0,   347,     0,   145,
       0,     0,     0,   164,     0,     0,     0,   368,   378,     0,
     365,     0,   280,     0,   306,   297,     0,     0,   343,     0,
     386,     0,     0,     0,     0,   128,   129,   130,   131,   104,
       0,   173,     0,   223,     0,   258,   135,   349,     0,   149,
     167,   166,     0,     0,   370,    39,     0,   284,     0,   301,
       0,     0,   117,   118,   119,   116,   121,   123,   125,   175,
     225,   260,   151,   374,   376,   286,   303,   345,   392,     0,
     390,     0,     0,   389,   404,     0,   402,   400,   396,     0,
     394,   398,   399,   397,   391,     0,     0,     0,     0,   393,
       0,   401,     0,   395,     0,   403,   408,     0,   406,     0,
       0,   405,   412,     0,   410,   407,     0,     0,   409,     0,
     411,   413
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,     9,  -399,  -399,  -399,  -399,   -16,  -399,  -399,
      46,  -399,   -94,  -399,   -54,  -399,  -399,  -399,   190,  -399,
    -399,  -399,  -399,    26,   165,   -56,   -40,   -38,  -399,  -399,
     -37,  -399,  -399,    24,   166,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,    27,  -109,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,   -59,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -120,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -125,  -399,  -399,  -399,  -116,   134,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -115,  -399,  -399,
    -399,  -399,  -101,  -399,  -399,  -399,   -97,   172,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -398,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
     -95,  -399,  -399,  -399,   -91,  -399,   154,  -399,   -52,  -399,
    -399,  -399,  -399,  -399,   -48,  -399,  -399,  -399,  -399,  -399,
     -47,  -399,  -399,  -399,   -93,  -399,  -399,  -399,   -92,  -399,
     155,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -112,  -399,  -399,  -399,  -107,   184,  -399,  -399,  -399,
    -399,  -399,  -399,  -114,  -399,  -399,  -399,  -108,  -399,   170,
     -43,  -399,  -261,  -399,  -258,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
      48,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   -96,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,   -62,  -399,  -399,  -399,  -161,  -399,  -399,  -176,
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
     273,   111,   254,   112,   255,   476,   477,   478,   544,   625,
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
     244,   463,   464,   465,   540,   639,   640,   641,   649,   650,
     651,   652,   657,   653,   655,   667,   668,   669,   673,   674,
     676
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   145,   220,   144,   167,   181,   203,   219,   233,   221,
     161,   168,   182,   222,   164,   360,   186,   146,   361,   147,
     148,    30,   510,    23,   130,    24,    69,    25,    93,   130,
      22,   564,    83,    84,   565,   231,   232,    66,   166,    84,
     172,   173,   197,   217,   198,   199,   218,    34,   248,    87,
      88,    89,   197,   249,   131,   132,   133,   270,    93,    36,
     274,    73,   271,   290,    93,   275,    38,   134,   291,   135,
     136,   137,   138,   139,   140,   293,   321,    40,   141,   142,
     294,   322,   174,   141,    73,   143,   175,   176,   177,   178,
     179,   644,   180,   645,   646,    70,   566,    73,    42,   567,
      81,    71,    72,    82,    83,    84,    44,    73,    85,    86,
      84,   172,   173,    73,    73,    26,    27,    28,    29,    46,
      73,    87,    88,    89,    90,    91,   270,   541,   274,    92,
      93,   539,   542,   543,   467,    93,   197,    48,   468,   469,
     470,   471,   472,   473,   474,    50,   552,    94,    95,   239,
     196,   553,   552,   572,   355,   197,   576,   554,   573,    96,
     242,   577,    97,    98,    99,   578,   238,   100,   607,   360,
     290,   197,   361,   198,   199,   629,   200,   201,   202,   321,
     293,   241,   658,   677,   632,   635,    73,   659,   678,   642,
     670,    73,   643,   671,    74,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,   500,   501,   502,   503,   240,
      73,   622,   623,   624,   124,   125,   242,   357,   231,   232,
     519,   520,   356,   247,   251,   252,    73,   256,   257,   358,
     258,   259,   267,   359,   145,   284,   144,   285,   304,   167,
     305,   332,   308,   161,   312,   314,   168,   164,   323,   324,
     146,   181,   147,   148,   313,   316,   317,   318,   182,   220,
     203,   325,   186,   326,   219,   327,   221,   328,   329,   331,
     222,   333,   334,   335,   336,   341,   337,   342,   343,   338,
     339,   340,   344,   345,   346,   347,   348,   349,   350,   352,
     353,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   381,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   393,   394,   395,   396,   397,   398,
     401,   404,   399,   405,   407,   402,   413,   462,   408,   409,
     412,   414,   415,   416,   417,   418,   419,   410,   411,   420,
     421,   427,   431,   422,   423,   424,   425,   429,   430,   432,
     433,   434,   435,   436,   437,   482,   482,   438,   440,   439,
     475,   475,   441,   442,   443,   488,   492,   496,   512,   444,
     527,   357,   446,   447,   448,   529,   356,   533,   548,   449,
     549,   550,   551,   358,   557,   556,   559,   359,   560,   562,
     563,   450,   451,   570,   569,   571,   583,   588,   582,   586,
     585,   589,   591,   592,   593,   594,   612,   613,   525,   452,
     615,   620,   537,   621,   459,   453,   460,   630,   631,   636,
     638,   656,   660,   454,   455,   662,   666,   664,   679,   456,
     457,   445,   579,   672,   461,   351,   466,   458,   330,   516,
     354,   580,   487,   599,   606,   609,   596,   595,   598,   597,
     610,   626,   608,   627,   628,   406,   601,   611,   600,   633,
     634,   637,   380,   661,   665,   603,   681,   602,   400,   604,
     605,   617,   619,   403,   616,   392,   618,   382,   528,   590,
     614,   654,   663,   675,   680,     0,     0,     0,     0,     0,
       0,     0,     0,   482,     0,     0,     0,     0,   475,   145,
       0,   144,   220,     0,   203,     0,     0,   219,   161,   221,
       0,     0,   164,   222,   233,   146,     0,   147,   148,     0,
       0,     0,     0,     0,     0,     0,     0,   167,     0,     0,
     181,     0,     0,     0,   168,     0,     0,   182,     0,     0,
       0,   186,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   648,     0,     0,     0,     0,   647,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   648,
       0,     0,     0,     0,   647
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,   276,    59,    57,   276,    57,
      57,    12,   420,     5,     7,     7,    10,     9,    41,     7,
       0,     3,    15,    16,     6,    71,    72,    97,    51,    16,
      17,    18,    42,    43,    44,    45,    46,     7,     3,    32,
      33,    34,    42,     8,    37,    38,    39,     3,    41,     7,
       3,    97,     8,     3,    41,     8,     7,    50,     8,    52,
      53,    54,    55,    56,    57,     3,     3,     7,    61,    62,
       8,     8,    59,    61,    97,    68,    63,    64,    65,    66,
      67,    81,    69,    83,    84,    79,     3,    97,     7,     6,
      11,    85,    86,    14,    15,    16,     7,    97,    19,    20,
      16,    17,    18,    97,    97,    97,    98,    99,   100,     7,
      97,    32,    33,    34,    35,    36,     3,     3,     3,    40,
      41,     8,     8,     8,    21,    41,    42,     7,    25,    26,
      27,    28,    29,    30,    31,     7,     3,    58,    59,     3,
      21,     8,     3,     3,    60,    42,     3,     8,     8,    70,
       3,     8,    73,    74,    75,     8,     6,    78,   566,   430,
       3,    42,   430,    44,    45,     8,    47,    48,    49,     3,
       3,     8,     3,     3,     8,     8,    97,     8,     8,     3,
       3,    97,     6,     6,   248,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    63,    64,    65,    66,     4,
      97,    22,    23,    24,    12,    13,     3,   276,    71,    72,
      76,    77,   276,     4,     4,     4,    97,     4,     4,   276,
       4,     4,     4,   276,   290,     4,   290,     4,     8,   293,
       3,   100,     4,   290,     4,     3,   293,   290,   239,   240,
     290,   305,   290,   290,     8,     4,     8,     3,   305,   318,
     314,    97,   305,     4,   318,     4,   318,     4,     4,     4,
     318,   100,     4,     4,     4,     4,    98,     4,     4,    98,
      98,    98,     4,     4,     4,     4,    98,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,    98,   100,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    98,     4,     4,     4,
       4,     4,   100,     4,     4,   100,    97,    80,     7,     7,
       7,     7,     7,     5,     5,     5,     5,   328,   329,     5,
       5,    97,    97,     7,     7,     7,     5,     8,     3,    97,
      97,     5,    97,    97,    97,   414,   415,    97,     5,    97,
     414,   415,     7,    97,    97,     7,     7,     7,     7,    97,
       4,   430,    97,    97,    97,     7,   430,     7,     4,    97,
       4,     4,     4,   430,     3,     6,     6,   430,     3,     6,
       3,    97,    97,     3,     6,     4,     3,     8,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     4,   424,    97,
       6,     4,    69,     5,   405,    97,   407,     8,     8,     8,
       7,     4,     4,    97,    97,     4,     7,     5,     4,    97,
      97,   385,   526,    82,   408,   270,   412,    97,   248,    97,
     274,    97,   415,   552,   564,   570,    98,   100,    98,   100,
      98,    97,   568,    97,    97,   321,   557,   572,   555,    97,
      97,    97,   290,    98,    97,   560,    97,   558,   314,   561,
     563,   583,   586,   318,   581,   305,   584,   293,   430,   541,
     576,   642,   658,   670,   677,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   552,    -1,    -1,    -1,    -1,   552,   555,
      -1,   555,   561,    -1,   558,    -1,    -1,   561,   555,   561,
      -1,    -1,   555,   561,   568,   555,    -1,   555,   555,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   581,    -1,    -1,
     584,    -1,    -1,    -1,   581,    -1,    -1,   584,    -1,    -1,
      -1,   584,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   641,    -1,    -1,    -1,    -1,   641,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   658,
      -1,    -1,    -1,    -1,   658
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,     0,     5,     7,     9,    97,    98,    99,   100,
     113,   114,   115,   119,     7,   126,     7,   132,     7,   146,
       7,   205,     7,   274,     7,   286,     7,   233,     7,   257,
       7,   187,   120,   116,   127,   133,   147,   206,   275,   287,
     234,   258,   188,   113,   123,   124,    97,   117,   118,    10,
      79,    85,    86,    97,   125,   128,   129,   130,   336,   338,
     340,    11,    14,    15,    16,    19,    20,    32,    33,    34,
      35,    36,    40,    41,    58,    59,    70,    73,    74,    75,
      78,   125,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   152,   154,   173,   181,   195,   199,   227,   251,   291,
     315,   325,   326,   334,    12,    13,   144,   145,   148,   150,
       7,    37,    38,    39,    50,    52,    53,    54,    55,    56,
      57,    61,    62,    68,   125,   136,   137,   138,   141,   207,
     208,   209,   211,   213,   215,   217,   219,   221,   223,   225,
     226,   251,   268,   280,   291,   311,    51,   125,   251,   276,
     277,   278,    17,    18,    59,    63,    64,    65,    66,    67,
      69,   125,   251,   288,   289,   290,   291,   293,   295,   297,
     299,   301,   303,   305,   307,   309,    21,    42,    44,    45,
      47,    48,    49,   125,   167,   235,   236,   237,   238,   239,
     240,   241,   243,   245,   247,   248,   250,    43,    46,   125,
     167,   239,   245,   259,   260,   261,   262,   263,   265,   266,
     267,    71,    72,   125,   189,   190,   191,   193,     6,     3,
       4,     8,     3,   131,   341,   337,   339,     4,     3,     8,
     143,     4,     4,   292,   153,   155,     4,     4,     4,     4,
     200,   228,   252,   174,   316,   182,   196,     4,   327,   335,
       3,     8,   149,   151,     3,     8,   318,   212,   214,   216,
     269,   210,   218,   220,     4,     4,   224,   222,   281,   312,
       3,     8,   279,     3,     8,   294,   296,   310,   300,   302,
     306,   304,   308,   298,     8,     3,   242,   168,     4,   246,
     244,   249,     4,     8,     3,   264,     4,     8,     3,   192,
     194,     3,     8,   113,   113,    97,     4,     4,     4,     4,
     129,     4,   100,   100,     4,     4,     4,    98,    98,    98,
      98,     4,     4,     4,     4,     4,     4,     4,    98,     4,
       4,   135,     4,     4,   145,    60,   125,   167,   251,   291,
     293,   295,   319,   320,   321,   322,   323,     4,     4,     4,
       4,     4,     4,     4,    98,   100,     4,     4,     4,     4,
     208,     4,   277,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   290,     4,     4,    98,     4,     4,     4,   100,
     237,     4,   100,   261,     4,     4,   190,     4,     7,     7,
     113,   113,     7,    97,     7,     7,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     5,   121,    97,   324,     8,
       3,    97,    97,    97,     5,    97,    97,    97,    97,    97,
       5,     7,    97,    97,    97,   121,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,   113,
     113,   134,    80,   342,   343,   344,   144,    21,    25,    26,
      27,    28,    29,    30,    31,   125,   156,   157,   158,   161,
     163,   165,   167,   169,   170,   171,   172,   156,     7,   201,
     202,   203,     7,   229,   230,   231,     7,   253,   254,   255,
      63,    64,    65,    66,   175,   176,   177,   178,   179,   180,
     221,   317,     7,   183,   184,   185,    97,   197,   198,    76,
      77,   328,   329,   330,   332,   118,   122,     4,   321,     7,
     270,   271,   272,     7,   282,   283,   284,    69,   313,     8,
     345,     3,     8,     8,   159,   162,   164,   166,     4,     4,
       4,     4,     3,     8,     8,   204,     6,     3,   232,     6,
       3,   256,     6,     3,     3,     6,     3,     6,   186,     6,
       3,     4,     3,     8,   331,   333,     3,     8,     8,   123,
      97,   273,     6,     3,   285,     6,     3,   314,     8,     4,
     343,     4,     4,     4,     4,   100,    98,   100,    98,   157,
     207,   203,   235,   231,   259,   255,   176,   221,   189,   185,
      98,   198,     4,     4,   329,     6,   276,   272,   288,   284,
       4,     5,    22,    23,    24,   160,    97,    97,    97,     8,
       8,     8,     8,    97,    97,     8,     8,    97,     7,   346,
     347,   348,     3,     6,    81,    83,    84,   125,   167,   349,
     350,   351,   352,   354,   347,   355,     4,   353,     3,     8,
       4,    98,     4,   350,     5,    97,     7,   356,   357,   358,
       3,     6,    82,   359,   360,   357,   361,     3,     8,     4,
     360,    97
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   101,   103,   102,   104,   102,   105,   102,   106,   102,
     107,   102,   108,   102,   109,   102,   110,   102,   111,   102,
     112,   102,   113,   113,   113,   113,   113,   113,   113,   114,
     116,   115,   117,   117,   118,   118,   120,   119,   122,   121,
     123,   123,   124,   124,   125,   127,   126,   128,   128,   129,
     129,   129,   129,   129,   131,   130,   133,   132,   134,   134,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   136,   137,   138,   139,   140,   141,   143,   142,   144,
     144,   145,   145,   147,   146,   149,   148,   151,   150,   153,
     152,   155,   154,   156,   156,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   159,   158,   160,   160,   160,
     162,   161,   164,   163,   166,   165,   168,   167,   169,   170,
     171,   172,   174,   173,   175,   175,   176,   176,   176,   176,
     177,   178,   179,   180,   182,   181,   183,   183,   184,   184,
     186,   185,   188,   187,   189,   189,   189,   190,   190,   192,
     191,   194,   193,   196,   195,   197,   197,   198,   200,   199,
     201,   201,   202,   202,   204,   203,   206,   205,   207,   207,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     210,   209,   212,   211,   214,   213,   216,   215,   218,   217,
     220,   219,   222,   221,   224,   223,   225,   226,   228,   227,
     229,   229,   230,   230,   232,   231,   234,   233,   235,   235,
     236,   236,   237,   237,   237,   237,   237,   237,   237,   237,
     238,   239,   240,   242,   241,   244,   243,   246,   245,   247,
     249,   248,   250,   252,   251,   253,   253,   254,   254,   256,
     255,   258,   257,   259,   259,   260,   260,   261,   261,   261,
     261,   261,   261,   262,   264,   263,   265,   266,   267,   269,
     268,   270,   270,   271,   271,   273,   272,   275,   274,   276,
     276,   277,   277,   277,   279,   278,   281,   280,   282,   282,
     283,   283,   285,   284,   287,   286,   288,   288,   289,   289,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   292,   291,   294,   293,   296,   295,   298,   297,
     300,   299,   302,   301,   304,   303,   306,   305,   308,   307,
     310,   309,   312,   311,   314,   313,   316,   315,   317,   317,
     318,   221,   319,   319,   320,   320,   321,   321,   321,   321,
     321,   321,   321,   322,   324,   323,   325,   327,   326,   328,
     328,   329,   329,   331,   330,   333,   332,   335,   334,   337,
     336,   339,   338,   341,   340,   342,   342,   343,   345,   344,
     346,   346,   348,   347,   349,   349,   350,   350,   350,   350,
     350,   351,   353,   352,   355,   354,   356,   356,   358,   357,
     359,   359,   361,   360
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
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     0,     4
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
  "\"postgresql\"", "\"user\"", "\"password\"", "\"host\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
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
       0,   197,   197,   197,   198,   198,   199,   199,   200,   200,
     201,   201,   202,   202,   203,   203,   204,   204,   205,   205,
     206,   206,   214,   215,   216,   217,   218,   219,   220,   223,
     228,   228,   240,   241,   244,   248,   255,   255,   263,   263,
     270,   271,   274,   278,   289,   299,   299,   311,   312,   316,
     317,   318,   319,   320,   323,   323,   340,   340,   348,   349,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   377,   382,   387,   392,   397,   402,   408,   408,   418,
     419,   422,   423,   426,   426,   434,   434,   444,   444,   452,
     452,   462,   462,   472,   473,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   488,   488,   495,   496,   497,
     500,   500,   508,   508,   516,   516,   524,   524,   532,   537,
     542,   547,   552,   552,   562,   563,   566,   567,   568,   569,
     572,   577,   582,   587,   592,   592,   602,   603,   606,   607,
     610,   610,   618,   618,   626,   627,   628,   631,   632,   635,
     635,   643,   643,   651,   651,   661,   662,   668,   676,   676,
     689,   690,   693,   694,   701,   701,   724,   724,   733,   734,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,   754,   755,   756,   757,
     760,   760,   768,   768,   776,   776,   784,   784,   792,   792,
     800,   800,   808,   808,   816,   816,   824,   829,   838,   838,
     850,   851,   854,   855,   860,   860,   871,   871,   881,   882,
     885,   886,   889,   890,   891,   892,   893,   894,   895,   896,
     899,   901,   906,   908,   908,   916,   916,   924,   924,   932,
     934,   934,   942,   951,   951,   963,   964,   969,   970,   975,
     975,   986,   986,   997,   998,  1003,  1004,  1009,  1010,  1011,
    1012,  1013,  1014,  1017,  1019,  1019,  1027,  1029,  1031,  1039,
    1039,  1051,  1052,  1055,  1056,  1059,  1059,  1067,  1067,  1075,
    1076,  1079,  1080,  1081,  1084,  1084,  1095,  1095,  1105,  1106,
    1109,  1110,  1113,  1113,  1121,  1121,  1129,  1130,  1133,  1134,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,
    1148,  1149,  1152,  1152,  1160,  1160,  1168,  1168,  1176,  1176,
    1184,  1184,  1192,  1192,  1200,  1200,  1208,  1208,  1217,  1217,
    1225,  1225,  1238,  1238,  1248,  1248,  1259,  1259,  1269,  1270,
    1273,  1273,  1281,  1282,  1285,  1286,  1289,  1290,  1291,  1292,
    1293,  1294,  1295,  1298,  1300,  1300,  1312,  1319,  1319,  1329,
    1330,  1333,  1334,  1337,  1337,  1345,  1345,  1355,  1355,  1367,
    1367,  1374,  1374,  1386,  1386,  1399,  1400,  1404,  1408,  1408,
    1420,  1421,  1425,  1425,  1433,  1434,  1437,  1438,  1439,  1440,
    1441,  1444,  1448,  1448,  1456,  1456,  1466,  1467,  1470,  1470,
    1478,  1479,  1482,  1482
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
#line 3470 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1490 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
