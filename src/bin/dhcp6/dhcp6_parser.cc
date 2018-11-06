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
      case 507: // ncr_protocol_value
      case 515: // replace_client_name_value
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
      case 507: // ncr_protocol_value
      case 515: // replace_client_name_value
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

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 171: // "integer"

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 172: // "floating point"

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 173: // "boolean"

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 191: // value

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 195: // map_value

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 247: // db_type

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 336: // hr_mode

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 472: // duid_type

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 507: // ncr_protocol_value

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 515: // replace_client_name_value

#line 248 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 507: // ncr_protocol_value
      case 515: // replace_client_name_value
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
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 285 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 304 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 333 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 337 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 355 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 359 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 385 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 408 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 636 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 195:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1618 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 858 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1685 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 988 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 257:
#line 1010 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1897 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1998 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2028 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1206 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2117 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1294 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1339 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2341 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2351 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2729 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2863 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr qc = yystack_[0].value.as< ElementPtr > ();
    ctx.stack_.back()->set("queue-control", qc);

    if (!qc->contains("queue-type")) {
        std::stringstream msg;
        msg << "'queue-type' is required: ";
        msg  << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    ctx.leave();
}
#line 3065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3076 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1958 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3097 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3142 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2045 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2057 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2083 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2086 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2089 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2098 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2108 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2133 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2138 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3425 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3434 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3473 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3503 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2206 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2215 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 640:
#line 2248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3580 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 641:
#line 2252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 651:
#line 2269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 653:
#line 2276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 654:
#line 2282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 655:
#line 2287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 658:
#line 2296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 659:
#line 2300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3653 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 666:
#line 2314 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 667:
#line 2316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 668:
#line 2322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 669:
#line 2327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 670:
#line 2332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3698 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3702 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -823;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     316,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,    64,    46,    50,    68,
      86,   119,   129,   141,   143,   145,   184,   188,   192,   198,
     202,   204,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,    46,   -64,    44,    45,    63,   206,   236,    34,
      65,    88,    53,   189,   -27,   328,    69,    57,  -823,   201,
     229,   230,   228,   248,  -823,  -823,  -823,  -823,  -823,   260,
    -823,   130,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,   262,   266,   275,   280,   286,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,   307,  -823,  -823,  -823,  -823,
     132,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,   310,  -823,   178,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,   313,   323,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,   186,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   200,
    -823,  -823,  -823,  -823,  -823,   331,  -823,   342,   346,  -823,
    -823,  -823,  -823,  -823,  -823,   277,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,   273,   318,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,   362,  -823,  -823,   378,  -823,  -823,  -823,
     381,  -823,  -823,   388,   395,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   382,   398,
    -823,  -823,  -823,  -823,   401,   415,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   288,  -823,
    -823,  -823,   418,  -823,  -823,   464,  -823,   484,   489,  -823,
    -823,   490,   491,   492,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,   295,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
     296,  -823,  -823,  -823,  -823,   315,  -823,  -823,  -823,    46,
      46,  -823,   249,   493,   495,   496,   497,   501,  -823,    44,
    -823,    57,   502,   503,   504,   505,   506,   272,   340,   341,
     343,   345,   509,   511,   513,   515,   516,   517,   518,   519,
     520,   524,   525,   526,   527,   528,   529,   530,   364,   532,
     534,   535,    45,  -823,   536,   368,    63,  -823,   538,   539,
     540,   543,   546,   380,   379,   549,   550,   551,   552,   206,
    -823,   555,   236,  -823,   557,   391,   559,   393,   394,    34,
    -823,   562,   563,   564,   567,   569,   570,   571,  -823,    65,
    -823,   572,   573,   407,   575,   576,   577,   410,  -823,    53,
     580,   413,   414,  -823,   189,   581,   584,   152,  -823,   416,
     586,   587,   421,   589,   424,   428,   590,   592,   430,   431,
     434,   593,   594,   596,   597,   328,  -823,   598,    69,  -823,
     602,    57,  -823,  -823,  -823,   604,   603,   605,    46,    46,
      46,  -823,   317,   606,   607,   608,   609,   612,  -823,  -823,
    -823,  -823,  -823,   441,   613,   614,   615,   616,   451,   617,
     619,   620,   621,   622,   623,   625,   626,   627,   628,  -823,
     629,   616,   630,  -823,   633,  -823,  -823,   634,   635,   457,
     462,   463,  -823,  -823,   151,   633,   471,   636,  -823,   472,
    -823,   474,  -823,   475,  -823,  -823,  -823,   633,   633,   633,
     476,   477,   478,   479,  -823,   480,   481,  -823,   482,   483,
     485,  -823,  -823,   486,  -823,  -823,  -823,   487,    46,  -823,
    -823,   488,   494,  -823,   498,  -823,  -823,   -52,   473,  -823,
    -823,  -823,   -24,   499,   500,   507,  -823,   649,  -823,   654,
    -823,    46,    45,    69,  -823,  -823,  -823,  -823,    57,    63,
     142,   142,   653,  -823,   655,   656,   658,  -823,  -823,  -823,
     659,   -31,    46,   396,   591,   660,   664,   666,   156,   118,
     127,  -823,   328,  -823,  -823,   667,   668,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,   -15,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,   669,   653,  -823,   335,   344,   350,   360,  -823,  -823,
    -823,  -823,   657,   674,   675,   676,   677,  -823,   678,   679,
    -823,   680,   681,   682,  -823,   363,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,   375,  -823,   683,   684,  -823,  -823,
     685,   687,  -823,  -823,   686,   690,  -823,  -823,   688,   692,
    -823,  -823,   691,   693,  -823,  -823,  -823,    73,  -823,  -823,
    -823,   694,  -823,  -823,  -823,    99,  -823,  -823,  -823,  -823,
     397,  -823,  -823,  -823,   139,  -823,  -823,   695,   696,  -823,
    -823,   697,   699,  -823,   700,   701,   702,   703,   704,   705,
     408,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
     706,   707,   708,  -823,  -823,  -823,  -823,   412,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   423,
    -823,  -823,  -823,   425,   544,  -823,   709,   710,  -823,  -823,
     711,   713,  -823,  -823,  -823,   712,  -823,  -823,   159,  -823,
     715,  -823,  -823,  -823,  -823,   714,   718,   719,   720,   548,
     553,   554,   556,   560,   723,   561,   565,   724,   566,   568,
     574,   142,  -823,  -823,   142,  -823,   653,   206,  -823,   655,
      53,  -823,   656,   189,  -823,   658,   268,  -823,   659,   -31,
    -823,  -823,   396,  -823,   726,   591,  -823,   221,   660,  -823,
      65,  -823,   664,   -27,  -823,   666,   578,   579,   582,   583,
     585,   588,   156,  -823,   729,   730,   595,   600,   601,   118,
    -823,   731,   734,   127,  -823,  -823,  -823,   735,   737,   236,
    -823,   667,    34,  -823,   668,   738,  -823,   276,   669,  -823,
    -823,   443,   599,   610,   611,  -823,  -823,  -823,  -823,  -823,
     632,  -823,  -823,   644,  -823,  -823,  -823,  -823,   426,  -823,
     427,  -823,   736,  -823,   740,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   429,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   646,  -823,
    -823,   739,  -823,  -823,  -823,  -823,  -823,   743,   742,  -823,
    -823,  -823,  -823,  -823,   744,  -823,   433,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,   383,   662,  -823,  -823,  -823,
    -823,   671,   672,  -823,  -823,   689,   436,  -823,   437,  -823,
     716,  -823,   751,  -823,  -823,  -823,  -823,  -823,   439,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   268,  -823,
    -823,   753,   650,  -823,   221,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   754,   624,
     756,   276,  -823,  -823,   721,  -823,  -823,   741,  -823,   722,
    -823,  -823,   755,  -823,  -823,   179,  -823,   180,   755,  -823,
    -823,   757,   759,   760,   459,  -823,  -823,  -823,  -823,  -823,
    -823,   761,   661,   665,   698,   180,  -823,   725,  -823,  -823,
    -823,  -823,  -823
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   116,     9,
     257,    11,   402,    13,   427,    15,   457,    17,   327,    19,
     335,    21,   372,    23,   222,    25,   556,    27,   631,    29,
     621,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     459,     0,   337,   374,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   629,   611,   613,   615,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   617,   619,
     114,   128,   130,   132,     0,     0,     0,     0,     0,   112,
     249,   325,   364,   415,   417,   298,   195,   212,   203,   188,
     494,   449,   214,   233,   515,     0,   539,   552,   554,   106,
       0,    74,    76,    77,    78,    79,    80,   105,    83,    84,
      85,    86,   102,    87,    89,    88,    93,    94,    81,    82,
      91,    92,   100,   101,   103,    90,    95,    96,    97,    98,
      99,   104,   125,     0,   124,     0,   118,   120,   121,   122,
     123,   394,   419,   281,   283,   285,     0,     0,   291,   289,
     287,   488,   280,   261,   262,   263,   264,     0,   259,   268,
     269,   270,   273,   274,   276,   271,   272,   265,   266,   278,
     279,   267,   275,   277,   413,   412,   408,   409,   407,     0,
     404,   406,   410,   411,   442,     0,   445,     0,     0,   441,
     435,   436,   434,   439,   440,     0,   429,   431,   432,   437,
     438,   433,   486,   474,   476,   478,   480,   482,   484,   473,
     470,   471,   472,     0,   460,   461,   465,   466,   463,   467,
     468,   469,   464,     0,   354,   173,     0,   358,   356,   361,
       0,   350,   351,     0,   338,   339,   341,   353,   342,   343,
     344,   360,   345,   346,   347,   348,   349,   388,     0,     0,
     386,   387,   390,   391,     0,   375,   376,   378,   379,   380,
     381,   382,   383,   384,   385,   229,   231,   226,     0,   224,
     227,   228,     0,   580,   582,     0,   585,     0,     0,   589,
     593,     0,     0,     0,   598,   605,   607,   609,   578,   576,
     577,     0,   558,   560,   561,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   574,   575,   636,
       0,   633,   635,   627,   626,     0,   623,   625,    48,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    59,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,     0,     0,   403,     0,     0,     0,     0,     0,     0,
     428,     0,     0,     0,     0,     0,     0,     0,   458,     0,
     328,     0,     0,     0,     0,     0,     0,     0,   336,     0,
       0,     0,     0,   373,     0,     0,     0,     0,   223,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   557,     0,     0,   632,
       0,     0,   622,    52,    45,     0,     0,     0,     0,     0,
       0,    63,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   538,
       0,     0,     0,    75,     0,   127,   119,     0,     0,     0,
       0,     0,   296,   297,     0,     0,     0,     0,   260,     0,
     405,     0,   444,     0,   447,   448,   430,     0,     0,     0,
       0,     0,     0,     0,   462,     0,     0,   352,     0,     0,
       0,   363,   340,     0,   392,   393,   377,     0,     0,   225,
     579,     0,     0,   584,     0,   587,   588,     0,     0,   595,
     596,   597,     0,     0,     0,     0,   559,     0,   634,     0,
     624,     0,     0,     0,   612,   614,   616,   618,     0,     0,
       0,     0,   134,   113,   251,   329,   366,    42,   416,   418,
     300,     0,    49,     0,     0,     0,   451,   216,     0,     0,
       0,   553,     0,    53,   126,   396,   421,   282,   284,   286,
     293,   294,   295,   292,   290,   288,     0,   414,   443,   446,
     487,   475,   477,   479,   481,   483,   485,   355,   174,   359,
     357,   362,   389,   230,   232,   581,   583,   586,   591,   592,
     590,   594,   600,   601,   602,   603,   604,   599,   606,   608,
     610,     0,   134,    46,     0,     0,     0,     0,   160,   166,
     168,   170,     0,     0,     0,     0,     0,   183,     0,     0,
     186,     0,     0,     0,   159,     0,   140,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   154,   155,   156,
     157,   152,   153,   158,     0,   138,     0,   135,   136,   255,
       0,   252,   253,   333,     0,   330,   331,   370,     0,   367,
     368,   304,     0,   301,   302,   201,   202,     0,   197,   199,
     200,     0,   210,   211,   207,     0,   205,   208,   209,   193,
       0,   190,   192,   498,     0,   496,   455,     0,   452,   453,
     220,     0,   217,   218,     0,     0,     0,     0,     0,     0,
       0,   235,   237,   238,   239,   240,   241,   242,   528,   534,
       0,     0,     0,   527,   524,   525,   526,     0,   517,   519,
     522,   520,   521,   523,   548,   550,   547,   545,   546,     0,
     541,   543,   544,     0,    55,   400,     0,   397,   398,   425,
       0,   422,   423,   492,   491,     0,   490,   640,     0,   638,
       0,    71,   630,   620,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   131,     0,   133,     0,     0,   250,     0,
     337,   326,     0,   374,   365,     0,     0,   299,     0,     0,
     196,   213,     0,   204,     0,     0,   189,   500,     0,   495,
     459,   450,     0,     0,   215,     0,     0,     0,     0,     0,
       0,     0,     0,   234,     0,     0,     0,     0,     0,     0,
     516,     0,     0,     0,   540,   555,    57,     0,    56,     0,
     395,     0,     0,   420,     0,     0,   489,     0,     0,   637,
     628,     0,     0,     0,     0,   172,   175,   176,   177,   178,
       0,   185,   179,     0,   180,   181,   182,   141,     0,   137,
       0,   254,     0,   332,     0,   369,   324,   319,   321,   312,
     313,   308,   309,   310,   311,   317,   318,   316,   320,     0,
     306,   314,   322,   323,   315,   303,   198,   206,     0,   191,
     512,     0,   510,   511,   507,   508,   509,     0,   501,   502,
     504,   505,   506,   497,     0,   454,     0,   219,   243,   244,
     245,   246,   247,   248,   236,     0,     0,   533,   536,   537,
     518,     0,     0,   542,    54,     0,     0,   399,     0,   424,
       0,   654,     0,   652,   650,   644,   648,   649,     0,   642,
     646,   647,   645,   639,   162,   163,   164,   165,   161,   167,
     169,   171,   184,   187,   139,   256,   334,   371,     0,   305,
     194,     0,     0,   499,     0,   456,   221,   530,   531,   532,
     529,   535,   549,   551,    58,   401,   426,   493,     0,     0,
       0,     0,   641,   307,     0,   514,   503,     0,   651,     0,
     643,   513,     0,   653,   658,     0,   656,     0,     0,   655,
     666,     0,     0,     0,     0,   660,   662,   663,   664,   665,
     657,     0,     0,     0,     0,     0,   659,     0,   668,   669,
     670,   661,   667
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,    14,  -823,  -447,
    -823,   167,  -823,  -823,  -823,  -823,   162,  -823,  -347,  -823,
    -823,  -823,   -74,  -823,  -823,  -823,   329,  -823,  -823,  -823,
    -823,   176,   373,   -70,   -58,   -55,   -38,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,   185,   372,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,   111,  -823,   -59,  -823,  -577,
     -51,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,   -46,  -823,  -607,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   -39,
    -823,  -823,  -823,  -823,  -823,   -30,  -600,  -823,  -823,  -823,
    -823,   -16,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
     -45,  -823,  -823,  -823,   -26,   399,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,   -44,  -823,  -823,  -823,  -823,  -823,  -823,
    -822,  -823,  -823,  -823,    -1,  -823,  -823,  -823,     3,   432,
    -823,  -823,  -818,  -823,  -816,  -823,   -34,  -823,   -32,  -823,
    -808,  -823,  -823,  -823,  -807,  -823,  -823,  -823,  -823,    -5,
    -823,  -823,  -174,   779,  -823,  -823,  -823,  -823,  -823,    10,
    -823,  -823,  -823,    13,  -823,   417,  -823,   -42,  -823,  -823,
    -823,  -823,  -823,   -40,  -823,  -823,  -823,  -823,  -823,   -12,
    -823,  -823,  -823,     9,  -823,  -823,  -823,    18,  -823,   419,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,   -29,  -823,  -823,  -823,   -25,   453,  -823,  -823,   -62,
    -823,   -50,  -823,  -823,  -823,  -823,  -823,   -28,  -823,  -823,
    -823,   -23,   448,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
     -35,  -823,  -823,  -823,     6,  -823,  -823,  -823,    11,  -823,
     444,   244,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -806,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,    16,  -823,  -823,  -823,  -152,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,    -4,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,     0,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   267,
     422,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -346,
     420,  -823,  -823,  -823,  -823,  -823,  -823,   301,   435,  -823,
    -823,  -823,   -20,  -823,  -823,  -155,  -823,  -823,  -823,  -823,
    -823,  -823,  -170,  -823,  -823,  -186,  -823,  -823,  -823,  -823,
    -823
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   608,    92,    93,    43,    72,    89,    90,   624,   804,
     897,   898,   354,    45,    74,   101,   102,   103,   363,    47,
      75,   140,   141,   142,   143,   144,   145,   146,   147,   382,
     148,   373,    49,    76,   175,   176,   177,   404,   178,   149,
     374,   150,   375,   151,   376,   716,   717,   718,   844,   695,
     696,   697,   825,  1018,   698,   826,   699,   827,   700,   828,
     701,   702,   442,   703,   704,   705,   706,   707,   708,   709,
     710,   711,   834,   712,   713,   837,   152,   392,   750,   751,
     752,   864,   153,   389,   737,   738,   739,   740,   154,   391,
     745,   746,   747,   748,   155,   390,   156,   395,   761,   762,
     763,   873,    65,    84,   308,   309,   310,   455,   311,   456,
     157,   396,   770,   771,   772,   773,   774,   775,   776,   777,
     158,   383,   720,   721,   722,   847,    51,    77,   197,   198,
     199,   410,   200,   411,   201,   412,   202,   417,   203,   416,
     204,   415,   633,   205,   206,   159,   388,   732,   733,   734,
     856,   949,   950,   160,   384,    59,    81,   724,   725,   726,
     850,    61,    82,   273,   274,   275,   276,   277,   278,   279,
     441,   280,   445,   281,   444,   282,   283,   446,   284,   161,
     385,   728,   729,   730,   853,    63,    83,   294,   295,   296,
     297,   298,   450,   299,   300,   301,   302,   208,   408,   806,
     807,   808,   899,    53,    78,   219,   220,   221,   421,   162,
     386,   163,   387,   211,   409,   810,   811,   812,   902,    55,
      79,   235,   236,   237,   424,   238,   239,   426,   240,   241,
     164,   394,   757,   758,   759,   870,    57,    80,   253,   254,
     255,   256,   432,   257,   433,   258,   434,   259,   435,   260,
     436,   261,   437,   262,   431,   213,   418,   815,   816,   905,
     165,   393,   754,   755,   867,   967,   968,   969,   970,   971,
    1031,   972,   166,   397,   787,   788,   789,   884,  1040,   790,
     791,   885,   792,   793,   167,   168,   399,   799,   800,   801,
     891,   802,   892,   169,   400,   170,   401,    67,    85,   331,
     332,   333,   334,   460,   335,   461,   336,   337,   463,   338,
     339,   340,   466,   660,   341,   467,   342,   343,   344,   345,
     471,   667,   346,   472,   347,   473,   348,   474,   104,   365,
     105,   366,   106,   367,   171,   371,   372,    71,    87,   355,
     356,   357,   480,   107,   364,    69,    86,   350,   351,   352,
     477,   818,   819,   907,  1008,  1009,  1010,  1011,  1050,  1012,
    1048,  1065,  1066,  1067,  1074,  1075,  1076,  1081,  1077,  1078,
    1079
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
     100,   139,   174,   192,   215,   229,   249,   193,   271,   290,
     307,   328,   784,   744,   179,   209,   222,   233,   251,   194,
     285,   303,   195,   329,   714,   492,   180,   210,   223,   234,
     252,    40,   286,   304,   942,   330,   272,   291,   943,   196,
     944,   292,   212,   293,   216,   230,   217,   231,   947,   948,
     954,    33,   108,    34,    94,    35,   109,    44,   110,   735,
     607,   111,   112,   113,    32,   207,   218,   232,   250,   353,
     305,   306,   264,   243,   607,    46,   859,   172,   173,   860,
     813,   122,   658,   659,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    48,   224,   225,   226,   227,   228,   123,
     124,   265,   862,   266,   267,   863,    91,   268,   269,   270,
     123,   124,   122,   662,   663,   664,   665,   189,   123,   124,
     190,   125,   126,   127,   128,   129,    50,   130,   123,   124,
     123,   124,   131,   369,   121,   402,    52,   778,   370,   736,
     403,   132,   868,    99,   133,   869,   683,   242,    54,   666,
      56,   134,    58,   243,   244,   245,   246,   247,   248,   135,
     136,   678,   908,   137,   138,   909,   679,   680,   681,   682,
     683,   684,   685,   686,   687,   688,   689,   690,   691,   692,
     693,   406,  1068,   123,   124,  1069,   407,    95,   634,   419,
     265,    60,   123,   124,   420,    62,    96,    97,    98,    64,
     640,   641,   642,   422,    99,    66,   942,   358,   423,    68,
     943,    70,   944,   349,    99,    99,    36,    37,    38,    39,
     947,   948,   954,    99,   630,   631,   632,    99,   779,   780,
     781,   782,   359,    99,   360,    99,   361,   265,   287,   266,
     267,   288,   289,   794,   795,   114,   115,   116,   117,   305,
     306,   362,   676,   122,   123,   124,   764,   765,   766,   767,
     768,   769,   744,   181,   368,   182,   377,   928,   122,   265,
     378,   123,   124,   183,   184,   185,   186,   187,   188,   379,
     429,   438,   784,   122,   380,   430,   123,   124,    99,   189,
     381,   457,   190,   131,   214,   100,   458,    99,   475,   478,
     191,   123,   124,   476,   479,   960,   961,   114,   115,   116,
     117,   398,    99,   120,   405,   122,   265,   413,   481,   189,
     481,   439,   190,   482,   265,   597,  1070,   414,   139,  1071,
    1072,  1073,   174,   123,   124,   425,   184,   185,   402,   187,
     188,   123,   124,   821,   179,   192,   427,   478,   215,   193,
     428,   189,   822,   481,   190,   229,   180,   209,   823,    99,
     222,   194,   191,   406,   195,   249,   841,   233,   824,   210,
     440,   842,   223,   483,   484,   271,    99,   251,   841,   234,
     290,   196,   443,   843,   212,   447,   451,   285,   216,   252,
     217,    99,   303,   123,   124,   230,   448,   231,   449,   286,
     865,   328,   452,   272,   304,   866,    99,   207,   291,   453,
     218,   882,   292,   329,   293,   889,   883,   232,   454,   485,
     890,  1001,   459,  1002,  1003,   330,   893,   250,   475,   841,
     419,   894,  1028,   895,  1024,  1025,   457,  1029,    99,   422,
     429,  1036,  1051,   498,  1045,  1046,    99,  1052,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,  1085,  1014,  1015,  1016,  1017,  1086,   462,   326,
     327,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,   735,   742,   464,   743,
    1037,  1038,  1039,   465,   468,   469,   470,   486,    99,   487,
     488,   489,   594,   595,   596,   490,   493,   494,   495,   496,
     497,   499,   500,   503,   501,   504,   502,   505,   139,   506,
     507,   508,   509,   510,   511,   174,   694,   694,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   179,   521,   522,
     524,   525,   527,   528,   529,   783,   796,   530,   328,   180,
     531,   532,   533,   534,   535,   536,   537,   785,   797,   539,
     329,   541,   542,   543,   544,   545,   547,   548,   549,   786,
     798,   550,   330,   551,   552,   553,   555,   556,   557,   558,
     559,   560,   654,   561,   563,   567,   564,   565,   568,   570,
     571,   572,   573,   574,   577,   575,   578,   582,   583,   576,
     584,   585,   587,   579,   580,   673,   589,   581,   591,   661,
     592,   603,   593,   598,   599,   600,   601,   602,   604,   605,
     606,   609,   610,    34,   611,   612,   613,   627,   615,   614,
     616,   617,   628,   629,   618,   619,   620,   622,   623,   625,
     626,   635,   637,   636,   638,   639,   643,   644,   645,   646,
     647,   648,   649,   650,   671,   651,   652,   653,   655,   672,
     715,   829,   719,   723,   656,   727,   731,   753,   657,   668,
     669,   756,   749,   760,   805,   809,   817,   670,   830,   831,
     832,   833,   835,   836,   838,   839,   840,   846,   621,   845,
     849,   848,   851,   852,   854,   855,   858,   857,   491,   872,
     861,   871,   875,   874,   876,   877,   878,   879,   880,   881,
     886,   887,   888,   901,   896,   900,   904,   903,   911,   915,
     906,   910,   912,   913,   914,   917,   916,   920,   923,   918,
     958,   919,   921,   985,   986,   991,   922,   924,   992,   925,
     995,   994,  1000,  1032,  1026,  1034,  1062,   926,  1027,   978,
     979,  1033,  1035,   980,   981,  1049,   982,  1054,  1057,   983,
    1059,  1082,  1064,  1083,  1084,  1087,   987,   694,   674,  1019,
     694,   988,   989,   192,   741,   523,   271,   193,   526,   290,
    1020,  1021,   936,   820,   677,   209,   937,   929,   285,   194,
     927,   303,   195,   962,   952,  1058,   249,   210,   938,   307,
     286,   939,  1022,   304,   272,   965,   953,   291,   251,   196,
     941,   292,   212,   293,  1023,   783,  1030,   966,   940,   796,
     252,   963,   945,  1055,   946,   215,   959,   785,   229,   956,
     977,   797,  1041,  1004,  1088,   207,  1089,   222,   984,   786,
     233,  1042,  1043,   798,   951,  1006,   957,   976,   931,   223,
     930,   538,   234,   955,  1053,   964,   569,  1007,   250,  1044,
     263,  1005,   933,   932,   935,   216,   562,   217,   230,  1090,
     231,   934,   997,   566,   996,   540,   999,   546,   975,   998,
     814,   974,  1056,   554,   973,   990,  1047,   218,  1013,   803,
     232,  1061,  1063,   993,   675,  1092,  1060,   586,  1080,  1091,
       0,   590,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   588,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   936,     0,     0,     0,   937,     0,
     962,     0,     0,     0,     0,     0,   952,     0,     0,     0,
     938,     0,   965,   939,     0,     0,     0,  1004,   953,     0,
       0,     0,   941,     0,   966,     0,     0,     0,   963,  1006,
     940,     0,     0,     0,   945,     0,   946,     0,     0,     0,
       0,  1007,     0,     0,     0,  1005,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   951,     0,     0,     0,
       0,     0,   964
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,   619,   613,    76,    77,    78,    79,    80,    77,
      82,    83,    77,    85,   601,   371,    76,    77,    78,    79,
      80,    17,    82,    83,   856,    85,    82,    83,   856,    77,
     856,    83,    77,    83,    78,    79,    78,    79,   856,   856,
     856,     5,     7,     7,    10,     9,    11,     7,    13,    90,
     507,    16,    17,    18,     0,    77,    78,    79,    80,    12,
      97,    98,    19,    88,   521,     7,     3,    14,    15,     6,
      95,    47,   134,   135,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     7,    60,    61,    62,    63,    64,    65,
      66,    48,     3,    50,    51,     6,   170,    54,    55,    56,
      65,    66,    47,   137,   138,   139,   140,    83,    65,    66,
      86,    76,    77,    78,    79,    80,     7,    82,    65,    66,
      65,    66,    87,     3,    46,     3,     7,    19,     8,   170,
       8,    96,     3,   170,    99,     6,    28,    82,     7,   173,
       7,   106,     7,    88,    89,    90,    91,    92,    93,   114,
     115,    19,     3,   118,   119,     6,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,     3,     3,    65,    66,     6,     8,   143,   535,     3,
      48,     7,    65,    66,     8,     7,   152,   153,   154,     7,
     547,   548,   549,     3,   170,     7,  1028,     6,     8,     7,
    1028,     7,  1028,   144,   170,   170,   170,   171,   172,   173,
    1028,  1028,  1028,   170,    73,    74,    75,   170,   110,   111,
     112,   113,     3,   170,     4,   170,     8,    48,    49,    50,
      51,    52,    53,   116,   117,    39,    40,    41,    42,    97,
      98,     3,   598,    47,    65,    66,   100,   101,   102,   103,
     104,   105,   862,    57,     4,    59,     4,   844,    47,    48,
       4,    65,    66,    67,    68,    69,    70,    71,    72,     4,
       3,     8,   889,    47,     4,     8,    65,    66,   170,    83,
       4,     3,    86,    87,    58,   369,     8,   170,     3,     3,
      94,    65,    66,     8,     8,    84,    85,    39,    40,    41,
      42,     4,   170,    45,     4,    47,    48,     4,     3,    83,
       3,     3,    86,     8,    48,     8,   146,     4,   402,   149,
     150,   151,   406,    65,    66,     4,    68,    69,     3,    71,
      72,    65,    66,     8,   406,   419,     4,     3,   422,   419,
       4,    83,     8,     3,    86,   429,   406,   419,     8,   170,
     422,   419,    94,     3,   419,   439,     3,   429,     8,   419,
       8,     8,   422,   359,   360,   449,   170,   439,     3,   429,
     454,   419,     4,     8,   419,     4,     4,   449,   422,   439,
     422,   170,   454,    65,    66,   429,     8,   429,     3,   449,
       3,   475,     4,   449,   454,     8,   170,   419,   454,     8,
     422,     3,   454,   475,   454,     3,     8,   429,     3,   170,
       8,   145,     4,   147,   148,   475,     3,   439,     3,     3,
       3,     8,     3,     8,     8,     8,     3,     8,   170,     3,
       3,     8,     3,   171,     8,     8,   170,     8,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,     3,    20,    21,    22,    23,     8,     4,   141,
     142,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,    90,    91,     4,    93,
     107,   108,   109,     4,     4,     4,     4,     4,   170,     4,
       4,     4,   488,   489,   490,     4,     4,     4,     4,     4,
       4,   171,   171,     4,   171,     4,   171,     4,   592,     4,
       4,     4,     4,     4,     4,   599,   600,   601,     4,     4,
       4,     4,     4,     4,     4,   171,     4,   599,     4,     4,
       4,   173,     4,     4,     4,   619,   620,     4,   622,   599,
       4,   171,   173,     4,     4,     4,     4,   619,   620,     4,
     622,     4,   171,     4,   171,   171,     4,     4,     4,   619,
     620,     4,   622,     4,     4,     4,     4,     4,   171,     4,
       4,     4,   568,   173,     4,     4,   173,   173,     4,   173,
       4,     4,   171,     4,     4,   171,     4,     4,     4,   171,
       4,     4,     4,   173,   173,   591,     4,   173,     4,   136,
       7,   170,     7,     7,     7,     7,     7,     5,     5,     5,
       5,   170,     5,     7,     5,     5,     5,   170,     5,     7,
       5,     5,   170,   170,     7,     7,     7,     7,     5,     5,
       5,   170,   170,     7,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,     5,   170,   170,   170,   170,     5,
       7,     4,     7,     7,   170,     7,     7,     7,   170,   170,
     170,     7,    81,     7,     7,     7,     7,   170,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   521,     6,
       3,     6,     6,     3,     6,     3,     3,     6,   369,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   170,     6,     3,     6,     4,   171,
       8,     6,     4,     4,     4,   171,   173,     4,     4,   173,
       4,   171,   171,     4,     4,     4,   171,   171,     4,   171,
       3,     6,     4,     4,     8,     3,     5,   173,     8,   171,
     171,     8,     8,   171,   171,     4,   171,     4,     4,   171,
       4,     4,     7,     4,     4,     4,   171,   841,   592,   170,
     844,   171,   171,   847,   612,   402,   850,   847,   406,   853,
     170,   170,   856,   672,   599,   847,   856,   846,   850,   847,
     841,   853,   847,   867,   856,   171,   870,   847,   856,   873,
     850,   856,   170,   853,   850,   867,   856,   853,   870,   847,
     856,   853,   847,   853,   170,   889,   170,   867,   856,   893,
     870,   867,   856,   173,   856,   899,   865,   889,   902,   859,
     875,   893,   170,   907,   173,   847,   171,   899,   882,   889,
     902,   170,   170,   893,   856,   907,   862,   873,   849,   899,
     847,   419,   902,   858,  1028,   867,   457,   907,   870,   170,
      81,   907,   852,   850,   855,   899,   449,   899,   902,   171,
     902,   853,   901,   454,   899,   422,   904,   429,   872,   902,
     636,   870,  1034,   439,   868,   889,   170,   899,   908,   622,
     902,   170,   170,   893,   593,   170,  1051,   475,  1068,  1085,
      -1,   481,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   478,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1028,    -1,    -1,    -1,  1028,    -1,
    1034,    -1,    -1,    -1,    -1,    -1,  1028,    -1,    -1,    -1,
    1028,    -1,  1034,  1028,    -1,    -1,    -1,  1051,  1028,    -1,
      -1,    -1,  1028,    -1,  1034,    -1,    -1,    -1,  1034,  1051,
    1028,    -1,    -1,    -1,  1028,    -1,  1028,    -1,    -1,    -1,
      -1,  1051,    -1,    -1,    -1,  1051,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1028,    -1,    -1,    -1,
      -1,    -1,  1034
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
       7,   355,     7,   379,     7,   296,     7,   491,     7,   539,
       7,   531,   199,   194,   208,   214,   227,   321,   398,   414,
     431,   350,   356,   380,   297,   492,   540,   532,   191,   200,
     201,   170,   196,   197,    10,   143,   152,   153,   154,   170,
     206,   209,   210,   211,   522,   524,   526,   537,     7,    11,
      13,    16,    17,    18,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    65,    66,    76,    77,    78,    79,    80,
      82,    87,    96,    99,   106,   114,   115,   118,   119,   206,
     215,   216,   217,   218,   219,   220,   221,   222,   224,   233,
     235,   237,   270,   276,   282,   288,   290,   304,   314,   339,
     347,   373,   403,   405,   424,   454,   466,   478,   479,   487,
     489,   528,    14,    15,   206,   228,   229,   230,   232,   403,
     405,    57,    59,    67,    68,    69,    70,    71,    72,    83,
      86,    94,   206,   217,   218,   219,   220,   322,   323,   324,
     326,   328,   330,   332,   334,   337,   338,   373,   391,   403,
     405,   407,   424,   449,    58,   206,   330,   332,   373,   399,
     400,   401,   403,   405,    60,    61,    62,    63,    64,   206,
     330,   332,   373,   403,   405,   415,   416,   417,   419,   420,
     422,   423,    82,    88,    89,    90,    91,    92,    93,   206,
     373,   403,   405,   432,   433,   434,   435,   437,   439,   441,
     443,   445,   447,   347,    19,    48,    50,    51,    54,    55,
      56,   206,   255,   357,   358,   359,   360,   361,   362,   363,
     365,   367,   369,   370,   372,   403,   405,    49,    52,    53,
     206,   255,   361,   367,   381,   382,   383,   384,   385,   387,
     388,   389,   390,   403,   405,    97,    98,   206,   298,   299,
     300,   302,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   141,   142,   206,   403,
     405,   493,   494,   495,   496,   498,   500,   501,   503,   504,
     505,   508,   510,   511,   512,   513,   516,   518,   520,   144,
     541,   542,   543,    12,   206,   533,   534,   535,     6,     3,
       4,     8,     3,   212,   538,   523,   525,   527,     4,     3,
       8,   529,   530,   225,   234,   236,   238,     4,     4,     4,
       4,     4,   223,   315,   348,   374,   404,   406,   340,   277,
     289,   283,   271,   455,   425,   291,   305,   467,     4,   480,
     488,   490,     3,     8,   231,     4,     3,     8,   392,   408,
     325,   327,   329,     4,     4,   335,   333,   331,   450,     3,
       8,   402,     3,     8,   418,     4,   421,     4,     4,     3,
       8,   448,   436,   438,   440,   442,   444,   446,     8,     3,
       8,   364,   256,     4,   368,   366,   371,     4,     8,     3,
     386,     4,     4,     8,     3,   301,   303,     3,     8,     4,
     497,   499,     4,   502,     4,     4,   506,   509,     4,     4,
       4,   514,   517,   519,   521,     3,     8,   544,     3,     8,
     536,     3,     8,   191,   191,   170,     4,     4,     4,     4,
       4,   210,   533,     4,     4,     4,     4,     4,   171,   171,
     171,   171,   171,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   171,
       4,     4,     4,   216,     4,   173,   229,     4,     4,     4,
       4,     4,   171,   173,     4,     4,     4,     4,   323,     4,
     400,     4,   171,     4,   171,   171,   416,     4,     4,     4,
       4,     4,     4,     4,   434,     4,     4,   171,     4,     4,
       4,   173,   359,     4,   173,   173,   383,     4,     4,   299,
     173,     4,     4,   171,     4,   171,   171,     4,     4,   173,
     173,   173,     4,     4,     4,     4,   494,     4,   542,     4,
     534,     4,     7,     7,   191,   191,   191,     8,     7,     7,
       7,     7,     5,   170,     5,     5,     5,   193,   195,   170,
       5,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,   195,     7,     5,   202,     5,     5,   170,   170,   170,
      73,    74,    75,   336,   202,   170,     7,   170,   170,   170,
     202,   202,   202,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   191,   170,   170,   170,   134,   135,
     507,   136,   137,   138,   139,   140,   173,   515,   170,   170,
     170,     5,     5,   191,   215,   541,   533,   228,    19,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   206,   243,   244,   245,   248,   250,
     252,   254,   255,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   267,   268,   243,     7,   239,   240,   241,     7,
     316,   317,   318,     7,   351,   352,   353,     7,   375,   376,
     377,     7,   341,   342,   343,    90,   170,   278,   279,   280,
     281,   200,    91,    93,   280,   284,   285,   286,   287,    81,
     272,   273,   274,     7,   456,   457,     7,   426,   427,   428,
       7,   292,   293,   294,   100,   101,   102,   103,   104,   105,
     306,   307,   308,   309,   310,   311,   312,   313,    19,   110,
     111,   112,   113,   206,   257,   403,   405,   468,   469,   470,
     473,   474,   476,   477,   116,   117,   206,   403,   405,   481,
     482,   483,   485,   493,   203,     7,   393,   394,   395,     7,
     409,   410,   411,    95,   435,   451,   452,     7,   545,   546,
     239,     8,     8,     8,     8,   246,   249,   251,   253,     4,
       4,     4,     4,     4,   266,     4,     4,   269,     4,     4,
       4,     3,     8,     8,   242,     6,     3,   319,     6,     3,
     354,     6,     3,   378,     6,     3,   344,     6,     3,     3,
       6,     6,     3,     6,   275,     3,     8,   458,     3,     6,
     429,     6,     3,   295,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   471,   475,     4,     4,     4,     3,
       8,   484,   486,     3,     8,     8,   170,   204,   205,   396,
       6,     3,   412,     6,     3,   453,     8,   547,     3,     6,
       6,     4,     4,     4,     4,   171,   173,   171,   173,   171,
       4,   171,   171,     4,   171,   171,   173,   244,   243,   241,
     322,   318,   357,   353,   381,   377,   206,   217,   218,   219,
     220,   255,   314,   326,   328,   330,   332,   334,   338,   345,
     346,   373,   403,   405,   449,   343,   279,   285,     4,   273,
      84,    85,   206,   255,   373,   403,   405,   459,   460,   461,
     462,   463,   465,   457,   432,   428,   298,   294,   171,   171,
     171,   171,   171,   171,   307,     4,     4,   171,   171,   171,
     469,     4,     4,   482,     6,     3,   399,   395,   415,   411,
       4,   145,   147,   148,   206,   255,   403,   405,   548,   549,
     550,   551,   553,   546,    20,    21,    22,    23,   247,   170,
     170,   170,   170,   170,     8,     8,     8,     8,     3,     8,
     170,   464,     4,     8,     3,     8,     8,   107,   108,   109,
     472,   170,   170,   170,   170,     8,     8,   170,   554,     4,
     552,     3,     8,   346,     4,   173,   461,     4,   171,     4,
     549,   170,     5,   170,     7,   555,   556,   557,     3,     6,
     146,   149,   150,   151,   558,   559,   560,   562,   563,   564,
     556,   561,     4,     4,     4,     3,     8,     4,   173,   171,
     171,   559,   170
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
     216,   216,   216,   216,   216,   216,   216,   217,   218,   219,
     220,   221,   223,   222,   225,   224,   227,   226,   228,   228,
     229,   229,   229,   229,   229,   231,   230,   232,   234,   233,
     236,   235,   238,   237,   239,   239,   240,   240,   242,   241,
     243,   243,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     246,   245,   247,   247,   247,   247,   249,   248,   251,   250,
     253,   252,   254,   256,   255,   257,   258,   259,   260,   261,
     262,   263,   264,   266,   265,   267,   269,   268,   271,   270,
     272,   272,   273,   275,   274,   277,   276,   278,   278,   279,
     279,   280,   281,   283,   282,   284,   284,   285,   285,   285,
     286,   287,   289,   288,   291,   290,   292,   292,   293,   293,
     295,   294,   297,   296,   298,   298,   298,   299,   299,   301,
     300,   303,   302,   305,   304,   306,   306,   307,   307,   307,
     307,   307,   307,   308,   309,   310,   311,   312,   313,   315,
     314,   316,   316,   317,   317,   319,   318,   321,   320,   322,
     322,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   325,   324,   327,   326,   329,   328,   331,   330,   333,
     332,   335,   334,   336,   336,   336,   337,   338,   340,   339,
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
     486,   485,   488,   487,   490,   489,   492,   491,   493,   493,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   495,
     497,   496,   499,   498,   500,   502,   501,   503,   504,   506,
     505,   507,   507,   509,   508,   510,   511,   512,   514,   513,
     515,   515,   515,   515,   515,   517,   516,   519,   518,   521,
     520,   523,   522,   525,   524,   527,   526,   529,   528,   530,
     528,   532,   531,   533,   533,   534,   534,   536,   535,   538,
     537,   540,   539,   541,   541,   542,   544,   543,   545,   545,
     547,   546,   548,   548,   549,   549,   549,   549,   549,   549,
     549,   550,   552,   551,   554,   553,   555,   555,   557,   556,
     558,   558,   559,   559,   559,   559,   561,   560,   562,   563,
     564
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
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     3,     0,     4,     0,     6,
       1,     3,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
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
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     0,     6,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
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
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"queue-control\"",
  "\"dhcp-ddns\"", "\"enable-updates\"", "\"qualifying-suffix\"",
  "\"server-ip\"", "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
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
  "socket_name", "$@102", "queue_control", "$@103", "dhcp_ddns", "$@104",
  "sub_dhcp_ddns", "$@105", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@106", "server_ip", "$@107",
  "server_port", "sender_ip", "$@108", "sender_port", "max_queue_size",
  "ncr_protocol", "$@109", "ncr_protocol_value", "ncr_format", "$@110",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@111", "replace_client_name_value",
  "generated_prefix", "$@112", "hostname_char_set", "$@113",
  "hostname_char_replacement", "$@114", "dhcp4_json_object", "$@115",
  "dhcpddns_json_object", "$@116", "control_agent_json_object", "$@117",
  "config_control", "$@118", "$@119", "sub_config_control", "$@120",
  "config_control_params", "config_control_param", "config_databases",
  "$@121", "logging_object", "$@122", "sub_logging", "$@123",
  "logging_params", "logging_param", "loggers", "$@124", "loggers_entries",
  "logger_entry", "$@125", "logger_params", "logger_param", "debuglevel",
  "severity", "$@126", "output_options_list", "$@127",
  "output_options_list_content", "output_entry", "$@128",
  "output_params_list", "output_params", "output", "$@129", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   257,   257,   257,   258,   258,   259,   259,   260,   260,
     261,   261,   262,   262,   263,   263,   264,   264,   265,   265,
     266,   266,   267,   267,   268,   268,   269,   269,   270,   270,
     271,   271,   279,   280,   281,   282,   283,   284,   285,   288,
     293,   293,   304,   307,   308,   311,   315,   322,   322,   329,
     330,   333,   337,   344,   344,   351,   352,   355,   359,   370,
     380,   380,   395,   396,   400,   401,   402,   403,   404,   405,
     408,   408,   423,   423,   432,   433,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   471,   476,   481,
     486,   491,   496,   496,   504,   504,   515,   515,   524,   525,
     528,   529,   530,   531,   532,   535,   535,   545,   551,   551,
     563,   563,   575,   575,   585,   586,   589,   590,   593,   593,
     603,   604,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     627,   627,   634,   635,   636,   637,   640,   640,   648,   648,
     656,   656,   664,   669,   669,   677,   682,   687,   692,   697,
     702,   707,   712,   717,   717,   725,   730,   730,   738,   738,
     748,   749,   751,   753,   753,   771,   771,   781,   782,   785,
     786,   789,   794,   799,   799,   809,   810,   813,   814,   815,
     818,   823,   830,   830,   840,   840,   850,   851,   854,   855,
     858,   858,   868,   868,   878,   879,   880,   883,   884,   887,
     887,   895,   895,   903,   903,   914,   915,   918,   919,   920,
     921,   922,   923,   926,   931,   936,   941,   946,   951,   959,
     959,   972,   973,   976,   977,   984,   984,  1010,  1010,  1021,
    1022,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,
    1045,  1048,  1048,  1056,  1056,  1064,  1064,  1072,  1072,  1080,
    1080,  1090,  1090,  1097,  1098,  1099,  1102,  1107,  1115,  1115,
    1126,  1127,  1131,  1132,  1135,  1135,  1143,  1144,  1147,  1148,
    1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
    1159,  1160,  1161,  1162,  1163,  1170,  1170,  1183,  1183,  1192,
    1193,  1196,  1197,  1202,  1202,  1217,  1217,  1231,  1232,  1235,
    1236,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1251,  1253,  1258,  1260,  1260,  1268,  1268,  1276,  1276,
    1284,  1286,  1286,  1294,  1303,  1303,  1315,  1316,  1321,  1322,
    1327,  1327,  1339,  1339,  1351,  1352,  1357,  1358,  1363,  1364,
    1365,  1366,  1367,  1368,  1369,  1370,  1371,  1374,  1376,  1376,
    1384,  1386,  1388,  1393,  1401,  1401,  1413,  1414,  1417,  1418,
    1421,  1421,  1431,  1431,  1440,  1441,  1444,  1445,  1446,  1447,
    1448,  1449,  1450,  1453,  1453,  1461,  1461,  1486,  1486,  1516,
    1516,  1528,  1529,  1532,  1533,  1536,  1536,  1548,  1548,  1560,
    1561,  1564,  1565,  1566,  1567,  1568,  1569,  1570,  1571,  1572,
    1573,  1574,  1577,  1577,  1585,  1590,  1590,  1598,  1603,  1611,
    1611,  1621,  1622,  1625,  1626,  1629,  1629,  1638,  1638,  1647,
    1648,  1651,  1652,  1656,  1657,  1658,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1666,  1669,  1669,  1679,  1679,  1689,  1689,
    1697,  1697,  1705,  1705,  1713,  1713,  1721,  1721,  1734,  1734,
    1744,  1745,  1748,  1748,  1759,  1759,  1769,  1770,  1773,  1773,
    1783,  1784,  1787,  1788,  1791,  1792,  1793,  1794,  1795,  1796,
    1797,  1800,  1802,  1802,  1810,  1818,  1818,  1830,  1831,  1834,
    1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1845,  1845,
    1852,  1853,  1854,  1857,  1862,  1862,  1870,  1875,  1882,  1889,
    1889,  1899,  1900,  1903,  1904,  1905,  1906,  1907,  1910,  1910,
    1918,  1918,  1928,  1928,  1946,  1946,  1958,  1958,  1968,  1969,
    1972,  1973,  1974,  1975,  1976,  1977,  1978,  1979,  1980,  1981,
    1982,  1983,  1984,  1985,  1986,  1987,  1988,  1989,  1990,  1993,
    1998,  1998,  2006,  2006,  2014,  2019,  2019,  2027,  2032,  2037,
    2037,  2045,  2046,  2049,  2049,  2057,  2062,  2067,  2072,  2072,
    2080,  2083,  2086,  2089,  2092,  2098,  2098,  2106,  2106,  2114,
    2114,  2124,  2124,  2131,  2131,  2138,  2138,  2147,  2147,  2156,
    2156,  2167,  2167,  2177,  2178,  2182,  2183,  2186,  2186,  2201,
    2201,  2211,  2211,  2222,  2223,  2227,  2231,  2231,  2243,  2244,
    2248,  2248,  2256,  2257,  2260,  2261,  2262,  2263,  2264,  2265,
    2266,  2269,  2274,  2274,  2282,  2282,  2292,  2293,  2296,  2296,
    2304,  2305,  2308,  2309,  2310,  2311,  2314,  2314,  2322,  2327,
    2332
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
#line 5014 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2337 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
