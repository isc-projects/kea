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

  case 100:
#line 459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 139:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1481 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1743 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 254:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1050 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2110 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2254 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1411 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 426:
#line 1505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 428:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3110 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1961 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1964 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1970 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3210 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3219 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2062 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2118 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2127 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3457 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3501 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2163 "dhcp4_parser.yy" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -787;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     413,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,    32,    22,    33,    45,    64,   107,
     109,   120,   127,   155,   159,   170,   183,   192,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,    22,  -127,    27,    95,    57,   187,
     160,   358,   145,    28,    79,   -58,   425,    80,  -787,   222,
     252,   267,   279,   294,  -787,  -787,  -787,  -787,  -787,   295,
    -787,    74,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
     298,   306,  -787,  -787,  -787,  -787,  -787,  -787,   307,   308,
     309,   310,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,   314,  -787,  -787,  -787,    81,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,   316,  -787,
      99,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,   318,   320,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,   101,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,   102,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,   317,   323,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,   322,  -787,  -787,   324,  -787,
    -787,  -787,   329,  -787,  -787,   327,   333,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
     334,   335,  -787,  -787,  -787,  -787,   336,   338,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
     105,  -787,  -787,  -787,   343,  -787,  -787,   345,  -787,   346,
     348,  -787,  -787,   352,   355,   357,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,   125,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,   147,  -787,  -787,  -787,    22,    22,  -787,   176,
     359,   361,   364,   367,   369,  -787,    27,  -787,   371,   372,
     178,   214,   376,   381,   383,   385,   386,   388,   200,   234,
     237,   239,   391,   398,   400,   402,   405,   406,   408,   409,
     411,   412,   256,   415,   416,    95,  -787,   418,   419,   428,
     265,    57,  -787,   429,   430,   431,   432,   433,   434,   436,
     284,   277,   439,   440,   441,   443,   452,   187,  -787,   453,
     160,  -787,   454,   470,   471,   472,   473,   474,   475,   476,
    -787,   358,  -787,   477,   478,   321,   481,   482,   483,   326,
    -787,    28,   484,   328,   331,  -787,    79,   487,   489,   -14,
    -787,   332,   495,   496,   339,   499,   342,   347,   501,   503,
     344,   351,   353,   506,   507,   508,   512,   425,  -787,   514,
      80,  -787,  -787,  -787,   516,   515,   517,    22,    22,    22,
    -787,   520,   521,  -787,  -787,   360,   368,   370,   523,   525,
     528,  -787,  -787,  -787,  -787,   529,   530,   531,   533,   546,
     393,   550,   553,   569,   568,  -787,   570,   571,  -787,   574,
     201,   283,  -787,  -787,   420,   421,   422,   575,   423,   426,
     427,  -787,  -787,   -20,   574,   435,   584,   583,  -787,   437,
    -787,   574,   438,   442,   444,   445,   446,   447,   448,  -787,
     449,   450,  -787,   451,   455,   456,  -787,  -787,   457,  -787,
    -787,  -787,   458,    22,  -787,  -787,   459,   460,  -787,   461,
    -787,  -787,    29,   462,  -787,  -787,  -787,     5,   463,   464,
     465,  -787,   587,  -787,    22,    95,    80,  -787,  -787,  -787,
      57,   555,  -787,  -787,  -787,   424,   424,   586,   588,   590,
     593,   594,  -787,  -787,  -787,   -36,   595,   597,   118,    59,
     425,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,   606,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,   607,   210,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,   608,  -787,   172,
     188,   190,  -787,   198,  -787,  -787,  -787,  -787,  -787,  -787,
     619,   623,   624,   625,   626,  -787,  -787,   627,   628,   629,
     630,   631,  -787,   199,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,   206,  -787,   632,   591,  -787,  -787,   633,   634,
    -787,  -787,   635,   637,  -787,  -787,   636,   640,  -787,  -787,
     638,   642,  -787,  -787,  -787,  -787,  -787,  -787,    72,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,   153,  -787,  -787,   641,
     643,  -787,   644,   645,   646,   647,   648,   649,   226,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,   227,  -787,  -787,  -787,   233,   493,  -787,   650,   652,
    -787,  -787,   651,   655,  -787,  -787,  -787,  -787,   653,  -787,
     189,  -787,  -787,  -787,  -787,   656,   555,  -787,   658,   659,
     660,   661,   497,   502,   505,   504,   509,   665,   666,   510,
     511,   513,   518,   519,   424,  -787,  -787,   424,  -787,   586,
     187,  -787,   588,    28,  -787,   590,    79,  -787,   593,   244,
    -787,   594,   -36,  -787,    39,   595,  -787,   -58,  -787,   597,
     522,   524,   526,   527,   532,   534,   118,  -787,   670,   672,
      59,  -787,  -787,  -787,   671,   675,   160,  -787,   606,   358,
    -787,   607,   677,  -787,    20,   608,  -787,   536,  -787,   259,
     537,   538,   539,  -787,  -787,  -787,  -787,  -787,   540,   541,
    -787,  -787,  -787,  -787,  -787,  -787,   246,  -787,   250,  -787,
     674,  -787,   679,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,   270,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,   681,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,   682,   676,  -787,
    -787,  -787,  -787,  -787,   271,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,   542,   543,  -787,  -787,   544,   274,  -787,
     683,  -787,   574,  -787,   688,  -787,  -787,  -787,  -787,  -787,
     278,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,   244,  -787,   689,   545,  -787,    39,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,   691,   548,   702,    20,  -787,  -787,
     547,  -787,  -787,   706,  -787,   551,  -787,  -787,   700,  -787,
    -787,   282,  -787,   108,   700,  -787,  -787,   709,   710,   711,
     281,  -787,  -787,  -787,  -787,  -787,  -787,   712,   554,   557,
     558,   108,  -787,   556,  -787,  -787,  -787,  -787,  -787
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   117,     9,   254,    11,   411,    13,
     436,    15,   336,    17,   344,    19,   381,    21,   219,    23,
     526,    25,   589,    27,    45,    39,     0,     0,     0,     0,
       0,   438,     0,   346,   383,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   587,   581,   583,   585,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   106,   132,
       0,     0,   457,   459,   461,   130,   139,   141,     0,     0,
       0,     0,   246,   334,   373,   306,   424,   426,   197,   485,
     211,   230,     0,   511,   524,    99,     0,    70,    72,    73,
      74,    75,    91,    92,    78,    79,    98,    80,    81,    82,
      86,    87,    76,    77,    84,    85,    96,    97,    93,    94,
      95,    83,    88,    89,    90,   119,   121,   125,     0,   116,
       0,   108,   110,   111,   112,   113,   114,   115,   285,   287,
     289,   403,   283,   291,   293,     0,     0,   299,   297,   295,
     428,   481,   282,   258,   259,   260,   273,     0,   256,   263,
     277,   278,   279,   264,   265,   268,   269,   271,   266,   267,
     261,   262,   280,   281,   270,   274,   275,   276,   272,   422,
     421,   417,   418,   416,     0,   413,   415,   419,   420,   479,
     467,   469,   473,   471,   477,   475,   463,   456,   450,   454,
     455,     0,   439,   440,   451,   452,   453,   447,   442,   448,
     444,   445,   446,   449,   443,     0,   363,   182,     0,   367,
     365,   370,     0,   359,   360,     0,   347,   348,   350,   362,
     351,   352,   353,   369,   354,   355,   356,   357,   358,   397,
       0,     0,   395,   396,   399,   400,     0,   384,   385,   387,
     388,   389,   390,   391,   392,   393,   394,   226,   228,   223,
       0,   221,   224,   225,     0,   550,   552,     0,   555,     0,
       0,   559,   563,     0,     0,     0,   568,   575,   577,   579,
     548,   546,   547,     0,   528,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   594,     0,   591,   593,    44,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    55,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,   118,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   255,     0,
       0,   412,     0,     0,     0,     0,     0,     0,     0,     0,
     437,     0,   337,     0,     0,     0,     0,     0,     0,     0,
     345,     0,     0,     0,     0,   382,     0,     0,     0,     0,
     220,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   527,     0,
       0,   590,    48,    41,     0,     0,     0,     0,     0,     0,
      59,     0,     0,   104,   105,     0,     0,     0,     0,     0,
       0,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   510,     0,     0,    71,     0,
       0,     0,   129,   109,     0,     0,     0,     0,     0,     0,
       0,   304,   305,     0,     0,     0,     0,     0,   257,     0,
     414,     0,     0,     0,     0,     0,     0,     0,     0,   441,
       0,     0,   361,     0,     0,     0,   372,   349,     0,   401,
     402,   386,     0,     0,   222,   549,     0,     0,   554,     0,
     557,   558,     0,     0,   565,   566,   567,     0,     0,     0,
       0,   529,     0,   592,     0,     0,     0,   582,   584,   586,
       0,     0,   458,   460,   462,     0,     0,   143,   248,   338,
     375,   308,    38,   425,   427,     0,     0,   213,     0,     0,
       0,    49,   120,   123,   124,   122,   127,   128,   126,   286,
     288,   290,   405,   284,   292,   294,   301,   302,   303,   300,
     298,   296,   430,     0,   423,   480,   468,   470,   474,   472,
     478,   476,   464,   364,   183,   368,   366,   371,   398,   227,
     229,   551,   553,   556,   561,   562,   560,   564,   570,   571,
     572,   573,   574,   569,   576,   578,   580,     0,    42,     0,
       0,     0,   137,     0,   134,   136,   169,   175,   177,   179,
       0,     0,     0,     0,     0,   191,   193,     0,     0,     0,
       0,     0,   168,     0,   149,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   164,   165,   166,   161,   167,
     162,   163,     0,   147,     0,   144,   145,   252,     0,   249,
     250,   342,     0,   339,   340,   379,     0,   376,   377,   312,
       0,   309,   310,   206,   207,   208,   209,   210,     0,   199,
     201,   202,   203,   204,   205,   489,     0,   487,   217,     0,
     214,   215,     0,     0,     0,     0,     0,     0,     0,   232,
     234,   235,   236,   237,   238,   239,   520,   522,   519,   517,
     518,     0,   513,   515,   516,     0,    51,   409,     0,   406,
     407,   434,     0,   431,   432,   465,   483,   484,     0,   598,
       0,   596,    67,   588,   107,     0,     0,   133,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   140,     0,   142,     0,
       0,   247,     0,   346,   335,     0,   383,   374,     0,     0,
     307,     0,     0,   198,   491,     0,   486,     0,   212,     0,
       0,     0,     0,     0,     0,     0,     0,   231,     0,     0,
       0,   512,   525,    53,     0,    52,     0,   404,     0,   438,
     429,     0,     0,   482,     0,     0,   595,     0,   135,     0,
       0,     0,     0,   181,   184,   185,   186,   187,     0,     0,
     195,   196,   188,   189,   190,   150,     0,   146,     0,   251,
       0,   341,     0,   378,   333,   330,   319,   320,   322,   316,
     317,   318,   328,   329,   327,     0,   314,   321,   331,   332,
     323,   324,   325,   326,   311,   200,   507,     0,   505,   506,
     498,   499,   503,   504,   500,   501,   502,     0,   492,   493,
     495,   496,   497,   488,     0,   216,   240,   241,   242,   243,
     244,   245,   233,     0,     0,   514,    50,     0,     0,   408,
       0,   433,     0,   612,     0,   610,   608,   602,   606,   607,
       0,   600,   604,   605,   603,   597,   138,   171,   172,   173,
     174,   170,   176,   178,   180,   192,   194,   148,   253,   343,
     380,     0,   313,     0,     0,   490,     0,   218,   521,   523,
      54,   410,   435,   466,     0,     0,     0,     0,   599,   315,
       0,   509,   494,     0,   609,     0,   601,   508,     0,   611,
     616,     0,   614,     0,     0,   613,   624,     0,     0,     0,
       0,   618,   620,   621,   622,   623,   615,     0,     0,     0,
       0,     0,   617,     0,   626,   627,   628,   619,   625
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,   -31,  -787,   157,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -483,  -787,  -787,  -787,
     -66,  -787,  -787,  -787,   375,  -787,  -787,  -787,  -787,   167,
     350,   -46,   -44,   -43,  -787,  -787,   -28,  -787,  -787,   163,
     354,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,   -40,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,   -60,  -787,  -560,   -53,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
     -35,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,   -74,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,   -77,  -787,
    -787,  -787,   -70,   319,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,   -67,  -787,  -787,  -787,  -787,  -787,  -787,  -786,  -787,
    -787,  -787,   -41,  -787,  -787,  -787,   -38,   362,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -775,  -787,  -787,  -787,
     -34,  -787,   -21,  -787,  -769,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,   -27,  -787,  -787,  -194,   -61,  -787,  -787,
    -787,  -787,  -787,   -18,  -787,  -787,  -787,   -11,  -787,   363,
    -787,   -62,  -787,  -787,  -787,  -787,  -787,   -56,  -787,  -787,
    -787,  -787,  -787,    -3,  -787,  -787,  -787,   -19,  -787,  -787,
    -787,   -13,  -787,   365,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,   -42,  -787,  -787,  -787,   -37,
     390,  -787,  -787,   -54,  -787,   -23,  -787,  -787,  -787,  -787,
    -787,   -33,  -787,  -787,  -787,   -17,  -787,   374,     3,  -787,
      10,  -787,    14,  -787,   185,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -764,  -787,  -787,  -787,  -787,  -787,   -10,  -787,
    -787,  -787,  -162,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,   -12,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
     230,   373,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,
    -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,  -787,   260,
     377,  -787,  -787,  -787,   -16,  -787,  -787,  -152,  -787,  -787,
    -787,  -787,  -787,  -787,  -167,  -787,  -787,  -180,  -787,  -787,
    -787,  -787,  -787
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   573,
      82,    83,    39,    64,    79,    80,   582,   746,   824,   825,
     662,    41,    66,    91,    92,    93,   340,    43,    67,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   348,   160,
     161,    45,    68,   162,   377,   163,   378,   585,   164,   379,
     588,   165,   135,   355,   136,   349,   643,   644,   645,   765,
     137,   356,   138,   357,   684,   685,   686,   787,   663,   664,
     665,   768,   941,   666,   769,   667,   770,   668,   771,   669,
     670,   414,   671,   672,   673,   674,   675,   676,   677,   678,
     777,   679,   778,   680,   681,   139,   368,   708,   709,   710,
     711,   712,   713,   714,   140,   370,   719,   720,   721,   807,
      59,    75,   290,   291,   292,   427,   293,   428,   141,   371,
     728,   729,   730,   731,   732,   733,   734,   735,   142,   362,
     688,   689,   690,   790,    47,    69,   187,   188,   189,   387,
     190,   383,   191,   384,   192,   385,   193,   388,   194,   389,
     195,   394,   196,   393,   197,   392,   599,   198,   199,   143,
     365,   700,   701,   702,   799,   875,   876,   144,   363,    53,
      72,   692,   693,   694,   793,    55,    73,   255,   256,   257,
     258,   259,   260,   261,   413,   262,   417,   263,   416,   264,
     265,   418,   266,   145,   364,   696,   697,   698,   796,    57,
      74,   276,   277,   278,   279,   280,   422,   281,   282,   283,
     284,   201,   386,   748,   749,   750,   826,    49,    70,   214,
     215,   216,   399,   146,   366,   147,   367,   204,   395,   752,
     753,   754,   829,    51,    71,   231,   232,   233,   148,   352,
     149,   353,   150,   354,   237,   409,   757,   832,   238,   403,
     239,   404,   240,   406,   241,   405,   242,   408,   243,   407,
     244,   402,   208,   396,   758,   151,   369,   716,   717,   804,
     897,   898,   899,   900,   901,   953,   902,   152,   153,   373,
     741,   742,   743,   818,   744,   819,   154,   374,    61,    76,
     313,   314,   315,   316,   432,   317,   433,   318,   319,   435,
     320,   321,   322,   438,   626,   323,   439,   324,   325,   326,
     327,   443,   633,   328,   444,   329,   445,   330,   446,    94,
     342,    95,   343,    96,   344,    97,   341,    63,    77,   332,
     333,   334,   449,   760,   761,   834,   930,   931,   932,   933,
     966,   934,   964,   981,   982,   983,   990,   991,   992,   997,
     993,   994,   995
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   125,   159,   182,   210,   227,   682,   253,   272,   289,
     310,   245,   274,   870,   166,   202,   217,   229,   275,   267,
     285,   600,   311,   183,   871,   184,   185,    29,   605,    30,
     874,    31,    28,    78,    81,   883,   211,    84,   254,   273,
      40,   186,   287,   288,   624,   167,   203,   218,   230,   212,
     268,   286,    42,   312,   703,   704,   705,   706,   246,   707,
     596,   597,   598,   102,   103,   104,   200,   213,   228,   155,
     156,    44,   205,   157,   234,   802,   158,   346,   803,   206,
     247,   235,   347,   207,   375,   236,   287,   288,   247,   376,
     248,   249,   116,   117,   250,   251,   252,   113,   114,   247,
     116,   117,   381,    89,   397,   400,    98,   382,   429,   398,
     401,   116,   117,   430,    46,    99,    48,   100,   101,   102,
     103,   104,   105,   106,   107,   886,   887,    50,   447,   116,
     117,   116,   117,   448,    52,   628,   629,   630,   631,   247,
     269,   248,   249,   270,   271,   108,   109,   110,   111,   112,
     450,   116,   117,   113,   114,   451,   805,   625,   923,   806,
     924,   925,    54,    85,   115,   870,    56,   116,   117,   632,
     736,   737,    86,    87,    88,   375,   871,    58,   118,   119,
     762,    89,   874,    32,    33,    34,    35,   883,    89,    89,
      60,   450,   835,   381,   120,   836,   763,   121,   764,    62,
      89,   766,   784,   113,   122,   123,   767,   785,   124,   784,
     101,   102,   103,   104,   786,   583,   584,   331,    89,   114,
      89,   722,   723,   724,   725,   726,   727,   856,   335,   816,
     820,   209,   116,   117,   817,   821,   447,   108,   109,   110,
      89,   822,   168,   169,   170,   178,   114,   986,   179,   784,
     987,   988,   989,   397,   947,   336,    89,   171,   948,   116,
     117,   172,   173,   174,   175,   176,   177,   101,   102,   103,
     104,   337,   178,   951,   429,   179,   180,   400,   952,   957,
      90,   967,   961,   181,  1001,   984,   968,   338,   985,  1002,
     937,   938,   939,   940,   108,   109,   110,   339,   112,   345,
     586,   587,   350,   114,   247,   452,   453,   226,   755,   125,
     351,   358,   359,   360,   361,   159,   116,   117,   372,   173,
     380,    89,   390,   177,   391,   410,   411,   166,   415,   178,
     412,   182,   179,   419,   210,   420,   421,   454,   423,   424,
     181,   426,   463,   202,   425,   227,   217,   431,    89,   434,
     436,   183,   437,   184,   185,   253,   440,   229,   167,   441,
     272,   442,   471,   455,   274,   456,   211,   267,   457,   186,
     275,   458,   285,   459,   203,   461,   462,   218,   464,   212,
     465,   310,   102,   103,   104,   466,   254,   467,   230,   468,
     469,   273,   470,   311,   200,   475,   472,   213,   268,   473,
     205,   474,   476,   286,   477,    89,   478,   206,   228,   479,
     480,   207,   481,   482,   234,   483,   484,   114,   485,   486,
     487,   235,   489,   490,   312,   236,   557,   558,   559,   492,
     116,   117,   491,   494,   495,   496,   497,   498,   499,   963,
     500,   502,   219,   503,   504,   505,   501,   506,   220,   221,
     222,   223,   224,   225,   646,   226,   507,   509,   511,   647,
     648,   649,   650,   651,   652,   653,   654,   655,   656,   657,
     658,   659,   660,   661,   512,   513,   514,   515,   516,   517,
     518,   520,   521,   522,   247,   523,   524,   525,   528,   125,
     526,   532,   529,   533,   159,   530,   535,   116,   117,   536,
     537,   538,   620,   539,   540,   542,   166,   543,   544,   541,
     547,   548,   549,   738,   310,   545,   550,   546,   552,    89,
     554,   562,   555,   638,   556,   739,   311,   560,   561,   563,
     565,   564,   566,   567,   568,   569,   570,   167,   571,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,    30,   574,   575,   740,   312,   576,   308,
     309,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   577,   578,   642,   579,   580,   581,
     592,   589,   590,   591,   593,    89,    89,   594,   595,   602,
     603,   627,   637,   683,   789,   687,   601,   691,   604,   606,
     695,   699,   715,   607,   718,   608,   609,   610,   611,   612,
     613,   614,   615,   747,   751,   759,   616,   617,   618,   619,
     621,   622,   623,   772,   634,   635,   636,   773,   774,   775,
     776,   779,   780,   781,   782,   783,   572,   792,   788,   791,
     795,   794,   797,   798,   800,   801,   809,   808,   810,   811,
     812,   813,   814,   815,   823,   828,   827,   830,   831,   843,
     837,   833,   839,   840,   841,   842,   844,   845,   846,   848,
     849,   847,   850,   851,   913,   852,   914,   916,   917,   956,
     853,   922,   949,   854,   906,   954,   907,   950,   908,   909,
     955,   962,   965,   970,   910,   973,   911,   936,   942,   943,
     944,   945,   946,   958,   959,   960,   975,   980,   977,   971,
     974,   978,   979,   998,   999,  1000,  1003,  1008,  1004,  1005,
    1006,   460,   639,   641,   182,   488,   838,   253,   885,   857,
     272,   855,   905,   864,   274,   493,   202,   904,   888,   267,
     275,   289,   285,   890,   183,   878,   184,   185,   534,   912,
     892,   859,   858,   865,   738,   866,   867,   969,   254,   508,
     210,   273,   186,   227,   869,   872,   739,   203,   926,   889,
     268,   868,   217,   286,   884,   229,   879,   861,   873,   863,
     928,   893,   860,   862,   527,   519,   919,   200,   756,   918,
     510,   531,   211,   205,   972,   903,   877,   740,   921,   927,
     206,   891,   880,   218,   207,   212,   230,   894,   915,   881,
     745,   929,   920,   882,   895,   976,   640,   996,   896,   935,
     551,  1007,     0,   213,     0,     0,   228,   553,     0,     0,
       0,     0,   234,     0,     0,     0,     0,     0,     0,   235,
       0,     0,     0,   236,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   864,     0,     0,     0,     0,
     888,     0,     0,     0,     0,   890,     0,   878,     0,     0,
       0,   926,   892,     0,     0,   865,     0,   866,   867,     0,
       0,     0,     0,   928,     0,     0,   869,   872,     0,     0,
       0,   889,     0,   868,     0,     0,     0,     0,   879,     0,
     873,     0,   927,   893,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   929,     0,     0,     0,   877,     0,
       0,     0,     0,   891,   880,     0,     0,     0,     0,   894,
       0,   881,     0,     0,     0,   882,   895,     0,     0,     0,
     896
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,   566,    73,    74,    75,
      76,    72,    74,   799,    68,    69,    70,    71,    74,    73,
      74,   504,    76,    69,   799,    69,    69,     5,   511,     7,
     799,     9,     0,    64,   161,   799,    70,    10,    73,    74,
       7,    69,   100,   101,    15,    68,    69,    70,    71,    70,
      73,    74,     7,    76,    90,    91,    92,    93,    30,    95,
      80,    81,    82,    24,    25,    26,    69,    70,    71,    12,
      13,     7,    69,    16,    71,     3,    19,     3,     6,    69,
      60,    71,     8,    69,     3,    71,   100,   101,    60,     8,
      62,    63,    72,    73,    66,    67,    68,    58,    59,    60,
      72,    73,     3,   161,     3,     3,    11,     8,     3,     8,
       8,    72,    73,     8,     7,    20,     7,    22,    23,    24,
      25,    26,    27,    28,    29,    86,    87,     7,     3,    72,
      73,    72,    73,     8,     7,   130,   131,   132,   133,    60,
      61,    62,    63,    64,    65,    50,    51,    52,    53,    54,
       3,    72,    73,    58,    59,     8,     3,   128,   138,     6,
     140,   141,     7,   136,    69,   951,     7,    72,    73,   164,
     111,   112,   145,   146,   147,     3,   951,     7,    83,    84,
       8,   161,   951,   161,   162,   163,   164,   951,   161,   161,
       7,     3,     3,     3,    99,     6,     8,   102,     8,     7,
     161,     3,     3,    58,   109,   110,     8,     8,   113,     3,
      23,    24,    25,    26,     8,    14,    15,   137,   161,    59,
     161,   103,   104,   105,   106,   107,   108,   787,     6,     3,
       3,    71,    72,    73,     8,     8,     3,    50,    51,    52,
     161,     8,    55,    56,    57,    85,    59,   139,    88,     3,
     142,   143,   144,     3,     8,     3,   161,    70,     8,    72,
      73,    74,    75,    76,    77,    78,    79,    23,    24,    25,
      26,     4,    85,     3,     3,    88,    89,     3,     8,     8,
     346,     3,     8,    96,     3,     3,     8,     8,     6,     8,
      31,    32,    33,    34,    50,    51,    52,     3,    54,     4,
      17,    18,     4,    59,    60,   336,   337,    97,    98,   375,
       4,     4,     4,     4,     4,   381,    72,    73,     4,    75,
       4,   161,     4,    79,     4,     8,     3,   381,     4,    85,
       8,   397,    88,     4,   400,     8,     3,   161,     4,     4,
      96,     3,   164,   397,     8,   411,   400,     4,   161,     4,
       4,   397,     4,   397,   397,   421,     4,   411,   381,     4,
     426,     4,   162,     4,   426,     4,   400,   421,     4,   397,
     426,     4,   426,     4,   397,     4,     4,   400,   164,   400,
       4,   447,    24,    25,    26,     4,   421,     4,   411,     4,
       4,   426,     4,   447,   397,     4,   162,   400,   421,   162,
     397,   162,     4,   426,     4,   161,     4,   397,   411,     4,
       4,   397,     4,     4,   411,     4,     4,    59,   162,     4,
       4,   411,     4,     4,   447,   411,   457,   458,   459,   164,
      72,    73,     4,     4,     4,     4,     4,     4,     4,   922,
       4,   164,    84,     4,     4,     4,   162,     4,    90,    91,
      92,    93,    94,    95,    30,    97,     4,     4,     4,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   162,    60,     4,     4,     4,     4,   555,
     164,     4,   164,     4,   560,   164,   164,    72,    73,     4,
       4,   162,   533,     4,   162,     4,   560,     4,   164,   162,
       4,     4,     4,   579,   580,   164,     4,   164,     4,   161,
       4,   161,     7,   554,     7,   579,   580,     7,     7,   161,
       7,   161,     7,     5,     5,     5,     5,   560,     5,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,     7,   161,     5,   579,   580,     5,   134,
     135,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,     5,     7,    21,     7,     7,     5,
       5,   161,   161,   161,   161,   161,   161,   161,   161,     5,
       7,   129,     5,     7,     3,     7,   161,     7,   161,   161,
       7,     7,     7,   161,     7,   161,   161,   161,   161,   161,
     161,   161,   161,     7,     7,     7,   161,   161,   161,   161,
     161,   161,   161,     4,   161,   161,   161,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   479,     3,     6,     6,
       3,     6,     6,     3,     6,     3,     3,     6,     4,     4,
       4,     4,     4,     4,   161,     3,     6,     6,     3,   162,
       4,     8,     4,     4,     4,     4,   164,   162,   164,     4,
       4,   162,   162,   162,     4,   162,     4,     6,     3,     3,
     162,     4,     8,   164,   162,     4,   162,     8,   162,   162,
       8,     8,     4,     4,   162,     4,   162,   161,   161,   161,
     161,   161,   161,   161,   161,   161,     4,     7,   161,   164,
     162,     5,   161,     4,     4,     4,     4,   161,   164,   162,
     162,   346,   555,   560,   790,   375,   766,   793,   802,   789,
     796,   784,   809,   799,   796,   381,   790,   807,   804,   793,
     796,   807,   796,   804,   790,   799,   790,   790,   429,   816,
     804,   792,   790,   799,   820,   799,   799,   951,   793,   397,
     826,   796,   790,   829,   799,   799,   820,   790,   834,   804,
     793,   799,   826,   796,   801,   829,   799,   795,   799,   798,
     834,   804,   793,   796,   421,   411,   828,   790,   603,   826,
     400,   426,   826,   790,   956,   805,   799,   820,   831,   834,
     790,   804,   799,   826,   790,   826,   829,   804,   820,   799,
     580,   834,   829,   799,   804,   967,   556,   984,   804,   835,
     447,  1001,    -1,   826,    -1,    -1,   829,   450,    -1,    -1,
      -1,    -1,   829,    -1,    -1,    -1,    -1,    -1,    -1,   829,
      -1,    -1,    -1,   829,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   951,    -1,    -1,    -1,    -1,
     956,    -1,    -1,    -1,    -1,   956,    -1,   951,    -1,    -1,
      -1,   967,   956,    -1,    -1,   951,    -1,   951,   951,    -1,
      -1,    -1,    -1,   967,    -1,    -1,   951,   951,    -1,    -1,
      -1,   956,    -1,   951,    -1,    -1,    -1,    -1,   951,    -1,
     951,    -1,   967,   956,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   967,    -1,    -1,    -1,   951,    -1,
      -1,    -1,    -1,   956,   951,    -1,    -1,    -1,    -1,   956,
      -1,   951,    -1,    -1,    -1,   951,   956,    -1,    -1,    -1,
     956
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
      99,   102,   109,   110,   113,   195,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   227,   229,   235,   237,   270,
     279,   293,   303,   334,   342,   368,   398,   400,   413,   415,
     417,   440,   452,   453,   461,    12,    13,    16,    19,   195,
     214,   215,   218,   220,   223,   226,   398,   400,    55,    56,
      57,    70,    74,    75,    76,    77,    78,    79,    85,    88,
      89,    96,   195,   206,   207,   208,   211,   311,   312,   313,
     315,   317,   319,   321,   323,   325,   327,   329,   332,   333,
     368,   386,   398,   400,   402,   413,   415,   417,   437,    71,
     195,   325,   327,   368,   394,   395,   396,   398,   400,    84,
      90,    91,    92,    93,    94,    95,    97,   195,   368,   398,
     400,   410,   411,   412,   413,   415,   417,   419,   423,   425,
     427,   429,   431,   433,   435,   342,    30,    60,    62,    63,
      66,    67,    68,   195,   255,   352,   353,   354,   355,   356,
     357,   358,   360,   362,   364,   365,   367,   398,   400,    61,
      64,    65,   195,   255,   356,   362,   376,   377,   378,   379,
     380,   382,   383,   384,   385,   398,   400,   100,   101,   195,
     287,   288,   289,   291,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   134,   135,
     195,   398,   400,   465,   466,   467,   468,   470,   472,   473,
     475,   476,   477,   480,   482,   483,   484,   485,   488,   490,
     492,   137,   504,   505,   506,     6,     3,     4,     8,     3,
     201,   501,   495,   497,   499,     4,     3,     8,   213,   230,
       4,     4,   414,   416,   418,   228,   236,   238,     4,     4,
       4,     4,   304,   343,   369,   335,   399,   401,   271,   441,
     280,   294,     4,   454,   462,     3,     8,   219,   221,   224,
       4,     3,     8,   316,   318,   320,   387,   314,   322,   324,
       4,     4,   330,   328,   326,   403,   438,     3,     8,   397,
       3,     8,   436,   424,   426,   430,   428,   434,   432,   420,
       8,     3,     8,   359,   256,     4,   363,   361,   366,     4,
       8,     3,   381,     4,     4,     8,     3,   290,   292,     3,
       8,     4,   469,   471,     4,   474,     4,     4,   478,   481,
       4,     4,     4,   486,   489,   491,   493,     3,     8,   507,
       3,     8,   180,   180,   161,     4,     4,     4,     4,     4,
     199,     4,     4,   164,   164,     4,     4,     4,     4,     4,
       4,   162,   162,   162,   162,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   162,     4,     4,   205,     4,
       4,     4,   164,   215,     4,     4,     4,     4,     4,     4,
       4,   162,   164,     4,     4,     4,     4,     4,   312,     4,
     395,     4,     4,     4,     4,     4,     4,     4,     4,   412,
       4,     4,   162,     4,     4,     4,   164,   354,     4,   164,
     164,   378,     4,     4,   288,   164,     4,     4,   162,     4,
     162,   162,     4,     4,   164,   164,   164,     4,     4,     4,
       4,   466,     4,   505,     4,     7,     7,   180,   180,   180,
       7,     7,   161,   161,   161,     7,     7,     5,     5,     5,
       5,     5,   182,   184,   161,     5,     5,     5,     7,     7,
       7,     5,   191,    14,    15,   222,    17,    18,   225,   161,
     161,   161,     5,   161,   161,   161,    80,    81,    82,   331,
     191,   161,     5,     7,   161,   191,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     180,   161,   161,   161,    15,   128,   479,   129,   130,   131,
     132,   133,   164,   487,   161,   161,   161,     5,   180,   204,
     504,   214,    21,   231,   232,   233,    30,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,   195,   243,   244,   245,   248,   250,   252,   254,
     255,   257,   258,   259,   260,   261,   262,   263,   264,   266,
     268,   269,   243,     7,   239,   240,   241,     7,   305,   306,
     307,     7,   346,   347,   348,     7,   370,   371,   372,     7,
     336,   337,   338,    90,    91,    92,    93,    95,   272,   273,
     274,   275,   276,   277,   278,     7,   442,   443,     7,   281,
     282,   283,   103,   104,   105,   106,   107,   108,   295,   296,
     297,   298,   299,   300,   301,   302,   111,   112,   195,   398,
     400,   455,   456,   457,   459,   465,   192,     7,   388,   389,
     390,     7,   404,   405,   406,    98,   419,   421,   439,     7,
     508,   509,     8,     8,     8,   234,     3,     8,   246,   249,
     251,   253,     4,     4,     4,     4,     4,   265,   267,     4,
       4,     4,     4,     4,     3,     8,     8,   242,     6,     3,
     308,     6,     3,   349,     6,     3,   373,     6,     3,   339,
       6,     3,     3,     6,   444,     3,     6,   284,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   458,   460,
       3,     8,     8,   161,   193,   194,   391,     6,     3,   407,
       6,     3,   422,     8,   510,     3,     6,     4,   232,     4,
       4,     4,     4,   162,   164,   162,   164,   162,     4,     4,
     162,   162,   162,   162,   164,   244,   243,   241,   311,   307,
     352,   348,   376,   372,   195,   206,   207,   208,   211,   255,
     303,   321,   325,   327,   329,   340,   341,   368,   398,   400,
     413,   415,   417,   437,   338,   273,    86,    87,   195,   255,
     342,   368,   398,   400,   413,   415,   417,   445,   446,   447,
     448,   449,   451,   443,   287,   283,   162,   162,   162,   162,
     162,   162,   296,     4,     4,   456,     6,     3,   394,   390,
     410,   406,     4,   138,   140,   141,   195,   255,   398,   400,
     511,   512,   513,   514,   516,   509,   161,    31,    32,    33,
      34,   247,   161,   161,   161,   161,   161,     8,     8,     8,
       8,     3,     8,   450,     4,     8,     3,     8,   161,   161,
     161,     8,     8,   191,   517,     4,   515,     3,     8,   341,
       4,   164,   447,     4,   162,     4,   512,   161,     5,   161,
       7,   518,   519,   520,     3,     6,   139,   142,   143,   144,
     521,   522,   523,   525,   526,   527,   519,   524,     4,     4,
       4,     3,     8,     4,   164,   162,   162,   522,   161
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
     206,   207,   208,   209,   210,   211,   213,   212,   214,   214,
     215,   215,   215,   215,   215,   215,   215,   217,   216,   219,
     218,   221,   220,   222,   222,   224,   223,   225,   225,   226,
     228,   227,   230,   229,   231,   231,   232,   234,   233,   236,
     235,   238,   237,   239,   239,   240,   240,   242,   241,   243,
     243,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   246,
     245,   247,   247,   247,   247,   249,   248,   251,   250,   253,
     252,   254,   256,   255,   257,   258,   259,   260,   261,   262,
     263,   265,   264,   267,   266,   268,   269,   271,   270,   272,
     272,   273,   273,   273,   273,   273,   274,   275,   276,   277,
     278,   280,   279,   281,   281,   282,   282,   284,   283,   286,
     285,   287,   287,   287,   288,   288,   290,   289,   292,   291,
     294,   293,   295,   295,   296,   296,   296,   296,   296,   296,
     297,   298,   299,   300,   301,   302,   304,   303,   305,   305,
     306,   306,   308,   307,   310,   309,   311,   311,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   314,   313,   316,   315,   318,   317,   320,
     319,   322,   321,   324,   323,   326,   325,   328,   327,   330,
     329,   331,   331,   331,   332,   333,   335,   334,   336,   336,
     337,   337,   339,   338,   340,   340,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   343,   342,   345,   344,   346,   346,
     347,   347,   349,   348,   351,   350,   352,   352,   353,   353,
     354,   354,   354,   354,   354,   354,   354,   354,   354,   354,
     355,   356,   357,   359,   358,   361,   360,   363,   362,   364,
     366,   365,   367,   369,   368,   370,   370,   371,   371,   373,
     372,   375,   374,   376,   376,   377,   377,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   379,   381,   380,   382,
     383,   384,   385,   387,   386,   388,   388,   389,   389,   391,
     390,   393,   392,   394,   394,   395,   395,   395,   395,   395,
     395,   395,   397,   396,   399,   398,   401,   400,   403,   402,
     404,   404,   405,   405,   407,   406,   409,   408,   410,   410,
     411,   411,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   414,   413,   416,
     415,   418,   417,   420,   419,   422,   421,   424,   423,   426,
     425,   428,   427,   430,   429,   432,   431,   434,   433,   436,
     435,   438,   437,   439,   439,   441,   440,   442,   442,   444,
     443,   445,   445,   446,   446,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   448,   450,   449,   451,
     452,   454,   453,   455,   455,   456,   456,   456,   456,   456,
     458,   457,   460,   459,   462,   461,   464,   463,   465,   465,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   467,
     469,   468,   471,   470,   472,   474,   473,   475,   476,   478,
     477,   479,   479,   481,   480,   482,   483,   484,   486,   485,
     487,   487,   487,   487,   487,   489,   488,   491,   490,   493,
     492,   495,   494,   497,   496,   499,   498,   501,   500,   503,
     502,   504,   504,   505,   507,   506,   508,   508,   510,   509,
     511,   511,   512,   512,   512,   512,   512,   512,   512,   513,
     515,   514,   517,   516,   518,   518,   520,   519,   521,   521,
     522,   522,   522,   522,   524,   523,   525,   526,   527
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
       3,     3,     3,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     6,     1,     3,     1,     0,     4,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     0,     4,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
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
     459,   464,   469,   474,   479,   484,   490,   490,   501,   502,
     505,   506,   507,   508,   509,   510,   511,   514,   514,   523,
     523,   533,   533,   540,   541,   544,   544,   551,   553,   557,
     563,   563,   575,   575,   585,   586,   588,   590,   590,   608,
     608,   620,   620,   630,   631,   634,   635,   638,   638,   648,
     649,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   672,
     672,   679,   680,   681,   682,   685,   685,   693,   693,   701,
     701,   709,   714,   714,   722,   727,   732,   737,   742,   747,
     752,   757,   757,   765,   765,   773,   778,   783,   783,   793,
     794,   797,   798,   799,   800,   801,   804,   809,   814,   819,
     824,   829,   829,   839,   840,   843,   844,   847,   847,   857,
     857,   867,   868,   869,   872,   873,   876,   876,   884,   884,
     892,   892,   903,   904,   907,   908,   909,   910,   911,   912,
     915,   920,   925,   930,   935,   940,   948,   948,   961,   962,
     965,   966,   973,   973,   999,   999,  1010,  1011,  1015,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,
    1037,  1038,  1039,  1042,  1042,  1050,  1050,  1058,  1058,  1066,
    1066,  1074,  1074,  1082,  1082,  1090,  1090,  1098,  1098,  1108,
    1108,  1115,  1116,  1117,  1120,  1125,  1132,  1132,  1143,  1144,
    1148,  1149,  1152,  1152,  1160,  1161,  1164,  1165,  1166,  1167,
    1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,
    1178,  1179,  1180,  1181,  1188,  1188,  1201,  1201,  1210,  1211,
    1214,  1215,  1220,  1220,  1235,  1235,  1249,  1250,  1253,  1254,
    1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,  1266,
    1269,  1271,  1276,  1278,  1278,  1286,  1286,  1294,  1294,  1302,
    1304,  1304,  1312,  1321,  1321,  1333,  1334,  1339,  1340,  1345,
    1345,  1357,  1357,  1369,  1370,  1375,  1376,  1381,  1382,  1383,
    1384,  1385,  1386,  1387,  1388,  1389,  1392,  1394,  1394,  1402,
    1404,  1406,  1411,  1419,  1419,  1431,  1432,  1435,  1436,  1439,
    1439,  1449,  1449,  1459,  1460,  1463,  1464,  1465,  1466,  1467,
    1468,  1469,  1472,  1472,  1480,  1480,  1505,  1505,  1535,  1535,
    1545,  1546,  1549,  1550,  1553,  1553,  1562,  1562,  1571,  1572,
    1575,  1576,  1580,  1581,  1582,  1583,  1584,  1585,  1586,  1587,
    1588,  1589,  1590,  1591,  1592,  1593,  1594,  1597,  1597,  1605,
    1605,  1613,  1613,  1621,  1621,  1629,  1629,  1639,  1639,  1647,
    1647,  1655,  1655,  1663,  1663,  1671,  1671,  1679,  1679,  1687,
    1687,  1700,  1700,  1710,  1711,  1717,  1717,  1727,  1728,  1731,
    1731,  1741,  1742,  1745,  1746,  1749,  1750,  1751,  1752,  1753,
    1754,  1755,  1756,  1757,  1758,  1759,  1762,  1764,  1764,  1772,
    1781,  1788,  1788,  1798,  1799,  1802,  1803,  1804,  1805,  1806,
    1809,  1809,  1817,  1817,  1827,  1827,  1839,  1839,  1849,  1850,
    1853,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,  1862,
    1863,  1864,  1865,  1866,  1867,  1868,  1869,  1870,  1871,  1874,
    1879,  1879,  1887,  1887,  1895,  1900,  1900,  1908,  1913,  1918,
    1918,  1926,  1927,  1930,  1930,  1938,  1943,  1948,  1953,  1953,
    1961,  1964,  1967,  1970,  1973,  1979,  1979,  1987,  1987,  1995,
    1995,  2006,  2006,  2013,  2013,  2020,  2020,  2032,  2032,  2042,
    2042,  2053,  2054,  2058,  2062,  2062,  2074,  2075,  2079,  2079,
    2087,  2088,  2091,  2092,  2093,  2094,  2095,  2096,  2097,  2100,
    2105,  2105,  2113,  2113,  2123,  2124,  2127,  2127,  2135,  2136,
    2139,  2140,  2141,  2142,  2145,  2145,  2153,  2158,  2163
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
#line 4760 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2168 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
