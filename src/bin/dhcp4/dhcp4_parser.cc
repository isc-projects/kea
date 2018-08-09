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
      case 180: // value
      case 184: // map_value
      case 222: // socket_type
      case 225: // outbound_interface_value
      case 247: // db_type
      case 331: // hr_mode
      case 479: // ncr_protocol_value
      case 487: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 164: // "boolean"
        value.move< bool > (that.value);
        break;

      case 163: // "floating point"
        value.move< double > (that.value);
        break;

      case 162: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 161: // "constant string"
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
      case 180: // value
      case 184: // map_value
      case 222: // socket_type
      case 225: // outbound_interface_value
      case 247: // db_type
      case 331: // hr_mode
      case 479: // ncr_protocol_value
      case 487: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 164: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 163: // "floating point"
        value.copy< double > (that.value);
        break;

      case 162: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 161: // "constant string"
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
            case 161: // "constant string"

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 162: // "integer"

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 163: // "floating point"

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 164: // "boolean"

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 180: // value

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 184: // map_value

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 222: // socket_type

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 225: // outbound_interface_value

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 247: // db_type

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 331: // hr_mode

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 479: // ncr_protocol_value

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 487: // replace_client_name_value

#line 240 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 180: // value
      case 184: // map_value
      case 222: // socket_type
      case 225: // outbound_interface_value
      case 247: // db_type
      case 331: // hr_mode
      case 479: // ncr_protocol_value
      case 487: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 164: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 163: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 162: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 161: // "constant string"
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
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 294 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 301 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 305 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 323 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 327 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 345 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 349 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 375 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 399 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 683 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 694 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1481 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 753 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 789 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 848 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 885 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1743 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 974 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 978 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 1000 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1104 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2110 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1221 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2254 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1789 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3110 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1928 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1962 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1965 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1968 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1971 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3210 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1974 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3219 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2080 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2101 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2114 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2128 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3457 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2132 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2146 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2159 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3501 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3510 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3514 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -777;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     275,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,    53,    27,    61,    82,   140,   149,
     153,   168,   174,   178,   186,   189,   190,   192,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,    27,   -46,    25,    85,    48,   177,
     133,    58,    87,    56,   151,   -63,   469,    70,  -777,   202,
     207,   218,   223,   234,  -777,  -777,  -777,  -777,  -777,   241,
    -777,    46,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
     253,   256,  -777,  -777,  -777,  -777,  -777,  -777,   257,   266,
     267,   274,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,   278,  -777,  -777,  -777,    77,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
     279,  -777,    98,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,   295,   318,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   124,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,   138,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,   251,   298,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,   312,  -777,  -777,   321,
    -777,  -777,  -777,   322,  -777,  -777,   320,   327,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,   329,   330,  -777,  -777,  -777,  -777,   323,   333,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,   170,  -777,  -777,  -777,   339,  -777,  -777,   341,  -777,
     344,   345,  -777,  -777,   346,   347,   348,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,   217,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,   227,  -777,  -777,  -777,    27,    27,  -777,
     193,   349,   355,   356,   359,   360,  -777,    25,  -777,   362,
     363,   205,   206,   370,   372,   375,   376,   377,   383,   231,
     233,   235,   236,   385,   396,   398,   401,   407,   412,   415,
     416,   417,   432,   433,   280,   440,   441,    85,  -777,   442,
     443,   446,   291,    48,  -777,   447,   448,   449,   450,   452,
     453,   454,   301,   296,   455,   461,   462,   463,   177,  -777,
     465,   133,  -777,   466,   467,   468,   471,   472,   474,   475,
     476,  -777,    58,  -777,   477,   478,   311,   480,   482,   483,
     324,  -777,    56,   485,   328,   332,  -777,   151,   487,   489,
     -22,  -777,   334,   490,   493,   337,   496,   340,   343,   497,
     499,   342,   350,   353,   504,   505,   506,   507,   469,  -777,
     508,    70,  -777,  -777,  -777,   509,   511,   512,    27,    27,
      27,  -777,   513,   514,  -777,  -777,   361,   364,   365,   516,
     517,   524,  -777,  -777,  -777,  -777,   525,   526,   527,   528,
     529,   373,   532,   533,   534,   535,   536,  -777,   537,   538,
    -777,   541,    73,   108,  -777,  -777,   386,   387,   388,   546,
     392,   393,   411,  -777,  -777,   -41,   541,   413,   566,  -777,
     414,  -777,   541,   418,   419,   420,   436,   437,   438,   439,
    -777,   444,   445,  -777,   451,   456,   457,  -777,  -777,   458,
    -777,  -777,  -777,   459,    27,  -777,  -777,   460,   464,  -777,
     470,  -777,  -777,    31,   473,  -777,  -777,  -777,   -60,   479,
     481,   484,  -777,   571,  -777,    27,    85,    70,  -777,  -777,
    -777,    48,   556,  -777,  -777,  -777,   522,   522,   594,   600,
     601,   602,   603,  -777,  -777,  -777,     2,   604,   606,   607,
      59,   -21,   469,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,   608,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,    36,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   609,  -777,
     240,   255,   269,  -777,   276,  -777,  -777,  -777,  -777,  -777,
    -777,   574,   618,   619,   620,   622,  -777,  -777,   623,   624,
     625,   628,   629,  -777,   277,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,   287,  -777,   630,   631,  -777,  -777,   632,
     634,  -777,  -777,   633,   638,  -777,  -777,   637,   641,  -777,
    -777,   640,   644,  -777,  -777,  -777,  -777,  -777,  -777,    63,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,    96,  -777,  -777,
     642,   646,  -777,  -777,   645,   647,  -777,   648,   649,   650,
     651,   652,   653,   288,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,   289,  -777,  -777,  -777,
     290,   498,  -777,   654,   655,  -777,  -777,  -777,  -777,   627,
    -777,    97,  -777,  -777,  -777,  -777,   657,   556,  -777,   658,
     659,   660,   661,   510,   502,   515,   503,   518,   664,   665,
     519,   520,   523,   530,   531,   522,  -777,  -777,   522,  -777,
     594,   177,  -777,   600,    56,  -777,   601,   151,  -777,   602,
     389,  -777,   603,     2,  -777,   216,   604,  -777,    58,  -777,
     606,   -63,  -777,   607,   539,   540,   542,   543,   544,   545,
      59,  -777,   666,   667,   -21,  -777,  -777,  -777,   668,   670,
     133,  -777,   608,   671,  -777,   166,   609,  -777,   547,  -777,
     308,   548,   549,   550,  -777,  -777,  -777,  -777,  -777,   551,
     552,  -777,  -777,  -777,  -777,  -777,  -777,   297,  -777,   305,
    -777,   676,  -777,   678,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,   306,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   672,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   679,   675,
    -777,  -777,  -777,  -777,  -777,   680,  -777,   307,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,   553,   554,  -777,  -777,
     555,   313,  -777,   541,  -777,   685,  -777,  -777,  -777,  -777,
    -777,   315,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,   389,  -777,   686,   557,  -777,   216,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,   687,   558,   689,   166,  -777,
    -777,   561,  -777,  -777,   674,  -777,   562,  -777,  -777,   690,
    -777,  -777,   176,  -777,   125,   690,  -777,  -777,   692,   694,
     695,   316,  -777,  -777,  -777,  -777,  -777,  -777,   696,   560,
     564,   565,   125,  -777,   568,  -777,  -777,  -777,  -777,  -777
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   118,     9,   255,    11,   412,    13,
     437,    15,   337,    17,   345,    19,   382,    21,   220,    23,
     527,    25,   590,    27,    45,    39,     0,     0,     0,     0,
       0,   439,     0,   347,   384,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   588,   582,   584,   586,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   107,   133,
       0,     0,   458,   460,   462,   131,   140,   142,     0,     0,
       0,     0,   247,   335,   374,   307,   425,   427,   198,   486,
     429,   212,   231,     0,   512,   525,   100,     0,    70,    72,
      73,    74,    75,    91,    92,    78,    79,    98,    80,    81,
      82,    86,    87,    76,    77,    84,    85,    96,    97,    99,
      93,    94,    95,    83,    88,    89,    90,   120,   122,   126,
       0,   117,     0,   109,   111,   112,   113,   114,   115,   116,
     286,   288,   290,   404,   284,   292,   294,     0,     0,   300,
     298,   296,   482,   283,   259,   260,   261,   274,     0,   257,
     264,   278,   279,   280,   265,   266,   269,   270,   272,   267,
     268,   262,   263,   281,   282,   271,   275,   276,   277,   273,
     423,   422,   418,   419,   417,     0,   414,   416,   420,   421,
     480,   468,   470,   474,   472,   478,   476,   464,   457,   451,
     455,   456,     0,   440,   441,   452,   453,   454,   448,   443,
     449,   445,   446,   447,   450,   444,     0,   364,   183,     0,
     368,   366,   371,     0,   360,   361,     0,   348,   349,   351,
     363,   352,   353,   354,   370,   355,   356,   357,   358,   359,
     398,     0,     0,   396,   397,   400,   401,     0,   385,   386,
     388,   389,   390,   391,   392,   393,   394,   395,   227,   229,
     224,     0,   222,   225,   226,     0,   551,   553,     0,   556,
       0,     0,   560,   564,     0,     0,     0,   569,   576,   578,
     580,   549,   547,   548,     0,   529,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   595,     0,   592,   594,    44,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    55,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    69,     0,
       0,     0,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   256,
       0,     0,   413,     0,     0,     0,     0,     0,     0,     0,
       0,   438,     0,   338,     0,     0,     0,     0,     0,     0,
       0,   346,     0,     0,     0,     0,   383,     0,     0,     0,
       0,   221,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   528,
       0,     0,   591,    48,    41,     0,     0,     0,     0,     0,
       0,    59,     0,     0,   105,   106,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   511,     0,     0,
      71,     0,     0,     0,   130,   110,     0,     0,     0,     0,
       0,     0,     0,   305,   306,     0,     0,     0,     0,   258,
       0,   415,     0,     0,     0,     0,     0,     0,     0,     0,
     442,     0,     0,   362,     0,     0,     0,   373,   350,     0,
     402,   403,   387,     0,     0,   223,   550,     0,     0,   555,
       0,   558,   559,     0,     0,   566,   567,   568,     0,     0,
       0,     0,   530,     0,   593,     0,     0,     0,   583,   585,
     587,     0,     0,   459,   461,   463,     0,     0,   144,   249,
     339,   376,   309,    38,   426,   428,     0,     0,   431,   214,
       0,     0,     0,    49,   121,   124,   125,   123,   128,   129,
     127,   287,   289,   291,   406,   285,   293,   295,   302,   303,
     304,   301,   299,   297,     0,   424,   481,   469,   471,   475,
     473,   479,   477,   465,   365,   184,   369,   367,   372,   399,
     228,   230,   552,   554,   557,   562,   563,   561,   565,   571,
     572,   573,   574,   575,   570,   577,   579,   581,     0,    42,
       0,     0,     0,   138,     0,   135,   137,   170,   176,   178,
     180,     0,     0,     0,     0,     0,   192,   194,     0,     0,
       0,     0,     0,   169,     0,   150,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   165,   166,   167,   162,
     168,   163,   164,     0,   148,     0,   145,   146,   253,     0,
     250,   251,   343,     0,   340,   341,   380,     0,   377,   378,
     313,     0,   310,   311,   207,   208,   209,   210,   211,     0,
     200,   202,   203,   204,   205,   206,   490,     0,   488,   435,
       0,   432,   433,   218,     0,   215,   216,     0,     0,     0,
       0,     0,     0,     0,   233,   235,   236,   237,   238,   239,
     240,   521,   523,   520,   518,   519,     0,   514,   516,   517,
       0,    51,   410,     0,   407,   408,   466,   484,   485,     0,
     599,     0,   597,    67,   589,   108,     0,     0,   134,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   132,   141,     0,   143,
       0,     0,   248,     0,   347,   336,     0,   384,   375,     0,
       0,   308,     0,     0,   199,   492,     0,   487,   439,   430,
       0,     0,   213,     0,     0,     0,     0,     0,     0,     0,
       0,   232,     0,     0,     0,   513,   526,    53,     0,    52,
       0,   405,     0,     0,   483,     0,     0,   596,     0,   136,
       0,     0,     0,     0,   182,   185,   186,   187,   188,     0,
       0,   196,   197,   189,   190,   191,   151,     0,   147,     0,
     252,     0,   342,     0,   379,   334,   331,   320,   321,   323,
     317,   318,   319,   329,   330,   328,     0,   315,   322,   332,
     333,   324,   325,   326,   327,   312,   201,   508,     0,   506,
     507,   499,   500,   504,   505,   501,   502,   503,     0,   493,
     494,   496,   497,   498,   489,     0,   434,     0,   217,   241,
     242,   243,   244,   245,   246,   234,     0,     0,   515,    50,
       0,     0,   409,     0,   613,     0,   611,   609,   603,   607,
     608,     0,   601,   605,   606,   604,   598,   139,   172,   173,
     174,   175,   171,   177,   179,   181,   193,   195,   149,   254,
     344,   381,     0,   314,     0,     0,   491,     0,   436,   219,
     522,   524,    54,   411,   467,     0,     0,     0,     0,   600,
     316,     0,   510,   495,     0,   610,     0,   602,   509,     0,
     612,   617,     0,   615,     0,     0,   614,   625,     0,     0,
       0,     0,   619,   621,   622,   623,   624,   616,     0,     0,
       0,     0,     0,   618,     0,   627,   628,   629,   620,   626
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,   -51,  -777,   214,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -485,  -777,  -777,  -777,
     -66,  -777,  -777,  -777,   371,  -777,  -777,  -777,  -777,   147,
     382,   -43,   -14,    -7,  -777,  -777,    12,  -777,  -777,   156,
     336,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,   -37,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,   -58,  -777,  -544,   -52,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
     -44,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   -65,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   -53,  -777,
    -777,  -777,   -59,   317,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,   -71,  -777,  -777,  -777,  -777,  -777,  -777,  -776,  -777,
    -777,  -777,   -31,  -777,  -777,  -777,   -28,   369,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -775,  -777,  -777,  -777,
     -64,  -777,   -11,  -777,  -772,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,   -30,  -777,  -777,  -179,   -61,  -777,  -777,
    -777,  -777,  -777,   -16,  -777,  -777,  -777,   -19,  -777,   366,
    -777,   -62,  -777,  -777,  -777,  -777,  -777,   -56,  -777,  -777,
    -777,  -777,  -777,   -13,  -777,  -777,  -777,    -9,  -777,  -777,
    -777,     3,  -777,   374,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,   -49,  -777,  -777,  -777,   -23,
     421,  -777,  -777,   -54,  -777,   -26,  -777,   -36,  -777,  -777,
    -777,    -2,  -777,  -777,  -777,     7,  -777,   404,    -6,  -777,
       5,  -777,     6,  -777,   219,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -769,  -777,  -777,  -777,  -777,  -777,    14,  -777,
    -777,  -777,  -139,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,    -3,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
     242,   378,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   268,
     379,  -777,  -777,  -777,    -8,  -777,  -777,  -141,  -777,  -777,
    -777,  -777,  -777,  -777,  -156,  -777,  -777,  -171,  -777,  -777,
    -777,  -777,  -777
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   574,
      82,    83,    39,    64,    79,    80,   584,   751,   828,   829,
     663,    41,    66,    91,    92,    93,   341,    43,    67,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   349,   162,
     163,    45,    68,   164,   379,   165,   380,   587,   166,   381,
     590,   167,   136,   356,   137,   350,   644,   645,   646,   766,
     138,   357,   139,   358,   685,   686,   687,   788,   664,   665,
     666,   769,   942,   667,   770,   668,   771,   669,   772,   670,
     671,   415,   672,   673,   674,   675,   676,   677,   678,   679,
     778,   680,   779,   681,   682,   140,   369,   709,   710,   711,
     712,   713,   714,   715,   141,   372,   724,   725,   726,   811,
      59,    75,   291,   292,   293,   428,   294,   429,   142,   373,
     733,   734,   735,   736,   737,   738,   739,   740,   143,   363,
     689,   690,   691,   791,    47,    69,   188,   189,   190,   389,
     191,   385,   192,   386,   193,   387,   194,   390,   195,   391,
     196,   396,   197,   395,   198,   394,   601,   199,   200,   144,
     366,   701,   702,   703,   800,   876,   877,   145,   364,    53,
      72,   693,   694,   695,   794,    55,    73,   256,   257,   258,
     259,   260,   261,   262,   414,   263,   418,   264,   417,   265,
     266,   419,   267,   146,   365,   697,   698,   699,   797,    57,
      74,   277,   278,   279,   280,   281,   423,   282,   283,   284,
     285,   202,   388,   753,   754,   755,   830,    49,    70,   215,
     216,   217,   400,   147,   367,   148,   368,   149,   371,   720,
     721,   722,   808,    51,    71,   232,   233,   234,   150,   353,
     151,   354,   152,   355,   238,   410,   758,   833,   239,   404,
     240,   405,   241,   407,   242,   406,   243,   409,   244,   408,
     245,   403,   209,   397,   759,   153,   370,   717,   718,   805,
     898,   899,   900,   901,   902,   954,   903,   154,   155,   375,
     746,   747,   748,   822,   749,   823,   156,   376,    61,    76,
     314,   315,   316,   317,   433,   318,   434,   319,   320,   436,
     321,   322,   323,   439,   627,   324,   440,   325,   326,   327,
     328,   444,   634,   329,   445,   330,   446,   331,   447,    94,
     343,    95,   344,    96,   345,    97,   342,    63,    77,   333,
     334,   335,   450,   761,   762,   835,   931,   932,   933,   934,
     967,   935,   965,   982,   983,   984,   991,   992,   993,   998,
     994,   995,   996
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   126,   161,   183,   211,   228,   212,   254,   273,   290,
     311,   246,   275,    78,   168,   203,   218,   230,   276,   268,
     286,   602,   312,   683,   871,   872,   184,   606,   875,   255,
     274,   884,    29,   205,    30,    84,    31,   288,   289,   598,
     599,   600,   169,   204,   219,   231,   625,   269,   287,   347,
     313,   116,   117,    28,   348,   185,   201,   214,   229,   213,
     157,   158,   186,   206,   159,   235,   803,   160,    40,   804,
     629,   630,   631,   632,   207,   208,   236,   237,   288,   289,
     377,   187,   102,   103,   104,   378,   247,   585,   586,    42,
     741,   742,   704,   705,   706,   707,    98,   708,    89,   806,
     836,   383,   807,   837,   633,    99,   384,   100,   101,   102,
     103,   104,   105,   106,   107,    81,   248,   114,   249,   250,
     116,   117,   251,   252,   253,   588,   589,   398,   116,   117,
     116,   117,   399,   227,   756,   108,   109,   110,   111,   112,
      89,   401,   220,   113,   114,   113,   402,    44,   221,   222,
     223,   224,   225,   226,   115,   227,    46,   116,   117,   626,
      48,    85,   727,   728,   729,   730,   731,   732,   118,   119,
      86,    87,    88,   430,   120,    50,   871,   872,   431,   985,
     875,    52,   986,   884,   121,    54,    89,   122,    32,    33,
      34,    35,   114,    56,   123,   124,    58,    60,   125,    62,
     101,   102,   103,   104,   210,   116,   117,   332,   336,    89,
     337,   248,   270,   249,   250,   271,   272,    89,   180,    89,
     448,   181,   338,   116,   117,   449,   248,   108,   109,   110,
     451,   339,   170,   171,   172,   452,   114,   340,   116,   117,
     102,   103,   104,   377,   857,   346,    89,   173,   763,   116,
     117,   174,   175,   176,   177,   178,   179,   351,   451,   411,
     352,   359,   180,   764,   987,   181,   120,   988,   989,   990,
     360,   361,   383,   182,   113,   114,   248,   765,   362,   767,
     785,    90,   374,   382,   768,   786,   453,   454,   116,   117,
     785,   820,   824,   448,    89,   787,   821,   825,   826,   392,
     785,   412,   887,   888,   924,   948,   925,   926,   398,   952,
     430,   126,    89,   949,   953,   959,   401,   161,   968,  1002,
     413,   963,   393,   969,  1003,   416,   420,    89,   421,   168,
     422,   426,   183,   424,   425,   211,   427,   212,    89,   938,
     939,   940,   941,   432,   203,   435,   228,   218,   437,   438,
     441,   442,   443,   456,   455,   184,   254,   169,   230,   457,
     458,   273,   205,   459,   460,   275,   462,   463,   268,   464,
     465,   276,   204,   286,   466,   219,   467,    89,   255,   468,
     469,   470,   311,   274,   185,   201,   231,   471,   214,   476,
     213,   186,   206,   472,   312,   473,   269,   474,   475,   229,
     477,   287,   478,   207,   208,   479,   235,   558,   559,   560,
     187,   480,   101,   102,   103,   104,   481,   236,   237,   482,
     483,   484,   313,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   485,   486,   964,   108,
     109,   110,   487,   112,   488,   489,   491,   492,   114,   248,
     493,   496,   497,   498,   499,   494,   500,   501,   502,   505,
     504,   116,   117,   503,   175,   506,   507,   508,   179,   510,
     512,   513,   514,   523,   180,   515,   516,   181,   517,   518,
     519,   521,   522,   621,   524,   182,   525,   526,   527,   529,
     126,   533,   530,   534,   537,   161,   531,   538,   536,   539,
     540,   543,   541,   544,   639,   542,   545,   168,   548,   549,
     550,   551,   553,   555,   546,   743,   311,   547,   556,   557,
     561,   562,   563,   566,   567,   564,   565,   744,   312,   568,
     569,   570,   571,   572,   575,   169,    30,   576,   577,   578,
     579,   116,   117,   580,   581,   582,   583,   591,   592,   593,
      89,   594,   647,   595,   596,   745,   313,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   597,   604,   603,   605,   638,   643,   773,   607,
     608,   609,   248,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   610,   611,   612,
     613,   684,   628,   309,   310,   614,   615,   688,   692,   696,
     700,   716,   616,   719,   723,   752,   760,   617,   618,   619,
     620,   622,   774,   775,   776,   623,   777,   780,   781,   782,
      89,   624,   783,   784,   790,   834,   789,   793,   792,   795,
     635,   796,   636,   798,   799,   637,   801,   802,   809,   810,
     813,   812,   814,   815,   816,   817,   818,   819,   832,   827,
     831,   838,   840,   841,   842,   843,   845,   847,   849,   850,
     916,   917,   844,   920,   919,   923,   955,   846,   957,   979,
     848,   851,   852,    89,   950,   853,   951,   956,   958,   966,
     971,   974,   854,   976,   573,   855,   999,   981,  1000,  1001,
    1004,   909,   910,   640,   911,   912,   913,   914,   937,   943,
     944,   945,   946,   947,   960,   961,   962,   642,   461,   495,
     975,   972,   978,   980,  1005,   183,  1006,  1007,   254,  1009,
     839,   273,   858,   856,   865,   275,   873,   203,   886,   889,
     268,   276,   228,   286,   891,   290,   879,   535,   184,   915,
     255,   893,   907,   274,   230,   205,   870,   866,   743,   490,
     908,   890,   860,   859,   211,   204,   212,   509,   269,   927,
     744,   287,   885,   970,   880,   861,   218,   185,   201,   894,
     862,   929,   231,   922,   186,   206,   867,   878,   528,   874,
     864,   928,   892,   868,   881,   229,   207,   208,   745,   895,
     863,   532,   235,   187,   219,   882,   883,   921,   906,   930,
     896,   897,   869,   236,   237,   905,   520,   214,   973,   213,
     904,   918,   511,   757,   750,   641,   552,   977,   936,   997,
     554,  1008,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   865,     0,   873,     0,
       0,   889,     0,     0,     0,     0,   891,     0,   879,     0,
       0,     0,   927,   893,     0,     0,     0,     0,   870,   866,
       0,     0,     0,   890,   929,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   928,     0,   880,     0,     0,     0,
       0,   894,     0,     0,     0,     0,     0,     0,   867,   878,
       0,   874,   930,     0,   892,   868,   881,     0,     0,     0,
       0,   895,     0,     0,     0,     0,     0,   882,   883,     0,
       0,     0,   896,   897,   869
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,    70,    73,    74,    75,
      76,    72,    74,    64,    68,    69,    70,    71,    74,    73,
      74,   506,    76,   567,   800,   800,    69,   512,   800,    73,
      74,   800,     5,    69,     7,    10,     9,   100,   101,    80,
      81,    82,    68,    69,    70,    71,    15,    73,    74,     3,
      76,    72,    73,     0,     8,    69,    69,    70,    71,    70,
      12,    13,    69,    69,    16,    71,     3,    19,     7,     6,
     130,   131,   132,   133,    69,    69,    71,    71,   100,   101,
       3,    69,    24,    25,    26,     8,    30,    14,    15,     7,
     111,   112,    90,    91,    92,    93,    11,    95,   161,     3,
       3,     3,     6,     6,   164,    20,     8,    22,    23,    24,
      25,    26,    27,    28,    29,   161,    60,    59,    62,    63,
      72,    73,    66,    67,    68,    17,    18,     3,    72,    73,
      72,    73,     8,    97,    98,    50,    51,    52,    53,    54,
     161,     3,    84,    58,    59,    58,     8,     7,    90,    91,
      92,    93,    94,    95,    69,    97,     7,    72,    73,   128,
       7,   136,   103,   104,   105,   106,   107,   108,    83,    84,
     145,   146,   147,     3,    89,     7,   952,   952,     8,     3,
     952,     7,     6,   952,    99,     7,   161,   102,   161,   162,
     163,   164,    59,     7,   109,   110,     7,     7,   113,     7,
      23,    24,    25,    26,    71,    72,    73,   137,     6,   161,
       3,    60,    61,    62,    63,    64,    65,   161,    85,   161,
       3,    88,     4,    72,    73,     8,    60,    50,    51,    52,
       3,     8,    55,    56,    57,     8,    59,     3,    72,    73,
      24,    25,    26,     3,   788,     4,   161,    70,     8,    72,
      73,    74,    75,    76,    77,    78,    79,     4,     3,     8,
       4,     4,    85,     8,   139,    88,    89,   142,   143,   144,
       4,     4,     3,    96,    58,    59,    60,     8,     4,     3,
       3,   347,     4,     4,     8,     8,   337,   338,    72,    73,
       3,     3,     3,     3,   161,     8,     8,     8,     8,     4,
       3,     3,    86,    87,   138,     8,   140,   141,     3,     3,
       3,   377,   161,     8,     8,     8,     3,   383,     3,     3,
       8,     8,     4,     8,     8,     4,     4,   161,     8,   383,
       3,     8,   398,     4,     4,   401,     3,   401,   161,    31,
      32,    33,    34,     4,   398,     4,   412,   401,     4,     4,
       4,     4,     4,     4,   161,   398,   422,   383,   412,     4,
       4,   427,   398,     4,     4,   427,     4,     4,   422,   164,
     164,   427,   398,   427,     4,   401,     4,   161,   422,     4,
       4,     4,   448,   427,   398,   398,   412,     4,   401,     4,
     401,   398,   398,   162,   448,   162,   422,   162,   162,   412,
       4,   427,     4,   398,   398,     4,   412,   458,   459,   460,
     398,     4,    23,    24,    25,    26,     4,   412,   412,     4,
       4,     4,   448,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,     4,     4,   923,    50,
      51,    52,   162,    54,     4,     4,     4,     4,    59,    60,
       4,     4,     4,     4,     4,   164,     4,     4,     4,     4,
     164,    72,    73,   162,    75,     4,     4,     4,    79,     4,
       4,     4,     4,   162,    85,     4,     4,    88,     4,     4,
       4,     4,     4,   534,     4,    96,     4,     4,   164,     4,
     556,     4,   164,     4,     4,   561,   164,     4,   164,   162,
       4,     4,   162,     4,   555,   162,   164,   561,     4,     4,
       4,     4,     4,     4,   164,   581,   582,   164,     7,     7,
       7,     7,   161,     7,     7,   161,   161,   581,   582,     5,
       5,     5,     5,     5,   161,   561,     7,     5,     5,     5,
       5,    72,    73,     7,     7,     7,     5,   161,   161,   161,
     161,     5,    30,   161,   161,   581,   582,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,   161,     7,   161,   161,     5,    21,     4,   161,
     161,   161,    60,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   161,   161,   161,
     161,     7,   129,   134,   135,   161,   161,     7,     7,     7,
       7,     7,   161,     7,     7,     7,     7,   161,   161,   161,
     161,   161,     4,     4,     4,   161,     4,     4,     4,     4,
     161,   161,     4,     4,     3,     8,     6,     3,     6,     6,
     161,     3,   161,     6,     3,   161,     6,     3,     6,     3,
       3,     6,     4,     4,     4,     4,     4,     4,     3,   161,
       6,     4,     4,     4,     4,     4,   164,   164,     4,     4,
       4,     4,   162,     3,     6,     4,     4,   162,     3,     5,
     162,   162,   162,   161,     8,   162,     8,     8,     8,     4,
       4,     4,   162,     4,   480,   164,     4,     7,     4,     4,
       4,   162,   162,   556,   162,   162,   162,   162,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   561,   347,   383,
     162,   164,   161,   161,   164,   791,   162,   162,   794,   161,
     767,   797,   790,   785,   800,   797,   800,   791,   803,   805,
     794,   797,   808,   797,   805,   811,   800,   430,   791,   820,
     794,   805,   811,   797,   808,   791,   800,   800,   824,   377,
     813,   805,   793,   791,   830,   791,   830,   398,   794,   835,
     824,   797,   802,   952,   800,   794,   830,   791,   791,   805,
     796,   835,   808,   832,   791,   791,   800,   800,   422,   800,
     799,   835,   805,   800,   800,   808,   791,   791,   824,   805,
     797,   427,   808,   791,   830,   800,   800,   830,   810,   835,
     805,   805,   800,   808,   808,   808,   412,   830,   957,   830,
     806,   824,   401,   604,   582,   557,   448,   968,   836,   985,
     451,  1002,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   952,    -1,   952,    -1,
      -1,   957,    -1,    -1,    -1,    -1,   957,    -1,   952,    -1,
      -1,    -1,   968,   957,    -1,    -1,    -1,    -1,   952,   952,
      -1,    -1,    -1,   957,   968,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   968,    -1,   952,    -1,    -1,    -1,
      -1,   957,    -1,    -1,    -1,    -1,    -1,    -1,   952,   952,
      -1,   952,   968,    -1,   957,   952,   952,    -1,    -1,    -1,
      -1,   957,    -1,    -1,    -1,    -1,    -1,   952,   952,    -1,
      -1,    -1,   957,   957,   952
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,     0,     5,
       7,     9,   161,   162,   163,   164,   180,   181,   182,   187,
       7,   196,     7,   202,     7,   216,     7,   309,     7,   392,
       7,   408,     7,   344,     7,   350,     7,   374,     7,   285,
       7,   463,     7,   502,   188,   183,   197,   203,   217,   310,
     393,   409,   345,   351,   375,   286,   464,   503,   180,   189,
     190,   161,   185,   186,    10,   136,   145,   146,   147,   161,
     195,   198,   199,   200,   494,   496,   498,   500,    11,    20,
      22,    23,    24,    25,    26,    27,    28,    29,    50,    51,
      52,    53,    54,    58,    59,    69,    72,    73,    83,    84,
      89,    99,   102,   109,   110,   113,   195,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   227,   229,   235,   237,
     270,   279,   293,   303,   334,   342,   368,   398,   400,   402,
     413,   415,   417,   440,   452,   453,   461,    12,    13,    16,
      19,   195,   214,   215,   218,   220,   223,   226,   398,   400,
      55,    56,    57,    70,    74,    75,    76,    77,    78,    79,
      85,    88,    96,   195,   206,   207,   208,   211,   311,   312,
     313,   315,   317,   319,   321,   323,   325,   327,   329,   332,
     333,   368,   386,   398,   400,   402,   413,   415,   417,   437,
      71,   195,   325,   327,   368,   394,   395,   396,   398,   400,
      84,    90,    91,    92,    93,    94,    95,    97,   195,   368,
     398,   400,   410,   411,   412,   413,   415,   417,   419,   423,
     425,   427,   429,   431,   433,   435,   342,    30,    60,    62,
      63,    66,    67,    68,   195,   255,   352,   353,   354,   355,
     356,   357,   358,   360,   362,   364,   365,   367,   398,   400,
      61,    64,    65,   195,   255,   356,   362,   376,   377,   378,
     379,   380,   382,   383,   384,   385,   398,   400,   100,   101,
     195,   287,   288,   289,   291,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   134,
     135,   195,   398,   400,   465,   466,   467,   468,   470,   472,
     473,   475,   476,   477,   480,   482,   483,   484,   485,   488,
     490,   492,   137,   504,   505,   506,     6,     3,     4,     8,
       3,   201,   501,   495,   497,   499,     4,     3,     8,   213,
     230,     4,     4,   414,   416,   418,   228,   236,   238,     4,
       4,     4,     4,   304,   343,   369,   335,   399,   401,   271,
     441,   403,   280,   294,     4,   454,   462,     3,     8,   219,
     221,   224,     4,     3,     8,   316,   318,   320,   387,   314,
     322,   324,     4,     4,   330,   328,   326,   438,     3,     8,
     397,     3,     8,   436,   424,   426,   430,   428,   434,   432,
     420,     8,     3,     8,   359,   256,     4,   363,   361,   366,
       4,     8,     3,   381,     4,     4,     8,     3,   290,   292,
       3,     8,     4,   469,   471,     4,   474,     4,     4,   478,
     481,     4,     4,     4,   486,   489,   491,   493,     3,     8,
     507,     3,     8,   180,   180,   161,     4,     4,     4,     4,
       4,   199,     4,     4,   164,   164,     4,     4,     4,     4,
       4,     4,   162,   162,   162,   162,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   162,     4,     4,
     205,     4,     4,     4,   164,   215,     4,     4,     4,     4,
       4,     4,     4,   162,   164,     4,     4,     4,     4,   312,
       4,   395,     4,     4,     4,     4,     4,     4,     4,     4,
     412,     4,     4,   162,     4,     4,     4,   164,   354,     4,
     164,   164,   378,     4,     4,   288,   164,     4,     4,   162,
       4,   162,   162,     4,     4,   164,   164,   164,     4,     4,
       4,     4,   466,     4,   505,     4,     7,     7,   180,   180,
     180,     7,     7,   161,   161,   161,     7,     7,     5,     5,
       5,     5,     5,   182,   184,   161,     5,     5,     5,     5,
       7,     7,     7,     5,   191,    14,    15,   222,    17,    18,
     225,   161,   161,   161,     5,   161,   161,   161,    80,    81,
      82,   331,   191,   161,     7,   161,   191,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   180,   161,   161,   161,    15,   128,   479,   129,   130,
     131,   132,   133,   164,   487,   161,   161,   161,     5,   180,
     204,   504,   214,    21,   231,   232,   233,    30,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,   195,   243,   244,   245,   248,   250,   252,
     254,   255,   257,   258,   259,   260,   261,   262,   263,   264,
     266,   268,   269,   243,     7,   239,   240,   241,     7,   305,
     306,   307,     7,   346,   347,   348,     7,   370,   371,   372,
       7,   336,   337,   338,    90,    91,    92,    93,    95,   272,
     273,   274,   275,   276,   277,   278,     7,   442,   443,     7,
     404,   405,   406,     7,   281,   282,   283,   103,   104,   105,
     106,   107,   108,   295,   296,   297,   298,   299,   300,   301,
     302,   111,   112,   195,   398,   400,   455,   456,   457,   459,
     465,   192,     7,   388,   389,   390,    98,   419,   421,   439,
       7,   508,   509,     8,     8,     8,   234,     3,     8,   246,
     249,   251,   253,     4,     4,     4,     4,     4,   265,   267,
       4,     4,     4,     4,     4,     3,     8,     8,   242,     6,
       3,   308,     6,     3,   349,     6,     3,   373,     6,     3,
     339,     6,     3,     3,     6,   444,     3,     6,   407,     6,
       3,   284,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   458,   460,     3,     8,     8,   161,   193,   194,
     391,     6,     3,   422,     8,   510,     3,     6,     4,   232,
       4,     4,     4,     4,   162,   164,   162,   164,   162,     4,
       4,   162,   162,   162,   162,   164,   244,   243,   241,   311,
     307,   352,   348,   376,   372,   195,   206,   207,   208,   211,
     255,   303,   321,   325,   327,   329,   340,   341,   368,   398,
     400,   413,   415,   417,   437,   338,   273,    86,    87,   195,
     255,   342,   368,   398,   400,   413,   415,   417,   445,   446,
     447,   448,   449,   451,   443,   410,   406,   287,   283,   162,
     162,   162,   162,   162,   162,   296,     4,     4,   456,     6,
       3,   394,   390,     4,   138,   140,   141,   195,   255,   398,
     400,   511,   512,   513,   514,   516,   509,   161,    31,    32,
      33,    34,   247,   161,   161,   161,   161,   161,     8,     8,
       8,     8,     3,     8,   450,     4,     8,     3,     8,     8,
     161,   161,   161,     8,   191,   517,     4,   515,     3,     8,
     341,     4,   164,   447,     4,   162,     4,   512,   161,     5,
     161,     7,   518,   519,   520,     3,     6,   139,   142,   143,
     144,   521,   522,   523,   525,   526,   527,   519,   524,     4,
       4,     4,     3,     8,     4,   164,   162,   162,   522,   161
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   165,   167,   166,   168,   166,   169,   166,   170,   166,
     171,   166,   172,   166,   173,   166,   174,   166,   175,   166,
     176,   166,   177,   166,   178,   166,   179,   166,   180,   180,
     180,   180,   180,   180,   180,   181,   183,   182,   184,   185,
     185,   186,   186,   188,   187,   189,   189,   190,   190,   192,
     191,   193,   193,   194,   194,   195,   197,   196,   198,   198,
     199,   199,   199,   199,   199,   199,   201,   200,   203,   202,
     204,   204,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   206,   207,   208,   209,   210,   211,   213,   212,   214,
     214,   215,   215,   215,   215,   215,   215,   215,   217,   216,
     219,   218,   221,   220,   222,   222,   224,   223,   225,   225,
     226,   228,   227,   230,   229,   231,   231,   232,   234,   233,
     236,   235,   238,   237,   239,   239,   240,   240,   242,   241,
     243,   243,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     246,   245,   247,   247,   247,   247,   249,   248,   251,   250,
     253,   252,   254,   256,   255,   257,   258,   259,   260,   261,
     262,   263,   265,   264,   267,   266,   268,   269,   271,   270,
     272,   272,   273,   273,   273,   273,   273,   274,   275,   276,
     277,   278,   280,   279,   281,   281,   282,   282,   284,   283,
     286,   285,   287,   287,   287,   288,   288,   290,   289,   292,
     291,   294,   293,   295,   295,   296,   296,   296,   296,   296,
     296,   297,   298,   299,   300,   301,   302,   304,   303,   305,
     305,   306,   306,   308,   307,   310,   309,   311,   311,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   314,   313,   316,   315,   318,   317,
     320,   319,   322,   321,   324,   323,   326,   325,   328,   327,
     330,   329,   331,   331,   331,   332,   333,   335,   334,   336,
     336,   337,   337,   339,   338,   340,   340,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   343,   342,   345,   344,   346,
     346,   347,   347,   349,   348,   351,   350,   352,   352,   353,
     353,   354,   354,   354,   354,   354,   354,   354,   354,   354,
     354,   355,   356,   357,   359,   358,   361,   360,   363,   362,
     364,   366,   365,   367,   369,   368,   370,   370,   371,   371,
     373,   372,   375,   374,   376,   376,   377,   377,   378,   378,
     378,   378,   378,   378,   378,   378,   378,   379,   381,   380,
     382,   383,   384,   385,   387,   386,   388,   388,   389,   389,
     391,   390,   393,   392,   394,   394,   395,   395,   395,   395,
     395,   395,   395,   397,   396,   399,   398,   401,   400,   403,
     402,   404,   404,   405,   405,   407,   406,   409,   408,   410,
     410,   411,   411,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   414,   413,
     416,   415,   418,   417,   420,   419,   422,   421,   424,   423,
     426,   425,   428,   427,   430,   429,   432,   431,   434,   433,
     436,   435,   438,   437,   439,   439,   441,   440,   442,   442,
     444,   443,   445,   445,   446,   446,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   448,   450,   449,
     451,   452,   454,   453,   455,   455,   456,   456,   456,   456,
     456,   458,   457,   460,   459,   462,   461,   464,   463,   465,
     465,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     467,   469,   468,   471,   470,   472,   474,   473,   475,   476,
     478,   477,   479,   479,   481,   480,   482,   483,   484,   486,
     485,   487,   487,   487,   487,   487,   489,   488,   491,   490,
     493,   492,   495,   494,   497,   496,   499,   498,   501,   500,
     503,   502,   504,   504,   505,   507,   506,   508,   508,   510,
     509,   511,   511,   512,   512,   512,   512,   512,   512,   512,
     513,   515,   514,   517,   516,   518,   518,   520,   519,   521,
     521,   522,   522,   522,   522,   524,   523,   525,   526,   527
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     0,     6,     0,     6,     1,     3,     1,     0,     4,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     0,     4,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
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
       1,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"use-routing\"", "\"re-detect\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"next-server\"", "\"server-hostname\"", "\"boot-file-name\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"keyspace\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
  "re_detect", "lease_database", "$@25", "sanity_checks", "$@26",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@27",
  "hosts_database", "$@28", "hosts_databases", "$@29", "database_list",
  "not_empty_database_list", "database", "$@30", "database_map_params",
  "database_map_param", "database_type", "$@31", "db_type", "user", "$@32",
  "password", "$@33", "host", "$@34", "port", "name", "$@35", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@36", "keyspace",
  "$@37", "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@38",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@39", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@40",
  "sub_hooks_library", "$@41", "hooks_params", "hooks_param", "library",
  "$@42", "parameters", "$@43", "expired_leases_processing", "$@44",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@45",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@46",
  "sub_subnet4", "$@47", "subnet4_params", "subnet4_param", "subnet",
  "$@48", "subnet_4o6_interface", "$@49", "subnet_4o6_interface_id",
  "$@50", "subnet_4o6_subnet", "$@51", "interface", "$@52", "interface_id",
  "$@53", "client_class", "$@54", "require_client_classes", "$@55",
  "reservation_mode", "$@56", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@57", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@58",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@59", "sub_option_def_list", "$@60", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@61",
  "sub_option_def", "$@62", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@63",
  "option_def_record_types", "$@64", "space", "$@65", "option_def_space",
  "option_def_encapsulate", "$@66", "option_def_array", "option_data_list",
  "$@67", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@68", "sub_option_data", "$@69",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@70",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@71", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@72", "sub_pool4", "$@73",
  "pool_params", "pool_param", "pool_entry", "$@74", "user_context",
  "$@75", "comment", "$@76", "reservations", "$@77", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@78", "sub_reservation",
  "$@79", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@80", "server_hostname", "$@81",
  "boot_file_name", "$@82", "ip_address", "$@83", "ip_addresses", "$@84",
  "duid", "$@85", "hw_address", "$@86", "client_id_value", "$@87",
  "circuit_id_value", "$@88", "flex_id_value", "$@89", "hostname", "$@90",
  "reservation_client_classes", "$@91", "relay", "$@92", "relay_map",
  "client_classes", "$@93", "client_classes_list", "client_class_entry",
  "$@94", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@95",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@96",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@97", "control_socket_name", "$@98", "dhcp_ddns", "$@99",
  "sub_dhcp_ddns", "$@100", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@101", "server_ip", "$@102",
  "server_port", "sender_ip", "$@103", "sender_port", "max_queue_size",
  "ncr_protocol", "$@104", "ncr_protocol_value", "ncr_format", "$@105",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@106", "replace_client_name_value",
  "generated_prefix", "$@107", "hostname_char_set", "$@108",
  "hostname_char_replacement", "$@109", "dhcp6_json_object", "$@110",
  "dhcpddns_json_object", "$@111", "control_agent_json_object", "$@112",
  "logging_object", "$@113", "sub_logging", "$@114", "logging_params",
  "logging_param", "loggers", "$@115", "loggers_entries", "logger_entry",
  "$@116", "logger_params", "logger_param", "debuglevel", "severity",
  "$@117", "output_options_list", "$@118", "output_options_list_content",
  "output_entry", "$@119", "output_params_list", "output_params", "output",
  "$@120", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   249,   249,   249,   250,   250,   251,   251,   252,   252,
     253,   253,   254,   254,   255,   255,   256,   256,   257,   257,
     258,   258,   259,   259,   260,   260,   261,   261,   269,   270,
     271,   272,   273,   274,   275,   278,   283,   283,   294,   297,
     298,   301,   305,   312,   312,   319,   320,   323,   327,   334,
     334,   341,   342,   345,   349,   360,   370,   370,   386,   387,
     391,   392,   393,   394,   395,   396,   399,   399,   414,   414,
     423,   424,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   460,   465,   470,   475,   480,   485,   491,   491,   502,
     503,   506,   507,   508,   509,   510,   511,   512,   515,   515,
     524,   524,   534,   534,   541,   542,   545,   545,   552,   554,
     558,   564,   564,   576,   576,   586,   587,   589,   591,   591,
     609,   609,   621,   621,   631,   632,   635,   636,   639,   639,
     649,   650,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     673,   673,   680,   681,   682,   683,   686,   686,   694,   694,
     702,   702,   710,   715,   715,   723,   728,   733,   738,   743,
     748,   753,   758,   758,   766,   766,   774,   779,   784,   784,
     794,   795,   798,   799,   800,   801,   802,   805,   810,   815,
     820,   825,   830,   830,   840,   841,   844,   845,   848,   848,
     858,   858,   868,   869,   870,   873,   874,   877,   877,   885,
     885,   893,   893,   904,   905,   908,   909,   910,   911,   912,
     913,   916,   921,   926,   931,   936,   941,   949,   949,   962,
     963,   966,   967,   974,   974,  1000,  1000,  1011,  1012,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,
    1037,  1038,  1039,  1040,  1043,  1043,  1051,  1051,  1059,  1059,
    1067,  1067,  1075,  1075,  1083,  1083,  1091,  1091,  1099,  1099,
    1109,  1109,  1116,  1117,  1118,  1121,  1126,  1133,  1133,  1144,
    1145,  1149,  1150,  1153,  1153,  1161,  1162,  1165,  1166,  1167,
    1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,
    1178,  1179,  1180,  1181,  1182,  1189,  1189,  1202,  1202,  1211,
    1212,  1215,  1216,  1221,  1221,  1236,  1236,  1250,  1251,  1254,
    1255,  1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,  1266,
    1267,  1270,  1272,  1277,  1279,  1279,  1287,  1287,  1295,  1295,
    1303,  1305,  1305,  1313,  1322,  1322,  1334,  1335,  1340,  1341,
    1346,  1346,  1358,  1358,  1370,  1371,  1376,  1377,  1382,  1383,
    1384,  1385,  1386,  1387,  1388,  1389,  1390,  1393,  1395,  1395,
    1403,  1405,  1407,  1412,  1420,  1420,  1432,  1433,  1436,  1437,
    1440,  1440,  1450,  1450,  1460,  1461,  1464,  1465,  1466,  1467,
    1468,  1469,  1470,  1473,  1473,  1481,  1481,  1506,  1506,  1536,
    1536,  1546,  1547,  1550,  1551,  1554,  1554,  1563,  1563,  1572,
    1573,  1576,  1577,  1581,  1582,  1583,  1584,  1585,  1586,  1587,
    1588,  1589,  1590,  1591,  1592,  1593,  1594,  1595,  1598,  1598,
    1606,  1606,  1614,  1614,  1622,  1622,  1630,  1630,  1640,  1640,
    1648,  1648,  1656,  1656,  1664,  1664,  1672,  1672,  1680,  1680,
    1688,  1688,  1701,  1701,  1711,  1712,  1718,  1718,  1728,  1729,
    1732,  1732,  1742,  1743,  1746,  1747,  1750,  1751,  1752,  1753,
    1754,  1755,  1756,  1757,  1758,  1759,  1760,  1763,  1765,  1765,
    1773,  1782,  1789,  1789,  1799,  1800,  1803,  1804,  1805,  1806,
    1807,  1810,  1810,  1818,  1818,  1828,  1828,  1840,  1840,  1850,
    1851,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,  1862,
    1863,  1864,  1865,  1866,  1867,  1868,  1869,  1870,  1871,  1872,
    1875,  1880,  1880,  1888,  1888,  1896,  1901,  1901,  1909,  1914,
    1919,  1919,  1927,  1928,  1931,  1931,  1939,  1944,  1949,  1954,
    1954,  1962,  1965,  1968,  1971,  1974,  1980,  1980,  1988,  1988,
    1996,  1996,  2007,  2007,  2014,  2014,  2021,  2021,  2033,  2033,
    2043,  2043,  2054,  2055,  2059,  2063,  2063,  2075,  2076,  2080,
    2080,  2088,  2089,  2092,  2093,  2094,  2095,  2096,  2097,  2098,
    2101,  2106,  2106,  2114,  2114,  2124,  2125,  2128,  2128,  2136,
    2137,  2140,  2141,  2142,  2143,  2146,  2146,  2154,  2159,  2164
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
#line 4758 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2169 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
