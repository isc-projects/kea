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
      case 158: // value
      case 162: // map_value
      case 203: // db_type
      case 395: // duid_type
      case 428: // ncr_protocol_value
      case 437: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 143: // "boolean"
        value.move< bool > (that.value);
        break;

      case 142: // "floating point"
        value.move< double > (that.value);
        break;

      case 141: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 140: // "constant string"
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
      case 158: // value
      case 162: // map_value
      case 203: // db_type
      case 395: // duid_type
      case 428: // ncr_protocol_value
      case 437: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 143: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 142: // "floating point"
        value.copy< double > (that.value);
        break;

      case 141: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 140: // "constant string"
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
            case 140: // "constant string"

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 141: // "integer"

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 142: // "floating point"

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 143: // "boolean"

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 158: // value

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 162: // map_value

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 203: // db_type

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 395: // duid_type

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 428: // ncr_protocol_value

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 437: // replace_client_name_value

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 425 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 158: // value
      case 162: // map_value
      case 203: // db_type
      case 395: // duid_type
      case 428: // ncr_protocol_value
      case 437: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 143: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 142: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 141: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 140: // "constant string"
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
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 319 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 323 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 523 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 525 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1305 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 808 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1757 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 940 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 994 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1010 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1012 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1163 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1199 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1473 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1474 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2604 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2955 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3076 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3080 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -490;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
      63,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,    74,    19,   104,   116,   149,   151,   196,
     197,   214,   249,   253,   262,   265,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
      19,   -52,    17,    31,   264,    23,    -8,    48,   105,    32,
      -5,   -36,   108,  -490,   268,   274,   275,   272,   278,  -490,
    -490,  -490,  -490,   282,  -490,    83,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   283,   284,   290,   291,   293,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   295,
    -490,  -490,  -490,   102,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   298,  -490,  -490,
    -490,  -490,  -490,  -490,   297,   299,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   118,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   119,  -490,  -490,  -490,  -490,   310,  -490,
     311,   312,  -490,  -490,  -490,   128,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     309,   315,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   316,  -490,  -490,  -490,   317,  -490,  -490,   314,   320,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   321,  -490,  -490,  -490,  -490,   318,   324,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   130,  -490,  -490,
    -490,   325,  -490,  -490,   326,  -490,   327,   328,  -490,  -490,
     329,   330,   331,   332,  -490,  -490,  -490,   137,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,    19,    19,  -490,   158,   333,
     334,   335,   336,  -490,    17,  -490,   337,   338,   339,   161,
     178,   187,   203,   204,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   215,   353,   354,    31,  -490,   355,
    -490,    -6,   356,   357,   358,   359,   360,   224,   223,   363,
     364,   365,   366,    23,  -490,   367,   368,    -8,  -490,   369,
     235,   370,   236,   238,    48,  -490,   371,   374,   376,   377,
     378,   379,  -490,   105,   380,   381,   245,   383,   384,   385,
     248,  -490,    32,   386,   252,  -490,    -5,   388,   389,   -19,
    -490,   254,   390,   392,   257,   395,   261,   263,   399,   401,
     266,   267,   269,   270,   402,   403,   108,  -490,  -490,  -490,
     404,   407,   408,    19,    19,  -490,   409,   410,   411,  -490,
    -490,  -490,  -490,  -490,   406,   414,   415,   416,   417,   418,
     419,   420,   421,   422,  -490,   425,   426,  -490,   431,  -490,
    -490,  -490,  -490,   429,   423,  -490,  -490,  -490,   433,   434,
     287,   300,   302,  -490,  -490,   304,   305,   441,   440,  -490,
     313,   442,  -490,   319,  -490,   323,  -490,  -490,  -490,   431,
     431,   431,   340,   341,   352,  -490,   361,   362,  -490,   372,
     373,   375,  -490,  -490,   382,  -490,  -490,   387,    19,  -490,
    -490,   391,   393,  -490,   394,  -490,  -490,    16,   396,  -490,
    -490,  -490,  -490,    -4,   397,  -490,    19,    31,   398,  -490,
    -490,   264,   126,   126,   443,   444,   447,   -32,    19,    96,
      41,   448,    99,    28,   172,   108,  -490,  -490,   452,  -490,
      -6,   450,   451,  -490,  -490,  -490,  -490,  -490,   453,   400,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   162,  -490,   219,  -490,  -490,   456,
    -490,  -490,  -490,  -490,   457,   461,   462,   463,   464,  -490,
    -490,  -490,   220,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,   221,  -490,   465,   466,
    -490,  -490,   467,   469,  -490,  -490,   470,   474,  -490,  -490,
    -490,    81,  -490,  -490,  -490,   472,  -490,  -490,   237,  -490,
    -490,  -490,   251,  -490,   473,   479,  -490,   480,   481,   482,
     483,   484,   485,   227,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   486,   487,   490,  -490,  -490,   230,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   231,  -490,  -490,
    -490,   233,   405,   412,  -490,  -490,   477,   492,  -490,  -490,
     491,   493,  -490,  -490,   494,   495,  -490,  -490,   496,  -490,
     499,   398,  -490,  -490,   501,   502,   503,   504,   413,   424,
     427,   428,   432,   505,   506,   126,  -490,  -490,    23,  -490,
     443,    32,  -490,   444,    -5,  -490,   447,   -32,  -490,  -490,
      96,  -490,    41,  -490,   -36,  -490,   448,   435,   436,   437,
     438,   439,   445,    99,  -490,   510,   512,   446,   449,   454,
      28,  -490,   513,   514,   172,  -490,  -490,  -490,   515,   517,
    -490,    -8,  -490,   450,    48,  -490,   451,   105,  -490,   453,
     519,  -490,   520,  -490,   294,   430,   458,   459,  -490,  -490,
    -490,  -490,  -490,   460,   468,  -490,   234,  -490,   516,  -490,
     518,  -490,  -490,  -490,  -490,   241,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   -37,   471,  -490,  -490,  -490,  -490,
     475,   476,  -490,  -490,   478,   243,  -490,   244,  -490,   521,
    -490,   488,   523,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     258,  -490,    65,   523,  -490,  -490,   524,  -490,  -490,  -490,
     247,  -490,  -490,  -490,  -490,  -490,   528,   455,   531,    65,
    -490,   533,  -490,   507,  -490,   529,  -490,  -490,   259,  -490,
     489,   529,  -490,  -490,   250,  -490,  -490,   535,   489,  -490,
     508,  -490,  -490
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   204,    11,   306,    13,   326,    15,
     353,    17,   245,    19,   280,    21,   169,    23,   434,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   355,   247,
     282,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     487,   483,   485,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   102,   104,     0,     0,     0,     0,     0,   196,
     237,   272,   144,   159,   152,   383,   161,   180,   400,     0,
     422,   432,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   100,     0,   387,   298,
     318,   225,   227,   229,     0,     0,   233,   231,   345,   379,
     224,   208,   209,   210,   211,     0,   206,   215,   216,   217,
     220,   222,   218,   219,   212,   213,   214,   221,   223,   314,
     316,   313,   311,     0,   308,   310,   312,   338,     0,   341,
       0,     0,   337,   333,   336,     0,   328,   330,   331,   334,
     335,   332,   377,   367,   369,   371,   373,   375,   366,   365,
       0,   356,   357,   361,   362,   359,   363,   364,   360,   262,
     134,     0,   266,   264,   269,     0,   258,   259,     0,   248,
     249,   251,   261,   252,   253,   254,   268,   255,   256,   257,
     293,     0,   291,   292,   295,   296,     0,   283,   284,   286,
     287,   288,   289,   290,   176,   178,   173,     0,   171,   174,
     175,     0,   455,   457,     0,   460,     0,     0,   464,   468,
       0,     0,     0,     0,   474,   481,   453,     0,   436,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,    42,     0,     0,    35,     0,     0,
       0,     0,     0,    53,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      99,   389,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,     0,   307,     0,
       0,     0,     0,     0,     0,   327,     0,     0,     0,     0,
       0,     0,   354,     0,     0,     0,     0,     0,     0,     0,
       0,   246,     0,     0,     0,   281,     0,     0,     0,     0,
     170,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   435,    46,    39,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    91,
      92,    93,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   421,     0,     0,    68,     0,   398,
     396,   397,   395,     0,   390,   391,   393,   394,     0,     0,
       0,     0,     0,   235,   236,     0,     0,     0,     0,   207,
       0,     0,   309,     0,   340,     0,   343,   344,   329,     0,
       0,     0,     0,     0,     0,   358,     0,     0,   260,     0,
       0,     0,   271,   250,     0,   297,   285,     0,     0,   172,
     454,     0,     0,   459,     0,   462,   463,     0,     0,   470,
     471,   472,   473,     0,     0,   437,     0,     0,     0,   484,
     486,     0,     0,     0,   198,   239,   274,     0,    43,     0,
       0,   163,     0,     0,     0,     0,    47,   101,     0,   388,
       0,   300,   320,   226,   228,   230,   234,   232,   347,     0,
     315,    36,   317,   339,   342,   378,   368,   370,   372,   374,
     376,   263,   135,   267,   265,   270,   294,   177,   179,   456,
     458,   461,   466,   467,   465,   469,   476,   477,   478,   479,
     480,   475,   482,    40,     0,   492,     0,   489,   491,     0,
     121,   127,   129,   131,     0,     0,     0,     0,     0,   140,
     142,   120,     0,   106,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,     0,   202,     0,   199,
     200,   243,     0,   240,   241,   278,     0,   275,   276,   150,
     151,     0,   146,   148,   149,     0,   158,   156,     0,   154,
     157,   385,     0,   167,     0,   164,   165,     0,     0,     0,
       0,     0,     0,     0,   182,   184,   185,   186,   187,   188,
     189,   411,   417,     0,     0,     0,   410,   409,     0,   402,
     404,   407,   405,   406,   408,   428,   430,     0,   424,   426,
     427,     0,    49,     0,   392,   304,     0,   301,   302,   324,
       0,   321,   322,   351,     0,   348,   349,   381,     0,    64,
       0,     0,   488,    97,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   103,   105,     0,   197,
       0,   247,   238,     0,   282,   273,     0,     0,   145,   160,
       0,   153,     0,   384,     0,   162,     0,     0,     0,     0,
       0,     0,     0,     0,   181,     0,     0,     0,     0,     0,
       0,   401,     0,     0,     0,   423,   433,    51,     0,    50,
     399,     0,   299,     0,     0,   319,     0,   355,   346,     0,
       0,   380,     0,   490,     0,     0,     0,     0,   133,   136,
     137,   138,   139,     0,     0,   107,     0,   201,     0,   242,
       0,   277,   147,   155,   386,     0,   166,   190,   191,   192,
     193,   194,   195,   183,     0,     0,   416,   419,   420,   403,
       0,     0,   425,    48,     0,     0,   303,     0,   323,     0,
     350,     0,     0,   123,   124,   125,   126,   122,   128,   130,
     132,   141,   143,   203,   244,   279,   168,   413,   414,   415,
     412,   418,   429,   431,    52,   305,   325,   352,   382,   496,
       0,   494,     0,     0,   493,   508,     0,   506,   504,   500,
       0,   498,   502,   503,   501,   495,     0,     0,     0,     0,
     497,     0,   505,     0,   499,     0,   507,   512,     0,   510,
       0,     0,   509,   516,     0,   514,   511,     0,     0,   513,
       0,   515,   517
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,     7,  -490,    29,  -490,  -490,  -490,
    -490,  -490,  -490,     1,  -490,  -265,  -490,  -490,  -490,   -62,
    -490,  -490,  -490,   246,  -490,  -490,  -490,  -490,    54,   225,
     -63,   -50,   -49,   -43,  -490,  -490,  -490,  -490,  -490,    52,
    -490,  -490,  -490,  -490,  -490,    51,  -139,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   -58,  -490,  -489,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -150,  -474,  -490,  -490,  -490,  -490,  -152,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -157,  -490,  -490,  -490,  -154,   182,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -160,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -135,  -490,
    -490,  -490,  -132,   226,  -490,  -490,  -490,  -490,  -490,  -490,
    -477,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -136,  -490,  -490,  -490,  -133,  -490,   198,  -490,   -59,  -490,
    -490,  -490,  -490,  -490,   -57,  -490,  -490,  -490,  -490,  -490,
     -48,  -490,  -490,  -490,  -134,  -490,  -490,  -490,  -131,  -490,
     195,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -169,  -490,  -490,  -490,  -166,   229,  -490,  -490,   -66,
    -490,  -490,  -490,  -490,  -490,  -167,  -490,  -490,  -490,  -162,
     239,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -165,  -490,  -490,  -490,  -156,  -490,   222,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,    72,  -490,  -490,  -490,  -490,  -490,  -490,  -129,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -140,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
      80,   202,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   -82,  -490,  -490,  -490,  -231,  -490,  -490,
    -246,  -490,  -490,  -490,  -490,  -490,  -490,  -257,  -490,  -490,
    -261,  -490
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   522,    77,
      78,    37,    60,    74,    75,   507,   652,   728,   729,   112,
      39,    62,    85,    86,    87,   289,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   296,    43,    64,   137,
     319,   121,   297,   122,   298,   572,   573,   574,   674,   797,
     575,   675,   576,   676,   577,   677,   578,   217,   355,   580,
     581,   582,   583,   584,   683,   585,   684,   123,   307,   601,
     602,   603,   604,   124,   309,   608,   609,   610,   125,   308,
     126,   311,   614,   615,   616,   704,    57,    71,   247,   248,
     249,   367,   250,   368,   127,   312,   623,   624,   625,   626,
     627,   628,   629,   630,   128,   304,   588,   589,   590,   688,
      45,    65,   155,   156,   157,   324,   158,   325,   159,   326,
     160,   330,   161,   329,   162,   163,   129,   305,   592,   593,
     594,   691,    53,    69,   218,   219,   220,   221,   222,   223,
     224,   354,   225,   358,   226,   357,   227,   228,   359,   229,
     130,   306,   596,   597,   598,   694,    55,    70,   236,   237,
     238,   239,   240,   363,   241,   242,   243,   165,   322,   656,
     657,   658,   731,    47,    66,   173,   174,   175,   335,   176,
     336,   166,   323,   660,   661,   662,   734,    49,    67,   185,
     186,   187,   339,   188,   189,   341,   190,   191,   167,   331,
     664,   665,   666,   737,    51,    68,   200,   201,   202,   203,
     347,   204,   348,   205,   349,   206,   350,   207,   351,   208,
     346,   168,   332,   668,   740,   131,   310,   612,   321,   423,
     424,   425,   426,   427,   508,   132,   313,   638,   639,   640,
     715,   810,   641,   642,   716,   643,   644,   133,   134,   315,
     647,   648,   649,   722,   650,   723,   135,   316,    59,    72,
     267,   268,   269,   270,   372,   271,   373,   272,   273,   375,
     274,   275,   276,   378,   544,   277,   379,   278,   279,   280,
     281,   282,   384,   551,   283,   385,    88,   291,    89,   292,
      90,   290,   556,   557,   558,   670,   820,   821,   822,   830,
     831,   832,   833,   838,   834,   836,   848,   849,   850,   854,
     855,   857
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   184,   151,   150,   171,   182,   198,   216,   232,   246,
     266,   234,   233,   235,   637,   152,   153,   164,   172,   183,
     199,    34,   154,   611,    27,   607,    28,    79,    29,   101,
     138,   101,   210,   210,   230,   211,   212,   231,   599,   169,
     244,   245,    91,   631,    92,    93,   170,   209,   138,   807,
     808,   809,   565,    94,    95,    96,    97,   244,   245,   419,
     101,    94,    95,    96,    97,    98,    99,   100,   101,   139,
     210,   140,   211,   212,    26,   213,   214,   215,   141,   142,
     143,   144,   145,   146,   697,   101,   294,   698,    76,   147,
     148,   295,   102,   103,   104,   105,   149,   177,   178,   179,
     180,   181,   170,   210,    83,   317,   106,   147,   600,   107,
     318,    38,   546,   547,   548,   549,   108,   632,   633,   634,
     635,   333,   337,    40,   109,   110,   334,   338,   111,   542,
     543,   344,    83,   369,    83,    83,   345,    80,   370,   550,
     386,   560,   101,    81,    82,   387,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,    42,    83,    44,    30,
      31,    32,    33,    83,   210,   317,   599,   606,    83,   192,
     669,    83,    83,   193,   194,   195,   196,   197,   617,   618,
     619,   620,   621,   622,   525,   526,   527,   825,    83,   826,
     827,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    46,    48,    83,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,    50,   671,   685,   685,   764,   607,   672,   686,   687,
     713,   637,    84,   720,   724,   714,   386,   333,   721,   725,
     700,   726,   803,   701,   369,    83,   337,   344,    83,   806,
     839,   815,   816,   858,   702,   840,    52,   703,   859,   420,
      54,   823,   851,   421,   824,   852,    83,   645,   646,    56,
     151,   150,    58,   422,   284,   171,   136,   285,   184,   286,
     287,   288,   182,   152,   153,   164,   293,   299,   300,   172,
     154,   198,   388,   389,   301,   302,   183,   303,   390,   314,
     216,   327,   399,   328,   232,   199,   320,   234,   233,   235,
     793,   794,   795,   796,   340,   342,   343,   352,   353,   400,
     356,   360,   361,   362,   266,   364,   365,   366,   401,   371,
     374,   376,   377,   380,   381,   382,   383,   391,   392,   393,
     394,   396,   397,   398,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   418,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   440,   441,   443,   445,   449,   444,   446,   450,   447,
     451,   452,   453,   454,   456,   457,   458,   459,   460,   461,
     464,   462,   467,   468,   471,   465,   472,   470,   473,   474,
     489,   490,   475,   477,   476,   478,   483,   484,   486,   479,
     480,   494,   481,   482,   487,   488,   491,   492,   493,   495,
     496,   497,   498,   499,   500,   501,   510,   513,   502,   503,
     571,   571,   504,   505,   579,   579,   506,   509,   511,   512,
     514,   636,   515,   266,   516,   517,   518,   519,   420,    28,
     587,   591,   421,   520,   595,   613,   653,   655,   659,   523,
     663,   678,   422,   524,   673,   679,   680,   681,   682,   690,
     521,   689,   693,   692,   667,   538,   695,   696,   699,   705,
     528,   529,   706,   732,   707,   708,   709,   710,   711,   712,
     717,   718,   530,   553,   719,   733,   736,   735,   739,   605,
     738,   531,   532,   742,   741,   744,   745,   746,   747,   753,
     754,   545,   533,   534,   774,   535,   775,   780,   781,   555,
     784,   783,   536,   791,   804,   792,   805,   537,   837,   817,
     819,   539,   841,   540,   541,   843,   847,   552,   845,   860,
     395,   554,   417,   559,   586,   727,   755,   762,   763,   766,
     765,   469,   730,   773,   748,   757,   756,   759,   758,   439,
     463,   466,   761,   760,   786,   785,   442,   749,   750,   788,
     798,   751,   787,   752,   790,   455,   767,   768,   769,   770,
     771,   789,   654,   448,   782,   651,   772,   776,   485,   743,
     777,   779,   835,   844,   856,   778,   842,   861,   799,   800,
     801,     0,     0,     0,     0,     0,     0,     0,   802,     0,
       0,   811,   853,     0,     0,   812,   813,     0,   814,     0,
       0,     0,     0,   571,     0,   151,   150,   579,   818,   216,
       0,     0,   232,     0,     0,   234,   233,   235,   152,   153,
     164,     0,   246,     0,     0,   154,     0,   846,   862,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   636,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   184,   171,
       0,     0,   182,     0,     0,   198,     0,     0,     0,     0,
       0,     0,     0,   172,     0,     0,   183,     0,     0,   199,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     828,     0,     0,     0,   829,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   828,     0,     0,
       0,   829
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   503,    65,    65,    65,    66,    67,
      68,    14,    65,   500,     5,   499,     7,    10,     9,    37,
       7,    37,    38,    38,    39,    40,    41,    42,    70,    47,
      76,    77,    11,    15,    13,    14,    54,    15,     7,    86,
      87,    88,    24,    30,    31,    32,    33,    76,    77,    65,
      37,    30,    31,    32,    33,    34,    35,    36,    37,    46,
      38,    48,    40,    41,     0,    43,    44,    45,    55,    56,
      57,    58,    59,    60,     3,    37,     3,     6,   140,    66,
      67,     8,    61,    62,    63,    64,    73,    49,    50,    51,
      52,    53,    54,    38,   140,     3,    75,    66,   140,    78,
       8,     7,   116,   117,   118,   119,    85,    89,    90,    91,
      92,     3,     3,     7,    93,    94,     8,     8,    97,   113,
     114,     3,   140,     3,   140,   140,     8,   120,     8,   143,
       3,    15,    37,   126,   127,     8,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     7,   140,     7,   140,
     141,   142,   143,   140,    38,     3,    70,    71,   140,    64,
       8,   140,   140,    68,    69,    70,    71,    72,    79,    80,
      81,    82,    83,    84,   449,   450,   451,   122,   140,   124,
     125,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,     7,     7,   140,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,     7,     3,     3,     3,   702,   700,     8,     8,     8,
       3,   720,   294,     3,     3,     8,     3,     3,     8,     8,
       3,     8,     8,     6,     3,   140,     3,     3,   140,     8,
       3,     8,     8,     3,     3,     8,     7,     6,     8,   321,
       7,     3,     3,   321,     6,     6,   140,    95,    96,     7,
     333,   333,     7,   321,     6,   337,    12,     3,   344,     4,
       8,     3,   344,   333,   333,   333,     4,     4,     4,   337,
     333,   353,   285,   286,     4,     4,   344,     4,   140,     4,
     362,     4,   141,     4,   366,   353,     8,   366,   366,   366,
      16,    17,    18,    19,     4,     4,     4,     8,     3,   141,
       4,     4,     8,     3,   386,     4,     8,     3,   141,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   141,   141,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   141,     4,     4,     4,
       4,     4,     4,     4,     4,   141,   143,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   141,   141,     4,   141,
       4,     4,     4,     4,     4,     4,   141,     4,     4,     4,
       4,   143,     4,     4,     4,   143,     4,   143,   141,     4,
     393,   394,   141,     4,   141,     4,     4,     4,     4,   143,
     143,     5,   143,   143,     7,     7,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     3,   140,     7,     7,
     492,   493,     7,     7,   492,   493,     5,     8,     5,     5,
     140,   503,   140,   505,   140,   140,     5,     7,   510,     7,
       7,     7,   510,   140,     7,     7,     4,     7,     7,   140,
       7,     4,   510,   140,     8,     4,     4,     4,     4,     3,
     441,     6,     3,     6,    74,   468,     6,     3,     6,     6,
     140,   140,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,   140,   486,     4,     3,     3,     6,     3,   498,
       6,   140,   140,     4,     8,     4,     4,     4,     4,     4,
       4,   115,   140,   140,     4,   140,     4,     4,     4,   121,
       3,     6,   140,     4,     8,     5,     8,   140,     4,     8,
       7,   140,     4,   140,   140,     4,     7,   140,     5,     4,
     294,   487,   317,   491,   493,   140,   685,   697,   700,   706,
     704,   369,   140,   713,   141,   690,   688,   693,   691,   333,
     362,   366,   696,   694,   733,   731,   337,   143,   141,   736,
     140,   143,   734,   141,   739,   353,   141,   141,   141,   141,
     141,   737,   510,   344,   724,   505,   141,   141,   386,   671,
     141,   720,   823,   839,   851,   141,   141,   858,   140,   140,
     140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,
      -1,   140,   123,    -1,    -1,   140,   140,    -1,   140,    -1,
      -1,    -1,    -1,   685,    -1,   688,   688,   685,   140,   691,
      -1,    -1,   694,    -1,    -1,   694,   694,   694,   688,   688,
     688,    -1,   704,    -1,    -1,   688,    -1,   140,   140,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   720,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   734,   731,
      -1,    -1,   734,    -1,    -1,   737,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   731,    -1,    -1,   734,    -1,    -1,   737,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     822,    -1,    -1,    -1,   822,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   839,    -1,    -1,
      -1,   839
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,     5,     7,     9,
     140,   141,   142,   143,   158,   159,   160,   165,     7,   174,
       7,   180,     7,   191,     7,   264,     7,   327,     7,   341,
       7,   358,     7,   286,     7,   310,     7,   240,     7,   412,
     166,   161,   175,   181,   192,   265,   328,   342,   359,   287,
     311,   241,   413,   158,   167,   168,   140,   163,   164,    10,
     120,   126,   127,   140,   173,   176,   177,   178,   440,   442,
     444,    11,    13,    14,    30,    31,    32,    33,    34,    35,
      36,    37,    61,    62,    63,    64,    75,    78,    85,    93,
      94,    97,   173,   182,   183,   184,   185,   186,   187,   188,
     189,   195,   197,   221,   227,   232,   234,   248,   258,   280,
     304,   379,   389,   401,   402,   410,    12,   193,     7,    46,
      48,    55,    56,    57,    58,    59,    60,    66,    67,    73,
     173,   184,   185,   186,   187,   266,   267,   268,   270,   272,
     274,   276,   278,   279,   304,   321,   335,   352,   375,    47,
      54,   173,   304,   329,   330,   331,   333,    49,    50,    51,
      52,    53,   173,   304,   333,   343,   344,   345,   347,   348,
     350,   351,    64,    68,    69,    70,    71,    72,   173,   304,
     360,   361,   362,   363,   365,   367,   369,   371,   373,    15,
      38,    40,    41,    43,    44,    45,   173,   211,   288,   289,
     290,   291,   292,   293,   294,   296,   298,   300,   301,   303,
      39,    42,   173,   211,   292,   298,   312,   313,   314,   315,
     316,   318,   319,   320,    76,    77,   173,   242,   243,   244,
     246,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   173,   414,   415,   416,
     417,   419,   421,   422,   424,   425,   426,   429,   431,   432,
     433,   434,   435,   438,     6,     3,     4,     8,     3,   179,
     445,   441,   443,     4,     3,     8,   190,   196,   198,     4,
       4,     4,     4,     4,   259,   281,   305,   222,   233,   228,
     380,   235,   249,   390,     4,   403,   411,     3,     8,   194,
       8,   382,   322,   336,   269,   271,   273,     4,     4,   277,
     275,   353,   376,     3,     8,   332,   334,     3,     8,   346,
       4,   349,     4,     4,     3,     8,   374,   364,   366,   368,
     370,   372,     8,     3,   295,   212,     4,   299,   297,   302,
       4,     8,     3,   317,     4,     8,     3,   245,   247,     3,
       8,     4,   418,   420,     4,   423,     4,     4,   427,   430,
       4,     4,     4,     4,   436,   439,     3,     8,   158,   158,
     140,     4,     4,     4,     4,   177,     4,     4,     4,   141,
     141,   141,   141,   141,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   141,     4,     4,   183,     4,    65,
     173,   211,   304,   383,   384,   385,   386,   387,     4,     4,
       4,     4,     4,   141,   143,     4,     4,     4,     4,   267,
       4,     4,   330,     4,   141,     4,   141,   141,   344,     4,
       4,     4,     4,     4,     4,   362,     4,     4,   141,     4,
       4,     4,   143,   290,     4,   143,   314,     4,     4,   243,
     143,     4,     4,   141,     4,   141,   141,     4,     4,   143,
     143,   143,   143,     4,     4,   415,     4,     7,     7,   158,
     158,     7,     7,     7,     5,     5,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     7,     5,   169,   388,     8,
       3,     5,     5,   140,   140,   140,   140,   140,     5,     7,
     140,   160,   162,   140,   140,   169,   169,   169,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   158,   140,
     140,   140,   113,   114,   428,   115,   116,   117,   118,   119,
     143,   437,   140,   158,   182,   121,   446,   447,   448,   193,
      15,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   173,   199,   200,   201,   204,   206,   208,   210,   211,
     213,   214,   215,   216,   217,   219,   199,     7,   260,   261,
     262,     7,   282,   283,   284,     7,   306,   307,   308,    70,
     140,   223,   224,   225,   226,   167,    71,   225,   229,   230,
     231,   274,   381,     7,   236,   237,   238,    79,    80,    81,
      82,    83,    84,   250,   251,   252,   253,   254,   255,   256,
     257,    15,    89,    90,    91,    92,   173,   213,   391,   392,
     393,   396,   397,   399,   400,    95,    96,   404,   405,   406,
     408,   414,   170,     4,   385,     7,   323,   324,   325,     7,
     337,   338,   339,     7,   354,   355,   356,    74,   377,     8,
     449,     3,     8,     8,   202,   205,   207,   209,     4,     4,
       4,     4,     4,   218,   220,     3,     8,     8,   263,     6,
       3,   285,     6,     3,   309,     6,     3,     3,     6,     6,
       3,     6,     3,     6,   239,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   394,   398,     4,     4,     4,
       3,     8,   407,   409,     3,     8,     8,   140,   171,   172,
     140,   326,     6,     3,   340,     6,     3,   357,     6,     3,
     378,     8,     4,   447,     4,     4,     4,     4,   141,   143,
     141,   143,   141,     4,     4,   200,   266,   262,   288,   284,
     312,   308,   224,   230,   274,   242,   238,   141,   141,   141,
     141,   141,   141,   251,     4,     4,   141,   141,   141,   392,
       4,     4,   405,     6,     3,   329,   325,   343,   339,   360,
     356,     4,     5,    16,    17,    18,    19,   203,   140,   140,
     140,   140,   140,     8,     8,     8,     8,    86,    87,    88,
     395,   140,   140,   140,   140,     8,     8,     8,   140,     7,
     450,   451,   452,     3,     6,   122,   124,   125,   173,   211,
     453,   454,   455,   456,   458,   451,   459,     4,   457,     3,
       8,     4,   141,     4,   454,     5,   140,     7,   460,   461,
     462,     3,     6,   123,   463,   464,   461,   465,     3,     8,
       4,   464,   140
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   144,   146,   145,   147,   145,   148,   145,   149,   145,
     150,   145,   151,   145,   152,   145,   153,   145,   154,   145,
     155,   145,   156,   145,   157,   145,   158,   158,   158,   158,
     158,   158,   158,   159,   161,   160,   162,   163,   163,   164,
     164,   166,   165,   167,   167,   168,   168,   170,   169,   171,
     171,   172,   172,   173,   175,   174,   176,   176,   177,   177,
     177,   177,   177,   179,   178,   181,   180,   182,   182,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   184,   185,   186,   187,   188,   190,   189,   192,   191,
     194,   193,   196,   195,   198,   197,   199,   199,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   202,   201,   203,   203,   203,   203,   205,   204,   207,
     206,   209,   208,   210,   212,   211,   213,   214,   215,   216,
     218,   217,   220,   219,   222,   221,   223,   223,   224,   224,
     225,   226,   228,   227,   229,   229,   230,   230,   231,   233,
     232,   235,   234,   236,   236,   237,   237,   239,   238,   241,
     240,   242,   242,   242,   243,   243,   245,   244,   247,   246,
     249,   248,   250,   250,   251,   251,   251,   251,   251,   251,
     252,   253,   254,   255,   256,   257,   259,   258,   260,   260,
     261,   261,   263,   262,   265,   264,   266,   266,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   269,   268,   271,   270,   273,
     272,   275,   274,   277,   276,   278,   279,   281,   280,   282,
     282,   283,   283,   285,   284,   287,   286,   288,   288,   289,
     289,   290,   290,   290,   290,   290,   290,   290,   290,   291,
     292,   293,   295,   294,   297,   296,   299,   298,   300,   302,
     301,   303,   305,   304,   306,   306,   307,   307,   309,   308,
     311,   310,   312,   312,   313,   313,   314,   314,   314,   314,
     314,   314,   315,   317,   316,   318,   319,   320,   322,   321,
     323,   323,   324,   324,   326,   325,   328,   327,   329,   329,
     330,   330,   330,   330,   332,   331,   334,   333,   336,   335,
     337,   337,   338,   338,   340,   339,   342,   341,   343,   343,
     344,   344,   344,   344,   344,   344,   344,   344,   346,   345,
     347,   349,   348,   350,   351,   353,   352,   354,   354,   355,
     355,   357,   356,   359,   358,   360,   360,   361,   361,   362,
     362,   362,   362,   362,   362,   362,   362,   364,   363,   366,
     365,   368,   367,   370,   369,   372,   371,   374,   373,   376,
     375,   378,   377,   380,   379,   381,   381,   382,   274,   383,
     383,   384,   384,   385,   385,   385,   385,   386,   388,   387,
     390,   389,   391,   391,   392,   392,   392,   392,   392,   392,
     392,   394,   393,   395,   395,   395,   396,   398,   397,   399,
     400,   401,   403,   402,   404,   404,   405,   405,   407,   406,
     409,   408,   411,   410,   413,   412,   414,   414,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   416,   418,   417,   420,   419,   421,
     423,   422,   424,   425,   427,   426,   428,   428,   430,   429,
     431,   432,   433,   434,   436,   435,   437,   437,   437,   437,
     437,   439,   438,   441,   440,   443,   442,   445,   444,   446,
     446,   447,   449,   448,   450,   450,   452,   451,   453,   453,
     454,   454,   454,   454,   454,   455,   457,   456,   459,   458,
     460,   460,   462,   461,   463,   463,   465,   464
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     0,     1,     3,
       5,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     0,     6,     0,     4,
       0,     4,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
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
  "\"hosts-database\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"preferred-lifetime\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"record-types\"", "\"encapsulate\"",
  "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"", "\"prefix\"",
  "\"prefix-len\"", "\"excluded-prefix\"", "\"excluded-prefix-len\"",
  "\"delegated-len\"", "\"user-context\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
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
  "$@11", "$@12", "value", "sub_json", "map2", "$@13", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@14", "list_content",
  "not_empty_list", "list_strings", "$@15", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@16",
  "global_objects", "global_object", "dhcp6_object", "$@17", "sub_dhcp6",
  "$@18", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@19",
  "sub_interfaces6", "$@20", "interface_config_map", "$@21",
  "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "database_type", "$@24",
  "db_type", "user", "$@25", "password", "$@26", "host", "$@27", "port",
  "name", "$@28", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@29", "keyspace", "$@30", "mac_sources", "$@31",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@32",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "relay_supplied_options", "$@33", "hooks_libraries",
  "$@34", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@35", "sub_hooks_library", "$@36", "hooks_params",
  "hooks_param", "library", "$@37", "parameters", "$@38",
  "expired_leases_processing", "$@39", "expired_leases_params",
  "expired_leases_param", "reclaim_timer_wait_time",
  "flush_reclaimed_timer_wait_time", "hold_reclaimed_time",
  "max_reclaim_leases", "max_reclaim_time", "unwarned_reclaim_cycles",
  "subnet6_list", "$@40", "subnet6_list_content", "not_empty_subnet6_list",
  "subnet6", "$@41", "sub_subnet6", "$@42", "subnet6_params",
  "subnet6_param", "subnet", "$@43", "interface", "$@44", "interface_id",
  "$@45", "client_class", "$@46", "reservation_mode", "$@47", "id",
  "rapid_commit", "option_def_list", "$@48", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@49",
  "sub_option_def", "$@50", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@51",
  "option_def_record_types", "$@52", "space", "$@53", "option_def_space",
  "option_def_encapsulate", "$@54", "option_def_array", "option_data_list",
  "$@55", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@56", "sub_option_data", "$@57",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@58",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@59", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@60", "sub_pool6", "$@61", "pool_params",
  "pool_param", "pool_entry", "$@62", "user_context", "$@63",
  "pd_pools_list", "$@64", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@65", "sub_pd_pool",
  "$@66", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@67",
  "pd_prefix_len", "excluded_prefix", "$@68", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@69", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@70", "sub_reservation",
  "$@71", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@72", "prefixes", "$@73", "duid",
  "$@74", "hw_address", "$@75", "hostname", "$@76",
  "reservation_client_classes", "$@77", "relay", "$@78", "relay_map",
  "$@79", "client_classes", "$@80", "client_classes_list", "$@81",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@82",
  "server_id", "$@83", "server_id_params", "server_id_param",
  "server_id_type", "$@84", "duid_type", "htype", "identifier", "$@85",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@86",
  "control_socket_params", "control_socket_param", "socket_type", "$@87",
  "socket_name", "$@88", "dhcp_ddns", "$@89", "sub_dhcp_ddns", "$@90",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@91", "server_ip", "$@92", "server_port",
  "sender_ip", "$@93", "sender_port", "max_queue_size", "ncr_protocol",
  "$@94", "ncr_protocol_value", "ncr_format", "$@95",
  "always_include_fqdn", "allow_client_update", "override_no_update",
  "override_client_update", "replace_client_name", "$@96",
  "replace_client_name_value", "generated_prefix", "$@97",
  "dhcp4_json_object", "$@98", "dhcpddns_json_object", "$@99",
  "logging_object", "$@100", "logging_params", "logging_param", "loggers",
  "$@101", "loggers_entries", "logger_entry", "$@102", "logger_params",
  "logger_param", "debuglevel", "severity", "$@103", "output_options_list",
  "$@104", "output_options_list_content", "output_entry", "$@105",
  "output_params", "output_param", "$@106", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   224,   224,   224,   225,   225,   226,   226,   227,   227,
     228,   228,   229,   229,   230,   230,   231,   231,   232,   232,
     233,   233,   234,   234,   235,   235,   243,   244,   245,   246,
     247,   248,   249,   252,   257,   257,   268,   271,   272,   275,
     279,   286,   286,   293,   294,   297,   301,   308,   308,   315,
     316,   319,   323,   334,   344,   344,   356,   357,   361,   362,
     363,   364,   365,   368,   368,   385,   385,   393,   394,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   423,   428,   433,   438,   443,   448,   448,   458,   458,
     466,   466,   476,   476,   486,   486,   496,   497,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   515,   515,   522,   523,   524,   525,   528,   528,   536,
     536,   544,   544,   552,   557,   557,   565,   570,   575,   580,
     585,   585,   593,   593,   602,   602,   612,   613,   616,   617,
     620,   625,   630,   630,   640,   641,   644,   645,   648,   655,
     655,   665,   665,   675,   676,   679,   680,   683,   683,   691,
     691,   699,   700,   701,   704,   705,   708,   708,   716,   716,
     724,   724,   734,   735,   738,   739,   740,   741,   742,   743,
     746,   751,   756,   761,   766,   771,   779,   779,   792,   793,
     796,   797,   804,   804,   827,   827,   836,   837,   841,   842,
     843,   844,   845,   846,   847,   848,   849,   850,   851,   852,
     853,   854,   855,   856,   857,   860,   860,   868,   868,   876,
     876,   884,   884,   892,   892,   900,   905,   914,   914,   926,
     927,   930,   931,   936,   936,   947,   947,   957,   958,   961,
     962,   965,   966,   967,   968,   969,   970,   971,   972,   975,
     977,   982,   984,   984,   992,   992,  1000,  1000,  1008,  1010,
    1010,  1018,  1027,  1027,  1039,  1040,  1045,  1046,  1051,  1051,
    1062,  1062,  1073,  1074,  1079,  1080,  1085,  1086,  1087,  1088,
    1089,  1090,  1093,  1095,  1095,  1103,  1105,  1107,  1115,  1115,
    1127,  1128,  1131,  1132,  1135,  1135,  1143,  1143,  1151,  1152,
    1155,  1156,  1157,  1158,  1161,  1161,  1169,  1169,  1179,  1179,
    1191,  1192,  1195,  1196,  1199,  1199,  1207,  1207,  1215,  1216,
    1219,  1220,  1221,  1222,  1223,  1224,  1225,  1226,  1229,  1229,
    1237,  1242,  1242,  1250,  1255,  1263,  1263,  1273,  1274,  1277,
    1278,  1281,  1281,  1289,  1289,  1297,  1298,  1301,  1302,  1306,
    1307,  1308,  1309,  1310,  1311,  1312,  1313,  1316,  1316,  1326,
    1326,  1336,  1336,  1344,  1344,  1352,  1352,  1360,  1360,  1373,
    1373,  1383,  1383,  1394,  1394,  1404,  1405,  1408,  1408,  1416,
    1417,  1420,  1421,  1424,  1425,  1426,  1427,  1430,  1432,  1432,
    1443,  1443,  1453,  1454,  1457,  1458,  1459,  1460,  1461,  1462,
    1463,  1466,  1466,  1473,  1474,  1475,  1478,  1483,  1483,  1491,
    1496,  1503,  1510,  1510,  1520,  1521,  1524,  1525,  1528,  1528,
    1536,  1536,  1546,  1546,  1556,  1556,  1564,  1565,  1568,  1569,
    1570,  1571,  1572,  1573,  1574,  1575,  1576,  1577,  1578,  1579,
    1580,  1581,  1582,  1583,  1586,  1591,  1591,  1599,  1599,  1607,
    1612,  1612,  1620,  1625,  1630,  1630,  1638,  1639,  1642,  1642,
    1650,  1655,  1660,  1665,  1670,  1670,  1678,  1681,  1684,  1687,
    1690,  1696,  1696,  1706,  1706,  1713,  1713,  1725,  1725,  1738,
    1739,  1743,  1747,  1747,  1759,  1760,  1764,  1764,  1772,  1773,
    1776,  1777,  1778,  1779,  1780,  1783,  1787,  1787,  1795,  1795,
    1805,  1806,  1809,  1809,  1817,  1818,  1821,  1821
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
#line 4189 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1829 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
