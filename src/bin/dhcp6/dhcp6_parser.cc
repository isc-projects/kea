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
      case 206: // db_type
      case 398: // duid_type
      case 431: // ncr_protocol_value
      case 439: // replace_client_name_value
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
      case 206: // db_type
      case 398: // duid_type
      case 431: // ncr_protocol_value
      case 439: // replace_client_name_value
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

      case 206: // db_type

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 398: // duid_type

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 431: // ncr_protocol_value

#line 215 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 439: // replace_client_name_value

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
      case 206: // db_type
      case 398: // duid_type
      case 431: // ncr_protocol_value
      case 439: // replace_client_name_value
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

  case 104:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 536 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 798 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1727 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1153 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1225 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1258 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2501 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2623 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2643 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2751 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2774 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1698 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2955 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1832 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -494;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     120,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,    46,    20,    23,    64,   119,   149,   159,
     165,   183,   200,   222,   239,   255,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
      20,   -55,    18,    27,   137,    19,    -1,    44,    82,    28,
      68,    41,    92,  -494,    96,   109,   266,   161,   214,  -494,
    -494,  -494,  -494,   274,  -494,    31,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,   288,   294,   295,   298,   299,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,   301,
    -494,  -494,  -494,    40,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,   302,   140,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,   303,   306,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,   162,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,   202,  -494,  -494,
    -494,  -494,   314,  -494,   315,   316,  -494,  -494,  -494,   203,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,   264,   318,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,   319,  -494,  -494,  -494,   320,
    -494,  -494,   293,   322,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,   324,  -494,  -494,  -494,  -494,
     321,   323,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,   206,  -494,  -494,  -494,   326,  -494,  -494,   327,  -494,
     328,   329,  -494,  -494,   330,   331,   332,  -494,  -494,  -494,
     210,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,    20,    20,  -494,
     182,   333,   334,   335,   336,  -494,    18,  -494,   337,   338,
     339,   204,   205,   207,   208,   211,   340,   343,   346,   347,
     349,   350,   351,   352,   353,   354,   218,   356,   357,    27,
    -494,   358,   220,   137,  -494,    17,   360,   361,   362,   363,
     364,   228,   229,   366,   367,   369,   370,    19,  -494,   371,
     372,    -1,  -494,   373,   238,   374,   240,   241,    44,  -494,
     376,   379,   380,   381,   382,   383,  -494,    82,   384,   385,
     249,   387,   388,   389,   251,  -494,    28,   391,   253,  -494,
      68,   393,   394,   105,  -494,   256,   396,   397,   262,   398,
     263,   267,   403,   405,   269,   270,   271,   406,   407,    92,
    -494,  -494,  -494,   411,   409,   410,    20,    20,  -494,   412,
     413,   414,  -494,  -494,  -494,  -494,  -494,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,  -494,   429,   430,
    -494,   435,  -494,  -494,  -494,  -494,  -494,  -494,   433,   415,
    -494,  -494,  -494,   437,   438,   290,   291,   304,  -494,  -494,
     308,   309,   441,   443,  -494,   311,   446,  -494,   317,  -494,
     325,  -494,  -494,  -494,   435,   435,   435,   341,   344,   345,
    -494,   348,   355,  -494,   365,   368,   375,  -494,  -494,   377,
    -494,  -494,   378,    20,  -494,  -494,   386,   390,  -494,   392,
    -494,  -494,   113,   359,  -494,  -494,  -494,    69,   395,  -494,
      20,    27,   342,  -494,  -494,   137,   107,   107,   447,   448,
     451,   -40,    20,   209,    38,   452,    95,    24,   194,    92,
    -494,  -494,   456,  -494,    17,   454,   455,  -494,  -494,  -494,
    -494,  -494,   457,   400,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,   212,  -494,
     213,  -494,  -494,   216,  -494,  -494,  -494,  -494,   463,   464,
     465,   466,   467,  -494,  -494,  -494,   225,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
     227,  -494,   470,   469,  -494,  -494,   471,   475,  -494,  -494,
     473,   477,  -494,  -494,  -494,    29,  -494,  -494,  -494,   480,
    -494,  -494,    30,  -494,  -494,  -494,    78,  -494,   481,   486,
    -494,   479,   487,   488,   489,   490,   492,   233,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,   493,   494,   496,
    -494,  -494,   234,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,   235,  -494,  -494,  -494,   236,   399,   401,  -494,  -494,
     484,   498,  -494,  -494,   497,   499,  -494,  -494,   500,   501,
    -494,  -494,   502,  -494,   503,   342,  -494,  -494,   505,   507,
     508,   509,   402,   404,   408,   416,   427,   510,   512,   107,
    -494,  -494,    19,  -494,   447,    28,  -494,   448,    68,  -494,
     451,   -40,  -494,  -494,   209,  -494,    38,  -494,    41,  -494,
     452,   428,   431,   432,   434,   436,   439,    95,  -494,   515,
     516,   440,   442,   444,    24,  -494,   517,   518,   194,  -494,
    -494,  -494,   519,   520,  -494,    -1,  -494,   454,    44,  -494,
     455,    82,  -494,   457,   523,  -494,   468,  -494,   297,   449,
     450,   453,  -494,  -494,  -494,  -494,  -494,   458,   459,  -494,
     237,  -494,   521,  -494,   525,  -494,  -494,  -494,  -494,   257,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,    53,   460,
    -494,  -494,  -494,  -494,   461,   462,  -494,  -494,   472,   258,
    -494,   261,  -494,   526,  -494,   474,   524,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,    98,  -494,    49,   524,  -494,  -494,
     532,  -494,  -494,  -494,   265,  -494,  -494,  -494,  -494,  -494,
     533,   445,   534,    49,  -494,   535,  -494,   476,  -494,   537,
    -494,  -494,   121,  -494,   482,   537,  -494,  -494,   268,  -494,
    -494,   538,   482,  -494,   478,  -494,  -494
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   209,    11,   311,    13,   331,    15,
     358,    17,   250,    19,   285,    21,   174,    23,   439,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   360,   252,
     287,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     490,   486,   488,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   107,   109,     0,     0,     0,     0,     0,   201,
     242,   277,   149,   164,   157,   388,   166,   185,   405,     0,
     427,   437,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   104,     0,     0,   100,
     102,   103,   392,   303,   323,   230,   232,   234,     0,     0,
     238,   236,   350,   384,   229,   213,   214,   215,   216,     0,
     211,   220,   221,   222,   225,   227,   223,   224,   217,   218,
     219,   226,   228,   319,   321,   318,   316,     0,   313,   315,
     317,   343,     0,   346,     0,     0,   342,   338,   341,     0,
     333,   335,   336,   339,   340,   337,   382,   372,   374,   376,
     378,   380,   371,   370,     0,   361,   362,   366,   367,   364,
     368,   369,   365,   267,   139,     0,   271,   269,   274,     0,
     263,   264,     0,   253,   254,   256,   266,   257,   258,   259,
     273,   260,   261,   262,   298,     0,   296,   297,   300,   301,
       0,   288,   289,   291,   292,   293,   294,   295,   181,   183,
     178,     0,   176,   179,   180,     0,   459,   461,     0,   464,
       0,     0,   468,   472,     0,     0,     0,   477,   484,   457,
       0,   441,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,    42,     0,     0,    35,
       0,     0,     0,     0,     0,    53,     0,    55,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,     0,     0,     0,    99,   394,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   210,     0,
       0,     0,   312,     0,     0,     0,     0,     0,     0,   332,
       0,     0,     0,     0,     0,     0,   359,     0,     0,     0,
       0,     0,     0,     0,     0,   251,     0,     0,     0,   286,
       0,     0,     0,     0,   175,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     440,    46,    39,     0,     0,     0,     0,     0,    57,     0,
       0,     0,    91,    92,    93,    94,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   426,     0,     0,
      68,     0,   106,   101,   403,   401,   402,   400,     0,   395,
     396,   398,   399,     0,     0,     0,     0,     0,   240,   241,
       0,     0,     0,     0,   212,     0,     0,   314,     0,   345,
       0,   348,   349,   334,     0,     0,     0,     0,     0,     0,
     363,     0,     0,   265,     0,     0,     0,   276,   255,     0,
     302,   290,     0,     0,   177,   458,     0,     0,   463,     0,
     466,   467,     0,     0,   474,   475,   476,     0,     0,   442,
       0,     0,     0,   487,   489,     0,     0,     0,   203,   244,
     279,     0,    43,     0,     0,   168,     0,     0,     0,     0,
      47,   105,     0,   393,     0,   305,   325,   231,   233,   235,
     239,   237,   352,     0,   320,    36,   322,   344,   347,   383,
     373,   375,   377,   379,   381,   268,   140,   272,   270,   275,
     299,   182,   184,   460,   462,   465,   470,   471,   469,   473,
     479,   480,   481,   482,   483,   478,   485,    40,     0,   495,
       0,   492,   494,     0,   126,   132,   134,   136,     0,     0,
       0,     0,     0,   145,   147,   125,     0,   111,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
       0,   207,     0,   204,   205,   248,     0,   245,   246,   283,
       0,   280,   281,   155,   156,     0,   151,   153,   154,     0,
     163,   161,     0,   159,   162,   390,     0,   172,     0,   169,
     170,     0,     0,     0,     0,     0,     0,     0,   187,   189,
     190,   191,   192,   193,   194,   416,   422,     0,     0,     0,
     415,   414,     0,   407,   409,   412,   410,   411,   413,   433,
     435,     0,   429,   431,   432,     0,    49,     0,   397,   309,
       0,   306,   307,   329,     0,   326,   327,   356,     0,   353,
     354,   386,     0,    64,     0,     0,   491,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   110,     0,   202,     0,   252,   243,     0,   287,   278,
       0,     0,   150,   165,     0,   158,     0,   389,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,   186,     0,
       0,     0,     0,     0,     0,   406,     0,     0,     0,   428,
     438,    51,     0,    50,   404,     0,   304,     0,     0,   324,
       0,   360,   351,     0,     0,   385,     0,   493,     0,     0,
       0,     0,   138,   141,   142,   143,   144,     0,     0,   112,
       0,   206,     0,   247,     0,   282,   152,   160,   391,     0,
     171,   195,   196,   197,   198,   199,   200,   188,     0,     0,
     421,   424,   425,   408,     0,     0,   430,    48,     0,     0,
     308,     0,   328,     0,   355,     0,     0,   128,   129,   130,
     131,   127,   133,   135,   137,   146,   148,   208,   249,   284,
     173,   418,   419,   420,   417,   423,   434,   436,    52,   310,
     330,   357,   387,   499,     0,   497,     0,     0,   496,   511,
       0,   509,   507,   503,     0,   501,   505,   506,   504,   498,
       0,     0,     0,     0,   500,     0,   508,     0,   502,     0,
     510,   515,     0,   513,     0,     0,   512,   519,     0,   517,
     514,     0,     0,   516,     0,   518,   520
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,     9,  -494,    99,  -494,  -494,  -494,
    -494,  -494,  -494,    22,  -494,  -171,  -494,  -494,  -494,   -62,
    -494,  -494,  -494,   232,  -494,  -494,  -494,  -494,    55,   231,
     -63,   -50,   -49,   -43,  -494,  -494,  -494,  -494,  -494,    56,
     230,  -494,  -494,  -494,  -494,  -494,  -494,  -494,    51,  -137,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
     -58,  -494,  -493,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -147,  -479,  -494,  -494,  -494,  -494,  -149,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -154,  -494,  -494,
    -494,  -151,   185,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -157,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -133,  -494,  -494,  -494,  -130,   226,  -494,  -494,  -494,
    -494,  -494,  -494,  -483,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -132,  -494,  -494,  -494,  -131,  -494,   201,
    -494,   -59,  -494,  -494,  -494,  -494,  -494,   -57,  -494,  -494,
    -494,  -494,  -494,   -48,  -494,  -494,  -494,  -134,  -494,  -494,
    -494,  -128,  -494,   217,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -166,  -494,  -494,  -494,  -161,   243,
    -494,  -494,   -66,  -494,  -494,  -494,  -494,  -494,  -164,  -494,
    -494,  -494,  -160,   244,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -155,  -494,  -494,  -494,  -162,
    -494,   246,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,    77,  -494,  -494,  -494,  -494,  -494,
    -494,  -142,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -124,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,    85,   219,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,   -80,  -494,  -494,  -494,  -231,
    -494,  -494,  -246,  -494,  -494,  -494,  -494,  -494,  -494,  -249,
    -494,  -494,  -255,  -494
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   526,    77,
      78,    37,    60,    74,    75,   511,   656,   732,   733,   112,
      39,    62,    85,    86,    87,   291,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   298,    43,    64,   138,
     139,   140,   321,   141,   121,   299,   122,   300,   576,   577,
     578,   678,   801,   579,   679,   580,   680,   581,   681,   582,
     221,   359,   584,   585,   586,   587,   588,   687,   589,   688,
     123,   309,   605,   606,   607,   608,   124,   311,   612,   613,
     614,   125,   310,   126,   313,   618,   619,   620,   708,    57,
      71,   251,   252,   253,   371,   254,   372,   127,   314,   627,
     628,   629,   630,   631,   632,   633,   634,   128,   306,   592,
     593,   594,   692,    45,    65,   159,   160,   161,   328,   162,
     329,   163,   330,   164,   334,   165,   333,   166,   167,   129,
     307,   596,   597,   598,   695,    53,    69,   222,   223,   224,
     225,   226,   227,   228,   358,   229,   362,   230,   361,   231,
     232,   363,   233,   130,   308,   600,   601,   602,   698,    55,
      70,   240,   241,   242,   243,   244,   367,   245,   246,   247,
     169,   326,   660,   661,   662,   735,    47,    66,   177,   178,
     179,   339,   180,   340,   170,   327,   664,   665,   666,   738,
      49,    67,   189,   190,   191,   343,   192,   193,   345,   194,
     195,   171,   335,   668,   669,   670,   741,    51,    68,   204,
     205,   206,   207,   351,   208,   352,   209,   353,   210,   354,
     211,   355,   212,   350,   172,   336,   672,   744,   131,   312,
     616,   325,   428,   429,   430,   431,   432,   512,   132,   315,
     642,   643,   644,   719,   814,   645,   646,   720,   647,   648,
     133,   134,   317,   651,   652,   653,   726,   654,   727,   135,
     318,    59,    72,   270,   271,   272,   273,   376,   274,   377,
     275,   276,   379,   277,   278,   279,   382,   548,   280,   383,
     281,   282,   283,   284,   387,   555,   285,   388,    88,   293,
      89,   294,    90,   292,   560,   561,   562,   674,   824,   825,
     826,   834,   835,   836,   837,   842,   838,   840,   852,   853,
     854,   858,   859,   861
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   188,   155,   154,   175,   186,   202,   220,   236,   250,
     269,   238,   237,   239,   641,   156,   157,   168,   176,   187,
     203,   615,   158,    34,   611,    27,   142,    28,    79,    29,
      38,   603,   701,   704,   296,   702,   705,   101,    91,   297,
     635,    92,    93,   319,   213,   142,    26,   173,   320,   569,
      94,    95,    96,    97,   174,   101,   214,   101,    94,    95,
      96,    97,    98,    99,   100,   101,   143,   214,   144,   215,
     216,    40,   217,   218,   219,   145,   146,   147,   148,   149,
     150,   706,   101,   424,   707,    76,   151,   152,   214,   102,
     103,   104,   105,   153,   181,   182,   183,   184,   185,   174,
     604,   827,   286,   106,   828,   151,   107,   214,   234,   215,
     216,   235,   287,   108,   636,   637,   638,   639,   248,   249,
     101,   109,   110,   564,   855,   111,    42,   856,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   574,    80,    83,
     811,   812,   813,   323,    81,    82,   214,   196,   324,   136,
     137,   197,   198,   199,   200,   201,    44,    83,    83,    83,
      30,    31,    32,    33,    83,   337,    46,    83,    83,   289,
     338,   829,    48,   830,   831,   621,   622,   623,   624,   625,
     626,    83,   248,   249,    83,   550,   551,   552,   553,    83,
      50,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   341,   348,    52,    83,   373,
     342,   349,   554,   389,   374,   319,   675,   290,   390,   323,
     673,   676,    83,   768,   677,   611,   546,   547,   689,    54,
     689,   641,    83,   690,    84,   691,   717,   724,   728,   389,
     337,   718,   725,   729,   730,   807,    56,    83,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
     373,   341,    58,   425,   348,   810,   819,   426,   843,   820,
     288,   862,   356,   844,   155,   154,   863,   427,   295,   175,
     603,   610,   188,   529,   530,   531,   186,   156,   157,   168,
     649,   650,   301,   176,   158,   202,   391,   392,   302,   303,
     187,   365,   304,   305,   220,   316,   322,   331,   236,   203,
     332,   238,   237,   239,   797,   798,   799,   800,   344,   346,
     347,   357,   393,   360,   364,   366,   370,   269,   368,   369,
     375,   378,   380,   381,   384,   385,   386,   394,   395,   396,
     397,   399,   400,   401,   407,   402,   403,   408,   404,   405,
     409,   410,   406,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   421,   422,   433,   434,   435,   436,   437,   438,
     440,   441,   439,   442,   443,   445,   446,   448,   450,   449,
     454,   451,   452,   455,   456,   457,   458,   459,   461,   462,
     463,   464,   465,   466,   467,   469,   470,   472,   473,   475,
     476,   477,   479,   478,   480,   493,   494,   482,   481,   483,
     487,   488,   484,   485,   486,   490,   491,   492,   514,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     517,   518,   506,   507,   575,   575,   508,   509,   583,   583,
     510,   513,   515,   516,   519,   640,   522,   269,   520,   521,
     523,   524,   425,    28,   591,   595,   426,   527,   599,   617,
     657,   659,   663,   559,   667,   528,   427,   682,   683,   684,
     685,   686,   694,   796,   549,   671,   693,   696,   697,   699,
     700,   532,   542,   711,   533,   534,   703,   709,   535,   710,
     736,   712,   713,   714,   715,   536,   716,   721,   722,   557,
     723,   737,   740,   739,   743,   537,   742,   746,   538,   748,
     745,   749,   750,   751,   757,   539,   758,   540,   541,   778,
     779,   784,   785,   788,   609,   787,   543,   795,   398,   808,
     544,   823,   545,   809,   821,   556,   841,   845,   847,   731,
     849,   734,   864,   752,   851,   525,   558,   753,   590,   754,
     420,   563,   759,   423,   766,   767,   770,   769,   474,   755,
     777,   761,   760,   444,   762,   763,   765,   468,   756,   771,
     764,   790,   772,   773,   789,   774,   792,   775,   791,   793,
     776,   780,   783,   781,   447,   782,   846,   471,   794,   802,
     803,   658,   453,   804,   655,   747,   839,   848,   805,   806,
     815,   816,   817,   460,   786,   857,   860,   865,   489,     0,
       0,     0,   818,     0,   822,     0,   850,     0,   866,     0,
       0,     0,     0,     0,     0,     0,     0,   575,     0,   155,
     154,   583,     0,   220,     0,     0,   236,     0,     0,   238,
     237,   239,   156,   157,   168,     0,   250,     0,     0,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   640,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   175,     0,     0,   186,     0,     0,   202,
       0,     0,     0,     0,     0,     0,     0,   176,     0,     0,
     187,     0,     0,   203,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   832,     0,     0,     0,   833,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   832,     0,     0,     0,   833
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   507,    65,    65,    65,    66,    67,
      68,   504,    65,    14,   503,     5,     7,     7,    10,     9,
       7,    71,     3,     3,     3,     6,     6,    38,    11,     8,
      16,    14,    15,     3,    16,     7,     0,    48,     8,    25,
      31,    32,    33,    34,    55,    38,    39,    38,    31,    32,
      33,    34,    35,    36,    37,    38,    47,    39,    49,    41,
      42,     7,    44,    45,    46,    56,    57,    58,    59,    60,
      61,     3,    38,    66,     6,   140,    67,    68,    39,    62,
      63,    64,    65,    74,    50,    51,    52,    53,    54,    55,
     140,     3,     6,    76,     6,    67,    79,    39,    40,    41,
      42,    43,     3,    86,    90,    91,    92,    93,    77,    78,
      38,    94,    95,    16,     3,    98,     7,     6,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,   120,   140,
      87,    88,    89,     3,   126,   127,    39,    65,     8,    12,
      13,    69,    70,    71,    72,    73,     7,   140,   140,   140,
     140,   141,   142,   143,   140,     3,     7,   140,   140,     8,
       8,   122,     7,   124,   125,    80,    81,    82,    83,    84,
      85,   140,    77,    78,   140,   116,   117,   118,   119,   140,
       7,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,     3,     3,     7,   140,     3,
       8,     8,   143,     3,     8,     3,     3,     3,     8,     3,
       8,     8,   140,   706,     8,   704,   113,   114,     3,     7,
       3,   724,   140,     8,   296,     8,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,     7,   140,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
       3,     3,     7,   325,     3,     8,     8,   325,     3,     8,
       4,     3,     8,     8,   337,   337,     8,   325,     4,   341,
      71,    72,   348,   454,   455,   456,   348,   337,   337,   337,
      96,    97,     4,   341,   337,   357,   287,   288,     4,     4,
     348,     8,     4,     4,   366,     4,     4,     4,   370,   357,
       4,   370,   370,   370,    17,    18,    19,    20,     4,     4,
       4,     3,   140,     4,     4,     3,     3,   389,     4,     8,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   141,   141,     4,   141,   141,
       4,     4,   141,     4,     4,     4,     4,     4,     4,   141,
       4,     4,     4,   143,     4,     4,     4,     4,     4,   141,
       4,     4,   143,     4,     4,     4,     4,     4,     4,   141,
       4,   141,   141,     4,     4,     4,     4,     4,     4,     4,
     141,     4,     4,     4,   143,     4,   143,     4,     4,   143,
       4,     4,     4,   141,   141,   396,   397,     4,   141,     4,
       4,     4,   143,   143,   143,     4,     7,     7,     3,     7,
       7,     7,     5,     5,     5,     5,     5,     5,     5,     5,
     140,   140,     7,     7,   496,   497,     7,     7,   496,   497,
       5,     8,     5,     5,   140,   507,     5,   509,   140,   140,
       7,   140,   514,     7,     7,     7,   514,   140,     7,     7,
       4,     7,     7,   121,     7,   140,   514,     4,     4,     4,
       4,     4,     3,     5,   115,    75,     6,     6,     3,     6,
       3,   140,   473,     4,   140,   140,     6,     6,   140,     3,
       6,     4,     4,     4,     4,   140,     4,     4,     4,   490,
       4,     3,     3,     6,     3,   140,     6,     4,   140,     4,
       8,     4,     4,     4,     4,   140,     4,   140,   140,     4,
       4,     4,     4,     3,   502,     6,   140,     4,   296,     8,
     140,     7,   140,     8,     8,   140,     4,     4,     4,   140,
       5,   140,     4,   141,     7,   446,   491,   143,   497,   141,
     319,   495,   689,   323,   701,   704,   710,   708,   373,   143,
     717,   694,   692,   337,   695,   697,   700,   366,   141,   141,
     698,   737,   141,   141,   735,   141,   740,   141,   738,   741,
     141,   141,   724,   141,   341,   141,   141,   370,   743,   140,
     140,   514,   348,   140,   509,   675,   827,   843,   140,   140,
     140,   140,   140,   357,   728,   123,   855,   862,   389,    -1,
      -1,    -1,   140,    -1,   140,    -1,   140,    -1,   140,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   689,    -1,   692,
     692,   689,    -1,   695,    -1,    -1,   698,    -1,    -1,   698,
     698,   698,   692,   692,   692,    -1,   708,    -1,    -1,   692,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   724,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   738,   735,    -1,    -1,   738,    -1,    -1,   741,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   735,    -1,    -1,
     738,    -1,    -1,   741,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   826,    -1,    -1,    -1,   826,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   843,    -1,    -1,    -1,   843
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,     5,     7,     9,
     140,   141,   142,   143,   158,   159,   160,   165,     7,   174,
       7,   180,     7,   191,     7,   267,     7,   330,     7,   344,
       7,   361,     7,   289,     7,   313,     7,   243,     7,   415,
     166,   161,   175,   181,   192,   268,   331,   345,   362,   290,
     314,   244,   416,   158,   167,   168,   140,   163,   164,    10,
     120,   126,   127,   140,   173,   176,   177,   178,   442,   444,
     446,    11,    14,    15,    31,    32,    33,    34,    35,    36,
      37,    38,    62,    63,    64,    65,    76,    79,    86,    94,
      95,    98,   173,   182,   183,   184,   185,   186,   187,   188,
     189,   198,   200,   224,   230,   235,   237,   251,   261,   283,
     307,   382,   392,   404,   405,   413,    12,    13,   193,   194,
     195,   197,     7,    47,    49,    56,    57,    58,    59,    60,
      61,    67,    68,    74,   173,   184,   185,   186,   187,   269,
     270,   271,   273,   275,   277,   279,   281,   282,   307,   324,
     338,   355,   378,    48,    55,   173,   307,   332,   333,   334,
     336,    50,    51,    52,    53,    54,   173,   307,   336,   346,
     347,   348,   350,   351,   353,   354,    65,    69,    70,    71,
      72,    73,   173,   307,   363,   364,   365,   366,   368,   370,
     372,   374,   376,    16,    39,    41,    42,    44,    45,    46,
     173,   214,   291,   292,   293,   294,   295,   296,   297,   299,
     301,   303,   304,   306,    40,    43,   173,   214,   295,   301,
     315,   316,   317,   318,   319,   321,   322,   323,    77,    78,
     173,   245,   246,   247,   249,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   173,
     417,   418,   419,   420,   422,   424,   425,   427,   428,   429,
     432,   434,   435,   436,   437,   440,     6,     3,     4,     8,
       3,   179,   447,   443,   445,     4,     3,     8,   190,   199,
     201,     4,     4,     4,     4,     4,   262,   284,   308,   225,
     236,   231,   383,   238,   252,   393,     4,   406,   414,     3,
       8,   196,     4,     3,     8,   385,   325,   339,   272,   274,
     276,     4,     4,   280,   278,   356,   379,     3,     8,   335,
     337,     3,     8,   349,     4,   352,     4,     4,     3,     8,
     377,   367,   369,   371,   373,   375,     8,     3,   298,   215,
       4,   302,   300,   305,     4,     8,     3,   320,     4,     8,
       3,   248,   250,     3,     8,     4,   421,   423,     4,   426,
       4,     4,   430,   433,     4,     4,     4,   438,   441,     3,
       8,   158,   158,   140,     4,     4,     4,     4,   177,     4,
       4,     4,   141,   141,   141,   141,   141,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   141,     4,     4,
     183,     4,   143,   194,    66,   173,   214,   307,   386,   387,
     388,   389,   390,     4,     4,     4,     4,     4,   141,   143,
       4,     4,     4,     4,   270,     4,     4,   333,     4,   141,
       4,   141,   141,   347,     4,     4,     4,     4,     4,     4,
     365,     4,     4,   141,     4,     4,     4,   143,   293,     4,
     143,   317,     4,     4,   246,   143,     4,     4,   141,     4,
     141,   141,     4,     4,   143,   143,   143,     4,     4,   418,
       4,     7,     7,   158,   158,     7,     7,     7,     5,     5,
       5,     5,     5,     5,     5,     5,     7,     7,     7,     7,
       5,   169,   391,     8,     3,     5,     5,   140,   140,   140,
     140,   140,     5,     7,   140,   160,   162,   140,   140,   169,
     169,   169,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   158,   140,   140,   140,   113,   114,   431,   115,
     116,   117,   118,   119,   143,   439,   140,   158,   182,   121,
     448,   449,   450,   193,    16,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   173,   202,   203,   204,   207,
     209,   211,   213,   214,   216,   217,   218,   219,   220,   222,
     202,     7,   263,   264,   265,     7,   285,   286,   287,     7,
     309,   310,   311,    71,   140,   226,   227,   228,   229,   167,
      72,   228,   232,   233,   234,   277,   384,     7,   239,   240,
     241,    80,    81,    82,    83,    84,    85,   253,   254,   255,
     256,   257,   258,   259,   260,    16,    90,    91,    92,    93,
     173,   216,   394,   395,   396,   399,   400,   402,   403,    96,
      97,   407,   408,   409,   411,   417,   170,     4,   388,     7,
     326,   327,   328,     7,   340,   341,   342,     7,   357,   358,
     359,    75,   380,     8,   451,     3,     8,     8,   205,   208,
     210,   212,     4,     4,     4,     4,     4,   221,   223,     3,
       8,     8,   266,     6,     3,   288,     6,     3,   312,     6,
       3,     3,     6,     6,     3,     6,     3,     6,   242,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   397,
     401,     4,     4,     4,     3,     8,   410,   412,     3,     8,
       8,   140,   171,   172,   140,   329,     6,     3,   343,     6,
       3,   360,     6,     3,   381,     8,     4,   449,     4,     4,
       4,     4,   141,   143,   141,   143,   141,     4,     4,   203,
     269,   265,   291,   287,   315,   311,   227,   233,   277,   245,
     241,   141,   141,   141,   141,   141,   141,   254,     4,     4,
     141,   141,   141,   395,     4,     4,   408,     6,     3,   332,
     328,   346,   342,   363,   359,     4,     5,    17,    18,    19,
      20,   206,   140,   140,   140,   140,   140,     8,     8,     8,
       8,    87,    88,    89,   398,   140,   140,   140,   140,     8,
       8,     8,   140,     7,   452,   453,   454,     3,     6,   122,
     124,   125,   173,   214,   455,   456,   457,   458,   460,   453,
     461,     4,   459,     3,     8,     4,   141,     4,   456,     5,
     140,     7,   462,   463,   464,     3,     6,   123,   465,   466,
     463,   467,     3,     8,     4,   466,   140
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
     193,   193,   194,   194,   196,   195,   197,   199,   198,   201,
     200,   202,   202,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   205,   204,   206,   206,
     206,   206,   208,   207,   210,   209,   212,   211,   213,   215,
     214,   216,   217,   218,   219,   221,   220,   223,   222,   225,
     224,   226,   226,   227,   227,   228,   229,   231,   230,   232,
     232,   233,   233,   234,   236,   235,   238,   237,   239,   239,
     240,   240,   242,   241,   244,   243,   245,   245,   245,   246,
     246,   248,   247,   250,   249,   252,   251,   253,   253,   254,
     254,   254,   254,   254,   254,   255,   256,   257,   258,   259,
     260,   262,   261,   263,   263,   264,   264,   266,   265,   268,
     267,   269,   269,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     272,   271,   274,   273,   276,   275,   278,   277,   280,   279,
     281,   282,   284,   283,   285,   285,   286,   286,   288,   287,
     290,   289,   291,   291,   292,   292,   293,   293,   293,   293,
     293,   293,   293,   293,   294,   295,   296,   298,   297,   300,
     299,   302,   301,   303,   305,   304,   306,   308,   307,   309,
     309,   310,   310,   312,   311,   314,   313,   315,   315,   316,
     316,   317,   317,   317,   317,   317,   317,   318,   320,   319,
     321,   322,   323,   325,   324,   326,   326,   327,   327,   329,
     328,   331,   330,   332,   332,   333,   333,   333,   333,   335,
     334,   337,   336,   339,   338,   340,   340,   341,   341,   343,
     342,   345,   344,   346,   346,   347,   347,   347,   347,   347,
     347,   347,   347,   349,   348,   350,   352,   351,   353,   354,
     356,   355,   357,   357,   358,   358,   360,   359,   362,   361,
     363,   363,   364,   364,   365,   365,   365,   365,   365,   365,
     365,   365,   367,   366,   369,   368,   371,   370,   373,   372,
     375,   374,   377,   376,   379,   378,   381,   380,   383,   382,
     384,   384,   385,   277,   386,   386,   387,   387,   388,   388,
     388,   388,   389,   391,   390,   393,   392,   394,   394,   395,
     395,   395,   395,   395,   395,   395,   397,   396,   398,   398,
     398,   399,   401,   400,   402,   403,   404,   406,   405,   407,
     407,   408,   408,   410,   409,   412,   411,   414,   413,   416,
     415,   417,   417,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   419,   421,
     420,   423,   422,   424,   426,   425,   427,   428,   430,   429,
     431,   431,   433,   432,   434,   435,   436,   438,   437,   439,
     439,   439,   439,   439,   441,   440,   443,   442,   445,   444,
     447,   446,   448,   448,   449,   451,   450,   452,   452,   454,
     453,   455,   455,   456,   456,   456,   456,   456,   457,   459,
     458,   461,   460,   462,   462,   464,   463,   465,   465,   467,
     466
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
       1,     3,     1,     1,     0,     4,     3,     0,     6,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     0,     4,     0,     4,     0,
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
       4,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     0,
       4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
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
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6",
  "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "value", "sub_json", "map2", "$@13", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@14", "list_content",
  "not_empty_list", "list_strings", "$@15", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@16",
  "global_objects", "global_object", "dhcp6_object", "$@17", "sub_dhcp6",
  "$@18", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@19",
  "sub_interfaces6", "$@20", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@21", "re_detect",
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
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@96", "replace_client_name_value",
  "generated_prefix", "$@97", "dhcp4_json_object", "$@98",
  "dhcpddns_json_object", "$@99", "logging_object", "$@100",
  "logging_params", "logging_param", "loggers", "$@101", "loggers_entries",
  "logger_entry", "$@102", "logger_params", "logger_param", "debuglevel",
  "severity", "$@103", "output_options_list", "$@104",
  "output_options_list_content", "output_entry", "$@105", "output_params",
  "output_param", "$@106", YY_NULLPTR
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
     466,   467,   470,   471,   474,   474,   484,   490,   490,   500,
     500,   510,   511,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   529,   529,   536,   537,
     538,   539,   542,   542,   550,   550,   558,   558,   566,   571,
     571,   579,   584,   589,   594,   599,   599,   607,   607,   616,
     616,   626,   627,   630,   631,   634,   639,   644,   644,   654,
     655,   658,   659,   662,   669,   669,   679,   679,   689,   690,
     693,   694,   697,   697,   705,   705,   713,   714,   715,   718,
     719,   722,   722,   730,   730,   738,   738,   748,   749,   752,
     753,   754,   755,   756,   757,   760,   765,   770,   775,   780,
     785,   793,   793,   806,   807,   810,   811,   818,   818,   841,
     841,   850,   851,   855,   856,   857,   858,   859,   860,   861,
     862,   863,   864,   865,   866,   867,   868,   869,   870,   871,
     874,   874,   882,   882,   890,   890,   898,   898,   906,   906,
     914,   919,   928,   928,   940,   941,   944,   945,   950,   950,
     961,   961,   971,   972,   975,   976,   979,   980,   981,   982,
     983,   984,   985,   986,   989,   991,   996,   998,   998,  1006,
    1006,  1014,  1014,  1022,  1024,  1024,  1032,  1041,  1041,  1053,
    1054,  1059,  1060,  1065,  1065,  1076,  1076,  1087,  1088,  1093,
    1094,  1099,  1100,  1101,  1102,  1103,  1104,  1107,  1109,  1109,
    1117,  1119,  1121,  1129,  1129,  1141,  1142,  1145,  1146,  1149,
    1149,  1157,  1157,  1165,  1166,  1169,  1170,  1171,  1172,  1175,
    1175,  1183,  1183,  1193,  1193,  1205,  1206,  1209,  1210,  1213,
    1213,  1221,  1221,  1229,  1230,  1233,  1234,  1235,  1236,  1237,
    1238,  1239,  1240,  1243,  1243,  1251,  1256,  1256,  1264,  1269,
    1277,  1277,  1287,  1288,  1291,  1292,  1295,  1295,  1303,  1303,
    1311,  1312,  1315,  1316,  1320,  1321,  1322,  1323,  1324,  1325,
    1326,  1327,  1330,  1330,  1340,  1340,  1350,  1350,  1358,  1358,
    1366,  1366,  1374,  1374,  1387,  1387,  1397,  1397,  1408,  1408,
    1418,  1419,  1422,  1422,  1430,  1431,  1434,  1435,  1438,  1439,
    1440,  1441,  1444,  1446,  1446,  1457,  1457,  1467,  1468,  1471,
    1472,  1473,  1474,  1475,  1476,  1477,  1480,  1480,  1487,  1488,
    1489,  1492,  1497,  1497,  1505,  1510,  1517,  1524,  1524,  1534,
    1535,  1538,  1539,  1542,  1542,  1550,  1550,  1560,  1560,  1570,
    1570,  1578,  1579,  1582,  1583,  1584,  1585,  1586,  1587,  1588,
    1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1599,  1604,
    1604,  1612,  1612,  1620,  1625,  1625,  1633,  1638,  1643,  1643,
    1651,  1652,  1655,  1655,  1663,  1668,  1673,  1678,  1678,  1686,
    1689,  1692,  1695,  1698,  1704,  1704,  1714,  1714,  1721,  1721,
    1733,  1733,  1746,  1747,  1751,  1755,  1755,  1767,  1768,  1772,
    1772,  1780,  1781,  1784,  1785,  1786,  1787,  1788,  1791,  1796,
    1796,  1804,  1804,  1814,  1815,  1818,  1818,  1826,  1827,  1830,
    1830
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
#line 4193 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1838 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
