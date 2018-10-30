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
      case 191: // value
      case 195: // map_value
      case 247: // db_type
      case 336: // hr_mode
      case 472: // duid_type
      case 505: // ncr_protocol_value
      case 513: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 173: // "boolean"
        value.move< bool > (that.value);
        break;

      case 172: // "floating point"
        value.move< double > (that.value);
        break;

      case 171: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 170: // "constant string"
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
      case 191: // value
      case 195: // map_value
      case 247: // db_type
      case 336: // hr_mode
      case 472: // duid_type
      case 505: // ncr_protocol_value
      case 513: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 173: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 172: // "floating point"
        value.copy< double > (that.value);
        break;

      case 171: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 170: // "constant string"
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
            case 170: // "constant string"

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 171: // "integer"

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 172: // "floating point"

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 173: // "boolean"

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 191: // value

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 195: // map_value

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 247: // db_type

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 336: // hr_mode

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 472: // duid_type

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 505: // ncr_protocol_value

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 513: // replace_client_name_value

#line 247 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 191: // value
      case 195: // map_value
      case 247: // db_type
      case 336: // hr_mode
      case 472: // duid_type
      case 505: // ncr_protocol_value
      case 513: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 173: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 172: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 171: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 170: // "constant string"
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
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 303 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 314 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 332 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 336 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 354 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 358 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 685 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 753 "dhcp6_parser.yy" // lalr1.cc:859
    {

    if ( (string(yystack_[0].value.as< std::string > ()) == "none") ||
         (string(yystack_[0].value.as< std::string > ()) == "warn") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix-del") ||
         (string(yystack_[0].value.as< std::string > ()) == "del")) {
        ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'lease-checks value: " + string(yystack_[0].value.as< std::string > ()) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}
#line 1511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 816 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1618 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1685 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
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

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 1012 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1897 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 1980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1138 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1174 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2079 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2186 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
    ConstElementPtr old = parent->get("user-context");

    // Handle already existing user context
    if (old) {
        // Check if it was a comment or a duplicate
        if ((old->size() != 1) || !old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the comment
        user_context->set("comment", old->get("comment"));
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    user_context->set("comment", comment);

    // Handle already existing user context
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        // Check for duplicate comment
        if (old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context/comment entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the user context in the comment
        merge(user_context, old);
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1547 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2520 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2538 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2547 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2681 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2707 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2725 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2026 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2043 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2061 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2064 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3284 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2070 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2073 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2081 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2097 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3380 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2137 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2148 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3472 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3503 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2187 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2192 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2212 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2233 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 650:
#line 2255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 651:
#line 2257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 653:
#line 2268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 656:
#line 2277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 657:
#line 2281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3633 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 664:
#line 2295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 665:
#line 2297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 666:
#line 2303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 667:
#line 2308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 668:
#line 2313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3678 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3682 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -822;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     413,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,    57,    46,    66,   106,
     142,   144,   146,   158,   179,   188,   198,   204,   227,   229,
     239,   252,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,    46,   -64,    44,    45,    55,   232,   200,   177,
      65,   202,    53,   203,   -23,   362,    63,    52,  -822,   257,
     274,   282,   284,   291,  -822,  -822,  -822,  -822,  -822,   292,
    -822,    71,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,   311,   313,   320,   322,   324,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,   326,  -822,  -822,  -822,    91,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   344,  -822,   124,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,   345,   355,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,   126,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,   135,  -822,  -822,
    -822,  -822,  -822,   367,  -822,   389,   391,  -822,  -822,  -822,
    -822,  -822,  -822,   136,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   332,   364,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   398,  -822,  -822,   393,  -822,  -822,  -822,   395,  -822,
    -822,   404,   410,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,   411,   412,  -822,  -822,
    -822,  -822,   432,   418,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,   182,  -822,  -822,  -822,
     437,  -822,  -822,   438,  -822,   441,   444,  -822,  -822,   451,
     452,   453,  -822,  -822,  -822,  -822,  -822,  -822,  -822,   186,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,   196,  -822,
    -822,  -822,  -822,   205,  -822,  -822,  -822,    46,    46,  -822,
     288,   455,   456,   457,   459,   460,  -822,    44,  -822,    52,
     462,   463,   464,   465,   466,   300,   301,   303,   305,   306,
     471,   474,   475,   476,   477,   492,   493,   494,   495,   496,
     497,   498,   501,   502,   503,   504,   338,   506,   507,    45,
    -822,   508,   340,    55,  -822,   511,   512,   513,   520,   521,
     356,   353,   524,   525,   526,   527,   232,  -822,   530,   200,
    -822,   531,   365,   533,   368,   369,   177,  -822,   534,   540,
     542,   543,   545,   546,   547,  -822,    65,  -822,   548,   552,
     386,   554,   555,   556,   388,  -822,    53,   558,   390,   414,
    -822,   203,   560,   579,    -3,  -822,   415,   580,   581,   419,
     582,   420,   421,   585,   589,   422,   423,   425,   590,   595,
     596,   597,   362,  -822,   598,    63,  -822,   599,    52,  -822,
    -822,  -822,   600,   601,   602,    46,    46,    46,  -822,   225,
     603,   604,   605,   606,   609,  -822,  -822,  -822,  -822,  -822,
     435,   610,   611,   612,   614,   436,   613,   617,   618,   619,
     620,   621,   623,   624,   625,   626,  -822,   627,   628,  -822,
     631,  -822,  -822,   632,   633,   449,   461,   469,  -822,  -822,
     363,   631,   470,   634,  -822,   472,  -822,   473,  -822,   478,
    -822,  -822,  -822,   631,   631,   631,   479,   480,   481,   482,
    -822,   483,   484,  -822,   485,   486,   487,  -822,  -822,   488,
    -822,  -822,  -822,   489,    46,  -822,  -822,   490,   491,  -822,
     499,  -822,  -822,     1,   509,  -822,  -822,  -822,   -57,   500,
     505,   510,  -822,   639,  -822,   641,  -822,    46,    45,    63,
    -822,  -822,  -822,  -822,    52,    55,   143,   143,   640,  -822,
     655,   656,   657,  -822,  -822,  -822,   658,   -20,    46,    23,
     584,   660,   661,   664,   231,   118,    75,   362,  -822,  -822,
     665,   666,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,     4,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,   667,   640,  -822,
     241,   267,   273,   275,  -822,  -822,  -822,  -822,   672,   673,
     674,   675,   677,  -822,   678,   679,  -822,   680,   681,   682,
    -822,   277,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
     287,  -822,   683,   622,  -822,  -822,   684,   685,  -822,  -822,
     686,   688,  -822,  -822,   687,   691,  -822,  -822,   689,   693,
    -822,  -822,  -822,    99,  -822,  -822,  -822,   692,  -822,  -822,
    -822,   160,  -822,  -822,  -822,  -822,   302,  -822,  -822,  -822,
     254,  -822,  -822,   694,   696,  -822,  -822,   695,   699,  -822,
     700,   701,   702,   703,   704,   705,   304,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,   706,   707,   708,  -822,
    -822,  -822,  -822,   335,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,   336,  -822,  -822,  -822,   347,
     517,  -822,   697,   710,  -822,  -822,   709,   711,  -822,  -822,
    -822,   712,  -822,  -822,   308,  -822,   713,  -822,  -822,  -822,
    -822,   714,   717,   718,   719,   553,   434,   557,   544,   559,
     721,   561,   562,   722,   563,   564,   565,   143,  -822,  -822,
     143,  -822,   640,   232,  -822,   655,    53,  -822,   656,   203,
    -822,   657,   378,  -822,   658,   -20,  -822,  -822,    23,  -822,
     723,   584,  -822,    12,   660,  -822,    65,  -822,   661,   -23,
    -822,   664,   566,   568,   569,   570,   571,   572,   231,  -822,
     725,   727,   573,   574,   575,   118,  -822,   732,   743,    75,
    -822,  -822,  -822,   742,   746,   200,  -822,   665,   177,  -822,
     666,   747,  -822,   161,   667,  -822,  -822,   431,   583,   586,
     587,  -822,  -822,  -822,  -822,  -822,   588,  -822,  -822,   591,
    -822,  -822,  -822,  -822,   348,  -822,   357,  -822,   744,  -822,
     751,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,   360,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,   592,  -822,  -822,   750,  -822,  -822,
    -822,  -822,  -822,   752,   761,  -822,  -822,  -822,  -822,  -822,
     757,  -822,   372,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   323,   607,  -822,  -822,  -822,  -822,   616,   642,  -822,
    -822,   649,   380,  -822,   400,  -822,   652,  -822,   763,  -822,
    -822,  -822,  -822,  -822,   426,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,   378,  -822,  -822,   764,   577,  -822,
      12,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,   766,   608,   767,   161,  -822,  -822,
     662,  -822,  -822,   769,  -822,   668,  -822,  -822,   690,  -822,
    -822,   376,  -822,   172,   690,  -822,  -822,   772,   776,   779,
     427,  -822,  -822,  -822,  -822,  -822,  -822,   787,   637,   654,
     659,   172,  -822,   676,  -822,  -822,  -822,  -822,  -822
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   115,     9,
     256,    11,   402,    13,   427,    15,   457,    17,   327,    19,
     335,    21,   372,    23,   221,    25,   554,    27,   629,    29,
     619,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     459,     0,   337,   374,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   627,   609,   611,   613,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   615,   617,
     113,   127,   129,   131,     0,     0,     0,     0,     0,   111,
     248,   325,   364,   415,   417,   298,   194,   211,   202,   187,
     494,   449,   213,   232,   515,     0,   539,   552,   105,     0,
      74,    76,    77,    78,    79,    80,   104,    83,    84,    85,
      86,   101,    87,    89,    88,    93,    94,    81,    82,    91,
      92,    99,   100,   102,    90,    95,    96,    97,    98,   103,
     124,     0,   123,     0,   117,   119,   120,   121,   122,   394,
     419,   280,   282,   284,     0,     0,   290,   288,   286,   488,
     279,   260,   261,   262,   263,     0,   258,   267,   268,   269,
     272,   273,   275,   270,   271,   264,   265,   277,   278,   266,
     274,   276,   413,   412,   408,   409,   407,     0,   404,   406,
     410,   411,   442,     0,   445,     0,     0,   441,   435,   436,
     434,   439,   440,     0,   429,   431,   432,   437,   438,   433,
     486,   474,   476,   478,   480,   482,   484,   473,   470,   471,
     472,     0,   460,   461,   465,   466,   463,   467,   468,   469,
     464,     0,   354,   172,     0,   358,   356,   361,     0,   350,
     351,     0,   338,   339,   341,   353,   342,   343,   344,   360,
     345,   346,   347,   348,   349,   388,     0,     0,   386,   387,
     390,   391,     0,   375,   376,   378,   379,   380,   381,   382,
     383,   384,   385,   228,   230,   225,     0,   223,   226,   227,
       0,   578,   580,     0,   583,     0,     0,   587,   591,     0,
       0,     0,   596,   603,   605,   607,   576,   574,   575,     0,
     556,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   634,     0,   631,
     633,   625,   624,     0,   621,   623,    48,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    59,     0,    61,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   257,     0,     0,
     403,     0,     0,     0,     0,     0,     0,   428,     0,     0,
       0,     0,     0,     0,     0,   458,     0,   328,     0,     0,
       0,     0,     0,     0,     0,   336,     0,     0,     0,     0,
     373,     0,     0,     0,     0,   222,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   555,     0,     0,   630,     0,     0,   620,
      52,    45,     0,     0,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,     0,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   538,     0,     0,    75,
       0,   126,   118,     0,     0,     0,     0,     0,   296,   297,
       0,     0,     0,     0,   259,     0,   405,     0,   444,     0,
     447,   448,   430,     0,     0,     0,     0,     0,     0,     0,
     462,     0,     0,   352,     0,     0,     0,   363,   340,     0,
     392,   393,   377,     0,     0,   224,   577,     0,     0,   582,
       0,   585,   586,     0,     0,   593,   594,   595,     0,     0,
       0,     0,   557,     0,   632,     0,   622,     0,     0,     0,
     610,   612,   614,   616,     0,     0,     0,     0,   133,   112,
     250,   329,   366,    42,   416,   418,   300,     0,    49,     0,
       0,     0,   451,   215,     0,     0,     0,     0,    53,   125,
     396,   421,   281,   283,   285,   292,   293,   294,   295,   291,
     289,   287,     0,   414,   443,   446,   487,   475,   477,   479,
     481,   483,   485,   355,   173,   359,   357,   362,   389,   229,
     231,   579,   581,   584,   589,   590,   588,   592,   598,   599,
     600,   601,   602,   597,   604,   606,   608,     0,   133,    46,
       0,     0,     0,     0,   159,   165,   167,   169,     0,     0,
       0,     0,     0,   182,     0,     0,   185,     0,     0,     0,
     158,     0,   139,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   153,   154,   155,   156,   151,   152,   157,
       0,   137,     0,   134,   135,   254,     0,   251,   252,   333,
       0,   330,   331,   370,     0,   367,   368,   304,     0,   301,
     302,   200,   201,     0,   196,   198,   199,     0,   209,   210,
     206,     0,   204,   207,   208,   192,     0,   189,   191,   498,
       0,   496,   455,     0,   452,   453,   219,     0,   216,   217,
       0,     0,     0,     0,     0,     0,     0,   234,   236,   237,
     238,   239,   240,   241,   528,   534,     0,     0,     0,   527,
     524,   525,   526,     0,   517,   519,   522,   520,   521,   523,
     548,   550,   547,   545,   546,     0,   541,   543,   544,     0,
      55,   400,     0,   397,   398,   425,     0,   422,   423,   492,
     491,     0,   490,   638,     0,   636,     0,    71,   628,   618,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   128,   130,
       0,   132,     0,     0,   249,     0,   337,   326,     0,   374,
     365,     0,     0,   299,     0,     0,   195,   212,     0,   203,
       0,     0,   188,   500,     0,   495,   459,   450,     0,     0,
     214,     0,     0,     0,     0,     0,     0,     0,     0,   233,
       0,     0,     0,     0,     0,     0,   516,     0,     0,     0,
     540,   553,    57,     0,    56,     0,   395,     0,     0,   420,
       0,     0,   489,     0,     0,   635,   626,     0,     0,     0,
       0,   171,   174,   175,   176,   177,     0,   184,   178,     0,
     179,   180,   181,   140,     0,   136,     0,   253,     0,   332,
       0,   369,   324,   319,   321,   312,   313,   308,   309,   310,
     311,   317,   318,   316,   320,     0,   306,   314,   322,   323,
     315,   303,   197,   205,     0,   190,   512,     0,   510,   511,
     507,   508,   509,     0,   501,   502,   504,   505,   506,   497,
       0,   454,     0,   218,   242,   243,   244,   245,   246,   247,
     235,     0,     0,   533,   536,   537,   518,     0,     0,   542,
      54,     0,     0,   399,     0,   424,     0,   652,     0,   650,
     648,   642,   646,   647,     0,   640,   644,   645,   643,   637,
     161,   162,   163,   164,   160,   166,   168,   170,   183,   186,
     138,   255,   334,   371,     0,   305,   193,     0,     0,   499,
       0,   456,   220,   530,   531,   532,   529,   535,   549,   551,
      58,   401,   426,   493,     0,     0,     0,     0,   639,   307,
       0,   514,   503,     0,   649,     0,   641,   513,     0,   651,
     656,     0,   654,     0,     0,   653,   664,     0,     0,     0,
       0,   658,   660,   661,   662,   663,   655,     0,     0,     0,
       0,     0,   657,     0,   666,   667,   668,   659,   665
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,    33,  -822,   212,
    -822,  -822,  -822,  -822,  -822,  -822,    22,  -822,  -343,  -822,
    -822,  -822,   -74,  -822,  -822,  -822,   467,  -822,  -822,  -822,
    -822,   167,   399,   -70,   -58,   -55,   -38,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,   233,   439,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,   169,  -822,   -16,  -822,  -573,
       6,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   -46,  -822,  -603,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,   -17,
    -822,  -822,  -822,  -822,  -822,    -8,  -596,  -822,  -822,  -822,
    -822,    -9,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
     -21,  -822,  -822,  -822,   -14,   402,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,   -26,  -822,  -822,  -822,  -822,  -822,  -822,
    -821,  -822,  -822,  -822,    13,  -822,  -822,  -822,    16,   446,
    -822,  -822,  -818,  -822,  -814,  -822,   -34,  -822,   -32,  -822,
    -812,  -822,  -822,  -822,  -804,  -822,  -822,  -822,  -822,    11,
    -822,  -822,  -164,   786,  -822,  -822,  -822,  -822,  -822,    20,
    -822,  -822,  -822,    24,  -822,   428,  -822,   -42,  -822,  -822,
    -822,  -822,  -822,   -40,  -822,  -822,  -822,  -822,  -822,   -12,
    -822,  -822,  -822,    18,  -822,  -822,  -822,    26,  -822,   429,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   -25,  -822,  -822,  -822,   -24,   454,  -822,  -822,   -62,
    -822,   -50,  -822,  -822,  -822,  -822,  -822,   -22,  -822,  -822,
    -822,   -19,   450,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
     -35,  -822,  -822,  -822,     9,  -822,  -822,  -822,    15,  -822,
     448,   250,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -803,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,    21,  -822,  -822,  -822,  -143,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,     3,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,     0,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,   276,   424,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -344,   416,  -822,
    -822,  -822,  -822,  -822,  -822,   309,   417,  -822,  -822,  -822,
     -13,  -822,  -822,  -157,  -822,  -822,  -822,  -822,  -822,  -822,
    -169,  -822,  -822,  -184,  -822,  -822,  -822,  -822,  -822
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   604,    92,    93,    43,    72,    89,    90,   619,   800,
     893,   894,   352,    45,    74,   101,   102,   103,   361,    47,
      75,   139,   140,   141,   142,   143,   144,   145,   146,   380,
     147,   371,    49,    76,   173,   174,   175,   401,   176,   148,
     372,   149,   373,   150,   374,   712,   713,   714,   840,   691,
     692,   693,   821,  1014,   694,   822,   695,   823,   696,   824,
     697,   698,   439,   699,   700,   701,   702,   703,   704,   705,
     706,   707,   830,   708,   709,   833,   151,   390,   746,   747,
     748,   860,   152,   387,   733,   734,   735,   736,   153,   389,
     741,   742,   743,   744,   154,   388,   155,   393,   757,   758,
     759,   869,    65,    84,   306,   307,   308,   452,   309,   453,
     156,   394,   766,   767,   768,   769,   770,   771,   772,   773,
     157,   381,   716,   717,   718,   843,    51,    77,   195,   196,
     197,   407,   198,   408,   199,   409,   200,   414,   201,   413,
     202,   412,   629,   203,   204,   158,   386,   728,   729,   730,
     852,   945,   946,   159,   382,    59,    81,   720,   721,   722,
     846,    61,    82,   271,   272,   273,   274,   275,   276,   277,
     438,   278,   442,   279,   441,   280,   281,   443,   282,   160,
     383,   724,   725,   726,   849,    63,    83,   292,   293,   294,
     295,   296,   447,   297,   298,   299,   300,   206,   405,   802,
     803,   804,   895,    53,    78,   217,   218,   219,   418,   161,
     384,   162,   385,   209,   406,   806,   807,   808,   898,    55,
      79,   233,   234,   235,   421,   236,   237,   423,   238,   239,
     163,   392,   753,   754,   755,   866,    57,    80,   251,   252,
     253,   254,   429,   255,   430,   256,   431,   257,   432,   258,
     433,   259,   434,   260,   428,   211,   415,   811,   812,   901,
     164,   391,   750,   751,   863,   963,   964,   965,   966,   967,
    1027,   968,   165,   395,   783,   784,   785,   880,  1036,   786,
     787,   881,   788,   789,   166,   167,   397,   795,   796,   797,
     887,   798,   888,   168,   398,    67,    85,   329,   330,   331,
     332,   457,   333,   458,   334,   335,   460,   336,   337,   338,
     463,   656,   339,   464,   340,   341,   342,   343,   468,   663,
     344,   469,   345,   470,   346,   471,   104,   363,   105,   364,
     106,   365,   169,   369,   370,    71,    87,   353,   354,   355,
     477,   107,   362,    69,    86,   348,   349,   350,   474,   814,
     815,   903,  1004,  1005,  1006,  1007,  1046,  1008,  1044,  1061,
    1062,  1063,  1070,  1071,  1072,  1077,  1073,  1074,  1075
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
     100,   138,   172,   190,   213,   227,   247,   191,   269,   288,
     305,   326,   780,   740,   177,   207,   220,   231,   249,   192,
     283,   301,   193,   327,   710,   489,   178,   208,   221,   232,
     250,   938,   284,   302,   939,   328,   270,   289,   940,   194,
     943,   290,   210,   291,   214,   228,   215,   229,   944,   950,
      40,    33,   108,    34,    94,    35,   109,    32,   110,   122,
     263,   111,   112,   113,   351,   205,   216,   230,   248,   170,
     171,   731,   262,    44,   367,   303,   304,   123,   124,   368,
     658,   659,   660,   661,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   241,   399,   303,   304,   956,   957,   400,
     809,   263,   855,   264,   265,   856,    91,   266,   267,   268,
     123,   124,   122,    46,   731,   738,   662,   739,   123,   124,
     123,   124,   125,   126,   127,   128,   129,   403,   130,   416,
     123,   124,   404,   131,   417,   654,   655,   774,   419,   426,
     123,   124,   132,   420,   427,   133,   679,    99,   240,    48,
     732,    50,   134,    52,   241,   242,   243,   244,   245,   246,
     135,   136,   674,   858,   137,    54,   859,   675,   676,   677,
     678,   679,   680,   681,   682,   683,   684,   685,   686,   687,
     688,   689,    99,   123,   124,   454,    56,    95,   630,   472,
     455,   263,   790,   791,   473,    58,    96,    97,    98,   475,
     636,   637,   638,   938,   476,    60,   939,   347,   478,   263,
     940,    62,   943,   479,    99,    99,    36,    37,    38,    39,
     944,   950,    99,    99,   122,    99,   123,   124,   478,   775,
     776,   777,   778,   593,    64,    99,    66,   222,   223,   224,
     225,   226,   123,   124,   399,    99,    68,   122,   121,   817,
     672,   263,   285,   264,   265,   286,   287,   864,   212,    70,
     865,   187,   740,   356,   188,   123,   124,   924,   123,   124,
     475,   114,   115,   116,   117,   818,   478,   357,   403,   122,
     837,   819,   780,   820,   187,   838,   358,   188,    99,   179,
     837,   180,   359,   100,   360,   839,   366,   123,   124,   181,
     182,   183,   184,   185,   186,   861,   997,   878,   998,   999,
     862,   904,   879,    99,   905,   375,   187,   376,  1066,   188,
     131,  1067,  1068,  1069,   377,   138,   378,   189,   379,   172,
     396,    99,   760,   761,   762,   763,   764,   765,   885,   889,
     435,   177,   190,   886,   890,   213,   191,    99,   402,   410,
     472,   837,   227,   178,   207,   891,  1020,   220,   192,   411,
     416,   193,   247,  1024,   231,  1021,   208,   436,  1025,   221,
      99,   422,   269,    99,   249,   454,   232,   288,   194,  1064,
    1032,   210,  1065,   419,   283,   214,   250,   215,  1041,   301,
     480,   481,   228,   424,   229,   425,   284,   440,   326,   444,
     270,   302,    99,   426,   205,   289,   437,   216,  1042,   290,
     327,   291,   445,   446,   230,   448,   449,   114,   115,   116,
     117,   451,   328,   120,   248,   122,   263,   123,   124,  1047,
    1081,  1033,  1034,  1035,  1048,  1082,   625,   626,   627,   628,
     450,   456,   459,   123,   124,   461,   182,   183,   462,   185,
     186,  1010,  1011,  1012,  1013,   465,   466,   467,   482,   483,
     484,   485,   187,   486,   487,   188,   490,   491,   492,   493,
     494,   495,   496,   189,   497,   500,   498,   499,   501,   502,
     503,   504,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   505,   506,   507,   508,
     509,   510,   511,   324,   325,   512,   513,   514,   515,   516,
     517,   518,   520,   521,   138,   523,   524,   525,   590,   591,
     592,   172,   690,   690,   526,   527,   529,   528,   530,   531,
     532,   533,    99,   177,   535,   537,   538,   539,   543,   540,
     541,   779,   792,   326,   544,   178,   545,   546,    99,   547,
     548,   549,   551,   781,   793,   327,   552,   553,   554,   555,
     556,   557,   559,   560,   563,   782,   794,   328,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,   564,   567,   568,   570,   561,   566,   573,
     569,   571,   572,   574,   578,   575,   576,   650,   577,   579,
     580,   581,   583,   585,   587,   599,   605,   912,   588,   589,
     594,   595,   596,   597,   598,   600,   601,   602,   606,   622,
     669,    34,   607,   608,   609,   842,   611,   610,   612,   613,
     737,   623,   614,   615,   616,   617,   618,   620,   621,   624,
     631,   632,   633,   634,   667,   657,   668,   711,   635,   639,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   649,
     651,   652,   715,   719,   723,   727,   745,   749,   752,   653,
     664,   756,   801,   805,   813,   665,   825,   826,   827,   828,
     666,   829,   831,   832,   834,   835,   836,   892,   845,   841,
     844,   848,   847,   850,   851,   853,   854,  1060,   857,   868,
     867,   870,   871,   896,   872,   873,   874,   875,   876,   877,
     882,   883,   884,   897,   900,   899,   603,   914,   907,   906,
     902,   908,   909,   910,   911,   916,   919,   954,   913,   981,
     915,   982,   917,   918,   920,   921,   987,   974,   922,   975,
     976,   977,   978,   979,   983,   984,   985,   988,   990,   991,
    1051,   996,  1022,  1015,  1028,   670,  1016,  1017,  1018,  1023,
    1029,  1019,  1026,   690,  1030,  1031,   690,  1045,  1050,   190,
    1053,  1055,   269,   191,  1058,   288,  1078,  1037,   932,  1054,
    1079,   207,   933,  1080,   283,   192,  1038,   301,   193,   958,
     948,  1083,   247,   208,   934,   305,   284,   935,   519,   302,
     270,   961,   949,   289,   249,   194,   937,   290,   210,   291,
    1084,   779,  1039,   962,   936,   792,   250,   959,   941,  1040,
     942,   213,  1043,   781,   227,  1085,   925,   793,   673,  1000,
    1086,   205,  1057,   220,   488,   782,   231,   816,  1059,   794,
     947,  1002,   522,   923,   955,   221,  1088,   952,   232,   953,
     973,   960,   980,  1003,   248,   972,   565,  1001,   927,   926,
    1049,   214,   534,   215,   228,   951,   229,   261,   929,   931,
     928,   992,   993,   536,   558,   930,   542,   971,   995,   994,
     562,   970,   810,   216,   550,   969,   230,  1052,   986,   989,
    1056,  1009,   584,   799,   586,  1076,   582,  1087,   671,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     932,     0,     0,     0,   933,     0,   958,     0,     0,     0,
       0,     0,   948,     0,     0,     0,   934,     0,   961,   935,
       0,     0,     0,  1000,   949,     0,     0,     0,   937,     0,
     962,     0,     0,     0,   959,  1002,   936,     0,     0,     0,
     941,     0,   942,     0,     0,     0,     0,  1003,     0,     0,
       0,  1001,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   947,     0,     0,     0,     0,     0,   960
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,   615,   609,    76,    77,    78,    79,    80,    77,
      82,    83,    77,    85,   597,   369,    76,    77,    78,    79,
      80,   852,    82,    83,   852,    85,    82,    83,   852,    77,
     852,    83,    77,    83,    78,    79,    78,    79,   852,   852,
      17,     5,     7,     7,    10,     9,    11,     0,    13,    47,
      48,    16,    17,    18,    12,    77,    78,    79,    80,    14,
      15,    91,    19,     7,     3,    98,    99,    65,    66,     8,
     137,   138,   139,   140,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    89,     3,    98,    99,    85,    86,     8,
      96,    48,     3,    50,    51,     6,   170,    54,    55,    56,
      65,    66,    47,     7,    91,    92,   173,    94,    65,    66,
      65,    66,    77,    78,    79,    80,    81,     3,    83,     3,
      65,    66,     8,    88,     8,   134,   135,    19,     3,     3,
      65,    66,    97,     8,     8,   100,    28,   170,    83,     7,
     170,     7,   107,     7,    89,    90,    91,    92,    93,    94,
     115,   116,    19,     3,   119,     7,     6,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   170,    65,    66,     3,     7,   143,   531,     3,
       8,    48,   117,   118,     8,     7,   152,   153,   154,     3,
     543,   544,   545,  1024,     8,     7,  1024,   144,     3,    48,
    1024,     7,  1024,     8,   170,   170,   170,   171,   172,   173,
    1024,  1024,   170,   170,    47,   170,    65,    66,     3,   111,
     112,   113,   114,     8,     7,   170,     7,    60,    61,    62,
      63,    64,    65,    66,     3,   170,     7,    47,    46,     8,
     594,    48,    49,    50,    51,    52,    53,     3,    58,     7,
       6,    84,   858,     6,    87,    65,    66,   840,    65,    66,
       3,    39,    40,    41,    42,     8,     3,     3,     3,    47,
       3,     8,   885,     8,    84,     8,     4,    87,   170,    57,
       3,    59,     8,   367,     3,     8,     4,    65,    66,    67,
      68,    69,    70,    71,    72,     3,   145,     3,   147,   148,
       8,     3,     8,   170,     6,     4,    84,     4,   146,    87,
      88,   149,   150,   151,     4,   399,     4,    95,     4,   403,
       4,   170,   101,   102,   103,   104,   105,   106,     3,     3,
       8,   403,   416,     8,     8,   419,   416,   170,     4,     4,
       3,     3,   426,   403,   416,     8,     8,   419,   416,     4,
       3,   416,   436,     3,   426,     8,   416,     3,     8,   419,
     170,     4,   446,   170,   436,     3,   426,   451,   416,     3,
       8,   416,     6,     3,   446,   419,   436,   419,     8,   451,
     357,   358,   426,     4,   426,     4,   446,     4,   472,     4,
     446,   451,   170,     3,   416,   451,     8,   419,     8,   451,
     472,   451,     8,     3,   426,     4,     4,    39,    40,    41,
      42,     3,   472,    45,   436,    47,    48,    65,    66,     3,
       3,   108,   109,   110,     8,     8,    73,    74,    75,    76,
       8,     4,     4,    65,    66,     4,    68,    69,     4,    71,
      72,    20,    21,    22,    23,     4,     4,     4,   170,     4,
       4,     4,    84,     4,     4,    87,     4,     4,     4,     4,
       4,   171,   171,    95,   171,     4,   171,   171,     4,     4,
       4,     4,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,     4,     4,     4,     4,
       4,     4,     4,   141,   142,     4,     4,     4,     4,   171,
       4,     4,     4,   173,   588,     4,     4,     4,   485,   486,
     487,   595,   596,   597,     4,     4,   173,   171,     4,     4,
       4,     4,   170,   595,     4,     4,   171,     4,     4,   171,
     171,   615,   616,   617,     4,   595,     4,     4,   170,     4,
       4,     4,     4,   615,   616,   617,     4,   171,     4,     4,
       4,   173,     4,   173,     4,   615,   616,   617,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,     4,     4,     4,     4,   173,   173,     4,
     171,   171,   171,     4,     4,   173,   173,   564,   173,     4,
       4,     4,     4,     4,     4,   170,   170,   173,     7,     7,
       7,     7,     7,     7,     5,     5,     5,     5,     5,   170,
     587,     7,     5,     5,     5,     3,     5,     7,     5,     5,
     608,   170,     7,     7,     7,     7,     5,     5,     5,   170,
     170,     7,   170,   170,     5,   136,     5,     7,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,     7,     7,     7,     7,    82,     7,     7,   170,
     170,     7,     7,     7,     7,   170,     4,     4,     4,     4,
     170,     4,     4,     4,     4,     4,     4,   170,     3,     6,
       6,     3,     6,     6,     3,     6,     3,     7,     6,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,     3,     6,   504,   173,     4,     6,
       8,     4,     4,     4,   171,     4,     4,     4,   171,     4,
     171,     4,   171,   171,   171,   171,     4,   171,   173,   171,
     171,   171,   171,   171,   171,   171,   171,     4,     6,     3,
     173,     4,     8,   170,     4,   588,   170,   170,   170,     8,
       8,   170,   170,   837,     3,     8,   840,     4,     4,   843,
       4,     4,   846,   843,     5,   849,     4,   170,   852,   171,
       4,   843,   852,     4,   846,   843,   170,   849,   843,   863,
     852,     4,   866,   843,   852,   869,   846,   852,   399,   849,
     846,   863,   852,   849,   866,   843,   852,   849,   843,   849,
     173,   885,   170,   863,   852,   889,   866,   863,   852,   170,
     852,   895,   170,   885,   898,   171,   842,   889,   595,   903,
     171,   843,   170,   895,   367,   885,   898,   668,   170,   889,
     852,   903,   403,   837,   861,   895,   170,   855,   898,   858,
     871,   863,   878,   903,   866,   869,   454,   903,   845,   843,
    1024,   895,   416,   895,   898,   854,   898,    81,   848,   851,
     846,   895,   897,   419,   446,   849,   426,   868,   900,   898,
     451,   866,   632,   895,   436,   864,   898,  1030,   885,   889,
    1047,   904,   475,   617,   478,  1064,   472,  1081,   589,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1024,    -1,    -1,    -1,  1024,    -1,  1030,    -1,    -1,    -1,
      -1,    -1,  1024,    -1,    -1,    -1,  1024,    -1,  1030,  1024,
      -1,    -1,    -1,  1047,  1024,    -1,    -1,    -1,  1024,    -1,
    1030,    -1,    -1,    -1,  1030,  1047,  1024,    -1,    -1,    -1,
    1024,    -1,  1024,    -1,    -1,    -1,    -1,  1047,    -1,    -1,
      -1,  1047,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1024,    -1,    -1,    -1,    -1,    -1,  1030
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,     0,     5,     7,     9,   170,   171,   172,   173,
     191,   192,   193,   198,     7,   207,     7,   213,     7,   226,
       7,   320,     7,   397,     7,   413,     7,   430,     7,   349,
       7,   355,     7,   379,     7,   296,     7,   489,     7,   537,
       7,   529,   199,   194,   208,   214,   227,   321,   398,   414,
     431,   350,   356,   380,   297,   490,   538,   530,   191,   200,
     201,   170,   196,   197,    10,   143,   152,   153,   154,   170,
     206,   209,   210,   211,   520,   522,   524,   535,     7,    11,
      13,    16,    17,    18,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    65,    66,    77,    78,    79,    80,    81,
      83,    88,    97,   100,   107,   115,   116,   119,   206,   215,
     216,   217,   218,   219,   220,   221,   222,   224,   233,   235,
     237,   270,   276,   282,   288,   290,   304,   314,   339,   347,
     373,   403,   405,   424,   454,   466,   478,   479,   487,   526,
      14,    15,   206,   228,   229,   230,   232,   403,   405,    57,
      59,    67,    68,    69,    70,    71,    72,    84,    87,    95,
     206,   217,   218,   219,   220,   322,   323,   324,   326,   328,
     330,   332,   334,   337,   338,   373,   391,   403,   405,   407,
     424,   449,    58,   206,   330,   332,   373,   399,   400,   401,
     403,   405,    60,    61,    62,    63,    64,   206,   330,   332,
     373,   403,   405,   415,   416,   417,   419,   420,   422,   423,
      83,    89,    90,    91,    92,    93,    94,   206,   373,   403,
     405,   432,   433,   434,   435,   437,   439,   441,   443,   445,
     447,   347,    19,    48,    50,    51,    54,    55,    56,   206,
     255,   357,   358,   359,   360,   361,   362,   363,   365,   367,
     369,   370,   372,   403,   405,    49,    52,    53,   206,   255,
     361,   367,   381,   382,   383,   384,   385,   387,   388,   389,
     390,   403,   405,    98,    99,   206,   298,   299,   300,   302,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   141,   142,   206,   403,   405,   491,
     492,   493,   494,   496,   498,   499,   501,   502,   503,   506,
     508,   509,   510,   511,   514,   516,   518,   144,   539,   540,
     541,    12,   206,   531,   532,   533,     6,     3,     4,     8,
       3,   212,   536,   521,   523,   525,     4,     3,     8,   527,
     528,   225,   234,   236,   238,     4,     4,     4,     4,     4,
     223,   315,   348,   374,   404,   406,   340,   277,   289,   283,
     271,   455,   425,   291,   305,   467,     4,   480,   488,     3,
       8,   231,     4,     3,     8,   392,   408,   325,   327,   329,
       4,     4,   335,   333,   331,   450,     3,     8,   402,     3,
       8,   418,     4,   421,     4,     4,     3,     8,   448,   436,
     438,   440,   442,   444,   446,     8,     3,     8,   364,   256,
       4,   368,   366,   371,     4,     8,     3,   386,     4,     4,
       8,     3,   301,   303,     3,     8,     4,   495,   497,     4,
     500,     4,     4,   504,   507,     4,     4,     4,   512,   515,
     517,   519,     3,     8,   542,     3,     8,   534,     3,     8,
     191,   191,   170,     4,     4,     4,     4,     4,   210,   531,
       4,     4,     4,     4,     4,   171,   171,   171,   171,   171,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   171,     4,     4,   216,
       4,   173,   229,     4,     4,     4,     4,     4,   171,   173,
       4,     4,     4,     4,   323,     4,   400,     4,   171,     4,
     171,   171,   416,     4,     4,     4,     4,     4,     4,     4,
     434,     4,     4,   171,     4,     4,     4,   173,   359,     4,
     173,   173,   383,     4,     4,   299,   173,     4,     4,   171,
       4,   171,   171,     4,     4,   173,   173,   173,     4,     4,
       4,     4,   492,     4,   540,     4,   532,     4,     7,     7,
     191,   191,   191,     8,     7,     7,     7,     7,     5,   170,
       5,     5,     5,   193,   195,   170,     5,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     7,     5,   202,
       5,     5,   170,   170,   170,    73,    74,    75,    76,   336,
     202,   170,     7,   170,   170,   170,   202,   202,   202,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     191,   170,   170,   170,   134,   135,   505,   136,   137,   138,
     139,   140,   173,   513,   170,   170,   170,     5,     5,   191,
     215,   539,   531,   228,    19,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
     206,   243,   244,   245,   248,   250,   252,   254,   255,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   267,   268,
     243,     7,   239,   240,   241,     7,   316,   317,   318,     7,
     351,   352,   353,     7,   375,   376,   377,     7,   341,   342,
     343,    91,   170,   278,   279,   280,   281,   200,    92,    94,
     280,   284,   285,   286,   287,    82,   272,   273,   274,     7,
     456,   457,     7,   426,   427,   428,     7,   292,   293,   294,
     101,   102,   103,   104,   105,   106,   306,   307,   308,   309,
     310,   311,   312,   313,    19,   111,   112,   113,   114,   206,
     257,   403,   405,   468,   469,   470,   473,   474,   476,   477,
     117,   118,   206,   403,   405,   481,   482,   483,   485,   491,
     203,     7,   393,   394,   395,     7,   409,   410,   411,    96,
     435,   451,   452,     7,   543,   544,   239,     8,     8,     8,
       8,   246,   249,   251,   253,     4,     4,     4,     4,     4,
     266,     4,     4,   269,     4,     4,     4,     3,     8,     8,
     242,     6,     3,   319,     6,     3,   354,     6,     3,   378,
       6,     3,   344,     6,     3,     3,     6,     6,     3,     6,
     275,     3,     8,   458,     3,     6,   429,     6,     3,   295,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     471,   475,     4,     4,     4,     3,     8,   484,   486,     3,
       8,     8,   170,   204,   205,   396,     6,     3,   412,     6,
       3,   453,     8,   545,     3,     6,     6,     4,     4,     4,
       4,   171,   173,   171,   173,   171,     4,   171,   171,     4,
     171,   171,   173,   244,   243,   241,   322,   318,   357,   353,
     381,   377,   206,   217,   218,   219,   220,   255,   314,   326,
     328,   330,   332,   334,   338,   345,   346,   373,   403,   405,
     449,   343,   279,   285,     4,   273,    85,    86,   206,   255,
     373,   403,   405,   459,   460,   461,   462,   463,   465,   457,
     432,   428,   298,   294,   171,   171,   171,   171,   171,   171,
     307,     4,     4,   171,   171,   171,   469,     4,     4,   482,
       6,     3,   399,   395,   415,   411,     4,   145,   147,   148,
     206,   255,   403,   405,   546,   547,   548,   549,   551,   544,
      20,    21,    22,    23,   247,   170,   170,   170,   170,   170,
       8,     8,     8,     8,     3,     8,   170,   464,     4,     8,
       3,     8,     8,   108,   109,   110,   472,   170,   170,   170,
     170,     8,     8,   170,   552,     4,   550,     3,     8,   346,
       4,   173,   461,     4,   171,     4,   547,   170,     5,   170,
       7,   553,   554,   555,     3,     6,   146,   149,   150,   151,
     556,   557,   558,   560,   561,   562,   554,   559,     4,     4,
       4,     3,     8,     4,   173,   171,   171,   557,   170
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   174,   176,   175,   177,   175,   178,   175,   179,   175,
     180,   175,   181,   175,   182,   175,   183,   175,   184,   175,
     185,   175,   186,   175,   187,   175,   188,   175,   189,   175,
     190,   175,   191,   191,   191,   191,   191,   191,   191,   192,
     194,   193,   195,   196,   196,   197,   197,   199,   198,   200,
     200,   201,   201,   203,   202,   204,   204,   205,   205,   206,
     208,   207,   209,   209,   210,   210,   210,   210,   210,   210,
     212,   211,   214,   213,   215,   215,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   217,   218,   219,   220,
     221,   223,   222,   225,   224,   227,   226,   228,   228,   229,
     229,   229,   229,   229,   231,   230,   232,   234,   233,   236,
     235,   238,   237,   239,   239,   240,   240,   242,   241,   243,
     243,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   246,
     245,   247,   247,   247,   247,   249,   248,   251,   250,   253,
     252,   254,   256,   255,   257,   258,   259,   260,   261,   262,
     263,   264,   266,   265,   267,   269,   268,   271,   270,   272,
     272,   273,   275,   274,   277,   276,   278,   278,   279,   279,
     280,   281,   283,   282,   284,   284,   285,   285,   285,   286,
     287,   289,   288,   291,   290,   292,   292,   293,   293,   295,
     294,   297,   296,   298,   298,   298,   299,   299,   301,   300,
     303,   302,   305,   304,   306,   306,   307,   307,   307,   307,
     307,   307,   308,   309,   310,   311,   312,   313,   315,   314,
     316,   316,   317,   317,   319,   318,   321,   320,   322,   322,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     325,   324,   327,   326,   329,   328,   331,   330,   333,   332,
     335,   334,   336,   336,   336,   336,   337,   338,   340,   339,
     341,   341,   342,   342,   344,   343,   345,   345,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   348,   347,   350,   349,   351,
     351,   352,   352,   354,   353,   356,   355,   357,   357,   358,
     358,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   360,   361,   362,   364,   363,   366,   365,   368,   367,
     369,   371,   370,   372,   374,   373,   375,   375,   376,   376,
     378,   377,   380,   379,   381,   381,   382,   382,   383,   383,
     383,   383,   383,   383,   383,   383,   383,   384,   386,   385,
     387,   388,   389,   390,   392,   391,   393,   393,   394,   394,
     396,   395,   398,   397,   399,   399,   400,   400,   400,   400,
     400,   400,   400,   402,   401,   404,   403,   406,   405,   408,
     407,   409,   409,   410,   410,   412,   411,   414,   413,   415,
     415,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   418,   417,   419,   421,   420,   422,   423,   425,
     424,   426,   426,   427,   427,   429,   428,   431,   430,   432,
     432,   433,   433,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   436,   435,   438,   437,   440,   439,
     442,   441,   444,   443,   446,   445,   448,   447,   450,   449,
     451,   451,   453,   452,   455,   454,   456,   456,   458,   457,
     459,   459,   460,   460,   461,   461,   461,   461,   461,   461,
     461,   462,   464,   463,   465,   467,   466,   468,   468,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   471,   470,
     472,   472,   472,   473,   475,   474,   476,   477,   478,   480,
     479,   481,   481,   482,   482,   482,   482,   482,   484,   483,
     486,   485,   488,   487,   490,   489,   491,   491,   492,   492,
     492,   492,   492,   492,   492,   492,   492,   492,   492,   492,
     492,   492,   492,   492,   492,   492,   492,   493,   495,   494,
     497,   496,   498,   500,   499,   501,   502,   504,   503,   505,
     505,   507,   506,   508,   509,   510,   512,   511,   513,   513,
     513,   513,   513,   515,   514,   517,   516,   519,   518,   521,
     520,   523,   522,   525,   524,   527,   526,   528,   526,   530,
     529,   531,   531,   532,   532,   534,   533,   536,   535,   538,
     537,   539,   539,   540,   542,   541,   543,   543,   545,   544,
     546,   546,   547,   547,   547,   547,   547,   547,   547,   548,
     550,   549,   552,   551,   553,   553,   555,   554,   556,   556,
     557,   557,   557,   557,   559,   558,   560,   561,   562
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     1,     3,     5,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     3,     0,     4,     0,     6,     1,
       3,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     6,     0,     6,     0,
       4,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"config-control\"",
  "\"config-databases\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"preferred-lifetime\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"shared-networks\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"client-classes\"", "\"require-client-classes\"",
  "\"test\"", "\"only-if-required\"", "\"client-class\"",
  "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"", "\"duid\"",
  "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "$@15", "value", "sub_json", "map2", "$@16", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@17", "list_content",
  "not_empty_list", "list_strings", "$@18", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@19",
  "global_objects", "global_object", "dhcp6_object", "$@20", "sub_dhcp6",
  "$@21", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "server_tag", "$@22", "interfaces_config",
  "$@23", "sub_interfaces6", "$@24", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@25", "re_detect",
  "lease_database", "$@26", "hosts_database", "$@27", "hosts_databases",
  "$@28", "database_list", "not_empty_database_list", "database", "$@29",
  "database_map_params", "database_map_param", "database_type", "$@30",
  "db_type", "user", "$@31", "password", "$@32", "host", "$@33", "port",
  "name", "$@34", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@35", "max_reconnect_tries", "keyspace", "$@36",
  "sanity_checks", "$@37", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@38", "mac_sources", "$@39", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@40",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@41",
  "hooks_libraries", "$@42", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@43",
  "sub_hooks_library", "$@44", "hooks_params", "hooks_param", "library",
  "$@45", "parameters", "$@46", "expired_leases_processing", "$@47",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@48",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@49",
  "sub_subnet6", "$@50", "subnet6_params", "subnet6_param", "subnet",
  "$@51", "interface", "$@52", "interface_id", "$@53", "client_class",
  "$@54", "require_client_classes", "$@55", "reservation_mode", "$@56",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@57",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@58", "shared_network_params", "shared_network_param",
  "option_def_list", "$@59", "sub_option_def_list", "$@60",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@61", "sub_option_def", "$@62",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@63",
  "option_def_record_types", "$@64", "space", "$@65", "option_def_space",
  "option_def_encapsulate", "$@66", "option_def_array", "option_data_list",
  "$@67", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@68", "sub_option_data", "$@69",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@70",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@71", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@72", "sub_pool6", "$@73",
  "pool_params", "pool_param", "pool_entry", "$@74", "user_context",
  "$@75", "comment", "$@76", "pd_pools_list", "$@77",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@78", "sub_pd_pool", "$@79", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@80", "pd_prefix_len", "excluded_prefix", "$@81",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@82",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@83", "sub_reservation", "$@84", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@85", "prefixes", "$@86", "duid", "$@87", "hw_address", "$@88",
  "hostname", "$@89", "flex_id_value", "$@90",
  "reservation_client_classes", "$@91", "relay", "$@92", "relay_map",
  "ip_address", "$@93", "client_classes", "$@94", "client_classes_list",
  "client_class_entry", "$@95", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@96", "only_if_required",
  "server_id", "$@97", "server_id_params", "server_id_param",
  "server_id_type", "$@98", "duid_type", "htype", "identifier", "$@99",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@100",
  "control_socket_params", "control_socket_param", "socket_type", "$@101",
  "socket_name", "$@102", "dhcp_ddns", "$@103", "sub_dhcp_ddns", "$@104",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@105", "server_ip", "$@106", "server_port",
  "sender_ip", "$@107", "sender_port", "max_queue_size", "ncr_protocol",
  "$@108", "ncr_protocol_value", "ncr_format", "$@109",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@110", "replace_client_name_value",
  "generated_prefix", "$@111", "hostname_char_set", "$@112",
  "hostname_char_replacement", "$@113", "dhcp4_json_object", "$@114",
  "dhcpddns_json_object", "$@115", "control_agent_json_object", "$@116",
  "config_control", "$@117", "$@118", "sub_config_control", "$@119",
  "config_control_params", "config_control_param", "config_databases",
  "$@120", "logging_object", "$@121", "sub_logging", "$@122",
  "logging_params", "logging_param", "loggers", "$@123", "loggers_entries",
  "logger_entry", "$@124", "logger_params", "logger_param", "debuglevel",
  "severity", "$@125", "output_options_list", "$@126",
  "output_options_list_content", "output_entry", "$@127",
  "output_params_list", "output_params", "output", "$@128", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   256,   256,   256,   257,   257,   258,   258,   259,   259,
     260,   260,   261,   261,   262,   262,   263,   263,   264,   264,
     265,   265,   266,   266,   267,   267,   268,   268,   269,   269,
     270,   270,   278,   279,   280,   281,   282,   283,   284,   287,
     292,   292,   303,   306,   307,   310,   314,   321,   321,   328,
     329,   332,   336,   343,   343,   350,   351,   354,   358,   369,
     379,   379,   394,   395,   399,   400,   401,   402,   403,   404,
     407,   407,   422,   422,   431,   432,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   469,   474,   479,   484,
     489,   494,   494,   502,   502,   513,   513,   522,   523,   526,
     527,   528,   529,   530,   533,   533,   543,   549,   549,   561,
     561,   573,   573,   583,   584,   587,   588,   591,   591,   601,
     602,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,   619,   620,   621,   622,   625,
     625,   632,   633,   634,   635,   638,   638,   646,   646,   654,
     654,   662,   667,   667,   675,   680,   685,   690,   695,   700,
     705,   710,   715,   715,   723,   728,   728,   736,   736,   746,
     747,   749,   751,   751,   769,   769,   779,   780,   783,   784,
     787,   792,   797,   797,   807,   808,   811,   812,   813,   816,
     821,   828,   828,   838,   838,   848,   849,   852,   853,   856,
     856,   866,   866,   876,   877,   878,   881,   882,   885,   885,
     893,   893,   901,   901,   912,   913,   916,   917,   918,   919,
     920,   921,   924,   929,   934,   939,   944,   949,   957,   957,
     970,   971,   974,   975,   982,   982,  1008,  1008,  1019,  1020,
    1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,
    1034,  1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,
    1046,  1046,  1054,  1054,  1062,  1062,  1070,  1070,  1078,  1078,
    1088,  1088,  1095,  1096,  1097,  1098,  1101,  1106,  1114,  1114,
    1125,  1126,  1130,  1131,  1134,  1134,  1142,  1143,  1146,  1147,
    1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,
    1158,  1159,  1160,  1161,  1162,  1169,  1169,  1182,  1182,  1191,
    1192,  1195,  1196,  1201,  1201,  1216,  1216,  1230,  1231,  1234,
    1235,  1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,
    1247,  1250,  1252,  1257,  1259,  1259,  1267,  1267,  1275,  1275,
    1283,  1285,  1285,  1293,  1302,  1302,  1314,  1315,  1320,  1321,
    1326,  1326,  1338,  1338,  1350,  1351,  1356,  1357,  1362,  1363,
    1364,  1365,  1366,  1367,  1368,  1369,  1370,  1373,  1375,  1375,
    1383,  1385,  1387,  1392,  1400,  1400,  1412,  1413,  1416,  1417,
    1420,  1420,  1430,  1430,  1439,  1440,  1443,  1444,  1445,  1446,
    1447,  1448,  1449,  1452,  1452,  1460,  1460,  1485,  1485,  1515,
    1515,  1527,  1528,  1531,  1532,  1535,  1535,  1547,  1547,  1559,
    1560,  1563,  1564,  1565,  1566,  1567,  1568,  1569,  1570,  1571,
    1572,  1573,  1576,  1576,  1584,  1589,  1589,  1597,  1602,  1610,
    1610,  1620,  1621,  1624,  1625,  1628,  1628,  1637,  1637,  1646,
    1647,  1650,  1651,  1655,  1656,  1657,  1658,  1659,  1660,  1661,
    1662,  1663,  1664,  1665,  1668,  1668,  1678,  1678,  1688,  1688,
    1696,  1696,  1704,  1704,  1712,  1712,  1720,  1720,  1733,  1733,
    1743,  1744,  1747,  1747,  1758,  1758,  1768,  1769,  1772,  1772,
    1782,  1783,  1786,  1787,  1790,  1791,  1792,  1793,  1794,  1795,
    1796,  1799,  1801,  1801,  1809,  1817,  1817,  1829,  1830,  1833,
    1834,  1835,  1836,  1837,  1838,  1839,  1840,  1841,  1844,  1844,
    1851,  1852,  1853,  1856,  1861,  1861,  1869,  1874,  1881,  1888,
    1888,  1898,  1899,  1902,  1903,  1904,  1905,  1906,  1909,  1909,
    1917,  1917,  1927,  1927,  1939,  1939,  1949,  1950,  1953,  1954,
    1955,  1956,  1957,  1958,  1959,  1960,  1961,  1962,  1963,  1964,
    1965,  1966,  1967,  1968,  1969,  1970,  1971,  1974,  1979,  1979,
    1987,  1987,  1995,  2000,  2000,  2008,  2013,  2018,  2018,  2026,
    2027,  2030,  2030,  2038,  2043,  2048,  2053,  2053,  2061,  2064,
    2067,  2070,  2073,  2079,  2079,  2087,  2087,  2095,  2095,  2105,
    2105,  2112,  2112,  2119,  2119,  2128,  2128,  2137,  2137,  2148,
    2148,  2158,  2159,  2163,  2164,  2167,  2167,  2182,  2182,  2192,
    2192,  2203,  2204,  2208,  2212,  2212,  2224,  2225,  2229,  2229,
    2237,  2238,  2241,  2242,  2243,  2244,  2245,  2246,  2247,  2250,
    2255,  2255,  2263,  2263,  2273,  2274,  2277,  2277,  2285,  2286,
    2289,  2290,  2291,  2292,  2295,  2295,  2303,  2308,  2313
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
#line 4985 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2318 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
