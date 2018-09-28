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
      case 185: // value
      case 189: // map_value
      case 227: // socket_type
      case 230: // outbound_interface_value
      case 252: // db_type
      case 336: // hr_mode
      case 484: // ncr_protocol_value
      case 492: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 168: // "boolean"
        value.move< bool > (that.value);
        break;

      case 167: // "floating point"
        value.move< double > (that.value);
        break;

      case 166: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 165: // "constant string"
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
      case 185: // value
      case 189: // map_value
      case 227: // socket_type
      case 230: // outbound_interface_value
      case 252: // db_type
      case 336: // hr_mode
      case 484: // ncr_protocol_value
      case 492: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 168: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 167: // "floating point"
        value.copy< double > (that.value);
        break;

      case 166: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 165: // "constant string"
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
            case 165: // "constant string"

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 166: // "integer"

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 167: // "floating point"

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 168: // "boolean"

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 185: // value

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 189: // map_value

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 227: // socket_type

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 230: // outbound_interface_value

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 252: // db_type

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 336: // hr_mode

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 484: // ncr_protocol_value

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 492: // replace_client_name_value

#line 244 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 185: // value
      case 189: // map_value
      case 227: // socket_type
      case 230: // outbound_interface_value
      case 252: // db_type
      case 336: // hr_mode
      case 484: // ncr_protocol_value
      case 492: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 168: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 167: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 166: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 165: // "constant string"
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
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 310 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 317 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 332 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 350 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 354 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 380 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 404 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1219 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1289 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 688 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 689 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 694 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 885 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 1006 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1122 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
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
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2407 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2437 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2557 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2567 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2595 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2723 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2777 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2835 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1789 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1801 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1935 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1969 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1972 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1975 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1981 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3336 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2044 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3365 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2074 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2124 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2136 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3517 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3547 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 641:
#line 2202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 642:
#line 2204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 643:
#line 2210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 644:
#line 2215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3600 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3604 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -805;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     125,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,    40,    27,    39,    57,    61,
      63,   123,   143,   157,   163,   182,   189,   213,   223,   227,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,    27,   -93,
      18,    60,    79,   174,   -22,   110,    73,   147,   360,   -43,
     444,   -23,    12,  -805,   142,   171,   194,   232,   244,  -805,
    -805,  -805,  -805,  -805,   270,  -805,    46,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,   296,   305,  -805,
    -805,  -805,  -805,  -805,  -805,   311,   315,   319,   323,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
     325,  -805,  -805,  -805,   137,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   331,  -805,
     141,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,   349,   366,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,   148,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,   172,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
     249,   257,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,   286,  -805,  -805,   367,  -805,  -805,
    -805,   370,  -805,  -805,   295,   334,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   371,
     373,  -805,  -805,  -805,  -805,   318,   375,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   178,
    -805,  -805,  -805,   376,  -805,  -805,   377,  -805,   381,   383,
    -805,  -805,   384,   386,   387,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,   179,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,   210,  -805,  -805,  -805,  -805,   211,  -805,  -805,  -805,
      27,    27,  -805,   233,   388,   396,   400,   402,   405,  -805,
      18,  -805,    12,   407,   409,   412,   262,   263,   428,   432,
     433,   434,   438,   439,   278,   279,   280,   281,   445,   446,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   285,
     460,   461,    60,  -805,   464,   465,   466,   303,    79,  -805,
     468,   469,   470,   471,   472,   473,   474,   314,   332,   479,
     495,   497,   498,   174,  -805,   499,   -22,  -805,   500,   501,
     502,   503,   506,   507,   508,   509,  -805,   110,  -805,   510,
     512,   356,   519,   520,   522,   361,  -805,   147,   524,   362,
     363,  -805,   360,   528,   529,    38,  -805,   369,   530,   534,
     378,   535,   379,   380,   537,   538,   382,   385,   390,   539,
     545,   547,   548,   444,  -805,   550,   -23,  -805,   552,    12,
    -805,  -805,  -805,   555,   553,   570,    27,    27,    27,  -805,
     235,   571,   572,   573,  -805,  -805,   418,   419,   420,   579,
     580,   583,  -805,  -805,  -805,  -805,   584,   585,   586,   587,
     588,   429,   591,   592,   593,   594,   595,  -805,   596,   597,
    -805,   600,   207,   217,  -805,  -805,   435,   436,   441,   602,
     443,   448,   449,  -805,  -805,    26,   600,   450,   603,  -805,
     462,  -805,   600,   463,   467,   475,   476,   477,   478,   480,
    -805,   481,   482,  -805,   483,   484,   485,  -805,  -805,   486,
    -805,  -805,  -805,   487,    27,  -805,  -805,   488,   489,  -805,
     490,  -805,  -805,    24,   491,  -805,  -805,  -805,   -29,   492,
     493,   494,  -805,   606,  -805,   611,  -805,    27,    60,   -23,
    -805,  -805,  -805,  -805,    12,    79,   598,  -805,  -805,  -805,
     447,   447,   610,   612,   613,   615,   617,  -805,  -805,  -805,
      65,   618,   619,   622,    17,     4,   444,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   623,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   191,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,   624,   610,  -805,   253,   255,   256,   264,
    -805,   290,  -805,  -805,  -805,  -805,  -805,  -805,   589,   614,
     629,   630,   631,  -805,  -805,   632,   633,   634,   635,   640,
    -805,   298,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
     299,  -805,   650,   657,  -805,  -805,   655,   659,  -805,  -805,
     658,   660,  -805,  -805,   661,   662,  -805,  -805,   663,   665,
    -805,  -805,  -805,  -805,  -805,  -805,    77,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,    89,  -805,  -805,   664,   668,  -805,
    -805,   666,   670,  -805,   671,   672,   673,   674,   675,   676,
     313,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,   322,  -805,  -805,  -805,   330,   516,  -805,
     677,   679,  -805,  -805,  -805,  -805,   678,  -805,    93,  -805,
     681,  -805,  -805,  -805,  -805,   680,   598,  -805,   684,   685,
     686,   687,   526,   517,   527,   531,   532,   690,   691,   536,
     540,   541,   542,   533,   447,  -805,  -805,   447,  -805,   610,
     174,  -805,   612,   147,  -805,   613,   360,  -805,   615,   243,
    -805,   617,    65,  -805,   392,   618,  -805,   110,  -805,   619,
     -43,  -805,   622,   543,   544,   546,   549,   551,   554,    17,
    -805,   692,   693,     4,  -805,  -805,  -805,   694,   700,   -22,
    -805,   623,   701,  -805,   167,   624,  -805,  -805,   556,  -805,
     328,   557,   558,   559,  -805,  -805,  -805,  -805,  -805,   560,
     561,  -805,  -805,  -805,  -805,  -805,  -805,   333,  -805,   341,
    -805,   696,  -805,   703,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,   342,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   709,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   706,   713,
    -805,  -805,  -805,  -805,  -805,   710,  -805,   344,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,   562,   563,  -805,  -805,
     564,   348,  -805,   600,  -805,   715,  -805,  -805,  -805,  -805,
    -805,   351,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,   243,  -805,   726,   565,  -805,   392,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,   727,   566,   730,   167,  -805,
    -805,   574,  -805,  -805,   669,  -805,   575,  -805,  -805,   728,
    -805,  -805,   126,  -805,   -44,   728,  -805,  -805,   732,   733,
     734,   357,  -805,  -805,  -805,  -805,  -805,  -805,   737,   577,
     576,   582,   -44,  -805,   578,  -805,  -805,  -805,  -805,  -805
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   121,     9,   258,    11,
     416,    13,   441,    15,   341,    17,   349,    19,   386,    21,
     223,    23,   531,    25,   606,    27,   596,    29,    47,    41,
       0,     0,     0,     0,     0,   443,     0,   351,   388,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     604,   586,   588,   590,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   592,   594,   110,   136,     0,     0,   462,
     464,   466,   134,   143,   145,     0,     0,     0,     0,   250,
     339,   378,   311,   429,   431,   201,   490,   433,   215,   234,
       0,   516,   529,   103,     0,    72,    74,    75,    76,    77,
      93,    94,    80,    81,   100,    82,    83,    84,    88,    89,
      78,    79,    86,    87,    98,    99,   101,    95,    96,    97,
      85,    90,    91,    92,   102,   123,   125,   129,     0,   120,
       0,   112,   114,   115,   116,   117,   118,   119,   289,   291,
     293,   408,   287,   295,   297,     0,     0,   303,   301,   299,
     486,   286,   262,   263,   264,   277,     0,   260,   267,   281,
     282,   283,   268,   269,   272,   273,   275,   270,   271,   265,
     266,   284,   285,   274,   278,   279,   280,   276,   427,   426,
     422,   423,   421,     0,   418,   420,   424,   425,   484,   472,
     474,   478,   476,   482,   480,   468,   461,   455,   459,   460,
       0,   444,   445,   456,   457,   458,   452,   447,   453,   449,
     450,   451,   454,   448,     0,   368,   186,     0,   372,   370,
     375,     0,   364,   365,     0,   352,   353,   355,   367,   356,
     357,   358,   374,   359,   360,   361,   362,   363,   402,     0,
       0,   400,   401,   404,   405,     0,   389,   390,   392,   393,
     394,   395,   396,   397,   398,   399,   230,   232,   227,     0,
     225,   228,   229,     0,   555,   557,     0,   560,     0,     0,
     564,   568,     0,     0,     0,   573,   580,   582,   584,   553,
     551,   552,     0,   533,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     611,     0,   608,   610,   602,   601,     0,   598,   600,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    71,     0,     0,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   259,     0,     0,   417,     0,     0,
       0,     0,     0,     0,     0,     0,   442,     0,   342,     0,
       0,     0,     0,     0,     0,     0,   350,     0,     0,     0,
       0,   387,     0,     0,     0,     0,   224,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   532,     0,     0,   607,     0,     0,
     597,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,   108,   109,     0,     0,     0,     0,
       0,     0,   104,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   515,     0,     0,
      73,     0,     0,     0,   133,   113,     0,     0,     0,     0,
       0,     0,     0,   309,   310,     0,     0,     0,     0,   261,
       0,   419,     0,     0,     0,     0,     0,     0,     0,     0,
     446,     0,     0,   366,     0,     0,     0,   377,   354,     0,
     406,   407,   391,     0,     0,   226,   554,     0,     0,   559,
       0,   562,   563,     0,     0,   570,   571,   572,     0,     0,
       0,     0,   534,     0,   609,     0,   599,     0,     0,     0,
     587,   589,   591,   593,     0,     0,     0,   463,   465,   467,
       0,     0,   147,   252,   343,   380,   313,    40,   430,   432,
       0,     0,   435,   217,     0,     0,     0,    51,   124,   127,
     128,   126,   131,   132,   130,   290,   292,   294,   410,   288,
     296,   298,   305,   306,   307,   308,   304,   302,   300,     0,
     428,   485,   473,   475,   479,   477,   483,   481,   469,   369,
     187,   373,   371,   376,   403,   231,   233,   556,   558,   561,
     566,   567,   565,   569,   575,   576,   577,   578,   579,   574,
     581,   583,   585,     0,   147,    44,     0,     0,     0,     0,
     141,     0,   138,   140,   173,   179,   181,   183,     0,     0,
       0,     0,     0,   195,   197,     0,     0,     0,     0,     0,
     172,     0,   153,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   168,   169,   170,   165,   171,   166,   167,
       0,   151,     0,   148,   149,   256,     0,   253,   254,   347,
       0,   344,   345,   384,     0,   381,   382,   317,     0,   314,
     315,   210,   211,   212,   213,   214,     0,   203,   205,   206,
     207,   208,   209,   494,     0,   492,   439,     0,   436,   437,
     221,     0,   218,   219,     0,     0,     0,     0,     0,     0,
       0,   236,   238,   239,   240,   241,   242,   243,   525,   527,
     524,   522,   523,     0,   518,   520,   521,     0,    53,   414,
       0,   411,   412,   470,   488,   489,     0,   615,     0,   613,
       0,    69,   605,   595,   111,     0,     0,   137,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   144,     0,   146,     0,
       0,   251,     0,   351,   340,     0,   388,   379,     0,     0,
     312,     0,     0,   202,   496,     0,   491,   443,   434,     0,
       0,   216,     0,     0,     0,     0,     0,     0,     0,     0,
     235,     0,     0,     0,   517,   530,    55,     0,    54,     0,
     409,     0,     0,   487,     0,     0,   612,   603,     0,   139,
       0,     0,     0,     0,   185,   188,   189,   190,   191,     0,
       0,   199,   200,   192,   193,   194,   154,     0,   150,     0,
     255,     0,   346,     0,   383,   338,   335,   324,   325,   327,
     321,   322,   323,   333,   334,   332,     0,   319,   326,   336,
     337,   328,   329,   330,   331,   316,   204,   512,     0,   510,
     511,   503,   504,   508,   509,   505,   506,   507,     0,   497,
     498,   500,   501,   502,   493,     0,   438,     0,   220,   244,
     245,   246,   247,   248,   249,   237,     0,     0,   519,    52,
       0,     0,   413,     0,   629,     0,   627,   625,   619,   623,
     624,     0,   617,   621,   622,   620,   614,   142,   175,   176,
     177,   178,   174,   180,   182,   184,   196,   198,   152,   257,
     348,   385,     0,   318,     0,     0,   495,     0,   440,   222,
     526,   528,    56,   415,   471,     0,     0,     0,     0,   616,
     320,     0,   514,   499,     0,   626,     0,   618,   513,     0,
     628,   633,     0,   631,     0,     0,   630,   641,     0,     0,
       0,     0,   635,   637,   638,   639,   640,   632,     0,     0,
       0,     0,     0,   634,     0,   643,   644,   645,   636,   642
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,   -37,  -805,   166,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -505,  -805,  -805,
    -805,   -70,  -805,  -805,  -805,   389,  -805,  -805,  -805,  -805,
     168,   359,   -47,   -18,   -11,  -805,  -805,     8,  -805,  -805,
     169,   354,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   -41,  -805,
    -805,  -805,  -805,  -805,  -805,    94,  -805,   -62,  -805,  -578,
     -51,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,   -48,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   -55,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,   -57,
    -805,  -805,  -805,   -56,   327,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,   -75,  -805,  -805,  -805,  -805,  -805,  -805,  -804,
    -805,  -805,  -805,   -35,  -805,  -805,  -805,   -32,   395,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -794,  -805,  -805,
    -805,   -68,  -805,   -15,  -805,  -792,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,   -39,  -805,  -805,  -185,   -65,  -805,
    -805,  -805,  -805,  -805,   -27,  -805,  -805,  -805,    -8,  -805,
     368,  -805,   -66,  -805,  -805,  -805,  -805,  -805,   -60,  -805,
    -805,  -805,  -805,  -805,   -17,  -805,  -805,  -805,   -28,  -805,
    -805,  -805,   -13,  -805,   391,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,   -36,  -805,  -805,  -805,
     -33,   416,  -805,  -805,   -58,  -805,   -30,  -805,   -40,  -805,
    -805,  -805,     6,  -805,  -805,  -805,     3,  -805,   414,   -10,
    -805,     1,  -805,     2,  -805,   214,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -791,  -805,  -805,  -805,  -805,  -805,    11,
    -805,  -805,  -805,  -140,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,    -5,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,   245,   393,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,  -805,
    -805,  -339,   394,  -805,  -805,  -805,  -805,  -805,  -805,   271,
     398,  -805,  -805,  -805,   -16,  -805,  -805,  -146,  -805,  -805,
    -805,  -805,  -805,  -805,  -162,  -805,  -805,  -178,  -805,  -805,
    -805,  -805,  -805
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     598,    87,    88,    41,    68,    84,    85,   608,   778,   857,
     858,   345,    43,    70,    96,    97,    98,   354,    45,    71,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   364,
     170,   171,    47,    72,   172,   394,   173,   395,   611,   174,
     396,   614,   175,   143,   371,   144,   365,   671,   672,   673,
     795,   145,   372,   146,   373,   712,   713,   714,   817,   691,
     692,   693,   798,   972,   694,   799,   695,   800,   696,   801,
     697,   698,   430,   699,   700,   701,   702,   703,   704,   705,
     706,   807,   707,   808,   708,   709,   147,   384,   736,   737,
     738,   739,   740,   741,   742,   148,   387,   751,   752,   753,
     840,    61,    79,   299,   300,   301,   443,   302,   444,   149,
     388,   760,   761,   762,   763,   764,   765,   766,   767,   150,
     378,   716,   717,   718,   820,    49,    73,   196,   197,   198,
     404,   199,   400,   200,   401,   201,   402,   202,   405,   203,
     406,   204,   411,   205,   410,   206,   409,   626,   207,   208,
     151,   381,   728,   729,   730,   829,   906,   907,   152,   379,
      55,    76,   720,   721,   722,   823,    57,    77,   264,   265,
     266,   267,   268,   269,   270,   429,   271,   433,   272,   432,
     273,   274,   434,   275,   153,   380,   724,   725,   726,   826,
      59,    78,   285,   286,   287,   288,   289,   438,   290,   291,
     292,   293,   210,   403,   780,   781,   782,   859,    51,    74,
     223,   224,   225,   415,   154,   382,   155,   383,   156,   386,
     747,   748,   749,   837,    53,    75,   240,   241,   242,   157,
     368,   158,   369,   159,   370,   246,   425,   785,   862,   247,
     419,   248,   420,   249,   422,   250,   421,   251,   424,   252,
     423,   253,   418,   217,   412,   786,   160,   385,   744,   745,
     834,   928,   929,   930,   931,   932,   984,   933,   161,   162,
     390,   773,   774,   775,   851,   776,   852,   163,   391,    63,
      80,   322,   323,   324,   325,   448,   326,   449,   327,   328,
     451,   329,   330,   331,   454,   652,   332,   455,   333,   334,
     335,   336,   459,   659,   337,   460,   338,   461,   339,   462,
      99,   356,   100,   357,   101,   358,   164,   362,   363,    67,
      82,   346,   347,   348,   468,   102,   355,    65,    81,   341,
     342,   343,   465,   788,   789,   864,   961,   962,   963,   964,
     997,   965,   995,  1012,  1013,  1014,  1021,  1022,  1023,  1028,
    1024,  1025,  1026
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   133,   169,   191,   219,   236,   220,   262,   281,   298,
     319,   254,   283,   710,   176,   211,   226,   238,   284,   276,
     294,   627,   320,   480,   344,   901,   192,   631,    89,   263,
     282,    83,    31,   213,    32,   902,    33,   905,   914,   121,
      30,   650,   177,   212,   227,   239,    42,   277,   295,   360,
     321,   218,   123,   124,   361,   193,   209,   222,   237,   221,
     296,   297,   194,   214,    44,   243,   188,   103,    46,   189,
      48,   104,    86,   105,   215,   216,   244,   245,   123,   124,
     832,   195,   106,   833,   107,   108,   109,   110,   111,   112,
     113,   114,   835,   165,   166,   836,   865,   167,  1017,   866,
     168,  1018,  1019,  1020,   654,   655,   656,   657,   622,   623,
     624,   625,   115,   116,   117,   118,   119,   340,   768,   769,
     120,   121,    94,   754,   755,   756,   757,   758,   759,  1015,
      50,   122,  1016,   120,   123,   124,   109,   110,   111,   658,
     392,   296,   297,    94,   398,   393,   125,   126,   349,   399,
      52,   413,   127,   123,   124,   651,   414,    90,   731,   732,
     733,   734,   128,   735,    54,   129,    91,    92,    93,    94,
      56,   121,   130,   131,   350,   416,   132,    94,   901,   255,
     417,   445,   463,    94,   123,   124,   446,   464,   902,    58,
     905,   914,    34,    35,    36,    37,    60,   228,   351,   108,
     109,   110,   111,   229,   230,   231,   232,   233,   234,   256,
     235,   257,   258,   466,   469,   259,   260,   261,   467,   470,
      62,   123,   124,   609,   610,    94,   115,   116,   117,   256,
      64,   178,   179,   180,    66,   121,   612,   613,   469,   887,
     352,   123,   124,   583,    94,   668,   181,   353,   123,   124,
     182,   183,   184,   185,   186,   187,   392,   426,   466,   469,
     427,   791,   188,   792,   793,   189,   127,   398,   108,   109,
     110,   111,   794,   190,   359,    94,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      95,   235,   783,   796,   428,   115,   116,   117,   797,   119,
     366,   814,   814,   436,   121,   256,   815,   816,   954,   367,
     955,   956,    94,   471,   472,   374,   849,   123,   124,   375,
     183,   850,   133,   376,   187,   853,   441,   377,   169,   389,
     854,   188,    94,   463,   189,   397,   814,   437,   855,    94,
     176,   978,   190,   191,   413,   982,   219,   445,   220,   979,
     983,   416,   989,   407,   998,   211,   993,   236,   226,   999,
    1032,   968,   969,   970,   971,  1033,   192,   262,   177,   238,
     408,   431,   281,   213,   435,   439,   283,   440,   442,   276,
     447,   450,   284,   212,   294,   452,   227,   453,   456,   263,
     457,   458,   474,   319,   282,   193,   209,   239,   473,   222,
     475,   221,   194,   214,   476,   320,   477,   277,    94,   478,
     237,   481,   295,   482,   215,   216,   483,   243,   109,   110,
     111,   195,   256,   278,   257,   258,   279,   280,   244,   245,
     484,   485,   486,   321,   123,   124,   487,   488,   489,   580,
     581,   582,   490,   491,   492,   493,   494,   495,   994,   496,
     497,   507,   120,   121,   256,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   508,   509,   123,   124,   511,   512,
     513,   514,   516,   517,   518,   519,   520,   521,   522,   674,
     523,   917,   918,   525,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   687,   688,   689,   526,
     524,   527,   528,   530,   532,   533,   534,   535,   133,   256,
     536,   537,   538,   539,   541,   169,   542,   646,   123,   124,
     690,   690,   543,   544,   545,    94,   546,   176,   549,   547,
     550,   551,   553,   554,   557,   770,   319,   556,   558,   560,
     665,   563,   564,   568,   559,   561,   562,   771,   320,   569,
     565,   570,   571,   566,   573,   177,   575,    94,   567,   577,
     578,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   772,   321,   579,   584,   585,
     586,   317,   318,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   802,   599,    32,   600,   601,   602,   603,
     615,   616,   604,   605,   606,   607,   617,   618,   619,    94,
     629,   663,    94,   620,   621,   628,   664,   711,   803,   715,
     719,   670,   723,   653,   727,   743,   746,   630,   632,   750,
     779,   787,   633,   804,   805,   806,   809,   810,   811,   812,
     634,   635,   636,   637,   813,   638,   639,   640,   641,   642,
     643,   644,   645,   647,   648,   649,   818,   660,   661,   662,
     819,   821,   822,   825,   824,   828,   597,   827,   831,   830,
     838,   839,   841,   842,  1009,   843,   844,   845,   846,   847,
     848,   856,   861,   860,   868,   875,   863,   867,   870,   871,
     872,   873,   874,   876,   879,   880,   946,   947,   878,   877,
     949,   885,   881,   950,   980,   953,   882,   883,   884,   939,
     940,   981,   941,   985,   986,   942,   987,   943,   988,   996,
     944,   967,   973,   974,   975,   976,   977,   990,   991,   992,
    1001,  1004,  1005,  1002,  1006,  1011,  1029,  1030,  1031,  1008,
    1010,  1034,  1036,  1039,   690,  1035,   666,   690,  1037,   479,
     191,   510,   515,   262,   669,   869,   281,   888,   790,   895,
     283,   903,   211,   886,   919,   276,   284,   236,   294,   921,
     298,   909,   555,   192,   945,   263,   923,   916,   282,   238,
     213,   900,   896,   770,   937,   938,   920,   890,   889,   219,
     212,   220,   915,   277,   957,   771,   295,  1000,   892,   910,
     894,   226,   193,   209,   924,   548,   959,   239,   529,   194,
     214,   897,   908,   893,   904,   891,   958,   922,   898,   911,
     237,   215,   216,   772,   925,   952,   951,   243,   195,   227,
     912,   913,   531,   552,   960,   926,   927,   899,   244,   245,
     935,   540,   222,   784,   221,   936,   934,  1003,   948,   966,
     667,   777,  1007,  1027,  1038,     0,   572,     0,     0,     0,
       0,     0,     0,   576,   574,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   895,     0,   903,     0,     0,   919,     0,     0,
       0,     0,   921,     0,   909,     0,     0,     0,   957,   923,
       0,     0,     0,     0,   900,   896,     0,     0,     0,   920,
     959,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     958,     0,   910,     0,     0,     0,     0,   924,     0,     0,
       0,     0,     0,     0,   897,   908,     0,   904,   960,     0,
     922,   898,   911,     0,     0,     0,     0,   925,     0,     0,
       0,     0,     0,   912,   913,     0,     0,     0,   926,   927,
     899
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    76,    78,   591,    72,    73,    74,    75,    78,    77,
      78,   526,    80,   362,    12,   829,    73,   532,    10,    77,
      78,    68,     5,    73,     7,   829,     9,   829,   829,    61,
       0,    17,    72,    73,    74,    75,     7,    77,    78,     3,
      80,    73,    74,    75,     8,    73,    73,    74,    75,    74,
     103,   104,    73,    73,     7,    75,    88,     7,     7,    91,
       7,    11,   165,    13,    73,    73,    75,    75,    74,    75,
       3,    73,    22,     6,    24,    25,    26,    27,    28,    29,
      30,    31,     3,    14,    15,     6,     3,    18,   142,     6,
      21,   145,   146,   147,   133,   134,   135,   136,    82,    83,
      84,    85,    52,    53,    54,    55,    56,   140,   114,   115,
      60,    61,   165,   106,   107,   108,   109,   110,   111,     3,
       7,    71,     6,    60,    74,    75,    26,    27,    28,   168,
       3,   103,   104,   165,     3,     8,    86,    87,     6,     8,
       7,     3,    92,    74,    75,   131,     8,   139,    93,    94,
      95,    96,   102,    98,     7,   105,   148,   149,   150,   165,
       7,    61,   112,   113,     3,     3,   116,   165,   982,    32,
       8,     3,     3,   165,    74,    75,     8,     8,   982,     7,
     982,   982,   165,   166,   167,   168,     7,    87,     4,    25,
      26,    27,    28,    93,    94,    95,    96,    97,    98,    62,
     100,    64,    65,     3,     3,    68,    69,    70,     8,     8,
       7,    74,    75,    16,    17,   165,    52,    53,    54,    62,
       7,    57,    58,    59,     7,    61,    19,    20,     3,   817,
       8,    74,    75,     8,   165,   584,    72,     3,    74,    75,
      76,    77,    78,    79,    80,    81,     3,     8,     3,     3,
       3,     8,    88,     8,     8,    91,    92,     3,    25,    26,
      27,    28,     8,    99,     4,   165,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     360,   100,   101,     3,     8,    52,    53,    54,     8,    56,
       4,     3,     3,     8,    61,    62,     8,     8,   141,     4,
     143,   144,   165,   350,   351,     4,     3,    74,    75,     4,
      77,     8,   392,     4,    81,     3,     8,     4,   398,     4,
       8,    88,   165,     3,    91,     4,     3,     3,     8,   165,
     398,     8,    99,   413,     3,     3,   416,     3,   416,     8,
       8,     3,     8,     4,     3,   413,     8,   427,   416,     8,
       3,    33,    34,    35,    36,     8,   413,   437,   398,   427,
       4,     4,   442,   413,     4,     4,   442,     4,     3,   437,
       4,     4,   442,   413,   442,     4,   416,     4,     4,   437,
       4,     4,     4,   463,   442,   413,   413,   427,   165,   416,
       4,   416,   413,   413,     4,   463,     4,   437,   165,     4,
     427,     4,   442,     4,   413,   413,     4,   427,    26,    27,
      28,   413,    62,    63,    64,    65,    66,    67,   427,   427,
     168,   168,     4,   463,    74,    75,     4,     4,     4,   476,
     477,   478,     4,     4,   166,   166,   166,   166,   953,     4,
       4,   166,    60,    61,    62,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    74,    75,     4,     4,
       4,   168,     4,     4,     4,     4,     4,     4,     4,    32,
     166,    89,    90,     4,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,     4,
     168,     4,     4,     4,     4,     4,     4,     4,   578,    62,
       4,     4,     4,     4,     4,   585,     4,   554,    74,    75,
     590,   591,   166,     4,     4,   165,     4,   585,     4,   168,
     168,   168,     4,     4,     4,   605,   606,   168,     4,     4,
     577,     4,     4,     4,   166,   166,   166,   605,   606,     4,
     168,     4,     4,   168,     4,   585,     4,   165,   168,     4,
       7,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   605,   606,     7,     7,     7,
       7,   137,   138,   165,   165,   165,     7,     7,     5,     5,
       5,     5,     5,     4,   165,     7,     5,     5,     5,     5,
     165,   165,     7,     7,     7,     5,   165,     5,   165,   165,
       7,     5,   165,   165,   165,   165,     5,     7,     4,     7,
       7,    23,     7,   132,     7,     7,     7,   165,   165,     7,
       7,     7,   165,     4,     4,     4,     4,     4,     4,     4,
     165,   165,   165,   165,     4,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,     6,   165,   165,   165,
       3,     6,     3,     3,     6,     3,   500,     6,     3,     6,
       6,     3,     6,     3,     5,     4,     4,     4,     4,     4,
       4,   165,     3,     6,     4,   168,     8,     6,     4,     4,
       4,     4,   166,   166,     4,     4,     4,     4,   166,   168,
       6,   168,   166,     3,     8,     4,   166,   166,   166,   166,
     166,     8,   166,     4,     8,   166,     3,   166,     8,     4,
     166,   165,   165,   165,   165,   165,   165,   165,   165,   165,
       4,     4,   166,   168,     4,     7,     4,     4,     4,   165,
     165,     4,   166,   165,   814,   168,   578,   817,   166,   360,
     820,   392,   398,   823,   585,   796,   826,   819,   664,   829,
     826,   829,   820,   814,   834,   823,   826,   837,   826,   834,
     840,   829,   445,   820,   849,   823,   834,   832,   826,   837,
     820,   829,   829,   853,   840,   842,   834,   822,   820,   859,
     820,   859,   831,   823,   864,   853,   826,   982,   825,   829,
     828,   859,   820,   820,   834,   437,   864,   837,   413,   820,
     820,   829,   829,   826,   829,   823,   864,   834,   829,   829,
     837,   820,   820,   853,   834,   861,   859,   837,   820,   859,
     829,   829,   416,   442,   864,   834,   834,   829,   837,   837,
     837,   427,   859,   629,   859,   839,   835,   987,   853,   865,
     579,   606,   998,  1015,  1032,    -1,   463,    -1,    -1,    -1,
      -1,    -1,    -1,   469,   466,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   982,    -1,   982,    -1,    -1,   987,    -1,    -1,
      -1,    -1,   987,    -1,   982,    -1,    -1,    -1,   998,   987,
      -1,    -1,    -1,    -1,   982,   982,    -1,    -1,    -1,   987,
     998,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     998,    -1,   982,    -1,    -1,    -1,    -1,   987,    -1,    -1,
      -1,    -1,    -1,    -1,   982,   982,    -1,   982,   998,    -1,
     987,   982,   982,    -1,    -1,    -1,    -1,   987,    -1,    -1,
      -1,    -1,    -1,   982,   982,    -1,    -1,    -1,   987,   987,
     982
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
       0,     5,     7,     9,   165,   166,   167,   168,   185,   186,
     187,   192,     7,   201,     7,   207,     7,   221,     7,   314,
       7,   397,     7,   413,     7,   349,     7,   355,     7,   379,
       7,   290,     7,   468,     7,   516,     7,   508,   193,   188,
     202,   208,   222,   315,   398,   414,   350,   356,   380,   291,
     469,   517,   509,   185,   194,   195,   165,   190,   191,    10,
     139,   148,   149,   150,   165,   200,   203,   204,   205,   499,
     501,   503,   514,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    52,    53,    54,    55,    56,
      60,    61,    71,    74,    75,    86,    87,    92,   102,   105,
     112,   113,   116,   200,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   232,   234,   240,   242,   275,   284,   298,
     308,   339,   347,   373,   403,   405,   407,   418,   420,   422,
     445,   457,   458,   466,   505,    14,    15,    18,    21,   200,
     219,   220,   223,   225,   228,   231,   403,   405,    57,    58,
      59,    72,    76,    77,    78,    79,    80,    81,    88,    91,
      99,   200,   211,   212,   213,   216,   316,   317,   318,   320,
     322,   324,   326,   328,   330,   332,   334,   337,   338,   373,
     391,   403,   405,   407,   418,   420,   422,   442,    73,   200,
     330,   332,   373,   399,   400,   401,   403,   405,    87,    93,
      94,    95,    96,    97,    98,   100,   200,   373,   403,   405,
     415,   416,   417,   418,   420,   422,   424,   428,   430,   432,
     434,   436,   438,   440,   347,    32,    62,    64,    65,    68,
      69,    70,   200,   260,   357,   358,   359,   360,   361,   362,
     363,   365,   367,   369,   370,   372,   403,   405,    63,    66,
      67,   200,   260,   361,   367,   381,   382,   383,   384,   385,
     387,   388,   389,   390,   403,   405,   103,   104,   200,   292,
     293,   294,   296,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   137,   138,   200,
     403,   405,   470,   471,   472,   473,   475,   477,   478,   480,
     481,   482,   485,   487,   488,   489,   490,   493,   495,   497,
     140,   518,   519,   520,    12,   200,   510,   511,   512,     6,
       3,     4,     8,     3,   206,   515,   500,   502,   504,     4,
       3,     8,   506,   507,   218,   235,     4,     4,   419,   421,
     423,   233,   241,   243,     4,     4,     4,     4,   309,   348,
     374,   340,   404,   406,   276,   446,   408,   285,   299,     4,
     459,   467,     3,     8,   224,   226,   229,     4,     3,     8,
     321,   323,   325,   392,   319,   327,   329,     4,     4,   335,
     333,   331,   443,     3,     8,   402,     3,     8,   441,   429,
     431,   435,   433,   439,   437,   425,     8,     3,     8,   364,
     261,     4,   368,   366,   371,     4,     8,     3,   386,     4,
       4,     8,     3,   295,   297,     3,     8,     4,   474,   476,
       4,   479,     4,     4,   483,   486,     4,     4,     4,   491,
     494,   496,   498,     3,     8,   521,     3,     8,   513,     3,
       8,   185,   185,   165,     4,     4,     4,     4,     4,   204,
     510,     4,     4,     4,   168,   168,     4,     4,     4,     4,
       4,     4,   166,   166,   166,   166,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   166,     4,     4,
     210,     4,     4,     4,   168,   220,     4,     4,     4,     4,
       4,     4,     4,   166,   168,     4,     4,     4,     4,   317,
       4,   400,     4,     4,     4,     4,     4,     4,     4,     4,
     417,     4,     4,   166,     4,     4,     4,   168,   359,     4,
     168,   168,   383,     4,     4,   293,   168,     4,     4,   166,
       4,   166,   166,     4,     4,   168,   168,   168,     4,     4,
       4,     4,   471,     4,   519,     4,   511,     4,     7,     7,
     185,   185,   185,     8,     7,     7,     7,   165,   165,   165,
       7,     7,     5,     5,     5,     5,     5,   187,   189,   165,
       5,     5,     5,     5,     7,     7,     7,     5,   196,    16,
      17,   227,    19,    20,   230,   165,   165,   165,     5,   165,
     165,   165,    82,    83,    84,    85,   336,   196,   165,     7,
     165,   196,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   185,   165,   165,   165,
      17,   131,   484,   132,   133,   134,   135,   136,   168,   492,
     165,   165,   165,     5,     5,   185,   209,   518,   510,   219,
      23,   236,   237,   238,    32,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
     200,   248,   249,   250,   253,   255,   257,   259,   260,   262,
     263,   264,   265,   266,   267,   268,   269,   271,   273,   274,
     248,     7,   244,   245,   246,     7,   310,   311,   312,     7,
     351,   352,   353,     7,   375,   376,   377,     7,   341,   342,
     343,    93,    94,    95,    96,    98,   277,   278,   279,   280,
     281,   282,   283,     7,   447,   448,     7,   409,   410,   411,
       7,   286,   287,   288,   106,   107,   108,   109,   110,   111,
     300,   301,   302,   303,   304,   305,   306,   307,   114,   115,
     200,   403,   405,   460,   461,   462,   464,   470,   197,     7,
     393,   394,   395,   101,   424,   426,   444,     7,   522,   523,
     244,     8,     8,     8,     8,   239,     3,     8,   251,   254,
     256,   258,     4,     4,     4,     4,     4,   270,   272,     4,
       4,     4,     4,     4,     3,     8,     8,   247,     6,     3,
     313,     6,     3,   354,     6,     3,   378,     6,     3,   344,
       6,     3,     3,     6,   449,     3,     6,   412,     6,     3,
     289,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   463,   465,     3,     8,     8,   165,   198,   199,   396,
       6,     3,   427,     8,   524,     3,     6,     6,     4,   237,
       4,     4,     4,     4,   166,   168,   166,   168,   166,     4,
       4,   166,   166,   166,   166,   168,   249,   248,   246,   316,
     312,   357,   353,   381,   377,   200,   211,   212,   213,   216,
     260,   308,   326,   330,   332,   334,   345,   346,   373,   403,
     405,   418,   420,   422,   442,   343,   278,    89,    90,   200,
     260,   347,   373,   403,   405,   418,   420,   422,   450,   451,
     452,   453,   454,   456,   448,   415,   411,   292,   288,   166,
     166,   166,   166,   166,   166,   301,     4,     4,   461,     6,
       3,   399,   395,     4,   141,   143,   144,   200,   260,   403,
     405,   525,   526,   527,   528,   530,   523,   165,    33,    34,
      35,    36,   252,   165,   165,   165,   165,   165,     8,     8,
       8,     8,     3,     8,   455,     4,     8,     3,     8,     8,
     165,   165,   165,     8,   196,   531,     4,   529,     3,     8,
     346,     4,   168,   452,     4,   166,     4,   526,   165,     5,
     165,     7,   532,   533,   534,     3,     6,   142,   145,   146,
     147,   535,   536,   537,   539,   540,   541,   533,   538,     4,
       4,     4,     3,     8,     4,   168,   166,   166,   536,   165
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   169,   171,   170,   172,   170,   173,   170,   174,   170,
     175,   170,   176,   170,   177,   170,   178,   170,   179,   170,
     180,   170,   181,   170,   182,   170,   183,   170,   184,   170,
     185,   185,   185,   185,   185,   185,   185,   186,   188,   187,
     189,   190,   190,   191,   191,   193,   192,   194,   194,   195,
     195,   197,   196,   198,   198,   199,   199,   200,   202,   201,
     203,   203,   204,   204,   204,   204,   204,   204,   206,   205,
     208,   207,   209,   209,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   211,   212,   213,   214,   215,   216,
     218,   217,   219,   219,   220,   220,   220,   220,   220,   220,
     220,   222,   221,   224,   223,   226,   225,   227,   227,   229,
     228,   230,   230,   231,   233,   232,   235,   234,   236,   236,
     237,   239,   238,   241,   240,   243,   242,   244,   244,   245,
     245,   247,   246,   248,   248,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   251,   250,   252,   252,   252,   252,   254,
     253,   256,   255,   258,   257,   259,   261,   260,   262,   263,
     264,   265,   266,   267,   268,   270,   269,   272,   271,   273,
     274,   276,   275,   277,   277,   278,   278,   278,   278,   278,
     279,   280,   281,   282,   283,   285,   284,   286,   286,   287,
     287,   289,   288,   291,   290,   292,   292,   292,   293,   293,
     295,   294,   297,   296,   299,   298,   300,   300,   301,   301,
     301,   301,   301,   301,   302,   303,   304,   305,   306,   307,
     309,   308,   310,   310,   311,   311,   313,   312,   315,   314,
     316,   316,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   319,   318,   321,
     320,   323,   322,   325,   324,   327,   326,   329,   328,   331,
     330,   333,   332,   335,   334,   336,   336,   336,   336,   337,
     338,   340,   339,   341,   341,   342,   342,   344,   343,   345,
     345,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   348,
     347,   350,   349,   351,   351,   352,   352,   354,   353,   356,
     355,   357,   357,   358,   358,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   360,   361,   362,   364,   363,
     366,   365,   368,   367,   369,   371,   370,   372,   374,   373,
     375,   375,   376,   376,   378,   377,   380,   379,   381,   381,
     382,   382,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   384,   386,   385,   387,   388,   389,   390,   392,   391,
     393,   393,   394,   394,   396,   395,   398,   397,   399,   399,
     400,   400,   400,   400,   400,   400,   400,   402,   401,   404,
     403,   406,   405,   408,   407,   409,   409,   410,   410,   412,
     411,   414,   413,   415,   415,   416,   416,   417,   417,   417,
     417,   417,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   419,   418,   421,   420,   423,   422,   425,   424,
     427,   426,   429,   428,   431,   430,   433,   432,   435,   434,
     437,   436,   439,   438,   441,   440,   443,   442,   444,   444,
     446,   445,   447,   447,   449,   448,   450,   450,   451,   451,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   453,   455,   454,   456,   457,   459,   458,   460,   460,
     461,   461,   461,   461,   461,   463,   462,   465,   464,   467,
     466,   469,   468,   470,   470,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   472,   474,   473,   476,   475,   477,
     479,   478,   480,   481,   483,   482,   484,   484,   486,   485,
     487,   488,   489,   491,   490,   492,   492,   492,   492,   492,
     494,   493,   496,   495,   498,   497,   500,   499,   502,   501,
     504,   503,   506,   505,   507,   505,   509,   508,   510,   510,
     511,   511,   513,   512,   515,   514,   517,   516,   518,   518,
     519,   521,   520,   522,   522,   524,   523,   525,   525,   526,
     526,   526,   526,   526,   526,   526,   527,   529,   528,   531,
     530,   532,   532,   534,   533,   535,   535,   536,   536,   536,
     536,   538,   537,   539,   540,   541
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     1,     1,     0,
       4,     1,     1,     3,     0,     6,     0,     6,     1,     3,
       1,     0,     4,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     1,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     0,     6,     0,     6,     0,     4,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
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
  "\"decline-probation-period\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@21",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@22", "interfaces_list", "$@23", "dhcp_socket_type", "$@24",
  "socket_type", "outbound_interface", "$@25", "outbound_interface_value",
  "re_detect", "lease_database", "$@26", "sanity_checks", "$@27",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@28",
  "hosts_database", "$@29", "hosts_databases", "$@30", "database_list",
  "not_empty_database_list", "database", "$@31", "database_map_params",
  "database_map_param", "database_type", "$@32", "db_type", "user", "$@33",
  "password", "$@34", "host", "$@35", "port", "name", "$@36", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@37", "keyspace",
  "$@38", "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@39",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@40", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@41",
  "sub_hooks_library", "$@42", "hooks_params", "hooks_param", "library",
  "$@43", "parameters", "$@44", "expired_leases_processing", "$@45",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@46",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@47",
  "sub_subnet4", "$@48", "subnet4_params", "subnet4_param", "subnet",
  "$@49", "subnet_4o6_interface", "$@50", "subnet_4o6_interface_id",
  "$@51", "subnet_4o6_subnet", "$@52", "interface", "$@53", "interface_id",
  "$@54", "client_class", "$@55", "require_client_classes", "$@56",
  "reservation_mode", "$@57", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@58", "shared_networks_content",
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
  "$@98", "control_socket_name", "$@99", "dhcp_ddns", "$@100",
  "sub_dhcp_ddns", "$@101", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@102", "server_ip", "$@103",
  "server_port", "sender_ip", "$@104", "sender_port", "max_queue_size",
  "ncr_protocol", "$@105", "ncr_protocol_value", "ncr_format", "$@106",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@107", "replace_client_name_value",
  "generated_prefix", "$@108", "hostname_char_set", "$@109",
  "hostname_char_replacement", "$@110", "dhcp6_json_object", "$@111",
  "dhcpddns_json_object", "$@112", "control_agent_json_object", "$@113",
  "config_control", "$@114", "$@115", "sub_config_control", "$@116",
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
       0,   253,   253,   253,   254,   254,   255,   255,   256,   256,
     257,   257,   258,   258,   259,   259,   260,   260,   261,   261,
     262,   262,   263,   263,   264,   264,   265,   265,   266,   266,
     274,   275,   276,   277,   278,   279,   280,   283,   288,   288,
     299,   302,   303,   306,   310,   317,   317,   324,   325,   328,
     332,   339,   339,   346,   347,   350,   354,   365,   375,   375,
     391,   392,   396,   397,   398,   399,   400,   401,   404,   404,
     419,   419,   428,   429,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   466,   471,   476,   481,   486,   491,
     497,   497,   508,   509,   512,   513,   514,   515,   516,   517,
     518,   521,   521,   530,   530,   540,   540,   547,   548,   551,
     551,   558,   560,   564,   570,   570,   582,   582,   592,   593,
     595,   597,   597,   615,   615,   627,   627,   637,   638,   641,
     642,   645,   645,   655,   656,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,   669,   670,   671,   672,   673,
     674,   675,   676,   679,   679,   686,   687,   688,   689,   692,
     692,   700,   700,   708,   708,   716,   721,   721,   729,   734,
     739,   744,   749,   754,   759,   764,   764,   772,   772,   780,
     785,   790,   790,   800,   801,   804,   805,   806,   807,   808,
     811,   816,   821,   826,   831,   836,   836,   846,   847,   850,
     851,   854,   854,   864,   864,   874,   875,   876,   879,   880,
     883,   883,   891,   891,   899,   899,   910,   911,   914,   915,
     916,   917,   918,   919,   922,   927,   932,   937,   942,   947,
     955,   955,   968,   969,   972,   973,   980,   980,  1006,  1006,
    1017,  1018,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,
    1040,  1041,  1042,  1043,  1044,  1045,  1046,  1049,  1049,  1057,
    1057,  1065,  1065,  1073,  1073,  1081,  1081,  1089,  1089,  1097,
    1097,  1105,  1105,  1115,  1115,  1122,  1123,  1124,  1125,  1128,
    1133,  1140,  1140,  1151,  1152,  1156,  1157,  1160,  1160,  1168,
    1169,  1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,
    1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,  1196,
    1196,  1209,  1209,  1218,  1219,  1222,  1223,  1228,  1228,  1243,
    1243,  1257,  1258,  1261,  1262,  1265,  1266,  1267,  1268,  1269,
    1270,  1271,  1272,  1273,  1274,  1277,  1279,  1284,  1286,  1286,
    1294,  1294,  1302,  1302,  1310,  1312,  1312,  1320,  1329,  1329,
    1341,  1342,  1347,  1348,  1353,  1353,  1365,  1365,  1377,  1378,
    1383,  1384,  1389,  1390,  1391,  1392,  1393,  1394,  1395,  1396,
    1397,  1400,  1402,  1402,  1410,  1412,  1414,  1419,  1427,  1427,
    1439,  1440,  1443,  1444,  1447,  1447,  1457,  1457,  1467,  1468,
    1471,  1472,  1473,  1474,  1475,  1476,  1477,  1480,  1480,  1488,
    1488,  1513,  1513,  1543,  1543,  1553,  1554,  1557,  1558,  1561,
    1561,  1570,  1570,  1579,  1580,  1583,  1584,  1588,  1589,  1590,
    1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,
    1601,  1602,  1605,  1605,  1613,  1613,  1621,  1621,  1629,  1629,
    1637,  1637,  1647,  1647,  1655,  1655,  1663,  1663,  1671,  1671,
    1679,  1679,  1687,  1687,  1695,  1695,  1708,  1708,  1718,  1719,
    1725,  1725,  1735,  1736,  1739,  1739,  1749,  1750,  1753,  1754,
    1757,  1758,  1759,  1760,  1761,  1762,  1763,  1764,  1765,  1766,
    1767,  1770,  1772,  1772,  1780,  1789,  1796,  1796,  1806,  1807,
    1810,  1811,  1812,  1813,  1814,  1817,  1817,  1825,  1825,  1835,
    1835,  1847,  1847,  1857,  1858,  1861,  1862,  1863,  1864,  1865,
    1866,  1867,  1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,
    1876,  1877,  1878,  1879,  1882,  1887,  1887,  1895,  1895,  1903,
    1908,  1908,  1916,  1921,  1926,  1926,  1934,  1935,  1938,  1938,
    1946,  1951,  1956,  1961,  1961,  1969,  1972,  1975,  1978,  1981,
    1987,  1987,  1995,  1995,  2003,  2003,  2014,  2014,  2021,  2021,
    2028,  2028,  2035,  2035,  2044,  2044,  2055,  2055,  2065,  2066,
    2070,  2071,  2074,  2074,  2089,  2089,  2099,  2099,  2110,  2111,
    2115,  2119,  2119,  2131,  2132,  2136,  2136,  2144,  2145,  2148,
    2149,  2150,  2151,  2152,  2153,  2154,  2157,  2162,  2162,  2170,
    2170,  2180,  2181,  2184,  2184,  2192,  2193,  2196,  2197,  2198,
    2199,  2202,  2202,  2210,  2215,  2220
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
#line 4875 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2225 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
