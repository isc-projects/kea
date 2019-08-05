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
      case 194: // value
      case 198: // map_value
      case 244: // socket_type
      case 247: // outbound_interface_value
      case 269: // db_type
      case 355: // hr_mode
      case 504: // ncr_protocol_value
      case 511: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 177: // "boolean"
        value.move< bool > (that.value);
        break;

      case 176: // "floating point"
        value.move< double > (that.value);
        break;

      case 175: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 174: // "constant string"
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
      case 194: // value
      case 198: // map_value
      case 244: // socket_type
      case 247: // outbound_interface_value
      case 269: // db_type
      case 355: // hr_mode
      case 504: // ncr_protocol_value
      case 511: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 177: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 176: // "floating point"
        value.copy< double > (that.value);
        break;

      case 175: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 174: // "constant string"
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
            case 174: // "constant string"

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 175: // "integer"

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 176: // "floating point"

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 177: // "boolean"

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 194: // value

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 198: // map_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 244: // socket_type

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 247: // outbound_interface_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 269: // db_type

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 355: // hr_mode

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 504: // ncr_protocol_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 511: // replace_client_name_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 194: // value
      case 198: // map_value
      case 244: // socket_type
      case 247: // outbound_interface_value
      case 269: // db_type
      case 355: // hr_mode
      case 504: // ncr_protocol_value
      case 511: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 177: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 176: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 175: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 174: // "constant string"
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
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 286 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 287 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 290 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 340 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 362 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 366 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 392 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 416 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1129 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1138 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1269 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1280 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 661 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 694 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1381 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 750 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 751 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1430 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 753 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1723 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1027 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1135 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2023 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1159 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1167 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1173 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1191 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2138 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2156 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2165 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2365 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2374 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2581 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2858 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2916 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1807 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2936 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3038 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1915 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 3094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2049 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2050 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2079 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2082 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2085 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2088 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2091 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2124 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3437 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 623:
#line 2138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3475 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2185 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 643:
#line 2225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 644:
#line 2230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3581 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2246 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 658:
#line 2263 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 659:
#line 2268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 660:
#line 2270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 661:
#line 2276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 662:
#line 2281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 665:
#line 2290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 666:
#line 2294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 674:
#line 2309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 675:
#line 2311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 676:
#line 2317 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 677:
#line 2322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 678:
#line 2327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 679:
#line 2332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 680:
#line 2334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3727 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3731 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -837;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     317,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,    32,    21,    71,    80,    98,
     114,   132,   136,   155,   183,   192,   209,   252,   260,   263,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,    21,    27,
      17,   123,    75,   227,    39,   234,   164,    28,   154,   -41,
     515,   134,   117,  -837,   274,   278,   287,   284,   290,  -837,
    -837,  -837,  -837,  -837,   302,  -837,    44,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   303,   316,   337,  -837,
    -837,  -837,  -837,  -837,  -837,   346,   347,   354,   356,   357,
     358,   359,   360,   361,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   362,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,    57,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,   363,  -837,    78,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   365,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,    90,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,    93,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   313,   345,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   364,  -837,
    -837,   366,  -837,  -837,  -837,   369,  -837,  -837,   367,   373,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   374,   375,  -837,  -837,  -837,  -837,   372,
     378,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,    96,  -837,  -837,  -837,   380,  -837,  -837,
     384,  -837,   387,   388,  -837,  -837,   389,   390,  -837,  -837,
    -837,  -837,  -837,   106,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     108,  -837,  -837,  -837,   392,   112,  -837,  -837,  -837,  -837,
      21,    21,  -837,   225,   402,   403,   405,   407,   408,  -837,
      17,  -837,   409,   411,   415,   200,   243,   244,   419,   425,
     434,   437,   439,   440,   267,   270,   283,   286,   295,   282,
     296,   297,   299,   458,   467,   471,   487,   488,   489,   498,
     499,   501,   502,   503,   504,   507,   338,   508,   510,   511,
     512,   513,   514,   123,  -837,   516,   517,   520,   342,    75,
    -837,   522,   524,   525,   526,   527,   528,   368,   529,   531,
     532,   227,  -837,   535,    39,  -837,   536,   538,   542,   543,
     544,   545,   546,   547,  -837,   234,  -837,   549,   550,   381,
     551,   553,   554,   382,  -837,    28,   556,   385,   386,  -837,
     154,   560,   561,    46,  -837,   391,   562,   563,   394,   567,
     398,   399,   572,   573,   404,   406,   575,   576,   515,  -837,
     134,  -837,   580,   410,   117,  -837,  -837,  -837,   582,   581,
     583,    21,    21,    21,  -837,   584,   586,   587,  -837,  -837,
    -837,   413,   418,   422,   590,   591,   597,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   430,   600,   601,   602,
     603,   604,   435,   240,   605,   608,   609,   610,   611,  -837,
     613,   604,   615,   442,   443,   649,  -837,   650,   153,   221,
    -837,  -837,   482,   484,   485,   657,   490,   491,  -837,   650,
     492,   656,  -837,   493,  -837,   650,   494,   495,   496,   497,
     500,   505,   506,  -837,   509,   518,  -837,   519,   521,   523,
    -837,  -837,   530,  -837,  -837,  -837,   533,    21,  -837,  -837,
     534,   537,  -837,   539,  -837,  -837,    26,   449,  -837,  -837,
     -16,   540,  -837,  -837,   667,  -837,  -837,    21,   123,   134,
    -837,  -837,  -837,   117,    75,   651,  -837,  -837,  -837,   585,
     585,   666,  -837,   669,   670,   671,   674,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   198,   675,   677,   678,   158,
     -34,  -837,   515,  -837,  -837,   679,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   680,  -837,  -837,
    -837,  -837,   143,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   666,  -837,   133,   139,   169,   170,
    -837,   202,  -837,  -837,  -837,  -837,  -837,  -837,   684,   686,
     687,   690,   692,  -837,  -837,  -837,  -837,   694,   695,   696,
     697,   698,  -837,   203,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   206,  -837,   699,   700,  -837,  -837,
     703,   707,  -837,  -837,   706,   712,  -837,  -837,   710,   714,
    -837,  -837,   713,   715,  -837,  -837,  -837,  -837,  -837,  -837,
      42,  -837,  -837,  -837,  -837,  -837,  -837,  -837,    77,  -837,
    -837,   716,   717,  -837,  -837,   718,   720,  -837,   702,   721,
     722,   723,   724,   725,   212,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   216,  -837,  -837,
    -837,   229,  -837,   219,  -837,   557,  -837,   726,   727,  -837,
    -837,  -837,  -837,   728,   729,  -837,  -837,  -837,  -837,   730,
     651,  -837,   733,   734,   735,   736,   558,   564,   568,   565,
     569,   741,   742,   743,   744,   574,   577,   578,   579,   588,
     585,  -837,  -837,   585,  -837,   666,   227,  -837,   669,    28,
    -837,   670,   154,  -837,   671,   438,  -837,   674,   198,  -837,
      47,   675,  -837,   234,  -837,   677,   -41,  -837,   678,   589,
     592,   593,   594,   595,   596,   158,  -837,   746,   747,   -34,
    -837,  -837,   194,   679,  -837,  -837,   749,   753,    39,  -837,
     680,   754,  -837,  -837,   598,  -837,   319,   599,   606,   607,
    -837,  -837,  -837,  -837,  -837,   614,   617,   619,   620,  -837,
    -837,  -837,  -837,  -837,  -837,   232,  -837,   242,  -837,   752,
    -837,   755,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     257,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   757,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   758,   759,  -837,  -837,  -837,  -837,  -837,   766,
    -837,   300,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     625,   634,  -837,  -837,   771,  -837,  -837,  -837,  -837,  -837,
     314,  -837,  -837,  -837,  -837,  -837,  -837,   635,   341,  -837,
     650,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   438,  -837,
     772,   637,  -837,    47,  -837,  -837,  -837,  -837,   773,   612,
     774,   194,  -837,  -837,  -837,  -837,  -837,   642,  -837,  -837,
     777,  -837,   659,  -837,  -837,   750,  -837,  -837,   255,  -837,
      13,   750,  -837,  -837,   775,   779,   780,  -837,   344,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   781,   648,   661,   664,
     838,    13,  -837,   708,  -837,  -837,  -837,   709,  -837,  -837,
    -837
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   141,     9,   284,    11,
     449,    13,   474,    15,   374,    17,   382,    19,   419,    21,
     249,    23,   566,    25,   638,    27,   627,    29,    47,    41,
       0,     0,     0,     0,     0,   476,     0,   384,   421,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     636,   619,   621,   623,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   625,   130,   156,     0,     0,     0,   495,
     497,   499,   154,   163,   165,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   276,   372,   411,   338,   462,
     464,   331,   227,   523,   466,   241,   260,     0,   549,   562,
     564,   615,   617,   643,   115,     0,    72,    74,    75,    76,
      77,    78,   109,   110,   111,    79,   107,    96,    97,    98,
      82,    83,   104,    84,    85,    86,    90,    91,    80,   108,
      81,    88,    89,   102,   103,   105,    99,   100,   101,    87,
      92,    93,    94,    95,   113,   114,   106,   112,   143,   145,
     149,     0,   140,     0,   132,   134,   135,   136,   137,   138,
     139,   319,   321,   323,   441,   317,   325,     0,   329,   327,
     519,   316,   288,   289,   290,   291,   292,   313,   314,   315,
     303,   304,     0,   286,   295,   308,   309,   310,   296,   298,
     299,   301,   297,   293,   294,   311,   312,   300,   305,   306,
     307,   302,   460,   459,   455,   456,   454,     0,   451,   453,
     457,   458,   517,   505,   507,   511,   509,   515,   513,   501,
     494,   488,   492,   493,     0,   477,   478,   489,   490,   491,
     485,   480,   486,   482,   483,   484,   487,   481,     0,   401,
     208,     0,   405,   403,   408,     0,   397,   398,     0,   385,
     386,   388,   400,   389,   390,   391,   407,   392,   393,   394,
     395,   396,   435,     0,     0,   433,   434,   437,   438,     0,
     422,   423,   425,   426,   427,   428,   429,   430,   431,   432,
     256,   258,   253,     0,   251,   254,   255,     0,   589,   591,
       0,   594,     0,     0,   598,   602,     0,     0,   606,   613,
     587,   585,   586,     0,   568,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
       0,   640,   642,   633,     0,     0,   629,   631,   632,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     0,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   285,     0,     0,   450,     0,     0,     0,     0,
       0,     0,     0,     0,   475,     0,   375,     0,     0,     0,
       0,     0,     0,     0,   383,     0,     0,     0,     0,   420,
       0,     0,     0,     0,   250,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   567,
       0,   639,     0,     0,     0,   628,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   548,
       0,     0,     0,     0,     0,     0,    73,     0,     0,     0,
     153,   133,     0,     0,     0,     0,     0,     0,   337,     0,
       0,     0,   287,     0,   452,     0,     0,     0,     0,     0,
       0,     0,     0,   479,     0,     0,   399,     0,     0,     0,
     410,   387,     0,   439,   440,   424,     0,     0,   252,   588,
       0,     0,   593,     0,   596,   597,     0,     0,   604,   605,
       0,     0,   569,   641,     0,   635,   630,     0,     0,     0,
     620,   622,   624,     0,     0,     0,   496,   498,   500,     0,
       0,   167,   126,   278,   376,   413,   340,    40,   463,   465,
     333,   334,   335,   336,   332,     0,     0,   468,   243,     0,
       0,   563,     0,   616,   618,     0,    51,   144,   147,   148,
     146,   151,   152,   150,   320,   322,   324,   443,   318,   326,
     330,   328,     0,   461,   518,   506,   508,   512,   510,   516,
     514,   502,   402,   209,   406,   404,   409,   436,   257,   259,
     590,   592,   595,   600,   601,   599,   603,   608,   609,   610,
     611,   612,   607,   614,   167,    44,     0,     0,     0,     0,
     161,     0,   158,   160,   195,   201,   203,   205,     0,     0,
       0,     0,     0,   217,   219,   221,   223,     0,     0,     0,
       0,     0,   194,     0,   173,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   188,   189,   190,   185,   191,
     192,   193,   186,   187,     0,   171,     0,   168,   169,   282,
       0,   279,   280,   380,     0,   377,   378,   417,     0,   414,
     415,   344,     0,   341,   342,   236,   237,   238,   239,   240,
       0,   229,   231,   232,   233,   234,   235,   527,     0,   525,
     472,     0,   469,   470,   247,     0,   244,   245,     0,     0,
       0,     0,     0,     0,     0,   262,   264,   265,   266,   267,
     268,   269,   558,   560,   557,   555,   556,     0,   551,   553,
     554,     0,   647,     0,   645,    53,   447,     0,   444,   445,
     503,   521,   522,     0,     0,    69,   637,   626,   131,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155,   164,     0,   166,     0,     0,   277,     0,   384,
     373,     0,   421,   412,     0,     0,   339,     0,     0,   228,
     529,     0,   524,   476,   467,     0,     0,   242,     0,     0,
       0,     0,     0,     0,     0,     0,   261,     0,     0,     0,
     550,   565,     0,     0,   644,    55,     0,    54,     0,   442,
       0,     0,   520,   634,     0,   159,     0,     0,     0,     0,
     207,   210,   211,   212,   213,     0,     0,     0,     0,   225,
     226,   214,   215,   216,   174,     0,   170,     0,   281,     0,
     379,     0,   416,   371,   363,   364,   365,   351,   352,   368,
     369,   370,   354,   355,   348,   349,   350,   361,   362,   360,
       0,   346,   353,   366,   367,   356,   357,   358,   359,   343,
     230,   545,     0,   543,   544,   536,   537,   541,   542,   538,
     539,   540,     0,   530,   531,   533,   534,   535,   526,     0,
     471,     0,   246,   270,   271,   272,   273,   274,   275,   263,
       0,     0,   552,   661,     0,   659,   657,   651,   655,   656,
       0,   649,   653,   654,   652,   646,    52,     0,     0,   446,
       0,   162,   197,   198,   199,   200,   196,   202,   204,   206,
     218,   220,   222,   224,   172,   283,   381,   418,     0,   345,
       0,     0,   528,     0,   473,   248,   559,   561,     0,     0,
       0,     0,   648,    56,   448,   504,   347,     0,   547,   532,
       0,   658,     0,   650,   546,     0,   660,   665,     0,   663,
       0,     0,   662,   674,     0,     0,     0,   679,     0,   667,
     669,   670,   671,   672,   673,   664,     0,     0,     0,     0,
       0,     0,   666,     0,   676,   677,   678,     0,   668,   675,
     680
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -46,  -837,  -468,  -837,
     180,  -837,  -837,  -837,  -837,  -837,  -837,  -534,  -837,  -837,
    -837,   -70,  -837,  -837,  -837,   464,  -837,  -837,  -837,  -837,
     237,   429,   -55,   -54,   -27,   -24,    -9,     6,     9,    11,
    -837,  -837,  -837,  -837,    12,    19,  -837,  -837,   247,   451,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,    55,  -837,  -837,  -837,
    -837,  -837,  -837,   195,  -837,    31,  -837,  -607,    38,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   -35,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    24,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    16,  -837,  -837,  -837,    14,   423,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,    10,  -837,  -837,  -837,  -837,  -837,
    -837,  -836,  -837,  -837,  -837,    40,  -837,  -837,  -837,    41,
     459,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -828,
    -837,   -17,  -837,    -5,  -837,    22,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,    34,  -837,  -837,  -129,   -65,  -837,  -837,
    -837,  -837,  -837,    43,  -837,  -837,  -837,    48,  -837,   441,
    -837,   -72,  -837,  -837,  -837,  -837,  -837,   -66,  -837,  -837,
    -837,  -837,  -837,    -7,  -837,  -837,  -837,    45,  -837,  -837,
    -837,    49,  -837,   432,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,     3,  -837,  -837,  -837,     7,
     466,  -837,  -837,   -39,  -837,   -19,  -837,   -59,  -837,  -837,
    -837,    33,  -837,  -837,  -837,    50,  -837,   457,   -58,  -837,
     -52,  -837,    -1,  -837,   251,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -825,  -837,  -837,  -837,  -837,  -837,    51,  -837,
    -837,  -837,  -119,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    29,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   273,   428,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -64,  -837,   -60,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     304,   426,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   310,
     431,   -57,  -837,  -837,    35,  -837,  -837,  -117,  -837,  -837,
    -837,  -837,  -837,  -837,  -136,  -837,  -837,  -155,  -837,  -837,
    -837,  -837,  -837,  -837,  -837
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     628,    87,    88,    41,    68,    84,    85,   647,   815,   896,
     897,   722,    43,    70,    96,    97,    98,   374,    45,    71,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   403,   157,   158,   159,   160,   383,   193,   194,
      47,    72,   195,   425,   196,   426,   650,   197,   427,   653,
     198,   161,   391,   162,   384,   701,   702,   703,   829,   163,
     392,   164,   393,   746,   747,   748,   853,   723,   724,   725,
     832,  1016,   726,   833,   727,   834,   728,   835,   729,   730,
     458,   731,   732,   733,   734,   735,   736,   737,   738,   841,
     739,   842,   740,   843,   741,   844,   742,   743,   165,   411,
     770,   771,   772,   773,   774,   775,   776,   166,   414,   785,
     786,   787,   876,    61,    79,   323,   324,   325,   471,   326,
     472,   167,   415,   794,   795,   796,   797,   798,   799,   800,
     801,   168,   404,   750,   751,   752,   856,    49,    73,   222,
     223,   224,   435,   225,   431,   226,   432,   227,   433,   228,
     436,   229,   439,   230,   438,   169,   410,   634,   232,   170,
     407,   762,   763,   764,   865,   950,   951,   171,   405,    55,
      76,   754,   755,   756,   859,    57,    77,   288,   289,   290,
     291,   292,   293,   294,   457,   295,   461,   296,   460,   297,
     298,   462,   299,   172,   406,   758,   759,   760,   862,    59,
      78,   309,   310,   311,   312,   313,   466,   314,   315,   316,
     317,   234,   434,   817,   818,   819,   898,    51,    74,   247,
     248,   249,   443,   173,   408,   174,   409,   175,   413,   781,
     782,   783,   873,    53,    75,   264,   265,   266,   176,   388,
     177,   389,   178,   390,   270,   453,   822,   901,   271,   447,
     272,   448,   273,   450,   274,   449,   275,   452,   276,   451,
     277,   446,   241,   440,   823,   179,   412,   778,   779,   870,
     972,   973,   974,   975,   976,  1030,   977,   180,   181,   417,
     807,   808,   809,   887,   810,   888,   182,   418,   183,   419,
      63,    80,   343,   344,   345,   346,   476,   347,   477,   348,
     349,   479,   350,   351,   352,   482,   685,   353,   483,   354,
     355,   356,   486,   692,   357,   487,   184,   420,   185,   421,
      99,   376,   100,   377,   101,   378,   186,   382,    67,    82,
     365,   366,   367,   492,   368,   102,   375,    65,    81,   360,
     361,   187,   422,   813,   814,   892,  1000,  1001,  1002,  1003,
    1040,  1004,  1038,  1058,  1059,  1060,  1068,  1069,  1070,  1076,
    1071,  1072,  1073,  1074,  1080
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   144,   192,   211,   243,   260,   307,   286,   305,   322,
     340,   278,   308,   744,   237,   238,   358,   267,   212,   213,
     359,   239,    83,   268,   362,   660,    31,    89,    32,   945,
      33,   664,    30,   199,   235,   250,   262,   946,   300,   318,
     958,   341,   287,   306,   683,   868,   214,   380,   869,   215,
     129,   130,   381,   200,   236,   251,   263,   244,   301,   319,
     423,   342,   279,   627,   216,   424,   233,   246,   261,   245,
     320,   321,   240,   627,   269,   109,   110,   111,    42,   217,
     871,   429,   218,   872,   219,   220,   430,    44,   802,   803,
     188,   189,   221,   441,   190,   231,   444,   191,   442,   473,
     280,   445,   281,   282,   474,    46,   283,   284,   285,   488,
     127,   490,   129,   130,   489,   494,   491,   126,   127,   280,
     495,    48,   242,   129,   130,   687,   688,   689,   690,   363,
     364,   129,   130,    94,   103,   208,   423,   104,   209,    50,
      94,   825,   490,    52,   961,   962,   105,   826,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   320,   321,   129,
     130,   691,    54,  1063,    90,   684,  1064,  1065,  1066,  1067,
     648,   649,   494,   429,    91,    92,    93,   827,   828,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      56,    94,   945,   126,   127,    34,    35,    36,    37,    58,
     946,    86,    94,   958,   128,   830,   850,   129,   130,   850,
     831,   851,   131,    94,   852,   885,    60,   132,   133,   889,
     886,    94,   893,   134,   890,   894,   280,   302,   281,   282,
     303,   304,   488,   135,   126,   850,   136,   891,   129,   130,
    1024,   651,   652,   137,   138,   441,   925,   139,   140,    94,
    1025,   259,   820,   107,   108,   109,   110,   111,  1061,    62,
    1028,  1062,   109,   110,   111,  1029,   280,    64,   141,   142,
      66,   143,   788,   789,   790,   791,   792,   793,   129,   130,
     369,   370,   143,   115,   116,   117,   118,   119,   120,   121,
     122,   371,   372,   373,   201,   202,   203,    94,   127,   765,
     766,   767,   768,   473,   769,   127,   379,   385,  1035,   204,
      95,   129,   130,   205,   206,   207,   131,  1041,   129,   130,
     386,   454,  1042,   208,   496,   497,   209,   134,    94,   252,
     630,   631,   632,   633,   210,   253,   254,   255,   256,   257,
     258,   387,   259,   993,   444,   994,   995,  1081,   455,  1044,
     394,   395,  1082,   144,  1012,  1013,  1014,  1015,   396,   192,
     397,   398,   399,   400,   401,   402,   416,   428,    94,   437,
     459,   211,   456,   463,   243,   464,   465,   508,   467,   468,
     469,   470,   237,   238,   475,   260,   212,   213,   478,   239,
     199,   480,   481,   484,   485,   286,   493,   267,   307,   498,
     305,    94,   235,   268,   308,   250,   499,   500,    94,   501,
     200,   502,   503,   505,   214,   506,   262,   215,   340,   507,
     509,   510,   236,   511,   358,   251,   300,   244,   359,   512,
     287,   318,   216,   362,   233,   306,   263,   246,   513,   245,
     240,   514,   517,   515,   516,   518,   301,   217,   261,   341,
     218,   319,   219,   220,   269,   610,   611,   612,   519,   522,
     221,   520,   526,   231,   107,   108,   109,   110,   111,   342,
     521,   527,   523,   524,   525,   528,  1045,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   529,   530,   531,   115,   116,   117,   118,   119,   120,
     121,   122,   532,   533,   125,   534,   535,   536,   537,   127,
     280,   538,   540,   539,   541,   542,   543,   544,   545,   550,
     547,   548,   129,   130,   549,   206,   552,   131,   553,   554,
     555,   556,   557,   559,   208,   560,   561,   209,   144,   563,
     565,   679,   566,   558,   192,   210,   567,   568,   569,   570,
     571,   572,   362,   574,   575,   577,   576,   578,   579,   580,
     582,   695,   583,   584,   586,   587,   590,   591,   589,   592,
     804,   593,   340,   594,   595,   199,   596,   597,   358,   600,
     601,   598,   359,   599,   604,   605,   607,   616,   608,   686,
     609,   613,   617,   614,   615,   200,   618,   619,   620,   129,
     130,   805,   621,   341,   622,   623,   624,   625,   626,   629,
     635,    32,    94,   636,   637,   638,   643,   644,   639,   704,
     640,   806,   642,   342,   705,   706,   707,   708,   709,   710,
     711,   712,   713,   714,   715,   716,   717,   718,   719,   720,
     721,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   645,   646,   654,   280,   655,   656,
     141,   142,   657,   662,   658,   659,   661,   663,   665,   666,
     667,   668,   694,   745,   669,   700,   749,   753,   757,   670,
     671,   761,   777,   672,   780,   784,   812,   816,   836,    94,
     837,   838,   673,   674,   839,   675,   840,   676,   845,   846,
     847,   848,   849,   855,   677,   854,   879,   678,   680,   857,
     858,   681,   860,   682,   693,   861,   863,   864,   867,   866,
     875,   641,   874,   878,   877,   880,   881,   882,   883,   884,
     900,   895,   899,   910,   904,   903,   902,   906,   907,   908,
     909,   911,   913,   912,   914,   915,   916,   917,   918,   919,
     990,   991,   920,   921,   922,  1006,  1007,  1057,  1010,    94,
    1026,  1031,  1033,  1027,   983,   923,  1032,   984,   985,   986,
     987,   988,  1011,  1017,  1034,  1039,  1047,  1050,  1052,  1077,
    1018,  1019,  1055,  1078,  1079,  1083,   211,  1051,  1020,   286,
     307,  1021,   305,  1022,  1023,   933,   308,   237,   238,  1036,
     963,   212,   213,   260,   239,   965,   322,   955,  1037,  1043,
     934,   935,   969,   956,  1048,   267,  1054,   235,   970,   804,
     300,   268,   996,   318,   287,  1084,   953,   306,   243,   214,
     944,   967,   215,  1056,   262,   964,  1085,   236,   936,  1086,
     301,   937,  1087,   319,   504,   696,   954,   216,   947,   233,
     805,   968,   546,   998,   263,   240,   938,   997,   952,   250,
     948,   699,   217,   966,   957,   218,   261,   219,   220,   971,
     806,   939,   269,   999,   940,   221,   941,   942,   231,   251,
     551,   244,  1089,  1090,   943,   905,   926,   949,   924,   824,
     981,   246,   960,   245,   982,   989,   588,   927,   928,  1046,
     562,   959,   585,  1009,   930,  1008,   581,   929,   980,   932,
     564,   931,   573,   821,  1049,   811,   602,   698,   992,   697,
     606,   603,   978,   979,  1053,  1075,  1088,     0,  1005,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   933,     0,
       0,     0,     0,   963,     0,     0,     0,     0,   965,     0,
     955,   996,     0,   934,   935,   969,   956,     0,     0,     0,
       0,   970,     0,     0,     0,     0,     0,     0,     0,   953,
       0,     0,     0,   944,   967,     0,     0,     0,   964,     0,
       0,   936,   998,     0,   937,     0,   997,     0,     0,   954,
       0,   947,     0,     0,   968,     0,     0,     0,     0,   938,
       0,   952,   999,   948,     0,     0,   966,   957,     0,     0,
       0,     0,   971,     0,   939,     0,     0,   940,     0,   941,
     942,     0,     0,     0,     0,     0,     0,   943,     0,     0,
     949
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    78,   620,    73,    73,    80,    75,    73,    73,
      80,    73,    68,    75,    81,   559,     5,    10,     7,   865,
       9,   565,     0,    72,    73,    74,    75,   865,    77,    78,
     865,    80,    77,    78,    18,     3,    73,     3,     6,    73,
      84,    85,     8,    72,    73,    74,    75,    74,    77,    78,
       3,    80,    34,   531,    73,     8,    73,    74,    75,    74,
     111,   112,    73,   541,    75,    28,    29,    30,     7,    73,
       3,     3,    73,     6,    73,    73,     8,     7,   122,   123,
      15,    16,    73,     3,    19,    73,     3,    22,     8,     3,
      72,     8,    74,    75,     8,     7,    78,    79,    80,     3,
      71,     3,    84,    85,     8,     3,     8,    70,    71,    72,
       8,     7,    83,    84,    85,   141,   142,   143,   144,    12,
      13,    84,    85,   174,    11,    96,     3,    14,    99,     7,
     174,     8,     3,     7,    97,    98,    23,     8,    25,    26,
      27,    28,    29,    30,    31,    32,    33,   111,   112,    84,
      85,   177,     7,   150,   147,   139,   153,   154,   155,   156,
      17,    18,     3,     3,   157,   158,   159,     8,     8,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
       7,   174,  1028,    70,    71,   174,   175,   176,   177,     7,
    1028,   174,   174,  1028,    81,     3,     3,    84,    85,     3,
       8,     8,    89,   174,     8,     3,     7,    94,    95,     3,
       8,   174,     3,   100,     8,     6,    72,    73,    74,    75,
      76,    77,     3,   110,    70,     3,   113,     8,    84,    85,
       8,    20,    21,   120,   121,     3,   853,   124,   125,   174,
       8,   108,   109,    26,    27,    28,    29,    30,     3,     7,
       3,     6,    28,    29,    30,     8,    72,     7,   145,   146,
       7,   148,   114,   115,   116,   117,   118,   119,    84,    85,
       6,     3,   148,    56,    57,    58,    59,    60,    61,    62,
      63,     4,     8,     3,    67,    68,    69,   174,    71,   101,
     102,   103,   104,     3,   106,    71,     4,     4,     8,    82,
     380,    84,    85,    86,    87,    88,    89,     3,    84,    85,
       4,     8,     8,    96,   370,   371,    99,   100,   174,    95,
      90,    91,    92,    93,   107,   101,   102,   103,   104,   105,
     106,     4,   108,   149,     3,   151,   152,     3,     3,     8,
       4,     4,     8,   423,    35,    36,    37,    38,     4,   429,
       4,     4,     4,     4,     4,     4,     4,     4,   174,     4,
       4,   441,     8,     4,   444,     8,     3,   177,     4,     4,
       8,     3,   441,   441,     4,   455,   441,   441,     4,   441,
     429,     4,     4,     4,     4,   465,     4,   455,   470,   174,
     470,   174,   441,   455,   470,   444,     4,     4,   174,     4,
     429,     4,     4,     4,   441,     4,   455,   441,   488,     4,
     177,   177,   441,     4,   488,   444,   465,   444,   488,     4,
     465,   470,   441,   490,   441,   470,   455,   444,     4,   444,
     441,     4,   175,     4,     4,   175,   465,   441,   455,   488,
     441,   470,   441,   441,   455,   501,   502,   503,   175,   177,
     441,   175,     4,   441,    26,    27,    28,    29,    30,   488,
     175,     4,   176,   176,   175,     4,  1010,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     4,     4,     4,    56,    57,    58,    59,    60,    61,
      62,    63,     4,     4,    66,     4,     4,     4,     4,    71,
      72,     4,     4,   175,     4,     4,     4,     4,     4,   177,
       4,     4,    84,    85,     4,    87,     4,    89,     4,     4,
       4,     4,     4,     4,    96,     4,     4,    99,   608,     4,
       4,   587,     4,   175,   614,   107,     4,     4,     4,     4,
       4,     4,   609,     4,     4,     4,   175,     4,     4,   177,
       4,   607,   177,   177,     4,     4,     4,     4,   177,   175,
     640,     4,   642,   175,   175,   614,     4,     4,   642,     4,
       4,   177,   642,   177,     4,   175,     4,   174,     7,   140,
       7,     7,   174,     7,     7,   614,   174,     7,     7,    84,
      85,   640,     5,   642,   174,     5,     5,     5,     5,   174,
       5,     7,   174,     5,     5,     5,   174,   174,     7,    34,
       7,   640,     7,   642,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,     5,     5,   174,    72,   174,   174,
     145,   146,     5,     7,   174,   174,   174,   174,   174,   174,
     174,   174,     5,     7,   174,    24,     7,     7,     7,   174,
     174,     7,     7,   174,     7,     7,     7,     7,     4,   174,
       4,     4,   174,   174,     4,   174,     4,   174,     4,     4,
       4,     4,     4,     3,   174,     6,     4,   174,   174,     6,
       3,   174,     6,   174,   174,     3,     6,     3,     3,     6,
       3,   541,     6,     3,     6,     4,     4,     4,     4,     4,
       3,   174,     6,   175,     4,     6,     8,     4,     4,     4,
       4,   177,   177,   175,   175,     4,     4,     4,     4,   175,
       4,     4,   175,   175,   175,     6,     3,     7,     4,   174,
       8,     4,     3,     8,   175,   177,     8,   175,   175,   175,
     175,   175,   174,   174,     8,     4,     4,     4,     4,     4,
     174,   174,     5,     4,     4,     4,   856,   175,   174,   859,
     862,   174,   862,   174,   174,   865,   862,   856,   856,   174,
     870,   856,   856,   873,   856,   870,   876,   865,   174,   174,
     865,   865,   870,   865,   177,   873,   174,   856,   870,   889,
     859,   873,   892,   862,   859,   177,   865,   862,   898,   856,
     865,   870,   856,   174,   873,   870,   175,   856,   865,   175,
     859,   865,     4,   862,   380,   608,   865,   856,   865,   856,
     889,   870,   423,   892,   873,   856,   865,   892,   865,   898,
     865,   614,   856,   870,   865,   856,   873,   856,   856,   870,
     889,   865,   873,   892,   865,   856,   865,   865,   856,   898,
     429,   898,   174,   174,   865,   830,   855,   865,   850,   694,
     876,   898,   868,   898,   878,   885,   473,   856,   858,  1028,
     441,   867,   470,   900,   861,   898,   465,   859,   875,   864,
     444,   862,   455,   662,  1033,   642,   488,   613,   889,   609,
     494,   490,   871,   873,  1041,  1061,  1081,    -1,   893,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1028,    -1,
      -1,    -1,    -1,  1033,    -1,    -1,    -1,    -1,  1033,    -1,
    1028,  1041,    -1,  1028,  1028,  1033,  1028,    -1,    -1,    -1,
      -1,  1033,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1028,
      -1,    -1,    -1,  1028,  1033,    -1,    -1,    -1,  1033,    -1,
      -1,  1028,  1041,    -1,  1028,    -1,  1041,    -1,    -1,  1028,
      -1,  1028,    -1,    -1,  1033,    -1,    -1,    -1,    -1,  1028,
      -1,  1028,  1041,  1028,    -1,    -1,  1033,  1028,    -1,    -1,
      -1,    -1,  1033,    -1,  1028,    -1,    -1,  1028,    -1,  1028,
    1028,    -1,    -1,    -1,    -1,    -1,    -1,  1028,    -1,    -1,
    1028
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
       0,     5,     7,     9,   174,   175,   176,   177,   194,   195,
     196,   201,     7,   210,     7,   216,     7,   238,     7,   335,
       7,   415,     7,   431,     7,   367,     7,   373,     7,   397,
       7,   311,     7,   488,     7,   535,     7,   526,   202,   197,
     211,   217,   239,   336,   416,   432,   368,   374,   398,   312,
     489,   536,   527,   194,   203,   204,   174,   199,   200,    10,
     147,   157,   158,   159,   174,   209,   212,   213,   214,   518,
     520,   522,   533,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    70,    71,    81,    84,
      85,    89,    94,    95,   100,   110,   113,   120,   121,   124,
     125,   145,   146,   148,   209,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   231,   232,   233,
     234,   249,   251,   257,   259,   296,   305,   319,   329,   353,
     357,   365,   391,   421,   423,   425,   436,   438,   440,   463,
     475,   476,   484,   486,   514,   516,   524,   539,    15,    16,
      19,    22,   209,   236,   237,   240,   242,   245,   248,   421,
     423,    67,    68,    69,    82,    86,    87,    88,    96,    99,
     107,   209,   220,   221,   222,   223,   224,   225,   226,   227,
     232,   233,   337,   338,   339,   341,   343,   345,   347,   349,
     351,   353,   356,   391,   409,   421,   423,   425,   436,   438,
     440,   460,    83,   209,   349,   351,   391,   417,   418,   419,
     421,   423,    95,   101,   102,   103,   104,   105,   106,   108,
     209,   391,   421,   423,   433,   434,   435,   436,   438,   440,
     442,   446,   448,   450,   452,   454,   456,   458,   365,    34,
      72,    74,    75,    78,    79,    80,   209,   277,   375,   376,
     377,   378,   379,   380,   381,   383,   385,   387,   388,   390,
     421,   423,    73,    76,    77,   209,   277,   379,   385,   399,
     400,   401,   402,   403,   405,   406,   407,   408,   421,   423,
     111,   112,   209,   313,   314,   315,   317,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     209,   421,   423,   490,   491,   492,   493,   495,   497,   498,
     500,   501,   502,   505,   507,   508,   509,   512,   514,   516,
     537,   538,   539,    12,    13,   528,   529,   530,   532,     6,
       3,     4,     8,     3,   215,   534,   519,   521,   523,     4,
       3,     8,   525,   235,   252,     4,     4,     4,   437,   439,
     441,   250,   258,   260,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   230,   330,   366,   392,   358,   422,   424,
     354,   297,   464,   426,   306,   320,     4,   477,   485,   487,
     515,   517,   540,     3,     8,   241,   243,   246,     4,     3,
       8,   342,   344,   346,   410,   340,   348,     4,   352,   350,
     461,     3,     8,   420,     3,     8,   459,   447,   449,   453,
     451,   457,   455,   443,     8,     3,     8,   382,   278,     4,
     386,   384,   389,     4,     8,     3,   404,     4,     4,     8,
       3,   316,   318,     3,     8,     4,   494,   496,     4,   499,
       4,     4,   503,   506,     4,     4,   510,   513,     3,     8,
       3,     8,   531,     4,     3,     8,   194,   194,   174,     4,
       4,     4,     4,     4,   213,     4,     4,     4,   177,   177,
     177,     4,     4,     4,     4,     4,     4,   175,   175,   175,
     175,   175,   177,   176,   176,   175,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   175,
       4,     4,     4,     4,     4,     4,   219,     4,     4,     4,
     177,   237,     4,     4,     4,     4,     4,     4,   175,     4,
       4,     4,   338,     4,   418,     4,     4,     4,     4,     4,
       4,     4,     4,   435,     4,     4,   175,     4,     4,     4,
     177,   377,     4,   177,   177,   401,     4,     4,   314,   177,
       4,     4,   175,     4,   175,   175,     4,     4,   177,   177,
       4,     4,   491,   538,     4,   175,   529,     4,     7,     7,
     194,   194,   194,     7,     7,     7,   174,   174,   174,     7,
       7,     5,   174,     5,     5,     5,     5,   196,   198,   174,
      90,    91,    92,    93,   355,     5,     5,     5,     5,     7,
       7,   198,     7,   174,   174,     5,     5,   205,    17,    18,
     244,    20,    21,   247,   174,   174,   174,     5,   174,   174,
     205,   174,     7,   174,   205,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   194,
     174,   174,   174,    18,   139,   504,   140,   141,   142,   143,
     144,   177,   511,   174,     5,   194,   218,   537,   528,   236,
      24,   253,   254,   255,    34,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,   209,   265,   266,   267,   270,   272,   274,   276,
     277,   279,   280,   281,   282,   283,   284,   285,   286,   288,
     290,   292,   294,   295,   265,     7,   261,   262,   263,     7,
     331,   332,   333,     7,   369,   370,   371,     7,   393,   394,
     395,     7,   359,   360,   361,   101,   102,   103,   104,   106,
     298,   299,   300,   301,   302,   303,   304,     7,   465,   466,
       7,   427,   428,   429,     7,   307,   308,   309,   114,   115,
     116,   117,   118,   119,   321,   322,   323,   324,   325,   326,
     327,   328,   122,   123,   209,   421,   423,   478,   479,   480,
     482,   490,     7,   541,   542,   206,     7,   411,   412,   413,
     109,   442,   444,   462,   261,     8,     8,     8,     8,   256,
       3,     8,   268,   271,   273,   275,     4,     4,     4,     4,
       4,   287,   289,   291,   293,     4,     4,     4,     4,     4,
       3,     8,     8,   264,     6,     3,   334,     6,     3,   372,
       6,     3,   396,     6,     3,   362,     6,     3,     3,     6,
     467,     3,     6,   430,     6,     3,   310,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   481,   483,     3,
       8,     8,   543,     3,     6,   174,   207,   208,   414,     6,
       3,   445,     8,     6,     4,   254,     4,     4,     4,     4,
     175,   177,   175,   177,   175,     4,     4,     4,     4,   175,
     175,   175,   175,   177,   266,   265,   263,   337,   333,   375,
     371,   399,   395,   209,   220,   221,   222,   223,   224,   225,
     226,   227,   232,   233,   277,   329,   347,   349,   351,   353,
     363,   364,   391,   421,   423,   436,   438,   440,   460,   361,
     299,    97,    98,   209,   277,   365,   391,   421,   423,   436,
     438,   440,   468,   469,   470,   471,   472,   474,   466,   433,
     429,   313,   309,   175,   175,   175,   175,   175,   175,   322,
       4,     4,   479,   149,   151,   152,   209,   277,   421,   423,
     544,   545,   546,   547,   549,   542,     6,     3,   417,   413,
       4,   174,    35,    36,    37,    38,   269,   174,   174,   174,
     174,   174,   174,   174,     8,     8,     8,     8,     3,     8,
     473,     4,     8,     3,     8,     8,   174,   174,   550,     4,
     548,     3,     8,   174,     8,   205,   364,     4,   177,   470,
       4,   175,     4,   545,   174,     5,   174,     7,   551,   552,
     553,     3,     6,   150,   153,   154,   155,   156,   554,   555,
     556,   558,   559,   560,   561,   552,   557,     4,     4,     4,
     562,     3,     8,     4,   177,   175,   175,     4,   555,   174,
     174
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   178,   180,   179,   181,   179,   182,   179,   183,   179,
     184,   179,   185,   179,   186,   179,   187,   179,   188,   179,
     189,   179,   190,   179,   191,   179,   192,   179,   193,   179,
     194,   194,   194,   194,   194,   194,   194,   195,   197,   196,
     198,   199,   199,   200,   200,   202,   201,   203,   203,   204,
     204,   206,   205,   207,   207,   208,   208,   209,   211,   210,
     212,   212,   213,   213,   213,   213,   213,   213,   215,   214,
     217,   216,   218,   218,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   230,   229,   231,   232,   233,
     235,   234,   236,   236,   237,   237,   237,   237,   237,   237,
     237,   239,   238,   241,   240,   243,   242,   244,   244,   246,
     245,   247,   247,   248,   250,   249,   252,   251,   253,   253,
     254,   256,   255,   258,   257,   260,   259,   261,   261,   262,
     262,   264,   263,   265,   265,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   268,   267,   269,   269,   269,
     269,   271,   270,   273,   272,   275,   274,   276,   278,   277,
     279,   280,   281,   282,   283,   284,   285,   287,   286,   289,
     288,   291,   290,   293,   292,   294,   295,   297,   296,   298,
     298,   299,   299,   299,   299,   299,   300,   301,   302,   303,
     304,   306,   305,   307,   307,   308,   308,   310,   309,   312,
     311,   313,   313,   313,   314,   314,   316,   315,   318,   317,
     320,   319,   321,   321,   322,   322,   322,   322,   322,   322,
     323,   324,   325,   326,   327,   328,   330,   329,   331,   331,
     332,   332,   334,   333,   336,   335,   337,   337,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   340,   339,   342,
     341,   344,   343,   346,   345,   348,   347,   350,   349,   352,
     351,   354,   353,   355,   355,   355,   355,   356,   358,   357,
     359,   359,   360,   360,   362,   361,   363,   363,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   366,   365,   368,   367,   369,   369,   370,   370,
     372,   371,   374,   373,   375,   375,   376,   376,   377,   377,
     377,   377,   377,   377,   377,   377,   377,   377,   378,   379,
     380,   382,   381,   384,   383,   386,   385,   387,   389,   388,
     390,   392,   391,   393,   393,   394,   394,   396,   395,   398,
     397,   399,   399,   400,   400,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   402,   404,   403,   405,   406,   407,
     408,   410,   409,   411,   411,   412,   412,   414,   413,   416,
     415,   417,   417,   418,   418,   418,   418,   418,   418,   418,
     420,   419,   422,   421,   424,   423,   426,   425,   427,   427,
     428,   428,   430,   429,   432,   431,   433,   433,   434,   434,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   437,   436,   439,   438,   441,
     440,   443,   442,   445,   444,   447,   446,   449,   448,   451,
     450,   453,   452,   455,   454,   457,   456,   459,   458,   461,
     460,   462,   462,   464,   463,   465,   465,   467,   466,   468,
     468,   469,   469,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   471,   473,   472,   474,   475,   477,
     476,   478,   478,   479,   479,   479,   479,   479,   481,   480,
     483,   482,   485,   484,   487,   486,   489,   488,   490,   490,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   492,   494,
     493,   496,   495,   497,   499,   498,   500,   501,   503,   502,
     504,   504,   506,   505,   507,   508,   510,   509,   511,   511,
     511,   511,   511,   513,   512,   515,   514,   517,   516,   519,
     518,   521,   520,   523,   522,   525,   524,   527,   526,   528,
     528,   529,   529,   531,   530,   532,   534,   533,   536,   535,
     537,   537,   538,   540,   539,   541,   541,   543,   542,   544,
     544,   545,   545,   545,   545,   545,   545,   545,   546,   548,
     547,   550,   549,   551,   551,   553,   552,   554,   554,   555,
     555,   555,   555,   555,   557,   556,   558,   559,   560,   562,
     561
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
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     1,     1,     0,
       4,     1,     1,     3,     0,     6,     0,     6,     1,     3,
       1,     0,     4,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     0,     6,     3,     0,     6,     0,     4,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"config-fetch-wait-time\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"authoritative\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"consistency\"", "\"serial-consistency\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"valid-lifetime\"", "\"min-valid-lifetime\"",
  "\"max-valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"calculate-tee-times\"", "\"t1-percent\"", "\"t2-percent\"",
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
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
  "$@39", "consistency", "$@40", "serial_consistency", "$@41",
  "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@42",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@43", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@44",
  "sub_hooks_library", "$@45", "hooks_params", "hooks_param", "library",
  "$@46", "parameters", "$@47", "expired_leases_processing", "$@48",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@49",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@50",
  "sub_subnet4", "$@51", "subnet4_params", "subnet4_param", "subnet",
  "$@52", "subnet_4o6_interface", "$@53", "subnet_4o6_interface_id",
  "$@54", "subnet_4o6_subnet", "$@55", "interface", "$@56", "client_class",
  "$@57", "require_client_classes", "$@58", "reservation_mode", "$@59",
  "hr_mode", "id", "shared_networks", "$@60", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@61",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@62", "sub_option_def_list", "$@63", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@64",
  "sub_option_def", "$@65", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@66",
  "option_def_record_types", "$@67", "space", "$@68", "option_def_space",
  "option_def_encapsulate", "$@69", "option_def_array", "option_data_list",
  "$@70", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@71", "sub_option_data", "$@72",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@73",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@74", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@75", "sub_pool4", "$@76",
  "pool_params", "pool_param", "pool_entry", "$@77", "user_context",
  "$@78", "comment", "$@79", "reservations", "$@80", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@81", "sub_reservation",
  "$@82", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@83", "server_hostname", "$@84",
  "boot_file_name", "$@85", "ip_address", "$@86", "ip_addresses", "$@87",
  "duid", "$@88", "hw_address", "$@89", "client_id_value", "$@90",
  "circuit_id_value", "$@91", "flex_id_value", "$@92", "hostname", "$@93",
  "reservation_client_classes", "$@94", "relay", "$@95", "relay_map",
  "client_classes", "$@96", "client_classes_list", "client_class_entry",
  "$@97", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@98",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@99",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@100", "control_socket_name", "$@101", "dhcp_queue_control", "$@102",
  "dhcp_ddns", "$@103", "sub_dhcp_ddns", "$@104", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@105",
  "server_ip", "$@106", "server_port", "sender_ip", "$@107", "sender_port",
  "max_queue_size", "ncr_protocol", "$@108", "ncr_protocol_value",
  "ncr_format", "$@109", "override_no_update", "override_client_update",
  "replace_client_name", "$@110", "replace_client_name_value",
  "generated_prefix", "$@111", "hostname_char_set", "$@112",
  "hostname_char_replacement", "$@113", "dhcp6_json_object", "$@114",
  "dhcpddns_json_object", "$@115", "control_agent_json_object", "$@116",
  "config_control", "$@117", "sub_config_control", "$@118",
  "config_control_params", "config_control_param", "config_databases",
  "$@119", "config_fetch_wait_time", "logging_object", "$@120",
  "sub_logging", "$@121", "logging_params", "logging_param", "loggers",
  "$@122", "loggers_entries", "logger_entry", "$@123", "logger_params",
  "logger_param", "debuglevel", "severity", "$@124", "output_options_list",
  "$@125", "output_options_list_content", "output_entry", "$@126",
  "output_params_list", "output_params", "output", "$@127", "flush",
  "maxsize", "maxver", "pattern", "$@128", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   265,   265,   265,   266,   266,   267,   267,   268,   268,
     269,   269,   270,   270,   271,   271,   272,   272,   273,   273,
     274,   274,   275,   275,   276,   276,   277,   277,   278,   278,
     286,   287,   288,   289,   290,   291,   292,   295,   300,   300,
     311,   314,   315,   318,   322,   329,   329,   336,   337,   340,
     344,   351,   351,   358,   359,   362,   366,   377,   387,   387,
     403,   404,   408,   409,   410,   411,   412,   413,   416,   416,
     431,   431,   440,   441,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   490,   495,   500,   505,
     510,   515,   520,   525,   530,   535,   535,   543,   548,   553,
     559,   559,   570,   571,   574,   575,   576,   577,   578,   579,
     580,   583,   583,   592,   592,   602,   602,   609,   610,   613,
     613,   620,   622,   626,   632,   632,   644,   644,   654,   655,
     657,   659,   659,   677,   677,   689,   689,   699,   700,   703,
     704,   707,   707,   717,   718,   721,   722,   723,   724,   725,
     726,   727,   728,   729,   730,   731,   732,   733,   734,   735,
     736,   737,   738,   739,   740,   743,   743,   750,   751,   752,
     753,   756,   756,   764,   764,   772,   772,   780,   785,   785,
     793,   798,   803,   808,   813,   818,   823,   828,   828,   836,
     836,   844,   844,   852,   852,   860,   865,   870,   870,   880,
     881,   884,   885,   886,   887,   888,   891,   896,   901,   906,
     911,   916,   916,   926,   927,   930,   931,   934,   934,   944,
     944,   954,   955,   956,   959,   960,   963,   963,   971,   971,
     979,   979,   990,   991,   994,   995,   996,   997,   998,   999,
    1002,  1007,  1012,  1017,  1022,  1027,  1035,  1035,  1048,  1049,
    1052,  1053,  1060,  1060,  1086,  1086,  1097,  1098,  1102,  1103,
    1104,  1105,  1106,  1107,  1108,  1109,  1110,  1111,  1112,  1113,
    1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,  1123,
    1124,  1125,  1126,  1127,  1128,  1129,  1130,  1133,  1133,  1141,
    1141,  1149,  1149,  1157,  1157,  1165,  1165,  1173,  1173,  1181,
    1181,  1191,  1191,  1198,  1199,  1200,  1201,  1204,  1211,  1211,
    1222,  1223,  1227,  1228,  1231,  1231,  1239,  1240,  1243,  1244,
    1245,  1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,  1254,
    1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,
    1265,  1266,  1273,  1273,  1286,  1286,  1295,  1296,  1299,  1300,
    1305,  1305,  1320,  1320,  1334,  1335,  1338,  1339,  1342,  1343,
    1344,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1354,  1356,
    1361,  1363,  1363,  1371,  1371,  1379,  1379,  1387,  1389,  1389,
    1397,  1406,  1406,  1418,  1419,  1424,  1425,  1430,  1430,  1442,
    1442,  1454,  1455,  1460,  1461,  1466,  1467,  1468,  1469,  1470,
    1471,  1472,  1473,  1474,  1477,  1479,  1479,  1487,  1489,  1491,
    1496,  1504,  1504,  1516,  1517,  1520,  1521,  1524,  1524,  1534,
    1534,  1544,  1545,  1548,  1549,  1550,  1551,  1552,  1553,  1554,
    1557,  1557,  1565,  1565,  1590,  1590,  1620,  1620,  1630,  1631,
    1634,  1635,  1638,  1638,  1647,  1647,  1656,  1657,  1660,  1661,
    1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,  1674,
    1675,  1676,  1677,  1678,  1679,  1682,  1682,  1690,  1690,  1698,
    1698,  1706,  1706,  1714,  1714,  1724,  1724,  1732,  1732,  1740,
    1740,  1748,  1748,  1756,  1756,  1764,  1764,  1772,  1772,  1785,
    1785,  1795,  1796,  1802,  1802,  1812,  1813,  1816,  1816,  1826,
    1827,  1830,  1831,  1834,  1835,  1836,  1837,  1838,  1839,  1840,
    1841,  1842,  1843,  1844,  1847,  1849,  1849,  1857,  1866,  1873,
    1873,  1883,  1884,  1887,  1888,  1889,  1890,  1891,  1894,  1894,
    1902,  1902,  1913,  1913,  1951,  1951,  1963,  1963,  1973,  1974,
    1977,  1978,  1979,  1980,  1981,  1982,  1983,  1984,  1985,  1986,
    1987,  1988,  1989,  1990,  1991,  1992,  1993,  1994,  1997,  2002,
    2002,  2010,  2010,  2018,  2023,  2023,  2031,  2036,  2041,  2041,
    2049,  2050,  2053,  2053,  2061,  2066,  2071,  2071,  2079,  2082,
    2085,  2088,  2091,  2097,  2097,  2105,  2105,  2113,  2113,  2124,
    2124,  2131,  2131,  2138,  2138,  2145,  2145,  2156,  2156,  2166,
    2167,  2171,  2172,  2175,  2175,  2185,  2195,  2195,  2205,  2205,
    2216,  2217,  2221,  2225,  2225,  2237,  2238,  2242,  2242,  2250,
    2251,  2254,  2255,  2256,  2257,  2258,  2259,  2260,  2263,  2268,
    2268,  2276,  2276,  2286,  2287,  2290,  2290,  2298,  2299,  2302,
    2303,  2304,  2305,  2306,  2309,  2309,  2317,  2322,  2327,  2332,
    2332
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
#line 5051 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2341 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
