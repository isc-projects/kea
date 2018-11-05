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
      case 187: // value
      case 191: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 338: // hr_mode
      case 492: // ncr_protocol_value
      case 500: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 170: // "boolean"
        value.move< bool > (that.value);
        break;

      case 169: // "floating point"
        value.move< double > (that.value);
        break;

      case 168: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 167: // "constant string"
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
      case 187: // value
      case 191: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 338: // hr_mode
      case 492: // ncr_protocol_value
      case 500: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 170: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 169: // "floating point"
        value.copy< double > (that.value);
        break;

      case 168: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 167: // "constant string"
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
            case 167: // "constant string"

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 168: // "integer"

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 169: // "floating point"

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 170: // "boolean"

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 187: // value

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 191: // map_value

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 231: // socket_type

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 234: // outbound_interface_value

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 256: // db_type

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 338: // hr_mode

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 492: // ncr_protocol_value

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 500: // replace_client_name_value

#line 247 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 187: // value
      case 191: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 338: // hr_mode
      case 492: // ncr_protocol_value
      case 500: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 170: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 169: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 168: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 167: // "constant string"
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
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 283 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 331 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 335 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 353 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 357 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 368 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 383 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 407 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 612 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 694 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 699 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 867 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 997 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1062 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2295 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2567 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-control", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.QUEUE_CONTROL);
}
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.require("queue-type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("capacity", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr qtype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qtype);
    ctx.leave();
}
#line 2998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", i);
}
#line 3007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3029 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3058 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3156 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1971 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1972 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 1993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2000 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2012 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3254 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2015 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2018 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2024 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3289 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2034 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2058 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2096 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2136 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 623:
#line 2161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2173 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2177 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3547 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2201 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3557 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 640:
#line 2207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 641:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 644:
#line 2221 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3587 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3595 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 653:
#line 2241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 654:
#line 2247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 655:
#line 2252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 656:
#line 2257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3640 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3644 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -813;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     439,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,    45,    29,    60,    64,    66,
      70,    86,    88,    90,    99,   108,   110,   123,   142,   152,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,    29,     3,
      42,    57,    51,   154,   196,   239,   127,   412,   337,   -60,
     420,    32,    34,  -813,   180,   192,   199,   203,   214,  -813,
    -813,  -813,  -813,  -813,   215,  -813,    96,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,   224,   242,  -813,
    -813,  -813,  -813,  -813,  -813,   249,   276,   277,   287,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,   295,  -813,  -813,  -813,  -813,   113,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,   306,  -813,   136,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,   315,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,   138,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,   144,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
     318,   324,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,   321,  -813,  -813,   335,  -813,  -813,
    -813,   336,  -813,  -813,   333,   341,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,   343,
     349,  -813,  -813,  -813,  -813,   347,   342,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,   157,
    -813,  -813,  -813,   354,  -813,  -813,   358,  -813,   361,   364,
    -813,  -813,   365,   367,   369,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,   159,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,   163,  -813,  -813,  -813,  -813,   170,  -813,  -813,  -813,
      29,    29,  -813,   210,   370,   374,   376,   378,   380,  -813,
      42,  -813,    34,   382,   383,   384,   221,   225,   390,   394,
     403,   404,   405,   411,   248,   256,   258,   259,   415,   425,
     426,   427,   429,   431,   432,   433,   441,   443,   446,   447,
     275,   449,   465,   466,    57,  -813,   467,   468,   470,   309,
      51,  -813,   472,   480,   481,   482,   485,   486,   323,   488,
     489,   490,   493,   154,  -813,   494,   196,  -813,   496,   497,
     498,   499,   501,   502,   503,   505,  -813,   239,  -813,   506,
     507,   344,   509,   510,   512,   348,  -813,   412,   513,   353,
     355,  -813,   337,   515,   520,    74,  -813,   356,   523,   524,
     362,   525,   363,   366,   528,   531,   387,   388,   391,   549,
     558,   559,   560,   420,  -813,   561,    32,  -813,   562,    34,
    -813,  -813,  -813,   563,   564,   565,    29,    29,    29,  -813,
     207,   566,   567,   568,  -813,  -813,   402,   409,   410,   571,
     573,   576,  -813,  -813,  -813,  -813,   416,   577,   580,   581,
     583,   599,   440,   603,   604,   605,   606,   607,  -813,   608,
     609,   610,  -813,   613,   168,    31,  -813,  -813,   445,   452,
     453,   616,   455,   456,  -813,   268,   613,   457,   618,  -813,
     459,  -813,   613,   460,   461,   462,   463,   464,   469,   471,
    -813,   473,   474,  -813,   475,   476,   477,  -813,  -813,   478,
    -813,  -813,  -813,   479,    29,  -813,  -813,   483,   484,  -813,
     487,  -813,  -813,    20,   436,  -813,  -813,  -813,    19,   491,
     492,   495,  -813,   627,  -813,   628,  -813,    29,    57,    32,
    -813,  -813,  -813,  -813,    34,    51,   590,  -813,  -813,  -813,
     417,   417,   630,  -813,   632,   640,   641,   642,  -813,  -813,
    -813,   128,   645,   646,   648,   198,   -22,   -27,   420,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
     649,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
     137,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,   650,   630,  -813,   232,   235,   251,
     252,  -813,   253,  -813,  -813,  -813,  -813,  -813,  -813,   631,
     656,   657,   659,   660,  -813,  -813,   661,   662,   663,   664,
     665,  -813,   254,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,   260,  -813,   666,   667,  -813,  -813,   668,   670,  -813,
    -813,   669,   673,  -813,  -813,   671,   675,  -813,  -813,   674,
     676,  -813,  -813,  -813,  -813,  -813,  -813,    41,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,    56,  -813,  -813,   677,   678,
    -813,  -813,   679,   681,  -813,   682,   683,   684,   685,   686,
     687,   261,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,   270,  -813,  -813,  -813,  -813,   688,
    -813,  -813,  -813,   274,  -813,  -813,  -813,   284,   504,  -813,
     689,   690,  -813,  -813,  -813,  -813,   626,  -813,   102,  -813,
     691,  -813,  -813,  -813,  -813,   692,   590,  -813,   694,   695,
     696,   697,   514,   532,   526,   533,   536,   701,   702,   539,
     540,   541,   542,   543,   417,  -813,  -813,   417,  -813,   630,
     154,  -813,   632,   412,  -813,   640,   337,  -813,   641,   222,
    -813,   642,   128,  -813,    75,   645,  -813,   239,  -813,   646,
     -60,  -813,   648,   544,   546,   547,   548,   550,   551,   198,
    -813,   707,   713,   -22,  -813,   716,   553,   -27,  -813,  -813,
    -813,   717,   719,   196,  -813,   649,   720,  -813,    59,   650,
    -813,  -813,   569,  -813,   406,   570,   572,   574,  -813,  -813,
    -813,  -813,  -813,   575,   578,  -813,  -813,  -813,  -813,  -813,
    -813,   285,  -813,   286,  -813,   718,  -813,   721,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
     308,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,   723,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,   722,   725,  -813,  -813,  -813,  -813,  -813,   724,
    -813,   310,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
     579,   582,  -813,   584,  -813,  -813,  -813,   585,   314,  -813,
     613,  -813,   727,  -813,  -813,  -813,  -813,  -813,   320,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,   222,
    -813,   729,   555,  -813,    75,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,   730,   587,   731,    59,  -813,  -813,   586,
    -813,  -813,   733,  -813,   589,  -813,  -813,   736,  -813,  -813,
     125,  -813,   -24,   736,  -813,  -813,   740,   743,   744,   334,
    -813,  -813,  -813,  -813,  -813,  -813,   746,   588,   591,   593,
     -24,  -813,   595,  -813,  -813,  -813,  -813,  -813
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
     227,    23,   542,    25,   617,    27,   607,    29,    47,    41,
       0,     0,     0,     0,     0,   442,     0,   350,   387,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     615,   597,   599,   601,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   603,   605,   114,   140,     0,     0,   461,
     463,   465,   138,   147,   149,     0,     0,     0,     0,   110,
     254,   338,   377,   310,   428,   430,   205,   489,   432,   219,
     238,     0,   515,   528,   540,   105,     0,    72,    74,    75,
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
     229,   232,   233,     0,   566,   568,     0,   571,     0,     0,
     575,   579,     0,     0,     0,   584,   591,   593,   595,   564,
     562,   563,     0,   544,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     622,     0,   619,   621,   613,   612,     0,   609,   611,    46,
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
       0,     0,     0,     0,   543,     0,     0,   618,     0,     0,
     608,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,   112,   113,     0,     0,     0,     0,
       0,     0,   106,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   514,     0,
       0,     0,    73,     0,     0,     0,   137,   117,     0,     0,
       0,     0,     0,     0,   309,     0,     0,     0,     0,   265,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
     445,     0,     0,   365,     0,     0,     0,   376,   353,     0,
     405,   406,   390,     0,     0,   230,   565,     0,     0,   570,
       0,   573,   574,     0,     0,   581,   582,   583,     0,     0,
       0,     0,   545,     0,   620,     0,   610,     0,     0,     0,
     598,   600,   602,   604,     0,     0,     0,   462,   464,   466,
       0,     0,   151,   111,   256,   342,   379,   312,    40,   429,
     431,     0,     0,   434,   221,     0,     0,     0,     0,    51,
     128,   131,   132,   130,   135,   136,   134,   292,   294,   296,
     409,   290,   298,   305,   306,   307,   308,   304,   302,   300,
       0,   427,   484,   472,   474,   478,   476,   482,   480,   468,
     368,   191,   372,   370,   375,   402,   235,   237,   567,   569,
     572,   577,   578,   576,   580,   586,   587,   588,   589,   590,
     585,   592,   594,   596,     0,   151,    44,     0,     0,     0,
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
     526,   523,   521,   522,     0,   517,   519,   520,   537,     0,
     536,   534,   535,     0,   530,   532,   533,     0,    53,   413,
       0,   410,   411,   469,   487,   488,     0,   626,     0,   624,
       0,    69,   616,   606,   115,     0,     0,   141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   139,   148,     0,   150,     0,
       0,   255,     0,   350,   339,     0,   387,   378,     0,     0,
     311,     0,     0,   206,   495,     0,   490,   442,   433,     0,
       0,   220,     0,     0,     0,     0,     0,     0,     0,     0,
     239,     0,     0,     0,   516,     0,     0,     0,   529,   541,
      55,     0,    54,     0,   408,     0,     0,   486,     0,     0,
     623,   614,     0,   143,     0,     0,     0,     0,   189,   192,
     193,   194,   195,     0,     0,   203,   204,   196,   197,   198,
     158,     0,   154,     0,   259,     0,   345,     0,   382,   337,
     334,   323,   324,   326,   320,   321,   322,   332,   333,   331,
       0,   318,   325,   335,   336,   327,   328,   329,   330,   315,
     208,   511,     0,   509,   510,   502,   503,   507,   508,   504,
     505,   506,     0,   496,   497,   499,   500,   501,   492,     0,
     437,     0,   224,   248,   249,   250,   251,   252,   253,   241,
       0,     0,   518,     0,   539,   531,    52,     0,     0,   412,
       0,   640,     0,   638,   636,   630,   634,   635,     0,   628,
     632,   633,   631,   625,   146,   179,   180,   181,   182,   178,
     184,   186,   188,   200,   202,   156,   261,   347,   384,     0,
     317,     0,     0,   494,     0,   439,   226,   525,   527,   538,
      56,   414,   470,     0,     0,     0,     0,   627,   319,     0,
     513,   498,     0,   637,     0,   629,   512,     0,   639,   644,
       0,   642,     0,     0,   641,   652,     0,     0,     0,     0,
     646,   648,   649,   650,   651,   643,     0,     0,     0,     0,
       0,   645,     0,   654,   655,   656,   647,   653
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,   -55,  -813,   264,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -497,  -813,  -813,
    -813,   -70,  -813,  -813,  -813,   407,  -813,  -813,  -813,  -813,
     162,   381,   -57,   -54,   -34,  -813,  -813,  -813,  -813,   -32,
    -813,  -813,   183,   372,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
     -20,  -813,  -813,  -813,  -813,  -813,  -813,   135,  -813,   -39,
    -813,  -576,   -23,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,   -45,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,   -40,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,   -48,  -813,  -813,  -813,   -44,   373,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,   -49,  -813,  -813,  -813,  -813,  -813,
    -813,  -812,  -813,  -813,  -813,   -18,  -813,  -813,  -813,   -21,
     399,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -809,
    -813,   -56,  -813,   -50,  -813,  -808,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,   -16,  -813,  -813,  -179,   -65,  -813,  -813,
    -813,  -813,  -813,   -11,  -813,  -813,  -813,    -5,  -813,   392,
    -813,   -72,  -813,  -813,  -813,  -813,  -813,   -66,  -813,  -813,
    -813,  -813,  -813,     1,  -813,  -813,  -813,    -6,  -813,  -813,
    -813,    -2,  -813,   395,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,   -37,  -813,  -813,  -813,   -31,
     423,  -813,  -813,   -52,  -813,   -17,  -813,   -59,  -813,  -813,
    -813,   -13,  -813,  -813,  -813,    -4,  -813,   414,     5,  -813,
      21,  -813,    25,  -813,   217,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -799,  -813,  -813,  -813,  -813,  -813,     8,  -813,
    -813,  -813,  -150,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,    -1,  -813,  -813,  -813,  -813,  -813,  -813,  -813,   -10,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,   250,   396,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,  -813,
    -813,  -813,  -813,  -813,  -813,  -813,  -813,  -345,   397,  -813,
    -813,  -813,  -813,  -813,  -813,   288,   413,  -813,  -813,  -813,
      -9,  -813,  -813,  -153,  -813,  -813,  -813,  -813,  -813,  -813,
    -162,  -813,  -813,  -177,  -813,  -813,  -813,  -813,  -813
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     599,    87,    88,    41,    68,    84,    85,   610,   788,   871,
     872,   345,    43,    70,    96,    97,    98,   354,    45,    71,
     136,   137,   138,   139,   140,   141,   142,   378,   143,   144,
     145,   364,   174,   175,    47,    72,   176,   396,   177,   397,
     613,   178,   398,   616,   179,   146,   371,   147,   365,   672,
     673,   674,   805,   148,   372,   149,   373,   713,   714,   715,
     827,   692,   693,   694,   808,   989,   695,   809,   696,   810,
     697,   811,   698,   699,   430,   700,   701,   702,   703,   704,
     705,   706,   707,   817,   708,   818,   709,   710,   150,   385,
     737,   738,   739,   740,   741,   742,   743,   151,   388,   752,
     753,   754,   850,    61,    79,   299,   300,   301,   443,   302,
     444,   152,   389,   761,   762,   763,   764,   765,   766,   767,
     768,   153,   379,   717,   718,   719,   830,    49,    73,   198,
     199,   200,   406,   201,   402,   202,   403,   203,   404,   204,
     407,   205,   411,   206,   410,   207,   409,   627,   208,   154,
     382,   729,   730,   731,   839,   920,   921,   155,   380,    55,
      76,   721,   722,   723,   833,    57,    77,   264,   265,   266,
     267,   268,   269,   270,   429,   271,   433,   272,   432,   273,
     274,   434,   275,   156,   381,   725,   726,   727,   836,    59,
      78,   285,   286,   287,   288,   289,   438,   290,   291,   292,
     293,   210,   405,   790,   791,   792,   873,    51,    74,   223,
     224,   225,   415,   157,   383,   158,   384,   159,   387,   748,
     749,   750,   847,    53,    75,   240,   241,   242,   160,   368,
     161,   369,   162,   370,   246,   425,   795,   876,   247,   419,
     248,   420,   249,   422,   250,   421,   251,   424,   252,   423,
     253,   418,   217,   412,   796,   163,   386,   745,   746,   844,
     942,   943,   944,   945,   946,  1001,   947,   164,   165,   391,
     774,   775,   776,   861,   777,   862,   166,   392,   783,   784,
     785,   865,   786,   167,   393,    63,    80,   322,   323,   324,
     325,   448,   326,   449,   327,   328,   451,   329,   330,   331,
     454,   653,   332,   455,   333,   334,   335,   336,   459,   660,
     337,   460,   338,   461,   339,   462,    99,   356,   100,   357,
     101,   358,   168,   362,   363,    67,    82,   346,   347,   348,
     468,   102,   355,    65,    81,   341,   342,   343,   465,   798,
     799,   878,   978,   979,   980,   981,  1015,   982,  1013,  1030,
    1031,  1032,  1039,  1040,  1041,  1046,  1042,  1043,  1044
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   135,   173,   193,   219,   236,   283,   262,   281,   298,
     319,   254,   284,    83,   213,   711,   194,   480,   220,   195,
     180,   211,   226,   238,   221,   276,   294,   915,   320,   628,
     916,   919,   263,   282,    31,   632,    32,   651,    33,   196,
     928,   197,   296,   297,   842,    30,   344,   843,   124,   125,
     614,   615,    89,   124,   125,   181,   212,   227,   239,   845,
     277,   295,   846,   321,   103,   169,   170,    42,   104,   171,
     105,    44,   172,    46,   209,   222,   237,    48,   214,   106,
     243,   107,   108,   109,   110,   111,   112,   113,   114,   778,
     779,   769,   770,    50,   215,    52,   244,    54,   216,   360,
     245,   109,   110,   111,   361,   879,    56,    94,   880,   115,
     116,   117,   118,   119,   120,    58,   394,    60,   121,   122,
    1035,   395,   256,  1036,  1037,  1038,   124,   125,  1033,   123,
      62,  1034,   124,   125,   124,   125,   121,   122,   256,   400,
      94,   413,   126,   127,   401,    94,   414,   416,   128,    64,
     124,   125,   417,   652,   655,   656,   657,   658,   129,    66,
     445,   130,   463,   931,   932,   446,   466,   464,   131,   132,
      86,   467,   133,   469,   340,   134,   296,   297,   470,   108,
     109,   110,   111,    90,   611,   612,   349,   915,   121,   659,
     916,   919,    91,    92,    93,   350,    34,    35,    36,    37,
     928,    94,   971,   351,   972,   973,   115,   116,   117,    94,
     469,   352,   182,   183,   184,   583,   122,   353,    94,   359,
     732,   733,   734,   735,    94,   736,    94,   185,   366,   124,
     125,   186,   187,   188,   189,   394,   235,   793,   466,   669,
     801,   190,    94,   802,   191,   128,   367,   108,   109,   110,
     111,   901,   192,   374,   469,   400,   806,   824,   122,   803,
     804,   807,   825,   824,   859,   109,   110,   111,   826,   860,
     218,   124,   125,   863,   115,   116,   117,   867,   864,   120,
     375,   376,   868,   190,   122,   256,   191,   463,   824,   413,
      95,   377,   869,   995,   996,   471,   472,   124,   125,   390,
     187,   122,   189,   755,   756,   757,   758,   759,   760,   190,
     399,   999,   191,   445,   124,   125,  1000,   416,  1006,   408,
     192,    94,  1011,  1016,   135,   228,   426,   427,  1017,   428,
     173,   229,   230,   231,   232,   233,   234,  1050,   235,   431,
     435,   436,  1051,   193,   437,   442,   219,   439,   180,   623,
     624,   625,   626,   440,   213,   441,   194,   236,   447,   195,
     220,   211,   450,    94,   226,   452,   221,   262,   453,   456,
     283,   457,   281,   458,   474,   238,   284,   473,   475,   196,
     476,   197,   477,   181,   478,   276,   481,   482,   483,    94,
     294,   484,   263,   319,   486,   485,   212,   282,   487,   227,
     256,   278,   257,   258,   279,   280,    94,   488,   489,   490,
     239,   320,   124,   125,   209,   491,   492,   222,   214,   496,
     277,   580,   581,   582,   493,   295,   494,   495,   237,   497,
     498,   499,   243,   500,   215,   501,   502,   503,   216,   985,
     986,   987,   988,   508,   255,   504,   321,   505,   244,   675,
     506,   507,   245,   509,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   510,
     511,   513,   514,  1012,   515,   256,   518,   257,   258,   516,
     256,   259,   260,   261,   519,   520,   521,   124,   125,   522,
     523,   524,   525,   526,   527,   124,   125,   528,   530,   647,
     532,   533,   534,   535,    94,   536,   537,   538,   135,   539,
     541,   542,   543,   544,   545,   173,   546,   549,   547,   553,
     691,   691,   666,   550,   554,   551,   556,   557,   558,   560,
     559,   561,   563,   180,   562,   564,   771,   780,   319,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   568,   772,   781,   320,   565,   566,   317,
     318,   567,   569,   570,   571,   573,   575,   577,   181,   587,
     654,   578,   579,   584,   585,   586,   588,   589,   590,    94,
     591,   592,   594,   593,    94,   595,   596,    94,   597,   773,
     782,   321,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    32,   600,   601,   602,
     603,   604,   617,   671,   605,   606,   607,   608,   609,   618,
     619,   620,   621,   622,   629,   630,   631,   633,   634,   635,
     636,   637,   664,   665,   877,   812,   638,   712,   639,   716,
     640,   641,   642,   643,   644,   645,   646,   720,   724,   728,
     648,   649,   744,   747,   650,   751,   789,   797,   661,   662,
     813,   814,   663,   815,   816,   819,   820,   821,   822,   823,
     829,   870,   828,   832,   831,   834,   835,   837,   838,   841,
     840,   849,   888,   848,   852,   851,   853,   854,   855,   856,
     857,   858,   866,   875,   890,   874,   882,   881,   884,   885,
     886,   887,   889,   891,   892,   893,   894,   895,   896,   897,
     898,   960,   953,   899,   954,   955,   956,   961,   957,   958,
     963,   964,   967,   966,   970,  1020,   997,  1002,  1004,   998,
    1003,  1014,  1005,  1019,  1022,  1024,   984,   990,  1027,   991,
     667,   992,   993,  1029,  1047,   994,  1007,  1048,  1049,  1008,
    1052,  1009,  1010,  1026,   691,  1023,  1028,   691,  1053,  1054,
     193,  1055,  1057,   262,   283,   598,   281,   479,   670,   909,
     284,   213,   517,   194,   933,   512,   195,   236,   211,   935,
     298,   276,   910,   917,   294,   911,   883,   923,   263,   918,
     902,   282,   937,   771,   914,   238,   196,   780,   197,   934,
     800,   900,   930,   219,   952,   912,   951,   913,   974,   903,
     959,   772,   529,   212,   904,   781,   277,   220,   555,   295,
    1018,   226,   924,   221,   906,   929,   976,   938,   905,   548,
     239,   209,   908,   975,   907,   214,   950,   552,   969,   531,
     922,   540,   968,   949,   925,   936,   773,   794,   237,   939,
     782,   215,   243,   948,  1021,   216,   227,   965,   787,   572,
     926,   977,   962,  1025,   927,   940,   576,   668,   244,   941,
     983,  1045,   245,  1056,   222,     0,     0,     0,     0,   574,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   909,
       0,     0,     0,     0,   933,     0,     0,     0,     0,   935,
       0,     0,   910,   917,     0,   911,   974,   923,     0,   918,
       0,     0,   937,     0,   914,     0,     0,     0,     0,   934,
       0,     0,     0,     0,   976,   912,     0,   913,     0,     0,
       0,   975,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   924,     0,     0,     0,     0,   938,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   977,
     922,     0,     0,     0,   925,   936,     0,     0,     0,   939,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     926,     0,     0,     0,   927,   940,     0,     0,     0,   941
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    78,    68,    73,   591,    73,   362,    74,    73,
      72,    73,    74,    75,    74,    77,    78,   839,    80,   526,
     839,   839,    77,    78,     5,   532,     7,    17,     9,    73,
     839,    73,   102,   103,     3,     0,    12,     6,    75,    76,
      19,    20,    10,    75,    76,    72,    73,    74,    75,     3,
      77,    78,     6,    80,     7,    14,    15,     7,    11,    18,
      13,     7,    21,     7,    73,    74,    75,     7,    73,    22,
      75,    24,    25,    26,    27,    28,    29,    30,    31,   116,
     117,   113,   114,     7,    73,     7,    75,     7,    73,     3,
      75,    26,    27,    28,     8,     3,     7,   167,     6,    52,
      53,    54,    55,    56,    57,     7,     3,     7,    61,    62,
     144,     8,    63,   147,   148,   149,    75,    76,     3,    72,
       7,     6,    75,    76,    75,    76,    61,    62,    63,     3,
     167,     3,    85,    86,     8,   167,     8,     3,    91,     7,
      75,    76,     8,   133,   135,   136,   137,   138,   101,     7,
       3,   104,     3,    88,    89,     8,     3,     8,   111,   112,
     167,     8,   115,     3,   142,   118,   102,   103,     8,    25,
      26,    27,    28,   141,    16,    17,     6,   999,    61,   170,
     999,   999,   150,   151,   152,     3,   167,   168,   169,   170,
     999,   167,   143,     4,   145,   146,    52,    53,    54,   167,
       3,     8,    58,    59,    60,     8,    62,     3,   167,     4,
      92,    93,    94,    95,   167,    97,   167,    73,     4,    75,
      76,    77,    78,    79,    80,     3,    99,   100,     3,   584,
       8,    87,   167,     8,    90,    91,     4,    25,    26,    27,
      28,   827,    98,     4,     3,     3,     3,     3,    62,     8,
       8,     8,     8,     3,     3,    26,    27,    28,     8,     8,
      74,    75,    76,     3,    52,    53,    54,     3,     8,    57,
       4,     4,     8,    87,    62,    63,    90,     3,     3,     3,
     360,     4,     8,     8,     8,   350,   351,    75,    76,     4,
      78,    62,    80,   105,   106,   107,   108,   109,   110,    87,
       4,     3,    90,     3,    75,    76,     8,     3,     8,     4,
      98,   167,     8,     3,   394,    86,     8,     3,     8,     8,
     400,    92,    93,    94,    95,    96,    97,     3,    99,     4,
       4,     8,     8,   413,     3,     3,   416,     4,   400,    81,
      82,    83,    84,     4,   413,     8,   413,   427,     4,   413,
     416,   413,     4,   167,   416,     4,   416,   437,     4,     4,
     442,     4,   442,     4,     4,   427,   442,   167,     4,   413,
       4,   413,     4,   400,     4,   437,     4,     4,     4,   167,
     442,   170,   437,   463,     4,   170,   413,   442,     4,   416,
      63,    64,    65,    66,    67,    68,   167,     4,     4,     4,
     427,   463,    75,    76,   413,     4,   168,   416,   413,     4,
     437,   476,   477,   478,   168,   442,   168,   168,   427,     4,
       4,     4,   427,     4,   413,     4,     4,     4,   413,    33,
      34,    35,    36,   168,    32,     4,   463,     4,   427,    32,
       4,     4,   427,     4,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,     4,
       4,     4,     4,   970,     4,    63,     4,    65,    66,   170,
      63,    69,    70,    71,     4,     4,     4,    75,    76,     4,
       4,   168,     4,     4,     4,    75,    76,     4,     4,   554,
       4,     4,     4,     4,   167,     4,     4,     4,   578,     4,
       4,     4,   168,     4,     4,   585,     4,     4,   170,     4,
     590,   591,   577,   170,     4,   170,   170,     4,     4,     4,
     168,   168,     4,   585,   168,     4,   606,   607,   608,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,     4,   606,   607,   608,   170,   170,   139,
     140,   170,     4,     4,     4,     4,     4,     4,   585,   167,
     134,     7,     7,     7,     7,     7,   167,   167,     7,   167,
       7,     5,     5,   167,   167,     5,     5,   167,     5,   606,
     607,   608,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,     7,   167,     5,     5,
       5,     5,   167,    23,     7,     7,     7,     7,     5,   167,
     167,     5,   167,   167,   167,     7,   167,   167,   167,   167,
     167,   167,     5,     5,     8,     4,   167,     7,   167,     7,
     167,   167,   167,   167,   167,   167,   167,     7,     7,     7,
     167,   167,     7,     7,   167,     7,     7,     7,   167,   167,
       4,     4,   167,     4,     4,     4,     4,     4,     4,     4,
       3,   167,     6,     3,     6,     6,     3,     6,     3,     3,
       6,     3,   168,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     3,   168,     6,     4,     6,     4,     4,
       4,     4,   170,   170,   168,     4,     4,   168,   168,   168,
     168,     4,   168,   170,   168,   168,   168,     4,   168,   168,
       4,   168,     3,     6,     4,   170,     8,     4,     3,     8,
       8,     4,     8,     4,     4,     4,   167,   167,     5,   167,
     578,   167,   167,     7,     4,   167,   167,     4,     4,   167,
       4,   167,   167,   167,   824,   168,   167,   827,   170,   168,
     830,   168,   167,   833,   836,   501,   836,   360,   585,   839,
     836,   830,   400,   830,   844,   394,   830,   847,   830,   844,
     850,   833,   839,   839,   836,   839,   806,   839,   833,   839,
     829,   836,   844,   863,   839,   847,   830,   867,   830,   844,
     665,   824,   842,   873,   852,   839,   850,   839,   878,   830,
     859,   863,   413,   830,   832,   867,   833,   873,   445,   836,
     999,   873,   839,   873,   835,   841,   878,   844,   833,   437,
     847,   830,   838,   878,   836,   830,   849,   442,   875,   416,
     839,   427,   873,   847,   839,   844,   863,   630,   847,   844,
     867,   830,   847,   845,  1004,   830,   873,   867,   608,   463,
     839,   878,   863,  1016,   839,   844,   469,   579,   847,   844,
     879,  1033,   847,  1050,   873,    -1,    -1,    -1,    -1,   466,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   999,
      -1,    -1,    -1,    -1,  1004,    -1,    -1,    -1,    -1,  1004,
      -1,    -1,   999,   999,    -1,   999,  1016,   999,    -1,   999,
      -1,    -1,  1004,    -1,   999,    -1,    -1,    -1,    -1,  1004,
      -1,    -1,    -1,    -1,  1016,   999,    -1,   999,    -1,    -1,
      -1,  1016,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   999,    -1,    -1,    -1,    -1,  1004,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1016,
     999,    -1,    -1,    -1,   999,  1004,    -1,    -1,    -1,  1004,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     999,    -1,    -1,    -1,   999,  1004,    -1,    -1,    -1,  1004
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
       0,     5,     7,     9,   167,   168,   169,   170,   187,   188,
     189,   194,     7,   203,     7,   209,     7,   225,     7,   318,
       7,   398,     7,   414,     7,   350,     7,   356,     7,   380,
       7,   294,     7,   476,     7,   524,     7,   516,   195,   190,
     204,   210,   226,   319,   399,   415,   351,   357,   381,   295,
     477,   525,   517,   187,   196,   197,   167,   192,   193,    10,
     141,   150,   151,   152,   167,   202,   205,   206,   207,   507,
     509,   511,   522,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    52,    53,    54,    55,    56,
      57,    61,    62,    72,    75,    76,    85,    86,    91,   101,
     104,   111,   112,   115,   118,   202,   211,   212,   213,   214,
     215,   216,   217,   219,   220,   221,   236,   238,   244,   246,
     279,   288,   302,   312,   340,   348,   374,   404,   406,   408,
     419,   421,   423,   446,   458,   459,   467,   474,   513,    14,
      15,    18,    21,   202,   223,   224,   227,   229,   232,   235,
     404,   406,    58,    59,    60,    73,    77,    78,    79,    80,
      87,    90,    98,   202,   213,   214,   215,   220,   320,   321,
     322,   324,   326,   328,   330,   332,   334,   336,   339,   374,
     392,   404,   406,   408,   419,   421,   423,   443,    74,   202,
     332,   334,   374,   400,   401,   402,   404,   406,    86,    92,
      93,    94,    95,    96,    97,    99,   202,   374,   404,   406,
     416,   417,   418,   419,   421,   423,   425,   429,   431,   433,
     435,   437,   439,   441,   348,    32,    63,    65,    66,    69,
      70,    71,   202,   264,   358,   359,   360,   361,   362,   363,
     364,   366,   368,   370,   371,   373,   404,   406,    64,    67,
      68,   202,   264,   362,   368,   382,   383,   384,   385,   386,
     388,   389,   390,   391,   404,   406,   102,   103,   202,   296,
     297,   298,   300,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   139,   140,   202,
     404,   406,   478,   479,   480,   481,   483,   485,   486,   488,
     489,   490,   493,   495,   496,   497,   498,   501,   503,   505,
     142,   526,   527,   528,    12,   202,   518,   519,   520,     6,
       3,     4,     8,     3,   208,   523,   508,   510,   512,     4,
       3,     8,   514,   515,   222,   239,     4,     4,   420,   422,
     424,   237,   245,   247,     4,     4,     4,     4,   218,   313,
     349,   375,   341,   405,   407,   280,   447,   409,   289,   303,
       4,   460,   468,   475,     3,     8,   228,   230,   233,     4,
       3,     8,   325,   327,   329,   393,   323,   331,     4,   337,
     335,   333,   444,     3,     8,   403,     3,     8,   442,   430,
     432,   436,   434,   440,   438,   426,     8,     3,     8,   365,
     265,     4,   369,   367,   372,     4,     8,     3,   387,     4,
       4,     8,     3,   299,   301,     3,     8,     4,   482,   484,
       4,   487,     4,     4,   491,   494,     4,     4,     4,   499,
     502,   504,   506,     3,     8,   529,     3,     8,   521,     3,
       8,   187,   187,   167,     4,     4,     4,     4,     4,   206,
     518,     4,     4,     4,   170,   170,     4,     4,     4,     4,
       4,     4,   168,   168,   168,   168,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   168,     4,
       4,     4,   212,     4,     4,     4,   170,   224,     4,     4,
       4,     4,     4,     4,   168,     4,     4,     4,     4,   321,
       4,   401,     4,     4,     4,     4,     4,     4,     4,     4,
     418,     4,     4,   168,     4,     4,     4,   170,   360,     4,
     170,   170,   384,     4,     4,   297,   170,     4,     4,   168,
       4,   168,   168,     4,     4,   170,   170,   170,     4,     4,
       4,     4,   479,     4,   527,     4,   519,     4,     7,     7,
     187,   187,   187,     8,     7,     7,     7,   167,   167,   167,
       7,     7,     5,   167,     5,     5,     5,     5,   189,   191,
     167,     5,     5,     5,     5,     7,     7,     7,     7,     5,
     198,    16,    17,   231,    19,    20,   234,   167,   167,   167,
       5,   167,   167,    81,    82,    83,    84,   338,   198,   167,
       7,   167,   198,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   187,   167,   167,
     167,    17,   133,   492,   134,   135,   136,   137,   138,   170,
     500,   167,   167,   167,     5,     5,   187,   211,   526,   518,
     223,    23,   240,   241,   242,    32,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,   202,   252,   253,   254,   257,   259,   261,   263,   264,
     266,   267,   268,   269,   270,   271,   272,   273,   275,   277,
     278,   252,     7,   248,   249,   250,     7,   314,   315,   316,
       7,   352,   353,   354,     7,   376,   377,   378,     7,   342,
     343,   344,    92,    93,    94,    95,    97,   281,   282,   283,
     284,   285,   286,   287,     7,   448,   449,     7,   410,   411,
     412,     7,   290,   291,   292,   105,   106,   107,   108,   109,
     110,   304,   305,   306,   307,   308,   309,   310,   311,   113,
     114,   202,   404,   406,   461,   462,   463,   465,   116,   117,
     202,   404,   406,   469,   470,   471,   473,   478,   199,     7,
     394,   395,   396,   100,   425,   427,   445,     7,   530,   531,
     248,     8,     8,     8,     8,   243,     3,     8,   255,   258,
     260,   262,     4,     4,     4,     4,     4,   274,   276,     4,
       4,     4,     4,     4,     3,     8,     8,   251,     6,     3,
     317,     6,     3,   355,     6,     3,   379,     6,     3,   345,
       6,     3,     3,     6,   450,     3,     6,   413,     6,     3,
     293,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   464,   466,     3,     8,   472,     4,     3,     8,     8,
     167,   200,   201,   397,     6,     3,   428,     8,   532,     3,
       6,     6,     4,   241,     4,     4,     4,     4,   168,   170,
     168,   170,   168,     4,     4,   168,   168,   168,   168,   170,
     253,   252,   250,   320,   316,   358,   354,   382,   378,   202,
     213,   214,   215,   220,   264,   312,   330,   332,   334,   336,
     346,   347,   374,   404,   406,   419,   421,   423,   443,   344,
     282,    88,    89,   202,   264,   348,   374,   404,   406,   419,
     421,   423,   451,   452,   453,   454,   455,   457,   449,   416,
     412,   296,   292,   168,   168,   168,   168,   168,   168,   305,
       4,     4,   462,     4,   168,   470,     6,     3,   400,   396,
       4,   143,   145,   146,   202,   264,   404,   406,   533,   534,
     535,   536,   538,   531,   167,    33,    34,    35,    36,   256,
     167,   167,   167,   167,   167,     8,     8,     8,     8,     3,
       8,   456,     4,     8,     3,     8,     8,   167,   167,   167,
     167,     8,   198,   539,     4,   537,     3,     8,   347,     4,
     170,   453,     4,   168,     4,   534,   167,     5,   167,     7,
     540,   541,   542,     3,     6,   144,   147,   148,   149,   543,
     544,   545,   547,   548,   549,   541,   546,     4,     4,     4,
       3,     8,     4,   170,   168,   168,   544,   167
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   171,   173,   172,   174,   172,   175,   172,   176,   172,
     177,   172,   178,   172,   179,   172,   180,   172,   181,   172,
     182,   172,   183,   172,   184,   172,   185,   172,   186,   172,
     187,   187,   187,   187,   187,   187,   187,   188,   190,   189,
     191,   192,   192,   193,   193,   195,   194,   196,   196,   197,
     197,   199,   198,   200,   200,   201,   201,   202,   204,   203,
     205,   205,   206,   206,   206,   206,   206,   206,   208,   207,
     210,   209,   211,   211,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   213,   214,   215,   216,
     218,   217,   219,   220,   222,   221,   223,   223,   224,   224,
     224,   224,   224,   224,   224,   226,   225,   228,   227,   230,
     229,   231,   231,   233,   232,   234,   234,   235,   237,   236,
     239,   238,   240,   240,   241,   243,   242,   245,   244,   247,
     246,   248,   248,   249,   249,   251,   250,   252,   252,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   255,   254,   256,
     256,   256,   256,   258,   257,   260,   259,   262,   261,   263,
     265,   264,   266,   267,   268,   269,   270,   271,   272,   274,
     273,   276,   275,   277,   278,   280,   279,   281,   281,   282,
     282,   282,   282,   282,   283,   284,   285,   286,   287,   289,
     288,   290,   290,   291,   291,   293,   292,   295,   294,   296,
     296,   296,   297,   297,   299,   298,   301,   300,   303,   302,
     304,   304,   305,   305,   305,   305,   305,   305,   306,   307,
     308,   309,   310,   311,   313,   312,   314,   314,   315,   315,
     317,   316,   319,   318,   320,   320,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   323,
     322,   325,   324,   327,   326,   329,   328,   331,   330,   333,
     332,   335,   334,   337,   336,   338,   338,   338,   338,   339,
     341,   340,   342,   342,   343,   343,   345,   344,   346,   346,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   349,   348,
     351,   350,   352,   352,   353,   353,   355,   354,   357,   356,
     358,   358,   359,   359,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   361,   362,   363,   365,   364,   367,
     366,   369,   368,   370,   372,   371,   373,   375,   374,   376,
     376,   377,   377,   379,   378,   381,   380,   382,   382,   383,
     383,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     385,   387,   386,   388,   389,   390,   391,   393,   392,   394,
     394,   395,   395,   397,   396,   399,   398,   400,   400,   401,
     401,   401,   401,   401,   401,   401,   403,   402,   405,   404,
     407,   406,   409,   408,   410,   410,   411,   411,   413,   412,
     415,   414,   416,   416,   417,   417,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   420,   419,   422,   421,   424,   423,   426,   425,   428,
     427,   430,   429,   432,   431,   434,   433,   436,   435,   438,
     437,   440,   439,   442,   441,   444,   443,   445,   445,   447,
     446,   448,   448,   450,   449,   451,   451,   452,   452,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     454,   456,   455,   457,   458,   460,   459,   461,   461,   462,
     462,   462,   462,   462,   464,   463,   466,   465,   468,   467,
     469,   469,   470,   470,   470,   470,   470,   472,   471,   473,
     475,   474,   477,   476,   478,   478,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   480,   482,   481,   484,   483,
     485,   487,   486,   488,   489,   491,   490,   492,   492,   494,
     493,   495,   496,   497,   499,   498,   500,   500,   500,   500,
     500,   502,   501,   504,   503,   506,   505,   508,   507,   510,
     509,   512,   511,   514,   513,   515,   513,   517,   516,   518,
     518,   519,   519,   521,   520,   523,   522,   525,   524,   526,
     526,   527,   529,   528,   530,   530,   532,   531,   533,   533,
     534,   534,   534,   534,   534,   534,   534,   535,   537,   536,
     539,   538,   540,   540,   542,   541,   543,   543,   544,   544,
     544,   544,   546,   545,   547,   548,   549
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
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     0,     6,     0,     6,     0,     4,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     3,     3,     3
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
  "\"socket-name\"", "\"queue-control\"", "\"queue-type\"", "\"capacity\"",
  "\"dhcp-ddns\"", "\"enable-updates\"", "\"qualifying-suffix\"",
  "\"server-ip\"", "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
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
  "queue_control_params", "queue_control_param", "queue_type", "$@101",
  "capacity", "dhcp_ddns", "$@102", "sub_dhcp_ddns", "$@103",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@104", "server_ip", "$@105", "server_port",
  "sender_ip", "$@106", "sender_port", "max_queue_size", "ncr_protocol",
  "$@107", "ncr_protocol_value", "ncr_format", "$@108",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@109", "replace_client_name_value",
  "generated_prefix", "$@110", "hostname_char_set", "$@111",
  "hostname_char_replacement", "$@112", "dhcp6_json_object", "$@113",
  "dhcpddns_json_object", "$@114", "control_agent_json_object", "$@115",
  "config_control", "$@116", "$@117", "sub_config_control", "$@118",
  "config_control_params", "config_control_param", "config_databases",
  "$@119", "logging_object", "$@120", "sub_logging", "$@121",
  "logging_params", "logging_param", "loggers", "$@122", "loggers_entries",
  "logger_entry", "$@123", "logger_params", "logger_param", "debuglevel",
  "severity", "$@124", "output_options_list", "$@125",
  "output_options_list_content", "output_entry", "$@126",
  "output_params_list", "output_params", "output", "$@127", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   256,   256,   256,   257,   257,   258,   258,   259,   259,
     260,   260,   261,   261,   262,   262,   263,   263,   264,   264,
     265,   265,   266,   266,   267,   267,   268,   268,   269,   269,
     277,   278,   279,   280,   281,   282,   283,   286,   291,   291,
     302,   305,   306,   309,   313,   320,   320,   327,   328,   331,
     335,   342,   342,   349,   350,   353,   357,   368,   378,   378,
     394,   395,   399,   400,   401,   402,   403,   404,   407,   407,
     422,   422,   431,   432,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   471,   476,   481,   486,
     491,   491,   499,   504,   510,   510,   521,   522,   525,   526,
     527,   528,   529,   530,   531,   534,   534,   543,   543,   553,
     553,   560,   561,   564,   564,   571,   573,   577,   583,   583,
     595,   595,   605,   606,   608,   610,   610,   628,   628,   640,
     640,   650,   651,   654,   655,   658,   658,   668,   669,   672,
     673,   674,   675,   676,   677,   678,   679,   680,   681,   682,
     683,   684,   685,   686,   687,   688,   689,   692,   692,   699,
     700,   701,   702,   705,   705,   713,   713,   721,   721,   729,
     734,   734,   742,   747,   752,   757,   762,   767,   772,   777,
     777,   785,   785,   793,   798,   803,   803,   813,   814,   817,
     818,   819,   820,   821,   824,   829,   834,   839,   844,   849,
     849,   859,   860,   863,   864,   867,   867,   877,   877,   887,
     888,   889,   892,   893,   896,   896,   904,   904,   912,   912,
     923,   924,   927,   928,   929,   930,   931,   932,   935,   940,
     945,   950,   955,   960,   968,   968,   981,   982,   985,   986,
     993,   993,  1019,  1019,  1030,  1031,  1035,  1036,  1037,  1038,
    1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,
    1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1060,
    1060,  1068,  1068,  1076,  1076,  1084,  1084,  1092,  1092,  1100,
    1100,  1108,  1108,  1118,  1118,  1125,  1126,  1127,  1128,  1131,
    1138,  1138,  1149,  1150,  1154,  1155,  1158,  1158,  1166,  1167,
    1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,
    1180,  1181,  1182,  1183,  1184,  1185,  1186,  1187,  1194,  1194,
    1207,  1207,  1216,  1217,  1220,  1221,  1226,  1226,  1241,  1241,
    1255,  1256,  1259,  1260,  1263,  1264,  1265,  1266,  1267,  1268,
    1269,  1270,  1271,  1272,  1275,  1277,  1282,  1284,  1284,  1292,
    1292,  1300,  1300,  1308,  1310,  1310,  1318,  1327,  1327,  1339,
    1340,  1345,  1346,  1351,  1351,  1363,  1363,  1375,  1376,  1381,
    1382,  1387,  1388,  1389,  1390,  1391,  1392,  1393,  1394,  1395,
    1398,  1400,  1400,  1408,  1410,  1412,  1417,  1425,  1425,  1437,
    1438,  1441,  1442,  1445,  1445,  1455,  1455,  1465,  1466,  1469,
    1470,  1471,  1472,  1473,  1474,  1475,  1478,  1478,  1486,  1486,
    1511,  1511,  1541,  1541,  1551,  1552,  1555,  1556,  1559,  1559,
    1568,  1568,  1577,  1578,  1581,  1582,  1586,  1587,  1588,  1589,
    1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,
    1600,  1603,  1603,  1611,  1611,  1619,  1619,  1627,  1627,  1635,
    1635,  1645,  1645,  1653,  1653,  1661,  1661,  1669,  1669,  1677,
    1677,  1685,  1685,  1693,  1693,  1706,  1706,  1716,  1717,  1723,
    1723,  1733,  1734,  1737,  1737,  1747,  1748,  1751,  1752,  1755,
    1756,  1757,  1758,  1759,  1760,  1761,  1762,  1763,  1764,  1765,
    1768,  1770,  1770,  1778,  1787,  1794,  1794,  1804,  1805,  1808,
    1809,  1810,  1811,  1812,  1815,  1815,  1823,  1823,  1834,  1834,
    1846,  1847,  1850,  1851,  1852,  1853,  1854,  1857,  1857,  1865,
    1872,  1872,  1884,  1884,  1894,  1895,  1898,  1899,  1900,  1901,
    1902,  1903,  1904,  1905,  1906,  1907,  1908,  1909,  1910,  1911,
    1912,  1913,  1914,  1915,  1916,  1919,  1924,  1924,  1932,  1932,
    1940,  1945,  1945,  1953,  1958,  1963,  1963,  1971,  1972,  1975,
    1975,  1983,  1988,  1993,  1998,  1998,  2006,  2009,  2012,  2015,
    2018,  2024,  2024,  2032,  2032,  2040,  2040,  2051,  2051,  2058,
    2058,  2065,  2065,  2072,  2072,  2081,  2081,  2092,  2092,  2102,
    2103,  2107,  2108,  2111,  2111,  2126,  2126,  2136,  2136,  2147,
    2148,  2152,  2156,  2156,  2168,  2169,  2173,  2173,  2181,  2182,
    2185,  2186,  2187,  2188,  2189,  2190,  2191,  2194,  2199,  2199,
    2207,  2207,  2217,  2218,  2221,  2221,  2229,  2230,  2233,  2234,
    2235,  2236,  2239,  2239,  2247,  2252,  2257
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
#line 4932 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2262 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
