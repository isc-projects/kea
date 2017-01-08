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
#line 352 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 99: // "integer"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 359 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 100: // "floating point"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 101: // "boolean"

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 114: // value

#line 189 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
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
#line 620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 199 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 200 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 201 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 202 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 203 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 215 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 216 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 217 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 835 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 867 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr type(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-socket-type", type);
    ctx.leave();
}
#line 1040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1617 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1707 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1715 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 986 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2129 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2381 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2407 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1433 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2457 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2552 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -414;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     187,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,    50,    22,    53,    55,    57,    74,    89,    99,   120,
     126,   144,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,    22,    59,    18,    71,    24,    19,    47,    93,
      91,   121,   -35,  -414,   158,   170,   182,   195,   211,  -414,
    -414,  -414,  -414,   186,  -414,    43,  -414,  -414,  -414,  -414,
    -414,  -414,   220,   231,  -414,  -414,  -414,   232,   235,   237,
     238,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,   240,
    -414,  -414,  -414,    58,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,    72,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
     241,   242,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,    85,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,   110,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,   208,   229,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
     244,  -414,  -414,  -414,   245,  -414,  -414,  -414,   215,   249,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,   254,  -414,  -414,  -414,  -414,   251,   250,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   111,  -414,  -414,
    -414,  -414,    22,    22,  -414,   167,   256,   257,   263,   265,
    -414,    18,  -414,   267,   171,   172,   281,   282,   283,   189,
     191,   193,   194,   285,   287,   290,   291,   292,   293,   296,
     297,   204,   298,   300,    71,  -414,   301,   302,    24,  -414,
      41,   303,   304,   305,   306,   307,   308,   309,   216,   213,
     312,   313,   314,   315,    19,  -414,   316,    47,  -414,   317,
     318,   319,   320,   321,   322,   323,   324,   325,  -414,    93,
     326,   327,   233,   329,   330,   331,   236,  -414,    91,   332,
     239,  -414,   121,   334,   335,     6,  -414,  -414,  -414,   337,
     336,   338,    22,    22,  -414,   339,  -414,  -414,   246,   340,
     341,  -414,  -414,  -414,  -414,   344,   345,   346,   347,   348,
     349,   350,   351,  -414,   352,   355,  -414,   358,   258,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   356,   364,  -414,
    -414,  -414,   270,   271,   272,   366,   274,   275,   277,  -414,
    -414,   286,   288,   374,   373,  -414,   289,  -414,   294,   299,
     358,   310,   311,   328,   333,   342,   343,  -414,   353,   354,
    -414,   357,   359,   360,  -414,  -414,   361,  -414,  -414,   362,
      22,  -414,    22,    71,   261,  -414,  -414,    24,  -414,    17,
      17,   376,   378,   381,   168,    38,   383,   363,   103,    65,
      59,  -414,  -414,  -414,   377,  -414,    41,  -414,  -414,  -414,
     384,  -414,  -414,  -414,  -414,  -414,   387,   365,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   141,  -414,   162,
    -414,  -414,   163,  -414,  -414,  -414,   391,   392,   394,  -414,
     164,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
     180,  -414,   393,   397,  -414,  -414,   395,   399,  -414,  -414,
     398,   400,  -414,  -414,  -414,  -414,  -414,  -414,    86,  -414,
    -414,  -414,  -414,  -414,   190,  -414,   401,   402,  -414,   406,
     184,  -414,  -414,   407,   408,   409,  -414,  -414,  -414,   192,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   196,  -414,  -414,
    -414,   199,   367,   368,  -414,  -414,   410,   403,  -414,  -414,
     411,   412,  -414,  -414,   413,  -414,   414,   261,  -414,  -414,
     415,   416,   418,   369,   370,   371,    17,  -414,  -414,    19,
    -414,   376,    91,  -414,   378,   121,  -414,   381,   168,  -414,
      38,  -414,   -35,  -414,   383,   372,   363,  -414,   419,   375,
     379,   380,   103,  -414,   420,   421,    65,  -414,  -414,  -414,
     422,   424,  -414,    47,  -414,   384,    93,  -414,   387,   425,
    -414,   427,  -414,   382,   385,   386,  -414,  -414,  -414,  -414,
     202,  -414,   426,  -414,   428,  -414,  -414,  -414,   203,  -414,
    -414,  -414,   388,  -414,  -414,  -414,  -414,   389,   390,  -414,
    -414,   396,   209,  -414,   429,  -414,   404,   431,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,   219,  -414,   100,   431,  -414,  -414,   435,
    -414,  -414,  -414,   210,  -414,  -414,  -414,  -414,  -414,   438,
     405,   439,   100,  -414,   430,  -414,   432,  -414,   437,  -414,
    -414,   228,  -414,   417,   437,  -414,  -414,   212,  -414,  -414,
     441,   417,  -414,   436,  -414,  -414
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    49,     5,    60,     7,    98,     9,
     176,    11,   286,    13,   303,    15,   226,    17,   260,    19,
     152,    21,    38,    32,     0,     0,     0,     0,     0,   305,
     228,   262,     0,    40,     0,    39,     0,     0,    33,    58,
     398,   394,   396,     0,    57,     0,    51,    53,    55,    56,
      54,    92,     0,     0,   321,   104,   106,     0,     0,     0,
       0,   168,   218,   252,   133,   345,   144,   163,   365,     0,
     382,   392,    85,     0,    62,    64,    65,    66,    67,    82,
      83,    69,    70,    71,    72,    76,    77,    68,    74,    75,
      84,    73,    78,    79,    80,    81,   100,   102,     0,    94,
      96,    97,   349,   202,   204,   206,   278,   200,   208,   210,
       0,     0,   214,   212,   295,   341,   199,   180,   181,   182,
     194,     0,   178,   185,   196,   197,   198,   186,   187,   190,
     192,   188,   189,   183,   184,   191,   195,   193,   293,   292,
     291,     0,   288,   290,   323,   325,   339,   329,   331,   335,
     333,   337,   327,   320,   316,     0,   306,   307,   317,   318,
     319,   313,   309,   314,   311,   312,   315,   310,   119,   127,
       0,   246,   244,   249,     0,   239,   243,   240,     0,   229,
     230,   232,   242,   233,   234,   235,   248,   236,   237,   238,
     273,     0,   271,   272,   275,   276,     0,   263,   264,   266,
     267,   268,   269,   270,   159,   161,   156,     0,   154,   157,
     158,    37,     0,     0,    31,     0,     0,     0,     0,     0,
      48,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,     0,     0,     0,    99,
     351,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   177,     0,     0,   287,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   304,     0,
       0,     0,     0,     0,     0,     0,     0,   227,     0,     0,
       0,   261,     0,     0,     0,     0,   153,    41,    34,     0,
       0,     0,     0,     0,    52,     0,    90,    91,     0,     0,
       0,    86,    87,    88,    89,     0,     0,     0,     0,     0,
       0,     0,     0,   381,     0,     0,    63,     0,     0,    95,
     363,   361,   362,   357,   358,   359,   360,     0,   352,   353,
     355,   356,     0,     0,     0,     0,     0,     0,     0,   216,
     217,     0,     0,     0,     0,   179,     0,   289,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   308,     0,     0,
     241,     0,     0,     0,   251,   231,     0,   277,   265,     0,
       0,   155,     0,     0,     0,   395,   397,     0,   322,     0,
       0,   170,   220,   254,     0,     0,   146,     0,     0,     0,
       0,    42,   101,   103,     0,   350,     0,   203,   205,   207,
     280,   201,   209,   211,   215,   213,   297,     0,   294,   324,
     326,   340,   330,   332,   336,   334,   338,   328,   120,   128,
     247,   245,   250,   274,   160,   162,    35,     0,   403,     0,
     400,   402,     0,   121,   123,   125,     0,     0,     0,   118,
       0,   108,   110,   111,   112,   113,   114,   115,   116,   117,
       0,   174,     0,   171,   172,   224,     0,   221,   222,   258,
       0,   255,   256,   132,   141,   142,   143,   137,     0,   135,
     138,   139,   140,   347,     0,   150,     0,   147,   148,     0,
       0,   165,   377,     0,     0,     0,   375,   369,   374,     0,
     367,   372,   370,   371,   373,   388,   390,     0,   384,   386,
     387,     0,    44,     0,   354,   284,     0,   281,   282,   301,
       0,   298,   299,   343,     0,    59,     0,     0,   399,    93,
       0,     0,     0,     0,     0,     0,     0,   105,   107,     0,
     169,     0,   228,   219,     0,   262,   253,     0,     0,   134,
       0,   346,     0,   145,     0,     0,     0,   164,     0,     0,
       0,     0,     0,   366,     0,     0,     0,   383,   393,    46,
       0,    45,   364,     0,   279,     0,   305,   296,     0,     0,
     342,     0,   401,     0,     0,     0,   129,   130,   131,   109,
       0,   173,     0,   223,     0,   257,   136,   348,     0,   149,
     167,   166,     0,   376,   379,   380,   368,     0,     0,   385,
      43,     0,     0,   283,     0,   300,     0,     0,   122,   124,
     126,   175,   225,   259,   151,   378,   389,   391,    47,   285,
     302,   344,   407,     0,   405,     0,     0,   404,   419,     0,
     417,   415,   411,     0,   409,   413,   414,   412,   406,     0,
       0,     0,     0,   408,     0,   416,     0,   410,     0,   418,
     423,     0,   421,     0,     0,   420,   427,     0,   425,   422,
       0,     0,   424,     0,   426,   428
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,   -34,  -414,  -414,  -414,  -414,   -75,  -414,  -414,
    -414,  -414,    56,  -414,  -414,  -414,   -54,  -414,  -414,  -414,
     197,  -414,  -414,  -414,  -414,     1,   159,   -56,   -40,   -38,
    -414,  -414,   -37,  -414,  -414,    30,   175,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,    29,  -116,  -398,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,   -59,  -414,  -413,
    -414,  -414,  -414,  -414,  -414,  -414,  -124,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -128,  -414,  -414,  -414,  -120,   138,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -122,  -414,  -414,
    -414,  -414,  -104,  -414,  -414,  -414,  -101,   179,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -402,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
     -99,  -414,  -414,  -414,   -96,  -414,   173,  -414,   -52,  -414,
    -414,  -414,  -414,   -48,  -414,  -414,  -414,  -414,  -414,   -47,
    -414,  -414,  -414,  -100,  -414,  -414,  -414,   -94,  -414,   160,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -115,  -414,  -414,  -414,  -118,   198,  -414,  -414,  -414,  -414,
    -414,  -414,  -119,  -414,  -414,  -414,  -114,  -414,   188,   -43,
    -414,  -256,  -414,  -255,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,    60,
    -414,  -414,  -414,  -414,  -414,  -414,   -93,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -103,  -414,  -414,  -414,
    -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,  -414,
     -51,  -414,  -414,  -414,  -168,  -414,  -414,  -181,  -414,  -414,
    -414,  -414,  -414,  -414,  -191,  -414,  -414,  -196,  -414
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    30,    31,    32,    53,    67,    68,    33,    52,
      64,    65,   432,   542,   600,   601,   102,    35,    54,    75,
      76,    77,   246,    37,    55,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   253,   128,   129,    39,    56,   130,
     276,   131,   277,   112,   257,   113,   258,   480,   481,   206,
     310,   483,   560,   484,   561,   485,   562,   207,   311,   487,
     488,   489,   507,   114,   266,   508,   509,   510,   511,   512,
     115,   268,   516,   517,   518,   582,    51,    62,   237,   238,
     239,   323,   240,   324,   116,   269,   520,   521,   117,   263,
     492,   493,   494,   569,    41,    57,   151,   152,   153,   285,
     154,   281,   155,   282,   156,   283,   157,   286,   158,   287,
     159,   291,   160,   290,   161,   162,   118,   264,   496,   497,
     498,   572,    47,    60,   208,   209,   210,   211,   212,   213,
     214,   215,   314,   216,   313,   217,   218,   315,   219,   119,
     265,   500,   501,   502,   575,    49,    61,   226,   227,   228,
     229,   230,   319,   231,   232,   233,   164,   284,   546,   547,
     548,   603,    43,    58,   171,   172,   173,   296,   165,   292,
     550,   551,   552,   606,    45,    59,   185,   186,   187,   120,
     256,   189,   299,   190,   300,   191,   307,   192,   302,   193,
     303,   194,   305,   195,   304,   196,   306,   197,   301,   167,
     293,   554,   609,   121,   267,   514,   280,   367,   368,   369,
     370,   371,   434,   122,   270,   529,   530,   531,   532,   588,
     533,   534,   123,   124,   272,   537,   538,   539,   594,   540,
     595,   125,   273,    78,   248,    79,   249,    80,   247,   469,
     470,   471,   556,   663,   664,   665,   673,   674,   675,   676,
     681,   677,   679,   691,   692,   693,   697,   698,   700
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   147,   223,   146,   169,   183,   205,   222,   236,   224,
     163,   170,   184,   225,   166,   528,   188,   148,    63,   149,
     150,   482,   482,   513,   365,   366,   132,    23,    69,    24,
     527,    25,   234,   235,    83,    84,   126,   127,   198,   473,
     474,   475,   476,   477,   478,   132,   251,    87,    88,    89,
      22,   252,   133,   134,   135,   199,    93,    84,   174,   175,
      34,   274,    36,    73,    38,   136,   275,   137,   138,   139,
     140,   141,   142,   234,   235,   278,   143,   144,    93,   199,
     279,    40,    81,   145,    93,    82,    83,    84,   294,   578,
      85,    86,   579,   295,   168,   143,    42,   360,    70,    87,
      88,    89,    90,    91,    71,    72,    44,    92,    93,    84,
     174,   175,   198,   297,   325,    73,    73,    73,   298,   326,
      26,    27,    28,    29,   198,    94,    95,    46,   476,   199,
      93,   200,   201,    48,   202,   203,   204,    96,   199,    73,
      97,    98,   535,   536,   274,    73,    99,   100,   176,   555,
     101,    50,   177,   178,   179,   180,   181,    66,   182,   199,
     220,   200,   201,   221,   241,   557,   278,   566,   482,    73,
     558,   559,   567,   242,   522,   523,   524,   525,   627,   528,
     365,   366,   668,   566,   669,   670,   243,   586,   568,    73,
     250,    73,   587,   580,   527,   592,   581,    74,    73,   596,
     593,    73,   245,   244,   597,   294,   325,   598,   327,   328,
     651,   654,   297,   682,   245,   701,   308,   659,   683,    73,
     702,   362,   666,   317,   254,   667,   361,   503,   504,   505,
     506,   694,   309,   363,   695,   255,   259,   364,   147,   260,
     146,   261,   262,   169,   271,   288,   289,   163,   312,   316,
     170,   166,   318,   322,   148,   183,   149,   150,   320,   321,
     330,   331,   184,   223,   205,   329,   188,   332,   222,   333,
     224,   335,   336,   337,   225,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,   338,   339,   340,   341,   345,
     342,   346,   343,   344,   347,   348,   349,   350,   415,   416,
     351,   352,   354,   353,   355,   357,   358,   372,   373,   374,
     375,   376,   377,   378,   380,   379,   381,   382,   383,   384,
     386,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     398,   399,   400,   401,   402,   403,   406,   404,   409,   410,
     407,   412,   468,   413,   418,   414,   417,   419,   420,   421,
     422,   423,   424,   425,   426,   541,   433,   427,   428,   429,
     486,   486,   430,   431,   435,   479,   479,   436,   437,   438,
     439,   440,   441,   442,   526,   443,   465,   362,   466,   446,
     447,   543,   361,   491,   444,   495,   445,   448,   499,   363,
     515,   545,   449,   364,   549,   563,   564,   450,   565,   570,
     571,   573,   574,   577,   576,   584,   605,   583,   452,   453,
     585,   589,   590,   591,   467,   608,   604,   607,   611,   613,
     614,   610,   615,   632,   637,   638,   454,   641,   640,   646,
     553,   455,   647,   356,   652,   688,   653,   660,   662,   680,
     456,   457,   684,   686,   690,   703,   451,   472,   334,   490,
     619,   458,   459,   359,   626,   460,   629,   461,   462,   463,
     464,   519,   628,   411,   631,   599,   602,   621,   620,   617,
     616,   630,   618,   385,   633,   623,   622,   625,   634,   635,
     648,   624,   408,   649,   650,   642,   655,   656,   657,   645,
     643,   405,   644,   639,   658,   387,   544,   397,   678,   636,
     696,   687,   661,   699,   685,   704,   612,   486,     0,     0,
       0,     0,   479,   147,     0,   146,   223,     0,   205,     0,
       0,   222,   163,   224,     0,     0,   166,   225,   236,   148,
     689,   149,   150,     0,   705,     0,     0,     0,   526,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   169,
       0,     0,   183,     0,     0,     0,   170,     0,     0,   184,
       0,     0,     0,   188,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   672,     0,     0,     0,
       0,   671,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   672,     0,     0,     0,     0,   671
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,   428,    59,    57,    52,    57,
      57,   419,   420,   425,   280,   280,     7,     5,    10,     7,
     428,     9,    67,    68,    15,    16,    12,    13,    21,    22,
      23,    24,    25,    26,    27,     7,     3,    28,    29,    30,
       0,     8,    33,    34,    35,    38,    37,    16,    17,    18,
       7,     3,     7,    98,     7,    46,     8,    48,    49,    50,
      51,    52,    53,    67,    68,     3,    57,    58,    37,    38,
       8,     7,    11,    64,    37,    14,    15,    16,     3,     3,
      19,    20,     6,     8,    47,    57,     7,    56,    80,    28,
      29,    30,    31,    32,    86,    87,     7,    36,    37,    16,
      17,    18,    21,     3,     3,    98,    98,    98,     8,     8,
      98,    99,   100,   101,    21,    54,    55,     7,    25,    38,
      37,    40,    41,     7,    43,    44,    45,    66,    38,    98,
      69,    70,    77,    78,     3,    98,    75,    76,    55,     8,
      79,     7,    59,    60,    61,    62,    63,    98,    65,    38,
      39,    40,    41,    42,     6,     3,     3,     3,   566,    98,
       8,     8,     8,     3,    71,    72,    73,    74,   580,   592,
     436,   436,    82,     3,    84,    85,     4,     3,     8,    98,
       4,    98,     8,     3,   592,     3,     6,   251,    98,     3,
       8,    98,     3,     8,     8,     3,     3,     8,   242,   243,
       8,     8,     3,     3,     3,     3,     8,     8,     8,    98,
       8,   280,     3,     8,     4,     6,   280,    59,    60,    61,
      62,     3,     3,   280,     6,     4,     4,   280,   294,     4,
     294,     4,     4,   297,     4,     4,     4,   294,     4,     4,
     297,   294,     3,     3,   294,   309,   294,   294,     4,     8,
       4,     4,   309,   322,   318,    98,   309,     4,   322,     4,
     322,     4,   101,   101,   322,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,     4,     4,     4,    99,     4,
      99,     4,    99,    99,     4,     4,     4,     4,   332,   333,
       4,     4,     4,    99,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   101,    99,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,    99,     4,     4,     4,     4,   101,     4,     4,
     101,     4,    81,     7,    98,     7,     7,     7,     7,     5,
       5,     5,     5,     5,     5,   430,    98,     7,     7,     7,
     419,   420,     7,     5,     8,   419,   420,     3,    98,    98,
      98,     5,    98,    98,   428,    98,   410,   436,   412,     5,
       7,     4,   436,     7,    98,     7,    98,    98,     7,   436,
       7,     7,    98,   436,     7,     4,     4,    98,     4,     6,
       3,     6,     3,     3,     6,     3,     3,     6,    98,    98,
       4,     4,     4,     4,   413,     3,     6,     6,     4,     4,
       4,     8,     4,     4,     4,     4,    98,     3,     6,     4,
      65,    98,     5,   274,     8,     5,     8,     8,     7,     4,
      98,    98,     4,     4,     7,     4,   390,   417,   251,   420,
     566,    98,    98,   278,   578,    98,   584,    98,    98,    98,
      98,    98,   582,   325,   586,    98,    98,   571,   569,    99,
     101,    99,   101,   294,    99,   574,   572,   577,    99,    99,
      98,   575,   322,    98,    98,   603,    98,    98,    98,   608,
     605,   318,   606,   596,    98,   297,   436,   309,   666,   592,
      83,   682,    98,   694,    99,   701,   557,   566,    -1,    -1,
      -1,    -1,   566,   569,    -1,   569,   575,    -1,   572,    -1,
      -1,   575,   569,   575,    -1,    -1,   569,   575,   582,   569,
      98,   569,   569,    -1,    98,    -1,    -1,    -1,   592,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   603,
      -1,    -1,   606,    -1,    -1,    -1,   603,    -1,    -1,   606,
      -1,    -1,    -1,   606,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   665,    -1,    -1,    -1,
      -1,   665,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   682,    -1,    -1,    -1,    -1,   682
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     0,     5,     7,     9,    98,    99,   100,   101,
     114,   115,   116,   120,     7,   129,     7,   135,     7,   149,
       7,   206,     7,   274,     7,   286,     7,   234,     7,   257,
       7,   188,   121,   117,   130,   136,   150,   207,   275,   287,
     235,   258,   189,   114,   122,   123,    98,   118,   119,    10,
      80,    86,    87,    98,   128,   131,   132,   133,   345,   347,
     349,    11,    14,    15,    16,    19,    20,    28,    29,    30,
      31,    32,    36,    37,    54,    55,    66,    69,    70,    75,
      76,    79,   128,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   155,   157,   175,   182,   196,   200,   228,   251,
     291,   315,   325,   334,   335,   343,    12,    13,   147,   148,
     151,   153,     7,    33,    34,    35,    46,    48,    49,    50,
      51,    52,    53,    57,    58,    64,   128,   139,   140,   141,
     144,   208,   209,   210,   212,   214,   216,   218,   220,   222,
     224,   226,   227,   251,   268,   280,   291,   311,    47,   128,
     251,   276,   277,   278,    17,    18,    55,    59,    60,    61,
      62,    63,    65,   128,   251,   288,   289,   290,   291,   293,
     295,   297,   299,   301,   303,   305,   307,   309,    21,    38,
      40,    41,    43,    44,    45,   128,   161,   169,   236,   237,
     238,   239,   240,   241,   242,   243,   245,   247,   248,   250,
      39,    42,   128,   169,   240,   245,   259,   260,   261,   262,
     263,   265,   266,   267,    67,    68,   128,   190,   191,   192,
     194,     6,     3,     4,     8,     3,   134,   350,   346,   348,
       4,     3,     8,   146,     4,     4,   292,   156,   158,     4,
       4,     4,     4,   201,   229,   252,   176,   316,   183,   197,
     326,     4,   336,   344,     3,     8,   152,   154,     3,     8,
     318,   213,   215,   217,   269,   211,   219,   221,     4,     4,
     225,   223,   281,   312,     3,     8,   279,     3,     8,   294,
     296,   310,   300,   302,   306,   304,   308,   298,     8,     3,
     162,   170,     4,   246,   244,   249,     4,     8,     3,   264,
       4,     8,     3,   193,   195,     3,     8,   114,   114,    98,
       4,     4,     4,     4,   132,     4,   101,   101,     4,     4,
       4,    99,    99,    99,    99,     4,     4,     4,     4,     4,
       4,     4,     4,    99,     4,     4,   138,     4,     4,   148,
      56,   128,   169,   251,   291,   293,   295,   319,   320,   321,
     322,   323,     4,     4,     4,     4,     4,     4,     4,    99,
     101,     4,     4,     4,     4,   209,     4,   277,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   290,     4,     4,
      99,     4,     4,     4,   101,   238,     4,   101,   261,     4,
       4,   191,     4,     7,     7,   114,   114,     7,    98,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   124,    98,   324,     8,     3,    98,    98,    98,
       5,    98,    98,    98,    98,    98,     5,     7,    98,    98,
      98,   124,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,   114,   114,   137,    81,   351,
     352,   353,   147,    22,    23,    24,    25,    26,    27,   128,
     159,   160,   161,   163,   165,   167,   169,   171,   172,   173,
     159,     7,   202,   203,   204,     7,   230,   231,   232,     7,
     253,   254,   255,    59,    60,    61,    62,   174,   177,   178,
     179,   180,   181,   222,   317,     7,   184,   185,   186,    98,
     198,   199,    71,    72,    73,    74,   128,   161,   171,   327,
     328,   329,   330,   332,   333,    77,    78,   337,   338,   339,
     341,   119,   125,     4,   321,     7,   270,   271,   272,     7,
     282,   283,   284,    65,   313,     8,   354,     3,     8,     8,
     164,   166,   168,     4,     4,     4,     3,     8,     8,   205,
       6,     3,   233,     6,     3,   256,     6,     3,     3,     6,
       3,     6,   187,     6,     3,     4,     3,     8,   331,     4,
       4,     4,     3,     8,   340,   342,     3,     8,     8,    98,
     126,   127,    98,   273,     6,     3,   285,     6,     3,   314,
       8,     4,   352,     4,     4,     4,   101,    99,   101,   160,
     208,   204,   236,   232,   259,   255,   178,   222,   190,   186,
      99,   199,     4,    99,    99,    99,   328,     4,     4,   338,
       6,     3,   276,   272,   288,   284,     4,     5,    98,    98,
      98,     8,     8,     8,     8,    98,    98,    98,    98,     8,
       8,    98,     7,   355,   356,   357,     3,     6,    82,    84,
      85,   128,   169,   358,   359,   360,   361,   363,   356,   364,
       4,   362,     3,     8,     4,    99,     4,   359,     5,    98,
       7,   365,   366,   367,     3,     6,    83,   368,   369,   366,
     370,     3,     8,     4,   369,    98
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   102,   104,   103,   105,   103,   106,   103,   107,   103,
     108,   103,   109,   103,   110,   103,   111,   103,   112,   103,
     113,   103,   114,   114,   114,   114,   114,   114,   114,   115,
     117,   116,   118,   118,   119,   119,   121,   120,   122,   122,
     123,   123,   125,   124,   126,   126,   127,   127,   128,   130,
     129,   131,   131,   132,   132,   132,   132,   132,   134,   133,
     136,   135,   137,   137,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   139,   140,   141,   142,
     143,   144,   146,   145,   147,   147,   148,   148,   150,   149,
     152,   151,   154,   153,   156,   155,   158,   157,   159,   159,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   162,
     161,   164,   163,   166,   165,   168,   167,   170,   169,   171,
     172,   173,   174,   176,   175,   177,   177,   178,   178,   178,
     178,   179,   180,   181,   183,   182,   184,   184,   185,   185,
     187,   186,   189,   188,   190,   190,   190,   191,   191,   193,
     192,   195,   194,   197,   196,   198,   198,   199,   201,   200,
     202,   202,   203,   203,   205,   204,   207,   206,   208,   208,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     211,   210,   213,   212,   215,   214,   217,   216,   219,   218,
     221,   220,   223,   222,   225,   224,   226,   227,   229,   228,
     230,   230,   231,   231,   233,   232,   235,   234,   236,   236,
     237,   237,   238,   238,   238,   238,   238,   238,   238,   238,
     239,   240,   241,   242,   244,   243,   246,   245,   247,   249,
     248,   250,   252,   251,   253,   253,   254,   254,   256,   255,
     258,   257,   259,   259,   260,   260,   261,   261,   261,   261,
     261,   261,   262,   264,   263,   265,   266,   267,   269,   268,
     270,   270,   271,   271,   273,   272,   275,   274,   276,   276,
     277,   277,   277,   279,   278,   281,   280,   282,   282,   283,
     283,   285,   284,   287,   286,   288,   288,   289,   289,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   292,   291,   294,   293,   296,   295,   298,   297,   300,
     299,   302,   301,   304,   303,   306,   305,   308,   307,   310,
     309,   312,   311,   314,   313,   316,   315,   317,   317,   318,
     222,   319,   319,   320,   320,   321,   321,   321,   321,   321,
     321,   321,   322,   324,   323,   326,   325,   327,   327,   328,
     328,   328,   328,   328,   328,   328,   329,   331,   330,   332,
     333,   334,   336,   335,   337,   337,   338,   338,   340,   339,
     342,   341,   344,   343,   346,   345,   348,   347,   350,   349,
     351,   351,   352,   354,   353,   355,   355,   357,   356,   358,
     358,   359,   359,   359,   359,   359,   360,   362,   361,   364,
     363,   365,   365,   367,   366,   368,   368,   370,   369
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     1,     3,     5,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     3,     1,     0,     6,     1,     3,     1,     1,     1,
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
       1,     3,     1,     1,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     0,     4
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
  "\"hosts-database\"", "\"type\"", "\"user\"", "\"password\"", "\"host\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"subnet\"", "\"interface\"", "\"interface-id\"", "\"id\"",
  "\"rapid-commit\"", "\"reservation-mode\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"server-id\"", "\"identifier\"",
  "\"htype\"", "\"time\"", "\"enterprise-id\"", "\"dhcp4o6-port\"",
  "\"control-socket\"", "\"socket-type\"", "\"socket-name\"",
  "\"dhcp-ddns\"", "\"Logging\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4",
  "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "value", "sub_json", "map2", "$@11",
  "map_content", "not_empty_map", "list_generic", "$@12", "list_content",
  "not_empty_list", "list_strings", "$@13", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@14",
  "global_objects", "global_object", "dhcp4_object", "$@15", "sub_dhcp4",
  "$@16", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@17",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@18", "interfaces_list", "$@19", "dhcp_socket_type", "$@20",
  "lease_database", "$@21", "hosts_database", "$@22",
  "database_map_params", "database_map_param", "type", "$@23", "user",
  "$@24", "password", "$@25", "host", "$@26", "name", "$@27", "persist",
  "lfc_interval", "readonly", "duid_id", "host_reservation_identifiers",
  "$@28", "host_reservation_identifiers_list",
  "host_reservation_identifier", "hw_address_id", "circuit_id",
  "client_id", "hooks_libraries", "$@29", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@30",
  "sub_hooks_library", "$@31", "hooks_params", "hooks_param", "library",
  "$@32", "parameters", "$@33", "expired_leases_processing", "$@34",
  "expired_leases_params", "expired_leases_param", "subnet4_list", "$@35",
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
  "pool_param", "pool_entry", "$@59", "reservations", "$@60",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@61", "sub_reservation", "$@62", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@63", "server_hostname", "$@64", "boot_file_name", "$@65",
  "ip_address", "$@66", "duid", "$@67", "hw_address", "$@68",
  "client_id_value", "$@69", "circuit_id_value", "$@70", "hostname",
  "$@71", "reservation_client_classes", "$@72", "relay", "$@73",
  "relay_map", "$@74", "client_classes", "$@75", "client_classes_list",
  "$@76", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@77",
  "server_id", "$@78", "server_id_params", "server_id_param", "htype",
  "identifier", "$@79", "time", "enterprise_id", "dhcp4o6_port",
  "control_socket", "$@80", "control_socket_params",
  "control_socket_param", "socket_type", "$@81", "socket_name", "$@82",
  "dhcp_ddns", "$@83", "dhcp6_json_object", "$@84", "dhcpddns_json_object",
  "$@85", "logging_object", "$@86", "logging_params", "logging_param",
  "loggers", "$@87", "loggers_entries", "logger_entry", "$@88",
  "logger_params", "logger_param", "debuglevel", "severity", "$@89",
  "output_options_list", "$@90", "output_options_list_content",
  "output_entry", "$@91", "output_params", "output_param", "$@92", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   198,   198,   198,   199,   199,   200,   200,   201,   201,
     202,   202,   203,   203,   204,   204,   205,   205,   206,   206,
     207,   207,   215,   216,   217,   218,   219,   220,   221,   224,
     229,   229,   241,   242,   245,   249,   256,   256,   263,   264,
     267,   271,   278,   278,   285,   286,   289,   293,   304,   314,
     314,   326,   327,   331,   332,   333,   334,   335,   338,   338,
     355,   355,   363,   364,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   393,   398,   403,   408,
     413,   418,   424,   424,   434,   435,   438,   439,   442,   442,
     450,   450,   460,   460,   468,   468,   478,   478,   488,   489,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   503,
     503,   511,   511,   519,   519,   527,   527,   535,   535,   543,
     548,   553,   558,   563,   563,   573,   574,   577,   578,   579,
     580,   583,   588,   593,   598,   598,   608,   609,   612,   613,
     616,   616,   624,   624,   632,   633,   634,   637,   638,   641,
     641,   649,   649,   657,   657,   667,   668,   674,   682,   682,
     695,   696,   699,   700,   707,   707,   730,   730,   739,   740,
     744,   745,   746,   747,   748,   749,   750,   751,   752,   753,
     754,   755,   756,   757,   758,   759,   760,   761,   762,   763,
     766,   766,   774,   774,   782,   782,   790,   790,   798,   798,
     806,   806,   814,   814,   822,   822,   830,   835,   844,   844,
     856,   857,   860,   861,   866,   866,   877,   877,   887,   888,
     891,   892,   895,   896,   897,   898,   899,   900,   901,   902,
     905,   907,   912,   914,   916,   916,   924,   924,   932,   934,
     934,   942,   951,   951,   963,   964,   969,   970,   975,   975,
     986,   986,   997,   998,  1003,  1004,  1009,  1010,  1011,  1012,
    1013,  1014,  1017,  1019,  1019,  1027,  1029,  1031,  1039,  1039,
    1051,  1052,  1055,  1056,  1059,  1059,  1067,  1067,  1075,  1076,
    1079,  1080,  1081,  1084,  1084,  1095,  1095,  1105,  1106,  1109,
    1110,  1113,  1113,  1121,  1121,  1129,  1130,  1133,  1134,  1138,
    1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,
    1149,  1152,  1152,  1160,  1160,  1168,  1168,  1176,  1176,  1184,
    1184,  1192,  1192,  1200,  1200,  1208,  1208,  1217,  1217,  1225,
    1225,  1238,  1238,  1248,  1248,  1259,  1259,  1269,  1270,  1273,
    1273,  1281,  1282,  1285,  1286,  1289,  1290,  1291,  1292,  1293,
    1294,  1295,  1298,  1300,  1300,  1311,  1311,  1321,  1322,  1325,
    1326,  1327,  1328,  1329,  1330,  1331,  1334,  1339,  1339,  1347,
    1352,  1359,  1366,  1366,  1376,  1377,  1380,  1381,  1384,  1384,
    1392,  1392,  1402,  1402,  1414,  1414,  1421,  1421,  1433,  1433,
    1446,  1447,  1451,  1455,  1455,  1467,  1468,  1472,  1472,  1480,
    1481,  1484,  1485,  1486,  1487,  1488,  1491,  1495,  1495,  1503,
    1503,  1513,  1514,  1517,  1517,  1525,  1526,  1529,  1529
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
#line 3514 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1537 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
