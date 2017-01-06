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
      case 116: // value
      case 155: // socket_type
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 116: // value
      case 155: // socket_type
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
            case 100: // "constant string"

#line 192 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 354 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 101: // "integer"

#line 192 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 361 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 102: // "floating point"

#line 192 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 368 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 103: // "boolean"

#line 192 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 375 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 116: // value

#line 192 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 382 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 155: // socket_type

#line 192 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 116: // value
      case 155: // socket_type
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
#line 201 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 202 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 203 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 204 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 205 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 654 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 206 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 207 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 208 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 209 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 210 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 218 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 219 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 220 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 221 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 222 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 223 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 224 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 327 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 334 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 456 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 457 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1439 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1491 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1501 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1519 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1527 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1581 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1858 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1932 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1950 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1144 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 1968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2058 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2112 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1251 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2328 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2410 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2430 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1487 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2515 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2551 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -411;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     108,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    37,    20,    25,    40,    64,    66,    73,    79,   110,
     118,   139,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,    20,    53,    18,    71,   219,    24,    -3,    93,
     122,     8,    29,  -411,   153,   160,   204,   228,   236,  -411,
    -411,  -411,  -411,   240,  -411,    31,  -411,  -411,  -411,  -411,
    -411,  -411,   244,   245,  -411,  -411,  -411,   248,   249,   254,
     255,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   256,
    -411,  -411,  -411,    32,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,    35,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     257,   261,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    50,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,    54,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,   259,   266,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
     267,  -411,  -411,  -411,   268,  -411,  -411,  -411,   265,   272,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   273,  -411,  -411,  -411,  -411,   270,   276,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   111,  -411,  -411,
    -411,  -411,    20,    20,  -411,   176,   277,   278,   279,   280,
    -411,    18,  -411,   281,   177,   183,   283,   284,   285,   190,
     191,   192,   193,   286,   291,   292,   293,   294,   295,   296,
     297,   201,   299,   300,    71,  -411,   301,   302,   219,  -411,
      76,   303,   304,   305,   306,   307,   308,   309,   213,   212,
     312,   313,   314,   315,    24,  -411,   316,    -3,  -411,   317,
     318,   319,   320,   321,   322,   323,   324,   325,  -411,    93,
     326,   327,   231,   329,   330,   333,   235,  -411,   122,   335,
     237,  -411,     8,   337,   338,   -25,  -411,  -411,  -411,   339,
     340,   341,    20,    20,  -411,   342,  -411,  -411,   246,   343,
     344,  -411,  -411,  -411,  -411,   347,   348,   349,   350,   351,
     352,   355,   356,  -411,   357,   360,  -411,   353,   220,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,   336,   365,  -411,
    -411,  -411,   269,   271,   275,   354,   282,   287,   288,  -411,
    -411,   289,   290,   367,   363,  -411,   298,  -411,   310,   311,
     353,   328,   331,   332,   334,   345,   346,  -411,   358,   359,
    -411,   361,   362,   364,  -411,  -411,   366,  -411,  -411,   368,
      20,  -411,    20,    71,   262,  -411,  -411,   219,  -411,    41,
      41,   369,   370,   371,   166,    26,   373,   372,   113,   162,
      53,  -411,  -411,  -411,  -411,  -411,   377,  -411,    76,  -411,
    -411,  -411,   376,  -411,  -411,  -411,  -411,  -411,   378,   374,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   123,
    -411,   158,  -411,  -411,   169,  -411,  -411,  -411,   382,   388,
     389,  -411,   170,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,   171,  -411,   390,   391,  -411,  -411,   393,   394,
    -411,  -411,   395,   397,  -411,  -411,  -411,  -411,  -411,  -411,
     127,  -411,  -411,  -411,  -411,  -411,   141,  -411,   396,   400,
    -411,   401,   172,  -411,  -411,   402,   403,   404,  -411,  -411,
    -411,   182,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   206,
    -411,  -411,  -411,   207,    20,   375,  -411,  -411,   398,   406,
    -411,  -411,   408,   409,  -411,  -411,   410,  -411,   412,   262,
    -411,  -411,   413,   415,   416,   379,   380,   381,    41,  -411,
    -411,    24,  -411,   369,   122,  -411,   370,     8,  -411,   371,
     166,  -411,    26,  -411,    29,  -411,   373,   384,   372,  -411,
     417,   385,   386,   387,   113,  -411,   418,   419,   162,  -411,
    -411,   420,  -411,    -3,  -411,   376,    93,  -411,   378,   421,
    -411,   422,  -411,   383,   392,   399,  -411,  -411,  -411,  -411,
     208,  -411,   425,  -411,   427,  -411,  -411,  -411,   209,  -411,
    -411,  -411,   405,  -411,  -411,  -411,  -411,   407,   411,  -411,
    -411,   215,  -411,   428,  -411,   426,   423,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,   188,  -411,    51,   423,  -411,  -411,   433,  -411,  -411,
    -411,   216,  -411,  -411,  -411,  -411,  -411,   434,   431,   435,
      51,  -411,   424,  -411,   436,  -411,   437,  -411,  -411,   189,
    -411,   442,   437,  -411,  -411,   217,  -411,  -411,   438,   442,
    -411,   439,  -411,  -411
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    36,    30,    26,    25,    22,    23,    24,
      29,     3,    27,    28,    45,     5,    56,     7,    94,     9,
     174,    11,   284,    13,   301,    15,   224,    17,   258,    19,
     150,    21,    40,    32,     0,     0,     0,     0,     0,   303,
     226,   260,     0,    42,     0,    41,     0,     0,    33,    54,
     396,   392,   394,     0,    53,     0,    47,    49,    51,    52,
      50,    88,     0,     0,   319,   102,   104,     0,     0,     0,
       0,   166,   216,   250,   131,   343,   142,   161,   363,     0,
     380,   390,    81,     0,    58,    60,    61,    62,    63,    78,
      79,    65,    66,    67,    68,    72,    73,    64,    70,    71,
      80,    69,    74,    75,    76,    77,    96,    98,     0,    90,
      92,    93,   347,   200,   202,   204,   276,   198,   206,   208,
       0,     0,   212,   210,   293,   339,   197,   178,   179,   180,
     192,     0,   176,   183,   194,   195,   196,   184,   185,   188,
     190,   186,   187,   181,   182,   189,   193,   191,   291,   290,
     289,     0,   286,   288,   321,   323,   337,   327,   329,   333,
     331,   335,   325,   318,   314,     0,   304,   305,   315,   316,
     317,   311,   307,   312,   309,   310,   313,   308,   117,   125,
       0,   244,   242,   247,     0,   237,   241,   238,     0,   227,
     228,   230,   240,   231,   232,   233,   246,   234,   235,   236,
     271,     0,   269,   270,   273,   274,     0,   261,   262,   264,
     265,   266,   267,   268,   157,   159,   154,     0,   152,   155,
     156,    37,     0,     0,    31,     0,     0,     0,     0,     0,
      44,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    95,
     349,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   175,     0,     0,   285,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   302,     0,
       0,     0,     0,     0,     0,     0,     0,   225,     0,     0,
       0,   259,     0,     0,     0,     0,   151,    43,    34,     0,
       0,     0,     0,     0,    48,     0,    86,    87,     0,     0,
       0,    82,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,   379,     0,     0,    59,     0,     0,    91,
     361,   359,   360,   355,   356,   357,   358,     0,   350,   351,
     353,   354,     0,     0,     0,     0,     0,     0,     0,   214,
     215,     0,     0,     0,     0,   177,     0,   287,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   306,     0,     0,
     239,     0,     0,     0,   249,   229,     0,   275,   263,     0,
       0,   153,     0,     0,     0,   393,   395,     0,   320,     0,
       0,   168,   218,   252,     0,     0,   144,     0,     0,     0,
       0,    38,    97,   100,   101,    99,     0,   348,     0,   201,
     203,   205,   278,   199,   207,   209,   213,   211,   295,     0,
     292,   322,   324,   338,   328,   330,   334,   332,   336,   326,
     118,   126,   245,   243,   248,   272,   158,   160,    35,     0,
     401,     0,   398,   400,     0,   119,   121,   123,     0,     0,
       0,   116,     0,   106,   108,   109,   110,   111,   112,   113,
     114,   115,     0,   172,     0,   169,   170,   222,     0,   219,
     220,   256,     0,   253,   254,   130,   139,   140,   141,   135,
       0,   133,   136,   137,   138,   345,     0,   148,     0,   145,
     146,     0,     0,   163,   375,     0,     0,     0,   373,   367,
     372,     0,   365,   370,   368,   369,   371,   386,   388,     0,
     382,   384,   385,     0,    40,     0,   352,   282,     0,   279,
     280,   299,     0,   296,   297,   341,     0,    55,     0,     0,
     397,    89,     0,     0,     0,     0,     0,     0,     0,   103,
     105,     0,   167,     0,   226,   217,     0,   260,   251,     0,
       0,   132,     0,   344,     0,   143,     0,     0,     0,   162,
       0,     0,     0,     0,     0,   364,     0,     0,     0,   381,
     391,     0,   362,     0,   277,     0,   303,   294,     0,     0,
     340,     0,   399,     0,     0,     0,   127,   128,   129,   107,
       0,   171,     0,   221,     0,   255,   134,   346,     0,   147,
     165,   164,     0,   374,   377,   378,   366,     0,     0,   383,
      39,     0,   281,     0,   298,     0,     0,   120,   122,   124,
     173,   223,   257,   149,   376,   387,   389,   283,   300,   342,
     405,     0,   403,     0,     0,   402,   417,     0,   415,   413,
     409,     0,   407,   411,   412,   410,   404,     0,     0,     0,
       0,   406,     0,   414,     0,   408,     0,   416,   421,     0,
     419,     0,     0,   418,   425,     0,   423,   420,     0,     0,
     422,     0,   424,   426
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,     3,  -411,  -411,  -411,  -411,   -57,  -411,  -411,
      34,  -411,  -104,  -411,   -54,  -411,  -411,  -411,   196,  -411,
    -411,  -411,  -411,    30,   174,   -56,   -40,   -38,  -411,  -411,
     -37,  -411,  -411,    33,   173,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,    36,  -119,  -398,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,   -59,  -411,  -410,  -411,
    -411,  -411,  -411,  -411,  -411,  -128,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -133,  -411,  -411,  -411,  -130,   130,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -131,  -411,  -411,  -411,
    -411,  -113,  -411,  -411,  -411,  -108,   175,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -399,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -111,
    -411,  -411,  -411,  -107,  -411,   152,  -411,   -52,  -411,  -411,
    -411,  -411,   -48,  -411,  -411,  -411,  -411,  -411,   -47,  -411,
    -411,  -411,  -106,  -411,  -411,  -411,  -103,  -411,   149,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -129,
    -411,  -411,  -411,  -126,   181,  -411,  -411,  -411,  -411,  -411,
    -411,  -118,  -411,  -411,  -411,  -127,  -411,   180,   -43,  -411,
    -257,  -411,  -256,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,    42,  -411,
    -411,  -411,  -411,  -411,  -411,  -101,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -102,  -411,  -411,  -411,  -411,
    -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,  -411,   -68,
    -411,  -411,  -411,  -170,  -411,  -411,  -185,  -411,  -411,  -411,
    -411,  -411,  -411,  -195,  -411,  -411,  -201,  -411
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    63,    31,    32,    53,    67,    68,    33,    52,
     432,   544,    64,    65,   102,    35,    54,    75,    76,    77,
     246,    37,    55,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   253,   128,   129,    39,    56,   130,   276,   131,
     277,   435,   112,   257,   113,   258,   482,   483,   206,   310,
     485,   562,   486,   563,   487,   564,   207,   311,   489,   490,
     491,   509,   114,   266,   510,   511,   512,   513,   514,   115,
     268,   518,   519,   520,   584,    51,    62,   237,   238,   239,
     323,   240,   324,   116,   269,   522,   523,   117,   263,   494,
     495,   496,   571,    41,    57,   151,   152,   153,   285,   154,
     281,   155,   282,   156,   283,   157,   286,   158,   287,   159,
     291,   160,   290,   161,   162,   118,   264,   498,   499,   500,
     574,    47,    60,   208,   209,   210,   211,   212,   213,   214,
     215,   314,   216,   313,   217,   218,   315,   219,   119,   265,
     502,   503,   504,   577,    49,    61,   226,   227,   228,   229,
     230,   319,   231,   232,   233,   164,   284,   548,   549,   550,
     603,    43,    58,   171,   172,   173,   296,   165,   292,   552,
     553,   554,   606,    45,    59,   185,   186,   187,   120,   256,
     189,   299,   190,   300,   191,   307,   192,   302,   193,   303,
     194,   305,   195,   304,   196,   306,   197,   301,   167,   293,
     556,   609,   121,   267,   516,   280,   367,   368,   369,   370,
     371,   436,   122,   270,   531,   532,   533,   534,   590,   535,
     536,   123,   124,   272,   539,   540,   541,   596,   542,   597,
     125,   273,    78,   248,    79,   249,    80,   247,   471,   472,
     473,   558,   661,   662,   663,   671,   672,   673,   674,   679,
     675,   677,   689,   690,   691,   695,   696,   698
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      74,   147,   223,   146,   169,   183,   205,   222,   236,   224,
     163,   170,   184,   225,   166,    30,   188,   148,   530,   149,
     150,   484,   484,   365,   366,    23,   515,    24,    69,    25,
     529,   132,    34,   132,   251,   274,    93,    22,   278,   252,
     275,    83,    84,   279,   234,   235,   168,    36,   199,   220,
     200,   201,   221,   294,    87,    88,    89,   297,   295,   133,
     134,   135,   298,    93,   198,   475,   476,   477,   478,   479,
     480,    38,   136,    40,   137,   138,   139,   140,   141,   142,
      42,   199,    81,   143,   144,   143,    44,    82,    83,    84,
     145,   199,    85,    86,    84,   174,   175,    73,   234,   235,
      70,    87,    88,    89,    90,    91,    71,    72,    73,    92,
      93,    84,   174,   175,   325,    93,   199,    46,    73,   326,
      26,    27,    28,    29,    73,    48,   274,    94,    95,    73,
     580,   557,    93,   581,   360,   666,   198,   667,   668,    96,
     478,    73,    97,    98,   582,   198,    50,   583,    99,   100,
     176,    73,   101,    66,   177,   178,   179,   180,   181,   241,
     182,   559,   199,   242,   200,   201,   560,   202,   203,   204,
     484,    73,   278,   568,   568,   588,    73,   561,   569,   570,
     589,   365,   366,   627,   530,   594,   524,   525,   526,   527,
     595,   664,   692,    73,   665,   693,   529,    74,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,   243,   598,
     245,   294,   325,    73,   599,   600,   650,   653,   297,   680,
     699,   362,    73,   657,   681,   700,   361,   505,   506,   507,
     508,   126,   127,   363,   433,   434,   244,   364,   147,   245,
     146,   537,   538,   169,   250,   327,   328,   163,   254,   255,
     170,   166,   259,   260,   148,   183,   149,   150,   261,   262,
     271,   288,   184,   223,   205,   289,   188,   308,   222,   309,
     224,   312,   316,   317,   225,   318,   329,   320,   321,   322,
     336,   330,   331,   332,   333,   335,   337,   338,   339,   340,
     345,   341,   342,   343,   344,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   357,   358,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     386,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     398,   399,   400,   401,   402,   415,   416,   403,   404,   406,
     407,   409,   410,   412,   437,   470,   418,   413,   414,   417,
     419,   420,   421,   422,   423,   424,   425,   426,   431,   442,
     488,   488,   427,   428,   429,   481,   481,   430,   438,   439,
     449,   440,   448,   543,   528,   441,   493,   497,   501,   362,
     517,   545,   443,   547,   361,   551,   565,   444,   445,   446,
     447,   363,   566,   567,   573,   364,   572,   576,   450,   575,
     579,   578,   585,   586,   604,   587,   591,   592,   593,   605,
     451,   452,   608,   467,   607,   468,   611,   613,   610,   614,
     615,   632,   637,   638,   453,   645,   640,   646,   454,   686,
     660,   455,   456,   651,   457,   652,   658,   678,   682,   684,
     601,   555,   701,   469,   688,   458,   459,   334,   356,   619,
     474,   359,   626,   629,   628,   411,   492,   631,   460,   461,
     621,   462,   463,   620,   464,   623,   465,   622,   466,   385,
     405,   408,   521,   625,   624,   602,   642,   641,   387,   643,
     546,   617,   616,   647,   618,   630,   633,   634,   635,   397,
     644,   612,   648,   636,   676,   685,   639,   697,   702,   649,
       0,     0,     0,     0,     0,   654,     0,   655,     0,   488,
       0,   656,     0,     0,   481,   147,     0,   146,   223,     0,
     205,     0,     0,   222,   163,   224,   659,   694,   166,   225,
     236,   148,   683,   149,   150,     0,   687,     0,     0,   703,
     528,     0,     0,     0,     0,     0,     0,     0,     0,   169,
       0,     0,   183,     0,     0,     0,   170,     0,     0,   184,
       0,     0,     0,   188,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   670,     0,     0,     0,     0,   669,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   670,     0,     0,     0,     0,   669
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      54,    57,    61,    57,    58,    59,    60,    61,    62,    61,
      57,    58,    59,    61,    57,    12,    59,    57,   428,    57,
      57,   419,   420,   280,   280,     5,   425,     7,    10,     9,
     428,     7,     7,     7,     3,     3,    39,     0,     3,     8,
       8,    17,    18,     8,    69,    70,    49,     7,    40,    41,
      42,    43,    44,     3,    30,    31,    32,     3,     8,    35,
      36,    37,     8,    39,    23,    24,    25,    26,    27,    28,
      29,     7,    48,     7,    50,    51,    52,    53,    54,    55,
       7,    40,    11,    59,    60,    59,     7,    16,    17,    18,
      66,    40,    21,    22,    18,    19,    20,   100,    69,    70,
      82,    30,    31,    32,    33,    34,    88,    89,   100,    38,
      39,    18,    19,    20,     3,    39,    40,     7,   100,     8,
     100,   101,   102,   103,   100,     7,     3,    56,    57,   100,
       3,     8,    39,     6,    58,    84,    23,    86,    87,    68,
      27,   100,    71,    72,     3,    23,     7,     6,    77,    78,
      57,   100,    81,   100,    61,    62,    63,    64,    65,     6,
      67,     3,    40,     3,    42,    43,     8,    45,    46,    47,
     568,   100,     3,     3,     3,     3,   100,     8,     8,     8,
       8,   438,   438,   582,   594,     3,    73,    74,    75,    76,
       8,     3,     3,   100,     6,     6,   594,   251,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,     4,     3,
       3,     3,     3,   100,     8,     8,     8,     8,     3,     3,
       3,   280,   100,     8,     8,     8,   280,    61,    62,    63,
      64,    12,    13,   280,    14,    15,     8,   280,   294,     3,
     294,    79,    80,   297,     4,   242,   243,   294,     4,     4,
     297,   294,     4,     4,   294,   309,   294,   294,     4,     4,
       4,     4,   309,   322,   318,     4,   309,     8,   322,     3,
     322,     4,     4,     8,   322,     3,   100,     4,     8,     3,
     103,     4,     4,     4,     4,     4,   103,     4,     4,     4,
       4,   101,   101,   101,   101,     4,     4,     4,     4,     4,
       4,     4,   101,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   101,   103,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   101,     4,     4,   332,   333,     4,   103,     4,
     103,     4,     4,     4,     8,    83,   100,     7,     7,     7,
       7,     7,     5,     5,     5,     5,     5,     5,     5,     5,
     419,   420,     7,     7,     7,   419,   420,     7,     3,   100,
       7,   100,     5,   430,   428,   100,     7,     7,     7,   438,
       7,     4,   100,     7,   438,     7,     4,   100,   100,   100,
     100,   438,     4,     4,     3,   438,     6,     3,   100,     6,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     3,
     100,   100,     3,   410,     6,   412,     4,     4,     8,     4,
       4,     4,     4,     4,   390,     4,     6,     5,   100,     5,
       7,   100,   100,     8,   100,     8,     8,     4,     4,     4,
     544,    67,     4,   413,     7,   100,   100,   251,   274,   568,
     417,   278,   580,   586,   584,   325,   420,   588,   100,   100,
     573,   100,   100,   571,   100,   576,   100,   574,   100,   294,
     318,   322,   100,   579,   577,   100,   605,   603,   297,   606,
     438,   101,   103,   100,   103,   101,   101,   101,   101,   309,
     608,   559,   100,   594,   664,   680,   598,   692,   699,   100,
      -1,    -1,    -1,    -1,    -1,   100,    -1,   100,    -1,   568,
      -1,   100,    -1,    -1,   568,   571,    -1,   571,   577,    -1,
     574,    -1,    -1,   577,   571,   577,   100,    85,   571,   577,
     584,   571,   101,   571,   571,    -1,   100,    -1,    -1,   100,
     594,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   603,
      -1,    -1,   606,    -1,    -1,    -1,   603,    -1,    -1,   606,
      -1,    -1,    -1,   606,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   663,    -1,    -1,    -1,    -1,   663,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   680,    -1,    -1,    -1,    -1,   680
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     0,     5,     7,     9,   100,   101,   102,   103,
     116,   117,   118,   122,     7,   129,     7,   135,     7,   149,
       7,   207,     7,   275,     7,   287,     7,   235,     7,   258,
       7,   189,   123,   119,   130,   136,   150,   208,   276,   288,
     236,   259,   190,   116,   126,   127,   100,   120,   121,    10,
      82,    88,    89,   100,   128,   131,   132,   133,   346,   348,
     350,    11,    16,    17,    18,    21,    22,    30,    31,    32,
      33,    34,    38,    39,    56,    57,    68,    71,    72,    77,
      78,    81,   128,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   156,   158,   176,   183,   197,   201,   229,   252,
     292,   316,   326,   335,   336,   344,    12,    13,   147,   148,
     151,   153,     7,    35,    36,    37,    48,    50,    51,    52,
      53,    54,    55,    59,    60,    66,   128,   139,   140,   141,
     144,   209,   210,   211,   213,   215,   217,   219,   221,   223,
     225,   227,   228,   252,   269,   281,   292,   312,    49,   128,
     252,   277,   278,   279,    19,    20,    57,    61,    62,    63,
      64,    65,    67,   128,   252,   289,   290,   291,   292,   294,
     296,   298,   300,   302,   304,   306,   308,   310,    23,    40,
      42,    43,    45,    46,    47,   128,   162,   170,   237,   238,
     239,   240,   241,   242,   243,   244,   246,   248,   249,   251,
      41,    44,   128,   170,   241,   246,   260,   261,   262,   263,
     264,   266,   267,   268,    69,    70,   128,   191,   192,   193,
     195,     6,     3,     4,     8,     3,   134,   351,   347,   349,
       4,     3,     8,   146,     4,     4,   293,   157,   159,     4,
       4,     4,     4,   202,   230,   253,   177,   317,   184,   198,
     327,     4,   337,   345,     3,     8,   152,   154,     3,     8,
     319,   214,   216,   218,   270,   212,   220,   222,     4,     4,
     226,   224,   282,   313,     3,     8,   280,     3,     8,   295,
     297,   311,   301,   303,   307,   305,   309,   299,     8,     3,
     163,   171,     4,   247,   245,   250,     4,     8,     3,   265,
       4,     8,     3,   194,   196,     3,     8,   116,   116,   100,
       4,     4,     4,     4,   132,     4,   103,   103,     4,     4,
       4,   101,   101,   101,   101,     4,     4,     4,     4,     4,
       4,     4,     4,   101,     4,     4,   138,     4,     4,   148,
      58,   128,   170,   252,   292,   294,   296,   320,   321,   322,
     323,   324,     4,     4,     4,     4,     4,     4,     4,   101,
     103,     4,     4,     4,     4,   210,     4,   278,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   291,     4,     4,
     101,     4,     4,     4,   103,   239,     4,   103,   262,     4,
       4,   192,     4,     7,     7,   116,   116,     7,   100,     7,
       7,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   124,    14,    15,   155,   325,     8,     3,   100,
     100,   100,     5,   100,   100,   100,   100,   100,     5,     7,
     100,   100,   100,   124,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   116,   116,   137,
      83,   352,   353,   354,   147,    24,    25,    26,    27,    28,
      29,   128,   160,   161,   162,   164,   166,   168,   170,   172,
     173,   174,   160,     7,   203,   204,   205,     7,   231,   232,
     233,     7,   254,   255,   256,    61,    62,    63,    64,   175,
     178,   179,   180,   181,   182,   223,   318,     7,   185,   186,
     187,   100,   199,   200,    73,    74,    75,    76,   128,   162,
     172,   328,   329,   330,   331,   333,   334,    79,    80,   338,
     339,   340,   342,   121,   125,     4,   322,     7,   271,   272,
     273,     7,   283,   284,   285,    67,   314,     8,   355,     3,
       8,     8,   165,   167,   169,     4,     4,     4,     3,     8,
       8,   206,     6,     3,   234,     6,     3,   257,     6,     3,
       3,     6,     3,     6,   188,     6,     3,     4,     3,     8,
     332,     4,     4,     4,     3,     8,   341,   343,     3,     8,
       8,   126,   100,   274,     6,     3,   286,     6,     3,   315,
       8,     4,   353,     4,     4,     4,   103,   101,   103,   161,
     209,   205,   237,   233,   260,   256,   179,   223,   191,   187,
     101,   200,     4,   101,   101,   101,   329,     4,     4,   339,
       6,   277,   273,   289,   285,     4,     5,   100,   100,   100,
       8,     8,     8,     8,   100,   100,   100,     8,     8,   100,
       7,   356,   357,   358,     3,     6,    84,    86,    87,   128,
     170,   359,   360,   361,   362,   364,   357,   365,     4,   363,
       3,     8,     4,   101,     4,   360,     5,   100,     7,   366,
     367,   368,     3,     6,    85,   369,   370,   367,   371,     3,
       8,     4,   370,   100
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   104,   106,   105,   107,   105,   108,   105,   109,   105,
     110,   105,   111,   105,   112,   105,   113,   105,   114,   105,
     115,   105,   116,   116,   116,   116,   116,   116,   116,   117,
     119,   118,   120,   120,   121,   121,   123,   122,   125,   124,
     126,   126,   127,   127,   128,   130,   129,   131,   131,   132,
     132,   132,   132,   132,   134,   133,   136,   135,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   139,   140,   141,   142,   143,   144,   146,   145,
     147,   147,   148,   148,   150,   149,   152,   151,   154,   153,
     155,   155,   157,   156,   159,   158,   160,   160,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   163,   162,   165,
     164,   167,   166,   169,   168,   171,   170,   172,   173,   174,
     175,   177,   176,   178,   178,   179,   179,   179,   179,   180,
     181,   182,   184,   183,   185,   185,   186,   186,   188,   187,
     190,   189,   191,   191,   191,   192,   192,   194,   193,   196,
     195,   198,   197,   199,   199,   200,   202,   201,   203,   203,
     204,   204,   206,   205,   208,   207,   209,   209,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   212,   211,
     214,   213,   216,   215,   218,   217,   220,   219,   222,   221,
     224,   223,   226,   225,   227,   228,   230,   229,   231,   231,
     232,   232,   234,   233,   236,   235,   237,   237,   238,   238,
     239,   239,   239,   239,   239,   239,   239,   239,   240,   241,
     242,   243,   245,   244,   247,   246,   248,   250,   249,   251,
     253,   252,   254,   254,   255,   255,   257,   256,   259,   258,
     260,   260,   261,   261,   262,   262,   262,   262,   262,   262,
     263,   265,   264,   266,   267,   268,   270,   269,   271,   271,
     272,   272,   274,   273,   276,   275,   277,   277,   278,   278,
     278,   280,   279,   282,   281,   283,   283,   284,   284,   286,
     285,   288,   287,   289,   289,   290,   290,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   293,
     292,   295,   294,   297,   296,   299,   298,   301,   300,   303,
     302,   305,   304,   307,   306,   309,   308,   311,   310,   313,
     312,   315,   314,   317,   316,   318,   318,   319,   223,   320,
     320,   321,   321,   322,   322,   322,   322,   322,   322,   322,
     323,   325,   324,   327,   326,   328,   328,   329,   329,   329,
     329,   329,   329,   329,   330,   332,   331,   333,   334,   335,
     337,   336,   338,   338,   339,   339,   341,   340,   343,   342,
     345,   344,   347,   346,   349,   348,   351,   350,   352,   352,
     353,   355,   354,   356,   356,   358,   357,   359,   359,   360,
     360,   360,   360,   360,   361,   363,   362,   365,   364,   366,
     366,   368,   367,   369,   369,   371,   370
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
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     0,     4
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
  "\"array\"", "\"pools\"", "\"pool\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
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
  "map_content", "not_empty_map", "list_generic", "$@12", "list2", "$@13",
  "list_content", "not_empty_list", "unknown_map_entry", "syntax_map",
  "$@14", "global_objects", "global_object", "dhcp4_object", "$@15",
  "sub_dhcp4", "$@16", "global_params", "global_param", "valid_lifetime",
  "renew_timer", "rebind_timer", "decline_probation_period",
  "echo_client_id", "match_client_id", "interfaces_config", "$@17",
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
  "control_socket_param", "control_socket_type", "$@81",
  "control_socket_name", "$@82", "dhcp_ddns", "$@83", "dhcp6_json_object",
  "$@84", "dhcpddns_json_object", "$@85", "logging_object", "$@86",
  "logging_params", "logging_param", "loggers", "$@87", "loggers_entries",
  "logger_entry", "$@88", "logger_params", "logger_param", "debuglevel",
  "severity", "$@89", "output_options_list", "$@90",
  "output_options_list_content", "output_entry", "$@91", "output_params",
  "output_param", "$@92", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   201,   201,   201,   202,   202,   203,   203,   204,   204,
     205,   205,   206,   206,   207,   207,   208,   208,   209,   209,
     210,   210,   218,   219,   220,   221,   222,   223,   224,   227,
     232,   232,   244,   245,   248,   252,   259,   259,   267,   267,
     274,   275,   278,   282,   293,   303,   303,   315,   316,   320,
     321,   322,   323,   324,   327,   327,   344,   344,   352,   353,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   382,   387,   392,   397,   402,   407,   413,   413,
     423,   424,   427,   428,   431,   431,   439,   439,   449,   449,
     456,   457,   460,   460,   470,   470,   480,   481,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   495,   495,   503,
     503,   511,   511,   519,   519,   527,   527,   535,   540,   545,
     550,   555,   555,   565,   566,   569,   570,   571,   572,   575,
     580,   585,   590,   590,   600,   601,   604,   605,   608,   608,
     616,   616,   624,   625,   626,   629,   630,   633,   633,   641,
     641,   649,   649,   659,   660,   666,   674,   674,   687,   688,
     691,   692,   699,   699,   722,   722,   731,   732,   736,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,   754,   755,   758,   758,
     766,   766,   774,   774,   782,   782,   790,   790,   798,   798,
     806,   806,   814,   814,   822,   827,   836,   836,   848,   849,
     852,   853,   858,   858,   869,   869,   879,   880,   883,   884,
     887,   888,   889,   890,   891,   892,   893,   894,   897,   899,
     904,   906,   908,   908,   916,   916,   924,   926,   926,   934,
     943,   943,   955,   956,   961,   962,   967,   967,   978,   978,
     989,   990,   995,   996,  1001,  1002,  1003,  1004,  1005,  1006,
    1009,  1011,  1011,  1019,  1021,  1023,  1031,  1031,  1043,  1044,
    1047,  1048,  1051,  1051,  1059,  1059,  1067,  1068,  1071,  1072,
    1073,  1076,  1076,  1087,  1087,  1097,  1098,  1101,  1102,  1105,
    1105,  1113,  1113,  1121,  1122,  1125,  1126,  1130,  1131,  1132,
    1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1144,
    1144,  1152,  1152,  1160,  1160,  1168,  1168,  1176,  1176,  1184,
    1184,  1192,  1192,  1200,  1200,  1209,  1209,  1217,  1217,  1230,
    1230,  1240,  1240,  1251,  1251,  1261,  1262,  1265,  1265,  1273,
    1274,  1277,  1278,  1281,  1282,  1283,  1284,  1285,  1286,  1287,
    1290,  1292,  1292,  1303,  1303,  1313,  1314,  1317,  1318,  1319,
    1320,  1321,  1322,  1323,  1326,  1331,  1331,  1339,  1344,  1351,
    1358,  1358,  1368,  1369,  1372,  1373,  1376,  1376,  1384,  1384,
    1394,  1394,  1406,  1406,  1413,  1413,  1425,  1425,  1438,  1439,
    1443,  1447,  1447,  1459,  1460,  1464,  1464,  1472,  1473,  1476,
    1477,  1478,  1479,  1480,  1483,  1487,  1487,  1495,  1495,  1505,
    1506,  1509,  1509,  1517,  1518,  1521,  1521
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
#line 3517 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1529 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
