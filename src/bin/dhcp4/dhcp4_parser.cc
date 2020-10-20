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
      case 210: // value
      case 214: // map_value
      case 255: // ddns_replace_client_name_value
      case 280: // socket_type
      case 283: // outbound_interface_value
      case 305: // db_type
      case 399: // hr_mode
      case 554: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 194: // "boolean"
        value.move< bool > (that.value);
        break;

      case 193: // "floating point"
        value.move< double > (that.value);
        break;

      case 192: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 191: // "constant string"
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
      case 210: // value
      case 214: // map_value
      case 255: // ddns_replace_client_name_value
      case 280: // socket_type
      case 283: // outbound_interface_value
      case 305: // db_type
      case 399: // hr_mode
      case 554: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 194: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 193: // "floating point"
        value.copy< double > (that.value);
        break;

      case 192: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 191: // "constant string"
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
            case 191: // "constant string"

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 192: // "integer"

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 193: // "floating point"

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 194: // "boolean"

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 210: // value

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 214: // map_value

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 255: // ddns_replace_client_name_value

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 280: // socket_type

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 283: // outbound_interface_value

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 305: // db_type

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 399: // hr_mode

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 554: // ncr_protocol_value

#line 273 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 210: // value
      case 214: // map_value
      case 255: // ddns_replace_client_name_value
      case 280: // socket_type
      case 283: // outbound_interface_value
      case 305: // db_type
      case 399: // hr_mode
      case 554: // ncr_protocol_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 194: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 193: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 192: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 191: // "constant string"
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
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 283 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 286 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 287 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 290 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 294 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 305 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 308 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 327 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 334 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as< std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as< std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 358 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 362 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 380 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 384 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1110 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1129 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 636 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1374 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 773 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1504 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 830 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 923 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 925 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1835 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1845 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 1016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1903 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1912 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 1034 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2028 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2210 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1474 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1476 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2585 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2611 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2643 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1694 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2751 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1896 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 3001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 2005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 2029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 2034 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 2037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 2043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2064 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2135 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2139 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2171 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2177 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2185 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2193 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2218 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3475 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 644:
#line 2261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr qt(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3504 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2282 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set(yystack_[3].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 650:
#line 2292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 651:
#line 2298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 653:
#line 2309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3575 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 674:
#line 2339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3585 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 675:
#line 2345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 676:
#line 2348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 677:
#line 2354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3614 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 678:
#line 2360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3623 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 679:
#line 2363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 680:
#line 2369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3643 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 681:
#line 2375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 682:
#line 2381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 683:
#line 2384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 684:
#line 2390 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 685:
#line 2391 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 686:
#line 2394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 687:
#line 2397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 688:
#line 2404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 689:
#line 2407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3721 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 690:
#line 2414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 691:
#line 2421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 692:
#line 2428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 693:
#line 2431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 694:
#line 2437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 695:
#line 2440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 696:
#line 2447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3787 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 697:
#line 2450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 698:
#line 2457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 699:
#line 2460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 700:
#line 2469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 701:
#line 2475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 702:
#line 2481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 703:
#line 2485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 708:
#line 2500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 709:
#line 2506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 710:
#line 2511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 711:
#line 2519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 712:
#line 2525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 715:
#line 2537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 716:
#line 2541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 726:
#line 2558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 727:
#line 2564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 728:
#line 2567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 729:
#line 2573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 730:
#line 2579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 733:
#line 2588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 734:
#line 2592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 742:
#line 2607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 743:
#line 2610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 744:
#line 2616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 745:
#line 2622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 746:
#line 2628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 747:
#line 2634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 748:
#line 2637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4063 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 4067 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -924;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     168,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,    31,    41,    36,    54,    57,    70,
      72,    74,    89,   104,   111,   121,   128,   135,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,    41,  -158,    27,   122,    67,   306,
      59,   185,   -37,   482,   230,   -86,   573,   162,  -924,   101,
     161,    49,   152,   164,  -924,   163,  -924,  -924,  -924,   172,
     215,   222,  -924,  -924,  -924,  -924,  -924,  -924,   225,   233,
     241,   249,   255,   261,   265,   278,   291,   295,   302,  -924,
     308,   310,   311,   337,   369,  -924,  -924,  -924,   370,   371,
     382,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,   389,  -924,  -924,  -924,  -924,  -924,  -924,
     396,  -924,   407,  -924,    84,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,   414,  -924,    94,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,   419,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,   100,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,   107,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,   208,   260,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,   331,  -924,  -924,   421,  -924,
    -924,  -924,   424,  -924,  -924,   422,   394,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
     427,   428,  -924,  -924,  -924,  -924,   425,   438,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
     118,  -924,  -924,  -924,   431,  -924,  -924,   440,  -924,   442,
     443,  -924,  -924,   444,   447,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,   129,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
     453,   131,  -924,  -924,  -924,  -924,    41,    41,  -924,  -140,
     454,  -924,   456,   457,   458,   269,   271,   273,   464,   467,
     470,   475,   477,   478,   293,   294,   297,   300,   301,   289,
     307,   312,   315,   309,   318,   483,   320,   321,   317,   325,
     329,   490,   500,   514,   332,   336,   340,   525,   527,   534,
     535,   536,   537,   562,   563,   565,   568,   569,   574,   385,
     575,   578,   579,   580,   581,   582,   397,   583,  -924,   122,
    -924,   588,   589,   591,   400,    67,  -924,   592,   593,   594,
     595,   596,   597,   411,   600,   601,   603,   306,  -924,   604,
      59,  -924,   605,   606,   607,   608,   609,   610,   611,   617,
    -924,   185,  -924,   618,   619,   434,   624,   625,   626,   437,
    -924,   482,   628,   439,   441,  -924,   230,   630,   632,   -70,
    -924,   445,   633,   634,   452,   641,   465,   466,   655,   656,
     480,   484,   673,   675,   680,   681,   573,  -924,   682,   495,
     162,  -924,  -924,  -924,   686,   685,   688,   689,   690,  -924,
    -924,  -924,   507,   508,   510,   695,   697,   700,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,   515,
    -924,  -924,  -924,  -924,  -924,   -90,   516,   517,  -924,  -924,
    -924,   704,   705,   707,   708,   709,   523,   174,   710,   712,
     713,   714,   726,  -924,   727,   728,   729,   730,   547,   550,
    -924,   737,  -924,   738,   234,   272,  -924,  -924,   553,   554,
     555,   742,   557,   558,  -924,   738,   559,   744,  -924,   561,
    -924,   738,   564,   567,   570,   571,   572,   576,   577,  -924,
     584,   585,  -924,   586,   587,   598,  -924,  -924,   599,  -924,
    -924,  -924,   602,   709,  -924,  -924,   612,   613,  -924,   614,
    -924,  -924,    10,   621,  -924,  -924,   -90,   615,   616,   620,
    -924,   748,  -924,  -924,    41,   122,   162,    67,   735,  -924,
    -924,  -924,   503,   503,   747,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,   753,   758,   759,   762,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,   157,   763,   764,   765,
     432,   149,    63,   -14,   573,  -924,  -924,   766,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,   767,
    -924,  -924,  -924,  -924,   186,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,   747,  -924,   160,   170,   219,  -924,   220,
    -924,  -924,  -924,  -924,  -924,  -924,   775,   776,   779,   780,
     781,  -924,  -924,  -924,  -924,   782,   783,   784,   787,   788,
     790,  -924,   235,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,   236,  -924,   789,   793,  -924,  -924,
     791,   795,  -924,  -924,   794,   796,  -924,  -924,   802,   798,
    -924,  -924,   803,   799,  -924,  -924,  -924,  -924,  -924,  -924,
      46,  -924,  -924,  -924,  -924,  -924,  -924,  -924,    87,  -924,
    -924,   804,   809,  -924,  -924,   807,   811,  -924,   812,   813,
     814,   815,   816,   817,   252,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,   818,   819,   820,  -924,   259,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,   263,  -924,
    -924,  -924,   821,  -924,   822,  -924,  -924,  -924,   319,  -924,
    -924,  -924,  -924,  -924,   322,  -924,   119,  -924,   636,  -924,
     823,   825,  -924,  -924,  -924,  -924,   824,   827,  -924,  -924,
    -924,   826,   735,  -924,   830,   831,   832,   833,   623,   637,
     646,   645,   648,   837,   838,   839,   840,   653,   654,   657,
     658,   659,   660,   503,  -924,  -924,   503,  -924,   747,   306,
    -924,   753,   482,  -924,   758,   230,  -924,   759,   590,  -924,
     762,   157,  -924,   212,   763,  -924,   185,  -924,   764,   -86,
    -924,   765,   662,   663,   664,   665,   666,   667,   432,  -924,
     669,   668,   672,   149,  -924,   843,   844,    63,  -924,   676,
     847,   674,   857,   -14,  -924,  -924,   -32,   766,  -924,  -924,
     861,   874,    59,  -924,   767,   881,  -924,  -924,   699,  -924,
     324,   711,   715,   716,  -924,  -924,  -924,  -924,  -924,   732,
     743,   750,   751,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
     323,  -924,   334,  -924,   878,  -924,   911,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,   335,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
     916,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
     918,   930,  -924,  -924,  -924,  -924,  -924,   936,  -924,   387,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,   801,   806,  -924,  -924,   808,  -924,    41,  -924,
    -924,   986,  -924,  -924,  -924,  -924,  -924,   391,  -924,  -924,
    -924,  -924,  -924,  -924,   810,   393,  -924,   738,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,   590,  -924,   990,   828,  -924,
     212,  -924,  -924,  -924,  -924,  -924,  -924,   991,   829,   994,
     -32,  -924,  -924,  -924,  -924,  -924,   834,  -924,  -924,   995,
    -924,   835,  -924,  -924,   996,  -924,  -924,   140,  -924,    34,
     996,  -924,  -924,   998,  1000,  1001,  -924,   409,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  1002,   836,   841,   842,  1003,
      34,  -924,   845,  -924,  -924,  -924,   846,  -924,  -924,  -924
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   172,     9,   330,    11,   521,    13,
     546,    15,   446,    17,   454,    19,   491,    21,   295,    23,
     652,    25,   702,    27,    45,    39,     0,     0,     0,     0,
       0,   548,     0,   456,   493,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   700,   161,   187,     0,
       0,     0,   567,   569,   571,   185,   194,   196,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
       0,     0,     0,     0,     0,   140,   147,   149,     0,     0,
       0,   322,   444,   483,   397,   534,   536,   390,   260,   595,
     538,   287,   306,     0,   274,   621,   634,   650,   153,   155,
       0,   711,     0,   120,     0,    62,    64,    65,    66,    67,
      68,    99,   100,   101,   102,   103,    69,    97,    86,    87,
      88,   107,   108,   109,   110,   111,   112,   113,   114,   105,
     106,   115,   116,   117,   119,    72,    73,    94,    74,    75,
      76,   118,    80,    81,    70,    98,    71,    78,    79,    92,
      93,    95,    89,    90,    91,    77,    82,    83,    84,    85,
      96,   104,   174,   176,   180,     0,   171,     0,   163,   165,
     166,   167,   168,   169,   170,   378,   380,   382,   513,   376,
     384,     0,   388,   386,   591,   375,   334,   335,   336,   337,
     338,   359,   360,   361,   362,   363,   349,   350,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,     0,
     332,   341,   354,   355,   356,   342,   344,   345,   347,   343,
     339,   340,   357,   358,   346,   351,   352,   353,   348,   532,
     531,   527,   528,   526,     0,   523,   525,   529,   530,   589,
     577,   579,   583,   581,   587,   585,   573,   566,   560,   564,
     565,     0,   549,   550,   561,   562,   563,   557,   552,   558,
     554,   555,   556,   559,   553,     0,   473,   240,     0,   477,
     475,   480,     0,   469,   470,     0,   457,   458,   460,   472,
     461,   462,   463,   479,   464,   465,   466,   467,   468,   507,
       0,     0,   505,   506,   509,   510,     0,   494,   495,   497,
     498,   499,   500,   501,   502,   503,   504,   302,   304,   299,
       0,   297,   300,   301,     0,   688,   675,     0,   678,     0,
       0,   682,   686,     0,     0,   692,   694,   696,   698,   673,
     671,   672,     0,   654,   656,   657,   658,   659,   660,   661,
     662,   663,   668,   664,   665,   666,   667,   669,   670,   708,
       0,     0,   704,   706,   707,    44,     0,     0,    37,     0,
       0,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    55,     0,
      61,     0,     0,     0,     0,     0,   173,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   331,     0,
       0,   522,     0,     0,     0,     0,     0,     0,     0,     0,
     547,     0,   447,     0,     0,     0,     0,     0,     0,     0,
     455,     0,     0,     0,     0,   492,     0,     0,     0,     0,
     296,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   653,     0,     0,
       0,   703,    48,    41,     0,     0,     0,     0,     0,   134,
     135,   136,     0,     0,     0,     0,     0,     0,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,     0,
     158,   159,   137,   138,   139,     0,     0,     0,   151,   152,
     157,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   620,     0,     0,     0,     0,     0,     0,
     160,     0,    63,     0,     0,     0,   184,   164,     0,     0,
       0,     0,     0,     0,   396,     0,     0,     0,   333,     0,
     524,     0,     0,     0,     0,     0,     0,     0,     0,   551,
       0,     0,   471,     0,     0,     0,   482,   459,     0,   511,
     512,   496,     0,     0,   298,   674,     0,     0,   677,     0,
     680,   681,     0,     0,   690,   691,     0,     0,     0,     0,
     655,     0,   710,   705,     0,     0,     0,     0,     0,   568,
     570,   572,     0,     0,   198,   133,   142,   143,   144,   145,
     146,   141,   148,   150,   324,   448,   485,   399,    38,   535,
     537,   392,   393,   394,   395,   391,     0,     0,   540,   289,
       0,     0,     0,     0,     0,   154,   156,     0,    49,   175,
     178,   179,   177,   182,   183,   181,   379,   381,   383,   515,
     377,   385,   389,   387,     0,   533,   590,   578,   580,   584,
     582,   588,   586,   574,   474,   241,   478,   476,   481,   508,
     303,   305,   689,   676,   679,   684,   685,   683,   687,   693,
     695,   697,   699,   198,    42,     0,     0,     0,   192,     0,
     189,   191,   227,   233,   235,   237,     0,     0,     0,     0,
       0,   249,   251,   253,   255,     0,     0,     0,     0,     0,
       0,   226,     0,   204,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   219,   220,   221,   216,   222,   223,
     224,   217,   218,   225,     0,   202,     0,   199,   200,   328,
       0,   325,   326,   452,     0,   449,   450,   489,     0,   486,
     487,   403,     0,   400,   401,   269,   270,   271,   272,   273,
       0,   262,   264,   265,   266,   267,   268,   599,     0,   597,
     544,     0,   541,   542,   293,     0,   290,   291,     0,     0,
       0,     0,     0,     0,     0,   308,   310,   311,   312,   313,
     314,   315,     0,     0,     0,   283,     0,   276,   278,   279,
     280,   281,   282,   630,   632,   629,   627,   628,     0,   623,
     625,   626,     0,   645,     0,   648,   641,   642,     0,   636,
     638,   639,   640,   643,     0,   715,     0,   713,    51,   519,
       0,   516,   517,   575,   593,   594,     0,     0,    59,   701,
     162,     0,     0,   188,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   186,   195,     0,   197,     0,     0,
     323,     0,   456,   445,     0,   493,   484,     0,     0,   398,
       0,     0,   261,   601,     0,   596,   548,   539,     0,     0,
     288,     0,     0,     0,     0,     0,     0,     0,     0,   307,
       0,     0,     0,     0,   275,     0,     0,     0,   622,     0,
       0,     0,     0,     0,   635,   651,     0,     0,   712,    53,
       0,    52,     0,   514,     0,     0,   592,   709,     0,   190,
       0,     0,     0,     0,   239,   242,   243,   244,   245,     0,
       0,     0,     0,   257,   258,   246,   247,   248,   259,   205,
       0,   201,     0,   327,     0,   451,     0,   488,   443,   422,
     423,   424,   410,   411,   427,   428,   429,   430,   431,   413,
     414,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   407,   408,   409,   420,   421,   419,     0,   405,
     412,   425,   426,   415,   416,   417,   418,   402,   263,   617,
       0,   615,   616,   608,   609,   613,   614,   610,   611,   612,
       0,   602,   603,   605,   606,   607,   598,     0,   543,     0,
     292,   316,   317,   318,   319,   320,   321,   309,   284,   285,
     286,   277,     0,     0,   624,   644,     0,   647,     0,   637,
     729,     0,   727,   725,   719,   723,   724,     0,   717,   721,
     722,   720,   714,    50,     0,     0,   518,     0,   193,   229,
     230,   231,   232,   228,   234,   236,   238,   250,   252,   254,
     256,   203,   329,   453,   490,     0,   404,     0,     0,   600,
       0,   545,   294,   631,   633,   646,   649,     0,     0,     0,
       0,   716,    54,   520,   576,   406,     0,   619,   604,     0,
     726,     0,   718,   618,     0,   728,   733,     0,   731,     0,
       0,   730,   742,     0,     0,     0,   747,     0,   735,   737,
     738,   739,   740,   741,   732,     0,     0,     0,     0,     0,
       0,   734,     0,   744,   745,   746,     0,   736,   743,   748
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,   -52,  -924,  -533,  -924,   375,
    -924,  -924,  -924,  -924,  -924,  -924,  -581,  -924,  -924,  -924,
     -67,  -924,  -924,  -924,  -924,  -924,  -924,   354,   551,   -40,
     -28,   -24,    -1,     1,    11,    19,    22,    25,    26,  -924,
    -924,  -924,  -924,    29,    30,    32,    37,    40,    43,  -924,
     365,    44,  -924,    45,  -924,    47,    48,    50,  -924,    51,
    -924,    55,  -924,  -924,  -924,  -924,  -924,   355,   548,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,   112,  -924,  -924,  -924,  -924,
    -924,  -924,   274,  -924,    88,  -924,  -650,    92,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,   -63,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,    77,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
      56,  -924,  -924,  -924,  -924,  -924,  -924,  -924,    69,  -924,
    -924,  -924,    75,   518,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,    65,  -924,  -924,  -924,  -924,  -924,  -924,  -923,  -924,
    -924,  -924,    97,  -924,  -924,  -924,   102,   552,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -917,  -924,   -65,  -924,
      53,  -924,    58,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
      98,  -924,  -924,  -103,   -46,  -924,  -924,  -924,  -924,  -924,
     105,  -924,  -924,  -924,   108,  -924,   540,  -924,   -42,  -924,
    -924,  -924,  -924,  -924,   -36,  -924,  -924,  -924,  -924,  -924,
     -35,  -924,  -924,  -924,   106,  -924,  -924,  -924,   109,  -924,
     539,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,    64,  -924,  -924,  -924,    60,   622,  -924,  -924,
     -51,  -924,   -11,  -924,   -25,  -924,  -924,  -924,    99,  -924,
    -924,  -924,   103,  -924,   560,   -55,  -924,     0,  -924,     7,
    -924,   338,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -911,
    -924,  -924,  -924,  -924,  -924,   110,  -924,  -924,  -924,   -87,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,    83,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,    82,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,   362,   531,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,
    -924,  -924,  -924,  -924,  -924,  -924,  -924,  -924,   402,   529,
    -924,  -924,  -924,  -924,  -924,  -924,    85,  -924,  -924,   -89,
    -924,  -924,  -924,  -924,  -924,  -924,  -110,  -924,  -924,  -127,
    -924,  -924,  -924,  -924,  -924,  -924,  -924
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   679,
      82,    83,    39,    64,    79,    80,   699,   888,   980,   981,
     771,    41,    66,    85,   400,    43,    67,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   425,   158,   159,   160,   161,   162,   163,   164,   431,
     671,   165,   432,   166,   433,   167,   168,   169,   454,   170,
     455,   171,   172,   173,   174,   175,   403,   207,   208,    45,
      68,   209,   461,   210,   462,   702,   211,   463,   705,   212,
     176,   411,   177,   404,   749,   750,   751,   901,   178,   412,
     179,   413,   796,   797,   798,   926,   772,   773,   774,   904,
    1123,   775,   905,   776,   906,   777,   907,   778,   779,   494,
     780,   781,   782,   783,   784,   785,   786,   787,   913,   788,
     914,   789,   915,   790,   916,   791,   792,   793,   180,   444,
     820,   821,   822,   823,   824,   825,   826,   181,   450,   856,
     857,   858,   859,   860,   182,   447,   835,   836,   837,   949,
      59,    75,   350,   351,   352,   507,   353,   508,   183,   448,
     844,   845,   846,   847,   848,   849,   850,   851,   184,   437,
     800,   801,   802,   929,    47,    69,   249,   250,   251,   471,
     252,   467,   253,   468,   254,   469,   255,   472,   256,   475,
     257,   474,   185,   443,   685,   259,   186,   440,   812,   813,
     814,   938,  1048,  1049,   187,   438,    53,    72,   804,   805,
     806,   932,    55,    73,   315,   316,   317,   318,   319,   320,
     321,   493,   322,   497,   323,   496,   324,   325,   498,   326,
     188,   439,   808,   809,   810,   935,    57,    74,   336,   337,
     338,   339,   340,   502,   341,   342,   343,   344,   261,   470,
     890,   891,   892,   982,    49,    70,   274,   275,   276,   479,
     189,   441,   190,   442,   191,   446,   831,   832,   833,   946,
      51,    71,   291,   292,   293,   192,   408,   193,   409,   194,
     410,   297,   489,   895,   985,   298,   483,   299,   484,   300,
     486,   301,   485,   302,   488,   303,   487,   304,   482,   268,
     476,   896,   195,   445,   828,   829,   943,  1070,  1071,  1072,
    1073,  1074,  1137,  1075,   196,   197,   451,   868,   869,   870,
     965,   871,   966,   198,   452,   878,   879,   880,   881,   970,
     882,   883,   972,   199,   453,    61,    76,   372,   373,   374,
     375,   513,   376,   377,   515,   378,   379,   380,   518,   737,
     381,   519,   382,   512,   383,   384,   385,   522,   386,   523,
     387,   524,   388,   525,   200,   402,    63,    77,   391,   392,
     393,   528,   394,   201,   457,   886,   887,   976,  1107,  1108,
    1109,  1110,  1149,  1111,  1147,  1167,  1168,  1169,  1177,  1178,
    1179,  1185,  1180,  1181,  1182,  1183,  1189
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
     143,   206,   225,   270,   287,   271,   313,   332,   349,   369,
     314,   333,    78,   794,   265,  1043,   294,   213,   262,   277,
     289,  1044,   327,   345,   712,   370,   305,  1056,   735,   226,
     716,    28,   334,    81,   260,   273,   288,    84,   335,   347,
     348,   227,   678,    40,   264,   228,    29,   122,    30,   941,
      31,   534,   942,   397,   307,   347,   348,   214,   263,   278,
     290,    42,   328,   346,    44,   371,   125,   126,   229,   266,
     230,   295,   666,   667,   668,   669,   267,    46,   296,    48,
     231,    50,   202,   203,   125,   126,   204,   459,   232,   205,
     944,   233,   460,   945,   234,   235,    52,   465,   236,   237,
     678,   238,   466,   477,   670,   142,   239,   395,   478,   240,
     480,    54,   241,   242,   243,   481,   244,   245,    56,   246,
     247,   509,   977,   272,   248,   978,   510,   258,    58,   872,
     873,   874,   526,    86,   530,    60,    87,   527,  1100,   531,
    1101,  1102,    62,  1170,   123,    88,  1171,    89,    90,    91,
      92,    93,    94,    95,    96,    97,   269,   125,   126,   142,
     398,   125,   126,   459,   396,   125,   126,   399,   898,   222,
     736,   401,   223,   530,   389,   390,   405,   875,   899,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   863,   864,  1172,   122,   123,  1173,  1174,
    1175,  1176,  1043,    92,    93,    94,   490,   124,  1044,   406,
     125,   126,   465,   902,  1056,   127,   407,   900,   903,   414,
     128,   129,    32,    33,    34,    35,   130,   415,   923,   923,
      92,    93,    94,   924,   925,   416,   131,   125,   126,   132,
     142,   700,   701,   417,   142,   958,   133,   134,   142,   418,
     959,   135,   963,   491,   136,   419,   967,   964,   137,   420,
     123,   968,   815,   816,   817,   818,  1010,   819,   681,   682,
     683,   684,   421,   125,   126,   852,   853,   854,   138,   139,
     140,   141,   703,   704,   279,   422,   122,   123,   307,   423,
     280,   281,   282,   283,   284,   285,   424,   286,   286,   893,
     125,   126,   426,   142,   427,   428,   307,   329,   308,   309,
     330,   331,   973,  1059,  1060,   526,   923,   974,   125,   126,
     975,  1131,    90,    91,    92,    93,    94,   477,  1135,   492,
     142,   429,  1132,  1136,   532,   533,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,  1119,
    1120,  1121,  1122,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   430,   434,   435,   142,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   436,   215,   216,   217,
     509,   123,   143,   449,  1150,  1142,   480,   501,   206,  1151,
     456,  1153,   218,   142,   125,   126,   219,   220,   221,   127,
     225,   458,  1190,   270,   213,   271,   222,  1191,   464,   223,
     130,   142,   265,   473,   287,   495,   262,   224,   499,   277,
     500,   503,   504,   505,   313,   511,   294,   226,   314,   332,
     289,   506,   260,   333,   514,   273,   516,   517,   520,   227,
     327,   521,   264,   228,   214,   345,   288,   529,   535,   369,
     536,   537,   538,   539,   334,   540,   263,   541,   542,   278,
     335,   543,   138,   139,   544,   370,   229,   266,   230,   545,
     290,   546,   547,   553,   267,   548,   549,   559,   231,   550,
     328,   295,   551,   552,   565,   346,   232,   142,   296,   233,
     554,   557,   234,   235,   566,   555,   236,   237,   556,   238,
     558,   562,   560,   561,   239,   371,   306,   240,   567,   563,
     241,   242,   243,   564,   244,   245,   568,   246,   247,   571,
     569,   572,   248,   272,   570,   258,  1154,   752,   573,   574,
     575,   576,   753,   754,   755,   756,   757,   758,   759,   760,
     761,   762,   763,   764,   765,   766,   767,   768,   769,   770,
     838,   839,   840,   841,   842,   843,   577,   578,   307,   579,
     308,   309,   580,   581,   310,   311,   312,   583,   582,   584,
     125,   126,   585,   586,   587,   588,   589,   591,   143,   307,
     206,   590,   593,   594,   596,   595,   598,   599,   600,   601,
     602,   603,   744,   604,   605,   606,   213,   607,   609,   611,
     612,   613,   614,   615,   616,   617,    90,    91,    92,    93,
      94,   618,   620,   621,   855,   865,   622,   369,   623,   624,
     625,   626,   628,   629,   632,   630,   633,   636,   637,   635,
     861,   866,   876,   370,   638,   639,   214,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   640,   641,   642,
     643,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   125,   126,   142,   644,   123,   307,   646,   645,   647,
     862,   867,   877,   371,   648,   649,   651,   652,   125,   126,
     654,   220,   655,   127,   142,   656,   657,   658,   659,   660,
     222,   661,   662,   223,   663,   664,   665,   672,   673,   674,
     675,   224,   676,   677,   680,   686,    30,   687,   688,   689,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   690,   691,   692,   693,   694,   695,   367,
     368,   696,   697,   698,   706,   707,   708,   709,   710,   711,
     713,   714,   715,   743,   795,   717,   138,   139,   718,   748,
     799,   719,   720,   721,   142,   803,   807,   722,   723,   811,
     827,   830,   834,   885,   889,   724,   725,   726,   727,   908,
     909,   142,   738,   910,   911,   912,   917,   918,   919,   728,
     729,   920,   921,   730,   922,   927,   928,   930,   931,   934,
     933,   937,   940,   732,   733,   734,   740,   741,   936,   939,
     947,   742,   948,   950,   951,   994,   952,   953,   954,   955,
     956,   957,   960,   961,   962,   969,   971,   979,   984,   983,
     988,   995,   986,   987,   990,   991,   992,   993,   996,   997,
     998,   999,  1000,  1001,  1002,  1003,  1004,  1092,  1093,  1005,
    1006,  1096,  1008,  1007,  1081,  1082,  1083,  1084,  1085,  1086,
    1089,  1098,   225,  1088,  1090,   313,  1097,  1113,   332,   314,
    1095,  1018,   333,  1045,   265,  1042,  1061,  1114,   262,   287,
    1062,   327,   349,  1053,   345,  1117,  1133,  1051,  1067,   226,
    1118,   294,  1065,   334,   260,   289,   855,  1063,  1019,   335,
     865,   227,  1124,  1050,   264,   228,  1125,  1126,  1064,  1103,
    1020,   288,   861,  1104,  1021,   270,   866,   271,   263,  1134,
    1138,   328,   876,  1127,   346,  1105,  1139,  1052,   229,   266,
     230,   277,  1066,  1140,  1128,   290,   267,  1022,  1054,  1023,
     231,  1129,  1130,  1068,  1141,  1055,   295,   273,   232,  1024,
    1069,   233,   862,   296,   234,   235,   867,  1025,   236,   237,
    1026,   238,   877,  1027,  1028,  1106,   239,  1029,  1030,   240,
    1031,   278,   241,   242,   243,  1032,   244,   245,  1033,   246,
     247,  1034,  1035,  1036,   248,  1037,  1038,   258,  1039,  1040,
    1148,  1046,  1143,  1041,  1156,  1159,  1047,  1144,  1161,  1145,
    1164,  1152,  1186,  1166,  1187,  1188,  1192,  1196,   731,   745,
     592,   739,   747,   597,   989,  1009,  1011,   897,  1058,  1091,
    1080,  1160,  1157,  1087,  1079,  1163,  1165,   634,  1013,   608,
    1193,  1012,  1155,  1194,  1195,   272,  1198,  1199,  1057,  1015,
    1014,   627,  1115,  1017,  1016,   631,  1146,  1078,  1116,  1077,
    1094,   619,   894,  1158,  1076,  1099,   884,   650,   746,   653,
    1184,  1162,  1112,  1197,     0,     0,     0,     0,  1018,     0,
    1045,     0,  1042,  1061,     0,     0,     0,  1062,     0,     0,
    1053,     0,     0,  1103,  1051,  1067,     0,  1104,     0,  1065,
       0,     0,     0,     0,  1063,  1019,     0,     0,     0,  1105,
    1050,     0,   610,     0,     0,  1064,     0,  1020,     0,     0,
       0,  1021,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1052,     0,     0,     0,     0,  1066,
       0,     0,     0,     0,  1022,  1054,  1023,     0,     0,  1106,
    1068,     0,  1055,     0,     0,     0,  1024,  1069,     0,     0,
       0,     0,     0,     0,  1025,     0,     0,  1026,     0,     0,
    1027,  1028,     0,     0,  1029,  1030,     0,  1031,     0,     0,
       0,     0,  1032,     0,     0,  1033,     0,     0,  1034,  1035,
    1036,     0,  1037,  1038,     0,  1039,  1040,     0,  1046,     0,
    1041,     0,     0,  1047
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   663,    69,   938,    71,    68,    69,    70,
      71,   938,    73,    74,   605,    76,    72,   938,    18,    69,
     611,     0,    74,   191,    69,    70,    71,    10,    74,   125,
     126,    69,   575,     7,    69,    69,     5,    84,     7,     3,
       9,   191,     6,     4,    86,   125,   126,    68,    69,    70,
      71,     7,    73,    74,     7,    76,    98,    99,    69,    69,
      69,    71,   162,   163,   164,   165,    69,     7,    71,     7,
      69,     7,    15,    16,    98,    99,    19,     3,    69,    22,
       3,    69,     8,     6,    69,    69,     7,     3,    69,    69,
     633,    69,     8,     3,   194,   191,    69,     6,     8,    69,
       3,     7,    69,    69,    69,     8,    69,    69,     7,    69,
      69,     3,     3,    70,    69,     6,     8,    69,     7,   143,
     144,   145,     3,    11,     3,     7,    14,     8,   170,     8,
     172,   173,     7,     3,    85,    23,     6,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    97,    98,    99,   191,
       8,    98,    99,     3,     3,    98,    99,     3,     8,   110,
     160,     8,   113,     3,    12,    13,     4,   191,     8,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   140,   141,   171,    84,    85,   174,   175,
     176,   177,  1135,    28,    29,    30,     8,    95,  1135,     4,
      98,    99,     3,     3,  1135,   103,     4,     8,     8,     4,
     108,   109,   191,   192,   193,   194,   114,     4,     3,     3,
      28,    29,    30,     8,     8,     4,   124,    98,    99,   127,
     191,    17,    18,     4,   191,     3,   134,   135,   191,     4,
       8,   139,     3,     3,   142,     4,     3,     8,   146,     4,
      85,     8,   115,   116,   117,   118,   926,   120,   104,   105,
     106,   107,     4,    98,    99,   136,   137,   138,   166,   167,
     168,   169,    20,    21,   109,     4,    84,    85,    86,     4,
     115,   116,   117,   118,   119,   120,     4,   122,   122,   123,
      98,    99,     4,   191,     4,     4,    86,    87,    88,    89,
      90,    91,     3,   111,   112,     3,     3,     8,    98,    99,
       8,     8,    26,    27,    28,    29,    30,     3,     3,     8,
     191,     4,     8,     8,   396,   397,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,    35,
      36,    37,    38,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     4,     4,     4,   191,    71,    72,    73,
      74,    75,    76,    77,    78,    79,     4,    81,    82,    83,
       3,    85,   459,     4,     3,     8,     3,     3,   465,     8,
       4,     8,    96,   191,    98,    99,   100,   101,   102,   103,
     477,     4,     3,   480,   465,   480,   110,     8,     4,   113,
     114,   191,   477,     4,   491,     4,   477,   121,     4,   480,
       8,     4,     4,     8,   501,     4,   491,   477,   501,   506,
     491,     3,   477,   506,     4,   480,     4,     4,     4,   477,
     501,     4,   477,   477,   465,   506,   491,     4,     4,   526,
       4,     4,     4,   194,   506,   194,   477,   194,     4,   480,
     506,     4,   166,   167,     4,   526,   477,   477,   477,     4,
     491,     4,     4,   194,   477,   192,   192,     4,   477,   192,
     501,   491,   192,   192,     4,   506,   477,   191,   491,   477,
     193,   192,   477,   477,     4,   193,   477,   477,   193,   477,
     192,   194,   192,   192,   477,   526,    34,   477,     4,   194,
     477,   477,   477,   194,   477,   477,   194,   477,   477,     4,
     194,     4,   477,   480,   194,   477,  1117,    34,     4,     4,
       4,     4,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
     128,   129,   130,   131,   132,   133,     4,     4,    86,     4,
      88,    89,     4,     4,    92,    93,    94,   192,     4,     4,
      98,    99,     4,     4,     4,     4,     4,     4,   655,    86,
     657,   194,     4,     4,   194,     4,     4,     4,     4,     4,
       4,     4,   654,   192,     4,     4,   657,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    26,    27,    28,    29,
      30,     4,     4,     4,   691,   692,   192,   694,     4,     4,
       4,   194,     4,   194,     4,   194,     4,     4,     4,   194,
     691,   692,   693,   694,   192,     4,   657,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,   192,   192,     4,
       4,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    98,    99,   191,   194,    85,    86,     4,   194,     4,
     691,   692,   693,   694,     4,     4,     4,   192,    98,    99,
       4,   101,     7,   103,   191,     7,     7,     7,   191,   191,
     110,   191,     7,   113,     7,     5,   191,   191,   191,     5,
       5,   121,     5,     5,   191,     5,     7,     5,     5,     5,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,     7,     7,     7,     7,     7,   191,   166,
     167,   191,     5,     5,   191,   191,   191,     5,   191,   191,
     191,     7,   191,     5,     7,   191,   166,   167,   191,    24,
       7,   191,   191,   191,   191,     7,     7,   191,   191,     7,
       7,     7,     7,     7,     7,   191,   191,   191,   191,     4,
       4,   191,   161,     4,     4,     4,     4,     4,     4,   191,
     191,     4,     4,   191,     4,     6,     3,     6,     3,     3,
       6,     3,     3,   191,   191,   191,   191,   191,     6,     6,
       6,   191,     3,     6,     3,   192,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   191,     3,     6,
       4,   194,     8,     6,     4,     4,     4,     4,   192,   194,
     192,     4,     4,     4,     4,   192,   192,     4,     4,   192,
     192,     4,   192,   194,   192,   192,   192,   192,   192,   192,
     192,     4,   929,   194,   192,   932,   192,     6,   935,   932,
     194,   938,   935,   938,   929,   938,   943,     3,   929,   946,
     943,   932,   949,   938,   935,     4,     8,   938,   943,   929,
     191,   946,   943,   935,   929,   946,   963,   943,   938,   935,
     967,   929,   191,   938,   929,   929,   191,   191,   943,   976,
     938,   946,   963,   976,   938,   982,   967,   982,   929,     8,
       4,   932,   973,   191,   935,   976,     8,   938,   929,   929,
     929,   982,   943,     3,   191,   946,   929,   938,   938,   938,
     929,   191,   191,   943,     8,   938,   946,   982,   929,   938,
     943,   929,   963,   946,   929,   929,   967,   938,   929,   929,
     938,   929,   973,   938,   938,   976,   929,   938,   938,   929,
     938,   982,   929,   929,   929,   938,   929,   929,   938,   929,
     929,   938,   938,   938,   929,   938,   938,   929,   938,   938,
       4,   938,   191,   938,     4,     4,   938,   191,     4,   191,
       5,   191,     4,     7,     4,     4,     4,     4,   633,   655,
     459,   646,   657,   465,   902,   923,   928,   743,   941,   963,
     951,   192,   194,   958,   949,   191,   191,   509,   931,   477,
     194,   929,  1135,   192,   192,   982,   191,   191,   940,   934,
     932,   501,   982,   937,   935,   506,  1098,   948,   984,   946,
     967,   491,   714,  1140,   944,   973,   694,   526,   656,   530,
    1170,  1150,   977,  1190,    -1,    -1,    -1,    -1,  1135,    -1,
    1135,    -1,  1135,  1140,    -1,    -1,    -1,  1140,    -1,    -1,
    1135,    -1,    -1,  1150,  1135,  1140,    -1,  1150,    -1,  1140,
      -1,    -1,    -1,    -1,  1140,  1135,    -1,    -1,    -1,  1150,
    1135,    -1,   480,    -1,    -1,  1140,    -1,  1135,    -1,    -1,
      -1,  1135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1135,    -1,    -1,    -1,    -1,  1140,
      -1,    -1,    -1,    -1,  1135,  1135,  1135,    -1,    -1,  1150,
    1140,    -1,  1135,    -1,    -1,    -1,  1135,  1140,    -1,    -1,
      -1,    -1,    -1,    -1,  1135,    -1,    -1,  1135,    -1,    -1,
    1135,  1135,    -1,    -1,  1135,  1135,    -1,  1135,    -1,    -1,
      -1,    -1,  1135,    -1,    -1,  1135,    -1,    -1,  1135,  1135,
    1135,    -1,  1135,  1135,    -1,  1135,  1135,    -1,  1135,    -1,
    1135,    -1,    -1,  1135
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,     0,     5,
       7,     9,   191,   192,   193,   194,   210,   211,   212,   217,
       7,   226,     7,   230,     7,   274,     7,   379,     7,   459,
       7,   475,     7,   411,     7,   417,     7,   441,     7,   355,
       7,   540,     7,   571,   218,   213,   227,   231,   275,   380,
     460,   476,   412,   418,   442,   356,   541,   572,   210,   219,
     220,   191,   215,   216,    10,   228,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    84,    85,    95,    98,    99,   103,   108,   109,
     114,   124,   127,   134,   135,   139,   142,   146,   166,   167,
     168,   169,   191,   225,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   247,   248,
     249,   250,   251,   252,   253,   256,   258,   260,   261,   262,
     264,   266,   267,   268,   269,   270,   285,   287,   293,   295,
     333,   342,   349,   363,   373,   397,   401,   409,   435,   465,
     467,   469,   480,   482,   484,   507,   519,   520,   528,   538,
     569,   578,    15,    16,    19,    22,   225,   272,   273,   276,
     278,   281,   284,   465,   467,    81,    82,    83,    96,   100,
     101,   102,   110,   113,   121,   225,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   248,   249,   250,   251,
     252,   253,   256,   258,   260,   261,   262,   264,   266,   381,
     382,   383,   385,   387,   389,   391,   393,   395,   397,   400,
     435,   453,   465,   467,   469,   480,   482,   484,   504,    97,
     225,   393,   395,   435,   461,   462,   463,   465,   467,   109,
     115,   116,   117,   118,   119,   120,   122,   225,   435,   465,
     467,   477,   478,   479,   480,   482,   484,   486,   490,   492,
     494,   496,   498,   500,   502,   409,    34,    86,    88,    89,
      92,    93,    94,   225,   313,   419,   420,   421,   422,   423,
     424,   425,   427,   429,   431,   432,   434,   465,   467,    87,
      90,    91,   225,   313,   423,   429,   443,   444,   445,   446,
     447,   449,   450,   451,   452,   465,   467,   125,   126,   225,
     357,   358,   359,   361,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   166,   167,   225,
     465,   467,   542,   543,   544,   545,   547,   548,   550,   551,
     552,   555,   557,   559,   560,   561,   563,   565,   567,    12,
      13,   573,   574,   575,   577,     6,     3,     4,     8,     3,
     229,     8,   570,   271,   288,     4,     4,     4,   481,   483,
     485,   286,   294,   296,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   246,     4,     4,     4,     4,
       4,   254,   257,   259,     4,     4,     4,   374,   410,   436,
     402,   466,   468,   398,   334,   508,   470,   350,   364,     4,
     343,   521,   529,   539,   263,   265,     4,   579,     4,     3,
       8,   277,   279,   282,     4,     3,     8,   386,   388,   390,
     454,   384,   392,     4,   396,   394,   505,     3,     8,   464,
       3,     8,   503,   491,   493,   497,   495,   501,   499,   487,
       8,     3,     8,   426,   314,     4,   430,   428,   433,     4,
       8,     3,   448,     4,     4,     8,     3,   360,   362,     3,
       8,     4,   558,   546,     4,   549,     4,     4,   553,   556,
       4,     4,   562,   564,   566,   568,     3,     8,   576,     4,
       3,     8,   210,   210,   191,     4,     4,     4,     4,   194,
     194,   194,     4,     4,     4,     4,     4,     4,   192,   192,
     192,   192,   192,   194,   193,   193,   193,   192,   192,     4,
     192,   192,   194,   194,   194,     4,     4,     4,   194,   194,
     194,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   192,     4,     4,     4,     4,     4,     4,
     194,     4,   233,     4,     4,     4,   194,   273,     4,     4,
       4,     4,     4,     4,   192,     4,     4,     4,   382,     4,
     462,     4,     4,     4,     4,     4,     4,     4,     4,   479,
       4,     4,   192,     4,     4,     4,   194,   421,     4,   194,
     194,   445,     4,     4,   358,   194,     4,     4,   192,     4,
     192,   192,     4,     4,   194,   194,     4,     4,     4,     4,
     543,     4,   192,   574,     4,     7,     7,     7,     7,   191,
     191,   191,     7,     7,     5,   191,   162,   163,   164,   165,
     194,   255,   191,   191,     5,     5,     5,     5,   212,   214,
     191,   104,   105,   106,   107,   399,     5,     5,     5,     5,
       7,     7,     7,     7,     7,   191,   191,     5,     5,   221,
      17,    18,   280,    20,    21,   283,   191,   191,   191,     5,
     191,   191,   221,   191,     7,   191,   221,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   214,   191,   191,   191,    18,   160,   554,   161,   255,
     191,   191,   191,     5,   210,   232,   573,   272,    24,   289,
     290,   291,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   225,   301,   302,   303,   306,   308,   310,   312,   313,
     315,   316,   317,   318,   319,   320,   321,   322,   324,   326,
     328,   330,   331,   332,   301,     7,   297,   298,   299,     7,
     375,   376,   377,     7,   413,   414,   415,     7,   437,   438,
     439,     7,   403,   404,   405,   115,   116,   117,   118,   120,
     335,   336,   337,   338,   339,   340,   341,     7,   509,   510,
       7,   471,   472,   473,     7,   351,   352,   353,   128,   129,
     130,   131,   132,   133,   365,   366,   367,   368,   369,   370,
     371,   372,   136,   137,   138,   225,   344,   345,   346,   347,
     348,   465,   467,   140,   141,   225,   465,   467,   522,   523,
     524,   526,   143,   144,   145,   191,   465,   467,   530,   531,
     532,   533,   535,   536,   542,     7,   580,   581,   222,     7,
     455,   456,   457,   123,   486,   488,   506,   297,     8,     8,
       8,   292,     3,     8,   304,   307,   309,   311,     4,     4,
       4,     4,     4,   323,   325,   327,   329,     4,     4,     4,
       4,     4,     4,     3,     8,     8,   300,     6,     3,   378,
       6,     3,   416,     6,     3,   440,     6,     3,   406,     6,
       3,     3,     6,   511,     3,     6,   474,     6,     3,   354,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   525,   527,     3,     8,     4,
     534,     4,   537,     3,     8,     8,   582,     3,     6,   191,
     223,   224,   458,     6,     3,   489,     8,     6,     4,   290,
       4,     4,     4,     4,   192,   194,   192,   194,   192,     4,
       4,     4,     4,   192,   192,   192,   192,   194,   192,   302,
     301,   299,   381,   377,   419,   415,   443,   439,   225,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   248,
     249,   250,   251,   252,   253,   256,   258,   260,   261,   262,
     264,   266,   313,   373,   391,   393,   395,   397,   407,   408,
     435,   465,   467,   480,   482,   484,   504,   405,   336,   111,
     112,   225,   313,   409,   435,   465,   467,   480,   482,   484,
     512,   513,   514,   515,   516,   518,   510,   477,   473,   357,
     353,   192,   192,   192,   192,   192,   192,   366,   194,   192,
     192,   345,     4,     4,   523,   194,     4,   192,     4,   531,
     170,   172,   173,   225,   313,   465,   467,   583,   584,   585,
     586,   588,   581,     6,     3,   461,   457,     4,   191,    35,
      36,    37,    38,   305,   191,   191,   191,   191,   191,   191,
     191,     8,     8,     8,     8,     3,     8,   517,     4,     8,
       3,     8,     8,   191,   191,   191,   210,   589,     4,   587,
       3,     8,   191,     8,   221,   408,     4,   194,   514,     4,
     192,     4,   584,   191,     5,   191,     7,   590,   591,   592,
       3,     6,   171,   174,   175,   176,   177,   593,   594,   595,
     597,   598,   599,   600,   591,   596,     4,     4,     4,   601,
       3,     8,     4,   194,   192,   192,     4,   594,   191,   191
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   195,   197,   196,   198,   196,   199,   196,   200,   196,
     201,   196,   202,   196,   203,   196,   204,   196,   205,   196,
     206,   196,   207,   196,   208,   196,   209,   196,   210,   210,
     210,   210,   210,   210,   210,   211,   213,   212,   214,   215,
     215,   216,   216,   218,   217,   219,   219,   220,   220,   222,
     221,   223,   223,   224,   224,   225,   227,   226,   229,   228,
     231,   230,   232,   232,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   246,   245,   247,   248,   249,   250,   251,   252,
     254,   253,   255,   255,   255,   255,   255,   257,   256,   259,
     258,   260,   261,   263,   262,   265,   264,   266,   267,   268,
     269,   271,   270,   272,   272,   273,   273,   273,   273,   273,
     273,   273,   275,   274,   277,   276,   279,   278,   280,   280,
     282,   281,   283,   283,   284,   286,   285,   288,   287,   289,
     289,   290,   292,   291,   294,   293,   296,   295,   297,   297,
     298,   298,   300,   299,   301,   301,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   304,   303,   305,
     305,   305,   305,   307,   306,   309,   308,   311,   310,   312,
     314,   313,   315,   316,   317,   318,   319,   320,   321,   323,
     322,   325,   324,   327,   326,   329,   328,   330,   331,   332,
     334,   333,   335,   335,   336,   336,   336,   336,   336,   337,
     338,   339,   340,   341,   343,   342,   344,   344,   345,   345,
     345,   345,   345,   345,   346,   347,   348,   350,   349,   351,
     351,   352,   352,   354,   353,   356,   355,   357,   357,   357,
     358,   358,   360,   359,   362,   361,   364,   363,   365,   365,
     366,   366,   366,   366,   366,   366,   367,   368,   369,   370,
     371,   372,   374,   373,   375,   375,   376,   376,   378,   377,
     380,   379,   381,   381,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   384,   383,   386,   385,
     388,   387,   390,   389,   392,   391,   394,   393,   396,   395,
     398,   397,   399,   399,   399,   399,   400,   402,   401,   403,
     403,   404,   404,   406,   405,   407,   407,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   410,   409,   412,   411,   413,   413,
     414,   414,   416,   415,   418,   417,   419,   419,   420,   420,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     422,   423,   424,   426,   425,   428,   427,   430,   429,   431,
     433,   432,   434,   436,   435,   437,   437,   438,   438,   440,
     439,   442,   441,   443,   443,   444,   444,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   446,   448,   447,   449,
     450,   451,   452,   454,   453,   455,   455,   456,   456,   458,
     457,   460,   459,   461,   461,   462,   462,   462,   462,   462,
     462,   462,   464,   463,   466,   465,   468,   467,   470,   469,
     471,   471,   472,   472,   474,   473,   476,   475,   477,   477,
     478,   478,   479,   479,   479,   479,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   479,   481,   480,   483,
     482,   485,   484,   487,   486,   489,   488,   491,   490,   493,
     492,   495,   494,   497,   496,   499,   498,   501,   500,   503,
     502,   505,   504,   506,   506,   508,   507,   509,   509,   511,
     510,   512,   512,   513,   513,   514,   514,   514,   514,   514,
     514,   514,   514,   514,   514,   514,   515,   517,   516,   518,
     519,   521,   520,   522,   522,   523,   523,   523,   523,   523,
     525,   524,   527,   526,   529,   528,   530,   530,   531,   531,
     531,   531,   531,   531,   532,   534,   533,   535,   537,   536,
     539,   538,   541,   540,   542,   542,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   544,   546,   545,   547,   549,   548,
     550,   551,   553,   552,   554,   554,   556,   555,   558,   557,
     559,   560,   562,   561,   564,   563,   566,   565,   568,   567,
     570,   569,   572,   571,   573,   573,   574,   574,   576,   575,
     577,   579,   578,   580,   580,   582,   581,   583,   583,   584,
     584,   584,   584,   584,   584,   584,   585,   587,   586,   589,
     588,   590,   590,   592,   591,   593,   593,   594,   594,   594,
     594,   594,   596,   595,   597,   598,   599,   601,   600
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     4,     0,     4,     3,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     1,     1,
       0,     4,     1,     1,     3,     0,     6,     0,     6,     1,
       3,     1,     0,     4,     0,     6,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     0,     4,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     6,
       3,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     0,     4
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
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"store-extended-info\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"ip-reservations-unique\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_object", "$@18", "sub_dhcp4", "$@19", "global_params",
  "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "echo_client_id", "match_client_id", "authoritative",
  "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@21",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@22",
  "ddns_qualifying_suffix", "$@23", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "hostname_char_set", "$@24",
  "hostname_char_replacement", "$@25", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "ip_reservations_unique", "interfaces_config", "$@26",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@27", "interfaces_list", "$@28", "dhcp_socket_type", "$@29",
  "socket_type", "outbound_interface", "$@30", "outbound_interface_value",
  "re_detect", "lease_database", "$@31", "sanity_checks", "$@32",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@33",
  "hosts_database", "$@34", "hosts_databases", "$@35", "database_list",
  "not_empty_database_list", "database", "$@36", "database_map_params",
  "database_map_param", "database_type", "$@37", "db_type", "user", "$@38",
  "password", "$@39", "host", "$@40", "port", "name", "$@41", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@42", "keyspace",
  "$@43", "consistency", "$@44", "serial_consistency", "$@45",
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
  "host_reservation_identifiers", "$@46",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@47", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@48", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@49",
  "sub_hooks_library", "$@50", "hooks_params", "hooks_param", "library",
  "$@51", "parameters", "$@52", "expired_leases_processing", "$@53",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@54",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@55",
  "sub_subnet4", "$@56", "subnet4_params", "subnet4_param", "subnet",
  "$@57", "subnet_4o6_interface", "$@58", "subnet_4o6_interface_id",
  "$@59", "subnet_4o6_subnet", "$@60", "interface", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "shared_networks", "$@65", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@66",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@67", "sub_option_def_list", "$@68", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@69",
  "sub_option_def", "$@70", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool4", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "reservations", "$@85", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@86", "sub_reservation",
  "$@87", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@88", "server_hostname", "$@89",
  "boot_file_name", "$@90", "ip_address", "$@91", "ip_addresses", "$@92",
  "duid", "$@93", "hw_address", "$@94", "client_id_value", "$@95",
  "circuit_id_value", "$@96", "flex_id_value", "$@97", "hostname", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "client_classes", "$@101", "client_classes_list", "client_class_entry",
  "$@102", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@103",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@104",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@105", "control_socket_name", "$@106", "dhcp_queue_control", "$@107",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@108", "capacity", "arbitrary_map_entry", "$@109",
  "dhcp_ddns", "$@110", "sub_dhcp_ddns", "$@111", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@112", "server_port",
  "sender_ip", "$@113", "sender_port", "max_queue_size", "ncr_protocol",
  "$@114", "ncr_protocol_value", "ncr_format", "$@115",
  "dep_qualifying_suffix", "$@116", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@117",
  "dep_generated_prefix", "$@118", "dep_hostname_char_set", "$@119",
  "dep_hostname_char_replacement", "$@120", "config_control", "$@121",
  "sub_config_control", "$@122", "config_control_params",
  "config_control_param", "config_databases", "$@123",
  "config_fetch_wait_time", "loggers", "$@124", "loggers_entries",
  "logger_entry", "$@125", "logger_params", "logger_param", "debuglevel",
  "severity", "$@126", "output_options_list", "$@127",
  "output_options_list_content", "output_entry", "$@128",
  "output_params_list", "output_params", "output", "$@129", "flush",
  "maxsize", "maxver", "pattern", "$@130", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   282,   282,   282,   283,   283,   284,   284,   285,   285,
     286,   286,   287,   287,   288,   288,   289,   289,   290,   290,
     291,   291,   292,   292,   293,   293,   294,   294,   302,   303,
     304,   305,   306,   307,   308,   311,   316,   316,   327,   330,
     331,   334,   339,   347,   347,   354,   355,   358,   362,   369,
     369,   376,   377,   380,   384,   395,   404,   404,   419,   419,
     436,   436,   445,   446,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   510,   516,   522,   528,   534,   540,   546,   552,   558,
     564,   570,   576,   576,   585,   591,   597,   603,   609,   615,
     621,   621,   630,   633,   636,   639,   642,   648,   648,   657,
     657,   666,   672,   678,   678,   687,   687,   696,   702,   708,
     714,   720,   720,   732,   733,   736,   737,   738,   739,   740,
     741,   742,   745,   745,   754,   754,   765,   765,   773,   774,
     777,   777,   785,   787,   791,   798,   798,   811,   811,   822,
     823,   825,   827,   827,   846,   846,   859,   859,   870,   871,
     874,   875,   878,   878,   888,   889,   892,   893,   894,   895,
     896,   897,   898,   899,   900,   901,   902,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   915,   915,   923,
     924,   925,   926,   929,   929,   938,   938,   947,   947,   956,
     962,   962,   971,   977,   983,   989,   995,  1001,  1007,  1013,
    1013,  1022,  1022,  1031,  1031,  1040,  1040,  1049,  1055,  1061,
    1068,  1068,  1079,  1080,  1083,  1084,  1085,  1086,  1087,  1090,
    1095,  1100,  1105,  1110,  1117,  1117,  1130,  1131,  1134,  1135,
    1136,  1137,  1138,  1139,  1142,  1148,  1154,  1160,  1160,  1171,
    1172,  1175,  1176,  1179,  1179,  1189,  1189,  1199,  1200,  1201,
    1204,  1205,  1208,  1208,  1217,  1217,  1226,  1226,  1238,  1239,
    1242,  1243,  1244,  1245,  1246,  1247,  1250,  1256,  1262,  1268,
    1274,  1280,  1289,  1289,  1303,  1304,  1307,  1308,  1315,  1315,
    1341,  1341,  1352,  1353,  1357,  1358,  1359,  1360,  1361,  1362,
    1363,  1364,  1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,
    1373,  1374,  1375,  1376,  1377,  1378,  1379,  1380,  1381,  1382,
    1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,  1391,  1392,
    1393,  1394,  1395,  1396,  1397,  1398,  1401,  1401,  1410,  1410,
    1419,  1419,  1428,  1428,  1437,  1437,  1446,  1446,  1455,  1455,
    1466,  1466,  1474,  1475,  1476,  1477,  1480,  1488,  1488,  1500,
    1501,  1505,  1506,  1509,  1509,  1517,  1518,  1521,  1522,  1523,
    1524,  1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,
    1534,  1535,  1536,  1537,  1538,  1539,  1540,  1541,  1542,  1543,
    1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,  1552,  1553,
    1554,  1555,  1556,  1557,  1564,  1564,  1578,  1578,  1587,  1588,
    1591,  1592,  1597,  1597,  1612,  1612,  1626,  1627,  1630,  1631,
    1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,
    1646,  1648,  1654,  1656,  1656,  1665,  1665,  1674,  1674,  1683,
    1685,  1685,  1694,  1704,  1704,  1717,  1718,  1723,  1724,  1729,
    1729,  1741,  1741,  1753,  1754,  1759,  1760,  1765,  1766,  1767,
    1768,  1769,  1770,  1771,  1772,  1773,  1776,  1778,  1778,  1787,
    1789,  1791,  1797,  1806,  1806,  1819,  1820,  1823,  1824,  1827,
    1827,  1837,  1837,  1847,  1848,  1851,  1852,  1853,  1854,  1855,
    1856,  1857,  1860,  1860,  1869,  1869,  1894,  1894,  1924,  1924,
    1935,  1936,  1939,  1940,  1943,  1943,  1952,  1952,  1961,  1962,
    1965,  1966,  1970,  1971,  1972,  1973,  1974,  1975,  1976,  1977,
    1978,  1979,  1980,  1981,  1982,  1983,  1984,  1987,  1987,  1996,
    1996,  2005,  2005,  2014,  2014,  2023,  2023,  2034,  2034,  2043,
    2043,  2052,  2052,  2061,  2061,  2070,  2070,  2079,  2079,  2088,
    2088,  2102,  2102,  2113,  2114,  2120,  2120,  2131,  2132,  2135,
    2135,  2145,  2146,  2149,  2150,  2153,  2154,  2155,  2156,  2157,
    2158,  2159,  2160,  2161,  2162,  2163,  2166,  2168,  2168,  2177,
    2185,  2193,  2193,  2204,  2205,  2208,  2209,  2210,  2211,  2212,
    2215,  2215,  2224,  2224,  2236,  2236,  2249,  2250,  2253,  2254,
    2255,  2256,  2257,  2258,  2261,  2267,  2267,  2276,  2282,  2282,
    2292,  2292,  2305,  2305,  2315,  2316,  2319,  2320,  2321,  2322,
    2323,  2324,  2325,  2326,  2327,  2328,  2329,  2330,  2331,  2332,
    2333,  2334,  2335,  2336,  2339,  2345,  2345,  2354,  2360,  2360,
    2369,  2375,  2381,  2381,  2390,  2391,  2394,  2394,  2404,  2404,
    2414,  2421,  2428,  2428,  2437,  2437,  2447,  2447,  2457,  2457,
    2469,  2469,  2481,  2481,  2491,  2492,  2496,  2497,  2500,  2500,
    2511,  2519,  2519,  2532,  2533,  2537,  2537,  2545,  2546,  2549,
    2550,  2551,  2552,  2553,  2554,  2555,  2558,  2564,  2564,  2573,
    2573,  2584,  2585,  2588,  2588,  2596,  2597,  2600,  2601,  2602,
    2603,  2604,  2607,  2607,  2616,  2622,  2628,  2634,  2634
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
#line 5486 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2643 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
