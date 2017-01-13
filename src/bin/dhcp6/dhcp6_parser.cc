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
      case 140: // value
      case 388: // ncr_protocol_value
      case 397: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 125: // "boolean"
        value.move< bool > (that.value);
        break;

      case 124: // "floating point"
        value.move< double > (that.value);
        break;

      case 123: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 122: // "constant string"
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
      case 140: // value
      case 388: // ncr_protocol_value
      case 397: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 125: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 124: // "floating point"
        value.copy< double > (that.value);
        break;

      case 123: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 122: // "constant string"
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
            case 122: // "constant string"

#line 194 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 356 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 123: // "integer"

#line 194 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 363 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 124: // "floating point"

#line 194 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 370 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 125: // "boolean"

#line 194 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 377 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 140: // value

#line 194 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 384 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 388: // ncr_protocol_value

#line 194 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 391 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 397: // replace_client_name_value

#line 194 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 140: // value
      case 388: // ncr_protocol_value
      case 397: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 125: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 124: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 123: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 122: // "constant string"
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
#line 203 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 204 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 205 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 206 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 207 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 208 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 209 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 210 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 211 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 212 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 213 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 214 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 757 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 840 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 906 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 933 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 391 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1007 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 547 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), value);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 703 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1581 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1590 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1618 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1643 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 907 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 940 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 1929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2030 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1206 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1218 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2088 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1224 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2106 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1232 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1234 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1258 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2182 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1314 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2332 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2406 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2433 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2451 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1506 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1507 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2533 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2604 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1555 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2628 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2729 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2739 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2774 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2804 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2812 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2830 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -499;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     212,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,    56,    26,    66,    91,   108,   129,   138,
     148,   150,   157,   180,   187,   199,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
      26,   -60,    12,    77,    63,    19,    22,    51,    99,    17,
      93,    11,   151,  -499,   170,   207,   174,   208,   224,  -499,
    -499,  -499,  -499,   250,  -499,    55,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,   251,   252,   254,   255,   256,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,   257,
    -499,  -499,  -499,   132,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,   239,  -499,  -499,
    -499,  -499,  -499,  -499,   258,   259,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,   134,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,   169,  -499,  -499,  -499,   260,  -499,   262,   263,
    -499,  -499,   171,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,   266,   265,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,   267,  -499,
    -499,  -499,   271,  -499,  -499,  -499,   268,   275,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,   277,
    -499,  -499,  -499,  -499,   274,   280,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,   172,  -499,  -499,  -499,   281,
    -499,  -499,   288,  -499,   289,   291,  -499,  -499,   296,   298,
     299,   300,  -499,  -499,  -499,   181,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,    26,    26,  -499,   162,   301,   302,   303,
     305,  -499,    12,  -499,   307,   308,   309,   147,   191,   192,
     195,   196,   312,   313,   316,   330,   331,   332,   333,   334,
     335,   336,   218,   338,   339,    77,  -499,   340,  -499,    16,
     341,   342,   343,   344,   345,   227,   226,   348,   349,   350,
     351,    19,  -499,   352,    22,  -499,   353,   235,   355,   237,
     238,    51,  -499,   358,   359,   360,   361,   362,   363,  -499,
      99,   364,   365,   247,   367,   368,   369,   249,  -499,    17,
     371,   253,  -499,    93,   372,   373,   -29,  -499,   261,   375,
     376,   264,   377,   269,   270,   378,   379,   272,   273,   276,
     278,   380,   381,   151,  -499,  -499,  -499,   384,   382,   383,
      26,    26,  -499,   387,   388,   389,  -499,  -499,  -499,  -499,
    -499,   386,   394,   395,   397,   399,   402,   403,   404,   405,
     406,  -499,   407,   408,  -499,   399,  -499,  -499,  -499,  -499,
     409,   413,  -499,  -499,  -499,   416,   417,   306,   310,   311,
    -499,  -499,   314,   317,   418,   411,  -499,   319,  -499,   320,
    -499,   321,  -499,  -499,  -499,   399,   399,   399,   323,   324,
     325,  -499,   326,   327,  -499,   328,   329,   337,  -499,  -499,
     346,  -499,  -499,   347,    26,  -499,  -499,   354,   356,  -499,
     366,  -499,  -499,   -68,   357,  -499,  -499,  -499,  -499,    70,
     370,  -499,    26,    77,   322,  -499,  -499,    63,    92,    92,
     422,   423,   424,   -25,  -499,  -499,    20,    27,   427,   374,
      45,   175,   151,  -499,   420,  -499,    16,   428,   446,  -499,
    -499,  -499,  -499,  -499,   448,   391,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,   182,  -499,
     183,  -499,  -499,   449,  -499,  -499,  -499,   454,   456,   457,
    -499,   190,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,   193,  -499,   458,   459,  -499,  -499,   460,   462,  -499,
    -499,   461,   467,  -499,  -499,  -499,    34,  -499,  -499,  -499,
      26,  -499,  -499,    68,  -499,  -499,  -499,   223,  -499,   465,
     469,  -499,   470,   194,  -499,  -499,   471,   473,   476,  -499,
    -499,  -499,   197,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
     200,  -499,  -499,  -499,   201,   385,  -499,  -499,   475,   479,
    -499,  -499,   477,   481,  -499,  -499,   480,   482,  -499,  -499,
     455,  -499,   483,   322,  -499,  -499,   485,   486,   487,   285,
     390,   286,    92,  -499,  -499,    19,  -499,   422,    17,  -499,
     423,    93,  -499,   424,   -25,  -499,   488,    20,  -499,    27,
    -499,    11,  -499,   427,   392,   374,  -499,   489,   393,   396,
     398,    45,  -499,   491,   494,   175,  -499,  -499,  -499,    22,
    -499,   428,    51,  -499,   446,    99,  -499,   448,   495,  -499,
     468,  -499,   400,   401,   410,  -499,  -499,  -499,  -499,   204,
    -499,   492,  -499,   493,  -499,  -499,  -499,  -499,  -499,   210,
    -499,  -499,  -499,   412,  -499,  -499,  -499,  -499,   414,   415,
    -499,   214,  -499,   216,  -499,   496,  -499,   419,   498,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,   243,  -499,    59,   498,  -499,  -499,
     499,  -499,  -499,  -499,   217,  -499,  -499,  -499,  -499,  -499,
     502,   421,   504,    59,  -499,   497,  -499,   425,  -499,   503,
    -499,  -499,   245,  -499,   426,   503,  -499,  -499,   220,  -499,
    -499,   505,   426,  -499,   429,  -499,  -499
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    40,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    49,     5,
      60,     7,    93,     9,   174,    11,   275,    13,   292,    15,
     318,    17,   215,    19,   249,    21,   150,    23,   394,    25,
      44,    36,     0,     0,     0,     0,     0,     0,   320,   217,
     251,     0,     0,    46,     0,    45,     0,     0,    37,    58,
     447,   443,   445,     0,    57,     0,    51,    53,    55,    56,
      54,    91,    97,    99,     0,     0,     0,     0,     0,   166,
     207,   241,   125,   140,   133,   348,   142,   161,   365,     0,
     382,   392,    85,     0,    62,    64,    65,    66,    67,    68,
      70,    71,    72,    73,    75,    74,    79,    80,    69,    77,
      78,    76,    81,    82,    83,    84,    95,     0,   352,   267,
     284,   195,   197,   199,     0,     0,   203,   201,   310,   344,
     194,   178,   179,   180,   181,     0,   176,   185,   186,   187,
     190,   192,   188,   189,   182,   183,   184,   191,   193,   282,
     281,   280,     0,   277,   279,   303,     0,   306,     0,     0,
     302,   299,     0,   294,   296,   297,   300,   301,   298,   342,
     332,   334,   336,   338,   340,   331,   330,     0,   321,   322,
     326,   327,   324,   328,   329,   325,   112,   120,     0,   235,
     233,   238,     0,   228,   232,   229,     0,   218,   219,   221,
     231,   222,   223,   224,   237,   225,   226,   227,   262,     0,
     260,   261,   264,   265,     0,   252,   253,   255,   256,   257,
     258,   259,   157,   159,   154,     0,   152,   155,   156,     0,
     415,   417,     0,   420,     0,     0,   424,   428,     0,     0,
       0,     0,   434,   441,   413,     0,   396,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,    41,     0,     0,    35,     0,     0,     0,     0,
       0,    48,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    94,   354,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   175,     0,     0,   276,     0,     0,     0,     0,
       0,     0,   293,     0,     0,     0,     0,     0,     0,   319,
       0,     0,     0,     0,     0,     0,     0,     0,   216,     0,
       0,     0,   250,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   395,    47,    38,     0,     0,     0,
       0,     0,    52,     0,     0,     0,    86,    87,    88,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   381,     0,     0,    63,     0,   363,   361,   362,   360,
       0,   355,   356,   358,   359,     0,     0,     0,     0,     0,
     205,   206,     0,     0,     0,     0,   177,     0,   278,     0,
     305,     0,   308,   309,   295,     0,     0,     0,     0,     0,
       0,   323,     0,     0,   230,     0,     0,     0,   240,   220,
       0,   266,   254,     0,     0,   153,   414,     0,     0,   419,
       0,   422,   423,     0,     0,   430,   431,   432,   433,     0,
       0,   397,     0,     0,     0,   444,   446,     0,     0,     0,
     168,   209,   243,     0,    42,   141,     0,     0,   144,     0,
       0,     0,     0,    96,     0,   353,     0,   269,   286,   196,
     198,   200,   204,   202,   312,     0,   283,   304,   307,   343,
     333,   335,   337,   339,   341,   113,   121,   236,   234,   239,
     263,   158,   160,   416,   418,   421,   426,   427,   425,   429,
     436,   437,   438,   439,   440,   435,   442,    39,     0,   452,
       0,   449,   451,     0,   114,   116,   118,     0,     0,     0,
     111,     0,   101,   103,   104,   105,   106,   107,   108,   109,
     110,     0,   172,     0,   169,   170,   213,     0,   210,   211,
     247,     0,   244,   245,   131,   132,     0,   127,   129,   130,
      44,   139,   137,     0,   135,   138,   350,     0,   148,     0,
     145,   146,     0,     0,   163,   377,     0,     0,     0,   375,
     369,   374,     0,   367,   372,   370,   371,   373,   388,   390,
       0,   384,   386,   387,     0,     0,   357,   273,     0,   270,
     271,   290,     0,   287,   288,   316,     0,   313,   314,   346,
       0,    59,     0,     0,   448,    92,     0,     0,     0,     0,
       0,     0,     0,    98,   100,     0,   167,     0,   217,   208,
       0,   251,   242,     0,     0,   126,     0,     0,   134,     0,
     349,     0,   143,     0,     0,     0,   162,     0,     0,     0,
       0,     0,   366,     0,     0,     0,   383,   393,   364,     0,
     268,     0,     0,   285,     0,   320,   311,     0,     0,   345,
       0,   450,     0,     0,     0,   122,   123,   124,   102,     0,
     171,     0,   212,     0,   246,   128,    43,   136,   351,     0,
     147,   165,   164,     0,   376,   379,   380,   368,     0,     0,
     385,     0,   272,     0,   289,     0,   315,     0,     0,   115,
     117,   119,   173,   214,   248,   149,   378,   389,   391,   274,
     291,   317,   347,   456,     0,   454,     0,     0,   453,   468,
       0,   466,   464,   460,     0,   458,   462,   463,   461,   455,
       0,     0,     0,     0,   457,     0,   465,     0,   459,     0,
     467,   472,     0,   470,     0,     0,   469,   476,     0,   474,
     471,     0,     0,   473,     0,   475,   477
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,    15,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -360,  -499,   -79,  -499,   -62,  -499,  -499,  -499,
     222,  -499,  -499,  -499,  -499,    29,   202,   -45,   -42,   -41,
     -40,  -499,  -499,  -499,  -499,  -499,    31,  -499,  -499,  -499,
    -499,  -499,    35,  -132,  -470,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,   -69,  -499,  -498,  -499,  -499,  -499,  -499,  -499,
    -139,  -475,  -499,  -499,  -499,  -499,  -141,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -146,  -499,  -499,  -499,  -143,   163,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -145,  -499,  -499,
    -499,  -499,  -124,  -499,  -499,  -499,  -120,   209,  -499,  -499,
    -499,  -499,  -499,  -499,  -481,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -122,  -499,  -499,  -499,  -119,  -499,
     184,  -499,   -55,  -499,  -499,  -499,  -499,   -53,  -499,  -499,
    -499,  -499,  -499,   -54,  -499,  -499,  -499,  -121,  -499,  -499,
    -499,  -116,  -499,   185,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -142,  -499,  -499,  -499,  -137,   219,
    -499,  -499,  -499,  -499,  -499,  -499,  -148,  -499,  -499,  -499,
    -138,   215,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -147,  -499,  -499,  -499,  -140,  -499,   211,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,    52,  -499,  -499,  -499,  -499,  -499,  -499,  -118,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -128,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,    57,   177,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,  -499,
    -499,   -81,  -499,  -499,  -499,  -193,  -499,  -499,  -208,  -499,
    -499,  -499,  -499,  -499,  -499,  -219,  -499,  -499,  -225,  -499
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,    77,    78,
      37,    60,   495,   590,    74,    75,   112,    39,    62,    85,
      86,    87,   287,    41,    63,   113,   114,   115,   116,   117,
     118,   119,   120,   294,    43,    64,   137,   317,   121,   295,
     122,   296,   561,   562,   214,   351,   564,   646,   565,   647,
     566,   648,   215,   352,   568,   569,   570,   123,   305,   586,
     587,   588,   589,   124,   307,   593,   594,   595,   125,   306,
     126,   309,   599,   600,   601,   671,    57,    71,   245,   246,
     247,   364,   248,   365,   127,   310,   603,   604,   128,   302,
     573,   574,   575,   655,    45,    65,   155,   156,   157,   322,
     158,   323,   159,   324,   160,   328,   161,   327,   162,   163,
     129,   303,   577,   578,   579,   658,    53,    69,   216,   217,
     218,   219,   220,   221,   222,   223,   355,   224,   354,   225,
     226,   356,   227,   130,   304,   581,   582,   583,   661,    55,
      70,   234,   235,   236,   237,   238,   360,   239,   240,   241,
     165,   320,   628,   629,   630,   689,    47,    66,   172,   173,
     174,   333,   166,   321,   632,   633,   634,   692,    49,    67,
     182,   183,   184,   336,   185,   186,   338,   187,   188,   167,
     329,   636,   637,   638,   695,    51,    68,   197,   198,   199,
     200,   344,   201,   345,   202,   346,   203,   347,   204,   348,
     205,   343,   168,   330,   640,   698,   131,   308,   597,   319,
     420,   421,   422,   423,   424,   504,   132,   311,   612,   613,
     614,   615,   677,   616,   617,   133,   134,   313,   620,   621,
     622,   683,   623,   684,   135,   314,    59,    72,   265,   266,
     267,   268,   369,   269,   370,   270,   271,   372,   272,   273,
     274,   375,   538,   275,   376,   276,   277,   278,   279,   280,
     381,   545,   281,   382,    88,   289,    89,   290,    90,   288,
     550,   551,   552,   642,   754,   755,   756,   764,   765,   766,
     767,   772,   768,   770,   782,   783,   784,   788,   789,   791
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   231,   611,   150,   170,   180,   195,   213,   230,   244,
     264,   164,   171,   181,   196,   232,   596,   233,   563,   563,
     151,   592,    79,   152,   153,   154,   138,   536,   537,    34,
     610,    27,   206,    28,   138,    29,   584,   664,   242,   243,
     665,    94,    95,    96,    97,   101,   207,   207,   101,   208,
     209,   101,   210,   211,   212,   503,    26,   139,   292,   140,
     206,   169,    76,   293,   557,   141,   142,   143,   144,   145,
     146,   667,   416,    38,   668,   136,   147,   148,   242,   243,
     101,   584,   591,   149,   147,   519,   520,   521,    91,   207,
      92,    93,   175,   176,   177,   178,   179,   585,    40,    94,
      95,    96,    97,    98,    99,   100,   101,   206,   554,   555,
     556,   557,   558,   559,    80,    42,   605,   606,   607,   608,
      81,    82,   207,   207,   228,   208,   209,   229,   101,   102,
     103,   104,   105,    83,    83,   315,    44,   331,    83,    83,
     316,    83,   332,   106,    83,    46,   107,   108,    30,    31,
      32,    33,   109,   110,   189,    48,   111,    50,   190,   191,
     192,   193,   194,   759,    52,   760,   761,    83,   540,   541,
     542,   543,   334,    83,   341,   366,   282,   335,   284,   342,
     367,    83,   563,   611,   383,   315,   643,    54,   718,   384,
     641,   644,   592,   652,    56,   544,   652,   675,   653,    83,
     681,   654,   676,   685,   383,   682,    58,   331,   686,   687,
     283,   610,   742,   366,    83,    83,   285,   334,   745,   341,
     773,    83,   749,   792,   750,   774,   669,   286,   793,   670,
      84,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   757,   318,   785,   758,
     418,   786,   618,   619,   291,   297,   298,   417,   299,   300,
     301,   312,   325,   326,   337,   419,   339,   340,   350,   150,
     396,   353,   170,    83,   349,   357,   358,   164,   359,   180,
     171,   361,   362,   363,   387,   368,   151,   181,   195,   152,
     153,   154,   371,   373,   231,   374,   196,   213,   385,   386,
     377,   230,   378,   379,   380,   388,   389,   390,   232,   391,
     233,   393,   394,   395,   397,   398,   401,   402,   399,   400,
     403,   264,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   415,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   437,   439,   440,   441,
     442,   443,   445,   446,   447,   448,   449,   450,   452,   453,
     454,   455,   456,   457,   458,   460,   463,   464,   461,   467,
     468,   470,   473,   474,   479,   480,   466,   469,   482,   483,
     484,   490,   471,   472,   487,   488,   489,   475,   476,   491,
     492,   477,   493,   478,   494,   485,   486,   496,   497,   498,
     705,   707,   499,   500,   501,   502,   506,   505,   515,   567,
     567,   507,   508,   514,   625,   549,   560,   560,   509,   572,
     576,   580,   510,   511,   598,   627,   512,   418,   609,   513,
     264,   516,   517,   518,   417,   522,   523,   524,   525,   526,
     527,   528,   419,   631,   539,   635,   639,   645,   649,   529,
     650,   651,   657,   699,   656,   660,   659,   662,   530,   531,
     663,   672,   673,   738,   674,   678,   533,   679,   534,   532,
     680,   690,   691,   693,   694,   697,   696,   700,   535,   702,
     703,   704,   546,   723,   716,   728,   602,   547,   729,   737,
     743,   744,   779,   771,   751,   753,   775,   688,   777,   794,
     781,   666,   548,   706,   392,   721,   724,   414,   553,   725,
     708,   726,   739,   740,   571,   715,   717,   720,   719,   465,
     722,   787,   741,   710,   746,   709,   747,   748,   712,   711,
     436,   752,   714,   459,   776,   713,   734,   780,   462,   732,
     736,   796,   731,   438,   733,   735,   444,   730,   626,   624,
     481,   451,   701,   727,   769,   778,   790,   795,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   567,     0,     0,     0,     0,     0,     0,
     560,     0,   231,   150,     0,     0,   213,     0,     0,   230,
       0,   164,     0,     0,     0,     0,   232,     0,   233,   244,
     151,     0,     0,   152,   153,   154,     0,     0,     0,   609,
       0,     0,     0,     0,     0,     0,     0,   170,     0,     0,
     180,     0,     0,   195,     0,   171,     0,     0,   181,     0,
       0,   196,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   763,     0,     0,
       0,     0,     0,     0,   762,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   763,     0,     0,     0,     0,     0,
       0,   762
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    70,   500,    65,    66,    67,    68,    69,    70,    71,
      72,    65,    66,    67,    68,    70,   497,    70,   488,   489,
      65,   496,    10,    65,    65,    65,     7,    95,    96,    14,
     500,     5,    15,     7,     7,     9,    61,     3,    67,    68,
       6,    22,    23,    24,    25,    29,    30,    30,    29,    32,
      33,    29,    35,    36,    37,   415,     0,    38,     3,    40,
      15,    39,   122,     8,    19,    46,    47,    48,    49,    50,
      51,     3,    56,     7,     6,    12,    57,    58,    67,    68,
      29,    61,    62,    64,    57,   445,   446,   447,    11,    30,
      13,    14,    41,    42,    43,    44,    45,   122,     7,    22,
      23,    24,    25,    26,    27,    28,    29,    15,    16,    17,
      18,    19,    20,    21,   102,     7,    71,    72,    73,    74,
     108,   109,    30,    30,    31,    32,    33,    34,    29,    52,
      53,    54,    55,   122,   122,     3,     7,     3,   122,   122,
       8,   122,     8,    66,   122,     7,    69,    70,   122,   123,
     124,   125,    75,    76,    55,     7,    79,     7,    59,    60,
      61,    62,    63,   104,     7,   106,   107,   122,    98,    99,
     100,   101,     3,   122,     3,     3,     6,     8,     4,     8,
       8,   122,   652,   681,     3,     3,     3,     7,   669,     8,
       8,     8,   667,     3,     7,   125,     3,     3,     8,   122,
       3,     8,     8,     3,     3,     8,     7,     3,     8,     8,
       3,   681,     8,     3,   122,   122,     8,     3,     8,     3,
       3,   122,     8,     3,     8,     8,     3,     3,     8,     6,
     292,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,     3,     8,     3,     6,
     319,     6,    77,    78,     4,     4,     4,   319,     4,     4,
       4,     4,     4,     4,     4,   319,     4,     4,     3,   331,
     123,     4,   334,   122,     8,     4,     8,   331,     3,   341,
     334,     4,     8,     3,   122,     4,   331,   341,   350,   331,
     331,   331,     4,     4,   363,     4,   350,   359,   283,   284,
       4,   363,     4,     4,     4,     4,     4,     4,   363,     4,
     363,     4,     4,     4,   123,   123,     4,     4,   123,   123,
       4,   383,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,     4,     4,     4,     4,     4,     4,
       4,   123,     4,     4,     4,     4,     4,     4,     4,     4,
     123,   125,     4,     4,     4,     4,     4,     4,   123,     4,
     123,   123,     4,     4,     4,     4,     4,     4,     4,     4,
     123,     4,     4,     4,   125,     4,     4,     4,   125,     4,
       4,     4,     4,     4,     4,     4,   125,   123,     4,     7,
       7,     5,   123,   123,     7,     7,     7,   125,   125,     5,
       5,   125,     5,   125,     5,   390,   391,     5,     5,     5,
     125,   125,     7,     7,     7,     7,     3,     8,     7,   488,
     489,     5,     5,     5,     4,   103,   488,   489,   122,     7,
       7,     7,   122,   122,     7,     7,   122,   506,   500,   122,
     502,   122,   122,   122,   506,   122,   122,   122,   122,   122,
     122,   122,   506,     7,    97,     7,    65,     8,     4,   122,
       4,     4,     3,     8,     6,     3,     6,     6,   122,   122,
       3,     6,     3,     5,     4,     4,   122,     4,   122,   464,
       4,     6,     3,     6,     3,     3,     6,     4,   122,     4,
       4,     4,   122,     4,     6,     4,   122,   482,     4,     4,
       8,     8,     5,     4,     8,     7,     4,   122,     4,     4,
       7,   590,   483,   123,   292,   123,   123,   315,   487,   123,
     652,   123,   122,   122,   489,   664,   667,   673,   671,   366,
     675,   105,   122,   657,   122,   655,   122,   122,   660,   658,
     331,   122,   663,   359,   123,   661,   694,   122,   363,   691,
     697,   122,   689,   334,   692,   695,   341,   685,   506,   502,
     383,   350,   643,   681,   757,   773,   785,   792,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   652,    -1,    -1,    -1,    -1,    -1,    -1,
     652,    -1,   661,   655,    -1,    -1,   658,    -1,    -1,   661,
      -1,   655,    -1,    -1,    -1,    -1,   661,    -1,   661,   671,
     655,    -1,    -1,   655,   655,   655,    -1,    -1,    -1,   681,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   689,    -1,    -1,
     692,    -1,    -1,   695,    -1,   689,    -1,    -1,   692,    -1,
      -1,   695,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   756,    -1,    -1,
      -1,    -1,    -1,    -1,   756,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   773,    -1,    -1,    -1,    -1,    -1,
      -1,   773
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,     0,     5,     7,     9,
     122,   123,   124,   125,   140,   141,   142,   146,     7,   153,
       7,   159,     7,   170,     7,   230,     7,   292,     7,   304,
       7,   321,     7,   252,     7,   275,     7,   212,     7,   372,
     147,   143,   154,   160,   171,   231,   293,   305,   322,   253,
     276,   213,   373,   140,   150,   151,   122,   144,   145,    10,
     102,   108,   109,   122,   152,   155,   156,   157,   400,   402,
     404,    11,    13,    14,    22,    23,    24,    25,    26,    27,
      28,    29,    52,    53,    54,    55,    66,    69,    70,    75,
      76,    79,   152,   161,   162,   163,   164,   165,   166,   167,
     168,   174,   176,   193,   199,   204,   206,   220,   224,   246,
     269,   342,   352,   361,   362,   370,    12,   172,     7,    38,
      40,    46,    47,    48,    49,    50,    51,    57,    58,    64,
     152,   163,   164,   165,   166,   232,   233,   234,   236,   238,
     240,   242,   244,   245,   269,   286,   298,   315,   338,    39,
     152,   269,   294,   295,   296,    41,    42,    43,    44,    45,
     152,   269,   306,   307,   308,   310,   311,   313,   314,    55,
      59,    60,    61,    62,    63,   152,   269,   323,   324,   325,
     326,   328,   330,   332,   334,   336,    15,    30,    32,    33,
      35,    36,    37,   152,   180,   188,   254,   255,   256,   257,
     258,   259,   260,   261,   263,   265,   266,   268,    31,    34,
     152,   188,   258,   263,   277,   278,   279,   280,   281,   283,
     284,   285,    67,    68,   152,   214,   215,   216,   218,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,   152,   374,   375,   376,   377,   379,
     381,   382,   384,   385,   386,   389,   391,   392,   393,   394,
     395,   398,     6,     3,     4,     8,     3,   158,   405,   401,
     403,     4,     3,     8,   169,   175,   177,     4,     4,     4,
       4,     4,   225,   247,   270,   194,   205,   200,   343,   207,
     221,   353,     4,   363,   371,     3,     8,   173,     8,   345,
     287,   299,   235,   237,   239,     4,     4,   243,   241,   316,
     339,     3,     8,   297,     3,     8,   309,     4,   312,     4,
       4,     3,     8,   337,   327,   329,   331,   333,   335,     8,
       3,   181,   189,     4,   264,   262,   267,     4,     8,     3,
     282,     4,     8,     3,   217,   219,     3,     8,     4,   378,
     380,     4,   383,     4,     4,   387,   390,     4,     4,     4,
       4,   396,   399,     3,     8,   140,   140,   122,     4,     4,
       4,     4,   156,     4,     4,     4,   123,   123,   123,   123,
     123,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   123,     4,     4,   162,     4,    56,   152,   188,   269,
     346,   347,   348,   349,   350,     4,     4,     4,     4,     4,
     123,   125,     4,     4,     4,     4,   233,     4,   295,     4,
     123,     4,   123,   123,   307,     4,     4,     4,     4,     4,
       4,   325,     4,     4,   123,     4,     4,     4,   125,   256,
       4,   125,   279,     4,     4,   215,   125,     4,     4,   123,
       4,   123,   123,     4,     4,   125,   125,   125,   125,     4,
       4,   375,     4,     7,     7,   140,   140,     7,     7,     7,
       5,     5,     5,     5,     5,   148,     5,     5,     5,     7,
       7,     7,     7,   148,   351,     8,     3,     5,     5,   122,
     122,   122,   122,   122,     5,     7,   122,   122,   122,   148,
     148,   148,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   140,   122,   122,   122,    95,    96,   388,    97,
      98,    99,   100,   101,   125,   397,   122,   140,   161,   103,
     406,   407,   408,   172,    16,    17,    18,    19,    20,    21,
     152,   178,   179,   180,   182,   184,   186,   188,   190,   191,
     192,   178,     7,   226,   227,   228,     7,   248,   249,   250,
       7,   271,   272,   273,    61,   122,   195,   196,   197,   198,
     149,    62,   197,   201,   202,   203,   240,   344,     7,   208,
     209,   210,   122,   222,   223,    71,    72,    73,    74,   152,
     180,   190,   354,   355,   356,   357,   359,   360,    77,    78,
     364,   365,   366,   368,   374,     4,   348,     7,   288,   289,
     290,     7,   300,   301,   302,     7,   317,   318,   319,    65,
     340,     8,   409,     3,     8,     8,   183,   185,   187,     4,
       4,     4,     3,     8,     8,   229,     6,     3,   251,     6,
       3,   274,     6,     3,     3,     6,   150,     3,     6,     3,
       6,   211,     6,     3,     4,     3,     8,   358,     4,     4,
       4,     3,     8,   367,   369,     3,     8,     8,   122,   291,
       6,     3,   303,     6,     3,   320,     6,     3,   341,     8,
       4,   407,     4,     4,     4,   125,   123,   125,   179,   232,
     228,   254,   250,   277,   273,   196,     6,   202,   240,   214,
     210,   123,   223,     4,   123,   123,   123,   355,     4,     4,
     365,   294,   290,   306,   302,   323,   319,     4,     5,   122,
     122,   122,     8,     8,     8,     8,   122,   122,   122,     8,
       8,     8,   122,     7,   410,   411,   412,     3,     6,   104,
     106,   107,   152,   188,   413,   414,   415,   416,   418,   411,
     419,     4,   417,     3,     8,     4,   123,     4,   414,     5,
     122,     7,   420,   421,   422,     3,     6,   105,   423,   424,
     421,   425,     3,     8,     4,   424,   122
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   126,   128,   127,   129,   127,   130,   127,   131,   127,
     132,   127,   133,   127,   134,   127,   135,   127,   136,   127,
     137,   127,   138,   127,   139,   127,   140,   140,   140,   140,
     140,   140,   140,   141,   143,   142,   144,   144,   145,   145,
     147,   146,   149,   148,   150,   150,   151,   151,   152,   154,
     153,   155,   155,   156,   156,   156,   156,   156,   158,   157,
     160,   159,   161,   161,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   163,   164,   165,   166,
     167,   169,   168,   171,   170,   173,   172,   175,   174,   177,
     176,   178,   178,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   181,   180,   183,   182,   185,   184,   187,   186,
     189,   188,   190,   191,   192,   194,   193,   195,   195,   196,
     196,   197,   198,   200,   199,   201,   201,   202,   202,   203,
     205,   204,   207,   206,   208,   208,   209,   209,   211,   210,
     213,   212,   214,   214,   214,   215,   215,   217,   216,   219,
     218,   221,   220,   222,   222,   223,   225,   224,   226,   226,
     227,   227,   229,   228,   231,   230,   232,   232,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   235,   234,   237,   236,   239,
     238,   241,   240,   243,   242,   244,   245,   247,   246,   248,
     248,   249,   249,   251,   250,   253,   252,   254,   254,   255,
     255,   256,   256,   256,   256,   256,   256,   256,   256,   257,
     258,   259,   260,   262,   261,   264,   263,   265,   267,   266,
     268,   270,   269,   271,   271,   272,   272,   274,   273,   276,
     275,   277,   277,   278,   278,   279,   279,   279,   279,   279,
     279,   280,   282,   281,   283,   284,   285,   287,   286,   288,
     288,   289,   289,   291,   290,   293,   292,   294,   294,   295,
     295,   295,   297,   296,   299,   298,   300,   300,   301,   301,
     303,   302,   305,   304,   306,   306,   307,   307,   307,   307,
     307,   307,   307,   309,   308,   310,   312,   311,   313,   314,
     316,   315,   317,   317,   318,   318,   320,   319,   322,   321,
     323,   323,   324,   324,   325,   325,   325,   325,   325,   325,
     325,   325,   327,   326,   329,   328,   331,   330,   333,   332,
     335,   334,   337,   336,   339,   338,   341,   340,   343,   342,
     344,   344,   345,   240,   346,   346,   347,   347,   348,   348,
     348,   348,   349,   351,   350,   353,   352,   354,   354,   355,
     355,   355,   355,   355,   355,   355,   356,   358,   357,   359,
     360,   361,   363,   362,   364,   364,   365,   365,   367,   366,
     369,   368,   371,   370,   373,   372,   374,   374,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   376,   378,   377,   380,   379,   381,
     383,   382,   384,   385,   387,   386,   388,   388,   390,   389,
     391,   392,   393,   394,   396,   395,   397,   397,   397,   397,
     397,   399,   398,   401,   400,   403,   402,   405,   404,   406,
     406,   407,   409,   408,   410,   410,   412,   411,   413,   413,
     414,   414,   414,   414,   414,   415,   417,   416,   419,   418,
     420,   420,   422,   421,   423,   423,   425,   424
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     1,     3,     5,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     0,     6,     0,     4,     0,     4,     0,     6,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     0,     4,     0,     4,     1,     0,     4,
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
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     1,
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
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"allow-client-update\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"Dhcp4\"", "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "value", "sub_json", "map2", "$@13", "map_content",
  "not_empty_map", "list_generic", "$@14", "list2", "$@15", "list_content",
  "not_empty_list", "unknown_map_entry", "syntax_map", "$@16",
  "global_objects", "global_object", "dhcp6_object", "$@17", "sub_dhcp6",
  "$@18", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@19",
  "sub_interfaces6", "$@20", "interface_config_map", "$@21",
  "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "type", "$@24", "user",
  "$@25", "password", "$@26", "host", "$@27", "name", "$@28", "persist",
  "lfc_interval", "readonly", "mac_sources", "$@29", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@30",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "relay_supplied_options", "$@31", "hooks_libraries",
  "$@32", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@33", "sub_hooks_library", "$@34", "hooks_params",
  "hooks_param", "library", "$@35", "parameters", "$@36",
  "expired_leases_processing", "$@37", "expired_leases_params",
  "expired_leases_param", "subnet6_list", "$@38", "subnet6_list_content",
  "not_empty_subnet6_list", "subnet6", "$@39", "sub_subnet6", "$@40",
  "subnet6_params", "subnet6_param", "subnet", "$@41", "interface", "$@42",
  "interface_id", "$@43", "client_class", "$@44", "reservation_mode",
  "$@45", "id", "rapid_commit", "option_def_list", "$@46",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@47", "sub_option_def", "$@48",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type",
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
  "server_id_params", "server_id_param", "htype", "identifier", "$@80",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@81",
  "control_socket_params", "control_socket_param", "socket_type", "$@82",
  "socket_name", "$@83", "dhcp_ddns", "$@84", "sub_dhcp_ddns", "$@85",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@86", "server_ip", "$@87", "server_port",
  "sender_ip", "$@88", "sender_port", "max_queue_size", "ncr_protocol",
  "$@89", "ncr_protocol_value", "ncr_format", "$@90",
  "always_include_fqdn", "allow_client_update", "override_no_update",
  "override_client_update", "replace_client_name", "$@91",
  "replace_client_name_value", "generated_prefix", "$@92",
  "dhcp4_json_object", "$@93", "dhcpddns_json_object", "$@94",
  "logging_object", "$@95", "logging_params", "logging_param", "loggers",
  "$@96", "loggers_entries", "logger_entry", "$@97", "logger_params",
  "logger_param", "debuglevel", "severity", "$@98", "output_options_list",
  "$@99", "output_options_list_content", "output_entry", "$@100",
  "output_params", "output_param", "$@101", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   203,   203,   203,   204,   204,   205,   205,   206,   206,
     207,   207,   208,   208,   209,   209,   210,   210,   211,   211,
     212,   212,   213,   213,   214,   214,   222,   223,   224,   225,
     226,   227,   228,   231,   236,   236,   248,   249,   252,   256,
     263,   263,   271,   271,   278,   279,   282,   286,   297,   307,
     307,   319,   320,   324,   325,   326,   327,   328,   331,   331,
     348,   348,   356,   357,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   386,   391,   396,   401,
     406,   411,   411,   421,   421,   429,   429,   439,   439,   449,
     449,   459,   460,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   474,   474,   482,   482,   490,   490,   498,   498,
     506,   506,   514,   519,   524,   529,   529,   539,   540,   543,
     544,   547,   552,   557,   557,   567,   568,   571,   572,   575,
     580,   580,   590,   590,   600,   601,   604,   605,   608,   608,
     616,   616,   624,   625,   626,   629,   630,   633,   633,   641,
     641,   649,   649,   659,   660,   666,   674,   674,   687,   688,
     691,   692,   699,   699,   722,   722,   731,   732,   736,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   755,   755,   763,   763,   771,
     771,   779,   779,   787,   787,   795,   800,   809,   809,   821,
     822,   825,   826,   831,   831,   842,   842,   852,   853,   856,
     857,   860,   861,   862,   863,   864,   865,   866,   867,   870,
     872,   877,   879,   881,   881,   889,   889,   897,   899,   899,
     907,   916,   916,   928,   929,   934,   935,   940,   940,   951,
     951,   962,   963,   968,   969,   974,   975,   976,   977,   978,
     979,   982,   984,   984,   992,   994,   996,  1004,  1004,  1016,
    1017,  1020,  1021,  1024,  1024,  1032,  1032,  1040,  1041,  1044,
    1045,  1046,  1049,  1049,  1060,  1060,  1072,  1073,  1076,  1077,
    1080,  1080,  1088,  1088,  1096,  1097,  1100,  1101,  1102,  1103,
    1104,  1105,  1106,  1109,  1109,  1117,  1122,  1122,  1130,  1135,
    1143,  1143,  1153,  1154,  1157,  1158,  1161,  1161,  1169,  1169,
    1177,  1178,  1181,  1182,  1186,  1187,  1188,  1189,  1190,  1191,
    1192,  1193,  1196,  1196,  1206,  1206,  1216,  1216,  1224,  1224,
    1232,  1232,  1240,  1240,  1253,  1253,  1263,  1263,  1274,  1274,
    1284,  1285,  1288,  1288,  1296,  1297,  1300,  1301,  1304,  1305,
    1306,  1307,  1310,  1312,  1312,  1323,  1323,  1333,  1334,  1337,
    1338,  1339,  1340,  1341,  1342,  1343,  1346,  1351,  1351,  1359,
    1364,  1371,  1378,  1378,  1388,  1389,  1392,  1393,  1396,  1396,
    1404,  1404,  1414,  1414,  1424,  1424,  1432,  1433,  1436,  1437,
    1438,  1439,  1440,  1441,  1442,  1443,  1444,  1445,  1446,  1447,
    1448,  1449,  1450,  1451,  1454,  1459,  1459,  1467,  1467,  1475,
    1480,  1480,  1488,  1493,  1498,  1498,  1506,  1507,  1510,  1510,
    1518,  1523,  1528,  1533,  1538,  1538,  1546,  1549,  1552,  1555,
    1558,  1564,  1564,  1574,  1574,  1581,  1581,  1593,  1593,  1606,
    1607,  1611,  1615,  1615,  1627,  1628,  1632,  1632,  1640,  1641,
    1644,  1645,  1646,  1647,  1648,  1651,  1655,  1655,  1663,  1663,
    1673,  1674,  1677,  1677,  1685,  1686,  1689,  1689
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
#line 3878 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1697 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
