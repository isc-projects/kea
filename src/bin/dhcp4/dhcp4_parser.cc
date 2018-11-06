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
      case 229: // socket_type
      case 232: // outbound_interface_value
      case 254: // db_type
      case 336: // hr_mode
      case 485: // ncr_protocol_value
      case 493: // replace_client_name_value
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
      case 229: // socket_type
      case 232: // outbound_interface_value
      case 254: // db_type
      case 336: // hr_mode
      case 485: // ncr_protocol_value
      case 493: // replace_client_name_value
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

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 166: // "integer"

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 167: // "floating point"

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 168: // "boolean"

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 185: // value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 189: // map_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 229: // socket_type

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 232: // outbound_interface_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 254: // db_type

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 336: // hr_mode

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 485: // ncr_protocol_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 493: // replace_client_name_value

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
      case 185: // value
      case 189: // map_value
      case 229: // socket_type
      case 232: // outbound_interface_value
      case 254: // db_type
      case 336: // hr_mode
      case 485: // ncr_protocol_value
      case 493: // replace_client_name_value
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

  case 106:
#line 469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 699 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 801 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1129 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1136 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1282 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2295 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2567 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:859
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
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1836 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3043 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3061 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1952 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1986 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1992 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1995 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3336 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2056 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3371 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2096 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2136 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2174 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2179 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2201 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 642:
#line 2219 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 643:
#line 2221 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 644:
#line 2227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3617 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3621 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -790;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     400,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,    48,    24,    53,   110,   114,
     118,   122,   155,   159,   168,   188,   192,   200,   202,   219,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,    24,     4,
      22,    52,    71,   152,    36,   226,    98,   263,   372,   -49,
     366,    33,    11,  -790,   235,   252,   260,   257,   268,  -790,
    -790,  -790,  -790,  -790,   262,  -790,    85,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,   292,   293,  -790,
    -790,  -790,  -790,  -790,  -790,   309,   333,   337,   343,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,   344,  -790,  -790,  -790,  -790,    91,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,   350,  -790,   146,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,   352,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,   147,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,   157,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
     271,   284,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,   353,  -790,  -790,   356,  -790,  -790,
    -790,   359,  -790,  -790,   363,   342,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,   360,
     369,  -790,  -790,  -790,  -790,   373,   371,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,   185,
    -790,  -790,  -790,   376,  -790,  -790,   379,  -790,   381,   382,
    -790,  -790,   383,   384,   386,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,   205,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,   215,  -790,  -790,  -790,  -790,   237,  -790,  -790,  -790,
      24,    24,  -790,   212,   390,   392,   393,   396,   397,  -790,
      22,  -790,    11,   399,   404,   406,   246,   247,   414,   415,
     418,   419,   420,   422,   251,   264,   278,   280,   425,   427,
     439,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     311,   470,   471,   474,    52,  -790,   475,   476,   477,   314,
      71,  -790,   493,   494,   495,   496,   497,   498,   339,   502,
     503,   505,   507,   152,  -790,   508,    36,  -790,   509,   510,
     512,   513,   514,   515,   518,   519,  -790,   226,  -790,   520,
     521,   362,   522,   525,   526,   364,  -790,   263,   530,   367,
     374,  -790,   372,   535,   536,   -56,  -790,   375,   537,   540,
     380,   541,   401,   403,   545,   561,   398,   405,   407,   567,
     568,   570,   572,   366,  -790,   573,    33,  -790,   575,    11,
    -790,  -790,  -790,   576,   574,   577,    24,    24,    24,  -790,
     241,   578,   579,   580,  -790,  -790,   417,   423,   424,   583,
     584,   587,  -790,  -790,  -790,  -790,   428,   589,   590,   591,
     592,   593,   433,   594,   596,   597,   598,   599,  -790,   600,
     593,   601,  -790,   604,    55,   196,  -790,  -790,   440,   445,
     446,   607,   448,   449,  -790,    19,   604,   450,   609,  -790,
     452,  -790,   604,   453,   454,   455,   456,   457,   458,   459,
    -790,   460,   472,  -790,   473,   478,   479,  -790,  -790,   480,
    -790,  -790,  -790,   481,    24,  -790,  -790,   482,   483,  -790,
     484,  -790,  -790,    21,   451,  -790,  -790,  -790,     6,   485,
     486,   487,  -790,   621,  -790,   622,  -790,    24,    52,    33,
    -790,  -790,  -790,  -790,    11,    71,   581,  -790,  -790,  -790,
     413,   413,   623,  -790,   624,   625,   626,   627,  -790,  -790,
    -790,   166,   628,   629,   632,    76,   162,  -790,   366,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
     633,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
      -9,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,   634,   623,  -790,   259,   265,   274,
     275,  -790,   277,  -790,  -790,  -790,  -790,  -790,  -790,   638,
     649,   650,   651,   652,  -790,  -790,   653,   654,   655,   656,
     657,  -790,   283,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,   286,  -790,   658,   659,  -790,  -790,   660,   662,  -790,
    -790,   661,   665,  -790,  -790,   663,   667,  -790,  -790,   666,
     668,  -790,  -790,  -790,  -790,  -790,  -790,    58,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,    81,  -790,  -790,   669,   670,
    -790,  -790,   671,   673,  -790,   674,   675,   676,   677,   678,
     679,   290,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,   296,  -790,  -790,  -790,   297,   523,
    -790,   680,   681,  -790,  -790,  -790,  -790,   620,  -790,   130,
    -790,   683,  -790,  -790,  -790,  -790,   686,   581,  -790,   687,
     688,   689,   690,   529,   506,   531,   517,   532,   692,   695,
     534,   538,   539,   542,   533,   413,  -790,  -790,   413,  -790,
     623,   152,  -790,   624,   263,  -790,   625,   372,  -790,   626,
     194,  -790,   627,   166,  -790,    69,   628,  -790,   226,  -790,
     629,   -49,  -790,   632,   543,   544,   546,   547,   548,   549,
      76,  -790,   698,   699,   162,  -790,  -790,  -790,   700,   684,
      36,  -790,   633,   703,  -790,    59,   634,  -790,  -790,   551,
    -790,   317,   552,   553,   554,  -790,  -790,  -790,  -790,  -790,
     555,   556,  -790,  -790,  -790,  -790,  -790,  -790,   300,  -790,
     306,  -790,   714,  -790,   715,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,   307,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,   707,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,   716,
     722,  -790,  -790,  -790,  -790,  -790,   718,  -790,   308,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,   562,   563,  -790,
    -790,   564,   328,  -790,   604,  -790,   726,  -790,  -790,  -790,
    -790,  -790,   332,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,   194,  -790,   727,   565,  -790,    69,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,   728,   569,   730,    59,
    -790,  -790,   571,  -790,  -790,   732,  -790,   582,  -790,  -790,
     731,  -790,  -790,   145,  -790,   -27,   731,  -790,  -790,   735,
     736,   737,   341,  -790,  -790,  -790,  -790,  -790,  -790,   738,
     585,   586,   613,   -27,  -790,   610,  -790,  -790,  -790,  -790,
    -790
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
     227,    23,   532,    25,   607,    27,   597,    29,    47,    41,
       0,     0,     0,     0,     0,   442,     0,   350,   387,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     605,   587,   589,   591,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   593,   595,   114,   140,     0,     0,   461,
     463,   465,   138,   147,   149,     0,     0,     0,     0,   110,
     254,   338,   377,   310,   428,   430,   205,   489,   432,   219,
     238,     0,   515,   528,   530,   105,     0,    72,    74,    75,
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
     229,   232,   233,     0,   556,   558,     0,   561,     0,     0,
     565,   569,     0,     0,     0,   574,   581,   583,   585,   554,
     552,   553,     0,   534,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     612,     0,   609,   611,   603,   602,     0,   599,   601,    46,
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
       0,     0,     0,     0,   533,     0,     0,   608,     0,     0,
     598,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,   112,   113,     0,     0,     0,     0,
       0,     0,   106,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   514,     0,
       0,     0,    73,     0,     0,     0,   137,   117,     0,     0,
       0,     0,     0,     0,   309,     0,     0,     0,     0,   265,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
     445,     0,     0,   365,     0,     0,     0,   376,   353,     0,
     405,   406,   390,     0,     0,   230,   555,     0,     0,   560,
       0,   563,   564,     0,     0,   571,   572,   573,     0,     0,
       0,     0,   535,     0,   610,     0,   600,     0,     0,     0,
     588,   590,   592,   594,     0,     0,     0,   462,   464,   466,
       0,     0,   151,   111,   256,   342,   379,   312,    40,   429,
     431,     0,     0,   434,   221,     0,     0,   529,     0,    51,
     128,   131,   132,   130,   135,   136,   134,   292,   294,   296,
     409,   290,   298,   305,   306,   307,   308,   304,   302,   300,
       0,   427,   484,   472,   474,   478,   476,   482,   480,   468,
     368,   191,   372,   370,   375,   402,   235,   237,   557,   559,
     562,   567,   568,   566,   570,   576,   577,   578,   579,   580,
     575,   582,   584,   586,     0,   151,    44,     0,     0,     0,
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
     526,   523,   521,   522,     0,   517,   519,   520,     0,    53,
     413,     0,   410,   411,   469,   487,   488,     0,   616,     0,
     614,     0,    69,   606,   596,   115,     0,     0,   141,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   139,   148,     0,   150,
       0,     0,   255,     0,   350,   339,     0,   387,   378,     0,
       0,   311,     0,     0,   206,   495,     0,   490,   442,   433,
       0,     0,   220,     0,     0,     0,     0,     0,     0,     0,
       0,   239,     0,     0,     0,   516,   531,    55,     0,    54,
       0,   408,     0,     0,   486,     0,     0,   613,   604,     0,
     143,     0,     0,     0,     0,   189,   192,   193,   194,   195,
       0,     0,   203,   204,   196,   197,   198,   158,     0,   154,
       0,   259,     0,   345,     0,   382,   337,   334,   323,   324,
     326,   320,   321,   322,   332,   333,   331,     0,   318,   325,
     335,   336,   327,   328,   329,   330,   315,   208,   511,     0,
     509,   510,   502,   503,   507,   508,   504,   505,   506,     0,
     496,   497,   499,   500,   501,   492,     0,   437,     0,   224,
     248,   249,   250,   251,   252,   253,   241,     0,     0,   518,
      52,     0,     0,   412,     0,   630,     0,   628,   626,   620,
     624,   625,     0,   618,   622,   623,   621,   615,   146,   179,
     180,   181,   182,   178,   184,   186,   188,   200,   202,   156,
     261,   347,   384,     0,   317,     0,     0,   494,     0,   439,
     226,   525,   527,    56,   414,   470,     0,     0,     0,     0,
     617,   319,     0,   513,   498,     0,   627,     0,   619,   512,
       0,   629,   634,     0,   632,     0,     0,   631,   642,     0,
       0,     0,     0,   636,   638,   639,   640,   641,   633,     0,
       0,     0,     0,     0,   635,     0,   644,   645,   646,   637,
     643
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,   -44,  -790,  -452,  -790,
     119,  -790,  -790,  -790,  -790,  -790,  -790,  -505,  -790,  -790,
    -790,   -70,  -790,  -790,  -790,   303,  -790,  -790,  -790,  -790,
     165,   355,   -48,   -45,   -43,  -790,  -790,  -790,  -790,   -11,
    -790,  -790,   161,   358,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
     -53,  -790,  -790,  -790,  -790,  -790,  -790,    90,  -790,   -64,
    -790,  -585,   -51,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,   -26,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,   -83,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,   -84,  -790,  -790,  -790,   -79,   336,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,   -62,  -790,  -790,  -790,  -790,  -790,
    -790,  -789,  -790,  -790,  -790,   -32,  -790,  -790,  -790,   -28,
     395,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -787,
    -790,   -24,  -790,    -4,  -790,  -786,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,   -33,  -790,  -790,  -189,   -65,  -790,  -790,
    -790,  -790,  -790,   -21,  -790,  -790,  -790,   -13,  -790,   388,
    -790,   -66,  -790,  -790,  -790,  -790,  -790,   -60,  -790,  -790,
    -790,  -790,  -790,   -18,  -790,  -790,  -790,   -16,  -790,  -790,
    -790,     7,  -790,   391,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,   -25,  -790,  -790,  -790,   -42,
     429,  -790,  -790,   -58,  -790,   -38,  -790,   -47,  -790,  -790,
    -790,     1,  -790,  -790,  -790,     2,  -790,   416,    -7,  -790,
      -6,  -790,     0,  -790,   214,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -785,  -790,  -790,  -790,  -790,  -790,    10,  -790,
    -790,  -790,  -141,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,    -5,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,   240,   387,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,  -790,
    -790,  -790,  -349,   385,  -790,  -790,  -790,  -790,  -790,  -790,
     272,   389,  -790,  -790,  -790,   -14,  -790,  -790,  -146,  -790,
    -790,  -790,  -790,  -790,  -790,  -159,  -790,  -790,  -175,  -790,
    -790,  -790,  -790,  -790
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     599,    87,    88,    41,    68,    84,    85,   610,   779,   858,
     859,   345,    43,    70,    96,    97,    98,   354,    45,    71,
     136,   137,   138,   139,   140,   141,   142,   378,   143,   144,
     145,   364,   174,   175,    47,    72,   176,   396,   177,   397,
     613,   178,   398,   616,   179,   146,   371,   147,   365,   672,
     673,   674,   796,   148,   372,   149,   373,   713,   714,   715,
     818,   692,   693,   694,   799,   973,   695,   800,   696,   801,
     697,   802,   698,   699,   430,   700,   701,   702,   703,   704,
     705,   706,   707,   808,   708,   809,   709,   710,   150,   385,
     737,   738,   739,   740,   741,   742,   743,   151,   388,   752,
     753,   754,   841,    61,    79,   299,   300,   301,   443,   302,
     444,   152,   389,   761,   762,   763,   764,   765,   766,   767,
     768,   153,   379,   717,   718,   719,   821,    49,    73,   198,
     199,   200,   406,   201,   402,   202,   403,   203,   404,   204,
     407,   205,   411,   206,   410,   207,   409,   627,   208,   154,
     382,   729,   730,   731,   830,   907,   908,   155,   380,    55,
      76,   721,   722,   723,   824,    57,    77,   264,   265,   266,
     267,   268,   269,   270,   429,   271,   433,   272,   432,   273,
     274,   434,   275,   156,   381,   725,   726,   727,   827,    59,
      78,   285,   286,   287,   288,   289,   438,   290,   291,   292,
     293,   210,   405,   781,   782,   783,   860,    51,    74,   223,
     224,   225,   415,   157,   383,   158,   384,   159,   387,   748,
     749,   750,   838,    53,    75,   240,   241,   242,   160,   368,
     161,   369,   162,   370,   246,   425,   786,   863,   247,   419,
     248,   420,   249,   422,   250,   421,   251,   424,   252,   423,
     253,   418,   217,   412,   787,   163,   386,   745,   746,   835,
     929,   930,   931,   932,   933,   985,   934,   164,   165,   391,
     774,   775,   776,   852,   777,   853,   166,   392,   167,   393,
      63,    80,   322,   323,   324,   325,   448,   326,   449,   327,
     328,   451,   329,   330,   331,   454,   653,   332,   455,   333,
     334,   335,   336,   459,   660,   337,   460,   338,   461,   339,
     462,    99,   356,   100,   357,   101,   358,   168,   362,   363,
      67,    82,   346,   347,   348,   468,   102,   355,    65,    81,
     341,   342,   343,   465,   789,   790,   865,   962,   963,   964,
     965,   998,   966,   996,  1013,  1014,  1015,  1022,  1023,  1024,
    1029,  1025,  1026,  1027
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   135,   173,   193,   219,   236,   711,   262,   281,   298,
     319,   254,   283,   480,   180,   211,   226,   238,   284,   276,
     294,   628,   320,   344,    83,   194,   213,   632,   195,    31,
     196,    32,    89,    33,   181,   212,   227,   239,   651,   277,
     295,   902,   321,   903,   906,   915,   296,   297,    30,   598,
     220,   263,   282,   296,   297,   209,   222,   237,   598,   103,
      42,   833,   197,   104,   834,   105,   214,   215,   243,   244,
     221,   611,   612,   216,   106,   245,   107,   108,   109,   110,
     111,   112,   113,   114,   836,   169,   170,   837,   360,   171,
     235,   784,   172,   361,   394,   109,   110,   111,   122,   395,
     623,   624,   625,   626,   115,   116,   117,   118,   119,   120,
     218,   124,   125,   121,   122,  1018,    94,    44,  1019,  1020,
    1021,    46,   256,   190,   123,    48,   191,   124,   125,    50,
     121,   122,   256,   866,   124,   125,   867,   126,   127,   655,
     656,   657,   658,   128,   124,   125,   124,   125,  1016,   400,
     413,  1017,   652,   129,   401,   414,   130,   918,   919,   121,
     416,    90,    52,   131,   132,   417,    54,   133,   134,    86,
      91,    92,    93,   340,   659,    56,    94,   108,   109,   110,
     111,   755,   756,   757,   758,   759,   760,    94,   445,    34,
      35,    36,    37,   446,   902,    58,   903,   906,   915,    60,
     955,    94,   956,   957,   115,   116,   117,    62,   463,    64,
     182,   183,   184,   464,   122,   614,   615,    94,   466,   108,
     109,   110,   111,   467,    94,   185,    66,   124,   125,   186,
     187,   188,   189,   888,    94,   669,    94,   124,   125,   190,
     469,   349,   191,   128,   469,   470,   115,   116,   117,   583,
     192,   120,   109,   110,   111,   350,   122,   256,   732,   733,
     734,   735,   394,   736,   351,   352,   359,   792,   466,   124,
     125,   353,   187,   793,   189,   769,   770,   469,   400,   426,
     797,   190,   794,   795,   191,   798,   815,   427,   122,   815,
      95,   816,   192,   850,   817,   255,   366,   367,   851,   854,
     463,   124,   125,   815,   855,   856,   471,   472,   979,   413,
     983,   445,   228,   374,   980,   984,   990,    94,   229,   230,
     231,   232,   233,   234,   135,   235,   256,    94,   257,   258,
     173,   416,   259,   260,   261,   999,   994,   375,   124,   125,
    1000,   376,   180,   193,  1033,   437,   219,   377,   390,  1034,
     969,   970,   971,   972,   399,   211,   408,   236,   226,    94,
     431,   428,   181,   435,   439,   194,   213,   262,   195,   238,
     196,   436,   281,   440,   442,   212,   283,   473,   227,   276,
     447,   441,   284,   450,   294,   452,   453,   456,   457,   239,
     458,    94,   220,   319,   474,   209,   475,   476,   222,   277,
     477,   478,   197,   481,   295,   320,   214,   215,   482,   237,
     483,   263,   221,   216,   484,   485,   282,   492,   486,   487,
     243,   244,   488,   489,   490,   321,   491,   245,    94,   496,
     493,   497,   580,   581,   582,   256,   278,   257,   258,   279,
     280,   124,   125,   498,   494,   675,   495,   124,   125,   995,
     676,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   690,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   509,   510,   256,   508,   511,   513,
     514,   515,   516,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   518,   519,   520,
     521,   522,   523,   317,   318,   524,   525,   526,   135,   527,
     647,   528,   530,   532,   533,   173,   534,   535,   536,   537,
     691,   691,   538,   539,   541,   542,   544,   180,   543,   545,
     546,    94,   547,   666,   549,   550,   771,    94,   319,   553,
     554,   557,   551,   556,   558,   560,   559,   181,   772,   563,
     320,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   564,   565,   561,   773,   562,
     321,   568,   569,   566,   570,   567,   571,   573,    94,   575,
     577,   578,   587,   654,   579,   584,   585,   586,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   600,   601,
      32,   602,   603,   604,   671,   617,   605,   606,   608,   609,
     618,   619,   620,   621,   622,   629,   630,   631,   633,   634,
     635,   636,   637,   638,   639,   640,   664,   665,   864,   607,
     712,   716,   720,   724,   728,   744,   747,   641,   642,   751,
     780,   788,   803,   643,   644,   645,   646,   648,   649,   650,
     661,   662,   663,   804,   805,   806,   807,   810,   811,   812,
     813,   814,   820,   479,   819,   823,   822,   825,   826,   828,
     829,   832,   831,   840,   876,   839,   843,   842,   844,   845,
     846,   847,   848,   849,   862,   878,   861,   951,   857,   868,
     869,   871,   872,   873,   874,   875,   880,   877,   879,   881,
     882,   886,   947,   948,   883,   884,   950,   954,   885,   940,
     941,   986,   942,   943,   944,   945,   968,   974,   975,   976,
     977,   978,   981,   982,   987,   988,   989,   991,   992,   993,
     997,  1002,  1005,  1003,  1007,  1006,  1009,  1010,  1012,  1030,
    1031,  1032,  1035,   667,   870,   691,   670,  1011,   691,   512,
     917,   193,  1037,  1036,   262,   791,   889,   281,   517,   939,
     896,   283,   938,   211,   887,   920,   276,   284,   236,   294,
     922,   298,   910,   194,   213,  1040,   195,   924,   196,  1038,
     238,   555,   897,   212,   771,   898,   277,   899,   946,   295,
     219,   891,   911,   890,  1001,   958,   772,   925,   263,   916,
     239,   282,   226,   209,   901,   893,   904,   960,   529,   921,
     197,   892,   909,   895,   214,   215,   773,   923,   952,   900,
     237,   216,   227,   912,   913,   548,   905,   961,   926,   927,
     914,   243,   244,   552,   894,   928,   220,   953,   245,   959,
     936,   937,   222,   540,   785,   531,   935,  1004,   778,   949,
     572,   668,   967,  1008,   576,   574,   221,  1028,  1039,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   896,     0,     0,     0,     0,   920,     0,
       0,     0,     0,   922,     0,   910,     0,     0,     0,   958,
     924,     0,     0,     0,     0,   897,     0,     0,   898,     0,
     899,   960,     0,     0,     0,   911,     0,     0,     0,     0,
     925,     0,     0,     0,     0,     0,     0,   901,     0,   904,
       0,   961,   921,     0,     0,   909,     0,     0,     0,     0,
     923,     0,   900,   959,     0,     0,   912,   913,     0,   905,
       0,   926,   927,   914,     0,     0,     0,     0,   928
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,   591,    77,    78,    79,
      80,    76,    78,   362,    72,    73,    74,    75,    78,    77,
      78,   526,    80,    12,    68,    73,    73,   532,    73,     5,
      73,     7,    10,     9,    72,    73,    74,    75,    17,    77,
      78,   830,    80,   830,   830,   830,   102,   103,     0,   501,
      74,    77,    78,   102,   103,    73,    74,    75,   510,     7,
       7,     3,    73,    11,     6,    13,    73,    73,    75,    75,
      74,    16,    17,    73,    22,    75,    24,    25,    26,    27,
      28,    29,    30,    31,     3,    14,    15,     6,     3,    18,
      99,   100,    21,     8,     3,    26,    27,    28,    62,     8,
      81,    82,    83,    84,    52,    53,    54,    55,    56,    57,
      74,    75,    76,    61,    62,   142,   165,     7,   145,   146,
     147,     7,    63,    87,    72,     7,    90,    75,    76,     7,
      61,    62,    63,     3,    75,    76,     6,    85,    86,   133,
     134,   135,   136,    91,    75,    76,    75,    76,     3,     3,
       3,     6,   131,   101,     8,     8,   104,    88,    89,    61,
       3,   139,     7,   111,   112,     8,     7,   115,   116,   165,
     148,   149,   150,   140,   168,     7,   165,    25,    26,    27,
      28,   105,   106,   107,   108,   109,   110,   165,     3,   165,
     166,   167,   168,     8,   983,     7,   983,   983,   983,     7,
     141,   165,   143,   144,    52,    53,    54,     7,     3,     7,
      58,    59,    60,     8,    62,    19,    20,   165,     3,    25,
      26,    27,    28,     8,   165,    73,     7,    75,    76,    77,
      78,    79,    80,   818,   165,   584,   165,    75,    76,    87,
       3,     6,    90,    91,     3,     8,    52,    53,    54,     8,
      98,    57,    26,    27,    28,     3,    62,    63,    92,    93,
      94,    95,     3,    97,     4,     8,     4,     8,     3,    75,
      76,     3,    78,     8,    80,   113,   114,     3,     3,     8,
       3,    87,     8,     8,    90,     8,     3,     3,    62,     3,
     360,     8,    98,     3,     8,    32,     4,     4,     8,     3,
       3,    75,    76,     3,     8,     8,   350,   351,     8,     3,
       3,     3,    86,     4,     8,     8,     8,   165,    92,    93,
      94,    95,    96,    97,   394,    99,    63,   165,    65,    66,
     400,     3,    69,    70,    71,     3,     8,     4,    75,    76,
       8,     4,   400,   413,     3,     3,   416,     4,     4,     8,
      33,    34,    35,    36,     4,   413,     4,   427,   416,   165,
       4,     8,   400,     4,     4,   413,   413,   437,   413,   427,
     413,     8,   442,     4,     3,   413,   442,   165,   416,   437,
       4,     8,   442,     4,   442,     4,     4,     4,     4,   427,
       4,   165,   416,   463,     4,   413,     4,     4,   416,   437,
       4,     4,   413,     4,   442,   463,   413,   413,     4,   427,
       4,   437,   416,   413,   168,   168,   442,   166,     4,     4,
     427,   427,     4,     4,     4,   463,     4,   427,   165,     4,
     166,     4,   476,   477,   478,    63,    64,    65,    66,    67,
      68,    75,    76,     4,   166,    32,   166,    75,    76,   954,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    63,   166,     4,     4,
       4,     4,   168,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     4,     4,     4,
       4,     4,     4,   137,   138,   166,     4,     4,   578,     4,
     554,     4,     4,     4,     4,   585,     4,     4,     4,     4,
     590,   591,     4,     4,     4,     4,     4,   585,   166,     4,
       4,   165,   168,   577,     4,   168,   606,   165,   608,     4,
       4,     4,   168,   168,     4,     4,   166,   585,   606,     4,
     608,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,     4,   168,   166,   606,   166,
     608,     4,     4,   168,     4,   168,     4,     4,   165,     4,
       4,     7,   165,   132,     7,     7,     7,     7,   165,   165,
       7,     7,     5,   165,     5,     5,     5,     5,   165,     5,
       7,     5,     5,     5,    23,   165,     7,     7,     7,     5,
     165,   165,     5,   165,   165,   165,     7,   165,   165,   165,
     165,   165,   165,   165,   165,   165,     5,     5,     8,   510,
       7,     7,     7,     7,     7,     7,     7,   165,   165,     7,
       7,     7,     4,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   360,     6,     3,     6,     6,     3,     6,
       3,     3,     6,     3,   168,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     3,   168,     6,     3,   165,     6,
       4,     4,     4,     4,     4,   166,     4,   166,   166,     4,
     166,   168,     4,     4,   166,   166,     6,     4,   166,   166,
     166,     4,   166,   166,   166,   166,   165,   165,   165,   165,
     165,   165,     8,     8,     8,     3,     8,   165,   165,   165,
       4,     4,     4,   168,     4,   166,   165,     5,     7,     4,
       4,     4,     4,   578,   797,   815,   585,   165,   818,   394,
     833,   821,   166,   168,   824,   665,   820,   827,   400,   843,
     830,   827,   841,   821,   815,   835,   824,   827,   838,   827,
     835,   841,   830,   821,   821,   165,   821,   835,   821,   166,
     838,   445,   830,   821,   854,   830,   824,   830,   850,   827,
     860,   823,   830,   821,   983,   865,   854,   835,   824,   832,
     838,   827,   860,   821,   830,   826,   830,   865,   413,   835,
     821,   824,   830,   829,   821,   821,   854,   835,   860,   830,
     838,   821,   860,   830,   830,   437,   830,   865,   835,   835,
     830,   838,   838,   442,   827,   835,   860,   862,   838,   865,
     838,   840,   860,   427,   630,   416,   836,   988,   608,   854,
     463,   579,   866,   999,   469,   466,   860,  1016,  1033,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   983,    -1,    -1,    -1,    -1,   988,    -1,
      -1,    -1,    -1,   988,    -1,   983,    -1,    -1,    -1,   999,
     988,    -1,    -1,    -1,    -1,   983,    -1,    -1,   983,    -1,
     983,   999,    -1,    -1,    -1,   983,    -1,    -1,    -1,    -1,
     988,    -1,    -1,    -1,    -1,    -1,    -1,   983,    -1,   983,
      -1,   999,   988,    -1,    -1,   983,    -1,    -1,    -1,    -1,
     988,    -1,   983,   999,    -1,    -1,   983,   983,    -1,   983,
      -1,   988,   988,   983,    -1,    -1,    -1,    -1,   988
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
       0,     5,     7,     9,   165,   166,   167,   168,   185,   186,
     187,   192,     7,   201,     7,   207,     7,   223,     7,   316,
       7,   396,     7,   412,     7,   348,     7,   354,     7,   378,
       7,   292,     7,   469,     7,   517,     7,   509,   193,   188,
     202,   208,   224,   317,   397,   413,   349,   355,   379,   293,
     470,   518,   510,   185,   194,   195,   165,   190,   191,    10,
     139,   148,   149,   150,   165,   200,   203,   204,   205,   500,
     502,   504,   515,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    52,    53,    54,    55,    56,
      57,    61,    62,    72,    75,    76,    85,    86,    91,   101,
     104,   111,   112,   115,   116,   200,   209,   210,   211,   212,
     213,   214,   215,   217,   218,   219,   234,   236,   242,   244,
     277,   286,   300,   310,   338,   346,   372,   402,   404,   406,
     417,   419,   421,   444,   456,   457,   465,   467,   506,    14,
      15,    18,    21,   200,   221,   222,   225,   227,   230,   233,
     402,   404,    58,    59,    60,    73,    77,    78,    79,    80,
      87,    90,    98,   200,   211,   212,   213,   218,   318,   319,
     320,   322,   324,   326,   328,   330,   332,   334,   337,   372,
     390,   402,   404,   406,   417,   419,   421,   441,    74,   200,
     330,   332,   372,   398,   399,   400,   402,   404,    86,    92,
      93,    94,    95,    96,    97,    99,   200,   372,   402,   404,
     414,   415,   416,   417,   419,   421,   423,   427,   429,   431,
     433,   435,   437,   439,   346,    32,    63,    65,    66,    69,
      70,    71,   200,   262,   356,   357,   358,   359,   360,   361,
     362,   364,   366,   368,   369,   371,   402,   404,    64,    67,
      68,   200,   262,   360,   366,   380,   381,   382,   383,   384,
     386,   387,   388,   389,   402,   404,   102,   103,   200,   294,
     295,   296,   298,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   137,   138,   200,
     402,   404,   471,   472,   473,   474,   476,   478,   479,   481,
     482,   483,   486,   488,   489,   490,   491,   494,   496,   498,
     140,   519,   520,   521,    12,   200,   511,   512,   513,     6,
       3,     4,     8,     3,   206,   516,   501,   503,   505,     4,
       3,     8,   507,   508,   220,   237,     4,     4,   418,   420,
     422,   235,   243,   245,     4,     4,     4,     4,   216,   311,
     347,   373,   339,   403,   405,   278,   445,   407,   287,   301,
       4,   458,   466,   468,     3,     8,   226,   228,   231,     4,
       3,     8,   323,   325,   327,   391,   321,   329,     4,   335,
     333,   331,   442,     3,     8,   401,     3,     8,   440,   428,
     430,   434,   432,   438,   436,   424,     8,     3,     8,   363,
     263,     4,   367,   365,   370,     4,     8,     3,   385,     4,
       4,     8,     3,   297,   299,     3,     8,     4,   475,   477,
       4,   480,     4,     4,   484,   487,     4,     4,     4,   492,
     495,   497,   499,     3,     8,   522,     3,     8,   514,     3,
       8,   185,   185,   165,     4,     4,     4,     4,     4,   204,
     511,     4,     4,     4,   168,   168,     4,     4,     4,     4,
       4,     4,   166,   166,   166,   166,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   166,     4,
       4,     4,   210,     4,     4,     4,   168,   222,     4,     4,
       4,     4,     4,     4,   166,     4,     4,     4,     4,   319,
       4,   399,     4,     4,     4,     4,     4,     4,     4,     4,
     416,     4,     4,   166,     4,     4,     4,   168,   358,     4,
     168,   168,   382,     4,     4,   295,   168,     4,     4,   166,
       4,   166,   166,     4,     4,   168,   168,   168,     4,     4,
       4,     4,   472,     4,   520,     4,   512,     4,     7,     7,
     185,   185,   185,     8,     7,     7,     7,   165,   165,   165,
       7,     7,     5,   165,     5,     5,     5,     5,   187,   189,
     165,     5,     5,     5,     5,     7,     7,   189,     7,     5,
     196,    16,    17,   229,    19,    20,   232,   165,   165,   165,
       5,   165,   165,    81,    82,    83,    84,   336,   196,   165,
       7,   165,   196,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   185,   165,   165,
     165,    17,   131,   485,   132,   133,   134,   135,   136,   168,
     493,   165,   165,   165,     5,     5,   185,   209,   519,   511,
     221,    23,   238,   239,   240,    32,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,   200,   250,   251,   252,   255,   257,   259,   261,   262,
     264,   265,   266,   267,   268,   269,   270,   271,   273,   275,
     276,   250,     7,   246,   247,   248,     7,   312,   313,   314,
       7,   350,   351,   352,     7,   374,   375,   376,     7,   340,
     341,   342,    92,    93,    94,    95,    97,   279,   280,   281,
     282,   283,   284,   285,     7,   446,   447,     7,   408,   409,
     410,     7,   288,   289,   290,   105,   106,   107,   108,   109,
     110,   302,   303,   304,   305,   306,   307,   308,   309,   113,
     114,   200,   402,   404,   459,   460,   461,   463,   471,   197,
       7,   392,   393,   394,   100,   423,   425,   443,     7,   523,
     524,   246,     8,     8,     8,     8,   241,     3,     8,   253,
     256,   258,   260,     4,     4,     4,     4,     4,   272,   274,
       4,     4,     4,     4,     4,     3,     8,     8,   249,     6,
       3,   315,     6,     3,   353,     6,     3,   377,     6,     3,
     343,     6,     3,     3,     6,   448,     3,     6,   411,     6,
       3,   291,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   462,   464,     3,     8,     8,   165,   198,   199,
     395,     6,     3,   426,     8,   525,     3,     6,     6,     4,
     239,     4,     4,     4,     4,   166,   168,   166,   168,   166,
       4,     4,   166,   166,   166,   166,   168,   251,   250,   248,
     318,   314,   356,   352,   380,   376,   200,   211,   212,   213,
     218,   262,   310,   328,   330,   332,   334,   344,   345,   372,
     402,   404,   417,   419,   421,   441,   342,   280,    88,    89,
     200,   262,   346,   372,   402,   404,   417,   419,   421,   449,
     450,   451,   452,   453,   455,   447,   414,   410,   294,   290,
     166,   166,   166,   166,   166,   166,   303,     4,     4,   460,
       6,     3,   398,   394,     4,   141,   143,   144,   200,   262,
     402,   404,   526,   527,   528,   529,   531,   524,   165,    33,
      34,    35,    36,   254,   165,   165,   165,   165,   165,     8,
       8,     8,     8,     3,     8,   454,     4,     8,     3,     8,
       8,   165,   165,   165,     8,   196,   532,     4,   530,     3,
       8,   345,     4,   168,   451,     4,   166,     4,   527,   165,
       5,   165,     7,   533,   534,   535,     3,     6,   142,   145,
     146,   147,   536,   537,   538,   540,   541,   542,   534,   539,
       4,     4,     4,     3,     8,     4,   168,   166,   166,   537,
     165
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
     210,   210,   210,   210,   210,   210,   211,   212,   213,   214,
     216,   215,   217,   218,   220,   219,   221,   221,   222,   222,
     222,   222,   222,   222,   222,   224,   223,   226,   225,   228,
     227,   229,   229,   231,   230,   232,   232,   233,   235,   234,
     237,   236,   238,   238,   239,   241,   240,   243,   242,   245,
     244,   246,   246,   247,   247,   249,   248,   250,   250,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   253,   252,   254,
     254,   254,   254,   256,   255,   258,   257,   260,   259,   261,
     263,   262,   264,   265,   266,   267,   268,   269,   270,   272,
     271,   274,   273,   275,   276,   278,   277,   279,   279,   280,
     280,   280,   280,   280,   281,   282,   283,   284,   285,   287,
     286,   288,   288,   289,   289,   291,   290,   293,   292,   294,
     294,   294,   295,   295,   297,   296,   299,   298,   301,   300,
     302,   302,   303,   303,   303,   303,   303,   303,   304,   305,
     306,   307,   308,   309,   311,   310,   312,   312,   313,   313,
     315,   314,   317,   316,   318,   318,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   321,
     320,   323,   322,   325,   324,   327,   326,   329,   328,   331,
     330,   333,   332,   335,   334,   336,   336,   336,   336,   337,
     339,   338,   340,   340,   341,   341,   343,   342,   344,   344,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   347,   346,
     349,   348,   350,   350,   351,   351,   353,   352,   355,   354,
     356,   356,   357,   357,   358,   358,   358,   358,   358,   358,
     358,   358,   358,   358,   359,   360,   361,   363,   362,   365,
     364,   367,   366,   368,   370,   369,   371,   373,   372,   374,
     374,   375,   375,   377,   376,   379,   378,   380,   380,   381,
     381,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     383,   385,   384,   386,   387,   388,   389,   391,   390,   392,
     392,   393,   393,   395,   394,   397,   396,   398,   398,   399,
     399,   399,   399,   399,   399,   399,   401,   400,   403,   402,
     405,   404,   407,   406,   408,   408,   409,   409,   411,   410,
     413,   412,   414,   414,   415,   415,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   418,   417,   420,   419,   422,   421,   424,   423,   426,
     425,   428,   427,   430,   429,   432,   431,   434,   433,   436,
     435,   438,   437,   440,   439,   442,   441,   443,   443,   445,
     444,   446,   446,   448,   447,   449,   449,   450,   450,   451,
     451,   451,   451,   451,   451,   451,   451,   451,   451,   451,
     452,   454,   453,   455,   456,   458,   457,   459,   459,   460,
     460,   460,   460,   460,   462,   461,   464,   463,   466,   465,
     468,   467,   470,   469,   471,   471,   472,   472,   472,   472,
     472,   472,   472,   472,   472,   472,   472,   472,   472,   472,
     472,   472,   472,   472,   472,   473,   475,   474,   477,   476,
     478,   480,   479,   481,   482,   484,   483,   485,   485,   487,
     486,   488,   489,   490,   492,   491,   493,   493,   493,   493,
     493,   495,   494,   497,   496,   499,   498,   501,   500,   503,
     502,   505,   504,   507,   506,   508,   506,   510,   509,   511,
     511,   512,   512,   514,   513,   516,   515,   518,   517,   519,
     519,   520,   522,   521,   523,   523,   525,   524,   526,   526,
     527,   527,   527,   527,   527,   527,   527,   528,   530,   529,
     532,   531,   533,   533,   535,   534,   536,   536,   537,   537,
     537,   537,   539,   538,   540,   541,   542
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
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
  "\"socket-name\"", "\"queue-control\"", "\"dhcp-ddns\"",
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
  "dhcp_ddns", "$@101", "sub_dhcp_ddns", "$@102", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@103",
  "server_ip", "$@104", "server_port", "sender_ip", "$@105", "sender_port",
  "max_queue_size", "ncr_protocol", "$@106", "ncr_protocol_value",
  "ncr_format", "$@107", "always_include_fqdn", "override_no_update",
  "override_client_update", "replace_client_name", "$@108",
  "replace_client_name_value", "generated_prefix", "$@109",
  "hostname_char_set", "$@110", "hostname_char_replacement", "$@111",
  "dhcp6_json_object", "$@112", "dhcpddns_json_object", "$@113",
  "control_agent_json_object", "$@114", "config_control", "$@115", "$@116",
  "sub_config_control", "$@117", "config_control_params",
  "config_control_param", "config_databases", "$@118", "logging_object",
  "$@119", "sub_logging", "$@120", "logging_params", "logging_param",
  "loggers", "$@121", "loggers_entries", "logger_entry", "$@122",
  "logger_params", "logger_param", "debuglevel", "severity", "$@123",
  "output_options_list", "$@124", "output_options_list_content",
  "output_entry", "$@125", "output_params_list", "output_params", "output",
  "$@126", "flush", "maxsize", "maxver", YY_NULLPTR
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
     461,   462,   463,   464,   465,   466,   469,   474,   479,   484,
     489,   489,   497,   502,   508,   508,   519,   520,   523,   524,
     525,   526,   527,   528,   529,   532,   532,   541,   541,   551,
     551,   558,   559,   562,   562,   569,   571,   575,   581,   581,
     593,   593,   603,   604,   606,   608,   608,   626,   626,   638,
     638,   648,   649,   652,   653,   656,   656,   666,   667,   670,
     671,   672,   673,   674,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   687,   690,   690,   697,
     698,   699,   700,   703,   703,   711,   711,   719,   719,   727,
     732,   732,   740,   745,   750,   755,   760,   765,   770,   775,
     775,   783,   783,   791,   796,   801,   801,   811,   812,   815,
     816,   817,   818,   819,   822,   827,   832,   837,   842,   847,
     847,   857,   858,   861,   862,   865,   865,   875,   875,   885,
     886,   887,   890,   891,   894,   894,   902,   902,   910,   910,
     921,   922,   925,   926,   927,   928,   929,   930,   933,   938,
     943,   948,   953,   958,   966,   966,   979,   980,   983,   984,
     991,   991,  1017,  1017,  1028,  1029,  1033,  1034,  1035,  1036,
    1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,
    1047,  1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1058,
    1058,  1066,  1066,  1074,  1074,  1082,  1082,  1090,  1090,  1098,
    1098,  1106,  1106,  1116,  1116,  1123,  1124,  1125,  1126,  1129,
    1136,  1136,  1147,  1148,  1152,  1153,  1156,  1156,  1164,  1165,
    1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,
    1178,  1179,  1180,  1181,  1182,  1183,  1184,  1185,  1192,  1192,
    1205,  1205,  1214,  1215,  1218,  1219,  1224,  1224,  1239,  1239,
    1253,  1254,  1257,  1258,  1261,  1262,  1263,  1264,  1265,  1266,
    1267,  1268,  1269,  1270,  1273,  1275,  1280,  1282,  1282,  1290,
    1290,  1298,  1298,  1306,  1308,  1308,  1316,  1325,  1325,  1337,
    1338,  1343,  1344,  1349,  1349,  1361,  1361,  1373,  1374,  1379,
    1380,  1385,  1386,  1387,  1388,  1389,  1390,  1391,  1392,  1393,
    1396,  1398,  1398,  1406,  1408,  1410,  1415,  1423,  1423,  1435,
    1436,  1439,  1440,  1443,  1443,  1453,  1453,  1463,  1464,  1467,
    1468,  1469,  1470,  1471,  1472,  1473,  1476,  1476,  1484,  1484,
    1509,  1509,  1539,  1539,  1549,  1550,  1553,  1554,  1557,  1557,
    1566,  1566,  1575,  1576,  1579,  1580,  1584,  1585,  1586,  1587,
    1588,  1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,
    1598,  1601,  1601,  1609,  1609,  1617,  1617,  1625,  1625,  1633,
    1633,  1643,  1643,  1651,  1651,  1659,  1659,  1667,  1667,  1675,
    1675,  1683,  1683,  1691,  1691,  1704,  1704,  1714,  1715,  1721,
    1721,  1731,  1732,  1735,  1735,  1745,  1746,  1749,  1750,  1753,
    1754,  1755,  1756,  1757,  1758,  1759,  1760,  1761,  1762,  1763,
    1766,  1768,  1768,  1776,  1785,  1792,  1792,  1802,  1803,  1806,
    1807,  1808,  1809,  1810,  1813,  1813,  1821,  1821,  1834,  1834,
    1852,  1852,  1864,  1864,  1874,  1875,  1878,  1879,  1880,  1881,
    1882,  1883,  1884,  1885,  1886,  1887,  1888,  1889,  1890,  1891,
    1892,  1893,  1894,  1895,  1896,  1899,  1904,  1904,  1912,  1912,
    1920,  1925,  1925,  1933,  1938,  1943,  1943,  1951,  1952,  1955,
    1955,  1963,  1968,  1973,  1978,  1978,  1986,  1989,  1992,  1995,
    1998,  2004,  2004,  2012,  2012,  2020,  2020,  2031,  2031,  2038,
    2038,  2045,  2045,  2052,  2052,  2061,  2061,  2072,  2072,  2082,
    2083,  2087,  2088,  2091,  2091,  2106,  2106,  2116,  2116,  2127,
    2128,  2132,  2136,  2136,  2148,  2149,  2153,  2153,  2161,  2162,
    2165,  2166,  2167,  2168,  2169,  2170,  2171,  2174,  2179,  2179,
    2187,  2187,  2197,  2198,  2201,  2201,  2209,  2210,  2213,  2214,
    2215,  2216,  2219,  2219,  2227,  2232,  2237
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
#line 4893 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2242 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
