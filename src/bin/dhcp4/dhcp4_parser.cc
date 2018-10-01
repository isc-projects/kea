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
      case 339: // hr_mode
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
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
      case 339: // hr_mode
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
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

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 167: // "integer"

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 168: // "floating point"

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 169: // "boolean"

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 186: // value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 190: // map_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 230: // socket_type

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 233: // outbound_interface_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 255: // db_type

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 339: // hr_mode

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 487: // ncr_protocol_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 495: // replace_client_name_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 339: // hr_mode
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
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
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 329 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 351 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 355 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 381 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 405 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 146:
#line 625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 699 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 970 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 994 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 261:
#line 1016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 1020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1101 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2023 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1135 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1174 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2274 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1525 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2575 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2585 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2723 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2777 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2864 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1753 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1845 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2996 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1944 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1979 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1982 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1991 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2024 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3328 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3345 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2104 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2129 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3481 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2167 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3517 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2174 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3535 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2185 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 644:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3581 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2214 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3618 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3622 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -794;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     428,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,    38,    24,    40,    47,    57,
     112,   119,   123,   153,   161,   178,   188,   197,   212,   214,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,    24,   -32,
      13,    52,    72,   147,   198,   222,    95,    66,   402,   -56,
     363,    46,    20,  -794,   253,   259,   265,   268,   276,  -794,
    -794,  -794,  -794,  -794,   289,  -794,    50,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   310,   311,  -794,
    -794,  -794,  -794,  -794,  -794,   322,   326,   328,   330,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   331,  -794,  -794,  -794,    81,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     340,  -794,    89,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   341,   343,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   130,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,   141,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,   288,   345,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   344,  -794,  -794,   349,
    -794,  -794,  -794,   350,  -794,  -794,   348,   354,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   355,   358,  -794,  -794,  -794,  -794,   359,   371,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   149,  -794,  -794,  -794,   372,  -794,  -794,   373,  -794,
     376,   379,  -794,  -794,   380,   382,   385,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   151,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   168,  -794,  -794,  -794,  -794,   174,  -794,
    -794,  -794,    24,    24,  -794,   224,   387,   389,   390,   393,
     395,  -794,    13,  -794,    20,   396,   399,   400,   237,   242,
     409,   414,   416,   417,   418,   421,   250,   262,   264,   266,
     422,   423,   430,   436,   438,   439,   440,   442,   443,   444,
     467,   468,   307,   469,   471,    52,  -794,   475,   476,   491,
     263,    72,  -794,   492,   493,   494,   495,   496,   499,   500,
     338,   337,   503,   504,   505,   506,   147,  -794,   507,   198,
    -794,   509,   511,   512,   513,   514,   516,   517,   518,  -794,
     222,  -794,   519,   522,   360,   524,   526,   528,   364,  -794,
      66,   530,   366,   367,  -794,   402,   534,   535,   -33,  -794,
     374,   538,   540,   378,   542,   381,   383,   543,   545,   386,
     388,   391,   550,   552,   554,   555,   363,  -794,   557,    46,
    -794,   558,    20,  -794,  -794,  -794,   559,   560,   562,    24,
      24,    24,  -794,   180,   563,   564,   567,  -794,  -794,   398,
     410,   411,   568,   571,   561,  -794,  -794,  -794,  -794,   429,
     589,   591,   592,   593,   594,   433,   595,   597,   598,   599,
     600,  -794,   601,   602,  -794,   605,    86,   225,  -794,  -794,
     445,   446,   447,   609,   449,   450,   451,  -794,  -794,   127,
     605,   452,   612,  -794,   454,  -794,   605,   455,   456,   457,
     458,   459,   460,   461,  -794,   462,   463,  -794,   464,   465,
     466,  -794,  -794,   470,  -794,  -794,  -794,   472,    24,  -794,
    -794,   473,   474,  -794,   477,  -794,  -794,    29,   432,  -794,
    -794,  -794,   -19,   478,   479,   480,  -794,   628,  -794,   629,
    -794,    24,    52,    46,  -794,  -794,  -794,  -794,    20,    72,
     582,  -794,  -794,  -794,   413,   413,   630,  -794,   634,   635,
     640,   641,  -794,  -794,  -794,    26,   642,   643,   644,   146,
     -15,   363,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   645,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   203,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   646,   630,
    -794,   181,   200,   227,   258,  -794,   260,  -794,  -794,  -794,
    -794,  -794,  -794,   631,   650,   651,   652,   653,  -794,  -794,
     654,   655,   656,   657,   658,  -794,   267,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,   274,  -794,   659,   603,  -794,
    -794,   660,   661,  -794,  -794,   662,   664,  -794,  -794,   663,
     667,  -794,  -794,   665,   669,  -794,  -794,  -794,  -794,  -794,
    -794,    82,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   140,
    -794,  -794,   668,   670,  -794,  -794,   671,   672,  -794,   674,
     675,   676,   677,   678,   679,   277,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   280,  -794,
    -794,  -794,   283,   497,  -794,   680,   673,  -794,  -794,  -794,
    -794,   681,  -794,   164,  -794,   682,  -794,  -794,  -794,  -794,
     683,   582,  -794,   686,   687,   688,   689,   527,   515,   529,
     531,   532,   691,   693,   536,   537,   539,   541,   533,   413,
    -794,  -794,   413,  -794,   630,   147,  -794,   634,    66,  -794,
     635,   402,  -794,   640,   189,  -794,   641,    26,  -794,   275,
     642,  -794,   222,  -794,   643,   -56,  -794,   644,   544,   546,
     547,   548,   549,   551,   146,  -794,   694,   697,   -15,  -794,
    -794,  -794,   699,   704,   198,  -794,   645,   705,  -794,    36,
     646,  -794,  -794,   553,  -794,   306,   556,   565,   566,  -794,
    -794,  -794,  -794,  -794,   569,   570,  -794,  -794,  -794,  -794,
    -794,  -794,   291,  -794,   292,  -794,   702,  -794,   709,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   303,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   708,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   712,   718,  -794,  -794,  -794,  -794,  -794,
     715,  -794,   304,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   572,   573,  -794,  -794,   574,   319,  -794,   605,  -794,
     720,  -794,  -794,  -794,  -794,  -794,   321,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   189,  -794,   721,
     575,  -794,   275,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     722,   576,   723,    36,  -794,  -794,   579,  -794,  -794,   724,
    -794,   580,  -794,  -794,   726,  -794,  -794,   228,  -794,   -52,
     726,  -794,  -794,   730,   733,   737,   325,  -794,  -794,  -794,
    -794,  -794,  -794,   738,   578,   581,   583,   -52,  -794,   585,
    -794,  -794,  -794,  -794,  -794
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   124,     9,   261,    11,
     419,    13,   444,    15,   344,    17,   352,    19,   389,    21,
     226,    23,   534,    25,   609,    27,   599,    29,    47,    41,
       0,     0,     0,     0,     0,   446,     0,   354,   391,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     607,   589,   591,   593,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   595,   597,   113,   139,     0,     0,   465,
     467,   469,   137,   146,   148,     0,     0,     0,     0,   109,
     253,   342,   381,   314,   432,   434,   204,   493,   436,   218,
     237,     0,   519,   532,   104,     0,    72,    74,    75,    76,
      77,   103,    93,    94,    80,    81,   100,    82,    83,    84,
      88,    89,    78,    79,    86,    87,    98,    99,   101,    95,
      96,    97,    85,    90,    91,    92,   102,   126,   128,   132,
       0,   123,     0,   115,   117,   118,   119,   120,   121,   122,
     292,   294,   296,   411,   290,   298,   300,     0,     0,   306,
     304,   302,   489,   289,   265,   266,   267,   280,     0,   263,
     270,   284,   285,   286,   271,   272,   275,   276,   278,   273,
     274,   268,   269,   287,   288,   277,   281,   282,   283,   279,
     430,   429,   425,   426,   424,     0,   421,   423,   427,   428,
     487,   475,   477,   481,   479,   485,   483,   471,   464,   458,
     462,   463,     0,   447,   448,   459,   460,   461,   455,   450,
     456,   452,   453,   454,   457,   451,     0,   371,   189,     0,
     375,   373,   378,     0,   367,   368,     0,   355,   356,   358,
     370,   359,   360,   361,   377,   362,   363,   364,   365,   366,
     405,     0,     0,   403,   404,   407,   408,     0,   392,   393,
     395,   396,   397,   398,   399,   400,   401,   402,   233,   235,
     230,     0,   228,   231,   232,     0,   558,   560,     0,   563,
       0,     0,   567,   571,     0,     0,     0,   576,   583,   585,
     587,   556,   554,   555,     0,   536,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   614,     0,   611,   613,   605,   604,     0,   601,
     603,    46,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    57,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   262,     0,     0,
     420,     0,     0,     0,     0,     0,     0,     0,     0,   445,
       0,   345,     0,     0,     0,     0,     0,     0,     0,   353,
       0,     0,     0,     0,   390,     0,     0,     0,     0,   227,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   535,     0,     0,
     610,     0,     0,   600,    50,    43,     0,     0,     0,     0,
       0,     0,    61,     0,     0,     0,     0,   111,   112,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   518,     0,     0,    73,     0,     0,     0,   136,   116,
       0,     0,     0,     0,     0,     0,     0,   312,   313,     0,
       0,     0,     0,   264,     0,   422,     0,     0,     0,     0,
       0,     0,     0,     0,   449,     0,     0,   369,     0,     0,
       0,   380,   357,     0,   409,   410,   394,     0,     0,   229,
     557,     0,     0,   562,     0,   565,   566,     0,     0,   573,
     574,   575,     0,     0,     0,     0,   537,     0,   612,     0,
     602,     0,     0,     0,   590,   592,   594,   596,     0,     0,
       0,   466,   468,   470,     0,     0,   150,   110,   255,   346,
     383,   316,    40,   433,   435,     0,     0,   438,   220,     0,
       0,     0,    51,   127,   130,   131,   129,   134,   135,   133,
     293,   295,   297,   413,   291,   299,   301,   308,   309,   310,
     311,   307,   305,   303,     0,   431,   488,   476,   478,   482,
     480,   486,   484,   472,   372,   190,   376,   374,   379,   406,
     234,   236,   559,   561,   564,   569,   570,   568,   572,   578,
     579,   580,   581,   582,   577,   584,   586,   588,     0,   150,
      44,     0,     0,     0,     0,   144,     0,   141,   143,   176,
     182,   184,   186,     0,     0,     0,     0,     0,   198,   200,
       0,     0,     0,     0,     0,   175,     0,   156,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   171,   172,
     173,   168,   174,   169,   170,     0,   154,     0,   151,   152,
     259,     0,   256,   257,   350,     0,   347,   348,   387,     0,
     384,   385,   320,     0,   317,   318,   213,   214,   215,   216,
     217,     0,   206,   208,   209,   210,   211,   212,   497,     0,
     495,   442,     0,   439,   440,   224,     0,   221,   222,     0,
       0,     0,     0,     0,     0,     0,   239,   241,   242,   243,
     244,   245,   246,   528,   530,   527,   525,   526,     0,   521,
     523,   524,     0,    53,   417,     0,   414,   415,   473,   491,
     492,     0,   618,     0,   616,     0,    69,   608,   598,   114,
       0,     0,   140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   147,     0,   149,     0,     0,   254,     0,   354,   343,
       0,   391,   382,     0,     0,   315,     0,     0,   205,   499,
       0,   494,   446,   437,     0,     0,   219,     0,     0,     0,
       0,     0,     0,     0,     0,   238,     0,     0,     0,   520,
     533,    55,     0,    54,     0,   412,     0,     0,   490,     0,
       0,   615,   606,     0,   142,     0,     0,     0,     0,   188,
     191,   192,   193,   194,     0,     0,   202,   203,   195,   196,
     197,   157,     0,   153,     0,   258,     0,   349,     0,   386,
     341,   338,   327,   328,   330,   324,   325,   326,   336,   337,
     335,     0,   322,   329,   339,   340,   331,   332,   333,   334,
     319,   207,   515,     0,   513,   514,   506,   507,   511,   512,
     508,   509,   510,     0,   500,   501,   503,   504,   505,   496,
       0,   441,     0,   223,   247,   248,   249,   250,   251,   252,
     240,     0,     0,   522,    52,     0,     0,   416,     0,   632,
       0,   630,   628,   622,   626,   627,     0,   620,   624,   625,
     623,   617,   145,   178,   179,   180,   181,   177,   183,   185,
     187,   199,   201,   155,   260,   351,   388,     0,   321,     0,
       0,   498,     0,   443,   225,   529,   531,    56,   418,   474,
       0,     0,     0,     0,   619,   323,     0,   517,   502,     0,
     629,     0,   621,   516,     0,   631,   636,     0,   634,     0,
       0,   633,   644,     0,     0,     0,     0,   638,   640,   641,
     642,   643,   635,     0,     0,     0,     0,     0,   637,     0,
     646,   647,   648,   639,   645
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   -44,  -794,   226,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -509,  -794,  -794,
    -794,   -70,  -794,  -794,  -794,   323,  -794,  -794,  -794,  -794,
     171,   333,   -48,   -45,   -43,  -794,  -794,  -794,  -794,   -11,
    -794,  -794,   165,   356,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     -42,  -794,  -794,  -794,  -794,  -794,  -794,    87,  -794,   -64,
    -794,  -589,   -57,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   -26,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   -74,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   -81,  -794,  -794,  -794,   -77,   335,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   -75,  -794,  -794,  -794,  -794,  -794,
    -794,  -793,  -794,  -794,  -794,   -35,  -794,  -794,  -794,   -40,
     401,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -791,
    -794,  -794,  -794,   -24,  -794,    -4,  -794,  -790,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   -41,  -794,  -794,  -190,
     -65,  -794,  -794,  -794,  -794,  -794,   -27,  -794,  -794,  -794,
     -30,  -794,   369,  -794,   -66,  -794,  -794,  -794,  -794,  -794,
     -60,  -794,  -794,  -794,  -794,  -794,   -18,  -794,  -794,  -794,
     -21,  -794,  -794,  -794,   -16,  -794,   377,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   -37,  -794,
    -794,  -794,   -23,   419,  -794,  -794,   -58,  -794,   -38,  -794,
     -47,  -794,  -794,  -794,     1,  -794,  -794,  -794,    -5,  -794,
     420,    -7,  -794,    -6,  -794,     0,  -794,   210,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -789,  -794,  -794,  -794,  -794,
    -794,     7,  -794,  -794,  -794,  -144,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,    -9,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   240,   392,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -351,   384,  -794,  -794,  -794,  -794,  -794,
    -794,   269,   394,  -794,  -794,  -794,   -17,  -794,  -794,  -149,
    -794,  -794,  -794,  -794,  -794,  -794,  -165,  -794,  -794,  -180,
    -794,  -794,  -794,  -794,  -794
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     603,    87,    88,    41,    68,    84,    85,   613,   783,   862,
     863,   347,    43,    70,    96,    97,    98,   356,    45,    71,
     135,   136,   137,   138,   139,   140,   141,   380,   142,   143,
     144,   366,   172,   173,    47,    72,   174,   397,   175,   398,
     616,   176,   399,   619,   177,   145,   373,   146,   367,   676,
     677,   678,   800,   147,   374,   148,   375,   717,   718,   719,
     822,   696,   697,   698,   803,   977,   699,   804,   700,   805,
     701,   806,   702,   703,   433,   704,   705,   706,   707,   708,
     709,   710,   711,   812,   712,   813,   713,   714,   149,   387,
     741,   742,   743,   744,   745,   746,   747,   150,   390,   756,
     757,   758,   845,    61,    79,   301,   302,   303,   446,   304,
     447,   151,   391,   765,   766,   767,   768,   769,   770,   771,
     772,   152,   381,   721,   722,   723,   825,    49,    73,   198,
     199,   200,   407,   201,   403,   202,   404,   203,   405,   204,
     408,   205,   409,   206,   414,   207,   413,   208,   412,   631,
     209,   210,   153,   384,   733,   734,   735,   834,   911,   912,
     154,   382,    55,    76,   725,   726,   727,   828,    57,    77,
     266,   267,   268,   269,   270,   271,   272,   432,   273,   436,
     274,   435,   275,   276,   437,   277,   155,   383,   729,   730,
     731,   831,    59,    78,   287,   288,   289,   290,   291,   441,
     292,   293,   294,   295,   212,   406,   785,   786,   787,   864,
      51,    74,   225,   226,   227,   418,   156,   385,   157,   386,
     158,   389,   752,   753,   754,   842,    53,    75,   242,   243,
     244,   159,   370,   160,   371,   161,   372,   248,   428,   790,
     867,   249,   422,   250,   423,   251,   425,   252,   424,   253,
     427,   254,   426,   255,   421,   219,   415,   791,   162,   388,
     749,   750,   839,   933,   934,   935,   936,   937,   989,   938,
     163,   164,   393,   778,   779,   780,   856,   781,   857,   165,
     394,    63,    80,   324,   325,   326,   327,   451,   328,   452,
     329,   330,   454,   331,   332,   333,   457,   657,   334,   458,
     335,   336,   337,   338,   462,   664,   339,   463,   340,   464,
     341,   465,    99,   358,   100,   359,   101,   360,   166,   364,
     365,    67,    82,   348,   349,   350,   471,   102,   357,    65,
      81,   343,   344,   345,   468,   793,   794,   869,   966,   967,
     968,   969,  1002,   970,  1000,  1017,  1018,  1019,  1026,  1027,
    1028,  1033,  1029,  1030,  1031
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   134,   171,   193,   221,   238,   715,   264,   283,   300,
     321,   256,   285,   483,   178,   213,   228,   240,   286,   278,
     296,   632,   322,    89,    83,   194,   215,   636,   195,    31,
     196,    32,   346,    33,   179,   214,   229,   241,    30,   279,
     297,   906,   323,   907,   910,   919,   655,    42,   298,   299,
     222,   265,   284,   362,    44,   211,   224,   239,   363,   103,
     124,   125,   197,   104,    46,   105,   216,   217,   245,   246,
     223,   298,   299,   218,   106,   247,   107,   108,   109,   110,
     111,   112,   113,   114,   395,   837,   167,   168,   838,   396,
     169,  1022,   401,   170,  1023,  1024,  1025,   402,   257,   258,
     773,   774,   614,   615,   115,   116,   117,   118,   119,   120,
      94,   124,   125,   121,   122,   659,   660,   661,   662,    48,
     736,   737,   738,   739,   123,   740,    50,   124,   125,   258,
      52,   259,   260,   416,    86,   261,   262,   263,   417,   126,
     127,   124,   125,   840,   419,   128,   841,   124,   125,   420,
     663,    94,   448,    90,   466,   129,   121,   449,   130,   467,
      54,   656,    91,    92,    93,   131,   132,   870,    56,   133,
     871,   469,   108,   109,   110,   111,   470,   472,   959,    94,
     960,   961,   473,   472,   395,    58,    94,   342,   587,   796,
      34,    35,    36,    37,   906,    60,   907,   910,   919,   115,
     116,   117,    94,   469,    62,   180,   181,   182,   797,   122,
     627,   628,   629,   630,   108,   109,   110,   111,    94,    64,
     183,    66,   124,   125,   184,   185,   186,   187,   188,   189,
     472,  1020,    94,   892,  1021,   798,   190,   673,    94,   191,
     128,   115,   116,   117,   617,   618,   120,   192,   109,   110,
     111,   122,   258,   759,   760,   761,   762,   763,   764,   351,
     122,   401,   352,   801,   124,   125,   799,   185,   802,   353,
     819,   189,   220,   124,   125,   820,   354,   819,   190,   355,
     854,   191,   821,   858,   122,   855,   466,   190,   859,   192,
     191,   860,    95,   361,   819,   416,   429,   124,   125,   983,
     984,   109,   110,   111,   237,   788,   987,   448,   474,   475,
     230,   988,   994,    94,   368,   369,   231,   232,   233,   234,
     235,   236,   419,   237,  1003,   134,   376,   998,  1037,  1004,
     377,   171,   378,  1038,   379,   392,   121,   122,   258,   973,
     974,   975,   976,   178,   400,   410,   193,   411,   430,   221,
     124,   125,   431,   434,   438,    94,   439,   440,   213,   442,
     238,   228,   443,   179,    94,   922,   923,   444,   194,   215,
     264,   195,   240,   196,   445,   283,   450,   453,   214,   285,
     455,   229,   278,   456,   459,   286,   460,   296,    94,   461,
     476,   477,   241,   478,   479,   222,   321,   480,   211,   481,
     484,   224,   279,   485,   486,   197,   487,   297,   322,   216,
     217,   488,   239,   489,   265,   223,   218,   495,   490,   284,
     491,   492,   493,   245,   246,   494,   499,   500,   323,   496,
     247,   497,   518,   498,   501,   584,   585,   586,   124,   125,
     502,    94,   503,   504,   505,   679,   506,   507,   508,   999,
     680,   681,   682,   683,   684,   685,   686,   687,   688,   689,
     690,   691,   692,   693,   694,   258,   280,   259,   260,   281,
     282,   509,   510,   512,   511,   513,   258,   124,   125,   515,
     516,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   517,   520,   521,   522,   523,
     524,   319,   320,   525,   526,   527,   528,   529,   530,   531,
     532,   534,   134,   536,   651,   537,   538,   539,   540,   171,
     541,   542,   543,   545,   695,   695,   546,   547,   548,    94,
     549,   178,   550,   551,   553,   554,   555,   670,   557,   558,
     775,   321,   561,   560,   562,   563,   564,   567,   565,   568,
     566,   179,   776,   322,   572,   569,   573,   570,   574,   575,
     571,   577,   579,   581,   591,   658,   596,   582,    94,   583,
     588,   589,   777,   323,   590,   594,   592,   593,   595,    94,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   598,   597,   599,   600,   601,   604,
     605,    32,   606,   607,   608,   675,   824,   609,   610,   611,
     612,   620,   621,   622,   623,   624,   625,   626,   633,   634,
     635,   637,   638,   639,   640,   641,   642,   643,   644,   645,
     646,   647,   648,   668,   669,   807,   649,   716,   650,   652,
     653,   720,   724,   654,   665,   666,   667,   728,   732,   748,
     751,   755,   784,   792,   808,   809,   810,   811,   814,   815,
     816,   817,   818,   861,   827,   823,   826,   830,   829,   832,
     833,   835,   836,   844,   843,   847,   866,   846,   848,   849,
     850,   851,   852,   853,   880,   482,   865,   873,   872,   868,
     875,   876,   877,   878,   879,   884,   881,   885,   951,   883,
     882,   952,   890,   886,   887,   954,   888,   955,   889,   958,
     985,   944,   990,   945,   946,   947,   948,   986,   949,   972,
     991,   992,   978,   993,  1001,  1006,  1009,  1011,   514,  1014,
     602,   979,   980,  1016,  1034,   981,   982,  1035,   995,   996,
     997,  1036,  1039,  1010,  1007,  1013,  1015,  1040,  1041,   695,
    1042,  1044,   695,   671,   674,   193,   795,   519,   264,   874,
     893,   283,   891,   921,   900,   285,   943,   213,   942,   924,
     278,   286,   238,   296,   926,   300,   914,   194,   215,   950,
     195,   928,   196,   559,   240,   894,   901,   214,   775,   902,
     279,   903,   895,   297,   221,   920,   915,  1005,   896,   962,
     776,   929,   265,   897,   241,   284,   228,   211,   905,   552,
     908,   964,   899,   925,   197,   898,   913,   533,   216,   217,
     777,   927,   556,   904,   239,   218,   229,   916,   917,   957,
     909,   965,   930,   931,   918,   245,   246,   940,   535,   932,
     222,   956,   247,   963,   789,   941,   224,   939,  1008,   953,
     544,   782,   672,   971,  1012,  1032,   580,  1043,   576,     0,
     223,     0,     0,   578,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   900,     0,     0,
       0,     0,   924,     0,     0,     0,     0,   926,     0,   914,
       0,     0,     0,   962,   928,     0,     0,     0,     0,   901,
       0,     0,   902,     0,   903,   964,     0,     0,     0,   915,
       0,     0,     0,     0,   929,     0,     0,     0,     0,     0,
       0,   905,     0,   908,     0,   965,   925,     0,     0,   913,
       0,     0,     0,     0,   927,     0,   904,   963,     0,     0,
     916,   917,     0,   909,     0,   930,   931,   918,     0,     0,
       0,     0,   932
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,   595,    77,    78,    79,
      80,    76,    78,   364,    72,    73,    74,    75,    78,    77,
      78,   530,    80,    10,    68,    73,    73,   536,    73,     5,
      73,     7,    12,     9,    72,    73,    74,    75,     0,    77,
      78,   834,    80,   834,   834,   834,    17,     7,   104,   105,
      74,    77,    78,     3,     7,    73,    74,    75,     8,     7,
      75,    76,    73,    11,     7,    13,    73,    73,    75,    75,
      74,   104,   105,    73,    22,    75,    24,    25,    26,    27,
      28,    29,    30,    31,     3,     3,    14,    15,     6,     8,
      18,   143,     3,    21,   146,   147,   148,     8,    32,    63,
     115,   116,    16,    17,    52,    53,    54,    55,    56,    57,
     166,    75,    76,    61,    62,   134,   135,   136,   137,     7,
      94,    95,    96,    97,    72,    99,     7,    75,    76,    63,
       7,    65,    66,     3,   166,    69,    70,    71,     8,    87,
      88,    75,    76,     3,     3,    93,     6,    75,    76,     8,
     169,   166,     3,   140,     3,   103,    61,     8,   106,     8,
       7,   132,   149,   150,   151,   113,   114,     3,     7,   117,
       6,     3,    25,    26,    27,    28,     8,     3,   142,   166,
     144,   145,     8,     3,     3,     7,   166,   141,     8,     8,
     166,   167,   168,   169,   987,     7,   987,   987,   987,    52,
      53,    54,   166,     3,     7,    58,    59,    60,     8,    62,
      83,    84,    85,    86,    25,    26,    27,    28,   166,     7,
      73,     7,    75,    76,    77,    78,    79,    80,    81,    82,
       3,     3,   166,   822,     6,     8,    89,   588,   166,    92,
      93,    52,    53,    54,    19,    20,    57,   100,    26,    27,
      28,    62,    63,   107,   108,   109,   110,   111,   112,     6,
      62,     3,     3,     3,    75,    76,     8,    78,     8,     4,
       3,    82,    74,    75,    76,     8,     8,     3,    89,     3,
       3,    92,     8,     3,    62,     8,     3,    89,     8,   100,
      92,     8,   362,     4,     3,     3,     8,    75,    76,     8,
       8,    26,    27,    28,   101,   102,     3,     3,   352,   353,
      88,     8,     8,   166,     4,     4,    94,    95,    96,    97,
      98,    99,     3,   101,     3,   395,     4,     8,     3,     8,
       4,   401,     4,     8,     4,     4,    61,    62,    63,    33,
      34,    35,    36,   401,     4,     4,   416,     4,     3,   419,
      75,    76,     8,     4,     4,   166,     8,     3,   416,     4,
     430,   419,     4,   401,   166,    90,    91,     8,   416,   416,
     440,   416,   430,   416,     3,   445,     4,     4,   416,   445,
       4,   419,   440,     4,     4,   445,     4,   445,   166,     4,
     166,     4,   430,     4,     4,   419,   466,     4,   416,     4,
       4,   419,   440,     4,     4,   416,   169,   445,   466,   416,
     416,   169,   430,     4,   440,   419,   416,   167,     4,   445,
       4,     4,     4,   430,   430,     4,     4,     4,   466,   167,
     430,   167,   169,   167,     4,   479,   480,   481,    75,    76,
       4,   166,     4,     4,     4,    32,     4,     4,     4,   958,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    63,    64,    65,    66,    67,
      68,     4,     4,     4,   167,     4,    63,    75,    76,     4,
       4,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,     4,     4,     4,     4,     4,
       4,   138,   139,     4,     4,   167,   169,     4,     4,     4,
       4,     4,   582,     4,   558,     4,     4,     4,     4,   589,
       4,     4,     4,     4,   594,   595,     4,   167,     4,   166,
       4,   589,     4,   169,     4,   169,   169,   581,     4,     4,
     610,   611,     4,   169,     4,   167,     4,     4,   167,     4,
     167,   589,   610,   611,     4,   169,     4,   169,     4,     4,
     169,     4,     4,     4,   166,   133,     5,     7,   166,     7,
       7,     7,   610,   611,     7,     7,   166,   166,     7,   166,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,     5,   166,     5,     5,     5,   166,
       5,     7,     5,     5,     5,    23,     3,     7,     7,     7,
       5,   166,   166,   166,     5,   166,   166,   166,   166,     7,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,     5,     5,     4,   166,     7,   166,   166,
     166,     7,     7,   166,   166,   166,   166,     7,     7,     7,
       7,     7,     7,     7,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   166,     3,     6,     6,     3,     6,     6,
       3,     6,     3,     3,     6,     3,     3,     6,     4,     4,
       4,     4,     4,     4,   169,   362,     6,     4,     6,     8,
       4,     4,     4,     4,   167,     4,   167,     4,     4,   167,
     169,     4,   169,   167,   167,     6,   167,     3,   167,     4,
       8,   167,     4,   167,   167,   167,   167,     8,   167,   166,
       8,     3,   166,     8,     4,     4,     4,     4,   395,     5,
     504,   166,   166,     7,     4,   166,   166,     4,   166,   166,
     166,     4,     4,   167,   169,   166,   166,   169,   167,   819,
     167,   166,   822,   582,   589,   825,   669,   401,   828,   801,
     824,   831,   819,   837,   834,   831,   847,   825,   845,   839,
     828,   831,   842,   831,   839,   845,   834,   825,   825,   854,
     825,   839,   825,   448,   842,   825,   834,   825,   858,   834,
     828,   834,   827,   831,   864,   836,   834,   987,   828,   869,
     858,   839,   828,   830,   842,   831,   864,   825,   834,   440,
     834,   869,   833,   839,   825,   831,   834,   416,   825,   825,
     858,   839,   445,   834,   842,   825,   864,   834,   834,   866,
     834,   869,   839,   839,   834,   842,   842,   842,   419,   839,
     864,   864,   842,   869,   634,   844,   864,   840,   992,   858,
     430,   611,   583,   870,  1003,  1020,   472,  1037,   466,    -1,
     864,    -1,    -1,   469,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   987,    -1,    -1,
      -1,    -1,   992,    -1,    -1,    -1,    -1,   992,    -1,   987,
      -1,    -1,    -1,  1003,   992,    -1,    -1,    -1,    -1,   987,
      -1,    -1,   987,    -1,   987,  1003,    -1,    -1,    -1,   987,
      -1,    -1,    -1,    -1,   992,    -1,    -1,    -1,    -1,    -1,
      -1,   987,    -1,   987,    -1,  1003,   992,    -1,    -1,   987,
      -1,    -1,    -1,    -1,   992,    -1,   987,  1003,    -1,    -1,
     987,   987,    -1,   987,    -1,   992,   992,   987,    -1,    -1,
      -1,    -1,   992
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,     5,     7,     9,   166,   167,   168,   169,   186,   187,
     188,   193,     7,   202,     7,   208,     7,   224,     7,   317,
       7,   400,     7,   416,     7,   352,     7,   358,     7,   382,
       7,   293,     7,   471,     7,   519,     7,   511,   194,   189,
     203,   209,   225,   318,   401,   417,   353,   359,   383,   294,
     472,   520,   512,   186,   195,   196,   166,   191,   192,    10,
     140,   149,   150,   151,   166,   201,   204,   205,   206,   502,
     504,   506,   517,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    52,    53,    54,    55,    56,
      57,    61,    62,    72,    75,    76,    87,    88,    93,   103,
     106,   113,   114,   117,   201,   210,   211,   212,   213,   214,
     215,   216,   218,   219,   220,   235,   237,   243,   245,   278,
     287,   301,   311,   342,   350,   376,   406,   408,   410,   421,
     423,   425,   448,   460,   461,   469,   508,    14,    15,    18,
      21,   201,   222,   223,   226,   228,   231,   234,   406,   408,
      58,    59,    60,    73,    77,    78,    79,    80,    81,    82,
      89,    92,   100,   201,   212,   213,   214,   219,   319,   320,
     321,   323,   325,   327,   329,   331,   333,   335,   337,   340,
     341,   376,   394,   406,   408,   410,   421,   423,   425,   445,
      74,   201,   333,   335,   376,   402,   403,   404,   406,   408,
      88,    94,    95,    96,    97,    98,    99,   101,   201,   376,
     406,   408,   418,   419,   420,   421,   423,   425,   427,   431,
     433,   435,   437,   439,   441,   443,   350,    32,    63,    65,
      66,    69,    70,    71,   201,   263,   360,   361,   362,   363,
     364,   365,   366,   368,   370,   372,   373,   375,   406,   408,
      64,    67,    68,   201,   263,   364,   370,   384,   385,   386,
     387,   388,   390,   391,   392,   393,   406,   408,   104,   105,
     201,   295,   296,   297,   299,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   138,
     139,   201,   406,   408,   473,   474,   475,   476,   478,   480,
     481,   483,   484,   485,   488,   490,   491,   492,   493,   496,
     498,   500,   141,   521,   522,   523,    12,   201,   513,   514,
     515,     6,     3,     4,     8,     3,   207,   518,   503,   505,
     507,     4,     3,     8,   509,   510,   221,   238,     4,     4,
     422,   424,   426,   236,   244,   246,     4,     4,     4,     4,
     217,   312,   351,   377,   343,   407,   409,   279,   449,   411,
     288,   302,     4,   462,   470,     3,     8,   227,   229,   232,
       4,     3,     8,   324,   326,   328,   395,   322,   330,   332,
       4,     4,   338,   336,   334,   446,     3,     8,   405,     3,
       8,   444,   432,   434,   438,   436,   442,   440,   428,     8,
       3,     8,   367,   264,     4,   371,   369,   374,     4,     8,
       3,   389,     4,     4,     8,     3,   298,   300,     3,     8,
       4,   477,   479,     4,   482,     4,     4,   486,   489,     4,
       4,     4,   494,   497,   499,   501,     3,     8,   524,     3,
       8,   516,     3,     8,   186,   186,   166,     4,     4,     4,
       4,     4,   205,   513,     4,     4,     4,   169,   169,     4,
       4,     4,     4,     4,     4,   167,   167,   167,   167,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   167,     4,     4,   211,     4,     4,     4,   169,   223,
       4,     4,     4,     4,     4,     4,     4,   167,   169,     4,
       4,     4,     4,   320,     4,   403,     4,     4,     4,     4,
       4,     4,     4,     4,   420,     4,     4,   167,     4,     4,
       4,   169,   362,     4,   169,   169,   386,     4,     4,   296,
     169,     4,     4,   167,     4,   167,   167,     4,     4,   169,
     169,   169,     4,     4,     4,     4,   474,     4,   522,     4,
     514,     4,     7,     7,   186,   186,   186,     8,     7,     7,
       7,   166,   166,   166,     7,     7,     5,   166,     5,     5,
       5,     5,   188,   190,   166,     5,     5,     5,     5,     7,
       7,     7,     5,   197,    16,    17,   230,    19,    20,   233,
     166,   166,   166,     5,   166,   166,   166,    83,    84,    85,
      86,   339,   197,   166,     7,   166,   197,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   186,   166,   166,   166,    17,   132,   487,   133,   134,
     135,   136,   137,   169,   495,   166,   166,   166,     5,     5,
     186,   210,   521,   513,   222,    23,   239,   240,   241,    32,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,   201,   251,   252,   253,   256,
     258,   260,   262,   263,   265,   266,   267,   268,   269,   270,
     271,   272,   274,   276,   277,   251,     7,   247,   248,   249,
       7,   313,   314,   315,     7,   354,   355,   356,     7,   378,
     379,   380,     7,   344,   345,   346,    94,    95,    96,    97,
      99,   280,   281,   282,   283,   284,   285,   286,     7,   450,
     451,     7,   412,   413,   414,     7,   289,   290,   291,   107,
     108,   109,   110,   111,   112,   303,   304,   305,   306,   307,
     308,   309,   310,   115,   116,   201,   406,   408,   463,   464,
     465,   467,   473,   198,     7,   396,   397,   398,   102,   427,
     429,   447,     7,   525,   526,   247,     8,     8,     8,     8,
     242,     3,     8,   254,   257,   259,   261,     4,     4,     4,
       4,     4,   273,   275,     4,     4,     4,     4,     4,     3,
       8,     8,   250,     6,     3,   316,     6,     3,   357,     6,
       3,   381,     6,     3,   347,     6,     3,     3,     6,   452,
       3,     6,   415,     6,     3,   292,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   466,   468,     3,     8,
       8,   166,   199,   200,   399,     6,     3,   430,     8,   527,
       3,     6,     6,     4,   240,     4,     4,     4,     4,   167,
     169,   167,   169,   167,     4,     4,   167,   167,   167,   167,
     169,   252,   251,   249,   319,   315,   360,   356,   384,   380,
     201,   212,   213,   214,   219,   263,   311,   329,   333,   335,
     337,   348,   349,   376,   406,   408,   421,   423,   425,   445,
     346,   281,    90,    91,   201,   263,   350,   376,   406,   408,
     421,   423,   425,   453,   454,   455,   456,   457,   459,   451,
     418,   414,   295,   291,   167,   167,   167,   167,   167,   167,
     304,     4,     4,   464,     6,     3,   402,   398,     4,   142,
     144,   145,   201,   263,   406,   408,   528,   529,   530,   531,
     533,   526,   166,    33,    34,    35,    36,   255,   166,   166,
     166,   166,   166,     8,     8,     8,     8,     3,     8,   458,
       4,     8,     3,     8,     8,   166,   166,   166,     8,   197,
     534,     4,   532,     3,     8,   349,     4,   169,   455,     4,
     167,     4,   529,   166,     5,   166,     7,   535,   536,   537,
       3,     6,   143,   146,   147,   148,   538,   539,   540,   542,
     543,   544,   536,   541,     4,     4,     4,     3,     8,     4,
     169,   167,   167,   539,   166
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
     211,   211,   211,   211,   211,   212,   213,   214,   215,   217,
     216,   218,   219,   221,   220,   222,   222,   223,   223,   223,
     223,   223,   223,   223,   225,   224,   227,   226,   229,   228,
     230,   230,   232,   231,   233,   233,   234,   236,   235,   238,
     237,   239,   239,   240,   242,   241,   244,   243,   246,   245,
     247,   247,   248,   248,   250,   249,   251,   251,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   254,   253,   255,   255,
     255,   255,   257,   256,   259,   258,   261,   260,   262,   264,
     263,   265,   266,   267,   268,   269,   270,   271,   273,   272,
     275,   274,   276,   277,   279,   278,   280,   280,   281,   281,
     281,   281,   281,   282,   283,   284,   285,   286,   288,   287,
     289,   289,   290,   290,   292,   291,   294,   293,   295,   295,
     295,   296,   296,   298,   297,   300,   299,   302,   301,   303,
     303,   304,   304,   304,   304,   304,   304,   305,   306,   307,
     308,   309,   310,   312,   311,   313,   313,   314,   314,   316,
     315,   318,   317,   319,   319,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     322,   321,   324,   323,   326,   325,   328,   327,   330,   329,
     332,   331,   334,   333,   336,   335,   338,   337,   339,   339,
     339,   339,   340,   341,   343,   342,   344,   344,   345,   345,
     347,   346,   348,   348,   349,   349,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   351,   350,   353,   352,   354,   354,   355,   355,
     357,   356,   359,   358,   360,   360,   361,   361,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   363,   364,
     365,   367,   366,   369,   368,   371,   370,   372,   374,   373,
     375,   377,   376,   378,   378,   379,   379,   381,   380,   383,
     382,   384,   384,   385,   385,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   387,   389,   388,   390,   391,   392,
     393,   395,   394,   396,   396,   397,   397,   399,   398,   401,
     400,   402,   402,   403,   403,   403,   403,   403,   403,   403,
     405,   404,   407,   406,   409,   408,   411,   410,   412,   412,
     413,   413,   415,   414,   417,   416,   418,   418,   419,   419,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   422,   421,   424,   423,   426,
     425,   428,   427,   430,   429,   432,   431,   434,   433,   436,
     435,   438,   437,   440,   439,   442,   441,   444,   443,   446,
     445,   447,   447,   449,   448,   450,   450,   452,   451,   453,
     453,   454,   454,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   456,   458,   457,   459,   460,   462,
     461,   463,   463,   464,   464,   464,   464,   464,   466,   465,
     468,   467,   470,   469,   472,   471,   473,   473,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   475,   477,   476,
     479,   478,   480,   482,   481,   483,   484,   486,   485,   487,
     487,   489,   488,   490,   491,   492,   494,   493,   495,   495,
     495,   495,   495,   497,   496,   499,   498,   501,   500,   503,
     502,   505,   504,   507,   506,   509,   508,   510,   508,   512,
     511,   513,   513,   514,   514,   516,   515,   518,   517,   520,
     519,   521,   521,   522,   524,   523,   525,   525,   527,   526,
     528,   528,   529,   529,   529,   529,   529,   529,   529,   530,
     532,   531,   534,   533,   535,   535,   537,   536,   538,   538,
     539,   539,   539,   539,   541,   540,   542,   543,   544
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
       1,     1,     1,     1,     1,     3,     3,     3,     3,     0,
       4,     3,     3,     0,     6,     1,     3,     1,     1,     1,
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
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     0,
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
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"global\"",
  "\"all\"", "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
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
  "$@52", "subnet_4o6_subnet", "$@53", "interface", "$@54", "interface_id",
  "$@55", "client_class", "$@56", "require_client_classes", "$@57",
  "reservation_mode", "$@58", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@59", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@60",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@61", "sub_option_def_list", "$@62", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@63",
  "sub_option_def", "$@64", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@65",
  "option_def_record_types", "$@66", "space", "$@67", "option_def_space",
  "option_def_encapsulate", "$@68", "option_def_array", "option_data_list",
  "$@69", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@70", "sub_option_data", "$@71",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@72",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@73", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@74", "sub_pool4", "$@75",
  "pool_params", "pool_param", "pool_entry", "$@76", "user_context",
  "$@77", "comment", "$@78", "reservations", "$@79", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@80", "sub_reservation",
  "$@81", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@82", "server_hostname", "$@83",
  "boot_file_name", "$@84", "ip_address", "$@85", "ip_addresses", "$@86",
  "duid", "$@87", "hw_address", "$@88", "client_id_value", "$@89",
  "circuit_id_value", "$@90", "flex_id_value", "$@91", "hostname", "$@92",
  "reservation_client_classes", "$@93", "relay", "$@94", "relay_map",
  "client_classes", "$@95", "client_classes_list", "client_class_entry",
  "$@96", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@97",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@98",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@99", "control_socket_name", "$@100", "dhcp_ddns", "$@101",
  "sub_dhcp_ddns", "$@102", "dhcp_ddns_params", "dhcp_ddns_param",
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
       0,   254,   254,   254,   255,   255,   256,   256,   257,   257,
     258,   258,   259,   259,   260,   260,   261,   261,   262,   262,
     263,   263,   264,   264,   265,   265,   266,   266,   267,   267,
     275,   276,   277,   278,   279,   280,   281,   284,   289,   289,
     300,   303,   304,   307,   311,   318,   318,   325,   326,   329,
     333,   340,   340,   347,   348,   351,   355,   366,   376,   376,
     392,   393,   397,   398,   399,   400,   401,   402,   405,   405,
     420,   420,   429,   430,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   468,   473,   478,   483,   488,
     488,   496,   501,   507,   507,   518,   519,   522,   523,   524,
     525,   526,   527,   528,   531,   531,   540,   540,   550,   550,
     557,   558,   561,   561,   568,   570,   574,   580,   580,   592,
     592,   602,   603,   605,   607,   607,   625,   625,   637,   637,
     647,   648,   651,   652,   655,   655,   665,   666,   669,   670,
     671,   672,   673,   674,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   689,   689,   696,   697,
     698,   699,   702,   702,   710,   710,   718,   718,   726,   731,
     731,   739,   744,   749,   754,   759,   764,   769,   774,   774,
     782,   782,   790,   795,   800,   800,   810,   811,   814,   815,
     816,   817,   818,   821,   826,   831,   836,   841,   846,   846,
     856,   857,   860,   861,   864,   864,   874,   874,   884,   885,
     886,   889,   890,   893,   893,   901,   901,   909,   909,   920,
     921,   924,   925,   926,   927,   928,   929,   932,   937,   942,
     947,   952,   957,   965,   965,   978,   979,   982,   983,   990,
     990,  1016,  1016,  1027,  1028,  1032,  1033,  1034,  1035,  1036,
    1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,
    1047,  1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,
    1059,  1059,  1067,  1067,  1075,  1075,  1083,  1083,  1091,  1091,
    1099,  1099,  1107,  1107,  1115,  1115,  1125,  1125,  1132,  1133,
    1134,  1135,  1138,  1143,  1150,  1150,  1161,  1162,  1166,  1167,
    1170,  1170,  1178,  1179,  1182,  1183,  1184,  1185,  1186,  1187,
    1188,  1189,  1190,  1191,  1192,  1193,  1194,  1195,  1196,  1197,
    1198,  1199,  1206,  1206,  1219,  1219,  1228,  1229,  1232,  1233,
    1238,  1238,  1253,  1253,  1267,  1268,  1271,  1272,  1275,  1276,
    1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1287,  1289,
    1294,  1296,  1296,  1304,  1304,  1312,  1312,  1320,  1322,  1322,
    1330,  1339,  1339,  1351,  1352,  1357,  1358,  1363,  1363,  1375,
    1375,  1387,  1388,  1393,  1394,  1399,  1400,  1401,  1402,  1403,
    1404,  1405,  1406,  1407,  1410,  1412,  1412,  1420,  1422,  1424,
    1429,  1437,  1437,  1449,  1450,  1453,  1454,  1457,  1457,  1467,
    1467,  1477,  1478,  1481,  1482,  1483,  1484,  1485,  1486,  1487,
    1490,  1490,  1498,  1498,  1523,  1523,  1553,  1553,  1563,  1564,
    1567,  1568,  1571,  1571,  1580,  1580,  1589,  1590,  1593,  1594,
    1598,  1599,  1600,  1601,  1602,  1603,  1604,  1605,  1606,  1607,
    1608,  1609,  1610,  1611,  1612,  1615,  1615,  1623,  1623,  1631,
    1631,  1639,  1639,  1647,  1647,  1657,  1657,  1665,  1665,  1673,
    1673,  1681,  1681,  1689,  1689,  1697,  1697,  1705,  1705,  1718,
    1718,  1728,  1729,  1735,  1735,  1745,  1746,  1749,  1749,  1759,
    1760,  1763,  1764,  1767,  1768,  1769,  1770,  1771,  1772,  1773,
    1774,  1775,  1776,  1777,  1780,  1782,  1782,  1790,  1799,  1806,
    1806,  1816,  1817,  1820,  1821,  1822,  1823,  1824,  1827,  1827,
    1835,  1835,  1845,  1845,  1857,  1857,  1867,  1868,  1871,  1872,
    1873,  1874,  1875,  1876,  1877,  1878,  1879,  1880,  1881,  1882,
    1883,  1884,  1885,  1886,  1887,  1888,  1889,  1892,  1897,  1897,
    1905,  1905,  1913,  1918,  1918,  1926,  1931,  1936,  1936,  1944,
    1945,  1948,  1948,  1956,  1961,  1966,  1971,  1971,  1979,  1982,
    1985,  1988,  1991,  1997,  1997,  2005,  2005,  2013,  2013,  2024,
    2024,  2031,  2031,  2038,  2038,  2045,  2045,  2054,  2054,  2065,
    2065,  2075,  2076,  2080,  2081,  2084,  2084,  2099,  2099,  2109,
    2109,  2120,  2121,  2125,  2129,  2129,  2141,  2142,  2146,  2146,
    2154,  2155,  2158,  2159,  2160,  2161,  2162,  2163,  2164,  2167,
    2172,  2172,  2180,  2180,  2190,  2191,  2194,  2194,  2202,  2203,
    2206,  2207,  2208,  2209,  2212,  2212,  2220,  2225,  2230
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
#line 4896 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2235 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
