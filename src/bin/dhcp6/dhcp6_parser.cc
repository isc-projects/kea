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
      case 149: // value
      case 374: // duid_type
      case 407: // ncr_protocol_value
      case 416: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 134: // "boolean"
        value.move< bool > (that.value);
        break;

      case 133: // "floating point"
        value.move< double > (that.value);
        break;

      case 132: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 131: // "constant string"
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
      case 149: // value
      case 374: // duid_type
      case 407: // ncr_protocol_value
      case 416: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 134: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 133: // "floating point"
        value.copy< double > (that.value);
        break;

      case 132: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 131: // "constant string"
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
            case 131: // "constant string"

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 358 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 132: // "integer"

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 365 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 133: // "floating point"

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 372 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 134: // "boolean"

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 379 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 149: // value

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 386 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 374: // duid_type

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 393 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 407: // ncr_protocol_value

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 400 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 416: // replace_client_name_value

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 407 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 149: // value
      case 374: // duid_type
      case 407: // ncr_protocol_value
      case 416: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 134: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 133: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 132: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 131: // "constant string"
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
#line 213 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 214 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 215 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 662 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 216 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 217 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 218 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 219 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 220 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 221 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 832 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 292 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 296 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 990 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1028 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1037 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1509 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1681 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1827 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1854 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1138 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1155 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1992 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1163 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1168 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2019 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1176 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1181 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1189 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1194 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1304 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1399 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1400 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2604 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2633 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1596 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1607 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1616 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2745 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2938 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2942 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -498;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     111,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,    32,    21,    41,    46,    59,    75,    85,
      93,   143,   163,   170,   171,   194,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
      21,   -92,    12,    80,   187,    11,    38,    45,   112,    48,
      65,     5,    91,  -498,   142,   223,   240,   219,   269,  -498,
    -498,  -498,  -498,   271,  -498,    62,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,   273,   276,   277,   278,   279,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   280,
    -498,  -498,  -498,   137,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   265,  -498,  -498,
    -498,  -498,  -498,  -498,   287,   288,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,   192,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,   209,  -498,  -498,  -498,   290,  -498,   295,   297,
    -498,  -498,   210,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   294,   300,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   301,  -498,
    -498,  -498,   302,  -498,  -498,   296,   305,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   306,  -498,
    -498,  -498,  -498,   303,   309,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,   211,  -498,  -498,  -498,   310,  -498,
    -498,   311,  -498,   312,   313,  -498,  -498,   314,   315,   317,
     318,  -498,  -498,  -498,   212,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,    21,    21,  -498,   182,   319,   320,   321,   322,
    -498,    12,  -498,   323,   324,   325,   198,   199,   200,   201,
     202,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   214,   341,   343,    80,  -498,   344,  -498,     8,   345,
     346,   347,   348,   349,   222,   221,   352,   353,   354,   355,
      11,  -498,   356,    38,  -498,   357,   230,   359,   232,   233,
      45,  -498,   362,   363,   364,   365,   366,   367,  -498,   112,
     368,   369,   244,   370,   371,   373,   246,  -498,    48,   374,
     247,  -498,    65,   375,   378,    53,  -498,   250,   379,   381,
     254,   383,   256,   257,   386,   387,   260,   261,   263,   264,
     388,   389,    91,  -498,  -498,  -498,   392,   393,   394,    21,
      21,  -498,   395,   396,   399,  -498,  -498,  -498,  -498,  -498,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   413,
    -498,   414,   415,  -498,   406,  -498,  -498,  -498,  -498,   391,
     412,  -498,  -498,  -498,   411,   418,   293,   298,   299,  -498,
    -498,   304,   307,   422,   421,  -498,   316,  -498,   326,  -498,
     327,  -498,  -498,  -498,   406,   406,   406,   328,   329,   330,
    -498,   342,   350,  -498,   351,   358,   360,  -498,  -498,   361,
    -498,  -498,   372,    21,  -498,  -498,   376,   377,  -498,   380,
    -498,  -498,    33,   382,  -498,  -498,  -498,  -498,    17,   384,
    -498,    21,    80,   385,  -498,  -498,   187,    26,    26,   424,
     425,   426,   -30,  -498,  -498,   136,    14,   427,   135,    35,
     138,    91,  -498,   436,  -498,     8,   434,   435,  -498,  -498,
    -498,  -498,  -498,   437,   390,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   213,  -498,   220,
    -498,  -498,   438,  -498,  -498,  -498,  -498,   441,   444,   445,
    -498,   239,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,   242,  -498,   446,   447,  -498,  -498,   448,   450,  -498,
    -498,   456,   453,  -498,  -498,  -498,    49,  -498,  -498,  -498,
      21,  -498,  -498,    73,  -498,  -498,  -498,   108,  -498,   457,
     461,  -498,   462,   463,   464,   465,   466,   467,   243,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   468,   470,
     471,  -498,  -498,   245,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,   249,  -498,  -498,  -498,   251,   397,  -498,  -498,
     459,   473,  -498,  -498,   474,   476,  -498,  -498,   477,   481,
    -498,  -498,   469,  -498,   482,   385,  -498,  -498,   483,   486,
     489,   490,   398,   401,   400,    26,  -498,  -498,    11,  -498,
     424,    48,  -498,   425,    65,  -498,   426,   -30,  -498,   479,
     136,  -498,    14,  -498,     5,  -498,   427,   416,   417,   419,
     420,   423,   428,   135,  -498,   491,   494,   429,   430,   431,
      35,  -498,   495,   496,   138,  -498,  -498,  -498,    38,  -498,
     434,    45,  -498,   435,   112,  -498,   437,   497,  -498,   499,
    -498,   433,   439,   440,   442,  -498,  -498,  -498,  -498,   252,
    -498,   498,  -498,   501,  -498,  -498,  -498,  -498,  -498,   255,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,    81,   443,
    -498,  -498,  -498,  -498,   449,   451,  -498,   258,  -498,   259,
    -498,   502,  -498,   452,   505,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,   116,  -498,    -3,   505,  -498,
    -498,   509,  -498,  -498,  -498,   262,  -498,  -498,  -498,  -498,
    -498,   510,   454,   512,    -3,  -498,   500,  -498,   458,  -498,
     511,  -498,  -498,   141,  -498,   432,   511,  -498,  -498,   266,
    -498,  -498,   513,   432,  -498,   460,  -498,  -498
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    40,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    49,     5,
      60,     7,    93,     9,   185,    11,   287,    13,   304,    15,
     330,    17,   226,    19,   261,    21,   150,    23,   411,    25,
      44,    36,     0,     0,     0,     0,     0,     0,   332,   228,
     263,     0,     0,    46,     0,    45,     0,     0,    37,    58,
     464,   460,   462,     0,    57,     0,    51,    53,    55,    56,
      54,    91,    97,    99,     0,     0,     0,     0,     0,   177,
     218,   253,   125,   140,   133,   360,   142,   161,   377,     0,
     399,   409,    85,     0,    62,    64,    65,    66,    67,    68,
      70,    71,    72,    73,    75,    74,    79,    80,    69,    77,
      78,    76,    81,    82,    83,    84,    95,     0,   364,   279,
     296,   206,   208,   210,     0,     0,   214,   212,   322,   356,
     205,   189,   190,   191,   192,     0,   187,   196,   197,   198,
     201,   203,   199,   200,   193,   194,   195,   202,   204,   294,
     293,   292,     0,   289,   291,   315,     0,   318,     0,     0,
     314,   311,     0,   306,   308,   309,   312,   313,   310,   354,
     344,   346,   348,   350,   352,   343,   342,     0,   333,   334,
     338,   339,   336,   340,   341,   337,   243,   120,     0,   247,
     245,   250,     0,   239,   240,     0,   229,   230,   232,   242,
     233,   234,   235,   249,   236,   237,   238,   274,     0,   272,
     273,   276,   277,     0,   264,   265,   267,   268,   269,   270,
     271,   157,   159,   154,     0,   152,   155,   156,     0,   432,
     434,     0,   437,     0,     0,   441,   445,     0,     0,     0,
       0,   451,   458,   430,     0,   413,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,    41,     0,     0,    35,     0,     0,     0,     0,     0,
      48,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,     0,    94,   366,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   186,     0,     0,   288,     0,     0,     0,     0,     0,
       0,   305,     0,     0,     0,     0,     0,     0,   331,     0,
       0,     0,     0,     0,     0,     0,     0,   227,     0,     0,
       0,   262,     0,     0,     0,     0,   151,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   412,    47,    38,     0,     0,     0,     0,
       0,    52,     0,     0,     0,    86,    87,    88,    89,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     398,     0,     0,    63,     0,   375,   373,   374,   372,     0,
     367,   368,   370,   371,     0,     0,     0,     0,     0,   216,
     217,     0,     0,     0,     0,   188,     0,   290,     0,   317,
       0,   320,   321,   307,     0,     0,     0,     0,     0,     0,
     335,     0,     0,   241,     0,     0,     0,   252,   231,     0,
     278,   266,     0,     0,   153,   431,     0,     0,   436,     0,
     439,   440,     0,     0,   447,   448,   449,   450,     0,     0,
     414,     0,     0,     0,   461,   463,     0,     0,     0,   179,
     220,   255,     0,    42,   141,     0,     0,   144,     0,     0,
       0,     0,    96,     0,   365,     0,   281,   298,   207,   209,
     211,   215,   213,   324,     0,   295,   316,   319,   355,   345,
     347,   349,   351,   353,   244,   121,   248,   246,   251,   275,
     158,   160,   433,   435,   438,   443,   444,   442,   446,   453,
     454,   455,   456,   457,   452,   459,    39,     0,   469,     0,
     466,   468,     0,   112,   114,   116,   118,     0,     0,     0,
     111,     0,   101,   103,   104,   105,   106,   107,   108,   109,
     110,     0,   183,     0,   180,   181,   224,     0,   221,   222,
     259,     0,   256,   257,   131,   132,     0,   127,   129,   130,
      44,   139,   137,     0,   135,   138,   362,     0,   148,     0,
     145,   146,     0,     0,     0,     0,     0,     0,     0,   163,
     165,   166,   167,   168,   169,   170,   388,   394,     0,     0,
       0,   387,   386,     0,   379,   381,   384,   382,   383,   385,
     405,   407,     0,   401,   403,   404,     0,     0,   369,   285,
       0,   282,   283,   302,     0,   299,   300,   328,     0,   325,
     326,   358,     0,    59,     0,     0,   465,    92,     0,     0,
       0,     0,     0,     0,     0,     0,    98,   100,     0,   178,
       0,   228,   219,     0,   263,   254,     0,     0,   126,     0,
       0,   134,     0,   361,     0,   143,     0,     0,     0,     0,
       0,     0,     0,     0,   162,     0,     0,     0,     0,     0,
       0,   378,     0,     0,     0,   400,   410,   376,     0,   280,
       0,     0,   297,     0,   332,   323,     0,     0,   357,     0,
     467,     0,     0,     0,     0,   122,   123,   124,   102,     0,
     182,     0,   223,     0,   258,   128,    43,   136,   363,     0,
     147,   171,   172,   173,   174,   175,   176,   164,     0,     0,
     393,   396,   397,   380,     0,     0,   402,     0,   284,     0,
     301,     0,   327,     0,     0,   113,   115,   117,   119,   184,
     225,   260,   149,   390,   391,   392,   389,   395,   406,   408,
     286,   303,   329,   359,   473,     0,   471,     0,     0,   470,
     485,     0,   483,   481,   477,     0,   475,   479,   480,   478,
     472,     0,     0,     0,     0,   474,     0,   482,     0,   476,
       0,   484,   489,     0,   487,     0,     0,   486,   493,     0,
     491,   488,     0,     0,   490,     0,   492,   494
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,    15,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -283,  -498,   -88,  -498,   -62,  -498,  -498,  -498,
     228,  -498,  -498,  -498,  -498,    39,   206,   -45,   -42,   -41,
     -40,  -498,  -498,  -498,  -498,  -498,    36,  -498,  -498,  -498,
    -498,  -498,    37,  -142,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,   -69,  -498,  -497,  -498,  -498,  -498,  -498,  -498,
    -153,  -476,  -498,  -498,  -498,  -498,  -154,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -159,  -498,  -498,  -498,  -155,   165,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -162,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -135,  -498,
    -498,  -498,  -132,   207,  -498,  -498,  -498,  -498,  -498,  -498,
    -480,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -134,  -498,  -498,  -498,  -133,  -498,   183,  -498,   -55,  -498,
    -498,  -498,  -498,  -498,   -53,  -498,  -498,  -498,  -498,  -498,
     -54,  -498,  -498,  -498,  -136,  -498,  -498,  -498,  -131,  -498,
     180,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -166,  -498,  -498,  -498,  -163,   217,  -498,  -498,  -498,
    -498,  -498,  -498,  -160,  -498,  -498,  -498,  -164,   216,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -158,  -498,  -498,  -498,  -157,  -498,   205,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,    54,
    -498,  -498,  -498,  -498,  -498,  -498,  -128,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -139,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,    66,   184,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,   -87,  -498,  -498,  -498,  -219,  -498,  -498,  -229,  -498,
    -498,  -498,  -498,  -498,  -498,  -240,  -498,  -498,  -246,  -498
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,    77,    78,
      37,    60,   494,   590,    74,    75,   112,    39,    62,    85,
      86,    87,   286,    41,    63,   113,   114,   115,   116,   117,
     118,   119,   120,   293,    43,    64,   137,   316,   121,   294,
     122,   295,   561,   562,   563,   658,   564,   659,   565,   660,
     566,   661,   214,   351,   568,   569,   570,   123,   304,   586,
     587,   588,   589,   124,   306,   593,   594,   595,   125,   305,
     126,   308,   599,   600,   601,   684,    57,    71,   244,   245,
     246,   363,   247,   364,   127,   309,   608,   609,   610,   611,
     612,   613,   614,   615,   128,   301,   573,   574,   575,   668,
      45,    65,   155,   156,   157,   321,   158,   322,   159,   323,
     160,   327,   161,   326,   162,   163,   129,   302,   577,   578,
     579,   671,    53,    69,   215,   216,   217,   218,   219,   220,
     221,   350,   222,   354,   223,   353,   224,   225,   355,   226,
     130,   303,   581,   582,   583,   674,    55,    70,   233,   234,
     235,   236,   237,   359,   238,   239,   240,   165,   319,   640,
     641,   642,   708,    47,    66,   172,   173,   174,   332,   166,
     320,   644,   645,   646,   711,    49,    67,   182,   183,   184,
     335,   185,   186,   337,   187,   188,   167,   328,   648,   649,
     650,   714,    51,    68,   197,   198,   199,   200,   343,   201,
     344,   202,   345,   203,   346,   204,   347,   205,   342,   168,
     329,   652,   717,   131,   307,   597,   318,   419,   420,   421,
     422,   423,   503,   132,   310,   623,   624,   625,   695,   776,
     626,   627,   696,   628,   629,   133,   134,   312,   632,   633,
     634,   702,   635,   703,   135,   313,    59,    72,   264,   265,
     266,   267,   368,   268,   369,   269,   270,   371,   271,   272,
     273,   374,   537,   274,   375,   275,   276,   277,   278,   279,
     380,   544,   280,   381,    88,   288,    89,   289,    90,   287,
     549,   550,   551,   654,   785,   786,   787,   795,   796,   797,
     798,   803,   799,   801,   813,   814,   815,   819,   820,   822
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   230,   622,   150,   170,   180,   195,   213,   229,   243,
     263,   164,   171,   181,   196,   231,   596,   232,   138,   592,
     151,   138,    79,   152,   153,   154,    27,   207,    28,    34,
      29,   584,    26,    94,    95,    96,    97,   101,   207,    76,
     101,   553,   554,   555,   556,   557,   558,   559,    38,   139,
     616,   140,   677,    40,   557,   678,   207,   141,   142,   143,
     144,   145,   146,   206,   415,   291,    42,   101,   147,   148,
     292,   147,   241,   242,   101,   149,   680,   169,   207,   681,
     208,   209,    44,   210,   211,   212,   175,   176,   177,   178,
     179,    91,    46,    92,    93,   207,   227,   208,   209,   228,
      48,   585,    94,    95,    96,    97,    98,    99,   100,   101,
     790,   682,   791,   792,   683,   617,   618,   619,   620,   788,
     241,   242,   789,    80,   539,   540,   541,   542,    83,    81,
      82,   502,   102,   103,   104,   105,    83,   535,   536,    83,
     314,   101,    83,    83,   816,   315,   106,   817,   281,   107,
      50,   543,    30,    31,    32,    33,   108,    83,   773,   774,
     775,   518,   519,   520,   109,   110,    83,   189,   111,    83,
      52,   190,   191,   192,   193,   194,    83,    54,    56,    83,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   330,    83,   584,   591,   136,
     331,    58,   738,   622,   592,   602,   603,   604,   605,   606,
     607,    83,   333,   340,   365,   382,   314,   334,   341,   366,
     383,   653,    83,   655,   630,   631,   282,   284,   656,    84,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,   665,    83,   283,   665,   693,   666,   700,   417,
     667,   694,   704,   701,   382,   330,   416,   705,   365,   706,
     769,   333,   340,   772,   418,   804,   780,   781,   150,   823,
     805,   170,   285,   317,   824,   290,   164,   296,   180,   171,
     297,   298,   299,   300,   311,   151,   181,   195,   152,   153,
     154,   324,   325,   230,   336,   196,   213,   384,   385,   338,
     229,   339,   348,   349,   357,   352,   356,   231,   358,   232,
     360,   361,   362,   386,   367,   370,   372,   373,   376,   377,
     263,   378,   379,   387,   388,   389,   390,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   411,   410,   412,   414,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     436,   438,   439,   440,   441,   442,   444,   445,   446,   447,
     448,   449,   451,   452,   454,   455,   453,   456,   459,   462,
     457,   460,   463,   466,   465,   467,   468,   469,   470,   471,
     472,   473,   478,   479,   474,   475,   481,   476,   477,   504,
     482,   483,   486,   487,   484,   485,   488,   489,   490,   491,
     492,   493,   495,   496,   497,   505,   506,   498,   567,   567,
     499,   500,   501,   507,   508,   560,   560,   513,   514,   509,
     510,   572,   576,   580,   598,   511,   417,   621,   512,   263,
     637,   639,   643,   416,   647,   662,   657,   515,   663,   664,
     670,   418,   669,   673,   672,   651,   676,   516,   517,   521,
     522,   523,   675,   685,   686,   709,   687,   688,   689,   690,
     691,   692,   697,   524,   698,   699,   710,   718,   531,   713,
     712,   525,   526,   715,   716,   736,   719,   721,   538,   527,
     722,   528,   529,   723,   724,   748,   546,   548,   749,   754,
     755,   763,   679,   530,   764,   810,   770,   532,   533,   771,
     782,   534,   784,   802,   806,   545,   808,   825,   812,   391,
     413,   547,   552,   728,   735,   571,   737,   740,   707,   739,
     464,   747,   725,   726,   727,   730,   729,   435,   731,   732,
     734,   458,   461,   733,   758,   757,   818,   759,   741,   742,
     437,   743,   744,   760,   450,   745,   443,   761,   762,   638,
     746,   750,   751,   752,   765,   756,   480,   636,   720,   800,
     766,   767,   753,   768,   777,   809,   821,   826,     0,     0,
     778,     0,   779,   783,     0,     0,   807,     0,     0,   811,
       0,   827,     0,     0,     0,     0,   567,     0,     0,     0,
       0,     0,     0,   560,     0,   230,   150,     0,     0,   213,
       0,     0,   229,     0,   164,     0,     0,     0,     0,   231,
       0,   232,   243,   151,     0,     0,   152,   153,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   621,     0,
       0,     0,     0,     0,     0,     0,   170,     0,     0,   180,
       0,     0,   195,     0,   171,     0,     0,   181,     0,     0,
     196,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   794,     0,
       0,     0,     0,     0,     0,   793,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   794,     0,     0,     0,     0,
       0,     0,   793
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    70,   499,    65,    66,    67,    68,    69,    70,    71,
      72,    65,    66,    67,    68,    70,   496,    70,     7,   495,
      65,     7,    10,    65,    65,    65,     5,    30,     7,    14,
       9,    61,     0,    22,    23,    24,    25,    29,    30,   131,
      29,    15,    16,    17,    18,    19,    20,    21,     7,    38,
      15,    40,     3,     7,    19,     6,    30,    46,    47,    48,
      49,    50,    51,    15,    56,     3,     7,    29,    57,    58,
       8,    57,    67,    68,    29,    64,     3,    39,    30,     6,
      32,    33,     7,    35,    36,    37,    41,    42,    43,    44,
      45,    11,     7,    13,    14,    30,    31,    32,    33,    34,
       7,   131,    22,    23,    24,    25,    26,    27,    28,    29,
     113,     3,   115,   116,     6,    80,    81,    82,    83,     3,
      67,    68,     6,   111,   107,   108,   109,   110,   131,   117,
     118,   414,    52,    53,    54,    55,   131,   104,   105,   131,
       3,    29,   131,   131,     3,     8,    66,     6,     6,    69,
       7,   134,   131,   132,   133,   134,    76,   131,    77,    78,
      79,   444,   445,   446,    84,    85,   131,    55,    88,   131,
       7,    59,    60,    61,    62,    63,   131,     7,     7,   131,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     3,   131,    61,    62,    12,
       8,     7,   682,   700,   680,    70,    71,    72,    73,    74,
      75,   131,     3,     3,     3,     3,     3,     8,     8,     8,
       8,     8,   131,     3,    86,    87,     3,     8,     8,   291,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     3,   131,     4,     3,     3,     8,     3,   318,
       8,     8,     3,     8,     3,     3,   318,     8,     3,     8,
       8,     3,     3,     8,   318,     3,     8,     8,   330,     3,
       8,   333,     3,     8,     8,     4,   330,     4,   340,   333,
       4,     4,     4,     4,     4,   330,   340,   349,   330,   330,
     330,     4,     4,   362,     4,   349,   358,   282,   283,     4,
     362,     4,     8,     3,     8,     4,     4,   362,     3,   362,
       4,     8,     3,   131,     4,     4,     4,     4,     4,     4,
     382,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     132,   132,   132,   132,   132,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   132,     4,     4,     4,
       4,     4,     4,     4,   132,   134,     4,     4,     4,     4,
       4,     4,   132,     4,   132,   132,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   132,     4,     4,     4,
     134,   134,     4,     4,   134,     4,   132,     4,   132,   132,
       4,     4,     4,     4,   134,   134,     4,   134,   134,     8,
       7,     7,     7,     7,   389,   390,     7,     5,     5,     5,
       5,     5,     5,     5,     5,     3,     5,     7,   487,   488,
       7,     7,     7,     5,   131,   487,   488,     5,     7,   131,
     131,     7,     7,     7,     7,   131,   505,   499,   131,   501,
       4,     7,     7,   505,     7,     4,     8,   131,     4,     4,
       3,   505,     6,     3,     6,    65,     3,   131,   131,   131,
     131,   131,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,   131,     4,     4,     3,     8,   463,     3,
       6,   131,   131,     6,     3,     6,     4,     4,   106,   131,
       4,   131,   131,     4,     4,     4,   481,   112,     4,     4,
       4,     4,   590,   131,     5,     5,     8,   131,   131,     8,
       8,   131,     7,     4,     4,   131,     4,     4,     7,   291,
     314,   482,   486,   665,   677,   488,   680,   686,   131,   684,
     365,   693,   134,   132,   134,   670,   668,   330,   671,   673,
     676,   358,   362,   674,   710,   708,   114,   711,   132,   132,
     333,   132,   132,   713,   349,   132,   340,   714,   716,   505,
     132,   132,   132,   132,   131,   704,   382,   501,   655,   788,
     131,   131,   700,   131,   131,   804,   816,   823,    -1,    -1,
     131,    -1,   131,   131,    -1,    -1,   132,    -1,    -1,   131,
      -1,   131,    -1,    -1,    -1,    -1,   665,    -1,    -1,    -1,
      -1,    -1,    -1,   665,    -1,   674,   668,    -1,    -1,   671,
      -1,    -1,   674,    -1,   668,    -1,    -1,    -1,    -1,   674,
      -1,   674,   684,   668,    -1,    -1,   668,   668,   668,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   700,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   708,    -1,    -1,   711,
      -1,    -1,   714,    -1,   708,    -1,    -1,   711,    -1,    -1,
     714,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   787,    -1,
      -1,    -1,    -1,    -1,    -1,   787,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   804,    -1,    -1,    -1,    -1,
      -1,    -1,   804
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,     0,     5,     7,     9,
     131,   132,   133,   134,   149,   150,   151,   155,     7,   162,
       7,   168,     7,   179,     7,   245,     7,   308,     7,   320,
       7,   337,     7,   267,     7,   291,     7,   221,     7,   391,
     156,   152,   163,   169,   180,   246,   309,   321,   338,   268,
     292,   222,   392,   149,   159,   160,   131,   153,   154,    10,
     111,   117,   118,   131,   161,   164,   165,   166,   419,   421,
     423,    11,    13,    14,    22,    23,    24,    25,    26,    27,
      28,    29,    52,    53,    54,    55,    66,    69,    76,    84,
      85,    88,   161,   170,   171,   172,   173,   174,   175,   176,
     177,   183,   185,   202,   208,   213,   215,   229,   239,   261,
     285,   358,   368,   380,   381,   389,    12,   181,     7,    38,
      40,    46,    47,    48,    49,    50,    51,    57,    58,    64,
     161,   172,   173,   174,   175,   247,   248,   249,   251,   253,
     255,   257,   259,   260,   285,   302,   314,   331,   354,    39,
     161,   285,   310,   311,   312,    41,    42,    43,    44,    45,
     161,   285,   322,   323,   324,   326,   327,   329,   330,    55,
      59,    60,    61,    62,    63,   161,   285,   339,   340,   341,
     342,   344,   346,   348,   350,   352,    15,    30,    32,    33,
      35,    36,    37,   161,   197,   269,   270,   271,   272,   273,
     274,   275,   277,   279,   281,   282,   284,    31,    34,   161,
     197,   273,   279,   293,   294,   295,   296,   297,   299,   300,
     301,    67,    68,   161,   223,   224,   225,   227,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   161,   393,   394,   395,   396,   398,   400,
     401,   403,   404,   405,   408,   410,   411,   412,   413,   414,
     417,     6,     3,     4,     8,     3,   167,   424,   420,   422,
       4,     3,     8,   178,   184,   186,     4,     4,     4,     4,
       4,   240,   262,   286,   203,   214,   209,   359,   216,   230,
     369,     4,   382,   390,     3,     8,   182,     8,   361,   303,
     315,   250,   252,   254,     4,     4,   258,   256,   332,   355,
       3,     8,   313,     3,     8,   325,     4,   328,     4,     4,
       3,     8,   353,   343,   345,   347,   349,   351,     8,     3,
     276,   198,     4,   280,   278,   283,     4,     8,     3,   298,
       4,     8,     3,   226,   228,     3,     8,     4,   397,   399,
       4,   402,     4,     4,   406,   409,     4,     4,     4,     4,
     415,   418,     3,     8,   149,   149,   131,     4,     4,     4,
       4,   165,     4,     4,     4,   132,   132,   132,   132,   132,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     132,     4,     4,   171,     4,    56,   161,   197,   285,   362,
     363,   364,   365,   366,     4,     4,     4,     4,     4,   132,
     134,     4,     4,     4,     4,   248,     4,   311,     4,   132,
       4,   132,   132,   323,     4,     4,     4,     4,     4,     4,
     341,     4,     4,   132,     4,     4,     4,   134,   271,     4,
     134,   295,     4,     4,   224,   134,     4,     4,   132,     4,
     132,   132,     4,     4,   134,   134,   134,   134,     4,     4,
     394,     4,     7,     7,   149,   149,     7,     7,     7,     5,
       5,     5,     5,     5,   157,     5,     5,     5,     7,     7,
       7,     7,   157,   367,     8,     3,     5,     5,   131,   131,
     131,   131,   131,     5,     7,   131,   131,   131,   157,   157,
     157,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   149,   131,   131,   131,   104,   105,   407,   106,   107,
     108,   109,   110,   134,   416,   131,   149,   170,   112,   425,
     426,   427,   181,    15,    16,    17,    18,    19,    20,    21,
     161,   187,   188,   189,   191,   193,   195,   197,   199,   200,
     201,   187,     7,   241,   242,   243,     7,   263,   264,   265,
       7,   287,   288,   289,    61,   131,   204,   205,   206,   207,
     158,    62,   206,   210,   211,   212,   255,   360,     7,   217,
     218,   219,    70,    71,    72,    73,    74,    75,   231,   232,
     233,   234,   235,   236,   237,   238,    15,    80,    81,    82,
      83,   161,   199,   370,   371,   372,   375,   376,   378,   379,
      86,    87,   383,   384,   385,   387,   393,     4,   364,     7,
     304,   305,   306,     7,   316,   317,   318,     7,   333,   334,
     335,    65,   356,     8,   428,     3,     8,     8,   190,   192,
     194,   196,     4,     4,     4,     3,     8,     8,   244,     6,
       3,   266,     6,     3,   290,     6,     3,     3,     6,   159,
       3,     6,     3,     6,   220,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   373,   377,     4,     4,     4,
       3,     8,   386,   388,     3,     8,     8,   131,   307,     6,
       3,   319,     6,     3,   336,     6,     3,   357,     8,     4,
     426,     4,     4,     4,     4,   134,   132,   134,   188,   247,
     243,   269,   265,   293,   289,   205,     6,   211,   255,   223,
     219,   132,   132,   132,   132,   132,   132,   232,     4,     4,
     132,   132,   132,   371,     4,     4,   384,   310,   306,   322,
     318,   339,   335,     4,     5,   131,   131,   131,   131,     8,
       8,     8,     8,    77,    78,    79,   374,   131,   131,   131,
       8,     8,     8,   131,     7,   429,   430,   431,     3,     6,
     113,   115,   116,   161,   197,   432,   433,   434,   435,   437,
     430,   438,     4,   436,     3,     8,     4,   132,     4,   433,
       5,   131,     7,   439,   440,   441,     3,     6,   114,   442,
     443,   440,   444,     3,     8,     4,   443,   131
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   135,   137,   136,   138,   136,   139,   136,   140,   136,
     141,   136,   142,   136,   143,   136,   144,   136,   145,   136,
     146,   136,   147,   136,   148,   136,   149,   149,   149,   149,
     149,   149,   149,   150,   152,   151,   153,   153,   154,   154,
     156,   155,   158,   157,   159,   159,   160,   160,   161,   163,
     162,   164,   164,   165,   165,   165,   165,   165,   167,   166,
     169,   168,   170,   170,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   172,   173,   174,   175,
     176,   178,   177,   180,   179,   182,   181,   184,   183,   186,
     185,   187,   187,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   190,   189,   192,   191,   194,   193,   196,   195,
     198,   197,   199,   200,   201,   203,   202,   204,   204,   205,
     205,   206,   207,   209,   208,   210,   210,   211,   211,   212,
     214,   213,   216,   215,   217,   217,   218,   218,   220,   219,
     222,   221,   223,   223,   223,   224,   224,   226,   225,   228,
     227,   230,   229,   231,   231,   232,   232,   232,   232,   232,
     232,   233,   234,   235,   236,   237,   238,   240,   239,   241,
     241,   242,   242,   244,   243,   246,   245,   247,   247,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   250,   249,   252,   251,
     254,   253,   256,   255,   258,   257,   259,   260,   262,   261,
     263,   263,   264,   264,   266,   265,   268,   267,   269,   269,
     270,   270,   271,   271,   271,   271,   271,   271,   271,   271,
     272,   273,   274,   276,   275,   278,   277,   280,   279,   281,
     283,   282,   284,   286,   285,   287,   287,   288,   288,   290,
     289,   292,   291,   293,   293,   294,   294,   295,   295,   295,
     295,   295,   295,   296,   298,   297,   299,   300,   301,   303,
     302,   304,   304,   305,   305,   307,   306,   309,   308,   310,
     310,   311,   311,   311,   313,   312,   315,   314,   316,   316,
     317,   317,   319,   318,   321,   320,   322,   322,   323,   323,
     323,   323,   323,   323,   323,   325,   324,   326,   328,   327,
     329,   330,   332,   331,   333,   333,   334,   334,   336,   335,
     338,   337,   339,   339,   340,   340,   341,   341,   341,   341,
     341,   341,   341,   341,   343,   342,   345,   344,   347,   346,
     349,   348,   351,   350,   353,   352,   355,   354,   357,   356,
     359,   358,   360,   360,   361,   255,   362,   362,   363,   363,
     364,   364,   364,   364,   365,   367,   366,   369,   368,   370,
     370,   371,   371,   371,   371,   371,   371,   371,   373,   372,
     374,   374,   374,   375,   377,   376,   378,   379,   380,   382,
     381,   383,   383,   384,   384,   386,   385,   388,   387,   390,
     389,   392,   391,   393,   393,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   395,   397,   396,   399,   398,   400,   402,   401,   403,
     404,   406,   405,   407,   407,   409,   408,   410,   411,   412,
     413,   415,   414,   416,   416,   416,   416,   416,   418,   417,
     420,   419,   422,   421,   424,   423,   425,   425,   426,   428,
     427,   429,   429,   431,   430,   432,   432,   433,   433,   433,
     433,   433,   434,   436,   435,   438,   437,   439,   439,   441,
     440,   442,   442,   444,   443
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
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     0,     4
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
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
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
  "database_map_params", "database_map_param", "database_type", "$@24",
  "user", "$@25", "password", "$@26", "host", "$@27", "name", "$@28",
  "persist", "lfc_interval", "readonly", "mac_sources", "$@29",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@30",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "relay_supplied_options", "$@31", "hooks_libraries",
  "$@32", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@33", "sub_hooks_library", "$@34", "hooks_params",
  "hooks_param", "library", "$@35", "parameters", "$@36",
  "expired_leases_processing", "$@37", "expired_leases_params",
  "expired_leases_param", "reclaim_timer_wait_time",
  "flush_reclaimed_timer_wait_time", "hold_reclaimed_time",
  "max_reclaim_leases", "max_reclaim_time", "unwarned_reclaim_cycles",
  "subnet6_list", "$@38", "subnet6_list_content", "not_empty_subnet6_list",
  "subnet6", "$@39", "sub_subnet6", "$@40", "subnet6_params",
  "subnet6_param", "subnet", "$@41", "interface", "$@42", "interface_id",
  "$@43", "client_class", "$@44", "reservation_mode", "$@45", "id",
  "rapid_commit", "option_def_list", "$@46", "option_def_list_content",
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
  "pool_list_entry", "$@58", "sub_pool6", "$@59", "pool_params",
  "pool_param", "pool_entry", "$@60", "pd_pools_list", "$@61",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@62", "sub_pd_pool", "$@63", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@64", "pd_prefix_len", "excluded_prefix", "$@65",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@66",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@67", "sub_reservation", "$@68", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@69", "prefixes", "$@70", "duid", "$@71", "hw_address", "$@72",
  "hostname", "$@73", "reservation_client_classes", "$@74", "relay",
  "$@75", "relay_map", "$@76", "client_classes", "$@77",
  "client_classes_list", "$@78", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@79", "server_id", "$@80",
  "server_id_params", "server_id_param", "server_id_type", "$@81",
  "duid_type", "htype", "identifier", "$@82", "time", "enterprise_id",
  "dhcp4o6_port", "control_socket", "$@83", "control_socket_params",
  "control_socket_param", "socket_type", "$@84", "socket_name", "$@85",
  "dhcp_ddns", "$@86", "sub_dhcp_ddns", "$@87", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@88",
  "server_ip", "$@89", "server_port", "sender_ip", "$@90", "sender_port",
  "max_queue_size", "ncr_protocol", "$@91", "ncr_protocol_value",
  "ncr_format", "$@92", "always_include_fqdn", "allow_client_update",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@93", "replace_client_name_value", "generated_prefix", "$@94",
  "dhcp4_json_object", "$@95", "dhcpddns_json_object", "$@96",
  "logging_object", "$@97", "logging_params", "logging_param", "loggers",
  "$@98", "loggers_entries", "logger_entry", "$@99", "logger_params",
  "logger_param", "debuglevel", "severity", "$@100", "output_options_list",
  "$@101", "output_options_list_content", "output_entry", "$@102",
  "output_params", "output_param", "$@103", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   213,   213,   213,   214,   214,   215,   215,   216,   216,
     217,   217,   218,   218,   219,   219,   220,   220,   221,   221,
     222,   222,   223,   223,   224,   224,   232,   233,   234,   235,
     236,   237,   238,   241,   246,   246,   258,   259,   262,   266,
     273,   273,   281,   281,   288,   289,   292,   296,   307,   317,
     317,   329,   330,   334,   335,   336,   337,   338,   341,   341,
     358,   358,   366,   367,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   396,   401,   406,   411,
     416,   421,   421,   431,   431,   439,   439,   449,   449,   459,
     459,   469,   470,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   484,   484,   492,   492,   500,   500,   508,   508,
     516,   516,   524,   529,   534,   539,   539,   549,   550,   553,
     554,   557,   562,   567,   567,   577,   578,   581,   582,   585,
     590,   590,   600,   600,   610,   611,   614,   615,   618,   618,
     626,   626,   634,   635,   636,   639,   640,   643,   643,   651,
     651,   659,   659,   669,   670,   673,   674,   675,   676,   677,
     678,   681,   686,   691,   696,   701,   706,   714,   714,   727,
     728,   731,   732,   739,   739,   762,   762,   771,   772,   776,
     777,   778,   779,   780,   781,   782,   783,   784,   785,   786,
     787,   788,   789,   790,   791,   792,   795,   795,   803,   803,
     811,   811,   819,   819,   827,   827,   835,   840,   849,   849,
     861,   862,   865,   866,   871,   871,   882,   882,   892,   893,
     896,   897,   900,   901,   902,   903,   904,   905,   906,   907,
     910,   912,   917,   919,   919,   927,   927,   935,   935,   943,
     945,   945,   953,   962,   962,   974,   975,   980,   981,   986,
     986,   997,   997,  1008,  1009,  1014,  1015,  1020,  1021,  1022,
    1023,  1024,  1025,  1028,  1030,  1030,  1038,  1040,  1042,  1050,
    1050,  1062,  1063,  1066,  1067,  1070,  1070,  1078,  1078,  1086,
    1087,  1090,  1091,  1092,  1095,  1095,  1106,  1106,  1118,  1119,
    1122,  1123,  1126,  1126,  1134,  1134,  1142,  1143,  1146,  1147,
    1148,  1149,  1150,  1151,  1152,  1155,  1155,  1163,  1168,  1168,
    1176,  1181,  1189,  1189,  1199,  1200,  1203,  1204,  1207,  1207,
    1215,  1215,  1223,  1224,  1227,  1228,  1232,  1233,  1234,  1235,
    1236,  1237,  1238,  1239,  1242,  1242,  1252,  1252,  1262,  1262,
    1270,  1270,  1278,  1278,  1286,  1286,  1299,  1299,  1309,  1309,
    1320,  1320,  1330,  1331,  1334,  1334,  1342,  1343,  1346,  1347,
    1350,  1351,  1352,  1353,  1356,  1358,  1358,  1369,  1369,  1379,
    1380,  1383,  1384,  1385,  1386,  1387,  1388,  1389,  1392,  1392,
    1399,  1400,  1401,  1404,  1409,  1409,  1417,  1422,  1429,  1436,
    1436,  1446,  1447,  1450,  1451,  1454,  1454,  1462,  1462,  1472,
    1472,  1482,  1482,  1490,  1491,  1494,  1495,  1496,  1497,  1498,
    1499,  1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,  1508,
    1509,  1512,  1517,  1517,  1525,  1525,  1533,  1538,  1538,  1546,
    1551,  1556,  1556,  1564,  1565,  1568,  1568,  1576,  1581,  1586,
    1591,  1596,  1596,  1604,  1607,  1610,  1613,  1616,  1622,  1622,
    1632,  1632,  1639,  1639,  1651,  1651,  1664,  1665,  1669,  1673,
    1673,  1685,  1686,  1690,  1690,  1698,  1699,  1702,  1703,  1704,
    1705,  1706,  1709,  1713,  1713,  1721,  1721,  1731,  1732,  1735,
    1735,  1743,  1744,  1747,  1747
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
#line 4015 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1755 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
