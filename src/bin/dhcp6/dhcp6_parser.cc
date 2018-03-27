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
      case 179: // value
      case 183: // map_value
      case 233: // db_type
      case 314: // hr_mode
      case 448: // duid_type
      case 481: // ncr_protocol_value
      case 489: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 162: // "boolean"
        value.move< bool > (that.value);
        break;

      case 161: // "floating point"
        value.move< double > (that.value);
        break;

      case 160: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 159: // "constant string"
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
      case 179: // value
      case 183: // map_value
      case 233: // db_type
      case 314: // hr_mode
      case 448: // duid_type
      case 481: // ncr_protocol_value
      case 489: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 162: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 161: // "floating point"
        value.copy< double > (that.value);
        break;

      case 160: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 159: // "constant string"
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
            case 159: // "constant string"

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 160: // "integer"

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 161: // "floating point"

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 162: // "boolean"

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 179: // value

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 183: // map_value

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 233: // db_type

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 314: // hr_mode

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 448: // duid_type

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 481: // ncr_protocol_value

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 489: // replace_client_name_value

#line 235 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 179: // value
      case 183: // map_value
      case 233: // db_type
      case 314: // hr_mode
      case 448: // duid_type
      case 481: // ncr_protocol_value
      case 489: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 162: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 161: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 160: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 159: // "constant string"
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
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 319 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 323 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 345 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 371 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 608 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 685 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1497 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1575 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1725 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 988 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1799 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1012 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1022 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1029 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1897 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1906 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1955 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1981 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1189 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2060 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1199 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2088 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2106 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1232 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2191 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1391 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2505 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1596 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2601 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2703 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2810 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1769 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1770 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1771 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3007 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1942 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3117 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1980 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1983 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 2005 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 2007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 2012 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3356 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2118 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2153 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 623:
#line 2158 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2163 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3457 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3461 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -774;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     307,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,    34,    40,    37,    39,    50,
      67,    97,   110,   189,   198,   227,   228,   237,   238,   239,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,    40,  -118,
      19,    49,    38,   212,    74,    18,   223,   115,    68,   144,
     -51,   436,   124,  -774,   266,   270,   289,   302,   294,  -774,
    -774,  -774,  -774,  -774,   316,  -774,   131,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,   339,   347,   349,
     358,   360,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,   362,  -774,  -774,  -774,   132,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,   375,  -774,   141,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     376,   379,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,   147,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,   151,  -774,  -774,  -774,  -774,  -774,   380,  -774,   382,
     383,  -774,  -774,  -774,  -774,  -774,   172,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   305,   386,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   384,  -774,  -774,   389,  -774,  -774,
    -774,   390,  -774,  -774,   388,   387,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   393,
     395,  -774,  -774,  -774,  -774,   397,   404,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   173,
    -774,  -774,  -774,   406,  -774,  -774,   407,  -774,   408,   409,
    -774,  -774,   410,   411,   412,  -774,  -774,  -774,  -774,  -774,
     195,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,   233,  -774,  -774,
    -774,    40,    40,  -774,   258,   414,   416,   417,   418,   419,
    -774,    19,  -774,   420,   421,   424,   427,   274,   275,   276,
     277,   278,   435,   440,   441,   442,   443,   444,   445,   446,
     462,   463,   464,   465,   466,   312,   467,   470,    49,  -774,
     471,   314,    38,  -774,   473,   475,   476,   477,   478,   323,
     322,   481,   482,   483,   484,   212,  -774,   485,    74,  -774,
     486,   331,   488,   333,   334,    18,  -774,   497,   498,   499,
     500,   501,   502,   503,  -774,   223,  -774,   504,   505,   350,
     507,   508,   509,   353,  -774,    68,   512,   359,   363,  -774,
     144,   516,   518,    42,  -774,   365,   520,   522,   369,   526,
     372,   374,   527,   531,   377,   378,   381,   532,   533,   436,
    -774,   534,   124,  -774,  -774,  -774,   537,   535,   555,    40,
      40,    40,  -774,   556,   557,   558,   539,  -774,  -774,  -774,
    -774,  -774,   561,   562,   563,   564,   413,   565,   568,   569,
     570,   571,   572,   573,   574,  -774,   575,   576,  -774,   579,
    -774,  -774,   580,   581,   428,   429,   430,  -774,  -774,    12,
     431,   586,   585,  -774,   434,  -774,   437,  -774,   438,  -774,
    -774,  -774,   579,   579,   579,   439,   447,   448,   449,  -774,
     450,   451,  -774,   452,   453,   454,  -774,  -774,   455,  -774,
    -774,  -774,   456,    40,  -774,  -774,   457,   458,  -774,   459,
    -774,  -774,    99,   472,  -774,  -774,  -774,   -59,   460,  -774,
     589,  -774,    40,    49,   124,  -774,  -774,  -774,    38,   187,
     187,   592,   594,   595,   596,  -774,  -774,  -774,   597,   -45,
      40,   250,   598,   613,    73,   125,    36,   436,  -774,  -774,
     614,   615,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     616,   490,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   617,  -774,   235,   245,   251,  -774,
    -774,  -774,  -774,   621,   622,   623,   624,   625,  -774,   626,
     627,  -774,   628,   629,   630,  -774,   252,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,   254,  -774,   631,   566,  -774,
    -774,   632,   633,  -774,  -774,   634,   636,  -774,  -774,   635,
     639,  -774,  -774,   637,   641,  -774,  -774,  -774,   335,  -774,
    -774,  -774,   640,  -774,  -774,  -774,   336,  -774,  -774,  -774,
    -774,   355,  -774,  -774,   642,   644,  -774,   645,   646,   647,
     648,   649,   650,   261,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,   651,   652,   653,  -774,  -774,  -774,  -774,
     262,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   279,  -774,  -774,  -774,   280,   506,  -774,   654,
     655,  -774,  -774,   656,   658,  -774,  -774,   657,   661,  -774,
    -774,   659,  -774,   367,  -774,  -774,  -774,  -774,   662,   664,
     665,   666,   511,   510,   513,   514,   515,   670,   517,   519,
     674,   521,   523,   524,   187,  -774,  -774,   187,  -774,   592,
     212,  -774,   594,    68,  -774,   595,   144,  -774,   596,   364,
    -774,   597,   -45,  -774,  -774,   250,  -774,    65,   598,  -774,
     -51,  -774,   613,   525,   528,   529,   530,   536,   538,    73,
    -774,   676,   678,   540,   541,   542,   125,  -774,   680,   683,
      36,  -774,  -774,  -774,   685,   689,    74,  -774,   614,    18,
    -774,   615,   223,  -774,   616,   690,  -774,   102,   617,  -774,
     310,   544,   545,   546,  -774,  -774,  -774,  -774,  -774,   547,
    -774,  -774,   548,  -774,  -774,  -774,  -774,   286,  -774,   287,
    -774,   687,  -774,   691,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,   293,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   700,   694,  -774,  -774,  -774,  -774,   308,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,    -6,   550,  -774,
    -774,  -774,  -774,   552,   553,  -774,  -774,   559,   309,  -774,
     311,  -774,   706,  -774,   567,  -774,   711,  -774,  -774,  -774,
    -774,  -774,   318,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   364,  -774,   713,  -774,    65,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     716,   577,   719,   102,  -774,  -774,   588,  -774,   688,  -774,
     599,  -774,  -774,   638,  -774,  -774,   371,  -774,   -34,   638,
    -774,  -774,   720,   725,   727,   324,  -774,  -774,  -774,  -774,
    -774,  -774,   729,   578,   591,   601,   -34,  -774,   606,  -774,
    -774,  -774,  -774,  -774
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   107,     9,   241,    11,
     382,    13,   406,    15,   435,    17,   307,    19,   315,    21,
     352,    23,   206,    25,   528,    27,   585,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   437,     0,   317,   354,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     583,   577,   579,   581,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   105,   119,   121,   123,     0,     0,     0,
       0,     0,   233,   305,   344,   394,   396,   279,   179,   196,
     187,   470,   198,   217,   489,     0,   513,   526,    99,     0,
      72,    74,    75,    76,    77,    78,    81,    82,    83,    84,
      85,    87,    86,    91,    92,    79,    80,    89,    90,    97,
      98,    88,    93,    94,    95,    96,   116,     0,   115,     0,
     109,   111,   112,   113,   114,   374,   398,   264,   266,   268,
       0,     0,   272,   270,   427,   466,   263,   245,   246,   247,
     248,     0,   243,   252,   253,   254,   257,   259,   255,   256,
     249,   250,   261,   262,   251,   258,   260,   392,   391,   388,
     387,     0,   384,   386,   389,   390,   420,     0,   423,     0,
       0,   419,   414,   413,   417,   418,     0,   408,   410,   411,
     415,   416,   412,   464,   452,   454,   456,   458,   460,   462,
     451,   448,   449,   450,     0,   438,   439,   443,   444,   441,
     445,   446,   447,   442,     0,   334,   164,     0,   338,   336,
     341,     0,   330,   331,     0,   318,   319,   321,   333,   322,
     323,   324,   340,   325,   326,   327,   328,   329,   368,     0,
       0,   366,   367,   370,   371,     0,   355,   356,   358,   359,
     360,   361,   362,   363,   364,   365,   213,   215,   210,     0,
     208,   211,   212,     0,   550,   552,     0,   555,     0,     0,
     559,   563,     0,     0,     0,   568,   575,   548,   546,   547,
       0,   530,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   590,     0,   587,   589,
      46,     0,     0,    39,     0,     0,     0,     0,     0,     0,
      57,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    71,
       0,     0,     0,   108,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   242,     0,     0,   383,
       0,     0,     0,     0,     0,     0,   407,     0,     0,     0,
       0,     0,     0,     0,   436,     0,   308,     0,     0,     0,
       0,     0,     0,     0,   316,     0,     0,     0,     0,   353,
       0,     0,     0,     0,   207,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     529,     0,     0,   586,    50,    43,     0,     0,     0,     0,
       0,     0,    61,     0,     0,     0,     0,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   512,     0,     0,    73,     0,
     118,   110,     0,     0,     0,     0,     0,   277,   278,     0,
       0,     0,     0,   244,     0,   385,     0,   422,     0,   425,
     426,   409,     0,     0,     0,     0,     0,     0,     0,   440,
       0,     0,   332,     0,     0,     0,   343,   320,     0,   372,
     373,   357,     0,     0,   209,   549,     0,     0,   554,     0,
     557,   558,     0,     0,   565,   566,   567,     0,     0,   531,
       0,   588,     0,     0,     0,   578,   580,   582,     0,     0,
       0,   125,   235,   309,   346,    40,   395,   397,   281,     0,
      47,     0,     0,   200,     0,     0,     0,     0,    51,   117,
     376,   400,   265,   267,   269,   274,   275,   276,   273,   271,
     429,     0,   393,   421,   424,   465,   453,   455,   457,   459,
     461,   463,   335,   165,   339,   337,   342,   369,   214,   216,
     551,   553,   556,   561,   562,   560,   564,   570,   571,   572,
     573,   574,   569,   576,     0,    44,     0,     0,     0,   151,
     157,   159,   161,     0,     0,     0,     0,     0,   174,     0,
       0,   177,     0,     0,     0,   150,     0,   131,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   145,   146,
     147,   148,   143,   144,   149,     0,   129,     0,   126,   127,
     239,     0,   236,   237,   313,     0,   310,   311,   350,     0,
     347,   348,   285,     0,   282,   283,   185,   186,     0,   181,
     183,   184,     0,   194,   195,   191,     0,   189,   192,   193,
     474,     0,   472,   204,     0,   201,   202,     0,     0,     0,
       0,     0,     0,     0,   219,   221,   222,   223,   224,   225,
     226,   502,   508,     0,     0,     0,   501,   498,   499,   500,
       0,   491,   493,   496,   494,   495,   497,   522,   524,   521,
     519,   520,     0,   515,   517,   518,     0,    53,   380,     0,
     377,   378,   404,     0,   401,   402,   433,     0,   430,   431,
     468,     0,   594,     0,   592,    69,   584,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   120,   122,     0,   124,     0,
       0,   234,     0,   317,   306,     0,   354,   345,     0,     0,
     280,     0,     0,   180,   197,     0,   188,   476,     0,   471,
       0,   199,     0,     0,     0,     0,     0,     0,     0,     0,
     218,     0,     0,     0,     0,     0,     0,   490,     0,     0,
       0,   514,   527,    55,     0,    54,     0,   375,     0,     0,
     399,     0,   437,   428,     0,     0,   467,     0,     0,   591,
       0,     0,     0,     0,   163,   166,   167,   168,   169,     0,
     176,   170,     0,   171,   172,   173,   132,     0,   128,     0,
     238,     0,   312,     0,   349,   304,   299,   301,   293,   294,
     289,   290,   291,   292,   298,   297,   300,     0,   287,   295,
     302,   303,   296,   284,   182,   190,   487,   485,   486,   482,
     483,   484,     0,   477,   478,   480,   481,   473,     0,   203,
     227,   228,   229,   230,   231,   232,   220,     0,     0,   507,
     510,   511,   492,     0,     0,   516,    52,     0,     0,   379,
       0,   403,     0,   432,     0,   608,     0,   606,   604,   598,
     602,   603,     0,   596,   600,   601,   599,   593,   153,   154,
     155,   156,   152,   158,   160,   162,   175,   178,   130,   240,
     314,   351,     0,   286,     0,   475,     0,   205,   504,   505,
     506,   503,   509,   523,   525,    56,   381,   405,   434,   469,
       0,     0,     0,     0,   595,   288,     0,   479,     0,   605,
       0,   597,   488,     0,   607,   612,     0,   610,     0,     0,
     609,   620,     0,     0,     0,     0,   614,   616,   617,   618,
     619,   611,     0,     0,     0,     0,     0,   613,     0,   622,
     623,   624,   615,   621
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,    -9,  -774,   114,  -774,
    -774,  -774,  -774,  -774,  -774,    75,  -774,  -330,  -774,  -774,
    -774,   -70,  -774,  -774,  -774,   433,  -774,  -774,  -774,  -774,
     116,   366,   -41,   -37,   -36,   -25,  -774,  -774,  -774,  -774,
    -774,   197,   398,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,    -8,  -774,  -535,     1,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   -61,  -774,
    -553,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,   -38,  -548,  -774,  -774,
    -774,  -774,   -16,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,   -22,  -774,  -774,  -774,   -17,   368,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   -24,  -774,  -774,  -774,  -774,  -774,
    -774,  -773,  -774,  -774,  -774,     4,  -774,  -774,  -774,     7,
     403,  -774,  -774,  -770,  -774,  -769,  -774,   -32,  -774,  -768,
    -774,  -774,  -774,  -767,  -774,  -774,  -774,  -774,     2,  -774,
    -774,  -160,   718,  -774,  -774,  -774,  -774,  -774,    13,  -774,
    -774,  -774,    16,  -774,   392,  -774,   -65,  -774,  -774,  -774,
    -774,  -774,   -44,  -774,  -774,  -774,  -774,  -774,    -7,  -774,
    -774,  -774,    14,  -774,  -774,  -774,    15,  -774,   385,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     -18,  -774,  -774,  -774,   -23,   423,  -774,  -774,   -48,  -774,
     -20,  -774,  -774,  -774,  -774,  -774,   -27,  -774,  -774,  -774,
     -21,   425,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,   -19,  -774,  -774,  -774,   -14,  -774,   422,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -766,  -774,  -774,  -774,  -774,  -774,
    -774,    23,  -774,  -774,  -774,  -143,  -774,  -774,  -774,  -774,
    -774,  -774,    -2,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,    -4,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   256,   391,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   282,
     394,  -774,  -774,  -774,   -10,  -774,  -774,  -149,  -774,  -774,
    -774,  -774,  -774,  -774,  -158,  -774,  -774,  -177,  -774,  -774,
    -774,  -774,  -774
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     556,    87,    88,    41,    68,    84,    85,   569,   737,   824,
     825,   635,    43,    70,    96,    97,    98,   335,    45,    71,
     129,   130,   131,   132,   133,   134,   135,   136,   343,    47,
      72,   159,   160,   161,   370,   162,   137,   344,   138,   345,
     139,   346,   657,   658,   659,   777,   636,   637,   638,   758,
     942,   639,   759,   640,   760,   641,   761,   642,   643,   408,
     644,   645,   646,   647,   648,   649,   650,   651,   652,   767,
     653,   654,   770,   140,   358,   678,   679,   680,   681,   141,
     360,   686,   687,   688,   689,   142,   359,   143,   362,   694,
     695,   696,   800,    63,    80,   289,   290,   291,   421,   292,
     422,   144,   363,   703,   704,   705,   706,   707,   708,   709,
     710,   145,   352,   661,   662,   663,   780,    49,    73,   181,
     182,   183,   376,   184,   377,   185,   378,   186,   382,   187,
     381,   578,   188,   189,   146,   357,   673,   674,   675,   789,
     877,   878,   147,   353,    57,    77,   665,   666,   667,   783,
      59,    78,   254,   255,   256,   257,   258,   259,   260,   407,
     261,   411,   262,   410,   263,   264,   412,   265,   148,   354,
     669,   670,   671,   786,    61,    79,   275,   276,   277,   278,
     279,   416,   280,   281,   282,   283,   191,   374,   739,   740,
     741,   826,    51,    74,   201,   202,   203,   387,   149,   355,
     150,   356,   194,   375,   743,   744,   745,   829,    53,    75,
     216,   217,   218,   390,   219,   220,   392,   221,   222,   195,
     383,   747,   748,   749,   832,    55,    76,   234,   235,   236,
     237,   398,   238,   399,   239,   400,   240,   401,   241,   402,
     242,   403,   243,   397,   196,   384,   751,   835,   151,   361,
     691,   692,   797,   892,   893,   894,   895,   896,   954,   152,
     364,   720,   721,   722,   811,   961,   723,   724,   812,   725,
     726,   153,   154,   366,   732,   733,   734,   818,   735,   819,
     155,   367,    65,    81,   310,   311,   312,   313,   426,   314,
     427,   315,   316,   429,   317,   318,   319,   432,   605,   320,
     433,   321,   322,   323,   324,   437,   612,   325,   438,    99,
     337,   100,   338,   101,   339,   102,   336,    67,    82,   327,
     328,   329,   441,   753,   754,   837,   932,   933,   934,   935,
     972,   936,   970,   986,   987,   988,   995,   996,   997,  1002,
     998,   999,  1000
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   128,   158,   176,   198,   211,   230,    38,   252,   271,
     288,   307,   717,   685,   273,   655,   871,   253,   272,   872,
     873,   875,   876,   882,   163,   192,   204,   214,   232,    89,
     266,   284,   177,   308,    30,   274,   178,   179,   676,   286,
     287,    86,   199,   212,    42,    31,    44,    32,   180,    33,
     156,   157,   164,   193,   205,   215,   233,    46,   267,   285,
     103,   309,   114,   104,   105,   106,   190,   200,   213,   231,
     607,   608,   609,   610,    48,   206,   207,   208,   209,   210,
     115,   116,   575,   576,   577,   245,   107,   108,   109,   110,
     111,   112,   113,   114,   958,   959,   960,   173,   115,   116,
     115,   116,   991,   611,    50,   992,   993,   994,    94,   114,
     246,   115,   116,   246,   677,   247,   248,    52,   114,   249,
     250,   251,   117,   118,   119,   120,   121,   115,   116,   197,
     115,   116,   286,   287,   341,   368,   115,   116,   122,   342,
     369,   123,   711,   886,   372,   727,   728,   246,   124,   373,
     385,   624,    90,   173,   388,   386,   125,   126,   113,   389,
     127,    91,    92,    93,   115,   116,   697,   698,   699,   700,
     701,   702,   585,   586,   587,   395,   423,    94,    94,   871,
     396,   424,   872,   873,   875,   876,   882,   115,   116,   246,
     268,   247,   248,   269,   270,    94,    54,    94,   439,    34,
      35,    36,    37,   440,   619,    56,   115,   116,    94,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,    94,   603,   604,    94,   712,   713,
     714,   715,   246,    94,    58,    60,   442,   925,   368,   926,
     927,   443,   857,   755,    62,    64,    66,   685,   442,   107,
     108,   109,   110,   756,   372,   774,   114,   774,   326,   757,
     775,    94,   776,   717,   809,   816,   165,   114,   166,   810,
     817,    95,   330,   331,   115,   116,   167,   168,   169,   170,
     171,   172,   820,   439,    94,   115,   116,   821,   822,   774,
     385,   173,   174,   332,   948,   949,   952,   334,   128,   175,
     223,   953,   158,    94,   224,   225,   226,   227,   228,   229,
     333,   423,   388,   404,   395,   176,   957,   966,   198,   967,
     340,   973,   444,   445,   163,   211,   974,  1006,   938,   939,
     940,   941,  1007,   676,   683,   230,   684,   192,   792,   795,
     204,   793,   796,   347,   177,   252,    94,   214,   178,   179,
     271,   348,   164,   349,   253,   273,   199,   232,   798,   272,
     180,   799,   350,   212,   351,   193,   365,   266,   205,   307,
     838,    94,   284,   839,   989,   215,   274,   990,   190,   371,
     379,   200,    94,   380,   391,   233,   393,   394,   213,   405,
     415,   308,   406,   409,   413,   267,   414,   417,   231,   418,
     285,   107,   108,   109,   110,   419,   112,   420,   114,   246,
     425,   428,   430,   431,   434,   435,   436,   446,   447,   309,
     448,   449,   450,   451,   453,   454,   115,   116,   455,   168,
     169,   456,   171,   172,   457,   458,   459,   460,   461,   462,
     545,   546,   547,   173,   463,   464,   465,   466,   467,   468,
     469,   175,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   470,   471,   472,   473,
     474,   476,   475,   128,   477,   479,   480,   482,   158,   483,
     484,   485,   486,   487,   488,   489,   490,   491,   492,   494,
     496,   497,   498,   499,   500,   716,   729,   307,   115,   116,
     163,   502,   503,   504,   505,   506,   507,   508,   510,   511,
     512,   513,   514,   515,   599,   516,   518,   718,   730,   308,
     522,   519,   523,    94,   526,   520,   527,   525,   164,   528,
     529,   532,   530,   615,   531,   533,   537,   538,   540,   534,
     535,   542,   543,   536,   551,   719,   731,   309,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   544,   548,   549,   550,   552,   553,   554,   779,
     558,    32,   557,   559,   560,   561,   562,   563,   750,   555,
     564,   565,   566,   567,   568,   570,   571,   572,   573,   574,
     579,   580,   581,   582,   614,    94,   583,   584,   588,   656,
     606,   660,   664,   668,   672,   690,   589,   590,   591,   592,
     593,   594,   595,   596,   597,   598,   600,   601,   602,   613,
     693,   738,   742,   746,   752,   762,   763,   764,   765,   766,
     768,   769,   771,   772,   773,   682,   782,   778,   781,   785,
     784,   787,   788,   790,   791,   985,   794,   802,   801,   803,
     804,   805,   806,   807,   808,   813,   814,   815,   828,   616,
     827,   831,   830,   833,   834,   823,   840,   836,   841,   842,
     843,   844,   845,   846,   849,   848,   847,   850,   852,   851,
     907,   853,   908,   854,   913,   900,   855,   914,   901,   902,
     903,   916,   917,   983,   924,   950,   904,   956,   905,   951,
     909,   910,   911,   943,   944,   945,   946,   947,   955,   962,
     176,   963,   964,   252,   968,   971,   271,   976,   965,   865,
     978,   273,   253,   980,  1003,   272,   969,   887,   870,  1004,
     288,  1005,   192,  1008,   478,   266,   888,   979,   284,   177,
    1009,   880,   274,   178,   179,   618,   716,   982,   866,   890,
     729,  1010,   867,   868,   884,   180,   198,   874,   984,   211,
     193,  1011,   230,   267,   869,  1013,   285,   928,   718,   881,
     481,   858,   730,   190,   452,   856,   929,   891,   204,   885,
     899,   214,   879,   898,   232,   906,   860,   859,   493,   930,
     889,   524,   975,   883,   199,   244,   719,   212,   862,   861,
     731,   863,   864,   918,   921,   521,   205,   517,   920,   215,
     919,   495,   233,   977,   912,   923,   915,   931,   922,   200,
     501,   897,   213,   736,   981,   231,   617,   509,   937,  1012,
     539,  1001,     0,     0,     0,     0,   541,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   865,     0,     0,     0,   887,     0,     0,     0,
       0,   870,     0,     0,     0,   888,     0,     0,     0,     0,
       0,     0,     0,   928,   880,     0,     0,     0,   890,     0,
       0,   866,   929,     0,     0,   867,   868,     0,     0,     0,
     874,     0,     0,     0,     0,   930,     0,   869,     0,     0,
       0,     0,   881,     0,     0,     0,   891,     0,     0,     0,
       0,     0,     0,     0,     0,   879,     0,     0,     0,   889,
       0,     0,     0,   931
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    16,    78,    79,
      80,    81,   565,   561,    79,   550,   789,    78,    79,   789,
     789,   789,   789,   789,    72,    73,    74,    75,    76,    10,
      78,    79,    73,    81,     0,    79,    73,    73,    83,    90,
      91,   159,    74,    75,     7,     5,     7,     7,    73,     9,
      12,    13,    72,    73,    74,    75,    76,     7,    78,    79,
      11,    81,    44,    14,    15,    16,    73,    74,    75,    76,
     129,   130,   131,   132,     7,    57,    58,    59,    60,    61,
      62,    63,    70,    71,    72,    17,    37,    38,    39,    40,
      41,    42,    43,    44,   100,   101,   102,    79,    62,    63,
      62,    63,   136,   162,     7,   139,   140,   141,   159,    44,
      45,    62,    63,    45,   159,    47,    48,     7,    44,    51,
      52,    53,    73,    74,    75,    76,    77,    62,    63,    55,
      62,    63,    90,    91,     3,     3,    62,    63,    89,     8,
       8,    92,    17,    78,     3,   109,   110,    45,    99,     8,
       3,    26,   133,    79,     3,     8,   107,   108,    43,     8,
     111,   142,   143,   144,    62,    63,    93,    94,    95,    96,
      97,    98,   502,   503,   504,     3,     3,   159,   159,   952,
       8,     8,   952,   952,   952,   952,   952,    62,    63,    45,
      46,    47,    48,    49,    50,   159,     7,   159,     3,   159,
     160,   161,   162,     8,    17,     7,    62,    63,   159,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,   159,   126,   127,   159,   103,   104,
     105,   106,    45,   159,     7,     7,     3,   135,     3,   137,
     138,     8,   777,     8,     7,     7,     7,   795,     3,    37,
      38,    39,    40,     8,     3,     3,    44,     3,   134,     8,
       8,   159,     8,   816,     3,     3,    54,    44,    56,     8,
       8,   341,     6,     3,    62,    63,    64,    65,    66,    67,
      68,    69,     3,     3,   159,    62,    63,     8,     8,     3,
       3,    79,    80,     4,     8,     8,     3,     3,   368,    87,
      77,     8,   372,   159,    81,    82,    83,    84,    85,    86,
       8,     3,     3,     8,     3,   385,     8,     8,   388,     8,
       4,     3,   331,   332,   372,   395,     8,     3,    18,    19,
      20,    21,     8,    83,    84,   405,    86,   385,     3,     3,
     388,     6,     6,     4,   385,   415,   159,   395,   385,   385,
     420,     4,   372,     4,   415,   420,   388,   405,     3,   420,
     385,     6,     4,   395,     4,   385,     4,   415,   388,   439,
       3,   159,   420,     6,     3,   395,   420,     6,   385,     4,
       4,   388,   159,     4,     4,   405,     4,     4,   395,     3,
       3,   439,     8,     4,     4,   415,     8,     4,   405,     4,
     420,    37,    38,    39,    40,     8,    42,     3,    44,    45,
       4,     4,     4,     4,     4,     4,     4,   159,     4,   439,
       4,     4,     4,     4,     4,     4,    62,    63,     4,    65,
      66,     4,    68,    69,   160,   160,   160,   160,   160,     4,
     449,   450,   451,    79,     4,     4,     4,     4,     4,     4,
       4,    87,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,     4,     4,     4,     4,
       4,     4,   160,   543,     4,     4,   162,     4,   548,     4,
       4,     4,     4,   160,   162,     4,     4,     4,     4,     4,
       4,   160,     4,   160,   160,   565,   566,   567,    62,    63,
     548,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     160,     4,     4,     4,   523,   162,     4,   565,   566,   567,
       4,   162,     4,   159,     4,   162,     4,   162,   548,   160,
       4,     4,   160,   542,   160,     4,     4,     4,     4,   162,
     162,     4,     7,   162,     5,   565,   566,   567,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     7,     7,     7,     7,     5,     5,     5,     3,
       5,     7,   159,     5,     5,     5,     5,     5,    88,   465,
       7,     7,     7,     7,     5,     5,     5,   159,   159,   159,
     159,     5,     7,   159,     5,   159,   159,   159,   159,     7,
     128,     7,     7,     7,     7,     7,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
       7,     7,     7,     7,     7,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   560,     3,     6,     6,     3,
       6,     6,     3,     6,     3,     7,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   543,
       6,     3,     6,     6,     3,   159,     4,     8,     4,     4,
       4,   160,   162,   160,     4,   160,   162,   160,     4,   160,
       4,   160,     4,   160,     4,   160,   162,     4,   160,   160,
     160,     6,     3,     5,     4,     8,   160,     3,   160,     8,
     160,   160,   160,   159,   159,   159,   159,   159,     8,   159,
     780,   159,   159,   783,     8,     4,   786,     4,   159,   789,
       4,   786,   783,     4,     4,   786,   159,   797,   789,     4,
     800,     4,   780,     4,   368,   783,   797,   160,   786,   780,
     162,   789,   786,   780,   780,   548,   816,   159,   789,   797,
     820,   160,   789,   789,   792,   780,   826,   789,   159,   829,
     780,   160,   832,   783,   789,   159,   786,   837,   816,   789,
     372,   779,   820,   780,   341,   774,   837,   797,   826,   795,
     802,   829,   789,   800,   832,   809,   782,   780,   385,   837,
     797,   423,   952,   791,   826,    77,   816,   829,   785,   783,
     820,   786,   788,   826,   831,   420,   826,   415,   829,   829,
     828,   388,   832,   956,   816,   834,   820,   837,   832,   826,
     395,   798,   829,   567,   973,   832,   544,   405,   838,  1006,
     439,   989,    -1,    -1,    -1,    -1,   442,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   952,    -1,    -1,    -1,   956,    -1,    -1,    -1,
      -1,   952,    -1,    -1,    -1,   956,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   973,   952,    -1,    -1,    -1,   956,    -1,
      -1,   952,   973,    -1,    -1,   952,   952,    -1,    -1,    -1,
     952,    -1,    -1,    -1,    -1,   973,    -1,   952,    -1,    -1,
      -1,    -1,   952,    -1,    -1,    -1,   956,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   952,    -1,    -1,    -1,   956,
      -1,    -1,    -1,   973
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
       0,     5,     7,     9,   159,   160,   161,   162,   179,   180,
     181,   186,     7,   195,     7,   201,     7,   212,     7,   300,
       7,   375,     7,   391,     7,   408,     7,   327,     7,   333,
       7,   357,     7,   276,     7,   465,     7,   500,   187,   182,
     196,   202,   213,   301,   376,   392,   409,   328,   334,   358,
     277,   466,   501,   179,   188,   189,   159,   184,   185,    10,
     133,   142,   143,   144,   159,   194,   197,   198,   199,   492,
     494,   496,   498,    11,    14,    15,    16,    37,    38,    39,
      40,    41,    42,    43,    44,    62,    63,    73,    74,    75,
      76,    77,    89,    92,    99,   107,   108,   111,   194,   203,
     204,   205,   206,   207,   208,   209,   210,   219,   221,   223,
     256,   262,   268,   270,   284,   294,   317,   325,   351,   381,
     383,   431,   442,   454,   455,   463,    12,    13,   194,   214,
     215,   216,   218,   381,   383,    54,    56,    64,    65,    66,
      67,    68,    69,    79,    80,    87,   194,   205,   206,   207,
     208,   302,   303,   304,   306,   308,   310,   312,   315,   316,
     351,   369,   381,   383,   385,   402,   427,    55,   194,   310,
     351,   377,   378,   379,   381,   383,    57,    58,    59,    60,
      61,   194,   310,   351,   381,   383,   393,   394,   395,   397,
     398,   400,   401,    77,    81,    82,    83,    84,    85,    86,
     194,   351,   381,   383,   410,   411,   412,   413,   415,   417,
     419,   421,   423,   425,   325,    17,    45,    47,    48,    51,
      52,    53,   194,   241,   335,   336,   337,   338,   339,   340,
     341,   343,   345,   347,   348,   350,   381,   383,    46,    49,
      50,   194,   241,   339,   345,   359,   360,   361,   362,   363,
     365,   366,   367,   368,   381,   383,    90,    91,   194,   278,
     279,   280,   282,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   194,   381,   383,
     467,   468,   469,   470,   472,   474,   475,   477,   478,   479,
     482,   484,   485,   486,   487,   490,   134,   502,   503,   504,
       6,     3,     4,     8,     3,   200,   499,   493,   495,   497,
       4,     3,     8,   211,   220,   222,   224,     4,     4,     4,
       4,     4,   295,   326,   352,   382,   384,   318,   257,   269,
     263,   432,   271,   285,   443,     4,   456,   464,     3,     8,
     217,     4,     3,     8,   370,   386,   305,   307,   309,     4,
       4,   313,   311,   403,   428,     3,     8,   380,     3,     8,
     396,     4,   399,     4,     4,     3,     8,   426,   414,   416,
     418,   420,   422,   424,     8,     3,     8,   342,   242,     4,
     346,   344,   349,     4,     8,     3,   364,     4,     4,     8,
       3,   281,   283,     3,     8,     4,   471,   473,     4,   476,
       4,     4,   480,   483,     4,     4,     4,   488,   491,     3,
       8,   505,     3,     8,   179,   179,   159,     4,     4,     4,
       4,     4,   198,     4,     4,     4,     4,   160,   160,   160,
     160,   160,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   160,     4,     4,   204,     4,
     162,   215,     4,     4,     4,     4,     4,   160,   162,     4,
       4,     4,     4,   303,     4,   378,     4,   160,     4,   160,
     160,   394,     4,     4,     4,     4,     4,     4,     4,   412,
       4,     4,   160,     4,     4,     4,   162,   337,     4,   162,
     162,   361,     4,     4,   279,   162,     4,     4,   160,     4,
     160,   160,     4,     4,   162,   162,   162,     4,     4,   468,
       4,   503,     4,     7,     7,   179,   179,   179,     7,     7,
       7,     5,     5,     5,     5,   181,   183,   159,     5,     5,
       5,     5,     5,     5,     7,     7,     7,     7,     5,   190,
       5,     5,   159,   159,   159,    70,    71,    72,   314,   159,
       5,     7,   159,   159,   159,   190,   190,   190,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   179,
     159,   159,   159,   126,   127,   481,   128,   129,   130,   131,
     132,   162,   489,   159,     5,   179,   203,   502,   214,    17,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,   194,   229,   230,   231,   234,
     236,   238,   240,   241,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   253,   254,   229,     7,   225,   226,   227,
       7,   296,   297,   298,     7,   329,   330,   331,     7,   353,
     354,   355,     7,   319,   320,   321,    83,   159,   258,   259,
     260,   261,   188,    84,    86,   260,   264,   265,   266,   267,
       7,   433,   434,     7,   272,   273,   274,    93,    94,    95,
      96,    97,    98,   286,   287,   288,   289,   290,   291,   292,
     293,    17,   103,   104,   105,   106,   194,   243,   381,   383,
     444,   445,   446,   449,   450,   452,   453,   109,   110,   194,
     381,   383,   457,   458,   459,   461,   467,   191,     7,   371,
     372,   373,     7,   387,   388,   389,     7,   404,   405,   406,
      88,   429,     7,   506,   507,     8,     8,     8,   232,   235,
     237,   239,     4,     4,     4,     4,     4,   252,     4,     4,
     255,     4,     4,     4,     3,     8,     8,   228,     6,     3,
     299,     6,     3,   332,     6,     3,   356,     6,     3,   322,
       6,     3,     3,     6,     6,     3,     6,   435,     3,     6,
     275,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   447,   451,     4,     4,     4,     3,     8,   460,   462,
       3,     8,     8,   159,   192,   193,   374,     6,     3,   390,
       6,     3,   407,     6,     3,   430,     8,   508,     3,     6,
       4,     4,     4,     4,   160,   162,   160,   162,   160,     4,
     160,   160,     4,   160,   160,   162,   230,   229,   227,   302,
     298,   335,   331,   359,   355,   194,   205,   206,   207,   208,
     241,   294,   306,   308,   310,   312,   316,   323,   324,   351,
     381,   383,   427,   321,   259,   265,    78,   194,   241,   351,
     381,   383,   436,   437,   438,   439,   440,   434,   278,   274,
     160,   160,   160,   160,   160,   160,   287,     4,     4,   160,
     160,   160,   445,     4,     4,   458,     6,     3,   377,   373,
     393,   389,   410,   406,     4,   135,   137,   138,   194,   241,
     381,   383,   509,   510,   511,   512,   514,   507,    18,    19,
      20,    21,   233,   159,   159,   159,   159,   159,     8,     8,
       8,     8,     3,     8,   441,     8,     3,     8,   100,   101,
     102,   448,   159,   159,   159,   159,     8,     8,     8,   159,
     515,     4,   513,     3,     8,   324,     4,   438,     4,   160,
       4,   510,   159,     5,   159,     7,   516,   517,   518,     3,
       6,   136,   139,   140,   141,   519,   520,   521,   523,   524,
     525,   517,   522,     4,     4,     4,     3,     8,     4,   162,
     160,   160,   520,   159
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   163,   165,   164,   166,   164,   167,   164,   168,   164,
     169,   164,   170,   164,   171,   164,   172,   164,   173,   164,
     174,   164,   175,   164,   176,   164,   177,   164,   178,   164,
     179,   179,   179,   179,   179,   179,   179,   180,   182,   181,
     183,   184,   184,   185,   185,   187,   186,   188,   188,   189,
     189,   191,   190,   192,   192,   193,   193,   194,   196,   195,
     197,   197,   198,   198,   198,   198,   198,   198,   200,   199,
     202,   201,   203,   203,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     205,   206,   207,   208,   209,   211,   210,   213,   212,   214,
     214,   215,   215,   215,   215,   215,   217,   216,   218,   220,
     219,   222,   221,   224,   223,   225,   225,   226,   226,   228,
     227,   229,   229,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   232,   231,   233,   233,   233,   233,   235,   234,   237,
     236,   239,   238,   240,   242,   241,   243,   244,   245,   246,
     247,   248,   249,   250,   252,   251,   253,   255,   254,   257,
     256,   258,   258,   259,   259,   260,   261,   263,   262,   264,
     264,   265,   265,   265,   266,   267,   269,   268,   271,   270,
     272,   272,   273,   273,   275,   274,   277,   276,   278,   278,
     278,   279,   279,   281,   280,   283,   282,   285,   284,   286,
     286,   287,   287,   287,   287,   287,   287,   288,   289,   290,
     291,   292,   293,   295,   294,   296,   296,   297,   297,   299,
     298,   301,   300,   302,   302,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   305,   304,   307,   306,   309,   308,
     311,   310,   313,   312,   314,   314,   314,   315,   316,   318,
     317,   319,   319,   320,   320,   322,   321,   323,   323,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   326,   325,   328,   327,   329,
     329,   330,   330,   332,   331,   334,   333,   335,   335,   336,
     336,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   338,   339,   340,   342,   341,   344,   343,   346,   345,
     347,   349,   348,   350,   352,   351,   353,   353,   354,   354,
     356,   355,   358,   357,   359,   359,   360,   360,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   362,   364,   363,
     365,   366,   367,   368,   370,   369,   371,   371,   372,   372,
     374,   373,   376,   375,   377,   377,   378,   378,   378,   378,
     378,   378,   380,   379,   382,   381,   384,   383,   386,   385,
     387,   387,   388,   388,   390,   389,   392,   391,   393,   393,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     396,   395,   397,   399,   398,   400,   401,   403,   402,   404,
     404,   405,   405,   407,   406,   409,   408,   410,   410,   411,
     411,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   414,   413,   416,   415,   418,   417,   420,   419,
     422,   421,   424,   423,   426,   425,   428,   427,   430,   429,
     432,   431,   433,   433,   435,   434,   436,   436,   437,   437,
     438,   438,   438,   438,   438,   438,   439,   441,   440,   443,
     442,   444,   444,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   447,   446,   448,   448,   448,   449,   451,   450,
     452,   453,   454,   456,   455,   457,   457,   458,   458,   458,
     458,   458,   460,   459,   462,   461,   464,   463,   466,   465,
     467,   467,   468,   468,   468,   468,   468,   468,   468,   468,
     468,   468,   468,   468,   468,   468,   468,   468,   468,   469,
     471,   470,   473,   472,   474,   476,   475,   477,   478,   480,
     479,   481,   481,   483,   482,   484,   485,   486,   488,   487,
     489,   489,   489,   489,   489,   491,   490,   493,   492,   495,
     494,   497,   496,   499,   498,   501,   500,   502,   502,   503,
     505,   504,   506,   506,   508,   507,   509,   509,   510,   510,
     510,   510,   510,   510,   510,   511,   513,   512,   515,   514,
     516,   516,   518,   517,   519,   519,   520,   520,   520,   520,
     522,   521,   523,   524,   525
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
       1,     3,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
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
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"preferred-lifetime\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
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
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "value", "sub_json", "map2", "$@15", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp6_object", "$@19", "sub_dhcp6",
  "$@20", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@21",
  "sub_interfaces6", "$@22", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@23", "re_detect",
  "lease_database", "$@24", "hosts_database", "$@25", "hosts_databases",
  "$@26", "database_list", "not_empty_database_list", "database", "$@27",
  "database_map_params", "database_map_param", "database_type", "$@28",
  "db_type", "user", "$@29", "password", "$@30", "host", "$@31", "port",
  "name", "$@32", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@33", "max_reconnect_tries", "keyspace", "$@34",
  "mac_sources", "$@35", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@36",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@37",
  "hooks_libraries", "$@38", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@39",
  "sub_hooks_library", "$@40", "hooks_params", "hooks_param", "library",
  "$@41", "parameters", "$@42", "expired_leases_processing", "$@43",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@44",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@45",
  "sub_subnet6", "$@46", "subnet6_params", "subnet6_param", "subnet",
  "$@47", "interface", "$@48", "interface_id", "$@49", "client_class",
  "$@50", "reservation_mode", "$@51", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@52", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@53",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@54", "sub_option_def_list", "$@55", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@56",
  "sub_option_def", "$@57", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@58",
  "option_def_record_types", "$@59", "space", "$@60", "option_def_space",
  "option_def_encapsulate", "$@61", "option_def_array", "option_data_list",
  "$@62", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@63", "sub_option_data", "$@64",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@65",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@66", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@67", "sub_pool6", "$@68",
  "pool_params", "pool_param", "pool_entry", "$@69", "user_context",
  "$@70", "comment", "$@71", "pd_pools_list", "$@72",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@73", "sub_pd_pool", "$@74", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@75", "pd_prefix_len", "excluded_prefix", "$@76",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@77",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@78", "sub_reservation", "$@79", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@80", "prefixes", "$@81", "duid", "$@82", "hw_address", "$@83",
  "hostname", "$@84", "flex_id_value", "$@85",
  "reservation_client_classes", "$@86", "relay", "$@87", "relay_map",
  "$@88", "client_classes", "$@89", "client_classes_list",
  "client_class_entry", "$@90", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@91", "server_id", "$@92",
  "server_id_params", "server_id_param", "server_id_type", "$@93",
  "duid_type", "htype", "identifier", "$@94", "time", "enterprise_id",
  "dhcp4o6_port", "control_socket", "$@95", "control_socket_params",
  "control_socket_param", "socket_type", "$@96", "socket_name", "$@97",
  "dhcp_ddns", "$@98", "sub_dhcp_ddns", "$@99", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@100",
  "server_ip", "$@101", "server_port", "sender_ip", "$@102", "sender_port",
  "max_queue_size", "ncr_protocol", "$@103", "ncr_protocol_value",
  "ncr_format", "$@104", "always_include_fqdn", "override_no_update",
  "override_client_update", "replace_client_name", "$@105",
  "replace_client_name_value", "generated_prefix", "$@106",
  "dhcp4_json_object", "$@107", "dhcpddns_json_object", "$@108",
  "control_agent_json_object", "$@109", "logging_object", "$@110",
  "sub_logging", "$@111", "logging_params", "logging_param", "loggers",
  "$@112", "loggers_entries", "logger_entry", "$@113", "logger_params",
  "logger_param", "debuglevel", "severity", "$@114", "output_options_list",
  "$@115", "output_options_list_content", "output_entry", "$@116",
  "output_params_list", "output_params", "output", "$@117", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   244,   244,   244,   245,   245,   246,   246,   247,   247,
     248,   248,   249,   249,   250,   250,   251,   251,   252,   252,
     253,   253,   254,   254,   255,   255,   256,   256,   257,   257,
     265,   266,   267,   268,   269,   270,   271,   274,   279,   279,
     290,   293,   294,   297,   301,   308,   308,   315,   316,   319,
     323,   330,   330,   337,   338,   341,   345,   356,   366,   366,
     381,   382,   386,   387,   388,   389,   390,   391,   394,   394,
     409,   409,   418,   419,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     452,   457,   462,   467,   472,   477,   477,   488,   488,   497,
     498,   501,   502,   503,   504,   505,   508,   508,   518,   524,
     524,   536,   536,   548,   548,   558,   559,   562,   563,   566,
     566,   576,   577,   580,   581,   582,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,   595,   596,
     597,   600,   600,   607,   608,   609,   610,   613,   613,   621,
     621,   629,   629,   637,   642,   642,   650,   655,   660,   665,
     670,   675,   680,   685,   690,   690,   698,   703,   703,   712,
     712,   722,   723,   726,   727,   730,   735,   740,   740,   750,
     751,   754,   755,   756,   759,   764,   771,   771,   781,   781,
     791,   792,   795,   796,   799,   799,   809,   809,   819,   820,
     821,   824,   825,   828,   828,   836,   836,   844,   844,   855,
     856,   859,   860,   861,   862,   863,   864,   867,   872,   877,
     882,   887,   892,   900,   900,   913,   914,   917,   918,   925,
     925,   951,   951,   962,   963,   967,   968,   969,   970,   971,
     972,   973,   974,   975,   976,   977,   978,   979,   980,   981,
     982,   983,   984,   985,   988,   988,   996,   996,  1004,  1004,
    1012,  1012,  1020,  1020,  1027,  1028,  1029,  1032,  1037,  1045,
    1045,  1056,  1057,  1061,  1062,  1065,  1065,  1073,  1074,  1077,
    1078,  1079,  1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,
    1088,  1089,  1090,  1091,  1092,  1099,  1099,  1112,  1112,  1121,
    1122,  1125,  1126,  1131,  1131,  1146,  1146,  1160,  1161,  1164,
    1165,  1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,
    1177,  1180,  1182,  1187,  1189,  1189,  1197,  1197,  1205,  1205,
    1213,  1215,  1215,  1223,  1232,  1232,  1244,  1245,  1250,  1251,
    1256,  1256,  1268,  1268,  1280,  1281,  1286,  1287,  1292,  1293,
    1294,  1295,  1296,  1297,  1298,  1299,  1300,  1303,  1305,  1305,
    1313,  1315,  1317,  1322,  1330,  1330,  1342,  1343,  1346,  1347,
    1350,  1350,  1360,  1360,  1369,  1370,  1373,  1374,  1375,  1376,
    1377,  1378,  1381,  1381,  1389,  1389,  1414,  1414,  1444,  1444,
    1456,  1457,  1460,  1461,  1464,  1464,  1476,  1476,  1488,  1489,
    1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,  1500,  1501,
    1504,  1504,  1512,  1517,  1517,  1525,  1530,  1538,  1538,  1548,
    1549,  1552,  1553,  1556,  1556,  1565,  1565,  1574,  1575,  1578,
    1579,  1583,  1584,  1585,  1586,  1587,  1588,  1589,  1590,  1591,
    1592,  1593,  1596,  1596,  1606,  1606,  1616,  1616,  1624,  1624,
    1632,  1632,  1640,  1640,  1648,  1648,  1661,  1661,  1671,  1671,
    1682,  1682,  1692,  1693,  1696,  1696,  1706,  1707,  1710,  1711,
    1714,  1715,  1716,  1717,  1718,  1719,  1722,  1724,  1724,  1735,
    1735,  1747,  1748,  1751,  1752,  1753,  1754,  1755,  1756,  1757,
    1758,  1759,  1762,  1762,  1769,  1770,  1771,  1774,  1779,  1779,
    1787,  1792,  1799,  1806,  1806,  1816,  1817,  1820,  1821,  1822,
    1823,  1824,  1827,  1827,  1835,  1835,  1845,  1845,  1857,  1857,
    1867,  1868,  1871,  1872,  1873,  1874,  1875,  1876,  1877,  1878,
    1879,  1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,  1890,
    1895,  1895,  1903,  1903,  1911,  1916,  1916,  1924,  1929,  1934,
    1934,  1942,  1943,  1946,  1946,  1954,  1959,  1964,  1969,  1969,
    1977,  1980,  1983,  1986,  1989,  1995,  1995,  2005,  2005,  2012,
    2012,  2019,  2019,  2032,  2032,  2042,  2042,  2053,  2054,  2058,
    2062,  2062,  2074,  2075,  2079,  2079,  2087,  2088,  2091,  2092,
    2093,  2094,  2095,  2096,  2097,  2100,  2105,  2105,  2113,  2113,
    2123,  2124,  2127,  2127,  2135,  2136,  2139,  2140,  2141,  2142,
    2145,  2145,  2153,  2158,  2163
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
#line 4706 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2168 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
