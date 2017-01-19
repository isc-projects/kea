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
      case 376: // duid_type
      case 409: // ncr_protocol_value
      case 418: // replace_client_name_value
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
      case 376: // duid_type
      case 409: // ncr_protocol_value
      case 418: // replace_client_name_value
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

      case 376: // duid_type

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 393 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 409: // ncr_protocol_value

#line 204 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 400 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 418: // replace_client_name_value

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
      case 376: // duid_type
      case 409: // ncr_protocol_value
      case 418: // replace_client_name_value
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

  case 44:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 306 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 355 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 372 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 410 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1046 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1310 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 759 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1527 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 851 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1643 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1681 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 978 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1827 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 1013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1863 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1071 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1192 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2076 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1258 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1294 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2263 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2284 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2505 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2604 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1580 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2763 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2956 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 2960 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -497;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
      91,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,    37,    19,    50,    70,    80,    89,    92,
     101,   149,   189,   241,   246,   254,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
      19,   -83,    17,    78,    43,    18,     7,     9,    59,    48,
      93,     6,   141,  -497,    88,   263,   245,   261,   267,  -497,
    -497,  -497,  -497,   269,  -497,    87,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,   270,   271,   272,   273,   276,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,   277,
    -497,  -497,  -497,    90,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,   284,  -497,  -497,
    -497,  -497,  -497,  -497,   280,   290,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,   133,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,   156,  -497,  -497,  -497,   291,  -497,   293,   295,
    -497,  -497,   157,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,   294,   298,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,   301,  -497,
    -497,  -497,   302,  -497,  -497,   299,   305,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,   306,  -497,
    -497,  -497,  -497,   303,   309,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,   166,  -497,  -497,  -497,   310,  -497,
    -497,   311,  -497,   312,   313,  -497,  -497,   314,   315,   317,
     318,  -497,  -497,  -497,   167,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,    19,    19,  -497,   178,   319,   320,   321,   322,
    -497,    17,  -497,   323,   324,   325,   181,   198,   199,   200,
     201,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   212,   341,   342,    78,  -497,   343,  -497,    41,   344,
     345,   346,   347,   348,   221,   222,   350,   351,   353,   354,
      18,  -497,   355,     7,  -497,   356,   229,   358,   231,   232,
       9,  -497,   361,   362,   363,   364,   365,   366,  -497,    59,
     367,   368,   247,   369,   370,   371,   248,  -497,    48,   372,
     249,  -497,    93,   373,   374,   100,  -497,   250,   376,   377,
     253,   382,   255,   257,   384,   386,   258,   259,   260,   262,
     387,   391,   141,  -497,  -497,  -497,   395,   393,   394,    19,
      19,  -497,   396,   397,   398,  -497,  -497,  -497,  -497,  -497,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
    -497,   411,   412,  -497,   415,  -497,  -497,  -497,  -497,   413,
     399,  -497,  -497,  -497,   417,   418,   283,   296,   297,  -497,
    -497,   300,   304,   419,   425,  -497,   308,  -497,   326,  -497,
     327,  -497,  -497,  -497,   415,   415,   415,   328,   329,   349,
    -497,   352,   357,  -497,   359,   360,   375,  -497,  -497,   378,
    -497,  -497,   379,    19,  -497,  -497,   380,   381,  -497,   383,
    -497,  -497,    73,   340,  -497,  -497,  -497,  -497,   -48,   385,
    -497,    19,    78,   388,  -497,  -497,    43,    14,    14,   426,
     427,   430,   -22,    19,   146,    72,   433,   110,    30,   139,
     141,  -497,  -497,   437,  -497,    41,   435,   438,  -497,  -497,
    -497,  -497,  -497,   441,   390,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,   168,  -497,   183,
    -497,  -497,   436,  -497,  -497,  -497,  -497,   445,   446,   447,
    -497,   184,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,   185,  -497,   450,   449,  -497,  -497,   455,   459,  -497,
    -497,   457,   461,  -497,  -497,  -497,   136,  -497,  -497,  -497,
     460,  -497,  -497,   140,  -497,  -497,  -497,   251,  -497,   462,
     464,  -497,   465,   466,   468,   469,   470,   471,   186,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,   472,   473,
     474,  -497,  -497,   192,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,   194,  -497,  -497,  -497,   195,   389,   392,  -497,
    -497,   475,   476,  -497,  -497,   478,   479,  -497,  -497,   480,
     482,  -497,  -497,   484,  -497,   483,   388,  -497,  -497,   489,
     490,   491,   492,   281,   400,   414,    14,  -497,  -497,    18,
    -497,   426,    48,  -497,   427,    93,  -497,   430,   -22,  -497,
    -497,   146,  -497,    72,  -497,     6,  -497,   433,   420,   421,
     422,   423,   424,   428,   110,  -497,   493,   494,   429,   431,
     432,    30,  -497,   495,   497,   139,  -497,  -497,  -497,   496,
     500,  -497,     7,  -497,   435,     9,  -497,   438,    59,  -497,
     441,   501,  -497,   448,  -497,   416,   434,   439,   440,  -497,
    -497,  -497,  -497,   196,  -497,   499,  -497,   505,  -497,  -497,
    -497,  -497,   219,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,    38,   442,  -497,  -497,  -497,  -497,   443,   444,  -497,
    -497,   451,   220,  -497,   242,  -497,   507,  -497,   452,   458,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,   252,  -497,    42,   458,  -497,  -497,   504,  -497,  -497,
    -497,   243,  -497,  -497,  -497,  -497,  -497,   513,   453,   514,
      42,  -497,   516,  -497,   456,  -497,   512,  -497,  -497,   256,
    -497,   454,   512,  -497,  -497,   244,  -497,  -497,   518,   454,
    -497,   463,  -497,  -497
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    40,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    53,     5,
      64,     7,    97,     9,   189,    11,   291,    13,   308,    15,
     334,    17,   230,    19,   265,    21,   154,    23,   415,    25,
      42,    36,     0,     0,     0,     0,     0,     0,   336,   232,
     267,     0,     0,    44,     0,    43,     0,     0,    37,    62,
     468,   464,   466,     0,    61,     0,    55,    57,    59,    60,
      58,    95,   101,   103,     0,     0,     0,     0,     0,   181,
     222,   257,   129,   144,   137,   364,   146,   165,   381,     0,
     403,   413,    89,     0,    66,    68,    69,    70,    71,    72,
      74,    75,    76,    77,    79,    78,    83,    84,    73,    81,
      82,    80,    85,    86,    87,    88,    99,     0,   368,   283,
     300,   210,   212,   214,     0,     0,   218,   216,   326,   360,
     209,   193,   194,   195,   196,     0,   191,   200,   201,   202,
     205,   207,   203,   204,   197,   198,   199,   206,   208,   298,
     297,   296,     0,   293,   295,   319,     0,   322,     0,     0,
     318,   315,     0,   310,   312,   313,   316,   317,   314,   358,
     348,   350,   352,   354,   356,   347,   346,     0,   337,   338,
     342,   343,   340,   344,   345,   341,   247,   124,     0,   251,
     249,   254,     0,   243,   244,     0,   233,   234,   236,   246,
     237,   238,   239,   253,   240,   241,   242,   278,     0,   276,
     277,   280,   281,     0,   268,   269,   271,   272,   273,   274,
     275,   161,   163,   158,     0,   156,   159,   160,     0,   436,
     438,     0,   441,     0,     0,   445,   449,     0,     0,     0,
       0,   455,   462,   434,     0,   417,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,    41,     0,     0,    35,     0,     0,     0,     0,     0,
      52,     0,    54,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,     0,    98,   370,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   190,     0,     0,   292,     0,     0,     0,     0,     0,
       0,   309,     0,     0,     0,     0,     0,     0,   335,     0,
       0,     0,     0,     0,     0,     0,     0,   231,     0,     0,
       0,   266,     0,     0,     0,     0,   155,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   416,    45,    38,     0,     0,     0,     0,
       0,    56,     0,     0,     0,    90,    91,    92,    93,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     402,     0,     0,    67,     0,   379,   377,   378,   376,     0,
     371,   372,   374,   375,     0,     0,     0,     0,     0,   220,
     221,     0,     0,     0,     0,   192,     0,   294,     0,   321,
       0,   324,   325,   311,     0,     0,     0,     0,     0,     0,
     339,     0,     0,   245,     0,     0,     0,   256,   235,     0,
     282,   270,     0,     0,   157,   435,     0,     0,   440,     0,
     443,   444,     0,     0,   451,   452,   453,   454,     0,     0,
     418,     0,     0,     0,   465,   467,     0,     0,     0,   183,
     224,   259,     0,    42,     0,     0,   148,     0,     0,     0,
       0,    46,   100,     0,   369,     0,   285,   302,   211,   213,
     215,   219,   217,   328,     0,   299,   320,   323,   359,   349,
     351,   353,   355,   357,   248,   125,   252,   250,   255,   279,
     162,   164,   437,   439,   442,   447,   448,   446,   450,   457,
     458,   459,   460,   461,   456,   463,    39,     0,   473,     0,
     470,   472,     0,   116,   118,   120,   122,     0,     0,     0,
     115,     0,   105,   107,   108,   109,   110,   111,   112,   113,
     114,     0,   187,     0,   184,   185,   228,     0,   225,   226,
     263,     0,   260,   261,   135,   136,     0,   131,   133,   134,
       0,   143,   141,     0,   139,   142,   366,     0,   152,     0,
     149,   150,     0,     0,     0,     0,     0,     0,     0,   167,
     169,   170,   171,   172,   173,   174,   392,   398,     0,     0,
       0,   391,   390,     0,   383,   385,   388,   386,   387,   389,
     409,   411,     0,   405,   407,   408,     0,    48,     0,   373,
     289,     0,   286,   287,   306,     0,   303,   304,   332,     0,
     329,   330,   362,     0,    63,     0,     0,   469,    96,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   104,     0,
     182,     0,   232,   223,     0,   267,   258,     0,     0,   130,
     145,     0,   138,     0,   365,     0,   147,     0,     0,     0,
       0,     0,     0,     0,     0,   166,     0,     0,     0,     0,
       0,     0,   382,     0,     0,     0,   404,   414,    50,     0,
      49,   380,     0,   284,     0,     0,   301,     0,   336,   327,
       0,     0,   361,     0,   471,     0,     0,     0,     0,   126,
     127,   128,   106,     0,   186,     0,   227,     0,   262,   132,
     140,   367,     0,   151,   175,   176,   177,   178,   179,   180,
     168,     0,     0,   397,   400,   401,   384,     0,     0,   406,
      47,     0,     0,   288,     0,   305,     0,   331,     0,     0,
     117,   119,   121,   123,   188,   229,   264,   153,   394,   395,
     396,   393,   399,   410,   412,    51,   290,   307,   333,   363,
     477,     0,   475,     0,     0,   474,   489,     0,   487,   485,
     481,     0,   479,   483,   484,   482,   476,     0,     0,     0,
       0,   478,     0,   486,     0,   480,     0,   488,   493,     0,
     491,     0,     0,   490,   497,     0,   495,   492,     0,     0,
     494,     0,   496,   498
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,     8,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,    11,  -497,  -181,  -497,  -497,  -497,   -62,  -497,
    -497,  -497,   233,  -497,  -497,  -497,  -497,    44,   211,   -47,
     -45,   -44,   -42,  -497,  -497,  -497,  -497,  -497,    45,  -497,
    -497,  -497,  -497,  -497,    39,  -138,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,   -58,  -497,  -496,  -497,  -497,  -497,
    -497,  -497,  -149,  -475,  -497,  -497,  -497,  -497,  -151,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -154,  -497,  -497,  -497,
    -150,   169,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -158,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -134,  -497,  -497,  -497,  -131,   209,  -497,  -497,  -497,  -497,
    -497,  -497,  -482,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -133,  -497,  -497,  -497,  -132,  -497,   187,  -497,
     -69,  -497,  -497,  -497,  -497,  -497,   -59,  -497,  -497,  -497,
    -497,  -497,   -51,  -497,  -497,  -497,  -135,  -497,  -497,  -497,
    -129,  -497,   182,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -171,  -497,  -497,  -497,  -163,   217,  -497,
    -497,  -497,  -497,  -497,  -497,  -166,  -497,  -497,  -497,  -157,
     226,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -161,  -497,  -497,  -497,  -156,  -497,   208,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,    62,  -497,  -497,  -497,  -497,  -497,  -497,  -125,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -136,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
      77,   190,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,   -78,  -497,  -497,  -497,  -215,  -497,  -497,
    -230,  -497,  -497,  -497,  -497,  -497,  -497,  -241,  -497,  -497,
    -245,  -497
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,    77,    78,
      37,    60,    74,    75,   502,   637,   709,   710,   112,    39,
      62,    85,    86,    87,   286,    41,    63,   113,   114,   115,
     116,   117,   118,   119,   120,   293,    43,    64,   137,   316,
     121,   294,   122,   295,   561,   562,   563,   659,   564,   660,
     565,   661,   566,   662,   214,   351,   568,   569,   570,   123,
     304,   586,   587,   588,   589,   124,   306,   593,   594,   595,
     125,   305,   126,   308,   599,   600,   601,   685,    57,    71,
     244,   245,   246,   363,   247,   364,   127,   309,   608,   609,
     610,   611,   612,   613,   614,   615,   128,   301,   573,   574,
     575,   669,    45,    65,   155,   156,   157,   321,   158,   322,
     159,   323,   160,   327,   161,   326,   162,   163,   129,   302,
     577,   578,   579,   672,    53,    69,   215,   216,   217,   218,
     219,   220,   221,   350,   222,   354,   223,   353,   224,   225,
     355,   226,   130,   303,   581,   582,   583,   675,    55,    70,
     233,   234,   235,   236,   237,   359,   238,   239,   240,   165,
     319,   641,   642,   643,   712,    47,    66,   172,   173,   174,
     332,   166,   320,   645,   646,   647,   715,    49,    67,   182,
     183,   184,   335,   185,   186,   337,   187,   188,   167,   328,
     649,   650,   651,   718,    51,    68,   197,   198,   199,   200,
     343,   201,   344,   202,   345,   203,   346,   204,   347,   205,
     342,   168,   329,   653,   721,   131,   307,   597,   318,   419,
     420,   421,   422,   423,   503,   132,   310,   623,   624,   625,
     696,   781,   626,   627,   697,   628,   629,   133,   134,   312,
     632,   633,   634,   703,   635,   704,   135,   313,    59,    72,
     264,   265,   266,   267,   368,   268,   369,   269,   270,   371,
     271,   272,   273,   374,   537,   274,   375,   275,   276,   277,
     278,   279,   380,   544,   280,   381,    88,   288,    89,   289,
      90,   287,   549,   550,   551,   655,   791,   792,   793,   801,
     802,   803,   804,   809,   805,   807,   819,   820,   821,   825,
     826,   828
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   231,   622,   150,   170,   180,   195,   213,   229,   243,
     263,   232,   230,   596,   164,   171,   181,   196,   151,   592,
     152,   153,    34,   154,    27,   138,    28,    79,    29,   553,
     554,   555,   556,   557,   558,   559,   101,    26,   101,   584,
      94,    95,    96,    97,   207,   616,   169,   101,    76,   557,
     175,   176,   177,   178,   179,   136,   139,    38,   140,   539,
     540,   541,   542,   206,   141,   142,   143,   144,   145,   146,
     101,   207,   207,   241,   242,   147,   148,    40,   207,   138,
     208,   209,   149,   210,   211,   212,   543,    42,   101,    91,
     291,    92,    93,   314,   281,   292,    44,   415,   315,    46,
      94,    95,    96,    97,    98,    99,   100,   101,    48,   585,
     617,   618,   619,   620,   189,   778,   779,   780,   190,   191,
     192,   193,   194,   207,   227,   208,   209,   228,    80,   147,
     102,   103,   104,   105,    81,    82,   330,    83,    83,   678,
      83,   331,   679,   681,   106,    83,   682,   107,    83,    83,
      30,    31,    32,    33,   108,   796,    50,   797,   798,   333,
     340,    83,   109,   110,   334,   341,   111,   241,   242,   365,
     382,   314,    83,    83,   366,   383,   654,   535,   536,    83,
     602,   603,   604,   605,   606,   607,   656,   666,   666,   694,
      83,   657,   667,   668,   695,   701,    52,   705,   382,   330,
     702,   741,   706,   707,   774,   622,   592,   584,   591,    83,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,   365,   333,    83,   630,   631,   777,   786,    84,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   340,   810,   829,    54,   283,
     787,   811,   830,    56,   683,   794,   416,   684,   795,   822,
     417,    58,   823,   518,   519,   520,   282,   418,   150,   284,
     285,   170,    83,   290,   296,   297,   298,   299,   180,   164,
     300,   311,   171,   151,   324,   152,   153,   195,   154,   181,
     384,   385,   317,   231,   325,   336,   213,   338,   196,   339,
     229,   349,   348,   232,   230,   352,   356,   357,   358,   386,
     360,   361,   362,   395,   367,   370,   372,   373,   376,   377,
     263,   378,   379,   387,   388,   389,   390,   392,   393,   394,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   414,   424,   425,
     426,   427,   428,   429,   431,   432,   430,   433,   434,   436,
     438,   439,   440,   441,   442,   444,   445,   446,   447,   448,
     449,   451,   452,   454,   455,   456,   459,   462,   463,   453,
     466,   467,   457,   460,   465,   468,   469,   470,   472,   471,
     473,   478,   474,   475,   476,   479,   477,   484,   485,   481,
     482,   483,   505,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   508,   729,   497,   498,   499,   500,
     501,   504,   506,   507,   513,   560,   560,   509,   510,   567,
     567,   511,   514,   572,   576,   512,   621,   580,   263,   515,
     598,   638,   640,   416,   658,   644,   538,   417,   648,   663,
     664,   665,   671,   769,   418,   652,   670,   516,   517,   521,
     522,   673,   674,   676,   677,   790,   680,   687,   686,   688,
     689,   531,   690,   691,   692,   693,   698,   699,   700,   714,
     523,   713,   717,   524,   716,   720,   719,   723,   525,   546,
     526,   527,   722,   725,   726,   727,   728,   751,   752,   757,
     548,   758,   760,   761,   590,   768,   528,   775,   808,   529,
     530,   532,   533,   776,   534,   788,   545,   812,   814,   818,
     708,   816,   831,   711,   391,   413,   547,   571,   732,   739,
     740,   552,   730,   743,   464,   742,   750,   734,   733,   435,
     735,   736,   738,   763,   461,   458,   737,   770,   731,   762,
     437,   765,   744,   745,   746,   747,   748,   450,   764,   767,
     749,   753,   766,   754,   755,   771,   443,   639,   824,   759,
     772,   773,   480,   782,   783,   784,   756,   636,   724,   806,
     815,   827,   785,   789,   832,   813,     0,   817,     0,     0,
       0,     0,     0,     0,   833,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   560,     0,   231,   150,   567,     0,
     213,     0,     0,   229,     0,     0,   232,   230,   164,     0,
       0,     0,   151,   243,   152,   153,     0,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   621,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     170,     0,     0,   180,     0,     0,   195,     0,     0,     0,
       0,   171,     0,     0,   181,     0,     0,   196,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   799,     0,     0,     0,   800,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   799,     0,
       0,     0,   800
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    70,   498,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,   495,    65,    66,    67,    68,    65,   494,
      65,    65,    14,    65,     5,     7,     7,    10,     9,    15,
      16,    17,    18,    19,    20,    21,    29,     0,    29,    61,
      22,    23,    24,    25,    30,    15,    39,    29,   131,    19,
      41,    42,    43,    44,    45,    12,    38,     7,    40,   107,
     108,   109,   110,    15,    46,    47,    48,    49,    50,    51,
      29,    30,    30,    67,    68,    57,    58,     7,    30,     7,
      32,    33,    64,    35,    36,    37,   134,     7,    29,    11,
       3,    13,    14,     3,     6,     8,     7,    56,     8,     7,
      22,    23,    24,    25,    26,    27,    28,    29,     7,   131,
      80,    81,    82,    83,    55,    77,    78,    79,    59,    60,
      61,    62,    63,    30,    31,    32,    33,    34,   111,    57,
      52,    53,    54,    55,   117,   118,     3,   131,   131,     3,
     131,     8,     6,     3,    66,   131,     6,    69,   131,   131,
     131,   132,   133,   134,    76,   113,     7,   115,   116,     3,
       3,   131,    84,    85,     8,     8,    88,    67,    68,     3,
       3,     3,   131,   131,     8,     8,     8,   104,   105,   131,
      70,    71,    72,    73,    74,    75,     3,     3,     3,     3,
     131,     8,     8,     8,     8,     3,     7,     3,     3,     3,
       8,   683,     8,     8,     8,   701,   681,    61,    62,   131,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     3,     3,   131,    86,    87,     8,     8,   291,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     3,     3,     3,     7,     4,
       8,     8,     8,     7,     3,     3,   318,     6,     6,     3,
     318,     7,     6,   444,   445,   446,     3,   318,   330,     8,
       3,   333,   131,     4,     4,     4,     4,     4,   340,   330,
       4,     4,   333,   330,     4,   330,   330,   349,   330,   340,
     282,   283,     8,   362,     4,     4,   358,     4,   349,     4,
     362,     3,     8,   362,   362,     4,     4,     8,     3,   131,
       4,     8,     3,   132,     4,     4,     4,     4,     4,     4,
     382,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     132,   132,   132,   132,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   132,     4,     4,     4,     4,     4,
       4,     4,     4,   132,     4,     4,   134,     4,     4,     4,
       4,   132,     4,   132,   132,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   132,
       4,     4,   134,   134,   134,   132,     4,   132,     4,   132,
       4,     4,   134,   134,   134,     4,   134,   389,   390,     4,
       7,     7,     3,     7,     7,     7,     5,     5,     5,     5,
       5,     5,     5,     5,   131,   134,     7,     7,     7,     7,
       5,     8,     5,     5,     5,   487,   488,   131,   131,   487,
     488,   131,     7,     7,     7,   131,   498,     7,   500,   131,
       7,     4,     7,   505,     8,     7,   106,   505,     7,     4,
       4,     4,     3,     5,   505,    65,     6,   131,   131,   131,
     131,     6,     3,     6,     3,     7,     6,     3,     6,     4,
       4,   463,     4,     4,     4,     4,     4,     4,     4,     3,
     131,     6,     3,   131,     6,     3,     6,     4,   131,   481,
     131,   131,     8,     4,     4,     4,     4,     4,     4,     4,
     112,     4,     6,     3,   493,     4,   131,     8,     4,   131,
     131,   131,   131,     8,   131,     8,   131,     4,     4,     7,
     131,     5,     4,   131,   291,   314,   482,   488,   666,   678,
     681,   486,   132,   687,   365,   685,   694,   671,   669,   330,
     672,   674,   677,   714,   362,   358,   675,   131,   134,   712,
     333,   717,   132,   132,   132,   132,   132,   349,   715,   720,
     132,   132,   718,   132,   132,   131,   340,   505,   114,   705,
     131,   131,   382,   131,   131,   131,   701,   500,   656,   794,
     810,   822,   131,   131,   829,   132,    -1,   131,    -1,    -1,
      -1,    -1,    -1,    -1,   131,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   666,    -1,   675,   669,   666,    -1,
     672,    -1,    -1,   675,    -1,    -1,   675,   675,   669,    -1,
      -1,    -1,   669,   685,   669,   669,    -1,   669,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   701,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     712,    -1,    -1,   715,    -1,    -1,   718,    -1,    -1,    -1,
      -1,   712,    -1,    -1,   715,    -1,    -1,   718,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   793,    -1,    -1,    -1,   793,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   810,    -1,
      -1,    -1,   810
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,     0,     5,     7,     9,
     131,   132,   133,   134,   149,   150,   151,   155,     7,   164,
       7,   170,     7,   181,     7,   247,     7,   310,     7,   322,
       7,   339,     7,   269,     7,   293,     7,   223,     7,   393,
     156,   152,   165,   171,   182,   248,   311,   323,   340,   270,
     294,   224,   394,   149,   157,   158,   131,   153,   154,    10,
     111,   117,   118,   131,   163,   166,   167,   168,   421,   423,
     425,    11,    13,    14,    22,    23,    24,    25,    26,    27,
      28,    29,    52,    53,    54,    55,    66,    69,    76,    84,
      85,    88,   163,   172,   173,   174,   175,   176,   177,   178,
     179,   185,   187,   204,   210,   215,   217,   231,   241,   263,
     287,   360,   370,   382,   383,   391,    12,   183,     7,    38,
      40,    46,    47,    48,    49,    50,    51,    57,    58,    64,
     163,   174,   175,   176,   177,   249,   250,   251,   253,   255,
     257,   259,   261,   262,   287,   304,   316,   333,   356,    39,
     163,   287,   312,   313,   314,    41,    42,    43,    44,    45,
     163,   287,   324,   325,   326,   328,   329,   331,   332,    55,
      59,    60,    61,    62,    63,   163,   287,   341,   342,   343,
     344,   346,   348,   350,   352,   354,    15,    30,    32,    33,
      35,    36,    37,   163,   199,   271,   272,   273,   274,   275,
     276,   277,   279,   281,   283,   284,   286,    31,    34,   163,
     199,   275,   281,   295,   296,   297,   298,   299,   301,   302,
     303,    67,    68,   163,   225,   226,   227,   229,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   163,   395,   396,   397,   398,   400,   402,
     403,   405,   406,   407,   410,   412,   413,   414,   415,   416,
     419,     6,     3,     4,     8,     3,   169,   426,   422,   424,
       4,     3,     8,   180,   186,   188,     4,     4,     4,     4,
       4,   242,   264,   288,   205,   216,   211,   361,   218,   232,
     371,     4,   384,   392,     3,     8,   184,     8,   363,   305,
     317,   252,   254,   256,     4,     4,   260,   258,   334,   357,
       3,     8,   315,     3,     8,   327,     4,   330,     4,     4,
       3,     8,   355,   345,   347,   349,   351,   353,     8,     3,
     278,   200,     4,   282,   280,   285,     4,     8,     3,   300,
       4,     8,     3,   228,   230,     3,     8,     4,   399,   401,
       4,   404,     4,     4,   408,   411,     4,     4,     4,     4,
     417,   420,     3,     8,   149,   149,   131,     4,     4,     4,
       4,   167,     4,     4,     4,   132,   132,   132,   132,   132,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     132,     4,     4,   173,     4,    56,   163,   199,   287,   364,
     365,   366,   367,   368,     4,     4,     4,     4,     4,   132,
     134,     4,     4,     4,     4,   250,     4,   313,     4,   132,
       4,   132,   132,   325,     4,     4,     4,     4,     4,     4,
     343,     4,     4,   132,     4,     4,     4,   134,   273,     4,
     134,   297,     4,     4,   226,   134,     4,     4,   132,     4,
     132,   132,     4,     4,   134,   134,   134,   134,     4,     4,
     396,     4,     7,     7,   149,   149,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   159,   369,     8,     3,     5,     5,   131,   131,
     131,   131,   131,     5,     7,   131,   131,   131,   159,   159,
     159,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   149,   131,   131,   131,   104,   105,   409,   106,   107,
     108,   109,   110,   134,   418,   131,   149,   172,   112,   427,
     428,   429,   183,    15,    16,    17,    18,    19,    20,    21,
     163,   189,   190,   191,   193,   195,   197,   199,   201,   202,
     203,   189,     7,   243,   244,   245,     7,   265,   266,   267,
       7,   289,   290,   291,    61,   131,   206,   207,   208,   209,
     157,    62,   208,   212,   213,   214,   257,   362,     7,   219,
     220,   221,    70,    71,    72,    73,    74,    75,   233,   234,
     235,   236,   237,   238,   239,   240,    15,    80,    81,    82,
      83,   163,   201,   372,   373,   374,   377,   378,   380,   381,
      86,    87,   385,   386,   387,   389,   395,   160,     4,   366,
       7,   306,   307,   308,     7,   318,   319,   320,     7,   335,
     336,   337,    65,   358,     8,   430,     3,     8,     8,   192,
     194,   196,   198,     4,     4,     4,     3,     8,     8,   246,
       6,     3,   268,     6,     3,   292,     6,     3,     3,     6,
       6,     3,     6,     3,     6,   222,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   375,   379,     4,     4,
       4,     3,     8,   388,   390,     3,     8,     8,   131,   161,
     162,   131,   309,     6,     3,   321,     6,     3,   338,     6,
       3,   359,     8,     4,   428,     4,     4,     4,     4,   134,
     132,   134,   190,   249,   245,   271,   267,   295,   291,   207,
     213,   257,   225,   221,   132,   132,   132,   132,   132,   132,
     234,     4,     4,   132,   132,   132,   373,     4,     4,   386,
       6,     3,   312,   308,   324,   320,   341,   337,     4,     5,
     131,   131,   131,   131,     8,     8,     8,     8,    77,    78,
      79,   376,   131,   131,   131,   131,     8,     8,     8,   131,
       7,   431,   432,   433,     3,     6,   113,   115,   116,   163,
     199,   434,   435,   436,   437,   439,   432,   440,     4,   438,
       3,     8,     4,   132,     4,   435,     5,   131,     7,   441,
     442,   443,     3,     6,   114,   444,   445,   442,   446,     3,
       8,     4,   445,   131
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   135,   137,   136,   138,   136,   139,   136,   140,   136,
     141,   136,   142,   136,   143,   136,   144,   136,   145,   136,
     146,   136,   147,   136,   148,   136,   149,   149,   149,   149,
     149,   149,   149,   150,   152,   151,   153,   153,   154,   154,
     156,   155,   157,   157,   158,   158,   160,   159,   161,   161,
     162,   162,   163,   165,   164,   166,   166,   167,   167,   167,
     167,   167,   169,   168,   171,   170,   172,   172,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     174,   175,   176,   177,   178,   180,   179,   182,   181,   184,
     183,   186,   185,   188,   187,   189,   189,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   192,   191,   194,   193,
     196,   195,   198,   197,   200,   199,   201,   202,   203,   205,
     204,   206,   206,   207,   207,   208,   209,   211,   210,   212,
     212,   213,   213,   214,   216,   215,   218,   217,   219,   219,
     220,   220,   222,   221,   224,   223,   225,   225,   225,   226,
     226,   228,   227,   230,   229,   232,   231,   233,   233,   234,
     234,   234,   234,   234,   234,   235,   236,   237,   238,   239,
     240,   242,   241,   243,   243,   244,   244,   246,   245,   248,
     247,   249,   249,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     252,   251,   254,   253,   256,   255,   258,   257,   260,   259,
     261,   262,   264,   263,   265,   265,   266,   266,   268,   267,
     270,   269,   271,   271,   272,   272,   273,   273,   273,   273,
     273,   273,   273,   273,   274,   275,   276,   278,   277,   280,
     279,   282,   281,   283,   285,   284,   286,   288,   287,   289,
     289,   290,   290,   292,   291,   294,   293,   295,   295,   296,
     296,   297,   297,   297,   297,   297,   297,   298,   300,   299,
     301,   302,   303,   305,   304,   306,   306,   307,   307,   309,
     308,   311,   310,   312,   312,   313,   313,   313,   315,   314,
     317,   316,   318,   318,   319,   319,   321,   320,   323,   322,
     324,   324,   325,   325,   325,   325,   325,   325,   325,   327,
     326,   328,   330,   329,   331,   332,   334,   333,   335,   335,
     336,   336,   338,   337,   340,   339,   341,   341,   342,   342,
     343,   343,   343,   343,   343,   343,   343,   343,   345,   344,
     347,   346,   349,   348,   351,   350,   353,   352,   355,   354,
     357,   356,   359,   358,   361,   360,   362,   362,   363,   257,
     364,   364,   365,   365,   366,   366,   366,   366,   367,   369,
     368,   371,   370,   372,   372,   373,   373,   373,   373,   373,
     373,   373,   375,   374,   376,   376,   376,   377,   379,   378,
     380,   381,   382,   384,   383,   385,   385,   386,   386,   388,
     387,   390,   389,   392,   391,   394,   393,   395,   395,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   397,   399,   398,   401,   400,
     402,   404,   403,   405,   406,   408,   407,   409,   409,   411,
     410,   412,   413,   414,   415,   417,   416,   418,   418,   418,
     418,   418,   420,   419,   422,   421,   424,   423,   426,   425,
     427,   427,   428,   430,   429,   431,   431,   433,   432,   434,
     434,   435,   435,   435,   435,   435,   436,   438,   437,   440,
     439,   441,   441,   443,   442,   444,   444,   446,   445
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     1,     3,     5,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     0,     6,     0,     4,     0,
       4,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     0,     6,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
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
  "not_empty_map", "list_generic", "$@14", "list_content",
  "not_empty_list", "list_strings", "$@15", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@16",
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
     273,   273,   280,   281,   284,   288,   295,   295,   302,   303,
     306,   310,   321,   331,   331,   343,   344,   348,   349,   350,
     351,   352,   355,   355,   372,   372,   380,   381,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     410,   415,   420,   425,   430,   435,   435,   445,   445,   453,
     453,   463,   463,   473,   473,   483,   484,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   498,   498,   506,   506,
     514,   514,   522,   522,   530,   530,   538,   543,   548,   553,
     553,   563,   564,   567,   568,   571,   576,   581,   581,   591,
     592,   595,   596,   599,   606,   606,   616,   616,   626,   627,
     630,   631,   634,   634,   642,   642,   650,   651,   652,   655,
     656,   659,   659,   667,   667,   675,   675,   685,   686,   689,
     690,   691,   692,   693,   694,   697,   702,   707,   712,   717,
     722,   730,   730,   743,   744,   747,   748,   755,   755,   778,
     778,   787,   788,   792,   793,   794,   795,   796,   797,   798,
     799,   800,   801,   802,   803,   804,   805,   806,   807,   808,
     811,   811,   819,   819,   827,   827,   835,   835,   843,   843,
     851,   856,   865,   865,   877,   878,   881,   882,   887,   887,
     898,   898,   908,   909,   912,   913,   916,   917,   918,   919,
     920,   921,   922,   923,   926,   928,   933,   935,   935,   943,
     943,   951,   951,   959,   961,   961,   969,   978,   978,   990,
     991,   996,   997,  1002,  1002,  1013,  1013,  1024,  1025,  1030,
    1031,  1036,  1037,  1038,  1039,  1040,  1041,  1044,  1046,  1046,
    1054,  1056,  1058,  1066,  1066,  1078,  1079,  1082,  1083,  1086,
    1086,  1094,  1094,  1102,  1103,  1106,  1107,  1108,  1111,  1111,
    1122,  1122,  1134,  1135,  1138,  1139,  1142,  1142,  1150,  1150,
    1158,  1159,  1162,  1163,  1164,  1165,  1166,  1167,  1168,  1171,
    1171,  1179,  1184,  1184,  1192,  1197,  1205,  1205,  1215,  1216,
    1219,  1220,  1223,  1223,  1231,  1231,  1239,  1240,  1243,  1244,
    1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1258,  1258,
    1268,  1268,  1278,  1278,  1286,  1286,  1294,  1294,  1302,  1302,
    1315,  1315,  1325,  1325,  1336,  1336,  1346,  1347,  1350,  1350,
    1358,  1359,  1362,  1363,  1366,  1367,  1368,  1369,  1372,  1374,
    1374,  1385,  1385,  1395,  1396,  1399,  1400,  1401,  1402,  1403,
    1404,  1405,  1408,  1408,  1415,  1416,  1417,  1420,  1425,  1425,
    1433,  1438,  1445,  1452,  1452,  1462,  1463,  1466,  1467,  1470,
    1470,  1478,  1478,  1488,  1488,  1498,  1498,  1506,  1507,  1510,
    1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,  1520,
    1521,  1522,  1523,  1524,  1525,  1528,  1533,  1533,  1541,  1541,
    1549,  1554,  1554,  1562,  1567,  1572,  1572,  1580,  1581,  1584,
    1584,  1592,  1597,  1602,  1607,  1612,  1612,  1620,  1623,  1626,
    1629,  1632,  1638,  1638,  1648,  1648,  1655,  1655,  1667,  1667,
    1680,  1681,  1685,  1689,  1689,  1701,  1702,  1706,  1706,  1714,
    1715,  1718,  1719,  1720,  1721,  1722,  1725,  1729,  1729,  1737,
    1737,  1747,  1748,  1751,  1751,  1759,  1760,  1763,  1763
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
#line 4041 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1771 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
