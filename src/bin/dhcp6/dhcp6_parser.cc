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
      case 514: // replace_client_name_value
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
      case 514: // replace_client_name_value
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

      case 514: // replace_client_name_value

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
      case 514: // replace_client_name_value
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

  case 108:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 636 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 754 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 756 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 196:
#line 772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 824 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1618 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1685 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 989 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 258:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1897 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1093 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 1980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2079 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1204 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2186 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 419:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1490 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 421:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2520 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2538 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2547 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2681 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2707 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2725 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr qc = yystack_[0].value.as< ElementPtr > ();
    ctx.stack_.back()->set("dhcp-queue-control", qc);

    // Doing this manually, because dhcp-queue-control
    // content is otherwise arbitrary
    if (!qc->contains("enable-queue")) {
        std::stringstream msg;
        msg << "'enable-queue' is required: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    // queue-enable is mandatory
    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
     }

    // if queue-type is supplied make sure it's a string
    if (qc->contains("queue-type")) {
        ConstElementPtr queue_type = qc->get("queue-type");
        if (queue_type->getType() != Element::string) {
            std::stringstream msg;
            msg << "'queue-type' must be a string: ";
            msg  << "(" << qc->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
    }

    ctx.leave();
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2029 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2044 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2068 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3248 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2098 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2101 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2107 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3356 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2118 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2144 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2158 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2165 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3471 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2174 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3482 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2179 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2189 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2204 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2219 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2224 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3551 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2233 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3580 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 640:
#line 2266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3599 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 641:
#line 2270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 651:
#line 2287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3624 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 653:
#line 2294 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 654:
#line 2300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 655:
#line 2305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 658:
#line 2314 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 659:
#line 2318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 666:
#line 2332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 667:
#line 2334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 668:
#line 2340 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 669:
#line 2345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 670:
#line 2350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3717 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3721 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -826;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     418,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,    45,    65,    44,    50,
      58,    78,   111,   121,   141,   149,   155,   159,   163,   165,
     184,   193,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,    65,   -78,    34,    64,    25,   236,    29,    36,
     196,   161,   103,   198,   -49,   375,   110,    26,  -826,   183,
     253,   261,   259,   269,  -826,  -826,  -826,  -826,  -826,   276,
    -826,    70,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,   315,   321,   323,   339,   345,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,   355,  -826,  -826,  -826,
    -826,    85,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,   361,  -826,   109,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   365,   367,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   132,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
     147,  -826,  -826,  -826,  -826,  -826,   383,  -826,   387,   414,
    -826,  -826,  -826,  -826,  -826,  -826,   170,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,   303,   348,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,   411,  -826,  -826,   416,  -826,  -826,
    -826,   419,  -826,  -826,   417,   350,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   424,
     431,  -826,  -826,  -826,  -826,   429,   423,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   182,
    -826,  -826,  -826,   442,  -826,  -826,   443,  -826,   444,   449,
    -826,  -826,   450,   451,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,   189,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   195,
    -826,  -826,  -826,  -826,   237,  -826,  -826,  -826,    65,    65,
    -826,   252,   454,   457,   460,   461,   462,  -826,    34,  -826,
      26,   463,   464,   465,   466,   467,   301,   302,   305,   308,
     309,   470,   473,   477,   478,   479,   480,   481,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   505,   340,   506,
     508,   509,    64,  -826,   510,   346,    25,  -826,   514,   516,
     517,   521,   522,   356,   360,   524,   528,   530,   236,  -826,
     531,    29,  -826,   532,   366,   535,   369,   370,    36,  -826,
     538,   539,   540,   542,   545,   547,   548,  -826,   196,  -826,
     549,   550,   384,   552,   553,   554,   386,  -826,   103,   556,
     389,   392,  -826,   198,   563,   564,   201,  -826,   396,   566,
     567,   420,   584,   421,   425,   585,   586,   426,   428,   589,
     590,   591,   598,   375,  -826,   599,   110,  -826,   600,    26,
    -826,  -826,  -826,   601,   603,   604,    65,    65,    65,  -826,
     263,   605,   606,   607,   608,   602,  -826,  -826,  -826,  -826,
    -826,   436,   611,   612,   613,   614,   438,   157,   615,   617,
     618,   619,   620,   621,   623,   624,   625,   626,  -826,   627,
     614,   628,  -826,   631,  -826,  -826,   632,   633,   455,   469,
     471,  -826,  -826,   631,   472,   636,  -826,   474,  -826,   475,
    -826,   476,  -826,  -826,  -826,   631,   631,   631,   482,   492,
     493,   494,  -826,   495,   496,  -826,   497,   498,   499,  -826,
    -826,   500,  -826,  -826,  -826,   501,    65,  -826,  -826,   502,
     503,  -826,   504,  -826,  -826,    47,   511,  -826,  -826,   -13,
     507,   512,   513,  -826,   635,  -826,   643,  -826,    65,    64,
     110,  -826,  -826,  -826,  -826,    26,    25,   191,   191,   642,
    -826,   644,   646,   647,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,   648,    -7,    65,   150,   537,   649,   650,   651,
     232,   146,    -3,  -826,   375,  -826,  -826,   652,   653,  -826,
    -826,  -826,  -826,  -826,   -48,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   654,
     642,  -826,   266,   288,   289,   306,  -826,  -826,  -826,  -826,
     671,   672,   674,   675,   676,  -826,   677,   680,  -826,   681,
     682,   683,  -826,   307,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,   310,  -826,   684,   685,  -826,  -826,   686,   688,
    -826,  -826,   687,   691,  -826,  -826,   689,   693,  -826,  -826,
     692,   694,  -826,  -826,  -826,    83,  -826,  -826,  -826,   695,
    -826,  -826,  -826,   143,  -826,  -826,  -826,  -826,   314,  -826,
    -826,  -826,   249,  -826,  -826,   696,   697,  -826,  -826,   698,
     700,  -826,   701,   702,   703,   704,   705,   706,   318,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   707,   708,
     709,  -826,  -826,  -826,  -826,   337,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,   338,  -826,  -826,
    -826,   347,   519,  -826,   710,   711,  -826,  -826,   712,   714,
    -826,  -826,  -826,   622,  -826,  -826,   278,  -826,   713,  -826,
    -826,  -826,  -826,   716,   717,   718,   719,   544,   526,   555,
     551,   557,   721,   558,   559,   723,   560,   561,   562,   191,
    -826,  -826,   191,  -826,   642,   236,  -826,   644,   103,  -826,
     646,   198,  -826,   647,   391,  -826,   648,    -7,  -826,  -826,
     150,  -826,   729,   537,  -826,   128,   649,  -826,   196,  -826,
     650,   -49,  -826,   651,   565,   568,   569,   570,   571,   572,
     232,  -826,   730,   733,   573,   574,   575,   146,  -826,   734,
     743,    -3,  -826,  -826,  -826,   742,   746,    29,  -826,   652,
      36,  -826,   653,   747,  -826,   264,   654,  -826,  -826,   422,
     580,   582,   583,  -826,  -826,  -826,  -826,  -826,   587,  -826,
    -826,   588,  -826,  -826,  -826,  -826,   349,  -826,   359,  -826,
     748,  -826,   751,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,   378,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,   592,  -826,  -826,   750,
    -826,  -826,  -826,  -826,  -826,   752,   758,  -826,  -826,  -826,
    -826,  -826,   755,  -826,   385,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,   342,   594,  -826,  -826,  -826,  -826,   596,
     597,  -826,  -826,   609,   395,  -826,   397,  -826,   616,  -826,
     765,  -826,  -826,  -826,  -826,  -826,   405,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,   391,  -826,  -826,   766,
     641,  -826,   128,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,   768,   630,   769,   264,
    -826,  -826,   634,  -826,  -826,   645,  -826,   655,  -826,  -826,
     781,  -826,  -826,   336,  -826,   -12,   781,  -826,  -826,   772,
     785,   794,   413,  -826,  -826,  -826,  -826,  -826,  -826,   801,
     659,   657,   665,   -12,  -826,   667,  -826,  -826,  -826,  -826,
    -826
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   117,     9,
     258,    11,   404,    13,   429,    15,   459,    17,   329,    19,
     337,    21,   374,    23,   223,    25,   558,    27,   631,    29,
     621,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     461,     0,   339,   376,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   629,   611,   613,   615,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   617,   619,
     115,   129,   131,   133,     0,     0,     0,     0,     0,   113,
     250,   327,   366,   417,   419,   292,   300,   196,   213,   204,
     189,   496,   451,   215,   234,   517,     0,   541,   554,   556,
     107,     0,    74,    76,    77,    78,    79,    80,   105,    83,
      84,    85,    86,   102,    87,    89,    88,    93,    94,    81,
     106,    82,    91,    92,   100,   101,   103,    90,    95,    96,
      97,    98,    99,   104,   126,     0,   125,     0,   119,   121,
     122,   123,   124,   396,   421,   282,   284,   286,     0,     0,
     290,   288,   490,   281,   262,   263,   264,   265,     0,   260,
     269,   270,   271,   274,   275,   277,   272,   273,   266,   267,
     279,   280,   268,   276,   278,   415,   414,   410,   411,   409,
       0,   406,   408,   412,   413,   444,     0,   447,     0,     0,
     443,   437,   438,   436,   441,   442,     0,   431,   433,   434,
     439,   440,   435,   488,   476,   478,   480,   482,   484,   486,
     475,   472,   473,   474,     0,   462,   463,   467,   468,   465,
     469,   470,   471,   466,     0,   356,   174,     0,   360,   358,
     363,     0,   352,   353,     0,   340,   341,   343,   355,   344,
     345,   346,   362,   347,   348,   349,   350,   351,   390,     0,
       0,   388,   389,   392,   393,     0,   377,   378,   380,   381,
     382,   383,   384,   385,   386,   387,   230,   232,   227,     0,
     225,   228,   229,     0,   581,   583,     0,   586,     0,     0,
     590,   594,     0,     0,   598,   605,   607,   609,   579,   577,
     578,     0,   560,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   636,     0,
     633,   635,   627,   626,     0,   623,   625,    48,     0,     0,
      41,     0,     0,     0,     0,     0,     0,    59,     0,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   259,
       0,     0,   405,     0,     0,     0,     0,     0,     0,   430,
       0,     0,     0,     0,     0,     0,     0,   460,     0,   330,
       0,     0,     0,     0,     0,     0,     0,   338,     0,     0,
       0,     0,   375,     0,     0,     0,     0,   224,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   559,     0,     0,   632,     0,     0,
     622,    52,    45,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   540,     0,
       0,     0,    75,     0,   128,   120,     0,     0,     0,     0,
       0,   298,   299,     0,     0,     0,   261,     0,   407,     0,
     446,     0,   449,   450,   432,     0,     0,     0,     0,     0,
       0,     0,   464,     0,     0,   354,     0,     0,     0,   365,
     342,     0,   394,   395,   379,     0,     0,   226,   580,     0,
       0,   585,     0,   588,   589,     0,     0,   596,   597,     0,
       0,     0,     0,   561,     0,   634,     0,   624,     0,     0,
       0,   612,   614,   616,   618,     0,     0,     0,     0,   135,
     114,   252,   331,   368,    42,   418,   420,   294,   295,   296,
     297,   293,   302,     0,    49,     0,     0,     0,   453,   217,
       0,     0,     0,   555,     0,    53,   127,   398,   423,   283,
     285,   287,   291,   289,     0,   416,   445,   448,   489,   477,
     479,   481,   483,   485,   487,   357,   175,   361,   359,   364,
     391,   231,   233,   582,   584,   587,   592,   593,   591,   595,
     600,   601,   602,   603,   604,   599,   606,   608,   610,     0,
     135,    46,     0,     0,     0,     0,   161,   167,   169,   171,
       0,     0,     0,     0,     0,   184,     0,     0,   187,     0,
       0,     0,   160,     0,   141,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   155,   156,   157,   158,   153,
     154,   159,     0,   139,     0,   136,   137,   256,     0,   253,
     254,   335,     0,   332,   333,   372,     0,   369,   370,   306,
       0,   303,   304,   202,   203,     0,   198,   200,   201,     0,
     211,   212,   208,     0,   206,   209,   210,   194,     0,   191,
     193,   500,     0,   498,   457,     0,   454,   455,   221,     0,
     218,   219,     0,     0,     0,     0,     0,     0,     0,   236,
     238,   239,   240,   241,   242,   243,   530,   536,     0,     0,
       0,   529,   526,   527,   528,     0,   519,   521,   524,   522,
     523,   525,   550,   552,   549,   547,   548,     0,   543,   545,
     546,     0,    55,   402,     0,   399,   400,   427,     0,   424,
     425,   494,   493,     0,   492,   640,     0,   638,     0,    71,
     630,   620,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,   132,     0,   134,     0,     0,   251,     0,   339,   328,
       0,   376,   367,     0,     0,   301,     0,     0,   197,   214,
       0,   205,     0,     0,   190,   502,     0,   497,   461,   452,
       0,     0,   216,     0,     0,     0,     0,     0,     0,     0,
       0,   235,     0,     0,     0,     0,     0,     0,   518,     0,
       0,     0,   542,   557,    57,     0,    56,     0,   397,     0,
       0,   422,     0,     0,   491,     0,     0,   637,   628,     0,
       0,     0,     0,   173,   176,   177,   178,   179,     0,   186,
     180,     0,   181,   182,   183,   142,     0,   138,     0,   255,
       0,   334,     0,   371,   326,   321,   323,   314,   315,   310,
     311,   312,   313,   319,   320,   318,   322,     0,   308,   316,
     324,   325,   317,   305,   199,   207,     0,   192,   514,     0,
     512,   513,   509,   510,   511,     0,   503,   504,   506,   507,
     508,   499,     0,   456,     0,   220,   244,   245,   246,   247,
     248,   249,   237,     0,     0,   535,   538,   539,   520,     0,
       0,   544,    54,     0,     0,   401,     0,   426,     0,   654,
       0,   652,   650,   644,   648,   649,     0,   642,   646,   647,
     645,   639,   163,   164,   165,   166,   162,   168,   170,   172,
     185,   188,   140,   257,   336,   373,     0,   307,   195,     0,
       0,   501,     0,   458,   222,   532,   533,   534,   531,   537,
     551,   553,    58,   403,   428,   495,     0,     0,     0,     0,
     641,   309,     0,   516,   505,     0,   651,     0,   643,   515,
       0,   653,   658,     0,   656,     0,     0,   655,   666,     0,
       0,     0,     0,   660,   662,   663,   664,   665,   657,     0,
       0,     0,     0,     0,   659,     0,   668,   669,   670,   661,
     667
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,    43,  -826,  -441,
    -826,   235,  -826,  -826,  -826,  -826,   192,  -826,  -414,  -826,
    -826,  -826,   -74,  -826,  -826,  -826,   447,  -826,  -826,  -826,
    -826,   227,   446,   -62,   -46,   -45,   -43,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,   223,   432,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,   175,  -826,    -4,  -826,  -572,
     -19,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,   -70,  -826,  -605,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   -17,
    -826,  -826,  -826,  -826,  -826,    -8,  -592,  -826,  -826,  -826,
    -826,   -10,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
     -22,  -826,  -826,  -826,   -18,   399,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,   -28,  -826,  -826,  -826,  -826,  -826,  -826,
    -825,  -826,  -826,  -826,     9,  -826,  -826,  -826,    13,   441,
    -826,  -826,  -824,  -826,  -821,  -826,   -36,  -826,   -32,  -826,
     -42,  -826,  -826,  -826,  -818,  -826,  -826,  -826,  -826,     4,
    -826,  -826,  -164,   788,  -826,  -826,  -826,  -826,  -826,    16,
    -826,  -826,  -826,    22,  -826,   427,  -826,   -76,  -826,  -826,
    -826,  -826,  -826,   -69,  -826,  -826,  -826,  -826,  -826,   -11,
    -826,  -826,  -826,    18,  -826,  -826,  -826,    21,  -826,   430,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,   -25,  -826,  -826,  -826,   -20,   458,  -826,  -826,   -58,
    -826,   -24,  -826,  -826,  -826,  -826,  -826,   -15,  -826,  -826,
    -826,   -16,   452,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
     -60,  -826,  -826,  -826,     8,  -826,  -826,  -826,    14,  -826,
     453,   251,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -817,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,    24,  -826,  -826,  -826,  -144,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,     5,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,     2,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,   270,
     433,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,
    -826,  -826,  -826,  -826,  -826,  -826,  -826,  -826,  -342,   434,
    -826,  -826,  -826,  -826,  -826,  -826,   311,   435,  -826,  -826,
    -826,    -9,  -826,  -826,  -154,  -826,  -826,  -826,  -826,  -826,
    -826,  -170,  -826,  -826,  -185,  -826,  -826,  -826,  -826,  -826
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   605,    92,    93,    43,    72,    89,    90,   626,   802,
     895,   896,   353,    45,    74,   101,   102,   103,   362,    47,
      75,   141,   142,   143,   144,   145,   146,   147,   148,   381,
     149,   372,    49,    76,   177,   178,   179,   404,   180,   150,
     373,   151,   374,   152,   375,   714,   715,   716,   842,   693,
     694,   695,   823,  1016,   696,   824,   697,   825,   698,   826,
     699,   700,   441,   701,   702,   703,   704,   705,   706,   707,
     708,   709,   832,   710,   711,   835,   153,   392,   748,   749,
     750,   862,   154,   389,   735,   736,   737,   738,   155,   391,
     743,   744,   745,   746,   156,   390,   157,   395,   759,   760,
     761,   871,    65,    84,   309,   310,   311,   454,   312,   455,
     158,   396,   768,   769,   770,   771,   772,   773,   774,   775,
     159,   382,   718,   719,   720,   845,    51,    77,   198,   199,
     200,   410,   201,   411,   202,   412,   203,   416,   204,   415,
     160,   387,   611,   206,   207,   161,   388,   730,   731,   732,
     854,   947,   948,   162,   383,    59,    81,   722,   723,   724,
     848,    61,    82,   274,   275,   276,   277,   278,   279,   280,
     440,   281,   444,   282,   443,   283,   284,   445,   285,   163,
     384,   726,   727,   728,   851,    63,    83,   295,   296,   297,
     298,   299,   449,   300,   301,   302,   303,   209,   408,   804,
     805,   806,   897,    53,    78,   220,   221,   222,   420,   164,
     385,   165,   386,   212,   409,   808,   809,   810,   900,    55,
      79,   236,   237,   238,   423,   239,   240,   425,   241,   242,
     166,   394,   755,   756,   757,   868,    57,    80,   254,   255,
     256,   257,   431,   258,   432,   259,   433,   260,   434,   261,
     435,   262,   436,   263,   430,   214,   417,   813,   814,   903,
     167,   393,   752,   753,   865,   965,   966,   967,   968,   969,
    1029,   970,   168,   397,   785,   786,   787,   882,  1038,   788,
     789,   883,   790,   791,   169,   170,   399,   797,   798,   799,
     889,   800,   890,   171,   400,   172,   401,    67,    85,   331,
     332,   333,   334,   459,   335,   460,   336,   337,   462,   338,
     339,   340,   465,   658,   341,   466,   342,   343,   344,   469,
     665,   345,   470,   346,   471,   347,   472,   104,   364,   105,
     365,   106,   366,   173,   370,   371,    71,    87,   354,   355,
     356,   478,   107,   363,    69,    86,   349,   350,   351,   475,
     816,   817,   905,  1006,  1007,  1008,  1009,  1048,  1010,  1046,
    1063,  1064,  1065,  1072,  1073,  1074,  1079,  1075,  1076,  1077
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
     100,   140,   176,   193,   216,   230,   250,   293,   272,   291,
     308,   328,   273,   292,   294,   194,   782,   213,   181,   210,
     223,   234,   252,   742,   286,   304,   712,   329,   490,   940,
     941,   195,   196,   942,   197,   205,   946,   952,   352,   174,
     175,   244,   217,   231,    94,    32,   218,   232,   811,   306,
     307,    44,   182,   211,   224,   235,   253,    46,   287,   305,
      40,   330,   123,   124,   604,    48,   208,   219,   233,   251,
      33,   108,    34,   368,    35,   109,   122,   110,   369,   604,
     111,   112,   113,   122,   733,    50,   857,   215,   402,   858,
     123,   124,    91,   403,   123,   124,   225,   226,   227,   228,
     229,   123,   124,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   406,   190,   792,   793,   191,   407,    52,   632,
     190,    99,   265,   191,   660,   661,   662,   663,    54,   123,
     124,   638,   639,   640,  1068,   418,   125,  1069,  1070,  1071,
     419,   126,   127,   128,   129,   130,   860,   131,    56,   861,
     421,   266,   132,   267,   268,   422,    58,   269,   270,   271,
     664,   133,    60,   734,   134,   776,    62,    99,   123,   124,
      64,   135,    66,   428,   681,   122,   266,    95,   429,   136,
     137,   656,   657,   138,   139,   456,    96,    97,    98,   357,
     457,    68,   473,   123,   124,    99,    99,   474,   476,    99,
      70,   940,   941,   477,    99,   942,    99,   121,   946,   952,
     676,   123,   124,   958,   959,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   691,
     607,   608,   609,   610,    99,    36,    37,    38,    39,   266,
     479,   733,   740,   122,   741,   480,   266,   288,   267,   268,
     289,   290,   866,   674,   348,   867,   358,   777,   778,   779,
     780,   123,   124,   123,   124,   359,   479,   360,   742,   402,
     926,   594,   361,    99,   819,   114,   115,   116,   117,   243,
     367,   906,   782,   122,   907,   244,   245,   246,   247,   248,
     249,   476,   479,   183,   100,   184,   820,   821,    99,   306,
     307,   123,   124,   185,   186,   187,   188,   189,   125,   406,
     839,   437,   266,   839,   822,   840,    99,   863,   841,   376,
     190,   880,   864,   191,   132,   377,   881,   378,   140,   123,
     124,   192,   176,   762,   763,   764,   765,   766,   767,  1066,
     887,   891,  1067,   379,   193,   888,   892,   216,   181,   380,
     473,   438,   839,   448,   230,   893,   194,  1022,   213,   398,
     210,    99,   418,   223,   250,   405,    99,  1023,    99,   413,
     234,   414,   195,   196,   272,   197,   205,   293,   273,   291,
     252,  1026,   182,   292,   294,   217,  1027,   424,   456,   218,
     286,   426,   231,  1034,   211,   304,   232,   224,   421,   328,
     428,   481,   482,  1043,   235,  1044,    99,   208,  1049,   999,
     219,  1000,  1001,  1050,   253,   329,  1083,   233,   427,   439,
     442,  1084,   483,   446,   287,   447,   453,   251,   450,   305,
     114,   115,   116,   117,    99,   451,   120,   452,   122,   266,
     123,   124,  1012,  1013,  1014,  1015,   458,   461,   463,   330,
    1035,  1036,  1037,   464,   467,   468,   123,   124,   484,   186,
     187,   485,   189,   125,   486,   487,   488,   491,   492,   493,
     494,   495,   496,   497,   501,   190,   498,   502,   191,   499,
     500,   503,   504,   505,   506,   507,   192,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   517,
     519,   518,   520,   521,   523,   140,   326,   327,   526,   524,
     527,   528,   176,   692,   692,   529,   530,   531,   533,   591,
     592,   593,   534,   532,   535,   537,   539,   540,   181,   541,
     542,   543,   545,   546,   547,    99,   548,   781,   794,   549,
     328,   550,   551,   553,   554,   555,   556,   557,   558,   559,
     561,    99,   562,   783,   795,   563,   329,   565,   566,   568,
     569,   570,   182,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   572,   575,
     576,   571,   573,   579,   580,   581,   574,   784,   796,   577,
     330,   578,   582,   584,   586,   588,   600,   599,   606,   652,
     589,   590,   595,   596,   597,   598,   601,   602,   603,   747,
     612,    34,   613,   614,   615,   629,   617,   616,   618,   619,
     904,   671,   620,   621,   622,   624,   625,   627,   628,   630,
     669,   631,   633,   634,   635,   636,   637,   659,   670,   713,
    1060,   717,   641,   721,   725,   729,   751,   754,   758,   803,
     807,   815,   642,   643,   644,   645,   646,   647,   648,   649,
     650,   651,   653,   654,   655,   827,   828,   666,   829,   830,
     831,   833,   667,   668,   834,   836,   837,   838,   844,   894,
     843,   847,   846,   849,   850,   852,   853,   856,   855,   914,
     870,   859,   869,   873,   872,   874,   875,   876,   877,   878,
     879,   884,   885,   886,   899,   913,   898,   902,   901,   908,
     909,   910,   911,   912,   916,   918,   915,   921,   917,   919,
     920,   922,   923,   956,   983,   924,   976,   984,   989,   977,
     978,   979,   980,   981,   985,   986,   987,   990,   992,   993,
    1017,   998,  1018,  1019,  1030,   623,  1024,  1020,  1021,  1025,
    1031,  1032,  1028,  1033,  1039,   692,  1040,  1041,   692,  1047,
    1052,   193,  1055,  1057,   272,   293,  1080,   291,   273,  1042,
     934,   292,   294,   194,   939,   213,  1045,   210,  1062,  1081,
     286,   960,   935,   304,   250,   961,   950,   308,  1082,   195,
     196,  1056,   197,   205,  1059,  1085,   739,   963,   936,   937,
     252,   938,   945,   781,  1053,   489,   672,   794,   943,   675,
     925,   211,   944,   216,   287,  1061,   230,   305,  1087,   783,
     951,  1002,  1086,   795,   208,  1003,  1088,  1090,   525,   223,
     927,   964,   234,   949,   253,   818,   957,  1004,   522,   954,
     955,   975,   982,   974,   962,   567,   929,   251,   928,   536,
     953,   217,  1051,   784,   231,   218,   931,   796,   232,   264,
     930,   933,   932,   224,   995,   560,   235,   994,   973,   538,
     544,  1005,   972,   564,   996,   812,   219,   997,  1054,   233,
     971,   552,   988,   991,   801,  1058,  1078,  1011,  1089,     0,
       0,   673,     0,     0,     0,     0,   583,     0,     0,     0,
       0,   585,     0,   587,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   934,     0,     0,     0,   939,     0,   960,     0,
       0,     0,   961,     0,   935,     0,     0,     0,   950,     0,
       0,     0,     0,     0,   963,  1002,     0,     0,     0,  1003,
     936,   937,     0,   938,   945,     0,     0,     0,     0,     0,
     943,  1004,     0,     0,   944,     0,     0,     0,     0,     0,
       0,     0,   951,     0,     0,     0,     0,     0,   964,     0,
       0,     0,     0,     0,     0,   949,     0,     0,     0,     0,
       0,   962,     0,     0,     0,  1005
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    82,    83,    83,    77,   621,    77,    76,    77,
      78,    79,    80,   615,    82,    83,   598,    85,   370,   854,
     854,    77,    77,   854,    77,    77,   854,   854,    12,    14,
      15,    89,    78,    79,    10,     0,    78,    79,    96,    98,
      99,     7,    76,    77,    78,    79,    80,     7,    82,    83,
      17,    85,    65,    66,   505,     7,    77,    78,    79,    80,
       5,     7,     7,     3,     9,    11,    47,    13,     8,   520,
      16,    17,    18,    47,    91,     7,     3,    58,     3,     6,
      65,    66,   170,     8,    65,    66,    60,    61,    62,    63,
      64,    65,    66,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     3,    84,   117,   118,    87,     8,     7,   533,
      84,   170,    19,    87,   137,   138,   139,   140,     7,    65,
      66,   545,   546,   547,   146,     3,    72,   149,   150,   151,
       8,    77,    78,    79,    80,    81,     3,    83,     7,     6,
       3,    48,    88,    50,    51,     8,     7,    54,    55,    56,
     173,    97,     7,   170,   100,    19,     7,   170,    65,    66,
       7,   107,     7,     3,    28,    47,    48,   143,     8,   115,
     116,   134,   135,   119,   120,     3,   152,   153,   154,     6,
       8,     7,     3,    65,    66,   170,   170,     8,     3,   170,
       7,  1026,  1026,     8,   170,  1026,   170,    46,  1026,  1026,
      19,    65,    66,    85,    86,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      73,    74,    75,    76,   170,   170,   171,   172,   173,    48,
       3,    91,    92,    47,    94,     8,    48,    49,    50,    51,
      52,    53,     3,   595,   144,     6,     3,   111,   112,   113,
     114,    65,    66,    65,    66,     4,     3,     8,   860,     3,
     842,     8,     3,   170,     8,    39,    40,    41,    42,    83,
       4,     3,   887,    47,     6,    89,    90,    91,    92,    93,
      94,     3,     3,    57,   368,    59,     8,     8,   170,    98,
      99,    65,    66,    67,    68,    69,    70,    71,    72,     3,
       3,     8,    48,     3,     8,     8,   170,     3,     8,     4,
      84,     3,     8,    87,    88,     4,     8,     4,   402,    65,
      66,    95,   406,   101,   102,   103,   104,   105,   106,     3,
       3,     3,     6,     4,   418,     8,     8,   421,   406,     4,
       3,     3,     3,     3,   428,     8,   418,     8,   418,     4,
     418,   170,     3,   421,   438,     4,   170,     8,   170,     4,
     428,     4,   418,   418,   448,   418,   418,   453,   448,   453,
     438,     3,   406,   453,   453,   421,     8,     4,     3,   421,
     448,     4,   428,     8,   418,   453,   428,   421,     3,   473,
       3,   358,   359,     8,   428,     8,   170,   418,     3,   145,
     421,   147,   148,     8,   438,   473,     3,   428,     4,     8,
       4,     8,   170,     4,   448,     8,     3,   438,     4,   453,
      39,    40,    41,    42,   170,     4,    45,     8,    47,    48,
      65,    66,    20,    21,    22,    23,     4,     4,     4,   473,
     108,   109,   110,     4,     4,     4,    65,    66,     4,    68,
      69,     4,    71,    72,     4,     4,     4,     4,     4,     4,
       4,     4,   171,   171,     4,    84,   171,     4,    87,   171,
     171,     4,     4,     4,     4,     4,    95,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,     4,
       4,   171,     4,     4,     4,   589,   141,   142,     4,   173,
       4,     4,   596,   597,   598,     4,     4,   171,     4,   486,
     487,   488,     4,   173,     4,     4,     4,   171,   596,     4,
     171,   171,     4,     4,     4,   170,     4,   621,   622,     4,
     624,     4,     4,     4,     4,   171,     4,     4,     4,   173,
       4,   170,   173,   621,   622,   173,   624,     4,     4,   173,
       4,     4,   596,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,     4,     4,
       4,   171,   171,     4,     4,     4,   171,   621,   622,   173,
     624,   173,     4,     4,     4,     4,   170,     5,   170,   566,
       7,     7,     7,     7,     7,     7,     5,     5,     5,    82,
       5,     7,     5,     5,     5,   170,     5,     7,     5,     5,
       8,   588,     7,     7,     7,     7,     5,     5,     5,   170,
       5,   170,   170,     7,   170,   170,   170,   136,     5,     7,
       5,     7,   170,     7,     7,     7,     7,     7,     7,     7,
       7,     7,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,     4,     4,   170,     4,     4,
       4,     4,   170,   170,     4,     4,     4,     4,     3,   170,
       6,     3,     6,     6,     3,     6,     3,     3,     6,   173,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   171,     6,     3,     6,     6,
       4,     4,     4,     4,   173,     4,   171,     4,   171,   171,
     171,   171,   171,     4,     4,   173,   171,     4,     4,   171,
     171,   171,   171,   171,   171,   171,   171,     4,     6,     3,
     170,     4,   170,   170,     4,   520,     8,   170,   170,     8,
       8,     3,   170,     8,   170,   839,   170,   170,   842,     4,
       4,   845,     4,     4,   848,   851,     4,   851,   848,   170,
     854,   851,   851,   845,   854,   845,   170,   845,     7,     4,
     848,   865,   854,   851,   868,   865,   854,   871,     4,   845,
     845,   171,   845,   845,   170,     4,   614,   865,   854,   854,
     868,   854,   854,   887,   173,   368,   589,   891,   854,   596,
     839,   845,   854,   897,   848,   170,   900,   851,   171,   887,
     854,   905,   173,   891,   845,   905,   171,   170,   406,   897,
     844,   865,   900,   854,   868,   670,   863,   905,   402,   857,
     860,   873,   880,   871,   865,   456,   847,   868,   845,   418,
     856,   897,  1026,   887,   900,   897,   850,   891,   900,    81,
     848,   853,   851,   897,   899,   448,   900,   897,   870,   421,
     428,   905,   868,   453,   900,   634,   897,   902,  1032,   900,
     866,   438,   887,   891,   624,  1049,  1066,   906,  1083,    -1,
      -1,   590,    -1,    -1,    -1,    -1,   473,    -1,    -1,    -1,
      -1,   476,    -1,   479,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1026,    -1,    -1,    -1,  1026,    -1,  1032,    -1,
      -1,    -1,  1032,    -1,  1026,    -1,    -1,    -1,  1026,    -1,
      -1,    -1,    -1,    -1,  1032,  1049,    -1,    -1,    -1,  1049,
    1026,  1026,    -1,  1026,  1026,    -1,    -1,    -1,    -1,    -1,
    1026,  1049,    -1,    -1,  1026,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1026,    -1,    -1,    -1,    -1,    -1,  1032,    -1,
      -1,    -1,    -1,    -1,    -1,  1026,    -1,    -1,    -1,    -1,
      -1,  1032,    -1,    -1,    -1,  1049
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
       7,   355,     7,   379,     7,   296,     7,   491,     7,   538,
       7,   530,   199,   194,   208,   214,   227,   321,   398,   414,
     431,   350,   356,   380,   297,   492,   539,   531,   191,   200,
     201,   170,   196,   197,    10,   143,   152,   153,   154,   170,
     206,   209,   210,   211,   521,   523,   525,   536,     7,    11,
      13,    16,    17,    18,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    65,    66,    72,    77,    78,    79,    80,
      81,    83,    88,    97,   100,   107,   115,   116,   119,   120,
     206,   215,   216,   217,   218,   219,   220,   221,   222,   224,
     233,   235,   237,   270,   276,   282,   288,   290,   304,   314,
     334,   339,   347,   373,   403,   405,   424,   454,   466,   478,
     479,   487,   489,   527,    14,    15,   206,   228,   229,   230,
     232,   403,   405,    57,    59,    67,    68,    69,    70,    71,
      84,    87,    95,   206,   217,   218,   219,   220,   322,   323,
     324,   326,   328,   330,   332,   334,   337,   338,   373,   391,
     403,   405,   407,   424,   449,    58,   206,   330,   332,   373,
     399,   400,   401,   403,   405,    60,    61,    62,    63,    64,
     206,   330,   332,   373,   403,   405,   415,   416,   417,   419,
     420,   422,   423,    83,    89,    90,    91,    92,    93,    94,
     206,   373,   403,   405,   432,   433,   434,   435,   437,   439,
     441,   443,   445,   447,   347,    19,    48,    50,    51,    54,
      55,    56,   206,   255,   357,   358,   359,   360,   361,   362,
     363,   365,   367,   369,   370,   372,   403,   405,    49,    52,
      53,   206,   255,   361,   367,   381,   382,   383,   384,   385,
     387,   388,   389,   390,   403,   405,    98,    99,   206,   298,
     299,   300,   302,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   141,   142,   206,   403,
     405,   493,   494,   495,   496,   498,   500,   501,   503,   504,
     505,   508,   510,   511,   512,   515,   517,   519,   144,   540,
     541,   542,    12,   206,   532,   533,   534,     6,     3,     4,
       8,     3,   212,   537,   522,   524,   526,     4,     3,     8,
     528,   529,   225,   234,   236,   238,     4,     4,     4,     4,
       4,   223,   315,   348,   374,   404,   406,   335,   340,   277,
     289,   283,   271,   455,   425,   291,   305,   467,     4,   480,
     488,   490,     3,     8,   231,     4,     3,     8,   392,   408,
     325,   327,   329,     4,     4,   333,   331,   450,     3,     8,
     402,     3,     8,   418,     4,   421,     4,     4,     3,     8,
     448,   436,   438,   440,   442,   444,   446,     8,     3,     8,
     364,   256,     4,   368,   366,   371,     4,     8,     3,   386,
       4,     4,     8,     3,   301,   303,     3,     8,     4,   497,
     499,     4,   502,     4,     4,   506,   509,     4,     4,   513,
     516,   518,   520,     3,     8,   543,     3,     8,   535,     3,
       8,   191,   191,   170,     4,     4,     4,     4,     4,   210,
     532,     4,     4,     4,     4,     4,   171,   171,   171,   171,
     171,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   171,     4,
       4,     4,   216,     4,   173,   229,     4,     4,     4,     4,
       4,   171,   173,     4,     4,     4,   323,     4,   400,     4,
     171,     4,   171,   171,   416,     4,     4,     4,     4,     4,
       4,     4,   434,     4,     4,   171,     4,     4,     4,   173,
     359,     4,   173,   173,   383,     4,     4,   299,   173,     4,
       4,   171,     4,   171,   171,     4,     4,   173,   173,     4,
       4,     4,     4,   494,     4,   541,     4,   533,     4,     7,
       7,   191,   191,   191,     8,     7,     7,     7,     7,     5,
     170,     5,     5,     5,   193,   195,   170,    73,    74,    75,
      76,   336,     5,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,   195,     7,     5,   202,     5,     5,   170,
     170,   170,   202,   170,     7,   170,   170,   170,   202,   202,
     202,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   191,   170,   170,   170,   134,   135,   507,   136,
     137,   138,   139,   140,   173,   514,   170,   170,   170,     5,
       5,   191,   215,   540,   532,   228,    19,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   206,   243,   244,   245,   248,   250,   252,   254,
     255,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     267,   268,   243,     7,   239,   240,   241,     7,   316,   317,
     318,     7,   351,   352,   353,     7,   375,   376,   377,     7,
     341,   342,   343,    91,   170,   278,   279,   280,   281,   200,
      92,    94,   280,   284,   285,   286,   287,    82,   272,   273,
     274,     7,   456,   457,     7,   426,   427,   428,     7,   292,
     293,   294,   101,   102,   103,   104,   105,   106,   306,   307,
     308,   309,   310,   311,   312,   313,    19,   111,   112,   113,
     114,   206,   257,   403,   405,   468,   469,   470,   473,   474,
     476,   477,   117,   118,   206,   403,   405,   481,   482,   483,
     485,   493,   203,     7,   393,   394,   395,     7,   409,   410,
     411,    96,   435,   451,   452,     7,   544,   545,   239,     8,
       8,     8,     8,   246,   249,   251,   253,     4,     4,     4,
       4,     4,   266,     4,     4,   269,     4,     4,     4,     3,
       8,     8,   242,     6,     3,   319,     6,     3,   354,     6,
       3,   378,     6,     3,   344,     6,     3,     3,     6,     6,
       3,     6,   275,     3,     8,   458,     3,     6,   429,     6,
       3,   295,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   471,   475,     4,     4,     4,     3,     8,   484,
     486,     3,     8,     8,   170,   204,   205,   396,     6,     3,
     412,     6,     3,   453,     8,   546,     3,     6,     6,     4,
       4,     4,     4,   171,   173,   171,   173,   171,     4,   171,
     171,     4,   171,   171,   173,   244,   243,   241,   322,   318,
     357,   353,   381,   377,   206,   217,   218,   219,   220,   255,
     314,   326,   328,   330,   332,   334,   338,   345,   346,   373,
     403,   405,   449,   343,   279,   285,     4,   273,    85,    86,
     206,   255,   373,   403,   405,   459,   460,   461,   462,   463,
     465,   457,   432,   428,   298,   294,   171,   171,   171,   171,
     171,   171,   307,     4,     4,   171,   171,   171,   469,     4,
       4,   482,     6,     3,   399,   395,   415,   411,     4,   145,
     147,   148,   206,   255,   403,   405,   547,   548,   549,   550,
     552,   545,    20,    21,    22,    23,   247,   170,   170,   170,
     170,   170,     8,     8,     8,     8,     3,     8,   170,   464,
       4,     8,     3,     8,     8,   108,   109,   110,   472,   170,
     170,   170,   170,     8,     8,   170,   553,     4,   551,     3,
       8,   346,     4,   173,   461,     4,   171,     4,   548,   170,
       5,   170,     7,   554,   555,   556,     3,     6,   146,   149,
     150,   151,   557,   558,   559,   561,   562,   563,   555,   560,
       4,     4,     4,     3,     8,     4,   173,   171,   171,   558,
     170
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
     216,   216,   216,   216,   216,   216,   216,   216,   217,   218,
     219,   220,   221,   223,   222,   225,   224,   227,   226,   228,
     228,   229,   229,   229,   229,   229,   231,   230,   232,   234,
     233,   236,   235,   238,   237,   239,   239,   240,   240,   242,
     241,   243,   243,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   246,   245,   247,   247,   247,   247,   249,   248,   251,
     250,   253,   252,   254,   256,   255,   257,   258,   259,   260,
     261,   262,   263,   264,   266,   265,   267,   269,   268,   271,
     270,   272,   272,   273,   275,   274,   277,   276,   278,   278,
     279,   279,   280,   281,   283,   282,   284,   284,   285,   285,
     285,   286,   287,   289,   288,   291,   290,   292,   292,   293,
     293,   295,   294,   297,   296,   298,   298,   298,   299,   299,
     301,   300,   303,   302,   305,   304,   306,   306,   307,   307,
     307,   307,   307,   307,   308,   309,   310,   311,   312,   313,
     315,   314,   316,   316,   317,   317,   319,   318,   321,   320,
     322,   322,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   325,   324,   327,   326,   329,   328,   331,   330,
     333,   332,   335,   334,   336,   336,   336,   336,   337,   338,
     340,   339,   341,   341,   342,   342,   344,   343,   345,   345,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   348,   347,   350,
     349,   351,   351,   352,   352,   354,   353,   356,   355,   357,
     357,   358,   358,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   360,   361,   362,   364,   363,   366,   365,
     368,   367,   369,   371,   370,   372,   374,   373,   375,   375,
     376,   376,   378,   377,   380,   379,   381,   381,   382,   382,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   384,
     386,   385,   387,   388,   389,   390,   392,   391,   393,   393,
     394,   394,   396,   395,   398,   397,   399,   399,   400,   400,
     400,   400,   400,   400,   400,   402,   401,   404,   403,   406,
     405,   408,   407,   409,   409,   410,   410,   412,   411,   414,
     413,   415,   415,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   418,   417,   419,   421,   420,   422,
     423,   425,   424,   426,   426,   427,   427,   429,   428,   431,
     430,   432,   432,   433,   433,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   436,   435,   438,   437,
     440,   439,   442,   441,   444,   443,   446,   445,   448,   447,
     450,   449,   451,   451,   453,   452,   455,   454,   456,   456,
     458,   457,   459,   459,   460,   460,   461,   461,   461,   461,
     461,   461,   461,   462,   464,   463,   465,   467,   466,   468,
     468,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     471,   470,   472,   472,   472,   473,   475,   474,   476,   477,
     478,   480,   479,   481,   481,   482,   482,   482,   482,   482,
     484,   483,   486,   485,   488,   487,   490,   489,   492,   491,
     493,   493,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     495,   497,   496,   499,   498,   500,   502,   501,   503,   504,
     506,   505,   507,   507,   509,   508,   510,   511,   513,   512,
     514,   514,   514,   514,   514,   516,   515,   518,   517,   520,
     519,   522,   521,   524,   523,   526,   525,   528,   527,   529,
     527,   531,   530,   532,   532,   533,   533,   535,   534,   537,
     536,   539,   538,   540,   540,   541,   543,   542,   544,   544,
     546,   545,   547,   547,   548,   548,   548,   548,   548,   548,
     548,   549,   551,   550,   553,   552,   554,   554,   556,   555,
     557,   557,   558,   558,   558,   558,   560,   559,   561,   562,
     563
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     0,     4,     0,
       6,     1,     3,     1,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
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
  "socket_name", "$@102", "dhcp_queue_control", "$@103", "dhcp_ddns",
  "$@104", "sub_dhcp_ddns", "$@105", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@106", "server_ip", "$@107",
  "server_port", "sender_ip", "$@108", "sender_port", "max_queue_size",
  "ncr_protocol", "$@109", "ncr_protocol_value", "ncr_format", "$@110",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@111", "replace_client_name_value", "generated_prefix", "$@112",
  "hostname_char_set", "$@113", "hostname_char_replacement", "$@114",
  "dhcp4_json_object", "$@115", "dhcpddns_json_object", "$@116",
  "control_agent_json_object", "$@117", "config_control", "$@118", "$@119",
  "sub_config_control", "$@120", "config_control_params",
  "config_control_param", "config_databases", "$@121", "logging_object",
  "$@122", "sub_logging", "$@123", "logging_params", "logging_param",
  "loggers", "$@124", "loggers_entries", "logger_entry", "$@125",
  "logger_params", "logger_param", "debuglevel", "severity", "$@126",
  "output_options_list", "$@127", "output_options_list_content",
  "output_entry", "$@128", "output_params_list", "output_params", "output",
  "$@129", "flush", "maxsize", "maxver", YY_NULLPTR
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
     462,   463,   464,   465,   466,   467,   468,   469,   472,   477,
     482,   487,   492,   497,   497,   505,   505,   516,   516,   525,
     526,   529,   530,   531,   532,   533,   536,   536,   546,   552,
     552,   564,   564,   576,   576,   586,   587,   590,   591,   594,
     594,   604,   605,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   628,   628,   635,   636,   637,   638,   641,   641,   649,
     649,   657,   657,   665,   670,   670,   678,   683,   688,   693,
     698,   703,   708,   713,   718,   718,   726,   731,   731,   739,
     739,   749,   750,   752,   754,   754,   772,   772,   782,   783,
     786,   787,   790,   795,   800,   800,   810,   811,   814,   815,
     816,   819,   824,   831,   831,   841,   841,   851,   852,   855,
     856,   859,   859,   869,   869,   879,   880,   881,   884,   885,
     888,   888,   896,   896,   904,   904,   915,   916,   919,   920,
     921,   922,   923,   924,   927,   932,   937,   942,   947,   952,
     960,   960,   973,   974,   977,   978,   985,   985,  1011,  1011,
    1022,  1023,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,
    1045,  1046,  1049,  1049,  1057,  1057,  1065,  1065,  1073,  1073,
    1081,  1081,  1091,  1091,  1098,  1099,  1100,  1101,  1104,  1109,
    1117,  1117,  1128,  1129,  1133,  1134,  1137,  1137,  1145,  1146,
    1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
    1159,  1160,  1161,  1162,  1163,  1164,  1165,  1172,  1172,  1185,
    1185,  1194,  1195,  1198,  1199,  1204,  1204,  1219,  1219,  1233,
    1234,  1237,  1238,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1253,  1255,  1260,  1262,  1262,  1270,  1270,
    1278,  1278,  1286,  1288,  1288,  1296,  1305,  1305,  1317,  1318,
    1323,  1324,  1329,  1329,  1341,  1341,  1353,  1354,  1359,  1360,
    1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1373,  1376,
    1378,  1378,  1386,  1388,  1390,  1395,  1403,  1403,  1415,  1416,
    1419,  1420,  1423,  1423,  1433,  1433,  1442,  1443,  1446,  1447,
    1448,  1449,  1450,  1451,  1452,  1455,  1455,  1463,  1463,  1488,
    1488,  1518,  1518,  1530,  1531,  1534,  1535,  1538,  1538,  1550,
    1550,  1562,  1563,  1566,  1567,  1568,  1569,  1570,  1571,  1572,
    1573,  1574,  1575,  1576,  1579,  1579,  1587,  1592,  1592,  1600,
    1605,  1613,  1613,  1623,  1624,  1627,  1628,  1631,  1631,  1640,
    1640,  1649,  1650,  1653,  1654,  1658,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1666,  1667,  1668,  1671,  1671,  1681,  1681,
    1691,  1691,  1699,  1699,  1707,  1707,  1715,  1715,  1723,  1723,
    1736,  1736,  1746,  1747,  1750,  1750,  1761,  1761,  1771,  1772,
    1775,  1775,  1785,  1786,  1789,  1790,  1793,  1794,  1795,  1796,
    1797,  1798,  1799,  1802,  1804,  1804,  1812,  1820,  1820,  1832,
    1833,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,
    1847,  1847,  1854,  1855,  1856,  1859,  1864,  1864,  1872,  1877,
    1884,  1891,  1891,  1901,  1902,  1905,  1906,  1907,  1908,  1909,
    1912,  1912,  1920,  1920,  1930,  1930,  1970,  1970,  1982,  1982,
    1992,  1993,  1996,  1997,  1998,  1999,  2000,  2001,  2002,  2003,
    2004,  2005,  2006,  2007,  2008,  2009,  2010,  2011,  2012,  2013,
    2016,  2021,  2021,  2029,  2029,  2037,  2042,  2042,  2050,  2055,
    2060,  2060,  2068,  2069,  2072,  2072,  2080,  2085,  2090,  2090,
    2098,  2101,  2104,  2107,  2110,  2116,  2116,  2124,  2124,  2132,
    2132,  2142,  2142,  2149,  2149,  2156,  2156,  2165,  2165,  2174,
    2174,  2185,  2185,  2195,  2196,  2200,  2201,  2204,  2204,  2219,
    2219,  2229,  2229,  2240,  2241,  2245,  2249,  2249,  2261,  2262,
    2266,  2266,  2274,  2275,  2278,  2279,  2280,  2281,  2282,  2283,
    2284,  2287,  2292,  2292,  2300,  2300,  2310,  2311,  2314,  2314,
    2322,  2323,  2326,  2327,  2328,  2329,  2332,  2332,  2340,  2345,
    2350
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
#line 5031 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2355 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
