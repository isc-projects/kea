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
      case 203: // db_type
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

      case 203: // db_type

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
      case 203: // db_type
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

  case 159:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 814 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 206:
#line 833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1727 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1103 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1153 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1490 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2623 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2631 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2751 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2927 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3028 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3076 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3094 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3098 "dhcp6_parser.cc" // lalr1.cc:859
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
     183,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,    31,    20,    40,    63,    76,    95,   111,
     142,   143,   150,   158,   185,   214,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
      20,    91,    18,    27,   231,    19,    -1,    45,    83,    28,
     132,   -33,    96,  -490,   256,   262,   263,   260,   266,  -490,
    -490,  -490,  -490,   270,  -490,    29,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   272,   273,   275,   276,   277,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   282,
    -490,  -490,  -490,   101,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   279,  -490,  -490,
    -490,  -490,  -490,  -490,   284,   287,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   102,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   116,  -490,  -490,  -490,  -490,   289,  -490,
     293,   294,  -490,  -490,  -490,   140,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   291,   297,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   298,  -490,  -490,  -490,   299,  -490,  -490,
     296,   304,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   319,  -490,  -490,  -490,  -490,   317,   323,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   172,
    -490,  -490,  -490,   324,  -490,  -490,   325,  -490,   326,   327,
    -490,  -490,   328,   329,   330,  -490,  -490,  -490,   174,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,    20,    20,  -490,   126,   331,
     332,   333,   334,  -490,    18,  -490,   335,   336,   337,   186,
     201,   202,   203,   204,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   215,   353,   354,    27,  -490,   355,
    -490,    43,   356,   357,   358,   359,   360,   224,   223,   363,
     364,   365,   366,    19,  -490,   367,   368,    -1,  -490,   369,
     233,   371,   235,   239,    45,  -490,   373,   374,   375,   377,
     378,   379,   380,  -490,    83,   381,   382,   249,   383,   384,
     385,   251,  -490,    28,   387,   252,  -490,   132,   388,   389,
     -23,  -490,   253,   393,   394,   259,   395,   264,   265,   397,
     400,   267,   268,   269,   403,   404,    96,  -490,  -490,  -490,
     405,   406,   407,    20,    20,  -490,   408,   409,   410,  -490,
    -490,  -490,  -490,  -490,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,  -490,   425,   426,  -490,   431,  -490,
    -490,  -490,  -490,   429,   423,  -490,  -490,  -490,   433,   434,
     300,   302,   305,  -490,  -490,   306,   307,   439,   442,  -490,
     310,   444,  -490,   313,  -490,   314,  -490,  -490,  -490,   431,
     431,   431,   315,   316,   318,   320,  -490,   321,   339,  -490,
     340,   341,   352,  -490,  -490,   361,  -490,  -490,   362,    20,
    -490,  -490,   370,   372,  -490,   376,  -490,  -490,    -2,   312,
    -490,  -490,  -490,    70,   386,  -490,    20,    27,   338,  -490,
    -490,   231,   108,   108,   450,   456,   457,   -40,    20,   120,
      35,   458,   134,    24,    30,    96,  -490,  -490,   462,  -490,
      43,   460,   461,  -490,  -490,  -490,  -490,  -490,   463,   396,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   217,  -490,   219,  -490,  -490,
     464,  -490,  -490,  -490,  -490,   465,   469,   470,   471,   472,
    -490,  -490,  -490,   221,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   227,  -490,   476,
     474,  -490,  -490,   477,   481,  -490,  -490,   479,   483,  -490,
    -490,  -490,    81,  -490,  -490,  -490,   482,  -490,  -490,  -490,
     163,  -490,  -490,  -490,  -490,   178,  -490,   484,   486,  -490,
     487,   489,   490,   492,   493,   494,   230,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,   495,   496,   499,  -490,
    -490,   234,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     236,  -490,  -490,  -490,   237,   390,   391,  -490,  -490,   498,
     502,  -490,  -490,   500,   504,  -490,  -490,   503,   505,  -490,
    -490,   506,  -490,   507,   338,  -490,  -490,   509,   511,   513,
     514,   392,   398,   399,   401,   402,   515,   516,   108,  -490,
    -490,    19,  -490,   450,    28,  -490,   456,   132,  -490,   457,
     -40,  -490,  -490,   120,  -490,    35,  -490,   -33,  -490,   458,
     411,   412,   424,   427,   428,   430,   134,  -490,   517,   518,
     432,   435,   436,    24,  -490,   519,   520,    30,  -490,  -490,
    -490,   521,   522,  -490,    -1,  -490,   460,    45,  -490,   461,
      83,  -490,   463,   524,  -490,   527,  -490,   193,   438,   440,
     441,  -490,  -490,  -490,  -490,  -490,   443,   445,  -490,   238,
    -490,   526,  -490,   528,  -490,  -490,  -490,  -490,   244,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   -54,   446,  -490,
    -490,  -490,  -490,   447,   448,  -490,  -490,   449,   246,  -490,
     247,  -490,   529,  -490,   451,   480,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   254,  -490,    54,   480,  -490,  -490,   525,
    -490,  -490,  -490,   248,  -490,  -490,  -490,  -490,  -490,   531,
     452,   534,    54,  -490,   537,  -490,   454,  -490,   532,  -490,
    -490,   258,  -490,   437,   532,  -490,  -490,   250,  -490,  -490,
     541,   437,  -490,   455,  -490,  -490
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   206,    11,   308,    13,   328,    15,
     355,    17,   247,    19,   282,    21,   171,    23,   439,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   357,   249,
     284,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     490,   486,   488,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   102,   104,     0,     0,     0,     0,     0,   198,
     239,   274,   144,   161,   152,   388,   163,   182,   405,     0,
     427,   437,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   100,     0,   392,   300,
     320,   227,   229,   231,     0,     0,   235,   233,   347,   384,
     226,   210,   211,   212,   213,     0,   208,   217,   218,   219,
     222,   224,   220,   221,   214,   215,   216,   223,   225,   316,
     318,   315,   313,     0,   310,   312,   314,   340,     0,   343,
       0,     0,   339,   335,   338,     0,   330,   332,   333,   336,
     337,   334,   382,   370,   372,   374,   376,   378,   380,   369,
     368,     0,   358,   359,   363,   364,   361,   365,   366,   367,
     362,   264,   134,     0,   268,   266,   271,     0,   260,   261,
       0,   250,   251,   253,   263,   254,   255,   256,   270,   257,
     258,   259,   295,     0,   293,   294,   297,   298,     0,   285,
     286,   288,   289,   290,   291,   292,   178,   180,   175,     0,
     173,   176,   177,     0,   459,   461,     0,   464,     0,     0,
     468,   472,     0,     0,     0,   477,   484,   457,     0,   441,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,    42,     0,     0,    35,     0,     0,
       0,     0,     0,    53,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      99,   394,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   207,     0,     0,     0,   309,     0,
       0,     0,     0,     0,     0,   329,     0,     0,     0,     0,
       0,     0,     0,   356,     0,     0,     0,     0,     0,     0,
       0,     0,   248,     0,     0,     0,   283,     0,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   440,    46,    39,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    91,
      92,    93,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   426,     0,     0,    68,     0,   403,
     401,   402,   400,     0,   395,   396,   398,   399,     0,     0,
       0,     0,     0,   237,   238,     0,     0,     0,     0,   209,
       0,     0,   311,     0,   342,     0,   345,   346,   331,     0,
       0,     0,     0,     0,     0,     0,   360,     0,     0,   262,
       0,     0,     0,   273,   252,     0,   299,   287,     0,     0,
     174,   458,     0,     0,   463,     0,   466,   467,     0,     0,
     474,   475,   476,     0,     0,   442,     0,     0,     0,   487,
     489,     0,     0,     0,   200,   241,   276,     0,    43,     0,
       0,   165,     0,     0,     0,     0,    47,   101,     0,   393,
       0,   302,   322,   228,   230,   232,   236,   234,   349,     0,
     317,    36,   319,   341,   344,   383,   371,   373,   375,   377,
     379,   381,   265,   135,   269,   267,   272,   296,   179,   181,
     460,   462,   465,   470,   471,   469,   473,   479,   480,   481,
     482,   483,   478,   485,    40,     0,   495,     0,   492,   494,
       0,   121,   127,   129,   131,     0,     0,     0,     0,     0,
     140,   142,   120,     0,   106,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,     0,   204,     0,
     201,   202,   245,     0,   242,   243,   280,     0,   277,   278,
     150,   151,     0,   146,   148,   149,     0,   159,   160,   156,
       0,   154,   157,   158,   390,     0,   169,     0,   166,   167,
       0,     0,     0,     0,     0,     0,     0,   184,   186,   187,
     188,   189,   190,   191,   416,   422,     0,     0,     0,   415,
     414,     0,   407,   409,   412,   410,   411,   413,   433,   435,
       0,   429,   431,   432,     0,    49,     0,   397,   306,     0,
     303,   304,   326,     0,   323,   324,   353,     0,   350,   351,
     386,     0,    64,     0,     0,   491,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     105,     0,   199,     0,   249,   240,     0,   284,   275,     0,
       0,   145,   162,     0,   153,     0,   389,     0,   164,     0,
       0,     0,     0,     0,     0,     0,     0,   183,     0,     0,
       0,     0,     0,     0,   406,     0,     0,     0,   428,   438,
      51,     0,    50,   404,     0,   301,     0,     0,   321,     0,
     357,   348,     0,     0,   385,     0,   493,     0,     0,     0,
       0,   133,   136,   137,   138,   139,     0,     0,   107,     0,
     203,     0,   244,     0,   279,   147,   155,   391,     0,   168,
     192,   193,   194,   195,   196,   197,   185,     0,     0,   421,
     424,   425,   408,     0,     0,   430,    48,     0,     0,   305,
       0,   325,     0,   352,     0,     0,   123,   124,   125,   126,
     122,   128,   130,   132,   141,   143,   205,   246,   281,   170,
     418,   419,   420,   417,   423,   434,   436,    52,   307,   327,
     354,   387,   499,     0,   497,     0,     0,   496,   511,     0,
     509,   507,   503,     0,   501,   505,   506,   504,   498,     0,
       0,     0,     0,   500,     0,   508,     0,   502,     0,   510,
     515,     0,   513,     0,     0,   512,   519,     0,   517,   514,
       0,     0,   516,     0,   518,   520
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,     9,  -490,   105,  -490,  -490,  -490,
    -490,  -490,  -490,    49,  -490,  -309,  -490,  -490,  -490,   -62,
    -490,  -490,  -490,   255,  -490,  -490,  -490,  -490,    61,   240,
     -63,   -50,   -49,   -43,  -490,  -490,  -490,  -490,  -490,    59,
    -490,  -490,  -490,  -490,  -490,    58,  -134,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   -58,  -490,  -489,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -145,  -475,  -490,  -490,  -490,  -490,  -147,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -151,  -490,  -490,  -490,  -148,
     191,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -154,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -130,
    -490,  -490,  -490,  -127,   241,  -490,  -490,  -490,  -490,  -490,
    -490,  -479,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -129,  -490,  -490,  -490,  -128,  -490,   207,  -490,   -59,
    -490,  -490,  -490,  -490,  -490,   -57,  -490,  -490,  -490,  -490,
    -490,   -48,  -490,  -490,  -490,  -124,  -490,  -490,  -490,  -125,
    -490,   212,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -152,  -490,  -490,  -490,  -144,   245,  -490,  -490,
     -66,  -490,  -490,  -490,  -490,  -490,  -143,  -490,  -490,  -490,
    -140,   257,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -150,  -490,  -490,  -490,  -142,  -490,   261,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,    89,  -490,  -490,  -490,  -490,  -490,
    -490,  -123,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -122,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,    97,   218,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   -71,  -490,  -490,  -490,  -220,
    -490,  -490,  -235,  -490,  -490,  -490,  -490,  -490,  -490,  -246,
    -490,  -490,  -252,  -490
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   522,    77,
      78,    37,    60,    74,    75,   507,   655,   731,   732,   112,
      39,    62,    85,    86,    87,   289,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   296,    43,    64,   137,
     319,   121,   297,   122,   298,   573,   574,   575,   677,   800,
     576,   678,   577,   679,   578,   680,   579,   219,   356,   581,
     582,   583,   584,   585,   686,   586,   687,   123,   307,   602,
     603,   604,   605,   124,   309,   610,   611,   612,   613,   125,
     308,   126,   311,   617,   618,   619,   707,    57,    71,   249,
     250,   251,   368,   252,   369,   127,   312,   626,   627,   628,
     629,   630,   631,   632,   633,   128,   304,   589,   590,   591,
     691,    45,    65,   155,   156,   157,   324,   158,   325,   159,
     326,   160,   330,   161,   329,   162,   163,   129,   305,   593,
     594,   595,   694,    53,    69,   220,   221,   222,   223,   224,
     225,   226,   355,   227,   359,   228,   358,   229,   230,   360,
     231,   130,   306,   597,   598,   599,   697,    55,    70,   238,
     239,   240,   241,   242,   364,   243,   244,   245,   165,   322,
     659,   660,   661,   734,    47,    66,   173,   174,   175,   335,
     176,   336,   166,   323,   663,   664,   665,   737,    49,    67,
     185,   186,   187,   339,   188,   189,   341,   190,   191,   167,
     331,   667,   668,   669,   740,    51,    68,   201,   202,   203,
     204,   347,   205,   348,   206,   349,   207,   350,   208,   351,
     209,   352,   210,   346,   168,   332,   671,   743,   131,   310,
     615,   321,   423,   424,   425,   426,   427,   508,   132,   313,
     641,   642,   643,   718,   813,   644,   645,   719,   646,   647,
     133,   134,   315,   650,   651,   652,   725,   653,   726,   135,
     316,    59,    72,   268,   269,   270,   271,   373,   272,   374,
     273,   274,   376,   275,   276,   277,   379,   545,   278,   380,
     279,   280,   281,   282,   384,   552,   283,   385,    88,   291,
      89,   292,    90,   290,   557,   558,   559,   673,   823,   824,
     825,   833,   834,   835,   836,   841,   837,   839,   851,   852,
     853,   857,   858,   860
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   184,   151,   150,   171,   182,   199,   218,   234,   248,
     267,   236,   235,   237,   640,   152,   153,   164,   172,   183,
     200,   614,   154,    34,   609,    27,   138,    28,    79,    29,
     600,    26,   294,   810,   811,   812,   101,   295,    91,   634,
      92,    93,   138,   211,   246,   247,   169,    38,   566,    94,
      95,    96,    97,   170,   246,   247,   101,    94,    95,    96,
      97,    98,    99,   100,   101,   139,   212,   140,   213,   214,
      40,   215,   216,   217,   141,   142,   143,   144,   145,   146,
     101,   212,   101,    42,   700,   147,   148,   701,   102,   103,
     104,   105,   212,   149,   177,   178,   179,   180,   181,   170,
     601,   147,    44,   106,   317,   333,   107,    83,   419,   318,
     334,   543,   544,   108,   635,   636,   637,   638,    46,   337,
     101,   109,   110,   561,   338,   111,   648,   649,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,    80,    83,
     525,   526,   527,   344,    81,    82,   212,   192,   345,    48,
      50,   193,   194,   195,   196,   197,   198,    52,    83,    83,
      30,    31,    32,    33,    83,    54,   703,    83,    83,   704,
     212,   232,   213,   214,   233,   370,   828,   386,   829,   830,
     371,   705,   387,    83,   706,    83,   547,   548,   549,   550,
     600,   607,    56,   608,    83,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   796,
     797,   798,   799,   551,   620,   621,   622,   623,   624,   625,
     317,    58,   674,    83,   688,   672,   767,   675,   609,   689,
     688,    76,    84,   716,   640,   690,    83,   723,   717,   727,
     386,   333,   724,   136,   728,   729,   806,   370,    83,   337,
     344,   842,   809,   861,   818,   819,   843,   826,   862,   420,
     827,   854,   284,   421,   855,   285,   390,   286,   287,   288,
     151,   150,    83,   422,   293,   171,   299,   300,   184,   301,
     302,   303,   182,   152,   153,   164,   314,   320,   327,   172,
     154,   328,   199,   340,   388,   389,   183,   342,   343,   353,
     354,   218,   357,   361,   362,   234,   200,   363,   236,   235,
     237,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   365,   267,   366,   367,   399,   372,   375,
     377,   378,   381,   382,   383,   391,   392,   393,   394,   396,
     397,   398,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   418,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   440,   441,   443,   444,   445,   446,   449,   450,   451,
     447,   452,   453,   454,   455,   457,   458,   460,   461,   462,
     459,   465,   468,   469,   463,   466,   471,   472,   473,   475,
     474,   478,   489,   490,   479,   476,   477,   483,   484,   486,
     480,   481,   482,   487,   488,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   510,   546,   502,   503,
     572,   572,   504,   505,   580,   580,   506,   509,   511,   512,
     513,   639,   514,   267,   518,   515,   516,   517,   420,   519,
     520,    28,   421,   523,   524,   528,   529,   588,   530,   556,
     531,   532,   422,   592,   596,   616,   656,   658,   662,   681,
     666,   670,   676,   682,   683,   684,   685,   693,   539,   533,
     534,   535,   692,   695,   696,   698,   699,   822,   702,   709,
     708,   710,   536,   711,   712,   554,   713,   714,   715,   720,
     721,   537,   538,   722,   735,   736,   738,   739,   742,   741,
     540,   745,   541,   747,   744,   748,   542,   749,   750,   756,
     757,   777,   778,   783,   784,   787,   553,   786,   794,   840,
     730,   733,   795,   751,   807,   844,   808,   820,   846,   850,
     753,   752,   848,   755,   754,   863,   521,   606,   555,   395,
     560,   587,   770,   771,   758,   765,   766,   417,   769,   768,
     856,   470,   776,   760,   759,   772,   761,   762,   773,   774,
     464,   775,   763,   779,   439,   764,   780,   781,   801,   467,
     802,   803,   442,   804,   789,   805,   814,   815,   816,   817,
     788,   821,   793,   845,   849,   865,   791,   790,   792,   657,
     782,   448,   654,   746,   485,   785,   838,   847,   859,   864,
       0,     0,     0,     0,     0,   456,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   572,     0,   151,   150,
     580,     0,   218,     0,     0,   234,     0,     0,   236,   235,
     237,   152,   153,   164,     0,   248,     0,     0,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   639,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   184,   171,     0,     0,   182,     0,     0,   199,     0,
       0,     0,     0,     0,     0,     0,   172,     0,     0,   183,
       0,     0,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   831,     0,     0,     0,   832,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     831,     0,     0,     0,   832
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   503,    65,    65,    65,    66,    67,
      68,   500,    65,    14,   499,     5,     7,     7,    10,     9,
      70,     0,     3,    87,    88,    89,    37,     8,    11,    15,
      13,    14,     7,    15,    77,    78,    47,     7,    24,    30,
      31,    32,    33,    54,    77,    78,    37,    30,    31,    32,
      33,    34,    35,    36,    37,    46,    38,    48,    40,    41,
       7,    43,    44,    45,    55,    56,    57,    58,    59,    60,
      37,    38,    37,     7,     3,    66,    67,     6,    61,    62,
      63,    64,    38,    74,    49,    50,    51,    52,    53,    54,
     140,    66,     7,    76,     3,     3,    79,   140,    65,     8,
       8,   113,   114,    86,    90,    91,    92,    93,     7,     3,
      37,    94,    95,    15,     8,    98,    96,    97,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,   120,   140,
     449,   450,   451,     3,   126,   127,    38,    64,     8,     7,
       7,    68,    69,    70,    71,    72,    73,     7,   140,   140,
     140,   141,   142,   143,   140,     7,     3,   140,   140,     6,
      38,    39,    40,    41,    42,     3,   122,     3,   124,   125,
       8,     3,     8,   140,     6,   140,   116,   117,   118,   119,
      70,    71,     7,    73,   140,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,    16,
      17,    18,    19,   143,    80,    81,    82,    83,    84,    85,
       3,     7,     3,   140,     3,     8,   705,     8,   703,     8,
       3,   140,   294,     3,   723,     8,   140,     3,     8,     3,
       3,     3,     8,    12,     8,     8,     8,     3,   140,     3,
       3,     3,     8,     3,     8,     8,     8,     3,     8,   321,
       6,     3,     6,   321,     6,     3,   140,     4,     8,     3,
     333,   333,   140,   321,     4,   337,     4,     4,   344,     4,
       4,     4,   344,   333,   333,   333,     4,     8,     4,   337,
     333,     4,   354,     4,   285,   286,   344,     4,     4,     8,
       3,   363,     4,     4,     8,   367,   354,     3,   367,   367,
     367,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,     4,   386,     8,     3,   141,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   141,   141,   141,   141,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   141,     4,     4,     4,
       4,     4,     4,     4,     4,   141,   143,     4,     4,     4,
       4,     4,     4,     4,   141,     4,   141,     4,     4,     4,
     141,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     141,     4,     4,     4,   143,   143,   143,     4,     4,     4,
     141,     4,   393,   394,     4,   141,   141,     4,     4,     4,
     143,   143,   143,     7,     7,     7,     7,     7,     5,     5,
       5,     5,     5,     5,     5,     5,     3,   115,     7,     7,
     492,   493,     7,     7,   492,   493,     5,     8,     5,     5,
     140,   503,   140,   505,     5,   140,   140,   140,   510,     7,
     140,     7,   510,   140,   140,   140,   140,     7,   140,   121,
     140,   140,   510,     7,     7,     7,     4,     7,     7,     4,
       7,    75,     8,     4,     4,     4,     4,     3,   469,   140,
     140,   140,     6,     6,     3,     6,     3,     7,     6,     3,
       6,     4,   140,     4,     4,   486,     4,     4,     4,     4,
       4,   140,   140,     4,     6,     3,     6,     3,     3,     6,
     140,     4,   140,     4,     8,     4,   140,     4,     4,     4,
       4,     4,     4,     4,     4,     3,   140,     6,     4,     4,
     140,   140,     5,   141,     8,     4,     8,     8,     4,     7,
     141,   143,     5,   141,   143,     4,   441,   498,   487,   294,
     491,   493,   141,   141,   688,   700,   703,   317,   709,   707,
     123,   370,   716,   693,   691,   141,   694,   696,   141,   141,
     363,   141,   697,   141,   333,   699,   141,   141,   140,   367,
     140,   140,   337,   140,   736,   140,   140,   140,   140,   140,
     734,   140,   742,   141,   140,   140,   739,   737,   740,   510,
     723,   344,   505,   674,   386,   727,   826,   842,   854,   861,
      -1,    -1,    -1,    -1,    -1,   354,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   688,    -1,   691,   691,
     688,    -1,   694,    -1,    -1,   697,    -1,    -1,   697,   697,
     697,   691,   691,   691,    -1,   707,    -1,    -1,   691,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   723,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   737,   734,    -1,    -1,   737,    -1,    -1,   740,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   734,    -1,    -1,   737,
      -1,    -1,   740,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   825,    -1,    -1,    -1,   825,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     842,    -1,    -1,    -1,   842
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,     5,     7,     9,
     140,   141,   142,   143,   158,   159,   160,   165,     7,   174,
       7,   180,     7,   191,     7,   265,     7,   328,     7,   342,
       7,   359,     7,   287,     7,   311,     7,   241,     7,   415,
     166,   161,   175,   181,   192,   266,   329,   343,   360,   288,
     312,   242,   416,   158,   167,   168,   140,   163,   164,    10,
     120,   126,   127,   140,   173,   176,   177,   178,   442,   444,
     446,    11,    13,    14,    30,    31,    32,    33,    34,    35,
      36,    37,    61,    62,    63,    64,    76,    79,    86,    94,
      95,    98,   173,   182,   183,   184,   185,   186,   187,   188,
     189,   195,   197,   221,   227,   233,   235,   249,   259,   281,
     305,   382,   392,   404,   405,   413,    12,   193,     7,    46,
      48,    55,    56,    57,    58,    59,    60,    66,    67,    74,
     173,   184,   185,   186,   187,   267,   268,   269,   271,   273,
     275,   277,   279,   280,   305,   322,   336,   353,   378,    47,
      54,   173,   305,   330,   331,   332,   334,    49,    50,    51,
      52,    53,   173,   305,   334,   344,   345,   346,   348,   349,
     351,   352,    64,    68,    69,    70,    71,    72,    73,   173,
     305,   361,   362,   363,   364,   366,   368,   370,   372,   374,
     376,    15,    38,    40,    41,    43,    44,    45,   173,   211,
     289,   290,   291,   292,   293,   294,   295,   297,   299,   301,
     302,   304,    39,    42,   173,   211,   293,   299,   313,   314,
     315,   316,   317,   319,   320,   321,    77,    78,   173,   243,
     244,   245,   247,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   173,   417,   418,
     419,   420,   422,   424,   425,   427,   428,   429,   432,   434,
     435,   436,   437,   440,     6,     3,     4,     8,     3,   179,
     447,   443,   445,     4,     3,     8,   190,   196,   198,     4,
       4,     4,     4,     4,   260,   282,   306,   222,   234,   228,
     383,   236,   250,   393,     4,   406,   414,     3,     8,   194,
       8,   385,   323,   337,   270,   272,   274,     4,     4,   278,
     276,   354,   379,     3,     8,   333,   335,     3,     8,   347,
       4,   350,     4,     4,     3,     8,   377,   365,   367,   369,
     371,   373,   375,     8,     3,   296,   212,     4,   300,   298,
     303,     4,     8,     3,   318,     4,     8,     3,   246,   248,
       3,     8,     4,   421,   423,     4,   426,     4,     4,   430,
     433,     4,     4,     4,   438,   441,     3,     8,   158,   158,
     140,     4,     4,     4,     4,   177,     4,     4,     4,   141,
     141,   141,   141,   141,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   141,     4,     4,   183,     4,    65,
     173,   211,   305,   386,   387,   388,   389,   390,     4,     4,
       4,     4,     4,   141,   143,     4,     4,     4,     4,   268,
       4,     4,   331,     4,   141,     4,   141,   141,   345,     4,
       4,     4,     4,     4,     4,     4,   363,     4,     4,   141,
       4,     4,     4,   143,   291,     4,   143,   315,     4,     4,
     244,   143,     4,     4,   141,     4,   141,   141,     4,     4,
     143,   143,   143,     4,     4,   418,     4,     7,     7,   158,
     158,     7,     7,     7,     5,     5,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     7,     5,   169,   391,     8,
       3,     5,     5,   140,   140,   140,   140,   140,     5,     7,
     140,   160,   162,   140,   140,   169,   169,   169,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   158,
     140,   140,   140,   113,   114,   431,   115,   116,   117,   118,
     119,   143,   439,   140,   158,   182,   121,   448,   449,   450,
     193,    15,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   173,   199,   200,   201,   204,   206,   208,   210,
     211,   213,   214,   215,   216,   217,   219,   199,     7,   261,
     262,   263,     7,   283,   284,   285,     7,   307,   308,   309,
      70,   140,   223,   224,   225,   226,   167,    71,    73,   225,
     229,   230,   231,   232,   275,   384,     7,   237,   238,   239,
      80,    81,    82,    83,    84,    85,   251,   252,   253,   254,
     255,   256,   257,   258,    15,    90,    91,    92,    93,   173,
     213,   394,   395,   396,   399,   400,   402,   403,    96,    97,
     407,   408,   409,   411,   417,   170,     4,   388,     7,   324,
     325,   326,     7,   338,   339,   340,     7,   355,   356,   357,
      75,   380,     8,   451,     3,     8,     8,   202,   205,   207,
     209,     4,     4,     4,     4,     4,   218,   220,     3,     8,
       8,   264,     6,     3,   286,     6,     3,   310,     6,     3,
       3,     6,     6,     3,     6,     3,     6,   240,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   397,   401,
       4,     4,     4,     3,     8,   410,   412,     3,     8,     8,
     140,   171,   172,   140,   327,     6,     3,   341,     6,     3,
     358,     6,     3,   381,     8,     4,   449,     4,     4,     4,
       4,   141,   143,   141,   143,   141,     4,     4,   200,   267,
     263,   289,   285,   313,   309,   224,   230,   275,   243,   239,
     141,   141,   141,   141,   141,   141,   252,     4,     4,   141,
     141,   141,   395,     4,     4,   408,     6,     3,   330,   326,
     344,   340,   361,   357,     4,     5,    16,    17,    18,    19,
     203,   140,   140,   140,   140,   140,     8,     8,     8,     8,
      87,    88,    89,   398,   140,   140,   140,   140,     8,     8,
       8,   140,     7,   452,   453,   454,     3,     6,   122,   124,
     125,   173,   211,   455,   456,   457,   458,   460,   453,   461,
       4,   459,     3,     8,     4,   141,     4,   456,     5,   140,
       7,   462,   463,   464,     3,     6,   123,   465,   466,   463,
     467,     3,     8,     4,   466,   140
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
     225,   226,   228,   227,   229,   229,   230,   230,   230,   231,
     232,   234,   233,   236,   235,   237,   237,   238,   238,   240,
     239,   242,   241,   243,   243,   243,   244,   244,   246,   245,
     248,   247,   250,   249,   251,   251,   252,   252,   252,   252,
     252,   252,   253,   254,   255,   256,   257,   258,   260,   259,
     261,   261,   262,   262,   264,   263,   266,   265,   267,   267,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   270,   269,   272,
     271,   274,   273,   276,   275,   278,   277,   279,   280,   282,
     281,   283,   283,   284,   284,   286,   285,   288,   287,   289,
     289,   290,   290,   291,   291,   291,   291,   291,   291,   291,
     291,   292,   293,   294,   296,   295,   298,   297,   300,   299,
     301,   303,   302,   304,   306,   305,   307,   307,   308,   308,
     310,   309,   312,   311,   313,   313,   314,   314,   315,   315,
     315,   315,   315,   315,   316,   318,   317,   319,   320,   321,
     323,   322,   324,   324,   325,   325,   327,   326,   329,   328,
     330,   330,   331,   331,   331,   331,   333,   332,   335,   334,
     337,   336,   338,   338,   339,   339,   341,   340,   343,   342,
     344,   344,   345,   345,   345,   345,   345,   345,   345,   345,
     347,   346,   348,   350,   349,   351,   352,   354,   353,   355,
     355,   356,   356,   358,   357,   360,   359,   361,   361,   362,
     362,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     365,   364,   367,   366,   369,   368,   371,   370,   373,   372,
     375,   374,   377,   376,   379,   378,   381,   380,   383,   382,
     384,   384,   385,   275,   386,   386,   387,   387,   388,   388,
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
       0,     4,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
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
  "\"flex-id\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
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
  "sub_interfaces6", "$@20", "interface_config_map", "$@21",
  "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "database_type", "$@24",
  "db_type", "user", "$@25", "password", "$@26", "host", "$@27", "port",
  "name", "$@28", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@29", "keyspace", "$@30", "mac_sources", "$@31",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@32",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@33",
  "hooks_libraries", "$@34", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@35",
  "sub_hooks_library", "$@36", "hooks_params", "hooks_param", "library",
  "$@37", "parameters", "$@38", "expired_leases_processing", "$@39",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@40",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@41",
  "sub_subnet6", "$@42", "subnet6_params", "subnet6_param", "subnet",
  "$@43", "interface", "$@44", "interface_id", "$@45", "client_class",
  "$@46", "reservation_mode", "$@47", "id", "rapid_commit",
  "option_def_list", "$@48", "option_def_list_content",
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
  "$@74", "hw_address", "$@75", "hostname", "$@76", "flex_id_value",
  "$@77", "reservation_client_classes", "$@78", "relay", "$@79",
  "relay_map", "$@80", "client_classes", "$@81", "client_classes_list",
  "$@82", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@83",
  "server_id", "$@84", "server_id_params", "server_id_param",
  "server_id_type", "$@85", "duid_type", "htype", "identifier", "$@86",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@87",
  "control_socket_params", "control_socket_param", "socket_type", "$@88",
  "socket_name", "$@89", "dhcp_ddns", "$@90", "sub_dhcp_ddns", "$@91",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@92", "server_ip", "$@93", "server_port",
  "sender_ip", "$@94", "sender_port", "max_queue_size", "ncr_protocol",
  "$@95", "ncr_protocol_value", "ncr_format", "$@96",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@97", "replace_client_name_value",
  "generated_prefix", "$@98", "dhcp4_json_object", "$@99",
  "dhcpddns_json_object", "$@100", "logging_object", "$@101",
  "logging_params", "logging_param", "loggers", "$@102", "loggers_entries",
  "logger_entry", "$@103", "logger_params", "logger_param", "debuglevel",
  "severity", "$@104", "output_options_list", "$@105",
  "output_options_list_content", "output_entry", "$@106", "output_params",
  "output_param", "$@107", YY_NULLPTR
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
     620,   625,   630,   630,   640,   641,   644,   645,   646,   649,
     654,   661,   661,   671,   671,   681,   682,   685,   686,   689,
     689,   697,   697,   705,   706,   707,   710,   711,   714,   714,
     722,   722,   730,   730,   740,   741,   744,   745,   746,   747,
     748,   749,   752,   757,   762,   767,   772,   777,   785,   785,
     798,   799,   802,   803,   810,   810,   833,   833,   842,   843,
     847,   848,   849,   850,   851,   852,   853,   854,   855,   856,
     857,   858,   859,   860,   861,   862,   863,   866,   866,   874,
     874,   882,   882,   890,   890,   898,   898,   906,   911,   920,
     920,   932,   933,   936,   937,   942,   942,   953,   953,   963,
     964,   967,   968,   971,   972,   973,   974,   975,   976,   977,
     978,   981,   983,   988,   990,   990,   998,   998,  1006,  1006,
    1014,  1016,  1016,  1024,  1033,  1033,  1045,  1046,  1051,  1052,
    1057,  1057,  1068,  1068,  1079,  1080,  1085,  1086,  1091,  1092,
    1093,  1094,  1095,  1096,  1099,  1101,  1101,  1109,  1111,  1113,
    1121,  1121,  1133,  1134,  1137,  1138,  1141,  1141,  1149,  1149,
    1157,  1158,  1161,  1162,  1163,  1164,  1167,  1167,  1175,  1175,
    1185,  1185,  1197,  1198,  1201,  1202,  1205,  1205,  1213,  1213,
    1221,  1222,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,
    1235,  1235,  1243,  1248,  1248,  1256,  1261,  1269,  1269,  1279,
    1280,  1283,  1284,  1287,  1287,  1295,  1295,  1303,  1304,  1307,
    1308,  1312,  1313,  1314,  1315,  1316,  1317,  1318,  1319,  1320,
    1323,  1323,  1333,  1333,  1343,  1343,  1351,  1351,  1359,  1359,
    1367,  1367,  1375,  1375,  1388,  1388,  1398,  1398,  1409,  1409,
    1419,  1420,  1423,  1423,  1431,  1432,  1435,  1436,  1439,  1440,
    1441,  1442,  1445,  1447,  1447,  1458,  1458,  1468,  1469,  1472,
    1473,  1474,  1475,  1476,  1477,  1478,  1481,  1481,  1488,  1489,
    1490,  1493,  1498,  1498,  1506,  1511,  1518,  1525,  1525,  1535,
    1536,  1539,  1540,  1543,  1543,  1551,  1551,  1561,  1561,  1571,
    1571,  1579,  1580,  1583,  1584,  1585,  1586,  1587,  1588,  1589,
    1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1600,  1605,
    1605,  1613,  1613,  1621,  1626,  1626,  1634,  1639,  1644,  1644,
    1652,  1653,  1656,  1656,  1664,  1669,  1674,  1679,  1679,  1687,
    1690,  1693,  1696,  1699,  1705,  1705,  1715,  1715,  1722,  1722,
    1734,  1734,  1747,  1748,  1752,  1756,  1756,  1768,  1769,  1773,
    1773,  1781,  1782,  1785,  1786,  1787,  1788,  1789,  1792,  1797,
    1797,  1805,  1805,  1815,  1816,  1819,  1819,  1827,  1828,  1831,
    1831
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
#line 4211 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1839 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
