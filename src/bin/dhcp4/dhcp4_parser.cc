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
#define yylex   parser4_lex

// First part of user declarations.

#line 39 "dhcp4_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp4_parser.h"

// User implementation prologue.

#line 53 "dhcp4_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:413

#include <dhcp4/parser_context.h>

#line 59 "dhcp4_parser.cc" // lalr1.cc:413


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp4_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
    :
#if PARSER4_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp4Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp4Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp4Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp4Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 186: // value
      case 190: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 169: // "boolean"
        value.move< bool > (that.value);
        break;

      case 168: // "floating point"
        value.move< double > (that.value);
        break;

      case 167: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 166: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 186: // value
      case 190: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 169: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 168: // "floating point"
        value.copy< double > (that.value);
        break;

      case 167: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 166: // "constant string"
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo,
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
            case 166: // "constant string"

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 167: // "integer"

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 168: // "floating point"

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 169: // "boolean"

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 186: // value

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 190: // map_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 230: // socket_type

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 233: // outbound_interface_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 255: // db_type

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 337: // hr_mode

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 489: // ncr_protocol_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 497: // replace_client_name_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp4Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  inline Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::parse ()
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
      case 186: // value
      case 190: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 169: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 168: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 167: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 166: // "constant string"
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
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 301 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 308 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 312 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 330 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 334 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 352 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 356 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 970 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 699 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 761 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 807 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 848 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 853 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 992 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1101 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1317 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2295 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1487 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2491 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2567 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-control", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.QUEUE_CONTROL);
}
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.require("capacity", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2979 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", i);
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1960 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1961 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3211 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 1995 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3219 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2001 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2056 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2075 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2129 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3493 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 623:
#line 2162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3511 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3549 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2201 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 641:
#line 2210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 642:
#line 2214 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 650:
#line 2230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 651:
#line 2236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 653:
#line 2246 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3621 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3625 "dhcp4_parser.cc" // lalr1.cc:859
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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Dhcp4Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Dhcp4Parser::yypact_ninf_ = -811;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     155,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,    55,    21,    24,    52,    74,
      78,   121,   123,   130,   141,   156,   163,   187,   193,   195,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,    21,   -83,
      42,    64,    47,   179,    37,   188,    83,   230,   159,   -52,
     434,    45,    32,  -811,   205,   225,   238,   221,   248,  -811,
    -811,  -811,  -811,  -811,   249,  -811,    76,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,   271,   274,  -811,
    -811,  -811,  -811,  -811,  -811,   284,   294,   298,   325,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,   333,  -811,  -811,  -811,  -811,    79,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,   337,  -811,   107,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,   359,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,   126,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,   154,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
     253,   276,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,   332,  -811,  -811,   362,  -811,  -811,
    -811,   364,  -811,  -811,   341,   368,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,   369,
     370,  -811,  -811,  -811,  -811,   377,   374,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,   158,
    -811,  -811,  -811,   384,  -811,  -811,   387,  -811,   391,   394,
    -811,  -811,   398,   399,   404,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,   161,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,   164,  -811,  -811,  -811,  -811,   170,  -811,  -811,  -811,
      21,    21,  -811,   243,   407,   409,   411,   412,   418,  -811,
      42,  -811,    32,   419,   420,   422,   258,   269,   435,   436,
     453,   454,   455,   460,   245,   299,   300,   302,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   481,
     322,   483,   486,   487,    64,  -811,   488,   489,   490,   327,
      47,  -811,   493,   495,   496,   497,   498,   499,   338,   500,
     507,   508,   509,   179,  -811,   510,    37,  -811,   512,   513,
     514,   515,   518,   519,   520,   521,  -811,   188,  -811,   522,
     524,   365,   525,   527,   529,   366,  -811,   230,   530,   371,
     372,  -811,   159,   535,   538,   -30,  -811,   375,   539,   541,
     379,   547,   400,   410,   562,   571,   413,   414,   415,   572,
     574,   575,   576,   434,  -811,   577,    45,  -811,   581,    32,
    -811,  -811,  -811,   582,   580,   583,    21,    21,    21,  -811,
     209,   584,   585,   586,  -811,  -811,   423,   428,   429,   589,
     590,   593,  -811,  -811,  -811,  -811,   433,   596,   597,   598,
     599,   600,   439,   601,   603,   604,   605,   606,  -811,   607,
     608,   609,  -811,   612,    92,   190,  -811,  -811,   445,   446,
     452,   614,   456,   457,  -811,   137,   612,   458,   613,  -811,
     459,  -811,   612,   461,   462,   463,   464,   465,   466,   467,
    -811,   479,   480,  -811,   482,   484,   485,  -811,  -811,   491,
    -811,  -811,  -811,   492,    21,  -811,  -811,   494,   501,  -811,
     502,  -811,  -811,    28,   503,  -811,  -811,  -811,   -34,   504,
     505,   506,  -811,   616,  -811,   621,  -811,    21,    64,    45,
    -811,  -811,  -811,  -811,    32,    47,   565,  -811,  -811,  -811,
     405,   405,   627,  -811,   628,   630,   631,   632,  -811,  -811,
    -811,    59,   633,   634,   635,   226,    29,    31,   434,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
     636,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
      84,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,   637,   627,  -811,   237,   240,   241,
     257,  -811,   264,  -811,  -811,  -811,  -811,  -811,  -811,   643,
     645,   648,   649,   650,  -811,  -811,   651,   652,   655,   657,
     658,  -811,   265,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,   268,  -811,   659,   660,  -811,  -811,   663,   661,  -811,
    -811,   667,   671,  -811,  -811,   669,   673,  -811,  -811,   672,
     674,  -811,  -811,  -811,  -811,  -811,  -811,    60,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,   135,  -811,  -811,   675,   676,
    -811,  -811,   677,   679,  -811,   662,   680,   681,   682,   683,
     684,   283,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,   286,  -811,  -811,  -811,   685,  -811,
    -811,  -811,   289,  -811,  -811,   318,   526,  -811,   687,   688,
    -811,  -811,  -811,  -811,   686,  -811,   168,  -811,   689,  -811,
    -811,  -811,  -811,   692,   565,  -811,   693,   694,   695,   696,
     523,   511,   534,   533,   536,   700,   701,   540,   542,   543,
     544,   537,   405,  -811,  -811,   405,  -811,   627,   179,  -811,
     628,   230,  -811,   630,   159,  -811,   631,   408,  -811,   632,
      59,  -811,    70,   633,  -811,   188,  -811,   634,   -52,  -811,
     635,   545,   546,   548,   549,   550,   551,   226,  -811,   704,
     710,    29,  -811,   552,    31,  -811,  -811,  -811,   714,   718,
      37,  -811,   636,   719,  -811,   275,   637,  -811,  -811,   556,
    -811,   347,   558,   559,   560,  -811,  -811,  -811,  -811,  -811,
     561,   563,  -811,  -811,  -811,  -811,  -811,  -811,   319,  -811,
     320,  -811,   720,  -811,   722,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,   336,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,   727,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,   724,
     730,  -811,  -811,  -811,  -811,  -811,   726,  -811,   344,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,   569,   570,  -811,
    -811,  -811,  -811,   573,   345,  -811,   612,  -811,   733,  -811,
    -811,  -811,  -811,  -811,   353,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,   408,  -811,   734,   578,  -811,
      70,  -811,  -811,  -811,  -811,  -811,  -811,  -811,   736,   579,
     737,   275,  -811,  -811,   587,  -811,  -811,   738,  -811,   588,
    -811,  -811,   735,  -811,  -811,   174,  -811,   -90,   735,  -811,
    -811,   740,   741,   744,   356,  -811,  -811,  -811,  -811,  -811,
    -811,   745,   591,   592,   602,   -90,  -811,   617,  -811,  -811,
    -811,  -811,  -811
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   125,     9,   262,    11,
     415,    13,   440,    15,   340,    17,   348,    19,   385,    21,
     227,    23,   539,    25,   614,    27,   604,    29,    47,    41,
       0,     0,     0,     0,     0,   442,     0,   350,   387,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     612,   594,   596,   598,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   600,   602,   114,   140,     0,     0,   461,
     463,   465,   138,   147,   149,     0,     0,     0,     0,   110,
     254,   338,   377,   310,   428,   430,   205,   489,   432,   219,
     238,     0,   515,   528,   537,   105,     0,    72,    74,    75,
      76,    77,   104,    94,    95,    80,    81,   101,    82,    83,
      84,    88,    89,    78,    79,    86,    87,    99,   100,   102,
      96,    97,    98,    85,    90,    91,    92,    93,   103,   127,
     129,   133,     0,   124,     0,   116,   118,   119,   120,   121,
     122,   123,   291,   293,   295,   407,   289,   297,     0,   303,
     301,   299,   485,   288,   266,   267,   268,   279,     0,   264,
     271,   283,   284,   285,   272,   274,   275,   277,   273,   269,
     270,   286,   287,   276,   280,   281,   282,   278,   426,   425,
     421,   422,   420,     0,   417,   419,   423,   424,   483,   471,
     473,   477,   475,   481,   479,   467,   460,   454,   458,   459,
       0,   443,   444,   455,   456,   457,   451,   446,   452,   448,
     449,   450,   453,   447,     0,   367,   190,     0,   371,   369,
     374,     0,   363,   364,     0,   351,   352,   354,   366,   355,
     356,   357,   373,   358,   359,   360,   361,   362,   401,     0,
       0,   399,   400,   403,   404,     0,   388,   389,   391,   392,
     393,   394,   395,   396,   397,   398,   234,   236,   231,     0,
     229,   232,   233,     0,   563,   565,     0,   568,     0,     0,
     572,   576,     0,     0,     0,   581,   588,   590,   592,   561,
     559,   560,     0,   541,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     619,     0,   616,   618,   610,   609,     0,   606,   608,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,     0,     0,     0,
       0,   126,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   263,     0,     0,   416,     0,     0,
       0,     0,     0,     0,     0,     0,   441,     0,   341,     0,
       0,     0,     0,     0,     0,     0,   349,     0,     0,     0,
       0,   386,     0,     0,     0,     0,   228,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   540,     0,     0,   615,     0,     0,
     605,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,   112,   113,     0,     0,     0,     0,
       0,     0,   106,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   514,     0,
       0,     0,    73,     0,     0,     0,   137,   117,     0,     0,
       0,     0,     0,     0,   309,     0,     0,     0,     0,   265,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
     445,     0,     0,   365,     0,     0,     0,   376,   353,     0,
     405,   406,   390,     0,     0,   230,   562,     0,     0,   567,
       0,   570,   571,     0,     0,   578,   579,   580,     0,     0,
       0,     0,   542,     0,   617,     0,   607,     0,     0,     0,
     595,   597,   599,   601,     0,     0,     0,   462,   464,   466,
       0,     0,   151,   111,   256,   342,   379,   312,    40,   429,
     431,     0,     0,   434,   221,     0,     0,     0,     0,    51,
     128,   131,   132,   130,   135,   136,   134,   292,   294,   296,
     409,   290,   298,   305,   306,   307,   308,   304,   302,   300,
       0,   427,   484,   472,   474,   478,   476,   482,   480,   468,
     368,   191,   372,   370,   375,   402,   235,   237,   564,   566,
     569,   574,   575,   573,   577,   583,   584,   585,   586,   587,
     582,   589,   591,   593,     0,   151,    44,     0,     0,     0,
       0,   145,     0,   142,   144,   177,   183,   185,   187,     0,
       0,     0,     0,     0,   199,   201,     0,     0,     0,     0,
       0,   176,     0,   157,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   172,   173,   174,   169,   175,   170,
     171,     0,   155,     0,   152,   153,   260,     0,   257,   258,
     346,     0,   343,   344,   383,     0,   380,   381,   316,     0,
     313,   314,   214,   215,   216,   217,   218,     0,   207,   209,
     210,   211,   212,   213,   493,     0,   491,   438,     0,   435,
     436,   225,     0,   222,   223,     0,     0,     0,     0,     0,
       0,     0,   240,   242,   243,   244,   245,   246,   247,   524,
     526,   523,   521,   522,     0,   517,   519,   520,     0,   535,
     533,   534,     0,   530,   532,     0,    53,   413,     0,   410,
     411,   469,   487,   488,     0,   623,     0,   621,     0,    69,
     613,   603,   115,     0,     0,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   139,   148,     0,   150,     0,     0,   255,
       0,   350,   339,     0,   387,   378,     0,     0,   311,     0,
       0,   206,   495,     0,   490,   442,   433,     0,     0,   220,
       0,     0,     0,     0,     0,     0,     0,     0,   239,     0,
       0,     0,   516,     0,     0,   529,   538,    55,     0,    54,
       0,   408,     0,     0,   486,     0,     0,   620,   611,     0,
     143,     0,     0,     0,     0,   189,   192,   193,   194,   195,
       0,     0,   203,   204,   196,   197,   198,   158,     0,   154,
       0,   259,     0,   345,     0,   382,   337,   334,   323,   324,
     326,   320,   321,   322,   332,   333,   331,     0,   318,   325,
     335,   336,   327,   328,   329,   330,   315,   208,   511,     0,
     509,   510,   502,   503,   507,   508,   504,   505,   506,     0,
     496,   497,   499,   500,   501,   492,     0,   437,     0,   224,
     248,   249,   250,   251,   252,   253,   241,     0,     0,   518,
     536,   531,    52,     0,     0,   412,     0,   637,     0,   635,
     633,   627,   631,   632,     0,   625,   629,   630,   628,   622,
     146,   179,   180,   181,   182,   178,   184,   186,   188,   200,
     202,   156,   261,   347,   384,     0,   317,     0,     0,   494,
       0,   439,   226,   525,   527,    56,   414,   470,     0,     0,
       0,     0,   624,   319,     0,   513,   498,     0,   634,     0,
     626,   512,     0,   636,   641,     0,   639,     0,     0,   638,
     649,     0,     0,     0,     0,   643,   645,   646,   647,   648,
     640,     0,     0,     0,     0,     0,   642,     0,   651,   652,
     653,   644,   650
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,   -47,  -811,   250,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -503,  -811,  -811,
    -811,   -70,  -811,  -811,  -811,   390,  -811,  -811,  -811,  -811,
     178,   363,   -27,   -19,   -13,  -811,  -811,  -811,  -811,    -3,
    -811,  -811,   180,   382,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
     -41,  -811,  -811,  -811,  -811,  -811,  -811,   101,  -811,   -53,
    -811,  -578,   -51,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,   -45,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,   -55,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,   -62,  -811,  -811,  -811,   -50,   350,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,   -49,  -811,  -811,  -811,  -811,  -811,
    -811,  -810,  -811,  -811,  -811,   -17,  -811,  -811,  -811,    -8,
     427,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -799,
    -811,   -56,  -811,   -10,  -811,  -796,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,   -18,  -811,  -811,  -167,   -65,  -811,  -811,
    -811,  -811,  -811,     2,  -811,  -811,  -811,    10,  -811,   416,
    -811,   -72,  -811,  -811,  -811,  -811,  -811,   -66,  -811,  -811,
    -811,  -811,  -811,   -26,  -811,  -811,  -811,     9,  -811,  -811,
    -811,    14,  -811,   417,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,   -23,  -811,  -811,  -811,   -16,
     440,  -811,  -811,   -58,  -811,   -38,  -811,   -48,  -811,  -811,
    -811,     4,  -811,  -811,  -811,     7,  -811,   430,    -6,  -811,
       1,  -811,     5,  -811,   228,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -794,  -811,  -811,  -811,  -811,  -811,    12,  -811,
    -811,  -811,  -139,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,     3,  -811,  -811,  -811,  -811,  -811,  -811,  -811,    -2,
    -811,  -811,  -811,  -811,  -811,   255,   402,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -338,   397,  -811,  -811,  -811,
    -811,  -811,  -811,   288,   403,  -811,  -811,  -811,    -5,  -811,
    -811,  -143,  -811,  -811,  -811,  -811,  -811,  -811,  -158,  -811,
    -811,  -173,  -811,  -811,  -811,  -811,  -811
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     599,    87,    88,    41,    68,    84,    85,   610,   786,   868,
     869,   345,    43,    70,    96,    97,    98,   354,    45,    71,
     136,   137,   138,   139,   140,   141,   142,   378,   143,   144,
     145,   364,   174,   175,    47,    72,   176,   396,   177,   397,
     613,   178,   398,   616,   179,   146,   371,   147,   365,   672,
     673,   674,   803,   148,   372,   149,   373,   713,   714,   715,
     825,   692,   693,   694,   806,   985,   695,   807,   696,   808,
     697,   809,   698,   699,   430,   700,   701,   702,   703,   704,
     705,   706,   707,   815,   708,   816,   709,   710,   150,   385,
     737,   738,   739,   740,   741,   742,   743,   151,   388,   752,
     753,   754,   848,    61,    79,   299,   300,   301,   443,   302,
     444,   152,   389,   761,   762,   763,   764,   765,   766,   767,
     768,   153,   379,   717,   718,   719,   828,    49,    73,   198,
     199,   200,   406,   201,   402,   202,   403,   203,   404,   204,
     407,   205,   411,   206,   410,   207,   409,   627,   208,   154,
     382,   729,   730,   731,   837,   917,   918,   155,   380,    55,
      76,   721,   722,   723,   831,    57,    77,   264,   265,   266,
     267,   268,   269,   270,   429,   271,   433,   272,   432,   273,
     274,   434,   275,   156,   381,   725,   726,   727,   834,    59,
      78,   285,   286,   287,   288,   289,   438,   290,   291,   292,
     293,   210,   405,   788,   789,   790,   870,    51,    74,   223,
     224,   225,   415,   157,   383,   158,   384,   159,   387,   748,
     749,   750,   845,    53,    75,   240,   241,   242,   160,   368,
     161,   369,   162,   370,   246,   425,   793,   873,   247,   419,
     248,   420,   249,   422,   250,   421,   251,   424,   252,   423,
     253,   418,   217,   412,   794,   163,   386,   745,   746,   842,
     939,   940,   941,   942,   943,   997,   944,   164,   165,   391,
     774,   775,   776,   859,   777,   860,   166,   392,   782,   783,
     784,   167,   393,    63,    80,   322,   323,   324,   325,   448,
     326,   449,   327,   328,   451,   329,   330,   331,   454,   653,
     332,   455,   333,   334,   335,   336,   459,   660,   337,   460,
     338,   461,   339,   462,    99,   356,   100,   357,   101,   358,
     168,   362,   363,    67,    82,   346,   347,   348,   468,   102,
     355,    65,    81,   341,   342,   343,   465,   796,   797,   875,
     974,   975,   976,   977,  1010,   978,  1008,  1025,  1026,  1027,
    1034,  1035,  1036,  1041,  1037,  1038,  1039
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   135,   173,   193,   219,   236,   283,   262,   281,   298,
     319,   254,   284,   711,   180,   211,   226,   238,   220,   276,
     294,    83,   320,   628,   480,   213,    31,   912,    32,   632,
      33,    42,   263,   282,   181,   212,   227,   239,   913,   277,
     295,   916,   321,   925,   344,   651,   194,   209,   222,   237,
     296,   297,    89,  1030,   195,    30,  1031,  1032,  1033,    44,
     196,   169,   170,   840,   221,   171,   841,   214,   172,   243,
     197,   103,   296,   297,   215,   104,   244,   105,   216,   360,
     245,    46,   394,    86,   361,    48,   106,   395,   107,   108,
     109,   110,   111,   112,   113,   114,   109,   110,   111,   122,
     655,   656,   657,   658,   124,   125,   124,   125,   611,   612,
     400,   218,   124,   125,    94,   401,   115,   116,   117,   118,
     119,   120,   124,   125,   190,   121,   122,   191,    50,   413,
      52,   121,   122,   256,   414,   659,   123,    54,   843,   124,
     125,   844,   769,   770,   121,   124,   125,   778,    56,   126,
     127,   732,   733,   734,   735,   128,   736,   416,   928,   929,
     652,   445,   417,    58,   463,   129,   446,   466,   130,   464,
      60,   876,   467,   469,   877,   131,   132,  1028,   470,   133,
    1029,   134,    90,   235,   791,   912,   340,    34,    35,    36,
      37,    91,    92,    93,    62,    94,   913,    94,    94,   916,
      64,   925,    66,    94,   108,   109,   110,   111,    94,   614,
     615,   349,   469,    94,   109,   110,   111,   583,   623,   624,
     625,   626,   256,   278,   257,   258,   279,   280,   350,   352,
      94,   115,   116,   117,   124,   125,    94,   182,   183,   184,
     394,   122,   351,   466,   469,   799,   669,   898,   800,   801,
     122,   353,   185,   359,   124,   125,   186,   187,   188,   189,
     400,   426,   255,   124,   125,   802,   190,   804,   822,   191,
     128,   822,   805,   823,   228,   366,   824,   192,   367,   427,
     229,   230,   231,   232,   233,   234,   857,   235,   374,   861,
      95,   858,   864,   256,   862,   257,   258,   865,   375,   259,
     260,   261,   376,   471,   472,   124,   125,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   463,   822,   413,   135,    94,   866,   991,   992,   377,
     173,   755,   756,   757,   758,   759,   760,   390,   256,   995,
     428,   399,   180,   193,   996,    94,   219,   445,   416,   436,
     124,   125,  1002,  1006,    94,   211,  1011,   236,   226,  1045,
     220,  1012,   181,   408,  1046,   213,   431,   262,   435,   238,
     283,   437,   281,   439,   440,   212,   284,   442,   227,   276,
     981,   982,   983,   984,   294,   441,   194,   209,   447,   239,
     222,   450,   263,   319,   195,   452,    94,   282,   453,   277,
     196,   237,   456,   457,   295,   320,   221,   214,   458,   473,
     197,   474,   492,   475,   215,   476,   477,   967,   216,   968,
     969,   243,   478,   481,   482,   321,   483,   484,   244,   580,
     581,   582,   245,   108,   109,   110,   111,   675,   485,   486,
     487,    94,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   488,   489,   490,
     115,   116,   117,  1007,   491,   120,   493,   494,   256,   495,
     122,   256,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   124,   125,   507,   187,   509,   189,   508,
     510,   511,   513,   514,   515,   190,   516,   518,   191,   519,
     520,   521,   522,   523,   525,   524,   192,   647,   135,   124,
     125,   526,   527,   528,   530,   173,   532,   533,   534,   535,
     691,   691,   536,   537,   538,   539,   541,   180,   542,   544,
     666,   545,   543,   546,   549,   547,   771,   779,   319,   553,
     550,   551,   554,   557,   556,   558,   559,   181,   772,   780,
     320,   560,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   563,   561,   773,   781,
     321,    94,   317,   318,    94,   564,   568,   562,   569,   570,
     571,   573,   565,   566,   567,   575,   577,   578,   671,   587,
     579,   584,   585,   586,   588,   589,   590,   591,   592,   593,
      94,   594,   595,   596,   597,   600,   601,    32,   602,   603,
     604,   617,   618,   605,   606,   607,   608,   609,   619,   620,
     630,   664,   621,   622,   629,   631,   665,   633,   634,   635,
     636,   637,   638,   639,   712,   716,   654,   720,   724,   728,
     744,   747,   751,   787,   795,   640,   641,   810,   642,   811,
     643,   644,   812,   813,   814,   817,   818,   645,   646,   819,
     648,   820,   821,   827,   830,   826,   851,   649,   650,   829,
     661,   662,   663,   832,   833,   835,   836,   839,   838,   847,
     886,   846,   850,   849,   852,   853,   854,   855,   856,   863,
     885,   872,   867,   871,   874,   878,   879,   881,   882,   883,
     884,   887,   888,   889,   890,   891,   896,   892,   957,   893,
     894,   895,   950,   951,   958,   952,   953,   954,   955,   960,
     962,   963,   980,   966,   986,   987,   988,   989,   993,   990,
     994,   998,   999,  1000,  1001,  1003,  1004,  1009,  1014,  1005,
    1017,  1019,  1024,  1022,  1042,  1043,  1018,  1015,  1044,  1047,
     479,   598,   691,  1021,  1023,   691,   667,   512,   193,  1049,
    1048,   262,   283,   880,   281,   670,   798,   906,   284,  1050,
     211,   897,   930,   276,   899,   236,   294,   932,   298,   920,
     213,   914,   517,  1052,   934,   927,   263,   238,   949,   282,
     212,   771,   911,   277,   779,   555,   295,   931,   948,   921,
     219,   194,   209,   772,   935,   970,   780,   239,   956,   195,
     907,   919,   226,   901,   220,   196,   933,   972,   908,   237,
     900,   926,   214,   773,   909,   197,   781,   915,  1013,   215,
     971,   922,   227,   216,   910,   903,   936,   973,   923,   243,
     529,   902,   924,   937,   222,   905,   244,   938,   904,   965,
     245,   947,   946,   548,   964,   945,   531,   540,   792,   552,
     221,  1016,   961,   785,   959,   572,   576,   668,  1020,   574,
    1040,   979,  1051,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   906,     0,     0,     0,     0,
     930,     0,     0,     0,     0,   932,     0,   920,     0,   914,
       0,   970,   934,     0,     0,     0,     0,     0,     0,     0,
     911,     0,     0,   972,     0,   931,     0,   921,     0,     0,
       0,     0,   935,     0,     0,     0,   971,     0,   907,   919,
       0,     0,     0,   973,   933,     0,   908,     0,     0,     0,
       0,     0,   909,     0,     0,   915,     0,     0,     0,   922,
       0,     0,   910,     0,   936,     0,   923,     0,     0,     0,
     924,   937,     0,     0,     0,   938
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    78,   591,    72,    73,    74,    75,    74,    77,
      78,    68,    80,   526,   362,    73,     5,   837,     7,   532,
       9,     7,    77,    78,    72,    73,    74,    75,   837,    77,
      78,   837,    80,   837,    12,    17,    73,    73,    74,    75,
     102,   103,    10,   143,    73,     0,   146,   147,   148,     7,
      73,    14,    15,     3,    74,    18,     6,    73,    21,    75,
      73,     7,   102,   103,    73,    11,    75,    13,    73,     3,
      75,     7,     3,   166,     8,     7,    22,     8,    24,    25,
      26,    27,    28,    29,    30,    31,    26,    27,    28,    62,
     134,   135,   136,   137,    75,    76,    75,    76,    16,    17,
       3,    74,    75,    76,   166,     8,    52,    53,    54,    55,
      56,    57,    75,    76,    87,    61,    62,    90,     7,     3,
       7,    61,    62,    63,     8,   169,    72,     7,     3,    75,
      76,     6,   113,   114,    61,    75,    76,   116,     7,    85,
      86,    92,    93,    94,    95,    91,    97,     3,    88,    89,
     132,     3,     8,     7,     3,   101,     8,     3,   104,     8,
       7,     3,     8,     3,     6,   111,   112,     3,     8,   115,
       6,   117,   140,    99,   100,   995,   141,   166,   167,   168,
     169,   149,   150,   151,     7,   166,   995,   166,   166,   995,
       7,   995,     7,   166,    25,    26,    27,    28,   166,    19,
      20,     6,     3,   166,    26,    27,    28,     8,    81,    82,
      83,    84,    63,    64,    65,    66,    67,    68,     3,     8,
     166,    52,    53,    54,    75,    76,   166,    58,    59,    60,
       3,    62,     4,     3,     3,     8,   584,   825,     8,     8,
      62,     3,    73,     4,    75,    76,    77,    78,    79,    80,
       3,     8,    32,    75,    76,     8,    87,     3,     3,    90,
      91,     3,     8,     8,    86,     4,     8,    98,     4,     3,
      92,    93,    94,    95,    96,    97,     3,    99,     4,     3,
     360,     8,     3,    63,     8,    65,    66,     8,     4,    69,
      70,    71,     4,   350,   351,    75,    76,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,     3,     3,     3,   394,   166,     8,     8,     8,     4,
     400,   105,   106,   107,   108,   109,   110,     4,    63,     3,
       8,     4,   400,   413,     8,   166,   416,     3,     3,     8,
      75,    76,     8,     8,   166,   413,     3,   427,   416,     3,
     416,     8,   400,     4,     8,   413,     4,   437,     4,   427,
     442,     3,   442,     4,     4,   413,   442,     3,   416,   437,
      33,    34,    35,    36,   442,     8,   413,   413,     4,   427,
     416,     4,   437,   463,   413,     4,   166,   442,     4,   437,
     413,   427,     4,     4,   442,   463,   416,   413,     4,   166,
     413,     4,   167,     4,   413,     4,     4,   142,   413,   144,
     145,   427,     4,     4,     4,   463,     4,   169,   427,   476,
     477,   478,   427,    25,    26,    27,    28,    32,   169,     4,
       4,   166,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,     4,     4,     4,
      52,    53,    54,   966,     4,    57,   167,   167,    63,   167,
      62,    63,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    75,    76,     4,    78,     4,    80,   167,
       4,     4,     4,     4,     4,    87,   169,     4,    90,     4,
       4,     4,     4,     4,     4,   167,    98,   554,   578,    75,
      76,     4,     4,     4,     4,   585,     4,     4,     4,     4,
     590,   591,     4,     4,     4,     4,     4,   585,     4,     4,
     577,     4,   167,     4,     4,   169,   606,   607,   608,     4,
     169,   169,     4,     4,   169,     4,   167,   585,   606,   607,
     608,     4,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,     4,   167,   606,   607,
     608,   166,   138,   139,   166,     4,     4,   167,     4,     4,
       4,     4,   169,   169,   169,     4,     4,     7,    23,   166,
       7,     7,     7,     7,   166,   166,     7,     7,     5,   166,
     166,     5,     5,     5,     5,   166,     5,     7,     5,     5,
       5,   166,   166,     7,     7,     7,     7,     5,   166,     5,
       7,     5,   166,   166,   166,   166,     5,   166,   166,   166,
     166,   166,   166,   166,     7,     7,   133,     7,     7,     7,
       7,     7,     7,     7,     7,   166,   166,     4,   166,     4,
     166,   166,     4,     4,     4,     4,     4,   166,   166,     4,
     166,     4,     4,     3,     3,     6,     4,   166,   166,     6,
     166,   166,   166,     6,     3,     6,     3,     3,     6,     3,
     169,     6,     3,     6,     4,     4,     4,     4,     4,     4,
     167,     3,   166,     6,     8,     6,     4,     4,     4,     4,
       4,   167,   169,   167,     4,     4,   169,   167,     4,   167,
     167,   167,   167,   167,     4,   167,   167,   167,   167,   167,
       6,     3,   166,     4,   166,   166,   166,   166,     8,   166,
       8,     4,     8,     3,     8,   166,   166,     4,     4,   166,
       4,     4,     7,     5,     4,     4,   167,   169,     4,     4,
     360,   501,   822,   166,   166,   825,   578,   394,   828,   167,
     169,   831,   834,   804,   834,   585,   665,   837,   834,   167,
     828,   822,   842,   831,   827,   845,   834,   842,   848,   837,
     828,   837,   400,   166,   842,   840,   831,   845,   850,   834,
     828,   861,   837,   831,   864,   445,   834,   842,   848,   837,
     870,   828,   828,   861,   842,   875,   864,   845,   857,   828,
     837,   837,   870,   830,   870,   828,   842,   875,   837,   845,
     828,   839,   828,   861,   837,   828,   864,   837,   995,   828,
     875,   837,   870,   828,   837,   833,   842,   875,   837,   845,
     413,   831,   837,   842,   870,   836,   845,   842,   834,   872,
     845,   847,   845,   437,   870,   843,   416,   427,   630,   442,
     870,  1000,   864,   608,   861,   463,   469,   579,  1011,   466,
    1028,   876,  1045,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   995,    -1,    -1,    -1,    -1,
    1000,    -1,    -1,    -1,    -1,  1000,    -1,   995,    -1,   995,
      -1,  1011,  1000,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     995,    -1,    -1,  1011,    -1,  1000,    -1,   995,    -1,    -1,
      -1,    -1,  1000,    -1,    -1,    -1,  1011,    -1,   995,   995,
      -1,    -1,    -1,  1011,  1000,    -1,   995,    -1,    -1,    -1,
      -1,    -1,   995,    -1,    -1,   995,    -1,    -1,    -1,   995,
      -1,    -1,   995,    -1,  1000,    -1,   995,    -1,    -1,    -1,
     995,  1000,    -1,    -1,    -1,  1000
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,     5,     7,     9,   166,   167,   168,   169,   186,   187,
     188,   193,     7,   202,     7,   208,     7,   224,     7,   317,
       7,   397,     7,   413,     7,   349,     7,   355,     7,   379,
       7,   293,     7,   473,     7,   521,     7,   513,   194,   189,
     203,   209,   225,   318,   398,   414,   350,   356,   380,   294,
     474,   522,   514,   186,   195,   196,   166,   191,   192,    10,
     140,   149,   150,   151,   166,   201,   204,   205,   206,   504,
     506,   508,   519,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    52,    53,    54,    55,    56,
      57,    61,    62,    72,    75,    76,    85,    86,    91,   101,
     104,   111,   112,   115,   117,   201,   210,   211,   212,   213,
     214,   215,   216,   218,   219,   220,   235,   237,   243,   245,
     278,   287,   301,   311,   339,   347,   373,   403,   405,   407,
     418,   420,   422,   445,   457,   458,   466,   471,   510,    14,
      15,    18,    21,   201,   222,   223,   226,   228,   231,   234,
     403,   405,    58,    59,    60,    73,    77,    78,    79,    80,
      87,    90,    98,   201,   212,   213,   214,   219,   319,   320,
     321,   323,   325,   327,   329,   331,   333,   335,   338,   373,
     391,   403,   405,   407,   418,   420,   422,   442,    74,   201,
     331,   333,   373,   399,   400,   401,   403,   405,    86,    92,
      93,    94,    95,    96,    97,    99,   201,   373,   403,   405,
     415,   416,   417,   418,   420,   422,   424,   428,   430,   432,
     434,   436,   438,   440,   347,    32,    63,    65,    66,    69,
      70,    71,   201,   263,   357,   358,   359,   360,   361,   362,
     363,   365,   367,   369,   370,   372,   403,   405,    64,    67,
      68,   201,   263,   361,   367,   381,   382,   383,   384,   385,
     387,   388,   389,   390,   403,   405,   102,   103,   201,   295,
     296,   297,   299,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   138,   139,   201,
     403,   405,   475,   476,   477,   478,   480,   482,   483,   485,
     486,   487,   490,   492,   493,   494,   495,   498,   500,   502,
     141,   523,   524,   525,    12,   201,   515,   516,   517,     6,
       3,     4,     8,     3,   207,   520,   505,   507,   509,     4,
       3,     8,   511,   512,   221,   238,     4,     4,   419,   421,
     423,   236,   244,   246,     4,     4,     4,     4,   217,   312,
     348,   374,   340,   404,   406,   279,   446,   408,   288,   302,
       4,   459,   467,   472,     3,     8,   227,   229,   232,     4,
       3,     8,   324,   326,   328,   392,   322,   330,     4,   336,
     334,   332,   443,     3,     8,   402,     3,     8,   441,   429,
     431,   435,   433,   439,   437,   425,     8,     3,     8,   364,
     264,     4,   368,   366,   371,     4,     8,     3,   386,     4,
       4,     8,     3,   298,   300,     3,     8,     4,   479,   481,
       4,   484,     4,     4,   488,   491,     4,     4,     4,   496,
     499,   501,   503,     3,     8,   526,     3,     8,   518,     3,
       8,   186,   186,   166,     4,     4,     4,     4,     4,   205,
     515,     4,     4,     4,   169,   169,     4,     4,     4,     4,
       4,     4,   167,   167,   167,   167,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   167,     4,
       4,     4,   211,     4,     4,     4,   169,   223,     4,     4,
       4,     4,     4,     4,   167,     4,     4,     4,     4,   320,
       4,   400,     4,     4,     4,     4,     4,     4,     4,     4,
     417,     4,     4,   167,     4,     4,     4,   169,   359,     4,
     169,   169,   383,     4,     4,   296,   169,     4,     4,   167,
       4,   167,   167,     4,     4,   169,   169,   169,     4,     4,
       4,     4,   476,     4,   524,     4,   516,     4,     7,     7,
     186,   186,   186,     8,     7,     7,     7,   166,   166,   166,
       7,     7,     5,   166,     5,     5,     5,     5,   188,   190,
     166,     5,     5,     5,     5,     7,     7,     7,     7,     5,
     197,    16,    17,   230,    19,    20,   233,   166,   166,   166,
       5,   166,   166,    81,    82,    83,    84,   337,   197,   166,
       7,   166,   197,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   186,   166,   166,
     166,    17,   132,   489,   133,   134,   135,   136,   137,   169,
     497,   166,   166,   166,     5,     5,   186,   210,   523,   515,
     222,    23,   239,   240,   241,    32,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,   201,   251,   252,   253,   256,   258,   260,   262,   263,
     265,   266,   267,   268,   269,   270,   271,   272,   274,   276,
     277,   251,     7,   247,   248,   249,     7,   313,   314,   315,
       7,   351,   352,   353,     7,   375,   376,   377,     7,   341,
     342,   343,    92,    93,    94,    95,    97,   280,   281,   282,
     283,   284,   285,   286,     7,   447,   448,     7,   409,   410,
     411,     7,   289,   290,   291,   105,   106,   107,   108,   109,
     110,   303,   304,   305,   306,   307,   308,   309,   310,   113,
     114,   201,   403,   405,   460,   461,   462,   464,   116,   201,
     403,   405,   468,   469,   470,   475,   198,     7,   393,   394,
     395,   100,   424,   426,   444,     7,   527,   528,   247,     8,
       8,     8,     8,   242,     3,     8,   254,   257,   259,   261,
       4,     4,     4,     4,     4,   273,   275,     4,     4,     4,
       4,     4,     3,     8,     8,   250,     6,     3,   316,     6,
       3,   354,     6,     3,   378,     6,     3,   344,     6,     3,
       3,     6,   449,     3,     6,   412,     6,     3,   292,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   463,
     465,     3,     8,     4,     3,     8,     8,   166,   199,   200,
     396,     6,     3,   427,     8,   529,     3,     6,     6,     4,
     240,     4,     4,     4,     4,   167,   169,   167,   169,   167,
       4,     4,   167,   167,   167,   167,   169,   252,   251,   249,
     319,   315,   357,   353,   381,   377,   201,   212,   213,   214,
     219,   263,   311,   329,   331,   333,   335,   345,   346,   373,
     403,   405,   418,   420,   422,   442,   343,   281,    88,    89,
     201,   263,   347,   373,   403,   405,   418,   420,   422,   450,
     451,   452,   453,   454,   456,   448,   415,   411,   295,   291,
     167,   167,   167,   167,   167,   167,   304,     4,     4,   461,
     167,   469,     6,     3,   399,   395,     4,   142,   144,   145,
     201,   263,   403,   405,   530,   531,   532,   533,   535,   528,
     166,    33,    34,    35,    36,   255,   166,   166,   166,   166,
     166,     8,     8,     8,     8,     3,     8,   455,     4,     8,
       3,     8,     8,   166,   166,   166,     8,   197,   536,     4,
     534,     3,     8,   346,     4,   169,   452,     4,   167,     4,
     531,   166,     5,   166,     7,   537,   538,   539,     3,     6,
     143,   146,   147,   148,   540,   541,   542,   544,   545,   546,
     538,   543,     4,     4,     4,     3,     8,     4,   169,   167,
     167,   541,   166
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   170,   172,   171,   173,   171,   174,   171,   175,   171,
     176,   171,   177,   171,   178,   171,   179,   171,   180,   171,
     181,   171,   182,   171,   183,   171,   184,   171,   185,   171,
     186,   186,   186,   186,   186,   186,   186,   187,   189,   188,
     190,   191,   191,   192,   192,   194,   193,   195,   195,   196,
     196,   198,   197,   199,   199,   200,   200,   201,   203,   202,
     204,   204,   205,   205,   205,   205,   205,   205,   207,   206,
     209,   208,   210,   210,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   212,   213,   214,   215,
     217,   216,   218,   219,   221,   220,   222,   222,   223,   223,
     223,   223,   223,   223,   223,   225,   224,   227,   226,   229,
     228,   230,   230,   232,   231,   233,   233,   234,   236,   235,
     238,   237,   239,   239,   240,   242,   241,   244,   243,   246,
     245,   247,   247,   248,   248,   250,   249,   251,   251,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   254,   253,   255,
     255,   255,   255,   257,   256,   259,   258,   261,   260,   262,
     264,   263,   265,   266,   267,   268,   269,   270,   271,   273,
     272,   275,   274,   276,   277,   279,   278,   280,   280,   281,
     281,   281,   281,   281,   282,   283,   284,   285,   286,   288,
     287,   289,   289,   290,   290,   292,   291,   294,   293,   295,
     295,   295,   296,   296,   298,   297,   300,   299,   302,   301,
     303,   303,   304,   304,   304,   304,   304,   304,   305,   306,
     307,   308,   309,   310,   312,   311,   313,   313,   314,   314,
     316,   315,   318,   317,   319,   319,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   322,
     321,   324,   323,   326,   325,   328,   327,   330,   329,   332,
     331,   334,   333,   336,   335,   337,   337,   337,   337,   338,
     340,   339,   341,   341,   342,   342,   344,   343,   345,   345,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   348,   347,
     350,   349,   351,   351,   352,   352,   354,   353,   356,   355,
     357,   357,   358,   358,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   360,   361,   362,   364,   363,   366,
     365,   368,   367,   369,   371,   370,   372,   374,   373,   375,
     375,   376,   376,   378,   377,   380,   379,   381,   381,   382,
     382,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     384,   386,   385,   387,   388,   389,   390,   392,   391,   393,
     393,   394,   394,   396,   395,   398,   397,   399,   399,   400,
     400,   400,   400,   400,   400,   400,   402,   401,   404,   403,
     406,   405,   408,   407,   409,   409,   410,   410,   412,   411,
     414,   413,   415,   415,   416,   416,   417,   417,   417,   417,
     417,   417,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   419,   418,   421,   420,   423,   422,   425,   424,   427,
     426,   429,   428,   431,   430,   433,   432,   435,   434,   437,
     436,   439,   438,   441,   440,   443,   442,   444,   444,   446,
     445,   447,   447,   449,   448,   450,   450,   451,   451,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     453,   455,   454,   456,   457,   459,   458,   460,   460,   461,
     461,   461,   461,   461,   463,   462,   465,   464,   467,   466,
     468,   468,   469,   469,   469,   469,   470,   472,   471,   474,
     473,   475,   475,   476,   476,   476,   476,   476,   476,   476,
     476,   476,   476,   476,   476,   476,   476,   476,   476,   476,
     476,   476,   477,   479,   478,   481,   480,   482,   484,   483,
     485,   486,   488,   487,   489,   489,   491,   490,   492,   493,
     494,   496,   495,   497,   497,   497,   497,   497,   499,   498,
     501,   500,   503,   502,   505,   504,   507,   506,   509,   508,
     511,   510,   512,   510,   514,   513,   515,   515,   516,   516,
     518,   517,   520,   519,   522,   521,   523,   523,   524,   526,
     525,   527,   527,   529,   528,   530,   530,   531,   531,   531,
     531,   531,   531,   531,   532,   534,   533,   536,   535,   537,
     537,   539,   538,   540,   540,   541,   541,   541,   541,   543,
     542,   544,   545,   546
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
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
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       0,     4,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     0,     4,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     1,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     3,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       0,     6,     0,     6,     0,     4,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"outbound-interface\"",
  "\"same-as-inbound\"", "\"use-routing\"", "\"re-detect\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"queue-control\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "server_tag", "$@21",
  "echo_client_id", "match_client_id", "interfaces_config", "$@22",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@23", "interfaces_list", "$@24", "dhcp_socket_type", "$@25",
  "socket_type", "outbound_interface", "$@26", "outbound_interface_value",
  "re_detect", "lease_database", "$@27", "sanity_checks", "$@28",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@29",
  "hosts_database", "$@30", "hosts_databases", "$@31", "database_list",
  "not_empty_database_list", "database", "$@32", "database_map_params",
  "database_map_param", "database_type", "$@33", "db_type", "user", "$@34",
  "password", "$@35", "host", "$@36", "port", "name", "$@37", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@38", "keyspace",
  "$@39", "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@40",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@41", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@42",
  "sub_hooks_library", "$@43", "hooks_params", "hooks_param", "library",
  "$@44", "parameters", "$@45", "expired_leases_processing", "$@46",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@47",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@48",
  "sub_subnet4", "$@49", "subnet4_params", "subnet4_param", "subnet",
  "$@50", "subnet_4o6_interface", "$@51", "subnet_4o6_interface_id",
  "$@52", "subnet_4o6_subnet", "$@53", "interface", "$@54", "client_class",
  "$@55", "require_client_classes", "$@56", "reservation_mode", "$@57",
  "hr_mode", "id", "shared_networks", "$@58", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@59",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@60", "sub_option_def_list", "$@61", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@62",
  "sub_option_def", "$@63", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@64",
  "option_def_record_types", "$@65", "space", "$@66", "option_def_space",
  "option_def_encapsulate", "$@67", "option_def_array", "option_data_list",
  "$@68", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@69", "sub_option_data", "$@70",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@71",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@72", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@73", "sub_pool4", "$@74",
  "pool_params", "pool_param", "pool_entry", "$@75", "user_context",
  "$@76", "comment", "$@77", "reservations", "$@78", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@79", "sub_reservation",
  "$@80", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@81", "server_hostname", "$@82",
  "boot_file_name", "$@83", "ip_address", "$@84", "ip_addresses", "$@85",
  "duid", "$@86", "hw_address", "$@87", "client_id_value", "$@88",
  "circuit_id_value", "$@89", "flex_id_value", "$@90", "hostname", "$@91",
  "reservation_client_classes", "$@92", "relay", "$@93", "relay_map",
  "client_classes", "$@94", "client_classes_list", "client_class_entry",
  "$@95", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@96",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@97",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@98", "control_socket_name", "$@99", "queue_control", "$@100",
  "queue_control_params", "queue_control_param", "capacity", "dhcp_ddns",
  "$@101", "sub_dhcp_ddns", "$@102", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@103", "server_ip", "$@104",
  "server_port", "sender_ip", "$@105", "sender_port", "max_queue_size",
  "ncr_protocol", "$@106", "ncr_protocol_value", "ncr_format", "$@107",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@108", "replace_client_name_value",
  "generated_prefix", "$@109", "hostname_char_set", "$@110",
  "hostname_char_replacement", "$@111", "dhcp6_json_object", "$@112",
  "dhcpddns_json_object", "$@113", "control_agent_json_object", "$@114",
  "config_control", "$@115", "$@116", "sub_config_control", "$@117",
  "config_control_params", "config_control_param", "config_databases",
  "$@118", "logging_object", "$@119", "sub_logging", "$@120",
  "logging_params", "logging_param", "loggers", "$@121", "loggers_entries",
  "logger_entry", "$@122", "logger_params", "logger_param", "debuglevel",
  "severity", "$@123", "output_options_list", "$@124",
  "output_options_list_content", "output_entry", "$@125",
  "output_params_list", "output_params", "output", "$@126", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   255,   255,   255,   256,   256,   257,   257,   258,   258,
     259,   259,   260,   260,   261,   261,   262,   262,   263,   263,
     264,   264,   265,   265,   266,   266,   267,   267,   268,   268,
     276,   277,   278,   279,   280,   281,   282,   285,   290,   290,
     301,   304,   305,   308,   312,   319,   319,   326,   327,   330,
     334,   341,   341,   348,   349,   352,   356,   367,   377,   377,
     393,   394,   398,   399,   400,   401,   402,   403,   406,   406,
     421,   421,   430,   431,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   470,   475,   480,   485,
     490,   490,   498,   503,   509,   509,   520,   521,   524,   525,
     526,   527,   528,   529,   530,   533,   533,   542,   542,   552,
     552,   559,   560,   563,   563,   570,   572,   576,   582,   582,
     594,   594,   604,   605,   607,   609,   609,   627,   627,   639,
     639,   649,   650,   653,   654,   657,   657,   667,   668,   671,
     672,   673,   674,   675,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,   687,   688,   691,   691,   698,
     699,   700,   701,   704,   704,   712,   712,   720,   720,   728,
     733,   733,   741,   746,   751,   756,   761,   766,   771,   776,
     776,   784,   784,   792,   797,   802,   802,   812,   813,   816,
     817,   818,   819,   820,   823,   828,   833,   838,   843,   848,
     848,   858,   859,   862,   863,   866,   866,   876,   876,   886,
     887,   888,   891,   892,   895,   895,   903,   903,   911,   911,
     922,   923,   926,   927,   928,   929,   930,   931,   934,   939,
     944,   949,   954,   959,   967,   967,   980,   981,   984,   985,
     992,   992,  1018,  1018,  1029,  1030,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,
    1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,  1059,
    1059,  1067,  1067,  1075,  1075,  1083,  1083,  1091,  1091,  1099,
    1099,  1107,  1107,  1117,  1117,  1124,  1125,  1126,  1127,  1130,
    1137,  1137,  1148,  1149,  1153,  1154,  1157,  1157,  1165,  1166,
    1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,
    1179,  1180,  1181,  1182,  1183,  1184,  1185,  1186,  1193,  1193,
    1206,  1206,  1215,  1216,  1219,  1220,  1225,  1225,  1240,  1240,
    1254,  1255,  1258,  1259,  1262,  1263,  1264,  1265,  1266,  1267,
    1268,  1269,  1270,  1271,  1274,  1276,  1281,  1283,  1283,  1291,
    1291,  1299,  1299,  1307,  1309,  1309,  1317,  1326,  1326,  1338,
    1339,  1344,  1345,  1350,  1350,  1362,  1362,  1374,  1375,  1380,
    1381,  1386,  1387,  1388,  1389,  1390,  1391,  1392,  1393,  1394,
    1397,  1399,  1399,  1407,  1409,  1411,  1416,  1424,  1424,  1436,
    1437,  1440,  1441,  1444,  1444,  1454,  1454,  1464,  1465,  1468,
    1469,  1470,  1471,  1472,  1473,  1474,  1477,  1477,  1485,  1485,
    1510,  1510,  1540,  1540,  1550,  1551,  1554,  1555,  1558,  1558,
    1567,  1567,  1576,  1577,  1580,  1581,  1585,  1586,  1587,  1588,
    1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,
    1599,  1602,  1602,  1610,  1610,  1618,  1618,  1626,  1626,  1634,
    1634,  1644,  1644,  1652,  1652,  1660,  1660,  1668,  1668,  1676,
    1676,  1684,  1684,  1692,  1692,  1705,  1705,  1715,  1716,  1722,
    1722,  1732,  1733,  1736,  1736,  1746,  1747,  1750,  1751,  1754,
    1755,  1756,  1757,  1758,  1759,  1760,  1761,  1762,  1763,  1764,
    1767,  1769,  1769,  1777,  1786,  1793,  1793,  1803,  1804,  1807,
    1808,  1809,  1810,  1811,  1814,  1814,  1822,  1822,  1833,  1833,
    1844,  1845,  1848,  1849,  1850,  1851,  1854,  1861,  1861,  1873,
    1873,  1883,  1884,  1887,  1888,  1889,  1890,  1891,  1892,  1893,
    1894,  1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,  1903,
    1904,  1905,  1908,  1913,  1913,  1921,  1921,  1929,  1934,  1934,
    1942,  1947,  1952,  1952,  1960,  1961,  1964,  1964,  1972,  1977,
    1982,  1987,  1987,  1995,  1998,  2001,  2004,  2007,  2013,  2013,
    2021,  2021,  2029,  2029,  2040,  2040,  2047,  2047,  2054,  2054,
    2061,  2061,  2070,  2070,  2081,  2081,  2091,  2092,  2096,  2097,
    2100,  2100,  2115,  2115,  2125,  2125,  2136,  2137,  2141,  2145,
    2145,  2157,  2158,  2162,  2162,  2170,  2171,  2174,  2175,  2176,
    2177,  2178,  2179,  2180,  2183,  2188,  2188,  2196,  2196,  2206,
    2207,  2210,  2210,  2218,  2219,  2222,  2223,  2224,  2225,  2228,
    2228,  2236,  2241,  2246
  };

  // Print the state stack on the debug stream.
  void
  Dhcp4Parser::yystack_print_ ()
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4908 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2251 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
