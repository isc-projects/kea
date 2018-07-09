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
      case 178: // value
      case 182: // map_value
      case 220: // socket_type
      case 223: // outbound_interface_value
      case 239: // db_type
      case 323: // hr_mode
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 178: // value
      case 182: // map_value
      case 220: // socket_type
      case 223: // outbound_interface_value
      case 239: // db_type
      case 323: // hr_mode
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
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
            case 159: // "constant string"

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 160: // "integer"

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 161: // "floating point"

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 162: // "boolean"

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 178: // value

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 182: // map_value

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 220: // socket_type

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 223: // outbound_interface_value

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 239: // db_type

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 323: // hr_mode

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 471: // ncr_protocol_value

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 479: // replace_client_name_value

#line 237 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 178: // value
      case 182: // map_value
      case 220: // socket_type
      case 223: // outbound_interface_value
      case 239: // db_type
      case 323: // hr_mode
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
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
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 298 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 320 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 342 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 346 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1979 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1080 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1167 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1251 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1445 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2497 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2535 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2571 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2635 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2707 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1694 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1890 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1924 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3138 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1936 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2000 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2121 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3462 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3466 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -747;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     413,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,    58,    23,    41,    55,    68,    82,
      88,    97,   129,   136,   150,   168,   170,   179,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,    23,   -94,    19,    59,    75,   176,
      48,   383,    21,    32,    62,   -45,   468,    34,  -747,   196,
     217,   218,   237,   251,  -747,  -747,  -747,  -747,  -747,   254,
    -747,    56,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   265,
     271,  -747,  -747,  -747,  -747,  -747,  -747,   273,   284,   290,
     307,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,   309,  -747,  -747,  -747,    63,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,   310,  -747,    66,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,   311,   312,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,    98,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,   134,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   249,
     294,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,   297,  -747,  -747,   313,  -747,  -747,  -747,
     314,  -747,  -747,   315,   316,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   317,   318,
    -747,  -747,  -747,  -747,   319,   322,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   152,  -747,
    -747,  -747,   325,  -747,  -747,   326,  -747,   328,   329,  -747,
    -747,   330,   332,   333,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,   184,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
     186,  -747,  -747,  -747,    23,    23,  -747,   161,   334,   335,
     337,   342,   343,  -747,    19,  -747,   345,   164,   188,   347,
     349,   352,   354,   355,   362,   207,   210,   213,   219,   368,
     373,   377,   381,   384,   387,   391,   392,   394,   395,   227,
     397,   398,    59,  -747,   400,   404,   405,   255,    75,  -747,
     410,   411,   412,   414,   415,   416,   420,   266,   263,   423,
     424,   425,   426,   427,   176,  -747,   429,    48,  -747,   430,
     431,   432,   433,   434,   435,   437,   438,  -747,   383,  -747,
     439,   440,   285,   442,   443,   444,   287,  -747,    32,   446,
     289,   296,  -747,    62,   448,   455,    14,  -747,   298,   457,
     458,   303,   460,   306,   308,   463,   473,   320,   327,   331,
     475,   476,   477,   483,   468,  -747,   484,    34,  -747,  -747,
    -747,   487,   485,   488,    23,    23,    23,  -747,   489,  -747,
    -747,   338,   339,   340,   493,   494,   498,  -747,  -747,  -747,
    -747,   499,   500,   501,   505,   504,   353,   508,   509,   510,
     512,  -747,   536,   537,  -747,   511,   113,   193,  -747,  -747,
     358,   386,   388,   541,   390,   393,   396,  -747,  -747,   163,
     511,   417,   545,   544,  -747,   418,  -747,   511,   419,   436,
     445,   447,   449,   450,   451,  -747,   452,   453,  -747,   454,
     456,   459,  -747,  -747,   461,  -747,  -747,  -747,   462,    23,
    -747,  -747,   464,   465,  -747,   466,  -747,  -747,    18,   367,
    -747,  -747,  -747,    43,   467,   469,   470,  -747,   548,  -747,
      23,    59,    34,  -747,  -747,  -747,    75,  -747,  -747,  -747,
     490,   490,   547,   549,   550,   565,   566,  -747,  -747,  -747,
      61,   567,   568,   178,    29,   468,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,   572,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,   587,   212,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,   589,  -747,   198,   200,   201,  -747,  -747,  -747,
    -747,   593,   594,   595,   598,   599,  -747,  -747,   601,   603,
     610,   612,   613,  -747,   209,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,   211,  -747,   616,   627,  -747,  -747,   625,
     629,  -747,  -747,   628,   630,  -747,  -747,   631,   632,  -747,
    -747,   633,   635,  -747,  -747,  -747,  -747,  -747,  -747,    70,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,   155,  -747,  -747,
     634,   638,  -747,   615,   639,   640,   641,   642,   643,   220,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,   252,  -747,  -747,  -747,   253,   491,  -747,   636,
     645,  -747,  -747,   646,   648,  -747,  -747,  -747,  -747,   647,
    -747,   162,  -747,  -747,  -747,  -747,   649,   650,   652,   653,
     502,   474,   503,   496,   506,   655,   656,   507,   513,   514,
     515,   516,   490,  -747,  -747,   490,  -747,   547,   176,  -747,
     549,    32,  -747,   550,    62,  -747,   565,   216,  -747,   566,
      61,  -747,   399,   567,  -747,   -45,  -747,   568,   517,   519,
     520,   521,   522,   523,   178,  -747,   657,   660,    29,  -747,
    -747,  -747,   659,   665,    48,  -747,   572,   383,  -747,   587,
     666,  -747,    77,   589,  -747,    20,   525,   526,   527,  -747,
    -747,  -747,  -747,  -747,   528,   529,  -747,  -747,  -747,  -747,
    -747,  -747,   264,  -747,   268,  -747,   661,  -747,   663,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,   282,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,   668,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,   681,   673,  -747,  -747,  -747,  -747,  -747,
     292,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   531,
     532,  -747,  -747,   533,   293,  -747,   685,  -747,   511,  -747,
     690,  -747,  -747,  -747,  -747,  -747,   295,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,   216,  -747,   691,   534,
    -747,   399,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   693,
     538,   695,    77,  -747,  -747,   542,  -747,  -747,   697,  -747,
     546,  -747,  -747,   696,  -747,  -747,   229,  -747,    39,   696,
    -747,  -747,   700,   702,   703,   301,  -747,  -747,  -747,  -747,
    -747,  -747,   704,   551,   540,   554,    39,  -747,   552,  -747,
    -747,  -747,  -747,  -747
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   116,     9,   246,    11,   403,    13,
     428,    15,   328,    17,   336,    19,   373,    21,   211,    23,
     518,    25,   581,    27,    45,    39,     0,     0,     0,     0,
       0,   430,     0,   338,   375,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   579,   573,   575,   577,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   105,     0,
       0,   449,   451,   453,   129,   131,   133,     0,     0,     0,
       0,   238,   326,   365,   298,   416,   418,   189,   477,   203,
     222,     0,   503,   516,    98,     0,    70,    72,    73,    74,
      75,    91,    92,    78,    79,    80,    81,    82,    86,    87,
      76,    77,    84,    85,    96,    97,    93,    94,    95,    83,
      88,    89,    90,   118,   120,   124,     0,   115,     0,   107,
     109,   110,   111,   112,   113,   114,   277,   279,   281,   395,
     275,   283,   285,     0,     0,   291,   289,   287,   420,   473,
     274,   250,   251,   252,   265,     0,   248,   255,   269,   270,
     271,   256,   257,   260,   261,   263,   258,   259,   253,   254,
     272,   273,   262,   266,   267,   268,   264,   414,   413,   409,
     410,   408,     0,   405,   407,   411,   412,   471,   459,   461,
     465,   463,   469,   467,   455,   448,   442,   446,   447,     0,
     431,   432,   443,   444,   445,   439,   434,   440,   436,   437,
     438,   441,   435,     0,   355,   174,     0,   359,   357,   362,
       0,   351,   352,     0,   339,   340,   342,   354,   343,   344,
     345,   361,   346,   347,   348,   349,   350,   389,     0,     0,
     387,   388,   391,   392,     0,   376,   377,   379,   380,   381,
     382,   383,   384,   385,   386,   218,   220,   215,     0,   213,
     216,   217,     0,   542,   544,     0,   547,     0,     0,   551,
     555,     0,     0,     0,   560,   567,   569,   571,   540,   538,
     539,     0,   520,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   586,
       0,   583,   585,    44,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    55,     0,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   247,     0,     0,   404,     0,
       0,     0,     0,     0,     0,     0,     0,   429,     0,   329,
       0,     0,     0,     0,     0,     0,     0,   337,     0,     0,
       0,     0,   374,     0,     0,     0,     0,   212,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   519,     0,     0,   582,    48,
      41,     0,     0,     0,     0,     0,     0,    59,     0,   103,
     104,     0,     0,     0,     0,     0,     0,    99,   100,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   502,     0,     0,    71,     0,     0,     0,   128,   108,
       0,     0,     0,     0,     0,     0,     0,   296,   297,     0,
       0,     0,     0,     0,   249,     0,   406,     0,     0,     0,
       0,     0,     0,     0,     0,   433,     0,     0,   353,     0,
       0,     0,   364,   341,     0,   393,   394,   378,     0,     0,
     214,   541,     0,     0,   546,     0,   549,   550,     0,     0,
     557,   558,   559,     0,     0,     0,     0,   521,     0,   584,
       0,     0,     0,   574,   576,   578,     0,   450,   452,   454,
       0,     0,   135,   240,   330,   367,   300,    38,   417,   419,
       0,     0,   205,     0,     0,     0,    49,   119,   122,   123,
     121,   126,   127,   125,   278,   280,   282,   397,   276,   284,
     286,   293,   294,   295,   292,   290,   288,   422,     0,   415,
     472,   460,   462,   466,   464,   470,   468,   456,   356,   175,
     360,   358,   363,   390,   219,   221,   543,   545,   548,   553,
     554,   552,   556,   562,   563,   564,   565,   566,   561,   568,
     570,   572,     0,    42,     0,     0,     0,   161,   167,   169,
     171,     0,     0,     0,     0,     0,   183,   185,     0,     0,
       0,     0,     0,   160,     0,   141,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   156,   157,   158,   153,
     159,   154,   155,     0,   139,     0,   136,   137,   244,     0,
     241,   242,   334,     0,   331,   332,   371,     0,   368,   369,
     304,     0,   301,   302,   198,   199,   200,   201,   202,     0,
     191,   193,   194,   195,   196,   197,   481,     0,   479,   209,
       0,   206,   207,     0,     0,     0,     0,     0,     0,     0,
     224,   226,   227,   228,   229,   230,   231,   512,   514,   511,
     509,   510,     0,   505,   507,   508,     0,    51,   401,     0,
     398,   399,   426,     0,   423,   424,   457,   475,   476,     0,
     590,     0,   588,    67,   580,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,   132,     0,   134,     0,     0,   239,
       0,   338,   327,     0,   375,   366,     0,     0,   299,     0,
       0,   190,   483,     0,   478,     0,   204,     0,     0,     0,
       0,     0,     0,     0,     0,   223,     0,     0,     0,   504,
     517,    53,     0,    52,     0,   396,     0,   430,   421,     0,
       0,   474,     0,     0,   587,     0,     0,     0,     0,   173,
     176,   177,   178,   179,     0,     0,   187,   188,   180,   181,
     182,   142,     0,   138,     0,   243,     0,   333,     0,   370,
     325,   322,   311,   312,   314,   308,   309,   310,   320,   321,
     319,     0,   306,   313,   323,   324,   315,   316,   317,   318,
     303,   192,   499,     0,   497,   498,   490,   491,   495,   496,
     492,   493,   494,     0,   484,   485,   487,   488,   489,   480,
       0,   208,   232,   233,   234,   235,   236,   237,   225,     0,
       0,   506,    50,     0,     0,   400,     0,   425,     0,   604,
       0,   602,   600,   594,   598,   599,     0,   592,   596,   597,
     595,   589,   163,   164,   165,   166,   162,   168,   170,   172,
     184,   186,   140,   245,   335,   372,     0,   305,     0,     0,
     482,     0,   210,   513,   515,    54,   402,   427,   458,     0,
       0,     0,     0,   591,   307,     0,   501,   486,     0,   601,
       0,   593,   500,     0,   603,   608,     0,   606,     0,     0,
     605,   616,     0,     0,     0,     0,   610,   612,   613,   614,
     615,   607,     0,     0,     0,     0,     0,   609,     0,   618,
     619,   620,   611,   617
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,   -43,  -747,   234,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -476,  -747,  -747,  -747,
     -66,  -747,  -747,  -747,   366,  -747,  -747,  -747,  -747,   166,
     348,    -2,    -1,     3,  -747,  -747,     9,  -747,  -747,   167,
     341,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
     -49,  -747,  -548,   -36,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,   -47,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,   -65,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,   -58,  -747,  -747,  -747,   -38,   323,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,   -39,  -747,  -747,  -747,  -747,
    -747,  -747,  -746,  -747,  -747,  -747,   -37,  -747,  -747,  -747,
     -19,   375,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -743,  -747,  -747,  -747,   -52,  -747,   -32,  -747,  -741,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,   -22,  -747,  -747,
    -164,   -61,  -747,  -747,  -747,  -747,  -747,     6,  -747,  -747,
    -747,    11,  -747,   376,  -747,   -68,  -747,  -747,  -747,  -747,
    -747,   -62,  -747,  -747,  -747,  -747,  -747,   -14,  -747,  -747,
    -747,     7,  -747,  -747,  -747,    13,  -747,   372,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   -18,
    -747,  -747,  -747,   -15,   407,  -747,  -747,   -54,  -747,   -34,
    -747,  -747,  -747,  -747,  -747,   -17,  -747,  -747,  -747,   -16,
    -747,   402,   -46,  -747,   -26,  -747,    -8,  -747,   208,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -740,  -747,  -747,  -747,
    -747,  -747,    12,  -747,  -747,  -747,  -134,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,     0,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,   236,   369,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,   260,   370,  -747,  -747,  -747,    -9,  -747,
    -747,  -137,  -747,  -747,  -747,  -747,  -747,  -747,  -153,  -747,
    -747,  -168,  -747,  -747,  -747,  -747,  -747
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   568,
      82,    83,    39,    64,    79,    80,   577,   737,   812,   813,
     653,    41,    66,    91,    92,    93,   338,    43,    67,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   346,   158,
     159,    45,    68,   160,   374,   161,   375,   580,   162,   376,
     583,   163,   134,   352,   135,   353,   136,   354,   675,   676,
     677,   775,   654,   655,   656,   756,   926,   657,   757,   658,
     758,   659,   759,   660,   661,   411,   662,   663,   664,   665,
     666,   667,   668,   669,   765,   670,   766,   671,   672,   137,
     365,   699,   700,   701,   702,   703,   704,   705,   138,   367,
     710,   711,   712,   795,    59,    75,   288,   289,   290,   424,
     291,   425,   139,   368,   719,   720,   721,   722,   723,   724,
     725,   726,   140,   359,   679,   680,   681,   778,    47,    69,
     185,   186,   187,   384,   188,   380,   189,   381,   190,   382,
     191,   385,   192,   386,   193,   391,   194,   390,   195,   389,
     594,   196,   197,   141,   362,   691,   692,   693,   787,   861,
     862,   142,   360,    53,    72,   683,   684,   685,   781,    55,
      73,   253,   254,   255,   256,   257,   258,   259,   410,   260,
     414,   261,   413,   262,   263,   415,   264,   143,   361,   687,
     688,   689,   784,    57,    74,   274,   275,   276,   277,   278,
     419,   279,   280,   281,   282,   199,   383,   739,   740,   741,
     814,    49,    70,   212,   213,   214,   396,   144,   363,   145,
     364,   202,   392,   743,   744,   745,   817,    51,    71,   229,
     230,   231,   146,   349,   147,   350,   148,   351,   235,   406,
     748,   820,   236,   400,   237,   401,   238,   403,   239,   402,
     240,   405,   241,   404,   242,   399,   206,   393,   749,   149,
     366,   707,   708,   792,   883,   884,   885,   886,   887,   938,
     888,   150,   151,   370,   732,   733,   734,   806,   735,   807,
     152,   371,    61,    76,   311,   312,   313,   314,   429,   315,
     430,   316,   317,   432,   318,   319,   320,   435,   621,   321,
     436,   322,   323,   324,   325,   440,   628,   326,   441,   327,
     442,   328,   443,    94,   340,    95,   341,    96,   342,    97,
     339,    63,    77,   330,   331,   332,   446,   751,   752,   822,
     916,   917,   918,   919,   951,   920,   949,   966,   967,   968,
     975,   976,   977,   982,   978,   979,   980
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   124,   157,   180,   208,   225,   272,   251,   270,   287,
     308,   243,   273,   673,   164,   200,   215,   227,   209,   265,
     283,    78,   309,   203,   595,   232,   252,   271,    29,    84,
      30,   600,    31,   619,   165,   201,   216,   228,   210,   266,
     284,   856,   310,   204,   857,   233,   860,   869,    40,   922,
     923,   924,   925,   285,   286,   198,   211,   226,    28,   344,
     244,   205,    42,   234,   345,    81,   372,   181,   182,   378,
      98,   373,   183,   790,   379,    44,   791,   112,   184,    99,
     100,   101,   102,   103,   104,   105,   106,   153,   154,    46,
     245,   155,   246,   247,   156,    48,   248,   249,   250,   115,
     116,   394,   115,   116,    50,   113,   395,   107,   108,   109,
     110,   111,   285,   286,    89,   112,   113,   207,   115,   116,
     245,   267,   246,   247,   268,   269,   114,   578,   579,   115,
     116,   176,   115,   116,   177,   245,    52,   397,   727,   728,
     117,   118,   398,    54,   620,   115,   116,   115,   116,   694,
     695,   696,   697,    85,   698,   426,   119,    56,   793,   120,
     427,   794,    86,    87,    88,   823,   121,   122,   824,   329,
     123,   623,   624,   625,   626,    58,   971,    60,    89,   972,
     973,   974,    32,    33,    34,    35,    62,   444,    89,   447,
     856,    89,   445,   857,   448,   860,   869,   100,   101,   102,
     103,   372,   333,   447,   378,   627,   753,    89,   754,   755,
     581,   582,   772,   909,   772,   910,   911,   773,    89,   774,
     334,    89,   335,   804,   107,   108,   109,   842,   805,   166,
     167,   168,   969,   113,    89,   970,    89,   100,   101,   102,
     103,   591,   592,   593,   169,   336,   115,   116,   170,   171,
     172,   173,   174,   175,   337,   808,   444,   407,   343,   176,
     809,   810,   177,   178,   107,   108,   109,   772,   111,   347,
     179,   394,   932,   113,   245,   348,   933,   355,    90,   713,
     714,   715,   716,   717,   718,   936,   115,   116,   356,   171,
     937,   449,   450,   175,   357,   426,   397,   408,   952,   176,
     942,   946,   177,   953,   986,   409,   124,   224,   746,   987,
     179,   358,   157,   369,   377,   387,   388,   412,   416,   418,
     451,   420,   421,   417,   164,   423,   459,   422,   180,   428,
     431,   208,   433,   434,   437,    89,   438,   439,   452,   453,
     200,   454,   225,   215,   165,   209,   455,   456,   203,   458,
     460,   461,   251,   462,   227,   272,   463,   270,   464,   465,
     201,   273,   232,   216,   265,   210,   466,   467,   204,   283,
     468,   252,   471,   469,   228,    89,   271,   472,   308,   470,
     198,   473,   233,   211,   266,   474,   205,   481,   475,   284,
     309,   476,   181,   182,   226,   477,   478,   183,   479,   480,
     234,   482,   483,   184,   485,   101,   102,   103,   486,   487,
     310,   553,   554,   555,   490,   491,   492,   488,   493,   494,
     495,   101,   102,   103,   496,   498,   497,   499,   500,   501,
     502,   503,   948,   505,   507,   508,   509,   510,   511,   512,
     113,   513,   514,   516,   517,   518,   519,   520,   521,   522,
     524,   525,   528,   115,   116,   112,   113,   245,   526,   529,
     531,   532,   533,   534,   535,   217,   536,   538,   537,   115,
     116,   218,   219,   220,   221,   222,   223,   539,   224,   543,
     544,   545,   540,   872,   873,   124,   615,   546,   548,   541,
     157,   550,   551,   542,   622,   552,   556,   557,   558,   559,
     560,   561,   164,   562,   563,   564,   565,   633,   729,   308,
     566,    30,   569,   570,   571,   572,   576,   584,   637,   573,
     730,   309,   165,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   115,   116,
     731,   310,    89,   574,   575,   585,   587,   586,   245,   588,
     597,   598,   589,   632,   674,   590,   678,   682,    89,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   686,   690,   706,   709,   596,   599,   601,   738,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   742,   602,   750,   760,   761,   762,
     306,   307,   763,   764,   603,   767,   604,   768,   605,   606,
     607,   608,   609,   610,   769,   611,   770,   771,   612,   798,
     613,   614,   776,   616,   617,   618,   629,    89,   630,   631,
     777,   779,   780,   783,   782,   786,   830,   785,   789,   788,
     796,   797,   815,   799,   800,   801,   802,   803,   816,    89,
     811,   819,   818,   825,   826,   821,   827,   828,   832,   834,
     835,   899,   829,   831,   900,   902,   833,   836,   903,   934,
     908,   935,   939,   837,   838,   839,   941,   892,   840,   893,
     894,   895,   896,   897,   927,   928,   929,   930,   931,   940,
     943,   944,   945,   947,   950,   955,   956,   958,   959,   960,
     990,   962,   963,   965,   983,   964,   984,   985,   988,   567,
     457,   993,   180,   989,   991,   251,   272,   634,   270,   489,
     484,   850,   273,   636,   200,   871,   874,   265,   843,   287,
     283,   876,   203,   864,   252,   858,   841,   271,   878,   891,
     855,   866,   729,   845,   201,   875,   880,   266,   208,   530,
     284,   225,   204,   865,   730,   859,   912,   890,   879,   844,
     215,   867,   209,   227,   198,   898,   881,   870,   914,   504,
     205,   232,   954,   863,   731,   913,   181,   182,   877,   868,
     216,   183,   210,   228,   882,   851,   852,   184,   915,   847,
     853,   233,   846,   849,   523,   527,   854,   848,   905,   904,
     211,   906,   907,   226,   506,   889,   747,   957,   901,   234,
     515,   736,   635,   547,   921,   961,   981,   549,   992,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     850,     0,     0,     0,     0,   874,     0,     0,     0,     0,
     876,     0,   864,     0,   858,     0,   912,   878,     0,   855,
     866,     0,     0,     0,   875,   880,     0,     0,   914,     0,
       0,     0,   865,     0,   859,   913,     0,   879,     0,     0,
     867,     0,     0,     0,     0,   881,     0,     0,   915,     0,
       0,     0,   863,     0,     0,     0,     0,   877,   868,     0,
       0,     0,     0,   882,   851,   852,     0,     0,     0,   853,
       0,     0,     0,     0,     0,   854
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,    74,    73,    74,    75,
      76,    72,    74,   561,    68,    69,    70,    71,    70,    73,
      74,    64,    76,    69,   500,    71,    73,    74,     5,    10,
       7,   507,     9,    15,    68,    69,    70,    71,    70,    73,
      74,   787,    76,    69,   787,    71,   787,   787,     7,    29,
      30,    31,    32,    98,    99,    69,    70,    71,     0,     3,
      28,    69,     7,    71,     8,   159,     3,    69,    69,     3,
      11,     8,    69,     3,     8,     7,     6,    56,    69,    20,
      21,    22,    23,    24,    25,    26,    27,    12,    13,     7,
      58,    16,    60,    61,    19,     7,    64,    65,    66,    70,
      71,     3,    70,    71,     7,    57,     8,    48,    49,    50,
      51,    52,    98,    99,   159,    56,    57,    69,    70,    71,
      58,    59,    60,    61,    62,    63,    67,    14,    15,    70,
      71,    83,    70,    71,    86,    58,     7,     3,   109,   110,
      81,    82,     8,     7,   126,    70,    71,    70,    71,    88,
      89,    90,    91,   134,    93,     3,    97,     7,     3,   100,
       8,     6,   143,   144,   145,     3,   107,   108,     6,   135,
     111,   128,   129,   130,   131,     7,   137,     7,   159,   140,
     141,   142,   159,   160,   161,   162,     7,     3,   159,     3,
     936,   159,     8,   936,     8,   936,   936,    21,    22,    23,
      24,     3,     6,     3,     3,   162,     8,   159,     8,     8,
      17,    18,     3,   136,     3,   138,   139,     8,   159,     8,
       3,   159,     4,     3,    48,    49,    50,   775,     8,    53,
      54,    55,     3,    57,   159,     6,   159,    21,    22,    23,
      24,    78,    79,    80,    68,     8,    70,    71,    72,    73,
      74,    75,    76,    77,     3,     3,     3,     8,     4,    83,
       8,     8,    86,    87,    48,    49,    50,     3,    52,     4,
      94,     3,     8,    57,    58,     4,     8,     4,   344,   101,
     102,   103,   104,   105,   106,     3,    70,    71,     4,    73,
       8,   334,   335,    77,     4,     3,     3,     3,     3,    83,
       8,     8,    86,     8,     3,     8,   372,    95,    96,     8,
      94,     4,   378,     4,     4,     4,     4,     4,     4,     3,
     159,     4,     4,     8,   378,     3,   162,     8,   394,     4,
       4,   397,     4,     4,     4,   159,     4,     4,     4,     4,
     394,     4,   408,   397,   378,   397,     4,     4,   394,     4,
     162,     4,   418,     4,   408,   423,     4,   423,     4,     4,
     394,   423,   408,   397,   418,   397,     4,   160,   394,   423,
     160,   418,     4,   160,   408,   159,   423,     4,   444,   160,
     394,     4,   408,   397,   418,     4,   394,   160,     4,   423,
     444,     4,   394,   394,   408,     4,     4,   394,     4,     4,
     408,     4,     4,   394,     4,    22,    23,    24,     4,     4,
     444,   454,   455,   456,     4,     4,     4,   162,     4,     4,
       4,    22,    23,    24,     4,   162,   160,     4,     4,     4,
       4,     4,   908,     4,     4,     4,     4,     4,     4,     4,
      57,     4,     4,     4,     4,   160,     4,     4,     4,   162,
       4,   162,     4,    70,    71,    56,    57,    58,   162,     4,
     162,     4,     4,   160,     4,    82,   160,     4,   160,    70,
      71,    88,    89,    90,    91,    92,    93,     4,    95,     4,
       4,     4,   162,    84,    85,   551,   529,     4,     4,   162,
     556,     4,     7,   162,   127,     7,     7,   159,   159,   159,
       7,     7,   556,     5,     5,     5,     5,   550,   574,   575,
       5,     7,   159,     5,     5,     5,     5,   159,    28,     7,
     574,   575,   556,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    70,    71,
     574,   575,   159,     7,     7,   159,     5,   159,    58,   159,
       5,     7,   159,     5,     7,   159,     7,     7,   159,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,     7,     7,     7,     7,   159,   159,   159,     7,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     7,   159,     7,     4,     4,     4,
     132,   133,     4,     4,   159,     4,   159,     4,   159,   159,
     159,   159,   159,   159,     4,   159,     4,     4,   159,     4,
     159,   159,     6,   159,   159,   159,   159,   159,   159,   159,
       3,     6,     3,     3,     6,     3,   162,     6,     3,     6,
       6,     3,     6,     4,     4,     4,     4,     4,     3,   159,
     159,     3,     6,     4,     4,     8,     4,     4,   162,     4,
       4,     4,   160,   160,     4,     6,   160,   160,     3,     8,
       4,     8,     4,   160,   160,   160,     3,   160,   162,   160,
     160,   160,   160,   160,   159,   159,   159,   159,   159,     8,
     159,   159,   159,     8,     4,     4,   162,     4,   160,     4,
     160,   159,     5,     7,     4,   159,     4,     4,     4,   475,
     344,   159,   778,   162,   160,   781,   784,   551,   784,   378,
     372,   787,   784,   556,   778,   790,   792,   781,   777,   795,
     784,   792,   778,   787,   781,   787,   772,   784,   792,   797,
     787,   787,   808,   780,   778,   792,   792,   781,   814,   426,
     784,   817,   778,   787,   808,   787,   822,   795,   792,   778,
     814,   787,   814,   817,   778,   804,   792,   789,   822,   394,
     778,   817,   936,   787,   808,   822,   778,   778,   792,   787,
     814,   778,   814,   817,   792,   787,   787,   778,   822,   783,
     787,   817,   781,   786,   418,   423,   787,   784,   816,   814,
     814,   817,   819,   817,   397,   793,   598,   941,   808,   817,
     408,   575,   552,   444,   823,   952,   969,   447,   986,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     936,    -1,    -1,    -1,    -1,   941,    -1,    -1,    -1,    -1,
     941,    -1,   936,    -1,   936,    -1,   952,   941,    -1,   936,
     936,    -1,    -1,    -1,   941,   941,    -1,    -1,   952,    -1,
      -1,    -1,   936,    -1,   936,   952,    -1,   941,    -1,    -1,
     936,    -1,    -1,    -1,    -1,   941,    -1,    -1,   952,    -1,
      -1,    -1,   936,    -1,    -1,    -1,    -1,   941,   936,    -1,
      -1,    -1,    -1,   941,   936,   936,    -1,    -1,    -1,   936,
      -1,    -1,    -1,    -1,    -1,   936
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,     0,     5,
       7,     9,   159,   160,   161,   162,   178,   179,   180,   185,
       7,   194,     7,   200,     7,   214,     7,   301,     7,   384,
       7,   400,     7,   336,     7,   342,     7,   366,     7,   277,
       7,   455,     7,   494,   186,   181,   195,   201,   215,   302,
     385,   401,   337,   343,   367,   278,   456,   495,   178,   187,
     188,   159,   183,   184,    10,   134,   143,   144,   145,   159,
     193,   196,   197,   198,   486,   488,   490,   492,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    48,    49,    50,
      51,    52,    56,    57,    67,    70,    71,    81,    82,    97,
     100,   107,   108,   111,   193,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   225,   227,   229,   262,   271,   285,
     295,   326,   334,   360,   390,   392,   405,   407,   409,   432,
     444,   445,   453,    12,    13,    16,    19,   193,   212,   213,
     216,   218,   221,   224,   390,   392,    53,    54,    55,    68,
      72,    73,    74,    75,    76,    77,    83,    86,    87,    94,
     193,   204,   205,   206,   209,   303,   304,   305,   307,   309,
     311,   313,   315,   317,   319,   321,   324,   325,   360,   378,
     390,   392,   394,   405,   407,   409,   429,    69,   193,   317,
     319,   360,   386,   387,   388,   390,   392,    82,    88,    89,
      90,    91,    92,    93,    95,   193,   360,   390,   392,   402,
     403,   404,   405,   407,   409,   411,   415,   417,   419,   421,
     423,   425,   427,   334,    28,    58,    60,    61,    64,    65,
      66,   193,   247,   344,   345,   346,   347,   348,   349,   350,
     352,   354,   356,   357,   359,   390,   392,    59,    62,    63,
     193,   247,   348,   354,   368,   369,   370,   371,   372,   374,
     375,   376,   377,   390,   392,    98,    99,   193,   279,   280,
     281,   283,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   132,   133,   193,   390,
     392,   457,   458,   459,   460,   462,   464,   465,   467,   468,
     469,   472,   474,   475,   476,   477,   480,   482,   484,   135,
     496,   497,   498,     6,     3,     4,     8,     3,   199,   493,
     487,   489,   491,     4,     3,     8,   211,     4,     4,   406,
     408,   410,   226,   228,   230,     4,     4,     4,     4,   296,
     335,   361,   327,   391,   393,   263,   433,   272,   286,     4,
     446,   454,     3,     8,   217,   219,   222,     4,     3,     8,
     308,   310,   312,   379,   306,   314,   316,     4,     4,   322,
     320,   318,   395,   430,     3,     8,   389,     3,     8,   428,
     416,   418,   422,   420,   426,   424,   412,     8,     3,     8,
     351,   248,     4,   355,   353,   358,     4,     8,     3,   373,
       4,     4,     8,     3,   282,   284,     3,     8,     4,   461,
     463,     4,   466,     4,     4,   470,   473,     4,     4,     4,
     478,   481,   483,   485,     3,     8,   499,     3,     8,   178,
     178,   159,     4,     4,     4,     4,     4,   197,     4,   162,
     162,     4,     4,     4,     4,     4,     4,   160,   160,   160,
     160,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   160,     4,     4,   203,     4,     4,     4,   162,   213,
       4,     4,     4,     4,     4,     4,     4,   160,   162,     4,
       4,     4,     4,     4,   304,     4,   387,     4,     4,     4,
       4,     4,     4,     4,     4,   404,     4,     4,   160,     4,
       4,     4,   162,   346,     4,   162,   162,   370,     4,     4,
     280,   162,     4,     4,   160,     4,   160,   160,     4,     4,
     162,   162,   162,     4,     4,     4,     4,   458,     4,   497,
       4,     7,     7,   178,   178,   178,     7,   159,   159,   159,
       7,     7,     5,     5,     5,     5,     5,   180,   182,   159,
       5,     5,     5,     7,     7,     7,     5,   189,    14,    15,
     220,    17,    18,   223,   159,   159,   159,     5,   159,   159,
     159,    78,    79,    80,   323,   189,   159,     5,     7,   159,
     189,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   178,   159,   159,   159,    15,
     126,   471,   127,   128,   129,   130,   131,   162,   479,   159,
     159,   159,     5,   178,   202,   496,   212,    28,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,   193,   235,   236,   237,   240,   242,   244,
     246,   247,   249,   250,   251,   252,   253,   254,   255,   256,
     258,   260,   261,   235,     7,   231,   232,   233,     7,   297,
     298,   299,     7,   338,   339,   340,     7,   362,   363,   364,
       7,   328,   329,   330,    88,    89,    90,    91,    93,   264,
     265,   266,   267,   268,   269,   270,     7,   434,   435,     7,
     273,   274,   275,   101,   102,   103,   104,   105,   106,   287,
     288,   289,   290,   291,   292,   293,   294,   109,   110,   193,
     390,   392,   447,   448,   449,   451,   457,   190,     7,   380,
     381,   382,     7,   396,   397,   398,    96,   411,   413,   431,
       7,   500,   501,     8,     8,     8,   238,   241,   243,   245,
       4,     4,     4,     4,     4,   257,   259,     4,     4,     4,
       4,     4,     3,     8,     8,   234,     6,     3,   300,     6,
       3,   341,     6,     3,   365,     6,     3,   331,     6,     3,
       3,     6,   436,     3,     6,   276,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   450,   452,     3,     8,
       8,   159,   191,   192,   383,     6,     3,   399,     6,     3,
     414,     8,   502,     3,     6,     4,     4,     4,     4,   160,
     162,   160,   162,   160,     4,     4,   160,   160,   160,   160,
     162,   236,   235,   233,   303,   299,   344,   340,   368,   364,
     193,   204,   205,   206,   209,   247,   295,   313,   317,   319,
     321,   332,   333,   360,   390,   392,   405,   407,   409,   429,
     330,   265,    84,    85,   193,   247,   334,   360,   390,   392,
     405,   407,   409,   437,   438,   439,   440,   441,   443,   435,
     279,   275,   160,   160,   160,   160,   160,   160,   288,     4,
       4,   448,     6,     3,   386,   382,   402,   398,     4,   136,
     138,   139,   193,   247,   390,   392,   503,   504,   505,   506,
     508,   501,    29,    30,    31,    32,   239,   159,   159,   159,
     159,   159,     8,     8,     8,     8,     3,     8,   442,     4,
       8,     3,     8,   159,   159,   159,     8,     8,   189,   509,
       4,   507,     3,     8,   333,     4,   162,   439,     4,   160,
       4,   504,   159,     5,   159,     7,   510,   511,   512,     3,
       6,   137,   140,   141,   142,   513,   514,   515,   517,   518,
     519,   511,   516,     4,     4,     4,     3,     8,     4,   162,
     160,   160,   514,   159
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   163,   165,   164,   166,   164,   167,   164,   168,   164,
     169,   164,   170,   164,   171,   164,   172,   164,   173,   164,
     174,   164,   175,   164,   176,   164,   177,   164,   178,   178,
     178,   178,   178,   178,   178,   179,   181,   180,   182,   183,
     183,   184,   184,   186,   185,   187,   187,   188,   188,   190,
     189,   191,   191,   192,   192,   193,   195,   194,   196,   196,
     197,   197,   197,   197,   197,   197,   199,   198,   201,   200,
     202,   202,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   204,
     205,   206,   207,   208,   209,   211,   210,   212,   212,   213,
     213,   213,   213,   213,   213,   213,   215,   214,   217,   216,
     219,   218,   220,   220,   222,   221,   223,   223,   224,   226,
     225,   228,   227,   230,   229,   231,   231,   232,   232,   234,
     233,   235,   235,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   238,   237,   239,   239,   239,   239,   241,   240,   243,
     242,   245,   244,   246,   248,   247,   249,   250,   251,   252,
     253,   254,   255,   257,   256,   259,   258,   260,   261,   263,
     262,   264,   264,   265,   265,   265,   265,   265,   266,   267,
     268,   269,   270,   272,   271,   273,   273,   274,   274,   276,
     275,   278,   277,   279,   279,   279,   280,   280,   282,   281,
     284,   283,   286,   285,   287,   287,   288,   288,   288,   288,
     288,   288,   289,   290,   291,   292,   293,   294,   296,   295,
     297,   297,   298,   298,   300,   299,   302,   301,   303,   303,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   306,   305,   308,   307,   310,
     309,   312,   311,   314,   313,   316,   315,   318,   317,   320,
     319,   322,   321,   323,   323,   323,   324,   325,   327,   326,
     328,   328,   329,   329,   331,   330,   332,   332,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   335,   334,   337,   336,
     338,   338,   339,   339,   341,   340,   343,   342,   344,   344,
     345,   345,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   347,   348,   349,   351,   350,   353,   352,   355,
     354,   356,   358,   357,   359,   361,   360,   362,   362,   363,
     363,   365,   364,   367,   366,   368,   368,   369,   369,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   371,   373,
     372,   374,   375,   376,   377,   379,   378,   380,   380,   381,
     381,   383,   382,   385,   384,   386,   386,   387,   387,   387,
     387,   387,   387,   387,   389,   388,   391,   390,   393,   392,
     395,   394,   396,   396,   397,   397,   399,   398,   401,   400,
     402,   402,   403,   403,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   406,
     405,   408,   407,   410,   409,   412,   411,   414,   413,   416,
     415,   418,   417,   420,   419,   422,   421,   424,   423,   426,
     425,   428,   427,   430,   429,   431,   431,   433,   432,   434,
     434,   436,   435,   437,   437,   438,   438,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   440,   442,
     441,   443,   444,   446,   445,   447,   447,   448,   448,   448,
     448,   448,   450,   449,   452,   451,   454,   453,   456,   455,
     457,   457,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   459,   461,   460,   463,   462,   464,   466,   465,   467,
     468,   470,   469,   471,   471,   473,   472,   474,   475,   476,
     478,   477,   479,   479,   479,   479,   479,   481,   480,   483,
     482,   485,   484,   487,   486,   489,   488,   491,   490,   493,
     492,   495,   494,   496,   496,   497,   499,   498,   500,   500,
     502,   501,   503,   503,   504,   504,   504,   504,   504,   504,
     504,   505,   507,   506,   509,   508,   510,   510,   512,   511,
     513,   513,   514,   514,   514,   514,   516,   515,   517,   518,
     519
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     4,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     1,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"echo-client-id\"",
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
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"all\"",
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
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "value",
  "sub_json", "map2", "$@14", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@15", "list_content", "not_empty_list", "list_strings",
  "$@16", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@17", "global_objects",
  "global_object", "dhcp4_object", "$@18", "sub_dhcp4", "$@19",
  "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@20",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@21", "interfaces_list", "$@22", "dhcp_socket_type", "$@23",
  "socket_type", "outbound_interface", "$@24", "outbound_interface_value",
  "re_detect", "lease_database", "$@25", "hosts_database", "$@26",
  "hosts_databases", "$@27", "database_list", "not_empty_database_list",
  "database", "$@28", "database_map_params", "database_map_param",
  "database_type", "$@29", "db_type", "user", "$@30", "password", "$@31",
  "host", "$@32", "port", "name", "$@33", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@34", "keyspace", "$@35",
  "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@36",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@37", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@38",
  "sub_hooks_library", "$@39", "hooks_params", "hooks_param", "library",
  "$@40", "parameters", "$@41", "expired_leases_processing", "$@42",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@43",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@44",
  "sub_subnet4", "$@45", "subnet4_params", "subnet4_param", "subnet",
  "$@46", "subnet_4o6_interface", "$@47", "subnet_4o6_interface_id",
  "$@48", "subnet_4o6_subnet", "$@49", "interface", "$@50", "interface_id",
  "$@51", "client_class", "$@52", "require_client_classes", "$@53",
  "reservation_mode", "$@54", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@55", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@56",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@57", "sub_option_def_list", "$@58", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@59",
  "sub_option_def", "$@60", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@61",
  "option_def_record_types", "$@62", "space", "$@63", "option_def_space",
  "option_def_encapsulate", "$@64", "option_def_array", "option_data_list",
  "$@65", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@66", "sub_option_data", "$@67",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@68",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@69", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@70", "sub_pool4", "$@71",
  "pool_params", "pool_param", "pool_entry", "$@72", "user_context",
  "$@73", "comment", "$@74", "reservations", "$@75", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@76", "sub_reservation",
  "$@77", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@78", "server_hostname", "$@79",
  "boot_file_name", "$@80", "ip_address", "$@81", "ip_addresses", "$@82",
  "duid", "$@83", "hw_address", "$@84", "client_id_value", "$@85",
  "circuit_id_value", "$@86", "flex_id_value", "$@87", "hostname", "$@88",
  "reservation_client_classes", "$@89", "relay", "$@90", "relay_map",
  "client_classes", "$@91", "client_classes_list", "client_class_entry",
  "$@92", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@93",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@94",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@95", "control_socket_name", "$@96", "dhcp_ddns", "$@97",
  "sub_dhcp_ddns", "$@98", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@99", "server_ip", "$@100",
  "server_port", "sender_ip", "$@101", "sender_port", "max_queue_size",
  "ncr_protocol", "$@102", "ncr_protocol_value", "ncr_format", "$@103",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@104", "replace_client_name_value",
  "generated_prefix", "$@105", "hostname_char_set", "$@106",
  "hostname_char_replacement", "$@107", "dhcp6_json_object", "$@108",
  "dhcpddns_json_object", "$@109", "control_agent_json_object", "$@110",
  "logging_object", "$@111", "sub_logging", "$@112", "logging_params",
  "logging_param", "loggers", "$@113", "loggers_entries", "logger_entry",
  "$@114", "logger_params", "logger_param", "debuglevel", "severity",
  "$@115", "output_options_list", "$@116", "output_options_list_content",
  "output_entry", "$@117", "output_params_list", "output_params", "output",
  "$@118", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   246,   246,   246,   247,   247,   248,   248,   249,   249,
     250,   250,   251,   251,   252,   252,   253,   253,   254,   254,
     255,   255,   256,   256,   257,   257,   258,   258,   266,   267,
     268,   269,   270,   271,   272,   275,   280,   280,   291,   294,
     295,   298,   302,   309,   309,   316,   317,   320,   324,   331,
     331,   338,   339,   342,   346,   357,   367,   367,   383,   384,
     388,   389,   390,   391,   392,   393,   396,   396,   411,   411,
     420,   421,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   455,
     460,   465,   470,   475,   480,   486,   486,   497,   498,   501,
     502,   503,   504,   505,   506,   507,   510,   510,   519,   519,
     529,   529,   536,   537,   540,   540,   547,   549,   553,   559,
     559,   571,   571,   583,   583,   593,   594,   597,   598,   601,
     601,   611,   612,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,   635,   635,   642,   643,   644,   645,   648,   648,   656,
     656,   664,   664,   672,   677,   677,   685,   690,   695,   700,
     705,   710,   715,   720,   720,   728,   728,   736,   741,   746,
     746,   756,   757,   760,   761,   762,   763,   764,   767,   772,
     777,   782,   787,   792,   792,   802,   803,   806,   807,   810,
     810,   820,   820,   830,   831,   832,   835,   836,   839,   839,
     847,   847,   855,   855,   866,   867,   870,   871,   872,   873,
     874,   875,   878,   883,   888,   893,   898,   903,   911,   911,
     924,   925,   928,   929,   936,   936,   962,   962,   973,   974,
     978,   979,   980,   981,   982,   983,   984,   985,   986,   987,
     988,   989,   990,   991,   992,   993,   994,   995,   996,   997,
     998,   999,  1000,  1001,  1002,  1005,  1005,  1013,  1013,  1021,
    1021,  1029,  1029,  1037,  1037,  1045,  1045,  1053,  1053,  1061,
    1061,  1071,  1071,  1078,  1079,  1080,  1083,  1088,  1095,  1095,
    1106,  1107,  1111,  1112,  1115,  1115,  1123,  1124,  1127,  1128,
    1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,  1138,
    1139,  1140,  1141,  1142,  1143,  1144,  1151,  1151,  1164,  1164,
    1173,  1174,  1177,  1178,  1183,  1183,  1198,  1198,  1212,  1213,
    1216,  1217,  1220,  1221,  1222,  1223,  1224,  1225,  1226,  1227,
    1228,  1229,  1232,  1234,  1239,  1241,  1241,  1249,  1249,  1257,
    1257,  1265,  1267,  1267,  1275,  1284,  1284,  1296,  1297,  1302,
    1303,  1308,  1308,  1320,  1320,  1332,  1333,  1338,  1339,  1344,
    1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1355,  1357,
    1357,  1365,  1367,  1369,  1374,  1382,  1382,  1394,  1395,  1398,
    1399,  1402,  1402,  1412,  1412,  1422,  1423,  1426,  1427,  1428,
    1429,  1430,  1431,  1432,  1435,  1435,  1443,  1443,  1468,  1468,
    1498,  1498,  1508,  1509,  1512,  1513,  1516,  1516,  1525,  1525,
    1534,  1535,  1538,  1539,  1543,  1544,  1545,  1546,  1547,  1548,
    1549,  1550,  1551,  1552,  1553,  1554,  1555,  1556,  1557,  1560,
    1560,  1568,  1568,  1576,  1576,  1584,  1584,  1592,  1592,  1602,
    1602,  1610,  1610,  1618,  1618,  1626,  1626,  1634,  1634,  1642,
    1642,  1650,  1650,  1663,  1663,  1673,  1674,  1680,  1680,  1690,
    1691,  1694,  1694,  1704,  1705,  1708,  1709,  1712,  1713,  1714,
    1715,  1716,  1717,  1718,  1719,  1720,  1721,  1722,  1725,  1727,
    1727,  1735,  1744,  1751,  1751,  1761,  1762,  1765,  1766,  1767,
    1768,  1769,  1772,  1772,  1780,  1780,  1790,  1790,  1802,  1802,
    1812,  1813,  1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,
    1824,  1825,  1826,  1827,  1828,  1829,  1830,  1831,  1832,  1833,
    1834,  1837,  1842,  1842,  1850,  1850,  1858,  1863,  1863,  1871,
    1876,  1881,  1881,  1889,  1890,  1893,  1893,  1901,  1906,  1911,
    1916,  1916,  1924,  1927,  1930,  1933,  1936,  1942,  1942,  1950,
    1950,  1958,  1958,  1969,  1969,  1976,  1976,  1983,  1983,  1995,
    1995,  2005,  2005,  2016,  2017,  2021,  2025,  2025,  2037,  2038,
    2042,  2042,  2050,  2051,  2054,  2055,  2056,  2057,  2058,  2059,
    2060,  2063,  2068,  2068,  2076,  2076,  2086,  2087,  2090,  2090,
    2098,  2099,  2102,  2103,  2104,  2105,  2108,  2108,  2116,  2121,
    2126
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
#line 4700 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2131 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
