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
      case 188: // value
      case 192: // map_value
      case 236: // socket_type
      case 239: // outbound_interface_value
      case 261: // db_type
      case 343: // hr_mode
      case 492: // ncr_protocol_value
      case 499: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 171: // "boolean"
        value.move< bool > (that.value);
        break;

      case 170: // "floating point"
        value.move< double > (that.value);
        break;

      case 169: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 168: // "constant string"
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
      case 188: // value
      case 192: // map_value
      case 236: // socket_type
      case 239: // outbound_interface_value
      case 261: // db_type
      case 343: // hr_mode
      case 492: // ncr_protocol_value
      case 499: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 171: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 170: // "floating point"
        value.copy< double > (that.value);
        break;

      case 169: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 168: // "constant string"
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
            case 168: // "constant string"

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 169: // "integer"

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 170: // "floating point"

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 171: // "boolean"

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 188: // value

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 192: // map_value

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 236: // socket_type

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 239: // outbound_interface_value

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 261: // db_type

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 343: // hr_mode

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 492: // ncr_protocol_value

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 499: // replace_client_name_value

#line 248 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 188: // value
      case 192: // map_value
      case 236: // socket_type
      case 239: // outbound_interface_value
      case 261: // db_type
      case 343: // hr_mode
      case 492: // ncr_protocol_value
      case 499: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 171: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 170: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 169: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 168: // "constant string"
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
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 283 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 310 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 314 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 332 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 336 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 354 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 358 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 384 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 408 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 487 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 586 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 725 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1707 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 986 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 994 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1122 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2023 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2061 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2096 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1173 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2527 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2535 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1547 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2575 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
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

    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

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
#line 3040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1986 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2005 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3201 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3219 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3228 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3254 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2034 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2037 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2043 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2046 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3295 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2062 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3374 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2129 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2144 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2174 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2179 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2191 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 640:
#line 2217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 641:
#line 2219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 642:
#line 2225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 643:
#line 2230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3593 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 654:
#line 2257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 655:
#line 2259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 656:
#line 2265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 657:
#line 2270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 658:
#line 2275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3646 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3650 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -812;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     437,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,    28,    35,    58,    60,    62,
      64,    75,    94,    96,   108,   110,   143,   160,   169,   177,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,    35,   -78,
      17,    82,    43,   154,   181,   397,    32,    54,   399,   -27,
     449,   -11,   152,  -812,   190,   196,   206,   204,   227,  -812,
    -812,  -812,  -812,  -812,   228,  -812,    81,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,   247,   253,   263,  -812,
    -812,  -812,  -812,  -812,  -812,   281,   282,   292,   337,  -812,
    -812,  -812,  -812,   338,   344,   346,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,   347,  -812,  -812,  -812,  -812,
      83,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,   348,  -812,   139,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,   349,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
     146,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,   157,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,   235,   323,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,   326,  -812,  -812,   350,
    -812,  -812,  -812,   353,  -812,  -812,   328,   358,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,   360,   361,  -812,  -812,  -812,  -812,   354,   363,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,   170,  -812,  -812,  -812,   366,  -812,  -812,   368,  -812,
     371,   372,  -812,  -812,   373,   376,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,   183,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,   192,  -812,  -812,  -812,   213,  -812,  -812,  -812,    35,
      35,  -812,   199,   379,   381,   383,   387,   389,  -812,    17,
    -812,   390,   391,   392,   230,   231,   232,   394,   395,   403,
     404,   407,   408,   244,   245,   250,   252,   412,   423,   426,
     427,   267,   264,   269,   441,   442,   445,   446,   451,   452,
     453,   454,   455,   284,   457,   458,   465,    82,  -812,   467,
     468,   469,   299,    43,  -812,   470,   471,   476,   477,   478,
     479,   316,   480,   482,   484,   154,  -812,   485,   181,  -812,
     486,   487,   488,   497,   498,   499,   515,   516,  -812,   397,
    -812,   519,   520,   356,   522,   527,   528,   362,  -812,    54,
     530,   364,   365,  -812,   399,   533,   534,    46,  -812,   370,
     535,   538,   374,   541,   377,   378,   544,   545,   380,   385,
     546,   548,   550,   553,   449,  -812,   555,   -11,  -812,   556,
     152,  -812,  -812,  -812,   557,   562,   576,    35,    35,    35,
    -812,   578,   580,   581,  -812,  -812,  -812,   396,   438,   439,
     598,   601,   558,  -812,  -812,  -812,  -812,   443,   604,   605,
     607,  -812,  -812,  -812,   608,   609,   447,   220,   613,   614,
     615,   616,   617,  -812,   618,   609,   619,  -812,   622,   158,
     173,  -812,  -812,   460,   461,   462,   626,   464,   472,  -812,
     622,   473,   628,  -812,   474,  -812,   622,   475,   481,   483,
     489,   490,   491,   492,  -812,   493,   494,  -812,   495,   496,
     500,  -812,  -812,   501,  -812,  -812,  -812,   502,    35,  -812,
    -812,   503,   504,  -812,   505,  -812,  -812,    29,   509,  -812,
    -812,    87,   506,   507,   508,  -812,   631,  -812,   632,  -812,
      35,    82,   -11,  -812,  -812,  -812,   152,    43,   539,  -812,
    -812,  -812,   466,   466,   638,  -812,   639,   640,   641,   643,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,   -23,   645,
     646,   647,   167,   -20,  -812,   449,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,   648,  -812,  -812,
    -812,  -812,   136,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,   649,   638,  -812,   238,
     239,   265,   266,  -812,   279,  -812,  -812,  -812,  -812,  -812,
    -812,   610,   629,   634,   635,   661,  -812,  -812,   662,   663,
     673,   674,   675,  -812,   285,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,   286,  -812,   676,   620,  -812,  -812,   677,
     678,  -812,  -812,   679,   681,  -812,  -812,   680,   684,  -812,
    -812,   682,   686,  -812,  -812,  -812,  -812,  -812,  -812,    99,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,   113,  -812,  -812,
     685,   687,  -812,  -812,   688,   689,  -812,   691,   692,   693,
     694,   695,   696,   294,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,   295,  -812,  -812,  -812,
     301,   512,  -812,   697,   690,  -812,  -812,  -812,  -812,   698,
    -812,   125,  -812,   699,  -812,  -812,  -812,  -812,   700,   539,
    -812,   703,   704,   705,   706,   532,   531,   542,   543,   547,
     708,   709,   549,   551,   552,   554,   559,   466,  -812,  -812,
     466,  -812,   638,   154,  -812,   639,    54,  -812,   640,   399,
    -812,   641,   237,  -812,   643,   -23,  -812,   191,   645,  -812,
     397,  -812,   646,   -27,  -812,   647,   560,   563,   564,   565,
     566,   567,   167,  -812,   711,   713,   -20,  -812,  -812,  -812,
     716,   721,   181,  -812,   648,   715,  -812,   -17,   649,  -812,
    -812,   569,  -812,   310,   570,   571,   572,  -812,  -812,  -812,
    -812,  -812,   573,   574,  -812,  -812,  -812,  -812,  -812,  -812,
     312,  -812,   315,  -812,   717,  -812,   718,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,   321,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,   723,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,   720,   728,  -812,  -812,  -812,
    -812,  -812,   735,  -812,   322,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,   577,   579,  -812,  -812,   582,   324,  -812,
     622,  -812,   740,  -812,  -812,  -812,  -812,  -812,   330,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,   237,
    -812,   742,   583,  -812,   191,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,   744,   584,   745,   -17,  -812,  -812,   587,  -812,
    -812,   746,  -812,   588,  -812,  -812,   750,  -812,  -812,   140,
    -812,  -100,   750,  -812,  -812,   748,   754,   755,   332,  -812,
    -812,  -812,  -812,  -812,  -812,   756,   590,   593,   595,  -100,
    -812,   597,  -812,  -812,  -812,  -812,  -812
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   134,     9,   271,    11,
     432,    13,   457,    15,   357,    17,   365,    19,   402,    21,
     236,    23,   549,    25,   619,    27,   610,    29,    47,    41,
       0,     0,     0,     0,     0,   459,     0,   367,   404,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     617,   602,   604,   606,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   608,   123,   149,     0,     0,     0,   478,
     480,   482,   147,   156,   158,     0,     0,     0,     0,   118,
     263,   355,   394,     0,     0,     0,   323,   445,   447,   316,
     214,   506,   449,   228,   247,     0,   532,   545,   547,   110,
       0,    72,    74,    75,    76,   107,   108,   109,    77,   105,
      94,    95,    96,    80,    81,   102,    82,    83,    84,    88,
      89,    78,   106,    79,    86,    87,   100,   101,   103,    97,
      98,    99,    85,    90,    91,    92,    93,   104,   136,   138,
     142,     0,   133,     0,   125,   127,   128,   129,   130,   131,
     132,   304,   306,   308,   424,   302,   310,     0,   314,   312,
     502,   301,   275,   276,   277,   298,   299,   300,   288,   289,
       0,   273,   280,   293,   294,   295,   281,   283,   284,   286,
     282,   278,   279,   296,   297,   285,   290,   291,   292,   287,
     443,   442,   438,   439,   437,     0,   434,   436,   440,   441,
     500,   488,   490,   494,   492,   498,   496,   484,   477,   471,
     475,   476,     0,   460,   461,   472,   473,   474,   468,   463,
     469,   465,   466,   467,   470,   464,     0,   384,   199,     0,
     388,   386,   391,     0,   380,   381,     0,   368,   369,   371,
     383,   372,   373,   374,   390,   375,   376,   377,   378,   379,
     418,     0,     0,   416,   417,   420,   421,     0,   405,   406,
     408,   409,   410,   411,   412,   413,   414,   415,   243,   245,
     240,     0,   238,   241,   242,     0,   572,   574,     0,   577,
       0,     0,   581,   585,     0,     0,   589,   596,   598,   600,
     570,   568,   569,     0,   551,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     624,     0,   621,   623,   615,     0,   612,   614,    46,     0,
       0,    39,     0,     0,     0,     0,     0,     0,    57,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,   135,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   272,     0,     0,   433,
       0,     0,     0,     0,     0,     0,     0,     0,   458,     0,
     358,     0,     0,     0,     0,     0,     0,     0,   366,     0,
       0,     0,     0,   403,     0,     0,     0,     0,   237,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   550,     0,     0,   620,     0,
       0,   611,    50,    43,     0,     0,     0,     0,     0,     0,
      61,     0,     0,     0,   120,   121,   122,     0,     0,     0,
       0,     0,     0,   111,   112,   113,   117,     0,     0,     0,
       0,   114,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   531,     0,     0,     0,    73,     0,     0,
       0,   146,   126,     0,     0,     0,     0,     0,     0,   322,
       0,     0,     0,   274,     0,   435,     0,     0,     0,     0,
       0,     0,     0,     0,   462,     0,     0,   382,     0,     0,
       0,   393,   370,     0,   422,   423,   407,     0,     0,   239,
     571,     0,     0,   576,     0,   579,   580,     0,     0,   587,
     588,     0,     0,     0,     0,   552,     0,   622,     0,   613,
       0,     0,     0,   603,   605,   607,     0,     0,     0,   479,
     481,   483,     0,     0,   160,   119,   265,   359,   396,   325,
      40,   446,   448,   318,   319,   320,   321,   317,     0,     0,
     451,   230,     0,     0,   546,     0,    51,   137,   140,   141,
     139,   144,   145,   143,   305,   307,   309,   426,   303,   311,
     315,   313,     0,   444,   501,   489,   491,   495,   493,   499,
     497,   485,   385,   200,   389,   387,   392,   419,   244,   246,
     573,   575,   578,   583,   584,   582,   586,   591,   592,   593,
     594,   595,   590,   597,   599,   601,     0,   160,    44,     0,
       0,     0,     0,   154,     0,   151,   153,   186,   192,   194,
     196,     0,     0,     0,     0,     0,   208,   210,     0,     0,
       0,     0,     0,   185,     0,   166,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   181,   182,   183,   178,
     184,   179,   180,     0,   164,     0,   161,   162,   269,     0,
     266,   267,   363,     0,   360,   361,   400,     0,   397,   398,
     329,     0,   326,   327,   223,   224,   225,   226,   227,     0,
     216,   218,   219,   220,   221,   222,   510,     0,   508,   455,
       0,   452,   453,   234,     0,   231,   232,     0,     0,     0,
       0,     0,     0,     0,   249,   251,   252,   253,   254,   255,
     256,   541,   543,   540,   538,   539,     0,   534,   536,   537,
       0,    53,   430,     0,   427,   428,   486,   504,   505,     0,
     628,     0,   626,     0,    69,   618,   609,   124,     0,     0,
     150,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   148,   157,
       0,   159,     0,     0,   264,     0,   367,   356,     0,   404,
     395,     0,     0,   324,     0,     0,   215,   512,     0,   507,
     459,   450,     0,     0,   229,     0,     0,     0,     0,     0,
       0,     0,     0,   248,     0,     0,     0,   533,   548,    55,
       0,    54,     0,   425,     0,     0,   503,     0,     0,   625,
     616,     0,   152,     0,     0,     0,     0,   198,   201,   202,
     203,   204,     0,     0,   212,   213,   205,   206,   207,   167,
       0,   163,     0,   268,     0,   362,     0,   399,   354,   348,
     336,   337,   351,   352,   353,   339,   340,   333,   334,   335,
     346,   347,   345,     0,   331,   338,   349,   350,   341,   342,
     343,   344,   328,   217,   528,     0,   526,   527,   519,   520,
     524,   525,   521,   522,   523,     0,   513,   514,   516,   517,
     518,   509,     0,   454,     0,   233,   257,   258,   259,   260,
     261,   262,   250,     0,     0,   535,    52,     0,     0,   429,
       0,   642,     0,   640,   638,   632,   636,   637,     0,   630,
     634,   635,   633,   627,   155,   188,   189,   190,   191,   187,
     193,   195,   197,   209,   211,   165,   270,   364,   401,     0,
     330,     0,     0,   511,     0,   456,   235,   542,   544,    56,
     431,   487,     0,     0,     0,     0,   629,   332,     0,   530,
     515,     0,   639,     0,   631,   529,     0,   641,   646,     0,
     644,     0,     0,   643,   654,     0,     0,     0,     0,   648,
     650,   651,   652,   653,   645,     0,     0,     0,     0,     0,
     647,     0,   656,   657,   658,   649,   655
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,   -46,  -812,  -472,  -812,
      97,  -812,  -812,  -812,  -812,  -812,  -812,  -516,  -812,  -812,
    -812,   -70,  -812,  -812,  -812,   398,  -812,  -812,  -812,  -812,
     179,   384,   -47,   -44,     4,    12,    15,    19,  -812,  -812,
    -812,  -812,    23,    26,  -812,  -812,   171,   375,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,   -31,  -812,  -812,  -812,  -812,  -812,
    -812,   104,  -812,   -40,  -812,  -578,   -28,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,   -26,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,   -33,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,   -54,  -812,  -812,  -812,   -48,
     367,  -812,  -812,  -812,  -812,  -812,  -812,  -812,   -56,  -812,
    -812,  -812,  -812,  -812,  -812,  -811,  -812,  -812,  -812,   -16,
    -812,  -812,  -812,   -15,   400,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -810,  -812,   -68,  -812,   -55,  -812,    27,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,   -22,  -812,  -812,
    -170,   -63,  -812,  -812,  -812,  -812,  -812,    -6,  -812,  -812,
    -812,    -2,  -812,   393,  -812,   -66,  -812,  -812,  -812,  -812,
    -812,   -64,  -812,  -812,  -812,  -812,  -812,   -19,  -812,  -812,
    -812,    -5,  -812,  -812,  -812,    10,  -812,   409,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,   -12,
    -812,  -812,  -812,    -8,   444,  -812,  -812,   -57,  -812,   -39,
    -812,   -62,  -812,  -812,  -812,    14,  -812,  -812,  -812,    20,
    -812,   428,    -7,  -812,    -3,  -812,     8,  -812,   229,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -805,  -812,  -812,  -812,
    -812,  -812,    25,  -812,  -812,  -812,  -130,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,     9,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,   251,   405,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,  -812,
    -812,  -812,  -812,  -812,   287,   401,  -812,  -812,  -812,  -812,
    -812,  -812,   288,   410,  -812,  -812,  -812,    -1,  -812,  -812,
    -137,  -812,  -812,  -812,  -812,  -812,  -812,  -150,  -812,  -812,
    -165,  -812,  -812,  -812,  -812,  -812
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     611,    87,    88,    41,    68,    84,    85,   627,   791,   870,
     871,   703,    43,    70,    96,    97,    98,   363,    45,    71,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     387,   150,   151,   152,   153,   372,   183,   184,    47,    72,
     185,   409,   186,   410,   630,   187,   411,   633,   188,   154,
     380,   155,   373,   684,   685,   686,   808,   156,   381,   157,
     382,   725,   726,   727,   830,   704,   705,   706,   811,   989,
     707,   812,   708,   813,   709,   814,   710,   711,   442,   712,
     713,   714,   715,   716,   717,   718,   719,   820,   720,   821,
     721,   722,   158,   398,   749,   750,   751,   752,   753,   754,
     755,   159,   401,   764,   765,   766,   853,    61,    79,   311,
     312,   313,   455,   314,   456,   160,   402,   773,   774,   775,
     776,   777,   778,   779,   780,   161,   388,   729,   730,   731,
     833,    49,    73,   210,   211,   212,   419,   213,   415,   214,
     416,   215,   417,   216,   420,   217,   423,   218,   422,   162,
     397,   617,   220,   163,   394,   741,   742,   743,   842,   923,
     924,   164,   389,    55,    76,   733,   734,   735,   836,    57,
      77,   276,   277,   278,   279,   280,   281,   282,   441,   283,
     445,   284,   444,   285,   286,   446,   287,   165,   390,   737,
     738,   739,   839,    59,    78,   297,   298,   299,   300,   301,
     450,   302,   303,   304,   305,   222,   418,   793,   794,   795,
     872,    51,    74,   235,   236,   237,   427,   166,   395,   167,
     396,   168,   400,   760,   761,   762,   850,    53,    75,   252,
     253,   254,   169,   377,   170,   378,   171,   379,   258,   437,
     798,   875,   259,   431,   260,   432,   261,   434,   262,   433,
     263,   436,   264,   435,   265,   430,   229,   424,   799,   172,
     399,   757,   758,   847,   945,   946,   947,   948,   949,  1001,
     950,   173,   174,   404,   786,   787,   788,   864,   789,   865,
     175,   405,   176,   406,    63,    80,   333,   334,   335,   336,
     460,   337,   461,   338,   339,   463,   340,   341,   342,   466,
     665,   343,   467,   344,   345,   346,   470,   672,   347,   471,
     348,   472,   349,   473,    99,   365,   100,   366,   101,   367,
     177,   371,    67,    82,   355,   356,   357,   479,   102,   364,
      65,    81,   351,   352,   353,   476,   801,   802,   877,   978,
     979,   980,   981,  1014,   982,  1012,  1029,  1030,  1031,  1038,
    1039,  1040,  1045,  1041,  1042,  1043
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   139,   182,   201,   231,   248,   232,   274,   293,   310,
     330,   225,   295,   266,   296,   189,   223,   238,   250,   233,
     288,   306,    83,   331,   640,   723,   202,    89,    30,   203,
     644,   918,   919,   190,   224,   239,   251,   931,   289,   307,
      31,   332,    32,   610,    33,  1034,   663,   268,  1035,  1036,
    1037,   275,   294,   610,   221,   234,   249,   178,   179,   127,
     128,   180,   127,   128,   181,    42,   226,    44,   255,    46,
     227,    48,   256,   744,   745,   746,   747,   204,   748,   308,
     309,   228,    50,   257,   369,   205,   407,   267,   206,   370,
      86,   408,   207,   103,   121,   104,   208,   781,   782,   209,
     219,    52,   845,    54,   105,   846,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    56,   848,    58,   268,   849,
     269,   270,   127,   128,   271,   272,   273,   971,   878,   972,
     973,   879,   350,   127,   128,   115,   116,   117,   118,   119,
     120,    94,   413,  1032,   121,   122,  1033,   414,    94,   425,
      60,    94,   308,   309,   426,   123,   124,   125,   126,    90,
     428,   127,   128,   664,   354,   429,   129,    62,    91,    92,
      93,   130,   131,   457,   628,   629,    64,   132,   458,   107,
     108,   109,   110,   111,    66,    94,   474,   133,   918,   919,
     134,   475,   631,   632,   931,   477,   358,   135,   136,   359,
     478,   137,   138,    34,    35,    36,    37,   115,   116,   117,
     360,    94,   361,   191,   192,   193,   480,   122,   109,   110,
     111,   481,    94,   667,   668,   669,   670,   123,   124,   125,
     362,   194,   368,   127,   128,   195,   196,   197,   129,   247,
     796,   407,   477,   438,   122,   198,   804,   805,   199,   132,
      94,   374,   900,   121,   122,   268,   200,   375,   671,   230,
     127,   128,   107,   108,   109,   110,   111,   376,   480,   413,
     127,   128,   198,   806,   807,   199,   767,   768,   769,   770,
     771,   772,   809,   934,   935,   383,   384,   810,   827,   827,
     115,   116,   117,   828,   829,   120,   385,   862,   866,    95,
     122,   268,   863,   867,   474,   613,   614,   615,   616,   868,
     123,   124,   125,   482,   483,   827,   127,   128,   425,   196,
     995,   129,    94,   996,   999,   457,   439,   428,   198,  1000,
    1006,   199,  1010,  1015,   440,  1049,   448,   139,  1016,   200,
    1050,   386,   391,   182,   985,   986,   987,   988,   392,    94,
     393,   403,   412,   421,   443,   201,   189,   447,   231,    94,
     232,   449,   453,   225,   451,   452,   454,   484,   223,   248,
     459,   238,   462,   233,   190,   464,   465,   468,   202,   274,
     469,   203,   250,   485,   293,   486,   224,   487,   295,   239,
     296,   488,   288,   489,   491,   492,   493,   306,   497,   498,
     251,   494,   495,   496,   330,    94,   221,   499,   500,   234,
     289,   501,   502,   503,   504,   307,   507,   331,   226,   505,
     249,   506,   227,   275,   109,   110,   111,   508,   294,   204,
     509,   510,   255,   228,   512,   332,   256,   205,   511,   513,
     206,   593,   594,   595,   207,   514,   515,   257,   208,   516,
     517,   209,   219,   523,  1011,   518,   519,   520,   521,   522,
     122,   524,   525,   268,   290,   269,   270,   291,   292,   526,
     531,   528,   529,   530,   533,   534,   127,   128,   127,   128,
     535,   536,   537,   538,   540,   539,   541,   240,   542,   544,
     546,   547,   548,   241,   242,   243,   244,   245,   246,   687,
     247,   549,   550,   551,   688,   689,   690,   691,   692,   693,
     694,   695,   696,   697,   698,   699,   700,   701,   702,   552,
     553,   139,   659,   555,   556,   557,   558,   182,   127,   128,
     268,   559,   560,   561,   563,   564,   565,   567,   568,   571,
     189,   570,   572,   573,   678,   574,   575,   576,   577,   578,
     581,   579,   582,   783,   583,   330,   580,   584,   190,   586,
     588,   590,   683,   604,   599,    94,   784,    94,   331,   591,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   592,   785,   596,   332,   597,   598,   328,
     329,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   602,   600,   601,   603,   606,
     607,   605,   608,   609,   815,   612,    32,    94,   618,   619,
     620,   621,   624,   832,   622,   623,   625,   626,   634,   635,
     636,   637,   638,   816,    94,   642,   676,   677,   817,   818,
     639,   641,   643,   645,   666,   724,   728,   732,   736,   646,
     740,   647,   756,   759,   763,   792,   800,   648,   649,   650,
     651,   652,   653,   654,   655,   819,   822,   823,   656,   657,
     658,   660,   661,   662,   673,   674,   675,   824,   825,   826,
     869,   835,   831,   834,   838,   837,   840,   841,   843,   844,
     852,   851,   855,   874,   854,   856,   857,   858,   859,   860,
     861,   887,   888,   873,   881,   880,   876,   883,   884,   885,
     886,   889,   892,   893,   890,   963,   891,   964,   894,   970,
     895,   896,   966,   897,   967,   997,   998,  1002,  1003,   956,
     898,  1004,   957,   958,   959,   960,   961,   984,   990,   991,
     992,   993,   994,  1005,  1013,  1007,  1018,  1008,  1021,  1023,
    1009,  1026,  1046,  1022,  1019,  1025,  1027,  1028,  1047,  1048,
    1051,  1052,  1053,   201,  1054,  1056,   274,   490,   682,   293,
     679,   225,   908,   295,   920,   296,   223,   936,   882,   288,
     248,   803,   306,   310,   938,   926,   202,   921,   532,   203,
     940,   527,   901,   250,   224,   909,   783,   289,   910,   899,
     307,   955,   231,   927,   232,   954,   962,   974,   941,   784,
     275,   251,   933,   294,   221,   238,   917,   233,   902,   903,
     976,   937,   932,   925,   569,   543,   226,   785,   939,  1017,
     227,   249,   905,   239,   904,   928,   907,   204,   977,   929,
     942,   228,   562,   255,   943,   205,   911,   256,   206,   906,
     930,   975,   207,   234,   912,   944,   208,   913,   257,   209,
     219,   914,   969,   566,   968,   915,   953,   554,   916,   922,
     952,   797,   545,   951,  1020,   965,   790,   983,  1024,   585,
     680,   589,  1044,   681,  1055,     0,     0,   587,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   908,
       0,   920,     0,     0,   936,     0,     0,     0,     0,     0,
       0,   938,   926,     0,   921,   974,     0,   940,     0,     0,
       0,     0,   909,     0,     0,   910,     0,     0,   976,     0,
     927,     0,     0,     0,     0,   941,     0,     0,     0,     0,
       0,     0,     0,   917,     0,     0,   977,     0,   937,     0,
     925,     0,     0,     0,     0,   939,     0,     0,     0,   975,
       0,     0,   928,     0,     0,     0,   929,   942,     0,     0,
       0,   943,     0,   911,     0,     0,     0,   930,     0,     0,
       0,   912,   944,     0,   913,     0,     0,     0,   914,     0,
       0,     0,   915,     0,     0,   916,   922
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,    74,
      77,    78,    68,    80,   540,   603,    73,    10,     0,    73,
     546,   842,   842,    72,    73,    74,    75,   842,    77,    78,
       5,    80,     7,   515,     9,   145,    17,    64,   148,   149,
     150,    77,    78,   525,    73,    74,    75,    14,    15,    79,
      80,    18,    79,    80,    21,     7,    73,     7,    75,     7,
      73,     7,    75,    96,    97,    98,    99,    73,   101,   106,
     107,    73,     7,    75,     3,    73,     3,    33,    73,     8,
     168,     8,    73,    11,    62,    13,    73,   117,   118,    73,
      73,     7,     3,     7,    22,     6,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     7,     3,     7,    64,     6,
      66,    67,    79,    80,    70,    71,    72,   144,     3,   146,
     147,     6,   143,    79,    80,    53,    54,    55,    56,    57,
      58,   168,     3,     3,    62,    63,     6,     8,   168,     3,
       7,   168,   106,   107,     8,    73,    74,    75,    76,   142,
       3,    79,    80,   134,    12,     8,    84,     7,   151,   152,
     153,    89,    90,     3,    16,    17,     7,    95,     8,    25,
      26,    27,    28,    29,     7,   168,     3,   105,   999,   999,
     108,     8,    19,    20,   999,     3,     6,   115,   116,     3,
       8,   119,   120,   168,   169,   170,   171,    53,    54,    55,
       4,   168,     8,    59,    60,    61,     3,    63,    27,    28,
      29,     8,   168,   136,   137,   138,   139,    73,    74,    75,
       3,    77,     4,    79,    80,    81,    82,    83,    84,   103,
     104,     3,     3,     8,    63,    91,     8,     8,    94,    95,
     168,     4,   830,    62,    63,    64,   102,     4,   171,    78,
      79,    80,    25,    26,    27,    28,    29,     4,     3,     3,
      79,    80,    91,     8,     8,    94,   109,   110,   111,   112,
     113,   114,     3,    92,    93,     4,     4,     8,     3,     3,
      53,    54,    55,     8,     8,    58,     4,     3,     3,   369,
      63,    64,     8,     8,     3,    85,    86,    87,    88,     8,
      73,    74,    75,   359,   360,     3,    79,    80,     3,    82,
       8,    84,   168,     8,     3,     3,     3,     3,    91,     8,
       8,    94,     8,     3,     8,     3,     8,   407,     8,   102,
       8,     4,     4,   413,    34,    35,    36,    37,     4,   168,
       4,     4,     4,     4,     4,   425,   413,     4,   428,   168,
     428,     3,     8,   425,     4,     4,     3,   168,   425,   439,
       4,   428,     4,   428,   413,     4,     4,     4,   425,   449,
       4,   425,   439,     4,   454,     4,   425,     4,   454,   428,
     454,     4,   449,     4,     4,     4,     4,   454,     4,     4,
     439,   171,   171,   171,   474,   168,   425,     4,     4,   428,
     449,     4,     4,   169,   169,   454,     4,   474,   425,   169,
     439,   169,   425,   449,    27,    28,    29,     4,   454,   425,
       4,     4,   439,   425,   170,   474,   439,   425,   171,   170,
     425,   487,   488,   489,   425,     4,     4,   439,   425,     4,
       4,   425,   425,   169,   970,     4,     4,     4,     4,     4,
      63,     4,     4,    64,    65,    66,    67,    68,    69,     4,
     171,     4,     4,     4,     4,     4,    79,    80,    79,    80,
       4,     4,     4,     4,     4,   169,     4,    90,     4,     4,
       4,     4,     4,    96,    97,    98,    99,   100,   101,    33,
     103,     4,     4,     4,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,     4,
       4,   591,   568,     4,     4,   169,     4,   597,    79,    80,
      64,     4,     4,   171,     4,   171,   171,     4,     4,     4,
     597,   171,     4,   169,   590,     4,   169,   169,     4,     4,
       4,   171,     4,   623,     4,   625,   171,     4,   597,     4,
       4,     4,    23,     5,   168,   168,   623,   168,   625,     7,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,     7,   623,     7,   625,     7,     7,   140,
     141,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,     7,   168,   168,     7,     5,
       5,   168,     5,     5,     4,   168,     7,   168,     5,     5,
       5,     5,   525,     3,     7,     7,     7,     5,   168,   168,
     168,     5,   168,     4,   168,     7,     5,     5,     4,     4,
     168,   168,   168,   168,   135,     7,     7,     7,     7,   168,
       7,   168,     7,     7,     7,     7,     7,   168,   168,   168,
     168,   168,   168,   168,   168,     4,     4,     4,   168,   168,
     168,   168,   168,   168,   168,   168,   168,     4,     4,     4,
     168,     3,     6,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,     3,     6,     4,     4,     4,     4,     4,
       4,   169,   171,     6,     4,     6,     8,     4,     4,     4,
       4,   169,     4,     4,   171,     4,   169,     4,   169,     4,
     169,   169,     6,   169,     3,     8,     8,     4,     8,   169,
     171,     3,   169,   169,   169,   169,   169,   168,   168,   168,
     168,   168,   168,     8,     4,   168,     4,   168,     4,     4,
     168,     5,     4,   169,   171,   168,   168,     7,     4,     4,
       4,   171,   169,   833,   169,   168,   836,   369,   597,   839,
     591,   833,   842,   839,   842,   839,   833,   847,   809,   836,
     850,   677,   839,   853,   847,   842,   833,   842,   413,   833,
     847,   407,   832,   850,   833,   842,   866,   836,   842,   827,
     839,   855,   872,   842,   872,   853,   862,   877,   847,   866,
     836,   850,   845,   839,   833,   872,   842,   872,   833,   835,
     877,   847,   844,   842,   457,   425,   833,   866,   847,   999,
     833,   850,   838,   872,   836,   842,   841,   833,   877,   842,
     847,   833,   449,   850,   847,   833,   842,   850,   833,   839,
     842,   877,   833,   872,   842,   847,   833,   842,   850,   833,
     833,   842,   874,   454,   872,   842,   852,   439,   842,   842,
     850,   642,   428,   848,  1004,   866,   625,   878,  1015,   474,
     592,   480,  1032,   596,  1049,    -1,    -1,   477,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   999,
      -1,   999,    -1,    -1,  1004,    -1,    -1,    -1,    -1,    -1,
      -1,  1004,   999,    -1,   999,  1015,    -1,  1004,    -1,    -1,
      -1,    -1,   999,    -1,    -1,   999,    -1,    -1,  1015,    -1,
     999,    -1,    -1,    -1,    -1,  1004,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   999,    -1,    -1,  1015,    -1,  1004,    -1,
     999,    -1,    -1,    -1,    -1,  1004,    -1,    -1,    -1,  1015,
      -1,    -1,   999,    -1,    -1,    -1,   999,  1004,    -1,    -1,
      -1,  1004,    -1,   999,    -1,    -1,    -1,   999,    -1,    -1,
      -1,   999,  1004,    -1,   999,    -1,    -1,    -1,   999,    -1,
      -1,    -1,   999,    -1,    -1,   999,   999
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
       0,     5,     7,     9,   168,   169,   170,   171,   188,   189,
     190,   195,     7,   204,     7,   210,     7,   230,     7,   323,
       7,   403,     7,   419,     7,   355,     7,   361,     7,   385,
       7,   299,     7,   476,     7,   522,     7,   514,   196,   191,
     205,   211,   231,   324,   404,   420,   356,   362,   386,   300,
     477,   523,   515,   188,   197,   198,   168,   193,   194,    10,
     142,   151,   152,   153,   168,   203,   206,   207,   208,   506,
     508,   510,   520,    11,    13,    22,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    53,    54,    55,    56,    57,
      58,    62,    63,    73,    74,    75,    76,    79,    80,    84,
      89,    90,    95,   105,   108,   115,   116,   119,   120,   203,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     223,   224,   225,   226,   241,   243,   249,   251,   284,   293,
     307,   317,   341,   345,   353,   379,   409,   411,   413,   424,
     426,   428,   451,   463,   464,   472,   474,   512,    14,    15,
      18,    21,   203,   228,   229,   232,   234,   237,   240,   409,
     411,    59,    60,    61,    77,    81,    82,    83,    91,    94,
     102,   203,   214,   215,   216,   217,   218,   219,   224,   225,
     325,   326,   327,   329,   331,   333,   335,   337,   339,   341,
     344,   379,   397,   409,   411,   413,   424,   426,   428,   448,
      78,   203,   337,   339,   379,   405,   406,   407,   409,   411,
      90,    96,    97,    98,    99,   100,   101,   103,   203,   379,
     409,   411,   421,   422,   423,   424,   426,   428,   430,   434,
     436,   438,   440,   442,   444,   446,   353,    33,    64,    66,
      67,    70,    71,    72,   203,   269,   363,   364,   365,   366,
     367,   368,   369,   371,   373,   375,   376,   378,   409,   411,
      65,    68,    69,   203,   269,   367,   373,   387,   388,   389,
     390,   391,   393,   394,   395,   396,   409,   411,   106,   107,
     203,   301,   302,   303,   305,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   140,   141,
     203,   409,   411,   478,   479,   480,   481,   483,   485,   486,
     488,   489,   490,   493,   495,   496,   497,   500,   502,   504,
     143,   524,   525,   526,    12,   516,   517,   518,     6,     3,
       4,     8,     3,   209,   521,   507,   509,   511,     4,     3,
       8,   513,   227,   244,     4,     4,     4,   425,   427,   429,
     242,   250,   252,     4,     4,     4,     4,   222,   318,   354,
     380,     4,     4,     4,   346,   410,   412,   342,   285,   452,
     414,   294,   308,     4,   465,   473,   475,     3,     8,   233,
     235,   238,     4,     3,     8,   330,   332,   334,   398,   328,
     336,     4,   340,   338,   449,     3,     8,   408,     3,     8,
     447,   435,   437,   441,   439,   445,   443,   431,     8,     3,
       8,   370,   270,     4,   374,   372,   377,     4,     8,     3,
     392,     4,     4,     8,     3,   304,   306,     3,     8,     4,
     482,   484,     4,   487,     4,     4,   491,   494,     4,     4,
     498,   501,   503,   505,     3,     8,   527,     3,     8,   519,
       3,     8,   188,   188,   168,     4,     4,     4,     4,     4,
     207,     4,     4,     4,   171,   171,   171,     4,     4,     4,
       4,     4,     4,   169,   169,   169,   169,     4,     4,     4,
       4,   171,   170,   170,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   169,     4,     4,     4,   213,     4,     4,
       4,   171,   229,     4,     4,     4,     4,     4,     4,   169,
       4,     4,     4,   326,     4,   406,     4,     4,     4,     4,
       4,     4,     4,     4,   423,     4,     4,   169,     4,     4,
       4,   171,   365,     4,   171,   171,   389,     4,     4,   302,
     171,     4,     4,   169,     4,   169,   169,     4,     4,   171,
     171,     4,     4,     4,     4,   479,     4,   525,     4,   517,
       4,     7,     7,   188,   188,   188,     7,     7,     7,   168,
     168,   168,     7,     7,     5,   168,     5,     5,     5,     5,
     190,   192,   168,    85,    86,    87,    88,   343,     5,     5,
       5,     5,     7,     7,   192,     7,     5,   199,    16,    17,
     236,    19,    20,   239,   168,   168,   168,     5,   168,   168,
     199,   168,     7,   168,   199,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   188,
     168,   168,   168,    17,   134,   492,   135,   136,   137,   138,
     139,   171,   499,   168,   168,   168,     5,     5,   188,   212,
     524,   516,   228,    23,   245,   246,   247,    33,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,   203,   257,   258,   259,   262,   264,   266,
     268,   269,   271,   272,   273,   274,   275,   276,   277,   278,
     280,   282,   283,   257,     7,   253,   254,   255,     7,   319,
     320,   321,     7,   357,   358,   359,     7,   381,   382,   383,
       7,   347,   348,   349,    96,    97,    98,    99,   101,   286,
     287,   288,   289,   290,   291,   292,     7,   453,   454,     7,
     415,   416,   417,     7,   295,   296,   297,   109,   110,   111,
     112,   113,   114,   309,   310,   311,   312,   313,   314,   315,
     316,   117,   118,   203,   409,   411,   466,   467,   468,   470,
     478,   200,     7,   399,   400,   401,   104,   430,   432,   450,
       7,   528,   529,   253,     8,     8,     8,     8,   248,     3,
       8,   260,   263,   265,   267,     4,     4,     4,     4,     4,
     279,   281,     4,     4,     4,     4,     4,     3,     8,     8,
     256,     6,     3,   322,     6,     3,   360,     6,     3,   384,
       6,     3,   350,     6,     3,     3,     6,   455,     3,     6,
     418,     6,     3,   298,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   469,   471,     3,     8,     8,   168,
     201,   202,   402,     6,     3,   433,     8,   530,     3,     6,
       6,     4,   246,     4,     4,     4,     4,   169,   171,   169,
     171,   169,     4,     4,   169,   169,   169,   169,   171,   258,
     257,   255,   325,   321,   363,   359,   387,   383,   203,   214,
     215,   216,   217,   218,   219,   224,   225,   269,   317,   335,
     337,   339,   341,   351,   352,   379,   409,   411,   424,   426,
     428,   448,   349,   287,    92,    93,   203,   269,   353,   379,
     409,   411,   424,   426,   428,   456,   457,   458,   459,   460,
     462,   454,   421,   417,   301,   297,   169,   169,   169,   169,
     169,   169,   310,     4,     4,   467,     6,     3,   405,   401,
       4,   144,   146,   147,   203,   269,   409,   411,   531,   532,
     533,   534,   536,   529,   168,    34,    35,    36,    37,   261,
     168,   168,   168,   168,   168,     8,     8,     8,     8,     3,
       8,   461,     4,     8,     3,     8,     8,   168,   168,   168,
       8,   199,   537,     4,   535,     3,     8,   352,     4,   171,
     458,     4,   169,     4,   532,   168,     5,   168,     7,   538,
     539,   540,     3,     6,   145,   148,   149,   150,   541,   542,
     543,   545,   546,   547,   539,   544,     4,     4,     4,     3,
       8,     4,   171,   169,   169,   542,   168
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   172,   174,   173,   175,   173,   176,   173,   177,   173,
     178,   173,   179,   173,   180,   173,   181,   173,   182,   173,
     183,   173,   184,   173,   185,   173,   186,   173,   187,   173,
     188,   188,   188,   188,   188,   188,   188,   189,   191,   190,
     192,   193,   193,   194,   194,   196,   195,   197,   197,   198,
     198,   200,   199,   201,   201,   202,   202,   203,   205,   204,
     206,   206,   207,   207,   207,   207,   207,   207,   209,   208,
     211,   210,   212,   212,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   214,   215,   216,   217,   218,   219,   220,   222,   221,
     223,   224,   225,   227,   226,   228,   228,   229,   229,   229,
     229,   229,   229,   229,   231,   230,   233,   232,   235,   234,
     236,   236,   238,   237,   239,   239,   240,   242,   241,   244,
     243,   245,   245,   246,   248,   247,   250,   249,   252,   251,
     253,   253,   254,   254,   256,   255,   257,   257,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   260,   259,   261,   261,
     261,   261,   263,   262,   265,   264,   267,   266,   268,   270,
     269,   271,   272,   273,   274,   275,   276,   277,   279,   278,
     281,   280,   282,   283,   285,   284,   286,   286,   287,   287,
     287,   287,   287,   288,   289,   290,   291,   292,   294,   293,
     295,   295,   296,   296,   298,   297,   300,   299,   301,   301,
     301,   302,   302,   304,   303,   306,   305,   308,   307,   309,
     309,   310,   310,   310,   310,   310,   310,   311,   312,   313,
     314,   315,   316,   318,   317,   319,   319,   320,   320,   322,
     321,   324,   323,   325,   325,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   328,   327,   330,   329,   332,   331,   334,   333,
     336,   335,   338,   337,   340,   339,   342,   341,   343,   343,
     343,   343,   344,   346,   345,   347,   347,   348,   348,   350,
     349,   351,   351,   352,   352,   352,   352,   352,   352,   352,
     352,   352,   352,   352,   352,   352,   352,   352,   352,   352,
     352,   352,   352,   352,   352,   354,   353,   356,   355,   357,
     357,   358,   358,   360,   359,   362,   361,   363,   363,   364,
     364,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   366,   367,   368,   370,   369,   372,   371,   374,   373,
     375,   377,   376,   378,   380,   379,   381,   381,   382,   382,
     384,   383,   386,   385,   387,   387,   388,   388,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   390,   392,   391,
     393,   394,   395,   396,   398,   397,   399,   399,   400,   400,
     402,   401,   404,   403,   405,   405,   406,   406,   406,   406,
     406,   406,   406,   408,   407,   410,   409,   412,   411,   414,
     413,   415,   415,   416,   416,   418,   417,   420,   419,   421,
     421,   422,   422,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   425,   424,
     427,   426,   429,   428,   431,   430,   433,   432,   435,   434,
     437,   436,   439,   438,   441,   440,   443,   442,   445,   444,
     447,   446,   449,   448,   450,   450,   452,   451,   453,   453,
     455,   454,   456,   456,   457,   457,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   459,   461,   460,
     462,   463,   465,   464,   466,   466,   467,   467,   467,   467,
     467,   469,   468,   471,   470,   473,   472,   475,   474,   477,
     476,   478,   478,   479,   479,   479,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   479,   479,   479,   479,
     479,   480,   482,   481,   484,   483,   485,   487,   486,   488,
     489,   491,   490,   492,   492,   494,   493,   495,   496,   498,
     497,   499,   499,   499,   499,   499,   501,   500,   503,   502,
     505,   504,   507,   506,   509,   508,   511,   510,   513,   512,
     515,   514,   516,   516,   517,   519,   518,   521,   520,   523,
     522,   524,   524,   525,   527,   526,   528,   528,   530,   529,
     531,   531,   532,   532,   532,   532,   532,   532,   532,   533,
     535,   534,   537,   536,   538,   538,   540,   539,   541,   541,
     542,   542,   542,   542,   544,   543,   545,   546,   547
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     4,     1,     1,     3,     0,     6,     0,
       6,     1,     3,     1,     0,     4,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       0,     4,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     0,     6,     0,
       4,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"shared-networks\"", "\"pools\"",
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
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
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "interfaces_config", "$@22",
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
  "$@98", "control_socket_name", "$@99", "dhcp_queue_control", "$@100",
  "dhcp_ddns", "$@101", "sub_dhcp_ddns", "$@102", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@103",
  "server_ip", "$@104", "server_port", "sender_ip", "$@105", "sender_port",
  "max_queue_size", "ncr_protocol", "$@106", "ncr_protocol_value",
  "ncr_format", "$@107", "override_no_update", "override_client_update",
  "replace_client_name", "$@108", "replace_client_name_value",
  "generated_prefix", "$@109", "hostname_char_set", "$@110",
  "hostname_char_replacement", "$@111", "dhcp6_json_object", "$@112",
  "dhcpddns_json_object", "$@113", "control_agent_json_object", "$@114",
  "config_control", "$@115", "sub_config_control", "$@116",
  "config_control_params", "config_control_param", "config_databases",
  "$@117", "logging_object", "$@118", "sub_logging", "$@119",
  "logging_params", "logging_param", "loggers", "$@120", "loggers_entries",
  "logger_entry", "$@121", "logger_params", "logger_param", "debuglevel",
  "severity", "$@122", "output_options_list", "$@123",
  "output_options_list_content", "output_entry", "$@124",
  "output_params_list", "output_params", "output", "$@125", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   257,   257,   257,   258,   258,   259,   259,   260,   260,
     261,   261,   262,   262,   263,   263,   264,   264,   265,   265,
     266,   266,   267,   267,   268,   268,   269,   269,   270,   270,
     278,   279,   280,   281,   282,   283,   284,   287,   292,   292,
     303,   306,   307,   310,   314,   321,   321,   328,   329,   332,
     336,   343,   343,   350,   351,   354,   358,   369,   379,   379,
     395,   396,   400,   401,   402,   403,   404,   405,   408,   408,
     423,   423,   432,   433,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   477,   482,   487,   492,   497,   502,   507,   512,   512,
     520,   525,   530,   536,   536,   547,   548,   551,   552,   553,
     554,   555,   556,   557,   560,   560,   569,   569,   579,   579,
     586,   587,   590,   590,   597,   599,   603,   609,   609,   621,
     621,   631,   632,   634,   636,   636,   654,   654,   666,   666,
     676,   677,   680,   681,   684,   684,   694,   695,   698,   699,
     700,   701,   702,   703,   704,   705,   706,   707,   708,   709,
     710,   711,   712,   713,   714,   715,   718,   718,   725,   726,
     727,   728,   731,   731,   739,   739,   747,   747,   755,   760,
     760,   768,   773,   778,   783,   788,   793,   798,   803,   803,
     811,   811,   819,   824,   829,   829,   839,   840,   843,   844,
     845,   846,   847,   850,   855,   860,   865,   870,   875,   875,
     885,   886,   889,   890,   893,   893,   903,   903,   913,   914,
     915,   918,   919,   922,   922,   930,   930,   938,   938,   949,
     950,   953,   954,   955,   956,   957,   958,   961,   966,   971,
     976,   981,   986,   994,   994,  1007,  1008,  1011,  1012,  1019,
    1019,  1045,  1045,  1056,  1057,  1061,  1062,  1063,  1064,  1065,
    1066,  1067,  1068,  1069,  1070,  1071,  1072,  1073,  1074,  1075,
    1076,  1077,  1078,  1079,  1080,  1081,  1082,  1083,  1084,  1085,
    1086,  1087,  1090,  1090,  1098,  1098,  1106,  1106,  1114,  1114,
    1122,  1122,  1130,  1130,  1138,  1138,  1148,  1148,  1155,  1156,
    1157,  1158,  1161,  1168,  1168,  1179,  1180,  1184,  1185,  1188,
    1188,  1196,  1197,  1200,  1201,  1202,  1203,  1204,  1205,  1206,
    1207,  1208,  1209,  1210,  1211,  1212,  1213,  1214,  1215,  1216,
    1217,  1218,  1219,  1220,  1221,  1228,  1228,  1241,  1241,  1250,
    1251,  1254,  1255,  1260,  1260,  1275,  1275,  1289,  1290,  1293,
    1294,  1297,  1298,  1299,  1300,  1301,  1302,  1303,  1304,  1305,
    1306,  1309,  1311,  1316,  1318,  1318,  1326,  1326,  1334,  1334,
    1342,  1344,  1344,  1352,  1361,  1361,  1373,  1374,  1379,  1380,
    1385,  1385,  1397,  1397,  1409,  1410,  1415,  1416,  1421,  1422,
    1423,  1424,  1425,  1426,  1427,  1428,  1429,  1432,  1434,  1434,
    1442,  1444,  1446,  1451,  1459,  1459,  1471,  1472,  1475,  1476,
    1479,  1479,  1489,  1489,  1499,  1500,  1503,  1504,  1505,  1506,
    1507,  1508,  1509,  1512,  1512,  1520,  1520,  1545,  1545,  1575,
    1575,  1585,  1586,  1589,  1590,  1593,  1593,  1602,  1602,  1611,
    1612,  1615,  1616,  1620,  1621,  1622,  1623,  1624,  1625,  1626,
    1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,  1637,  1637,
    1645,  1645,  1653,  1653,  1661,  1661,  1669,  1669,  1679,  1679,
    1687,  1687,  1695,  1695,  1703,  1703,  1711,  1711,  1719,  1719,
    1727,  1727,  1740,  1740,  1750,  1751,  1757,  1757,  1767,  1768,
    1771,  1771,  1781,  1782,  1785,  1786,  1789,  1790,  1791,  1792,
    1793,  1794,  1795,  1796,  1797,  1798,  1799,  1802,  1804,  1804,
    1812,  1821,  1828,  1828,  1838,  1839,  1842,  1843,  1844,  1845,
    1846,  1849,  1849,  1857,  1857,  1868,  1868,  1906,  1906,  1918,
    1918,  1928,  1929,  1932,  1933,  1934,  1935,  1936,  1937,  1938,
    1939,  1940,  1941,  1942,  1943,  1944,  1945,  1946,  1947,  1948,
    1949,  1952,  1957,  1957,  1965,  1965,  1973,  1978,  1978,  1986,
    1991,  1996,  1996,  2004,  2005,  2008,  2008,  2016,  2021,  2026,
    2026,  2034,  2037,  2040,  2043,  2046,  2052,  2052,  2060,  2060,
    2068,  2068,  2079,  2079,  2086,  2086,  2093,  2093,  2100,  2100,
    2111,  2111,  2121,  2122,  2126,  2129,  2129,  2144,  2144,  2154,
    2154,  2165,  2166,  2170,  2174,  2174,  2186,  2187,  2191,  2191,
    2199,  2200,  2203,  2204,  2205,  2206,  2207,  2208,  2209,  2212,
    2217,  2217,  2225,  2225,  2235,  2236,  2239,  2239,  2247,  2248,
    2251,  2252,  2253,  2254,  2257,  2257,  2265,  2270,  2275
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
#line 4937 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2280 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
