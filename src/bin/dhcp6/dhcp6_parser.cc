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
      case 219: // value
      case 223: // map_value
      case 264: // ddns_replace_client_name_value
      case 304: // db_type
      case 405: // hr_mode
      case 541: // duid_type
      case 584: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 202: // "boolean"
        value.move< bool > (that.value);
        break;

      case 201: // "floating point"
        value.move< double > (that.value);
        break;

      case 200: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 199: // "constant string"
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
      case 219: // value
      case 223: // map_value
      case 264: // ddns_replace_client_name_value
      case 304: // db_type
      case 405: // hr_mode
      case 541: // duid_type
      case 584: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 202: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 201: // "floating point"
        value.copy< double > (that.value);
        break;

      case 200: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 199: // "constant string"
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
            case 199: // "constant string"

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 200: // "integer"

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 201: // "floating point"

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 202: // "boolean"

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 219: // value

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 223: // map_value

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 264: // ddns_replace_client_name_value

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 304: // db_type

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 405: // hr_mode

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 541: // duid_type

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 584: // ncr_protocol_value

#line 279 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 219: // value
      case 223: // map_value
      case 264: // ddns_replace_client_name_value
      case 304: // db_type
      case 405: // hr_mode
      case 541: // duid_type
      case 584: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 202: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 201: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 200: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 199: // "constant string"
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
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 289 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 291 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 292 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 293 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 294 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 296 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 298 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 299 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 300 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 309 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 313 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 314 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as< std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 346 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as< std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 365 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 369 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 387 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 391 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 927 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 402 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1263 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1302 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1380 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1471 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1527 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1548 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 878 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1604 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 879 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1677 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 978 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 1005 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1862 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 1020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1982 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2064 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1166 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2163 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1232 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2529 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2599 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2649 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2707 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2757 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1858 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1869 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2969 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3060 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 2002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 2023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 2029 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 2042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 2055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2093 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3182 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3191 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2125 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3248 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3257 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2181 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2187 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2200 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2225 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2228 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2234 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 642:
#line 2271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 643:
#line 2274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 644:
#line 2279 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2280 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3451 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2281 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 650:
#line 2299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 651:
#line 2305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 653:
#line 2321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 654:
#line 2327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3537 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 662:
#line 2343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 663:
#line 2346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3556 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 664:
#line 2352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 665:
#line 2355 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3575 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 666:
#line 2364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 667:
#line 2370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 676:
#line 2389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 677:
#line 2395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 678:
#line 2398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr qt(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 679:
#line 2404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 680:
#line 2410 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 681:
#line 2413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set(yystack_[3].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 682:
#line 2420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 683:
#line 2426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 684:
#line 2433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 685:
#line 2437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 706:
#line 2467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 707:
#line 2474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 708:
#line 2477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3727 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 709:
#line 2483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 710:
#line 2486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 711:
#line 2492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 712:
#line 2498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 713:
#line 2501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 714:
#line 2507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 715:
#line 2513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 716:
#line 2519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3804 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 717:
#line 2522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 718:
#line 2528 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 719:
#line 2529 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 720:
#line 2532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 721:
#line 2535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3844 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 722:
#line 2542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3854 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 723:
#line 2549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 724:
#line 2556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 725:
#line 2559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 726:
#line 2565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 727:
#line 2568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 728:
#line 2575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 729:
#line 2578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 730:
#line 2585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 731:
#line 2588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 732:
#line 2597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 733:
#line 2603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 734:
#line 2609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 735:
#line 2613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 740:
#line 2628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3992 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 741:
#line 2634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 742:
#line 2639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 743:
#line 2647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 744:
#line 2653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 747:
#line 2665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 748:
#line 2669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 4050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 758:
#line 2686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4060 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 759:
#line 2692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 760:
#line 2695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4079 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 761:
#line 2701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 762:
#line 2707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 765:
#line 2716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 766:
#line 2720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 4118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 774:
#line 2735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 775:
#line 2738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 776:
#line 2744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 777:
#line 2750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 778:
#line 2756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 779:
#line 2762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 780:
#line 2765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4186 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 4190 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -949;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     190,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,    39,    33,    62,    64,    78,
      89,    99,   103,   107,   131,   138,   217,   231,   244,   254,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,    33,  -132,
     119,   115,    49,   505,   258,   235,   221,   127,   120,   283,
     -75,   537,   144,  -949,   311,   226,   239,   242,   294,  -949,
     323,  -949,  -949,  -949,  -949,  -949,  -949,   328,   338,   339,
     358,   386,   404,   405,   408,   409,   411,   414,   417,   424,
     426,  -949,   428,   433,   436,   437,   439,  -949,  -949,  -949,
     440,   442,   448,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,   452,
    -949,  -949,  -949,  -949,  -949,  -949,   457,  -949,   462,  -949,
      60,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
     464,  -949,    94,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,   467,   468,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,   101,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,   109,  -949,  -949,  -949,  -949,
    -949,   469,  -949,   472,   473,  -949,  -949,  -949,  -949,  -949,
    -949,   113,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,   357,
     343,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,   390,
    -949,  -949,   476,  -949,  -949,  -949,   479,  -949,  -949,   477,
     481,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,   482,   484,  -949,  -949,  -949,  -949,
     485,   489,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,   128,  -949,  -949,  -949,   491,  -949,
    -949,   492,  -949,   493,   494,  -949,  -949,   495,   496,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,   129,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,   498,   186,  -949,  -949,  -949,  -949,
      33,    33,  -949,   306,   500,  -949,   508,   510,   512,   513,
     515,   520,   309,   327,   329,   331,   333,   334,   335,   336,
     337,   341,   344,   346,   340,   362,   534,   363,   364,   373,
     374,   376,   539,   561,   575,   378,   379,   380,   579,   580,
     581,   582,   584,   586,   587,   588,   589,   590,   599,   600,
     601,   602,   604,   605,   412,   607,   609,   611,   612,   615,
     616,   419,   618,  -949,   115,  -949,   619,   422,    49,  -949,
     625,   626,   627,   628,   629,   434,   435,   631,   632,   634,
     505,  -949,   635,   258,  -949,   636,   441,   638,   446,   449,
     235,  -949,   644,   646,   647,   648,   649,   650,   651,  -949,
     221,  -949,   652,   653,   458,   660,   661,   662,   466,  -949,
     120,   665,   470,   471,  -949,   283,   666,   667,    67,  -949,
     474,   670,   671,   480,   673,   483,   486,   677,   680,   487,
     501,   681,   683,   684,   701,   537,  -949,   702,   507,   144,
    -949,  -949,  -949,   704,   705,   514,   707,   726,   727,   728,
     742,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,   551,  -949,  -949,  -949,  -949,
    -949,  -110,   552,   553,  -949,  -949,  -949,   748,   749,   750,
     751,   557,   326,   752,   754,   755,   756,   757,   758,   760,
     763,   764,   767,  -949,   768,   769,   770,   771,   563,   583,
    -949,   774,  -949,   775,  -949,  -949,   776,   778,   585,   591,
     592,  -949,  -949,   775,   593,   779,  -949,   594,  -949,   595,
    -949,   596,  -949,  -949,  -949,   775,   775,   775,   598,   603,
     606,   608,  -949,   610,   613,  -949,   614,   617,   620,  -949,
    -949,   621,  -949,  -949,  -949,   622,   751,  -949,  -949,   623,
     624,  -949,   630,  -949,  -949,  -113,   541,  -949,  -949,  -110,
     633,   637,   639,  -949,   782,  -949,  -949,    33,   115,  -949,
     144,    49,   243,   243,   791,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,   792,   793,   794,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,   796,   -79,    33,   149,   682,
     797,   799,   801,    23,   167,     4,     9,    -7,   537,  -949,
    -949,   803,  -949,  -949,   804,   807,  -949,  -949,  -949,  -949,
    -949,   -70,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,   791,  -949,   199,   201,   219,  -949,  -949,  -949,  -949,
     811,   813,   814,   820,   821,  -949,   822,   823,  -949,  -949,
    -949,   824,   826,   827,   829,  -949,   222,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,   223,  -949,
     828,   832,  -949,  -949,   831,   836,  -949,  -949,   834,   838,
    -949,  -949,   837,   839,  -949,  -949,   840,   841,  -949,  -949,
    -949,    75,  -949,  -949,  -949,   842,  -949,  -949,  -949,   122,
    -949,  -949,  -949,  -949,   233,  -949,  -949,  -949,   236,  -949,
    -949,   845,   844,  -949,  -949,   846,   850,  -949,   851,   852,
     853,   854,   855,   856,   246,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,   857,   858,   859,  -949,  -949,  -949,
    -949,   284,  -949,  -949,  -949,  -949,  -949,  -949,   860,   861,
     862,  -949,   291,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,   292,  -949,  -949,  -949,   863,  -949,
     864,  -949,  -949,  -949,   293,  -949,  -949,  -949,  -949,  -949,
     305,  -949,   256,  -949,   655,  -949,   865,   866,  -949,  -949,
     867,   869,  -949,  -949,  -949,   868,  -949,   871,  -949,  -949,
    -949,   870,   874,   875,   876,   645,   668,   685,   679,   686,
     878,   687,   688,   879,   880,   885,   690,   691,   692,   693,
     243,  -949,  -949,   243,  -949,   791,   505,  -949,   792,   120,
    -949,   793,   283,  -949,   794,   676,  -949,   796,   -79,  -949,
    -949,   149,  -949,   888,   682,  -949,   261,   797,  -949,   221,
    -949,   799,   -75,  -949,   801,   696,   697,   699,   700,   703,
     710,    23,  -949,   908,   909,   722,   729,   730,   167,  -949,
     739,   744,   781,     4,  -949,   924,   946,     9,  -949,   773,
     952,   785,   965,    -7,  -949,  -949,   237,   803,  -949,  -949,
     972,   979,   258,  -949,   804,   235,  -949,   807,   985,  -949,
    -949,   191,   798,   812,   817,  -949,  -949,  -949,  -949,  -949,
     830,  -949,  -949,   833,   835,   843,  -949,  -949,  -949,  -949,
    -949,   342,  -949,   360,  -949,  1004,  -949,  1012,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,   361,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,   847,  -949,  -949,  1017,  -949,  -949,  -949,  -949,  -949,
    1014,  1022,  -949,  -949,  -949,  -949,  -949,  1018,  -949,   388,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,   220,   848,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,   872,   873,
    -949,  -949,   882,  -949,    33,  -949,  -949,  1024,  -949,  -949,
    -949,  -949,  -949,   394,  -949,  -949,  -949,  -949,  -949,  -949,
     883,   396,  -949,   402,  -949,   886,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,   676,  -949,  -949,  1026,   849,  -949,   261,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    1027,   877,  1031,   237,  -949,  -949,  -949,  -949,  -949,  -949,
     887,  -949,  -949,  1032,  -949,   889,  -949,  -949,  1033,  -949,
    -949,   312,  -949,   211,  1033,  -949,  -949,  1034,  1035,  1037,
    -949,   403,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  1039,
     890,   884,   891,  1040,   211,  -949,   894,  -949,  -949,  -949,
     895,  -949,  -949,  -949
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   168,     9,   330,    11,
     516,    13,   541,    15,   571,    17,   441,    19,   449,    21,
     486,    23,   295,    25,   684,    27,   734,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   573,     0,   451,   488,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   124,   732,   166,   180,   182,   184,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   163,     0,     0,     0,     0,     0,   143,   150,   152,
       0,     0,     0,   322,   439,   478,   529,   531,   384,   392,
     255,   272,   263,   248,   608,   563,   287,   306,   629,     0,
     274,   653,   666,   682,   156,   158,     0,   743,     0,   123,
       0,    64,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   102,   103,   104,   105,   106,    75,   110,   111,   112,
     113,   114,   115,   116,   117,   108,   109,   118,   119,   120,
     100,   122,    78,    79,    80,    81,    97,    82,    84,    83,
     121,    88,    89,    76,   101,    77,    86,    87,    95,    96,
      98,    85,    90,    91,    92,    93,    94,    99,   107,   177,
       0,   176,     0,   170,   172,   173,   174,   175,   508,   533,
     374,   376,   378,     0,     0,   382,   380,   602,   373,   334,
     335,   336,   337,   338,   339,   340,   341,   357,   358,   359,
     360,   361,   364,   365,   366,   367,   368,   369,   370,   371,
     362,   363,   372,     0,   332,   345,   346,   347,   350,   351,
     353,   348,   349,   342,   343,   355,   356,   344,   352,   354,
     527,   526,   522,   523,   521,     0,   518,   520,   524,   525,
     556,     0,   559,     0,     0,   555,   549,   550,   548,   553,
     554,     0,   543,   545,   546,   551,   552,   547,   600,   588,
     590,   592,   594,   596,   598,   587,   584,   585,   586,     0,
     574,   575,   579,   580,   577,   581,   582,   583,   578,     0,
     468,   228,     0,   472,   470,   475,     0,   464,   465,     0,
     452,   453,   455,   467,   456,   457,   458,   474,   459,   460,
     461,   462,   463,   502,     0,     0,   500,   501,   504,   505,
       0,   489,   490,   492,   493,   494,   495,   496,   497,   498,
     499,   302,   304,   299,     0,   297,   300,   301,     0,   707,
     709,     0,   712,     0,     0,   716,   720,     0,     0,   724,
     726,   728,   730,   705,   703,   704,     0,   686,   688,   700,
     689,   690,   691,   692,   693,   694,   695,   696,   697,   698,
     699,   701,   702,   740,     0,     0,   736,   738,   739,    46,
       0,     0,    39,     0,     0,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    57,     0,    63,     0,     0,     0,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   331,     0,     0,   517,     0,     0,     0,     0,     0,
       0,   542,     0,     0,     0,     0,     0,     0,     0,   572,
       0,   442,     0,     0,     0,     0,     0,     0,     0,   450,
       0,     0,     0,     0,   487,     0,     0,     0,     0,   296,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   685,     0,     0,     0,
     735,    50,    43,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,     0,   161,   162,   140,   141,
     142,     0,     0,     0,   154,   155,   160,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   652,     0,     0,     0,     0,     0,     0,
     165,     0,    65,     0,   179,   171,     0,     0,     0,     0,
       0,   390,   391,     0,     0,     0,   333,     0,   519,     0,
     558,     0,   561,   562,   544,     0,     0,     0,     0,     0,
       0,     0,   576,     0,     0,   466,     0,     0,     0,   477,
     454,     0,   506,   507,   491,     0,     0,   298,   706,     0,
       0,   711,     0,   714,   715,     0,     0,   722,   723,     0,
       0,     0,     0,   687,     0,   742,   737,     0,     0,   125,
       0,     0,     0,     0,   186,   164,   145,   146,   147,   148,
     149,   144,   151,   153,   324,   443,   480,    40,   530,   532,
     386,   387,   388,   389,   385,   394,     0,    47,     0,     0,
       0,   565,   289,     0,     0,     0,     0,     0,     0,   157,
     159,     0,    51,   178,   510,   535,   375,   377,   379,   383,
     381,     0,   528,   557,   560,   601,   589,   591,   593,   595,
     597,   599,   469,   229,   473,   471,   476,   503,   303,   305,
     708,   710,   713,   718,   719,   717,   721,   725,   727,   729,
     731,   186,    44,     0,     0,     0,   215,   221,   223,   225,
       0,     0,     0,     0,     0,   239,     0,     0,   242,   244,
     246,     0,     0,     0,     0,   214,     0,   192,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   206,   213,
     207,   208,   209,   204,   205,   210,   211,   212,     0,   190,
       0,   187,   188,   328,     0,   325,   326,   447,     0,   444,
     445,   484,     0,   481,   482,   398,     0,   395,   396,   261,
     262,     0,   257,   259,   260,     0,   270,   271,   267,     0,
     265,   268,   269,   253,     0,   250,   252,   612,     0,   610,
     569,     0,   566,   567,   293,     0,   290,   291,     0,     0,
       0,     0,     0,     0,     0,   308,   310,   311,   312,   313,
     314,   315,   642,   648,     0,     0,     0,   641,   638,   639,
     640,     0,   631,   633,   636,   634,   635,   637,     0,     0,
       0,   283,     0,   276,   278,   279,   280,   281,   282,   662,
     664,   661,   659,   660,     0,   655,   657,   658,     0,   677,
       0,   680,   673,   674,     0,   668,   670,   671,   672,   675,
       0,   747,     0,   745,    53,   514,     0,   511,   512,   539,
       0,   536,   537,   606,   605,     0,   604,     0,    61,   733,
     167,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   181,   183,     0,   185,     0,     0,   323,     0,   451,
     440,     0,   488,   479,     0,     0,   393,     0,     0,   256,
     273,     0,   264,     0,     0,   249,   614,     0,   609,   573,
     564,     0,     0,   288,     0,     0,     0,     0,     0,     0,
       0,     0,   307,     0,     0,     0,     0,     0,     0,   630,
       0,     0,     0,     0,   275,     0,     0,     0,   654,     0,
       0,     0,     0,     0,   667,   683,     0,     0,   744,    55,
       0,    54,     0,   509,     0,     0,   534,     0,     0,   603,
     741,     0,     0,     0,     0,   227,   230,   231,   232,   233,
       0,   241,   234,     0,     0,     0,   236,   237,   238,   235,
     193,     0,   189,     0,   327,     0,   446,     0,   483,   438,
     413,   414,   415,   417,   418,   419,   406,   407,   422,   423,
     424,   425,   426,   429,   430,   431,   432,   433,   434,   435,
     436,   427,   428,   437,   402,   403,   404,   405,   411,   412,
     410,   416,     0,   400,   408,   420,   421,   409,   397,   258,
     266,     0,   251,   626,     0,   624,   625,   621,   622,   623,
       0,   615,   616,   618,   619,   620,   611,     0,   568,     0,
     292,   316,   317,   318,   319,   320,   321,   309,     0,     0,
     647,   650,   651,   632,   284,   285,   286,   277,     0,     0,
     656,   676,     0,   679,     0,   669,   761,     0,   759,   757,
     751,   755,   756,     0,   749,   753,   754,   752,   746,    52,
       0,     0,   513,     0,   538,     0,   217,   218,   219,   220,
     216,   222,   224,   226,   240,   243,   245,   247,   191,   329,
     448,   485,     0,   399,   254,     0,     0,   613,     0,   570,
     294,   644,   645,   646,   643,   649,   663,   665,   678,   681,
       0,     0,     0,     0,   748,    56,   515,   540,   607,   401,
       0,   628,   617,     0,   758,     0,   750,   627,     0,   760,
     765,     0,   763,     0,     0,   762,   774,     0,     0,     0,
     779,     0,   767,   769,   770,   771,   772,   773,   764,     0,
       0,     0,     0,     0,     0,   766,     0,   776,   777,   778,
       0,   768,   775,   780
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,   -10,  -949,  -549,  -949,
     393,  -949,  -949,  -949,  -949,   345,  -949,  -580,  -949,  -949,
    -949,   -71,  -949,  -949,  -949,  -949,  -949,  -949,   372,   640,
    -949,  -949,   -59,   -43,   -42,   -40,   -39,   -28,   -27,   -26,
     -23,   -21,   -15,    -9,    -3,  -949,    -1,    17,    18,    20,
    -949,   384,    25,  -949,    28,  -949,    30,    32,    35,  -949,
      38,  -949,    40,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,   375,   576,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,   296,  -949,    90,  -949,  -661,    98,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,   -67,
    -949,  -699,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,    76,  -949,  -949,  -949,  -949,  -949,    81,  -683,
    -949,  -949,  -949,  -949,    80,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,    50,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
      68,  -949,  -949,  -949,    72,   538,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,    66,  -949,  -949,  -949,  -949,  -949,  -949,
    -948,  -949,  -949,  -949,    97,  -949,  -949,  -949,   102,   597,
    -949,  -949,  -947,  -949,  -946,  -949,    44,  -949,    48,  -949,
      42,  -949,  -949,  -949,  -940,  -949,  -949,  -949,  -949,    92,
    -949,  -949,  -122,   996,  -949,  -949,  -949,  -949,  -949,   104,
    -949,  -949,  -949,   105,  -949,   558,  -949,   -66,  -949,  -949,
    -949,  -949,  -949,   -47,  -949,  -949,  -949,  -949,  -949,    13,
    -949,  -949,  -949,   116,  -949,  -949,  -949,   117,  -949,   570,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,    63,  -949,  -949,  -949,    69,   641,  -949,  -949,   -55,
    -949,     1,  -949,  -949,  -949,  -949,  -949,    59,  -949,  -949,
    -949,    65,   654,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
     -57,  -949,  -949,  -949,   108,  -949,  -949,  -949,   114,  -949,
     657,   367,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -939,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,   118,  -949,  -949,  -949,   -96,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,    96,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,    91,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,    83,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,   389,   564,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,
    -949,  -949,  -949,  -949,  -949,  -949,  -949,  -949,   430,   562,
    -949,  -949,  -949,  -949,  -949,  -949,    85,  -949,  -949,  -100,
    -949,  -949,  -949,  -949,  -949,  -949,  -119,  -949,  -949,  -138,
    -949,  -949,  -949,  -949,  -949,  -949,  -949
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     698,    87,    88,    41,    68,    84,    85,   723,   924,  1030,
    1031,   785,    43,    70,    90,   414,    45,    71,   150,   151,
     152,   416,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     442,   691,   171,   443,   172,   444,   173,   174,   175,   469,
     176,   470,   177,   178,   179,   180,   436,   181,   182,   418,
      47,    72,   212,   213,   214,   476,   215,   183,   419,   184,
     420,   185,   421,   810,   811,   812,   963,   786,   787,   788,
     941,  1180,   789,   942,   790,   943,   791,   944,   792,   793,
     513,   794,   795,   796,   797,   798,   799,   800,   801,   802,
     803,   950,   804,   805,   953,   806,   954,   807,   955,   186,
     458,   844,   845,   846,   983,   187,   455,   831,   832,   833,
     834,   188,   457,   839,   840,   841,   842,   189,   456,   190,
     465,   892,   893,   894,   895,   896,   191,   461,   855,   856,
     857,   992,    63,    80,   364,   365,   366,   526,   367,   527,
     192,   462,   864,   865,   866,   867,   868,   869,   870,   871,
     193,   448,   814,   815,   816,   966,    49,    73,   253,   254,
     255,   482,   256,   483,   257,   484,   258,   488,   259,   487,
     194,   453,   704,   261,   262,   195,   454,   826,   827,   828,
     975,  1102,  1103,   196,   449,    57,    77,   818,   819,   820,
     969,    59,    78,   329,   330,   331,   332,   333,   334,   335,
     512,   336,   516,   337,   515,   338,   339,   517,   340,   197,
     450,   822,   823,   824,   972,    61,    79,   350,   351,   352,
     353,   354,   521,   355,   356,   357,   358,   264,   480,   926,
     927,   928,  1032,    51,    74,   275,   276,   277,   492,   198,
     451,   199,   452,   267,   481,   930,   931,   932,  1035,    53,
      75,   291,   292,   293,   495,   294,   295,   497,   296,   297,
     200,   460,   851,   852,   853,   989,    55,    76,   309,   310,
     311,   312,   503,   313,   504,   314,   505,   315,   506,   316,
     507,   317,   508,   318,   502,   269,   489,   935,   936,  1038,
     201,   459,   848,   849,   986,  1120,  1121,  1122,  1123,  1124,
    1195,  1125,   202,   463,   881,   882,   883,  1003,  1204,   884,
     885,  1004,   886,   887,   203,   204,   466,   904,   905,   906,
    1015,   907,  1016,   205,   467,   914,   915,   916,   917,  1020,
     918,   919,  1022,   206,   468,    65,    81,   386,   387,   388,
     389,   531,   390,   532,   391,   392,   534,   393,   394,   395,
     537,   755,   396,   538,   397,   398,   399,   541,   400,   542,
     401,   543,   402,   544,   207,   417,    67,    82,   405,   406,
     407,   547,   408,   208,   472,   922,   923,  1026,  1163,  1164,
    1165,  1166,  1212,  1167,  1210,  1231,  1232,  1233,  1241,  1242,
    1243,  1249,  1244,  1245,  1246,  1247,  1253
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
     149,   211,   228,   271,   285,   305,    38,   327,   346,   363,
     383,   328,   347,   348,   229,   878,   268,   216,   265,   278,
     289,   307,   808,   341,   359,   838,   384,  1095,  1096,  1097,
     230,   231,   349,   232,   233,  1101,  1107,   829,    31,    30,
      32,   697,    33,   729,   299,   234,   235,   236,   361,   362,
     237,   933,   238,   753,   754,   735,   736,   737,   239,   686,
     687,   688,   689,   474,   240,   209,   210,    86,   475,    42,
     241,    44,   242,   217,   266,   279,   290,   308,   978,   342,
     360,   979,   385,   126,   127,    46,   263,   274,   288,   306,
     243,   244,   690,   245,   126,   127,    48,   478,   246,   126,
     127,   247,   479,   248,   490,   249,    50,   697,   250,   491,
      52,   251,   493,   252,    54,   260,   500,   494,   272,   286,
     830,   501,   273,   287,   148,   981,    91,    92,   982,    89,
      93,   528,   545,    94,    95,    96,   529,   546,    56,   126,
     127,   320,   908,   909,   910,    58,   888,   889,   890,   858,
     859,   860,   861,   862,   863,   899,   900,   403,   404,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   872,   549,
     361,   362,   911,   321,   550,   322,   323,   771,   124,   324,
     325,   326,   474,   148,   549,   126,   127,   938,   148,   939,
     126,   127,   128,  1176,  1177,  1178,  1179,   129,   130,   131,
     132,   133,   478,   134,    60,   960,   960,   940,   135,   410,
     961,   962,    34,    35,    36,    37,   984,   136,    62,   987,
     137,   985,   988,   411,  1095,  1096,  1097,   138,   148,  1001,
     412,    64,  1101,  1107,  1002,   139,   140,   126,   127,  1027,
     141,    66,  1028,   142,   766,   829,   836,   143,   837,   767,
     768,   769,   770,   771,   772,   773,   774,   775,   776,   777,
     778,   779,   780,   781,   782,   783,   784,  1008,   144,   145,
     146,   147,  1009,   125,  1013,  1017,  1023,   413,   838,  1014,
    1018,  1024,  1061,   873,   874,   875,   876,   125,   545,   878,
     321,   126,   127,  1025,   148,  1234,   321,   409,  1235,   148,
     280,   281,   282,   283,   284,   126,   127,   126,   127,   298,
     125,   415,   422,   125,   321,   299,   300,   301,   302,   303,
     304,   270,   423,   424,   225,   960,   510,   226,   126,   127,
    1188,   126,   127,  1201,  1202,  1203,   321,   343,   322,   323,
     344,   345,   425,   490,  1192,   509,   148,   225,  1189,  1193,
     226,  1113,  1114,   126,   127,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,  1236,
     426,   528,  1237,  1238,  1239,  1240,  1200,  1213,   511,   493,
     551,   552,  1214,   149,  1216,   500,  1254,   211,   427,   428,
    1217,  1255,   429,   430,  1156,   431,  1157,  1158,   432,   228,
     148,   433,   271,   216,   700,   701,   702,   703,   434,   285,
     435,   229,   437,   268,   148,   265,   148,   438,   278,   305,
     439,   440,   148,   441,   445,   289,   446,   230,   231,   327,
     232,   233,   447,   328,   346,   307,   464,   148,   347,   348,
     148,   471,   234,   235,   236,   341,   473,   237,   477,   238,
     359,   485,   486,   496,   383,   239,   498,   499,   349,   217,
     514,   240,   148,   518,   520,   519,   522,   241,   523,   242,
     384,   266,   525,   524,   279,   530,   533,   535,   536,   539,
     540,   290,   548,   263,   554,   553,   274,   243,   244,   561,
     245,   308,   555,   288,   556,   246,   557,   558,   247,   559,
     248,   342,   249,   306,   560,   250,   360,   562,   251,   563,
     252,   564,   260,   565,   566,   567,   568,   272,   575,   569,
     573,   273,   570,   581,   286,   571,   385,   572,   287,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   574,   576,   577,   582,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   578,   579,   125,   580,   583,
     584,   585,   586,   587,   588,   589,   590,   218,   591,   219,
     592,   593,   594,   595,   596,   126,   127,   220,   221,   222,
     223,   224,   128,   597,   598,   599,   600,   149,   601,   602,
     211,   604,   603,   605,   225,   606,   607,   226,   135,   608,
     609,   610,   611,   613,   614,   227,   216,   126,   127,   616,
     617,   618,   619,   620,   621,   623,   624,   622,   625,   627,
     629,   630,   631,   877,   891,   901,   632,   383,   635,   633,
     636,   637,   638,   639,   640,   641,   643,   644,   645,   879,
     897,   902,   912,   384,   646,   647,   648,   762,   649,   651,
     655,   656,   652,   653,   659,   660,   658,   662,   144,   145,
     661,   665,   217,   663,   666,   669,   664,   670,   671,   667,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   668,   148,   672,   674,   675,   677,   756,
     381,   382,   678,   679,   680,   880,   898,   903,   913,   385,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   681,   682,   683,   148,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   684,   125,   321,
     685,   692,   693,   694,   695,   696,   699,   705,    32,   706,
     707,   708,   719,   710,   709,   711,   126,   127,   712,   221,
     222,   713,   224,   128,   714,   715,   716,   717,   718,   721,
     722,   724,   720,   725,   726,   225,   731,   761,   226,   843,
     727,   728,   730,   732,   733,   734,   227,   738,   809,   813,
     817,   821,   739,   825,   847,   740,   850,   741,   854,   742,
     921,   925,   743,   744,   929,   945,   745,   946,   947,   746,
     747,   748,   750,   751,   948,   949,   951,   952,   956,   752,
     957,   958,   758,   959,   964,   965,   759,   967,   760,   968,
     970,   971,   974,   973,   977,  1045,   976,   991,   980,   144,
     145,   990,   993,   994,  1029,   995,   996,   997,   998,   999,
    1000,  1005,  1006,  1007,  1010,  1011,  1012,  1019,  1021,  1034,
    1046,  1033,  1037,  1036,  1041,   148,  1039,  1040,  1042,  1043,
    1044,  1048,  1050,  1053,  1054,  1047,  1049,  1051,  1052,  1055,
    1056,  1057,  1111,  1059,  1058,   228,  1131,  1132,   327,  1133,
    1134,   346,   328,  1135,  1069,   347,   348,   229,  1094,   268,
    1136,   265,  1138,  1139,   341,  1115,  1070,   359,   305,  1116,
    1105,   363,  1140,   230,   231,   349,   232,   233,  1148,  1141,
    1142,  1118,  1071,  1072,   307,  1073,  1074,   877,   234,   235,
     236,  1144,   891,   237,  1145,   238,   901,  1075,  1076,  1077,
    1149,   239,  1078,   879,  1079,  1159,  1152,   240,   897,  1160,
    1080,   271,   902,   241,   285,   242,  1081,   266,   912,  1154,
     342,  1161,  1082,   360,  1083,  1151,  1106,   278,  1169,   263,
     289,  1146,  1170,   243,   244,  1153,   245,  1119,  1104,  1175,
     308,   246,  1084,  1085,   247,  1086,   248,  1181,   249,  1117,
    1087,   250,   306,  1088,   251,  1089,   252,  1090,   260,   880,
    1091,  1182,  1190,  1092,   898,  1093,  1183,  1100,   903,  1098,
    1191,  1196,  1197,  1099,   913,  1198,  1199,  1162,  1211,  1184,
    1220,  1223,  1185,   279,  1186,  1225,   290,  1228,  1250,  1251,
    1230,  1252,  1187,  1256,  1260,   274,  1194,  1205,   288,   749,
     763,  1221,   835,   757,   615,  1062,   765,   937,  1060,  1109,
    1112,  1110,  1130,  1147,  1129,  1064,   657,  1137,  1063,  1108,
    1219,  1206,  1207,   319,  1065,  1066,   272,  1224,   650,   286,
     273,  1208,  1215,   287,  1258,  1218,  1227,   626,  1229,  1067,
    1068,  1259,  1257,  1262,  1263,   654,  1174,  1172,   934,  1128,
    1173,  1171,  1222,  1127,  1143,  1126,  1155,   920,  1150,   673,
     764,   676,  1168,  1226,   612,  1248,  1261,     0,     0,     0,
       0,  1069,     0,     0,     0,  1094,     0,  1115,     0,     0,
       0,  1116,     0,  1070,   628,     0,     0,  1105,     0,     0,
       0,     0,  1159,  1118,  1209,     0,  1160,     0,     0,  1071,
    1072,     0,  1073,  1074,   634,     0,     0,     0,  1161,     0,
       0,     0,     0,     0,  1075,  1076,  1077,   642,     0,  1078,
       0,  1079,     0,     0,     0,     0,     0,  1080,     0,     0,
       0,     0,     0,  1081,     0,     0,     0,     0,     0,  1082,
       0,  1083,     0,  1106,     0,     0,     0,     0,     0,  1119,
       0,     0,     0,     0,     0,  1104,     0,     0,     0,  1084,
    1085,  1117,  1086,     0,  1162,     0,     0,  1087,     0,     0,
    1088,     0,  1089,     0,  1090,     0,     0,  1091,     0,     0,
    1092,     0,  1093,     0,  1100,     0,  1098,     0,     0,     0,
    1099
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   714,    73,    72,    73,    74,
      75,    76,   683,    78,    79,   708,    81,   975,   975,   975,
      73,    73,    79,    73,    73,   975,   975,   116,     5,     0,
       7,   590,     9,   623,   114,    73,    73,    73,   123,   124,
      73,   121,    73,   166,   167,   635,   636,   637,    73,   169,
     170,   171,   172,     3,    73,    16,    17,   199,     8,     7,
      73,     7,    73,    72,    73,    74,    75,    76,     3,    78,
      79,     6,    81,    90,    91,     7,    73,    74,    75,    76,
      73,    73,   202,    73,    90,    91,     7,     3,    73,    90,
      91,    73,     8,    73,     3,    73,     7,   656,    73,     8,
       7,    73,     3,    73,     7,    73,     3,     8,    74,    75,
     199,     8,    74,    75,   199,     3,    11,    12,     6,    10,
      15,     3,     3,    18,    19,    20,     8,     8,     7,    90,
      91,    21,   149,   150,   151,     7,   142,   143,   144,   126,
     127,   128,   129,   130,   131,   146,   147,    13,    14,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    21,     3,
     123,   124,   199,    73,     8,    75,    76,    30,    71,    79,
      80,    81,     3,   199,     3,    90,    91,     8,   199,     8,
      90,    91,    97,    22,    23,    24,    25,   102,   103,   104,
     105,   106,     3,   108,     7,     3,     3,     8,   113,     3,
       8,     8,   199,   200,   201,   202,     3,   122,     7,     3,
     125,     8,     6,     4,  1192,  1192,  1192,   132,   199,     3,
       8,     7,  1192,  1192,     8,   140,   141,    90,    91,     3,
     145,     7,     6,   148,    21,   116,   117,   152,   119,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,     3,   173,   174,
     175,   176,     8,    72,     3,     3,     3,     3,   981,     8,
       8,     8,   963,   136,   137,   138,   139,    72,     3,  1008,
      73,    90,    91,     8,   199,     3,    73,     6,     6,   199,
      85,    86,    87,    88,    89,    90,    91,    90,    91,   108,
      72,     8,     4,    72,    73,   114,   115,   116,   117,   118,
     119,    83,     4,     4,   109,     3,     3,   112,    90,    91,
       8,    90,    91,   133,   134,   135,    73,    74,    75,    76,
      77,    78,     4,     3,     3,     8,   199,   109,     8,     8,
     112,   110,   111,    90,    91,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   178,
       4,     3,   181,   182,   183,   184,     8,     3,     8,     3,
     410,   411,     8,   474,     8,     3,     3,   478,     4,     4,
       8,     8,     4,     4,   177,     4,   179,   180,     4,   490,
     199,     4,   493,   478,    98,    99,   100,   101,     4,   500,
       4,   490,     4,   490,   199,   490,   199,     4,   493,   510,
       4,     4,   199,     4,     4,   500,     4,   490,   490,   520,
     490,   490,     4,   520,   525,   510,     4,   199,   525,   525,
     199,     4,   490,   490,   490,   520,     4,   490,     4,   490,
     525,     4,     4,     4,   545,   490,     4,     4,   525,   478,
       4,   490,   199,     4,     3,     8,     4,   490,     4,   490,
     545,   490,     3,     8,   493,     4,     4,     4,     4,     4,
       4,   500,     4,   490,     4,   199,   493,   490,   490,   200,
     490,   510,     4,   500,     4,   490,     4,     4,   490,     4,
     490,   520,   490,   510,     4,   490,   525,   200,   490,   200,
     490,   200,   490,   200,   200,   200,   200,   493,     4,   202,
     200,   493,   201,     4,   500,   201,   545,   201,   500,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,   200,   200,   200,     4,    61,    62,    63,    64,
      65,    66,    67,    68,    69,   202,   202,    72,   202,     4,
     202,   202,   202,     4,     4,     4,     4,    82,     4,    84,
       4,     4,     4,     4,     4,    90,    91,    92,    93,    94,
      95,    96,    97,     4,     4,     4,     4,   678,     4,     4,
     681,     4,   200,     4,   109,     4,     4,   112,   113,     4,
       4,   202,     4,     4,   202,   120,   681,    90,    91,     4,
       4,     4,     4,     4,   200,     4,     4,   202,     4,     4,
       4,   200,     4,   714,   715,   716,   200,   718,     4,   200,
       4,     4,     4,     4,     4,     4,     4,     4,   200,   714,
     715,   716,   717,   718,     4,     4,     4,   677,   202,     4,
       4,     4,   202,   202,     4,     4,   202,     4,   173,   174,
     200,     4,   681,   200,     4,     4,   200,     4,     4,   202,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   202,   199,     4,     4,   200,     4,   168,
     173,   174,     7,   199,     7,   714,   715,   716,   717,   718,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,     7,     7,     7,   199,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,     5,    72,    73,
     199,   199,   199,     5,     5,     5,   199,     5,     7,     5,
       5,     5,   199,     5,     7,     5,    90,    91,     5,    93,
      94,     7,    96,    97,     7,     7,     7,     7,     7,     5,
       5,     5,   199,     5,   199,   109,     7,     5,   112,   107,
     199,   199,   199,   199,   199,   199,   120,   199,     7,     7,
       7,     7,   199,     7,     7,   199,     7,   199,     7,   199,
       7,     7,   199,   199,     7,     4,   199,     4,     4,   199,
     199,   199,   199,   199,     4,     4,     4,     4,     4,   199,
       4,     4,   199,     4,     6,     3,   199,     6,   199,     3,
       6,     3,     3,     6,     3,   200,     6,     3,     6,   173,
     174,     6,     6,     3,   199,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     202,     6,     3,     6,     4,   199,     8,     6,     4,     4,
       4,   202,     4,     4,     4,   200,   200,   200,   200,     4,
     200,   200,     4,   200,   202,   966,   200,   200,   969,   200,
     200,   972,   969,   200,   975,   972,   972,   966,   975,   966,
     200,   966,     4,     4,   969,   986,   975,   972,   989,   986,
     975,   992,   200,   966,   966,   972,   966,   966,     4,   200,
     200,   986,   975,   975,   989,   975,   975,  1008,   966,   966,
     966,   202,  1013,   966,   200,   966,  1017,   975,   975,   975,
       4,   966,   975,  1008,   975,  1026,     4,   966,  1013,  1026,
     975,  1032,  1017,   966,  1035,   966,   975,   966,  1023,     4,
     969,  1026,   975,   972,   975,   202,   975,  1032,     6,   966,
    1035,   200,     3,   966,   966,   200,   966,   986,   975,     4,
     989,   966,   975,   975,   966,   975,   966,   199,   966,   986,
     975,   966,   989,   975,   966,   975,   966,   975,   966,  1008,
     975,   199,     8,   975,  1013,   975,   199,   975,  1017,   975,
       8,     4,     8,   975,  1023,     3,     8,  1026,     4,   199,
       4,     4,   199,  1032,   199,     4,  1035,     5,     4,     4,
       7,     4,   199,     4,     4,  1032,   199,   199,  1035,   656,
     678,   202,   707,   669,   478,   965,   681,   761,   960,   978,
     984,   981,   994,  1013,   992,   968,   528,  1001,   966,   977,
    1192,   199,   199,    77,   969,   971,  1032,   200,   520,  1035,
    1032,   199,   199,  1035,   200,   199,   199,   490,   199,   972,
     974,   200,   202,   199,   199,   525,  1037,  1034,   731,   991,
    1035,  1032,  1198,   989,  1008,   987,  1023,   718,  1017,   545,
     680,   549,  1027,  1213,   474,  1234,  1254,    -1,    -1,    -1,
      -1,  1192,    -1,    -1,    -1,  1192,    -1,  1198,    -1,    -1,
      -1,  1198,    -1,  1192,   493,    -1,    -1,  1192,    -1,    -1,
      -1,    -1,  1213,  1198,  1154,    -1,  1213,    -1,    -1,  1192,
    1192,    -1,  1192,  1192,   500,    -1,    -1,    -1,  1213,    -1,
      -1,    -1,    -1,    -1,  1192,  1192,  1192,   510,    -1,  1192,
      -1,  1192,    -1,    -1,    -1,    -1,    -1,  1192,    -1,    -1,
      -1,    -1,    -1,  1192,    -1,    -1,    -1,    -1,    -1,  1192,
      -1,  1192,    -1,  1192,    -1,    -1,    -1,    -1,    -1,  1198,
      -1,    -1,    -1,    -1,    -1,  1192,    -1,    -1,    -1,  1192,
    1192,  1198,  1192,    -1,  1213,    -1,    -1,  1192,    -1,    -1,
    1192,    -1,  1192,    -1,  1192,    -1,    -1,  1192,    -1,    -1,
    1192,    -1,  1192,    -1,  1192,    -1,  1192,    -1,    -1,    -1,
    1192
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
       0,     5,     7,     9,   199,   200,   201,   202,   219,   220,
     221,   226,     7,   235,     7,   239,     7,   283,     7,   389,
       7,   466,     7,   482,     7,   499,     7,   418,     7,   424,
       7,   448,     7,   365,     7,   568,     7,   599,   227,   222,
     236,   240,   284,   390,   467,   483,   500,   419,   425,   449,
     366,   569,   600,   219,   228,   229,   199,   224,   225,    10,
     237,    11,    12,    15,    18,    19,    20,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    90,    91,    97,   102,
     103,   104,   105,   106,   108,   113,   122,   125,   132,   140,
     141,   145,   148,   152,   173,   174,   175,   176,   199,   234,
     241,   242,   243,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   265,   267,   269,   270,   271,   273,   275,   276,   277,
     278,   280,   281,   290,   292,   294,   332,   338,   344,   350,
     352,   359,   373,   383,   403,   408,   416,   442,   472,   474,
     493,   523,   535,   547,   548,   556,   566,   597,   606,    16,
      17,   234,   285,   286,   287,   289,   472,   474,    82,    84,
      92,    93,    94,    95,    96,   109,   112,   120,   234,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   259,   260,   261,   262,   265,   267,   269,   270,
     271,   273,   275,   391,   392,   393,   395,   397,   399,   401,
     403,   406,   407,   442,   460,   472,   474,   476,   493,   518,
      83,   234,   399,   401,   442,   468,   469,   470,   472,   474,
      85,    86,    87,    88,    89,   234,   399,   401,   442,   472,
     474,   484,   485,   486,   488,   489,   491,   492,   108,   114,
     115,   116,   117,   118,   119,   234,   442,   472,   474,   501,
     502,   503,   504,   506,   508,   510,   512,   514,   516,   416,
      21,    73,    75,    76,    79,    80,    81,   234,   312,   426,
     427,   428,   429,   430,   431,   432,   434,   436,   438,   439,
     441,   472,   474,    74,    77,    78,   234,   312,   430,   436,
     450,   451,   452,   453,   454,   456,   457,   458,   459,   472,
     474,   123,   124,   234,   367,   368,   369,   371,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   173,   174,   234,   472,   474,   570,   571,   572,   573,
     575,   577,   578,   580,   581,   582,   585,   587,   588,   589,
     591,   593,   595,    13,    14,   601,   602,   603,   605,     6,
       3,     4,     8,     3,   238,     8,   244,   598,   282,   291,
     293,   295,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   279,     4,     4,     4,
       4,     4,   263,   266,   268,     4,     4,     4,   384,   417,
     443,   473,   475,   404,   409,   339,   351,   345,   333,   524,
     494,   360,   374,   536,     4,   353,   549,   557,   567,   272,
     274,     4,   607,     4,     3,     8,   288,     4,     3,     8,
     461,   477,   394,   396,   398,     4,     4,   402,   400,   519,
       3,     8,   471,     3,     8,   487,     4,   490,     4,     4,
       3,     8,   517,   505,   507,   509,   511,   513,   515,     8,
       3,     8,   433,   313,     4,   437,   435,   440,     4,     8,
       3,   455,     4,     4,     8,     3,   370,   372,     3,     8,
       4,   574,   576,     4,   579,     4,     4,   583,   586,     4,
       4,   590,   592,   594,   596,     3,     8,   604,     4,     3,
       8,   219,   219,   199,     4,     4,     4,     4,     4,     4,
       4,   200,   200,   200,   200,   200,   200,   200,   200,   202,
     201,   201,   201,   200,   200,     4,   200,   200,   202,   202,
     202,     4,     4,     4,   202,   202,   202,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   200,     4,     4,     4,     4,     4,     4,
     202,     4,   242,     4,   202,   286,     4,     4,     4,     4,
       4,   200,   202,     4,     4,     4,   392,     4,   469,     4,
     200,     4,   200,   200,   485,     4,     4,     4,     4,     4,
       4,     4,   503,     4,     4,   200,     4,     4,     4,   202,
     428,     4,   202,   202,   452,     4,     4,   368,   202,     4,
       4,   200,     4,   200,   200,     4,     4,   202,   202,     4,
       4,     4,     4,   571,     4,   200,   602,     4,     7,   199,
       7,     7,     7,     7,     5,   199,   169,   170,   171,   172,
     202,   264,   199,   199,     5,     5,     5,   221,   223,   199,
      98,    99,   100,   101,   405,     5,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   199,
     199,     5,     5,   230,     5,     5,   199,   199,   199,   230,
     199,     7,   199,   199,   199,   230,   230,   230,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   223,
     199,   199,   199,   166,   167,   584,   168,   264,   199,   199,
     199,     5,   219,   241,   601,   285,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,   234,   300,   301,   302,   305,
     307,   309,   311,   312,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   325,   326,   328,   330,   300,     7,
     296,   297,   298,     7,   385,   386,   387,     7,   420,   421,
     422,     7,   444,   445,   446,     7,   410,   411,   412,   116,
     199,   340,   341,   342,   343,   228,   117,   119,   342,   346,
     347,   348,   349,   107,   334,   335,   336,     7,   525,   526,
       7,   495,   496,   497,     7,   361,   362,   363,   126,   127,
     128,   129,   130,   131,   375,   376,   377,   378,   379,   380,
     381,   382,    21,   136,   137,   138,   139,   234,   314,   472,
     474,   537,   538,   539,   542,   543,   545,   546,   142,   143,
     144,   234,   354,   355,   356,   357,   358,   472,   474,   146,
     147,   234,   472,   474,   550,   551,   552,   554,   149,   150,
     151,   199,   472,   474,   558,   559,   560,   561,   563,   564,
     570,     7,   608,   609,   231,     7,   462,   463,   464,     7,
     478,   479,   480,   121,   504,   520,   521,   296,     8,     8,
       8,   303,   306,   308,   310,     4,     4,     4,     4,     4,
     324,     4,     4,   327,   329,   331,     4,     4,     4,     4,
       3,     8,     8,   299,     6,     3,   388,     6,     3,   423,
       6,     3,   447,     6,     3,   413,     6,     3,     3,     6,
       6,     3,     6,   337,     3,     8,   527,     3,     6,   498,
       6,     3,   364,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   540,   544,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   553,   555,     3,     8,     4,
     562,     4,   565,     3,     8,     8,   610,     3,     6,   199,
     232,   233,   465,     6,     3,   481,     6,     3,   522,     8,
       6,     4,     4,     4,     4,   200,   202,   200,   202,   200,
       4,   200,   200,     4,     4,     4,   200,   200,   202,   200,
     301,   300,   298,   391,   387,   426,   422,   450,   446,   234,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   259,   260,   261,   262,   265,   267,   269,
     270,   271,   273,   275,   312,   383,   395,   397,   399,   401,
     403,   407,   414,   415,   442,   472,   474,   518,   412,   341,
     347,     4,   335,   110,   111,   234,   312,   442,   472,   474,
     528,   529,   530,   531,   532,   534,   526,   501,   497,   367,
     363,   200,   200,   200,   200,   200,   200,   376,     4,     4,
     200,   200,   200,   538,   202,   200,   200,   355,     4,     4,
     551,   202,     4,   200,     4,   559,   177,   179,   180,   234,
     312,   472,   474,   611,   612,   613,   614,   616,   609,     6,
       3,   468,   464,   484,   480,     4,    22,    23,    24,    25,
     304,   199,   199,   199,   199,   199,   199,   199,     8,     8,
       8,     8,     3,     8,   199,   533,     4,     8,     3,     8,
       8,   133,   134,   135,   541,   199,   199,   199,   199,   219,
     617,     4,   615,     3,     8,   199,     8,     8,   199,   415,
       4,   202,   530,     4,   200,     4,   612,   199,     5,   199,
       7,   618,   619,   620,     3,     6,   178,   181,   182,   183,
     184,   621,   622,   623,   625,   626,   627,   628,   619,   624,
       4,     4,     4,   629,     3,     8,     4,   202,   200,   200,
       4,   622,   199,   199
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   203,   205,   204,   206,   204,   207,   204,   208,   204,
     209,   204,   210,   204,   211,   204,   212,   204,   213,   204,
     214,   204,   215,   204,   216,   204,   217,   204,   218,   204,
     219,   219,   219,   219,   219,   219,   219,   220,   222,   221,
     223,   224,   224,   225,   225,   227,   226,   228,   228,   229,
     229,   231,   230,   232,   232,   233,   233,   234,   236,   235,
     238,   237,   240,   239,   241,   241,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   244,   243,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   263,   262,   264,   264,   264,   264,   264,
     266,   265,   268,   267,   269,   270,   272,   271,   274,   273,
     275,   276,   277,   279,   278,   280,   282,   281,   284,   283,
     285,   285,   286,   286,   286,   286,   286,   288,   287,   289,
     291,   290,   293,   292,   295,   294,   296,   296,   297,   297,
     299,   298,   300,   300,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,   301,   303,   302,   304,   304,   304,
     304,   306,   305,   308,   307,   310,   309,   311,   313,   312,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   324,
     323,   325,   327,   326,   329,   328,   331,   330,   333,   332,
     334,   334,   335,   337,   336,   339,   338,   340,   340,   341,
     341,   342,   343,   345,   344,   346,   346,   347,   347,   347,
     348,   349,   351,   350,   353,   352,   354,   354,   355,   355,
     355,   355,   355,   355,   356,   357,   358,   360,   359,   361,
     361,   362,   362,   364,   363,   366,   365,   367,   367,   367,
     368,   368,   370,   369,   372,   371,   374,   373,   375,   375,
     376,   376,   376,   376,   376,   376,   377,   378,   379,   380,
     381,   382,   384,   383,   385,   385,   386,   386,   388,   387,
     390,   389,   391,   391,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   394,   393,   396,   395,   398,   397,
     400,   399,   402,   401,   404,   403,   405,   405,   405,   405,
     406,   407,   409,   408,   410,   410,   411,   411,   413,   412,
     414,   414,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   417,
     416,   419,   418,   420,   420,   421,   421,   423,   422,   425,
     424,   426,   426,   427,   427,   428,   428,   428,   428,   428,
     428,   428,   428,   428,   428,   429,   430,   431,   433,   432,
     435,   434,   437,   436,   438,   440,   439,   441,   443,   442,
     444,   444,   445,   445,   447,   446,   449,   448,   450,   450,
     451,   451,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   453,   455,   454,   456,   457,   458,   459,   461,   460,
     462,   462,   463,   463,   465,   464,   467,   466,   468,   468,
     469,   469,   469,   469,   469,   469,   469,   471,   470,   473,
     472,   475,   474,   477,   476,   478,   478,   479,   479,   481,
     480,   483,   482,   484,   484,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   487,   486,   488,   490,
     489,   491,   492,   494,   493,   495,   495,   496,   496,   498,
     497,   500,   499,   501,   501,   502,   502,   503,   503,   503,
     503,   503,   503,   503,   503,   503,   503,   503,   505,   504,
     507,   506,   509,   508,   511,   510,   513,   512,   515,   514,
     517,   516,   519,   518,   520,   520,   522,   521,   524,   523,
     525,   525,   527,   526,   528,   528,   529,   529,   530,   530,
     530,   530,   530,   530,   530,   531,   533,   532,   534,   536,
     535,   537,   537,   538,   538,   538,   538,   538,   538,   538,
     538,   538,   540,   539,   541,   541,   541,   542,   544,   543,
     545,   546,   547,   549,   548,   550,   550,   551,   551,   551,
     551,   551,   553,   552,   555,   554,   557,   556,   558,   558,
     559,   559,   559,   559,   559,   559,   560,   562,   561,   563,
     565,   564,   567,   566,   569,   568,   570,   570,   571,   571,
     571,   571,   571,   571,   571,   571,   571,   571,   571,   571,
     571,   571,   571,   571,   571,   571,   572,   574,   573,   576,
     575,   577,   579,   578,   580,   581,   583,   582,   584,   584,
     586,   585,   587,   588,   590,   589,   592,   591,   594,   593,
     596,   595,   598,   597,   600,   599,   601,   601,   602,   602,
     604,   603,   605,   607,   606,   608,   608,   610,   609,   611,
     611,   612,   612,   612,   612,   612,   612,   612,   613,   615,
     614,   617,   616,   618,   618,   620,   619,   621,   621,   622,
     622,   622,   622,   622,   624,   623,   625,   626,   627,   629,
     628
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     0,     4,
       3,     3,     3,     0,     4,     3,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     3,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       0,     6,     3,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"data-directory\"",
  "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"consistency\"",
  "\"serial-consistency\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max-age\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"store-extended-info\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"ip-reservations-unique\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6",
  "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION",
  "SUB_OPTION_DEFS", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_CONFIG_CONTROL",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "value", "sub_json", "map2", "$@15", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_object", "$@19", "sub_dhcp6", "$@20", "global_params",
  "global_param", "data_directory", "$@21", "preferred_lifetime",
  "min_preferred_lifetime", "max_preferred_lifetime", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "cache_threshold", "cache_max_age", "decline_probation_period",
  "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@22",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@23",
  "ddns_qualifying_suffix", "$@24", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "hostname_char_set", "$@25",
  "hostname_char_replacement", "$@26", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "server_tag", "$@27", "ip_reservations_unique", "interfaces_config",
  "$@28", "sub_interfaces6", "$@29", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@30", "re_detect",
  "lease_database", "$@31", "hosts_database", "$@32", "hosts_databases",
  "$@33", "database_list", "not_empty_database_list", "database", "$@34",
  "database_map_params", "database_map_param", "database_type", "$@35",
  "db_type", "user", "$@36", "password", "$@37", "host", "$@38", "port",
  "name", "$@39", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "max_row_errors", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@40",
  "max_reconnect_tries", "keyspace", "$@41", "consistency", "$@42",
  "serial_consistency", "$@43", "sanity_checks", "$@44",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@45",
  "mac_sources", "$@46", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@47",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@48",
  "dhcp_multi_threading", "$@49", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@50", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@51",
  "sub_hooks_library", "$@52", "hooks_params", "hooks_param", "library",
  "$@53", "parameters", "$@54", "expired_leases_processing", "$@55",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@56",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@57",
  "sub_subnet6", "$@58", "subnet6_params", "subnet6_param", "subnet",
  "$@59", "interface", "$@60", "interface_id", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@65",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@66", "shared_network_params", "shared_network_param",
  "option_def_list", "$@67", "sub_option_def_list", "$@68",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@69", "sub_option_def", "$@70",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool6", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "pd_pools_list", "$@85",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@86", "sub_pd_pool", "$@87", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@88", "pd_prefix_len", "excluded_prefix", "$@89",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@90",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@91", "sub_reservation", "$@92", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@93", "prefixes", "$@94", "duid", "$@95", "hw_address", "$@96",
  "hostname", "$@97", "flex_id_value", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "ip_address", "$@101", "client_classes", "$@102", "client_classes_list",
  "client_class_entry", "$@103", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@104", "only_if_required",
  "server_id", "$@105", "server_id_params", "server_id_param",
  "server_id_type", "$@106", "duid_type", "htype", "identifier", "$@107",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@108",
  "control_socket_params", "control_socket_param", "socket_type", "$@109",
  "socket_name", "$@110", "dhcp_queue_control", "$@111",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@112", "capacity", "arbitrary_map_entry", "$@113",
  "dhcp_ddns", "$@114", "sub_dhcp_ddns", "$@115", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@116",
  "server_ip", "$@117", "server_port", "sender_ip", "$@118", "sender_port",
  "max_queue_size", "ncr_protocol", "$@119", "ncr_protocol_value",
  "ncr_format", "$@120", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@121",
  "dep_generated_prefix", "$@122", "dep_hostname_char_set", "$@123",
  "dep_hostname_char_replacement", "$@124", "config_control", "$@125",
  "sub_config_control", "$@126", "config_control_params",
  "config_control_param", "config_databases", "$@127",
  "config_fetch_wait_time", "loggers", "$@128", "loggers_entries",
  "logger_entry", "$@129", "logger_params", "logger_param", "debuglevel",
  "severity", "$@130", "output_options_list", "$@131",
  "output_options_list_content", "output_entry", "$@132",
  "output_params_list", "output_params", "output", "$@133", "flush",
  "maxsize", "maxver", "pattern", "$@134", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   288,   288,   288,   289,   289,   290,   290,   291,   291,
     292,   292,   293,   293,   294,   294,   295,   295,   296,   296,
     297,   297,   298,   298,   299,   299,   300,   300,   301,   301,
     309,   310,   311,   312,   313,   314,   315,   318,   323,   323,
     334,   337,   338,   341,   346,   354,   354,   361,   362,   365,
     369,   376,   376,   383,   384,   387,   391,   402,   411,   411,
     426,   426,   443,   443,   452,   453,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   513,   514,   515,   518,   518,   527,   533,   539,   545,
     551,   557,   563,   569,   575,   581,   587,   593,   599,   605,
     611,   617,   623,   629,   629,   638,   641,   644,   647,   650,
     656,   656,   665,   665,   674,   680,   686,   686,   695,   695,
     704,   710,   716,   722,   722,   731,   737,   737,   749,   749,
     758,   759,   762,   763,   764,   765,   766,   769,   769,   780,
     786,   786,   799,   799,   812,   812,   823,   824,   827,   828,
     831,   831,   841,   842,   845,   846,   847,   848,   849,   850,
     851,   852,   853,   854,   855,   856,   857,   858,   859,   860,
     861,   862,   863,   864,   865,   868,   868,   876,   877,   878,
     879,   882,   882,   891,   891,   900,   900,   909,   915,   915,
     924,   930,   936,   942,   948,   954,   960,   966,   972,   978,
     978,   987,   993,   993,  1002,  1002,  1011,  1011,  1020,  1020,
    1031,  1032,  1034,  1036,  1036,  1055,  1055,  1066,  1067,  1070,
    1071,  1074,  1079,  1084,  1084,  1095,  1096,  1099,  1100,  1101,
    1104,  1109,  1116,  1116,  1129,  1129,  1142,  1143,  1146,  1147,
    1148,  1149,  1150,  1151,  1154,  1160,  1166,  1172,  1172,  1183,
    1184,  1187,  1188,  1191,  1191,  1201,  1201,  1211,  1212,  1213,
    1216,  1217,  1220,  1220,  1229,  1229,  1238,  1238,  1250,  1251,
    1254,  1255,  1256,  1257,  1258,  1259,  1262,  1268,  1274,  1280,
    1286,  1292,  1301,  1301,  1315,  1316,  1319,  1320,  1327,  1327,
    1353,  1353,  1364,  1365,  1369,  1370,  1371,  1372,  1373,  1374,
    1375,  1376,  1377,  1378,  1379,  1380,  1381,  1382,  1383,  1384,
    1385,  1386,  1387,  1388,  1389,  1390,  1391,  1392,  1393,  1394,
    1395,  1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,
    1405,  1406,  1407,  1408,  1411,  1411,  1420,  1420,  1429,  1429,
    1438,  1438,  1447,  1447,  1458,  1458,  1466,  1467,  1468,  1469,
    1472,  1478,  1486,  1486,  1498,  1499,  1503,  1504,  1507,  1507,
    1515,  1516,  1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,
    1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,  1536,
    1537,  1538,  1539,  1540,  1541,  1542,  1543,  1544,  1545,  1546,
    1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,  1562,
    1562,  1576,  1576,  1585,  1586,  1589,  1590,  1595,  1595,  1610,
    1610,  1624,  1625,  1628,  1629,  1632,  1633,  1634,  1635,  1636,
    1637,  1638,  1639,  1640,  1641,  1644,  1646,  1652,  1654,  1654,
    1663,  1663,  1672,  1672,  1681,  1683,  1683,  1692,  1702,  1702,
    1715,  1716,  1721,  1722,  1727,  1727,  1739,  1739,  1751,  1752,
    1757,  1758,  1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,
    1771,  1774,  1776,  1776,  1785,  1787,  1789,  1795,  1804,  1804,
    1817,  1818,  1821,  1822,  1825,  1825,  1835,  1835,  1845,  1846,
    1849,  1850,  1851,  1852,  1853,  1854,  1855,  1858,  1858,  1867,
    1867,  1892,  1892,  1922,  1922,  1935,  1936,  1939,  1940,  1943,
    1943,  1955,  1955,  1967,  1968,  1971,  1972,  1973,  1974,  1975,
    1976,  1977,  1978,  1979,  1980,  1981,  1984,  1984,  1993,  1999,
    1999,  2008,  2014,  2023,  2023,  2034,  2035,  2038,  2039,  2042,
    2042,  2051,  2051,  2060,  2061,  2064,  2065,  2069,  2070,  2071,
    2072,  2073,  2074,  2075,  2076,  2077,  2078,  2079,  2082,  2082,
    2093,  2093,  2104,  2104,  2113,  2113,  2122,  2122,  2131,  2131,
    2140,  2140,  2154,  2154,  2165,  2166,  2169,  2169,  2181,  2181,
    2192,  2193,  2196,  2196,  2206,  2207,  2210,  2211,  2214,  2215,
    2216,  2217,  2218,  2219,  2220,  2223,  2225,  2225,  2234,  2243,
    2243,  2256,  2257,  2260,  2261,  2262,  2263,  2264,  2265,  2266,
    2267,  2268,  2271,  2271,  2279,  2280,  2281,  2284,  2290,  2290,
    2299,  2305,  2313,  2321,  2321,  2332,  2333,  2336,  2337,  2338,
    2339,  2340,  2343,  2343,  2352,  2352,  2364,  2364,  2377,  2378,
    2381,  2382,  2383,  2384,  2385,  2386,  2389,  2395,  2395,  2404,
    2410,  2410,  2420,  2420,  2433,  2433,  2443,  2444,  2447,  2448,
    2449,  2450,  2451,  2452,  2453,  2454,  2455,  2456,  2457,  2458,
    2459,  2460,  2461,  2462,  2463,  2464,  2467,  2474,  2474,  2483,
    2483,  2492,  2498,  2498,  2507,  2513,  2519,  2519,  2528,  2529,
    2532,  2532,  2542,  2549,  2556,  2556,  2565,  2565,  2575,  2575,
    2585,  2585,  2597,  2597,  2609,  2609,  2619,  2620,  2624,  2625,
    2628,  2628,  2639,  2647,  2647,  2660,  2661,  2665,  2665,  2673,
    2674,  2677,  2678,  2679,  2680,  2681,  2682,  2683,  2686,  2692,
    2692,  2701,  2701,  2712,  2713,  2716,  2716,  2724,  2725,  2728,
    2729,  2730,  2731,  2732,  2735,  2735,  2744,  2750,  2756,  2762,
    2762
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
#line 5663 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2771 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
